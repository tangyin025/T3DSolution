
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
		_ASSERT(NULL == s_ptr);
		s_ptr = this;
	}

	ErrorReporter::~ErrorReporter(void)
	{
		_ASSERT(this == s_ptr);
		s_ptr = NULL;
	}

	void ErrorReporter::addErrorListener(ErrorListener * listener)
	{
		_ASSERT(NULL != listener);

		m_listenerList.push_back(listener);
	}

	void ErrorReporter::report(const std::basic_string<charT> & info)
	{
		ErrorListenerPList::iterator l_iter = m_listenerList.begin();
		for(; l_iter != m_listenerList.end(); l_iter++)
		{
			_ASSERT(NULL != *l_iter);

			(*l_iter)->onReport(info);
		}
	}

	ColorConversion * ColorConversion::s_ptr = NULL;

	ColorConversion::ColorConversion(void)
	{
		_ASSERT(NULL == s_ptr);
		s_ptr = this;
	}

	ColorConversion::~ColorConversion(void)
	{
		_ASSERT(NULL != s_ptr);
		s_ptr = NULL;
	}

	uint32 ColorConversion16::convertColor(const my::Color & color)
	{
		_ASSERT(0 <= color.x && color.x <= 1);
		_ASSERT(0 <= color.y && color.y <= 1);
		_ASSERT(0 <= color.z && color.z <= 1);

		return _RGB16BIT(
			t3d::real_to_int(color.x * 255),
			t3d::real_to_int(color.y * 255),
			t3d::real_to_int(color.z * 255));
	}

	uint32 ColorConversion16::convertColor(const t3d::Vec4<int> & color)
	{
		_ASSERT(0 <= color.x && color.x <= 255);
		_ASSERT(0 <= color.y && color.y <= 255);
		_ASSERT(0 <= color.z && color.z <= 255);

		return _RGB16BIT(
			color.x, color.y, color.z);
	}

	my::ImagePtr ColorConversion16::convertImage(const my::Image * image)
	{
		return image->convertTo16Bits565();
	}

	uint32 ColorConversion32::convertColor(const my::Color & color)
	{
		_ASSERT(0 <= color.x && color.x <= 1);
		_ASSERT(0 <= color.y && color.y <= 1);
		_ASSERT(0 <= color.z && color.z <= 1);

		return _RGB32BIT(
			t3d::real_to_int(color.x * 255),
			t3d::real_to_int(color.y * 255),
			t3d::real_to_int(color.z * 255));
	}

	uint32 ColorConversion32::convertColor(const t3d::Vec4<int> & color)
	{
		_ASSERT(0 <= color.x && color.x <= 255);
		_ASSERT(0 <= color.y && color.y <= 255);
		_ASSERT(0 <= color.z && color.z <= 255);

		return _RGB32BIT(
			color.x, color.y, color.z);
	}

	my::ImagePtr ColorConversion32::convertImage(const my::Image * image)
	{
		return image->convertTo32Bits();
	}

	Game::CONFIG_DESC::CONFIG_DESC(DWORD _width, DWORD _height, int _smode)
		: width(_width), height(_height), smode(_smode)
	{
	}

	Game::Game(void)
		: m_pwnd(NULL)
	{
	}

	Game::~Game(void)
	{
	}

	void Game::prepare(const CONFIG_DESC & cfg)
	{
		// create error reporter
		m_errorRpt = ErrorReporterPtr(new ErrorReporter());

		// create resource manager
		m_resourceMgr = ResourceMgrPtr(new ResourceMgr());

		// create main window
		m_pwnd = createWindow(getModuleFileName());

		// create ddraw object
		m_ddraw = t3d::DDrawPtr(new t3d::DDraw());

		m_ddraw->setCooperativeLevel(m_pwnd->getHandle(), t3d::DDraw::CL_NORMAL);

		// update video config
		prepareConfig(cfg);
	}

	void Game::prepareConfig(const CONFIG_DESC & cfg)
	{
		_ASSERT(m_ddraw != NULL);

		_ASSERT(NULL != m_pwnd);

		//// NOTE: destory previous primary surface before re-create it
		//m_sprim = t3d::DDSurfacePtr();

		CRect clientRect(0, 0, cfg.width, cfg.height);

		// set ddraw and main window with config
		switch(cfg.smode)
		{
		case my::Game::SM_WINDOWED:
			m_ddraw->setCooperativeLevel(m_pwnd->getHandle(), t3d::DDraw::CL_NORMAL);
			//m_ddraw->RestoreDisplayMode();
			m_pwnd->setWindowStyle(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
			m_pwnd->adjustClientRect(clientRect);
			m_pwnd->centerWindow();
			break;

		case my::Game::SM_FULLSCREEN16:
			m_ddraw->setCooperativeLevel(m_pwnd->getHandle(), t3d::DDraw::CL_EXCLUSIVE);
			m_ddraw->setDisplayMode(cfg.width, cfg.height, 16);
			m_pwnd->setWindowStyle(WS_POPUP | WS_VISIBLE);
			m_pwnd->adjustClientRect(clientRect);
			break;

		case my::Game::SM_FULLSCREEN32:
			m_ddraw->setCooperativeLevel(m_pwnd->getHandle(), t3d::DDraw::CL_EXCLUSIVE);
			m_ddraw->setDisplayMode(cfg.width, cfg.height, 32);
			m_pwnd->setWindowStyle(WS_POPUP | WS_VISIBLE);
			m_pwnd->adjustClientRect(clientRect);
			break;

		default:
			T3D_CUSEXCEPT(_T("unsupported screen mode"));
		}

		//// create primary surface with main window clipper
		//m_sprim = m_ddraw->createWindowSurface();

		//m_sprim->setClipper(m_ddraw->createWindowClipper(m_pwnd->getHandle()).get());

		// create back surface with custom rect clipper
		m_sback = m_ddraw->createMemorySurface(cfg.width, cfg.height);

		m_sback->setClipper(m_ddraw->createMemoryClipper(&clientRect, 1).get());

		// save the back surface rect clipper for blt
		m_rback = clientRect;

		// get display mode info
		bool bSupportedPixelFormat = false;
		//DDPIXELFORMAT ddpf = m_sprim->getPixelFormat();
		DDPIXELFORMAT ddpf = m_ddraw->getDisplayMode().ddpfPixelFormat;
		if(ddpf.dwFlags & DDPF_RGB)
		{
			// create render context
			switch(ddpf.dwRGBBitCount)
			{
			case 16:
				if(ddpf.dwRBitMask == RGB16_RED_MASK
					&& ddpf.dwGBitMask == RGB16_GREEN_MASK
					&& ddpf.dwBBitMask == RGB16_BLUE_MASK)
				{
					m_rc = t3d::RenderContextPtr(new t3d::RenderContext16());
					m_cc = ColorConversionPtr(); // Singleton object should be destoryed before create
					m_cc = ColorConversionPtr(new ColorConversion16());
					bSupportedPixelFormat = true;
				}
				break;

			case 32:
				if(ddpf.dwRBitMask == RGB32_RED_MASK
					&& ddpf.dwGBitMask == RGB32_GREEN_MASK
					&& ddpf.dwBBitMask == RGB32_BLUE_MASK)
				{
					m_rc = t3d::RenderContextPtr(new t3d::RenderContext32());
					m_cc = ColorConversionPtr();
					m_cc = ColorConversionPtr(new ColorConversion32());
					bSupportedPixelFormat = true;
				}
				break;
			}
		}

		if(!bSupportedPixelFormat)
		{
			T3D_CUSEXCEPT(_T("unsupported pixel format"));
		}

		// create zbuffer
		m_zbuff = t3d::ZBufferPtr(new t3d::ZBuffer(cfg.width, cfg.height));

		// save back surface & zbuffer to render context
		DDSURFACEDESC2 ddsd = m_sback->lock();

		m_rc->setSurfaceBuffer(ddsd.lpSurface, ddsd.lPitch, ddsd.dwWidth, ddsd.dwHeight);

		m_sback->unlock();

		m_rc->setZBufferBuffer(m_zbuff->getBuffer(), m_zbuff->getPitch(), m_rc->getSurfaceWidth(), m_rc->getSurfaceHeight());

		// set back surface rect to render context clipper
		m_rc->setClipperRect(m_rback);

		// show main window
		m_pwnd->showWindow();

		m_pwnd->updateWindow();
	}

	void Game::bltBackSurfaceToPrimary(void)
	{
		_ASSERT(NULL != m_pwnd);

		// commit back surface to primary surface within corrected rectangle
		//m_rprim = m_pwnd->getClientRect();
		//m_pwnd->clientToScreenSelf(m_rprim);
		CRect rect = m_pwnd->getClientRect();

		// NOTE: for some reason, if the window size is greater than the desktop size, will lead these assert abort
		_ASSERT(rect == m_rback);

		//m_sprim->blt(&m_rprim, m_sback.get(), &m_rback);
		HDC hdcSrc = m_sback->getDC();
		HDC hdc = m_pwnd->getDC();
		if(!::BitBlt(hdc, rect.left, rect.top, rect.Width(), rect.Height(), hdcSrc, m_rback.left, m_rback.top, SRCCOPY))
		{
			T3D_WINEXCEPT(::GetLastError());
		}
		m_pwnd->releaseDC(hdc);
		m_sback->releaseDC(hdcSrc);
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

	int Game::run(const CONFIG_DESC & cfg /*= CONFIG_DESC(800, 600, SM_WINDOWED)*/)
	{
		int res = 1;

		try
		{
			// prepare game base
			prepare(cfg);

			// create dinput
			m_dinput = t3d::DInputPtr(new t3d::DInput(getHandle()));

			// create sys keyboard
			m_keyboard = m_dinput->createSysKeyboard();
			m_keyboard->setCooperativeLevel(m_pwnd->getHandle(), t3d::DIDevice::CL_NORMAL);
			m_keyboard->acquire();

			// create sys mouse
			m_mouse = m_dinput->createSysMouse();
			m_mouse->setCooperativeLevel(m_pwnd->getHandle(), t3d::DIDevice::CL_NORMAL);
			m_mouse->acquire();

			// create dsound
			m_dsound = t3d::DSoundPtr(new t3d::DSound());
			m_dsound->setCooperativeLevel(m_pwnd->getHandle(), t3d::DSound::CL_PRIORITY);

			// register current directory input source dir
			m_resourceMgr->registerDir(_T("."));

			// do initialize
			if(onInit())
			{
				// run main application
				res = Application::run();
			}

			// do shutdown
			onShutdown();
		}
		catch(t3d::Exception & e)
		{
			::MessageBox(m_pwnd ? m_pwnd->getHandle() : NULL, e.getFullDesc().c_str(), _T("Exception"), MB_OK);
			exit(1);
		}

		return res;
	}

	void Game::onIdle(void)
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
			return;
		}

		// swap the backup and primary surface
		bltBackSurfaceToPrimary();
	}
}
