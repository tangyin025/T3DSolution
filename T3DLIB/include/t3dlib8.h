
#ifndef __T3DLIB8_H__
#define __T3DLIB8_H__

#include "t3dcommon.h"
#include "t3dlib5.h"
#include "t3dlib6.h"

namespace t3d
{
	void fillDepthStencilBuffer(
		SurfaceRef<int> stencilbuff,
		const CRect & rect,
		int value);

	void countScanBehindDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz);

	void countClippedScanBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz);

	void countScanInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz);

	void countClippedScanInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz);

	void countTriangleBehindDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	void countClippedTriangleBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	void countTriangleInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	void countClippedTriangleInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	CLIP_STATE clipTriangleFrontfaceAtWorld(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & eye);

	void removeTriangleListFrontfaceAtWorld(
		const VertexList & vertexList,
		ClipStateList & clipStateList,
		const Vec4<real> & eye);

	void removeTriangleIndexListFrontfaceAtWorld(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const Vec4<real> & eye);

	class SilhouetteEdge
	{
	public:
		Vec4<real> v0;
		Vec4<real> v1;
		size_t tri0_i;
		size_t tri1_i;
	};

	typedef std::vector<SilhouetteEdge> SilhouetteEdgeList;

	SilhouetteEdgeList & buildSilhouetteEdgeListFromTriangleList(
		SilhouetteEdgeList & retSilhouetteEdgeList,
		const VertexList & vertexList);

	SilhouetteEdgeList & buildSilhouetteEdgeListFromTriangleIndexList(
		SilhouetteEdgeList & retSilhouetteEdgeList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList);

	typedef std::vector<real> IndicatorList;

	IndicatorList & buildIndicatorListFromTriangleListByPoint(
		IndicatorList & retIndicatorList,
		const VertexList & vertexList,
		const Vec4<real> & point);

	IndicatorList & buildIndicatorListFromTriangleIndexListByPoint(
		IndicatorList & retIndicatorList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const Vec4<real> & point);

	IndicatorList & buildIndicatorListFromTriangleListByDirection(
		IndicatorList & retIndicatorList,
		const VertexList & vertexList,
		const Vec4<real> & direction);

	IndicatorList & buildIndicatorListFromTriangleIndexListByDirection(
		IndicatorList & retIndicatorList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const Vec4<real> & direction);

	VertexList & buildShadowVolumeByPoint(
		VertexList & retVertexList,
		const SilhouetteEdgeList & silhouetteEdgeList,
		const IndicatorList & indicatorList,
		const Vec4<real> & point,
		real distance);

	VertexList & buildShadowVolumeByDirection(
		VertexList & retVertexList,
		const SilhouetteEdgeList & silhouetteEdgeList,
		const IndicatorList & indicatorList,
		const Vec4<real> & direction,
		real distance);
}

#endif // __T3DLIB8_H__
