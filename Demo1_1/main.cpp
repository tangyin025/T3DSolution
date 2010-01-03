
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

class MyGame
	: public my::Game			// 用以实现基于帧循环的基本应用程序框架，并已经实现了常见的 primary、back surface 结构
	, public my::DrawnHelper			// 用以绘制常见多边形，如 sphere、box、plane 等
	, public my::ErrorListener	// 实现接受错误信息的接口，这些错误信息通常来自于 my 的封装，也可以使用 REPORT_ERROR 宏对这个接口报错
	, public my::Window::MessageListener
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

	// 自定义成员
	my::BoneAssignmentIndexObjectPtr m_jackModel;

	my::ImagePtr m_jackTexture;

	my::SkeletonAnimationsFromOgreSkeletonPtr m_jackSkeleton;

	t3d::BoneNodeList m_jackBoneNodeList;

	t3d::BoneTransformList m_jackBoneTransformList;

	t3d::DSBufferPtr m_dsbuffer;

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
		m_eularCam->setDefaultPosition(my::Vec4<real>(50, 50, -50));
		m_eularCam->setDefaultRotation(my::Vec4<real>(DEG_TO_RAD(45), DEG_TO_RAD(-45), DEG_TO_RAD(0)));
		m_eularCam->reset();

		// 添加媒体搜索路径，建立快捷方式时要注意当前路径的位置
		m_resourceMgr->registerDir(_T("../../common/medias"));

		// load 第一个贴图
		my::ImagePtr tmpImage;
		tmpImage = my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("checker5x5.bmp"))));
		m_defaultTexture = my::ImagePtr(my::ColorConversion::getSingleton().convertImage(tmpImage.get()));

		// ======================================== TODO: BEGIN ========================================

		// 自定义初始化
		my::IOStreamPtr tmpStream;
		tmpStream = my::IOStreamPtr(my::ResourceMgr::getSingleton().openIOStream(_T("jack_hres.mesh.xml")));
		m_jackModel = my::BoneAssignmentIndexObjectPtr(new my::BoneAssignmentIndexObjectFromOgreMesh(tmpStream.get()));

		tmpImage = my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("jack_texture.png"))));
		m_jackTexture = my::ImagePtr(my::ColorConversion::getSingleton().convertImage(tmpImage.get()));

		tmpStream = my::IOStreamPtr(my::ResourceMgr::getSingleton().openIOStream(_T("jack_anim_stand.skeleton.xml")));
		m_jackSkeleton = my::SkeletonAnimationsFromOgreSkeletonPtr(new my::SkeletonAnimationsFromOgreSkeleton(tmpStream.get()));
		m_jackSkeleton->getSkeletonAnimation("clip1").setNextAnimationName("clip2");
		m_jackSkeleton->getSkeletonAnimation("clip2").setNextAnimationName("clip1");
		m_jackSkeleton->getSkeletonAnimation("clip3").setNextAnimationName("clip4");
		m_jackSkeleton->getSkeletonAnimation("clip4").setNextAnimationName("clip3");
		m_jackSkeleton->setCurrentAnimationName("clip3");
		m_jackSkeleton->setCurrentAnimationTime(0);

		m_jackBoneNodeList = m_jackSkeleton->getOrigBoneNodeList();

		m_jackBoneTransformList.resize(m_jackSkeleton->getOrigBoneNodeListSize());

		//// load 背景音乐
		//my::WavPtr tmpWav = my::WavPtr(new my::Wav(my::ResourceMgr::getSingleton().findFileOrException(_T("stationthrob.wav"))));
		//m_dsbuffer = t3d::DSBufferPtr(my::createDSoundBufferForWholeWav(m_dsound.get(), tmpWav.get()));
		//my::copyWholeWavBufferToDSoundBuffer(m_dsbuffer.get(), tmpWav.get());
		//m_dsbuffer->play();

		// ======================================== TODO: END   ========================================

		m_pwnd->setMessageListener(this);

		return true;
	}

	/** 实现 my::Game::onShutdown 接口
	在这里销毁自己创建的东西，由于基层框架全部使用 smart_ptr，所以框架不需要 shutdown
	但框架还是会在退出应用程序时，调用这个接口，用于自定义的销毁
	*/
	virtual void onShutdown(void)
	{
	}

	/** 实现 my::Game::onFrame 接口
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

		// 从用户输入来更新欧拉相机的坐标和方位
		m_eularCam->update(m_keyboard.get(), m_mouse.get(), elapsedTime);

		// 这里创建一个比窗口小的 clipper 区域，仅用于测试 3d 渲染得 clipper bug
		// 由于软件渲染器，其 clipper 是通过算法实现的，所以若算法不强健，回到之绘图时越过 clipper 区域
		// 甚至越过窗口区域，所以将绘图区域缩小一部分可以稍微避免，因越界导致系统崩溃的现象
		RECT clipper = {m_rback.left + 10, m_rback.top + 10, m_rback.right - 10, m_rback.bottom - 10};

		m_rc->setClipperRect(clipper);

		// 清理 back surface
		fillBackSurface(m_rc->getClipperRect());

		// 清理 zbuffer
		clearZBuffer(m_rc->getClipperRect());

		// 锁住 back surface，由于 back surface 是内存 memory，所以这里即使不锁也不要紧
		DDSURFACEDESC2 ddsc = m_sback->lock();

		// 设置渲染上下文的 surface、clipper、zbuffer
		m_rc->setSurfaceBuffer(ddsc.lpSurface, ddsc.lPitch, ddsc.dwWidth, ddsc.dwHeight);
		m_rc->setClipperRect(clipper);
		m_rc->setZBufferBuffer(m_zbuff.get(), m_zbuffPitch, 0, 0);

		// 设置渲染上下文的 camera
		//m_rc->setCameraPosition(m_eularCam->getPosition());
		m_rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEular(m_eularCam->getPosition(), m_eularCam->getRotation()));
		m_rc->setViewport(clipper);
		m_rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), clipper.right - clipper.left, clipper.bottom - clipper.top));
		m_rc->setCameraNearZ(1);
		m_rc->setCameraFarZ(10000);

		// 渲染网格
		m_grid->drawZBufferRW(m_rc.get());

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

		// 自定义渲染
		const t3d::BoneNodeList & boneNodeList =
			m_jackSkeleton->gotoAnimation(m_jackSkeleton->getCurrentAnimationName(), m_jackSkeleton->getCurrentAnimationTime() + elapsedTime);

		t3d::STreeNode::IndexList::const_iterator root_iter = m_jackSkeleton->getRootIndexListBegin();
		for(; root_iter != m_jackSkeleton->getRootIndexListEnd(); root_iter++)
		{
			// 和 banding position 叠加
			t3d::incrementBoneNodeList(
				m_jackBoneNodeList,
				m_jackSkeleton->getOrigBoneNodeList(),
				boneNodeList,
				*root_iter);

			// 获取当前动作的 transform matrix
			t3d::updateBoneTransformListFromBoneNodeList(
				m_jackBoneTransformList,
				m_jackBoneNodeList,
				*root_iter,
				my::Mat4<real>::IDENTITY,
				my::Mat4<real>::IDENTITY);
		}

		// 获取最终 transform matrix
		t3d::combineVertexNormalBoneTransformList(
			m_jackBoneTransformList,
			m_jackSkeleton->getOrigBoneInverseTransformList(),
			m_jackBoneTransformList);

		t3d::bindVertexListNormalListFromBoneTransformList(
			m_jackModel->getVertexList(),
			m_jackModel->getNormalList(),
			m_jackModel->getOriginalVertexList(),
			m_jackModel->getOriginalNormalList(),
			m_jackModel->getBoneAssignmentList(),
			m_jackBoneTransformList);

		m_rc->setTextureBuffer(m_jackTexture->getBits(), m_jackTexture->getPitch(), m_jackTexture->getWidth(), m_jackTexture->getHeight());
		m_jackModel->drawGouraudTextureZBufferRW(m_rc.get());

		// ======================================== TODO: END   ========================================

		// 解锁 back surface
		m_sback->unlock();

		// 输出常用信息，如帧速率、相机方位等
		std::basic_string<charT> strTmp;
		HDC hdc = m_sback->getDC();

		strTmp = str_printf(_T("fps: %.1f"), 1 / elapsedTime);
		::TextOut(hdc, 10, 10, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("fps: %.1f"), m_fpsMgr->getFPS());
		::TextOut(hdc, 10, 30, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("cam.pos: %f, %f, %f"),
			m_eularCam->getPosition().x, m_eularCam->getPosition().y, m_eularCam->getPosition().z);
		::TextOut(hdc, 10, 50, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("cam.rot: %f, %f, %f"),
			RAD_TO_DEG(m_eularCam->getRotation().x), RAD_TO_DEG(m_eularCam->getRotation().y), RAD_TO_DEG(m_eularCam->getRotation().z));
		::TextOut(hdc, 10, 70, strTmp.c_str(), (int)strTmp.length());

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

	BOOL notifyMessage(LRESULT & lResult, my::Window * win, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch(message)
		{
		case WM_KEYDOWN:
			switch(wparam)
			{
			case VK_F1:
				prepareConfig(my::GameBase::CONFIG_DESC(640, 480, SM_WINDOWED));
				break;

			case VK_F2:
				prepareConfig(my::GameBase::CONFIG_DESC(800, 600, SM_WINDOWED));
				break;

			case VK_F3:
				prepareConfig(my::GameBase::CONFIG_DESC(1024, 768, SM_WINDOWED));
				break;

			case VK_F4:
				prepareConfig(my::GameBase::CONFIG_DESC(1280, 1024, SM_WINDOWED));
				break;
			}
			lResult = 0;
			return TRUE;
		}

		return FALSE;
	}
};

int APIENTRY WinMain(
	HINSTANCE	/*hInstance*/,
	HINSTANCE	/*hPrevInstance*/,
	LPSTR		/*lpCmdLine*/,
	int			/*nCmdShow*/)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF & _CRTDBG_ALLOC_MEM_DF);

	try
	{
		// 建立一个应用程序，以 800 x 600 窗口模式运行
		MyGame game;
		return game.run(my::Game::CONFIG_DESC(800, 600, my::Game::SM_WINDOWED));
		//return game.run(my::Game::CONFIG_DESC(1680, 1050, my::Game::SM_FULLSCREEN32));
	}
	catch(t3d::Exception & e)
	{
		::MessageBox(NULL, e.getFullDesc().c_str(), _T("Exception"), MB_OK);
	}

	return -1;
}
