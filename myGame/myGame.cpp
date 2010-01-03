
#include "stdafx.h"
#include "myGame.h"
#include <cmath>
#include <iostream>
//#include <boost/program_options.hpp>

namespace my
{
	ErrorListener::~ErrorListener(void)
	{
	}

	ErrorReporter * ErrorReporter::s_ptr = NULL;

	ErrorReporter::ErrorReporter(void)
	{
		assert(NULL == s_ptr);
		s_ptr = this;
	}

	ErrorReporter::~ErrorReporter(void)
	{
		assert(this == s_ptr);
		s_ptr = NULL;
	}

	void ErrorReporter::addErrorListener(ErrorListener * listener)
	{
		assert(NULL != listener);

		m_listenerList.push_back(listener);
	}

	void ErrorReporter::report(const std::basic_string<charT> & info)
	{
		ErrorListenerPList::iterator l_iter = m_listenerList.begin();
		for(; l_iter != m_listenerList.end(); l_iter++)
		{
			assert(NULL != *l_iter);

			(*l_iter)->onReport(info);
		}
	}

	ColorConversion * ColorConversion::s_ptr = NULL;

	ColorConversion::ColorConversion(void)
	{
		assert(NULL == s_ptr);
		s_ptr = this;
	}

	ColorConversion::~ColorConversion(void)
	{
		assert(NULL != s_ptr);
		s_ptr = NULL;
	}

	uint32 ColorConversion16::convertColor(const my::Color & color)
	{
		assert(0 <= color.x && color.x <= 1);
		assert(0 <= color.y && color.y <= 1);
		assert(0 <= color.z && color.z <= 1);

		return _RGB16BIT(
			t3d::real_to_int(color.x * 255),
			t3d::real_to_int(color.y * 255),
			t3d::real_to_int(color.z * 255));
	}

	uint32 ColorConversion16::convertColor(const t3d::Vec4<int> & color)
	{
		assert(0 <= color.x && color.x <= 255);
		assert(0 <= color.y && color.y <= 255);
		assert(0 <= color.z && color.z <= 255);

		return _RGB16BIT(
			color.x, color.y, color.z);
	}

	my::ImagePtr ColorConversion16::convertImage(const my::Image * image)
	{
		return image->convertTo16Bits565();
	}

	uint32 ColorConversion32::convertColor(const my::Color & color)
	{
		assert(0 <= color.x && color.x <= 1);
		assert(0 <= color.y && color.y <= 1);
		assert(0 <= color.z && color.z <= 1);

		return _RGB32BIT(
			t3d::real_to_int(color.x * 255),
			t3d::real_to_int(color.y * 255),
			t3d::real_to_int(color.z * 255));
	}

	uint32 ColorConversion32::convertColor(const t3d::Vec4<int> & color)
	{
		assert(0 <= color.x && color.x <= 255);
		assert(0 <= color.y && color.y <= 255);
		assert(0 <= color.z && color.z <= 255);

		return _RGB32BIT(
			color.x, color.y, color.z);
	}

	my::ImagePtr ColorConversion32::convertImage(const my::Image * image)
	{
		return image->convertTo32Bits();
	}

	GameBase::CONFIG_DESC::CONFIG_DESC(DWORD _width /*= 800*/, DWORD _height /*= 600*/, int _smode /*= SM_WINDOWED*/)
		: width(_width), height(_height), smode(_smode)
	{
	}

	GameBase::GameBase(HINSTANCE hinst)
		: Application(hinst)
		, m_pwnd(NULL)
	{
	}

	GameBase::~GameBase(void)
	{
	}

	void GameBase::prepare(const CONFIG_DESC & cfg)
	{
		// create error reporter
		m_errorRpt = ErrorReporterPtr(new ErrorReporter());

		// create resource manager
		m_resourceMgr = ResourceMgrPtr(new ResourceMgr());

		// create main window
		m_pwnd = createWindow(_T("T3DLIB_WINDOW"), getModuleFileName());

		// create ddraw object
		m_ddraw = t3d::DDrawPtr(new t3d::DDraw());

		m_ddraw->setCooperativeLevel(m_pwnd->getHandle(), t3d::DDraw::CL_NORMAL);

		// update video config
		prepareConfig(cfg);
	}

	void GameBase::prepareConfig(const CONFIG_DESC & cfg)
	{
		assert(m_ddraw != NULL);

		assert(NULL != m_pwnd);

		// NOTE: destory previous primary surface before re-create it
		m_sprim = t3d::DDSurfacePtr();

		CRect clientRect(0, 0, cfg.width, cfg.height);

		// set ddraw and main window with config
		switch(cfg.smode)
		{
		case my::GameBase::SM_WINDOWED:
			m_ddraw->setCooperativeLevel(m_pwnd->getHandle(), t3d::DDraw::CL_NORMAL);
			//m_ddraw->RestoreDisplayMode();
			m_pwnd->setWindowStyle(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
			m_pwnd->adjustClientRect(clientRect);
			m_pwnd->centerWindow();
			break;

		case my::GameBase::SM_FULLSCREEN16:
			m_ddraw->setCooperativeLevel(m_pwnd->getHandle(), t3d::DDraw::CL_EXCLUSIVE);
			m_ddraw->setDisplayMode(cfg.width, cfg.height, 16);
			m_pwnd->setWindowStyle(WS_POPUP | WS_VISIBLE);
			m_pwnd->adjustClientRect(clientRect);
			break;

		case my::GameBase::SM_FULLSCREEN32:
			m_ddraw->setCooperativeLevel(m_pwnd->getHandle(), t3d::DDraw::CL_EXCLUSIVE);
			m_ddraw->setDisplayMode(cfg.width, cfg.height, 32);
			m_pwnd->setWindowStyle(WS_POPUP | WS_VISIBLE);
			m_pwnd->adjustClientRect(clientRect);
			break;

		default:
			T3D_CUSEXCEPT(_T("unsupported screen mode"));
		}

		// create primary surface with main window clipper
		m_sprim = m_ddraw->createWindowSurface();

		m_sprim->setClipper(m_ddraw->createWindowClipper(m_pwnd->getHandle()).get());

		// create back surface with custom rect clipper
		m_sback = m_ddraw->createMemorySurface(cfg.width, cfg.height);

		m_sback->setClipper(m_ddraw->createMemoryClipper(&clientRect, 1).get());

		// save the back surface rect clipper for blt
		m_rback = clientRect;

		// create render context
		switch(m_sprim->getPixelFormat().dwRGBBitCount)
		{
		case 16:
			m_rc = RenderContextPtr(new t3d::RenderContext16());
			if(m_cc == NULL)
				m_cc = ColorConversionPtr(new ColorConversion16());
			break;

		case 32:
			m_rc = RenderContextPtr(new t3d::RenderContext32());
			if(m_cc == NULL)
				m_cc = ColorConversionPtr(new ColorConversion32());
			break;

		default:
			T3D_CUSEXCEPT(_T("unsupported pixel format"));
		}

		// create zbuffer
		m_zbuff = ZBufferPtr(new fixp28[cfg.width * cfg.height]);

		m_zbuffPitch = cfg.width * sizeof(fixp28);

		// save back surface & zbuffer to render context
		DDSURFACEDESC2 ddsc = m_sback->lock();

		m_rc->setSurfaceBuffer(ddsc.lpSurface, ddsc.lPitch, ddsc.dwWidth, ddsc.dwHeight);

		m_sback->unlock();

		m_rc->setZBufferBuffer(m_zbuff.get(), m_zbuffPitch, 0, 0);

		// set back surface rect to render context clipper
		m_rc->setClipperRect(m_rback);

		// show main window
		m_pwnd->showWindow();
	}

	void GameBase::bltBackSurfaceToPrimary(void)
	{
		// commit back surface to primary surface within corrected rectangle
		m_rprim = m_pwnd->getClientRect();

		/*
		 * NOTE: for some reason, if the window size is greater than the desktop size, will lead these assert abort
		 */
		assert((m_rprim.right - m_rprim.left) == m_rback.right && m_rback.left == 0);

		assert((m_rprim.bottom - m_rprim.top) == m_rback.bottom && m_rback.top == 0);

		//m_sprim->blt(&m_rprim, m_sback.get(), &m_rback);
		HDC hdcSrc = m_sback->getDC();
		HDC hdc = m_pwnd->getDC();
		::BitBlt(hdc, 0, 0, m_rback.Width(), m_rback.Height(), hdcSrc, 0, 0, SRCCOPY);
		m_pwnd->releaseDC(hdc);
		m_sback->releaseDC(hdcSrc);
	}

	void GameBase::fillBackSurface(const CRect & rect, const t3d::Vec4<int> & color /*= my::Vec4<int>(197, 197, 197)*/)
	{
		// clear back surface use render context's clipper
		m_sback->fill(const_cast<CRect *>(&rect), m_cc->convertColor(color));
	}

	static void _clearZBuffer(void * pbuffer, DWORD pitch, const CRect & rect, fixp28 value /*= 0*/)
	{
		// clear zbuffer with specified value
		for(LONG y = rect.top; y < rect.bottom; y++)
		{
			memset(&t3d::SurfaceRef<fixp28>(static_cast<fixp28*>(pbuffer), pitch)[y][rect.left], value, rect.Width() * sizeof(fixp28));
		}
	}

	void GameBase::clearZBuffer(const CRect & rect, t3d::fixp28 value /*= 0*/)
	{
		// clear zbuffer use render context's clipper
		_clearZBuffer(m_zbuff.get(), m_zbuffPitch, rect, value);
	}

	Game::Game(HINSTANCE hinst /*= NULL*/)
		: GameBase(hinst)
	{
	}

	Game::~Game(void)
	{
	}

	//int Game::run(LPTSTR lpCmdLine)
	//{
	//	// build program option descriptions
	//	int i_opt;
	//	boost::program_options::options_description desc("my game options");
	//	desc.add_options()
	//		("width,W", boost::program_options::value<int>(&i_opt)->default_value(640), "specify resolution width")
	//		("height,H", boost::program_options::value<int>(&i_opt)->default_value(480), "specify resolution height")
	//		("fullscreen-mode,F", boost::program_options::value<int>(&i_opt)->default_value(0), "specify color deepth for fullscreen mode")
	//		;

	//	// store comman line argument to variables map
	//	boost::program_options::variables_map vmap;
	//	std::vector<std::basic_string<charT> > args = boost::program_options::split_winmain(lpCmdLine);
	//	boost::program_options::store(
	//		boost::program_options::basic_command_line_parser<charT>(args).options(desc).run(), vmap);
	//	boost::program_options::notify(vmap);

	//	return run(CONFIG_DESC(vmap["width"].as<int>(), vmap["height"].as<int>(), vmap["fullscreen-mode"].as<int>()));
	//}

	int Game::run(const CONFIG_DESC & cfg)
	{
		int res = -1;

		// prepare game base
		prepare(cfg);

		// create dinput and keyboard & mouse
		m_dinput = t3d::DInputPtr(new t3d::DInput(getHandle()));

		m_keyboard = m_dinput->createSysKeyboard();
		m_keyboard->setCooperativeLevel(m_pwnd->getHandle(), t3d::DIDevice::CL_NORMAL);
		m_keyboard->acquire();

		m_mouse = m_dinput->createSysMouse();
		m_mouse->setCooperativeLevel(m_pwnd->getHandle(), t3d::DIDevice::CL_NORMAL);
		m_mouse->acquire();

		m_dsound = t3d::DSoundPtr(new t3d::DSound());
		m_dsound->setCooperativeLevel(m_pwnd->getHandle(), t3d::DSound::CL_PRIORITY);

		// register this to idle listener
		setIdleListener(this);

		//// register current directory input source dir
		//m_resourceMgr->registerDir(_T("."));

		// do initialize
		if(onInit())
		{
			// run main application
			res = Application::run();
		}

		// do shutdown
		onShutdown();

		return res;
	}

	BOOL Game::nodifyIdle(void)
	{
		// update keyboard
		m_keyboard->update();

		// update mouse
		m_mouse->update();

		// do client's frame, if failed destroy main window
		if(!onFrame())
		{
			// destroy window
			m_pwnd->destroyWindow();

			m_pwnd = NULL;

			return TRUE;
		}

		// swap the backup and primary surface
		bltBackSurfaceToPrimary();

		return TRUE;
	}
}
