
#ifndef __MYCOLLISION_H__
#define __MYCOLLISION_H__

#include "myCommon.h"
#include <vector>
#include "myMath.h"
#include "myPhysics.h"

namespace my
{
	// /////////////////////////////////////////////////////////////////////////////////////
	// BoundingSphere
	// /////////////////////////////////////////////////////////////////////////////////////

	class BoundingSphere
	{
	protected:
		t3d::Vec4<real> center;

		real radius;

	public:
		const t3d::Vec4<real> & getCenter(void) const;

		void setCenter(const t3d::Vec4<real> & _center);

		const real getRadius(void) const;

		void setRadius(real _radius);

	public:
		BoundingSphere(const t3d::Vec4<real> & _center, real _radius);

		bool overlaps(const BoundingSphere & other) const;

		real getGrowth(const BoundingSphere & other) const;

		real getVolumn(void) const;
	};

	BoundingSphere buildBoundingSphere(const BoundingSphere & lhs, const BoundingSphere & rhs);

	// /////////////////////////////////////////////////////////////////////////////////////
	// PotentialContact
	// /////////////////////////////////////////////////////////////////////////////////////

	class RigidBody;

	struct PotentialContact
	{
		RigidBody * body0;

		RigidBody * body1;
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// BVHNode
	// /////////////////////////////////////////////////////////////////////////////////////

	template <class BoundingVolumeClass>
	class BVHNode
	{
	protected:
		class BoundingVolumeLt
		{
		protected:
			BoundingVolumeClass volume;

		public:
			BoundingVolumeLt(const BoundingVolumeClass & _volume)
				: volume(_volume)
			{
			}

			bool operator () (const BVHNode<BoundingVolumeClass> & lhs, const BVHNode<BoundingVolumeClass> & rhs)
			{
				return lhs.volume.getGrowth(volume) < rhs.volume.getGrowth(volume);
			}
		};

	protected:
		typedef std::vector<BVHNode<BoundingVolumeClass> > BVHNodeList;

		BVHNodeList childs;

		BoundingVolumeClass volume;

		RigidBody * body;

	protected:
		bool overlaps(const BVHNode<BoundingVolumeClass> & other) const;

		unsigned getPotentialContactsWith(const BVHNode<BoundingVolumeClass> & other, PotentialContact * contacts, unsigned limit) const;

		void recalculateBoundingVolume(void);

	public:
		BVHNode(const BoundingVolumeClass & _volume, RigidBody * _body = NULL);

		bool isLeaf(void) const;

		unsigned getPotentialContacts(PotentialContact * contacts, unsigned limit) const;

		void insert(RigidBody * _body, const BoundingVolumeClass & _volume);
	};

	template <class BoundingVolumeClass>
	bool BVHNode<BoundingVolumeClass>::overlaps(const BVHNode<BoundingVolumeClass> & other) const
	{
		return volume.overlap(other.volume);
	}

	template <class BoundingVolumeClass>
	unsigned BVHNode<BoundingVolumeClass>::getPotentialContactsWith(const BVHNode<BoundingVolumeClass> & other, PotentialContact * contacts, unsigned limit) const
	{
		if(limit > 0)
		{
			if(overlaps(other))
			{
				if(isLeaf())
				{
					if(other.isLeaf())
					{
						contacts[0].body0 = body;
						contacts[0].body1 = other.body;
						return 1;
					}

					return other.getPotentialContactsWith(*this, contants, limit);
				}

				unsigned nret = 0;
				BVHNodeList::constant_iterator child_iter = childs.begin();
				for(; child_iter != childs.end(); child_iter++)
				{
					nret += child_iter->getPotentialContactsWith(other, &contacts[nret], limit - nret);
				}
				return nret;
			}
		}
		return 0;
	}

	template <class BoundingVolumeClass>
	void BVHNode<BoundingVolumeClass>::recalculateBoundingVolume(void)
	{
		assert(!childs.empty());

		BVHNodeList::const_iterator child_iter = childs.begin();
		volume = child_iter->volume;
		child_iter++;
		for(; child_iter != childs.end(); child_iter++)
		{
			volume = buildBoundingSphere(volume, child_iter->volume);
		}
	}

	template <class BoundingVolumeClass>
	BVHNode<BoundingVolumeClass>::BVHNode(const BoundingVolumeClass & _volume, RigidBody * _body = NULL)
		: volume(_volume)
		, body(_body)
	{
	}

	template <class BoundingVolumeClass>
	bool BVHNode<BoundingVolumeClass>::isLeaf(void) const
	{
		if(NULL == body)
		{
			assert(childs.empty());

			return true;
		}

		assert(!childs.empty());

		return false;
	}

	template <class BoundingVolumeClass>
	unsigned BVHNode<BoundingVolumeClass>::getPotentialContacts(PotentialContact * contacts, unsigned limit) const
	{
		if(limit > 0)
		{
			if(!isLeaf())
			{
				unsigned nret = 0;
				BVHNodeList::constant_iterator child_iter = childs.begin();
				for(; child_iter != childs.end(); child_iter++)
				{
					BVHNodeList::constant_iterator other_child_iter = child_iter + 1;
					for(; other_child_iter != childs.end(); other_child_iter++)
					{
						nret += child_iter->getPotentialContactsWith(*other_child_iter, &contacts[nret], limit - nret);
					}
				}
				return nret;
			}
		}
		return 0;
	}

	template <class BoundingVolumeClass>
	void BVHNode<BoundingVolumeClass>::insert(RigidBody * _body, const BoundingVolumeClass & _volume)
	{
		if(isLeaf())
		{
			childs.push_back(BVHNode<BoundingVolumeClass>(volume, body));

			childs.push_back(BVHNode<BoundingVolumeClass>(_volume, _body));

			body = NULL;
		}
		else
		{
			BVHNodeList::iterator child_iter = std::min_element(childs.begin(), childs.end(), BoundingVolumeLt(_volume));

			child_iter->insert(_body, _volume);
		}

		recalculateBoundingVolume();
	}

	// /////////////////////////////////////////////////////////////////////////////////////
	// CollisionPrimitive
	// /////////////////////////////////////////////////////////////////////////////////////

	class CollisionPrimitive
	{
		friend class IntersectionTests;

	//protected:
	public:
		RigidBody * body;

		t3d::Mat4<real> offset;

		t3d::Mat4<real> rotationOffset;

		t3d::Mat4<real> transform;

		t3d::Mat4<real> rotationTransform;

	public:
		virtual ~CollisionPrimitive(void);

	public:
		virtual void calculateInternals(void);

		t3d::Vec4<real> getAxis0(void) const;

		t3d::Vec4<real> getAxis1(void) const;

		t3d::Vec4<real> getAxis2(void) const;

		t3d::Vec4<real> getAxis3(void) const;

		t3d::Vec4<real> getAxis(size_t axis_i) const;

		const t3d::Mat4<real> & getTransform(void) const;

		t3d::Mat4<real> getInverseTransform(void) const;

		const t3d::Mat4<real> & getRotationTransform(void) const;

		t3d::Mat4<real> getInverseRotationTransform(void) const;
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// CollisionSphere
	// /////////////////////////////////////////////////////////////////////////////////////

	class CollisionSphere : public CollisionPrimitive
	{
	public:
		real radius;
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// CollisionBox
	// /////////////////////////////////////////////////////////////////////////////////////

	class CollisionBox : public CollisionPrimitive
	{
	public:
		t3d::Vec4<real> halfSize;
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// CollisionPlane
	// /////////////////////////////////////////////////////////////////////////////////////

	class CollisionPlane //: public CollisionPrimitive
	{
	public:
		t3d::Vec4<real> direction;

		real distance;
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// IntersectionTests
	// /////////////////////////////////////////////////////////////////////////////////////

	class IntersectionTests
	{
	public:
		static bool sphereAndHalfSpace(
			const CollisionSphere & sphere,
			const CollisionPlane & plane);

		static bool sphereAndSphere(
			const CollisionSphere & sphere0,
			const CollisionSphere & sphere1);

		static bool boxAndHalfSpace(
			const CollisionBox & box,
			const CollisionPlane & plane);

		static bool boxAndBox(
			const CollisionBox & box0,
			const CollisionBox & box1);

		static std::pair<bool, real> rayAndHalfTriangle(
			const t3d::Vec4<real> & pos,
			const t3d::Vec4<real> & dir,
			real radius,
			const t3d::Vec4<real> & v0,
			const t3d::Vec4<real> & v1,
			const t3d::Vec4<real> & v2);
	};

	// /////////////////////////////////////////////////////////////////////////////////////
	// CollisionDetector
	// /////////////////////////////////////////////////////////////////////////////////////

	class Contact;

	typedef std::vector<Contact> ContactList;

	class CollisionDetector
	{
	public:
		static unsigned sphereAndHalfSpace(
			const CollisionSphere & sphere,
			const CollisionPlane & plane,
			Contact * contacts,
			unsigned limits);

		static unsigned sphereAndTruePlane(
			const CollisionSphere & sphere,
			const CollisionPlane & plane,
			Contact * contacts,
			unsigned limits);

		static unsigned sphereAndPoint(
			const CollisionSphere & sphere,
			const t3d::Vec4<real> & point,
			RigidBody * bodyForPoint,
			Contact * contacts,
			unsigned limits);

		static unsigned sphereAndLine(
			const CollisionSphere & sphere,
			const t3d::Vec4<real> & v0,
			const t3d::Vec4<real> & v1,
			RigidBody * bodyForLine,
			Contact * contacts,
			unsigned limits);

		static unsigned sphereAndTriangle(
			const CollisionSphere & sphere,
			const t3d::Vec4<real> & v0,
			const t3d::Vec4<real> & v1,
			const t3d::Vec4<real> & v2,
			RigidBody * bodyForTriangle,
			Contact * contacts,
			unsigned limits);

		static unsigned sphereAndSphere(
			const CollisionSphere & sphere0,
			const CollisionSphere & sphere1,
			Contact * contacts,
			unsigned limits);

		static unsigned pointAndHalfSpace(
			const t3d::Vec4<real> & point,
			RigidBody * bodyForPoint,
			const CollisionPlane & plane,
			Contact * contacts,
			unsigned limits);

		static unsigned boxAndHalfSpace(
			const CollisionBox & box,
			const CollisionPlane & plane,
			Contact * contacts,
			unsigned limits);

		static unsigned boxAndSphere(
			const CollisionBox & box,
			const CollisionSphere & sphere,
			Contact * contacts,
			unsigned limits);

		static unsigned boxAndPointAways(
			const CollisionBox & box,
			const t3d::Vec4<real> & point,
			RigidBody * bodyForPoint,
			Contact * contacts,
			unsigned limits);

		static unsigned boxAndBox(
			const CollisionBox & box0,
			const CollisionBox & box1,
			Contact * contacts,
			unsigned limits);

		//static unsigned boxAndTriangle(
		//	const CollisionBox & box,
		//	const t3d::Vec4<real> & v0,
		//	const t3d::Vec4<real> & v1,
		//	const t3d::Vec4<real> & v2,
		//	RigidBody * bodyForTriangle,
		//	Contact * contacts,
		//	unsigned limits);
	};
}

#endif // __MYCOLLISION_H__
