
#include "StdAfx.h"
#include "MyWorld.h"
#include "MyGameEx.h"

MyWorld::MyWorld(void)
	: my::World(256)
	, my::ParticleWorld(256)
{
	// //////////////////////////////////////////////////////////////////////////////////////////

	// initialize ground plane attribute
	m_groundPlane.normal = my::Vec4<real>::UNIT_Y;
	m_groundPlane.distance = 0;

	// create rigid body for character
	m_character.body = my::RigidBodyPtr(new my::RigidBody());
	m_character.body->setMass(my::calculateSphereMass(5, 1));
	m_character.body->setInertialTensor(my::calculateSphereInertiaTensor(5, m_character.body->getMass()));
	m_character.body->setDamping(0.95f);
	m_character.body->setAngularDamping(0);
	m_character.body->setPosition(my::Vec4<real>(0, 10, 0));
	m_character.body->setAcceleration(my::Vec4<real>(0, -9.8 * 10, 0));
	m_character.body->setSleepEpsilon(10.4f); // ***
	m_character.body->setAwake(true); // must be call after setSleepEpsilon
	m_character.body->calculateDerivedData(); // never forget this

	// add rigid body to physical world
	m_character.sphere.setRigidBody(m_character.body.get());
	m_character.sphere.setRadius(5);
	bodyList.push_back(m_character.body);

	// create particle for camera view at character head
	m_viewpoint.particle = my::ParticlePtr(new my::Particle());
	m_viewpoint.particle->setMass(1);
	m_viewpoint.particle->setPosition(t3d::vec3Add(m_character.body->getPosition(), my::Vec4<real>(0, 10, 0)));
	m_viewpoint.particle->setVelocity(my::Vec4<real>::ZERO);
	m_viewpoint.particle->setDamping(0.00001f); // ***
	m_viewpoint.particle->setAcceleration(my::Vec4<real>::ZERO);
	particleList.push_back(m_viewpoint.particle);

	// create particle spring for view point
	m_viewpoint.spring = my::ParticleAnchoredSpringPtr(new my::ParticleAnchoredSpring(m_character.body->getPosition(), 100, 10)); // ***
	my::ParticleWorld::registry.add(m_viewpoint.particle.get(), m_viewpoint.spring.get());

	// create particle spring cable
	m_viewpoint.cable = my::ParticleCableConstraintPtr(new my::ParticleCableConstraint(m_viewpoint.particle.get(), m_character.body->getPosition(), 13, 0.0f));
	particleContactGeneratorList.push_back(m_viewpoint.cable);

	// create stack boxes
	const int countx = 5 * 10 / 2;
	const int county = 5 * 10 - 5;
	for(int x = -countx + 5; x < countx + 5; x += 10)
	{
		for(int y = 5; y <= county; y += 10)
		{
			// create rigid body for box
			my::Vec4<real> halfSize(5, 5, 5);
			my::RigidBodyPtr body(new my::RigidBody());
			body->setMass(my::calculateBoxVolume(halfSize.x * 2, halfSize.y * 2, halfSize.z * 2) * 0.4f);
			body->setInertialTensor(my::calculateBlockInertiaTensor(halfSize, body->getMass()));
			body->setDamping(0.95f);
			body->setAngularDamping(0.8f);
			body->setPosition(my::Vec4<real>(x, y, 30));
			body->setAcceleration(my::Vec4<real>(0, -9.8 * 10, 0));
			body->setSleepEpsilon(10.4f);
			body->setAwake(true);
			body->calculateDerivedData();
			m_boxBodyList.push_back(body);

			// create collision box
			m_boxList.push_back(my::CollisionBox(halfSize, body.get()));

			// for parent maintained body list
			bodyList.push_back(body);
		}
	}

	// //////////////////////////////////////////////////////////////////////////////////////////
}

MyWorld::~MyWorld(void)
{
}

void MyWorld::startFrame(void)
{
	my::World::startFrame();
}

void MyWorld::integrate(real duration)
{
	// //////////////////////////////////////////////////////////////////////////////////////////

	MyGameStatePtr gameState = MyGame::getSingleton().getState<MyGameState>(MyGameState::s_name);

	t3d::DIKeyboard * keyboard = MyGame::getSingleton().m_keyboard.get();

	t3d::Vec4<real> vrot = gameState->m_eulerCam->getRotation();

	t3d::Vec4<real> vvel = my::EulerCamera::buildMovOffset(keyboard, vrot.y, keyboard->isKeyDown(DIK_LSHIFT) ? 90 : 30);

	if(!t3d::vec3IsZero(vvel))
	{
		m_character.body->setVelocity(my::Vec4<real>(vvel.x, m_character.body->getVelocity().y, vvel.z));

		t3d::Vec4<real> vdir = my::Vec4<real>::UNIT_Z * m_character.body->getRotationTransform();

		t3d::Vec4<real> vcro = t3d::vec3Cross(vdir, vvel);

		real costheta = t3d::vec3CosTheta(vdir, t3d::vec3Normalize(vvel));

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

	// //////////////////////////////////////////////////////////////////////////////////////////

	my::World::integrate(duration);

	// //////////////////////////////////////////////////////////////////////////////////////////

	m_character.sphere.calculateInternals();

	for(size_t i = 0; i < m_boxList.size(); i++)
	{
		m_boxList[i].calculateInternals();
	}

	// //////////////////////////////////////////////////////////////////////////////////////////
}

unsigned MyWorld::generateContacts(my::Contact * contacts, unsigned limits)
{
	unsigned used = 0;

	// //////////////////////////////////////////////////////////////////////////////////////////

	used += my::CollisionDetector::sphereAndHalfSpace(
		m_character.sphere,
		m_groundPlane.normal,
		m_groundPlane.distance,
		&contacts[used],
		limits - used);

	unsigned i = 0;
	for(; i < used; i++)
	{
		contacts[i].friction = 10.0f; //0.9f;
		contacts[i].restitution = 0; //0.6f;
	}

	for(size_t j = 0; j < m_boxList.size(); j++)
	{
		for(size_t k = j + 1; k < m_boxList.size(); k++)
		{
			used += my::CollisionDetector::boxAndBox(
				m_boxList[j],
				m_boxList[k],
				&contacts[used],
				limits - used);
		}

		used += my::CollisionDetector::boxAndHalfSpace(
			m_boxList[j],
			m_groundPlane.normal,
			m_groundPlane.distance,
			&contacts[used],
			limits - used);

		used += my::CollisionDetector::boxAndSphere(
			m_boxList[j],
			m_character.sphere,
			&contacts[used],
			limits - used);
	}

	for(; i < used; i++)
	{
		contacts[i].friction = 0.9f;
		contacts[i].restitution = 0.6f;
	}

	// //////////////////////////////////////////////////////////////////////////////////////////

	return used;
}

void MyWorld::startFrameParticle(void)
{
	my::ParticleWorld::startFrame();

	// //////////////////////////////////////////////////////////////////////////////////////////

	m_viewpoint.spring->setAnchor(m_character.body->getPosition());

	m_viewpoint.cable->setAnchor(m_character.body->getPosition());

	m_viewpoint.particle->setPosition(my::Vec4<real>(m_character.body->getPosition().x, m_viewpoint.particle->getPosition().y, m_character.body->getPosition().z));

	// //////////////////////////////////////////////////////////////////////////////////////////
}

void MyWorld::integrateParticle(real duration)
{
	return my::ParticleWorld::integrate(duration);
}

unsigned MyWorld::generateContactsParticle(my::ParticleContact * contacts, unsigned limits)
{
	return my::ParticleWorld::generateContacts(contacts, limits);
}

void MyWorld::runPhysics(real duration)
{
	//my::World::runPhysics(duration);

	startFrame();

	my::World::registry.updateForces(duration);

	integrate(duration);

	unsigned usedContacts = generateContacts(&contactList[0], my::World::maxContacts);

	my::World::resolver.setPositionIterations(usedContacts * 4);

	my::World::resolver.setVelocityIterations(usedContacts * 4);

	my::World::resolver.resolveContacts(&contactList[0], usedContacts, duration);

	//my::ParticleWorld::runPhysics(duration);

	startFrameParticle();

	my::ParticleWorld::registry.updateForces(duration);

	integrateParticle(duration);

	unsigned used = generateContactsParticle(&particleContactArray[0], my::ParticleWorld::maxContacts);

	my::ParticleWorld::resolver.setIterations(used * 2);

	my::ParticleWorld::resolver.resolveContacts(&particleContactArray[0], used, duration);
}
