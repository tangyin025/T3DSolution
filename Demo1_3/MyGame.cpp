
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
	// initialize fps manager
	m_fpsMgr = my::FPSManagerPtr(new my::FPSManager());
	m_fpsMgr->start();

	// initialize timer
	m_timer = my::TimerPtr(new my::Timer());
	m_timer->start();

	// initialize grid
	m_grid = my::GridPtr(new my::Grid());

	// initialize euler camera
	m_eulerCam = my::EulerCameraPtr(new my::EulerCamera());
	m_eulerCam->setDefaultPosition(my::Vec4<real>(-50, 50, -50));
	m_eulerCam->setDefaultRotation(my::Vec4<real>(DEG_TO_RAD(45), DEG_TO_RAD(45), DEG_TO_RAD(0)));
	m_eulerCam->reset();

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
	_ASSERT(clipper.left	>= m_rback.left);
	_ASSERT(clipper.top		>= m_rback.top);
	_ASSERT(clipper.right	<= m_rback.right);
	_ASSERT(clipper.bottom	<= m_rback.bottom);
	m_rc->setClipperRect(clipper);

	//// set default media files searching directory
	//m_resourceMgr->addDir(_T("."));

	return my::Game::onInit(cfg);
}

bool MyGame::onFrame(void)
{
	// exit application by return false with user input 'escape'
	if(m_keyboard->isKeyDown(DIK_ESCAPE))
	{
		return false;
	}

	// fps manager, witch calculated fps by incremented frame
	// the precision of this fps manager witch depend on sampling second was low, but its enough
	m_fpsMgr->addFrame();

	// the high precision timer, witch calculate time interval between last frame by cpu count
	// to avoid to too many time interval that crash the physical engine, set the max interval as 30 / 1 second
	const real elapsedTime = std::min((real)m_timer->getElapsedTime(), (real)0.033);

	//// here i created the clipper region smaller than the window, only used to test the clipper bug
	//// because of the software simulating, the algorithm of cutting polygon is implemented by software,
	//// so the unstrong algorithm will lead edge overflow, and even crash the application
	//// reducing the clipper region will somehow avoid this phenomenon
	//CRect clipper(m_rback);
	//clipper.DeflateRect(10, 10);
	//m_rc->setClipperRect(clipper);

	// clear back surface with gray color
	m_rc->fillSurface(m_rc->getClipperRect(), my::Color(0.8f, 0.8f, 0.8f));

	// clear zbuffer with infinite distance
	m_rc->fillZbuffer(m_rc->getClipperRect(), 0);

	// set render context camera
	m_rc->setViewport(m_rc->getClipperRect());
	m_rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), m_rc->getClipperRect().Width(), m_rc->getClipperRect().Height()));
	m_rc->setCameraNearZ(1);
	m_rc->setCameraFarZ(10000);

	// update euler cameras position and orientation by user input
	m_eulerCam->update(m_keyboard.get(), m_mouse.get(), elapsedTime);
	m_rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEuler(m_eulerCam->getPosition(), m_eulerCam->getRotation()));

	// set render context lights
	my::Vec4<real> l_pos(-30, 30, -30);
	l_pos *= t3d::mat3RotZXY(m_eulerCam->getRotation()) * t3d::mat3Mov(m_eulerCam->getPosition());
	m_rc->clearLightList();
	m_rc->pushLightAmbient(my::Vec4<real>(0.2f, 0.2f, 0.2f));
	m_rc->pushLightPoint(my::Vec4<real>(1, 1, 1), l_pos); //my::Vec4<real>(100, 100, -100));

	// set render context material
	m_rc->setAmbient(my::Color::WHITE);
	m_rc->setDiffuse(my::Color::WHITE);

	// draw default grid, with use to test distance of the scene
	m_grid->drawZBufferRW(m_rc.get());

	// general information output
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
		RAD_TO_DEG(m_eulerCam->getRotation().x), RAD_TO_DEG(m_eulerCam->getRotation().y), RAD_TO_DEG(m_eulerCam->getRotation().z));
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	m_sback->releaseDC(hdc);

	return my::Game::onFrame();
}

void MyGame::onShutdown(void)
{
}
