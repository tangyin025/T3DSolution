
#include "StdAfx.h"
#include "MyGameBase.h"

MyWindow::MyWindow(HWND hwnd)
	: GameWnd(hwnd)
{
}

MyWindow::~MyWindow(void)
{
}

LRESULT MyWindow::onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch(message)
	{
	case WM_CLOSE:
		if(MyGameBase::getSingleton().getCurrentStateName() == MyLoadState::s_name)
		{
			// for load state, there must be waiting for another thread to prepare for quiting
			MyLoadStatePtr loadState = MyGameBase::getSingleton().getCurrentState<MyLoadState>();
			if(!loadState->getExitFlag())
			{
				loadState->setExitFlag();
			}
			return 0;
		}
		break;

	case WM_USER + 0:
		{
			// handle the exception thrown from the load state thread
			t3d::Exception * e = reinterpret_cast<t3d::Exception *>(wparam);
			_ASSERT(NULL != e);
			::MessageBox(getHandle(), e->getFullDesc().c_str(), _T("Exception"), MB_OK);
		}
		break;
	}
	return GameWnd::onProc(hwnd, message, wparam, lparam);
}

MyGameBase::MyGameBase(void)
{
}

MyGameBase::~MyGameBase(void)
{
}

my::Window * MyGameBase::newWindow(HWND hwnd)
{
	return new MyWindow(hwnd);
}

bool MyGameBase::onInit(const my::Config & cfg)
{
	// predefine config values
	const int cfgWidth = m_rc->getSurfaceWidth();
	const int cfgHeight = m_rc->getSurfaceHeight();

	// calculate aspect ratio
	real aspect_ratio;
	switch(cfg.getInt(_T("aspectratio")))
	{
	default:
		_ASSERT(ASPECT_RATIO_STRETCHED == cfg.getInt(_T("aspectratio")));
		aspect_ratio = (real)cfgWidth / cfgHeight;
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
	if(aspect_ratio < (real)cfgWidth / (real)cfgHeight)
	{
		lHeight = cfgHeight;
		lWidth = (LONG)(lHeight * aspect_ratio + .5f);
		clipper.left = (cfgWidth - lWidth) / 2;
		clipper.top = 0;
		clipper.right = clipper.left + lWidth;
		clipper.bottom = clipper.top + lHeight;
	}
	else
	{
		lWidth = cfgWidth;
		lHeight = (LONG)(lWidth / aspect_ratio + .5f);
		clipper.left = 0;
		clipper.top = (cfgHeight - lHeight) / 2;
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
	addState(MyLoadState::s_name, MyLoadStatePtr(new MyLoadState(this)));

	// create and add game state
	addState(MyGameState::s_name, MyGameStatePtr(new MyGameState(this)));

	// set current state to load state
	setCurrentState(MyLoadState::s_name);

	// call default parent onInit
	return my::Game::onInit(cfg);
}

bool MyGameBase::onFrame(void)
{
	// get current state and do frame
	if(!getCurrentState<MyFrameState>()->doFrame())
	{
		return false;
	}

	// call default parent onFrame
	return my::Game::onFrame();
}

void MyGameBase::onShutdown(void)
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

MyLoadState::MyLoadState(MyGameBase * game)
	: m_game(game)
	, m_exitFlag(false)
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
	CRect clipper = m_game->m_rc->getClipperRect();
	int x = clipper.left + (clipper.Width() - barWidth) / 2;
	int y = clipper.top + (clipper.Height() - barHeight) / 2;
	m_progressBox = MyUIProgressBarBoxPtr(new MyUIProgressBarBox(CRect(CPoint(x, y), CSize(barWidth, barHeight))));

	// begin work thread here
	CreateThread();
	ResumeThread();
}

void MyLoadState::leaveState(void)
{
	_ASSERT(WaitForThreadStopped(0));
}

bool MyLoadState::doFrame(void)
{
	// exit application by return false with user input 'escape'
	if(m_game->m_keyboard->isKeyDown(DIK_ESCAPE))
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
			m_game->setCurrentState(MyGameState::s_name);
			return true;
		}
	}

	// define render context point
	t3d::RenderContext * rc = m_game->m_rc.get();

	// clear back surface with gray color
	rc->fillSurface(rc->getClipperRect(), my::Color::BLACK);

	// draw progress bar
	m_progressBoxLock.enter();
	m_progressBox->draw(rc);
	m_progressBoxLock.leave();

	// general information output
	std::basic_string<charT> strTmp;
	if(!getExitFlag())
	{
		strTmp = _T("Loading ...");
	}
	else
	{
		strTmp = _T("Exiting ...");
	}
	HDC hdc = m_game->m_backSurface->getDC();
	int bkMode = ::SetBkMode(hdc, TRANSPARENT);
	COLORREF textColor = ::SetTextColor(hdc, RGB(255, 255, 255));
	::DrawText(hdc, strTmp.c_str(), strTmp.length(), &m_progressBox->m_titleRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	::SetTextColor(hdc, textColor);
	::SetBkMode(hdc, bkMode);
	m_game->m_backSurface->releaseDC(hdc);

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
		// gain the game state obj
		MyGameStatePtr gameState = m_game->getState<MyGameState>(MyGameState::s_name);

		// create fps manager
		gameState->m_fpsMgr = my::FPSManagerPtr(new my::FPSManager());

		// create timer
		gameState->m_timer = my::TimerPtr(new my::Timer());

		// create grid
		gameState->m_grid = my::GridPtr(new my::Grid());

		// create euler camera
		gameState->m_eulerCam = my::EulerCameraPtr(new my::EulerCamera());

		// //////////////////////////////////////////////////////////////////////////////////////////

		// report the process
		const real processCount = 6;
		if(getExitFlag())
		{
			return false;
		}
		setPercent(1 / processCount);
		::Sleep(33);

		// load gun mesh
		my::IOStreamPtr stream = my::ResourceMgr::getSingleton().openIOStream(_T("gun.mesh.xml"));
		gameState->m_obj = my::IndexObjectPtr(new my::BoneAssignmentIndexObjectFromOgreMesh(stream.get()));
		if(getExitFlag())
		{
			return false;
		}
		setPercent(2 / processCount);
		::Sleep(33);

		// load gun triangle list mesh
		stream = my::ResourceMgr::getSingleton().openIOStream(_T("gun_tri_list.mesh.xml"));
		gameState->m_lstObj = my::ObjectPtr(new my::ObjectFromOgreMesh(stream.get()));
		if(getExitFlag())
		{
			return false;
		}
		setPercent(3 / processCount);
		::Sleep(33);

		// load gun texture
		my::ImagePtr tmpImg = my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("92fs_brigadier.jpg"))));
		gameState->m_objImg = my::ColorConversion::getSingleton().convertImage(tmpImg.get());
		if(getExitFlag())
		{
			return false;
		}
		setPercent(4 / processCount);
		::Sleep(33);

		// load wav file
		gameState->m_wav = my::WavPtr(new my::Wav(m_game->m_dsound.get(), my::ResourceMgr::getSingleton().findFileOrException(_T("stationthrob.wav"))));
		gameState->m_ds3dbuffer = gameState->m_wav->m_dsbuffer->getDS3DBuffer();
		gameState->m_ds3dListener = m_game->m_dsound->getPrimarySoundBuffer()->getDS3DListener();
		if(getExitFlag())
		{
			return false;
		}
		setPercent(5 / processCount);
		::Sleep(33);

		// load mp3 file
		gameState->m_mp3 = my::Mp3Ptr(new my::Mp3(m_game->m_dsound, my::ResourceMgr::getSingleton().openIOStream(_T("i am the wind.mp3"))));
		gameState->m_mp3->play();
		gameState->m_mp3->stop();
		setPercent(6 / processCount);
		::Sleep(33);

		// //////////////////////////////////////////////////////////////////////////////////////////
	}
	catch(t3d::Exception & e)
	{
		m_game->m_pwnd->sendMessage(WM_USER + 0, (WPARAM)&e);
		setExitFlag(true);
	}

	return 0;
}

const std::basic_string<charT> MyGameState::s_name(_T("MyGameState"));

MyGameState::MyGameState(MyGameBase * game)
	: m_game(game)
{
}

MyGameState::~MyGameState(void)
{
}

void MyGameState::enterState(void)
{
	// start fps manager
	m_fpsMgr->start();

	// start timer
	m_timer->start();

	// reset eular camera !!!
	m_eulerCam->setDefaultPosition(my::Vec4<real>(50, 50, -50));
	m_eulerCam->setDefaultRotation(my::Vec4<real>(DEG_TO_RAD(45), DEG_TO_RAD(-45), DEG_TO_RAD(0)));
	m_eulerCam->reset();

	// play the wave
	m_wav->m_dsbuffer->play(0, DSBPLAY_LOOPING);
}

void MyGameState::leaveState(void)
{
	// stop the wave
	m_wav->m_dsbuffer->stop();
}

bool MyGameState::doFrame(void)
{
	// exit application by return false with user input 'escape'
	if(m_game->m_keyboard->isKeyDown(DIK_ESCAPE))
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
	m_game->m_rc->fillSurface(m_game->m_rc->getClipperRect(), my::Color(0.8f, 0.8f, 0.8f));

	// clear zbuffer with infinite distance
	m_game->m_rc->fillZbuffer(m_game->m_rc->getClipperRect(), 0);

	// set render context camera
	m_game->m_rc->setViewport(m_game->m_rc->getClipperRect());
	m_game->m_rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), m_game->m_rc->getClipperRect().Width(), m_game->m_rc->getClipperRect().Height()));
	m_game->m_rc->setCameraNearZ(1);
	m_game->m_rc->setCameraFarZ(10000);

	// update euler cameras position and orientation by user input
	m_eulerCam->update(m_game->m_keyboard.get(), m_game->m_mouse.get(), elapsedTime);
	m_game->m_rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEuler(m_eulerCam->getPosition(), m_eulerCam->getRotation()));

	// set render context lights
	my::Vec4<real> l_pos(-30, 30, -30);
	l_pos *= t3d::mat3RotZXY(m_eulerCam->getRotation()) * t3d::mat3Mov(m_eulerCam->getPosition());
	m_game->m_rc->clearLightList();
	m_game->m_rc->pushLightAmbient(my::Vec4<real>(0.2f, 0.2f, 0.2f));
	m_game->m_rc->pushLightPoint(my::Vec4<real>(1, 1, 1), l_pos); //my::Vec4<real>(100, 100, -100));

	// set render context material
	m_game->m_rc->setAmbient(my::Color::WHITE);
	m_game->m_rc->setDiffuse(my::Color::WHITE);

	// draw default grid, with use to test distance of the scene
	m_grid->drawZBufferRW(m_game->m_rc.get());

	// //////////////////////////////////////////////////////////////////////////////////////////

	DS3DBUFFER ds3db = {sizeof(ds3db)};
	m_ds3dbuffer->getAllParameters(&ds3db);
	ds3db.vPosition.x = 0;
	ds3db.vPosition.y = 0;
	ds3db.vPosition.z = 0;
	ds3db.vVelocity.x = 0;
	ds3db.vVelocity.y = 0;
	ds3db.vVelocity.z = 0;
	ds3db.flMinDistance = 5;
	ds3db.flMaxDistance = 50;
	ds3db.dwMode = DS3DMODE_NORMAL;
	m_ds3dbuffer->setAllParameters(&ds3db);

	DS3DLISTENER ds3dl = {sizeof(ds3dl)};
	m_ds3dListener->getAllParameters(&ds3dl);
	ds3dl.vPosition.x = m_eulerCam->getPosition().x;
	ds3dl.vPosition.y = m_eulerCam->getPosition().y;
	ds3dl.vPosition.z = m_eulerCam->getPosition().z;
	my::Mat4<real> camMatRot = t3d::mat4GetRotationScalePart(m_game->m_rc->getCameraMatrix().inverse());
	my::Vec4<real> vfront = my::Vec4<real>::UNIT_Z.transform(camMatRot);
	ds3dl.vOrientFront.x = vfront.x;
	ds3dl.vOrientFront.y = vfront.y;
	ds3dl.vOrientFront.z = vfront.z;
	my::Vec4<real> vtop = my::Vec4<real>::UNIT_Y.transform(camMatRot);
	ds3dl.vOrientTop.x = vtop.x;
	ds3dl.vOrientTop.y = vtop.y;
	ds3dl.vOrientTop.z = vtop.z;
	ds3dl.flDistanceFactor = 1.0f;
	ds3dl.flRolloffFactor = 0.05f;
	ds3dl.flDopplerFactor = 0;
	m_ds3dListener->setAllParameters(&ds3dl, DS3D_IMMEDIATE);

	real idxZ = -50, lstZ = -50;

	m_game->m_rc->setTextureBuffer(m_objImg->getBits(), m_objImg->getPitch(), m_objImg->getWidth(), m_objImg->getHeight());

	m_obj->drawWireZBufferRW(m_game->m_rc.get(), my::Color::BLUE, t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)));

	m_lstObj->drawWireZBufferRW(m_game->m_rc.get(), my::Color::BLUE, t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)));

	m_obj->drawZBufferRW(m_game->m_rc.get(), my::Color::BLUE, t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)));

	m_lstObj->drawZBufferRW(m_game->m_rc.get(), my::Color::BLUE, t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)));

	m_obj->drawGouraudZBufferRW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)), my::Mat4<real>::IDENTITY);

	m_lstObj->drawGouraudZBufferRW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)), my::Mat4<real>::IDENTITY);

	m_obj->drawTextureZBufferW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)));

	m_lstObj->drawTextureZBufferW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)));

	m_obj->drawTexturePerspectiveLPZBufferW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)));

	m_lstObj->drawTexturePerspectiveLPZBufferW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)));

	m_obj->drawTextureZBufferRW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)));

	m_lstObj->drawTextureZBufferRW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)));

	m_obj->drawTexturePerspectiveLPZBufferRW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)));

	m_lstObj->drawTexturePerspectiveLPZBufferRW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)));

	m_obj->drawGouraudTextureZBufferRW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)), my::Mat4<real>::IDENTITY);

	m_lstObj->drawGouraudTextureZBufferRW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)), my::Mat4<real>::IDENTITY);

	m_obj->drawGouraudTexturePerspectiveLPZBufferRW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)), my::Mat4<real>::IDENTITY);

	m_lstObj->drawGouraudTexturePerspectiveLPZBufferRW(m_game->m_rc.get(), t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)), my::Mat4<real>::IDENTITY);

	// //////////////////////////////////////////////////////////////////////////////////////////

	// general information output
	std::basic_string<charT> strTmp;
	HDC hdc = m_game->m_backSurface->getDC();

	int textx = m_game->m_rc->getClipperRect().left + 10;
	int texty = m_game->m_rc->getClipperRect().top + 10;

	strTmp = str_printf(_T("fps: %.1f"), m_fpsMgr->getFPS());
	::TextOut(hdc, textx, texty, strTmp.c_str(), (int)strTmp.length());

	strTmp = str_printf(_T("fps: %.1f"), 1 / elapsedTime);
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	t3d::Vec4<real> camPos = t3d::CameraContext::calculateCameraPosition(m_game->m_rc->getCameraMatrix());
	strTmp = str_printf(_T("cam.pos: %f, %f, %f"),
		camPos.x, camPos.y, camPos.z);
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	strTmp = str_printf(_T("cam.rot: %f, %f, %f"),
		RAD_TO_DEG(m_eulerCam->getRotation().x), RAD_TO_DEG(m_eulerCam->getRotation().y), RAD_TO_DEG(m_eulerCam->getRotation().z));
	::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

	m_game->m_backSurface->releaseDC(hdc);

	return true;
}
