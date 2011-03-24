﻿
#include "StdAfx.h"
#include "MyGameEx.h"

LRESULT MyWindow::OnClose(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	// for load state, there must be waiting for another thread to prepare for quiting
	if(MyGame::getSingleton().getCurrentStateName() == MyLoadState::s_name)
	{
		MyLoadStatePtr loadState = MyGame::getSingleton().getCurrentState<MyLoadState>();
		if(!loadState->getExitFlagSync())
		{
			loadState->setExitFlagSync();
			return 0;
		}
	}

	bHandled = FALSE;
	return 0;
}

LRESULT MyWindow::OnUser0(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	// handle the exception thrown from the load state thread
	t3d::Exception * e = reinterpret_cast<t3d::Exception *>(wParam);
	_ASSERT(NULL != e);
	MessageBox(e->getFullDesc().c_str(), _T("Exception"));

	return 0;
}

MyGame::MyGame(void)
{
}

MyGame::~MyGame(void)
{
}

my::WindowPtr MyGame::newWindow(void)
{
	// new a driver window
	return my::WindowPtr(new MyWindow());
}

bool MyGame::onInit(const my::Config & cfg)
{
	// call default parent onInit
	if(!my::Game::onInit(cfg))
	{
		return false;
	}

	// create console simulate
	m_consoleSim = my::ConsoleSimulatorPtr(new my::ConsoleSimulator(10));

	// set self as error listener
	my::ErrorReporter::getSingleton().addErrorListener(this);

	// predefine config values
	const CSize screen(m_rc->getSurfaceWidth(), m_rc->getSurfaceHeight());

	// calculate aspect ratio
	real aspect_ratio;
	switch(cfg.getInt(_T("aspectratio")))
	{
	default:
		_ASSERT(ASPECT_RATIO_STRETCHED == cfg.getInt(_T("aspectratio")));
		aspect_ratio = (real)screen.cx / screen.cy;
		break;

	case ASPECT_RATIO_STANDARD:
		aspect_ratio = (real)4 / 3;
		break;

	case ASPECT_RATIO_WIDESCREEN:
		aspect_ratio = (real)16 / 9;
		break;
	}

	// adjust clipper region by aspect ratio
	LONG lWidth, lHeight;
	CRect clipper;
	if(aspect_ratio < (real)screen.cx / (real)screen.cy)
	{
		lHeight = screen.cy;
		lWidth = (LONG)(lHeight * aspect_ratio + .5f);
		clipper.left = (screen.cx - lWidth) / 2;
		clipper.top = 0;
		clipper.right = clipper.left + lWidth;
		clipper.bottom = clipper.top + lHeight;
	}
	else
	{
		lWidth = screen.cx;
		lHeight = (LONG)(lWidth / aspect_ratio + .5f);
		clipper.left = 0;
		clipper.top = (screen.cy - lHeight) / 2;
		clipper.right = clipper.left + lWidth;
		clipper.bottom = clipper.top + lHeight;
	}

	// validate the clipper region
	_ASSERT(clipper.left	>= m_backSurfaceRect.left);
	_ASSERT(clipper.top		>= m_backSurfaceRect.top);
	_ASSERT(clipper.right	<= m_backSurfaceRect.right);
	_ASSERT(clipper.bottom	<= m_backSurfaceRect.bottom);

	// update clipper region to render context,
	// and later the camera's viewport & projection will be recalculated by this clipper rect
	m_rc->setClipperRect(clipper);

	// create and start fps manager
	m_fpsMgr = my::FPSManagerPtr(new my::FPSManager());
	m_fpsMgr->start();

	// create and start timer
	m_timer = my::TimerPtr(new my::Timer());
	m_timer->start();

	// create eular camera
	m_eulerCam = my::EulerCameraPtr(new my::EulerCamera());
	m_rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEuler(m_eulerCam->getPosition(), m_eulerCam->getRotation()));

	// create common ui font
	HDC hdc = m_backSurface->getDC();
	m_font = my::FontPtr(new my::Font(my::Font::CalculateFontHeightByPointSize(hdc, 10)));
	m_backSurface->releaseDC(hdc);

	// create and add load state
	addState(MyLoadState::s_name, MyLoadStatePtr(new MyLoadState()));

	// create and add game state
	addState(MyGameState::s_name, MyGameStatePtr(new MyGameState()));

	// set current state to load state
	setCurrentState(MyLoadState::s_name);

	return true;
}

void MyGame::onReport(const std::basic_string<charT> & info)
{
	m_consoleSim->report(info);
}

bool MyGame::onFrame(void)
{
	// fps manager, witch calculated fps by incremented frame
	// the precision of this fps manager witch depend on sampling second was low, but its enough
	m_fpsMgr->addFrame();

	// the high precision timer, witch calculate time interval between last frame by cpu count
	// to avoid to too many time interval that crash the physical engine, set the max interval as 30 / 1 second
	const real elapsedTime = std::min((real)m_timer->getElapsedTime(), (real)0.033);

	// get current state and do frame
	if(!getCurrentState<MyFrameState>()->doFrame(elapsedTime))
	{
		return false;
	}

	// get the back buffer dc
	HDC hdc = m_backSurface->getDC();
	HANDLE oldFont = SelectObject(hdc, m_font->GetHandle());

	// output fps
	int textx = m_rc->getClipperRect().left + 10;
	int texty = m_rc->getClipperRect().top + 10;
	std::basic_string<charT> strTmp = str_printf(_T("fps: %.1f"), m_fpsMgr->getFPS());
	::TextOut(hdc, textx, texty, strTmp.c_str(), (int)strTmp.length());
	strTmp = str_printf(_T("fps: %.1f"), 1 / elapsedTime);
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	// output camera position
	strTmp = str_printf(_T("cam.pos: %f, %f, %f"),
		m_rc->getCameraPosition().x,
		m_rc->getCameraPosition().y,
		m_rc->getCameraPosition().z);
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	// output camera rotation
	strTmp = str_printf(_T("cam.rot: %f, %f, %f"),
		RAD_TO_DEG(m_eulerCam->getRotation().x),
		RAD_TO_DEG(m_eulerCam->getRotation().y),
		RAD_TO_DEG(m_eulerCam->getRotation().z));
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	// release back buffer dc
	SelectObject(hdc, oldFont);
	m_backSurface->releaseDC(hdc);

	// draw console simulator
	m_consoleSim->draw(m_backSurface.get(), textx, texty += 20);

	return true;
}

void MyGame::onShutdown(void)
{
	// get current state and do leaveState
	getCurrentState<MyState>()->leaveState();
}

MyFrameState::MyFrameState(void)
{
}

MyFrameState::~MyFrameState(void)
{
}

const std::basic_string<charT> MyLoadState::s_name(_T("MyLoadState"));

MyLoadState::MyLoadState(void)
: m_exitFlag(false)
{
}

MyLoadState::~MyLoadState(void)
{
}

void MyLoadState::enterState(void)
{
	// initial progress box
	int barWidth = 250;
	int barHeight = 60;
	CRect clipper = MyGame::getSingleton().m_rc->getClipperRect();
	int x = clipper.left + (clipper.Width() - barWidth) / 2;
	int y = clipper.top + (clipper.Height() - barHeight) / 2;
	m_progressBox = MyUIProgressBarBoxPtr(
		new MyUIProgressBarBox(CRect(CPoint(x, y), CSize(barWidth, barHeight)), MyGame::getSingleton().m_font));

	// create loading thread
	CreateThread();

	// resume loading thread
	ResumeThread();
}

void MyLoadState::leaveState(void)
{
	// make sure the loading thread must be stopped
	_ASSERT(WaitForThreadStopped(0));
}

bool MyLoadState::doFrame(real elapsedTime)
{
	// exit application by return false with user input 'escape'
	t3d::DIKeyboard * keyboard = MyGame::getSingleton().m_keyboard.get();
	if(keyboard->isKeyDown(DIK_ESCAPE))
	{
		// DO NOT USE TerminateThread HERE!
		if(!getExitFlagSync())
		{
			setExitFlagSync(true);
		}
	}

	// exit application by return false with user input 'escape'
	if(WaitForThreadStopped(0))
	{
		if(getExitFlagSync())
		{
			// the working thread should be failed, and stopped unexpectly
			return false;
		}
		else
		{
			// the working thread succeeded, and shift to the next scene
			MyGame::getSingleton().setCurrentState(MyGameState::s_name);
			return true;
		}
	}

	// define render context point
	t3d::RenderContext * rc = MyGame::getSingleton().m_rc.get();

	// clear back surface with black color
	rc->fillSurface(rc->getClipperRect(), my::Color::BLACK);

	// draw progress box
	m_progressBoxLock.enter();
	m_progressBox->draw(rc);
	m_progressBoxLock.leave();

	// sleep some time to set aside cpu resource to back thread
	::Sleep(33);

	return true;
}

DWORD MyLoadState::onProc(void)
{
	// NOTE: because of multi-thread frame, the try block in the main thread
	// could not catch any exceptions which was thrown from the this thread proc
	try
	{
		m_progressBoxLock.enter();
		m_progressBox->setTitleText(_T("正在读取 ..."));
		m_progressBoxLock.leave();

		MyGameState * gameState = MyGame::getSingleton().getState<MyGameState>(MyGameState::s_name).get();
		_ASSERT(NULL != gameState);

		// create physics world for game state
		gameState->m_phyWorld = MyWorldPtr(new MyWorld());

		// create grid for game state
		gameState->m_grid = my::GridPtr(new my::Grid(100, 10));

		const int loopCount = 5;
		for(int i = 1; i <= loopCount; i++)
		{
			::Sleep(100);
			m_progressBoxLock.enter();
			m_progressBox->setPercent((real)i / loopCount);
			m_progressBoxLock.leave();
		}
	}
	catch(t3d::Exception & e)
	{
		MyGame::getSingleton().m_wnd->SendMessage(WM_USER + 0, (WPARAM)&e);
		setExitFlagSync(true);
	}

	return 0;
}

const std::basic_string<charT> MyGameState::s_name(_T("MyGameState"));

MyGameState::MyGameState(void)
{
}

MyGameState::~MyGameState(void)
{
}

void MyGameState::enterState(void)
{
	// create eular camera
	my::EulerCamera * eulerCam = MyGame::getSingleton().m_eulerCam.get();
	eulerCam->setDefaultPosition(my::Vec4<real>(50, 50, -50));
	eulerCam->setDefaultRotation(my::Vec4<real>(DEG_TO_RAD(45), DEG_TO_RAD(-45), DEG_TO_RAD(0)));
	eulerCam->reset();

	// VERIFY specified date should be created
	_ASSERT(NULL != m_phyWorld);
	_ASSERT(NULL != m_grid);
}

void MyGameState::leaveState(void)
{
}

bool MyGameState::doFrame(real elapsedTime)
{
	// obtain render context pointer
	t3d::RenderContext * rc = MyGame::getSingleton().m_rc.get();

	// exit application by return false with user input 'escape'
	t3d::DIKeyboard * keyboard = MyGame::getSingleton().m_keyboard.get();
	if(keyboard->isKeyDown(DIK_ESCAPE))
	{
		return false;
	}

	// clear back surface with gray color
	rc->fillSurface(rc->getClipperRect(), my::Color(0.8f, 0.8f, 0.8f));

	// clear zbuffer with infinite distance
	rc->fillZbuffer(rc->getClipperRect(), 0);

	// clear stencil buffer with zero
	rc->fillStencilBuffer(rc->getClipperRect(), 0);

	// set render context camera
	rc->setViewport(rc->getClipperRect());
	rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), rc->getClipperRect().Width(), rc->getClipperRect().Height()));
	rc->setCameraNearZ(1);
	rc->setCameraFarZ(10000);

	// update euler cameras position and orientation by user input
	my::EulerCamera * eulerCam = MyGame::getSingleton().m_eulerCam.get();
	eulerCam->update(keyboard, MyGame::getSingleton().m_mouse.get(), elapsedTime);
	rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEuler(eulerCam->getPosition(), eulerCam->getRotation()));

	// 30 frames per rendering frame for physics engine
	const unsigned phyCount = 30;
	for(unsigned i = 0; i < phyCount; i++)
	{
		m_phyWorld->runPhysics(elapsedTime / phyCount);
	}

	// set render context lights
	my::Vec4<real> l_pos(-30, 30, -30);
	l_pos *= t3d::mat3RotZXY(eulerCam->getRotation()) * t3d::mat3Mov(eulerCam->getPosition());
	rc->clearLightList();
	rc->pushLightAmbient(my::Vec4<real>(0.2f, 0.2f, 0.2f));
	rc->pushLightPoint(my::Color::WHITE, l_pos);

	// draw default grid, with use to test distance of the scene
	m_grid->drawZBufferRW(rc);

	return true;
}
