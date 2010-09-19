
#pragma once

#include "myPhysics.h"

class MyWorld : public my::World
{
protected:
	my::CollisionSphere m_characterSphere;

	struct
	{
		my::Vec4<t3d::real> normal;

		t3d::real distance;
	}
	m_groundPlane;

public:
	MyWorld(void);

	~MyWorld(void);

protected:
	void integrate(real duration);

	unsigned generateContacts(my::Contact * contacts, unsigned limits);
};
