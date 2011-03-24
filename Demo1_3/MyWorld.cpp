
#include "StdAfx.h"
#include "MyWorld.h"
#include "MyGameEx.h"

MyWorld::MyWorld(void)
	: World(256)
	, ParticleWorld(256)
{
}

MyWorld::~MyWorld(void)
{
}

void MyWorld::runPhysics(real duration)
{
	World::startFrame();

	World::registry.updateForces(duration);

	World::integrate(duration);

	unsigned usedContacts = World::generateContacts(&contactList[0], World::maxContacts);

	World::resolver.setPositionIterations(usedContacts * 4);

	World::resolver.setVelocityIterations(usedContacts * 4);

	World::resolver.resolveContacts(&contactList[0], usedContacts, duration);

	ParticleWorld::startFrame();

	ParticleWorld::registry.updateForces(duration);

	ParticleWorld::integrate(duration);

	unsigned used = ParticleWorld::generateContacts(&particleContactArray[0], ParticleWorld::maxContacts);

	ParticleWorld::resolver.setIterations(used * 2);

	ParticleWorld::resolver.resolveContacts(&particleContactArray[0], used, duration);
}
