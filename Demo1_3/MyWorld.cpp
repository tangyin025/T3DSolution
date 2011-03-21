
#include "StdAfx.h"
#include "MyWorld.h"
#include "MyGameEx.h"

MyWorld::MyWorld(void)
	: my::World(256)
	, my::ParticleWorld(256)
{
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
	my::World::integrate(duration);
}

unsigned MyWorld::generateContacts(my::Contact * contacts, unsigned limits)
{
	return my::World::generateContacts(contacts, limits);
}

void MyWorld::startFrameParticle(void)
{
	my::ParticleWorld::startFrame();
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
