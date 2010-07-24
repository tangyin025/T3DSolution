
#ifndef __MYPHYSICS_H__
#define __MYPHYSICS_H__

#include "myCommon.h"
#include <cmath>
#include <list>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "myMath.h"

namespace my
{
	// /////////////////////////////////////////////////////////////////////////////////////
	// Particle
	// /////////////////////////////////////////////////////////////////////////////////////

	class Particle
	{
	protected:
		t3d::Vec4<real> position;

		t3d::Vec4<real> velocity;

		t3d::Vec4<real> acceleration;

		t3d::Vec4<real> forceAccum;

		real damping;

		real inverseMass;

	public:
		void setPosition(const t3d::Vec4<real> & _position);

		void addPosition(const t3d::Vec4<real> & _position);

		const t3d::Vec4<real> & getPosition(void) const;

		void setVelocity(const t3d::Vec4<real> & _velocity);

		void addVelocity(const t3d::Vec4<real> & _velocity);

		const t3d::Vec4<real> & getVelocity(void) const;

		void setAcceleration(const t3d::Vec4<real> & _acceleration);

		const t3d::Vec4<real> & getAcceleration(void) const;

		void addForce(const t3d::Vec4<real> & force);

		const t3d::Vec4<real> & getAccumlator(void) const;

		void clearAccumulator(void);

		void setDamping(real _damping);

		real getDamping(void) const;

		void setInverseMass(real _inverseMass);

		real getInverseMass(void) const;

		void setMass(real mass);

		real getMass(void) const;

		bool hasFiniteMass(void) const;

		void integrate(real duration);
	};

	typedef boost::shared_ptr<Particle> ParticlePtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleForceRegistry
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleForceGenerator;

	class ParticleForceRegistry
	{
	protected:
		class ParticleForceRegistration
		{
		public:
			Particle * particle;

			ParticleForceGenerator * forceGenerator;

		public:
			ParticleForceRegistration(Particle * _particle, ParticleForceGenerator * _forceGenerator);
		};

		typedef std::list<ParticleForceRegistration> ParticleForceRegistrationList;

		ParticleForceRegistrationList forceRegistrationList;

	public:
		void add(Particle * particle, ParticleForceGenerator * forceGenerator);

		void remove(Particle * particle, ParticleForceGenerator * forceGenerator);

		void clear(void);

		void updateForces(real duration);
	};

	typedef boost::shared_ptr<ParticleForceRegistry> ParticleForceRegistryPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleForceGenerator
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleForceGenerator
	{
	public:
		virtual ~ParticleForceGenerator(void);

	public:
		virtual void updateForce(Particle * particle, real duration) = 0;
	};

	typedef boost::shared_ptr<ParticleForceGenerator> ParticleForceGeneratorPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleGravity
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleGravity : public ParticleForceGenerator
	{
	protected:
		t3d::Vec4<real> gravity;

	public:
		ParticleGravity(const t3d::Vec4<real> & _gravity);

		void updateForce(Particle * particle, real duration);
	};

	typedef boost::shared_ptr<ParticleGravity> ParticleGravityPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleDrag
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleDrag : public ParticleForceGenerator
	{
	protected:
		real k1;

		real k2;

	public:
		ParticleDrag(real _k1, real _k2);

		void updateForce(Particle * particle, real duration);
	};

	typedef boost::shared_ptr<ParticleDrag> ParticleDragPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleSpring
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleSpring : public ParticleForceGenerator
	{
	protected:
		Particle * other;

		real springConstant;

		real restLength;

	public:
		ParticleSpring(Particle * _other, real _springConstant, real _restLength);

		void updateForce(Particle * particle, real duration);
	};

	typedef boost::shared_ptr<ParticleSpring> ParticleSpringPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleAnchoredSpring
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleAnchoredSpring : public ParticleForceGenerator
	{
	protected:
		t3d::Vec4<real> anchor;

		real springConstant;

		real restLength;

	public:
		ParticleAnchoredSpring(const t3d::Vec4<real> & _anchor, real _springConstant, real _restLength);

		void updateForce(Particle * particle, real duration);
	};

	typedef boost::shared_ptr<ParticleAnchoredSpring> ParticleAnchoredSpringPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleBungee
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleBungee : public ParticleForceGenerator
	{
	protected:
		Particle * other;

		real springConstant;

		real restLength;

	public:
		ParticleBungee(Particle * _other, real _springConstant, real _restLength);

		void updateForce(Particle * particle, real duration);
	};

	typedef boost::shared_ptr<ParticleBungee> ParticleBungeePtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleAnchoredBungee
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleAnchoredBungee : public ParticleForceGenerator
	{
	protected:
		t3d::Vec4<real> anchor;

		real springConstant;

		real restLength;

	public:
		ParticleAnchoredBungee(const t3d::Vec4<real> & _anchor, real _springConstant, real _restLength);

		void updateForce(Particle * particle, real duration);
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleBuoyancy
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleBuoyancy : public ParticleForceGenerator
	{
	protected:
		real maxDepth;

		real volumn;

		real waterHeight;

		real liquidDensity;

	public:
		ParticleBuoyancy(real _maxDepth, real _volumn, real _waterHeight, real _liquidDensity = 1000.0f);

		void updateForce(Particle * particle, real duration);
	};

	typedef boost::shared_ptr<ParticleBuoyancy> ParticleBuoyancyPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleFakeSpring
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleFakeSpring : public ParticleForceGenerator
	{
	protected:
		t3d::Vec4<real> anchor;

		real springConstant;

		real damping;

	public:
		ParticleFakeSpring(const t3d::Vec4<real> & _anchor, real _springConstant, real _damping);

		void updateForce(Particle * particle, real duration);
	};

	typedef boost::shared_ptr<ParticleFakeSpring> ParticleFakeSpringPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleContact
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleContact
	{
		friend class ParticleContactResolver;

	public:
		Particle * particles[2];

		real restitution;

		t3d::Vec4<real> contactNormal;

		real penetration;

	protected:
		void resolve(real duration);

		real calculateSeparatingVelocity(void) const;

		void resolveVelocity(real duration);

		void resolveInterpenetration(real duration);
	};

	typedef boost::shared_ptr<ParticleContact> ParticleContactPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleContactResolver
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleContactResolver
	{
	protected:
		unsigned iterations;

		unsigned iterationsUsed;

	public:
		ParticleContactResolver(unsigned _iterations);

		void setIterations(unsigned _iterations);

		unsigned getIterations(void) const;

		void resolveContacts(ParticleContact * contactArray, unsigned numContacts, real duration);
	};

	typedef boost::shared_ptr<ParticleContactResolver> ParticleContactResolverPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleContactGenerator
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleContactGenerator
	{
	public:
		virtual ~ParticleContactGenerator(void);

	public:
		virtual unsigned addContact(ParticleContact * contact, unsigned limit) const = 0;
	};

	typedef boost::shared_ptr<ParticleContactGenerator> ParticleContactGeneratorPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleLink
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleLink : public ParticleContactGenerator
	{
	public:
		Particle * particles[2];

	public:
		ParticleLink(Particle * particle0, Particle * particle1);

	protected:
		real currentLength() const;

	//public:
	//	virtual unsigned addContact(ParticleContact * contact, unsigned limit) const = 0;
	};

	typedef boost::shared_ptr<ParticleLink> ParticleLinkPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleCable
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleCable : public ParticleLink
	{
	public:
		real maxLength;

		real restitution;

	public:
		ParticleCable(Particle * particle0, Particle * particle1, real _maxLength, real _restitution);

		unsigned addContact(ParticleContact * contact, unsigned limit) const;
	};

	typedef boost::shared_ptr<ParticleCable> ParticleCablePtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleRod
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleRod : public ParticleLink
	{
	public:
		real length;

	public:
		ParticleRod(Particle * particle0, Particle * particle1, real _length);

		unsigned addContact(ParticleContact * contact, unsigned limit) const;
	};

	typedef boost::shared_ptr<ParticleRod> ParticleRodPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleConstraint
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleConstraint : public ParticleContactGenerator
	{
	public:
		Particle * particle;

		t3d::Vec4<real> anchor;

	public:
		ParticleConstraint(Particle * _particle, const my::Vec4<real> & _anchor);

	protected:
		real currentLength() const;

	//public:
	//	virtual unsigned addContact(ParticleContact * contact, unsigned limit) const = 0;
	};

	typedef boost::shared_ptr<ParticleConstraint> ParticleConstraintPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleCableConstraint
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleCableConstraint : public ParticleConstraint
	{
	public:
		real maxLength;

		real restitution;

	public:
		ParticleCableConstraint(Particle * particle, const my::Vec4<real> & anchor, real _maxLength, real _restitution);

		unsigned addContact(ParticleContact * contact, unsigned limit) const;
	};

	typedef boost::shared_ptr<ParticleCableConstraint> ParticleCableConstraintPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleRodConstraint
	// /////////////////////////////////////////////////////////////////////////////////////

	class ParticleRodConstraint : public ParticleConstraint
	{
	public:
		real length;

	public:
		ParticleRodConstraint(Particle * particle, const my::Vec4<real> & anchor, real _length);

		unsigned addContact(ParticleContact * contact, unsigned limit) const;
	};

	typedef boost::shared_ptr<ParticleRodConstraint> ParticleRodConstraintPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ParticleWorld
	// /////////////////////////////////////////////////////////////////////////////////////

	typedef std::vector<my::ParticlePtr> ParticlePtrList;

	typedef std::vector<my::ParticleContactGeneratorPtr> ParticleContactGeneratorPtrList;

	typedef std::vector<my::ParticleContact> ParticleContactArray;

	class ParticleWorld
	{
	protected:
		ParticlePtrList particleList;

		ParticleForceRegistry registry;

		ParticleContactResolver resolver;

		ParticleContactGeneratorPtrList particleContactGeneratorList;

		ParticleContactArray particleContactArray;

		unsigned maxContacts;

	public:
		ParticleWorld(unsigned _maxContacts, unsigned _iterations = 0);

		virtual ~ParticleWorld(void);

		virtual void startFrame(void);

		virtual unsigned generateContacts(void);

		virtual void integrate(real duration);

		void runPhysics(real duration);
	};

	typedef boost::shared_ptr<ParticleWorld> ParticleWorldPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// RigidBody
	// /////////////////////////////////////////////////////////////////////////////////////

	class RigidBody
	{
	//protected:
	public:
		real inverseMass;

		t3d::Vec4<real> position;

		t3d::Quat<real> orientation;

		t3d::Vec4<real> velocity;

		t3d::Vec4<real> rotation;

		t3d::Mat4<real> transform;

		t3d::Mat4<real> rotationTransform;

		t3d::Mat4<real> inverseInertiaTensor;

		t3d::Mat4<real> inverseInertiaTensorWorld;

		t3d::Vec4<real> acceleration;

		t3d::Vec4<real> forceAccum;

		t3d::Vec4<real> torqueAccum;

		t3d::Vec4<real> resultingAcc;

		t3d::Vec4<real> resultingAngularAcc;

		real damping;

		real angularDamping;

		real motion;

		bool isAwake;

		bool canSleep;

		static real sleepEpsilon;

	public:
		void calculateDerivedData(void);

		void setMass(real mass);

		real getMass(void) const;

		void setInverseMass(real _inverseMass);

		real getInverseMass(void) const;

		void setPosition(const t3d::Vec4<real> & _position);

		void addPosition(const t3d::Vec4<real> & _position);

		const t3d::Vec4<real> & getPosition(void) const;

		void setOrientation(const t3d::Quat<real> & _orientation);

		void addOrientation(const t3d::Vec4<real> & _rotation); // ***

		const t3d::Quat<real> & getOrientation(void) const;

		void setVelocity(const t3d::Vec4<real> & _velocity);

		const t3d::Vec4<real> & getVelocity(void) const;

		void addVelocity(const t3d::Vec4<real> & _velocity);

		void setRotation(const t3d::Vec4<real> & _rotation);

		const t3d::Vec4<real> & getRotation(void) const;

		void addRotation(const t3d::Vec4<real> & _rotation);

		const t3d::Mat4<real> & getTransform(void) const;

		t3d::Mat4<real> getInverseTransform(void) const;

		const t3d::Mat4<real> & getRotationTransform(void) const;

		t3d::Mat4<real> getInverseRotationTransform(void) const;

		void setInertialTensor(const t3d::Mat4<real> & inertialTensor);

		t3d::Mat4<real> getInertialTensor(void) const;

		void setInverseInertialTensor(const t3d::Mat4<real> & _inverseInertiaTensor);

		const t3d::Mat4<real> & getInverseInertialTensor(void) const;

		void setAcceleration(const t3d::Vec4<real> & _acceleration);

		const t3d::Vec4<real> & getAcceleration(void) const;

		void addForce(const t3d::Vec4<real> & force);

		void addTorque(const t3d::Vec4<real> & torque);

		const t3d::Vec4<real> & getResultingAcc(void) const;

		const t3d::Vec4<real> & getResultingAngularAcc(void) const;

		void setDamping(real _damping);

		real getDamping(void) const;

		void setAngularDamping(real _angularDamping);

		real getAngularDamping(void) const;

		void setAwake(bool _isAwake = true);

		bool getAwake(void) const;

		void setCanSleep(bool _canSleep = true);

		bool getCanSleep(void) const;

		static void setSleepEpsilon(real _sleepEpsilon);

		static real getSleepEpsilon();

		void addForceAtPoint(const t3d::Vec4<real> & force, const t3d::Vec4<real> & point);

		void clearAccumulator(void);

		bool hasFiniteMass(void) const;

		void integrate(real duration);
	};

	typedef boost::shared_ptr<RigidBody> RigidBodyPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ForceRegistry
	// /////////////////////////////////////////////////////////////////////////////////////

	class ForceGenerator;

	class ForceRegistry
	{
	protected:
		class ForceRegistration
		{
		public:
			RigidBody * body;

			ForceGenerator * forceGenerator;

		public:
			ForceRegistration(RigidBody * _body, ForceGenerator * _forceGenerator);
		};

		typedef std::list<ForceRegistration> ForceRegistrationList;

		ForceRegistrationList forceRegistrationList;

	public:
		void add(RigidBody * body, ForceGenerator * forceGenerator);

		void remove(RigidBody * body, ForceGenerator * forceGenerator);

		void clear(void);

		void updateForces(real duration);
	};

	typedef boost::shared_ptr<ForceRegistry> ForceRegistryPtr;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ForceGenerator
	// /////////////////////////////////////////////////////////////////////////////////////

	class ForceGenerator
	{
	public:
		virtual ~ForceGenerator(void);

		virtual void updateForce(RigidBody * body, real duration) = 0;
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// Gravity
	// /////////////////////////////////////////////////////////////////////////////////////

	class Gravity : public ForceGenerator
	{
	protected:
		t3d::Vec4<real> gravity;

	public:
		Gravity(const t3d::Vec4<real> & _gravity);

		void updateForce(RigidBody * body, real duration);
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// Spring
	// /////////////////////////////////////////////////////////////////////////////////////

	class Spring : public ForceGenerator
	{
	protected:
		t3d::Vec4<real> connectionPoint;

		RigidBody * other;

		t3d::Vec4<real> otherConnectionPoint;

		real springConstant;

		real restLength;

	public:
		Spring(
			const t3d::Vec4<real> & _connectionPoint,
			RigidBody * _other,
			const t3d::Vec4<real> & _otherConnectionPoint,
			real _springConstant,
			real _restLength);

		void updateForce(RigidBody * body, real duration);
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// Aero
	// /////////////////////////////////////////////////////////////////////////////////////

	class Aero : public ForceGenerator
	{
	//protected:
	public:
		t3d::Mat4<real> tensor;

		t3d::Vec4<real> position;

		const t3d::Vec4<real> * pwindSpeed;

	public:
		Aero(
			const t3d::Mat4<real> & _tensor,
			const t3d::Vec4<real> & _position,
			const t3d::Vec4<real> * _pwindSpeed);

		void updateForce(RigidBody * body, real duration);

		void updateForceFromTensor(RigidBody * body, real duration, const t3d::Mat4<real> & _tensor);
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// AeroControl
	// /////////////////////////////////////////////////////////////////////////////////////

	class AeroControl : public Aero
	{
	//protected:
	public:
		t3d::Mat4<real> minTensor;

		t3d::Mat4<real> maxTensor;

		real controlSetting;

	public:
		void setControl(real value);

	public:
		AeroControl(
			const t3d::Mat4<real> & _tensor,
			const t3d::Mat4<real> & _minTensor,
			const t3d::Mat4<real> & _maxTensor,
			const t3d::Vec4<real> & _position,
			const t3d::Vec4<real> * _pwindSpeed);

		void updateForce(RigidBody * body, real duration);

		void updateForceFromControl(RigidBody * body, real duration, real _controlSetting);
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// AngledAero
	// /////////////////////////////////////////////////////////////////////////////////////

	class AngledAero : public Aero
	{
	protected:
		t3d::Quat<real> orientation;

	public:
		void setOrientation(const t3d::Quat<real> & _orientation);

		const t3d::Quat<real> & getOrientation(void) const;

	public:
		AngledAero(
			const t3d::Mat4<real> & _tensor,
			const t3d::Vec4<real> & _position,
			const t3d::Vec4<real> * _pwindSpeed);

		void updateForce(RigidBody * body, real duration);
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// Buoyancy
	// /////////////////////////////////////////////////////////////////////////////////////

	class Buoyancy : public ForceGenerator
	{
	protected:
		real maxDepth;

		real volume;

		real waterHeight;

		real liquidDensity;

		t3d::Vec4<real> centerOfBuoyancy;

	public:
		Buoyancy(
			const t3d::Vec4<real> & _centerOfBuoyancy,
			real _maxDepth,
			real _volume,
			real _waterHeight,
			real _liquidDensity = 1000.0f);

		void updateForce(RigidBody * body, real duration);
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// Contact
	// /////////////////////////////////////////////////////////////////////////////////////

	class Contact
	{
		friend class ContactResolver;

	public:
		RigidBody * bodys[2];

		real friction;

		real restitution;

		t3d::Vec4<real> contactPoint;

		t3d::Vec4<real> contactNormal;

		real penetration;

	//protected:
	public:
		t3d::Mat4<real> contactToWorld;

		t3d::Vec4<real> contactVelocity;

		real desiredDeltaVelocity;

		t3d::Vec4<real> relativeContactPositions[2];

	//protected:
	public:
		void swapBodies(void);

		void matchAwakeState(void);

		void calculateContactBasis(void);

		t3d::Vec4<real> calculateLocalVelocity(const RigidBody & body, const t3d::Vec4<real> & relativeContactPosition, real duration) const;

		void calculateDesiredDeltaVelocity(real duration);

		void calculateInternals(real duration);

		t3d::Vec4<real> calculateFrictionlessImpulse(const t3d::Mat4<real> inverseInertialTensors[]) const;

		t3d::Vec4<real> calculateFrictionImpulse(const t3d::Mat4<real> inverseInertialTensors[]) const;

		void applyPositionChange(t3d::Vec4<real> linearChanges[2], t3d::Vec4<real> angularChanges[2]);

		void applyVelocityChange(t3d::Vec4<real> velocityChanges[2], t3d::Vec4<real> rotationChanges[2]);
	};

	typedef std::vector<Contact> ContactList;

	// /////////////////////////////////////////////////////////////////////////////////////
	// ContactResolver
	// /////////////////////////////////////////////////////////////////////////////////////

	class ContactResolver
	{
	protected:
		unsigned positionIterations;

		unsigned velocityIterations;

		real positionEpsilon;

		real velocityEpsilon;

		unsigned positionIterationsUsed;

		unsigned velocityIterationsUsed;

	public:
		void setPositionIterations(unsigned iterations);

		unsigned getPositionIterations(void) const;

		void setVelocityIterations(unsigned iterations);

		unsigned getVelocityIterations(void) const;

		void setPositionEpsilon(real value);

		real getPositionEpsilon(void) const;

		void setVelocityEpsilon(real value);

		real getVelocityEpsilon(void) const;

	public:
		ContactResolver(
			unsigned _positionIterations = 0,
			unsigned _velocityIterations = 0,
			real _positionEpsilon = 0.01f,
			real _velocityEpsilon = 0.01f);

	protected:
		void prepareContacts(
			Contact * contacts,
			unsigned numContacts,
			real duration);

		//void _updateContactPenetration(
		//	Contact & contact,
		//	const t3d::Vec4<real> & relativeContactPosition,
		//	const t3d::Vec4<real> & linearChange,
		//	const t3d::Vec4<real> & angularChange,
		//	unsigned bodyIndex);

		void adjustPositions(
			Contact * contacts,
			unsigned numContacts,
			real duration);

		//void _updateContactVelocity(
		//	Contact & contact,
		//	const t3d::Vec4<real> & relativeContactPosition,
		//	const t3d::Vec4<real> & velocityChange,
		//	const t3d::Vec4<real> & rotationChange,
		//	real duration);

		void adjustVelocities(
			Contact * contacts,
			unsigned numContacts,
			real duration);

	public:
		void resolveContacts(
			Contact * contacts,
			unsigned numContacts,
			real duration);
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// World
	// /////////////////////////////////////////////////////////////////////////////////////

	typedef std::vector<RigidBodyPtr> RigidBodyPtrList;

	class World
	{
	protected:
		RigidBodyPtrList bodyList;

		ForceRegistry registry;

		ContactList contactList;

		unsigned maxContacts;

		ContactResolver resolver;

	public:
		World(unsigned _maxContacts = 256);

		virtual ~World(void);

		virtual void startFrame(void);

		virtual void integrate(real duration);

		virtual unsigned generateContacts(Contact * contacts, unsigned limits) = 0;

		void runPhysics(real duration);
	};

	typedef boost::shared_ptr<World> WorldPtr;
}

#endif // __MYPHYSICS_H__
