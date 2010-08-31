
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
}
