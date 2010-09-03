
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
	addState(MyLoadState::s_name, MyLoadStatePtr(new MyLoadState()));

	// create and add game state
	addState(MyGameState::s_name, MyGameStatePtr(new MyGameState()));

	// set current state to load state
	setCurrentState(MyLoadState::s_name);

	// call default parent onInit
	return my::Game::onInit(cfg);
}

bool MyGame::onFrame(void)
{
	// get current state and do frame
	if(!getCurrentState<MyFrameState>()->doFrame())
	{
		return false;
	}

	// call default parent onFrame
	return my::Game::onFrame();
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

	// //////////////////////////////////////////////////////////////////////////////////////////

	// gain the game state obj
	MyGameStatePtr gameState = MyGame::getSingleton().getState<MyGameState>(MyGameState::s_name);

	// initial load jobs
	pushJob(MyJobPtr(new SimpleCreateObjJob<my::FPSManager>(gameState->m_fpsMgr, 0)));

	pushJob(MyJobPtr(new SimpleCreateObjJob<my::Timer>(gameState->m_timer, 0)));

	pushJob(MyJobPtr(new SimpleCreateObjJob<my::Grid>(gameState->m_grid, 0)));

	pushJob(MyJobPtr(new SimpleCreateObjJob<my::EulerCamera>(gameState->m_eulerCam, 1)));

	//pushJob(MyJobPtr(new LoadBoneAssignmentIndexObjectJob(gameState->m_obj, _T("gun.mesh.xml"))));

	//pushJob(MyJobPtr(new LoadObjectJob(gameState->m_lstObj, _T("gun_tri_list.mesh.xml"))));

	//pushJob(MyJobPtr(new LoadImageJob(gameState->m_objImg, _T("92fs_brigadier.jpg"))));

	//pushJob(MyJobPtr(new LoadWavJob(gameState->m_wav, _T("stationthrob.wav"), MyGame::getSingleton().m_dsound.get())));

	//pushJob(MyJobPtr(new LoadMp3Job(gameState->m_mp3, _T("castle1_20.mp3"), MyGame::getSingleton().m_dsound)));

	//// load & play mp3 while loading
	//m_mp3 = my::Mp3Ptr(new my::Mp3(
	//	MyGame::getSingleton().m_dsound, my::IOStreamPtr(new my::FileStream(my::ResourceMgr::getSingleton().findFileOrException(_T("castle1_05.mp3"))))));

	//m_mp3->play();

	// //////////////////////////////////////////////////////////////////////////////////////////

	// begin work thread here
	CreateThread();
	ResumeThread();
}

void MyLoadState::leaveState(void)
{
	_ASSERT(WaitForThreadStopped(0));

	// //////////////////////////////////////////////////////////////////////////////////////////

	//m_mp3->stop();

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
		// calculate total weight
		real totalWeight = 0;
		MyJobList::const_iterator job_iter = getJobListBegin();
		for(; job_iter != getJobListEnd(); job_iter++)
		{
			totalWeight += (*job_iter)->getWeight();
		}

		// do all the jobs
		real currentWeight = 0;
		job_iter = getJobListBegin();
		for(; job_iter != getJobListEnd(); job_iter++)
		{
			// check exit flag
			if(getExitFlag())
			{
				return false;
			}

			// do job
			if(!(*job_iter)->doJob())
			{
				setExitFlag();
				return false;
			}

			// update progress bar
			currentWeight += (*job_iter)->getWeight();
			{
				my::CriticalSectionLock lock(m_progressBoxLock);
				m_progressBox->setPercent(currentWeight / totalWeight);
			}
			::Sleep(33);
		}
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
	: my::World(256)
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

	// //////////////////////////////////////////////////////////////////////////////////////////

	//// create ds3d buffer & ds3d listener
	//m_ds3dbuffer = m_wav->m_dsbuffer->getDS3DBuffer();

	//m_ds3dListener = MyGame::getSingleton().m_dsound->getPrimarySoundBuffer()->getDS3DListener();

	//// play the wave
	//m_wav->m_dsbuffer->play(0, DSBPLAY_LOOPING);

	//// play the mp3
	//m_mp3->play(true);

	m_plane = my::IndexPlaneObjectPtr(new my::IndexPlaneObject(200, 200));

	//m_obj = my::IndexObjectPtr(new my::IndexPlaneObject(20, 20));

	m_obj = my::IndexObjectPtr(new my::IndexCubeObject(20, 20, 20));

	//m_obj = my::IndexObjectPtr(new my::IndexSphereObject(10, 20, 20));

	t3d::buildConnectionEdgeListFromTriangleIndexList(
		m_connectionEdgeList,
		m_obj->getVertexList(),
		m_obj->getVertexIndexList());

	m_stencilbuff = t3d::StencilBufferPtr(new t3d::StencilBuffer(
		MyGame::getSingleton().m_rc->getSurfaceWidth(), MyGame::getSingleton().m_rc->getSurfaceHeight()));

	// //////////////////////////////////////////////////////////////////////////////////////////
}

void MyGameState::leaveState(void)
{
	// //////////////////////////////////////////////////////////////////////////////////////////

	//// stop the wave
	//m_wav->m_dsbuffer->stop();

	//// stop the mp3
	//m_mp3->stop();

	// //////////////////////////////////////////////////////////////////////////////////////////
}

unsigned MyGameState::generateContacts(my::Contact * contacts, unsigned limits)
{
	return 0;
}

bool MyGameState::doFrame(void)
{
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

	//// here i created the clipper region smaller than the window, only used to test the clipper bug
	//// because of the software simulating, the algorithm of cutting polygon is implemented by software,
	//// so the unstrong algorithm will lead edge overflow, and even crash the application
	//// reducing the clipper region will somehow avoid this phenomenon
	//CRect clipper(m_rback);
	//clipper.DeflateRect(10, 10);
	//m_rc->setClipperRect(clipper);

	// clear back surface with gray color
	t3d::RenderContext * rc = MyGame::getSingleton().m_rc.get();
	rc->fillSurface(rc->getClipperRect(), my::Color(0.8f, 0.8f, 0.8f));

	// clear zbuffer with infinite distance
	rc->fillZbuffer(rc->getClipperRect(), 0);

	// set render context camera
	rc->setViewport(rc->getClipperRect());
	rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), rc->getClipperRect().Width(), rc->getClipperRect().Height()));
	rc->setCameraNearZ(1);
	rc->setCameraFarZ(10000);

	// update euler cameras position and orientation by user input
	m_eulerCam->update(keyboard, MyGame::getSingleton().m_mouse.get(), elapsedTime);
	rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEuler(m_eulerCam->getPosition(), m_eulerCam->getRotation()));

	// set render context lights
	my::Vec4<real> l_pos(-30, 30, -30);
	//l_pos *= t3d::mat3RotZXY(m_eulerCam->getRotation()) * t3d::mat3Mov(m_eulerCam->getPosition());
	rc->clearLightList();
	rc->pushLightAmbient(my::Vec4<real>(0.2f, 0.2f, 0.2f));
	rc->pushLightPoint(my::Vec4<real>(1, 1, 1), l_pos); //my::Vec4<real>(100, 100, -100));

	// set render context material
	rc->setAmbient(my::Color::WHITE);
	rc->setDiffuse(my::Color::WHITE);

	//// draw default grid, with use to test distance of the scene
	//m_grid->drawZBufferRW(rc);

	// //////////////////////////////////////////////////////////////////////////////////////////

	//DS3DBUFFER ds3db = {sizeof(ds3db)};
	//m_ds3dbuffer->getAllParameters(&ds3db);
	//ds3db.vPosition.x = 0;
	//ds3db.vPosition.y = 0;
	//ds3db.vPosition.z = 0;
	//ds3db.vVelocity.x = 0;
	//ds3db.vVelocity.y = 0;
	//ds3db.vVelocity.z = 0;
	//ds3db.flMinDistance = 5;
	//ds3db.flMaxDistance = 50;
	//ds3db.dwMode = DS3DMODE_NORMAL;
	//m_ds3dbuffer->setAllParameters(&ds3db);

	//DS3DLISTENER ds3dl = {sizeof(ds3dl)};
	//m_ds3dListener->getAllParameters(&ds3dl);
	//ds3dl.vPosition.x = m_eulerCam->getPosition().x;
	//ds3dl.vPosition.y = m_eulerCam->getPosition().y;
	//ds3dl.vPosition.z = m_eulerCam->getPosition().z;
	//my::Mat4<real> camMatRot = t3d::mat4GetRotationScalePart(rc->getCameraMatrix().inverse());
	//my::Vec4<real> vfront = my::Vec4<real>::UNIT_Z.transform(camMatRot);
	//ds3dl.vOrientFront.x = vfront.x;
	//ds3dl.vOrientFront.y = vfront.y;
	//ds3dl.vOrientFront.z = vfront.z;
	//my::Vec4<real> vtop = my::Vec4<real>::UNIT_Y.transform(camMatRot);
	//ds3dl.vOrientTop.x = vtop.x;
	//ds3dl.vOrientTop.y = vtop.y;
	//ds3dl.vOrientTop.z = vtop.z;
	//ds3dl.flDistanceFactor = 1.0f;
	//ds3dl.flRolloffFactor = 0.05f;
	//ds3dl.flDopplerFactor = 0;
	//m_ds3dListener->setAllParameters(&ds3dl, DS3D_IMMEDIATE);

	//real idxZ = -50, lstZ = -50;

	//rc->setTextureBuffer(m_objImg->getBits(), m_objImg->getPitch(), m_objImg->getWidth(), m_objImg->getHeight());

	//m_obj->drawWireZBufferRW(rc, my::Color::BLUE, t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)));

	//m_lstObj->drawWireZBufferRW(rc, my::Color::BLUE, t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)));

	//m_obj->drawZBufferRW(rc, my::Color::BLUE, t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)));

	//m_lstObj->drawZBufferRW(rc, my::Color::BLUE, t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)));

	//m_obj->drawGouraudZBufferRW(rc, t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)), my::Mat4<real>::IDENTITY);

	//m_lstObj->drawGouraudZBufferRW(rc, t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)), my::Mat4<real>::IDENTITY);

	//m_obj->drawTextureZBufferW(rc, t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)));

	//m_lstObj->drawTextureZBufferW(rc, t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)));

	//m_obj->drawTexturePerspectiveLPZBufferW(rc, t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)));

	//m_lstObj->drawTexturePerspectiveLPZBufferW(rc, t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)));

	//m_obj->drawTextureZBufferRW(rc, t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)));

	//m_lstObj->drawTextureZBufferRW(rc, t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)));

	//m_obj->drawTexturePerspectiveLPZBufferRW(rc, t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)));

	//m_lstObj->drawTexturePerspectiveLPZBufferRW(rc, t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)));

	//m_obj->drawGouraudTextureZBufferRW(rc, t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)), my::Mat4<real>::IDENTITY);

	//m_lstObj->drawGouraudTextureZBufferRW(rc, t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)), my::Mat4<real>::IDENTITY);

	//m_obj->drawGouraudTexturePerspectiveLPZBufferRW(rc, t3d::mat3Mov(my::Vec4<real>(10, 0, idxZ += 10)), my::Mat4<real>::IDENTITY);

	//m_lstObj->drawGouraudTexturePerspectiveLPZBufferRW(rc, t3d::mat3Mov(my::Vec4<real>(-10, 0, lstZ += 10)), my::Mat4<real>::IDENTITY);

	m_plane->drawGouraudZBufferRW(rc, t3d::mat3Mov(my::Vec4<real>(0, -20, 0)), my::Mat4<real>::IDENTITY);

	rc->setDiffuse(my::Color(0.5f, 1.0f, 0.5f));

	m_obj->drawGouraudZBufferRW(rc);

	m_obj->drawWireZBufferRW(rc, my::Color::YELLOW);

	t3d::buildIndicatorListFromTriangleIndexListByPoint(
		m_indicatorList,
		m_obj->getVertexList(),
		m_obj->getVertexIndexList(),
		l_pos);

	m_silhouetteEdgeList.clear();
	t3d::pushSilhouetteEdgeList(
		m_silhouetteEdgeList,
		m_connectionEdgeList,
		m_obj->getVertexList(),
		m_indicatorList);

	//// draw silhouette edge
	//rc->clearVertexList();
	//rc->pushVertexList(m_silhouetteEdgeList.begin(), m_silhouetteEdgeList.end());
	//rc->drawLineListZBufferRW(my::Color::RED);

	m_objShadowVolume.clear();
	t3d::buildShadowVolumeByPoint(
		m_objShadowVolume,
		m_silhouetteEdgeList,
		l_pos,
		100);

	// draw Shadow Volume Frame
	rc->clearVertexList();
	rc->pushVertexList(m_objShadowVolume.begin(), m_objShadowVolume.end());
	rc->drawTriangleListWireZBufferRW(my::Color::RED);
	//rc->drawTriangleListZBufferRW(my::Color::RED);

	// build stencil buffer reference
	t3d::SurfaceRef<int> stencilBuffRef(m_stencilbuff->getBuffer(), m_stencilbuff->getPitch());
	t3d::fillStencilBuffer(stencilBuffRef, rc->getClipperRect(), 0);

	// Shadow Volume Piple Line
	m_tmpVertexList.clear();
	t3d::transformVertexList(m_tmpVertexList, m_objShadowVolume, my::Mat4<real>::IDENTITY);
	t3d::resetClipStateList(rc->getClipStateList(), m_tmpVertexList.size() / 3);
	t3d::removeTriangleListBackfaceAtWorld(m_tmpVertexList, rc->getClipStateList(), rc->getCameraPosition());
	t3d::transformTriangleList(rc->getVertexList(), m_tmpVertexList, rc->getClipStateList(), rc->getCameraMatrix());
	t3d::clipTriangleListAtCamera(rc->getVertexList(), rc->getClipStateList(), rc->getCamera());
	t3d::cameraToScreenTriangleList(rc->getVertexList(), rc->getClipStateList(), rc->getCameraProjection(), rc->getViewport());
	t3d::clipTriangleListAtScreen(rc->getVertexList(), rc->getClipStateList(), rc->getViewport());

	// Count Shadow Volume
	for(size_t i = 0; i < rc->getClipStateListSize(); i++)
	{
		switch(rc->clipStateAt(i))
		{
		case t3d::CLIP_STATE_NONE:
			t3d::countTriangleIncrementInFrontOfDepth(
				stencilBuffRef,
				rc->getZBufferRef28(),
				rc->vertexAt(i * 3 + 0),
				rc->vertexAt(i * 3 + 1),
				rc->vertexAt(i * 3 + 2));
			break;

		case t3d::CLIP_STATE_SCLIPPED:
			t3d::countClippedTriangleIncrementInFrontOfDepth(
				stencilBuffRef,
				rc->getClipperRect(),
				rc->getZBufferRef28(),
				rc->vertexAt(i * 3 + 0),
				rc->vertexAt(i * 3 + 1),
				rc->vertexAt(i * 3 + 2));
			break;
		}
	}

	// 2nd Shadow Volume Piple Line
	t3d::resetClipStateList(rc->getClipStateList(), m_tmpVertexList.size() / 3);
	t3d::removeTriangleListFrontfaceAtWorld(m_tmpVertexList, rc->getClipStateList(), rc->getCameraPosition());
	t3d::transformTriangleList(rc->getVertexList(), m_tmpVertexList, rc->getClipStateList(), rc->getCameraMatrix());
	t3d::clipTriangleListAtCamera(rc->getVertexList(), rc->getClipStateList(), rc->getCamera());
	t3d::cameraToScreenTriangleList(rc->getVertexList(), rc->getClipStateList(), rc->getCameraProjection(), rc->getViewport());
	t3d::clipTriangleListAtScreen(rc->getVertexList(), rc->getClipStateList(), rc->getViewport());

	// Count Shadow Volume
	for(size_t i = 0; i < rc->getClipStateListSize(); i++)
	{
		switch(rc->clipStateAt(i))
		{
		case t3d::CLIP_STATE_NONE:
			t3d::countTriangleDecrementInFrontOfDepth(
				stencilBuffRef,
				rc->getZBufferRef28(),
				rc->vertexAt(i * 3 + 0),
				rc->vertexAt(i * 3 + 1),
				rc->vertexAt(i * 3 + 2));
			break;

		case t3d::CLIP_STATE_SCLIPPED:
			t3d::countClippedTriangleDecrementInFrontOfDepth(
				stencilBuffRef,
				rc->getClipperRect(),
				rc->getZBufferRef28(),
				rc->vertexAt(i * 3 + 0),
				rc->vertexAt(i * 3 + 1),
				rc->vertexAt(i * 3 + 2));
			break;
		}
	}

	// Render Shadow Volume
	t3d::boundSurfaceStencilBufferColor32(
		rc->getSurfaceRef32(),
		rc->getClipperRect(),
		stencilBuffRef,
		my::Color(97, 97, 97));

	// //////////////////////////////////////////////////////////////////////////////////////////

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

	return true;
}
