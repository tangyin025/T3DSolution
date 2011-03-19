/** FILE: main.cpp
	定义了一个基于 my::Game 类的复杂框架的应用
*/

#include <myGame.h>				// 应用程序封装
#include <myUtility.h>			// 快速模型绘制
#include <libc.h>				// 扩展 string 函数
#include "resource.h"			// resource

using t3d::real;

using t3d::charT;

// ----------------------------------------------------------------------------------------------------
// MyConfig
// ----------------------------------------------------------------------------------------------------

// 这个类主要用来保存配置信息，参见 MyDialog
// 继承自 my::Config 类，已经封装了从配置文件读取选项的基本功能
class MyConfig
	: public my::Config
{
public:
	real m_aspectRatio; // 为这个类增加一个成员用来支持“纵横比”

public:
	MyConfig(
		int width = 800,
		int height = 600,
		my::Game::SCREEN_MODE smode = my::Game::SCREEN_MODE_WINDOWED,
		real aspectRatio = (real)4 / 3)
		: m_aspectRatio(aspectRatio)
	{
		addInt(_T("width"), width);
		addInt(_T("height"), height);
		addInt(_T("screenmode"), smode);
	}
};

// ----------------------------------------------------------------------------------------------------
// MyDialog
// ----------------------------------------------------------------------------------------------------

// 这里定义一个对话框，主要是为了，让用户来决定如何初始化应用程序，如分辨率，纵横比，是否全屏等
class MyDialog
	: public CDialogImpl<MyDialog, CWindow>
{
public:
	enum { IDD = IDD_DIALOG1 };

public:
	MyConfig m_cfg; // 这个变量用来保存用户自定义配置

public:
	MyDialog(const MyConfig & cfg)
		: m_cfg(cfg)
	{
	}

	// Dialog 消息事件处理
	BEGIN_MSG_MAP(MyDialog)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDC_COMBO1, CBN_SELCHANGE, OnCombo1SelChange)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// 设置窗口标题
		SetWindowText(_T("User Configuration"));

		// 插入各个分辨率
		VERIFY(CB_ERR != GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("320x240")));
		VERIFY(CB_ERR != GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("640x480")));
		VERIFY(CB_ERR != GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("800x600")));
		VERIFY(CB_ERR != GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1024x768")));
		VERIFY(CB_ERR != GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1280x800")));
		VERIFY(CB_ERR != GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1280x1024")));
		VERIFY(CB_ERR != GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1366x768")));
		VERIFY(CB_ERR != GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1680x1050")));

		// 设置默认分辨率为 800x600，并更新编辑框
		VERIFY(CB_ERR != GetDlgItem(IDC_COMBO1).SendMessage(CB_SELECTSTRING, (WPARAM)-1, (LPARAM)_T("800x600")));
		SendMessage(WM_COMMAND, MAKEWPARAM(IDC_COMBO1, CBN_SELCHANGE), (LPARAM)GetDlgItem(IDC_COMBO1).m_hWnd);

		// 设置默认为窗口模式
		switch(m_cfg.getInt(_T("screenmode")))
		{
		case my::Game::SCREEN_MODE_FULLSCREEN16:
			VERIFY(CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO2));
			break;
		case my::Game::SCREEN_MODE_FULLSCREEN32:
			VERIFY(CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO3));
			break;
		default:
			VERIFY(CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1));
			break;
		}

		// 对其窗口
		CenterWindow();
		return TRUE;
	}

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		EndDialog(IDCANCEL);
		return 0;
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// 保存分辨率选项
		m_cfg.setInt(_T("width"), GetDlgItemInt(IDC_EDIT1, NULL, FALSE));
		m_cfg.setInt(_T("height"), GetDlgItemInt(IDC_EDIT2, NULL, FALSE));

		// 保存屏幕模式选项
		if(IsDlgButtonChecked(IDC_RADIO1))
		{
			m_cfg.setInt(_T("screenmode"), my::Game::SCREEN_MODE_WINDOWED);
		}
		else if(IsDlgButtonChecked(IDC_RADIO2))
		{
			m_cfg.setInt(_T("screenmode"), my::Game::SCREEN_MODE_FULLSCREEN16);
		}
		else
		{
			_ASSERT(IsDlgButtonChecked(IDC_RADIO3));
			m_cfg.setInt(_T("screenmode"), my::Game::SCREEN_MODE_FULLSCREEN32);
		}

		// 保存纵横比
		if(IsDlgButtonChecked(IDC_RADIO4))
		{
			m_cfg.m_aspectRatio = (real)m_cfg.getInt(_T("width")) / m_cfg.getInt(_T("height"));
		}
		else if(IsDlgButtonChecked(IDC_RADIO5))
		{
			m_cfg.m_aspectRatio = (real)4 / 3;
		}
		else
		{
			_ASSERT(IsDlgButtonChecked(IDC_RADIO6));
			m_cfg.m_aspectRatio = (real)16 / 9;
		}
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCombo1SelChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// 获取用户在下拉列表中选择的分辨率
		CWindow combo1 = GetDlgItem(IDC_COMBO1);
		int nIndex = combo1.SendMessage(CB_GETCURSEL, 0, 0);
		_ASSERT(CB_ERR != nIndex);
		std::basic_string<charT> strTmp;
		strTmp.resize(combo1.SendMessage(CB_GETLBTEXTLEN, nIndex, 0));
		VERIFY(CB_ERR != combo1.SendMessage(CB_GETLBTEXT, nIndex, (LPARAM)&strTmp[0]));
		int nWidth, nHeight;
		VERIFY(2 == _stscanf_s(strTmp.c_str(), _T("%dx%d"), &nWidth, &nHeight));

		// 将分辨率更新到编辑框中
		VERIFY(SetDlgItemInt(IDC_EDIT1, nWidth, FALSE));
		VERIFY(SetDlgItemInt(IDC_EDIT2, nHeight, FALSE));

		// 同时跟新纵横比
		real aspectRatio = (real)nWidth / nHeight;
		if((real)4 / 3 == aspectRatio)
		{
			VERIFY(CheckRadioButton(IDC_RADIO4, IDC_RADIO6, IDC_RADIO5));
		}
		else if((real)16 / 9 == aspectRatio)
		{
			VERIFY(CheckRadioButton(IDC_RADIO4, IDC_RADIO6, IDC_RADIO6));
		}
		else
		{
			VERIFY(CheckRadioButton(IDC_RADIO4, IDC_RADIO6, IDC_RADIO4));
		}
		return 0;
	}
};

// ----------------------------------------------------------------------------------------------------
// MyGameBase
// ----------------------------------------------------------------------------------------------------

// 这个类主定义了一个 3d 应用程序的基本框架，实现了一些常用操作，如显示帧速率，定义相机，绘制网格等
// 继承者应当另开一个类继承，将一些实现细节和常规操作分开
class MyGameBase
	: public my::ErrorListener	// 实现接受错误信息的接口，这些错误信息通常来自于 my 的封装，这样就可以使用 REPORT_ERROR 宏对这个接口报错
	, public my::Game			// 用以实现基于帧循环的基本应用程序框架，并已经实现了常见的 primary、back surface 结构
{
protected:
	// 一个类似控制台的模拟器，可以在 surface 上输出控制台信息
	my::ConsoleSimulatorPtr m_consoleSim;

	// 基于采样的帧速率计算工具
	my::FPSManagerPtr m_fpsMgr;

	// 基于主频的帧速率计算工具，主要提供物理引擎支持
	my::TimerPtr m_timer;

	// 欧拉相机，默认可以使用欧拉相机在场景中自由观察
	my::EulerCameraPtr m_eulerCam;

	// 绘制网格的工具
	my::GridPtr m_grid;

	// 为什么要使用 ptr，而不直接在构造函数中初始化？
	// 应为某些对象在建立时，会用有先决条件，而 my::Game 在构造函数时，还没有初始化一些对象，如 SingleTon 对象
	// 只有在框架调用 my::Game::onInit(...) 时，这些前提条件才成熟，所以通常是先使用 ptr，然后再在 onInit(...) 里边再构造

public:
	// 实现 my::ErrorListener 的 onReport 接口，
	// 用以接收来自框架的错误 message，并将其打印到模拟控制台
	void onReport(const std::basic_string<charT> & info)
	{
		m_consoleSim->report(info);
	}

	// 实现 my::Game 的 onInit 结构
	// 通常在应用程序初始化时，框架会掉用这个接口，所以应当在这里实现自定义的初始化操作
	bool onInit(const my::Config & cfg)
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

		// 构造欧拉相机
		m_eulerCam = my::EulerCameraPtr(new my::EulerCamera());
		m_eulerCam->setDefaultPosition(my::Vec4<real>(-50, 50, -50));
		m_eulerCam->setDefaultRotation(my::Vec4<real>(DEG_TO_RAD(45), DEG_TO_RAD(45), DEG_TO_RAD(0)));
		m_eulerCam->reset();

		// 根据 aspect ratio 重新计算 clipper rect
		const MyConfig * pcfg = static_cast<const MyConfig *>(&cfg);
		LONG lWidth, lHeight;
		CRect clipper;
		if(pcfg->m_aspectRatio < (real)cfg.getInt(_T("width")) / (real)cfg.getInt(_T("height")))
		{
			lHeight = cfg.getInt(_T("height"));
			lWidth = (LONG)(lHeight * pcfg->m_aspectRatio + .5f);
			clipper.left = (cfg.getInt(_T("width")) - lWidth) / 2;
			clipper.top = 0;
			clipper.right = clipper.left + lWidth;
			clipper.bottom = clipper.top + lHeight;
		}
		else
		{
			lWidth = cfg.getInt(_T("width"));
			lHeight = (LONG)(lWidth / pcfg->m_aspectRatio + .5f);
			clipper.left = 0;
			clipper.top = (cfg.getInt(_T("height")) - lHeight) / 2;
			clipper.right = clipper.left + lWidth;
			clipper.bottom = clipper.top + lHeight;
		}

		// 设置渲染上下文的 clipper rect
		_ASSERT(clipper.left	>= m_backSurfaceRect.left);
		_ASSERT(clipper.top		>= m_backSurfaceRect.top);
		_ASSERT(clipper.right	<= m_backSurfaceRect.right);
		_ASSERT(clipper.bottom	<= m_backSurfaceRect.bottom);
		m_rc->setClipperRect(clipper);

		//// 如果需要读取资源，还要添加媒体搜索路径，建立快捷方式时要注意当前路径的位置
		//my::ResourceMgr::getSingleton().addDir(_T("."));
		//my::ResourceMgr::getSingleton().addDir(_T("../../common/medias/demo1_2"));

		// 初始化网格
		m_grid = my::GridPtr(new my::Grid());
		return true;
	}

	// 实现 my::Game 的 onShutdown 结构
	// 框架会在退出应用程序时，调用这个接口，用于自定义的销毁，但是由于基层框架全部使用 smart_ptr，所以不再需要释放资源
	void onShutdown(void)
	{
	}

	// 实现 my::Game 的 onFrame 结构
	// 框架会在主线程没有消息处理的时候调用这个接口，应当在这里进行帧操作，如渲染，step 物理引擎等
	bool onFrame(void)
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
		//CRect clipper(m_backSurfaceRect);
		//clipper.DeflateRect(10, 10);
		//m_rc->setClipperRect(clipper);

		// 设置渲染上下文的 camera
		m_rc->setViewport(m_rc->getClipperRect());
		m_rc->setCameraProjection(
			t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), m_rc->getClipperRect().Width(), m_rc->getClipperRect().Height()));
		m_rc->setCameraNearZ(1);
		m_rc->setCameraFarZ(10000);

		// 开始渲染
		doRender(elapsedTime);

		// 获取后缓存的 dc，用以使用 gui 来输出信息
		HDC hdc = m_backSurface->getDC();

		// 输出帧速率
		int textx = m_rc->getClipperRect().left + 10;
		int texty = m_rc->getClipperRect().top + 10;
		std::basic_string<charT> strTmp = str_printf(_T("fps: %.1f"), m_fpsMgr->getFPS());
		::TextOut(hdc, textx, texty, strTmp.c_str(), (int)strTmp.length());
		strTmp = str_printf(_T("fps: %.1f"), 1 / elapsedTime);
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		// 输出相机位置信息，my::CameraContext::getCameraPosition 已经优化过了，所以可以直接调用
		strTmp = str_printf(_T("cam.pos: %f, %f, %f"),
			m_rc->getCameraPosition().x,
			m_rc->getCameraPosition().y,
			m_rc->getCameraPosition().z);
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		// 输出相机旋转信息
		strTmp = str_printf(_T("cam.rot: %f, %f, %f"),
			RAD_TO_DEG(m_eulerCam->getRotation().x),
			RAD_TO_DEG(m_eulerCam->getRotation().y),
			RAD_TO_DEG(m_eulerCam->getRotation().z));
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		// 释放为输出字符串而分配的 dc
		m_backSurface->releaseDC(hdc);

		// 绘制控制台模拟器
		m_consoleSim->draw(m_backSurface.get(), 10, texty += 20);
		return true;
	}

	// MyGameBase 自己的接口，
	// 会在 onFrame 中被调用，主要是用来清理背景，更新相机，绘制场景等常用 render 操作，继承者应该另外实现自己的目的
	virtual void doRender(real elapsedTime)
	{
		// 清理 back surface
		m_rc->fillSurface(m_rc->getClipperRect(), my::Color(0.8f, 0.8f, 0.8f));

		// 清理 zbuffer
		m_rc->fillZbuffer(m_rc->getClipperRect(), 0);

		//// 清理 stencil buffer，这个操作其实是为了绘制阴影而准备的，如果不用可以省略掉
		//m_rc->fillStencilBuffer(m_rc->getClipperRect(), 0);

		// 从用户输入来更新欧拉相机的坐标和方位
		m_eulerCam->update(m_keyboard.get(), m_mouse.get(), elapsedTime);
		m_rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEuler(m_eulerCam->getPosition(), m_eulerCam->getRotation()));

		// 渲染网格
		m_grid->drawZBufferRW(m_rc.get());
	}
};

// ----------------------------------------------------------------------------------------------------
// MyGame
// ----------------------------------------------------------------------------------------------------

class MyGame
	: public MyGameBase
	, public my::DrawnHelper	// 绘图辅助类，可以使用简单的代码绘制一些基本形状
{
public:
	bool onInit(const my::Config & cfg)
	{
		// 先初始化父类框架
		if(!MyGameBase::onInit(cfg))
		{
			return false;
		}

		return true;
	}

	void doRender(real elapsedTime)
	{
		// 清理 back surface
		m_rc->fillSurface(m_rc->getClipperRect(), my::Color(0.8f, 0.8f, 0.8f));

		// 清理 zbuffer
		m_rc->fillZbuffer(m_rc->getClipperRect(), 0);

		// 从用户输入来更新欧拉相机的坐标和方位
		m_eulerCam->update(m_keyboard.get(), m_mouse.get(), elapsedTime);
		m_rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEuler(m_eulerCam->getPosition(), m_eulerCam->getRotation()));

		// 渲染网格
		m_grid->drawZBufferRW(m_rc.get());
	}
};

// ----------------------------------------------------------------------------------------------------
// _tWinMain
// ----------------------------------------------------------------------------------------------------

int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	// 运行时内存泄漏检查
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));

	// 在这个地方读取用户自定义分辨率，屏幕设置等，详情参考 my::Game::SCREEN_MODE
	MyDialog dlg(MyConfig(800));
	return IDOK != dlg.DoModal() ? 0 : MyGame().run(dlg.m_cfg);
}
