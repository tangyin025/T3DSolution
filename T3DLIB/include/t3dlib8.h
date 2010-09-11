
#ifndef __T3DLIB8_H__
#define __T3DLIB8_H__

#include "t3dcommon.h"
#include "t3dlib6.h"

namespace t3d
{
	void fillStencilBuffer(
		SurfaceRef<int> stencilbuff,
		const CRect & rect,
		int value);

	void countScanIncrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz);

	void countScanDecrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz);

	void countClippedScanIncrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz);

	void countClippedScanDecrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz);

	void countScanIncrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz);

	void countScanDecrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz);

	void countClippedScanIncrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz);

	void countClippedScanDecrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz);

	void countTriangleIncrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	void countTriangleDecrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	void countClippedTriangleIncrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	void countClippedTriangleDecrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	void countTriangleIncrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	void countTriangleDecrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	void countClippedTriangleIncrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	void countClippedTriangleDecrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	void countTriangleListIncrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList);

	void countTriangleListDecrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList);

	void countTriangleIndexListIncrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList);

	void countTriangleIndexListDecrementBehindDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList);

	void countTriangleListIncrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList);

	void countTriangleListDecrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList);

	void countTriangleIndexListIncrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList);

	void countTriangleIndexListDecrementInFrontOfDepth(
		SurfaceRef<int> stencilbuff,
		const RECT & clipper,
		const SurfaceRef<fixp28> & zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList);

	void boundSurfaceStencilBufferColor16(
		SurfaceRef<uint16> surface,
		const CRect & rect,
		SurfaceRef<int> stencilbuff,
		const t3d::Vec4<real> & color);

	void boundSurfaceStencilBufferColor32(
		SurfaceRef<uint32> surface,
		const CRect & rect,
		SurfaceRef<int> stencilbuff,
		const t3d::Vec4<real> & color);

	bool cullTriangleBackfaceAtScreen(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2);

	void removeTriangleListBackfaceAtScreen(
		const VertexList & vertexList,
		ClipStateList & clipStateList);

	void removeTriangleIndexListBackfaceAtScreen(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList);

	ClipStateList & reversalClipStateListScreenCulling(
		ClipStateList & retClipStateList,
		const ClipStateList & clipStateList);

	class ConnectionEdge
	{
	public:
		size_t v0_i;
		size_t v1_i;
		size_t tri0_i;
		size_t tri1_i;
	};

	typedef std::vector<ConnectionEdge> ConnectionEdgeList;

	ConnectionEdgeList & buildConnectionEdgeListFromTriangleList(
		ConnectionEdgeList & retConnectionEdgeList,
		const VertexList & vertexList);

	ConnectionEdgeList & buildConnectionEdgeListFromTriangleIndexList(
		ConnectionEdgeList & retConnectionEdgeList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList);

	class IndicatorList : public std::vector<real>
	{
	public:
		static bool isBack(real indicator)
		{
			return indicator > 0;
		}

		static bool isFront(real indicator)
		{
			return indicator < 0;
		}

		static real buildTriangleIndicatorByPoint(
			const Vec4<real> & v0,
			const Vec4<real> & v1,
			const Vec4<real> & v2,
			const Vec4<real> & point)
		{
			return vec3Dot(vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(v0, point));
		}

		static real buildTriangleIndicatorByDirection(
			const Vec4<real> & v0,
			const Vec4<real> & v1,
			const Vec4<real> & v2,
			const Vec4<real> & direction)
		{
			return vec3Dot(vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), direction);
		}
	};

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

	VertexList & pushSilhouetteEdgeList(
		VertexList & retSilhouetteEdgeList,
		const ConnectionEdgeList & connectionEdgeList,
		const VertexList & vertexList,
		const IndicatorList & indicatorList);

	VertexList & pushUncappedShadowVolumeByPoint(
		VertexList & retVertexList,
		const VertexList & silhouetteEdgeList,
		const Vec4<real> & point,
		real distance);

	VertexList & pushUncappedShadowVolumeByDirection(
		VertexList & retVertexList,
		const VertexList & silhouetteEdgeList,
		const Vec4<real> & direction,
		real distance);

	VertexList & pushTriangleListFrontCapByPoint(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const IndicatorList & indicatorList,
		const Vec4<real> & point,
		real distance);

	VertexList & pushTriangleIndexListFrontCapByPoint(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const IndicatorList & indicatorList,
		const Vec4<real> & point,
		real distance);

	VertexList & pushTriangleListBackCapByPoint(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const IndicatorList & indicatorList,
		const Vec4<real> & point,
		real distance);

	VertexList & pushTriangleIndexListBackCapByPoint(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const IndicatorList & indicatorList,
		const Vec4<real> & point,
		real distance);

	VertexList & pushTriangleListFrontCapByDirection(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const IndicatorList & indicatorList,
		const Vec4<real> & direction,
		real distance);

	VertexList & pushTriangleIndexListFrontCapByDirection(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const IndicatorList & indicatorList,
		const Vec4<real> & direction,
		real distance);

	VertexList & pushTriangleListBackCapByDirection(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const IndicatorList & indicatorList,
		const Vec4<real> & direction,
		real distance);

	VertexList & pushTriangleIndexListBackCapByDirection(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const IndicatorList & indicatorList,
		const Vec4<real> & direction,
		real distance);

	VertexList & pushTriangleListCappedShadowVolumeByPoint(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const IndicatorList & indicatorList,
		const VertexList & silhouetteEdgeList,
		const Vec4<real> & point,
		real distance);

	VertexList & pushTriangleIndexListCappedShadowVolumeByPoint(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const IndicatorList & indicatorList,
		const VertexList & silhouetteEdgeList,
		const Vec4<real> & point,
		real distance);

	VertexList & pushTriangleListCappedShadowVolumeByDirection(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const IndicatorList & indicatorList,
		const VertexList & silhouetteEdgeList,
		const Vec4<real> & direction,
		real distance);

	VertexList & pushTriangleIndexListCappedShadowVolumeByDirection(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const IndicatorList & indicatorList,
		const VertexList & silhouetteEdgeList,
		const Vec4<real> & direction,
		real distance);
}

#endif // __T3DLIB8_H__
