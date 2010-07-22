
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

	Singleton<ErrorReporter>::DRIVED_CLASS_PTR ErrorReporter::s_ptr;

	ErrorReporter::ErrorReporter(void)
	{
	}

	ErrorReporter::~ErrorReporter(void)
	{
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

	my::ImagePtr ColorConversion16::convertImage(const my::ImagePtr image)
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

	my::ImagePtr ColorConversion32::convertImage(const my::ImagePtr image)
	{
		return image->convertTo32Bits();
	}

	GameWnd::GameWnd(HWND hwnd)
		: Window(hwnd)
	{
	}

	GameWnd::~GameWnd(void)
	{
	}

	LRESULT GameWnd::onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		_ASSERT(hwnd == m_hwnd);

		switch(message)
		{
		case WM_PAINT:
			{
				// obtain global application object
				Game * game = dynamic_cast<Game *>(Application::getSingletonPtr());

				// back surface must be created
				_ASSERT(NULL != game->m_backSurface);

				// update the attached back surface to client area
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HDC hdcSrc = game->m_backSurface->getDC();
				BitBlt(
					hdc,
					game->m_backSurfaceRect.left,
					game->m_backSurfaceRect.top,
					game->m_backSurfaceRect.Width(),
					game->m_backSurfaceRect.Height(),
					hdcSrc,
					0,
					0,
					SRCCOPY);
				game->m_backSurface->releaseDC(hdcSrc);
				EndPaint(hwnd, &ps);
				return 0;
			}
		}

		return Window::onProc(hwnd, message, wparam, lparam);
	}

	Game::Game(void)
		: m_pwnd(NULL)
	{
	}

	Game::~Game(void)
	{
	}

	Window * Game::newWindow(HWND hwnd)
	{
		return new GameWnd(hwnd);
	}

	bool Game::prepare(const Config & cfg)
	{
		// create main window
		m_pwnd = createWindow(getModuleFileName());

		// predefine config values
		const int cfgWidth = cfg.getIntOrDefault(_T("width"), 800);
		const int cfgHeight = cfg.getIntOrDefault(_T("height"), 600);
		const int cfgScreenmode = cfg.getIntOrDefault(_T("screenmode"), SCREEN_MODE_WINDOWED);

		if(NULL == m_pwnd)
		{
			return false;
		}

		// create ddraw object
		m_ddraw = t3d::DDrawPtr(new t3d::DDraw());

		m_ddraw->setCooperativeLevel(m_pwnd->getHandle(), t3d::DDraw::CL_NORMAL);

		// set back surface rect
		m_backSurfaceRect.SetRect(0, 0, cfgWidth, cfgHeight);

		// create ddraw and adjust main window
		switch(cfgScreenmode)
		{
		case SCREEN_MODE_WINDOWED:
			m_ddraw->setCooperativeLevel(m_pwnd->getHandle(), t3d::DDraw::CL_NORMAL);
			m_pwnd->setWindowStyle(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
			m_pwnd->adjustClientRect(m_backSurfaceRect);
			m_pwnd->centerWindow();
			break;

		case SCREEN_MODE_FULLSCREEN16:
			m_ddraw->setCooperativeLevel(m_pwnd->getHandle(), t3d::DDraw::CL_EXCLUSIVE);
			m_ddraw->setDisplayMode(cfgWidth, cfgHeight, 16);
			m_pwnd->setWindowStyle(WS_POPUP | WS_VISIBLE);
			m_pwnd->adjustClientRect(m_backSurfaceRect);
			m_pwnd->InvalidateRect(NULL);
			break;

		case SCREEN_MODE_FULLSCREEN32:
			m_ddraw->setCooperativeLevel(m_pwnd->getHandle(), t3d::DDraw::CL_EXCLUSIVE);
			m_ddraw->setDisplayMode(cfgWidth, cfgHeight, 32);
			m_pwnd->setWindowStyle(WS_POPUP | WS_VISIBLE);
			m_pwnd->adjustClientRect(m_backSurfaceRect);
			m_pwnd->InvalidateRect(NULL);
			break;

		default:
			T3D_CUSEXCEPT(_T("unsupported screen mode"));
		}

		//// destory previous primary surface
		//m_primSurface = t3d::DDSurfacePtr();

		//// create primary surface
		//m_primSurface = m_ddraw->createWindowSurface();

		//m_primSurface->setClipper(m_ddraw->createWindowClipper(m_pwnd->getHandle()).get());

		//DDPIXELFORMAT ddpf = m_primSurface->getPixelFormat();
		DDPIXELFORMAT ddpf = m_ddraw->getDisplayMode().ddpfPixelFormat;
		if( !(ddpf.dwFlags & DDPF_RGB) )
		{
			T3D_CUSEXCEPT(_T("unsupported pixel format"));
		}

		// create pixel dependency objects
		// NOTE: some singleton object should be re-destoryed before creating, such as m_cc
		if(ddpf.dwRGBBitCount == 16
			&& ddpf.dwRBitMask == RGB16_RED_MASK
			&& ddpf.dwGBitMask == RGB16_GREEN_MASK
			&& ddpf.dwBBitMask == RGB16_BLUE_MASK)
		{
			m_rc = t3d::RenderContextPtr(new t3d::RenderContext16());
			m_cc = ColorConversionPtr();
			m_cc = ColorConversionPtr(new ColorConversion16());
		}
		else if(ddpf.dwRGBBitCount == 32
			&& ddpf.dwRBitMask == RGB32_RED_MASK
			&& ddpf.dwGBitMask == RGB32_GREEN_MASK
			&& ddpf.dwBBitMask == RGB32_BLUE_MASK)
		{
			m_rc = t3d::RenderContextPtr(new t3d::RenderContext32());
			m_cc = ColorConversionPtr();
			m_cc = ColorConversionPtr(new ColorConversion32());
		}
		else
		{
			T3D_CUSEXCEPT(_T("unsupported pixel format"));
		}

		// create screen compatible back surface
		m_backSurface = m_ddraw->createMemorySurface(cfgWidth, cfgHeight, ddpf);

		m_backSurface->setClipper(m_ddraw->createMemoryClipper(&m_backSurfaceRect, 1).get());

		// create dinput
		m_dinput = t3d::DInputPtr(new t3d::DInput(getHandle()));

		// create sys keyboard
		m_keyboard = m_dinput->createSysKeyboard();

		m_keyboard->setCooperativeLevel(m_pwnd->getHandle(), t3d::DIDevice::CL_NORMAL);

		// create sys mouse
		m_mouse = m_dinput->createSysMouse();

		m_mouse->setCooperativeLevel(m_pwnd->getHandle(), t3d::DIDevice::CL_NORMAL);

		// create dsound
		m_dsound = t3d::DSoundPtr(new t3d::DSound());

		m_dsound->setCooperativeLevel(m_pwnd->getHandle(), t3d::DSound::CL_PRIORITY);

		// create zbuffer
		m_zbuff = t3d::ZBufferPtr(new t3d::ZBuffer(cfgWidth, cfgHeight));

		// save back surface & zbuffer to render context
		DDSURFACEDESC2 ddsd = m_backSurface->lock();

		m_rc->setSurfaceBuffer(ddsd.lpSurface, ddsd.lPitch, ddsd.dwWidth, ddsd.dwHeight);

		m_backSurface->unlock();

		m_rc->setZBufferBuffer(m_zbuff->getBuffer(), m_zbuff->getPitch(), m_rc->getSurfaceWidth(), m_rc->getSurfaceHeight());

		// set back surface rect to render context clipper
		m_rc->setClipperRect(m_backSurfaceRect);

		// show main window
		m_pwnd->showWindow();

		// update window immediately
		m_pwnd->updateWindow();

		return onInit(cfg);
	}

	//int Game::run(LPTSTR lpCmdLine)
	//{
	//	// build program option descriptions
	//	int i_opt;
	//	boost::program_options::options_description desc("my game options");
	//	desc.add_options()
	//		("width,W", boost::program_options::value<int>(&i_opt)->default_value(800), "specify resolution width")
	//		("height,H", boost::program_options::value<int>(&i_opt)->default_value(600), "specify resolution height")
	//		("screenmode,S", boost::program_options::value<int>(&i_opt)->default_value(SCREEN_MODE_WINDOWED), "specify color deepth for fullscreen mode");

	//	// store comman line argument to variables map
	//	boost::program_options::variables_map vmap;
	//	std::vector<std::basic_string<charT> > args = boost::program_options::split_winmain(lpCmdLine);
	//	boost::program_options::store(
	//		boost::program_options::basic_command_line_parser<charT>(args).options(desc).run(), vmap);
	//	boost::program_options::notify(vmap);

	//	// build config obj
	//	Config cfg;
	//	cfg.addInt(_T("width"), vmap["width"].as<int>());
	//	cfg.addInt(_T("height"), vmap["height"].as<int>());
	//	cfg.addInt(_T("screenmode"), vmap["screenmode"].as<int>());
	//	return run(cfg);
	//}

	int Game::run(const Config & cfg)
	{
		int res = 1;

		// set up configuration
		if(prepare(cfg))
		{
			// run main application
			res = Application::run();
		}

		// do shutdown
		onShutdown();

		return res;
	}

	void Game::onIdle(void)
	{
		// update keyboard state
		m_keyboard->acquire();

		m_keyboard->update();

		// update mouse state
		m_mouse->acquire();

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
		m_pwnd->InvalidateRect(&m_rc->getClipperRect(), FALSE);
	}

	bool Game::onInit(const Config & cfg)
	{
		return true;
		UNREFERENCED_PARAMETER(cfg);
	}

	bool Game::onFrame(void)
	{
		return true;
	}

	void Game::onShutdown(void)
	{
	}
}
