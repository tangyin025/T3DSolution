
#pragma once

class MyWorld
	: public my::World
	, public my::ParticleWorld
{
public:
	my::CollisionSphere m_characterSphere;

	struct
	{
		my::Vec4<t3d::real> normal;

		t3d::real distance;
	}
	m_groundPlane;

	my::RigidBodyPtr m_characterBody;

public:
	MyWorld(void);

	~MyWorld(void);

	//void integrate(real duration);

	//unsigned generateContacts(my::Contact * contacts, unsigned limits);

	void runPhysics(real duration);
};

typedef boost::shared_ptr<MyWorld> MyWorldPtr;
