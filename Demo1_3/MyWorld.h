
#pragma once

class MyWorld
	: public my::World
	, public my::ParticleWorld
{
public:
	// //////////////////////////////////////////////////////////////////////////////////////////

	struct _Plane
	{
		my::Vec4<t3d::real> normal;

		t3d::real distance;
	}
	m_groundPlane;

	struct _Character
	{
		my::RigidBodyPtr body;

		my::CollisionSphere sphere;

		_Character(void)
			: body()
			, sphere(0, NULL)
		{
		}
	}
	m_character;

	struct _Viewpoint
	{
		my::ParticlePtr particle;

		my::ParticleAnchoredSpringPtr spring;

		my::ParticleCableConstraintPtr cable;
	}
	m_viewpoint;

	typedef std::vector<my::CollisionBox> CollisionBoxList;

	CollisionBoxList m_boxList;

	my::RigidBodyPtrList m_boxBodyList;

	// //////////////////////////////////////////////////////////////////////////////////////////

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
