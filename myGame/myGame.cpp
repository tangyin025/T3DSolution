
#include "stdafx.h"
#include "myGame.h"

#include <cmath>
#include <iostream>
#include <crtdbg.h>
//#include <boost/program_options.hpp>

#ifdef MYGAME_EXPORTS
BOOL APIENTRY DllMain(HANDLE	hModule,
					  DWORD		ul_reason_for_call,
					  LPVOID	lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		//_CrtDumpMemoryLeaks(); // NOTE: dont use like this, because some glabol obj havent been destroyed yet !!!
		break;
	}

	return TRUE;
	hModule;
	lpReserved;
}
#endif

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

	my::Image * ColorConversion16::convertImage(const my::Image & image)
	{
		return image.convertTo16Bits565();
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

	my::Image * ColorConversion32::convertImage(const my::Image & image)
	{
		return image.convertTo32Bits();
	}

	GameBase::CONFIG_DESC::CONFIG_DESC(DWORD _width /*= 800*/, DWORD _height /*= 600*/, int _smode /*= SM_WINDOWED*/)
		: width(_width), height(_height), smode(_smode)
	{
	}

	GameBase::GameBase(HINSTANCE hinst)
		: Application(hinst)
		, m_win(NULL)
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
		m_win = createWindow(_T("T3DLIB_WINDOW"), _T("myWindow"));

		// create ddraw object
		m_ddraw = DDrawPtr(new t3d::DDraw());

		// update video config
		prepareConfig(cfg);
	}

	void GameBase::prepareConfig(const CONFIG_DESC & cfg)
	{
		assert(m_ddraw != NULL);

		assert(NULL != m_win);

		RECT clientRect = {0, 0, cfg.width, cfg.height};

		// set ddraw and main window with config
		switch(cfg.smode)
		{
		case my::GameBase::SM_WINDOWED:
			m_ddraw->setCooperativeLevel(m_win->getHandle(), t3d::DDraw::CL_NORMAL);
			//m_ddraw->restoreDisplayMode();
			m_win->setWindowStyle(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
			m_win->setClientRect(clientRect);
			m_win->centerWindow();
			break;

		case my::GameBase::SM_FULLSCREEN16:
			m_ddraw->setCooperativeLevel(m_win->getHandle(), t3d::DDraw::CL_EXCLUSIVE);
			m_ddraw->setDisplayMode(cfg.width, cfg.height, 16);
			m_win->setWindowStyle(WS_POPUP | WS_VISIBLE);
			m_win->setClientRect(clientRect);
			break;

		case my::GameBase::SM_FULLSCREEN32:
			m_ddraw->setCooperativeLevel(m_win->getHandle(), t3d::DDraw::CL_EXCLUSIVE);
			m_ddraw->setDisplayMode(cfg.width, cfg.height, 32);
			m_win->setWindowStyle(WS_POPUP | WS_VISIBLE);
			m_win->setClientRect(clientRect);
			break;

		default:
			T3D_CUSEXCEPT(_T("unsupported screen mode"));
		}

		// show main window
		m_win->showWindow();

		// NOTE: destroy existed primary surface before m_ddraw->createWindowSurface !!!
		m_sprim = DDrawSurfacePtr();

		// create primary surface with main window clipper
		m_sprim = DDrawSurfacePtr(m_ddraw->createWindowSurface());

		DDrawClipperPtr clipperPtr(m_ddraw->createWindowClipper(m_win->getHandle()));

		m_sprim->setClipper(clipperPtr.get());

		// create back surface with custom rect clipper
		m_sback = DDrawSurfacePtr(m_ddraw->createMemorySurface(cfg.width, cfg.height));

		clipperPtr = DDrawClipperPtr(m_ddraw->createMemoryClipper(&clientRect, 1));

		m_sback->setClipper(clipperPtr.get());

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
	}

	void GameBase::bltBackSurfaceToPrimary(void)
	{
		// commit back surface to primary surface within corrected rectangle
		m_rprim = m_win->getClientRect();

		/*
		 * NOTE: for some reason, if the window size is greater than the desktop size, will lead these assert abort
		 */
		assert((m_rprim.right - m_rprim.left) == m_rback.right && m_rback.left == 0);

		assert((m_rprim.bottom - m_rprim.top) == m_rback.bottom && m_rback.top == 0);

		m_sprim->blt(&m_rprim, m_sback.get(), &m_rback);
	}

	void GameBase::fillBackSurface(const RECT & rect, const t3d::Vec4<int> & color /*= my::Vec4<int>(197, 197, 197)*/)
	{
		// clear back surface use render context's clipper
		m_sback->fill(&rect, m_cc->convertColor(color));
	}

	static inline void _clearZBuffer(void * pbuffer, DWORD pitch, const RECT & clipper, fixp28 value /*= 0*/)
	{
		// clear zbuffer with specified value
		for(LONG y = clipper.top; y < clipper.bottom; y++)
		{
			memset(&t3d::SurfaceRef<fixp28>(static_cast<fixp28*>(pbuffer), pitch)[y][clipper.left], value, (clipper.right - clipper.left) * sizeof(fixp28));
		}
	}

	void GameBase::clearZBuffer(const RECT & rect, t3d::fixp28 value /*= 0*/)
	{
		// clear zbuffer use render context's clipper
		_clearZBuffer(m_zbuff.get(), m_zbuffPitch, rect, value);
	}

	Game::Game(HINSTANCE hinst /*= Application::getModuleHandle()*/)
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
		m_dinput = DInputPtr(new t3d::DInput(getHandle()));

		m_dsound = DSoundPtr(new t3d::DSound());

		m_dsound->setCooperativeLevel(m_win->getHandle(), t3d::DSound::CL_PRIORITY);

		m_keyboard = DInputKeyboardPtr(m_dinput->createSysKeyboard(m_win->getHandle()));

		m_mouse = DInputMousePtr(m_dinput->createSysMouse(m_win->getHandle()));

		// register this to idle listener
		addIdleListener(this);

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

	void Game::nodifyIdle(void)
	{
		// update keyboard
		m_keyboard->update();

		// update mouse
		m_mouse->update();

		// do client's frame, if failed destroy main window
		if(!onFrame())
		{
			::DestroyWindow(m_win->getHandle());

			m_win = NULL;

			return;
		}

		// swap the backup and primary surface
		bltBackSurfaceToPrimary();
	}
}
