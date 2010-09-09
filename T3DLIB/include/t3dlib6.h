
#ifndef __T3DLIB6_H__
#define __T3DLIB6_H__

#include "t3dcommon.h"

#include <vector>
#include <cmath>
#include "t3dlib4.h"
#include "t3dlib5.h"
#include <boost/shared_ptr.hpp>

namespace t3d
{
	typedef std::vector<Vec4<real> > VertexList;

	typedef std::vector<size_t> VertexIndexList;

	typedef std::vector<Vec4<real> > NormalList;

	typedef std::vector<Vec2<real> > UVList;

	typedef std::vector<Vec4<real> > ColorList;

	enum CLIP_STATE
	{
		CLIP_STATE_NONE,
		CLIP_STATE_CULLED,
		CLIP_STATE_SCLIPPED,
		CLIP_STATE_CULLED_SCREEN,
	};

	typedef std::vector<CLIP_STATE> ClipStateList;

	struct MATERIAL
	{
		Vec4<real> ambient;
		Vec4<real> diffuse;
		Vec4<real> specular;
		Vec4<real> emissive;
	};

	enum LIGHT_TYPE
	{
		LT_UNKNOWN,
		LT_AMBIENT,
		LT_DIRECTIONAL,
		LT_POINT,
	};

	enum LIGHT_STATE
	{
		LS_ON,
		LS_OFF,
	};

	struct LIGHT
	{
		LIGHT_TYPE type;
		LIGHT_STATE state;
		Vec4<real> pos;
		Vec4<real> dir;
		Vec4<real> ambient;
		Vec4<real> diffuse;
		Vec4<real> specular;
		real kc;
		real kl;
		real kq;
	};

	typedef std::vector<LIGHT> LightList;

	struct CAMERA
	{
		Mat4<real> mcam; // *** an INVERSED matrix of camera transform
		Vec2<real> proj;
		real nz;
		real fz;
		CRect viewport;
	};

	VertexList & transformVertexList(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const Mat4<real> & mmat);

	VertexList & transformVertexListSelf(
		VertexList & vertexList,
		const Mat4<real> & mmat);

	VertexList & transformLineList(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat);

	VertexList & transformLineListSelf(
		VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat);

	VertexList & transformLineIndexList(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat);

	VertexList & transformLineIndexListSelf(
		VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat);

	CLIP_STATE clipLineAtCamera(
		Vec4<real> v0,
		Vec4<real> v1,
		const CAMERA & camera,
		VertexList & retVertexList,
		ClipStateList & retClipStateList);

	void clipLineListAtCamera(
		VertexList & vertexList,
		ClipStateList & clipStateList,
		const CAMERA & camera);

	CLIP_STATE clipLineIndexAtCamera(
		VertexList & vertexList,
		size_t v0_i,
		size_t v1_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	void clipLineIndexListAtCamera(
		VertexList & vertexList,
		VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const CAMERA & camera);

	void cameraToScreenVertexSelf(
		Vec4<real> & vertex,
		const Vec2<real> & projection,
		const CPoint & centerPoint,
		const CSize & halfSize);

	void cameraToScreenLineList(
		VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec2<real> & projection,
		const CRect & viewport);

	void cameraToScreenLineIndexList(
		VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec2<real> & projection,
		const CRect & viewport);

	CLIP_STATE clipLineAtScreen(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const CRect & viewport);

	void clipLineListAtScreen(
		const VertexList & vertexList,
		ClipStateList & clipStateList,
		const CRect & viewport);

	void clipLineIndexListAtScreen(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const CRect & viewport);

	void drawLineListZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color);

	void drawLineListZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color);

	void drawLineIndexListZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color);

	void drawLineIndexListZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color);

	CLIP_STATE clipTriangleBackfaceAtWorld(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & eye);

	void removeTriangleListBackfaceAtWorld(
		const VertexList & vertexList,
		ClipStateList & clipStateList,
		const Vec4<real> & eye);

	void removeTriangleIndexListBackfaceAtWorld(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const Vec4<real> & eye);

	VertexList & transformTriangleList(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat);

	VertexList & transformTriangleListSelf(
		VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat);

	VertexList & transformTriangleIndexList(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat);

	VertexList & transformTriangleIndexListSelf(
		VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat);

	CLIP_STATE clipTriangleAtCameraNearZDouble(
		Vec4<real> v0,
		Vec4<real> v1,
		Vec4<real> v2,
		const CAMERA & camera,
		VertexList & retVertexList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleAtCameraNearZSingle(
		Vec4<real> v0,
		Vec4<real> v1,
		Vec4<real> v2,
		const CAMERA & camera,
		VertexList & retVertexList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleAtCameraFarZ(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const CAMERA & camera);

	CLIP_STATE clipTriangleAtCamera(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const CAMERA & camera,
		VertexList & retVertexList,
		ClipStateList & retClipStateList);

	void clipTriangleListAtCamera(
		VertexList & vertexList,
		ClipStateList & clipStateList,
		const CAMERA & camera);

	CLIP_STATE clipTriangleIndexAtCameraNearZDouble(
		VertexList & vertexList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleIndexAtCameraNearZSingle(
		VertexList & vertexList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	//CLIP_STATE clipTriangleIndexAtCameraFarZ(
	//	VertexList & vertexList,
	//	size_t v0_i,
	//	size_t v1_i,
	//	size_t v2_i,
	//	const CAMERA & camera,
	//	VertexIndexList & retVertexIndexList,
	//	ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleIndexAtCamera(
		VertexList & vertexList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	void clipTriangleIndexListAtCamera(
		VertexList & vertexList,
		VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const CAMERA & camera);

	void cameraToScreenTriangleList(
		VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec2<real> & projection,
		const CRect & viewport);

	void cameraToScreenTriangleIndexList(
		VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec2<real> & projection,
		const CRect & viewport);

	CLIP_STATE clipTriangleAtScreen(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const CRect & viewport);

	void clipTriangleListAtScreen(
		const VertexList & vertexList,
		ClipStateList & clipStateList,
		const CRect & viewport);

	void clipTriangleIndexListAtScreen(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const CRect & viewport);

	void drawTriangleListWireZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color);

	void drawTriangleListWireZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color);

	void drawTriangleIndexListWireZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color);

	void drawTriangleIndexListWireZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color);

	void drawTriangleListZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color);

	void drawTriangleListZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color);

	void drawTriangleIndexListZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color);

	void drawTriangleIndexListZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color);

	void lightTriangleListAtWorld(
		const VertexList & vertexList,
		const VertexList & normalList,
		const ClipStateList & clipStateList,
		const LightList & lightList,
		const MATERIAL & material,
		ColorList & retColorList);

	void lightTriangleIndexListAtWorld(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const VertexList & normalList,
		const ClipStateList & clipStateList,
		const LightList & lightList,
		const MATERIAL & material,
		ColorList & retColorList);

	CLIP_STATE clipTriangleGouraudAtCameraNearZDouble(
		Vec4<real> v0,
		Vec4<real> v1,
		Vec4<real> v2,
		Vec4<real> c0,
		Vec4<real> c1,
		Vec4<real> c2,
		const CAMERA & camera,
		VertexList & retVertexList,
		ColorList & retColorList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleGouraudAtCameraNearZSingle(
		Vec4<real> v0,
		Vec4<real> v1,
		Vec4<real> v2,
		Vec4<real> c0,
		Vec4<real> c1,
		Vec4<real> c2,
		const CAMERA & camera,
		VertexList & retVertexList,
		ColorList & retColorList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleGouraudAtCamera(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & c0,
		const Vec4<real> & c1,
		const Vec4<real> & c2,
		const CAMERA & camera,
		VertexList & retVertexList,
		ColorList & retColorList,
		ClipStateList & retClipStateList);

	void clipTriangleListGouraudAtCamera(
		VertexList & vertexList,
		ColorList & colorList,
		ClipStateList & clipStateList,
		const CAMERA & camera);

	CLIP_STATE clipTriangleIndexGouraudAtCameraNearZDouble(
		VertexList & vertexList,
		ColorList & colorList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleIndexGouraudAtCameraNearZSingle(
		VertexList & vertexList,
		ColorList & colorList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleIndexGouraudAtCamera(
		VertexList & vertexList,
		ColorList & colorList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	void clipTriangleIndexListGouraudAtCamera(
		VertexList & vertexList,
		VertexIndexList & vertexIndexList,
		ColorList & colorList,
		ClipStateList & clipStateList,
		const CAMERA & camera);

	void drawTriangleListGouraudZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ColorList & colorList,
		const ClipStateList & clipStateList);

	void drawTriangleListGouraudZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ColorList & colorList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListGouraudZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ColorList & colorList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListGouraudZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ColorList & colorList,
		const ClipStateList & clipStateList);

	CLIP_STATE clipTriangleTextureAtCameraNearZDouble(
		Vec4<real> v0,
		Vec4<real> v1,
		Vec4<real> v2,
		Vec2<real> t0,
		Vec2<real> t1,
		Vec2<real> t2,
		const CAMERA & camera,
		VertexList & retVertexList,
		UVList & retUVList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleTextureAtCameraNearZSingle(
		Vec4<real> v0,
		Vec4<real> v1,
		Vec4<real> v2,
		Vec2<real> t0,
		Vec2<real> t1,
		Vec2<real> t2,
		const CAMERA & camera,
		VertexList & retVertexList,
		UVList & retUVList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleTextureAtCamera(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2,
		const CAMERA & camera,
		VertexList & retVertexList,
		UVList & retUVList,
		ClipStateList & retClipStateList);

	void clipTriangleListTextureAtCamera(
		VertexList & vertexList,
		UVList & uvList,
		ClipStateList & clipStateList,
		const CAMERA & camera);

	CLIP_STATE clipTriangleIndexTextureAtCameraNearZDouble(
		VertexList & vertexList,
		UVList & uvList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleIndexTextureAtCameraNearZSingle(
		VertexList & vertexList,
		UVList & uvList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleIndexTextureAtCamera(
		VertexList & vertexList,
		UVList & uvList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	void clipTriangleIndexListTextureAtCamera(
		VertexList & vertexList,
		VertexIndexList & vertexIndexList,
		UVList & uvList,
		ClipStateList & clipStateList,
		const CAMERA & camera);

	void drawTriangleListTextureZBufferW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleListTextureZBufferW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListTextureZBufferW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListTextureZBufferW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleListTexturePerspectiveLPZBufferW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleListTexturePerspectiveLPZBufferW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListTexturePerspectiveLPZBufferW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListTexturePerspectiveLPZBufferW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleListTextureZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleListTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListTextureZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleListTexturePerspectiveLPZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleListTexturePerspectiveLPZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListTexturePerspectiveLPZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListTexturePerspectiveLPZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	CLIP_STATE clipTriangleGouraudTextureAtCameraNearZDouble(
		Vec4<real> v0,
		Vec4<real> v1,
		Vec4<real> v2,
		Vec4<real> c0,
		Vec4<real> c1,
		Vec4<real> c2,
		Vec2<real> t0,
		Vec2<real> t1,
		Vec2<real> t2,
		const CAMERA & camera,
		VertexList & retVertexList,
		ColorList & retColorList,
		UVList & retUVList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleGouraudTextureAtCameraNearZSingle(
		Vec4<real> v0,
		Vec4<real> v1,
		Vec4<real> v2,
		Vec4<real> c0,
		Vec4<real> c1,
		Vec4<real> c2,
		Vec2<real> t0,
		Vec2<real> t1,
		Vec2<real> t2,
		const CAMERA & camera,
		VertexList & retVertexList,
		ColorList & retColorList,
		UVList & retUVList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleGouraudTextureAtCamera(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & c0,
		const Vec4<real> & c1,
		const Vec4<real> & c2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2,
		const CAMERA & camera,
		VertexList & retVertexList,
		ColorList & retColorList,
		UVList & retUVList,
		ClipStateList & retClipStateList);

	void clipTriangleListGouraudTextureAtCamera(
		VertexList & vertexList,
		ColorList & colorList,
		UVList & uvList,
		ClipStateList & clipStateList,
		const CAMERA & camera);

	CLIP_STATE clipTriangleIndexGouraudTextureAtCameraNearZDouble(
		VertexList & vertexList,
		ColorList & colorList,
		UVList & uvList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleIndexGouraudTextureAtCameraNearZSingle(
		VertexList & vertexList,
		ColorList & colorList,
		UVList & uvList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	CLIP_STATE clipTriangleIndexGouraudTextureAtCamera(
		VertexList & vertexList,
		ColorList & colorList,
		UVList & uvList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList);

	void clipTriangleIndexListGouraudTextureAtCamera(
		VertexList & vertexList,
		VertexIndexList & vertexIndexList,
		ColorList & colorList,
		UVList & uvList,
		ClipStateList & clipStateList,
		const CAMERA & camera);

	void drawTriangleListGouraudTextureZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleListGouraudTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListGouraudTextureZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListGouraudTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleListGouraudTexturePerspectiveLPZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleListGouraudTexturePerspectiveLPZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList);

	void drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList);
}

#endif // __T3DLIB6_H__
