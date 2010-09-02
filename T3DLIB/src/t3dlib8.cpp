
#include "stdafx.h"
#include "t3dlib8.h"

namespace t3d
{
	void fillDepthStencilBuffer(
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

	CLIP_STATE clipTriangleFrontfaceAtWorld(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & eye)
	{
		return vec3Dot(vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(eye, v0)) >= 0 ? CLIP_STATE_CULLED : CLIP_STATE_NONE;
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

	SilhouetteEdgeList & buildSilhouetteEdgeListFromTriangleList(
		SilhouetteEdgeList & retSilhouetteEdgeList,
		const VertexList & vertexList)
	{
		_ASSERT(retSilhouetteEdgeList.empty());
		_ASSERT(vertexList.size() % 3 == 0);

		for(size_t i = 0; i < vertexList.size(); i += 3)
		{
			for(int j = 0; j < 3; j++)
			{
				const Vec4<real> & v0 = vertexList[i + (j + 0) % 3];
				const Vec4<real> & v1 = vertexList[i + (j + 1) % 3];
				SilhouetteEdgeList::iterator silhouette_edge_iter = retSilhouetteEdgeList.begin();
				for(; silhouette_edge_iter != retSilhouetteEdgeList.end(); silhouette_edge_iter++)
				{
					const Vec4<real> & ev0 = vertexList[silhouette_edge_iter->v0_i];
					const Vec4<real> & ev1 = vertexList[silhouette_edge_iter->v1_i];
					if((vec3IsEqual(v0, ev0) && vec3IsEqual(v1, ev1))
						|| (vec3IsEqual(v1, ev0) && vec3IsEqual(v0, ev1)))
					{
						if(silhouette_edge_iter->tri1_i != SIZE_MAX)
						{
							continue; // ***
						}

						silhouette_edge_iter->tri1_i = i / 3;
						break;
					}
				}

				if(silhouette_edge_iter == retSilhouetteEdgeList.end())
				{
					SilhouetteEdge silhouetteEdge;
					silhouetteEdge.v0_i = i + (j + 0) % 3;
					silhouetteEdge.v1_i = i + (j + 1) % 3;
					silhouetteEdge.tri0_i = i / 3;
					silhouetteEdge.tri1_i = SIZE_MAX;

					retSilhouetteEdgeList.push_back(silhouetteEdge);
				}
			}
		}

		return retSilhouetteEdgeList;
	}

	SilhouetteEdgeList & buildSilhouetteEdgeListFromTriangleIndexList(
		SilhouetteEdgeList & retSilhouetteEdgeList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList)
	{
		_ASSERT(retSilhouetteEdgeList.empty());
		_ASSERT(vertexIndexList.size() % 3 == 0);

		for(size_t i = 0; i < vertexIndexList.size(); i += 3)
		{
			for(int j = 0; j < 3; j++)
			{
				size_t v0_i = vertexIndexList[i + (j + 0) % 3];
				size_t v1_i = vertexIndexList[i + (j + 1) % 3];
				SilhouetteEdgeList::iterator silhouette_edge_iter = retSilhouetteEdgeList.begin();
				for(; silhouette_edge_iter != retSilhouetteEdgeList.end(); silhouette_edge_iter++)
				{
					if((v0_i == silhouette_edge_iter->v0_i && v1_i == silhouette_edge_iter->v1_i)
						|| (v1_i == silhouette_edge_iter->v0_i && v0_i == silhouette_edge_iter->v1_i))
					{
						if(silhouette_edge_iter->tri1_i != SIZE_MAX)
						{
							continue; // ***
						}

						silhouette_edge_iter->tri1_i = i / 3;
						break;
					}
				}

				if(silhouette_edge_iter == retSilhouetteEdgeList.end())
				{
					SilhouetteEdge silhouetteEdge;
					silhouetteEdge.v0_i = v0_i;
					silhouetteEdge.v1_i = v1_i;
					silhouetteEdge.tri0_i = i / 3;
					silhouetteEdge.tri1_i = SIZE_MAX;

					retSilhouetteEdgeList.push_back(silhouetteEdge);
				}
			}
		}

		return retSilhouetteEdgeList;
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

	VertexList & buildShadowVolumeByPoint(
		VertexList & retVertexList,
		const SilhouetteEdgeList & silhouetteEdgeList,
		const VertexList & vertexList,
		const IndicatorList & indicatorList,
		const Vec4<real> & point,
		real distance)
	{
		_ASSERT(retVertexList.empty());

		SilhouetteEdgeList::const_iterator silhouette_edge_iter = silhouetteEdgeList.begin();
		for(; silhouette_edge_iter != silhouetteEdgeList.end(); silhouette_edge_iter++)
		{
			Vec4<real> v0, v1, v2, v3;
			if(indicatorList[silhouette_edge_iter->tri0_i] >= 0)
			{
				if(SIZE_MAX == silhouette_edge_iter->tri1_i
					|| indicatorList[silhouette_edge_iter->tri1_i] < 0) // ***
				{
					v0 = vertexList[silhouette_edge_iter->v0_i];
					v1 = vertexList[silhouette_edge_iter->v1_i];
				}
				else
				{
					continue;
				}
			}
			else
			{
				if(SIZE_MAX == silhouette_edge_iter->tri1_i
					|| indicatorList[silhouette_edge_iter->tri1_i] >= 0) // ***
				{
					v0 = vertexList[silhouette_edge_iter->v1_i];
					v1 = vertexList[silhouette_edge_iter->v0_i];
				}
				else
				{
					continue;
				}
			}

			v2 = vec3Add(v1, vec3Mul(vec3Normalize(vec3Sub(v1, point)), distance));
			v3 = vec3Add(v0, vec3Mul(vec3Normalize(vec3Sub(v0, point)), distance));

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
		const SilhouetteEdgeList & silhouetteEdgeList,
		const VertexList & vertexList,
		const IndicatorList & indicatorList,
		const Vec4<real> & direction,
		real distance)
	{
		_ASSERT(retVertexList.empty());
		_ASSERT(vec3IsNormalized(direction));

		SilhouetteEdgeList::const_iterator silhouette_edge_iter = silhouetteEdgeList.begin();
		for(; silhouette_edge_iter != silhouetteEdgeList.end(); silhouette_edge_iter++)
		{
			Vec4<real> v0, v1, v2, v3;
			if(indicatorList[silhouette_edge_iter->tri0_i] >= 0)
			{
				if(SIZE_MAX == silhouette_edge_iter->tri1_i
					|| indicatorList[silhouette_edge_iter->tri1_i] < 0) // ***
				{
					v0 = vertexList[silhouette_edge_iter->v0_i];
					v1 = vertexList[silhouette_edge_iter->v1_i];
				}
				else
				{
					continue;
				}
			}
			else
			{
				if(SIZE_MAX == silhouette_edge_iter->tri1_i
					|| indicatorList[silhouette_edge_iter->tri1_i] >= 0) // ***
				{
					v0 = vertexList[silhouette_edge_iter->v1_i];
					v1 = vertexList[silhouette_edge_iter->v0_i];
				}
				else
				{
					continue;
				}
			}

			v2 = vec3Add(v1, vec3Mul(direction, distance));
			v3 = vec3Add(v0, vec3Mul(direction, distance));

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
