
#include "StdAfx.h"
#include "MyGameEx.h"

LRESULT MyWindow::OnClose(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	// for game state, exit application directly
	if(MyGame::getSingleton().getCurrentStateName() == MyGameState::s_name)
	{
		bHandled = FALSE;
		return 0;
	}

	// else there must be waiting for another thread to prepare for quiting
	_ASSERT(MyGame::getSingleton().getCurrentStateName() == MyLoadState::s_name);
	MyLoadStatePtr loadState = MyGame::getSingleton().getCurrentState<MyLoadState>();
	if(!loadState->getExitFlagSync())
	{
		loadState->setExitFlagSync();
	}

	_ASSERT(TRUE == bHandled);
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

#define EXIT_OR_UPDATE_PROGRESS(percent) \
	if(getExitFlagSync()) \
	{ \
		return 0; \
	} \
	updateProgressSync(percent);

DWORD MyLoadState::onProc(void)
{
	// NOTE: because of multi-thread frame, the try block in the main thread
	// could not catch any exceptions which was thrown from the this thread proc
	try
	{
		updateTitleSync(_T("Loading ..."));

		MyGameState * gameState = MyGame::getSingleton().getState<MyGameState>(MyGameState::s_name).get();
		_ASSERT(NULL != gameState);

		// HERE, INITIAL gameState objects that are time-consuming
		const int total_step = 14;
		int current_step = 1;

		// exit or update progress percent
		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		// load scene
		gameState->m_scene = my::ObjectFromOgreMeshPtr(new my::ObjectFromOgreMesh(
			my::IOStreamPtr(new my::FileStream(my::ResourceMgr::getSingleton().findFileOrException(_T("office_tri_list.mesh.xml"))))));

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		// load scene texture
		my::ImagePtr scene_tex = my::ColorConversion::getSingleton().convertImage(
			my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("office_texture.jpg")))));

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		// build bsp scene
		gameState->m_scene_bsp = my::buildFrontToBackBspSceneGouraudTexturePerspectiveLPZBufferRW(
			gameState->m_scene->getVertexList(),
			gameState->m_scene->getNormalList(),
			gameState->m_scene->getUVList(),
			my::MaterialPtr(new my::Material(my::Color::WHITE, my::Color::WHITE)),
			scene_tex);

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		// load jack bone assignment model
		my::BoneAssignmentIndexObjectFromOgreMeshPtr bone_assignment_obj;
		bone_assignment_obj = my::BoneAssignmentIndexObjectFromOgreMeshPtr(new my::BoneAssignmentIndexObjectFromOgreMesh(
			my::IOStreamPtr(new my::FileStream(my::ResourceMgr::getSingleton().findFileOrException(_T("jack_hres.mesh.xml"))))));
		gameState->m_jack_bone_assignments.push_back(bone_assignment_obj);

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		// load jack texture
		my::ImagePtr jack_tex = my::ColorConversion::getSingleton().convertImage(
			my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("jack_texture.jpg")))));

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		// copy original mesh from jack bone assignment to custom shader obj
		my::CustomShaderIndexObjectPtr custom_shader_obj;
		custom_shader_obj = my::CustomShaderIndexObjectPtr(new my::CustomShaderIndexObjectGouraudTextureZBufferRW(
			my::MaterialPtr(new my::Material(my::Color::WHITE, my::Color::WHITE)), jack_tex));
		custom_shader_obj->getVertexList() = bone_assignment_obj->getOriginalVertexList();
		custom_shader_obj->getVertexIndexList() = bone_assignment_obj->getVertexIndexList();
		custom_shader_obj->getNormalList() = bone_assignment_obj->getOriginalNormalList();
		custom_shader_obj->getUVList() = bone_assignment_obj->getUVList();
		gameState->m_jack_meshs.push_back(custom_shader_obj);

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		// build connection edge
		gameState->m_jack_connection_edges.push_back(t3d::ConnectionEdgeList());
		MyGameState::ConnectionEdgeListList::reverse_iterator connect_edge_iter;
		connect_edge_iter = gameState->m_jack_connection_edges.rbegin();
		t3d::buildConnectionEdgeListFromTriangleIndexList(
			*connect_edge_iter,
			custom_shader_obj->getVertexList(),
			custom_shader_obj->getVertexIndexList());

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		// load jack hair as the same
		bone_assignment_obj = my::BoneAssignmentIndexObjectFromOgreMeshPtr(new my::BoneAssignmentIndexObjectFromOgreMesh(
			my::IOStreamPtr(new my::FileStream(my::ResourceMgr::getSingleton().findFileOrException(_T("jack_hres_hair.mesh.xml"))))));
		gameState->m_jack_bone_assignments.push_back(bone_assignment_obj);

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		custom_shader_obj = my::CustomShaderIndexObjectPtr(new my::CustomShaderIndexObjectGouraudTextureZBufferRWWithBackface(
			my::MaterialPtr(new my::Material(my::Color::WHITE, my::Color::WHITE)), jack_tex));
		custom_shader_obj->getVertexList() = bone_assignment_obj->getOriginalVertexList();
		custom_shader_obj->getVertexIndexList() = bone_assignment_obj->getVertexIndexList();
		custom_shader_obj->getNormalList() = bone_assignment_obj->getOriginalNormalList();
		custom_shader_obj->getUVList() = bone_assignment_obj->getUVList();
		gameState->m_jack_meshs.push_back(custom_shader_obj);

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		gameState->m_jack_connection_edges.push_back(t3d::ConnectionEdgeList());
		connect_edge_iter = gameState->m_jack_connection_edges.rbegin();
		t3d::buildConnectionEdgeListFromTriangleIndexList(
			*connect_edge_iter,
			custom_shader_obj->getVertexList(),
			custom_shader_obj->getVertexIndexList());

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		// load jack skeleton animation
		my::SkeletonAnimationsFromOgreSkeletonPtr skeleton_anim(new my::SkeletonAnimationsFromOgreSkeleton(
			my::IOStreamPtr(new my::FileStream(my::ResourceMgr::getSingleton().findFileOrException(_T("jack_anim_stand.skeleton.xml"))))));
		skeleton_anim->getSkeletonAnimationNode("clip1").setNextAnimationName("clip2");
		skeleton_anim->getSkeletonAnimationNode("clip2").setNextAnimationName("clip1");
		skeleton_anim->getSkeletonAnimationNode("clip3").setNextAnimationName("clip4");
		skeleton_anim->getSkeletonAnimationNode("clip4").setNextAnimationName("clip3");
		skeleton_anim->setCurrentAnimationName("clip1");
		skeleton_anim->setCurrentAnimationTime(0);
		gameState->m_jack_skel = skeleton_anim;

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		// load sky sphere
		gameState->m_sky_sphere = my::IndexSphereObjectPtr(new my::IndexSphereObject(50000.0f, 20, 20, true));
		gameState->m_sky_sphere_tex = my::ColorConversion::getSingleton().convertImage(
			my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("1316532925.jpg")))));

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		// load & play mp3
		std::basic_string<t3d::charT> mp3_path = my::ResourceMgr::getSingleton().findFile(_T("castle1_34.mp3"));
		if(!mp3_path.empty())
		{
			gameState->m_music = my::Mp3Ptr(new my::Mp3(MyGame::getSingleton().m_dsound, my::IOStreamPtr(new my::FileStream(mp3_path))));
			gameState->m_music->play(true);
		}

		EXIT_OR_UPDATE_PROGRESS((real)current_step++ / total_step);

		// sleep a moment
		Sleep(300);
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
	m_hander.particle->setPosition(t3d::vec3Add(m_character.body->getPosition(), my::Vec4<real>(0, 20, 0)));
	m_hander.particle->setVelocity(my::Vec4<real>::ZERO);
	m_hander.particle->setDamping(0.00001f); // ***
	m_hander.particle->setAcceleration(my::Vec4<real>::ZERO);
	particleList.push_back(m_hander.particle);

	// initial camera hander spring
	m_hander.spring = my::ParticleAnchoredSpringPtr(new my::ParticleAnchoredSpring(m_character.body->getPosition(), 200, 20)); // ***
	ParticleWorld::registry.add(m_hander.particle.get(), m_hander.spring.get());

	// initial camera hander cable
	m_hander.cable = my::ParticleCableConstraintPtr(new my::ParticleCableConstraint(m_character.body->getPosition(), m_hander.particle.get(), 23, 0.0f));
	particleContactGeneratorList.push_back(m_hander.cable);

	// initial global physics ground
	m_ground.setNormal(my::Vec4<real>::UNIT_Y);
	m_ground.setDistance(-50);

	// check time-consuming resources are created
	_ASSERT(NULL != m_scene_bsp);
	_ASSERT(2 == m_jack_bone_assignments.size());
	_ASSERT(m_jack_bone_assignments.size() == m_jack_meshs.size());
	_ASSERT(m_jack_bone_assignments.size() == m_jack_connection_edges.size());
	_ASSERT(NULL != m_jack_skel);
	_ASSERT(NULL != m_sky_sphere);
	_ASSERT(NULL != m_sky_sphere_tex);

	// initialize some temp structs
	m_jack_intersection_offset = 0.5f;
	m_jack_combine_bone_node_list = m_jack_skel->getBoneNodeList();
	m_jack_bone_node_list = m_jack_skel->getBoneNodeList();
	m_jack_bone_transform_list.resize(m_jack_skel->getBoneNodeListSize());
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

		// set awake
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

	// collision detect between character and scene
	for(size_t i = 0; i < m_scene->getTriangleCount() && used < limits; i++)
	{
		used += my::CollisionDetector::sphereAndTriangle(
			m_character.sphere,
			m_scene->getTriangleVertex0(i),
			m_scene->getTriangleVertex1(i),
			m_scene->getTriangleVertex2(i),
			NULL,
			&contacts[used],
			limits - used); // *** take care of contact overflow
	}

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

	//// clear back surface with gray color
	//rc->fillSurface(rc->getClipperRect(), my::Color(0.8f, 0.8f, 0.8f));

	//// clear zbuffer with infinite distance
	//rc->fillZbuffer(rc->getClipperRect(), 0);

	// clear stencil buffer with zero
	rc->fillStencilBuffer(rc->getClipperRect(), 0);

	// set render context camera
	rc->setViewport(rc->getClipperRect());
	rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), rc->getClipperRect().Width(), rc->getClipperRect().Height()));
	rc->setCameraNearZ(1);
	rc->setCameraFarZ(100000);

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
		t3d::Mat4<real> matPosition = t3d::mat3Mov(my::Vec4<real>(0, 0, -20)) * matRotation * t3d::mat3Mov(m_hander.particle->getPosition());
		eulerCam->setPosition(my::Vec4<real>::ZERO * matPosition);
	}

	// set camera matrix (inversed matrix)
	rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEuler(eulerCam->getPosition(), eulerCam->getRotation()));

	// draw sky sphere to write both surface and zbuffer
	rc->setTextureBuffer(
		m_sky_sphere_tex->getBits(),
		m_sky_sphere_tex->getPitch(),
		m_sky_sphere_tex->getWidth(),
		m_sky_sphere_tex->getHeight());
	m_sky_sphere->drawTextureZBufferWWithBackface(rc);

	// set render context lights
	my::Vec4<real> l_pos(-30, 30, -10);
	l_pos *= t3d::CameraContext::buildCameraTransformEuler(eulerCam->getPosition(), eulerCam->getRotation());
	rc->clearLightList();
	rc->pushLightAmbient(my::Vec4<real>(0.2f, 0.2f, 0.2f));
	rc->pushLightPoint(my::Color::WHITE, l_pos);

	//// render character sphere
	//drawSphereWireZBufferRW(
	//	rc,
	//	m_character.sphere.getRadius(),
	//	m_character.body->getAwake() ? my::Color::RED : t3d::vec3Mul(my::Color::RED, 0.7f),
	//	m_character.body->getTransform());

	//// render camera hander particle
	//drawSphereWireZBufferRW(
	//	rc, 1, my::Color::YELLOW, t3d::mat3Mov(m_hander.particle->getPosition()));

	//// render the direction of character body
	//drawLinePointAndNormalZBufferRW(
	//	rc,
	//	m_character.body->getPosition(),
	//	my::Vec4<real>(0, 0, 10) * m_character.body->getRotationTransform(),
	//	my::Color::BLUE);

	//// draw grids that always around character
	//static int gridStep = 10;
	//static int gridRange = 10;
	//int gridCentX = (int)floor(m_character.body->getPosition().x / gridStep);
	//int gridCentZ = (int)floor(m_character.body->getPosition().z / gridStep);
	//real gridStartX = (gridCentX - gridRange) * gridStep;
	//real gridStartZ = (gridCentZ - gridRange) * gridStep;
	//real gridEndX = (gridCentX + gridRange) * gridStep;
	//real gridEndZ = (gridCentZ + gridRange) * gridStep;
	//rc->clearVertexList();
	//for(int i = -gridRange; i <= gridRange; i++)
	//{
	//	rc->pushVertex(my::Vec4<real>(gridStartX, 0, (gridCentZ + i) * gridStep));
	//	rc->pushVertex(my::Vec4<real>(gridEndX, 0, (gridCentZ + i) * gridStep));

	//	rc->pushVertex(my::Vec4<real>((gridCentX + i) * gridStep, 0, gridStartZ));
	//	rc->pushVertex(my::Vec4<real>((gridCentX + i) * gridStep, 0, gridEndZ));
	//}
	//rc->drawLineListZBufferRW(my::Color(0.6f, 0.6f, 0.6f));

	// render the scene
	m_scene_bsp->draw(rc);

	// update skeleton animation
	std::string current_anim_name = m_jack_skel->getCurrentAnimationName();
	if (t3d::vec3Length(m_character.body->getVelocity()) > 1)
	{
		if(current_anim_name != "clip3" && current_anim_name != "clip4")
		{
			m_jack_skel->setCurrentAnimationName("clip3");
			m_jack_skel->setCurrentAnimationTime(0);
			m_jack_intersection_offset = 0.5f;
		}
	}
	else
	{
		if(current_anim_name != "clip1" && current_anim_name != "clip2")
		{
			m_jack_skel->setCurrentAnimationName("clip1");
			m_jack_skel->setCurrentAnimationTime(0);
			m_jack_intersection_offset = 0.5f;
		}
	}

	// combine multi skeleton animation to bone node list
	t3d::BoneIndexList::const_iterator bone_index_iter = m_jack_skel->getRootIndexListBegin();
	for(; bone_index_iter != m_jack_skel->getRootIndexListEnd(); bone_index_iter++)
	{
		const t3d::BoneNodeList & boneNodeList = m_jack_skel->gotoAnimation(
			m_jack_skel->getCurrentAnimationName(),
			*bone_index_iter,
			m_jack_skel->getCurrentAnimationTime() + elapsedTime);

		t3d::incrementBoneNodeList(
			m_jack_combine_bone_node_list,
			m_jack_skel->getOrigBoneNodeList(),
			boneNodeList,
			*bone_index_iter);
	}

	// intersection current bone node list to combine bone node list
	t3d::intersectBoneNodeList(
		m_jack_bone_node_list,
		m_jack_bone_node_list,
		m_jack_combine_bone_node_list,
		0.5f,
		0,
		m_jack_intersection_offset,
		m_jack_skel->getRootIndexListBegin(),
		m_jack_skel->getRootIndexListEnd());

	// decrease intersection offset
	m_jack_intersection_offset = std::max<t3d::real>(0, m_jack_intersection_offset - elapsedTime);

	// calculate character rotation matrix
	t3d::Mat4<real> jack_mrot = t3d::buildRotationMatrixFromQuatLH(
		m_character.body->getOrientation() * t3d::buildQuatFromAngleAxis(DEG_TO_RAD(180), my::Vec4<real>::UNIT_Y));

	// gain bone transform list
	t3d::buildBoneTransformListFromBoneNodeList(
		m_jack_bone_transform_list,
		m_jack_bone_node_list,
		jack_mrot,
		jack_mrot * t3d::mat3Mov(t3d::vec3Add(m_character.body->getPosition(), my::Vec4<real>(0, -5.0f, 0))),
		m_jack_skel->getRootIndexListBegin(),
		m_jack_skel->getRootIndexListEnd());

	// combine final bone transform list
	t3d::combineVertexNormalBoneTransformList(
		m_jack_bone_transform_list,
		m_jack_skel->getOrigBoneInverseTransformList(),
		m_jack_bone_transform_list);

	m_jack_silhouette_edge_list.clear();
	for(int i = 0; i < 2; i++)
	{
		// combine jack model with bone transform list
		t3d::bindVertexListNormalListFromBoneTransformList(
			m_jack_meshs[i]->getVertexList(),
			m_jack_meshs[i]->getNormalList(),
			m_jack_bone_assignments[i]->getOriginalVertexList(),
			m_jack_bone_assignments[i]->getOriginalNormalList(),
			m_jack_bone_assignments[i]->getBoneAssignmentList(),
			m_jack_bone_transform_list);

		// draw jack sub mesh
		m_jack_meshs[i]->draw(rc);

		// calculate Indicator List, use the light at world directly
		t3d::IndicatorList jack_indicator_list;
		t3d::buildIndicatorListFromTriangleIndexListByPoint(
			jack_indicator_list,
			m_jack_meshs[i]->getVertexList(),
			m_jack_meshs[i]->getVertexIndexList(),
			l_pos);

		// calculate silhouette edge list
		t3d::pushSilhouetteEdgeList(
			m_jack_silhouette_edge_list,
			m_jack_connection_edges[i],
			m_jack_meshs[i]->getVertexList(),
			jack_indicator_list);
	}

	// calculate shadow volume
	m_jack_shadow_volume.clear();
	t3d::pushUncappedShadowVolumeByPoint(
		m_jack_shadow_volume,
		m_jack_silhouette_edge_list,
		l_pos,
		300);

	// draw shadow volume
	rc->clearVertexList();
	rc->pushVertexList(m_jack_shadow_volume.begin(), m_jack_shadow_volume.end());
	rc->drawTriangleListShadowVolumeZPass(my::Color(0.39f, 0.39f, 0.39f));
	return true;
}
