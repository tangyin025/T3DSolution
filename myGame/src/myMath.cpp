
#include "stdafx.h"
#include "myMath.h"

namespace my
{
	const Vec2<real> Vec2<real>::ZERO(0, 0);

	const Vec2<real> Vec2<real>::UNIT_X(1, 0);

	const Vec2<real> Vec2<real>::UNIT_Y(0, 1);

	const Vec2<real> Vec2<real>::NEGATIVE_UNIT_X(-1, 0);

	const Vec2<real> Vec2<real>::NEGATIVE_UNIT_Y(0, -1);

	const Vec2<real> Vec2<real>::UNIT_SCALE(1, 1);

	const Vec4<real> Vec4<real>::ZERO(0, 0, 0, 1);

	const Vec4<real> Vec4<real>::UNIT_X(1, 0, 0, 1);

	const Vec4<real> Vec4<real>::UNIT_Y(0, 1, 0, 1);

	const Vec4<real> Vec4<real>::UNIT_Z(0, 0, 1, 1);

	//const Vec4<real> Vec4<real>::UNIT_W(0, 0, 0, 1);

	const Vec4<real> Vec4<real>::UNIT_SCALE(1, 1, 1, 1);

	const Vec4<real> Vec4<real>::NEGATIVE_UNIT_X(-1, 0, 0, 1);

	const Vec4<real> Vec4<real>::NEGATIVE_UNIT_Y(0, -1, 0, 1);

	const Vec4<real> Vec4<real>::NEGATIVE_UNIT_Z(0, 0, -1, 1);

	//const Vec4<real> Vec4<real>::NEGATIVE_UNIT_W(0, 0, 0, -1);

	const Vec4<real> Vec4<real>::NEGATIVE_UNIT_SCALE(-1, -1, -1, 1);

	const Mat4<real> Mat4<real>::ZERO(	0, 0, 0, 0,
										0, 0, 0, 0,
										0, 0, 0, 0,
										0, 0, 0, 0);

	const Mat4<real> Mat4<real>::IDENTITY(	1, 0, 0, 0,
											0, 1, 0, 0,
											0, 0, 1, 0,
											0, 0, 0, 1);

	const Quat<real> Quat<real>::ZERO(0, 0, 0, 0);

	const Quat<real> Quat<real>::IDENTITY(1, 0, 0, 0);

	const Color Color::WHITE(1, 1, 1);

	const Color Color::RED(1, 0, 0);

	const Color Color::GREEN(0, 1, 0);

	const Color Color::BLUE(0, 0, 1);

	const Color Color::BLACK(0, 0, 0);

	const Color Color::YELLOW(1, 1, 0);
}
