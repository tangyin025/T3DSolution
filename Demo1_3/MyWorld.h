
#pragma once

class MyWorld
	: public my::World
	, public my::ParticleWorld
{
public:
	MyWorld(void);

	~MyWorld(void);

	void startFrame(void);

	void integrate(real duration);

	unsigned generateContacts(my::Contact * contacts, unsigned limits);

	void startFrameParticle(void);

	void integrateParticle(real duration);

	unsigned generateContactsParticle(my::ParticleContact * contacts, unsigned limits);

	void runPhysics(real duration);
};

typedef boost::shared_ptr<MyWorld> MyWorldPtr;
