
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
		m_progressBox->setTitleText(_T("読み取っています ..."));
		m_progressBoxLock.leave();

		MyGameState * gameState = MyGame::getSingleton().getState<MyGameState>(MyGameState::s_name).get();
		_ASSERT(NULL != gameState);

		// HERE, INITIAL gameState objects that are time-consuming

		// load grass texture for game state
		gameState->m_grassTexture = my::ColorConversion::getSingleton().convertImage(
			my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("草地草坪014.jpg")))));

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
	// reset camera default position
	my::EulerCamera * eulerCam = MyGame::getSingleton().m_eulerCam.get();
	eulerCam->setDefaultPosition(my::Vec4<real>::ZERO);
	eulerCam->setDefaultRotation(my::Vec4<real>::ZERO);
	eulerCam->reset();

	// some physics const variables
	const real damping = 0.95f;
	const my::Vec4<real> gravity(0, -9.8f * 10, 0);
	const real sleepEpsilon = 10.4f; // ***

	// initial character rigid body
	const real sphereRadius = 5.0f;
	const real sphereMass = my::calculateSphereMass(sphereRadius, 1.0f);
	const my::Vec4<real> spherePos(0, 10.0f, 0);
	m_character.body = my::RigidBodyPtr(new my::RigidBody());
	m_character.body->setMass(sphereMass);
	m_character.body->setInertialTensor(my::calculateSphereInertiaTensor(sphereRadius, sphereMass));
	m_character.body->setDamping(damping);
	m_character.body->setAngularDamping(0);
	m_character.body->setPosition(spherePos);
	m_character.body->setAcceleration(gravity);
	m_character.body->setSleepEpsilon(sleepEpsilon);
	m_character.body->setAwake(true); // must be call after setSleepEpsilon
	m_character.body->calculateDerivedData(); // never forget this
	bodyList.push_back(m_character.body);

	// initial character collision sphere
	m_character.sphere.setRigidBody(m_character.body.get());
	m_character.sphere.setRadius(sphereRadius);
	m_character.move = my::Vec4<real>::ZERO;

	// initial camera hander particle
	m_hander.particle = my::ParticlePtr(new my::Particle());
	m_hander.particle->setMass(1);
	m_hander.particle->setPosition(t3d::vec3Add(m_character.body->getPosition(), my::Vec4<real>(0, 10, 0)));
	m_hander.particle->setVelocity(my::Vec4<real>::ZERO);
	m_hander.particle->setDamping(0.00001f); // ***
	m_hander.particle->setAcceleration(my::Vec4<real>::ZERO);
	particleList.push_back(m_hander.particle);

	// initial camera hander spring
	m_hander.spring = my::ParticleAnchoredSpringPtr(new my::ParticleAnchoredSpring(m_character.body->getPosition(), 100, 10)); // ***
	ParticleWorld::registry.add(m_hander.particle.get(), m_hander.spring.get());

	// initial camera hander cable
	m_hander.cable = my::ParticleCableConstraintPtr(new my::ParticleCableConstraint(m_character.body->getPosition(), m_hander.particle.get(), 13, 0.0f));
	particleContactGeneratorList.push_back(m_hander.cable);

	// initial global physics ground
	m_ground.setNormal(my::Vec4<real>::UNIT_Y);
	m_ground.setDistance(0);

	// create grid for game state
	m_grid = my::GridPtr(new my::Grid(100, 10));

	// verify grass texture have been created
	_ASSERT(NULL != m_grassTexture);
}

void MyGameState::leaveState(void)
{
}

void MyGameState::integrate(real duration)
{
	if(!t3d::vec3IsZero(m_character.move))
	{
		// set character velocity
		m_character.body->setVelocity(my::Vec4<real>(m_character.move.x, m_character.body->getVelocity().y, m_character.move.z));

		// work out character rotation velocity
		t3d::Vec4<real> vdir = my::Vec4<real>::UNIT_Z * m_character.body->getRotationTransform();
		t3d::Vec4<real> vcro = t3d::vec3Cross(vdir, m_character.move);
		real costheta = t3d::vec3CosTheta(vdir, t3d::vec3Normalize(m_character.move));
		if(!IS_ZERO_FLOAT(t3d::vec3LengthSquare(vcro)))
		{
			real angle = std::max(DEG_TO_RAD(-360 * duration), std::min(DEG_TO_RAD(360 * duration), acos(costheta)));
			t3d::Vec4<real> axis = t3d::vec3Normalize(vcro);
			m_character.body->setOrientation(m_character.body->getOrientation() * t3d::buildQuatFromAngleAxis(angle, axis));
		}
		else if(costheta < 0)
		{
			real angle = DEG_TO_RAD(10);
			t3d::Vec4<real> axis = my::Vec4<real>::UNIT_Y;
			m_character.body->setOrientation(m_character.body->getOrientation() * t3d::buildQuatFromAngleAxis(angle, axis));
		}
		m_character.body->setAwake(true);
	}

	// integrate rigid world
	my::World::integrate(duration);

	// update character collision sphere's transform information
	m_character.sphere.calculateInternals();
}

unsigned MyGameState::generateContacts(my::Contact * contacts, unsigned limits)
{
	unsigned used = 0;

	// collision detect between character and ground
	used += my::CollisionDetector::sphereAndHalfSpace(
		m_character.sphere,
		m_ground.getNormal(),
		m_ground.getDistance(),
		&contacts[used],
		limits - used);

	// update friction & restitution manually
	unsigned i = 0;
	for(; i < used; i++)
	{
		contacts[i].friction = 10.0f;
		contacts[i].restitution = 0;
	}

	return used;
}

void MyGameState::runPhysics(real duration)
{
	// rigid body physics
	World::startFrame();
	World::registry.updateForces(duration);
	integrate(duration);
	unsigned usedContacts = generateContacts(&contactList[0], World::maxContacts);
	World::resolver.setPositionIterations(usedContacts * 4);
	World::resolver.setVelocityIterations(usedContacts * 4);
	World::resolver.resolveContacts(&contactList[0], usedContacts, duration);

	// the position of character body have already changed, so synchronized camera hander particle
	m_hander.particle->setPosition(
		my::Vec4<real>(m_character.body->getPosition().x, m_hander.particle->getPosition().y, m_character.body->getPosition().z));

	// particle physics
	ParticleWorld::startFrame();
	ParticleWorld::registry.updateForces(duration);
	ParticleWorld::integrate(duration);
	unsigned used = ParticleWorld::generateContacts(&particleContactArray[0], ParticleWorld::maxContacts);
	ParticleWorld::resolver.setIterations(used * 2);
	ParticleWorld::resolver.resolveContacts(&particleContactArray[0], used, duration);
}

bool MyGameState::doFrame(real elapsedTime)
{
	// obtain global objects, such as render context pointer ..
	t3d::RenderContext * rc = MyGame::getSingleton().m_rc.get();
	my::EulerCamera * eulerCam = MyGame::getSingleton().m_eulerCam.get();
	t3d::DIKeyboard * keyboard = MyGame::getSingleton().m_keyboard.get();
	t3d::DIMouse * mouse = MyGame::getSingleton().m_mouse.get();

	// exit application by return false with user input 'escape'
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
	rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(72), rc->getClipperRect().Width(), rc->getClipperRect().Height()));
	rc->setCameraNearZ(5);
	rc->setCameraFarZ(10000);

	if(keyboard->isKeyDown(DIK_LCONTROL))
	{
		// update euler cameras position and orientation by user input
		eulerCam->update(keyboard, MyGame::getSingleton().m_mouse.get(), elapsedTime);
	}
	else
	{
		// update camera rotation according user mouse input
		eulerCam->addRotation(my::EulerCamera::buildRotOffset(mouse));

		// update character move according user keyboard input
		m_character.move = my::EulerCamera::buildMovOffset(
			keyboard, eulerCam->getRotation().y, keyboard->isKeyDown(DIK_LSHIFT) ? 90.0f : 30.0f);

		// 30 frames per rendering frame for physics engine
		const unsigned phyCount = 30;
		for(unsigned i = 0; i < phyCount; i++)
		{
			runPhysics(elapsedTime / phyCount);
		}

		// update camera matrix according to the camera hander followed with character
		t3d::Mat4<real> matRotation = mat3RotXYZ(eulerCam->getRotation());
		t3d::Mat4<real> matPosition = t3d::mat3Mov(my::Vec4<real>(0, 0, -30)) * matRotation * t3d::mat3Mov(m_hander.particle->getPosition());
		eulerCam->setPosition(my::Vec4<real>::ZERO * matPosition);
	}

	// set camera matrix (inversed matrix)
	rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEuler(eulerCam->getPosition(), eulerCam->getRotation()));

	// set render context lights
	my::Vec4<real> l_pos(-30, 30, -30);
	l_pos *= t3d::mat3RotZXY(eulerCam->getRotation()) * t3d::mat3Mov(eulerCam->getPosition());
	rc->clearLightList();
	rc->pushLightAmbient(my::Vec4<real>(0.2f, 0.2f, 0.2f));
	rc->pushLightPoint(my::Color::WHITE, l_pos);

	// render character sphere
	drawSphereWireZBufferRW(
		rc,
		m_character.sphere.getRadius(),
		m_character.body->getAwake() ? my::Color::RED : t3d::vec3Mul(my::Color::RED, 0.7f),
		m_character.body->getTransform());

	// render camera hander particle
	drawSphereWireZBufferRW(
		rc, 1, my::Color::YELLOW, t3d::mat3Mov(m_hander.particle->getPosition()));

	// render the direction of character body
	drawLinePointAndNormalZBufferRW(
		rc,
		m_character.body->getPosition(),
		my::Vec4<real>(0, 0, 10) * m_character.body->getRotationTransform(),
		my::Color::BLUE);

	//// draw default grid, with use to test distance of the scene
	//m_grid->drawZBufferRW(rc);

	// draw ground grass
	rc->setTextureBuffer(
		m_grassTexture->getBits(),
		m_grassTexture->getPitch(),
		m_grassTexture->getWidth(),
		m_grassTexture->getHeight());
	drawPlaneTexturePerspectiveLPZBufferRW(rc, 100, 100, my::Mat4<real>::IDENTITY);

	return true;
}
