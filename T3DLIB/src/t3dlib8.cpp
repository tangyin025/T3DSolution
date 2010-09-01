
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

	void countScanBehindDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz)
	{
#define __draw_behind_depth
#include "count_scan.hpp"
	}

	void countClippedScanBehindDepth(
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
#define __draw_clipped
#include "count_scan.hpp"
	}

	void countScanInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz)
	{
#define __draw_in_front_of_depth
#include "count_scan.hpp"
	}

	void countClippedScanInFrontOfDepth(
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
#define __draw_clipped
#include "count_scan.hpp"
	}

	void countTriangleBehindDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2)
	{
#define __draw_func countScanBehindDepth
#include "count_triangle.hpp"
	}

	void countClippedTriangleBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2)
	{
#define __draw_clipped
#define __draw_func countScanBehindDepth
#define __draw_clipped_func countClippedScanBehindDepth
#include "count_triangle.hpp"
	}

	void countTriangleInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2)
	{
#define __draw_func countScanInFrontOfDepth
#include "count_triangle.hpp"
	}

	void countClippedTriangleInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2)
	{
#define __draw_clipped
#define __draw_func countScanInFrontOfDepth
#define __draw_clipped_func countClippedScanInFrontOfDepth
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
				const Vec4<real> & v0 = vertexList[(j + 0) % 3];
				const Vec4<real> & v1 = vertexList[(j + 1) % 3];
				SilhouetteEdgeList::iterator silhouette_edge_iter = retSilhouetteEdgeList.begin();
				for(; silhouette_edge_iter != retSilhouetteEdgeList.end(); silhouette_edge_iter++)
				{
					if((vec3IsEqual(v0, silhouette_edge_iter->v0) && vec3IsEqual(v1, silhouette_edge_iter->v1))
						|| (vec3IsEqual(v1, silhouette_edge_iter->v0) && vec3IsEqual(v0, silhouette_edge_iter->v1)))
					{
						_ASSERT(SIZE_MAX == silhouette_edge_iter->tri1_i);

						silhouette_edge_iter->tri1_i = i / 3;
					}
				}

				if(silhouette_edge_iter == retSilhouetteEdgeList.end())
				{
					SilhouetteEdge silhouetteEdge;
					silhouetteEdge.v0 = v0;
					silhouetteEdge.v1 = v1;
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
				const Vec4<real> & v0 = vertexList[vertexIndexList[(j + 0) % 3]];
				const Vec4<real> & v1 = vertexList[vertexIndexList[(j + 1) % 3]];
				SilhouetteEdgeList::iterator silhouette_edge_iter = retSilhouetteEdgeList.begin();
				for(; silhouette_edge_iter != retSilhouetteEdgeList.end(); silhouette_edge_iter++)
				{
					if((vec3IsEqual(v0, silhouette_edge_iter->v0) && vec3IsEqual(v1, silhouette_edge_iter->v1))
						|| (vec3IsEqual(v1, silhouette_edge_iter->v0) && vec3IsEqual(v0, silhouette_edge_iter->v1)))
					{
						_ASSERT(SIZE_MAX == silhouette_edge_iter->tri1_i);

						silhouette_edge_iter->tri1_i = i / 3;
					}
				}

				if(silhouette_edge_iter == retSilhouetteEdgeList.end())
				{
					SilhouetteEdge silhouetteEdge;
					silhouetteEdge.v0 = v0;
					silhouetteEdge.v1 = v1;
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

			retIndicatorList[i / 3] = vec3Dot(vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(point, v0));
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

			retIndicatorList[i / 3] = vec3Dot(vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(point, v0));
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
		const IndicatorList & indicatorList,
		const Vec4<real> & point,
		real distance)
	{
		_ASSERT(retVertexList.empty());

		SilhouetteEdgeList::const_iterator silhouette_edge_iter = silhouetteEdgeList.begin();
		for(; silhouette_edge_iter != silhouetteEdgeList.end(); silhouette_edge_iter++)
		{
		}

		return retVertexList;
	}

	VertexList & buildShadowVolumeByDirection(
		VertexList & retVertexList,
		const SilhouetteEdgeList & silhouetteEdgeList,
		const IndicatorList & indicatorList,
		const Vec4<real> & direction,
		real distance)
	{
		_ASSERT(retVertexList.empty());

		SilhouetteEdgeList::const_iterator silhouette_edge_iter = silhouetteEdgeList.begin();
		for(; silhouette_edge_iter != silhouetteEdgeList.end(); silhouette_edge_iter++)
		{
		}

		return retVertexList;
	}
}
