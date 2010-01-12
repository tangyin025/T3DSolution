
#ifndef __T3DLIB4_H__
#define __T3DLIB4_H__

#include "t3dcommon.h"
#include <cassert>
#include <cmath>
#include <iostream>

#define IR(f)				((t3d::uint32 &)(f))
#define IS_NAN(f)			((IR(f) & 0x7f800000) == 0x7f800000)
#define IS_INDETERMINATE(f)	(IR(f) == 0xffc00000)
#define IS_PLUS_INF(f)		(IR(f) == 0x7f800000)
#define IS_MINUS_INF(f)		(IR(f) == 0xff800000)
#define IS_VALID_FLOAT(f)	(!IS_NAN(f) && !IS_INDETERMINATE(f) && !IS_PLUS_INF(f) && !IS_MINUS_INF(f))

#define IS_ZERO_FLOAT(f)	(abs(f) < REAL_ZERO_LIMIT) // -1.1102230246251565e-016

#define PI					(3.1415926535897932384626433832795)

#define DEG_TO_RAD(deg)		(((deg) / (t3d::real)180.0) * (t3d::real)PI)
#define RAD_TO_DEG(rad)		(((rad) / (t3d::real)PI) * (t3d::real)180.0)

#define LINE2D_INTERSECT(ca, a0, a1, b0, b1)	((b0) + ((b1) - (b0)) * ((ca) - (a0)) / ((a1) - (a0)))

namespace t3d
{
	//inline long _ftoi(double dval)
	//{
	//	// seee,eeee,eeee,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm
	//	return *(int *)&(dval += 1.5 * (1LL << 52));
	//}

	//inline long _ftoi(float fval)
	//{
	//	// seee,eeee,emmm,mmmm,mmmm,mmmm,mmmm,mmmm
	//	return *(int *)&(fval += 1.5 * (1LL << 23)) << 10 >> 10;
	//}

	//inline fixp16 _ftofixp16(double dval)
	//{
	//	// seee,eeee,eeee,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm
	//	return *(fixp16 *)&(dval += 1.5 * (1LL << (52 - 16)));
	//}

	//inline fixp16 _ftofixp16(float fval)
	//{
	//	// seee,eeee,emmm,mmmm,mmmm,mmmm,mmmm,mmmm
	//	return *(fixp16 *)&(fval += 1.5 * (1LL << (23 - 6))) << 10;
	//}

	//inline fixp28 _ftofixp28(double dval)
	//{
	//	// seee,eeee,eeee,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm,mmmm
	//	return *(fixp28 *)&(dval += 1.5 * (1LL << (52 - 28)));
	//}

	//inline fixp28 _ftofixp28(float fval)
	//{
	//	// seee,eeee,emmm,mmmm,mmmm,mmmm,mmmm,mmmm
	//	return *(fixp28 *)&(fval += 1.5 * (1LL << (23 - 18))) << 10;
	//}
#pragma warning(disable: 4201)
	template <typename elem_t>
	class Mat4
	{
	public:
		union
		{
			/*__declspec(align(16))*/ elem_t _M[4 * 4];

			struct
			{
				elem_t m00, m10, m20, m30;
				elem_t m01, m11, m21, m31;
				elem_t m02, m12, m22, m32;
				elem_t m03, m13, m23, m33;
			};
		};

	public:
		inline Mat4(void)
		{
		}

		inline Mat4
			( const elem_t _m00, const elem_t _m01, const elem_t _m02, const elem_t _m03
			, const elem_t _m10, const elem_t _m11, const elem_t _m12, const elem_t _m13
			, const elem_t _m20, const elem_t _m21, const elem_t _m22, const elem_t _m23
			, const elem_t _m30, const elem_t _m31, const elem_t _m32, const elem_t _m33
			)
			: m00(_m00), m01(_m01), m02(_m02), m03(_m03)
			, m10(_m10), m11(_m11), m12(_m12), m13(_m13)
			, m20(_m20), m21(_m21), m22(_m22), m23(_m23)
			, m30(_m30), m31(_m31), m32(_m32), m33(_m33)
		{
		}

	public:
		inline Mat4 operator - (void) const
		{
			return Mat4(
				-m00, -m01, -m02, -m03,
				-m10, -m11, -m12, -m13,
				-m20, -m21, -m22, -m23,
				-m30, -m31, -m32, -m33);
		}

		inline bool operator == (const Mat4 & rhs) const
		{
			return m00 == rhs.m00 && m01 == rhs.m01 && m02 == rhs.m02 && m03 == rhs.m03
				&& m10 == rhs.m10 && m11 == rhs.m11 && m12 == rhs.m12 && m13 == rhs.m13
				&& m20 == rhs.m20 && m21 == rhs.m21 && m22 == rhs.m22 && m23 == rhs.m23
				&& m30 == rhs.m30 && m31 == rhs.m31 && m32 == rhs.m32 && m33 == rhs.m33;
		}

		inline Mat4 operator + (const Mat4 & rhs) const
		{
			return Mat4(
				m00 + rhs.m00, m01 + rhs.m01, m02 + rhs.m02, m03 + rhs.m03,
				m10 + rhs.m10, m11 + rhs.m11, m12 + rhs.m12, m13 + rhs.m13,
				m20 + rhs.m20, m21 + rhs.m21, m22 + rhs.m22, m23 + rhs.m23,
				m30 + rhs.m30, m31 + rhs.m31, m32 + rhs.m32, m33 + rhs.m33);
		}

		inline Mat4 operator + (elem_t scaler) const
		{
			return Mat4(
				m00 + scaler, m01 + scaler, m02 + scaler, m03 + scaler,
				m10 + scaler, m11 + scaler, m12 + scaler, m13 + scaler,
				m20 + scaler, m21 + scaler, m22 + scaler, m23 + scaler,
				m30 + scaler, m31 + scaler, m32 + scaler, m33 + scaler);
		}

		inline Mat4 & operator +=(const Mat4 & rhs)
		{
			m00 += rhs.m00; m01 += rhs.m01; m02 += rhs.m02; m03 += rhs.m03;
			m10 += rhs.m10; m11 += rhs.m11; m12 += rhs.m12; m13 += rhs.m13;
			m20 += rhs.m20; m21 += rhs.m21; m22 += rhs.m22; m23 += rhs.m23;
			m30 += rhs.m30; m31 += rhs.m31; m32 += rhs.m32; m33 += rhs.m33;
			return *this;
		}

		inline Mat4 & operator +=(elem_t scaler)
		{
			m00 += scaler; m01 += scaler; m02 += scaler; m03 += scaler;
			m10 += scaler; m11 += scaler; m12 += scaler; m13 += scaler;
			m20 += scaler; m21 += scaler; m22 += scaler; m23 += scaler;
			m30 += scaler; m31 += scaler; m32 += scaler; m33 += scaler;
			return *this;
		}

		inline Mat4 operator - (const Mat4 & rhs) const
		{
			return Mat4(
				m00 - rhs.m00, m01 - rhs.m01, m02 - rhs.m02, m03 - rhs.m03,
				m10 - rhs.m10, m11 - rhs.m11, m12 - rhs.m12, m13 - rhs.m13,
				m20 - rhs.m20, m21 - rhs.m21, m22 - rhs.m22, m23 - rhs.m23,
				m30 - rhs.m30, m31 - rhs.m31, m32 - rhs.m32, m33 - rhs.m33);
		}

		inline Mat4 operator - (elem_t scaler) const
		{
			return Mat4(
				m00 - scaler, m01 - scaler, m02 - scaler, m03 - scaler,
				m10 - scaler, m11 - scaler, m12 - scaler, m13 - scaler,
				m20 - scaler, m21 - scaler, m22 - scaler, m23 - scaler,
				m30 - scaler, m31 - scaler, m32 - scaler, m33 - scaler);
		}

		inline Mat4 & operator -=(const Mat4 & rhs)
		{
			m00 -= rhs.m00; m01 -= rhs.m01; m02 -= rhs.m02; m03 -= rhs.m03;
			m10 -= rhs.m10; m11 -= rhs.m11; m12 -= rhs.m12; m13 -= rhs.m13;
			m20 -= rhs.m20; m21 -= rhs.m21; m22 -= rhs.m22; m23 -= rhs.m23;
			m30 -= rhs.m30; m31 -= rhs.m31; m32 -= rhs.m32; m33 -= rhs.m33;
			return *this;
		}

		inline Mat4 & operator -=(elem_t scaler)
		{
			m00 -= scaler; m01 -= scaler; m02 -= scaler; m03 -= scaler;
			m10 -= scaler; m11 -= scaler; m12 -= scaler; m13 -= scaler;
			m20 -= scaler; m21 -= scaler; m22 -= scaler; m23 -= scaler;
			m30 -= scaler; m31 -= scaler; m32 -= scaler; m33 -= scaler;
			return *this;
		}

		inline Mat4 operator * (const Mat4 & rhs) const
		{
			return Mat4(
				m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20 + m03 * rhs.m30,
				m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21 + m03 * rhs.m31,
				m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22 + m03 * rhs.m32,
				m00 * rhs.m03 + m01 * rhs.m13 + m02 * rhs.m23 + m03 * rhs.m33,

				m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20 + m13 * rhs.m30,
				m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31,
				m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32,
				m10 * rhs.m03 + m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33,

				m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20 + m23 * rhs.m30,
				m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31,
				m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32,
				m20 * rhs.m03 + m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33,

				m30 * rhs.m00 + m31 * rhs.m10 + m32 * rhs.m20 + m33 * rhs.m30,
				m30 * rhs.m01 + m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31,
				m30 * rhs.m02 + m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32,
				m30 * rhs.m03 + m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33);
		}

		inline Mat4 operator * (elem_t scaler) const
		{
			return Mat4(
				m00 * scaler, m01 * scaler, m02 * scaler, m03 * scaler,
				m10 * scaler, m11 * scaler, m12 * scaler, m13 * scaler,
				m20 * scaler, m21 * scaler, m22 * scaler, m23 * scaler,
				m30 * scaler, m31 * scaler, m32 * scaler, m33 * scaler);
		}

		inline Mat4 & operator *=(const Mat4 & rhs)
		{
			return *this = *this * rhs;
		}

		inline Mat4 & operator *=(elem_t scaler)
		{
			m00 *= scaler; m01 *= scaler; m02 *= scaler; m03 *= scaler;
			m10 *= scaler; m11 *= scaler; m12 *= scaler; m13 *= scaler;
			m20 *= scaler; m21 *= scaler; m22 *= scaler; m23 *= scaler;
			m30 *= scaler; m31 *= scaler; m32 *= scaler; m33 *= scaler;
			return *this;
		}

		//inline Mat4 operator / (const Mat4 & rhs) const
		//{
		//	return *this * rhs.inverse();
		//}

		//inline Mat4 operator / (elem_t scaler) const
		//{
		//	return Mat4(
		//		m00 / scaler, m01 / scaler, m02 / scaler, m03 / scaler,
		//		m10 / scaler, m11 / scaler, m12 / scaler, m13 / scaler,
		//		m20 / scaler, m21 / scaler, m22 / scaler, m23 / scaler,
		//		m30 / scaler, m31 / scaler, m32 / scaler, m33 / scaler);
		//}

		//inline Mat4 & operator /=(const Mat4 & rhs)
		//{
		//	return *this = *this / rhs;
		//}

		//inline Mat4 & operator /=(elem_t scaler)
		//{
		//	m00 /= scaler; m01 /= scaler; m02 /= scaler; m03 /= scaler;
		//	m10 /= scaler; m11 /= scaler; m12 /= scaler; m13 /= scaler;
		//	m20 /= scaler; m21 /= scaler; m22 /= scaler; m23 /= scaler;
		//	m30 /= scaler; m31 /= scaler; m32 /= scaler; m33 /= scaler;
		//	return *this;
		//}

	public:
		inline elem_t a00(void) const
		{
			return m11 * m22 * m33
				 + m12 * m23 * m31
				 + m13 * m21 * m32
				 - m11 * m23 * m32
				 - m12 * m21 * m33
				 - m13 * m22 * m31;
		}

		inline elem_t a01(void) const
		{
			return m12 * m23 * m30
				 + m13 * m20 * m32
				 + m10 * m22 * m33
				 - m12 * m20 * m33
				 - m13 * m22 * m30
				 - m10 * m23 * m32;
		}

		inline elem_t a02(void) const
		{
			return m13 * m20 * m31
				 + m10 * m21 * m33
				 + m11 * m23 * m30
				 - m13 * m21 * m30
				 - m10 * m23 * m31
				 - m11 * m20 * m33;
		}

		inline elem_t a03(void) const
		{
			return m10 * m21 * m32
				 + m11 * m22 * m30
				 + m12 * m20 * m31
				 - m10 * m22 * m31
				 - m11 * m20 * m32
				 - m12 * m21 * m30;
		}

		inline elem_t a10(void) const
		{
			return m21 * m32 * m03
				 + m22 * m33 * m01
				 + m23 * m31 * m02
				 - m21 * m33 * m02
				 - m22 * m31 * m03
				 - m23 * m32 * m01;
		}

		inline elem_t a11(void) const
		{
			return m22 * m33 * m00
				 + m23 * m30 * m02
				 + m20 * m32 * m03
				 - m22 * m30 * m03
				 - m23 * m32 * m00
				 - m20 * m33 * m02;
		}

		inline elem_t a12(void) const
		{
			return m23 * m30 * m01
				 + m20 * m31 * m03
				 + m21 * m33 * m00
				 - m23 * m31 * m00
				 - m20 * m33 * m01
				 - m21 * m30 * m03;
		}

		inline elem_t a13(void) const
		{
			return m20 * m31 * m02
				 + m21 * m32 * m00
				 + m22 * m30 * m01
				 - m20 * m32 * m01
				 - m21 * m30 * m02
				 - m22 * m31 * m00;
		}

		inline elem_t a20(void) const
		{
			return m31 * m02 * m13
				 + m32 * m03 * m11
				 + m33 * m01 * m12
				 - m31 * m03 * m12
				 - m32 * m01 * m13
				 - m33 * m02 * m11;
		}

		inline elem_t a21(void) const
		{
			return m32 * m03 * m10
				 + m33 * m00 * m12
				 + m30 * m02 * m13
				 - m32 * m00 * m13
				 - m33 * m02 * m10
				 - m30 * m03 * m12;
		}

		inline elem_t a22(void) const
		{
			return m33 * m00 * m11
				 + m30 * m01 * m13
				 + m31 * m03 * m10
				 - m33 * m01 * m10
				 - m30 * m03 * m11
				 - m31 * m00 * m13;
		}

		inline elem_t a23(void) const
		{
			return m30 * m01 * m12
				 + m31 * m02 * m10
				 + m32 * m00 * m11
				 - m30 * m02 * m11
				 - m31 * m00 * m12
				 - m32 * m01 * m10;
		}

		inline elem_t a30(void) const
		{
			return m01 * m12 * m23
				 + m02 * m13 * m21
				 + m03 * m11 * m22
				 - m01 * m13 * m22
				 - m02 * m11 * m23
				 - m03 * m12 * m21;
		}

		inline elem_t a31(void) const
		{
			return m02 * m13 * m20
				 + m03 * m10 * m22
				 + m00 * m12 * m23
				 - m02 * m10 * m23
				 - m03 * m12 * m20
				 - m00 * m13 * m22;
		}

		inline elem_t a32(void) const
		{
			return m03 * m10 * m21
				 + m00 * m11 * m23
				 + m01 * m13 * m20
				 - m03 * m11 * m20
				 - m00 * m13 * m21
				 - m01 * m10 * m23;
		}

		inline elem_t a33(void) const
		{
			return m00 * m11 * m22
				 + m01 * m12 * m20
				 + m02 * m10 * m21
				 - m00 * m12 * m21
				 - m01 * m10 * m22
				 - m02 * m11 * m20;
		}

		inline Mat4 adjoint(void) const
		{
			return Mat4(
				 a00(), -a10(),  a20(), -a30(),
				-a01(),  a11(), -a21(),  a31(),
				 a02(), -a12(),  a22(), -a32(),
				-a03(),  a13(), -a23(),  a33());
		}

		inline elem_t determinant(void) const
		{
			return m00 * a00() - m01 * a01() + m02 * a02() - m03 * a03();
		}

		inline Mat4 inverse(void) const
		{
			//assert(!IS_ZERO_FLOAT(determinant()));

			return adjoint() * (1 / determinant());
		}

		inline Mat4 & inverseSelf(void)
		{
			return *this = inverse();
		}

		inline Mat4 transpose(void) const
		{
			return Mat4(
				m00, m10, m20, m30,
				m01, m11, m21, m31,
				m02, m12, m22, m32,
				m03, m13, m23, m33);
		}

		inline Mat4 & transposeSelf(void)
		{
			return *this = transpose();
		}

		inline Mat4 transform(const Mat4<elem_t> & rhs) const
		{
			return *this * rhs;
		}

		inline Mat4 & transformSelf(const Mat4<elem_t> & rhs)
		{
			return *this = transform(rhs);
		}

		inline Mat4 transformTranspose(const Mat4<elem_t> & rhs) const
		{
			return Mat4(
				m00 * rhs.m00 + m01 * rhs.m01 + m02 * rhs.m02 + m03 * rhs.m03,
				m00 * rhs.m10 + m01 * rhs.m11 + m02 * rhs.m12 + m03 * rhs.m13,
				m00 * rhs.m20 + m01 * rhs.m21 + m02 * rhs.m22 + m03 * rhs.m23,
				m00 * rhs.m30 + m01 * rhs.m31 + m02 * rhs.m32 + m03 * rhs.m33,

				m10 * rhs.m00 + m11 * rhs.m01 + m12 * rhs.m02 + m13 * rhs.m03,
				m10 * rhs.m10 + m11 * rhs.m11 + m12 * rhs.m12 + m13 * rhs.m13,
				m10 * rhs.m20 + m11 * rhs.m21 + m12 * rhs.m22 + m13 * rhs.m23,
				m10 * rhs.m30 + m11 * rhs.m31 + m12 * rhs.m32 + m13 * rhs.m33,

				m20 * rhs.m00 + m21 * rhs.m01 + m22 * rhs.m02 + m23 * rhs.m03,
				m20 * rhs.m10 + m21 * rhs.m11 + m22 * rhs.m12 + m23 * rhs.m13,
				m20 * rhs.m20 + m21 * rhs.m21 + m22 * rhs.m22 + m23 * rhs.m23,
				m20 * rhs.m30 + m21 * rhs.m31 + m22 * rhs.m32 + m23 * rhs.m33,

				m30 * rhs.m00 + m31 * rhs.m01 + m32 * rhs.m02 + m33 * rhs.m03,
				m30 * rhs.m10 + m31 * rhs.m11 + m32 * rhs.m12 + m33 * rhs.m13,
				m30 * rhs.m20 + m31 * rhs.m21 + m32 * rhs.m22 + m33 * rhs.m23,
				m30 * rhs.m30 + m31 * rhs.m31 + m32 * rhs.m32 + m33 * rhs.m33);
		}

		inline Mat4 & transformTransposeSelf(const Mat4<elem_t> & rhs)
		{
			return *this = transformTranspose(rhs);
		}
	};

	template <typename elem_t>
	class Vec2
	{
	public:
		union
		{
			/*__declspec(align(16))*/ elem_t _M[2];

			struct
			{
				elem_t x;
				elem_t y;
			};
		};

	public:
		inline Vec2(void)
		{
		}

		inline Vec2(elem_t _x, elem_t _y)
			: x(_x)
			, y(_y)
		{
		}

	public:
		inline Vec2 operator - (void) const
		{
			return Vec2(
				-x,
				-y);
		}

		inline bool operator == (const Vec2 & rhs) const
		{
			return x == rhs.x
				&& y == rhs.y;
		}

		inline Vec2 operator + (const Vec2 & rhs) const
		{
			return Vec2(
				x + rhs.x,
				y + rhs.y);
		}

		inline Vec2 operator + (elem_t scaler) const
		{
			return Vec2(
				x + scaler,
				y + scaler);
		}

		inline Vec2 & operator +=(const Vec2 & rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		inline Vec2 & operator +=(elem_t scaler)
		{
			x += scaler;
			y += scaler;
			return *this;
		}

		inline Vec2 operator - (const Vec2 & rhs) const
		{
			return Vec2(
				x - rhs.x,
				y - rhs.y);
		}

		inline Vec2 operator - (elem_t scaler) const
		{
			return Vec2(
				x - scaler,
				y - scaler);
		}

		inline Vec2 & operator -=(const Vec2 & rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		inline Vec2 & operator -=(elem_t scaler)
		{
			x -= scaler;
			y -= scaler;
			return *this;
		}

		inline Vec2 operator * (const Vec2 & rhs) const
		{
			return Vec2(
				x * rhs.x,
				y * rhs.y);
		}

		inline Vec2 operator * (elem_t scaler) const
		{
			return Vec2(
				x * scaler,
				y * scaler);
		}

		inline Vec2 & operator *=(const Vec2 & rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}

		inline Vec2 & operator *=(elem_t scaler)
		{
			x *= scaler;
			y *= scaler;
			return *this;
		}

		inline Vec2 operator / (const Vec2 & rhs) const
		{
			return Vec2(
				x / rhs.x,
				y / rhs.y);
		}

		inline Vec2 operator / (elem_t scaler) const
		{
			return Vec2(
				x / scaler,
				y / scaler);
		}

		inline Vec2 & operator /=(const Vec2 & rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}

		inline Vec2 & operator /=(elem_t scaler)
		{
			x /= scaler;
			y /= scaler;
			return *this;
		}
	};

	template <typename elem_t>
	class Vec4
	{
	public:
		union
		{
			/*__declspec(align(16))*/ elem_t _M[4];

			struct
			{
				elem_t x;
				elem_t y;
				elem_t z;
				elem_t w;
			};
		};

	public:
		inline Vec4(void)
		{
		}

		inline Vec4(elem_t _x, elem_t _y, elem_t _z, elem_t _w)
			: x(_x)
			, y(_y)
			, z(_z)
			, w(_w)
		{
		}

	public:
		inline Vec4 operator - (void) const
		{
			return Vec4(
				-x,
				-y,
				-z,
				-w);
		}

		inline bool operator == (const Vec4 & rhs) const
		{
			return x == rhs.x
				&& y == rhs.y
				&& z == rhs.z
				&& w == rhs.w;
		}

		inline Vec4 operator + (const Vec4 & rhs) const
		{
			return Vec4(
				x + rhs.x,
				y + rhs.y,
				z + rhs.z,
				w + rhs.w);
		}

		inline Vec4 operator + (elem_t scaler) const
		{
			return Vec4(
				x + scaler,
				y + scaler,
				z + scaler,
				w + scaler);
		}

		inline Vec4 & operator +=(const Vec4 & rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
			return *this;
		}

		inline Vec4 & operator +=(elem_t scaler)
		{
			x += scaler;
			y += scaler;
			z += scaler;
			w += scaler;
			return *this;
		}

		inline Vec4 operator - (const Vec4 & rhs) const
		{
			return Vec4(
				x - rhs.x,
				y - rhs.y,
				z - rhs.z,
				w - rhs.w);
		}

		inline Vec4 operator - (elem_t scaler) const
		{
			return Vec4(
				x - scaler,
				y - scaler,
				z - scaler,
				w - scaler);
		}

		inline Vec4 & operator -=(const Vec4 & rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;
			return *this;
		}

		inline Vec4 & operator -=(elem_t scaler)
		{
			x -= scaler;
			y -= scaler;
			z -= scaler;
			w -= scaler;
			return *this;
		}

		inline Vec4 operator * (const Vec4 & rhs) const
		{
			return Vec4(
				x * rhs.x,
				y * rhs.y,
				z * rhs.z,
				w * rhs.w);
		}

		inline Vec4 operator * (elem_t scaler) const
		{
			return Vec4(
				x * scaler,
				y * scaler,
				z * scaler,
				w * scaler);
		}

		inline Vec4 & operator *=(const Vec4 & rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			w *= rhs.w;
			return *this;
		}

		inline Vec4 & operator *=(elem_t scaler)
		{
			x *= scaler;
			y *= scaler;
			z *= scaler;
			w *= scaler;
			return *this;
		}

		inline Vec4 operator / (const Vec4 & rhs) const
		{
			return Vec4(
				x / rhs.x,
				y / rhs.y,
				z / rhs.z,
				w / rhs.w);
		}

		inline Vec4 operator / (elem_t scaler) const
		{
			return Vec4(
				x / scaler,
				y / scaler,
				z / scaler,
				w / scaler);
		}

		inline Vec4 & operator /=(const Vec4 & rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			w /= rhs.w;
			return *this;
		}

		inline Vec4 & operator /=(elem_t scaler)
		{
			x /= scaler;
			y /= scaler;
			z /= scaler;
			w /= scaler;
			return *this;
		}

	public:
		inline Vec4 operator * (const Mat4<elem_t> & rhs) const
		{
			return Vec4(
				x * rhs.m00 + y * rhs.m10 + z * rhs.m20 + w * rhs.m30,
				x * rhs.m01 + y * rhs.m11 + z * rhs.m21 + w * rhs.m31,
				x * rhs.m02 + y * rhs.m12 + z * rhs.m22 + w * rhs.m32,
				x * rhs.m03 + y * rhs.m13 + z * rhs.m23 + w * rhs.m33);
		}

		inline Vec4 & operator *=(const Mat4<elem_t> & rhs)
		{
			return *this = *this * rhs;
		}

		inline Vec4 transform(const Mat4<elem_t> & rhs) const
		{
			return *this * rhs;
		}

		inline Vec4 & transformSelf(const Mat4<elem_t> & rhs)
		{
			return *this = transform(rhs);
		}

		inline Vec4 transformTranspose(const Mat4<elem_t> & rhs) const
		{
			return Vec4(
				x * rhs.m00 + y * rhs.m01 + z * rhs.m02 + w * rhs.m03,
				x * rhs.m10 + y * rhs.m11 + z * rhs.m12 + w * rhs.m13,
				x * rhs.m20 + y * rhs.m21 + z * rhs.m22 + w * rhs.m23,
				x * rhs.m30 + y * rhs.m31 + z * rhs.m32 + w * rhs.m33);
		}

		inline Vec4 & transformTransposeSelf(const Mat4<elem_t> & rhs)
		{
			return *this = transformTranspose(rhs);
		}
	};

	template <typename elem_t>
	class Quat
	{
	public:
		union
		{
			/*__declspec(align(16))*/ elem_t _M[4];

			struct
			{
				elem_t w;
				elem_t x;
				elem_t y;
				elem_t z;
			};
		};

	public:
		inline Quat(void)
		{
		}

		inline Quat(elem_t _w, elem_t _x, elem_t _y, elem_t _z)
			: w(_w)
			, x(_x)
			, y(_y)
			, z(_z)
		{
		}

	public:
		inline Quat operator + (const Quat & rhs) const
		{
			return Quat(
				w + rhs.w,
				x + rhs.x,
				y + rhs.y,
				z + rhs.z);
		}

		inline Quat operator + (elem_t scaler) const
		{
			return Quat(
				w + scaler,
				x + scaler,
				y + scaler,
				z + scaler);
		}

		inline Quat & operator +=(const Quat & rhs)
		{
			w += rhs.w;
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		inline Quat & operator +=(elem_t scaler)
		{
			w += scaler;
			x += scaler;
			y += scaler;
			z += scaler;
			return *this;
		}

		inline Quat operator - (const Quat & rhs) const
		{
			return Quat(
				w - rhs.w,
				x - rhs.x,
				y - rhs.y,
				z - rhs.z);
		}

		inline Quat operator - (elem_t scaler) const
		{
			return Quat(
				w - scaler,
				x - scaler,
				y - scaler,
				z - scaler);
		}

		inline Quat & operator -=(const Quat & rhs)
		{
			w -= rhs.w;
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		inline Quat & operator -=(elem_t scaler)
		{
			w -= scaler;
			x -= scaler;
			y -= scaler;
			z -= scaler;
			return *this;
		}

		inline Quat operator * (const Quat & rhs) const
		{
			return Quat(
				w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z,
				w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
				w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
				w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x);
		}

		inline Quat operator * (elem_t scaler) const
		{
			return Quat(
				w * scaler,
				x * scaler,
				y * scaler,
				z * scaler);
		}

		inline Quat & operator *= (const Quat & rhs)
		{
			return *this = *this * rhs;
		}

		inline Quat & operator *=(elem_t scaler)
		{
			w *= scaler;
			x *= scaler;
			y *= scaler;
			z *= scaler;
			return *this;
		}

		//inline Quat operator / (const Quat & rhs) const
		//{
		//	return *this * rhs.inverse();
		//}

		//inline Quat operator / (elem_t scaler) const
		//{
		//	return Quat(
		//		w / scaler, x / scaler, y / scaler, z / scaler);
		//}

		//inline Quat & operator /=(const Quat & rhs)
		//{
		//	return *this = *this / rhs;
		//}

		//inline Quat & operator /=(elem_t scaler)
		//{
		//	w /= scaler;
		//	x /= scaler;
		//	y /= scaler;
		//	z /= scaler;
		//	return *this;
		//}

	public:
		inline Quat scale(elem_t scaler) const
		{
			return Quat(
				w * scaler,
				x * scaler,
				y * scaler,
				z * scaler);
		}

		inline Quat & scaleSelf(elem_t scaler)
		{
			w *= scaler;
			x *= scaler;
			y *= scaler;
			z *= scaler;
			return *this;
		}

		inline Quat conjugate(void) const
		{
			return Quat(
				w, -x, -y, -z);
		}

		inline Quat & conjugateSelf(void)
		{
			x = -x;
			y = -y;
			z = -z;
			return *this;
		}

		inline elem_t norm2(void) const
		{
			return w * w + x * x + y * y + z * z;
		}

		inline elem_t norm(void) const
		{
			return sqrt(norm2());
		}

		inline Quat inverse(void) const
		{
			assert(!IS_ZERO_FLOAT(norm()));

			return conjugate().scale(1 / norm());
		}

		inline Quat & inverseSelf(void)
		{
			return *this = inverse();
		}

		inline Quat unitInverse(void) const
		{
			assert(IS_ZERO_FLOAT(norm() - 1));

			return conjugate();
		}

		inline Quat & unitInverseSelf(void)
		{
			assert(IS_ZERO_FLOAT(norm() - 1));

			return conjugateSelf();
		}

		inline Quat normalize(void) const
		{
			assert(!IS_ZERO_FLOAT(norm()));

			elem_t length_inv = 1 / norm();
			return Quat(
				w * length_inv,
				x * length_inv,
				y * length_inv,
				z * length_inv);
		}

		inline Quat & normalizeSelf(void)
		{
			assert(!IS_ZERO_FLOAT(norm()));

			elem_t length = norm();
			w /= length;
			x /= length;
			y /= length;
			z /= length;
			return *this;
		}
	};
#pragma warning(default: 4201)
	inline real int_to_real(int ival)
	{
		return real(ival);
	}

	inline int real_to_int(real rval)
	{
#ifdef T3DLIB_REPORT_PRECISION_ERROR
		if(rval < INT_MIN || rval > INT_MAX)
			std::cerr << "error: convert real value " << rval << " to int" << std::endl;
#endif
		return int(rval);
	}

	inline fixp16 int_to_fixp16(int ival)
	{
		return ival << 16;
	}

	inline int fixp16_to_int(fixp16 fval)
	{
		return fval >> 16;
	}

	inline fixp16 real_to_fixp16(real rval)
	{
#ifdef T3DLIB_REPORT_PRECISION_ERROR
		if(rval < FIXP16_MIN || rval > FIXP16_MAX)
			std::cerr << "error: convert real value " << rval << " to fixp16" << std::endl;
#endif
		return fixp16(rval * (1 << 16));
	}

	inline real fixp16_to_real(fixp16 fval)
	{
		return real(fval) / (1 << 16);
	}

	inline fixp28 int_to_fixp28(int ival)
	{
		return ival << 28;
	}

	inline int fixp28_to_int(fixp28 fval)
	{
		return fval >> 28;
	}

	inline fixp28 real_to_fixp28(real rval)
	{
#ifdef T3DLIB_REPORT_PRECISION_ERROR
		if(rval < FIXP28_MIN || rval > FIXP28_MAX)
			std::cerr << "error: convert real value " << rval << " to fixp28" << std::endl;
#endif
		return fixp28(rval * (1 << 28));
	}

	inline real fixp28_to_real(fixp28 fval)
	{
		return real(fval) / (1 << 28);
	}

	inline Vec2<real> int_to_real(const Vec2<int> & ival)
	{
		return Vec2<real>(
			int_to_real(ival.x),
			int_to_real(ival.y));
	}

	inline Vec2<int> real_to_int(const Vec2<real> & rval)
	{
		return Vec2<int>(
			real_to_int(rval.x),
			real_to_int(rval.y));
	}

	inline Vec2<fixp16> int_to_fixp16(const Vec2<int> & ival)
	{
		return Vec2<fixp16>(
			int_to_fixp16(ival.x),
			int_to_fixp16(ival.y));
	}

	inline Vec2<int> fixp16_to_int(const Vec2<fixp16> & fval)
	{
		return Vec2<int>(
			fixp16_to_int(fval.x),
			fixp16_to_int(fval.y));
	}

	inline Vec2<fixp16> real_to_fixp16(const Vec2<real> & rval)
	{
		return Vec2<fixp16>(
			real_to_fixp16(rval.x),
			real_to_fixp16(rval.y));
	}

	inline Vec2<real> fixp16_to_real(const Vec2<fixp16> & fval)
	{
		return Vec2<real>(
			fixp16_to_real(fval.x),
			fixp16_to_real(fval.y));
	}

	inline Vec2<fixp28> real_to_fixp28(const Vec2<real> & rval)
	{
		return Vec2<fixp28>(
			real_to_fixp28(rval.x),
			real_to_fixp28(rval.y));
	}

	inline Vec2<real> fixp28_to_real(const Vec2<fixp28> & fval)
	{
		return Vec2<real>(
			fixp28_to_real(fval.x),
			fixp28_to_real(fval.y));
	}

	inline Vec4<real> int_to_real(const Vec4<int> & ival)
	{
		return Vec4<real>(
			int_to_real(ival.x),
			int_to_real(ival.y),
			int_to_real(ival.z),
			int_to_real(ival.w));
	}

	inline Vec4<int> real_to_int(const Vec4<real> & rval)
	{
		return Vec4<int>(
			real_to_int(rval.x),
			real_to_int(rval.y),
			real_to_int(rval.z),
			real_to_int(rval.w));
	}

	inline Vec4<fixp16> int_to_fixp16(const Vec4<int> & ival)
	{
		return Vec4<fixp16>(
			int_to_fixp16(ival.x),
			int_to_fixp16(ival.y),
			int_to_fixp16(ival.z),
			int_to_fixp16(ival.w));
	}

	inline Vec4<int> fixp16_to_int(const Vec4<fixp16> & fval)
	{
		return Vec4<int>(
			fixp16_to_int(fval.x),
			fixp16_to_int(fval.y),
			fixp16_to_int(fval.z),
			fixp16_to_int(fval.w));
	}

	inline Vec4<fixp16> real_to_fixp16(const Vec4<real> & rval)
	{
		return Vec4<fixp16>(
			real_to_fixp16(rval.x),
			real_to_fixp16(rval.y),
			real_to_fixp16(rval.z),
			real_to_fixp16(rval.w));
	}

	inline Vec4<real> fixp16_to_real(const Vec4<fixp16> & fval)
	{
		return Vec4<real>(
			fixp16_to_real(fval.x),
			fixp16_to_real(fval.y),
			fixp16_to_real(fval.z),
			fixp16_to_real(fval.w));
	}

	inline Vec4<fixp28> int_to_fixp28(const Vec4<int> & ival)
	{
		return Vec4<fixp28>(
			int_to_fixp28(ival.x),
			int_to_fixp28(ival.y),
			int_to_fixp28(ival.z),
			int_to_fixp28(ival.w));
	}

	inline Vec4<int> fixp28_to_int(const Vec4<fixp28> & fval)
	{
		return Vec4<int>(
			fixp28_to_int(fval.x),
			fixp28_to_int(fval.y),
			fixp28_to_int(fval.z),
			fixp28_to_int(fval.w));
	}

	inline Vec4<fixp28> real_to_fixp28(const Vec4<real> & rval)
	{
		return Vec4<fixp28>(
			real_to_fixp28(rval.x),
			real_to_fixp28(rval.y),
			real_to_fixp28(rval.z),
			real_to_fixp28(rval.w));
	}

	inline Vec4<real> fixp28_to_real(const Vec4<fixp28> & fval)
	{
		return Vec4<real>(
			fixp28_to_real(fval.x),
			fixp28_to_real(fval.y),
			fixp28_to_real(fval.z),
			fixp28_to_real(fval.w));
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Build(elem_t x, elem_t y, elem_t z)
	{
		return Vec4<elem_t>(x, y, z, 1);
	}

	template <typename elem_t>
	inline bool vec3IsZero(const Vec4<elem_t> & rhs)
	{
		return IS_ZERO_FLOAT(rhs.x) && IS_ZERO_FLOAT(rhs.y) && IS_ZERO_FLOAT(rhs.z);
	}

	template <typename elem_t>
	inline bool vec3IsEqual(const Vec4<elem_t> & lhs, const Vec4<elem_t> & rhs)
	{
		return lhs.x == rhs.x
			&& lhs.y == rhs.y
			&& lhs.z == rhs.z;
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Neg(const Vec4<elem_t> & rhs)
	{
		return Vec4<elem_t>(
			-rhs.x,
			-rhs.y,
			-rhs.z,
			1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> & vec3NegSelf(Vec4<elem_t> & res)
	{
		assert(1 == res.w);

		res.x = -res.x;
		res.y = -res.y;
		res.z = -res.z;
		return res;
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Inverse(const Vec4<elem_t> & rhs)
	{
		return Vec4<elem_t>(
			1 / rhs.x,
			1 / rhs.y,
			1 / rhs.z,
			1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> & vec3InverseSelf(Vec4<elem_t> & res)
	{
		assert(1 == res.w);

		res.x = 1 / res.x;
		res.y = 1 / res.y;
		res.z = 1 / res.z;
		return res;
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Add(const Vec4<elem_t> & lhs, const Vec4<elem_t> & rhs)
	{
		return Vec4<elem_t>(
			lhs.x + rhs.x,
			lhs.y + rhs.y,
			lhs.z + rhs.z,
			1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> & vec3AddSelf(Vec4<elem_t> & res, const Vec4<elem_t> & rhs)
	{
		assert(1 == res.w);

		res.x += rhs.x;
		res.y += rhs.y;
		res.z += rhs.z;
		return res;
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Add(const Vec4<elem_t> & lhs, elem_t scaler)
	{
		return Vec4<elem_t>(
			lhs.x + scaler,
			lhs.y + scaler,
			lhs.z + scaler,
			1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> & vec3AddSelf(Vec4<elem_t> & res, elem_t scaler)
	{
		assert(1 == res.w);

		res.x += scaler;
		res.y += scaler;
		res.z += scaler;
		return res;
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Sub(const Vec4<elem_t> & lhs, const Vec4<elem_t> & rhs)
	{
		return Vec4<elem_t>(
			lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z,
			1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> & vec3SubSelf(Vec4<elem_t> & res, const Vec4<elem_t> & rhs)
	{
		assert(1 == res.w);

		res.x -= rhs.x;
		res.y -= rhs.y;
		res.z -= rhs.z;
		return res;
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Sub(const Vec4<elem_t> & lhs, elem_t scaler)
	{
		return Vec4<elem_t>(
			lhs.x - scaler,
			lhs.y - scaler,
			lhs.z - scaler,
			1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> & vec3SubSelf(Vec4<elem_t> & res, elem_t scaler)
	{
		assert(1 == res.w);

		res.x -= scaler;
		res.y -= scaler;
		res.z -= scaler;
		return res;
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Mul(const Vec4<elem_t> & lhs, const Vec4<elem_t> & rhs)
	{
		return Vec4<elem_t>(
			lhs.x * rhs.x,
			lhs.y * rhs.y,
			lhs.z * rhs.z,
			1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> & vec3MulSelf(Vec4<elem_t> & res, const Vec4<elem_t> & rhs)
	{
		assert(1 == res.w);

		res.x *= rhs.x;
		res.y *= rhs.y;
		res.z *= rhs.z;
		return res;
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Mul(const Vec4<elem_t> & lhs, elem_t scaler)
	{
		return Vec4<elem_t>(
			lhs.x * scaler,
			lhs.y * scaler,
			lhs.z * scaler,
			1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> & vec3MulSelf(Vec4<elem_t> & res, elem_t scaler)
	{
		assert(1 == res.w);

		res.x *= scaler;
		res.y *= scaler;
		res.z *= scaler;
		return res;
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Div(const Vec4<elem_t> & lhs, const Vec4<elem_t> & rhs)
	{
		return Vec4<elem_t>(
			lhs.x / rhs.x,
			lhs.y / rhs.y,
			lhs.z / rhs.z,
			1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> & vec3DivSelf(Vec4<elem_t> & res, const Vec4<elem_t> & rhs)
	{
		assert(1 == res.w);

		res.x /= rhs.x;
		res.y /= rhs.y;
		res.z /= rhs.z;
		return res;
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Div(const Vec4<elem_t> & lhs, elem_t scaler)
	{
		return Vec4<elem_t>(
			lhs.x / scaler,
			lhs.y / scaler,
			lhs.z / scaler,
			1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> & vec3DivSelf(Vec4<elem_t> & res, elem_t scaler)
	{
		assert(1 == res.w);

		res.x /= scaler;
		res.y /= scaler;
		res.z /= scaler;
		return res;
	}

	template <typename elem_t>
	inline elem_t vec3LengthSquare(const Vec4<elem_t> & rhs)
	{
		return rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z;
	}

	template <typename elem_t>
	inline elem_t vec3Length(const Vec4<elem_t> & rhs)
	{
		return sqrt(vec3LengthSquare(rhs));
	}

	template <typename elem_t>
	inline bool vec3IsNormalized(const Vec4<elem_t> & rhs)
	{
		return IS_ZERO_FLOAT(vec3Length(rhs) - 1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Normalize(const Vec4<elem_t> & rhs)
	{
		assert(!IS_ZERO_FLOAT(vec3Length(rhs)));

		elem_t len = vec3Length(rhs);
		return Vec4<elem_t>(
			rhs.x / len,
			rhs.y / len,
			rhs.z / len,
			1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> & vec3NormalizeSelf(Vec4<elem_t> & res)
	{
		assert(1 == res.w);

		elem_t len = vec3Length(res);
		res.x /= len;
		res.y /= len;
		res.z /= len;
		return res;
	}

	template <typename elem_t>
	inline elem_t vec3Dot(const Vec4<elem_t> & lhs, const Vec4<elem_t> & rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Cross(const Vec4<elem_t> & lhs, const Vec4<elem_t> & rhs)
	{
		return Vec4<elem_t>(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x,
			1);
	}

	template <typename elem_t>
	inline elem_t vec3CosTheta(const Vec4<elem_t> & lhs, const Vec4<elem_t> & rhs)
	{
		assert(!IS_ZERO_FLOAT(vec3Length(lhs) * vec3Length(rhs)));

		return vec3Dot(lhs, rhs) / (vec3Length(lhs) * vec3Length(rhs));
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3Build(
			const elem_t _m00, const elem_t _m01, const elem_t _m02,
			const elem_t _m10, const elem_t _m11, const elem_t _m12,
			const elem_t _m20, const elem_t _m21, const elem_t _m22)
	{
		return Mat4<elem_t>(
			_m00,			_m01,			_m02,			0,
			_m10,			_m11,			_m12,			0,
			_m20,			_m21,			_m22,			0,
			0,				0,				0,				1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> mat3GetRow0(const Mat4<elem_t> & rhs)
	{
		return Vec4<elem_t>(rhs.m00, rhs.m01, rhs.m02, 1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> mat3GetRow1(const Mat4<elem_t> & rhs)
	{
		return Vec4<elem_t>(rhs.m10, rhs.m11, rhs.m12, 1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> mat3GetRow2(const Mat4<elem_t> & rhs)
	{
		return Vec4<elem_t>(rhs.m20, rhs.m21, rhs.m22, 1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> mat3GetRow3(const Mat4<elem_t> & rhs)
	{
		return Vec4<elem_t>(rhs.m30, rhs.m31, rhs.m32, 1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> mat3GetRow(const Mat4<elem_t> & rhs, size_t row_i)
	{
		switch(row_i)
		{
		case 0:
			return mat3GetRow0(rhs);

		case 1:
			return mat3GetRow1(rhs);

		case 2:
			return mat3GetRow2(rhs);

		case 3:
			return mat3GetRow3(rhs);
		}

		assert(false); return Vec4<elem_t>();
	}

	template <typename elem_t>
	inline Vec4<elem_t> mat3GetColumn0(const Mat4<elem_t> & rhs)
	{
		return Vec4<elem_t>(rhs.m00, rhs.m10, rhs.m20, 1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> mat3GetColumn1(const Mat4<elem_t> & rhs)
	{
		return Vec4<elem_t>(rhs.m01, rhs.m11, rhs.m21, 1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> mat3GetColumn2(const Mat4<elem_t> & rhs)
	{
		return Vec4<elem_t>(rhs.m02, rhs.m12, rhs.m22, 1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> mat3GetColumn3(const Mat4<elem_t> & rhs)
	{
		return Vec4<elem_t>(rhs.m03, rhs.m13, rhs.m23, 1);
	}

	template <typename elem_t>
	inline Vec4<elem_t> mat3GetColumn(const Mat4<elem_t> & rhs, size_t column_i)
	{
		switch(column_i)
		{
		case 0:
			return mat3GetColumn0(rhs);

		case 1:
			return mat3GetColumn1(rhs);

		case 2:
			return mat3GetColumn2(rhs);

		case 3:
			return mat3GetColumn3(rhs);
		}

		assert(false); return Vec4<elem_t>();
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3Scale(const Vec4<elem_t> & scaler)
	{
		return Mat4<elem_t>(
			scaler.x,		0,				0,				0,
			0,				scaler.y,		0,				0,
			0,				0,				scaler.z,		0,
			0,				0,				0,				1);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3InverseScale(const Vec4<elem_t> & scaler)
	{
		return mat3Scale(vec3Inverse(scaler));
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3Mov(const Vec4<elem_t> & rhs)
	{
		return Mat4<elem_t>(
			1,				0,				0,				0,
			0,				1,				0,				0,
			0,				0,				1,				0,
			rhs.x,			rhs.y,			rhs.z,			1);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3InverseMov(const Vec4<elem_t> & rhs)
	{
		return mat3Mov(vec3Neg(rhs));
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3RotX(elem_t radian)
	{
		return Mat4<elem_t>(
			1,				0,				0,				0,
			0,				cos(radian),	sin(radian),	0,
			0,				-sin(radian),	cos(radian),	0,
			0,				0,				0,				1);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3InverseRotX(elem_t radian)
	{
		return mat3RotX(-radian);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3RotY(elem_t radian)
	{
		return Mat4<elem_t>(
			cos(radian),	0,				-sin(radian),	0,
			0,				1,				0,				0,
			sin(radian),	0,				cos(radian),	0,
			0,				0,				0,				1);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3InverseRotY(elem_t radian)
	{
		return mat3RotY(-radian);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3RotZ(elem_t radian)
	{
		return Mat4<elem_t>(
			cos(radian),	sin(radian),	0,				0,
			-sin(radian),	cos(radian),	0,				0,
			0,				0,				1,				0,
			0,				0,				0,				1);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3InverseRotZ(elem_t radian)
	{
		return mat3RotZ(-radian);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3RotXYZ(const Vec4<elem_t> & rhs)
	{
		return mat3RotX(rhs.x) * mat3RotY(rhs.y) * mat3RotZ(rhs.z);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3InverseRotXYZ(const Vec4<elem_t> & rhs)
	{
		return mat3InverseRotZ(rhs.z) * mat3InverseRotY(rhs.y) * mat3InverseRotX(rhs.x);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3RotYXZ(const Vec4<elem_t> & rhs)
	{
		return mat3RotY(rhs.y) * mat3RotX(rhs.x) * mat3RotZ(rhs.z);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3InverseRotYXZ(const Vec4<elem_t> & rhs)
	{
		return mat3InverseRotZ(rhs.z) * mat3InverseRotX(rhs.x) * mat3InverseRotY(rhs.y);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3RotXZY(const Vec4<elem_t> & rhs)
	{
		return mat3RotX(rhs.x) * mat3RotZ(rhs.z) * mat3RotY(rhs.y);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3InverseRotXZY(const Vec4<elem_t> & rhs)
	{
		return mat3InverseRotY(rhs.y) * mat3InverseRotZ(rhs.z) * mat3InverseRotX(rhs.x);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3RotZXY(const Vec4<elem_t> & rhs)
	{
		return mat3RotZ(rhs.z) * mat3RotX(rhs.x) * mat3RotY(rhs.y);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3InverseRotZXY(const Vec4<elem_t> & rhs)
	{
		return mat3InverseRotY(rhs.y) * mat3InverseRotX(rhs.x) * mat3InverseRotZ(rhs.z);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3RotYZX(const Vec4<elem_t> & rhs)
	{
		return mat3RotY(rhs.y) * mat3RotZ(rhs.z) * mat3RotX(rhs.x);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3InverseRotYZX(const Vec4<elem_t> & rhs)
	{
		return mat3InverseRotX(rhs.x) * mat3InverseRotZ(rhs.z) * mat3InverseRotY(rhs.y);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3RotZYX(const Vec4<elem_t> & rhs)
	{
		return mat3RotZ(rhs.z) * mat3RotY(rhs.y) * mat3RotX(rhs.x);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3InverseRotZYX(const Vec4<elem_t> & rhs)
	{
		return mat3InverseRotX(rhs.x) * mat3InverseRotY(rhs.y) * mat3InverseRotZ(rhs.z);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3Uvn(const Vec4<elem_t> & u, const Vec4<elem_t> & v, const Vec4<elem_t> & n)
	{
		assert(IS_ZERO_FLOAT(vec3Dot(u, v)));
		assert(IS_ZERO_FLOAT(vec3Dot(u, n)));
		assert(IS_ZERO_FLOAT(vec3Dot(v, n)));

		return Mat4<elem_t>(
			u.x,			v.x,			n.x,			0,
			u.y,			v.y,			n.y,			0,
			u.z,			v.z,			n.z,			0,
			0,				0,				0,				1);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3TransposUvn(const Vec4<elem_t> & u, const Vec4<elem_t> & v, const Vec4<elem_t> & n)
	{
		assert(IS_ZERO_FLOAT(vec3Dot(u, v)));
		assert(IS_ZERO_FLOAT(vec3Dot(u, n)));
		assert(IS_ZERO_FLOAT(vec3Dot(v, n)));

		return Mat4<elem_t>(
			u.x,			u.y,			u.z,			0,
			v.x,			v.y,			v.z,			0,
			n.x,			n.y,			n.z,			0,
			0,				0,				0,				1);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat3LookAt(const Vec4<elem_t> & pos, const Vec4<elem_t> & target, const Vec4<elem_t> & up)
	{
		Vec4<elem_t> n(vec3Sub(target, pos));
		Vec4<elem_t> u(vec3Cross(up, n));
		Vec4<elem_t> v(vec3Cross(n, u));

		return mat3Uvn(vec3Normalize(u), vec3Normalize(v), vec3Normalize(n));
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat4GetRotationScalePart(const Mat4<elem_t> & rhs)
	{
		return Mat4<elem_t>(
			rhs.m00,		rhs.m01,		rhs.m02,		0,
			rhs.m10,		rhs.m11,		rhs.m12,		0,
			rhs.m20,		rhs.m21,		rhs.m22,		0,
			0,				0,				0,				1);
	}

	template <typename elem_t>
	inline Quat<elem_t> buildQuatFromAngularVelocity(const Vec4<elem_t> & angularVelocity)
	{
		return Quat<elem_t>(0, angularVelocity.x, angularVelocity.y, angularVelocity.z);
	}

	template <typename elem_t>
	inline Quat<elem_t> quatAddAngularVelocity(const Quat<elem_t> & lhs, const Vec4<elem_t> & rhs)
	{
		return lhs + buildQuatFromAngularVelocity(rhs) * lhs * 0.5f;
	}

	template <typename elem_t>
	Quat<elem_t> & quatAddAngularVelocitySelf(Quat<elem_t> & lhs, const Vec4<elem_t> & rhs)
	{
		return lhs += buildQuatFromAngularVelocity(rhs) * lhs * 0.5f;
	}

	template <typename elem_t>
	inline Quat<elem_t> buildQuatFromEulerZYX(elem_t z, elem_t y, elem_t x)
	{
		return Quat<elem_t>(
			cos(z / 2) * cos(y / 2) * cos(x / 2) + sin(z / 2) * sin(y / 2) * sin(x / 2),
			cos(z / 2) * cos(y / 2) * sin(x / 2) - sin(z / 2) * sin(y / 2) * cos(x / 2),
			cos(z / 2) * sin(y / 2) * cos(x / 2) + sin(z / 2) * cos(y / 2) * sin(x / 2),
			sin(z / 2) * cos(y / 2) * cos(x / 2) - cos(z / 2) * sin(y / 2) * sin(x / 2));
	}

	template <typename elem_t>
	inline Quat<elem_t> buildQuatFromAngleAxis(elem_t angle, const Vec4<elem_t> & axis)
	{
		assert(IS_ZERO_FLOAT(vec3Length(axis) - 1));

		return Quat<elem_t>(
			cos(angle / 2),
			axis.x * sin(angle / 2),
			axis.y * sin(angle / 2),
			axis.z * sin(angle / 2));
	}

	template <typename elem_t>
	inline Mat4<elem_t> buildRotationMatrixFromQuatLH(const Quat<elem_t> & quat)
	{
		assert(IS_ZERO_FLOAT(quat.norm() - 1));

		return Mat4<elem_t>(
			1 - (2 * quat.y * quat.y + 2 * quat.z * quat.z),	2 * quat.x * quat.y + 2 * quat.w * quat.z,			2 * quat.x * quat.z - 2 * quat.w * quat.y,			0,
			2 * quat.x * quat.y - 2 * quat.w * quat.z,			1 - (2 * quat.x * quat.x + 2 * quat.z * quat.z),	2 * quat.y * quat.z + 2 * quat.w * quat.x,			0,
			2 * quat.x * quat.z + 2 * quat.w * quat.y,			2 * quat.y * quat.z - 2 * quat.w * quat.x,			1 - (2 * quat.x * quat.x + 2 * quat.y * quat.y),	0,
			0,													0,													0,													1);
	}

	template <typename elem_t>
	inline Mat4<elem_t> buildInverseRotationMatrixFromQuatLH(const Quat<elem_t> & quat)
	{
		assert(IS_ZERO_FLOAT(quat.norm() - 1));

		return buildRotationMatrixFromQuatLH(quat.unitInverse());
	}

	//template <typename elem_t>
	//inline Mat4<elem_t> buildTransformMatrixLH(
	//	const Vec4<elem_t> & pos,
	//	const Quat<elem_t> & ori,
	//	const Vec4<elem_t> & scaler)
	//{
	//	return mat3Scale(scaler) * buildRotationMatrixFromQuatLH(ori) * mat3Mov(pos);
	//}

	//template <typename elem_t>
	//inline void buildTransformMatrixLH(
	//	Mat4<elem_t> & mmat,
	//	Mat4<elem_t> & mrot,
	//	const Vec4<elem_t> & pos,
	//	const Quat<elem_t> & ori,
	//	const Vec4<elem_t> & scaler)
	//{
	//	mrot = buildRotationMatrixFromQuatLH(ori);

	//	mmat = mat3Scale(scaler) * mrot * mat3Mov(pos);
	//}

	//template <typename elem_t>
	//inline Mat4<elem_t> buildInverseTransformMatrixLH(
	//	const Vec4<elem_t> & pos,
	//	const Quat<elem_t> & ori,
	//	const Vec4<elem_t> & scaler)
	//{
	//	return mat3InverseMov(pos) * buildInverseRotationMatrixFromQuatLH(ori) * mat3InverseScale(scaler);
	//}

	//template <typename elem_t>
	//inline void buildInverseTransformMatrixLH(
	//	Mat4<elem_t> & mInverseMat,
	//	Mat4<elem_t> & mInverseRot,
	//	const Vec4<elem_t> & pos,
	//	const Quat<elem_t> & ori,
	//	const Vec4<elem_t> & scaler)
	//{
	//	mInverseRot = buildInverseRotationMatrixFromQuatLH(ori);

	//	mInverseMat = mat3InverseMov(pos) * mInverseRot * mat3InverseScale(scaler);
	//}

	template <typename elem_t>
	inline Mat4<elem_t> removeTranslationMatrix(const Mat4<elem_t> & mmat)
	{
		return Mat4<elem_t>(
			mmat.m00,		mmat.m01,		mmat.m02,		0,
			mmat.m10,		mmat.m11,		mmat.m12,		0,
			mmat.m20,		mmat.m21,		mmat.m22,		0,
			0,				0,				0,				1);
	}

	template <typename elem_t>
	inline Mat4<elem_t> buildSkewSymmetricMatrxi(const Vec4<elem_t> & rhs)
	{
		return Mat4<elem_t>(
			0,				 rhs.z,			-rhs.y,			0,
			-rhs.z,			0,				 rhs.x,			0,
			 rhs.y,			-rhs.x,			0,				0,
			0,				0,				0,				1);

	}

	template <typename elem_t>
	inline Vec2<elem_t> vec2Intersect(const Vec2<elem_t> & v0, const Vec2<elem_t> & v1, elem_t a0, elem_t a1, elem_t ca)
	{
		return Vec2<elem_t>(
			LINE2D_INTERSECT(ca, a0, a1, v0.x, v1.x),
			LINE2D_INTERSECT(ca, a0, a1, v0.y, v1.y));
	}

	template <typename elem_t>
	inline Vec4<elem_t> vec3Intersect(const Vec4<elem_t> & v0, const Vec4<elem_t> & v1, elem_t a0, elem_t a1, elem_t ca)
	{
		return Vec4<elem_t>(
			LINE2D_INTERSECT(ca, a0, a1, v0.x, v1.x),
			LINE2D_INTERSECT(ca, a0, a1, v0.y, v1.y),
			LINE2D_INTERSECT(ca, a0, a1, v0.z, v1.z),
			1);
	}

	template <typename elem_t>
	inline Mat4<elem_t> mat4Intersect(const Mat4<elem_t> & m0, const Mat4<elem_t> & m1, elem_t a0, elem_t a1, elem_t ca)
	{
		return Mat4<elem_t>(
			LINE2D_INTERSECT(ca, a0, a1, m0.m00, m1.m00),
			LINE2D_INTERSECT(ca, a0, a1, m0.m01, m1.m01),
			LINE2D_INTERSECT(ca, a0, a1, m0.m02, m1.m02),
			LINE2D_INTERSECT(ca, a0, a1, m0.m03, m1.m03),

			LINE2D_INTERSECT(ca, a0, a1, m0.m10, m1.m10),
			LINE2D_INTERSECT(ca, a0, a1, m0.m11, m1.m11),
			LINE2D_INTERSECT(ca, a0, a1, m0.m12, m1.m12),
			LINE2D_INTERSECT(ca, a0, a1, m0.m13, m1.m13),

			LINE2D_INTERSECT(ca, a0, a1, m0.m20, m1.m20),
			LINE2D_INTERSECT(ca, a0, a1, m0.m21, m1.m21),
			LINE2D_INTERSECT(ca, a0, a1, m0.m22, m1.m22),
			LINE2D_INTERSECT(ca, a0, a1, m0.m23, m1.m23),

			LINE2D_INTERSECT(ca, a0, a1, m0.m30, m1.m30),
			LINE2D_INTERSECT(ca, a0, a1, m0.m31, m1.m31),
			LINE2D_INTERSECT(ca, a0, a1, m0.m32, m1.m32),
			LINE2D_INTERSECT(ca, a0, a1, m0.m33, m1.m33));
	}

	template <typename elem_t>
	inline Quat<elem_t> quatIntersect(const Quat<elem_t> & q0, const Quat<elem_t> & q1, elem_t a0, elem_t a1, elem_t ca)
	{
		return Quat<elem_t>(
			LINE2D_INTERSECT(ca, a0, a1, q0.w, q1.w),
			LINE2D_INTERSECT(ca, a0, a1, q0.x, q1.x),
			LINE2D_INTERSECT(ca, a0, a1, q0.y, q1.y),
			LINE2D_INTERSECT(ca, a0, a1, q0.z, q1.z));
	}

	template <typename elem_t>
	inline Vec4<elem_t> lineClipX(const Vec4<elem_t> & v0, const Vec4<elem_t> & v1, elem_t clipx)
	{
		return vec3Build(
			clipx,
			LINE2D_INTERSECT(clipx, v0.x, v1.x, v0.y, v1.y),
			LINE2D_INTERSECT(clipx, v0.x, v1.x, v0.z, v1.z));
	}

	template <typename elem_t>
	inline Vec4<elem_t> lineClipY(const Vec4<elem_t> & v0, const Vec4<elem_t> & v1, elem_t clipy)
	{
		return vec3Build(
			LINE2D_INTERSECT(clipy, v0.y, v1.y, v0.x, v1.x),
			clipy,
			LINE2D_INTERSECT(clipy, v0.y, v1.y, v0.z, v1.z));
	}

	template <typename elem_t>
	inline Vec4<elem_t> lineClipZ(const Vec4<elem_t> & v0, const Vec4<elem_t> & v1, elem_t clipz)
	{
		return vec3Build(
			LINE2D_INTERSECT(clipz, v0.z, v1.z, v0.x, v1.x),
			LINE2D_INTERSECT(clipz, v0.z, v1.z, v0.y, v1.y),
			clipz);
	}

	template <typename elem_t>
	inline bool rgbaIsValid(const Vec4<elem_t> & rhs, elem_t min, elem_t max)
	{
		return rhs.x >= min && rhs.x <= max
			&& rhs.y >= min && rhs.y <= max
			&& rhs.z >= min && rhs.z <= max;
	}

	template <typename elem_t>
	inline Vec4<elem_t> rgbaSaturate(const Vec4<elem_t> & rhs, elem_t intensity = 1.0f)
	{
		return Vec4<elem_t>(
			limit(rhs.x, elem_t(0), intensity),
			limit(rhs.y, elem_t(0), intensity),
			limit(rhs.z, elem_t(0), intensity),
			limit(rhs.w, elem_t(0), intensity));
	}

	template <typename elem_t>
	inline Vec4<elem_t> & rgbaSaturateSelf(Vec4<elem_t> & res, elem_t intensity = 1.0f)
	{
		res.x = limit(res.x, elem_t(0), intensity);
		res.y = limit(res.y, elem_t(0), intensity);
		res.z = limit(res.z, elem_t(0), intensity);
		res.w = limit(res.w, elem_t(0), intensity);
		return res;
	}
}

#endif // __T3DLIB4_H__
