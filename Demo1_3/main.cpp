/** FILE: main.cpp
	定义了一个基本的 my::Game 应用程序的框架
*/

// 包含 my 的封装类
#include "libc.h"				// 扩展 string 函数
#include "myGame.h"				// 应用程序封装
#include "myUtility.h"			// 快速模型绘制
#include "myPhysics.h"			// 物理引擎
#include "myCollision.h"		// 碰撞系统
#include "myScene.h"			// 场景管理

// unicode 支持
using t3d::charT;

// 实型
using t3d::real;

// ======================================== TODO: BEGIN ========================================

// 在这个地方定义自己的类

// ======================================== TODO: END   ========================================

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

	t3d::DSBufferPtr m_dsbuffer;
	t3d::DS3DBufferPtr m_ds3dbuffer;
	t3d::DS3DListenerPtr m_ds3dlistener;

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

		// 测试 direct sound 3d buffer
		my::WavPtr tmpWav(new my::Wav(my::ResourceMgr::getSingleton().findFileOrException(_T("MusicMono.wav"))));
		m_dsbuffer = my::createDSoundBufferForWholeWav(m_dsound.get(), tmpWav.get(), DSBCAPS_CTRL3D);
		m_ds3dbuffer = m_dsbuffer->getDS3DBuffer();

		// 注意，listener 必须是 primary sound buffer 才能创建
		DSBUFFERDESC ddsc = {sizeof(ddsc)};
		ddsc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
		t3d::DSBufferPtr dsbprimary = m_dsound->createSoundBuffer(&ddsc);
		m_ds3dlistener = dsbprimary->getDS3DListener();

		// 设置 3dbuffer parameter
		DS3DBUFFER ds3dbp = {sizeof(ds3dbp)};
		m_ds3dbuffer->getAllParameters(&ds3dbp);
		DS3DLISTENER ds3dlp = {sizeof(ds3dlp)};
		m_ds3dlistener->getAllParameters(&ds3dlp);

		m_ds3dbuffer->setMinDistance(1);
		m_ds3dbuffer->setMaxDistance(50);
		ds3dlp.flDopplerFactor = 0;
		ds3dlp.flRolloffFactor = 0.5;
		m_ds3dlistener->setAllParameters(&ds3dlp);
		m_ds3dlistener->commitDeferredSettings();

		// 播放声音
		my::copyWholeWavBufferToDSoundBuffer(m_dsbuffer.get(), tmpWav.get());
		m_dsbuffer->play(0, DSBPLAY_LOOPING);

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

		// 清理 back surface
		m_rc->fillSurface(m_rc->getClipperRect(), my::Color(0.8f, 0.8f, 0.8f));

		// 清理 zbuffer
		m_rc->fillZbuffer(m_rc->getClipperRect(), 0);

		// 设置渲染上下文的 camera
		m_rc->setViewport(m_rc->getClipperRect());
		m_rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), m_rc->getClipperRect().Width(), m_rc->getClipperRect().Height()));
		m_rc->setCameraNearZ(1);
		m_rc->setCameraFarZ(10000);

		// 从用户输入来更新欧拉相机的坐标和方位
		m_eularCam->update(m_keyboard.get(), m_mouse.get(), elapsedTime);
		m_rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEular(m_eularCam->getPosition(), m_eularCam->getRotation()));

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

		m_ds3dlistener->setPosition(m_eularCam->getPosition().x, m_eularCam->getPosition().y, m_eularCam->getPosition().z);
		my::Mat4<real> mCameraRotation = t3d::mat4GetRotationScalePart(m_rc->getCameraMatrix().inverse());
		my::Vec4<real> vFront = my::Vec4<real>::UNIT_Z * mCameraRotation;
		my::Vec4<real> vTop = my::Vec4<real>::UNIT_Y * mCameraRotation;
		m_ds3dlistener->setOrientation(vFront.x, vFront.y, vFront.z, vTop.x, vTop.y, vTop.z);
		m_ds3dlistener->commitDeferredSettings();

		// ======================================== TODO: END   ========================================

		// 渲染网格
		m_grid->drawZBufferRW(m_rc.get());

		// 输出常用信息，如帧速率、相机方位等
		std::basic_string<charT> strTmp;
		HDC hdc = m_sback->getDC();

		int textx = m_rc->getClipperRect().left + 10;
		int texty = m_rc->getClipperRect().top + 10;

		strTmp = str_printf(_T("fps: %.1f"), m_fpsMgr->getFPS());
		::TextOut(hdc, textx, texty, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("fps: %.1f"), 1 / elapsedTime);
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		t3d::Vec4<real> camPos = t3d::CameraContext::calculateCameraPosition(m_rc->getCameraMatrix());
		strTmp = str_printf(_T("cam.pos: %f, %f, %f"),
			camPos.x, camPos.y, camPos.z);
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("cam.rot: %f, %f, %f"),
			RAD_TO_DEG(m_eularCam->getRotation().x), RAD_TO_DEG(m_eularCam->getRotation().y), RAD_TO_DEG(m_eularCam->getRotation().z));
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

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

int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	// 运行时内存泄漏检查
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));

	// 在这个地方读取用户自定义分辨率，屏幕设置等，详情参考 my::Game::SCREEN_MODE
	return MyGame().run(my::Game::CONFIG_DESC(800, 600, my::Game::SM_WINDOWED));

	//// 下面是可运行最简单的应用程序模型
	//my::Application app;
	//my::Window * pwnd = app.createWindow(_T("Hello world"));
	//pwnd->showWindow();
	//pwnd->updateWindow();
	//return app.run();

	//// 下面是可运行最简单的游戏框架模型
	//return my::Game().run();
}
