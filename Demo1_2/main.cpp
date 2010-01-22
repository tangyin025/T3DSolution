
// 包含 c++ 库文件
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <crtdbg.h>
#include <boost/shared_array.hpp>

// 包含 3d 图形库
#include "t3dlib1.h"
#include "t3dlib2.h"
#include "t3dlib3.h"
#include "t3dlib4.h"
#include "t3dlib5.h"
#include "t3dlib6.h"

// 包含 my 的封装
#include "libc.h"				// c 样式 string 函数
#include "myGame.h"				// 应用程序封装
#include "myUtility.h"			// 快速模型绘制
#include "myPhysics.h"			// 物理引擎
#include "myCollision.h"		// 碰撞系统
#include "myScene.h"

// 附加 windows 多媒体库
#pragma comment(lib, "winmm.lib")

using t3d::charT;				// unicode 支持
using t3d::real;				// 实型

// ======================================== TODO: BEGIN ========================================

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

	void updateCharacter(t3d::DIKeyboard * keyboard, t3d::DIMouse * mouse, real step_time)
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
			m_characterRotation.y =
				acos(t3d::vec3CosTheta(my::Vec4<real>(movOffset.x, 0, movOffset.z), my::Vec4<real>::UNIT_Z)) * (movOffset.x > 0 ? 1 : -1) + DEG_TO_RAD(180);

			// 唤醒 body
			m_characterBody->setAwake();
		}

		// 限制 x 轴旋转量，用以避开 uvn 垂直死角
		m_characterTracker.rotation.x = std::min(DEG_TO_RAD(80), std::max(DEG_TO_RAD(-80), m_characterTracker.rotation.x));
	}
};

// ======================================== TODO: END   ========================================

typedef boost::shared_ptr<MyWorld> MyWorldPtr;

class MyGame
	: public my::Game						// 用以实现基于帧循环的基本应用程序框架，并已经实现了常见的 primary、back surface 结构
	, public my::DrawnHelper				// 用以绘制常见多边形，如 sphere、box、plane 等
	, public my::ErrorListener				// 实现接受错误信息的接口，这些错误信息通常来自于 my 的封装，也可以使用 REPORT_ERROR 宏对这个接口报错
{
protected:
	my::ConsoleSimulatorPtr m_consoleSim;	// 一个类似控制台的模拟器，可以在 surface 上输出控制台信息
	my::TimerPtr m_timer;					// 管理时间的工具，主要用以精确帧速率计算
	my::FPSManagerPtr m_fpsMgr;				// 管理 fps 的工具，模糊帧速率计算
	my::GridPtr m_grid;						// 绘制网格的工具
	my::EularCameraPtr m_eularCam;			// 欧拉相机
	my::ImagePtr m_defaultTexture;			// 默认贴图

	/** 为什么要使用 ptr，而不直接构造函数？
	应为某些对象在建立时，会用有先决条件，而 my::Game 在构造函数时，还没有初始化一些对象，如 SingleTon 对象
	只有在 my::Game::onInit(...) 之后，这些前提条件才成熟，
	所以通常是使用 ptr，在 onInit(...) 里边再构造
	*/

	// ======================================== TODO: BEGIN ========================================

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
	virtual bool onInit(void)
	{
		// 初始化控制台模拟器
		m_consoleSim = my::ConsoleSimulatorPtr(new my::ConsoleSimulator(10));

		// 将自己注册为 my::ErrorReporter 的监听者
		my::ErrorReporter::getSingleton().addErrorListener(this);

		// 初始化并开始 timer
		m_timer = my::TimerPtr(new my::Timer());
		m_timer->start();

		// 初始化 fps 管理器
		m_fpsMgr = my::FPSManagerPtr(new my::FPSManager());
		m_fpsMgr->start();

		// 初始化网格
		m_grid = my::GridPtr(new my::Grid());

		// 构造欧拉相机
		m_eularCam = my::EularCameraPtr(new my::EularCamera());
		m_eularCam->setDefaultPosition(my::Vec4<real>(-50, 50, -50));
		m_eularCam->setDefaultRotation(my::Vec4<real>(DEG_TO_RAD(45), DEG_TO_RAD(45), DEG_TO_RAD(0)));
		m_eularCam->reset();

		// 添加媒体搜索路径，建立快捷方式时要注意当前路径的位置
		m_resourceMgr->registerDir(_T("../../common/medias"));
		my::IOStreamPtr tmpStream;
		my::ImagePtr tmpImage;

		// load 第一个贴图
		tmpImage = my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("checker5x5.bmp"))));
		m_defaultTexture = my::ImagePtr(my::ColorConversion::getSingleton().convertImage(tmpImage.get()));

		// ======================================== TODO: BEGIN ========================================

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

		// 获得精确帧时间，即上一次 getElapsedTime 到这次之间的时间
		// 注意：为防止由于两帧时间间隔太长，导致物理引擎崩溃，所以设置成最差不得小于 30 帧 / 秒
		const real elapsedTime = std::min((real)m_timer->getElapsedTime(), (real)0.033);

		// 累计 fps 管理器
		// fps 管理器是通过不断采样来获得帧速率的，所以没有 timer 灵敏，但普通应用已经足够了
		m_fpsMgr->addFrame();

		// 这里创建一个比窗口小的 clipper 区域，仅用于测试 3d 渲染得 clipper bug
		// 由于软件渲染器，其 clipper 是通过算法实现的，所以若算法不强健，回到之绘图时越过 clipper 区域
		// 甚至越过窗口区域，所以将绘图区域缩小一部分可以稍微避免，因越界导致系统崩溃的现象
		RECT clipper = {m_rback.left + 10, m_rback.top + 10, m_rback.right - 10, m_rback.bottom - 10};
		m_rc->setClipperRect(clipper);

		//// 清理 back surface
		//m_rc->fillSurface(clipper, my::Color(0.8f, 0.8f, 0.8f));

		//// 清理 zbuffer
		//m_rc->fillZbuffer(clipper, 0);

		// 设置渲染上下文的 camera
		m_rc->setViewport(m_rc->getClipperRect());
		m_rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVHeight(DEG_TO_RAD(90), m_rc->getClipperRect().right - m_rc->getClipperRect().left, m_rc->getClipperRect().bottom - m_rc->getClipperRect().top));
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

		t3d::STreeNode::IndexList::const_iterator root_iter = m_character_skel->getRootIndexListBegin();
		for(; root_iter != m_character_skel->getRootIndexListEnd(); root_iter++)
		{
			// 和 banding position 叠加
			t3d::incrementBoneNodeList(
				m_character_bone_node_list,
				m_character_skel->getOrigBoneNodeList(),
				boneNodeList,
				*root_iter);

			// 获取当前动作的 transform matrix
			t3d::updateBoneTransformListFromBoneNodeList(
				m_character_bone_transform_list,
				m_character_bone_node_list,
				*root_iter,
				my::Mat4<real>::IDENTITY,
				my::Mat4<real>::IDENTITY);
		}

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
		my::pushVertexByPointProject(
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
		my::pushVertexByPointProject(
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

		strTmp = str_printf(_T("fps: %.1f"), 1 / elapsedTime);
		::TextOut(hdc, 10, 10, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("fps: %.1f"), m_fpsMgr->getFPS());
		::TextOut(hdc, 10, 30, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("cam.pos: %f, %f, %f"),
			m_rc->getCameraPosition().x, m_rc->getCameraPosition().y, m_rc->getCameraPosition().z);
		::TextOut(hdc, 10, 50, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("cam.rot: %f, %f, %f"),
			RAD_TO_DEG(m_eularCam->getRotation().x), RAD_TO_DEG(m_eularCam->getRotation().y), RAD_TO_DEG(m_eularCam->getRotation().z));
		::TextOut(hdc, 10, 70, strTmp.c_str(), (int)strTmp.length());

		//// 输出手柄信息
		//if(m_joy.get())
		//{
		//	m_joy->update();

		//	strTmp = str_printf(_T("%s lstick: %ld, %ld"),
		//		m_DIDeviceInstList.front().tszInstanceName, m_joy->getX(), m_joy->getY());
		//	::TextOut(hdc, 10, 90, strTmp.c_str(), (int)strTmp.length());

		//	strTmp = str_printf(_T("%s rstick: %ld, %ld"),
		//		m_DIDeviceInstList.front().tszInstanceName, m_joy->getRz(), m_joy->getZ());
		//	::TextOut(hdc, 10, 110, strTmp.c_str(), (int)strTmp.length());
		//}

		m_sback->releaseDC(hdc);

		// 绘制控制台模拟器
		m_consoleSim->draw(m_sback.get(), 10, 10);

		return true;
	}

	void onReport(const std::basic_string<charT> & info)
	{
		// 将错误信息打印到控制台模拟器，这里稍微作了判断以防止答应重复信息
		if(m_consoleSim->m_lines.empty() || info != m_consoleSim->m_lines.back())
		{
			m_consoleSim->report(info);
		}
	}

	//BOOL notifyMessage(LRESULT & lResult, my::Window * win, UINT message, WPARAM wparam, LPARAM lparam)
	//{
	//	switch(message)
	//	{
	//	case WM_KEYDOWN:
	//		switch(wparam)
	//		{
	//		case VK_F1:
	//			prepareConfig(my::GameBase::CONFIG_DESC(640, 480, SM_WINDOWED));
	//			break;

	//		case VK_F2:
	//			prepareConfig(my::GameBase::CONFIG_DESC(800, 600, SM_WINDOWED));
	//			break;

	//		case VK_F3:
	//			prepareConfig(my::GameBase::CONFIG_DESC(1024, 768, SM_WINDOWED));
	//			break;

	//		case VK_F4:
	//			prepareConfig(my::GameBase::CONFIG_DESC(1280, 1024, SM_WINDOWED));
	//			break;
	//		}
	//		lResult = 0;
	//		return TRUE;
	//	}

	//	return FALSE;
	//}
};

int APIENTRY WinMain(
	HINSTANCE	/*hInstance*/,
	HINSTANCE	/*hPrevInstance*/,
	LPSTR		/*lpCmdLine*/,
	int			/*nCmdShow*/)
{
	MyGame game;
	return game.run(my::Game::CONFIG_DESC(800, 600, my::Game::SM_WINDOWED));
}
