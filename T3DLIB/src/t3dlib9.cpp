
#include "stdafx.h"
#include "t3dlib9.h"

#pragma warning(disable: 4244)

namespace t3d
{
	LIGHT LightListContext::buildLightAmbient(const Vec4<real> & ambient, LIGHT_STATE state /*= LS_ON*/)
	{
		_ASSERT(rgbaIsValid(ambient, real(0), real(1)));

		LIGHT light;
		light.type = LT_AMBIENT;
		light.state = state;
		light.ambient = ambient;
		return light;
	}

	LIGHT LightListContext::buildLightDirectional(const Vec4<real> & diffuse, const Vec4<real> & dir, LIGHT_STATE state /*= LS_ON*/)
	{
		_ASSERT(rgbaIsValid(diffuse, real(0), real(1)));

		LIGHT light;
		light.type = LT_DIRECTIONAL;
		light.state = state;
		light.dir = dir;
		light.diffuse = diffuse;
		return light;
	}

	LIGHT LightListContext::buildLightPoint(const Vec4<real> & diffuse, const Vec4<real> & pos, real kc /*= 1.0f*/, real kl /*= 0.001f*/, real kq /*= 0.00001f*/, LIGHT_STATE state /*= LS_ON*/)
	{
		_ASSERT(rgbaIsValid(diffuse, real(0), real(1)));

		LIGHT light;
		light.type = LT_POINT;
		light.state = state;
		light.pos = pos;
		light.diffuse = diffuse;
		light.kc = kc;
		light.kl = kl;
		light.kq = kq;
		return light;
	}

	Vec4<real> LightListContext::lightVertexAmbient(const LIGHT & light, const MATERIAL & material, const Vec4<real> & vertex, const Vec4<real> & normal)
	{
		_ASSERT(LT_AMBIENT == light.type);
		_ASSERT(LS_ON == light.state);

		// I(d)ambient = I0ambient * Clambient

		return light.ambient * material.ambient;
		UNREFERENCED_PARAMETER(vertex);
		UNREFERENCED_PARAMETER(normal);
	}

	Vec4<real> LightListContext::lightVertexDirectional(const LIGHT & light, const MATERIAL & material, const Vec4<real> & vertex, const Vec4<real> & normal)
	{
		_ASSERT(LT_DIRECTIONAL == light.type);
		_ASSERT(LS_ON == light.state);

		// I(d)dir = I0dir * Cldir (n . l)

		real dot = vec3Dot(light.dir, normal);

		if(dot < 0)
		{
			return light.diffuse * material.diffuse * -dot;
		}

		return Vec4<real>(0, 0, 0, 0);
		UNREFERENCED_PARAMETER(vertex);
	}

	Vec4<real> LightListContext::lightVertexPoint(const LIGHT & light, const MATERIAL & material, const Vec4<real> & vertex, const Vec4<real> & normal)
	{
		_ASSERT(LT_POINT == light.type);
		_ASSERT(LS_ON == light.state);

		//               I0point * Clpoint
		// I(d)point = --------------------- (n . l)
		//             kc + kl * d + kq * d2

		Vec4<real> dir = vec3Sub(vertex, light.pos);
		real dot = vec3Dot(normal, dir);
		real len = vec3Length(dir);

		if(dot < 0)
		{
			return light.diffuse * material.diffuse * -dot / (len * (light.kc + light.kl * len + light.kq * len * len));
		}

		return Vec4<real>(0, 0, 0, 0);
	}

	Mat4<real> CameraContext::buildCameraTransformEuler(const Vec4<real> & pos, const Vec4<real> & rot, DWORD rot_seq /*= RS_ZXY*/)
	{
		switch(rot_seq)
		{
		case RS_XYZ:
			return mat3RotXYZ(rot) * mat3Mov(pos);
		case RS_XZY:
			return mat3RotXZY(rot) * mat3Mov(pos);
		case RS_YXZ:
			return mat3RotYXZ(rot) * mat3Mov(pos);
		case RS_YZX:
			return mat3RotYZX(rot) * mat3Mov(pos);
		case RS_ZXY:
			return mat3RotZXY(rot) * mat3Mov(pos);
		case RS_ZYX:
			return mat3RotZYX(rot) * mat3Mov(pos);
		default:
			_ASSERT(false); return Mat4<real>();
		};
	}

	Mat4<real> CameraContext::buildInverseCameraTransformEuler(const Vec4<real> & pos, const Vec4<real> & rot, DWORD rot_seq /*= RS_ZXY*/)
	{
		switch(rot_seq)
		{
		case RS_XYZ:
			return mat3InverseMov(pos) * mat3InverseRotXYZ(rot);
		case RS_XZY:
			return mat3InverseMov(pos) * mat3InverseRotXZY(rot);
		case RS_YXZ:
			return mat3InverseMov(pos) * mat3InverseRotYXZ(rot);
		case RS_YZX:
			return mat3InverseMov(pos) * mat3InverseRotYZX(rot);
		case RS_ZXY:
			return mat3InverseMov(pos) * mat3InverseRotZXY(rot);
		case RS_ZYX:
			return mat3InverseMov(pos) * mat3InverseRotZYX(rot);
		default:
			_ASSERT(false); return Mat4<real>();
		};
	}

	Mat4<real> CameraContext::buildInverseCameraTransformUVN(const Vec4<real> & pos, const Vec4<real> & target, const Vec4<real> & up)
	{
		return mat3InverseMov(pos) * mat3LookAt(pos, target, up);
	}

	Mat4<real> CameraContext::buildInverseCameraTransformQuat(const Vec4<real> & pos, const Quat<real> & ori)
	{
		return mat3InverseMov(pos) * buildInverseRotationMatrixFromQuatLH(ori);
	}

	Vec2<real> CameraContext::buildCameraProjectionFOVWidth(real fov, DWORD width, DWORD height)
	{
		//             width / 2                    height / 2
		// proj.x = --------------, proj.y = -----------------------
		//           tan(fov / 2)             tan(fov / 2) / aspect

		real aspect = (real)width / (real)height;
		real scale = 1 / tan(fov / 2);
		return Vec2<real>(scale, scale * aspect);
	}

	Vec2<real> CameraContext::buildCameraProjectionFOVHeight(real fov, DWORD width, DWORD height)
	{
		//                 width / 2                    height / 2
		// proj.x = -----------------------, proj.y = --------------
		//           tan(fov / 2) * aspect             tan(fov / 2)

		real aspect = (real)width / (real)height;
		real scale = 1 / tan(fov / 2);
		return Vec2<real>(scale / aspect, scale);
	}

	Vec2<real> CameraContext::buildCameraProjectionFOVAuto(real fov, DWORD width, DWORD height)
	{
		if(width < height)
			return buildCameraProjectionFOVWidth(fov, width, height);
		else
			return buildCameraProjectionFOVHeight(fov, width, height);
	}

	real CameraContext::calculateCameraHalfFovX(const Vec2<real> & proj)
	{
		return atan(1 / proj.x);
	}

	real CameraContext::calculateCameraHalfFovY(const Vec2<real> & proj)
	{
		return atan(1 / proj.y);
	}

	real CameraContext::calculateCameraMinHalfFov(const Vec2<real> & proj)
	{
		return proj.x > proj.y ? calculateCameraHalfFovX(proj) : calculateCameraHalfFovY(proj);
	}

	real CameraContext::calculateCameraMaxHalfFov(const Vec2<real> & proj)
	{
		return proj.x < proj.y ? calculateCameraHalfFovX(proj) : calculateCameraHalfFovY(proj);
	}

	Vec4<real> CameraContext::calculateCameraPosition(const Mat4<real> & mcam)
	{
		return mat3GetRow3(mcam.inverse());
	}

	Vec4<real> CameraContext::calculateCameraDirection(const Mat4<real> & mcam)
	{
		return Vec4<real>(0, 0, 1, 1) * mat4GetRotationScalePart(mcam.inverse());
	}

	RenderContext::RenderContext(void)
	{
	}

	RenderContext::~RenderContext(void)
	{
	}

	void RenderContext::fillZbuffer(const CRect & rect, real value_inv)
	{
		fillZBuffer28(getZBufferRef28(), m_clipper & rect, value_inv);
	}

	void RenderContext::fillStencilBuffer(const CRect & rect, int value)
	{
		t3d::fillStencilBuffer(getStencilBufferRef(), rect, value);
	}

	void RenderContext16::fillSurface(const CRect & rect, const Vec4<real> & color)
	{
		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		fillSurface16(getSurfaceRef16(), m_clipper & rect, rgbaSaturate<real>(color * 255, 255));
	}

	void RenderContext16::drawTriangleListShadowVolumeZPass(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		removeTriangleListBackfaceAtScreen(getVertexList(), getClipStateList());
		reversalClipStateListScreenCulling(m_clipStateList2nd, getClipStateList());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		countTriangleListIncrementInFrontOfDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList());
		sClipTriangleListAtScreen(getVertexList(), m_clipStateList2nd, getViewport());
		countTriangleListDecrementInFrontOfDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), m_clipStateList2nd);
		boundSurfaceStencilBufferColor16(getSurfaceRef16(), getClipperRect(), getStencilBufferRef(), color);
	}

	void RenderContext16::drawTriangleIndexListShadowVolumeZPass(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		removeTriangleIndexListBackfaceAtScreen(getVertexList(), getVertexIndexList(), getClipStateList());
		reversalClipStateListScreenCulling(m_clipStateList2nd, getClipStateList());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		countTriangleIndexListIncrementInFrontOfDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), m_clipStateList2nd, getViewport());
		countTriangleIndexListDecrementInFrontOfDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), m_clipStateList2nd);
		boundSurfaceStencilBufferColor16(getSurfaceRef16(), getClipperRect(), getStencilBufferRef(), color);
	}

	void RenderContext16::drawTriangleListShadowVolumeZFail(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		removeTriangleListBackfaceAtScreen(getVertexList(), getClipStateList());
		reversalClipStateListScreenCulling(m_clipStateList2nd, getClipStateList());
		sClipTriangleListAtScreen(getVertexList(), m_clipStateList2nd, getViewport());
		countTriangleListIncrementBehindDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), m_clipStateList2nd);
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		countTriangleListDecrementBehindDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList());
		boundSurfaceStencilBufferColor16(getSurfaceRef16(), getClipperRect(), getStencilBufferRef(), color);
	}

	void RenderContext16::drawTriangleIndexListShadowVolumeZFail(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		removeTriangleIndexListBackfaceAtScreen(getVertexList(), getVertexIndexList(), getClipStateList());
		reversalClipStateListScreenCulling(m_clipStateList2nd, getClipStateList());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), m_clipStateList2nd, getViewport());
		countTriangleIndexListIncrementBehindDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), m_clipStateList2nd);
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		countTriangleIndexListDecrementBehindDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList());
		boundSurfaceStencilBufferColor16(getSurfaceRef16(), getClipperRect(), getStencilBufferRef(), color);
	}

	void RenderContext16::drawHorizonLine(int x0, int y0, int width, const Vec4<real> & color)
	{
		drawClippedHorizonLine16(getSurfaceRef16(), getClipperRect(), x0, y0, width, rgbaSaturate<real>(color * 255, 255));
	}

	void RenderContext16::drawVerticalLine(int x0, int y0, int height, const Vec4<real> & color)
	{
		drawClippedVerticalLine16(getSurfaceRef16(), getClipperRect(), x0, y0, height, rgbaSaturate<real>(color * 255, 255));
	}

	void RenderContext16::drawLineListZBufferRW(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 2);
		transformLineListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipLineListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenLineList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipLineListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawLineListZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList(), color);
	}

	void RenderContext16::drawLineIndexListZBufferRW(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 2);
		transformLineIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipLineIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenLineIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipLineIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawLineIndexListZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	void RenderContext16::drawTriangleListWireZBufferRW(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListWireZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList(), color);
	}

	void RenderContext16::drawTriangleIndexListWireZBufferRW(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListWireZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	void RenderContext16::drawTriangleListWireZBufferRWWithBackface(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListWireZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList(), color);
	}

	void RenderContext16::drawTriangleIndexListWireZBufferRWWithBackface(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListWireZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	void RenderContext16::drawTriangleListZBufferRW(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList(), color);
	}

	void RenderContext16::drawTriangleIndexListZBufferRW(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	void RenderContext16::drawTriangleListZBufferRWWithBackface(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList(), color);
	}

	void RenderContext16::drawTriangleIndexListZBufferRWWithBackface(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	void RenderContext16::drawTriangleListGouraudZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListGouraudAtCamera(getVertexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getColorList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListGouraudZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListGouraudAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getColorList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListGouraudZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListGouraudAtCamera(getVertexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getColorList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListGouraudZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListGouraudAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getColorList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListTextureZBufferW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTextureZBufferW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListTextureZBufferW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTextureZBufferW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListTextureZBufferWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTextureZBufferW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListTextureZBufferWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTextureZBufferW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListTexturePerspectiveLPZBufferW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTexturePerspectiveLPZBufferW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListTexturePerspectiveLPZBufferW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTexturePerspectiveLPZBufferW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListTexturePerspectiveLPZBufferWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTexturePerspectiveLPZBufferW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListTexturePerspectiveLPZBufferWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTexturePerspectiveLPZBufferW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListTextureZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTextureZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListTextureZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTextureZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListTextureZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTextureZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListTextureZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTextureZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListTexturePerspectiveLPZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTexturePerspectiveLPZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListTexturePerspectiveLPZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTexturePerspectiveLPZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListTexturePerspectiveLPZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTexturePerspectiveLPZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListTexturePerspectiveLPZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTexturePerspectiveLPZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListGouraudTextureZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudTextureZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListGouraudTextureZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTextureZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListGouraudTextureZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudTextureZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListGouraudTextureZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTextureZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListGouraudTexturePerspectiveLPZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudTexturePerspectiveLPZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleListGouraudTexturePerspectiveLPZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudTexturePerspectiveLPZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext16::drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef16(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext32::fillSurface(const CRect & rect, const Vec4<real> & color)
	{
		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		fillSurface32(getSurfaceRef32(), m_clipper & rect, rgbaSaturate<real>(color * 255, 255));
	}

	void RenderContext32::drawTriangleListShadowVolumeZPass(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		removeTriangleListBackfaceAtScreen(getVertexList(), getClipStateList());
		reversalClipStateListScreenCulling(m_clipStateList2nd, getClipStateList());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		countTriangleListIncrementInFrontOfDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList());
		sClipTriangleListAtScreen(getVertexList(), m_clipStateList2nd, getViewport());
		countTriangleListDecrementInFrontOfDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), m_clipStateList2nd);
		boundSurfaceStencilBufferColor32(getSurfaceRef32(), getClipperRect(), getStencilBufferRef(), color);
	}

	void RenderContext32::drawTriangleIndexListShadowVolumeZPass(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		removeTriangleIndexListBackfaceAtScreen(getVertexList(), getVertexIndexList(), getClipStateList());
		reversalClipStateListScreenCulling(m_clipStateList2nd, getClipStateList());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		countTriangleIndexListIncrementInFrontOfDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), m_clipStateList2nd, getViewport());
		countTriangleIndexListDecrementInFrontOfDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), m_clipStateList2nd);
		boundSurfaceStencilBufferColor32(getSurfaceRef32(), getClipperRect(), getStencilBufferRef(), color);
	}

	void RenderContext32::drawTriangleListShadowVolumeZFail(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		removeTriangleListBackfaceAtScreen(getVertexList(), getClipStateList());
		reversalClipStateListScreenCulling(m_clipStateList2nd, getClipStateList());
		sClipTriangleListAtScreen(getVertexList(), m_clipStateList2nd, getViewport());
		countTriangleListIncrementBehindDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), m_clipStateList2nd);
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		countTriangleListDecrementBehindDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList());
		boundSurfaceStencilBufferColor32(getSurfaceRef32(), getClipperRect(), getStencilBufferRef(), color);
	}

	void RenderContext32::drawTriangleIndexListShadowVolumeZFail(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		removeTriangleIndexListBackfaceAtScreen(getVertexList(), getVertexIndexList(), getClipStateList());
		reversalClipStateListScreenCulling(m_clipStateList2nd, getClipStateList());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), m_clipStateList2nd, getViewport());
		countTriangleIndexListIncrementBehindDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), m_clipStateList2nd);
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		countTriangleIndexListDecrementBehindDepth(getStencilBufferRef(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList());
		boundSurfaceStencilBufferColor32(getSurfaceRef32(), getClipperRect(), getStencilBufferRef(), color);
	}

	void RenderContext32::drawHorizonLine(int x0, int y0, int width, const Vec4<real> & color)
	{
		drawClippedHorizonLine32(getSurfaceRef32(), getClipperRect(), x0, y0, width, rgbaSaturate<real>(color * 255, 255));
	}

	void RenderContext32::drawVerticalLine(int x0, int y0, int height, const Vec4<real> & color)
	{
		drawClippedVerticalLine32(getSurfaceRef32(), getClipperRect(), x0, y0, height, rgbaSaturate<real>(color * 255, 255));
	}

	void RenderContext32::drawLineListZBufferRW(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 2);
		transformLineListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipLineListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenLineList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipLineListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawLineListZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList(), color);
	}

	void RenderContext32::drawLineIndexListZBufferRW(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 2);
		transformLineIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipLineIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenLineIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipLineIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawLineIndexListZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	void RenderContext32::drawTriangleListWireZBufferRW(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListWireZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList(), color);
	}

	void RenderContext32::drawTriangleIndexListWireZBufferRW(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListWireZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	void RenderContext32::drawTriangleListWireZBufferRWWithBackface(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListWireZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList(), color);
	}

	void RenderContext32::drawTriangleIndexListWireZBufferRWWithBackface(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListWireZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	void RenderContext32::drawTriangleListZBufferRW(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList(), color);
	}

	void RenderContext32::drawTriangleIndexListZBufferRW(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	void RenderContext32::drawTriangleListZBufferRWWithBackface(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList(), color);
	}

	void RenderContext32::drawTriangleIndexListZBufferRWWithBackface(const Vec4<real> & color)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	void RenderContext32::drawTriangleListGouraudZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListGouraudAtCamera(getVertexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getColorList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListGouraudZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListGouraudAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getColorList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListGouraudZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListGouraudAtCamera(getVertexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getColorList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListGouraudZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListGouraudAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getColorList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListTextureZBufferW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTextureZBufferW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListTextureZBufferW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTextureZBufferW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListTextureZBufferWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTextureZBufferW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListTextureZBufferWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTextureZBufferW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListTexturePerspectiveLPZBufferW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTexturePerspectiveLPZBufferW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListTexturePerspectiveLPZBufferW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTexturePerspectiveLPZBufferW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListTexturePerspectiveLPZBufferWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTexturePerspectiveLPZBufferW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListTexturePerspectiveLPZBufferWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTexturePerspectiveLPZBufferW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListTextureZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTextureZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListTextureZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTextureZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListTextureZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTextureZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListTextureZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTextureZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListTexturePerspectiveLPZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTexturePerspectiveLPZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListTexturePerspectiveLPZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTexturePerspectiveLPZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListTexturePerspectiveLPZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListTexturePerspectiveLPZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListTexturePerspectiveLPZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListTexturePerspectiveLPZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListGouraudTextureZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudTextureZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListGouraudTextureZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTextureZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListGouraudTextureZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudTextureZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListGouraudTextureZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTextureZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListGouraudTexturePerspectiveLPZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudTexturePerspectiveLPZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleListGouraudTexturePerspectiveLPZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexListSize() / 3);
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudTexturePerspectiveLPZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext32::drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRWWithBackface(void)
	{
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 3);
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraPosition());
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		zClipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		sClipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
	}
}
