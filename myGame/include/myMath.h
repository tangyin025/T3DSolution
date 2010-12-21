
#ifndef __MYMATH_H__
#define __MYMATH_H__

#include "myCommon.h"
#include <t3dlib4.h>

namespace my
{
	template <typename elem_t>
	class Mat4 : public t3d::Mat4<elem_t>
	{
	public:
		static const Mat4 ZERO;

		static const Mat4 IDENTITY;

	public:
		Mat4
			( const elem_t _m00, const elem_t _m01, const elem_t _m02, const elem_t _m03
			, const elem_t _m10, const elem_t _m11, const elem_t _m12, const elem_t _m13
			, const elem_t _m20, const elem_t _m21, const elem_t _m22, const elem_t _m23
			, const elem_t _m30, const elem_t _m31, const elem_t _m32, const elem_t _m33
			)
			: t3d::Mat4<elem_t>(
				_m00, _m01, _m02, _m03,
				_m10, _m11, _m12, _m13,
				_m20, _m21, _m22, _m23,
				_m30, _m31, _m32, _m33)
		{
		}

		Mat4(const t3d::Mat4<elem_t> & other)
			: t3d::Mat4<elem_t>(other)
		{
		}

		Mat4(void)
			: t3d::Mat4<elem_t>(my::Mat4<elem_t>::IDENTITY)
		{
		}

	public:
		friend std::basic_ostream<charT> & operator << (std::basic_ostream<charT> & ostr, const Mat4 & rhs)
		{
			ostr << rhs.m00 << _T(", ") << rhs.m01 << _T(", ") << rhs.m02 << _T(", ") << rhs.m03 << std::endl;
			ostr << rhs.m10 << _T(", ") << rhs.m11 << _T(", ") << rhs.m12 << _T(", ") << rhs.m13 << std::endl;
			ostr << rhs.m20 << _T(", ") << rhs.m21 << _T(", ") << rhs.m22 << _T(", ") << rhs.m23 << std::endl;
			ostr << rhs.m30 << _T(", ") << rhs.m31 << _T(", ") << rhs.m32 << _T(", ") << rhs.m33; // << std::endl;
			return ostr;
		}
	};

	template <typename elem_t>
	class Vec2 : public t3d::Vec2<elem_t>
	{
	public:
		static const Vec2 ZERO;

		static const Vec2 UNIT_X;

		static const Vec2 UNIT_Y;

		static const Vec2 NEGATIVE_UNIT_X;

		static const Vec2 NEGATIVE_UNIT_Y;

		static const Vec2 UNIT_SCALE;

	public:
		Vec2(const elem_t _x, const elem_t _y)
			: t3d::Vec2<elem_t>(_x, _y)
		{
		}

		Vec2(const t3d::Vec2<elem_t> & other)
			: t3d::Vec2<elem_t>(other)
		{
		}

		Vec2(void)
			: t3d::Vec2<elem_t>(my::Vec2<elem_t>::ZERO)
		{
		}

	public:
		friend std::basic_ostream<charT> & operator << (std::basic_ostream<charT> & ostr, const Vec2 & rhs)
		{
			return ostr << rhs.x << _T(", ") << rhs.y;
		}

		std::basic_string<charT> str(void) const
		{
			std::basic_ostringstream<charT> osstr;
			osstr << *this;
			return osstr.str();
		}
	};

	template <typename elem_t>
	class Vec4 : public t3d::Vec4<elem_t>
	{
	public:
		static const Vec4 ZERO;

		static const Vec4 UNIT_X;

		static const Vec4 UNIT_Y;

		static const Vec4 UNIT_Z;

		//static const Vec4 UNIT_W;

		static const Vec4 UNIT_SCALE;

		static const Vec4 NEGATIVE_UNIT_X;

		static const Vec4 NEGATIVE_UNIT_Y;

		static const Vec4 NEGATIVE_UNIT_Z;

		//static const Vec4 NEGATIVE_UNIT_W;

		static const Vec4 NEGATIVE_UNIT_SCALE;

	public:
		Vec4(const elem_t _x, const elem_t _y, const elem_t _z = 0, const elem_t _w = 1)
			: t3d::Vec4<elem_t>(_x, _y, _z, _w)
		{
		}

		Vec4(const t3d::Vec4<elem_t> & other)
			: t3d::Vec4<elem_t>(other)
		{
		}

		Vec4()
			: t3d::Vec4<elem_t>(my::Vec4<elem_t>::ZERO)
		{
		}

	public:
		friend std::basic_ostream<charT> & operator << (std::basic_ostream<charT> & ostr, const Vec4 & rhs)
		{
			return ostr << rhs.x << _T(", ") << rhs.y << _T(", ") << rhs.z << _T(", ") << rhs.w;
		}

		std::basic_string<charT> str(void) const
		{
			std::basic_ostringstream<charT> osstr;
			osstr << *this;
			return osstr.str();
		}
	};

	template <typename elem_t>
	class Quat : public t3d::Quat<elem_t>
	{
	public:
		static const Quat ZERO;

		static const Quat IDENTITY;

	public:
		Quat(elem_t w, elem_t x, elem_t y, elem_t z)
			: t3d::Quat<elem_t>(w, x, y, z)
		{
		}

		Quat(void)
			: t3d::Quat<elem_t>(my::Quat<elem_t>::IDENTITY)
		{
		}

	public:
		friend std::basic_ostream<charT> & operator << (std::basic_ostream<charT> & ostr, const Quat & rhs)
		{
			return ostr << rhs.w << _T(", ") << rhs.x << _T(", ") << rhs.y << _T(", ") << rhs.z;
		}

		std::basic_string<charT> str(void) const
		{
			std::basic_ostringstream<charT> osstr;
			osstr << *this;
			return osstr.str();
		}
	};

	class Color : public my::Vec4<real>
	{
	public:
		static const Color WHITE;

		static const Color RED;

		static const Color GREEN;

		static const Color BLUE;

		static const Color BLACK;

		static const Color YELLOW;

	public:
		Color(real r, real g, real b, real a = 1)
			: my::Vec4<real>(r, g, b, a)
		{
		}

		Color(void)
			: my::Vec4<real>(my::Color::BLACK)
		{
		}
	};

	inline real calculateBoxVolume(real width, real height, real deepth)
	{
		return width * height * deepth;
	}

	inline real calculateBoxMass(real width, real height, real deepth, real density)
	{
		return calculateBoxVolume(width, height, deepth) * density;
	}

	inline real calculateSphereVolume(real radius)
	{
		return (real)4 / (real)3 * (real)PI * radius * radius * radius;
	}

	inline real calculateSphereMass(real radius, real density)
	{
		return calculateSphereVolume(radius) * density;
	}

	inline t3d::Mat4<real> calculateInertiaTensor(real Ixx, real Iyy, real Izz, real Ixy = 0, real Ixz = 0, real Iyz = 0)
	{
		return t3d::Mat4<real>(
			 Ixx,			-Ixy,			-Ixz,			0,
			-Ixy,			 Iyy,			-Iyz,			0,
			-Ixz,			-Iyz,			 Izz,			0,
			0,				0,				0,				1);
	}

	inline t3d::Mat4<real> calculateSphereInertiaTensor(real radius, real mass)
	{
		real coeff = 0.4f * mass * radius * radius;

		return calculateInertiaTensor(coeff, coeff, coeff);
	}

	inline t3d::Mat4<real> calculateBlockInertiaTensor(const t3d::Vec4<real> & halfSizes, real mass)
	{
		Vec4<real> squares = vec3Mul(halfSizes, halfSizes);

		return calculateInertiaTensor(
			0.3f * mass * (squares.y + squares.z),
			0.3f * mass * (squares.x + squares.z),
			0.3f * mass * (squares.x + squares.y));
	}

	inline real calculatePointPlaneDistance(
		const t3d::Vec4<real> & point,
		const t3d::Vec4<real> & planeNormal,
		real planeDistance)
	{
		_ASSERT(t3d::vec3IsNormalized(planeNormal));

		return t3d::vec3Dot(point, planeNormal) - planeDistance;
	}

	inline real calculatePointPlaneDistance(
		const t3d::Vec4<real> & point,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		_ASSERT(t3d::vec3IsNormalized(planeNormal));

		return t3d::vec3Dot(t3d::vec3Sub(point, planePoint), planeNormal);
	}

	inline t3d::Vec4<real> calculatePointPlanePerpendicularPoint(
		const t3d::Vec4<real> & point,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		_ASSERT(t3d::vec3IsNormalized(planeNormal));

		return t3d::vec3Sub(point, t3d::vec3Mul(planeNormal, calculatePointPlaneDistance(point, planePoint, planeNormal)));
	}

	inline real calculateLinePlaneIntersection(
		const t3d::Vec4<real> & linePoint,
		const t3d::Vec4<real> & lineDirection,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		_ASSERT(t3d::vec3IsNormalized(planeNormal));

		_ASSERT(!IS_ZERO_FLOAT(t3d::vec3Dot(lineDirection, planeNormal)));

		return -(t3d::vec3Dot(linePoint, planeNormal) - t3d::vec3Dot(planePoint, planeNormal)) / t3d::vec3Dot(lineDirection, planeNormal);
	}

	inline t3d::Vec4<real> calculateLinePlaneIntersectionPoint(
		const t3d::Vec4<real> & linePoint,
		const t3d::Vec4<real> & lineDirection,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		real intersection = calculateLinePlaneIntersection(linePoint, lineDirection, planePoint, planeNormal);

		return t3d::vec3Add(linePoint, t3d::vec3Mul(lineDirection, intersection));
	}

	inline t3d::Vec4<real> calculateTriangleDirection(
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2)
	{
		return t3d::vec3Cross(t3d::vec3Sub(v1, v0), t3d::vec3Sub(v2, v0));
	}

	inline bool isValidTriangle(
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2)
	{
		return !IS_ZERO_FLOAT(t3d::vec3Length(calculateTriangleDirection(v0, v1, v2)));
	}

	inline t3d::Vec4<real> calculateTriangleNormal(
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2)
	{
		_ASSERT(isValidTriangle(v0, v1, v2));

		return t3d::vec3Normalize(calculateTriangleDirection(v0, v1, v2));
	}

	inline real isInsideTriangle(
		const t3d::Vec4<real> & point,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2)
	{
		_ASSERT(isValidTriangle(v0, v1, v2));

		t3d::Vec4<real> planeDir = calculateTriangleDirection(v0, v1, v2);

		return t3d::vec3Dot(planeDir, calculateTriangleDirection(point, v0, v1)) >= 0
			&& t3d::vec3Dot(planeDir, calculateTriangleDirection(point, v1, v2)) >= 0
			&& t3d::vec3Dot(planeDir, calculateTriangleDirection(point, v2, v0)) >= 0;
	}

	void splitTriangleVertexUp(
		t3d::VertexList & lVertexList,
		t3d::VertexList & rVertexList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexDown(
		t3d::VertexList & lVertexList,
		t3d::VertexList & rVertexList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexLeft(
		t3d::VertexList & lVertexList,
		t3d::VertexList & rVertexList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexRight(
		t3d::VertexList & lVertexList,
		t3d::VertexList & rVertexList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	bool splitTriangleVertex(
		t3d::VertexList & lVertexList,
		t3d::VertexList & rVertexList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexNormalUp(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexNormalDown(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexNormalLeft(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexNormalRight(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	bool splitTriangleVertexNormal(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexUVUp(
		t3d::VertexList & lVertexList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexUVDown(
		t3d::VertexList & lVertexList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexUVLeft(
		t3d::VertexList & lVertexList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexUVRight(
		t3d::VertexList & lVertexList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	bool splitTriangleVertexUV(
		t3d::VertexList & lVertexList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexNormalUVUp(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexNormalUVDown(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexNormalUVLeft(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexNormalUVRight(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	bool splitTriangleVertexNormalUV(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);
}

#endif // __MYMATH_H__
