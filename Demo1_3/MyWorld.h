
#pragma once

class MyWorld : public my::World
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

protected:
	void integrate(real duration);

	unsigned generateContacts(my::Contact * contacts, unsigned limits);
};

typedef boost::shared_ptr<MyWorld> MyWorldPtr;
