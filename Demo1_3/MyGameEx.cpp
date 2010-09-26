
#include "StdAfx.h"
#include "MyGameEx.h"

LRESULT MyWindow::OnClose(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	// for load state, there must be waiting for another thread to prepare for quiting
	if(MyGame::getSingleton().getCurrentStateName() == MyLoadState::s_name)
	{
		MyLoadStatePtr loadState = MyGame::getSingleton().getCurrentState<MyLoadState>();
		if(!loadState->getExitFlag())
		{
			loadState->setExitFlag();
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

	// create and add load state
	addState(MyLoadState::s_name, MyLoadStatePtr(new MyLoadState()));

	// create and add game state
	addState(MyGameState::s_name, MyGameStatePtr(new MyGameState()));

	// set current state to load state
	setCurrentState(MyLoadState::s_name);

	// call default parent onInit
	return my::Game::onInit(cfg);
}

void MyGame::onReport(const std::basic_string<charT> & info)
{
	m_consoleSim->report(info);
}

bool MyGame::onFrame(void)
{
	// get current state and do frame
	if(!getCurrentState<MyFrameState>()->doFrame())
	{
		return false;
	}

	// draw console simulator
	m_consoleSim->draw(m_backSurface.get(), 10, 10);

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
	m_progressBox = MyUIProgressBarBoxPtr(new MyUIProgressBarBox(CRect(CPoint(x, y), CSize(barWidth, barHeight))));

	//// //////////////////////////////////////////////////////////////////////////////////////////

	//// gain the game state obj
	//MyGameStatePtr gameState = MyGame::getSingleton().getState<MyGameState>(MyGameState::s_name);

	//// initial load jobs
	//pushJob(MyJobPtr(new SimpleCreateObjJob<my::FPSManager>(gameState->m_fpsMgr)));

	//pushJob(MyJobPtr(new SimpleCreateObjJob<my::Timer>(gameState->m_timer)));

	//pushJob(MyJobPtr(new SimpleCreateObjJob<my::Grid>(gameState->m_grid)));

	//pushJob(MyJobPtr(new SimpleCreateObjJob<my::EulerCamera>(gameState->m_eulerCam)));

	//pushJob(MyJobPtr(new SimpleCreateObjJob<MyWorld>(gameState->m_world)));

	//// //////////////////////////////////////////////////////////////////////////////////////////

	//// at lease do an empty job with weight = 1
	//pushJob(MyJobPtr(new EmptyJob()));

	// create loading thread
	CreateThread();

	// resume loading thread
	ResumeThread();
}

void MyLoadState::leaveState(void)
{
	// make sure the loading thread must be stopped
	_ASSERT(WaitForThreadStopped(0));

	// //////////////////////////////////////////////////////////////////////////////////////////

	// //////////////////////////////////////////////////////////////////////////////////////////
}

bool MyLoadState::doFrame(void)
{
	// exit application by return false with user input 'escape'
	t3d::DIKeyboard * keyboard = MyGame::getSingleton().m_keyboard.get();
	if(keyboard->isKeyDown(DIK_ESCAPE))
	{
		// DO NOT USE TerminateThread HERE!
		if(!getExitFlag())
		{
			setExitFlag();
		}
	}

	// exit application by return false with user input 'escape'
	if(WaitForThreadStopped(0))
	{
		if(getExitFlag())
		{
			return false;
		}
		else
		{
			MyGame::getSingleton().setCurrentState(MyGameState::s_name);
			return true;
		}
	}

	// define render context point
	t3d::RenderContext * rc = MyGame::getSingleton().m_rc.get();

	// clear back surface with black color
	rc->fillSurface(rc->getClipperRect(), my::Color::BLACK);

	// general information output
	std::basic_string<charT> strTmp;
	if(!getExitFlag())
	{
		m_progressBox->m_title.setText(_T("Loading ..."));
	}
	else
	{
		m_progressBox->m_title.setText(_T("Exiting ..."));
	}

	// draw progress bar
	{
		my::CriticalSectionLock lock(m_progressBoxLock);
		m_progressBox->draw(rc);
	}

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
		//// calculate total weight
		//real totalWeight = 0;
		//MyJobList::const_iterator job_iter = getJobListBegin();
		//for(; job_iter != getJobListEnd(); job_iter++)
		//{
		//	totalWeight += (*job_iter)->getWeight();
		//}

		//// make sure the total weight must greater than zero
		//_ASSERT(totalWeight > 0);

		//// do all the jobs
		//real currentWeight = 0;
		//job_iter = getJobListBegin();
		//for(; job_iter != getJobListEnd(); job_iter++)
		//{
		//	// check exit flag
		//	if(getExitFlag())
		//	{
		//		return false;
		//	}

		//	// do job
		//	if(!(*job_iter)->doJob())
		//	{
		//		setExitFlag();
		//		return false;
		//	}

		//	// update progress bar
		//	currentWeight += (*job_iter)->getWeight();
		//	{
		//		my::CriticalSectionLock lock(m_progressBoxLock);
		//		m_progressBox->setPercent(currentWeight / totalWeight);
		//	}
		//	::Sleep(33);
		//}

		// //////////////////////////////////////////////////////////////////////////////////////////

		//::Sleep(1000);

		// //////////////////////////////////////////////////////////////////////////////////////////
	}
	catch(t3d::Exception & e)
	{
		MyGame::getSingleton().m_wnd->SendMessage(WM_USER + 0, (WPARAM)&e);
		setExitFlag(true);
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
	// //////////////////////////////////////////////////////////////////////////////////////////
//
//#ifdef _DEBUG
//	// clear all surface to test software rendering clipper
//	CRect clipper = MyGame::getSingleton().m_rc->getClipperRect();
//	MyGame::getSingleton().m_rc->setClipperRect(MyGame::getSingleton().m_backSurfaceRect);
//	MyGame::getSingleton().m_rc->fillSurface(MyGame::getSingleton().m_backSurfaceRect, my::Color::WHITE);
//	MyGame::getSingleton().m_rc->fillZbuffer(MyGame::getSingleton().m_backSurfaceRect, 0);
//	MyGame::getSingleton().m_rc->fillStencilBuffer(MyGame::getSingleton().m_backSurfaceRect, 0);
//	MyGame::getSingleton().m_rc->setClipperRect(clipper);
//	MyGame::getSingleton().m_wnd->InvalidateRect(NULL);
//#endif

	// create and start fps manager
	m_fpsMgr = my::FPSManagerPtr(new my::FPSManager());
	m_fpsMgr->start();

	// create and start timer
	m_timer = my::TimerPtr(new my::Timer());
	m_timer->start();

	// create grid
	m_grid = my::GridPtr(new my::Grid(100, 10));

	// create eular camera
	m_eulerCam = my::EulerCameraPtr(new my::EulerCamera());
	//m_eulerCam->setDefaultPosition(my::Vec4<real>(50, 50, -50));
	//m_eulerCam->setDefaultRotation(my::Vec4<real>(DEG_TO_RAD(45), DEG_TO_RAD(-45), DEG_TO_RAD(0)));
	m_eulerCam->reset();

	// create physical world
	m_world = MyWorldPtr(new MyWorld());

	// //////////////////////////////////////////////////////////////////////////////////////////
}

void MyGameState::leaveState(void)
{
	// //////////////////////////////////////////////////////////////////////////////////////////

	// //////////////////////////////////////////////////////////////////////////////////////////
}

bool MyGameState::doFrame(void)
{
	// //////////////////////////////////////////////////////////////////////////////////////////

	// obtain render context pointer
	t3d::RenderContext * rc = MyGame::getSingleton().m_rc.get();

	// exit application by return false with user input 'escape'
	t3d::DIKeyboard * keyboard = MyGame::getSingleton().m_keyboard.get();
	if(keyboard->isKeyDown(DIK_ESCAPE))
	{
		return false;
	}

	// fps manager, witch calculated fps by incremented frame
	// the precision of this fps manager witch depend on sampling second was low, but its enough
	m_fpsMgr->addFrame();

	// the high precision timer, witch calculate time interval between last frame by cpu count
	// to avoid to too many time interval that crash the physical engine, set the max interval as 30 / 1 second
	const real elapsedTime = std::min((real)m_timer->getElapsedTime(), (real)0.033);
//
//#ifdef _DEBUG
//	// here i created the clipper region smaller than the window, only used to test the clipper bug
//	// because of the software simulating, the algorithm of cutting polygon is implemented by software,
//	// so the unstrong algorithm will lead edge overflow, and even crash the application
//	// reducing the clipper region will somehow avoid this phenomenon
//	CRect clipper(MyGame::getSingleton().m_backSurfaceRect);
//	clipper.DeflateRect(10, 10);
//	rc->setClipperRect(clipper);
//#endif

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
	if(keyboard->isKeyDown(DIK_LCONTROL))
	{
		m_eulerCam->update(keyboard, MyGame::getSingleton().m_mouse.get(), elapsedTime);
	}
	else
	{
		m_eulerCam->addRotation(my::EulerCamera::buildRotOffset(MyGame::getSingleton().m_mouse.get()));

		// step physics world
		const unsigned count = 30;
		unsigned decrement = count;
		while(decrement--)
		{
			m_world->runPhysics(elapsedTime / count);
		}

		t3d::Mat4<real> matRotation = mat3RotXYZ(m_eulerCam->getRotation());
		t3d::Mat4<real> matPosition = t3d::mat3Mov(my::Vec4<real>(0, 0, -30)) * matRotation * t3d::mat3Mov(m_world->m_viewpoint.particle->getPosition());
		m_eulerCam->setPosition(my::Vec4<real>::ZERO * matPosition);
	}
	rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEuler(m_eulerCam->getPosition(), m_eulerCam->getRotation()));

	// set render context lights
	my::Vec4<real> l_pos(-30, 30, -30);
	l_pos *= t3d::mat3RotZXY(m_eulerCam->getRotation()) * t3d::mat3Mov(m_eulerCam->getPosition());
	rc->clearLightList();
	rc->pushLightAmbient(my::Vec4<real>(0.2f, 0.2f, 0.2f));
	rc->pushLightPoint(my::Vec4<real>(1, 1, 1), l_pos); //my::Vec4<real>(100, 100, -100));

	// draw default grid, with use to test distance of the scene
	m_grid->drawZBufferRW(rc);

	// draw character body
	drawSphereWireZBufferRW(
		rc,
		m_world->m_character.sphere.getRadius(),
		m_world->m_character.body->getAwake() ? my::Color::RED : t3d::vec3Mul(my::Color::RED, 0.7f),
		m_world->m_character.body->getTransform());

	// draw viewpoint particle
	rc->setAmbient(my::Color::YELLOW);
	rc->setDiffuse(my::Color::YELLOW);
	drawSphereGouraudZBufferRW(
		rc,
		1,
		t3d::mat3Mov(m_world->m_viewpoint.particle->getPosition()));

	// draw character direction
	drawLinePointAndNormalZBufferRW(
		rc,
		my::Vec4<real>::ZERO,
		my::Vec4<real>(0, 0, 10),
		my::Color::BLUE,
		m_world->m_character.body->getTransform());

	// draw box
	for(size_t i = 0; i < m_world->m_boxList.size(); i++)
	{
		t3d::Vec4<real> color(m_world->m_boxBodyList[i]->getAwake() ? my::Color::BLUE : t3d::vec3Mul(my::Color::BLUE, 0.7f));
		rc->setAmbient(color);
		rc->setDiffuse(color);
		drawCubeGouraudZBufferRW(
			rc,
			m_world->m_boxList[i].getHalfSize(),
			m_world->m_boxBodyList[i]->getTransform(),
			m_world->m_boxBodyList[i]->getRotationTransform());
	}

	// general information output
	std::basic_string<charT> strTmp;
	HDC hdc = MyGame::getSingleton().m_backSurface->getDC();

	int textx = rc->getClipperRect().left + 10;
	int texty = rc->getClipperRect().top + 10;

	strTmp = str_printf(_T("fps: %.1f"), m_fpsMgr->getFPS());
	::TextOut(hdc, textx, texty, strTmp.c_str(), (int)strTmp.length());

	strTmp = str_printf(_T("fps: %.1f"), 1 / elapsedTime);
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	t3d::Vec4<real> camPos = rc->getCameraPosition();
	strTmp = str_printf(_T("cam.pos: %f, %f, %f"),
		camPos.x, camPos.y, camPos.z);
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	strTmp = str_printf(_T("cam.rot: %f, %f, %f"),
		RAD_TO_DEG(m_eulerCam->getRotation().x), RAD_TO_DEG(m_eulerCam->getRotation().y), RAD_TO_DEG(m_eulerCam->getRotation().z));
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	MyGame::getSingleton().m_backSurface->releaseDC(hdc);

	// //////////////////////////////////////////////////////////////////////////////////////////

	return true;
}
