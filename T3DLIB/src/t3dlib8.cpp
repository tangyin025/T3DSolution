
#include "stdafx.h"
#include "t3dlib8.h"
#include "t3dlib5.h"

namespace t3d
{
	void fillStencilBuffer(
		SurfaceRef<int> stencilbuff,
		const CRect & rect,
		int value)
	{
		for(int i = rect.top; i < rect.bottom; i++)
		{
			memSet32((int *)&stencilbuff[i][rect.left], value, rect.Width());
		}
	}

	void countScanIncrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz)
	{
#define __draw_behind_depth
#define __draw_increment
#include "count_scan.hpp"
	}

	void countScanDecrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz)
	{
#define __draw_behind_depth
#define __draw_decrement
#include "count_scan.hpp"
	}

	void countClippedScanIncrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz)
	{
#define __draw_behind_depth
#define __draw_increment
#define __draw_clipped
#include "count_scan.hpp"
	}

	void countClippedScanDecrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz)
	{
#define __draw_behind_depth
#define __draw_decrement
#define __draw_clipped
#include "count_scan.hpp"
	}

	void countScanIncrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz)
	{
#define __draw_in_front_of_depth
#define __draw_increment
#include "count_scan.hpp"
	}

	void countScanDecrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz)
	{
#define __draw_in_front_of_depth
#define __draw_decrement
#include "count_scan.hpp"
	}

	void countClippedScanIncrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz)
	{
#define __draw_in_front_of_depth
#define __draw_increment
#define __draw_clipped
#include "count_scan.hpp"
	}

	void countClippedScanDecrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz)
	{
#define __draw_in_front_of_depth
#define __draw_decrement
#define __draw_clipped
#include "count_scan.hpp"
	}

	void countTriangleIncrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2)
	{
#define __draw_func countScanIncrementBehindDepth
#include "count_triangle.hpp"
	}

	void countTriangleDecrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2)
	{
#define __draw_func countScanDecrementBehindDepth
#include "count_triangle.hpp"
	}

	void countClippedTriangleIncrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2)
	{
#define __draw_clipped
#define __draw_func countScanIncrementBehindDepth
#define __draw_clipped_func countClippedScanIncrementBehindDepth
#include "count_triangle.hpp"
	}

	void countClippedTriangleDecrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2)
	{
#define __draw_clipped
#define __draw_func countScanDecrementBehindDepth
#define __draw_clipped_func countClippedScanDecrementBehindDepth
#include "count_triangle.hpp"
	}

	void countTriangleIncrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2)
	{
#define __draw_func countScanIncrementInFrontOfDepth
#include "count_triangle.hpp"
	}

	void countTriangleDecrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2)
	{
#define __draw_func countScanDecrementInFrontOfDepth
#include "count_triangle.hpp"
	}

	void countClippedTriangleIncrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2)
	{
#define __draw_clipped
#define __draw_func countScanIncrementInFrontOfDepth
#define __draw_clipped_func countClippedScanIncrementInFrontOfDepth
#include "count_triangle.hpp"
	}

	void countClippedTriangleDecrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2)
	{
#define __draw_clipped
#define __draw_func countScanDecrementInFrontOfDepth
#define __draw_clipped_func countClippedScanDecrementInFrontOfDepth
#include "count_triangle.hpp"
	}

	void boundSurfaceStencilBufferColor16(
		SurfaceRef<uint16> surface,
		const CRect & rect,
		SurfaceRef<int> stencilbuff,
		const t3d::Vec4<real> & color)
	{
		for(int y = rect.top; y < rect.bottom; y++)
		{
			for(int x = rect.left; x < rect.right; x++)
			{
				if(stencilbuff[y][x] > 0)
				{
					surface[y][x] = _RGB16BIT_WITHOUT_RSHIFT(
						_COLORMUL(_RGB16GETR(surface[y][x]), real_to_int(color.x)),
						_COLORMUL(_RGB16GETG(surface[y][x]), real_to_int(color.y)),
						_COLORMUL(_RGB16GETB(surface[y][x]), real_to_int(color.z)));
				}
			}
		}
	}

	void boundSurfaceStencilBufferColor32(
		SurfaceRef<uint32> surface,
		const CRect & rect,
		SurfaceRef<int> stencilbuff,
		const t3d::Vec4<real> & color)
	{
		for(int y = rect.top; y < rect.bottom; y++)
		{
			for(int x = rect.left; x < rect.right; x++)
			{
				if(stencilbuff[y][x] > 0)
				{
					surface[y][x] = _RGB32BIT(
						_COLORMUL(_RGB32GETR(surface[y][x]), real_to_int(color.x)),
						_COLORMUL(_RGB32GETG(surface[y][x]), real_to_int(color.y)),
						_COLORMUL(_RGB32GETB(surface[y][x]), real_to_int(color.z)));
				}
			}
		}
	}

	CLIP_STATE clipTriangleFrontfaceAtWorld(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & eye)
	{
		return vec3Dot(vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(eye, v0)) > 0 ? CLIP_STATE_CULLED : CLIP_STATE_NONE;
	}

	void removeTriangleListFrontfaceAtWorld(
		const VertexList & vertexList,
		ClipStateList & clipStateList,
		const Vec4<real> & eye)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				clipStateList[i] = clipTriangleFrontfaceAtWorld(
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					eye);
			}
		}
	}

	void removeTriangleIndexListFrontfaceAtWorld(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const Vec4<real> & eye)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				clipStateList[i] = clipTriangleFrontfaceAtWorld(
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					eye);
			}
		}
	}

	ConnectionEdgeList & buildConnectionEdgeListFromTriangleList(
		ConnectionEdgeList & retConnectionEdgeList,
		const VertexList & vertexList)
	{
		_ASSERT(retConnectionEdgeList.empty());
		_ASSERT(vertexList.size() % 3 == 0);

		for(size_t i = 0; i < vertexList.size(); i += 3)
		{
			for(int j = 0; j < 3; j++)
			{
				const Vec4<real> & v0 = vertexList[i + (j + 0) % 3];
				const Vec4<real> & v1 = vertexList[i + (j + 1) % 3];

				ConnectionEdgeList::iterator connection_edge_iter = retConnectionEdgeList.begin();
				for(; connection_edge_iter != retConnectionEdgeList.end(); connection_edge_iter++)
				{
					const Vec4<real> & ev0 = vertexList[connection_edge_iter->v0_i];
					const Vec4<real> & ev1 = vertexList[connection_edge_iter->v1_i];

					if(vec3IsEqual(v1, ev0) && vec3IsEqual(v0, ev1))
					{
						if(connection_edge_iter->tri1_i != SIZE_MAX)
						{
							_ASSERT(false); continue; // ***
						}

						connection_edge_iter->tri1_i = i / 3;
						break;
					}
				}

				if(retConnectionEdgeList.end() == connection_edge_iter)
				{
					ConnectionEdge silhouetteEdge;
					silhouetteEdge.v0_i = i + (j + 0) % 3;
					silhouetteEdge.v1_i = i + (j + 1) % 3;
					silhouetteEdge.tri0_i = i / 3;
					silhouetteEdge.tri1_i = SIZE_MAX;

					retConnectionEdgeList.push_back(silhouetteEdge);
				}
			}
		}

		return retConnectionEdgeList;
	}

	ConnectionEdgeList & buildConnectionEdgeListFromTriangleIndexList(
		ConnectionEdgeList & retConnectionEdgeList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList)
	{
		_ASSERT(retConnectionEdgeList.empty());
		_ASSERT(vertexIndexList.size() % 3 == 0);

		for(size_t i = 0; i < vertexIndexList.size(); i += 3)
		{
			for(int j = 0; j < 3; j++)
			{
				size_t v0_i = vertexIndexList[i + (j + 0) % 3];
				size_t v1_i = vertexIndexList[i + (j + 1) % 3];

				ConnectionEdgeList::iterator connection_edge_iter = retConnectionEdgeList.begin();
				for(; connection_edge_iter != retConnectionEdgeList.end(); connection_edge_iter++)
				{
					if(v1_i == connection_edge_iter->v0_i && v0_i == connection_edge_iter->v1_i)
					{
						if(connection_edge_iter->tri1_i != SIZE_MAX)
						{
							_ASSERT(false); continue; // ***
						}

						connection_edge_iter->tri1_i = i / 3;
						break;
					}
				}

				if(retConnectionEdgeList.end() == connection_edge_iter)
				{
					ConnectionEdge silhouetteEdge;
					silhouetteEdge.v0_i = v0_i;
					silhouetteEdge.v1_i = v1_i;
					silhouetteEdge.tri0_i = i / 3;
					silhouetteEdge.tri1_i = SIZE_MAX;

					retConnectionEdgeList.push_back(silhouetteEdge);
				}
			}
		}

		return retConnectionEdgeList;
	}

	IndicatorList & buildIndicatorListFromTriangleListByPoint(
		IndicatorList & retIndicatorList,
		const VertexList & vertexList,
		const Vec4<real> & point)
	{
		_ASSERT(vertexList.size() % 3 == 0);

		retIndicatorList.resize(vertexList.size() / 3);
		for(size_t i = 0; i < vertexList.size(); i += 3)
		{
			const Vec4<real> & v0 = vertexList[i + 0];
			const Vec4<real> & v1 = vertexList[i + 1];
			const Vec4<real> & v2 = vertexList[i + 2];

			retIndicatorList[i / 3] = vec3Dot(vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(v0, point));
		}

		return retIndicatorList;
	}

	IndicatorList & buildIndicatorListFromTriangleIndexListByPoint(
		IndicatorList & retIndicatorList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const Vec4<real> & point)
	{
		_ASSERT(vertexIndexList.size() % 3 == 0);

		retIndicatorList.resize(vertexIndexList.size() / 3);
		for(size_t i = 0; i < vertexIndexList.size(); i += 3)
		{
			const Vec4<real> & v0 = vertexList[vertexIndexList[i + 0]];
			const Vec4<real> & v1 = vertexList[vertexIndexList[i + 1]];
			const Vec4<real> & v2 = vertexList[vertexIndexList[i + 2]];

			retIndicatorList[i / 3] = vec3Dot(vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(v0, point));
		}

		return retIndicatorList;
	}

	IndicatorList & buildIndicatorListFromTriangleListByDirection(
		IndicatorList & retIndicatorList,
		const VertexList & vertexList,
		const Vec4<real> & direction)
	{
		_ASSERT(vertexList.size() % 3 == 0);

		retIndicatorList.resize(vertexList.size() / 3);
		for(size_t i = 0; i < vertexList.size(); i += 3)
		{
			const Vec4<real> & v0 = vertexList[i + 0];
			const Vec4<real> & v1 = vertexList[i + 1];
			const Vec4<real> & v2 = vertexList[i + 2];

			retIndicatorList[i / 3] = vec3Dot(vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), direction);
		}

		return retIndicatorList;
	}

	IndicatorList & buildIndicatorListFromTriangleIndexListByDirection(
		IndicatorList & retIndicatorList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const Vec4<real> & direction)
	{
		_ASSERT(vertexIndexList.size() % 3 == 0);

		retIndicatorList.resize(vertexIndexList.size() / 3);
		for(size_t i = 0; i < vertexIndexList.size(); i += 3)
		{
			const Vec4<real> & v0 = vertexList[vertexIndexList[i + 0]];
			const Vec4<real> & v1 = vertexList[vertexIndexList[i + 1]];
			const Vec4<real> & v2 = vertexList[vertexIndexList[i + 2]];

			retIndicatorList[i / 3] = vec3Dot(vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), direction);
		}

		return retIndicatorList;
	}

	VertexList & pushSilhouetteEdgeList(
		VertexList & retSilhouetteEdgeList,
		const ConnectionEdgeList & connectionEdgeList,
		const VertexList & vertexList,
		const IndicatorList & indicatorList)
	{
		//_ASSERT(retSilhouetteEdgeList.empty());

		ConnectionEdgeList::const_iterator connection_edge_iter = connectionEdgeList.begin();
		for(; connection_edge_iter != connectionEdgeList.end(); connection_edge_iter++)
		{
			if(indicatorList[connection_edge_iter->tri0_i] >= 0)
			{
				if(SIZE_MAX != connection_edge_iter->tri1_i
					&& indicatorList[connection_edge_iter->tri1_i] < 0)
				{
					retSilhouetteEdgeList.push_back(vertexList[connection_edge_iter->v0_i]);
					retSilhouetteEdgeList.push_back(vertexList[connection_edge_iter->v1_i]);
				}
			}
			else
			{
				if(SIZE_MAX == connection_edge_iter->tri1_i
					|| indicatorList[connection_edge_iter->tri1_i] >= 0)
				{
					retSilhouetteEdgeList.push_back(vertexList[connection_edge_iter->v1_i]);
					retSilhouetteEdgeList.push_back(vertexList[connection_edge_iter->v0_i]);
				}
			}
		}

		return retSilhouetteEdgeList;
	}

	VertexList & buildShadowVolumeByPoint(
		VertexList & retVertexList,
		const VertexList & silhouetteEdgeList,
		const Vec4<real> & point,
		real distance)
	{
		_ASSERT(retVertexList.empty());

		for(int i = 0; i < silhouetteEdgeList.size(); i += 2)
		{
			const Vec4<real> & v0 = silhouetteEdgeList[i + 0];
			const Vec4<real> & v1 = silhouetteEdgeList[i + 1];

			Vec4<real> v2 = vec3Add(v1, vec3Mul(vec3Normalize(vec3Sub(v1, point)), distance));
			Vec4<real> v3 = vec3Add(v0, vec3Mul(vec3Normalize(vec3Sub(v0, point)), distance));

			retVertexList.push_back(v0);
			retVertexList.push_back(v1);
			retVertexList.push_back(v2);

			retVertexList.push_back(v2);
			retVertexList.push_back(v3);
			retVertexList.push_back(v0);
		}

		return retVertexList;
	}

	VertexList & buildShadowVolumeByDirection(
		VertexList & retVertexList,
		const VertexList & silhouetteEdgeList,
		const Vec4<real> & direction,
		real distance)
	{
		_ASSERT(retVertexList.empty());

		for(int i = 0; i < silhouetteEdgeList.size(); i += 2)
		{
			const Vec4<real> & v0 = silhouetteEdgeList[i + 0];
			const Vec4<real> & v1 = silhouetteEdgeList[i + 1];

			Vec4<real> v2 = vec3Add(v1, vec3Mul(direction, distance));
			Vec4<real> v3 = vec3Add(v0, vec3Mul(direction, distance));

			retVertexList.push_back(v0);
			retVertexList.push_back(v1);
			retVertexList.push_back(v2);

			retVertexList.push_back(v2);
			retVertexList.push_back(v3);
			retVertexList.push_back(v0);
		}

		return retVertexList;
	}
}
