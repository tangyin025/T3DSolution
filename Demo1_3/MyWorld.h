
#pragma once

class MyCollisionPrimitive
{
public:
	virtual unsigned collisionDetect(const my::CollisionPlane & plane, my::Contact * contacts, unsigned limits) const = 0;

	virtual unsigned collisionDetect(const my::CollisionSphere & sphere, my::Contact * contacts, unsigned limits) const = 0;

	virtual unsigned collisionDetect(const my::CollisionBox & box, my::Contact * contacts, unsigned limits) const = 0;

	virtual unsigned collisionDetect(const MyCollisionPrimitive & primitive, my::Contact * contacts, unsigned limits) const = 0;
};

typedef boost::shared_ptr<MyCollisionPrimitive> MyCollisionPrimitivePtr;

typedef std::vector<MyCollisionPrimitivePtr> MyCollisionPrimitivePtrList;

class MyCollisionPlane : public my::CollisionPlane
{
public:
	unsigned collisionDetect(const my::CollisionPlane & plane, my::Contact * contacts, unsigned limits) const
	{
		return 0;
	}

	unsigned collisionDetect(const my::CollisionSphere & sphere, my::Contact * contacts, unsigned limits) const
	{
		return my::CollisionDetector::sphereAndHalfSpace(sphere, normal, distance, contacts, limits);
	}

	unsigned collisionDetect(const my::CollisionBox & box, my::Contact * contacts, unsigned limits) const
	{
		return my::CollisionDetector::boxAndHalfSpace(box, normal, distance, contacts, limits);
	}

	unsigned collisionDetect(const MyCollisionPrimitive & primitive, my::Contact * contacts, unsigned limits) const
	{
		return primitive.collisionDetect(*this, contacts, limits);
	}
};

class MyCollisionSphere : public my::CollisionSphere
{
public:
	unsigned collisionDetect(const my::CollisionPlane & plane, my::Contact * contacts, unsigned limits) const
	{
		return my::CollisionDetector::sphereAndHalfSpace(*this, plane.getNormal(), plane.getDistance(), contacts, limits);
	}

	unsigned collisionDetect(const my::CollisionSphere & sphere, my::Contact * contacts, unsigned limits) const
	{
		return my::CollisionDetector::sphereAndSphere(sphere, *this, contacts, limits);
	}

	unsigned collisionDetect(const my::CollisionBox & box, my::Contact * contacts, unsigned limits) const
	{
		return my::CollisionDetector::boxAndSphere(box, *this, contacts, limits);
	}

	unsigned collisionDetect(const MyCollisionPrimitive & primitive, my::Contact * contacts, unsigned limits) const
	{
		return primitive.collisionDetect(*this, contacts, limits);
	}
};

class MyCollisionBox : public my::CollisionBox
{
public:
	unsigned collisionDetect(const my::CollisionPlane & plane, my::Contact * contacts, unsigned limits) const
	{
		return my::CollisionDetector::boxAndHalfSpace(*this, plane.getNormal(), plane.getDistance(), contacts, limits);
	}

	unsigned collisionDetect(const my::CollisionSphere & sphere, my::Contact * contacts, unsigned limits) const
	{
		return my::CollisionDetector::boxAndSphere(*this, sphere, contacts, limits);
	}

	unsigned collisionDetect(const my::CollisionBox & box, my::Contact * contacts, unsigned limits) const
	{
		return my::CollisionDetector::boxAndBox(box, *this, contacts, limits);
	}

	unsigned collisionDetect(const MyCollisionPrimitive & primitive, my::Contact * contacts, unsigned limits) const
	{
		return primitive.collisionDetect(*this, contacts, limits);
	}
};

class TPSCharacter
{
public:
	my::RigidBodyPtr body;

	my::CollisionSphere sphere;
};

class CharacterMonitorHander
{
public:
	my::ParticlePtr particle;

	my::ParticleAnchoredSpringPtr spring;

	my::ParticleCableConstraintPtr cable;
};

class MyWorld
	: public my::World
	, public my::ParticleWorld
{
public:
	TPSCharacter m_character;

	CharacterMonitorHander m_hander;

	MyCollisionPrimitivePtrList m_scene;

public:
	MyWorld(void);

	~MyWorld(void);

	void runPhysics(real duration);
};

typedef boost::shared_ptr<MyWorld> MyWorldPtr;
