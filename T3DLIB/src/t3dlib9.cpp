
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

	//bool TriangleStateListContext::isTriVisible(TRI_STATE state)
	//{
	//	return state == TS_ACTIVE || state == TS_CLIPPED; //|| state == TS_LARGE_CLIPPED;
	//}

	//const TriStateList & TriangleStateListContext::getTriStateList(void) const
	//{
	//	return m_triStateList;
	//}

	//TriStateList & TriangleStateListContext::getTriStateList(void)
	//{
	//	return m_triStateList;
	//}

	//void TriangleStateListContext::pushTriState(TRI_STATE state)
	//{
	//	m_triStateList.push_back(state);
	//}

	//void TriangleStateListContext::pushTriStateList(TriStateList::const_iterator begin, TriStateList::const_iterator end)
	//{
	//	m_triStateList.insert(getTriStateListEnd(), begin, end);
	//}

	//void TriangleStateListContext::clearTriStateList(void)
	//{
	//	m_triStateList.clear();
	//}

	//void TriangleStateListContext::resizeTriStateList(TriStateList::size_type size)
	//{
	//	m_triStateList.resize(size);
	//}

	//void TriangleStateListContext::resizeTriStateList(TriStateList::size_type size, TriStateList::const_reference state)
	//{
	//	m_triStateList.resize(size, state);
	//}

	//TriStateList::size_type TriangleStateListContext::getTriStateListSize(void) const
	//{
	//	return m_triStateList.size();
	//}

	//TriStateList::reference TriangleStateListContext::triStateAt(TriStateList::size_type i)
	//{
	//	_ASSERT(i < getTriStateListSize());

	//	return m_triStateList[i];
	//}

	//TriStateList::const_reference TriangleStateListContext::triStateAt(TriStateList::size_type i) const
	//{
	//	_ASSERT(i < getTriStateListSize());

	//	return m_triStateList[i];
	//}

	//TriStateList::iterator TriangleStateListContext::getTriStateListBegin()
	//{
	//	return m_triStateList.begin();
	//}

	//TriStateList::const_iterator TriangleStateListContext::getTriStateListBegin() const
	//{
	//	return m_triStateList.begin();
	//}

	//TriStateList::iterator TriangleStateListContext::getTriStateListEnd()
	//{
	//	return m_triStateList.end();
	//}

	//TriStateList::const_iterator TriangleStateListContext::getTriStateListEnd() const
	//{
	//	return m_triStateList.end();
	//}

	//TRI_STATE RenderLineListZBufferRW::zClipLineAtCamera(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());
	//	_ASSERT(getCameraNearZ() >= 1 && getCameraNearZ() < getCameraFarZ());

	//	const size_t v0_i = index * 2 + 0;
	//	const size_t v1_i = index * 2 + 1;

	//	if(vertexAt(v0_i).z < getCameraNearZ())
	//	{
	//		if(vertexAt(v1_i).z < getCameraNearZ())
	//		{
	//			return TS_CULLED;
	//		}
	//		else
	//		{
	//			resizeVertexList(getVertexListSize() + 2);
	//			const Vec4<real> & v0 = vertexAt(v0_i);
	//			const Vec4<real> & v1 = vertexAt(v1_i);

	//			Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 2);
	//			Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 1);

	//			new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.x, v1.x);
	//			new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.y, v1.y);
	//			new_v0.z = getCameraNearZ();

	//			new_v1 = v1;

	//			pushTriState(TS_ACTIVE);
	//		}
	//	}
	//	else
	//	{
	//		if(vertexAt(v1_i).z < getCameraNearZ())
	//		{
	//			resizeVertexList(getVertexListSize() + 2);
	//			const Vec4<real> & v0 = vertexAt(v0_i);
	//			const Vec4<real> & v1 = vertexAt(v1_i);

	//			Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 2);
	//			Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 1);

	//			new_v0 = v0;

	//			new_v1.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.x, v1.x);
	//			new_v1.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.y, v1.y);
	//			new_v1.z = getCameraNearZ();

	//			pushTriState(TS_ACTIVE);
	//		}
	//		else
	//		{
	//			return TS_ACTIVE;
	//		}
	//	}
	//	return TS_CULLED;
	//}

	//TRI_STATE RenderLineListZBufferRW::sClipLineAtScreen(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());

	//	const size_t ti = index * 2;
	//	const Vec4<real> & v0 = vertexAt(ti + 0);
	//	const Vec4<real> & v1 = vertexAt(ti + 1);

	//	if(std::min(v0.x, v1.x) >= getViewport().right)
	//		return TS_CULLED;

	//	if(std::min(v0.y, v1.y) >= getViewport().bottom)
	//		return TS_CULLED;

	//	if(std::max(v0.x, v1.x) < getViewport().left)
	//		return TS_CULLED;

	//	if(std::max(v0.y, v1.y) < getViewport().top)
	//		return TS_CULLED;

	//	if(std::min(v0.x, v1.x) < getViewport().left)
	//		return TS_CLIPPED;

	//	if(std::min(v0.y, v1.y) < getViewport().top)
	//		return TS_CLIPPED;

	//	if(std::max(v0.x, v1.x) >= getViewport().right)
	//		return TS_CLIPPED;

	//	if(std::max(v0.y, v1.y) >= getViewport().bottom)
	//		return TS_CLIPPED;

	//	return TS_ACTIVE;
	//}

	//void RenderLineListZBufferRW::reset(void)
	//{
	//	clearTriStateList();
	//	resizeTriStateList(getVertexListSize() / 2, TS_ACTIVE);

	//	resizeVertexList(getTriStateListSize() * 2);
	//}

	//void RenderLineListZBufferRW::worldToCamera(void)
	//{
	//	VertexList::iterator v_iter = getVertexListBegin();
	//	for(; v_iter != getVertexListEnd(); v_iter++)
	//	{
	//		*v_iter *= getCameraMatrix();
	//	}
	//}

	//void RenderLineListZBufferRW::zClipAtCamera(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 2);

	//	const size_t orig_size = getTriStateListSize();

	//	for(size_t i = 0; i < orig_size; i++)
	//	{
	//		_ASSERT(TS_ACTIVE == triStateAt(i));

	//		TRI_STATE state = zClipLineAtCamera(i); triStateAt(i) = state; // ***
	//	}
	//}

	//void RenderLineListZBufferRW::cameraToScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 2);

	//	const real halfWidth = (real)(getViewport().right - getViewport().left) / 2;
	//	const real halfHeight = (real)(getViewport().bottom - getViewport().top) / 2;

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			const size_t vi = i * 2;
	//			Vec4<real> & v0 = vertexAt(vi + 0);
	//			Vec4<real> & v1 = vertexAt(vi + 1);

	//			//       x * ( width / 2 ) * ctan( fov / 2 )
	//			// x' = -------------------------------------
	//			//                       z

	//			v0.x = getViewport().left + v0.x * getCameraProjection().x / v0.z * halfWidth + halfWidth;
	//			v1.x = getViewport().left + v1.x * getCameraProjection().x / v1.z * halfWidth + halfWidth;

	//			//       y * ( height / 2 ) * ctan( fov / 2 )
	//			// y' = -------------------------------------
	//			//                       z

	//			v0.y = getViewport().top + halfHeight - v0.y * getCameraProjection().y / v0.z * halfHeight;
	//			v1.y = getViewport().top + halfHeight - v1.y * getCameraProjection().y / v1.z * halfHeight;
	//		}
	//	}
	//}

	//void RenderLineListZBufferRW::sClipAtScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 2);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			triStateAt(i) = sClipLineAtScreen(i);
	//		}
	//	}
	//}

	//void RenderLineListZBufferRW::drawLineList16(const Vec4<real> & color)
	//{
	//	_ASSERT(false);

	//	UNREFERENCED_PARAMETER(color);
	//}

	//void RenderLineListZBufferRW::drawLineList32(const Vec4<real> & color)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 2);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t vi = i * 2;

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawLineZBufferRW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				rgbaSaturate(color * 255, real(255)));
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedLineZBufferRW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				rgbaSaturate(color * 255, real(255)));
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//TRI_STATE RenderLineIndexListZBufferRW::zClipLineAtCamera(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());
	//	_ASSERT(getCameraNearZ() >= 1 && getCameraNearZ() < getCameraFarZ());

	//	const size_t v0_i = vertexIndexAt(index * 2 + 0);
	//	const size_t v1_i = vertexIndexAt(index * 2 + 1);

	//	if(vertexAt(v0_i).z < getCameraNearZ())
	//	{
	//		if(vertexAt(v1_i).z < getCameraNearZ())
	//		{
	//			return TS_CULLED;
	//		}
	//		else
	//		{
	//			resizeVertexList(getVertexListSize() + 1);
	//			const Vec4<real> & v0 = vertexAt(v0_i);
	//			const Vec4<real> & v1 = vertexAt(v1_i);

	//			Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 1);

	//			new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.x, v1.x);
	//			new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.y, v1.y);
	//			new_v0.z = getCameraNearZ();

	//			pushVertexIndex(getVertexListSize() - 1);
	//			pushVertexIndex(v1_i);

	//			pushTriState(TS_ACTIVE);
	//		}
	//	}
	//	else
	//	{
	//		if(vertexAt(v1_i).z < getCameraNearZ())
	//		{
	//			resizeVertexList(getVertexListSize() + 1);
	//			const Vec4<real> & v0 = vertexAt(v0_i);
	//			const Vec4<real> & v1 = vertexAt(v1_i);

	//			Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 1);

	//			new_v1.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.x, v1.x);
	//			new_v1.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.y, v1.y);
	//			new_v1.z = getCameraNearZ();

	//			pushVertexIndex(v0_i);
	//			pushVertexIndex(getVertexListSize() - 1);

	//			pushTriState(TS_ACTIVE);
	//		}
	//		else
	//		{
	//			return TS_ACTIVE;
	//		}
	//	}
	//	return TS_CULLED;
	//}

	//TRI_STATE RenderLineIndexListZBufferRW::sClipLineAtScreen(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());

	//	const size_t ti = index * 2;
	//	const Vec4<real> & v0 = vertexAt(vertexIndexAt(ti + 0));
	//	const Vec4<real> & v1 = vertexAt(vertexIndexAt(ti + 1));

	//	if(std::min(v0.x, v1.x) >= getViewport().right)
	//		return TS_CULLED;

	//	if(std::min(v0.y, v1.y) >= getViewport().bottom)
	//		return TS_CULLED;

	//	if(std::max(v0.x, v1.x) < getViewport().left)
	//		return TS_CULLED;

	//	if(std::max(v0.y, v1.y) < getViewport().top)
	//		return TS_CULLED;

	//	if(std::min(v0.x, v1.x) < getViewport().left)
	//		return TS_CLIPPED;

	//	if(std::min(v0.y, v1.y) < getViewport().top)
	//		return TS_CLIPPED;

	//	if(std::max(v0.x, v1.x) >= getViewport().right)
	//		return TS_CLIPPED;

	//	if(std::max(v0.y, v1.y) >= getViewport().bottom)
	//		return TS_CLIPPED;

	//	return TS_ACTIVE;
	//}

	//void RenderLineIndexListZBufferRW::reset(void)
	//{
	//	clearTriStateList();
	//	resizeTriStateList(getVertexIndexListSize() / 2, TS_ACTIVE);

	//	resizeVertexIndexList(getTriStateListSize() * 2);
	//}

	//void RenderLineIndexListZBufferRW::worldToCamera(void)
	//{
	//	VertexList::iterator v_iter = getVertexListBegin();
	//	for(; v_iter != getVertexListEnd(); v_iter++)
	//	{
	//		*v_iter *= getCameraMatrix();
	//	}
	//}

	//void RenderLineIndexListZBufferRW::zClipAtCamera(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 2);

	//	const size_t orig_size = getTriStateListSize();

	//	for(size_t i = 0; i < orig_size; i++)
	//	{
	//		_ASSERT(TS_ACTIVE == triStateAt(i));

	//		TRI_STATE state = zClipLineAtCamera(i); triStateAt(i) = state; // ***
	//	}
	//}

	//void RenderLineIndexListZBufferRW::cameraToScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 2);

	//	const real halfWidth = (real)(getViewport().right - getViewport().left) / 2;
	//	const real halfHeight = (real)(getViewport().bottom - getViewport().top) / 2;

	//	VertexList::iterator v_iter = getVertexListBegin();
	//	for(; v_iter != getVertexListEnd(); v_iter++)
	//	{
	//		//       x * ( width / 2 ) * ctan( fov / 2 )
	//		// x' = -------------------------------------
	//		//                       z

	//		v_iter->x = getViewport().left + v_iter->x * getCameraProjection().x / v_iter->z * halfWidth + halfWidth;

	//		//       y * ( height / 2 ) * ctan( fov / 2 )
	//		// y' = -------------------------------------
	//		//                       z

	//		v_iter->y = getViewport().top + halfHeight - v_iter->y * getCameraProjection().y / v_iter->z * halfHeight;
	//	}
	//}

	//void RenderLineIndexListZBufferRW::sClipAtScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 2);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			triStateAt(i) = sClipLineAtScreen(i);
	//		}
	//	}
	//}

	//void RenderLineIndexListZBufferRW::drawLineIndexList16(const Vec4<real> & color)
	//{
	//	_ASSERT(false);

	//	UNREFERENCED_PARAMETER(color);
	//}

	//void RenderLineIndexListZBufferRW::drawLineIndexList32(const Vec4<real> & color)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 2);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t vi = i * 2;

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawLineZBufferRW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				vertexAt(vertexIndexAt(vi + 0)),
	//				vertexAt(vertexIndexAt(vi + 1)),
	//				rgbaSaturate(color * 255, real(255)));
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedLineZBufferRW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				vertexAt(vertexIndexAt(vi + 0)),
	//				vertexAt(vertexIndexAt(vi + 1)),
	//				rgbaSaturate(color * 255, real(255)));
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleListWireZBufferRW::zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexListSize());
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		v0_i = index * 3 + 0;
	//		v1_i = index * 3 + 1;
	//		v2_i = index * 3 + 2;
	//		break;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		v0_i = index * 3 + 2;
	//		v1_i = index * 3 + 0;
	//		v2_i = index * 3 + 1;
	//		break;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		v0_i = index * 3 + 1;
	//		v1_i = index * 3 + 2;
	//		v2_i = index * 3 + 0;
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 3);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 3);
	//	Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & new_v2 = vertexAt(getVertexListSize() - 1);

	//	//resizeUVList(getUVListSize() + 3);
	//	//const Vec2<real> & t0 = uvAt(v0_i);
	//	//const Vec2<real> & t1 = uvAt(v1_i);
	//	//const Vec2<real> & t2 = uvAt(v2_i);

	//	//Vec2<real> & new_t0 = uvAt(getUVListSize() - 3);
	//	//Vec2<real> & new_t1 = uvAt(getUVListSize() - 2);
	//	//Vec2<real> & new_t2 = uvAt(getUVListSize() - 1);

	//	//resizeColorList(getColorListSize() + 3);
	//	//const Vec4<real> & c0 = colorAt(v0_i);
	//	//const Vec4<real> & c1 = colorAt(v1_i);
	//	//const Vec4<real> & c2 = colorAt(v2_i);

	//	//Vec4<real> & new_c0 = colorAt(getColorListSize() - 3);
	//	//Vec4<real> & new_c1 = colorAt(getColorListSize() - 2);
	//	//Vec4<real> & new_c2 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*		2
	//	* -------------
	//	*	1       0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	new_v0.z = getCameraNearZ();

	//	//new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	//new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	//new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	//new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	//new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	new_v1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.x, v2.x);
	//	new_v1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.y, v2.y);
	//	new_v1.z = getCameraNearZ();

	//	//new_t1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.x, t2.x);
	//	//new_t1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.y, t2.y);

	//	//new_c1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.x, c2.x);
	//	//new_c1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.y, c2.y);
	//	//new_c1.z = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.z, c2.z);

	//	new_v2 = v2;
	//	//new_t2 = t2;
	//	//new_c2 = c2;

	//	pushTriState(TS_ACTIVE);
	//}

	//void RenderTriangleListWireZBufferRW::zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexListSize());
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0:
	//		v0_i = index * 3 + 0;
	//		v1_i = index * 3 + 1;
	//		v2_i = index * 3 + 2;
	//		break;

	//	case CLIP_MASK_V1:
	//		v0_i = index * 3 + 1;
	//		v1_i = index * 3 + 2;
	//		v2_i = index * 3 + 0;
	//		break;

	//	case CLIP_MASK_V2:
	//		v0_i = index * 3 + 2;
	//		v1_i = index * 3 + 0;
	//		v2_i = index * 3 + 1;
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 6);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 6);
	//	Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 5);
	//	Vec4<real> & new_v2 = vertexAt(getVertexListSize() - 4);

	//	Vec4<real> & dbl_v0 = vertexAt(getVertexListSize() - 3);
	//	Vec4<real> & dbl_v1 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & dbl_v2 = vertexAt(getVertexListSize() - 1);

	//	//resizeUVList(getUVListSize() + 6);
	//	//const Vec2<real> & t0 = uvAt(v0_i);
	//	//const Vec2<real> & t1 = uvAt(v1_i);
	//	//const Vec2<real> & t2 = uvAt(v2_i);

	//	//Vec2<real> & new_t0 = uvAt(getUVListSize() - 6);
	//	//Vec2<real> & new_t1 = uvAt(getUVListSize() - 5);
	//	//Vec2<real> & new_t2 = uvAt(getUVListSize() - 4);

	//	//Vec2<real> & dbl_t0 = uvAt(getUVListSize() - 3);
	//	//Vec2<real> & dbl_t1 = uvAt(getUVListSize() - 2);
	//	//Vec2<real> & dbl_t2 = uvAt(getUVListSize() - 1);

	//	//resizeColorList(getColorListSize() + 6);
	//	//const Vec4<real> & c0 = colorAt(v0_i);
	//	//const Vec4<real> & c1 = colorAt(v1_i);
	//	//const Vec4<real> & c2 = colorAt(v2_i);

	//	//Vec4<real> & new_c0 = colorAt(getColorListSize() - 6);
	//	//Vec4<real> & new_c1 = colorAt(getColorListSize() - 5);
	//	//Vec4<real> & new_c2 = colorAt(getColorListSize() - 4);

	//	//Vec4<real> & dbl_c0 = colorAt(getColorListSize() - 3);
	//	//Vec4<real> & dbl_c1 = colorAt(getColorListSize() - 2);
	//	//Vec4<real> & dbl_c2 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*	1       2
	//	* -------------
	//	*		0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.x, v1.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.y, v1.y);
	//	new_v0.z = getCameraNearZ();

	//	//new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.x, t1.x);
	//	//new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.y, t1.y);

	//	//new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.x, c1.x);
	//	//new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.y, c1.y);
	//	//new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.z, c1.z);

	//	new_v1 = v1;
	//	//new_t1 = t1;
	//	//new_c1 = c1;

	//	new_v2 = v2;
	//	//new_t2 = t2;
	//	//new_c2 = c2;

	//	pushTriState(TS_ACTIVE);

	//	dbl_v0 = new_v0;
	//	//dbl_t0 = new_t0;
	//	//dbl_c0 = new_c0;

	//	dbl_v1 = v2;
	//	//dbl_t1 = t2;
	//	//dbl_c1 = c2;

	//	dbl_v2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	dbl_v2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	dbl_v2.z = getCameraNearZ();

	//	//dbl_t2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	//dbl_t2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	//dbl_c2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	//dbl_c2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	//dbl_c2.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	pushTriState(TS_ACTIVE);
	//}

	//TRI_STATE RenderTriangleListWireZBufferRW::zClipTriangleAtCamera(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());
	//	_ASSERT(getCameraNearZ() >= 1 && getCameraNearZ() < getCameraFarZ());

	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(ti + 0);
	//	const Vec4<real> & v1 = vertexAt(ti + 1);
	//	const Vec4<real> & v2 = vertexAt(ti + 2);

	//	DWORD clip_mask_nz = 0;
	//	DWORD clip_mask_fz = 0;

	//	if(v0.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V0;
	//	else if(v0.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V0;

	//	if(v1.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V1;
	//	else if(v1.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V1;

	//	if(v2.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V2;
	//	else if(v2.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V2;

	//	switch(clip_mask_fz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;
	//	}

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;
	//	}

	//	return TS_ACTIVE;
	//}

	//TRI_STATE RenderTriangleListWireZBufferRW::sClipTriangleAtScreen(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());

	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(ti + 0);
	//	const Vec4<real> & v1 = vertexAt(ti + 1);
	//	const Vec4<real> & v2 = vertexAt(ti + 2);

	//	if(min(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CULLED;

	//	if(min(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CULLED;

	//	if(max(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CULLED;

	//	if(max(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CULLED;

	//	if(min(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CLIPPED;

	//	if(min(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CLIPPED;

	//	if(max(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CLIPPED;

	//	if(max(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CLIPPED;

	//	return TS_ACTIVE;
	//}

	//void RenderTriangleListWireZBufferRW::reset(void)
	//{
	//	//_ASSERT(getVertexListSize() == getNormalListSize());
	//	//_ASSERT(getVertexListSize() == getUVListSize());

	//	clearTriStateList();
	//	resizeTriStateList(getVertexListSize() / 3, TS_ACTIVE);

	//	resizeVertexList(getTriStateListSize() * 3);
	//	//resizeNormalList(getTriStateListSize() * 3);
	//	//resizeUVList(getTriStateListSize() * 3);
	//}

	//void RenderTriangleListWireZBufferRW::removeBackfaceAtWorld(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		_ASSERT(TS_ACTIVE == triStateAt(i));

	//		const size_t vi = i * 3;
	//		const Vec4<real> & v0 = vertexAt(vi + 0);
	//		const Vec4<real> & v1 = vertexAt(vi + 1);
	//		const Vec4<real> & v2 = vertexAt(vi + 2);

	//		if(vec3Dot(
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(getCameraPosition(), v0)) <= 0)
	//		{
	//			triStateAt(i) = TS_BACKFACE;
	//		}
	//	}
	//}

	//void RenderTriangleListWireZBufferRW::worldToCamera(void)
	//{
	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			const size_t vi = i * 3;
	//			vertexAt(vi + 0) *= getCameraMatrix();
	//			vertexAt(vi + 1) *= getCameraMatrix();
	//			vertexAt(vi + 2) *= getCameraMatrix();
	//		}
	//	}
	//}

	//void RenderTriangleListWireZBufferRW::zClipAtCamera(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	const size_t orig_size = getTriStateListSize();

	//	for(size_t i = 0; i < orig_size; i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			TRI_STATE state = zClipTriangleAtCamera(i); triStateAt(i) = state; // ***
	//		}
	//	}
	//}

	//void RenderTriangleListWireZBufferRW::cameraToScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	const real halfWidth = (real)(getViewport().right - getViewport().left) / 2;
	//	const real halfHeight = (real)(getViewport().bottom - getViewport().top) / 2;

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			const size_t vi = i * 3;
	//			Vec4<real> & v0 = vertexAt(vi + 0);
	//			Vec4<real> & v1 = vertexAt(vi + 1);
	//			Vec4<real> & v2 = vertexAt(vi + 2);

	//			//       x * ( width / 2 ) * ctan( fov / 2 )
	//			// x' = -------------------------------------
	//			//                       z

	//			v0.x = getViewport().left + v0.x * getCameraProjection().x / v0.z * halfWidth + halfWidth;
	//			v1.x = getViewport().left + v1.x * getCameraProjection().x / v1.z * halfWidth + halfWidth;
	//			v2.x = getViewport().left + v2.x * getCameraProjection().x / v2.z * halfWidth + halfWidth;

	//			//       y * ( height / 2 ) * ctan( fov / 2 )
	//			// y' = -------------------------------------
	//			//                       z

	//			v0.y = getViewport().top + halfHeight - v0.y * getCameraProjection().y / v0.z * halfHeight;
	//			v1.y = getViewport().top + halfHeight - v1.y * getCameraProjection().y / v1.z * halfHeight;
	//			v2.y = getViewport().top + halfHeight - v2.y * getCameraProjection().y / v2.z * halfHeight;
	//		}
	//	}
	//}

	//void RenderTriangleListWireZBufferRW::sClipAtScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			triStateAt(i) = sClipTriangleAtScreen(i);
	//		}
	//	}
	//}

	//void RenderTriangleListWireZBufferRW::drawTriangleList16(const Vec4<real> & color)
	//{
	//	_ASSERT(false);

	//	UNREFERENCED_PARAMETER(color);
	//}

	//void RenderTriangleListWireZBufferRW::drawTriangleList32(const Vec4<real> & color)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	//const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = i * 3 + 0;
	//		const size_t v1_i = i * 3 + 1;
	//		const size_t v2_i = i * 3 + 2;

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawLineZBufferRW32(getSurfaceRef32(), getZBufferRef28(), vertexAt(v0_i), vertexAt(v1_i), rgbaSaturate(color * 255, real(255)));
	//			drawLineZBufferRW32(getSurfaceRef32(), getZBufferRef28(), vertexAt(v1_i), vertexAt(v2_i), rgbaSaturate(color * 255, real(255)));
	//			drawLineZBufferRW32(getSurfaceRef32(), getZBufferRef28(), vertexAt(v2_i), vertexAt(v0_i), rgbaSaturate(color * 255, real(255)));
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedLineZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v0_i), vertexAt(v1_i), rgbaSaturate(color * 255, real(255)));
	//			drawClippedLineZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v1_i), vertexAt(v2_i), rgbaSaturate(color * 255, real(255)));
	//			drawClippedLineZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v2_i), vertexAt(v0_i), rgbaSaturate(color * 255, real(255)));
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleListWireZBufferRW::drawTriangleListWithoutThird16(const Vec4<real> & color)
	//{
	//	_ASSERT(false);

	//	UNREFERENCED_PARAMETER(color);
	//}

	//void RenderTriangleListWireZBufferRW::drawTriangleListWithoutThird32(const Vec4<real> & color)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	//const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = i * 3 + 0;
	//		const size_t v1_i = i * 3 + 1;
	//		const size_t v2_i = i * 3 + 2;

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawLineZBufferRW32(getSurfaceRef32(), getZBufferRef28(), vertexAt(v0_i), vertexAt(v1_i), rgbaSaturate(color * 255, real(255)));
	//			drawLineZBufferRW32(getSurfaceRef32(), getZBufferRef28(), vertexAt(v1_i), vertexAt(v2_i), rgbaSaturate(color * 255, real(255)));
	//			//drawLineZBufferRW32(getSurfaceRef32(), getZBufferRef28(), vertexAt(v2_i), vertexAt(v0_i), rgbaSaturate(color * 255, real(255)));
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedLineZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v0_i), vertexAt(v1_i), rgbaSaturate(color * 255, real(255)));
	//			drawClippedLineZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v1_i), vertexAt(v2_i), rgbaSaturate(color * 255, real(255)));
	//			//drawClippedLineZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v2_i), vertexAt(v0_i), rgbaSaturate(color * 255, real(255)));
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListWireZBufferRW::zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexIndexListSize());
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		v0_i = vertexIndexAt(index * 3 + 0);
	//		v1_i = vertexIndexAt(index * 3 + 1);
	//		v2_i = vertexIndexAt(index * 3 + 2);
	//		break;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		v0_i = vertexIndexAt(index * 3 + 2);
	//		v1_i = vertexIndexAt(index * 3 + 0);
	//		v2_i = vertexIndexAt(index * 3 + 1);
	//		break;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		v0_i = vertexIndexAt(index * 3 + 1);
	//		v1_i = vertexIndexAt(index * 3 + 2);
	//		v2_i = vertexIndexAt(index * 3 + 0);
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 2);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 1);

	//	//resizeUVList(getUVListSize() + 2);
	//	//const Vec2<real> & t0 = uvAt(v0_i);
	//	//const Vec2<real> & t1 = uvAt(v1_i);
	//	//const Vec2<real> & t2 = uvAt(v2_i);

	//	//Vec2<real> & new_t0 = uvAt(getUVListSize() - 2);
	//	//Vec2<real> & new_t1 = uvAt(getUVListSize() - 1);

	//	//resizeColorList(getColorListSize() + 2);
	//	//const Vec4<real> & c0 = colorAt(v0_i);
	//	//const Vec4<real> & c1 = colorAt(v1_i);
	//	//const Vec4<real> & c2 = colorAt(v2_i);

	//	//Vec4<real> & new_c0 = colorAt(getColorListSize() - 2);
	//	//Vec4<real> & new_c1 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*		2
	//	* -------------
	//	*	1       0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	new_v0.z = getCameraNearZ();

	//	//new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	//new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	//new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	//new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	//new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	new_v1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.x, v2.x);
	//	new_v1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.y, v2.y);
	//	new_v1.z = getCameraNearZ();

	//	//new_t1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.x, t2.x);
	//	//new_t1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.y, t2.y);

	//	//new_c1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.x, c2.x);
	//	//new_c1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.y, c2.y);
	//	//new_c1.z = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.z, c2.z);

	//	pushVertexIndex(getVertexListSize() - 2);
	//	pushVertexIndex(getVertexListSize() - 1);
	//	pushVertexIndex(v2_i);

	//	pushTriState(TS_ACTIVE);
	//}

	//void RenderTriangleIndexListWireZBufferRW::zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexIndexListSize());
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0:
	//		v0_i = vertexIndexAt(index * 3 + 0);
	//		v1_i = vertexIndexAt(index * 3 + 1);
	//		v2_i = vertexIndexAt(index * 3 + 2);
	//		break;

	//	case CLIP_MASK_V1:
	//		v0_i = vertexIndexAt(index * 3 + 1);
	//		v1_i = vertexIndexAt(index * 3 + 2);
	//		v2_i = vertexIndexAt(index * 3 + 0);
	//		break;

	//	case CLIP_MASK_V2:
	//		v0_i = vertexIndexAt(index * 3 + 2);
	//		v1_i = vertexIndexAt(index * 3 + 0);
	//		v2_i = vertexIndexAt(index * 3 + 1);
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 2);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & dbl_v2 = vertexAt(getVertexListSize() - 1);

	//	//resizeUVList(getUVListSize() + 2);
	//	//const Vec2<real> & t0 = uvAt(v0_i);
	//	//const Vec2<real> & t1 = uvAt(v1_i);
	//	//const Vec2<real> & t2 = uvAt(v2_i);

	//	//Vec2<real> & new_t0 = uvAt(getUVListSize() - 2);
	//	//Vec2<real> & dbl_t2 = uvAt(getUVListSize() - 1);

	//	//resizeColorList(getColorListSize() + 2);
	//	//const Vec4<real> & c0 = colorAt(v0_i);
	//	//const Vec4<real> & c1 = colorAt(v1_i);
	//	//const Vec4<real> & c2 = colorAt(v2_i);

	//	//Vec4<real> & new_c0 = colorAt(getColorListSize() - 2);
	//	//Vec4<real> & dbl_c2 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*	1       2
	//	* -------------
	//	*		0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.x, v1.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.y, v1.y);
	//	new_v0.z = getCameraNearZ();

	//	//new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.x, t1.x);
	//	//new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.y, t1.y);

	//	//new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.x, c1.x);
	//	//new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.y, c1.y);
	//	//new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.z, c1.z);

	//	pushVertexIndex(getVertexListSize() - 2);
	//	pushVertexIndex(v1_i);
	//	pushVertexIndex(v2_i);

	//	pushTriState(TS_ACTIVE);

	//	dbl_v2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	dbl_v2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	dbl_v2.z = getCameraNearZ();

	//	//dbl_t2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	//dbl_t2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	//dbl_c2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	//dbl_c2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	//dbl_c2.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	pushVertexIndex(getVertexListSize() - 2);
	//	pushVertexIndex(v2_i);
	//	pushVertexIndex(getVertexListSize() - 1);

	//	pushTriState(TS_ACTIVE);
	//}

	//TRI_STATE RenderTriangleIndexListWireZBufferRW::zClipTriangleAtCamera(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());
	//	_ASSERT(getCameraNearZ() >= 1 && getCameraNearZ() < getCameraFarZ());

	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(vertexIndexAt(ti + 0));
	//	const Vec4<real> & v1 = vertexAt(vertexIndexAt(ti + 1));
	//	const Vec4<real> & v2 = vertexAt(vertexIndexAt(ti + 2));

	//	DWORD clip_mask_nz = 0;
	//	DWORD clip_mask_fz = 0;

	//	if(v0.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V0;
	//	else if(v0.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V0;

	//	if(v1.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V1;
	//	else if(v1.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V1;

	//	if(v2.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V2;
	//	else if(v2.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V2;

	//	switch(clip_mask_fz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;
	//	}

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;
	//	}

	//	return TS_ACTIVE;
	//}

	//TRI_STATE RenderTriangleIndexListWireZBufferRW::sClipTriangleAtScreen(const size_t index)
	//{
	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(vertexIndexAt(ti + 0));
	//	const Vec4<real> & v1 = vertexAt(vertexIndexAt(ti + 1));
	//	const Vec4<real> & v2 = vertexAt(vertexIndexAt(ti + 2));

	//	if(min(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CULLED;

	//	if(min(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CULLED;

	//	if(max(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CULLED;

	//	if(max(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CULLED;

	//	if(min(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CLIPPED;

	//	if(min(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CLIPPED;

	//	if(max(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CLIPPED;

	//	if(max(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CLIPPED;

	//	return TS_ACTIVE;
	//}

	//void RenderTriangleIndexListWireZBufferRW::reset(void)
	//{
	//	//_ASSERT(getVertexListSize() == getNormalListSize());
	//	//_ASSERT(getVertexListSize() == getUVListSize());

	//	clearTriStateList();
	//	resizeTriStateList(getVertexIndexListSize() / 3, TS_ACTIVE);

	//	resizeVertexIndexList(getTriStateListSize() * 3);
	//}

	//void RenderTriangleIndexListWireZBufferRW::removeBackfaceAtWorld(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		_ASSERT(TS_ACTIVE == triStateAt(i));

	//		const size_t vi = i * 3;
	//		const Vec4<real> & v0 = vertexAt(vertexIndexAt(vi + 0));
	//		const Vec4<real> & v1 = vertexAt(vertexIndexAt(vi + 1));
	//		const Vec4<real> & v2 = vertexAt(vertexIndexAt(vi + 2));

	//		if(vec3Dot(
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(getCameraPosition(), v0)) <= 0)
	//		{
	//			triStateAt(i) = TS_BACKFACE;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListWireZBufferRW::worldToCamera(void)
	//{
	//	VertexList::iterator v_iter = getVertexListBegin();
	//	for(; v_iter != getVertexListEnd(); v_iter++)
	//	{
	//		*v_iter *= getCameraMatrix();
	//	}
	//}

	//void RenderTriangleIndexListWireZBufferRW::zClipAtCamera(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);

	//	const size_t orig_size = getTriStateListSize();

	//	for(size_t i = 0; i < orig_size; i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			TRI_STATE state = zClipTriangleAtCamera(i); triStateAt(i) = state; // ***
	//		}
	//	}
	//}

	//void RenderTriangleIndexListWireZBufferRW::cameraToScreen(void)
	//{
	//	const real halfWidth = (real)(getViewport().right - getViewport().left) / 2;
	//	const real halfHeight = (real)(getViewport().bottom - getViewport().top) / 2;

	//	VertexList::iterator v_iter = getVertexListBegin();
	//	for(; v_iter != getVertexListEnd(); v_iter++)
	//	{
	//		//       x * ( width / 2 ) * ctan( fov / 2 )
	//		// x' = -------------------------------------
	//		//                       z

	//		v_iter->x = getViewport().left + v_iter->x * getCameraProjection().x / v_iter->z * halfWidth + halfWidth;

	//		//       y * ( height / 2 ) * ctan( fov / 2 )
	//		// y' = -------------------------------------
	//		//                       z

	//		v_iter->y = getViewport().top + halfHeight - v_iter->y * getCameraProjection().y / v_iter->z * halfHeight;
	//	}
	//}

	//void RenderTriangleIndexListWireZBufferRW::sClipAtScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			triStateAt(i) = sClipTriangleAtScreen(i);
	//		}
	//	}
	//}

	//void RenderTriangleIndexListWireZBufferRW::drawTriangleIndexList16(const Vec4<real> & color)
	//{
	//	_ASSERT(false);

	//	UNREFERENCED_PARAMETER(color);
	//}

	//void RenderTriangleIndexListWireZBufferRW::drawTriangleIndexList32(const Vec4<real> & color)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	//const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = vertexIndexAt(i * 3 + 0);
	//		const size_t v1_i = vertexIndexAt(i * 3 + 1);
	//		const size_t v2_i = vertexIndexAt(i * 3 + 2);

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawLineZBufferRW32(getSurfaceRef32(), getZBufferRef28(), vertexAt(v0_i), vertexAt(v1_i), rgbaSaturate(color * 255, real(255)));
	//			drawLineZBufferRW32(getSurfaceRef32(), getZBufferRef28(), vertexAt(v1_i), vertexAt(v2_i), rgbaSaturate(color * 255, real(255)));
	//			drawLineZBufferRW32(getSurfaceRef32(), getZBufferRef28(), vertexAt(v2_i), vertexAt(v0_i), rgbaSaturate(color * 255, real(255)));
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedLineZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v0_i), vertexAt(v1_i), rgbaSaturate(color * 255, real(255)));
	//			drawClippedLineZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v1_i), vertexAt(v2_i), rgbaSaturate(color * 255, real(255)));
	//			drawClippedLineZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v2_i), vertexAt(v0_i), rgbaSaturate(color * 255, real(255)));
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListWireZBufferRW::drawTriangleIndexListWithoutThird16(const Vec4<real> & color)
	//{
	//	_ASSERT(false);

	//	UNREFERENCED_PARAMETER(color);
	//}

	//void RenderTriangleIndexListWireZBufferRW::drawTriangleIndexListWithoutThird32(const Vec4<real> & color)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	//const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = vertexIndexAt(i * 3 + 0);
	//		const size_t v1_i = vertexIndexAt(i * 3 + 1);
	//		const size_t v2_i = vertexIndexAt(i * 3 + 2);

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawLineZBufferRW32(getSurfaceRef32(), getZBufferRef28(), vertexAt(v0_i), vertexAt(v1_i), rgbaSaturate(color * 255, real(255)));
	//			drawLineZBufferRW32(getSurfaceRef32(), getZBufferRef28(), vertexAt(v1_i), vertexAt(v2_i), rgbaSaturate(color * 255, real(255)));
	//			//drawLineZBufferRW32(getSurfaceRef32(), getZBufferRef28(), vertexAt(v2_i), vertexAt(v0_i), rgbaSaturate(color * 255, real(255)));
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedLineZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v0_i), vertexAt(v1_i), rgbaSaturate(color * 255, real(255)));
	//			drawClippedLineZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v1_i), vertexAt(v2_i), rgbaSaturate(color * 255, real(255)));
	//			//drawClippedLineZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v2_i), vertexAt(v0_i), rgbaSaturate(color * 255, real(255)));
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleListZBufferRW::drawTriangleList16(const Vec4<real> & color)
	//{
	//	_ASSERT(false);

	//	UNREFERENCED_PARAMETER(color);
	//}

	//void RenderTriangleListZBufferRW::drawTriangleList32(const Vec4<real> & color)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	//const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = i * 3 + 0;
	//		const size_t v1_i = i * 3 + 1;
	//		const size_t v2_i = i * 3 + 2;

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleZBufferRW32(
	//				getSurfaceRef32(), getZBufferRef28(), vertexAt(v0_i), vertexAt(v1_i), vertexAt(v2_i), rgbaSaturate(color * 255, real(255)));
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleZBufferRW32(
	//				getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v0_i), vertexAt(v1_i), vertexAt(v2_i), rgbaSaturate(color * 255, real(255)));
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListZBufferRW::drawTriangleIndexList16(const Vec4<real> & color)
	//{
	//	_ASSERT(false);

	//	UNREFERENCED_PARAMETER(color);
	//}

	//void RenderTriangleIndexListZBufferRW::drawTriangleIndexList32(const Vec4<real> & color)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	//const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = vertexIndexAt(i * 3 + 0);
	//		const size_t v1_i = vertexIndexAt(i * 3 + 1);
	//		const size_t v2_i = vertexIndexAt(i * 3 + 2);

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleZBufferRW32(
	//				getSurfaceRef32(), getZBufferRef28(), vertexAt(v0_i), vertexAt(v1_i), vertexAt(v2_i), rgbaSaturate(color * 255, real(255)));
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleZBufferRW32(
	//				getSurfaceRef32(), getClipperRect(), getZBufferRef28(), vertexAt(v0_i), vertexAt(v1_i), vertexAt(v2_i), rgbaSaturate(color * 255, real(255)));
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudZBufferRW::zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexListSize());
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		v0_i = index * 3 + 0;
	//		v1_i = index * 3 + 1;
	//		v2_i = index * 3 + 2;
	//		break;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		v0_i = index * 3 + 2;
	//		v1_i = index * 3 + 0;
	//		v2_i = index * 3 + 1;
	//		break;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		v0_i = index * 3 + 1;
	//		v1_i = index * 3 + 2;
	//		v2_i = index * 3 + 0;
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 3);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 3);
	//	Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & new_v2 = vertexAt(getVertexListSize() - 1);

	//	//resizeUVList(getUVListSize() + 3);
	//	//const Vec2<real> & t0 = uvAt(v0_i);
	//	//const Vec2<real> & t1 = uvAt(v1_i);
	//	//const Vec2<real> & t2 = uvAt(v2_i);

	//	//Vec2<real> & new_t0 = uvAt(getUVListSize() - 3);
	//	//Vec2<real> & new_t1 = uvAt(getUVListSize() - 2);
	//	//Vec2<real> & new_t2 = uvAt(getUVListSize() - 1);

	//	resizeColorList(getColorListSize() + 3);
	//	const Vec4<real> & c0 = colorAt(v0_i);
	//	const Vec4<real> & c1 = colorAt(v1_i);
	//	const Vec4<real> & c2 = colorAt(v2_i);

	//	Vec4<real> & new_c0 = colorAt(getColorListSize() - 3);
	//	Vec4<real> & new_c1 = colorAt(getColorListSize() - 2);
	//	Vec4<real> & new_c2 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*		2
	//	* -------------
	//	*	1       0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	new_v0.z = getCameraNearZ();

	//	//new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	//new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	new_v1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.x, v2.x);
	//	new_v1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.y, v2.y);
	//	new_v1.z = getCameraNearZ();

	//	//new_t1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.x, t2.x);
	//	//new_t1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.y, t2.y);

	//	new_c1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.x, c2.x);
	//	new_c1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.y, c2.y);
	//	new_c1.z = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.z, c2.z);

	//	new_v2 = v2;
	//	//new_t2 = t2;
	//	new_c2 = c2;

	//	pushTriState(TS_ACTIVE);
	//}

	//void RenderTriangleListGouraudZBufferRW::zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexListSize());
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0:
	//		v0_i = index * 3 + 0;
	//		v1_i = index * 3 + 1;
	//		v2_i = index * 3 + 2;
	//		break;

	//	case CLIP_MASK_V1:
	//		v0_i = index * 3 + 1;
	//		v1_i = index * 3 + 2;
	//		v2_i = index * 3 + 0;
	//		break;

	//	case CLIP_MASK_V2:
	//		v0_i = index * 3 + 2;
	//		v1_i = index * 3 + 0;
	//		v2_i = index * 3 + 1;
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 6);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 6);
	//	Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 5);
	//	Vec4<real> & new_v2 = vertexAt(getVertexListSize() - 4);

	//	Vec4<real> & dbl_v0 = vertexAt(getVertexListSize() - 3);
	//	Vec4<real> & dbl_v1 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & dbl_v2 = vertexAt(getVertexListSize() - 1);

	//	//resizeUVList(getUVListSize() + 6);
	//	//const Vec2<real> & t0 = uvAt(v0_i);
	//	//const Vec2<real> & t1 = uvAt(v1_i);
	//	//const Vec2<real> & t2 = uvAt(v2_i);

	//	//Vec2<real> & new_t0 = uvAt(getUVListSize() - 6);
	//	//Vec2<real> & new_t1 = uvAt(getUVListSize() - 5);
	//	//Vec2<real> & new_t2 = uvAt(getUVListSize() - 4);

	//	//Vec2<real> & dbl_t0 = uvAt(getUVListSize() - 3);
	//	//Vec2<real> & dbl_t1 = uvAt(getUVListSize() - 2);
	//	//Vec2<real> & dbl_t2 = uvAt(getUVListSize() - 1);

	//	resizeColorList(getColorListSize() + 6);
	//	const Vec4<real> & c0 = colorAt(v0_i);
	//	const Vec4<real> & c1 = colorAt(v1_i);
	//	const Vec4<real> & c2 = colorAt(v2_i);

	//	Vec4<real> & new_c0 = colorAt(getColorListSize() - 6);
	//	Vec4<real> & new_c1 = colorAt(getColorListSize() - 5);
	//	Vec4<real> & new_c2 = colorAt(getColorListSize() - 4);

	//	Vec4<real> & dbl_c0 = colorAt(getColorListSize() - 3);
	//	Vec4<real> & dbl_c1 = colorAt(getColorListSize() - 2);
	//	Vec4<real> & dbl_c2 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*	1       2
	//	* -------------
	//	*		0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.x, v1.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.y, v1.y);
	//	new_v0.z = getCameraNearZ();

	//	//new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.x, t1.x);
	//	//new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.y, t1.y);

	//	new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.x, c1.x);
	//	new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.y, c1.y);
	//	new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.z, c1.z);

	//	new_v1 = v1;
	//	//new_t1 = t1;
	//	new_c1 = c1;

	//	new_v2 = v2;
	//	//new_t2 = t2;
	//	new_c2 = c2;

	//	pushTriState(TS_ACTIVE);

	//	dbl_v0 = new_v0;
	//	//dbl_t0 = new_t0;
	//	dbl_c0 = new_c0;

	//	dbl_v1 = v2;
	//	//dbl_t1 = t2;
	//	dbl_c1 = c2;

	//	dbl_v2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	dbl_v2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	dbl_v2.z = getCameraNearZ();

	//	//dbl_t2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	//dbl_t2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	dbl_c2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	dbl_c2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	dbl_c2.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	pushTriState(TS_ACTIVE);
	//}

	//TRI_STATE RenderTriangleListGouraudZBufferRW::zClipTriangleAtCamera(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());
	//	_ASSERT(getCameraNearZ() >= 1 && getCameraNearZ() < getCameraFarZ());

	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(ti + 0);
	//	const Vec4<real> & v1 = vertexAt(ti + 1);
	//	const Vec4<real> & v2 = vertexAt(ti + 2);

	//	DWORD clip_mask_nz = 0;
	//	DWORD clip_mask_fz = 0;

	//	if(v0.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V0;
	//	else if(v0.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V0;

	//	if(v1.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V1;
	//	else if(v1.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V1;

	//	if(v2.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V2;
	//	else if(v2.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V2;

	//	switch(clip_mask_fz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;
	//	}

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;
	//	}

	//	return TS_ACTIVE;
	//}

	//TRI_STATE RenderTriangleListGouraudZBufferRW::sClipTriangleAtScreen(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());

	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(ti + 0);
	//	const Vec4<real> & v1 = vertexAt(ti + 1);
	//	const Vec4<real> & v2 = vertexAt(ti + 2);

	//	if(min(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CULLED;

	//	if(min(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CULLED;

	//	if(max(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CULLED;

	//	if(max(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CULLED;

	//	if(min(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CLIPPED;

	//	if(min(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CLIPPED;

	//	if(max(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CLIPPED;

	//	if(max(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CLIPPED;

	//	return TS_ACTIVE;
	//}

	//void RenderTriangleListGouraudZBufferRW::reset(void)
	//{
	//	_ASSERT(getVertexListSize() == getNormalListSize());
	//	//_ASSERT(getVertexListSize() == getUVListSize());

	//	clearTriStateList();
	//	resizeTriStateList(getVertexListSize() / 3, TS_ACTIVE);

	//	resizeVertexList(getTriStateListSize() * 3);
	//	resizeNormalList(getTriStateListSize() * 3);
	//	//resizeUVList(getTriStateListSize() * 3);
	//}

	//void RenderTriangleListGouraudZBufferRW::removeBackfaceAtWorld(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		_ASSERT(TS_ACTIVE == triStateAt(i));

	//		const size_t vi = i * 3;
	//		const Vec4<real> & v0 = vertexAt(vi + 0);
	//		const Vec4<real> & v1 = vertexAt(vi + 1);
	//		const Vec4<real> & v2 = vertexAt(vi + 2);

	//		if(vec3Dot(
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(getCameraPosition(), v0)) <= 0)
	//		{
	//			triStateAt(i) = TS_BACKFACE;
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudZBufferRW::lightAtWorld(void)
	//{
	//	_ASSERT(getVertexListSize() == getNormalListSize());

	//	clearColorList();
	//	resizeColorList(getTriStateListSize() * 3, Vec4<real>(0, 0, 0, 0));

	//	LightList::const_iterator l_iter = getLightListBegin();
	//	for(; l_iter != getLightListEnd(); l_iter++)
	//	{
	//		switch(l_iter->type)
	//		{
	//		case LT_AMBIENT:
	//			for(size_t i = 0; i < getTriStateListSize(); i++)
	//			{
	//				if(isTriVisible(triStateAt(i)))
	//				{
	//					const size_t vi = i * 3;
	//					colorAt(vi + 0) += lightVertexAmbient(*l_iter, getMaterial(), vertexAt(vi + 0), normalAt(vi + 0));
	//					colorAt(vi + 1) += lightVertexAmbient(*l_iter, getMaterial(), vertexAt(vi + 1), normalAt(vi + 1));
	//					colorAt(vi + 2) += lightVertexAmbient(*l_iter, getMaterial(), vertexAt(vi + 2), normalAt(vi + 2));
	//				}
	//			}
	//			break;

	//		case LT_DIRECTIONAL:
	//			for(size_t i = 0; i < getTriStateListSize(); i++)
	//			{
	//				if(isTriVisible(triStateAt(i)))
	//				{
	//					const size_t vi = i * 3;
	//					colorAt(vi + 0) += lightVertexDirectional(*l_iter, getMaterial(), vertexAt(vi + 0), normalAt(vi + 0));
	//					colorAt(vi + 1) += lightVertexDirectional(*l_iter, getMaterial(), vertexAt(vi + 1), normalAt(vi + 1));
	//					colorAt(vi + 2) += lightVertexDirectional(*l_iter, getMaterial(), vertexAt(vi + 2), normalAt(vi + 2));
	//				}
	//			}
	//			break;

	//		case LT_POINT:
	//			for(size_t i = 0; i < getTriStateListSize(); i++)
	//			{
	//				if(isTriVisible(triStateAt(i)))
	//				{
	//					const size_t vi = i * 3;
	//					colorAt(vi + 0) += lightVertexPoint(*l_iter, getMaterial(), vertexAt(vi + 0), normalAt(vi + 0));
	//					colorAt(vi + 1) += lightVertexPoint(*l_iter, getMaterial(), vertexAt(vi + 1), normalAt(vi + 1));
	//					colorAt(vi + 2) += lightVertexPoint(*l_iter, getMaterial(), vertexAt(vi + 2), normalAt(vi + 2));
	//				}
	//			}
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudZBufferRW::worldToCamera(void)
	//{
	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			const size_t vi = i * 3;
	//			vertexAt(vi + 0) *= getCameraMatrix();
	//			vertexAt(vi + 1) *= getCameraMatrix();
	//			vertexAt(vi + 2) *= getCameraMatrix();
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudZBufferRW::zClipAtCamera(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	const size_t orig_size = getTriStateListSize();

	//	for(size_t i = 0; i < orig_size; i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			TRI_STATE state = zClipTriangleAtCamera(i); triStateAt(i) = state; // ***
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudZBufferRW::cameraToScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	const real halfWidth = (real)(getViewport().right - getViewport().left) / 2;
	//	const real halfHeight = (real)(getViewport().bottom - getViewport().top) / 2;

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			const size_t vi = i * 3;
	//			Vec4<real> & v0 = vertexAt(vi + 0);
	//			Vec4<real> & v1 = vertexAt(vi + 1);
	//			Vec4<real> & v2 = vertexAt(vi + 2);

	//			//       x * ( width / 2 ) * ctan( fov / 2 )
	//			// x' = -------------------------------------
	//			//                       z

	//			v0.x = getViewport().left + v0.x * getCameraProjection().x / v0.z * halfWidth + halfWidth;
	//			v1.x = getViewport().left + v1.x * getCameraProjection().x / v1.z * halfWidth + halfWidth;
	//			v2.x = getViewport().left + v2.x * getCameraProjection().x / v2.z * halfWidth + halfWidth;

	//			//       y * ( height / 2 ) * ctan( fov / 2 )
	//			// y' = -------------------------------------
	//			//                       z

	//			v0.y = getViewport().top + halfHeight - v0.y * getCameraProjection().y / v0.z * halfHeight;
	//			v1.y = getViewport().top + halfHeight - v1.y * getCameraProjection().y / v1.z * halfHeight;
	//			v2.y = getViewport().top + halfHeight - v2.y * getCameraProjection().y / v2.z * halfHeight;
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudZBufferRW::sClipAtScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			triStateAt(i) = sClipTriangleAtScreen(i);
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudZBufferRW::drawTriangleList16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleListGouraudZBufferRW::drawTriangleList32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	//const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t vi = i * 3;

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleGouraudZBufferRW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				//getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				rgbaSaturate(colorAt(vi + 2) * 255, real(255)));
	//				//uvAt(vi + 0) * texture_expend,
	//				//uvAt(vi + 1) * texture_expend,
	//				//uvAt(vi + 2) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleGouraudZBufferRW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				//getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				rgbaSaturate(colorAt(vi + 2) * 255, real(255)));
	//				//uvAt(vi + 0) * texture_expend,
	//				//uvAt(vi + 1) * texture_expend,
	//				//uvAt(vi + 2) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListGouraudZBufferRW::zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexIndexListSize());
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		v0_i = vertexIndexAt(index * 3 + 0);
	//		v1_i = vertexIndexAt(index * 3 + 1);
	//		v2_i = vertexIndexAt(index * 3 + 2);
	//		break;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		v0_i = vertexIndexAt(index * 3 + 2);
	//		v1_i = vertexIndexAt(index * 3 + 0);
	//		v2_i = vertexIndexAt(index * 3 + 1);
	//		break;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		v0_i = vertexIndexAt(index * 3 + 1);
	//		v1_i = vertexIndexAt(index * 3 + 2);
	//		v2_i = vertexIndexAt(index * 3 + 0);
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 2);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 1);

	//	//resizeUVList(getUVListSize() + 2);
	//	//const Vec2<real> & t0 = uvAt(v0_i);
	//	//const Vec2<real> & t1 = uvAt(v1_i);
	//	//const Vec2<real> & t2 = uvAt(v2_i);

	//	//Vec2<real> & new_t0 = uvAt(getUVListSize() - 2);
	//	//Vec2<real> & new_t1 = uvAt(getUVListSize() - 1);

	//	resizeColorList(getColorListSize() + 2);
	//	const Vec4<real> & c0 = colorAt(v0_i);
	//	const Vec4<real> & c1 = colorAt(v1_i);
	//	const Vec4<real> & c2 = colorAt(v2_i);

	//	Vec4<real> & new_c0 = colorAt(getColorListSize() - 2);
	//	Vec4<real> & new_c1 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*		2
	//	* -------------
	//	*	1       0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	new_v0.z = getCameraNearZ();

	//	//new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	//new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	new_v1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.x, v2.x);
	//	new_v1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.y, v2.y);
	//	new_v1.z = getCameraNearZ();

	//	//new_t1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.x, t2.x);
	//	//new_t1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.y, t2.y);

	//	new_c1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.x, c2.x);
	//	new_c1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.y, c2.y);
	//	new_c1.z = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.z, c2.z);

	//	pushVertexIndex(getVertexListSize() - 2);
	//	pushVertexIndex(getVertexListSize() - 1);
	//	pushVertexIndex(v2_i);

	//	pushTriState(TS_ACTIVE);
	//}

	//void RenderTriangleIndexListGouraudZBufferRW::zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexIndexListSize());
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0:
	//		v0_i = vertexIndexAt(index * 3 + 0);
	//		v1_i = vertexIndexAt(index * 3 + 1);
	//		v2_i = vertexIndexAt(index * 3 + 2);
	//		break;

	//	case CLIP_MASK_V1:
	//		v0_i = vertexIndexAt(index * 3 + 1);
	//		v1_i = vertexIndexAt(index * 3 + 2);
	//		v2_i = vertexIndexAt(index * 3 + 0);
	//		break;

	//	case CLIP_MASK_V2:
	//		v0_i = vertexIndexAt(index * 3 + 2);
	//		v1_i = vertexIndexAt(index * 3 + 0);
	//		v2_i = vertexIndexAt(index * 3 + 1);
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 2);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & dbl_v2 = vertexAt(getVertexListSize() - 1);

	//	//resizeUVList(getUVListSize() + 2);
	//	//const Vec2<real> & t0 = uvAt(v0_i);
	//	//const Vec2<real> & t1 = uvAt(v1_i);
	//	//const Vec2<real> & t2 = uvAt(v2_i);

	//	//Vec2<real> & new_t0 = uvAt(getUVListSize() - 2);
	//	//Vec2<real> & dbl_t2 = uvAt(getUVListSize() - 1);

	//	resizeColorList(getColorListSize() + 2);
	//	const Vec4<real> & c0 = colorAt(v0_i);
	//	const Vec4<real> & c1 = colorAt(v1_i);
	//	const Vec4<real> & c2 = colorAt(v2_i);

	//	Vec4<real> & new_c0 = colorAt(getColorListSize() - 2);
	//	Vec4<real> & dbl_c2 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*	1       2
	//	* -------------
	//	*		0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.x, v1.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.y, v1.y);
	//	new_v0.z = getCameraNearZ();

	//	//new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.x, t1.x);
	//	//new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.y, t1.y);

	//	new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.x, c1.x);
	//	new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.y, c1.y);
	//	new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.z, c1.z);

	//	pushVertexIndex(getVertexListSize() - 2);
	//	pushVertexIndex(v1_i);
	//	pushVertexIndex(v2_i);

	//	pushTriState(TS_ACTIVE);

	//	dbl_v2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	dbl_v2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	dbl_v2.z = getCameraNearZ();

	//	//dbl_t2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	//dbl_t2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	dbl_c2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	dbl_c2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	dbl_c2.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	pushVertexIndex(getVertexListSize() - 2);
	//	pushVertexIndex(v2_i);
	//	pushVertexIndex(getVertexListSize() - 1);

	//	pushTriState(TS_ACTIVE);
	//}

	//TRI_STATE RenderTriangleIndexListGouraudZBufferRW::zClipTriangleAtCamera(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());
	//	_ASSERT(getCameraNearZ() >= 1 && getCameraNearZ() < getCameraFarZ());

	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(vertexIndexAt(ti + 0));
	//	const Vec4<real> & v1 = vertexAt(vertexIndexAt(ti + 1));
	//	const Vec4<real> & v2 = vertexAt(vertexIndexAt(ti + 2));

	//	DWORD clip_mask_nz = 0;
	//	DWORD clip_mask_fz = 0;

	//	if(v0.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V0;
	//	else if(v0.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V0;

	//	if(v1.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V1;
	//	else if(v1.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V1;

	//	if(v2.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V2;
	//	else if(v2.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V2;

	//	switch(clip_mask_fz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;
	//	}

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;
	//	}

	//	return TS_ACTIVE;
	//}

	//TRI_STATE RenderTriangleIndexListGouraudZBufferRW::sClipTriangleAtScreen(const size_t index)
	//{
	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(vertexIndexAt(ti + 0));
	//	const Vec4<real> & v1 = vertexAt(vertexIndexAt(ti + 1));
	//	const Vec4<real> & v2 = vertexAt(vertexIndexAt(ti + 2));

	//	if(min(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CULLED;

	//	if(min(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CULLED;

	//	if(max(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CULLED;

	//	if(max(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CULLED;

	//	if(min(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CLIPPED;

	//	if(min(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CLIPPED;

	//	if(max(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CLIPPED;

	//	if(max(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CLIPPED;

	//	return TS_ACTIVE;
	//}

	//void RenderTriangleIndexListGouraudZBufferRW::reset(void)
	//{
	//	_ASSERT(getVertexListSize() == getNormalListSize());
	//	//_ASSERT(getVertexListSize() == getUVListSize());

	//	clearTriStateList();
	//	resizeTriStateList(getVertexIndexListSize() / 3, TS_ACTIVE);

	//	resizeVertexIndexList(getTriStateListSize() * 3);
	//}

	//void RenderTriangleIndexListGouraudZBufferRW::removeBackfaceAtWorld(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		_ASSERT(TS_ACTIVE == triStateAt(i));

	//		const size_t vi = i * 3;
	//		const Vec4<real> & v0 = vertexAt(vertexIndexAt(vi + 0));
	//		const Vec4<real> & v1 = vertexAt(vertexIndexAt(vi + 1));
	//		const Vec4<real> & v2 = vertexAt(vertexIndexAt(vi + 2));

	//		if(vec3Dot(
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(getCameraPosition(), v0)) <= 0)
	//		{
	//			triStateAt(i) = TS_BACKFACE;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListGouraudZBufferRW::lightAtWorld(void)
	//{
	//	_ASSERT(getVertexListSize() == getNormalListSize());

	//	clearColorList();
	//	resizeColorList(getVertexListSize(), Vec4<real>(0, 0, 0, 0));

	//	LightList::const_iterator l_iter = getLightListBegin();
	//	for(; l_iter != getLightListEnd(); l_iter++)
	//	{
	//		switch(l_iter->type)
	//		{
	//		case LT_AMBIENT:
	//			for(size_t i = 0; i < getVertexListSize(); i++)
	//			{
	//				colorAt(i) += lightVertexAmbient(*l_iter, getMaterial(), vertexAt(i), normalAt(i));
	//			}
	//			break;

	//		case LT_DIRECTIONAL:
	//			for(size_t i = 0; i < getVertexListSize(); i++)
	//			{
	//				colorAt(i) += lightVertexDirectional(*l_iter, getMaterial(), vertexAt(i), normalAt(i));
	//			}
	//			break;

	//		case LT_POINT:
	//			for(size_t i = 0; i < getVertexListSize(); i++)
	//			{
	//				colorAt(i) += lightVertexPoint(*l_iter, getMaterial(), vertexAt(i), normalAt(i));
	//			}
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListGouraudZBufferRW::worldToCamera(void)
	//{
	//	VertexList::iterator v_iter = getVertexListBegin();
	//	for(; v_iter != getVertexListEnd(); v_iter++)
	//	{
	//		*v_iter *= getCameraMatrix();
	//	}
	//}

	//void RenderTriangleIndexListGouraudZBufferRW::zClipAtCamera(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);

	//	const size_t orig_size = getTriStateListSize();

	//	for(size_t i = 0; i < orig_size; i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			TRI_STATE state = zClipTriangleAtCamera(i); triStateAt(i) = state; // ***
	//		}
	//	}
	//}

	//void RenderTriangleIndexListGouraudZBufferRW::cameraToScreen(void)
	//{
	//	const real halfWidth = (real)(getViewport().right - getViewport().left) / 2;
	//	const real halfHeight = (real)(getViewport().bottom - getViewport().top) / 2;

	//	VertexList::iterator v_iter = getVertexListBegin();
	//	for(; v_iter != getVertexListEnd(); v_iter++)
	//	{
	//		//       x * ( width / 2 ) * ctan( fov / 2 )
	//		// x' = -------------------------------------
	//		//                       z

	//		v_iter->x = getViewport().left + v_iter->x * getCameraProjection().x / v_iter->z * halfWidth + halfWidth;

	//		//       y * ( height / 2 ) * ctan( fov / 2 )
	//		// y' = -------------------------------------
	//		//                       z

	//		v_iter->y = getViewport().top + halfHeight - v_iter->y * getCameraProjection().y / v_iter->z * halfHeight;
	//	}
	//}

	//void RenderTriangleIndexListGouraudZBufferRW::sClipAtScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			triStateAt(i) = sClipTriangleAtScreen(i);
	//		}
	//	}
	//}

	//void RenderTriangleIndexListGouraudZBufferRW::drawTriangleIndexList16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleIndexListGouraudZBufferRW::drawTriangleIndexList32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);
	//	//_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	//const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = vertexIndexAt(i * 3 + 0);
	//		const size_t v1_i = vertexIndexAt(i * 3 + 1);
	//		const size_t v2_i = vertexIndexAt(i * 3 + 2);

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleGouraudZBufferRW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				//getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				rgbaSaturate(colorAt(v2_i) * 255, real(255)));
	//				//uvAt(v0_i) * texture_expend,
	//				//uvAt(v1_i) * texture_expend,
	//				//uvAt(v2_i) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleGouraudZBufferRW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				//getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				rgbaSaturate(colorAt(v2_i) * 255, real(255)));
	//				//uvAt(v0_i) * texture_expend,
	//				//uvAt(v1_i) * texture_expend,
	//				//uvAt(v2_i) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleListTextureZBufferRW::zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexListSize());
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		v0_i = index * 3 + 0;
	//		v1_i = index * 3 + 1;
	//		v2_i = index * 3 + 2;
	//		break;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		v0_i = index * 3 + 2;
	//		v1_i = index * 3 + 0;
	//		v2_i = index * 3 + 1;
	//		break;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		v0_i = index * 3 + 1;
	//		v1_i = index * 3 + 2;
	//		v2_i = index * 3 + 0;
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 3);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 3);
	//	Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & new_v2 = vertexAt(getVertexListSize() - 1);

	//	resizeUVList(getUVListSize() + 3);
	//	const Vec2<real> & t0 = uvAt(v0_i);
	//	const Vec2<real> & t1 = uvAt(v1_i);
	//	const Vec2<real> & t2 = uvAt(v2_i);

	//	Vec2<real> & new_t0 = uvAt(getUVListSize() - 3);
	//	Vec2<real> & new_t1 = uvAt(getUVListSize() - 2);
	//	Vec2<real> & new_t2 = uvAt(getUVListSize() - 1);

	//	//resizeColorList(getColorListSize() + 3);
	//	//const Vec4<real> & c0 = colorAt(v0_i);
	//	//const Vec4<real> & c1 = colorAt(v1_i);
	//	//const Vec4<real> & c2 = colorAt(v2_i);

	//	//Vec4<real> & new_c0 = colorAt(getColorListSize() - 3);
	//	//Vec4<real> & new_c1 = colorAt(getColorListSize() - 2);
	//	//Vec4<real> & new_c2 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*		2
	//	* -------------
	//	*	1       0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	new_v0.z = getCameraNearZ();

	//	new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	//new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	//new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	//new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	new_v1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.x, v2.x);
	//	new_v1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.y, v2.y);
	//	new_v1.z = getCameraNearZ();

	//	new_t1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.x, t2.x);
	//	new_t1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.y, t2.y);

	//	//new_c1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.x, c2.x);
	//	//new_c1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.y, c2.y);
	//	//new_c1.z = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.z, c2.z);

	//	new_v2 = v2;
	//	new_t2 = t2;
	//	//new_c2 = c2;

	//	pushTriState(TS_ACTIVE);
	//}

	//void RenderTriangleListTextureZBufferRW::zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexListSize());
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0:
	//		v0_i = index * 3 + 0;
	//		v1_i = index * 3 + 1;
	//		v2_i = index * 3 + 2;
	//		break;

	//	case CLIP_MASK_V1:
	//		v0_i = index * 3 + 1;
	//		v1_i = index * 3 + 2;
	//		v2_i = index * 3 + 0;
	//		break;

	//	case CLIP_MASK_V2:
	//		v0_i = index * 3 + 2;
	//		v1_i = index * 3 + 0;
	//		v2_i = index * 3 + 1;
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 6);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 6);
	//	Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 5);
	//	Vec4<real> & new_v2 = vertexAt(getVertexListSize() - 4);

	//	Vec4<real> & dbl_v0 = vertexAt(getVertexListSize() - 3);
	//	Vec4<real> & dbl_v1 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & dbl_v2 = vertexAt(getVertexListSize() - 1);

	//	resizeUVList(getUVListSize() + 6);
	//	const Vec2<real> & t0 = uvAt(v0_i);
	//	const Vec2<real> & t1 = uvAt(v1_i);
	//	const Vec2<real> & t2 = uvAt(v2_i);

	//	Vec2<real> & new_t0 = uvAt(getUVListSize() - 6);
	//	Vec2<real> & new_t1 = uvAt(getUVListSize() - 5);
	//	Vec2<real> & new_t2 = uvAt(getUVListSize() - 4);

	//	Vec2<real> & dbl_t0 = uvAt(getUVListSize() - 3);
	//	Vec2<real> & dbl_t1 = uvAt(getUVListSize() - 2);
	//	Vec2<real> & dbl_t2 = uvAt(getUVListSize() - 1);

	//	//resizeColorList(getColorListSize() + 6);
	//	//const Vec4<real> & c0 = colorAt(v0_i);
	//	//const Vec4<real> & c1 = colorAt(v1_i);
	//	//const Vec4<real> & c2 = colorAt(v2_i);

	//	//Vec4<real> & new_c0 = colorAt(getColorListSize() - 6);
	//	//Vec4<real> & new_c1 = colorAt(getColorListSize() - 5);
	//	//Vec4<real> & new_c2 = colorAt(getColorListSize() - 4);

	//	//Vec4<real> & dbl_c0 = colorAt(getColorListSize() - 3);
	//	//Vec4<real> & dbl_c1 = colorAt(getColorListSize() - 2);
	//	//Vec4<real> & dbl_c2 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*	1       2
	//	* -------------
	//	*		0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.x, v1.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.y, v1.y);
	//	new_v0.z = getCameraNearZ();

	//	new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.x, t1.x);
	//	new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.y, t1.y);

	//	//new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.x, c1.x);
	//	//new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.y, c1.y);
	//	//new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.z, c1.z);

	//	new_v1 = v1;
	//	new_t1 = t1;
	//	//new_c1 = c1;

	//	new_v2 = v2;
	//	new_t2 = t2;
	//	//new_c2 = c2;

	//	pushTriState(TS_ACTIVE);

	//	dbl_v0 = new_v0;
	//	dbl_t0 = new_t0;
	//	//dbl_c0 = new_c0;

	//	dbl_v1 = v2;
	//	dbl_t1 = t2;
	//	//dbl_c1 = c2;

	//	dbl_v2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	dbl_v2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	dbl_v2.z = getCameraNearZ();

	//	dbl_t2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	dbl_t2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	//dbl_c2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	//dbl_c2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	//dbl_c2.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	pushTriState(TS_ACTIVE);
	//}

	//TRI_STATE RenderTriangleListTextureZBufferRW::zClipTriangleAtCamera(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());
	//	_ASSERT(getCameraNearZ() >= 1 && getCameraNearZ() < getCameraFarZ());

	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(ti + 0);
	//	const Vec4<real> & v1 = vertexAt(ti + 1);
	//	const Vec4<real> & v2 = vertexAt(ti + 2);

	//	DWORD clip_mask_nz = 0;
	//	DWORD clip_mask_fz = 0;

	//	if(v0.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V0;
	//	else if(v0.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V0;

	//	if(v1.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V1;
	//	else if(v1.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V1;

	//	if(v2.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V2;
	//	else if(v2.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V2;

	//	switch(clip_mask_fz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;
	//	}

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;
	//	}

	//	return TS_ACTIVE;
	//}

	//TRI_STATE RenderTriangleListTextureZBufferRW::sClipTriangleAtScreen(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());

	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(ti + 0);
	//	const Vec4<real> & v1 = vertexAt(ti + 1);
	//	const Vec4<real> & v2 = vertexAt(ti + 2);

	//	if(min(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CULLED;

	//	if(min(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CULLED;

	//	if(max(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CULLED;

	//	if(max(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CULLED;

	//	if(min(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CLIPPED;

	//	if(min(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CLIPPED;

	//	if(max(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CLIPPED;

	//	if(max(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CLIPPED;

	//	return TS_ACTIVE;
	//}

	//void RenderTriangleListTextureZBufferRW::reset(void)
	//{
	//	//_ASSERT(getVertexListSize() == getNormalListSize());
	//	_ASSERT(getVertexListSize() == getUVListSize());

	//	clearTriStateList();
	//	resizeTriStateList(getVertexListSize() / 3, TS_ACTIVE);

	//	resizeVertexList(getTriStateListSize() * 3);
	//	//resizeNormalList(getTriStateListSize() * 3);
	//	resizeUVList(getTriStateListSize() * 3);
	//}

	//void RenderTriangleListTextureZBufferRW::removeBackfaceAtWorld(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		_ASSERT(TS_ACTIVE == triStateAt(i));

	//		const size_t vi = i * 3;
	//		const Vec4<real> & v0 = vertexAt(vi + 0);
	//		const Vec4<real> & v1 = vertexAt(vi + 1);
	//		const Vec4<real> & v2 = vertexAt(vi + 2);

	//		if(vec3Dot(
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(getCameraPosition(), v0)) <= 0)
	//		{
	//			triStateAt(i) = TS_BACKFACE;
	//		}
	//	}
	//}

	//void RenderTriangleListTextureZBufferRW::worldToCamera(void)
	//{
	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			const size_t vi = i * 3;
	//			vertexAt(vi + 0) *= getCameraMatrix();
	//			vertexAt(vi + 1) *= getCameraMatrix();
	//			vertexAt(vi + 2) *= getCameraMatrix();
	//		}
	//	}
	//}

	//void RenderTriangleListTextureZBufferRW::zClipAtCamera(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	const size_t orig_size = getTriStateListSize();

	//	for(size_t i = 0; i < orig_size; i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			TRI_STATE state = zClipTriangleAtCamera(i); triStateAt(i) = state; // ***
	//		}
	//	}
	//}

	//void RenderTriangleListTextureZBufferRW::cameraToScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	const real halfWidth = (real)(getViewport().right - getViewport().left) / 2;
	//	const real halfHeight = (real)(getViewport().bottom - getViewport().top) / 2;

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			const size_t vi = i * 3;
	//			Vec4<real> & v0 = vertexAt(vi + 0);
	//			Vec4<real> & v1 = vertexAt(vi + 1);
	//			Vec4<real> & v2 = vertexAt(vi + 2);

	//			//       x * ( width / 2 ) * ctan( fov / 2 )
	//			// x' = -------------------------------------
	//			//                       z

	//			v0.x = getViewport().left + v0.x * getCameraProjection().x / v0.z * halfWidth + halfWidth;
	//			v1.x = getViewport().left + v1.x * getCameraProjection().x / v1.z * halfWidth + halfWidth;
	//			v2.x = getViewport().left + v2.x * getCameraProjection().x / v2.z * halfWidth + halfWidth;

	//			//       y * ( height / 2 ) * ctan( fov / 2 )
	//			// y' = -------------------------------------
	//			//                       z

	//			v0.y = getViewport().top + halfHeight - v0.y * getCameraProjection().y / v0.z * halfHeight;
	//			v1.y = getViewport().top + halfHeight - v1.y * getCameraProjection().y / v1.z * halfHeight;
	//			v2.y = getViewport().top + halfHeight - v2.y * getCameraProjection().y / v2.z * halfHeight;
	//		}
	//	}
	//}

	//void RenderTriangleListTextureZBufferRW::sClipAtScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			triStateAt(i) = sClipTriangleAtScreen(i);
	//		}
	//	}
	//}

	//void RenderTriangleListTextureZBufferRW::drawTriangleListZBufferW16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleListTextureZBufferRW::drawTriangleListZBufferW32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t vi = i * 3;

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleTextureZBufferW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				//rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 2) * 255, real(255)),
	//				uvAt(vi + 0) * texture_expend,
	//				uvAt(vi + 1) * texture_expend,
	//				uvAt(vi + 2) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleTextureZBufferW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				//rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 2) * 255, real(255)),
	//				uvAt(vi + 0) * texture_expend,
	//				uvAt(vi + 1) * texture_expend,
	//				uvAt(vi + 2) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleListTextureZBufferRW::drawTriangleList16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleListTextureZBufferRW::drawTriangleList32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t vi = i * 3;

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleTextureZBufferRW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				//rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 2) * 255, real(255)),
	//				uvAt(vi + 0) * texture_expend,
	//				uvAt(vi + 1) * texture_expend,
	//				uvAt(vi + 2) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleTextureZBufferRW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				//rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 2) * 255, real(255)),
	//				uvAt(vi + 0) * texture_expend,
	//				uvAt(vi + 1) * texture_expend,
	//				uvAt(vi + 2) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListTextureZBufferRW::zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexIndexListSize());
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		v0_i = vertexIndexAt(index * 3 + 0);
	//		v1_i = vertexIndexAt(index * 3 + 1);
	//		v2_i = vertexIndexAt(index * 3 + 2);
	//		break;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		v0_i = vertexIndexAt(index * 3 + 2);
	//		v1_i = vertexIndexAt(index * 3 + 0);
	//		v2_i = vertexIndexAt(index * 3 + 1);
	//		break;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		v0_i = vertexIndexAt(index * 3 + 1);
	//		v1_i = vertexIndexAt(index * 3 + 2);
	//		v2_i = vertexIndexAt(index * 3 + 0);
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 2);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 1);

	//	resizeUVList(getUVListSize() + 2);
	//	const Vec2<real> & t0 = uvAt(v0_i);
	//	const Vec2<real> & t1 = uvAt(v1_i);
	//	const Vec2<real> & t2 = uvAt(v2_i);

	//	Vec2<real> & new_t0 = uvAt(getUVListSize() - 2);
	//	Vec2<real> & new_t1 = uvAt(getUVListSize() - 1);

	//	//resizeColorList(getColorListSize() + 2);
	//	//const Vec4<real> & c0 = colorAt(v0_i);
	//	//const Vec4<real> & c1 = colorAt(v1_i);
	//	//const Vec4<real> & c2 = colorAt(v2_i);

	//	//Vec4<real> & new_c0 = colorAt(getColorListSize() - 2);
	//	//Vec4<real> & new_c1 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*		2
	//	* -------------
	//	*	1       0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	new_v0.z = getCameraNearZ();

	//	new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	//new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	//new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	//new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	new_v1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.x, v2.x);
	//	new_v1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.y, v2.y);
	//	new_v1.z = getCameraNearZ();

	//	new_t1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.x, t2.x);
	//	new_t1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.y, t2.y);

	//	//new_c1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.x, c2.x);
	//	//new_c1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.y, c2.y);
	//	//new_c1.z = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.z, c2.z);

	//	pushVertexIndex(getVertexListSize() - 2);
	//	pushVertexIndex(getVertexListSize() - 1);
	//	pushVertexIndex(v2_i);

	//	pushTriState(TS_ACTIVE);
	//}

	//void RenderTriangleIndexListTextureZBufferRW::zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexIndexListSize());
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0:
	//		v0_i = vertexIndexAt(index * 3 + 0);
	//		v1_i = vertexIndexAt(index * 3 + 1);
	//		v2_i = vertexIndexAt(index * 3 + 2);
	//		break;

	//	case CLIP_MASK_V1:
	//		v0_i = vertexIndexAt(index * 3 + 1);
	//		v1_i = vertexIndexAt(index * 3 + 2);
	//		v2_i = vertexIndexAt(index * 3 + 0);
	//		break;

	//	case CLIP_MASK_V2:
	//		v0_i = vertexIndexAt(index * 3 + 2);
	//		v1_i = vertexIndexAt(index * 3 + 0);
	//		v2_i = vertexIndexAt(index * 3 + 1);
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 2);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & dbl_v2 = vertexAt(getVertexListSize() - 1);

	//	resizeUVList(getUVListSize() + 2);
	//	const Vec2<real> & t0 = uvAt(v0_i);
	//	const Vec2<real> & t1 = uvAt(v1_i);
	//	const Vec2<real> & t2 = uvAt(v2_i);

	//	Vec2<real> & new_t0 = uvAt(getUVListSize() - 2);
	//	Vec2<real> & dbl_t2 = uvAt(getUVListSize() - 1);

	//	//resizeColorList(getColorListSize() + 2);
	//	//const Vec4<real> & c0 = colorAt(v0_i);
	//	//const Vec4<real> & c1 = colorAt(v1_i);
	//	//const Vec4<real> & c2 = colorAt(v2_i);

	//	//Vec4<real> & new_c0 = colorAt(getColorListSize() - 2);
	//	//Vec4<real> & dbl_c2 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*	1       2
	//	* -------------
	//	*		0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.x, v1.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.y, v1.y);
	//	new_v0.z = getCameraNearZ();

	//	new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.x, t1.x);
	//	new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.y, t1.y);

	//	//new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.x, c1.x);
	//	//new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.y, c1.y);
	//	//new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.z, c1.z);

	//	pushVertexIndex(getVertexListSize() - 2);
	//	pushVertexIndex(v1_i);
	//	pushVertexIndex(v2_i);

	//	pushTriState(TS_ACTIVE);

	//	dbl_v2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	dbl_v2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	dbl_v2.z = getCameraNearZ();

	//	dbl_t2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	dbl_t2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	//dbl_c2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	//dbl_c2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	//dbl_c2.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	pushVertexIndex(getVertexListSize() - 2);
	//	pushVertexIndex(v2_i);
	//	pushVertexIndex(getVertexListSize() - 1);

	//	pushTriState(TS_ACTIVE);
	//}

	//TRI_STATE RenderTriangleIndexListTextureZBufferRW::zClipTriangleAtCamera(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());
	//	_ASSERT(getCameraNearZ() >= 1 && getCameraNearZ() < getCameraFarZ());

	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(vertexIndexAt(ti + 0));
	//	const Vec4<real> & v1 = vertexAt(vertexIndexAt(ti + 1));
	//	const Vec4<real> & v2 = vertexAt(vertexIndexAt(ti + 2));

	//	DWORD clip_mask_nz = 0;
	//	DWORD clip_mask_fz = 0;

	//	if(v0.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V0;
	//	else if(v0.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V0;

	//	if(v1.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V1;
	//	else if(v1.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V1;

	//	if(v2.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V2;
	//	else if(v2.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V2;

	//	switch(clip_mask_fz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;
	//	}

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;
	//	}

	//	return TS_ACTIVE;
	//}

	//TRI_STATE RenderTriangleIndexListTextureZBufferRW::sClipTriangleAtScreen(const size_t index)
	//{
	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(vertexIndexAt(ti + 0));
	//	const Vec4<real> & v1 = vertexAt(vertexIndexAt(ti + 1));
	//	const Vec4<real> & v2 = vertexAt(vertexIndexAt(ti + 2));

	//	if(min(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CULLED;

	//	if(min(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CULLED;

	//	if(max(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CULLED;

	//	if(max(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CULLED;

	//	if(min(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CLIPPED;

	//	if(min(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CLIPPED;

	//	if(max(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CLIPPED;

	//	if(max(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CLIPPED;

	//	return TS_ACTIVE;
	//}

	//void RenderTriangleIndexListTextureZBufferRW::reset(void)
	//{
	//	//_ASSERT(getVertexListSize() == getNormalListSize());
	//	_ASSERT(getVertexListSize() == getUVListSize());

	//	clearTriStateList();
	//	resizeTriStateList(getVertexIndexListSize() / 3, TS_ACTIVE);

	//	resizeVertexIndexList(getTriStateListSize() * 3);
	//}

	//void RenderTriangleIndexListTextureZBufferRW::removeBackfaceAtWorld(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		_ASSERT(TS_ACTIVE == triStateAt(i));

	//		const size_t vi = i * 3;
	//		const Vec4<real> & v0 = vertexAt(vertexIndexAt(vi + 0));
	//		const Vec4<real> & v1 = vertexAt(vertexIndexAt(vi + 1));
	//		const Vec4<real> & v2 = vertexAt(vertexIndexAt(vi + 2));

	//		if(vec3Dot(
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(getCameraPosition(), v0)) <= 0)
	//		{
	//			triStateAt(i) = TS_BACKFACE;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListTextureZBufferRW::worldToCamera(void)
	//{
	//	VertexList::iterator v_iter = getVertexListBegin();
	//	for(; v_iter != getVertexListEnd(); v_iter++)
	//	{
	//		*v_iter *= getCameraMatrix();
	//	}
	//}

	//void RenderTriangleIndexListTextureZBufferRW::zClipAtCamera(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);

	//	const size_t orig_size = getTriStateListSize();

	//	for(size_t i = 0; i < orig_size; i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			TRI_STATE state = zClipTriangleAtCamera(i); triStateAt(i) = state; // ***
	//		}
	//	}
	//}

	//void RenderTriangleIndexListTextureZBufferRW::cameraToScreen(void)
	//{
	//	const real halfWidth = (real)(getViewport().right - getViewport().left) / 2;
	//	const real halfHeight = (real)(getViewport().bottom - getViewport().top) / 2;

	//	VertexList::iterator v_iter = getVertexListBegin();
	//	for(; v_iter != getVertexListEnd(); v_iter++)
	//	{
	//		//       x * ( width / 2 ) * ctan( fov / 2 )
	//		// x' = -------------------------------------
	//		//                       z

	//		v_iter->x = getViewport().left + v_iter->x * getCameraProjection().x / v_iter->z * halfWidth + halfWidth;

	//		//       y * ( height / 2 ) * ctan( fov / 2 )
	//		// y' = -------------------------------------
	//		//                       z

	//		v_iter->y = getViewport().top + halfHeight - v_iter->y * getCameraProjection().y / v_iter->z * halfHeight;
	//	}
	//}

	//void RenderTriangleIndexListTextureZBufferRW::sClipAtScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			triStateAt(i) = sClipTriangleAtScreen(i);
	//		}
	//	}
	//}

	//void RenderTriangleIndexListTextureZBufferRW::drawTriangleIndexListZBufferW16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleIndexListTextureZBufferRW::drawTriangleIndexListZBufferW32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = vertexIndexAt(i * 3 + 0);
	//		const size_t v1_i = vertexIndexAt(i * 3 + 1);
	//		const size_t v2_i = vertexIndexAt(i * 3 + 2);

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleTextureZBufferW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				//rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v2_i) * 255, real(255)),
	//				uvAt(v0_i) * texture_expend,
	//				uvAt(v1_i) * texture_expend,
	//				uvAt(v2_i) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleTextureZBufferW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				//rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v2_i) * 255, real(255)),
	//				uvAt(v0_i) * texture_expend,
	//				uvAt(v1_i) * texture_expend,
	//				uvAt(v2_i) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListTextureZBufferRW::drawTriangleIndexList16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleIndexListTextureZBufferRW::drawTriangleIndexList32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = vertexIndexAt(i * 3 + 0);
	//		const size_t v1_i = vertexIndexAt(i * 3 + 1);
	//		const size_t v2_i = vertexIndexAt(i * 3 + 2);

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleTextureZBufferRW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				//rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v2_i) * 255, real(255)),
	//				uvAt(v0_i) * texture_expend,
	//				uvAt(v1_i) * texture_expend,
	//				uvAt(v2_i) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleTextureZBufferRW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				//rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v2_i) * 255, real(255)),
	//				uvAt(v0_i) * texture_expend,
	//				uvAt(v1_i) * texture_expend,
	//				uvAt(v2_i) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleListTexturePerspectiveLPZBufferRW::drawTriangleListZBufferW16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleListTexturePerspectiveLPZBufferRW::drawTriangleListZBufferW32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t vi = i * 3;

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleTexturePerspectiveLPZBufferW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				//rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 2) * 255, real(255)),
	//				uvAt(vi + 0) * texture_expend,
	//				uvAt(vi + 1) * texture_expend,
	//				uvAt(vi + 2) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleTexturePerspectiveLPZBufferW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				//rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 2) * 255, real(255)),
	//				uvAt(vi + 0) * texture_expend,
	//				uvAt(vi + 1) * texture_expend,
	//				uvAt(vi + 2) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleListTexturePerspectiveLPZBufferRW::drawTriangleList16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleListTexturePerspectiveLPZBufferRW::drawTriangleList32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t vi = i * 3;

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleTexturePerspectiveLPZBufferRW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				//rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 2) * 255, real(255)),
	//				uvAt(vi + 0) * texture_expend,
	//				uvAt(vi + 1) * texture_expend,
	//				uvAt(vi + 2) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleTexturePerspectiveLPZBufferRW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				//rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				//rgbaSaturate(colorAt(vi + 2) * 255, real(255)),
	//				uvAt(vi + 0) * texture_expend,
	//				uvAt(vi + 1) * texture_expend,
	//				uvAt(vi + 2) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListTexturePerspectiveLPZBufferRW::drawTriangleIndexListZBufferW16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleIndexListTexturePerspectiveLPZBufferRW::drawTriangleIndexListZBufferW32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = vertexIndexAt(i * 3 + 0);
	//		const size_t v1_i = vertexIndexAt(i * 3 + 1);
	//		const size_t v2_i = vertexIndexAt(i * 3 + 2);

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleTexturePerspectiveLPZBufferW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				//rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v2_i) * 255, real(255)),
	//				uvAt(v0_i) * texture_expend,
	//				uvAt(v1_i) * texture_expend,
	//				uvAt(v2_i) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleTexturePerspectiveLPZBufferW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				//rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v2_i) * 255, real(255)),
	//				uvAt(v0_i) * texture_expend,
	//				uvAt(v1_i) * texture_expend,
	//				uvAt(v2_i) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListTexturePerspectiveLPZBufferRW::drawTriangleIndexList16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleIndexListTexturePerspectiveLPZBufferRW::drawTriangleIndexList32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	//_ASSERT(getVertexListSize() == getColorListSize());

	//	const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = vertexIndexAt(i * 3 + 0);
	//		const size_t v1_i = vertexIndexAt(i * 3 + 1);
	//		const size_t v2_i = vertexIndexAt(i * 3 + 2);

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleTexturePerspectiveLPZBufferRW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				//rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v2_i) * 255, real(255)),
	//				uvAt(v0_i) * texture_expend,
	//				uvAt(v1_i) * texture_expend,
	//				uvAt(v2_i) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleTexturePerspectiveLPZBufferRW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				//rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				//rgbaSaturate(colorAt(v2_i) * 255, real(255)),
	//				uvAt(v0_i) * texture_expend,
	//				uvAt(v1_i) * texture_expend,
	//				uvAt(v2_i) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudTextureZBufferRW::zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexListSize());
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		v0_i = index * 3 + 0;
	//		v1_i = index * 3 + 1;
	//		v2_i = index * 3 + 2;
	//		break;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		v0_i = index * 3 + 2;
	//		v1_i = index * 3 + 0;
	//		v2_i = index * 3 + 1;
	//		break;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		v0_i = index * 3 + 1;
	//		v1_i = index * 3 + 2;
	//		v2_i = index * 3 + 0;
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 3);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 3);
	//	Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & new_v2 = vertexAt(getVertexListSize() - 1);

	//	resizeUVList(getUVListSize() + 3);
	//	const Vec2<real> & t0 = uvAt(v0_i);
	//	const Vec2<real> & t1 = uvAt(v1_i);
	//	const Vec2<real> & t2 = uvAt(v2_i);

	//	Vec2<real> & new_t0 = uvAt(getUVListSize() - 3);
	//	Vec2<real> & new_t1 = uvAt(getUVListSize() - 2);
	//	Vec2<real> & new_t2 = uvAt(getUVListSize() - 1);

	//	resizeColorList(getColorListSize() + 3);
	//	const Vec4<real> & c0 = colorAt(v0_i);
	//	const Vec4<real> & c1 = colorAt(v1_i);
	//	const Vec4<real> & c2 = colorAt(v2_i);

	//	Vec4<real> & new_c0 = colorAt(getColorListSize() - 3);
	//	Vec4<real> & new_c1 = colorAt(getColorListSize() - 2);
	//	Vec4<real> & new_c2 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*		2
	//	* -------------
	//	*	1       0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	new_v0.z = getCameraNearZ();

	//	new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	new_v1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.x, v2.x);
	//	new_v1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.y, v2.y);
	//	new_v1.z = getCameraNearZ();

	//	new_t1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.x, t2.x);
	//	new_t1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.y, t2.y);

	//	new_c1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.x, c2.x);
	//	new_c1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.y, c2.y);
	//	new_c1.z = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.z, c2.z);

	//	new_v2 = v2;
	//	new_t2 = t2;
	//	new_c2 = c2;

	//	pushTriState(TS_ACTIVE);
	//}

	//void RenderTriangleListGouraudTextureZBufferRW::zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexListSize());
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0:
	//		v0_i = index * 3 + 0;
	//		v1_i = index * 3 + 1;
	//		v2_i = index * 3 + 2;
	//		break;

	//	case CLIP_MASK_V1:
	//		v0_i = index * 3 + 1;
	//		v1_i = index * 3 + 2;
	//		v2_i = index * 3 + 0;
	//		break;

	//	case CLIP_MASK_V2:
	//		v0_i = index * 3 + 2;
	//		v1_i = index * 3 + 0;
	//		v2_i = index * 3 + 1;
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 6);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 6);
	//	Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 5);
	//	Vec4<real> & new_v2 = vertexAt(getVertexListSize() - 4);

	//	Vec4<real> & dbl_v0 = vertexAt(getVertexListSize() - 3);
	//	Vec4<real> & dbl_v1 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & dbl_v2 = vertexAt(getVertexListSize() - 1);

	//	resizeUVList(getUVListSize() + 6);
	//	const Vec2<real> & t0 = uvAt(v0_i);
	//	const Vec2<real> & t1 = uvAt(v1_i);
	//	const Vec2<real> & t2 = uvAt(v2_i);

	//	Vec2<real> & new_t0 = uvAt(getUVListSize() - 6);
	//	Vec2<real> & new_t1 = uvAt(getUVListSize() - 5);
	//	Vec2<real> & new_t2 = uvAt(getUVListSize() - 4);

	//	Vec2<real> & dbl_t0 = uvAt(getUVListSize() - 3);
	//	Vec2<real> & dbl_t1 = uvAt(getUVListSize() - 2);
	//	Vec2<real> & dbl_t2 = uvAt(getUVListSize() - 1);

	//	resizeColorList(getColorListSize() + 6);
	//	const Vec4<real> & c0 = colorAt(v0_i);
	//	const Vec4<real> & c1 = colorAt(v1_i);
	//	const Vec4<real> & c2 = colorAt(v2_i);

	//	Vec4<real> & new_c0 = colorAt(getColorListSize() - 6);
	//	Vec4<real> & new_c1 = colorAt(getColorListSize() - 5);
	//	Vec4<real> & new_c2 = colorAt(getColorListSize() - 4);

	//	Vec4<real> & dbl_c0 = colorAt(getColorListSize() - 3);
	//	Vec4<real> & dbl_c1 = colorAt(getColorListSize() - 2);
	//	Vec4<real> & dbl_c2 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*	1       2
	//	* -------------
	//	*		0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.x, v1.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.y, v1.y);
	//	new_v0.z = getCameraNearZ();

	//	new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.x, t1.x);
	//	new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.y, t1.y);

	//	new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.x, c1.x);
	//	new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.y, c1.y);
	//	new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.z, c1.z);

	//	new_v1 = v1;
	//	new_t1 = t1;
	//	new_c1 = c1;

	//	new_v2 = v2;
	//	new_t2 = t2;
	//	new_c2 = c2;

	//	pushTriState(TS_ACTIVE);

	//	dbl_v0 = new_v0;
	//	dbl_t0 = new_t0;
	//	dbl_c0 = new_c0;

	//	dbl_v1 = v2;
	//	dbl_t1 = t2;
	//	dbl_c1 = c2;

	//	dbl_v2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	dbl_v2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	dbl_v2.z = getCameraNearZ();

	//	dbl_t2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	dbl_t2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	dbl_c2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	dbl_c2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	dbl_c2.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	pushTriState(TS_ACTIVE);
	//}

	//TRI_STATE RenderTriangleListGouraudTextureZBufferRW::zClipTriangleAtCamera(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());
	//	_ASSERT(getCameraNearZ() >= 1 && getCameraNearZ() < getCameraFarZ());

	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(ti + 0);
	//	const Vec4<real> & v1 = vertexAt(ti + 1);
	//	const Vec4<real> & v2 = vertexAt(ti + 2);

	//	DWORD clip_mask_nz = 0;
	//	DWORD clip_mask_fz = 0;

	//	if(v0.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V0;
	//	else if(v0.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V0;

	//	if(v1.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V1;
	//	else if(v1.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V1;

	//	if(v2.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V2;
	//	else if(v2.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V2;

	//	switch(clip_mask_fz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;
	//	}

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;
	//	}

	//	return TS_ACTIVE;
	//}

	//TRI_STATE RenderTriangleListGouraudTextureZBufferRW::sClipTriangleAtScreen(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());

	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(ti + 0);
	//	const Vec4<real> & v1 = vertexAt(ti + 1);
	//	const Vec4<real> & v2 = vertexAt(ti + 2);

	//	if(min(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CULLED;

	//	if(min(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CULLED;

	//	if(max(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CULLED;

	//	if(max(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CULLED;

	//	if(min(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CLIPPED;

	//	if(min(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CLIPPED;

	//	if(max(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CLIPPED;

	//	if(max(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CLIPPED;

	//	return TS_ACTIVE;
	//}

	//void RenderTriangleListGouraudTextureZBufferRW::reset(void)
	//{
	//	_ASSERT(getVertexListSize() == getNormalListSize());
	//	_ASSERT(getVertexListSize() == getUVListSize());

	//	clearTriStateList();
	//	resizeTriStateList(getVertexListSize() / 3, TS_ACTIVE);

	//	resizeVertexList(getTriStateListSize() * 3);
	//	resizeNormalList(getTriStateListSize() * 3);
	//	resizeUVList(getTriStateListSize() * 3);
	//}

	//void RenderTriangleListGouraudTextureZBufferRW::removeBackfaceAtWorld(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		_ASSERT(TS_ACTIVE == triStateAt(i));

	//		const size_t vi = i * 3;
	//		const Vec4<real> & v0 = vertexAt(vi + 0);
	//		const Vec4<real> & v1 = vertexAt(vi + 1);
	//		const Vec4<real> & v2 = vertexAt(vi + 2);

	//		if(vec3Dot(
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(getCameraPosition(), v0)) <= 0)
	//		{
	//			triStateAt(i) = TS_BACKFACE;
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudTextureZBufferRW::lightAtWorld(void)
	//{
	//	_ASSERT(getVertexListSize() == getNormalListSize());

	//	clearColorList();
	//	resizeColorList(getTriStateListSize() * 3, Vec4<real>(0, 0, 0, 0));

	//	LightList::const_iterator l_iter = getLightListBegin();
	//	for(; l_iter != getLightListEnd(); l_iter++)
	//	{
	//		switch(l_iter->type)
	//		{
	//		case LT_AMBIENT:
	//			for(size_t i = 0; i < getTriStateListSize(); i++)
	//			{
	//				if(isTriVisible(triStateAt(i)))
	//				{
	//					const size_t vi = i * 3;
	//					colorAt(vi + 0) += lightVertexAmbient(*l_iter, getMaterial(), vertexAt(vi + 0), normalAt(vi + 0));
	//					colorAt(vi + 1) += lightVertexAmbient(*l_iter, getMaterial(), vertexAt(vi + 1), normalAt(vi + 1));
	//					colorAt(vi + 2) += lightVertexAmbient(*l_iter, getMaterial(), vertexAt(vi + 2), normalAt(vi + 2));
	//				}
	//			}
	//			break;

	//		case LT_DIRECTIONAL:
	//			for(size_t i = 0; i < getTriStateListSize(); i++)
	//			{
	//				if(isTriVisible(triStateAt(i)))
	//				{
	//					const size_t vi = i * 3;
	//					colorAt(vi + 0) += lightVertexDirectional(*l_iter, getMaterial(), vertexAt(vi + 0), normalAt(vi + 0));
	//					colorAt(vi + 1) += lightVertexDirectional(*l_iter, getMaterial(), vertexAt(vi + 1), normalAt(vi + 1));
	//					colorAt(vi + 2) += lightVertexDirectional(*l_iter, getMaterial(), vertexAt(vi + 2), normalAt(vi + 2));
	//				}
	//			}
	//			break;

	//		case LT_POINT:
	//			for(size_t i = 0; i < getTriStateListSize(); i++)
	//			{
	//				if(isTriVisible(triStateAt(i)))
	//				{
	//					const size_t vi = i * 3;
	//					colorAt(vi + 0) += lightVertexPoint(*l_iter, getMaterial(), vertexAt(vi + 0), normalAt(vi + 0));
	//					colorAt(vi + 1) += lightVertexPoint(*l_iter, getMaterial(), vertexAt(vi + 1), normalAt(vi + 1));
	//					colorAt(vi + 2) += lightVertexPoint(*l_iter, getMaterial(), vertexAt(vi + 2), normalAt(vi + 2));
	//				}
	//			}
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudTextureZBufferRW::worldToCamera(void)
	//{
	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			const size_t vi = i * 3;
	//			vertexAt(vi + 0) *= getCameraMatrix();
	//			vertexAt(vi + 1) *= getCameraMatrix();
	//			vertexAt(vi + 2) *= getCameraMatrix();
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudTextureZBufferRW::zClipAtCamera(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	const size_t orig_size = getTriStateListSize();

	//	for(size_t i = 0; i < orig_size; i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			TRI_STATE state = zClipTriangleAtCamera(i); triStateAt(i) = state; // ***
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudTextureZBufferRW::cameraToScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	const real halfWidth = (real)(getViewport().right - getViewport().left) / 2;
	//	const real halfHeight = (real)(getViewport().bottom - getViewport().top) / 2;

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			const size_t vi = i * 3;
	//			Vec4<real> & v0 = vertexAt(vi + 0);
	//			Vec4<real> & v1 = vertexAt(vi + 1);
	//			Vec4<real> & v2 = vertexAt(vi + 2);

	//			//       x * ( width / 2 ) * ctan( fov / 2 )
	//			// x' = -------------------------------------
	//			//                       z

	//			v0.x = getViewport().left + v0.x * getCameraProjection().x / v0.z * halfWidth + halfWidth;
	//			v1.x = getViewport().left + v1.x * getCameraProjection().x / v1.z * halfWidth + halfWidth;
	//			v2.x = getViewport().left + v2.x * getCameraProjection().x / v2.z * halfWidth + halfWidth;

	//			//       y * ( height / 2 ) * ctan( fov / 2 )
	//			// y' = -------------------------------------
	//			//                       z

	//			v0.y = getViewport().top + halfHeight - v0.y * getCameraProjection().y / v0.z * halfHeight;
	//			v1.y = getViewport().top + halfHeight - v1.y * getCameraProjection().y / v1.z * halfHeight;
	//			v2.y = getViewport().top + halfHeight - v2.y * getCameraProjection().y / v2.z * halfHeight;
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudTextureZBufferRW::sClipAtScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			triStateAt(i) = sClipTriangleAtScreen(i);
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudTextureZBufferRW::drawTriangleList16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleListGouraudTextureZBufferRW::drawTriangleList32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t vi = i * 3;

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleGouraudTextureZBufferRW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				rgbaSaturate(colorAt(vi + 2) * 255, real(255)),
	//				uvAt(vi + 0) * texture_expend,
	//				uvAt(vi + 1) * texture_expend,
	//				uvAt(vi + 2) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleGouraudTextureZBufferRW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				rgbaSaturate(colorAt(vi + 2) * 255, real(255)),
	//				uvAt(vi + 0) * texture_expend,
	//				uvAt(vi + 1) * texture_expend,
	//				uvAt(vi + 2) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListGouraudTextureZBufferRW::zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexIndexListSize());
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		v0_i = vertexIndexAt(index * 3 + 0);
	//		v1_i = vertexIndexAt(index * 3 + 1);
	//		v2_i = vertexIndexAt(index * 3 + 2);
	//		break;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		v0_i = vertexIndexAt(index * 3 + 2);
	//		v1_i = vertexIndexAt(index * 3 + 0);
	//		v2_i = vertexIndexAt(index * 3 + 1);
	//		break;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		v0_i = vertexIndexAt(index * 3 + 1);
	//		v1_i = vertexIndexAt(index * 3 + 2);
	//		v2_i = vertexIndexAt(index * 3 + 0);
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 2);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & new_v1 = vertexAt(getVertexListSize() - 1);

	//	resizeUVList(getUVListSize() + 2);
	//	const Vec2<real> & t0 = uvAt(v0_i);
	//	const Vec2<real> & t1 = uvAt(v1_i);
	//	const Vec2<real> & t2 = uvAt(v2_i);

	//	Vec2<real> & new_t0 = uvAt(getUVListSize() - 2);
	//	Vec2<real> & new_t1 = uvAt(getUVListSize() - 1);

	//	resizeColorList(getColorListSize() + 2);
	//	const Vec4<real> & c0 = colorAt(v0_i);
	//	const Vec4<real> & c1 = colorAt(v1_i);
	//	const Vec4<real> & c2 = colorAt(v2_i);

	//	Vec4<real> & new_c0 = colorAt(getColorListSize() - 2);
	//	Vec4<real> & new_c1 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*		2
	//	* -------------
	//	*	1       0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	new_v0.z = getCameraNearZ();

	//	new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	new_v1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.x, v2.x);
	//	new_v1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, v1.y, v2.y);
	//	new_v1.z = getCameraNearZ();

	//	new_t1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.x, t2.x);
	//	new_t1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, t1.y, t2.y);

	//	new_c1.x = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.x, c2.x);
	//	new_c1.y = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.y, c2.y);
	//	new_c1.z = LINE2D_INTERSECT(getCameraNearZ(), v1.z, v2.z, c1.z, c2.z);

	//	pushVertexIndex(getVertexListSize() - 2);
	//	pushVertexIndex(getVertexListSize() - 1);
	//	pushVertexIndex(v2_i);

	//	pushTriState(TS_ACTIVE);
	//}

	//void RenderTriangleIndexListGouraudTextureZBufferRW::zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz)
	//{
	//	_ASSERT(getTriStateListSize() * 3 == getVertexIndexListSize());
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	size_t v0_i, v1_i, v2_i;

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0:
	//		v0_i = vertexIndexAt(index * 3 + 0);
	//		v1_i = vertexIndexAt(index * 3 + 1);
	//		v2_i = vertexIndexAt(index * 3 + 2);
	//		break;

	//	case CLIP_MASK_V1:
	//		v0_i = vertexIndexAt(index * 3 + 1);
	//		v1_i = vertexIndexAt(index * 3 + 2);
	//		v2_i = vertexIndexAt(index * 3 + 0);
	//		break;

	//	case CLIP_MASK_V2:
	//		v0_i = vertexIndexAt(index * 3 + 2);
	//		v1_i = vertexIndexAt(index * 3 + 0);
	//		v2_i = vertexIndexAt(index * 3 + 1);
	//		break;

	//	default:
	//		_ASSERT(false);
	//		return;
	//	}

	//	resizeVertexList(getVertexListSize() + 2);
	//	const Vec4<real> & v0 = vertexAt(v0_i);
	//	const Vec4<real> & v1 = vertexAt(v1_i);
	//	const Vec4<real> & v2 = vertexAt(v2_i);

	//	Vec4<real> & new_v0 = vertexAt(getVertexListSize() - 2);
	//	Vec4<real> & dbl_v2 = vertexAt(getVertexListSize() - 1);

	//	resizeUVList(getUVListSize() + 2);
	//	const Vec2<real> & t0 = uvAt(v0_i);
	//	const Vec2<real> & t1 = uvAt(v1_i);
	//	const Vec2<real> & t2 = uvAt(v2_i);

	//	Vec2<real> & new_t0 = uvAt(getUVListSize() - 2);
	//	Vec2<real> & dbl_t2 = uvAt(getUVListSize() - 1);

	//	resizeColorList(getColorListSize() + 2);
	//	const Vec4<real> & c0 = colorAt(v0_i);
	//	const Vec4<real> & c1 = colorAt(v1_i);
	//	const Vec4<real> & c2 = colorAt(v2_i);

	//	Vec4<real> & new_c0 = colorAt(getColorListSize() - 2);
	//	Vec4<real> & dbl_c2 = colorAt(getColorListSize() - 1);

	//	/**********************************************************************
	//	*	1       2
	//	* -------------
	//	*		0
	//	**********************************************************************/

	//	new_v0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.x, v1.x);
	//	new_v0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, v0.y, v1.y);
	//	new_v0.z = getCameraNearZ();

	//	new_t0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.x, t1.x);
	//	new_t0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, t0.y, t1.y);

	//	new_c0.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.x, c1.x);
	//	new_c0.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.y, c1.y);
	//	new_c0.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v1.z, c0.z, c1.z);

	//	pushVertexIndex(getVertexListSize() - 2);
	//	pushVertexIndex(v1_i);
	//	pushVertexIndex(v2_i);

	//	pushTriState(TS_ACTIVE);

	//	dbl_v2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.x, v2.x);
	//	dbl_v2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, v0.y, v2.y);
	//	dbl_v2.z = getCameraNearZ();

	//	dbl_t2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.x, t2.x);
	//	dbl_t2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, t0.y, t2.y);

	//	dbl_c2.x = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.x, c2.x);
	//	dbl_c2.y = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.y, c2.y);
	//	dbl_c2.z = LINE2D_INTERSECT(getCameraNearZ(), v0.z, v2.z, c0.z, c2.z);

	//	pushVertexIndex(getVertexListSize() - 2);
	//	pushVertexIndex(v2_i);
	//	pushVertexIndex(getVertexListSize() - 1);

	//	pushTriState(TS_ACTIVE);
	//}

	//TRI_STATE RenderTriangleIndexListGouraudTextureZBufferRW::zClipTriangleAtCamera(const size_t index)
	//{
	//	_ASSERT(index < getTriStateListSize());
	//	_ASSERT(getCameraNearZ() >= 1 && getCameraNearZ() < getCameraFarZ());

	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(vertexIndexAt(ti + 0));
	//	const Vec4<real> & v1 = vertexAt(vertexIndexAt(ti + 1));
	//	const Vec4<real> & v2 = vertexAt(vertexIndexAt(ti + 2));

	//	DWORD clip_mask_nz = 0;
	//	DWORD clip_mask_fz = 0;

	//	if(v0.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V0;
	//	else if(v0.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V0;

	//	if(v1.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V1;
	//	else if(v1.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V1;

	//	if(v2.z < getCameraNearZ())
	//		clip_mask_nz |= CLIP_MASK_V2;
	//	else if(v2.z > getCameraFarZ())
	//		clip_mask_fz |= CLIP_MASK_V2;

	//	switch(clip_mask_fz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;
	//	}

	//	switch(clip_mask_nz)
	//	{
	//	case CLIP_MASK_V0 | CLIP_MASK_V1 | CLIP_MASK_V2:
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1 | CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZDouble(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V0:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V1:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;

	//	case CLIP_MASK_V2:
	//		zClipTriangleAtCameraNearZSingle(index, clip_mask_nz);
	//		return TS_CULLED;
	//	}

	//	return TS_ACTIVE;
	//}

	//TRI_STATE RenderTriangleIndexListGouraudTextureZBufferRW::sClipTriangleAtScreen(const size_t index)
	//{
	//	const size_t ti = index * 3;
	//	const Vec4<real> & v0 = vertexAt(vertexIndexAt(ti + 0));
	//	const Vec4<real> & v1 = vertexAt(vertexIndexAt(ti + 1));
	//	const Vec4<real> & v2 = vertexAt(vertexIndexAt(ti + 2));

	//	if(min(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CULLED;

	//	if(min(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CULLED;

	//	if(max(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CULLED;

	//	if(max(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CULLED;

	//	if(min(v0.x, v1.x, v2.x) < getViewport().left)
	//		return TS_CLIPPED;

	//	if(min(v0.y, v1.y, v2.y) < getViewport().top)
	//		return TS_CLIPPED;

	//	if(max(v0.x, v1.x, v2.x) >= getViewport().right)
	//		return TS_CLIPPED;

	//	if(max(v0.y, v1.y, v2.y) >= getViewport().bottom)
	//		return TS_CLIPPED;

	//	return TS_ACTIVE;
	//}

	//void RenderTriangleIndexListGouraudTextureZBufferRW::reset(void)
	//{
	//	_ASSERT(getVertexListSize() == getNormalListSize());
	//	_ASSERT(getVertexListSize() == getUVListSize());

	//	clearTriStateList();
	//	resizeTriStateList(getVertexIndexListSize() / 3, TS_ACTIVE);

	//	resizeVertexIndexList(getTriStateListSize() * 3);
	//}

	//void RenderTriangleIndexListGouraudTextureZBufferRW::removeBackfaceAtWorld(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		_ASSERT(TS_ACTIVE == triStateAt(i));

	//		const size_t vi = i * 3;
	//		const Vec4<real> & v0 = vertexAt(vertexIndexAt(vi + 0));
	//		const Vec4<real> & v1 = vertexAt(vertexIndexAt(vi + 1));
	//		const Vec4<real> & v2 = vertexAt(vertexIndexAt(vi + 2));

	//		if(vec3Dot(
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(getCameraPosition(), v0)) <= 0)
	//		{
	//			triStateAt(i) = TS_BACKFACE;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListGouraudTextureZBufferRW::lightAtWorld(void)
	//{
	//	_ASSERT(getVertexListSize() == getNormalListSize());

	//	clearColorList();
	//	resizeColorList(getVertexListSize(), Vec4<real>(0, 0, 0, 0));

	//	LightList::const_iterator l_iter = getLightListBegin();
	//	for(; l_iter != getLightListEnd(); l_iter++)
	//	{
	//		switch(l_iter->type)
	//		{
	//		case LT_AMBIENT:
	//			for(size_t i = 0; i < getVertexListSize(); i++)
	//			{
	//				colorAt(i) += lightVertexAmbient(*l_iter, getMaterial(), vertexAt(i), normalAt(i));
	//			}
	//			break;

	//		case LT_DIRECTIONAL:
	//			for(size_t i = 0; i < getVertexListSize(); i++)
	//			{
	//				colorAt(i) += lightVertexDirectional(*l_iter, getMaterial(), vertexAt(i), normalAt(i));
	//			}
	//			break;

	//		case LT_POINT:
	//			for(size_t i = 0; i < getVertexListSize(); i++)
	//			{
	//				colorAt(i) += lightVertexPoint(*l_iter, getMaterial(), vertexAt(i), normalAt(i));
	//			}
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListGouraudTextureZBufferRW::worldToCamera(void)
	//{
	//	VertexList::iterator v_iter = getVertexListBegin();
	//	for(; v_iter != getVertexListEnd(); v_iter++)
	//	{
	//		*v_iter *= getCameraMatrix();
	//	}
	//}

	//void RenderTriangleIndexListGouraudTextureZBufferRW::zClipAtCamera(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);

	//	const size_t orig_size = getTriStateListSize();

	//	for(size_t i = 0; i < orig_size; i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			TRI_STATE state = zClipTriangleAtCamera(i); triStateAt(i) = state; // ***
	//		}
	//	}
	//}

	//void RenderTriangleIndexListGouraudTextureZBufferRW::cameraToScreen(void)
	//{
	//	const real halfWidth = (real)(getViewport().right - getViewport().left) / 2;
	//	const real halfHeight = (real)(getViewport().bottom - getViewport().top) / 2;

	//	VertexList::iterator v_iter = getVertexListBegin();
	//	for(; v_iter != getVertexListEnd(); v_iter++)
	//	{
	//		//       x * ( width / 2 ) * ctan( fov / 2 )
	//		// x' = -------------------------------------
	//		//                       z

	//		v_iter->x = getViewport().left + v_iter->x * getCameraProjection().x / v_iter->z * halfWidth + halfWidth;

	//		//       y * ( height / 2 ) * ctan( fov / 2 )
	//		// y' = -------------------------------------
	//		//                       z

	//		v_iter->y = getViewport().top + halfHeight - v_iter->y * getCameraProjection().y / v_iter->z * halfHeight;
	//	}
	//}

	//void RenderTriangleIndexListGouraudTextureZBufferRW::sClipAtScreen(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		if(isTriVisible(triStateAt(i)))
	//		{
	//			triStateAt(i) = sClipTriangleAtScreen(i);
	//		}
	//	}
	//}

	//void RenderTriangleIndexListGouraudTextureZBufferRW::drawTriangleIndexList16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleIndexListGouraudTextureZBufferRW::drawTriangleIndexList32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = vertexIndexAt(i * 3 + 0);
	//		const size_t v1_i = vertexIndexAt(i * 3 + 1);
	//		const size_t v2_i = vertexIndexAt(i * 3 + 2);

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleGouraudTextureZBufferRW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				rgbaSaturate(colorAt(v2_i) * 255, real(255)),
	//				uvAt(v0_i) * texture_expend,
	//				uvAt(v1_i) * texture_expend,
	//				uvAt(v2_i) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleGouraudTextureZBufferRW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				rgbaSaturate(colorAt(v2_i) * 255, real(255)),
	//				uvAt(v0_i) * texture_expend,
	//				uvAt(v1_i) * texture_expend,
	//				uvAt(v2_i) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::drawTriangleList16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::drawTriangleList32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexListSize() / 3);
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t vi = i * 3;

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleGouraudTexturePerspectiveLPZBufferRW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				rgbaSaturate(colorAt(vi + 2) * 255, real(255)),
	//				uvAt(vi + 0) * texture_expend,
	//				uvAt(vi + 1) * texture_expend,
	//				uvAt(vi + 2) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleGouraudTexturePerspectiveLPZBufferRW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(vi + 0),
	//				vertexAt(vi + 1),
	//				vertexAt(vi + 2),
	//				rgbaSaturate(colorAt(vi + 0) * 255, real(255)),
	//				rgbaSaturate(colorAt(vi + 1) * 255, real(255)),
	//				rgbaSaturate(colorAt(vi + 2) * 255, real(255)),
	//				uvAt(vi + 0) * texture_expend,
	//				uvAt(vi + 1) * texture_expend,
	//				uvAt(vi + 2) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

	//void RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::drawTriangleIndexList16(void)
	//{
	//	_ASSERT(false);
	//}

	//void RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::drawTriangleIndexList32(void)
	//{
	//	_ASSERT(getTriStateListSize() == getVertexIndexListSize() / 3);
	//	_ASSERT(getVertexListSize() == getUVListSize());
	//	_ASSERT(getVertexListSize() == getColorListSize());

	//	const Vec2<real> texture_expend(real(getTextureWidth() - 1), real(getTextureHeight() - 1));

	//	for(size_t i = 0; i < getTriStateListSize(); i++)
	//	{
	//		const size_t v0_i = vertexIndexAt(i * 3 + 0);
	//		const size_t v1_i = vertexIndexAt(i * 3 + 1);
	//		const size_t v2_i = vertexIndexAt(i * 3 + 2);

	//		switch(triStateAt(i))
	//		{
	//		case TS_ACTIVE:
	//			drawTriangleGouraudTexturePerspectiveLPZBufferRW32(
	//				getSurfaceRef32(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				rgbaSaturate(colorAt(v2_i) * 255, real(255)),
	//				uvAt(v0_i) * texture_expend,
	//				uvAt(v1_i) * texture_expend,
	//				uvAt(v2_i) * texture_expend);
	//			break;

	//		case TS_CLIPPED:
	//			drawClippedTriangleGouraudTexturePerspectiveLPZBufferRW32(
	//				getSurfaceRef32(),
	//				getClipperRect(),
	//				getZBufferRef28(),
	//				getTextureRef32(),
	//				vertexAt(v0_i),
	//				vertexAt(v1_i),
	//				vertexAt(v2_i),
	//				rgbaSaturate(colorAt(v0_i) * 255, real(255)),
	//				rgbaSaturate(colorAt(v1_i) * 255, real(255)),
	//				rgbaSaturate(colorAt(v2_i) * 255, real(255)),
	//				uvAt(v0_i) * texture_expend,
	//				uvAt(v1_i) * texture_expend,
	//				uvAt(v2_i) * texture_expend);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

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

	void RenderContext16::drawTriangleListShadowVolumnZPass(const Vec4<real> & color)
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

	void RenderContext16::drawTriangleIndexListShadowVolumnZPass(const Vec4<real> & color)
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
		//RenderLineListZBufferRW::reset();
		//RenderLineListZBufferRW::worldToCamera();
		//RenderLineListZBufferRW::zClipAtCamera();
		//RenderLineListZBufferRW::cameraToScreen();
		//RenderLineListZBufferRW::sClipAtScreen();
		//RenderLineListZBufferRW::drawLineList16(color);
		resetClipStateList(getClipStateList(), getVertexListSize() / 2);
		transformLineListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		clipLineListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenLineList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipLineListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawLineListZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList(), color);
	}

	void RenderContext16::drawLineIndexListZBufferRW(const Vec4<real> & color)
	{
		//RenderLineIndexListZBufferRW::reset();
		//RenderLineIndexListZBufferRW::worldToCamera();
		//RenderLineIndexListZBufferRW::zClipAtCamera();
		//RenderLineIndexListZBufferRW::cameraToScreen();
		//RenderLineIndexListZBufferRW::sClipAtScreen();
		//RenderLineIndexListZBufferRW::drawLineIndexList16(color);
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 2);
		transformLineIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipLineIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenLineIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipLineIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawLineIndexListZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	void RenderContext16::drawTriangleListWireZBufferRW(const Vec4<real> & color)
	{
		//RenderTriangleListWireZBufferRW::reset();
		//RenderTriangleListWireZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListWireZBufferRW::worldToCamera();
		//RenderTriangleListWireZBufferRW::zClipAtCamera();
		//RenderTriangleListWireZBufferRW::cameraToScreen();
		//RenderTriangleListWireZBufferRW::sClipAtScreen();
		//RenderTriangleListWireZBufferRW::drawTriangleList16(color);
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
		//RenderTriangleIndexListWireZBufferRW::reset();
		//RenderTriangleIndexListWireZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListWireZBufferRW::worldToCamera();
		//RenderTriangleIndexListWireZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListWireZBufferRW::cameraToScreen();
		//RenderTriangleIndexListWireZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListWireZBufferRW::drawTriangleIndexList16(color);
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
		//RenderTriangleListWireZBufferRW::reset();
		////RenderTriangleListWireZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListWireZBufferRW::worldToCamera();
		//RenderTriangleListWireZBufferRW::zClipAtCamera();
		//RenderTriangleListWireZBufferRW::cameraToScreen();
		//RenderTriangleListWireZBufferRW::sClipAtScreen();
		//RenderTriangleListWireZBufferRW::drawTriangleList16(color);
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
		//RenderTriangleIndexListWireZBufferRW::reset();
		////RenderTriangleIndexListWireZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListWireZBufferRW::worldToCamera();
		//RenderTriangleIndexListWireZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListWireZBufferRW::cameraToScreen();
		//RenderTriangleIndexListWireZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListWireZBufferRW::drawTriangleIndexList16(color);
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
		//RenderTriangleListZBufferRW::reset();
		//RenderTriangleListZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListZBufferRW::worldToCamera();
		//RenderTriangleListZBufferRW::zClipAtCamera();
		//RenderTriangleListZBufferRW::cameraToScreen();
		//RenderTriangleListZBufferRW::sClipAtScreen();
		//RenderTriangleListZBufferRW::drawTriangleList16(color);
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
		//RenderTriangleIndexListZBufferRW::reset();
		//RenderTriangleIndexListZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListZBufferRW::worldToCamera();
		//RenderTriangleIndexListZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListZBufferRW::cameraToScreen();
		//RenderTriangleIndexListZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListZBufferRW::drawTriangleIndexList16(color);
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
		//RenderTriangleListZBufferRW::reset();
		////RenderTriangleListZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListZBufferRW::worldToCamera();
		//RenderTriangleListZBufferRW::zClipAtCamera();
		//RenderTriangleListZBufferRW::cameraToScreen();
		//RenderTriangleListZBufferRW::sClipAtScreen();
		//RenderTriangleListZBufferRW::drawTriangleList16(color);
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
		//RenderTriangleIndexListZBufferRW::reset();
		////RenderTriangleIndexListZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListZBufferRW::worldToCamera();
		//RenderTriangleIndexListZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListZBufferRW::cameraToScreen();
		//RenderTriangleIndexListZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListZBufferRW::drawTriangleIndexList16(color);
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
		//RenderTriangleListGouraudZBufferRW::reset();
		//RenderTriangleListGouraudZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListGouraudZBufferRW::lightAtWorld();
		//RenderTriangleListGouraudZBufferRW::worldToCamera();
		//RenderTriangleListGouraudZBufferRW::zClipAtCamera();
		//RenderTriangleListGouraudZBufferRW::cameraToScreen();
		//RenderTriangleListGouraudZBufferRW::sClipAtScreen();
		//RenderTriangleListGouraudZBufferRW::drawTriangleList16();
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
		//RenderTriangleIndexListGouraudZBufferRW::reset();
		//RenderTriangleIndexListGouraudZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListGouraudZBufferRW::lightAtWorld();
		//RenderTriangleIndexListGouraudZBufferRW::worldToCamera();
		//RenderTriangleIndexListGouraudZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListGouraudZBufferRW::cameraToScreen();
		//RenderTriangleIndexListGouraudZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListGouraudZBufferRW::drawTriangleIndexList16();
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
		//RenderTriangleListGouraudZBufferRW::reset();
		////RenderTriangleListGouraudZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListGouraudZBufferRW::lightAtWorld();
		//RenderTriangleListGouraudZBufferRW::worldToCamera();
		//RenderTriangleListGouraudZBufferRW::zClipAtCamera();
		//RenderTriangleListGouraudZBufferRW::cameraToScreen();
		//RenderTriangleListGouraudZBufferRW::sClipAtScreen();
		//RenderTriangleListGouraudZBufferRW::drawTriangleList16();
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
		//RenderTriangleIndexListGouraudZBufferRW::reset();
		////RenderTriangleIndexListGouraudZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListGouraudZBufferRW::lightAtWorld();
		//RenderTriangleIndexListGouraudZBufferRW::worldToCamera();
		//RenderTriangleIndexListGouraudZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListGouraudZBufferRW::cameraToScreen();
		//RenderTriangleIndexListGouraudZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListGouraudZBufferRW::drawTriangleIndexList16();
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
		//RenderTriangleListTextureZBufferRW::reset();
		//RenderTriangleListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTextureZBufferRW::lightAtWorld();
		//RenderTriangleListTextureZBufferRW::worldToCamera();
		//RenderTriangleListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleListTextureZBufferRW::cameraToScreen();
		//RenderTriangleListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleListTextureZBufferRW::drawTriangleListZBufferW16();
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
		//RenderTriangleIndexListTextureZBufferRW::reset();
		//RenderTriangleIndexListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTextureZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTextureZBufferRW::worldToCamera();
		//RenderTriangleIndexListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTextureZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTextureZBufferRW::drawTriangleIndexListZBufferW16();
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
		//RenderTriangleListTextureZBufferRW::reset();
		////RenderTriangleListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTextureZBufferRW::lightAtWorld();
		//RenderTriangleListTextureZBufferRW::worldToCamera();
		//RenderTriangleListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleListTextureZBufferRW::cameraToScreen();
		//RenderTriangleListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleListTextureZBufferRW::drawTriangleListZBufferW16();
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
		//RenderTriangleIndexListTextureZBufferRW::reset();
		////RenderTriangleIndexListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTextureZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTextureZBufferRW::worldToCamera();
		//RenderTriangleIndexListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTextureZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTextureZBufferRW::drawTriangleIndexListZBufferW16();
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
		//RenderTriangleListTexturePerspectiveLPZBufferRW::reset();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::drawTriangleListZBufferW16();
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
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::reset();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::drawTriangleIndexListZBufferW16();
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
		//RenderTriangleListTexturePerspectiveLPZBufferRW::reset();
		////RenderTriangleListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::drawTriangleListZBufferW16();
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
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::reset();
		////RenderTriangleIndexListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::drawTriangleIndexListZBufferW16();
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
		//RenderTriangleListTextureZBufferRW::reset();
		//RenderTriangleListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTextureZBufferRW::lightAtWorld();
		//RenderTriangleListTextureZBufferRW::worldToCamera();
		//RenderTriangleListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleListTextureZBufferRW::cameraToScreen();
		//RenderTriangleListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleListTextureZBufferRW::drawTriangleList16();
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
		//RenderTriangleIndexListTextureZBufferRW::reset();
		//RenderTriangleIndexListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTextureZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTextureZBufferRW::worldToCamera();
		//RenderTriangleIndexListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTextureZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTextureZBufferRW::drawTriangleIndexList16();
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
		//RenderTriangleListTextureZBufferRW::reset();
		////RenderTriangleListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTextureZBufferRW::lightAtWorld();
		//RenderTriangleListTextureZBufferRW::worldToCamera();
		//RenderTriangleListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleListTextureZBufferRW::cameraToScreen();
		//RenderTriangleListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleListTextureZBufferRW::drawTriangleList16();
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
		//RenderTriangleIndexListTextureZBufferRW::reset();
		////RenderTriangleIndexListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTextureZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTextureZBufferRW::worldToCamera();
		//RenderTriangleIndexListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTextureZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTextureZBufferRW::drawTriangleIndexList16();
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
		//RenderTriangleListTexturePerspectiveLPZBufferRW::reset();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::drawTriangleList16();
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
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::reset();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::drawTriangleIndexList16();
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
		//RenderTriangleListTexturePerspectiveLPZBufferRW::reset();
		////RenderTriangleListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::drawTriangleList16();
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
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::reset();
		////RenderTriangleIndexListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::drawTriangleIndexList16();
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
		//RenderTriangleListGouraudTextureZBufferRW::reset();
		//RenderTriangleListGouraudTextureZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListGouraudTextureZBufferRW::lightAtWorld();
		//RenderTriangleListGouraudTextureZBufferRW::worldToCamera();
		//RenderTriangleListGouraudTextureZBufferRW::zClipAtCamera();
		//RenderTriangleListGouraudTextureZBufferRW::cameraToScreen();
		//RenderTriangleListGouraudTextureZBufferRW::sClipAtScreen();
		//RenderTriangleListGouraudTextureZBufferRW::drawTriangleList16();
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
		//RenderTriangleIndexListGouraudTextureZBufferRW::reset();
		//RenderTriangleIndexListGouraudTextureZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListGouraudTextureZBufferRW::lightAtWorld();
		//RenderTriangleIndexListGouraudTextureZBufferRW::worldToCamera();
		//RenderTriangleIndexListGouraudTextureZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListGouraudTextureZBufferRW::cameraToScreen();
		//RenderTriangleIndexListGouraudTextureZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListGouraudTextureZBufferRW::drawTriangleIndexList16();
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
		//RenderTriangleListGouraudTextureZBufferRW::reset();
		////RenderTriangleListGouraudTextureZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListGouraudTextureZBufferRW::lightAtWorld();
		//RenderTriangleListGouraudTextureZBufferRW::worldToCamera();
		//RenderTriangleListGouraudTextureZBufferRW::zClipAtCamera();
		//RenderTriangleListGouraudTextureZBufferRW::cameraToScreen();
		//RenderTriangleListGouraudTextureZBufferRW::sClipAtScreen();
		//RenderTriangleListGouraudTextureZBufferRW::drawTriangleList16();
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
		//RenderTriangleIndexListGouraudTextureZBufferRW::reset();
		////RenderTriangleIndexListGouraudTextureZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListGouraudTextureZBufferRW::lightAtWorld();
		//RenderTriangleIndexListGouraudTextureZBufferRW::worldToCamera();
		//RenderTriangleIndexListGouraudTextureZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListGouraudTextureZBufferRW::cameraToScreen();
		//RenderTriangleIndexListGouraudTextureZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListGouraudTextureZBufferRW::drawTriangleIndexList16();
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
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::reset();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::drawTriangleList16();
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
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::reset();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::drawTriangleIndexList16();
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
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::reset();
		////RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::drawTriangleList16();
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
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::reset();
		////RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::drawTriangleIndexList16();
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

	void RenderContext32::drawTriangleListShadowVolumnZPass(const Vec4<real> & color)
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

	void RenderContext32::drawTriangleIndexListShadowVolumnZPass(const Vec4<real> & color)
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
		//RenderLineListZBufferRW::reset();
		//RenderLineListZBufferRW::worldToCamera();
		//RenderLineListZBufferRW::zClipAtCamera();
		//RenderLineListZBufferRW::cameraToScreen();
		//RenderLineListZBufferRW::sClipAtScreen();
		//RenderLineListZBufferRW::drawLineList32(color);
		resetClipStateList(getClipStateList(), getVertexListSize() / 2);
		transformLineListSelf(getVertexList(), getClipStateList(), getCameraMatrix());
		clipLineListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenLineList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipLineListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawLineListZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getClipStateList(), color);
	}

	void RenderContext32::drawLineIndexListZBufferRW(const Vec4<real> & color)
	{
		//RenderLineIndexListZBufferRW::reset();
		//RenderLineIndexListZBufferRW::worldToCamera();
		//RenderLineIndexListZBufferRW::zClipAtCamera();
		//RenderLineIndexListZBufferRW::cameraToScreen();
		//RenderLineIndexListZBufferRW::sClipAtScreen();
		//RenderLineIndexListZBufferRW::drawLineIndexList32(color);
		resetClipStateList(getClipStateList(), getVertexIndexListSize() / 2);
		transformLineIndexListSelf(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipLineIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenLineIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipLineIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawLineIndexListZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	void RenderContext32::drawTriangleListWireZBufferRW(const Vec4<real> & color)
	{
		//RenderTriangleListWireZBufferRW::reset();
		//RenderTriangleListWireZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListWireZBufferRW::worldToCamera();
		//RenderTriangleListWireZBufferRW::zClipAtCamera();
		//RenderTriangleListWireZBufferRW::cameraToScreen();
		//RenderTriangleListWireZBufferRW::sClipAtScreen();
		//RenderTriangleListWireZBufferRW::drawTriangleList32(color);
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
		//RenderTriangleIndexListWireZBufferRW::reset();
		//RenderTriangleIndexListWireZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListWireZBufferRW::worldToCamera();
		//RenderTriangleIndexListWireZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListWireZBufferRW::cameraToScreen();
		//RenderTriangleIndexListWireZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListWireZBufferRW::drawTriangleIndexList32(color);
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
		//RenderTriangleListWireZBufferRW::reset();
		////RenderTriangleListWireZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListWireZBufferRW::worldToCamera();
		//RenderTriangleListWireZBufferRW::zClipAtCamera();
		//RenderTriangleListWireZBufferRW::cameraToScreen();
		//RenderTriangleListWireZBufferRW::sClipAtScreen();
		//RenderTriangleListWireZBufferRW::drawTriangleList32(color);
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
		//RenderTriangleIndexListWireZBufferRW::reset();
		////RenderTriangleIndexListWireZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListWireZBufferRW::worldToCamera();
		//RenderTriangleIndexListWireZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListWireZBufferRW::cameraToScreen();
		//RenderTriangleIndexListWireZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListWireZBufferRW::drawTriangleIndexList32(color);
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
		//RenderTriangleListZBufferRW::reset();
		//RenderTriangleListZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListZBufferRW::worldToCamera();
		//RenderTriangleListZBufferRW::zClipAtCamera();
		//RenderTriangleListZBufferRW::cameraToScreen();
		//RenderTriangleListZBufferRW::sClipAtScreen();
		//RenderTriangleListZBufferRW::drawTriangleList32(color);
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
		//RenderTriangleIndexListZBufferRW::reset();
		//RenderTriangleIndexListZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListZBufferRW::worldToCamera();
		//RenderTriangleIndexListZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListZBufferRW::cameraToScreen();
		//RenderTriangleIndexListZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListZBufferRW::drawTriangleIndexList32(color);
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
		//RenderTriangleListZBufferRW::reset();
		////RenderTriangleListZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListZBufferRW::worldToCamera();
		//RenderTriangleListZBufferRW::zClipAtCamera();
		//RenderTriangleListZBufferRW::cameraToScreen();
		//RenderTriangleListZBufferRW::sClipAtScreen();
		//RenderTriangleListZBufferRW::drawTriangleList32(color);
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
		//RenderTriangleIndexListZBufferRW::reset();
		////RenderTriangleIndexListZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListZBufferRW::worldToCamera();
		//RenderTriangleIndexListZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListZBufferRW::cameraToScreen();
		//RenderTriangleIndexListZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListZBufferRW::drawTriangleIndexList32(color);
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
		//RenderTriangleListGouraudZBufferRW::reset();
		//RenderTriangleListGouraudZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListGouraudZBufferRW::lightAtWorld();
		//RenderTriangleListGouraudZBufferRW::worldToCamera();
		//RenderTriangleListGouraudZBufferRW::zClipAtCamera();
		//RenderTriangleListGouraudZBufferRW::cameraToScreen();
		//RenderTriangleListGouraudZBufferRW::sClipAtScreen();
		//RenderTriangleListGouraudZBufferRW::drawTriangleList32();
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
		//RenderTriangleIndexListGouraudZBufferRW::reset();
		//RenderTriangleIndexListGouraudZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListGouraudZBufferRW::lightAtWorld();
		//RenderTriangleIndexListGouraudZBufferRW::worldToCamera();
		//RenderTriangleIndexListGouraudZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListGouraudZBufferRW::cameraToScreen();
		//RenderTriangleIndexListGouraudZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListGouraudZBufferRW::drawTriangleIndexList32();
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
		//RenderTriangleListGouraudZBufferRW::reset();
		////RenderTriangleListGouraudZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListGouraudZBufferRW::lightAtWorld();
		//RenderTriangleListGouraudZBufferRW::worldToCamera();
		//RenderTriangleListGouraudZBufferRW::zClipAtCamera();
		//RenderTriangleListGouraudZBufferRW::cameraToScreen();
		//RenderTriangleListGouraudZBufferRW::sClipAtScreen();
		//RenderTriangleListGouraudZBufferRW::drawTriangleList32();
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
		//RenderTriangleIndexListGouraudZBufferRW::reset();
		////RenderTriangleIndexListGouraudZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListGouraudZBufferRW::lightAtWorld();
		//RenderTriangleIndexListGouraudZBufferRW::worldToCamera();
		//RenderTriangleIndexListGouraudZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListGouraudZBufferRW::cameraToScreen();
		//RenderTriangleIndexListGouraudZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListGouraudZBufferRW::drawTriangleIndexList32();
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
		//RenderTriangleListTextureZBufferRW::reset();
		//RenderTriangleListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTextureZBufferRW::lightAtWorld();
		//RenderTriangleListTextureZBufferRW::worldToCamera();
		//RenderTriangleListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleListTextureZBufferRW::cameraToScreen();
		//RenderTriangleListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleListTextureZBufferRW::drawTriangleListZBufferW32();
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
		//RenderTriangleIndexListTextureZBufferRW::reset();
		//RenderTriangleIndexListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTextureZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTextureZBufferRW::worldToCamera();
		//RenderTriangleIndexListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTextureZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTextureZBufferRW::drawTriangleIndexListZBufferW32();
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
		//RenderTriangleListTextureZBufferRW::reset();
		////RenderTriangleListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTextureZBufferRW::lightAtWorld();
		//RenderTriangleListTextureZBufferRW::worldToCamera();
		//RenderTriangleListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleListTextureZBufferRW::cameraToScreen();
		//RenderTriangleListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleListTextureZBufferRW::drawTriangleListZBufferW32();
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
		//RenderTriangleIndexListTextureZBufferRW::reset();
		////RenderTriangleIndexListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTextureZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTextureZBufferRW::worldToCamera();
		//RenderTriangleIndexListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTextureZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTextureZBufferRW::drawTriangleIndexListZBufferW32();
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
		//RenderTriangleListTexturePerspectiveLPZBufferRW::reset();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::drawTriangleListZBufferW32();
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
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::reset();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::drawTriangleIndexListZBufferW32();
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
		//RenderTriangleListTexturePerspectiveLPZBufferRW::reset();
		////RenderTriangleListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::drawTriangleListZBufferW32();
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
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::reset();
		////RenderTriangleIndexListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::drawTriangleIndexListZBufferW32();
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
		//RenderTriangleListTextureZBufferRW::reset();
		//RenderTriangleListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTextureZBufferRW::lightAtWorld();
		//RenderTriangleListTextureZBufferRW::worldToCamera();
		//RenderTriangleListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleListTextureZBufferRW::cameraToScreen();
		//RenderTriangleListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleListTextureZBufferRW::drawTriangleList32();
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
		//RenderTriangleIndexListTextureZBufferRW::reset();
		//RenderTriangleIndexListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTextureZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTextureZBufferRW::worldToCamera();
		//RenderTriangleIndexListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTextureZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTextureZBufferRW::drawTriangleIndexList32();
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
		//RenderTriangleListTextureZBufferRW::reset();
		////RenderTriangleListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTextureZBufferRW::lightAtWorld();
		//RenderTriangleListTextureZBufferRW::worldToCamera();
		//RenderTriangleListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleListTextureZBufferRW::cameraToScreen();
		//RenderTriangleListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleListTextureZBufferRW::drawTriangleList32();
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
		//RenderTriangleIndexListTextureZBufferRW::reset();
		////RenderTriangleIndexListTextureZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTextureZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTextureZBufferRW::worldToCamera();
		//RenderTriangleIndexListTextureZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTextureZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTextureZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTextureZBufferRW::drawTriangleIndexList32();
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
		//RenderTriangleListTexturePerspectiveLPZBufferRW::reset();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::drawTriangleList32();
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
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::reset();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::drawTriangleIndexList32();
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
		//RenderTriangleListTexturePerspectiveLPZBufferRW::reset();
		////RenderTriangleListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleListTexturePerspectiveLPZBufferRW::drawTriangleList32();
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
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::reset();
		////RenderTriangleIndexListTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		////RenderTriangleIndexListTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListTexturePerspectiveLPZBufferRW::drawTriangleIndexList32();
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
		//RenderTriangleListGouraudTextureZBufferRW::reset();
		//RenderTriangleListGouraudTextureZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListGouraudTextureZBufferRW::lightAtWorld();
		//RenderTriangleListGouraudTextureZBufferRW::worldToCamera();
		//RenderTriangleListGouraudTextureZBufferRW::zClipAtCamera();
		//RenderTriangleListGouraudTextureZBufferRW::cameraToScreen();
		//RenderTriangleListGouraudTextureZBufferRW::sClipAtScreen();
		//RenderTriangleListGouraudTextureZBufferRW::drawTriangleList32();
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
		//RenderTriangleIndexListGouraudTextureZBufferRW::reset();
		//RenderTriangleIndexListGouraudTextureZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListGouraudTextureZBufferRW::lightAtWorld();
		//RenderTriangleIndexListGouraudTextureZBufferRW::worldToCamera();
		//RenderTriangleIndexListGouraudTextureZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListGouraudTextureZBufferRW::cameraToScreen();
		//RenderTriangleIndexListGouraudTextureZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListGouraudTextureZBufferRW::drawTriangleIndexList32();
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
		//RenderTriangleListGouraudTextureZBufferRW::reset();
		////RenderTriangleListGouraudTextureZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListGouraudTextureZBufferRW::lightAtWorld();
		//RenderTriangleListGouraudTextureZBufferRW::worldToCamera();
		//RenderTriangleListGouraudTextureZBufferRW::zClipAtCamera();
		//RenderTriangleListGouraudTextureZBufferRW::cameraToScreen();
		//RenderTriangleListGouraudTextureZBufferRW::sClipAtScreen();
		//RenderTriangleListGouraudTextureZBufferRW::drawTriangleList32();
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
		//RenderTriangleIndexListGouraudTextureZBufferRW::reset();
		////RenderTriangleIndexListGouraudTextureZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListGouraudTextureZBufferRW::lightAtWorld();
		//RenderTriangleIndexListGouraudTextureZBufferRW::worldToCamera();
		//RenderTriangleIndexListGouraudTextureZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListGouraudTextureZBufferRW::cameraToScreen();
		//RenderTriangleIndexListGouraudTextureZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListGouraudTextureZBufferRW::drawTriangleIndexList32();
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
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::reset();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::drawTriangleList32();
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
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::reset();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::drawTriangleIndexList32();
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
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::reset();
		////RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleListGouraudTexturePerspectiveLPZBufferRW::drawTriangleList32();
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
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::reset();
		////RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::removeBackfaceAtWorld();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::lightAtWorld();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::worldToCamera();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::zClipAtCamera();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::cameraToScreen();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::sClipAtScreen();
		//RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW::drawTriangleIndexList32();
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
