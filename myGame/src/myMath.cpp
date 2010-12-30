
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

#define DISTANCE_ZERO_LIMIT REAL_ZERO_LIMIT

#define INSERT_VERTEX_TO_UP(index0, index1, index2) \
	if(isValidTriangle(v##index0, v##index1, v##index2)) { \
		frontVertexList.push_back(v##index0); \
		frontVertexList.push_back(v##index1); \
		frontVertexList.push_back(v##index2); \
	}

#define INSERT_VERTEX_TO_DOWN(index0, index1, index2) \
	if(isValidTriangle(v##index0, v##index1, v##index2)) { \
		backVertexList.push_back(v##index0); \
		backVertexList.push_back(v##index1); \
		backVertexList.push_back(v##index2); \
	}

	void splitTriangleVertexUp(
		t3d::VertexList & frontVertexList,
		t3d::VertexList & backVertexList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v1, v0);
		t3d::Vec4<real> dir2 = t3d::vec3Sub(v2, v0);

		real intersection1 = calculateLinePlaneIntersection(v0, dir1, planePoint, planeNormal);
		real intersection2 = calculateLinePlaneIntersection(v0, dir2, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);
		_ASSERT(intersection2 >= 0 && intersection2 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v0, t3d::vec3Mul(dir1, intersection1));
		t3d::Vec4<real> v4 = t3d::vec3Add(v0, t3d::vec3Mul(dir2, intersection2));

		if(intersection1 > DISTANCE_ZERO_LIMIT && intersection2 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_TO_UP(0, 3, 4);
		}

		if(intersection1 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_TO_DOWN(3, 1, 2);
		}

		if(intersection2 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_TO_DOWN(3, 2, 4);
		}
	}

	void splitTriangleVertexDown(
		t3d::VertexList & frontVertexList,
		t3d::VertexList & backVertexList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v1, v0);
		t3d::Vec4<real> dir2 = t3d::vec3Sub(v2, v0);

		real intersection1 = calculateLinePlaneIntersection(v0, dir1, planePoint, planeNormal);
		real intersection2 = calculateLinePlaneIntersection(v0, dir2, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);
		_ASSERT(intersection2 >= 0 && intersection2 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v0, t3d::vec3Mul(dir1, intersection1));
		t3d::Vec4<real> v4 = t3d::vec3Add(v0, t3d::vec3Mul(dir2, intersection2));

		if(intersection1 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_TO_UP(1, 2, 3);
		}

		if(intersection2 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_TO_UP(2, 4, 3);
		}

		if(intersection1 > DISTANCE_ZERO_LIMIT && intersection2 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_TO_DOWN(3, 4, 0);
		}
	}

	void splitTriangleVertexLeft(
		t3d::VertexList & frontVertexList,
		t3d::VertexList & backVertexList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v2, v1);

		real intersection1 = calculateLinePlaneIntersection(v1, dir1, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v1, t3d::vec3Mul(dir1, intersection1));

		if(intersection1 < 1 - DISTANCE_ZERO_LIMIT && intersection1 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_TO_UP(1, 3, 0);
		}

		if(intersection1 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_TO_DOWN(0, 3, 2);
		}
	}

	void splitTriangleVertexRight(
		t3d::VertexList & frontVertexList,
		t3d::VertexList & backVertexList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v2, v1);

		real intersection1 = calculateLinePlaneIntersection(v1, dir1, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v1, t3d::vec3Mul(dir1, intersection1));

		if(intersection1 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_TO_UP(2, 0, 3);
		}

		if(intersection1 > DISTANCE_ZERO_LIMIT && intersection1 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_TO_DOWN(3, 0, 1);
		}
	}

#define INSERT_TRIANGLE_VERTEX_UP(index0, index1, index2) \
	splitTriangleVertexUp( \
		frontVertexList, \
		backVertexList, \
		v##index0, \
		v##index1, \
		v##index2, \
		planePoint, \
		planeNormal);

#define INSERT_TRIANGLE_VERTEX_DOWN(index0, index1, index2) \
	splitTriangleVertexDown( \
		frontVertexList, \
		backVertexList, \
		v##index0, \
		v##index1, \
		v##index2, \
		planePoint, \
		planeNormal);

#define INSERT_TRIANGLE_VERTEX_LEFT(index0, index1, index2) \
	splitTriangleVertexLeft( \
		frontVertexList, \
		backVertexList, \
		v##index0, \
		v##index1, \
		v##index2, \
		planePoint, \
		planeNormal);

#define INSERT_TRIANGLE_VERTEX_RIGHT(index0, index1, index2) \
	splitTriangleVertexRight( \
		frontVertexList, \
		backVertexList, \
		v##index0, \
		v##index1, \
		v##index2, \
		planePoint, \
		planeNormal);

	bool splitTriangleVertex(
		t3d::VertexList & frontVertexList,
		t3d::VertexList & backVertexList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		real d0 = calculatePointPlaneDistance(v0, planePoint, planeNormal);
		real d1 = calculatePointPlaneDistance(v1, planePoint, planeNormal);
		real d2 = calculatePointPlaneDistance(v2, planePoint, planeNormal);

		if(d0 > DISTANCE_ZERO_LIMIT)
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_DOWN(2, 0, 1);
				}
				else
				{
					INSERT_VERTEX_TO_UP(0, 1, 2);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_DOWN(1, 2, 0);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UP(0, 1, 2);
				}
				else
				{
					INSERT_TRIANGLE_VERTEX_LEFT(2, 0, 1);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_RIGHT(1, 2, 0);
				}
				else
				{
					INSERT_VERTEX_TO_UP(0, 1, 2);
				}
			}
		}
		else if(d0 < -DISTANCE_ZERO_LIMIT)
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_DOWN(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UP(1, 2, 0);
				}
				else
				{
					INSERT_TRIANGLE_VERTEX_RIGHT(2, 0, 1);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UP(2, 0, 1);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_TO_DOWN(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_TO_DOWN(0, 1, 2);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_LEFT(1, 2, 0);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_TO_DOWN(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_TO_DOWN(0, 1, 2);
				}
			}
		}
		else
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_LEFT(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_TO_UP(0, 1, 2);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_RIGHT(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_TO_DOWN(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_TO_DOWN(0, 1, 2);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_TO_DOWN(0, 1, 2);
				}
				else
				{
					return false;
				}
			}
		}

		return true;
	}

#define INSERT_VERTEX_NORMAL_TO_UP(index0, index1, index2) \
	if(isValidTriangle(v##index0, v##index1, v##index2)) { \
		frontVertexList.push_back(v##index0); \
		frontVertexList.push_back(v##index1); \
		frontVertexList.push_back(v##index2); \
		frontNormalList.push_back(n##index0); \
		frontNormalList.push_back(n##index1); \
		frontNormalList.push_back(n##index2); \
	}

#define INSERT_VERTEX_NORMAL_TO_DOWN(index0, index1, index2) \
	if(isValidTriangle(v##index0, v##index1, v##index2)) { \
		backVertexList.push_back(v##index0); \
		backVertexList.push_back(v##index1); \
		backVertexList.push_back(v##index2); \
		backNormalList.push_back(n##index0); \
		backNormalList.push_back(n##index1); \
		backNormalList.push_back(n##index2); \
	}

	void splitTriangleVertexNormalUp(
		t3d::VertexList & frontVertexList,
		t3d::NormalList & frontNormalList,
		t3d::VertexList & backVertexList,
		t3d::NormalList & backNormalList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v1, v0);
		t3d::Vec4<real> dir2 = t3d::vec3Sub(v2, v0);

		real intersection1 = calculateLinePlaneIntersection(v0, dir1, planePoint, planeNormal);
		real intersection2 = calculateLinePlaneIntersection(v0, dir2, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);
		_ASSERT(intersection2 >= 0 && intersection2 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v0, t3d::vec3Mul(dir1, intersection1));
		t3d::Vec4<real> v4 = t3d::vec3Add(v0, t3d::vec3Mul(dir2, intersection2));

		t3d::Vec4<real> n3 = t3d::vec3Add(n0, t3d::vec3Mul(t3d::vec3Sub(n1, n0), intersection1));
		t3d::Vec4<real> n4 = t3d::vec3Add(n0, t3d::vec3Mul(t3d::vec3Sub(n2, n0), intersection2));

		if(intersection1 > DISTANCE_ZERO_LIMIT && intersection2 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_TO_UP(0, 3, 4);
		}

		if(intersection1 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_TO_DOWN(3, 1, 2);
		}

		if(intersection2 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_TO_DOWN(3, 2, 4);
		}
	}

	void splitTriangleVertexNormalDown(
		t3d::VertexList & frontVertexList,
		t3d::NormalList & frontNormalList,
		t3d::VertexList & backVertexList,
		t3d::NormalList & backNormalList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v1, v0);
		t3d::Vec4<real> dir2 = t3d::vec3Sub(v2, v0);

		real intersection1 = calculateLinePlaneIntersection(v0, dir1, planePoint, planeNormal);
		real intersection2 = calculateLinePlaneIntersection(v0, dir2, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);
		_ASSERT(intersection2 >= 0 && intersection2 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v0, t3d::vec3Mul(dir1, intersection1));
		t3d::Vec4<real> v4 = t3d::vec3Add(v0, t3d::vec3Mul(dir2, intersection2));

		t3d::Vec4<real> n3 = t3d::vec3Add(n0, t3d::vec3Mul(t3d::vec3Sub(n1, n0), intersection1));
		t3d::Vec4<real> n4 = t3d::vec3Add(n0, t3d::vec3Mul(t3d::vec3Sub(n2, n0), intersection2));

		if(intersection1 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_TO_UP(1, 2, 3);
		}

		if(intersection2 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_TO_UP(2, 4, 3);
		}

		if(intersection1 > DISTANCE_ZERO_LIMIT && intersection2 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_TO_DOWN(3, 4, 0);
		}
	}

	void splitTriangleVertexNormalLeft(
		t3d::VertexList & frontVertexList,
		t3d::NormalList & frontNormalList,
		t3d::VertexList & backVertexList,
		t3d::NormalList & backNormalList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v2, v1);

		real intersection1 = calculateLinePlaneIntersection(v1, dir1, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v1, t3d::vec3Mul(dir1, intersection1));

		t3d::Vec4<real> n3 = t3d::vec3Add(n1, t3d::vec3Mul(t3d::vec3Sub(n2, n1), intersection1));

		if(intersection1 < 1 - DISTANCE_ZERO_LIMIT && intersection1 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_TO_UP(1, 3, 0);
		}

		if(intersection1 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_TO_DOWN(0, 3, 2);
		}
	}

	void splitTriangleVertexNormalRight(
		t3d::VertexList & frontVertexList,
		t3d::NormalList & frontNormalList,
		t3d::VertexList & backVertexList,
		t3d::NormalList & backNormalList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v2, v1);

		real intersection1 = calculateLinePlaneIntersection(v1, dir1, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v1, t3d::vec3Mul(dir1, intersection1));

		t3d::Vec4<real> n3 = t3d::vec3Add(n1, t3d::vec3Mul(t3d::vec3Sub(n2, n1), intersection1));

		if(intersection1 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_TO_UP(2, 0, 3);
		}

		if(intersection1 > DISTANCE_ZERO_LIMIT && intersection1 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_TO_DOWN(3, 0, 1);
		}
	}

#define INSERT_TRIANGLE_VERTEX_NORMAL_UP(index0, index1, index2) \
	splitTriangleVertexNormalUp( \
		frontVertexList, \
		frontNormalList, \
		backVertexList, \
		backNormalList, \
		v##index0, \
		v##index1, \
		v##index2, \
		n##index0, \
		n##index1, \
		n##index2, \
		planePoint, planeNormal);

#define INSERT_TRIANGLE_VERTEX_NORMAL_DOWN(index0, index1, index2) \
	splitTriangleVertexNormalDown( \
		frontVertexList, \
		frontNormalList, \
		backVertexList, \
		backNormalList, \
		v##index0, \
		v##index1, \
		v##index2, \
		n##index0, \
		n##index1, \
		n##index2, \
		planePoint, planeNormal);

#define INSERT_TRIANGLE_VERTEX_NORMAL_LEFT(index0, index1, index2) \
	splitTriangleVertexNormalLeft( \
		frontVertexList, \
		frontNormalList, \
		backVertexList, \
		backNormalList, \
		v##index0, \
		v##index1, \
		v##index2, \
		n##index0, \
		n##index1, \
		n##index2, \
		planePoint, planeNormal);

#define INSERT_TRIANGLE_VERTEX_NORMAL_RIGHT(index0, index1, index2) \
	splitTriangleVertexNormalRight( \
		frontVertexList, \
		frontNormalList, \
		backVertexList, \
		backNormalList, \
		v##index0, \
		v##index1, \
		v##index2, \
		n##index0, \
		n##index1, \
		n##index2, \
		planePoint, planeNormal);

	bool splitTriangleVertexNormal(
		t3d::VertexList & frontVertexList,
		t3d::NormalList & frontNormalList,
		t3d::VertexList & backVertexList,
		t3d::NormalList & backNormalList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		real d0 = calculatePointPlaneDistance(v0, planePoint, planeNormal);
		real d1 = calculatePointPlaneDistance(v1, planePoint, planeNormal);
		real d2 = calculatePointPlaneDistance(v2, planePoint, planeNormal);

		if(d0 > DISTANCE_ZERO_LIMIT)
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_DOWN(2, 0, 1);
				}
				else
				{
					INSERT_VERTEX_NORMAL_TO_UP(0, 1, 2);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_DOWN(1, 2, 0);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UP(0, 1, 2);
				}
				else
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_LEFT(2, 0, 1);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_RIGHT(1, 2, 0);
				}
				else
				{
					INSERT_VERTEX_NORMAL_TO_UP(0, 1, 2);
				}
			}
		}
		else if(d0 < -DISTANCE_ZERO_LIMIT)
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_DOWN(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UP(1, 2, 0);
				}
				else
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_RIGHT(2, 0, 1);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UP(2, 0, 1);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_TO_DOWN(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_NORMAL_TO_DOWN(0, 1, 2);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_LEFT(1, 2, 0);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_TO_DOWN(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_NORMAL_TO_DOWN(0, 1, 2);
				}
			}
		}
		else
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_LEFT(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_NORMAL_TO_UP(0, 1, 2);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_RIGHT(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_TO_DOWN(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_NORMAL_TO_DOWN(0, 1, 2);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_TO_DOWN(0, 1, 2);
				}
				else
				{
					return false;
				}
			}
		}

		return true;
	}

#define INSERT_VERTEX_UV_TO_UP(index0, index1, index2) \
	if(isValidTriangle(v##index0, v##index1, v##index2)) { \
		frontVertexList.push_back(v##index0); \
		frontVertexList.push_back(v##index1); \
		frontVertexList.push_back(v##index2); \
		frontUVList.push_back(t##index0); \
		frontUVList.push_back(t##index1); \
		frontUVList.push_back(t##index2); \
	}

#define INSERT_VERTEX_UV_TO_DOWN(index0, index1, index2) \
	if(isValidTriangle(v##index0, v##index1, v##index2)) { \
		backVertexList.push_back(v##index0); \
		backVertexList.push_back(v##index1); \
		backVertexList.push_back(v##index2); \
		backUVList.push_back(t##index0); \
		backUVList.push_back(t##index1); \
		backUVList.push_back(t##index2); \
	}

	void splitTriangleVertexUVUp(
		t3d::VertexList & frontVertexList,
		t3d::UVList & frontUVList,
		t3d::VertexList & backVertexList,
		t3d::UVList & backUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v1, v0);
		t3d::Vec4<real> dir2 = t3d::vec3Sub(v2, v0);

		real intersection1 = calculateLinePlaneIntersection(v0, dir1, planePoint, planeNormal);
		real intersection2 = calculateLinePlaneIntersection(v0, dir2, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);
		_ASSERT(intersection2 >= 0 && intersection2 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v0, t3d::vec3Mul(dir1, intersection1));
		t3d::Vec4<real> v4 = t3d::vec3Add(v0, t3d::vec3Mul(dir2, intersection2));

		t3d::Vec2<real> t3 = t0 + (t1 - t0) * intersection1;
		t3d::Vec2<real> t4 = t0 + (t2 - t0) * intersection2;

		if(intersection1 > DISTANCE_ZERO_LIMIT && intersection2 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_UV_TO_UP(0, 3, 4);
		}

		if(intersection1 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_UV_TO_DOWN(3, 1, 2);
		}

		if(intersection2 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_UV_TO_DOWN(3, 2, 4);
		}
	}

	void splitTriangleVertexUVDown(
		t3d::VertexList & frontVertexList,
		t3d::UVList & frontUVList,
		t3d::VertexList & backVertexList,
		t3d::UVList & backUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v1, v0);
		t3d::Vec4<real> dir2 = t3d::vec3Sub(v2, v0);

		real intersection1 = calculateLinePlaneIntersection(v0, dir1, planePoint, planeNormal);
		real intersection2 = calculateLinePlaneIntersection(v0, dir2, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);
		_ASSERT(intersection2 >= 0 && intersection2 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v0, t3d::vec3Mul(dir1, intersection1));
		t3d::Vec4<real> v4 = t3d::vec3Add(v0, t3d::vec3Mul(dir2, intersection2));

		t3d::Vec2<real> t3 = t0 + (t1 - t0) * intersection1;
		t3d::Vec2<real> t4 = t0 + (t2 - t0) * intersection2;

		if(intersection1 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_UV_TO_UP(1, 2, 3);
		}

		if(intersection2 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_UV_TO_UP(2, 4, 3);
		}

		if(intersection1 > DISTANCE_ZERO_LIMIT && intersection2 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_UV_TO_DOWN(3, 4, 0);
		}
	}

	void splitTriangleVertexUVLeft(
		t3d::VertexList & frontVertexList,
		t3d::UVList & frontUVList,
		t3d::VertexList & backVertexList,
		t3d::UVList & backUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v2, v1);

		real intersection1 = calculateLinePlaneIntersection(v1, dir1, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v1, t3d::vec3Mul(dir1, intersection1));

		t3d::Vec2<real> t3 = t1 + (t2 - t1) * intersection1;

		if(intersection1 < 1 - DISTANCE_ZERO_LIMIT && intersection1 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_UV_TO_UP(1, 3, 0);
		}

		if(intersection1 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_UV_TO_DOWN(0, 3, 2);
		}
	}

	void splitTriangleVertexUVRight(
		t3d::VertexList & frontVertexList,
		t3d::UVList & frontUVList,
		t3d::VertexList & backVertexList,
		t3d::UVList & backUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v2, v1);

		real intersection1 = calculateLinePlaneIntersection(v1, dir1, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v1, t3d::vec3Mul(dir1, intersection1));

		t3d::Vec2<real> t3 = t1 + (t2 - t1) * intersection1;

		if(intersection1 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_UV_TO_UP(2, 0, 3);
		}

		if(intersection1 > DISTANCE_ZERO_LIMIT && intersection1 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_UV_TO_DOWN(3, 0, 1);
		}
	}

#define INSERT_TRIANGLE_VERTEX_UV_UP(index0, index1, index2) \
	splitTriangleVertexUVUp( \
		frontVertexList, \
		frontUVList, \
		backVertexList, \
		backUVList, \
		v##index0, \
		v##index1, \
		v##index2, \
		t##index0, \
		t##index1, \
		t##index2, \
		planePoint, \
		planeNormal);

#define INSERT_TRIANGLE_VERTEX_UV_DOWN(index0, index1, index2) \
	splitTriangleVertexUVDown( \
		frontVertexList, \
		frontUVList, \
		backVertexList, \
		backUVList, \
		v##index0, \
		v##index1, \
		v##index2, \
		t##index0, \
		t##index1, \
		t##index2, \
		planePoint, \
		planeNormal);

#define INSERT_TRIANGLE_VERTEX_UV_LEFT(index0, index1, index2) \
	splitTriangleVertexUVLeft( \
		frontVertexList, \
		frontUVList, \
		backVertexList, \
		backUVList, \
		v##index0, \
		v##index1, \
		v##index2, \
		t##index0, \
		t##index1, \
		t##index2, \
		planePoint, \
		planeNormal);

#define INSERT_TRIANGLE_VERTEX_UV_RIGHT(index0, index1, index2) \
	splitTriangleVertexUVRight( \
		frontVertexList, \
		frontUVList, \
		backVertexList, \
		backUVList, \
		v##index0, \
		v##index1, \
		v##index2, \
		t##index0, \
		t##index1, \
		t##index2, \
		planePoint, \
		planeNormal);

	bool splitTriangleVertexUV(
		t3d::VertexList & frontVertexList,
		t3d::UVList & frontUVList,
		t3d::VertexList & backVertexList,
		t3d::UVList & backUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal)
	{
		real d0 = calculatePointPlaneDistance(v0, planePoint, planeNormal);
		real d1 = calculatePointPlaneDistance(v1, planePoint, planeNormal);
		real d2 = calculatePointPlaneDistance(v2, planePoint, planeNormal);

		if(d0 > DISTANCE_ZERO_LIMIT)
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_UV_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UV_DOWN(2, 0, 1);
				}
				else
				{
					INSERT_VERTEX_UV_TO_UP(0, 1, 2);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UV_DOWN(1, 2, 0);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UV_UP(0, 1, 2);
				}
				else
				{
					INSERT_TRIANGLE_VERTEX_UV_LEFT(2, 0, 1);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_UV_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UV_RIGHT(1, 2, 0);
				}
				else
				{
					INSERT_VERTEX_UV_TO_UP(0, 1, 2);
				}
			}
		}
		else if(d0 < -DISTANCE_ZERO_LIMIT)
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UV_DOWN(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UV_UP(1, 2, 0);
				}
				else
				{
					INSERT_TRIANGLE_VERTEX_UV_RIGHT(2, 0, 1);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UV_UP(2, 0, 1);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_UV_TO_DOWN(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_UV_TO_DOWN(0, 1, 2);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UV_LEFT(1, 2, 0);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_UV_TO_DOWN(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_UV_TO_DOWN(0, 1, 2);
				}
			}
		}
		else
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_UV_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UV_LEFT(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_UV_TO_UP(0, 1, 2);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_UV_RIGHT(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_UV_TO_DOWN(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_UV_TO_DOWN(0, 1, 2);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_UV_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_UV_TO_DOWN(0, 1, 2);
				}
				else
				{
					return false;
				}
			}
		}

		return true;
	}

#define INSERT_VERTEX_NORMAL_UV_TO_UP(index0, index1, index2) \
	if(isValidTriangle(v##index0, v##index1, v##index2)) { \
		frontVertexList.push_back(v##index0); \
		frontVertexList.push_back(v##index1); \
		frontVertexList.push_back(v##index2); \
		frontNormalList.push_back(n##index0); \
		frontNormalList.push_back(n##index1); \
		frontNormalList.push_back(n##index2); \
		frontUVList.push_back(t##index0); \
		frontUVList.push_back(t##index1); \
		frontUVList.push_back(t##index2); \
	}

#define INSERT_VERTEX_NORMAL_UV_TO_DOWN(index0, index1, index2) \
	if(isValidTriangle(v##index0, v##index1, v##index2)) { \
		backVertexList.push_back(v##index0); \
		backVertexList.push_back(v##index1); \
		backVertexList.push_back(v##index2); \
		backNormalList.push_back(n##index0); \
		backNormalList.push_back(n##index1); \
		backNormalList.push_back(n##index2); \
		backUVList.push_back(t##index0); \
		backUVList.push_back(t##index1); \
		backUVList.push_back(t##index2); \
	}

	void splitTriangleVertexNormalUVUp(
		t3d::VertexList & frontVertexList,
		t3d::NormalList & frontNormalList,
		t3d::UVList & frontUVList,
		t3d::VertexList & backVertexList,
		t3d::NormalList & backNormalList,
		t3d::UVList & backUVList,
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
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v1, v0);
		t3d::Vec4<real> dir2 = t3d::vec3Sub(v2, v0);

		real intersection1 = calculateLinePlaneIntersection(v0, dir1, planePoint, planeNormal);
		real intersection2 = calculateLinePlaneIntersection(v0, dir2, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);
		_ASSERT(intersection2 >= 0 && intersection2 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v0, t3d::vec3Mul(dir1, intersection1));
		t3d::Vec4<real> v4 = t3d::vec3Add(v0, t3d::vec3Mul(dir2, intersection2));

		t3d::Vec4<real> n3 = t3d::vec3Add(n0, t3d::vec3Mul(t3d::vec3Sub(n1, n0), intersection1));
		t3d::Vec4<real> n4 = t3d::vec3Add(n0, t3d::vec3Mul(t3d::vec3Sub(n2, n0), intersection2));

		t3d::Vec2<real> t3 = t0 + (t1 - t0) * intersection1;
		t3d::Vec2<real> t4 = t0 + (t2 - t0) * intersection2;

		if(intersection1 > DISTANCE_ZERO_LIMIT && intersection2 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_UV_TO_UP(0, 3, 4);
		}

		if(intersection1 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_UV_TO_DOWN(3, 1, 2);
		}

		if(intersection2 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_UV_TO_DOWN(3, 2, 4);
		}
	}

	void splitTriangleVertexNormalUVDown(
		t3d::VertexList & frontVertexList,
		t3d::NormalList & frontNormalList,
		t3d::UVList & frontUVList,
		t3d::VertexList & backVertexList,
		t3d::NormalList & backNormalList,
		t3d::UVList & backUVList,
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
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v1, v0);
		t3d::Vec4<real> dir2 = t3d::vec3Sub(v2, v0);

		real intersection1 = calculateLinePlaneIntersection(v0, dir1, planePoint, planeNormal);
		real intersection2 = calculateLinePlaneIntersection(v0, dir2, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);
		_ASSERT(intersection2 >= 0 && intersection2 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v0, t3d::vec3Mul(dir1, intersection1));
		t3d::Vec4<real> v4 = t3d::vec3Add(v0, t3d::vec3Mul(dir2, intersection2));

		t3d::Vec4<real> n3 = t3d::vec3Add(n0, t3d::vec3Mul(t3d::vec3Sub(n1, n0), intersection1));
		t3d::Vec4<real> n4 = t3d::vec3Add(n0, t3d::vec3Mul(t3d::vec3Sub(n2, n0), intersection2));

		t3d::Vec2<real> t3 = t0 + (t1 - t0) * intersection1;
		t3d::Vec2<real> t4 = t0 + (t2 - t0) * intersection2;

		if(intersection1 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_UV_TO_UP(1, 2, 3);
		}

		if(intersection2 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_UV_TO_UP(2, 4, 3);
		}

		if(intersection1 > DISTANCE_ZERO_LIMIT && intersection2 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_UV_TO_DOWN(3, 4, 0);
		}
	}

	void splitTriangleVertexNormalUVLeft(
		t3d::VertexList & frontVertexList,
		t3d::NormalList & frontNormalList,
		t3d::UVList & frontUVList,
		t3d::VertexList & backVertexList,
		t3d::NormalList & backNormalList,
		t3d::UVList & backUVList,
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
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v2, v1);

		real intersection1 = calculateLinePlaneIntersection(v1, dir1, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v1, t3d::vec3Mul(dir1, intersection1));

		t3d::Vec4<real> n3 = t3d::vec3Add(n1, t3d::vec3Mul(t3d::vec3Sub(n2, n1), intersection1));

		t3d::Vec2<real> t3 = t1 + (t2 - t1) * intersection1;

		if(intersection1 < 1 - DISTANCE_ZERO_LIMIT && intersection1 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_UV_TO_UP(1, 3, 0);
		}

		if(intersection1 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_UV_TO_DOWN(0, 3, 2);
		}
	}

	void splitTriangleVertexNormalUVRight(
		t3d::VertexList & frontVertexList,
		t3d::NormalList & frontNormalList,
		t3d::UVList & frontUVList,
		t3d::VertexList & backVertexList,
		t3d::NormalList & backNormalList,
		t3d::UVList & backUVList,
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
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v2, v1);

		real intersection1 = calculateLinePlaneIntersection(v1, dir1, planePoint, planeNormal);

		_ASSERT(intersection1 >= 0 && intersection1 <= 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v1, t3d::vec3Mul(dir1, intersection1));

		t3d::Vec4<real> n3 = t3d::vec3Add(n1, t3d::vec3Mul(t3d::vec3Sub(n2, n1), intersection1));

		t3d::Vec2<real> t3 = t1 + (t2 - t1) * intersection1;

		if(intersection1 > DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_UV_TO_UP(2, 0, 3);
		}

		if(intersection1 > DISTANCE_ZERO_LIMIT && intersection1 < 1 - DISTANCE_ZERO_LIMIT)
		{
			INSERT_VERTEX_NORMAL_UV_TO_DOWN(3, 0, 1);
		}
	}

#define INSERT_TRIANGLE_VERTEX_NORMAL_UV_UP(index0, index1, index2) \
	splitTriangleVertexNormalUVUp( \
		frontVertexList, \
		frontNormalList, \
		frontUVList, \
		backVertexList, \
		backNormalList, \
		backUVList, \
		v##index0, \
		v##index1, \
		v##index2, \
		n##index0, \
		n##index1, \
		n##index2, \
		t##index0, \
		t##index1, \
		t##index2, \
		planePoint, \
		planeNormal);

#define INSERT_TRIANGLE_VERTEX_NORMAL_UV_DOWN(index0, index1, index2) \
	splitTriangleVertexNormalUVDown( \
		frontVertexList, \
		frontNormalList, \
		frontUVList, \
		backVertexList, \
		backNormalList, \
		backUVList, \
		v##index0, \
		v##index1, \
		v##index2, \
		n##index0, \
		n##index1, \
		n##index2, \
		t##index0, \
		t##index1, \
		t##index2, \
		planePoint, \
		planeNormal);

#define INSERT_TRIANGLE_VERTEX_NORMAL_UV_LEFT(index0, index1, index2) \
	splitTriangleVertexNormalUVLeft( \
		frontVertexList, \
		frontNormalList, \
		frontUVList, \
		backVertexList, \
		backNormalList, \
		backUVList, \
		v##index0, \
		v##index1, \
		v##index2, \
		n##index0, \
		n##index1, \
		n##index2, \
		t##index0, \
		t##index1, \
		t##index2, \
		planePoint, \
		planeNormal);

#define INSERT_TRIANGLE_VERTEX_NORMAL_UV_RIGHT(index0, index1, index2) \
	splitTriangleVertexNormalUVRight( \
		frontVertexList, \
		frontNormalList, \
		frontUVList, \
		backVertexList, \
		backNormalList, \
		backUVList, \
		v##index0, \
		v##index1, \
		v##index2, \
		n##index0, \
		n##index1, \
		n##index2, \
		t##index0, \
		t##index1, \
		t##index2, \
		planePoint, \
		planeNormal);

	bool splitTriangleVertexNormalUV(
		t3d::VertexList & frontVertexList,
		t3d::NormalList & frontNormalList,
		t3d::UVList & frontUVList,
		t3d::VertexList & backVertexList,
		t3d::NormalList & backNormalList,
		t3d::UVList & backUVList,
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
		const t3d::Vec4<real> & planeNormal)
	{
		real d0 = calculatePointPlaneDistance(v0, planePoint, planeNormal);
		real d1 = calculatePointPlaneDistance(v1, planePoint, planeNormal);
		real d2 = calculatePointPlaneDistance(v2, planePoint, planeNormal);

		if(d0 > DISTANCE_ZERO_LIMIT)
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_DOWN(2, 0, 1);
				}
				else
				{
					INSERT_VERTEX_NORMAL_UV_TO_UP(0, 1, 2);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_DOWN(1, 2, 0);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_UP(0, 1, 2);
				}
				else
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_LEFT(2, 0, 1);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_RIGHT(1, 2, 0);
				}
				else
				{
					INSERT_VERTEX_NORMAL_UV_TO_UP(0, 1, 2);
				}
			}
		}
		else if(d0 < -DISTANCE_ZERO_LIMIT)
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_DOWN(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_UP(1, 2, 0);
				}
				else
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_RIGHT(2, 0, 1);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_UP(2, 0, 1);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_DOWN(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_NORMAL_UV_TO_DOWN(0, 1, 2);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_LEFT(1, 2, 0);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_DOWN(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_NORMAL_UV_TO_DOWN(0, 1, 2);
				}
			}
		}
		else
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_LEFT(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_NORMAL_UV_TO_UP(0, 1, 2);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_RIGHT(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_DOWN(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_NORMAL_UV_TO_DOWN(0, 1, 2);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_UP(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_DOWN(0, 1, 2);
				}
				else
				{
					return false;
				}
			}
		}

		return true;
	}
}
