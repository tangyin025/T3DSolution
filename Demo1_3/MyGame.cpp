
#include "StdAfx.h"
#include "MyGame.h"
#include "MyConfig.h"

MyGame::MyGame(void)
{
}

MyGame::~MyGame(void)
{
}

bool MyGame::onInit(const CONFIG_DESC & cfg)
{
	// calculate aspect ratio
	const MyConfig * pcfg = static_cast<const MyConfig *>(&cfg);
	real aspect_ratio;
	switch(pcfg->aspect_ratio_mode)
	{
	default:
		_ASSERT(MyConfig::ASPECT_RATIO_STRETCHED == pcfg->aspect_ratio_mode);
		aspect_ratio = (real)pcfg->width / pcfg->height;
		break;

	case MyConfig::ASPECT_RATIO_STANDARD:
		aspect_ratio = (real)4 / 3;
		break;

	case MyConfig::ASPECT_RATIO_WIDESCREEN:
		aspect_ratio = (real)16 / 9;
		break;
	}

	// adjust clipper region by aspect ratio
	LONG lWidth, lHeight;
	CRect clipper;
	if(aspect_ratio < (real)pcfg->width / (real)pcfg->height)
	{
		lHeight = pcfg->height;
		lWidth = (LONG)(lHeight * aspect_ratio + .5f);
		clipper.left = (pcfg->width - lWidth) / 2;
		clipper.top = 0;
		clipper.right = clipper.left + lWidth;
		clipper.bottom = clipper.top + lHeight;
	}
	else
	{
		lWidth = pcfg->width;
		lHeight = (LONG)(lWidth / aspect_ratio + .5f);
		clipper.left = 0;
		clipper.top = (pcfg->height - lHeight) / 2;
		clipper.right = clipper.left + lWidth;
		clipper.bottom = clipper.top + lHeight;
	}

	// validate the clipper region
	_ASSERT(clipper.left	>= m_rback.left);
	_ASSERT(clipper.top		>= m_rback.top);
	_ASSERT(clipper.right	<= m_rback.right);
	_ASSERT(clipper.bottom	<= m_rback.bottom);

	// update clipper region to render context
	m_rc->setClipperRect(clipper);

	// create and add load state
	addState(MyLoadState::s_name, MyLoadStatePtr(new MyLoadState(this)));

	// create and add game state
	addState(MyGameState::s_name, MyGameStatePtr(new MyGameState(this)));

	// set current state as load state
	setCurrentState(MyLoadState::s_name);

	// call default parent onInit
	return my::Game::onInit(cfg);
}

bool MyGame::onFrame(void)
{
	// get current state and do onFrame
	if(!getCurrentState<MyStateBase>()->onFrame())
	{
		return false;
	}

	// call default parent onFrame
	return my::Game::onFrame();
}

void MyGame::onShutdown(void)
{
	//// get current state and do leaveState
	//getCurrentState<MyStateBase>()->leaveState();
}

MyStateBase::MyStateBase(void)
{
}

MyStateBase::~MyStateBase(void)
{
}

const std::basic_string<charT> MyLoadState::s_name(_T("MyLoadState"));

MyLoadState::MyLoadState(MyGame * game)
	: m_game(game)
{
}

MyLoadState::~MyLoadState(void)
{
}

void MyLoadState::enterState(void)
{
	// begin work thread here
	CreateThread();
	ResumeThread();
}

void MyLoadState::leaveState(void)
{
}

bool MyLoadState::onFrame(void)
{
	// exit application by return false with user input 'escape'
	if(m_game->m_keyboard->isKeyDown(DIK_ESCAPE))
	{
		// DO NOT USE TerminateThread HERE!
		TerminateThread(1); // JUST FOR TEST!!!
		return false;
	}

	// exit application by return false with user input 'escape'
	if(WaitForThreadStopped(0))
	{
		m_game->setCurrentState(MyGameState::s_name);
		return true;
	}

	// define render context point
	t3d::RenderContext * rc = m_game->m_rc.get();

	// clear back surface with gray color
	rc->fillSurface(rc->getClipperRect(), my::Color::BLACK);

	// general information output
	std::basic_string<charT> strTmp;
	HDC hdc = m_game->m_sback->getDC();

	int textx = rc->getClipperRect().left + 10;
	int texty = rc->getClipperRect().top + 10;

	strTmp = _T("loading ...");
	::TextOut(hdc, textx, texty, strTmp.c_str(), (int)strTmp.length());

	m_game->m_sback->releaseDC(hdc);

	// sleep some time to set aside cpu resource to back thread
	::Sleep(33);
	return true;
}

DWORD MyLoadState::onProc(void)
{
	// initialize fps manager
	m_game->m_fpsMgr = my::FPSManagerPtr(new my::FPSManager());
	m_game->m_fpsMgr->start();

	// initialize timer
	m_game->m_timer = my::TimerPtr(new my::Timer());
	m_game->m_timer->start();

	// initialize grid
	m_game->m_grid = my::GridPtr(new my::Grid());

	// initialize euler camera
	m_game->m_eulerCam = my::EulerCameraPtr(new my::EulerCamera());
	m_game->m_eulerCam->setDefaultPosition(my::Vec4<real>(-50, 50, -50));
	m_game->m_eulerCam->setDefaultRotation(my::Vec4<real>(DEG_TO_RAD(45), DEG_TO_RAD(45), DEG_TO_RAD(0)));
	m_game->m_eulerCam->reset();

	// simulate times occupied process
	::Sleep(5000);
	return 0;
}

const std::basic_string<charT> MyGameState::s_name(_T("MyGameState"));

MyGameState::MyGameState(MyGame * game)
	: m_game(game)
{
}

MyGameState::~MyGameState(void)
{
}

void MyGameState::enterState(void)
{
	// verify all data are created properly
	_ASSERT(m_game->m_fpsMgr);
	_ASSERT(m_game->m_timer);
	_ASSERT(m_game->m_grid);
	_ASSERT(m_game->m_eulerCam);
}

void MyGameState::leaveState(void)
{
}

bool MyGameState::onFrame(void)
{
	// define render context point
	t3d::RenderContext * rc = m_game->m_rc.get();
	my::EulerCamera * eularCam = m_game->m_eulerCam.get();

	// exit application by return false with user input 'escape'
	if(m_game->m_keyboard->isKeyDown(DIK_ESCAPE))
	{
		return false;
	}

	// fps manager, witch calculated fps by incremented frame
	// the precision of this fps manager witch depend on sampling second was low, but its enough
	m_game->m_fpsMgr->addFrame();

	// the high precision timer, witch calculate time interval between last frame by cpu count
	// to avoid to too many time interval that crash the physical engine, set the max interval as 30 / 1 second
	const real elapsedTime = std::min((real)m_game->m_timer->getElapsedTime(), (real)0.033);

	//// here i created the clipper region smaller than the window, only used to test the clipper bug
	//// because of the software simulating, the algorithm of cutting polygon is implemented by software,
	//// so the unstrong algorithm will lead edge overflow, and even crash the application
	//// reducing the clipper region will somehow avoid this phenomenon
	//CRect clipper(m_game->m_rback);
	//clipper.DeflateRect(10, 10);
	//rc->setClipperRect(clipper);

	// clear back surface with gray color
	rc->fillSurface(rc->getClipperRect(), my::Color(0.8f, 0.8f, 0.8f));

	// clear zbuffer with infinite distance
	rc->fillZbuffer(rc->getClipperRect(), 0);

	// set render context camera
	rc->setViewport(rc->getClipperRect());
	rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), rc->getClipperRect().Width(), rc->getClipperRect().Height()));
	rc->setCameraNearZ(1);
	rc->setCameraFarZ(10000);

	// update euler cameras position and orientation by user input
	eularCam->update(m_game->m_keyboard.get(), m_game->m_mouse.get(), elapsedTime);
	rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEuler(eularCam->getPosition(), eularCam->getRotation()));

	// set render context lights
	my::Vec4<real> l_pos(-30, 30, -30);
	l_pos *= t3d::mat3RotZXY(eularCam->getRotation()) * t3d::mat3Mov(eularCam->getPosition());
	rc->clearLightList();
	rc->pushLightAmbient(my::Vec4<real>(0.2f, 0.2f, 0.2f));
	rc->pushLightPoint(my::Vec4<real>(1, 1, 1), l_pos); //my::Vec4<real>(100, 100, -100));

	// set render context material
	rc->setAmbient(my::Color::WHITE);
	rc->setDiffuse(my::Color::WHITE);

	// draw default grid, with use to test distance of the scene
	m_game->m_grid->drawZBufferRW(rc);

	// general information output
	std::basic_string<charT> strTmp;
	HDC hdc = m_game->m_sback->getDC();

	int textx = rc->getClipperRect().left + 10;
	int texty = rc->getClipperRect().top + 10;

	strTmp = str_printf(_T("fps: %.1f"), m_game->m_fpsMgr->getFPS());
	::TextOut(hdc, textx, texty, strTmp.c_str(), (int)strTmp.length());

	strTmp = str_printf(_T("fps: %.1f"), 1 / elapsedTime);
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	t3d::Vec4<real> camPos = t3d::CameraContext::calculateCameraPosition(rc->getCameraMatrix());
	strTmp = str_printf(_T("cam.pos: %f, %f, %f"),
		camPos.x, camPos.y, camPos.z);
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	strTmp = str_printf(_T("cam.rot: %f, %f, %f"),
		RAD_TO_DEG(eularCam->getRotation().x), RAD_TO_DEG(eularCam->getRotation().y), RAD_TO_DEG(eularCam->getRotation().z));
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	m_game->m_sback->releaseDC(hdc);

	return true;
}
