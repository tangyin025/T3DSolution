
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
	m_character.body->setMass(my::calculateSphereMass<real>(5, 1));
	m_character.body->setInertialTensor(my::calculateSphereInertiaTensor<real>(5, m_character.body->getMass()));
	m_character.body->setDamping(0.95f);
	m_character.body->setAngularDamping(0);
	m_character.body->setPosition(my::Vec4<real>(0, 10, 0));
	m_character.body->setAcceleration(my::Vec4<real>(0, -9.8 * 10, 0));
	m_character.body->setSleepEpsilon(10.4f); // ***
	m_character.body->setAwake(true); // must be call after setSleepEpsilon

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
	m_viewpoint.cable = my::ParticleCableConstraintPtr(new my::ParticleCableConstraint(m_viewpoint.particle.get(), m_character.body->getPosition(), 13, 0.3f));
	particleContactGeneratorList.push_back(m_viewpoint.cable);

	// //////////////////////////////////////////////////////////////////////////////////////////
}

MyWorld::~MyWorld(void)
{
}

void MyWorld::startFrame(void)
{
	my::World::startFrame();

	// //////////////////////////////////////////////////////////////////////////////////////////

	MyGameStatePtr gameState = MyGame::getSingleton().getState<MyGameState>(MyGameState::s_name);

	t3d::DIKeyboard * keyboard = MyGame::getSingleton().m_keyboard.get();

	t3d::Vec4<real> vrot = gameState->m_eulerCam->getRotation();

	t3d::Vec4<real> vvel = my::EulerCamera::buildMovOffset(keyboard, vrot.y, keyboard->isKeyDown(DIK_LSHIFT) ? 25 : 10);

	if(!t3d::vec3IsZero(vvel))
	{
		m_character.body->addVelocity(vvel);

		m_character.body->setAwake(true);
	}

	// //////////////////////////////////////////////////////////////////////////////////////////
}

void MyWorld::integrate(real duration)
{
	my::World::integrate(duration);

	m_character.sphere.calculateInternals();
}

unsigned MyWorld::generateContacts(my::Contact * contacts, unsigned limits)
{
	unsigned used = 0;

	// //////////////////////////////////////////////////////////////////////////////////////////

	used += my::CollisionDetector::sphereAndHalfSpace(m_character.sphere, m_groundPlane.normal, m_groundPlane.distance, &contacts[used], limits - used);

	// //////////////////////////////////////////////////////////////////////////////////////////

	for(unsigned i = 0; i < used; i++)
	{
		contacts[i].friction = 10.0f; //0.9f;

		contacts[i].restitution = 0; //0.6f;
	}

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
