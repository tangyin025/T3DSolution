/** FILE: main.cpp
	定义了一个基本的 t3dlib 应用程序的框架
*/
#include "resource.h"

// 包含 my 的封装类
#include "libc.h"				// 扩展 string 函数
#include "myGame.h"				// 应用程序封装
#include "myUtility.h"			// 快速模型绘制
#include "myPhysics.h"			// 物理引擎
#include "myCollision.h"		// 碰撞系统
#include "myScene.h"

// unicode 支持
using t3d::charT;

// 实型
using t3d::real;

// ======================================== TODO: BEGIN ========================================

// 在这个地方定义自己的类

void pushVertexByPointProject(
	t3d::RenderContext * rc,
	const t3d::Vec4<real> & point,
	const t3d::Vec4<real> & planePoint,
	const t3d::Vec4<real> & planeNormal,
	t3d::VertexList::const_iterator begin,
	t3d::VertexList::const_iterator end,
	const t3d::Mat4<real> & mmat)
{
	t3d::VertexList::const_iterator vert_iter = begin;
	for(; vert_iter != end; vert_iter++)
	{
		t3d::Vec4<real> tmpVert = *vert_iter * mmat;
		rc->pushVertex(my::calculateLinePlaneIntersectionPoint(
			tmpVert,
			t3d::vec3Sub(tmpVert, point),
			planePoint,
			planeNormal));
	}
}

class CharacterTracker
{
public:
	t3d::Vec4<real> distance;

	t3d::Vec4<real> rotation;
};

class MyWorld
	: public my::World			// 用以支持物理引擎的基本框架
{
public:
	my::CollisionSphere m_characterSphere;	// 用以控制角色的碰撞球
	my::RigidBody * m_characterBody;		// 表示角色运动状态的 rigid body
	my::Object * m_scene;					// 场景的多边形容器，这个场景只是物理场景，可能不参与绘制！
	CharacterTracker m_characterTracker;	// 用以跟踪角色的相机工具
	my::Vec4<real> m_characterRotation;		// 用以跟踪角色面向的向量

protected:
	/** 重写 my::World::integrate 接口
		integrate 是指某个物体在某个时间段之间所发生的微笑变化，这里实质就是将 character rigid body 进行一次微积分计算
	*/
	virtual void integrate(t3d::real duration)
	{
		// 由于 m_characterBody 已经交于 my::World 框架接管，所以只需调用 my::World::integrate 即可
		// 毋需调用 m_characterBody.integrate
		my::World::integrate(duration);

		// 此时 m_characterBody 的数据已经更新，所以需要同时更新对应的 m_characterSphere
		m_characterSphere.calculateInternals();
	}

	/** 实现 my::World::generateContacts 接口
		在这里进行碰撞检测，并生成 contacts
	*/
	virtual unsigned generateContacts(my::Contact * contacts, unsigned limits)
	{
		unsigned used = 0;

		// 对场景中的每一个三角形进行碰撞检测，并生成 contacts
		for(size_t i = 0; i < m_scene->getTriangleCount() && used < limits; i++)
		{
			used += my::CollisionDetector::sphereAndTriangle(
				m_characterSphere,
				m_scene->getTriangleVertex0(i),
				m_scene->getTriangleVertex1(i),
				m_scene->getTriangleVertex2(i),
				NULL,
				&contacts[used],
				limits - used); // *** 这个地方要党性越界
		}

		// 由于目前 my::CollisionDetector 不会设置 friction、restitution，所以一定要手动设置
		for(unsigned i = 0; i < used; i++)
		{
			contacts[i].friction = 10.0f; //0.9f;
			contacts[i].restitution = 0; //0.6f;
		}

		return used;
	}

public:
	MyWorld(real characterSphereRadius, real characterSphereMass, my::Object * scene)
		: my::World(32) // 由于只进行角色碰撞检测，所以最多也只会生成一两个碰撞点而已，也就要那么多的 contacts
	{
		// 由框架创建一个 rigid body
		bodyList.push_back(my::RigidBodyPtr(new my::RigidBody()));
		m_characterBody = bodyList.back().get();

		// 设置角色球的偏移量、半径等
		m_characterSphere.offset = my::Mat4<real>::IDENTITY;
		m_characterSphere.rotationOffset = my::Mat4<real>::IDENTITY;
		m_characterSphere.radius = characterSphereRadius;
		m_characterSphere.body = m_characterBody;

		// 设置 body 的质量及一些参、系数
		m_characterSphere.body->setMass(characterSphereMass);
		real coeff = 0.4f * m_characterSphere.body->getMass() * m_characterSphere.radius * m_characterSphere.radius;
		m_characterSphere.body->setInertialTensor(my::calculateInertiaTensor(coeff, coeff, coeff));
		m_characterSphere.body->setDamping(0.95f);
		//m_characterSphere.body->setAngularDamping(0.8f);
		m_characterSphere.body->setAngularDamping(0); // 这样可以不让角色球旋转
		m_characterSphere.body->setAcceleration(my::Vec4<real>(0, -10.0f, 0));

		// 初始化角色的位置
		m_characterSphere.body->setPosition(my::Vec4<real>(0, 30, 0));
		m_characterSphere.body->setOrientation(my::Quat<real>::IDENTITY);
		m_characterSphere.body->setVelocity(my::Vec4<real>::ZERO);
		m_characterSphere.body->setRotation(my::Vec4<real>::ZERO);
		m_characterSphere.body->setCanSleep();
		m_characterSphere.body->setAwake();

		// 不要忘记更新角色球的 transform
		m_characterSphere.body->calculateDerivedData();

		// 保存场景（指针）
		assert(NULL != scene);
		m_scene = scene;

		// 初始化跟踪器
		m_characterTracker.distance = my::Vec4<real>(0, 0, -20);
		m_characterTracker.rotation = my::Vec4<real>::ZERO;

		// 初始化角色面向
		m_characterRotation = my::Vec4<real>(0, DEG_TO_RAD(180), 0);
	}

	void updateCharacter(t3d::DIKeyboard * keyboard, t3d::DIMouse * mouse, real /*step_time*/)
	{
		// 控制跟踪器的方位
		t3d::vec3AddSelf(m_characterTracker.rotation, my::EularCamera::buildRotOffset(mouse));

		// 控制角色移动
		t3d::Vec4<real> movOffset = my::EularCamera::buildMovOffset(keyboard, m_characterTracker.rotation.y, 20 /** step_time*/);
		if(!IS_ZERO_FLOAT(movOffset.x) || !IS_ZERO_FLOAT(movOffset.y) || !IS_ZERO_FLOAT(movOffset.z))
		{
			// 加个速度就可以了，让框架来移动角色
			m_characterBody->setVelocity(movOffset);

			// 修正角色面部朝向
			my::Vec4<real> offset(movOffset.x, 0, movOffset.z);
			if(!IS_ZERO_FLOAT(t3d::vec3Length(offset)))
			{
				m_characterRotation.y =
					acos(t3d::vec3CosTheta(offset, my::Vec4<real>::UNIT_Z)) * (movOffset.x > 0 ? 1 : -1) + DEG_TO_RAD(180);
			}

			// 唤醒 body
			m_characterBody->setAwake();
		}

		// 限制 x 轴旋转量，用以避开 uvn 垂直死角
		m_characterTracker.rotation.x = t3d::limit(m_characterTracker.rotation.x, DEG_TO_RAD(-80), DEG_TO_RAD(80));
	}
};

typedef boost::shared_ptr<MyWorld> MyWorldPtr;

// ======================================== TODO: END   ========================================

class MyConfig
	: public my::Game::CONFIG_DESC
{
public:
	real m_aspectRatio;

public:
	MyConfig(int width, int height, my::Game::SCREEN_MODE smode, real aspectRatio)
		: my::Game::CONFIG_DESC(width, height, smode)
		, m_aspectRatio(aspectRatio)
	{
	}
};

class MyGame
	: public my::Game						// 用以实现基于帧循环的基本应用程序框架，并已经实现了常见的 primary、back surface 结构
	, public my::ErrorListener				// 实现接受错误信息的接口，这些错误信息通常来自于 my 的封装，这样就可以使用 REPORT_ERROR 宏对这个接口报错
	, public my::DrawnHelper				// 用以绘制常见多边形的帮助类，可用来绘制简单的 sphere、box、plane 等
{
protected:
	// 一个类似控制台的模拟器，可以在 surface 上输出控制台信息
	my::ConsoleSimulatorPtr m_consoleSim;

	// 基于采样的帧速率计算工具
	my::FPSManagerPtr m_fpsMgr;

	// 基于主频的帧速率计算工具，主要提供物理引擎支持
	my::TimerPtr m_timer;

	// 绘制网格的工具
	my::GridPtr m_grid;

	// 欧拉相机，默认可以使用欧拉相机在场景中自由观察
	my::EularCameraPtr m_eularCam;

	// 默认贴图，目的是防止贴图渲染时没有贴图导致出错
	my::ImagePtr m_defaultTexture;

	/** 为什么要使用 ptr，而不直接构造函数？
		应为某些对象在建立时，会用有先决条件，而 my::Game 在构造函数时，还没有初始化一些对象，如 SingleTon 对象
		只有在框架调用 my::Game::onInit(...) 时，这些前提条件才成熟，所以通常是使用 ptr，在 onInit(...) 里边再构造
	*/

	// ======================================== TODO: BEGIN ========================================

	// 在这个地方定义自己的对象

	my::ObjectPtr m_scene;							// 需要一个用来存储场景的容器
	my::BSPNodePtr m_scene_bsp;						// 基于 BSP 的场景，强吧 ^O^！
	my::ImagePtr m_scene_t;							// 场景的贴图
	MyWorldPtr m_world;								// 物理引擎管理器
	my::BoneAssignmentIndexObjectPtr m_character;	// 角色的身体模型
	my::BoneAssignmentIndexObjectPtr m_character_h;	// 角色的头发模型，由于头发使用双面渲染（将来还要带 color key），所以要另外开个 obj
	my::ImagePtr m_character_t;						// 角色的整个贴图

	my::SkeletonAnimationsFromOgreSkeletonPtr m_character_skel; // 角色的骨骼动画集，里边可以藏有一整套动画，是一个以动画名为 key 的 map
	t3d::BoneNodeList m_character_bone_node_list;				// 用以暂存 bone node list
	t3d::BoneTransformList m_character_bone_transform_list;		// 用以暂存 bone transform list

	my::IndexSphereObjectPtr m_skySphere;			// 天空球
	my::ImagePtr m_skySphere_t;						// 天空球的贴图
	t3d::DSBufferPtr m_dsbuffer;					// 背景音乐

	std::vector<DIDEVICEINSTANCE> m_DIDeviceInstList; // 手柄的 instance
	t3d::DIJoystickPtr m_joy;						// dinput joystick，目前仅用于测试

	// ======================================== TODO: END   ========================================

public:
	/** 实现 my::Game::onInit 接口
		通常在应用程序初始化时，框架会掉用这个接口，所以应当在这里实现自定义的初始化操作
	*/
	virtual bool onInit(const CONFIG_DESC & cfg)
	{
		// 初始化模拟控制台
		m_consoleSim = my::ConsoleSimulatorPtr(new my::ConsoleSimulator(10));

		// 将自己注册为 my::ErrorReporter 的监听者
		my::ErrorReporter::getSingleton().addErrorListener(this);

		// 初始化 fps 管理器
		m_fpsMgr = my::FPSManagerPtr(new my::FPSManager());
		m_fpsMgr->start();

		// 初始化并开始 timer
		m_timer = my::TimerPtr(new my::Timer());
		m_timer->start();

		// 初始化网格
		m_grid = my::GridPtr(new my::Grid());

		// 构造欧拉相机
		m_eularCam = my::EularCameraPtr(new my::EularCamera());
		m_eularCam->setDefaultPosition(my::Vec4<real>(-50, 50, -50));
		m_eularCam->setDefaultRotation(my::Vec4<real>(DEG_TO_RAD(45), DEG_TO_RAD(45), DEG_TO_RAD(0)));
		m_eularCam->reset();

		// 根据 aspect ratio 重新调整 clipper rect
		const MyConfig * pcfg = static_cast<const MyConfig *>(&cfg);
		LONG lWidth, lHeight;
		CRect clipper;
		if(pcfg->m_aspectRatio < (real)pcfg->width / (real)pcfg->height)
		{
			lHeight = pcfg->height;
			lWidth = (LONG)(lHeight * pcfg->m_aspectRatio + .5f);
			clipper.left = (pcfg->width - lWidth) / 2;
			clipper.top = 0;
			clipper.right = clipper.left + lWidth;
			clipper.bottom = clipper.top + lHeight;
		}
		else
		{
			lWidth = pcfg->width;
			lHeight = (LONG)(lWidth / pcfg->m_aspectRatio + .5f);
			clipper.left = 0;
			clipper.top = (pcfg->height - lHeight) / 2;
			clipper.right = clipper.left + lWidth;
			clipper.bottom = clipper.top + lHeight;
		}
		_ASSERT(clipper.left	>= m_rback.left);
		_ASSERT(clipper.top		>= m_rback.top);
		_ASSERT(clipper.right	<= m_rback.right);
		_ASSERT(clipper.bottom	<= m_rback.bottom);
		m_rc->setClipperRect(clipper);

		// 添加媒体搜索路径，建立快捷方式时要注意当前路径的位置
		m_resourceMgr->addDir(_T("."));
		m_resourceMgr->addDir(_T("../../common/medias"));

		// load 第一个贴图
		my::IOStreamPtr tmpStream;
		my::ImagePtr tmpImage;
		tmpImage = my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("checker5x5.bmp"))));
		m_defaultTexture = my::ImagePtr(my::ColorConversion::getSingleton().convertImage(tmpImage.get()));

		// ======================================== TODO: BEGIN ========================================

		// 在这个地方初始化自定义的对象

		// load 场景
		tmpStream = my::ResourceMgr::getSingleton().openIOStream(_T("office_tri_list.mesh.xml"));
		m_scene = my::ObjectFromOgreMeshPtr(new my::ObjectFromOgreMesh(tmpStream.get()));

		tmpImage = my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("office_texture.png"))));
		m_scene_t = my::ColorConversion::getSingleton().convertImage(tmpImage.get());

		// 创建 bsp 场景
		m_scene_bsp = my::buildBSPScene(m_scene->getVertexList(), m_scene->getNormalList(), m_scene->getUVList());

		// 构造物理引擎管理器
		m_world = MyWorldPtr(new MyWorld(5.0f, 4.0f * 0.3333f * (real)PI * 5.0f * 5.0f * 5.0f, m_scene.get()));

		// load 角色模型
		tmpStream = my::ResourceMgr::getSingleton().openIOStream(_T("jack_hres.mesh.xml"));
		m_character = my::BoneAssignmentIndexObjectPtr(new my::BoneAssignmentIndexObjectFromOgreMesh(tmpStream.get()));

		tmpStream = my::ResourceMgr::getSingleton().openIOStream(_T("jack_hres_hair.mesh.xml"));
		m_character_h = my::BoneAssignmentIndexObjectPtr(new my::BoneAssignmentIndexObjectFromOgreMesh(tmpStream.get()));

		tmpImage = my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("jack_texture.png"))));
		m_character_t = my::ColorConversion::getSingleton().convertImage(tmpImage.get());

		// load 角色骨骼动画
		tmpStream = my::IOStreamPtr(my::ResourceMgr::getSingleton().openIOStream(_T("jack_anim_stand.skeleton.xml")));
		m_character_skel = my::SkeletonAnimationsFromOgreSkeletonPtr(new my::SkeletonAnimationsFromOgreSkeleton(tmpStream.get()));
		m_character_skel->getSkeletonAnimation("clip1").setNextAnimationName("clip2");
		m_character_skel->getSkeletonAnimation("clip2").setNextAnimationName("clip1");
		m_character_skel->getSkeletonAnimation("clip3").setNextAnimationName("clip4");
		m_character_skel->getSkeletonAnimation("clip4").setNextAnimationName("clip3");
		m_character_skel->setCurrentAnimationName("clip1");
		m_character_skel->setCurrentAnimationTime(0);

		m_character_bone_node_list = m_character_skel->getOrigBoneNodeList();
		m_character_bone_transform_list.resize(m_character_skel->getOrigBoneNodeListSize());

		// load 天空球
		m_skySphere = my::IndexSphereObjectPtr(new my::IndexSphereObject(50000.0f, 20, 20, true));
		tmpImage = my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("1316532925.jpg"))));
		m_skySphere_t = my::ColorConversion::getSingleton().convertImage(tmpImage.get());

		//// load 背景音乐
		//my::WavPtr tmpWav(new my::Wav(my::ResourceMgr::getSingleton().findFileOrException(_T("stationthrob.wav"))));
		//m_dsbuffer = my::createDSoundBufferForWholeWav(m_dsound.get(), tmpWav.get());
		//my::copyWholeWavBufferToDSoundBuffer(m_dsbuffer.get(), tmpWav.get());
		//m_dsbuffer->play();

		//// 查询并创建手柄（仅测试）
		//m_DIDeviceInstList.clear();
		//m_dinput->findJoystickList(m_DIDeviceInstList);
		//if(!m_DIDeviceInstList.empty())
		//{
		//	m_joy = t3d::DIJoystickPtr(m_dinput->createJoystick(m_DIDeviceInstList.front().guidInstance));
		//	m_joy->setCooperativeLevel(m_pwnd->getHandle(), t3d::DIDevice::CL_NORMAL);
		//	m_joy->acquire();
		//}

		// ======================================== TODO: END   ========================================

		return true;
	}

	/** 实现 my::Game::onShutdown 接口
		框架会在退出应用程序时，调用这个接口，用于自定义的销毁，由于基层框架全部使用 smart_ptr，所以不需要 delete
	*/
	virtual void onShutdown(void)
	{
	}

	/** 实现 my::Game::onFrame 接口
		框架会在主线程没有消息处理的时候调用这个接口，应当在这里进行帧操作，如渲染，step 物理引擎等
	*/
	virtual bool onFrame(void)
	{
		// 如果用户输入 space 则 return false 结束应用程序
		if(m_keyboard->isKeyDown(DIK_ESCAPE))
			return false;

		// 累计 fps 管理器
		// fps 管理器是通过不断采样来获得帧速率的，所以没有 timer 灵敏，但普通应用已经足够了
		m_fpsMgr->addFrame();

		// 获得精确帧时间，即上一次 getElapsedTime 到这次之间的时间
		// 注意：为防止由于两帧时间间隔太长，导致物理引擎崩溃，所以设置成最差不得小于 30 帧 / 秒
		const real elapsedTime = std::min((real)m_timer->getElapsedTime(), (real)0.033);

		//// 这里创建一个比窗口小的 clipper 区域，仅用于测试渲染的 clipper bug
		//// 由于软件渲染器，其 clipper 是通过算法实现的，所以若算法不强健，会导致绘图时越过 clipper 区域
		//// 甚至越过窗口区域，所以将绘图区域缩小一部分可以稍微避免，因越界导致系统崩溃的现象
		//CRect clipper(m_rback);
		//clipper.DeflateRect(10, 10);
		//m_rc->setClipperRect(clipper);

		//// 清理 back surface
		//m_rc->fillSurface(m_rc->getClipperRect(), my::Color(0.8f, 0.8f, 0.8f));

		//// 清理 zbuffer
		//m_rc->fillZbuffer(m_rc->getClipperRect(), 0);

		// 设置渲染上下文的 camera
		m_rc->setViewport(m_rc->getClipperRect());
		m_rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), m_rc->getClipperRect().Width(), m_rc->getClipperRect().Height()));
		m_rc->setCameraNearZ(1);
		m_rc->setCameraFarZ(10000);

		//// 从用户输入来更新欧拉相机的坐标和方位
		//m_eularCam->update(m_keyboard.get(), m_mouse.get(), elapsedTime);
		//m_rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEular(m_eularCam->getPosition(), m_eularCam->getRotation()));

		// 设置渲染上下文的 light
		my::Vec4<real> l_pos(-30, 30, -30);
		l_pos *= t3d::mat3RotZXY(m_eularCam->getRotation()) * t3d::mat3Mov(m_eularCam->getPosition());
		m_rc->clearLightList();
		m_rc->pushLightAmbient(my::Vec4<real>(0.2f, 0.2f, 0.2f));
		m_rc->pushLightPoint(my::Vec4<real>(1, 1, 1), l_pos); //my::Vec4<real>(100, 100, -100));

		// 设置渲染上下文的 material
		m_rc->setAmbient(my::Color::WHITE);
		m_rc->setDiffuse(my::Color::WHITE);

		// 设置渲染上下文的 texture
		m_rc->setTextureBuffer(m_defaultTexture->getBits(), m_defaultTexture->getPitch(), m_defaultTexture->getWidth(), m_defaultTexture->getHeight());

		// ======================================== TODO: BEGIN ========================================

		// 这个地方自定义渲染，可改变之前渲染上下文的设置

		// 更新角色状态
		m_world->updateCharacter(m_keyboard.get(), m_mouse.get(), elapsedTime);

		// 以十倍的速度运行物理引擎
		int count = 10;
		while(count--)
		{
			m_world->runPhysics(elapsedTime / 10);
		}

		// 重新设定相机为 uvn 相机
		real cameraHeight = 20;
		t3d::Mat4<real> cameraOffset = t3d::CameraContext::buildCameraTransformEular(t3d::vec3Add(m_world->m_characterBody->getPosition(), my::Vec4<real>(0, cameraHeight, 0)), m_world->m_characterTracker.rotation);
		t3d::Vec4<real> cameraPos = m_world->m_characterTracker.distance * cameraOffset;
		m_rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformUVN(cameraPos, t3d::vec3Add(m_world->m_characterBody->getPosition(), my::Vec4<real>(0, cameraHeight, 0)), my::Vec4<real>::UNIT_Y));

		// 设置渲染上下文的 light
		l_pos = my::Vec4<real>(-30, 30, -30);
		l_pos *= cameraOffset;
		m_rc->clearLightList();
		m_rc->pushLightAmbient(my::Vec4<real>(0.2f, 0.2f, 0.2f));
		m_rc->pushLightPoint(my::Vec4<real>(1, 1, 1), l_pos);

		// 使用天空球来清理 surface 和 zbuffer
		m_rc->setCameraFarZ(100000);
		m_rc->setTextureBuffer(
			m_skySphere_t->getBits(),
			m_skySphere_t->getPitch(),
			m_skySphere_t->getWidth(),
			m_skySphere_t->getHeight());
		m_skySphere->drawTextureZBufferW(m_rc.get());
		m_rc->setCameraFarZ(10000);

		// 绘制 BSP 场景
		m_rc->setTextureBuffer(
			m_scene_t->getBits(),
			m_scene_t->getPitch(),
			m_scene_t->getWidth(),
			m_scene_t->getHeight());
		//m_scene->drawGouraudTexturePerspectiveLPZBufferRW(m_rc.get());
		m_scene_bsp->drawGouraudTexturePerspectiveLPZBufferRW(m_rc.get());

		//// 绘制角色球
		//drawSphereWireZBufferRW(
		//	m_rc.get(),
		//	m_world->m_characterSphere.radius,
		//	m_world->m_characterBody->getAwake() ? my::Color::RED : t3d::rgbaSaturate(t3d::vec3Sub(my::Color::RED, my::Vec4<real>(0.1f, 0.1f, 0.1f))),
		//	m_world->m_characterSphere.getTransform());

		// 注意：由于 2009年12月12日 修改了骨骼系统的底层，所以原先支持各个动作间过渡的功能目前不能使用
		std::string current_anim_name = m_character_skel->getCurrentAnimationName();
		if (t3d::vec3Length(m_world->m_characterBody->getVelocity()) > 1)
		{
			// 更新动画
			if(current_anim_name != "clip3" && current_anim_name != "clip4")
			{
				m_character_skel->setCurrentAnimationName("clip3");
				m_character_skel->setCurrentAnimationTime(0);
			}
		}
		else
		{
			// 更新动画
			if(current_anim_name != "clip1" && current_anim_name != "clip2")
			{
				m_character_skel->setCurrentAnimationName("clip1");
				m_character_skel->setCurrentAnimationTime(0);
			}
		}

		// 绑定角色骨骼系统
		const t3d::BoneNodeList & boneNodeList =
			m_character_skel->gotoAnimation(m_character_skel->getCurrentAnimationName(), m_character_skel->getCurrentAnimationTime() + elapsedTime);

		// 和 banding position 叠加
		t3d::incrementBoneNodeList(
			m_character_bone_node_list,
			m_character_skel->getOrigBoneNodeList(),
			boneNodeList,
			m_character_skel->getRootIndexListBegin(),
			m_character_skel->getRootIndexListEnd());

		// 获取当前动作的 transform matrix
		t3d::updateBoneTransformListFromBoneNodeList(
			m_character_bone_transform_list,
			m_character_bone_node_list,
			my::Mat4<real>::IDENTITY,
			my::Mat4<real>::IDENTITY,
			m_character_skel->getRootIndexListBegin(),
			m_character_skel->getRootIndexListEnd());

		// 获取最终 bone transform list
		t3d::combineVertexNormalBoneTransformList(
			m_character_bone_transform_list,
			m_character_skel->getOrigBoneInverseTransformList(),
			m_character_bone_transform_list);

		// 将骨骼应用到原始模型
		t3d::bindVertexListNormalListFromBoneTransformList(
			m_character->getVertexList(),
			m_character->getNormalList(),
			m_character->getOriginalVertexList(),
			m_character->getOriginalNormalList(),
			m_character->getBoneAssignmentList(),
			m_character_bone_transform_list);

		t3d::bindVertexListNormalListFromBoneTransformList(
			m_character_h->getVertexList(),
			m_character_h->getNormalList(),
			m_character_h->getOriginalVertexList(),
			m_character_h->getOriginalNormalList(),
			m_character_h->getBoneAssignmentList(),
			m_character_bone_transform_list);

		// 获得角色球的相关变换信息
		t3d::Mat4<real> mrot = t3d::mat3RotY(m_world->m_characterRotation.y);
		t3d::Mat4<real> mmat = mrot * t3d::mat3Mov(my::Vec4<real>(0, -5.0f, 0)) * m_world->m_characterSphere.getTransform();

		// 设置角色贴图
		m_rc->setTextureBuffer(
			m_character_t->getBits(),
			m_character_t->getPitch(),
			m_character_t->getWidth(),
			m_character_t->getHeight());

		// 绘制角色
		m_character->drawGouraudTextureZBufferRW(m_rc.get(), mmat, mrot);
		m_character_h->drawGouraudTextureZBufferRWWithBackface(m_rc.get(), mmat, mrot);

		// 绘制角色阴影，hack 手法
		m_rc->clearVertexList();
		m_rc->clearVertexIndexList();
		pushVertexByPointProject(
			m_rc.get(),
			l_pos,
			my::Vec4<real>(0, 0.5f, 0),
			my::Vec4<real>::UNIT_Y,
			m_character->getVertexListBegin(),
			m_character->getVertexListEnd(),
			mmat);
		m_rc->pushVertexIndexList(m_character->getVertexIndexListBegin(), m_character->getVertexIndexListEnd());
		m_rc->drawTriangleIndexListZBufferRW(my::Color(0.2f, 0.2f, 0.2f));

		m_rc->clearVertexList();
		m_rc->clearVertexIndexList();
		pushVertexByPointProject(
			m_rc.get(),
			l_pos,
			my::Vec4<real>(0, 0.5f, 0),
			my::Vec4<real>::UNIT_Y,
			m_character_h->getVertexListBegin(),
			m_character_h->getVertexListEnd(),
			mmat);
		m_rc->pushVertexIndexList(m_character_h->getVertexIndexListBegin(), m_character_h->getVertexIndexListEnd());
		m_rc->drawTriangleIndexListZBufferRW(my::Color(0.2f, 0.2f, 0.2f));

		// ======================================== TODO: END   ========================================

		//// 渲染网格
		//m_grid->drawZBufferRW(m_rc.get());

		// 输出常用信息，如帧速率、相机方位等
		std::basic_string<charT> strTmp;
		HDC hdc = m_sback->getDC();

		int textx = m_rc->getClipperRect().left + 10;
		int texty = m_rc->getClipperRect().top + 10;

		strTmp = str_printf(_T("fps: %.1f"), m_fpsMgr->getFPS());
		::TextOut(hdc, textx, texty, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("fps: %.1f"), 1 / elapsedTime);
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("cam.pos: %f, %f, %f"),
			m_rc->getCameraPosition().x, m_rc->getCameraPosition().y, m_rc->getCameraPosition().z);
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("cam.rot: %f, %f, %f"),
			RAD_TO_DEG(m_eularCam->getRotation().x), RAD_TO_DEG(m_eularCam->getRotation().y), RAD_TO_DEG(m_eularCam->getRotation().z));
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		//// 输出手柄信息（仅测试）
		//if(m_joy.get())
		//{
		//	m_joy->update();

		//	strTmp = str_printf(_T("%s lstick: %ld, %ld"),
		//		m_DIDeviceInstList.front().tszInstanceName, m_joy->getX(), m_joy->getY());
		//	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		//	strTmp = str_printf(_T("%s rstick: %ld, %ld"),
		//		m_DIDeviceInstList.front().tszInstanceName, m_joy->getRz(), m_joy->getZ());
		//	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());
		//}

		m_sback->releaseDC(hdc);

		// 绘制控制台模拟器
		m_consoleSim->draw(m_sback.get(), 10, texty += 20);

		return true;
	}

	/** 实现 ErrorListener::onReport 接口
		用以接收来自框架的错误 message，并将其打印到模拟控制台
	*/
	virtual void onReport(const std::basic_string<charT> & info)
	{
		// 将错误信息打印到控制台模拟器，这里稍微作了判断以防止答应重复信息
		if(m_consoleSim->m_lines.empty() || info != m_consoleSim->m_lines.back())
		{
			m_consoleSim->report(info);
		}
	}
};

class MyDialog
	: public my::ModelDialog	// 定义一个简单的 model 对话框，用来保存设置
{
public:
	MyConfig m_cfg;				// 这个用来保存用户自定义设置

public:
	/** 构造函数
		在这个地方已经开始了模式对话框，调用方可以通过 m_nResult 会的对话框的返回值
	*/
	MyDialog(const MyConfig & cfg)
		: ModelDialog(::GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), ::GetDesktopWindow())
		, m_cfg(cfg)
	{
	}

	/** 重载 onProc 函数
		用以初始化或保存用户在界面上的设置
	*/
	virtual INT_PTR onProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
		case WM_INITDIALOG:
			// 在这里初始界面值
			::SetWindowText(m_hdlg, _T("User Configuration"));
			VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("320x240")));
			VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("640x480")));
			VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("800x600")));
			VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1024x768")));
			VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1280x800")));
			VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1280x1024")));
			VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1366x768")));
			VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1680x1050")));
			VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_SELECTSTRING, (WPARAM)-1, (LPARAM)_T("800x600")));
			::SendMessage(m_hdlg, WM_COMMAND, MAKEWPARAM(IDC_COMBO1, CBN_SELCHANGE), (LPARAM)::GetDlgItem(m_hdlg, IDC_COMBO1));
			switch(m_cfg.smode)
			{
			case my::Game::SM_FULLSCREEN16:
				VERIFY(::CheckRadioButton(m_hdlg, IDC_RADIO1, IDC_RADIO3, IDC_RADIO2));
				break;
			case my::Game::SM_FULLSCREEN32:
				VERIFY(::CheckRadioButton(m_hdlg, IDC_RADIO1, IDC_RADIO3, IDC_RADIO3));
				break;
			default:
				VERIFY(::CheckRadioButton(m_hdlg, IDC_RADIO1, IDC_RADIO3, IDC_RADIO1));
				break;
			}
			break;

		case WM_COMMAND:
			switch(HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				{
					int nIndex = ::SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
					_ASSERT(CB_ERR != nIndex);
					std::basic_string<charT> strTmp;
					strTmp.resize(::SendMessage((HWND)lParam, CB_GETLBTEXTLEN, nIndex, 0));
					VERIFY(CB_ERR != ::SendMessage((HWND)lParam, CB_GETLBTEXT, nIndex, (LPARAM)&strTmp[0]));
					int nWidth, nHeight;
					VERIFY(2 == _stscanf_s(strTmp.c_str(), _T("%dx%d"), &nWidth, &nHeight));
					VERIFY(::SetDlgItemInt(m_hdlg, IDC_EDIT1, nWidth, FALSE));
					VERIFY(::SetDlgItemInt(m_hdlg, IDC_EDIT2, nHeight, FALSE));
					real aspectRatio = (real)nWidth / nHeight;
					if((real)4 / 3 == aspectRatio)
					{
						VERIFY(::CheckRadioButton(m_hdlg, IDC_RADIO4, IDC_RADIO6, IDC_RADIO5));
					}
					else if((real)16 / 9 == aspectRatio)
					{
						VERIFY(::CheckRadioButton(m_hdlg, IDC_RADIO4, IDC_RADIO6, IDC_RADIO6));
					}
					else
					{
						VERIFY(::CheckRadioButton(m_hdlg, IDC_RADIO4, IDC_RADIO6, IDC_RADIO4));
					}
				}
				break;

			default:
				switch(LOWORD(wParam))
				{
				case IDOK:
					// 在这里保存界面值
					m_cfg.width = ::GetDlgItemInt(m_hdlg, IDC_EDIT1, NULL, FALSE);
					m_cfg.height = ::GetDlgItemInt(m_hdlg, IDC_EDIT2, NULL, FALSE);
					if(::IsDlgButtonChecked(m_hdlg, IDC_RADIO1))
					{
						m_cfg.smode = my::Game::SM_WINDOWED;
					}
					else if(::IsDlgButtonChecked(m_hdlg, IDC_RADIO2))
					{
						m_cfg.smode = my::Game::SM_FULLSCREEN16;
					}
					else
					{
						_ASSERT(::IsDlgButtonChecked(m_hdlg, IDC_RADIO3));
						m_cfg.smode = my::Game::SM_FULLSCREEN32;
					}
					if(::IsDlgButtonChecked(m_hdlg, IDC_RADIO4))
					{
						m_cfg.m_aspectRatio = (real)m_cfg.width / m_cfg.height;
					}
					else if(::IsDlgButtonChecked(m_hdlg, IDC_RADIO5))
					{
						m_cfg.m_aspectRatio = (real)4 / 3;
					}
					else
					{
						_ASSERT(::IsDlgButtonChecked(m_hdlg, IDC_RADIO6));
						m_cfg.m_aspectRatio = (real)16 / 9;
					}
					break;
				}
				break;
			}
			break;
		}
		return ModelDialog::onProc(hwndDlg, uMsg, wParam, lParam);
	}
};

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 在这个地方读取用户自定义分辨率，屏幕设置等，详情参考 my::Game::SCREEN_MODE
	MyDialog dlg(MyConfig(800, 600, my::Game::SM_WINDOWED, (real)800 / 600));
	return IDOK != dlg.doModel() ? 0 : MyGame().run(dlg.m_cfg);

	//// 下面是可运行最简单的应用程序模型
	//my::Application app;
	//my::Window * pwnd = app.createWindow(_T("Hello world"));
	//pwnd->showWindow();
	//pwnd->updateWindow();
	//return app.run();

	//// 下面是可运行最简单的游戏框架模型
	//return my::Game().run();
}
