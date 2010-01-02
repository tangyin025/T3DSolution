
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
		inline Mat4
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

		inline Mat4(const t3d::Mat4<elem_t> & other)
			: t3d::Mat4<elem_t>(other)
		{
		}

		inline Mat4(void)
			: t3d::Mat4<elem_t>(my::Mat4<elem_t>::IDENTITY)
		{
		}

	public:
		friend inline std::basic_ostream<charT> & operator << (std::basic_ostream<charT> & ostr, const Mat4 & rhs)
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
		inline Vec2(const elem_t _x, const elem_t _y)
			: t3d::Vec2<elem_t>(_x, _y)
		{
		}

		inline Vec2(const t3d::Vec2<elem_t> & other)
			: t3d::Vec2<elem_t>(other)
		{
		}

		inline Vec2(void)
			: t3d::Vec2<elem_t>(my::Vec2<elem_t>::ZERO)
		{
		}

	public:
		friend inline std::basic_ostream<charT> & operator << (std::basic_ostream<charT> & ostr, const Vec2 & rhs)
		{
			return ostr << rhs.x << _T(", ") << rhs.y;
		}

		inline std::basic_string<charT> str(void) const
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
		inline Vec4(const elem_t _x, const elem_t _y, const elem_t _z = 0, const elem_t _w = 1)
			: t3d::Vec4<elem_t>(_x, _y, _z, _w)
		{
		}

		inline Vec4(const t3d::Vec4<elem_t> & other)
			: t3d::Vec4<elem_t>(other)
		{
		}

		inline Vec4()
			: t3d::Vec4<elem_t>(my::Vec4<elem_t>::ZERO)
		{
		}

	public:
		friend inline std::basic_ostream<charT> & operator << (std::basic_ostream<charT> & ostr, const Vec4 & rhs)
		{
			return ostr << rhs.x << _T(", ") << rhs.y << _T(", ") << rhs.z << _T(", ") << rhs.w;
		}

		inline std::basic_string<charT> str(void) const
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
		inline Quat(elem_t w, elem_t x, elem_t y, elem_t z)
			: t3d::Quat<elem_t>(w, x, y, z)
		{
		}

		inline Quat(void)
			: t3d::Quat<elem_t>(my::Quat<elem_t>::IDENTITY)
		{
		}

	public:
		friend inline std::basic_ostream<charT> & operator << (std::basic_ostream<charT> & ostr, const Quat & rhs)
		{
			return ostr << rhs.w << _T(", ") << rhs.x << _T(", ") << rhs.y << _T(", ") << rhs.z;
		}

		inline std::basic_string<charT> str(void) const
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
		inline Color(real r, real g, real b, real a = 1)
			: my::Vec4<real>(r, g, b, a)
		{
		}

		inline Color(void)
			: my::Vec4<real>(my::Color::BLACK)
		{
		}
	};

	template <typename elem_t>
	inline elem_t calculateBoxVolume(elem_t width, elem_t height, elem_t deepth)
	{
		return width * height * deepth;
	}

	template <typename elem_t>
	inline elem_t calculateBoxMass(elem_t width, elem_t height, elem_t deepth, elem_t density)
	{
		return calculateBoxVolume(width, height, deepth) * density;
	}

	template <typename elem_t>
	inline elem_t calculateSphereVolume(elem_t radius)
	{
		return (elem_t)4 / (elem_t)3 * (elem_t)PI * radius * radius * radius;
	}

	template <typename elem_t>
	inline elem_t calculateSphereMass(elem_t radius, elem_t density)
	{
		return calculateSphereVolume(radius) * density;
	}

	template <typename elem_t>
	inline t3d::Mat4<elem_t> calculateInertiaTensor(elem_t Ixx, elem_t Iyy, elem_t Izz, elem_t Ixy = 0, elem_t Ixz = 0, elem_t Iyz = 0)
	{
		return t3d::Mat4<elem_t>(
			 Ixx,			-Ixy,			-Ixz,			0,
			-Ixy,			 Iyy,			-Iyz,			0,
			-Ixz,			-Iyz,			 Izz,			0,
			0,				0,				0,				1);
	}

	template <typename elem_t>
	inline t3d::Mat4<elem_t> calculateBlockInertiaTensor(const t3d::Vec4<elem_t> & halfSizes, elem_t mass)
	{
		Vec4<elem_t> squares = vec3Mul(halfSizes, halfSizes);

		return calculateInertiaTensor(
			0.3f * mass * (squares.y + squares.z),
			0.3f * mass * (squares.x + squares.z),
			0.3f * mass * (squares.x + squares.y));
	}

	template <typename elem_t>
	inline elem_t calculatePointPlaneDistance(
		const t3d::Vec4<elem_t> & point,
		const t3d::Vec4<elem_t> & planeNormal,
		elem_t planeDistance)
	{
		assert(t3d::vec3IsNormalized(planeNormal));

		return t3d::vec3Dot(point, planeNormal) - planeDistance;
	}

	template <typename elem_t>
	inline elem_t calculatePointPlaneDistance(
		const t3d::Vec4<elem_t> & point,
		const t3d::Vec4<elem_t> & planePoint,
		const t3d::Vec4<elem_t> & planeNormal)
	{
		assert(t3d::vec3IsNormalized(planeNormal));

		return t3d::vec3Dot(t3d::vec3Sub(point, planePoint), planeNormal);
	}

	template <typename elem_t>
	inline elem_t calculatePointPlanePerpendicularPoint(
		const t3d::Vec4<elem_t> & point,
		const t3d::Vec4<elem_t> & planePoint,
		const t3d::Vec4<elem_t> & planeNormal)
	{
		assert(t3d::vec3IsNormalized(planeNormal));

		return t3d::vec3Sub(point, t3d::vec3Mul(planeNormal, calculatePointPlaneDistance(point, planePoint, planeNormal)));
	}

	template <typename elem_t>
	inline elem_t calculateLinePlaneIntersection(
		const t3d::Vec4<elem_t> & linePoint,
		const t3d::Vec4<elem_t> & lineDirection,
		const t3d::Vec4<elem_t> & planePoint,
		const t3d::Vec4<elem_t> & planeNormal)
	{
		assert(t3d::vec3IsNormalized(planeNormal));

		assert(!IS_ZERO_FLOAT(t3d::vec3Dot(lineDirection, planeNormal)));

		return -(t3d::vec3Dot(linePoint, planeNormal) - t3d::vec3Dot(planePoint, planeNormal)) / t3d::vec3Dot(lineDirection, planeNormal);
	}

	template <typename elem_t>
	inline t3d::Vec4<elem_t> calculateLinePlaneIntersectionPoint(
		const t3d::Vec4<elem_t> & linePoint,
		const t3d::Vec4<elem_t> & lineDirection,
		const t3d::Vec4<elem_t> & planePoint,
		const t3d::Vec4<elem_t> & planeNormal)
	{
		elem_t intersection = calculateLinePlaneIntersection(linePoint, lineDirection, planePoint, planeNormal);

		return t3d::vec3Add(linePoint, t3d::vec3Mul(lineDirection, intersection));
	}

	template <typename elem_t>
	inline t3d::Vec4<elem_t> calculateTriangleDirection(
		const t3d::Vec4<elem_t> & v0,
		const t3d::Vec4<elem_t> & v1,
		const t3d::Vec4<elem_t> & v2)
	{
		return t3d::vec3Cross(t3d::vec3Sub(v1, v0), t3d::vec3Sub(v2, v0));
	}

	template <typename elem_t>
	inline bool isValidTriangle(
		const t3d::Vec4<elem_t> & v0,
		const t3d::Vec4<elem_t> & v1,
		const t3d::Vec4<elem_t> & v2)
	{
		return !IS_ZERO_FLOAT(t3d::vec3Length(calculateTriangleDirection(v0, v1, v2)));
	}

	template <typename elem_t>
	inline t3d::Vec4<elem_t> calculateTriangleNormal(
		const t3d::Vec4<elem_t> & v0,
		const t3d::Vec4<elem_t> & v1,
		const t3d::Vec4<elem_t> & v2)
	{
		assert(isValidTriangle(v0, v1, v2));

		return t3d::vec3Normalize(calculateTriangleDirection(v0, v1, v2));
	}

	template <typename elem_t>
	inline elem_t isInsideTriangle(
		const t3d::Vec4<elem_t> & point,
		const t3d::Vec4<elem_t> & v0,
		const t3d::Vec4<elem_t> & v1,
		const t3d::Vec4<elem_t> & v2)
	{
		assert(isValidTriangle(v0, v1, v2));

		t3d::Vec4<elem_t> planeDir = calculateTriangleDirection(v0, v1, v2);

		return t3d::vec3Dot(planeDir, calculateTriangleDirection(point, v0, v1)) >= 0
			&& t3d::vec3Dot(planeDir, calculateTriangleDirection(point, v1, v2)) >= 0
			&& t3d::vec3Dot(planeDir, calculateTriangleDirection(point, v2, v0)) >= 0;
	}
}

#endif // __MYMATH_H__
