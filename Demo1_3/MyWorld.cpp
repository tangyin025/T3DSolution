
#include "StdAfx.h"
#include "MyWorld.h"

MyWorld::MyWorld(void)
	: my::World(256)
{
	// initialize ground plane attribute
	m_groundPlane.normal = my::Vec4<real>::UNIT_Y;
	m_groundPlane.distance = 0;

	// create rigid body for character
	m_characterBody = my::RigidBodyPtr(new my::RigidBody());
	m_characterBody->setMass(my::calculateSphereMass<real>(5, 1));
	m_characterBody->setInertialTensor(my::calculateSphereInertiaTensor<real>(5, m_characterBody->getMass()));
	m_characterBody->setDamping(0.95);
	m_characterBody->setAngularDamping(0);
	m_characterBody->setPosition(my::Vec4<real>(0, 10, 0));
	m_characterBody->setAcceleration(my::Vec4<real>(0, -9.8 * 10, 0));
	m_characterBody->setSleepEpsilon(10.4f); // ***
	m_characterBody->setAwake(true);

	// add rigid body to physical world
	m_characterSphere.setRigidBody(m_characterBody.get());
	m_characterSphere.setRadius(5);
	bodyList.push_back(m_characterBody);
}

MyWorld::~MyWorld(void)
{
}

void MyWorld::integrate(real duration)
{
	my::World::integrate(duration);

	m_characterSphere.calculateInternals();
}

unsigned MyWorld::generateContacts(my::Contact * contacts, unsigned limits)
{
	unsigned used = 0;

	// collision detect
	used += my::CollisionDetector::sphereAndHalfSpace(m_characterSphere, m_groundPlane.normal, m_groundPlane.distance, &contacts[used], limits - used);

	// must set friction and restitution after my::CollisionDetector
	for(unsigned i = 0; i < used; i++)
	{
		contacts[i].friction = 10.0f; //0.9f;

		contacts[i].restitution = 0; //0.6f;
	}

	return used;
}
