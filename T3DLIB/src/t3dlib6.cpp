
#include "stdafx.h"
#include "t3dlib6.h"

#define CLIP_MASK_V0	0x01
#define CLIP_MASK_V1	0x02
#define CLIP_MASK_V2	0x04

namespace t3d
{
	//const VertexList & VertexListContext::getVertexList(void) const
	//{
	//	return m_vertexList;
	//}

	//VertexList & VertexListContext::getVertexList(void)
	//{
	//	return m_vertexList;
	//}

	//void VertexListContext::pushVertex(real x, real y, real z)
	//{
	//	pushVertex(vec3Build(x, y, z));
	//}

	//void VertexListContext::pushVertex(real x, real y, real z, const Mat4<real> & mmat)
	//{
	//	pushVertex(vec3Build(x, y, z), mmat);
	//}

	//void VertexListContext::pushVertex(VertexList::const_reference vertex)
	//{
	//	getVertexList().push_back(vertex);
	//}

	//void VertexListContext::pushVertex(VertexList::const_reference vertex, const Mat4<real> & mmat)
	//{
	//	getVertexList().push_back(vertex * mmat);
	//}

	//void VertexListContext::pushVertexList(VertexList::const_iterator begin, VertexList::const_iterator end)
	//{
	//	getVertexList().insert(getVertexListEnd(), begin, end);
	//}

	//void VertexListContext::pushVertexList(VertexList::const_iterator begin, VertexList::const_iterator end, const Mat4<real> & mmat)
	//{
	//	_ASSERT(std::distance(begin, end) >= 0);

	//	const VertexList::size_type previous_size = getVertexListSize();
	//	const VertexList::difference_type inserted_size = previous_size + std::distance(begin, end);

	//	resizeVertexList(inserted_size);
	//	for(VertexList::difference_type i = previous_size; i < inserted_size; i++)
	//	{
	//		vertexAt(i) = *(begin + i) * mmat;
	//	}
	//}

	//void VertexListContext::clearVertexList(void)
	//{
	//	getVertexList().clear();
	//}

	//void VertexListContext::resizeVertexList(VertexList::size_type size)
	//{
	//	getVertexList().resize(size);
	//}

	//VertexList::size_type VertexListContext::getVertexListSize(void) const
	//{
	//	return getVertexList().size();
	//}

	//VertexList::reference VertexListContext::vertexAt(VertexList::size_type i)
	//{
	//	_ASSERT(i < getVertexListSize());

	//	return getVertexList()[i];
	//}

	//VertexList::const_reference VertexListContext::vertexAt(VertexList::size_type i) const
	//{
	//	_ASSERT(i < getVertexListSize());

	//	return getVertexList()[i];
	//}

	//VertexList::iterator VertexListContext::getVertexListBegin()
	//{
	//	return getVertexList().begin();
	//}

	//VertexList::const_iterator VertexListContext::getVertexListBegin() const
	//{
	//	return getVertexList().begin();
	//}

	//VertexList::iterator VertexListContext::getVertexListEnd()
	//{
	//	return getVertexList().end();
	//}

	//VertexList::const_iterator VertexListContext::getVertexListEnd() const
	//{
	//	return getVertexList().end();
	//}

	//const VertexIndexList & VertexIndexListContext::getVertexIndexList(void) const
	//{
	//	return m_vertexIndexList;
	//}

	//VertexIndexList & VertexIndexListContext::getVertexIndexList(void)
	//{
	//	return m_vertexIndexList;
	//}

	//void VertexIndexListContext::pushVertexIndex(VertexIndexList::const_reference index)
	//{
	//	getVertexIndexList().push_back(index);
	//}

	//void VertexIndexListContext::pushVertexIndexList(VertexIndexList::const_iterator begin, VertexIndexList::const_iterator end)
	//{
	//	getVertexIndexList().insert(getVertexIndexListEnd(), begin, end);
	//}

	//void VertexIndexListContext::clearVertexIndexList(void)
	//{
	//	getVertexIndexList().clear();
	//}

	//void VertexIndexListContext::resizeVertexIndexList(VertexIndexList::size_type size)
	//{
	//	getVertexIndexList().resize(size);
	//}

	//VertexIndexList::size_type VertexIndexListContext::getVertexIndexListSize(void) const
	//{
	//	return getVertexIndexList().size();
	//}

	//VertexIndexList::reference VertexIndexListContext::vertexIndexAt(VertexIndexList::size_type i)
	//{
	//	_ASSERT(i < getVertexIndexListSize());

	//	return getVertexIndexList()[i];
	//}

	//VertexIndexList::const_reference VertexIndexListContext::vertexIndexAt(VertexIndexList::size_type i) const
	//{
	//	_ASSERT(i < getVertexIndexListSize());

	//	return getVertexIndexList()[i];
	//}

	//VertexIndexList::iterator VertexIndexListContext::getVertexIndexListBegin()
	//{
	//	return getVertexIndexList().begin();
	//}

	//VertexIndexList::const_iterator VertexIndexListContext::getVertexIndexListBegin() const
	//{
	//	return getVertexIndexList().begin();
	//}

	//VertexIndexList::iterator VertexIndexListContext::getVertexIndexListEnd()
	//{
	//	return getVertexIndexList().end();
	//}

	//VertexIndexList::const_iterator VertexIndexListContext::getVertexIndexListEnd() const
	//{
	//	return getVertexIndexList().end();
	//}

	//const NormalList & NormalListContext::getNormalList(void) const
	//{
	//	return m_normalList;
	//}

	//NormalList & NormalListContext::getNormalList(void)
	//{
	//	return m_normalList;
	//}

	//void NormalListContext::pushNormal(real x, real y, real z)
	//{
	//	pushNormal(vec3Build(x, y, z));
	//}

	//void NormalListContext::pushNormal(real x, real y, real z, const Mat4<real> & mmat)
	//{
	//	pushNormal(vec3Build(x, y, z), mmat);
	//}

	//void NormalListContext::pushNormal(NormalList::const_reference normal)
	//{
	//	getNormalList().push_back(normal);
	//}

	//void NormalListContext::pushNormal(NormalList::const_reference normal, const Mat4<real> & mmat)
	//{
	//	getNormalList().push_back(normal * mmat);
	//}

	//void NormalListContext::pushNormalList(NormalList::const_iterator begin, NormalList::const_iterator end)
	//{
	//	getNormalList().insert(getNormalListEnd(), begin, end);
	//}

	//void NormalListContext::pushNormalList(NormalList::const_iterator begin, NormalList::const_iterator end, const Mat4<real> & mmat)
	//{
	//	_ASSERT(std::distance(begin, end) >= 0);

	//	const NormalList::size_type previous_size = getNormalListSize();
	//	const NormalList::difference_type inserted_size = previous_size + std::distance(begin, end);

	//	resizeNormalList(inserted_size);
	//	for(NormalList::difference_type i = previous_size; i < inserted_size; i++)
	//	{
	//		normalAt(i) = *(begin + i) * mmat;
	//	}
	//}

	//void NormalListContext::clearNormalList(void)
	//{
	//	getNormalList().clear();
	//}

	//void NormalListContext::resizeNormalList(NormalList::size_type size)
	//{
	//	getNormalList().resize(size);
	//}

	//NormalList::size_type NormalListContext::getNormalListSize(void) const
	//{
	//	return getNormalList().size();
	//}

	//NormalList::reference NormalListContext::normalAt(NormalList::size_type i)
	//{
	//	_ASSERT(i < getNormalListSize());

	//	return getNormalList()[i];
	//}

	//NormalList::const_reference NormalListContext::normalAt(NormalList::size_type i) const
	//{
	//	_ASSERT(i < getNormalListSize());

	//	return getNormalList()[i];
	//}

	//NormalList::iterator NormalListContext::getNormalListBegin()
	//{
	//	return getNormalList().begin();
	//}

	//NormalList::const_iterator NormalListContext::getNormalListBegin() const
	//{
	//	return getNormalList().begin();
	//}

	//NormalList::iterator NormalListContext::getNormalListEnd()
	//{
	//	return getNormalList().end();
	//}

	//NormalList::const_iterator NormalListContext::getNormalListEnd() const
	//{
	//	return getNormalList().end();
	//}

	//const UVList & UVListContext::getUVList(void) const
	//{
	//	return m_uvList;
	//}

	//UVList & UVListContext::getUVList(void)
	//{
	//	return m_uvList;
	//}

	//void UVListContext::pushUV(real u, real v)
	//{
	//	pushUV(Vec2<real>(u, v));
	//}

	//void UVListContext::pushUV(UVList::const_reference uv)
	//{
	//	getUVList().push_back(uv);
	//}

	//void UVListContext::pushUVList(UVList::const_iterator begin, UVList::const_iterator end)
	//{
	//	getUVList().insert(getUVListEnd(), begin, end);
	//}

	//void UVListContext::clearUVList(void)
	//{
	//	getUVList().clear();
	//}

	//void UVListContext::resizeUVList(UVList::size_type size)
	//{
	//	getUVList().resize(size);
	//}

	//UVList::size_type UVListContext::getUVListSize(void) const
	//{
	//	return getUVList().size();
	//}

	//UVList::reference UVListContext::uvAt(UVList::size_type i)
	//{
	//	_ASSERT(i < getUVListSize());

	//	return getUVList()[i];
	//}

	//UVList::const_reference UVListContext::uvAt(UVList::size_type i) const
	//{
	//	_ASSERT(i < getUVListSize());

	//	return getUVList()[i];
	//}

	//UVList::iterator UVListContext::getUVListBegin()
	//{
	//	return getUVList().begin();
	//}

	//UVList::const_iterator UVListContext::getUVListBegin() const
	//{
	//	return getUVList().begin();
	//}

	//UVList::iterator UVListContext::getUVListEnd()
	//{
	//	return getUVList().end();
	//}

	//UVList::const_iterator UVListContext::getUVListEnd() const
	//{
	//	return getUVList().end();
	//}

	//const ColorList & ColorListContext::getColorList(void) const
	//{
	//	return m_colorList;
	//}

	//ColorList & ColorListContext::getColorList(void)
	//{
	//	return m_colorList;
	//}

	//void ColorListContext::pushColor(real r, real g, real b, real a)
	//{
	//	pushColor(Vec4<real>(r, g, b, a));
	//}

	//void ColorListContext::pushColor(ColorList::const_reference color)
	//{
	//	m_colorList.push_back(color);
	//}

	//void ColorListContext::pushColorList(ColorList::const_iterator begin, ColorList::const_iterator end)
	//{
	//	m_colorList.insert(getColorListEnd(), begin, end);
	//}

	//void ColorListContext::clearColorList(void)
	//{
	//	m_colorList.clear();
	//}

	//void ColorListContext::resizeColorList(ColorList::size_type size)
	//{
	//	m_colorList.resize(size);
	//}

	//void ColorListContext::resizeColorList(ColorList::size_type size, ColorList::const_reference color)
	//{
	//	m_colorList.resize(size, color);
	//}

	//ColorList::size_type ColorListContext::getColorListSize(void) const
	//{
	//	return m_colorList.size();
	//}

	//ColorList::reference ColorListContext::colorAt(ColorList::size_type i)
	//{
	//	_ASSERT(i < getColorListSize());

	//	return m_colorList[i];
	//}

	//ColorList::const_reference ColorListContext::colorAt(ColorList::size_type i) const
	//{
	//	_ASSERT(i < getColorListSize());

	//	return m_colorList[i];
	//}

	//ColorList::iterator ColorListContext::getColorListBegin()
	//{
	//	return m_colorList.begin();
	//}

	//ColorList::const_iterator ColorListContext::getColorListBegin() const
	//{
	//	return m_colorList.begin();
	//}

	//ColorList::iterator ColorListContext::getColorListEnd()
	//{
	//	return m_colorList.end();
	//}

	//ColorList::const_iterator ColorListContext::getColorListEnd() const
	//{
	//	return m_colorList.end();
	//}

	//void SurfaceContext::setSurfaceBuffer(void * pbuffer)
	//{
	//	m_surfaceBuffer = pbuffer;
	//}

	//void SurfaceContext::setSurfaceBuffer(void * pbuffer, LONG pitch, DWORD width, DWORD height)
	//{
	//	setSurfaceBuffer(pbuffer);
	//	setSurfacePitch(pitch);
	//	setSurfaceWidth(width);
	//	setSurfaceHeight(height);
	//}

	//void * SurfaceContext::getSurfaceBuffer(void) const
	//{
	//	return m_surfaceBuffer;
	//}

	//void SurfaceContext::setSurfacePitch(LONG pitch)
	//{
	//	m_surfacePitch = pitch;
	//}

	//LONG SurfaceContext::getSurfacePitch(void) const
	//{
	//	return m_surfacePitch;
	//}

	//void SurfaceContext::setSurfaceWidth(DWORD width)
	//{
	//	m_surfaceWidth = width;
	//}

	//DWORD SurfaceContext::getSurfaceWidth(void) const
	//{
	//	return m_surfaceWidth;
	//}

	//void SurfaceContext::setSurfaceHeight(DWORD height)
	//{
	//	m_surfaceHeight = height;
	//}

	//DWORD SurfaceContext::getSurfaceHeight(void) const
	//{
	//	return m_surfaceHeight;
	//}

	//SurfaceRef<uint16> SurfaceContext::getSurfaceRef16(void) const
	//{
	//	return SurfaceRef<uint16>(static_cast<uint16*>(m_surfaceBuffer), m_surfacePitch);
	//}

	//SurfaceRef<uint32> SurfaceContext::getSurfaceRef32(void) const
	//{
	//	return SurfaceRef<uint32>(static_cast<uint32*>(m_surfaceBuffer), m_surfacePitch);
	//}

	//void ZBufferContext::setZBufferBuffer(void * pbuffer)
	//{
	//	m_zbufferBuffer = pbuffer;
	//}

	//void ZBufferContext::setZBufferBuffer(void * pbuffer, LONG pitch, DWORD width, DWORD height)
	//{
	//	setZBufferBuffer(pbuffer);
	//	setZBufferPitch(pitch);
	//	setZBufferWidth(width);
	//	setZBufferHeight(height);
	//}

	//void * ZBufferContext::getZBufferBuffer(void) const
	//{
	//	return m_zbufferBuffer;
	//}

	//void ZBufferContext::setZBufferPitch(LONG pitch)
	//{
	//	m_zbufferPitch = pitch;
	//}

	//LONG ZBufferContext::getZBufferPitch(void) const
	//{
	//	return m_zbufferPitch;
	//}

	//void ZBufferContext::setZBufferWidth(DWORD width)
	//{
	//	m_zbufferWidth = width;
	//}

	//DWORD ZBufferContext::getZBufferWidth(void) const
	//{
	//	return m_zbufferWidth;
	//}

	//void ZBufferContext::setZBufferHeight(DWORD height)
	//{
	//	m_zbufferHeight = height;
	//}

	//DWORD ZBufferContext::getZBufferHeight(void) const
	//{
	//	return m_zbufferHeight;
	//}

	//SurfaceRef<fixp28> ZBufferContext::getZBufferRef28(void) const
	//{
	//	return SurfaceRef<fixp28>(static_cast<fixp28*>(m_zbufferBuffer), m_zbufferPitch);
	//}

	//void TextureContext::setTextureBuffer(void * pbuffer)
	//{
	//	m_textureBuffer = pbuffer;
	//}

	//void TextureContext::setTextureBuffer(void * pbuffer, LONG pitch, DWORD width, DWORD height)
	//{
	//	setTextureBuffer(pbuffer);
	//	setTexturePitch(pitch);
	//	setTextureWidth(width);
	//	setTextureHeight(height);
	//}

	//void * TextureContext::getTextureBuffer(void) const
	//{
	//	return m_textureBuffer;
	//}

	//void TextureContext::setTexturePitch(LONG pitch)
	//{
	//	m_texturePitch = pitch;
	//}

	//LONG TextureContext::getTexturePitch(void) const
	//{
	//	return m_texturePitch;
	//}

	//void TextureContext::setTextureWidth(DWORD width)
	//{
	//	m_textureWidth = width;
	//}

	//DWORD TextureContext::getTextureWidth(void) const
	//{
	//	return m_textureWidth;
	//}

	//void TextureContext::setTextureHeight(DWORD height)
	//{
	//	m_textureHeight = height;
	//}

	//DWORD TextureContext::getTextureHeight(void) const
	//{
	//	return m_textureHeight;
	//}

	//SurfaceRef<uint16> TextureContext::getTextureRef16(void) const
	//{
	//	return SurfaceRef<uint16>(static_cast<uint16*>(m_textureBuffer), m_texturePitch);
	//}

	//SurfaceRef<uint32> TextureContext::getTextureRef32(void) const
	//{
	//	return SurfaceRef<uint32>(static_cast<uint32*>(m_textureBuffer), m_texturePitch);
	//}

	//void ClipperContext::setClipperRect(const CRect & clipper)
	//{
	//	m_clipper = clipper;
	//}

	//const CRect & ClipperContext::getClipperRect(void) const
	//{
	//	return m_clipper;
	//}

	//void MaterialContext::setMaterial(const MATERIAL & material)
	//{
	//	m_material = material;
	//}

	//const MATERIAL & MaterialContext::getMaterial(void) const
	//{
	//	return m_material;
	//}

	//void MaterialContext::setAmbient(const Vec4<real> & ambient)
	//{
	//	m_material.ambient = ambient;
	//}

	//void MaterialContext::setDiffuse(const Vec4<real> & diffuse)
	//{
	//	m_material.diffuse = diffuse;
	//}

	//void MaterialContext::setSpecular(const Vec4<real> & specular)
	//{
	//	m_material.specular = specular;
	//}

	//void MaterialContext::setEmissive(const Vec4<real> & emissive)
	//{
	//	m_material.emissive = emissive;
	//}

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

	//const LightList & LightListContext::getLightList(void) const
	//{
	//	return m_lightList;
	//}

	//LightList & LightListContext::getLightList(void)
	//{
	//	return m_lightList;
	//}

	//size_t LightListContext::pushLightAmbient(const Vec4<real> & ambient, LIGHT_STATE state /*= LS_ON*/)
	//{
	//	m_lightList.push_back(buildLightAmbient(ambient, state));

	//	return getLightListSize() - 1;
	//};

	//size_t LightListContext::pushLightDirectional(const Vec4<real> & diffuse, const Vec4<real> dir, LIGHT_STATE state /*= LS_ON*/)
	//{
	//	m_lightList.push_back(buildLightDirectional(diffuse, dir, state));

	//	return getLightListSize() - 1;
	//};

	//size_t LightListContext::pushLightPoint(const Vec4<real> & diffuse, const Vec4<real> pos, real kc /*= 1.0f*/, real kl /*= 0.001f*/, real kq /*= 0.00001f*/, LIGHT_STATE state /*= LS_ON*/)
	//{
	//	m_lightList.push_back(buildLightPoint(diffuse, pos, kc, kl, kq, state));

	//	return getLightListSize() - 1;
	//};

	//void LightListContext::clearLightList(void)
	//{
	//	m_lightList.clear();
	//}

	//void LightListContext::resizeLightList(LightList::size_type size)
	//{
	//	m_lightList.resize(size);
	//}

	//LightList::size_type LightListContext::getLightListSize(void) const
	//{
	//	return m_lightList.size();
	//}

	//LightList::reference LightListContext::lightAt(LightList::size_type i)
	//{
	//	_ASSERT(i < getLightListSize());

	//	return m_lightList[i];
	//}

	//LightList::const_reference LightListContext::lightAt(LightList::size_type i) const
	//{
	//	_ASSERT(i < getLightListSize());

	//	return m_lightList[i];
	//}

	//LightList::iterator LightListContext::getLightListBegin()
	//{
	//	return m_lightList.begin();
	//}

	//LightList::const_iterator LightListContext::getLightListBegin() const
	//{
	//	return m_lightList.begin();
	//}

	//LightList::iterator LightListContext::getLightListEnd()
	//{
	//	return m_lightList.end();
	//}

	//LightList::const_iterator LightListContext::getLightListEnd() const
	//{
	//	return m_lightList.end();
	//}

	Mat4<real> CameraContext::buildCameraTransformEular(const Vec4<real> & pos, const Vec4<real> & rot, DWORD rot_seq /*= RS_ZXY*/)
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

	Mat4<real> CameraContext::buildInverseCameraTransformEular(const Vec4<real> & pos, const Vec4<real> & rot, DWORD rot_seq /*= RS_ZXY*/)
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

	//real CameraContext::calculateCameraHalfFovX(const Vec2<real> & proj)
	//{
	//	return atan(1 / proj.x);
	//}

	//real CameraContext::calculateCameraHalfFovY(const Vec2<real> & proj)
	//{
	//	return atan(1 / proj.y);
	//}

	//real CameraContext::calculateCameraMaxHalfFov(const Vec2<real> & proj)
	//{
	//	return proj.x < proj.y ? calculateCameraHalfFovX(proj) : calculateCameraHalfFovY(proj);
	//}

	//Vec4<real> CameraContext::calculateCameraDirection(const Mat4<real> & mcam)
	//{
	//	return Vec4<real>(0, 0, 1, 1) * mat4GetRotationScalePart(mcam.inverse());
	//}

	//void CameraContext::setCameraMatrix(const Mat4<real> & mcam)
	//{
	//	m_camera.mcam = mcam;
	//}

	//const Mat4<real> & CameraContext::getCameraMatrix(void) const
	//{
	//	return m_camera.mcam;
	//}

	//void CameraContext::setCameraProjection(const Vec2<real> & proj)
	//{
	//	m_camera.proj = proj;
	//}

	//const Vec2<real> & CameraContext::getCameraProjection(void) const
	//{
	//	return m_camera.proj;
	//}

	//void CameraContext::setCameraNearZ(real nz)
	//{
	//	m_camera.nz = nz;
	//}

	//real CameraContext::getCameraNearZ(void) const
	//{
	//	return m_camera.nz;
	//}

	//void CameraContext::setCameraFarZ(real fz)
	//{
	//	m_camera.fz = fz;
	//}

	//real CameraContext::getCameraFarZ(void) const
	//{
	//	return m_camera.fz;
	//}

	//void CameraContext::setViewport(const CRect & viewport)
	//{
	//	m_camera.viewport = viewport;
	//}

	//const CRect & CameraContext::getViewport(void) const
	//{
	//	return m_camera.viewport;
	//}

	//Vec4<real> CameraContext::getCameraPosition(void) const
	//{
	//	return mat3GetRow3(getCameraMatrix().inverse());
	//}

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
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(calculateCameraPosition(getCameraMatrix()), v0)) <= 0)
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
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(calculateCameraPosition(getCameraMatrix()), v0)) <= 0)
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
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(calculateCameraPosition(getCameraMatrix()), v0)) <= 0)
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
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(calculateCameraPosition(getCameraMatrix()), v0)) <= 0)
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
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(calculateCameraPosition(getCameraMatrix()), v0)) <= 0)
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
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(calculateCameraPosition(getCameraMatrix()), v0)) <= 0)
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
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(calculateCameraPosition(getCameraMatrix()), v0)) <= 0)
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
	//			vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(calculateCameraPosition(getCameraMatrix()), v0)) <= 0)
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

	void RenderContext16::fillSurface(const CRect & rect, const Vec4<real> & color)
	{
		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		fillSurface16(getSurfaceRef16(), m_clipper & rect, rgbaSaturate<real>(color * 255, 255));
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
		transformLineList(getVertexList(), getClipStateList(), getCameraMatrix());
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
		transformLineIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListWireZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	//void RenderContext16::drawTriangleListWireZBufferRWWithoutThird(const Vec4<real> & color)
	//{
	//	RenderTriangleListWireZBufferRW::reset();
	//	RenderTriangleListWireZBufferRW::removeBackfaceAtWorld();
	//	RenderTriangleListWireZBufferRW::worldToCamera();
	//	RenderTriangleListWireZBufferRW::zClipAtCamera();
	//	RenderTriangleListWireZBufferRW::cameraToScreen();
	//	RenderTriangleListWireZBufferRW::sClipAtScreen();
	//	RenderTriangleListWireZBufferRW::drawTriangleListWithoutThird16(color);
	//}

	//void RenderContext16::drawTriangleIndexListWireZBufferRWWithoutThird(const Vec4<real> & color)
	//{
	//	RenderTriangleIndexListWireZBufferRW::reset();
	//	RenderTriangleIndexListWireZBufferRW::removeBackfaceAtWorld();
	//	RenderTriangleIndexListWireZBufferRW::worldToCamera();
	//	RenderTriangleIndexListWireZBufferRW::zClipAtCamera();
	//	RenderTriangleIndexListWireZBufferRW::cameraToScreen();
	//	RenderTriangleIndexListWireZBufferRW::sClipAtScreen();
	//	RenderTriangleIndexListWireZBufferRW::drawTriangleIndexListWithoutThird16(color);
	//}

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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListWireZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	//void RenderContext16::drawTriangleListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color)
	//{
	//	RenderTriangleListWireZBufferRW::reset();
	//	//RenderTriangleListWireZBufferRW::removeBackfaceAtWorld();
	//	RenderTriangleListWireZBufferRW::worldToCamera();
	//	RenderTriangleListWireZBufferRW::zClipAtCamera();
	//	RenderTriangleListWireZBufferRW::cameraToScreen();
	//	RenderTriangleListWireZBufferRW::sClipAtScreen();
	//	RenderTriangleListWireZBufferRW::drawTriangleListWithoutThird16(color);
	//}

	//void RenderContext16::drawTriangleIndexListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color)
	//{
	//	RenderTriangleIndexListWireZBufferRW::reset();
	//	//RenderTriangleIndexListWireZBufferRW::removeBackfaceAtWorld();
	//	RenderTriangleIndexListWireZBufferRW::worldToCamera();
	//	RenderTriangleIndexListWireZBufferRW::zClipAtCamera();
	//	RenderTriangleIndexListWireZBufferRW::cameraToScreen();
	//	RenderTriangleIndexListWireZBufferRW::sClipAtScreen();
	//	RenderTriangleIndexListWireZBufferRW::drawTriangleIndexListWithoutThird16(color);
	//}

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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListGouraudAtCamera(getVertexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListGouraudAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListGouraudAtCamera(getVertexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListGouraudAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudTextureZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getColorList(), getUVList(), getClipStateList());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTextureZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudTextureZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getColorList(), getUVList(), getClipStateList());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTextureZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudTexturePerspectiveLPZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getColorList(), getUVList(), getClipStateList());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
		drawTriangleListGouraudTexturePerspectiveLPZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getColorList(), getUVList(), getClipStateList());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW16(getSurfaceRef16(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
	}

	void RenderContext32::fillSurface(const CRect & rect, const Vec4<real> & color)
	{
		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		fillSurface32(getSurfaceRef32(), m_clipper & rect, rgbaSaturate<real>(color * 255, 255));
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
		transformLineList(getVertexList(), getClipStateList(), getCameraMatrix());
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
		transformLineIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListWireZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	//void RenderContext32::drawTriangleListWireZBufferRWWithoutThird(const Vec4<real> & color)
	//{
	//	RenderTriangleListWireZBufferRW::reset();
	//	RenderTriangleListWireZBufferRW::removeBackfaceAtWorld();
	//	RenderTriangleListWireZBufferRW::worldToCamera();
	//	RenderTriangleListWireZBufferRW::zClipAtCamera();
	//	RenderTriangleListWireZBufferRW::cameraToScreen();
	//	RenderTriangleListWireZBufferRW::sClipAtScreen();
	//	RenderTriangleListWireZBufferRW::drawTriangleListWithoutThird32(color);
	//}

	//void RenderContext32::drawTriangleIndexListWireZBufferRWWithoutThird(const Vec4<real> & color)
	//{
	//	RenderTriangleIndexListWireZBufferRW::reset();
	//	RenderTriangleIndexListWireZBufferRW::removeBackfaceAtWorld();
	//	RenderTriangleIndexListWireZBufferRW::worldToCamera();
	//	RenderTriangleIndexListWireZBufferRW::zClipAtCamera();
	//	RenderTriangleIndexListWireZBufferRW::cameraToScreen();
	//	RenderTriangleIndexListWireZBufferRW::sClipAtScreen();
	//	RenderTriangleIndexListWireZBufferRW::drawTriangleIndexListWithoutThird32(color);
	//}

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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListWireZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getVertexList(), getVertexIndexList(), getClipStateList(), color);
	}

	//void RenderContext32::drawTriangleListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color)
	//{
	//	RenderTriangleListWireZBufferRW::reset();
	//	//RenderTriangleListWireZBufferRW::removeBackfaceAtWorld();
	//	RenderTriangleListWireZBufferRW::worldToCamera();
	//	RenderTriangleListWireZBufferRW::zClipAtCamera();
	//	RenderTriangleListWireZBufferRW::cameraToScreen();
	//	RenderTriangleListWireZBufferRW::sClipAtScreen();
	//	RenderTriangleListWireZBufferRW::drawTriangleListWithoutThird32(color);
	//}

	//void RenderContext32::drawTriangleIndexListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color)
	//{
	//	RenderTriangleIndexListWireZBufferRW::reset();
	//	//RenderTriangleIndexListWireZBufferRW::removeBackfaceAtWorld();
	//	RenderTriangleIndexListWireZBufferRW::worldToCamera();
	//	RenderTriangleIndexListWireZBufferRW::zClipAtCamera();
	//	RenderTriangleIndexListWireZBufferRW::cameraToScreen();
	//	RenderTriangleIndexListWireZBufferRW::sClipAtScreen();
	//	RenderTriangleIndexListWireZBufferRW::drawTriangleIndexListWithoutThird32(color);
	//}

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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListAtCamera(getVertexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListAtCamera(getVertexList(), getVertexIndexList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListGouraudAtCamera(getVertexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListGouraudAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListGouraudAtCamera(getVertexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListGouraudAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListTextureAtCamera(getVertexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListTextureAtCamera(getVertexList(), getVertexIndexList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
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
		//removeTriangleListBackfaceAtWorld(getVertexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleListAtWorld(getVertexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleList(getVertexList(), getClipStateList(), getCameraMatrix());
		clipTriangleListGouraudTextureAtCamera(getVertexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleList(getVertexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleListAtScreen(getVertexList(), getClipStateList(), getViewport());
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
		//removeTriangleIndexListBackfaceAtWorld(getVertexList(), getVertexIndexList(), getClipStateList(), calculateCameraPosition(getCameraMatrix()));
		resetColorList(getColorList(), getVertexListSize());
		lightTriangleIndexListAtWorld(getVertexList(), getVertexIndexList(), getNormalList(), getClipStateList(), getLightList(), getMaterial(), getColorList());
		transformTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraMatrix());
		clipTriangleIndexListGouraudTextureAtCamera(getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList(), getCamera());
		cameraToScreenTriangleIndexList(getVertexList(), getVertexIndexList(), getClipStateList(), getCameraProjection(), getViewport());
		clipTriangleIndexListAtScreen(getVertexList(), getVertexIndexList(), getClipStateList(), getViewport());
		drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW32(getSurfaceRef32(), getClipperRect(), getZBufferRef28(), getTextureRef32(), Vec2<real>(getTextureWidth() - 1, getTextureHeight() - 1), getVertexList(), getVertexIndexList(), getColorList(), getUVList(), getClipStateList());
	}
//#pragma warning(disable: 4100)
	void transformVertexList(
		VertexList & vertexList,
		const Mat4<real> & mmat)
	{
		VertexList::iterator vert_iter = vertexList.begin();
		for(; vert_iter != vertexList.end(); vert_iter++)
		{
			(*vert_iter) *= mmat;
		}
	}

	//void transformVertexIndexList(
	//	VertexList & vertexList,
	//	VertexIndexList & vertexIndexList,
	//	const Mat4<real> & mmat)
	//{
	//	VertexIndexList::const_iterator vert_index_iter = vertexIndexList.begin();
	//	for(; vert_index_iter != vertexIndexList.end(); vert_index_iter++)
	//	{
	//		vertexList[*vert_index_iter] *= mmat;
	//	}
	//}

	void transformLineList(
		VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 2);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				vertexList[i * 2 + 0] *= mmat;
				vertexList[i * 2 + 1] *= mmat;
			}
		}
	}

	void transformLineIndexList(
		VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 2);

		transformVertexList(vertexList, mmat);
	}

	CLIP_STATE clipLineAtCamera(
		Vec4<real> v0,
		Vec4<real> v1,
		const CAMERA & camera,
		VertexList & retVertexList,
		ClipStateList & retClipStateList)
	{
		if(v0.z > camera.nz)
		{
			if(v1.z > camera.nz)
			{
				return CLIP_STATE_NONE;
			}
			else if(v1.z == camera.nz)
			{
				return CLIP_STATE_NONE;
			}
			else
			{
				retVertexList.push_back(v0);
				retVertexList.push_back(vec3ClipZ(v0, v1, camera.nz));
				retClipStateList.push_back(CLIP_STATE_NONE);
				return CLIP_STATE_CULLED;
			}
		}
		else if(v0.z == camera.nz)
		{
			if(v1.z > camera.nz)
			{
				return CLIP_STATE_NONE;
			}
			else if(v1.z == camera.nz)
			{
				return CLIP_STATE_NONE;
			}
			else
			{
				return CLIP_STATE_CULLED;
			}
		}
		else
		{
			if(v1.z > camera.nz)
			{
				retVertexList.push_back(vec3ClipZ(v0, v1, camera.nz));
				retVertexList.push_back(v1);
				retClipStateList.push_back(CLIP_STATE_NONE);
				return CLIP_STATE_CULLED;
			}
			else if(v1.z == camera.nz)
			{
				return CLIP_STATE_CULLED;
			}
			else
			{
				return CLIP_STATE_CULLED;
			}
		}
	}

	void clipLineListAtCamera(
		VertexList & vertexList,
		ClipStateList & clipStateList,
		const CAMERA & camera)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 2);

		const size_t orig_size = clipStateList.size();

		for(size_t i = 0; i < orig_size; i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				// NOTE: clipLineAtCamera will change the length of clipStateList,
				//	so take care of invalid reference of clipStateList[i]
				CLIP_STATE state = clipLineAtCamera(
					vertexList[i * 2 + 0], vertexList[i * 2 + 1], camera, vertexList, clipStateList);

				clipStateList[i] = state; // ***
			}
		}

		_ASSERT(vertexList.size() == clipStateList.size() * 2);
	}

	CLIP_STATE clipLineIndexAtCamera(
		VertexList & vertexList,
		size_t v0_i,
		size_t v1_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList)
	{
		if(vertexList[v0_i].z > camera.nz)
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				return CLIP_STATE_NONE;
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				return CLIP_STATE_NONE;
			}
			else
			{
				retVertexIndexList.push_back(v0_i);
				retVertexIndexList.push_back(vertexList.size());
				vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v1_i], camera.nz));
				retClipStateList.push_back(CLIP_STATE_NONE);
				return CLIP_STATE_CULLED;
			}
		}
		else if(vertexList[v0_i].z == camera.nz)
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				return CLIP_STATE_NONE;
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				return CLIP_STATE_NONE;
			}
			else
			{
				return CLIP_STATE_CULLED;
			}
		}
		else
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				retVertexIndexList.push_back(vertexList.size());
				vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v1_i], camera.nz));
				retVertexIndexList.push_back(v1_i);
				retClipStateList.push_back(CLIP_STATE_NONE);
				return CLIP_STATE_CULLED;
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				return CLIP_STATE_CULLED;
			}
			else
			{
				return CLIP_STATE_CULLED;
			}
		}
	}

	void clipLineIndexListAtCamera(
		VertexList & vertexList,
		VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const CAMERA & camera)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 2);

		const size_t orig_size = clipStateList.size();

		for(size_t i = 0; i < orig_size; i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				CLIP_STATE state = clipLineIndexAtCamera(
					vertexList, vertexIndexList[i * 2 + 0], vertexIndexList[i * 2 + 1], camera, vertexIndexList, clipStateList);

				clipStateList[i] = state;
			}
		}

		_ASSERT(vertexIndexList.size() == clipStateList.size() * 2);
	}

	void cameraToScreenVertexSelf(
		Vec4<real> & vertex,
		const Vec2<real> & projection,
		const CPoint & centerPoint,
		const CSize & halfSize)
	{
		vertex.x = centerPoint.x + vertex.x * projection.x / vertex.z * halfSize.cx;
		vertex.y = centerPoint.y - vertex.y * projection.y / vertex.z * halfSize.cy;
	}

	void cameraToScreenLineList(
		VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec2<real> & projection,
		const CRect & viewport)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 2);

		CSize halfSize(viewport.Width() / 2, viewport.Height() / 2);

		CPoint centerPoint(viewport.left + halfSize.cx, viewport.top + halfSize.cy);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				cameraToScreenVertexSelf(vertexList[i * 2 + 0], projection, centerPoint, halfSize);
				cameraToScreenVertexSelf(vertexList[i * 2 + 1], projection, centerPoint, halfSize);
			}
		}
	}

	void cameraToScreenLineIndexList(
		VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec2<real> & projection,
		const CRect & viewport)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 2);

		CSize halfSize(viewport.Width() / 2, viewport.Height() / 2);

		CPoint centerPoint(viewport.left + halfSize.cx, viewport.top + halfSize.cy);

		VertexList::iterator vert_iter = vertexList.begin();
		for(; vert_iter != vertexList.end(); vert_iter++)
		{
			cameraToScreenVertexSelf(*vert_iter, projection, centerPoint, halfSize);
		}

		UNREFERENCED_PARAMETER(vertexIndexList);
		UNREFERENCED_PARAMETER(clipStateList);
	}

	CLIP_STATE clipLineAtScreen(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const CRect & viewport)
	{
		if(std::max(v0.x, v1.x) < viewport.left)
			return CLIP_STATE_CULLED;

		if(std::max(v0.y, v1.y) < viewport.top)
			return CLIP_STATE_CULLED;

		if(std::min(v0.x, v1.x) >= viewport.right)
			return CLIP_STATE_CULLED;

		if(std::min(v0.y, v1.y) >= viewport.bottom)
			return CLIP_STATE_CULLED;

		if(std::min(v0.x, v1.x) < viewport.left)
			return CLIP_STATE_SCLIPPED;

		if(std::min(v0.y, v1.y) < viewport.top)
			return CLIP_STATE_SCLIPPED;

		if(std::max(v0.x, v1.x) >= viewport.right)
			return CLIP_STATE_SCLIPPED;

		if(std::max(v0.y, v1.y) >= viewport.bottom)
			return CLIP_STATE_SCLIPPED;

		return CLIP_STATE_NONE;
	}

	void clipLineListAtScreen(
		const VertexList & vertexList,
		ClipStateList & clipStateList,
		const CRect & viewport)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 2);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				clipStateList[i] = clipLineAtScreen(
					vertexList[i * 2 + 0],
					vertexList[i * 2 + 1],
					viewport);
			}
		}
	}

	void clipLineIndexListAtScreen(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const CRect & viewport)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 2);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				clipStateList[i] = clipLineAtScreen(
					vertexList[vertexIndexList[i * 2 + 0]],
					vertexList[vertexIndexList[i * 2 + 1]],
					viewport);
			}
		}
	}

	void drawLineListZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 2);

		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawLineZBufferRW16(
				//	surface,
				//	zbuffer,
				//	vertexList[i * 2 + 0],
				//	vertexList[i * 2 + 1],
				//	color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedLineZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	vertexList[i * 2 + 0],
				//	vertexList[i * 2 + 1],
				//	color * 255);
				break;
			}
		}
	}

	void drawLineListZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 2);

		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawLineZBufferRW32(
					surface,
					zbuffer,
					vertexList[i * 2 + 0],
					vertexList[i * 2 + 1],
					color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedLineZBufferRW32(
					surface,
					clipper,
					zbuffer,
					vertexList[i * 2 + 0],
					vertexList[i * 2 + 1],
					color * 255);
				break;
			}
		}
	}

	void drawLineIndexListZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 2);

		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawLineZBufferRW16(
				//	surface,
				//	zbuffer,
				//	vertexList[vertexIndexList[i * 2 + 0]],
				//	vertexList[vertexIndexList[i * 2 + 1]],
				//	color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedLineZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	vertexList[vertexIndexList[i * 2 + 0]],
				//	vertexList[vertexIndexList[i * 2 + 1]],
				//	color * 255);
				break;
			}
		}
	}

	void drawLineIndexListZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 2);

		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawLineZBufferRW32(
					surface,
					zbuffer,
					vertexList[vertexIndexList[i * 2 + 0]],
					vertexList[vertexIndexList[i * 2 + 1]],
					color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedLineZBufferRW32(
					surface,
					clipper,
					zbuffer,
					vertexList[vertexIndexList[i * 2 + 0]],
					vertexList[vertexIndexList[i * 2 + 1]],
					color * 255);
				break;
			}
		}
	}

	CLIP_STATE clipTriangleBackfaceAtWorld(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & cameraPosition)
	{
		return vec3Dot(vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(cameraPosition, v0)) <= 0 ? CLIP_STATE_CULLED : CLIP_STATE_NONE;
	}

	void removeTriangleListBackfaceAtWorld(
		const VertexList & vertexList,
		ClipStateList & clipStateList,
		const Vec4<real> & cameraPosition)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				clipStateList[i] = clipTriangleBackfaceAtWorld(
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					cameraPosition);
			}
		}
	}

	void removeTriangleIndexListBackfaceAtWorld(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const Vec4<real> & cameraPosition)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				clipStateList[i] = clipTriangleBackfaceAtWorld(
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					cameraPosition);
			}
		}
	}

	void transformTriangleList(
		VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				vertexList[i * 3 + 0] *= mmat;
				vertexList[i * 3 + 1] *= mmat;
				vertexList[i * 3 + 2] *= mmat;
			}
		}
	}

	void transformTriangleIndexList(
		VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);

		transformVertexList(vertexList, mmat);
	}

	CLIP_STATE clipTriangleAtCameraNearZDouble(
		Vec4<real> v0,
		Vec4<real> v1,
		Vec4<real> v2,
		const CAMERA & camera,
		VertexList & retVertexList,
		ClipStateList & retClipStateList)
	{
		/**********************************************************************
		*		0
		* -------------
		*	2       1
		**********************************************************************/

		Vec4<real> v3 = vec3ClipZ(v0, v1, camera.nz);

		Vec4<real> v4 = vec3ClipZ(v0, v2, camera.nz);

		retVertexList.push_back(v0);
		retVertexList.push_back(v3);
		retVertexList.push_back(v4);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

	CLIP_STATE clipTriangleAtCameraNearZSingle(
		Vec4<real> v0,
		Vec4<real> v1,
		Vec4<real> v2,
		const CAMERA & camera,
		VertexList & retVertexList,
		ClipStateList & retClipStateList)
	{
		/**********************************************************************
		*	1       2
		* -------------
		*		0
		**********************************************************************/

		Vec4<real> v3 = vec3ClipZ(v0, v1, camera.nz);

		Vec4<real> v4 = vec3ClipZ(v0, v2, camera.nz);

		retVertexList.push_back(v3);
		retVertexList.push_back(v1);
		retVertexList.push_back(v2);
		retClipStateList.push_back(CLIP_STATE_NONE);

		retVertexList.push_back(v3);
		retVertexList.push_back(v2);
		retVertexList.push_back(v4);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

	CLIP_STATE clipTriangleAtCameraFarZ(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const CAMERA & camera)
	{
		return v0.z < camera.fz || v1.z < camera.fz || v2.z < camera.fz ? CLIP_STATE_NONE : CLIP_STATE_CULLED;
	}

	CLIP_STATE clipTriangleAtCamera(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const CAMERA & camera,
		VertexList & retVertexList,
		ClipStateList & retClipStateList)
	{
		if(CLIP_STATE_CULLED == clipTriangleAtCameraFarZ(v0, v1, v2, camera))
		{
			return CLIP_STATE_CULLED;
		}

		if(v0.z > camera.nz)
		{
			if(v1.z > camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleAtCameraNearZSingle(v2, v0, v1, camera, retVertexList, retClipStateList);
				}
			}
			else if(v1.z == camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleAtCameraNearZSingle(v2, v0, v1, camera, retVertexList, retClipStateList);
				}
			}
			else
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleAtCameraNearZSingle(v1, v2, v0, camera, retVertexList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return clipTriangleAtCameraNearZDouble(v0, v1, v2, camera, retVertexList, retClipStateList);
				}
				else
				{
					return clipTriangleAtCameraNearZDouble(v0, v1, v2, camera, retVertexList, retClipStateList);
				}
			}
		}
		else if(v0.z == camera.nz)
		{
			if(v1.z > camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleAtCameraNearZDouble(v1, v2, v0, camera, retVertexList, retClipStateList);
				}
			}
			else if(v1.z == camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleAtCameraNearZDouble(v2, v0, v1, camera, retVertexList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
		else
		{
			if(v1.z > camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleAtCameraNearZSingle(v0, v1, v2, camera, retVertexList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return clipTriangleAtCameraNearZDouble(v1, v2, v0, camera, retVertexList, retClipStateList);
				}
				else
				{
					return clipTriangleAtCameraNearZDouble(v1, v2, v0, camera, retVertexList, retClipStateList);
				}
			}
			else if(v1.z == camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleAtCameraNearZDouble(v2, v0, v1, camera, retVertexList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleAtCameraNearZDouble(v2, v0, v1, camera, retVertexList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
	}

	void clipTriangleListAtCamera(
		VertexList & vertexList,
		ClipStateList & clipStateList,
		const CAMERA & camera)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				CLIP_STATE state = clipTriangleAtCamera(
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					camera,
					vertexList,
					clipStateList);

				clipStateList[i] = state;
			}
		}

		_ASSERT(vertexList.size() == clipStateList.size() * 3);
	}

	CLIP_STATE clipTriangleIndexAtCameraNearZDouble(
		VertexList & vertexList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList)
	{
		_ASSERT(v0_i < vertexList.size());
		_ASSERT(v1_i < vertexList.size());
		_ASSERT(v2_i < vertexList.size());

		/**********************************************************************
		*		0
		* -------------
		*	2       1
		**********************************************************************/

		size_t v3_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v1_i], camera.nz));

		size_t v4_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v2_i], camera.nz));

		retVertexIndexList.push_back(v0_i);
		retVertexIndexList.push_back(v3_i);
		retVertexIndexList.push_back(v4_i);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

	CLIP_STATE clipTriangleIndexAtCameraNearZSingle(
		VertexList & vertexList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList)
	{
		_ASSERT(v0_i < vertexList.size());
		_ASSERT(v1_i < vertexList.size());
		_ASSERT(v2_i < vertexList.size());

		/**********************************************************************
		*	1       2
		* -------------
		*		0
		**********************************************************************/

		size_t v3_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v1_i], camera.nz));

		size_t v4_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v2_i], camera.nz));

		retVertexIndexList.push_back(v3_i);
		retVertexIndexList.push_back(v1_i);
		retVertexIndexList.push_back(v2_i);
		retClipStateList.push_back(CLIP_STATE_NONE);

		retVertexIndexList.push_back(v3_i);
		retVertexIndexList.push_back(v2_i);
		retVertexIndexList.push_back(v4_i);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

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
		ClipStateList & retClipStateList)
	{
		if(CLIP_STATE_CULLED == clipTriangleAtCameraFarZ(vertexList[v0_i], vertexList[v1_i], vertexList[v2_i], camera))
		{
			return CLIP_STATE_CULLED;
		}

		if(vertexList[v0_i].z > camera.nz)
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleIndexAtCameraNearZSingle(vertexList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleIndexAtCameraNearZSingle(vertexList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexAtCameraNearZSingle(vertexList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return clipTriangleIndexAtCameraNearZDouble(vertexList, v0_i, v1_i, v2_i, camera, retVertexIndexList, retClipStateList);
				}
				else
				{
					return clipTriangleIndexAtCameraNearZDouble(vertexList, v0_i, v1_i, v2_i, camera, retVertexIndexList, retClipStateList);
				}
			}
		}
		else if(vertexList[v0_i].z == camera.nz)
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleIndexAtCameraNearZDouble(vertexList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexAtCameraNearZDouble(vertexList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
		else
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexAtCameraNearZSingle(vertexList, v0_i, v1_i, v2_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return clipTriangleIndexAtCameraNearZDouble(vertexList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
				else
				{
					return clipTriangleIndexAtCameraNearZDouble(vertexList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexAtCameraNearZDouble(vertexList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexAtCameraNearZDouble(vertexList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
	}

	void clipTriangleIndexListAtCamera(
		VertexList & vertexList,
		VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const CAMERA & camera)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				CLIP_STATE state = clipTriangleIndexAtCamera(
					vertexList,
					vertexIndexList[i * 3 + 0],
					vertexIndexList[i * 3 + 1],
					vertexIndexList[i * 3 + 2],
					camera,
					vertexIndexList,
					clipStateList);

				clipStateList[i] = state;
			}
		}

		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
	}

	void cameraToScreenTriangleList(
		VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec2<real> & projection,
		const CRect & viewport)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);

		CSize halfSize(viewport.Width() / 2, viewport.Height() / 2);

		CPoint centerPoint(viewport.left + halfSize.cx, viewport.top + halfSize.cy);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				cameraToScreenVertexSelf(vertexList[i * 3 + 0], projection, centerPoint, halfSize);
				cameraToScreenVertexSelf(vertexList[i * 3 + 1], projection, centerPoint, halfSize);
				cameraToScreenVertexSelf(vertexList[i * 3 + 2], projection, centerPoint, halfSize);
			}
		}
	}

	void cameraToScreenTriangleIndexList(
		VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec2<real> & projection,
		const CRect & viewport)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);

		CSize halfSize(viewport.Width() / 2, viewport.Height() / 2);

		CPoint centerPoint(viewport.left + halfSize.cx, viewport.top + halfSize.cy);

		VertexList::iterator vert_iter = vertexList.begin();
		for(; vert_iter != vertexList.end(); vert_iter++)
		{
			cameraToScreenVertexSelf(*vert_iter, projection, centerPoint, halfSize);
		}

		UNREFERENCED_PARAMETER(vertexIndexList);
		UNREFERENCED_PARAMETER(clipStateList);
	}

	CLIP_STATE clipTriangleAtScreen(
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const CRect & viewport)
	{
		if(max(v0.x, v1.x, v2.x) < viewport.left)
			return CLIP_STATE_CULLED;

		if(max(v0.y, v1.y, v2.y) < viewport.top)
			return CLIP_STATE_CULLED;

		if(min(v0.x, v1.x, v2.x) >= viewport.right)
			return CLIP_STATE_CULLED;

		if(min(v0.y, v1.y, v2.y) >= viewport.bottom)
			return CLIP_STATE_CULLED;

		if(min(v0.x, v1.x, v2.x) < viewport.left)
			return CLIP_STATE_SCLIPPED;

		if(min(v0.y, v1.y, v2.y) < viewport.top)
			return CLIP_STATE_SCLIPPED;

		if(max(v0.x, v1.x, v2.x) >= viewport.right)
			return CLIP_STATE_SCLIPPED;

		if(max(v0.y, v1.y, v2.y) >= viewport.bottom)
			return CLIP_STATE_SCLIPPED;

		return CLIP_STATE_NONE;
	}

	void clipTriangleListAtScreen(
		const VertexList & vertexList,
		ClipStateList & clipStateList,
		const CRect & viewport)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				clipStateList[i] = clipTriangleAtScreen(
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					viewport);
			}
		}
	}

	void clipTriangleIndexListAtScreen(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const CRect & viewport)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				clipStateList[i] = clipTriangleAtScreen(
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					viewport);
			}
		}
	}

	void drawTriangleListWireZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);

		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawLineZBufferRW16(surface, zbuffer, vertexList[i * 3 + 0], vertexList[i * 3 + 1], color * 255);
				//drawLineZBufferRW16(surface, zbuffer, vertexList[i * 3 + 1], vertexList[i * 3 + 2], color * 255);
				//drawLineZBufferRW16(surface, zbuffer, vertexList[i * 3 + 2], vertexList[i * 3 + 0], color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedLineZBufferRW16(surface, clipper, zbuffer, vertexList[i * 3 + 0], vertexList[i * 3 + 1], color * 255);
				//drawClippedLineZBufferRW16(surface, clipper, zbuffer, vertexList[i * 3 + 1], vertexList[i * 3 + 2], color * 255);
				//drawClippedLineZBufferRW16(surface, clipper, zbuffer, vertexList[i * 3 + 2], vertexList[i * 3 + 0], color * 255);
				break;
			}
		}
	}

	void drawTriangleListWireZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);

		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawLineZBufferRW32(surface, zbuffer, vertexList[i * 3 + 0], vertexList[i * 3 + 1], color * 255);
				drawLineZBufferRW32(surface, zbuffer, vertexList[i * 3 + 1], vertexList[i * 3 + 2], color * 255);
				drawLineZBufferRW32(surface, zbuffer, vertexList[i * 3 + 2], vertexList[i * 3 + 0], color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedLineZBufferRW32(surface, clipper, zbuffer, vertexList[i * 3 + 0], vertexList[i * 3 + 1], color * 255);
				drawClippedLineZBufferRW32(surface, clipper, zbuffer, vertexList[i * 3 + 1], vertexList[i * 3 + 2], color * 255);
				drawClippedLineZBufferRW32(surface, clipper, zbuffer, vertexList[i * 3 + 2], vertexList[i * 3 + 0], color * 255);
				break;
			}
		}
	}

	void drawTriangleIndexListWireZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);

		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawLineZBufferRW16(surface, zbuffer, vertexList[vertexIndexList[i * 3 + 0]], vertexList[vertexIndexList[i * 3 + 1]], color * 255);
				//drawLineZBufferRW16(surface, zbuffer, vertexList[vertexIndexList[i * 3 + 1]], vertexList[vertexIndexList[i * 3 + 2]], color * 255);
				//drawLineZBufferRW16(surface, zbuffer, vertexList[vertexIndexList[i * 3 + 2]], vertexList[vertexIndexList[i * 3 + 0]], color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedLineZBufferRW16(surface, clipper, zbuffer, vertexList[vertexIndexList[i * 3 + 0]], vertexList[vertexIndexList[i * 3 + 1]], color * 255);
				//drawClippedLineZBufferRW16(surface, clipper, zbuffer, vertexList[vertexIndexList[i * 3 + 1]], vertexList[vertexIndexList[i * 3 + 2]], color * 255);
				//drawClippedLineZBufferRW16(surface, clipper, zbuffer, vertexList[vertexIndexList[i * 3 + 2]], vertexList[vertexIndexList[i * 3 + 0]], color * 255);
				break;
			}
		}
	}

	void drawTriangleIndexListWireZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);

		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawLineZBufferRW32(surface, zbuffer, vertexList[vertexIndexList[i * 3 + 0]], vertexList[vertexIndexList[i * 3 + 1]], color * 255);
				drawLineZBufferRW32(surface, zbuffer, vertexList[vertexIndexList[i * 3 + 1]], vertexList[vertexIndexList[i * 3 + 2]], color * 255);
				drawLineZBufferRW32(surface, zbuffer, vertexList[vertexIndexList[i * 3 + 2]], vertexList[vertexIndexList[i * 3 + 0]], color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedLineZBufferRW32(surface, clipper, zbuffer, vertexList[vertexIndexList[i * 3 + 0]], vertexList[vertexIndexList[i * 3 + 1]], color * 255);
				drawClippedLineZBufferRW32(surface, clipper, zbuffer, vertexList[vertexIndexList[i * 3 + 1]], vertexList[vertexIndexList[i * 3 + 2]], color * 255);
				drawClippedLineZBufferRW32(surface, clipper, zbuffer, vertexList[vertexIndexList[i * 3 + 2]], vertexList[vertexIndexList[i * 3 + 0]], color * 255);
				break;
			}
		}
	}

	void drawTriangleListZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);

		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleZBufferRW16(
				//	surface,
				//	zbuffer,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	color * 255);
				break;
			}
		}
	}

	void drawTriangleListZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);

		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleZBufferRW32(
					surface,
					zbuffer,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleZBufferRW32(
					surface,
					clipper,
					zbuffer,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					color * 255);
				break;
			}
		}
	}

	void drawTriangleIndexListZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);

		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleZBufferRW16(
				//	surface,
				//	zbuffer,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	color * 255);
				break;
			}
		}
	}

	void drawTriangleIndexListZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Vec4<real> & color)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);

		_ASSERT(rgbaIsValid<real>(color, 0, 1));

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleZBufferRW32(
					surface,
					zbuffer,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleZBufferRW32(
					surface,
					clipper,
					zbuffer,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					color * 255);
				break;
			}
		}
	}

	void lightTriangleListAtWorld(
		const VertexList & vertexList,
		const VertexList & normalList,
		const ClipStateList & clipStateList,
		const LightList & lightList,
		const MATERIAL & material,
		ColorList & retColorList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(normalList.size() == clipStateList.size() * 3);
		_ASSERT(retColorList.size() == clipStateList.size() * 3);

		LightList::const_iterator light_iter = lightList.begin();
		for(; light_iter != lightList.end(); light_iter++)
		{
			switch(light_iter->type)
			{
			case LT_AMBIENT:
				for(size_t i = 0; i < clipStateList.size(); i++)
				{
					if(CLIP_STATE_NONE == clipStateList[i])
					{
						retColorList[i * 3 + 0] += LightListContext::lightVertexAmbient(*light_iter, material, vertexList[i * 3 + 0], normalList[i * 3 + 0]);
						retColorList[i * 3 + 1] += LightListContext::lightVertexAmbient(*light_iter, material, vertexList[i * 3 + 1], normalList[i * 3 + 1]);
						retColorList[i * 3 + 2] += LightListContext::lightVertexAmbient(*light_iter, material, vertexList[i * 3 + 2], normalList[i * 3 + 2]);
					}
				}
				break;

			case LT_DIRECTIONAL:
				for(size_t i = 0; i < clipStateList.size(); i++)
				{
					if(CLIP_STATE_NONE == clipStateList[i])
					{
						retColorList[i * 3 + 0] += LightListContext::lightVertexDirectional(*light_iter, material, vertexList[i * 3 + 0], normalList[i * 3 + 0]);
						retColorList[i * 3 + 1] += LightListContext::lightVertexDirectional(*light_iter, material, vertexList[i * 3 + 1], normalList[i * 3 + 1]);
						retColorList[i * 3 + 2] += LightListContext::lightVertexDirectional(*light_iter, material, vertexList[i * 3 + 2], normalList[i * 3 + 2]);
					}
				}
				break;

			case LT_POINT:
				for(size_t i = 0; i < clipStateList.size(); i++)
				{
					if(CLIP_STATE_NONE == clipStateList[i])
					{
						retColorList[i * 3 + 0] += LightListContext::lightVertexPoint(*light_iter, material, vertexList[i * 3 + 0], normalList[i * 3 + 0]);
						retColorList[i * 3 + 1] += LightListContext::lightVertexPoint(*light_iter, material, vertexList[i * 3 + 1], normalList[i * 3 + 1]);
						retColorList[i * 3 + 2] += LightListContext::lightVertexPoint(*light_iter, material, vertexList[i * 3 + 2], normalList[i * 3 + 2]);
					}
				}
				break;

			default:
				break;
			}
		}
	}

	void lightTriangleIndexListAtWorld(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const VertexList & normalList,
		const ClipStateList & clipStateList,
		const LightList & lightList,
		const MATERIAL & material,
		ColorList & retColorList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == normalList.size());
		_ASSERT(vertexList.size() == retColorList.size());

		LightList::const_iterator light_iter = lightList.begin();
		for(; light_iter != lightList.end(); light_iter++)
		{
			switch(light_iter->type)
			{
			case LT_AMBIENT:
				for(size_t i = 0; i < vertexList.size(); i++)
				{
					retColorList[i] += LightListContext::lightVertexAmbient(*light_iter, material, vertexList[i], normalList[i]);
				}
				break;

			case LT_DIRECTIONAL:
				for(size_t i = 0; i < vertexList.size(); i++)
				{
					retColorList[i] += LightListContext::lightVertexDirectional(*light_iter, material, vertexList[i], normalList[i]);
				}
				break;

			case LT_POINT:
				for(size_t i = 0; i < vertexList.size(); i++)
				{
					retColorList[i] += LightListContext::lightVertexPoint(*light_iter, material, vertexList[i], normalList[i]);
				}
				break;

			default:
				break;
			}
		}
	}

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
		ClipStateList & retClipStateList)
	{
		/**********************************************************************
		*		0
		* -------------
		*	2       1
		**********************************************************************/

		Vec4<real> v3 = vec3ClipZ(v0, v1, camera.nz);
		Vec4<real> c3 = vec3Intersect(c0, c1, v0.z, v1.z, camera.nz);

		Vec4<real> v4 = vec3ClipZ(v0, v2, camera.nz);
		Vec4<real> c4 = vec3Intersect(c0, c2, v0.z, v2.z, camera.nz);

		retVertexList.push_back(v0);
		retVertexList.push_back(v3);
		retVertexList.push_back(v4);
		retColorList.push_back(c0);
		retColorList.push_back(c3);
		retColorList.push_back(c4);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

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
		ClipStateList & retClipStateList)
	{
		/**********************************************************************
		*	1       2
		* -------------
		*		0
		**********************************************************************/

		Vec4<real> v3 = vec3ClipZ(v0, v1, camera.nz);
		Vec4<real> c3 = vec3Intersect(c0, c1, v0.z, v1.z, camera.nz);

		Vec4<real> v4 = vec3ClipZ(v0, v2, camera.nz);
		Vec4<real> c4 = vec3Intersect(c0, c2, v0.z, v2.z, camera.nz);

		retVertexList.push_back(v3);
		retVertexList.push_back(v1);
		retVertexList.push_back(v2);
		retColorList.push_back(c3);
		retColorList.push_back(c1);
		retColorList.push_back(c2);
		retClipStateList.push_back(CLIP_STATE_NONE);

		retVertexList.push_back(v3);
		retVertexList.push_back(v2);
		retVertexList.push_back(v4);
		retColorList.push_back(c3);
		retColorList.push_back(c2);
		retColorList.push_back(c4);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

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
		ClipStateList & retClipStateList)
	{
		if(CLIP_STATE_CULLED == clipTriangleAtCameraFarZ(v0, v1, v2, camera))
		{
			return CLIP_STATE_CULLED;
		}

		if(v0.z > camera.nz)
		{
			if(v1.z > camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleGouraudAtCameraNearZSingle(v2, v0, v1, c2, c0, c1, camera, retVertexList, retColorList, retClipStateList);
				}
			}
			else if(v1.z == camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleGouraudAtCameraNearZSingle(v2, v0, v1, c2, c0, c1, camera, retVertexList, retColorList, retClipStateList);
				}
			}
			else
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleGouraudAtCameraNearZSingle(v1, v2, v0, c1, c2, c0, camera, retVertexList, retColorList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return clipTriangleGouraudAtCameraNearZDouble(v0, v1, v2, c0, c1, c2, camera, retVertexList, retColorList, retClipStateList);
				}
				else
				{
					return clipTriangleGouraudAtCameraNearZDouble(v0, v1, v2, c0, c1, c2, camera, retVertexList, retColorList, retClipStateList);
				}
			}
		}
		else if(v0.z == camera.nz)
		{
			if(v1.z > camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleGouraudAtCameraNearZDouble(v1, v2, v0, c1, c2, c0, camera, retVertexList, retColorList, retClipStateList);
				}
			}
			else if(v1.z == camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleGouraudAtCameraNearZDouble(v2, v0, v1, c2, c0, c1, camera, retVertexList, retColorList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
		else
		{
			if(v1.z > camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleGouraudAtCameraNearZSingle(v0, v1, v2, c0, c1, c2, camera, retVertexList, retColorList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return clipTriangleGouraudAtCameraNearZDouble(v1, v2, v0, c1, c2, c0, camera, retVertexList, retColorList, retClipStateList);
				}
				else
				{
					return clipTriangleGouraudAtCameraNearZDouble(v1, v2, v0, c1, c2, c0, camera, retVertexList, retColorList, retClipStateList);
				}
			}
			else if(v1.z == camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleGouraudAtCameraNearZDouble(v2, v0, v1, c2, c0, c1, camera, retVertexList, retColorList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleGouraudAtCameraNearZDouble(v2, v0, v1, c2, c0, c1, camera, retVertexList, retColorList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
	}

	void clipTriangleListGouraudAtCamera(
		VertexList & vertexList,
		ColorList & colorList,
		ClipStateList & clipStateList,
		const CAMERA & camera)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(colorList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				CLIP_STATE state = clipTriangleGouraudAtCamera(
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					colorList[i * 3 + 0],
					colorList[i * 3 + 1],
					colorList[i * 3 + 2],
					camera,
					vertexList,
					colorList,
					clipStateList);

				clipStateList[i] = state;
			}
		}

		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(colorList.size() == clipStateList.size() * 3);
	}

	CLIP_STATE clipTriangleIndexGouraudAtCameraNearZDouble(
		VertexList & vertexList,
		ColorList & colorList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList)
	{
		_ASSERT(v0_i < vertexList.size());
		_ASSERT(v1_i < vertexList.size());
		_ASSERT(v2_i < vertexList.size());

		/**********************************************************************
		*		0
		* -------------
		*	2       1
		**********************************************************************/

		size_t v3_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v1_i], camera.nz));
		colorList.push_back(vec3Intersect(colorList[v0_i], colorList[v1_i], vertexList[v0_i].z, vertexList[v1_i].z, camera.nz));

		size_t v4_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v2_i], camera.nz));
		colorList.push_back(vec3Intersect(colorList[v0_i], colorList[v2_i], vertexList[v0_i].z, vertexList[v2_i].z, camera.nz));

		retVertexIndexList.push_back(v0_i);
		retVertexIndexList.push_back(v3_i);
		retVertexIndexList.push_back(v4_i);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

	CLIP_STATE clipTriangleIndexGouraudAtCameraNearZSingle(
		VertexList & vertexList,
		ColorList & colorList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList)
	{
		_ASSERT(v0_i < vertexList.size());
		_ASSERT(v1_i < vertexList.size());
		_ASSERT(v2_i < vertexList.size());

		/**********************************************************************
		*	1       2
		* -------------
		*		0
		**********************************************************************/

		size_t v3_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v1_i], camera.nz));
		colorList.push_back(vec3Intersect(colorList[v0_i], colorList[v1_i], vertexList[v0_i].z, vertexList[v1_i].z, camera.nz));

		size_t v4_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v2_i], camera.nz));
		colorList.push_back(vec3Intersect(colorList[v0_i], colorList[v2_i], vertexList[v0_i].z, vertexList[v2_i].z, camera.nz));

		retVertexIndexList.push_back(v3_i);
		retVertexIndexList.push_back(v1_i);
		retVertexIndexList.push_back(v2_i);
		retClipStateList.push_back(CLIP_STATE_NONE);

		retVertexIndexList.push_back(v3_i);
		retVertexIndexList.push_back(v2_i);
		retVertexIndexList.push_back(v4_i);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

	CLIP_STATE clipTriangleIndexGouraudAtCamera(
		VertexList & vertexList,
		ColorList & colorList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList)
	{
		if(CLIP_STATE_CULLED == clipTriangleAtCameraFarZ(vertexList[v0_i], vertexList[v1_i], vertexList[v2_i], camera))
		{
			return CLIP_STATE_CULLED;
		}

		if(vertexList[v0_i].z > camera.nz)
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleIndexGouraudAtCameraNearZSingle(vertexList, colorList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleIndexGouraudAtCameraNearZSingle(vertexList, colorList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexGouraudAtCameraNearZSingle(vertexList, colorList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return clipTriangleIndexGouraudAtCameraNearZDouble(vertexList, colorList, v0_i, v1_i, v2_i, camera, retVertexIndexList, retClipStateList);
				}
				else
				{
					return clipTriangleIndexGouraudAtCameraNearZDouble(vertexList, colorList, v0_i, v1_i, v2_i, camera, retVertexIndexList, retClipStateList);
				}
			}
		}
		else if(vertexList[v0_i].z == camera.nz)
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleIndexGouraudAtCameraNearZDouble(vertexList, colorList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexGouraudAtCameraNearZDouble(vertexList, colorList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
		else
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexGouraudAtCameraNearZSingle(vertexList, colorList, v0_i, v1_i, v2_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return clipTriangleIndexGouraudAtCameraNearZDouble(vertexList, colorList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
				else
				{
					return clipTriangleIndexGouraudAtCameraNearZDouble(vertexList, colorList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexGouraudAtCameraNearZDouble(vertexList, colorList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexGouraudAtCameraNearZDouble(vertexList, colorList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
	}

	void clipTriangleIndexListGouraudAtCamera(
		VertexList & vertexList,
		VertexIndexList & vertexIndexList,
		ColorList & colorList,
		ClipStateList & clipStateList,
		const CAMERA & camera)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == colorList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				CLIP_STATE state = clipTriangleIndexGouraudAtCamera(
					vertexList,
					colorList,
					vertexIndexList[i * 3 + 0],
					vertexIndexList[i * 3 + 1],
					vertexIndexList[i * 3 + 2],
					camera,
					vertexIndexList,
					clipStateList);

				clipStateList[i] = state;
			}
		}

		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == colorList.size());
	}

	void drawTriangleListGouraudZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ColorList & colorList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(colorList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleGouraudZBufferRW16(
				//	surface,
				//	zbuffer,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	rgbaSaturate<real>(colorList[i * 3 + 0] * 255, 255),
				//	rgbaSaturate<real>(colorList[i * 3 + 1] * 255, 255),
				//	rgbaSaturate<real>(colorList[i * 3 + 2] * 255, 255));
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleGouraudZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	rgbaSaturate<real>(colorList[i * 3 + 0] * 255, 255),
				//	rgbaSaturate<real>(colorList[i * 3 + 1] * 255, 255),
				//	rgbaSaturate<real>(colorList[i * 3 + 2] * 255, 255));
				break;
			}
		}
	}

	void drawTriangleListGouraudZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const ColorList & colorList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(colorList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleGouraudZBufferRW32(
					surface,
					zbuffer,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					rgbaSaturate<real>(colorList[i * 3 + 0] * 255, 255),
					rgbaSaturate<real>(colorList[i * 3 + 1] * 255, 255),
					rgbaSaturate<real>(colorList[i * 3 + 2] * 255, 255));
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleGouraudZBufferRW32(
					surface,
					clipper,
					zbuffer,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					rgbaSaturate<real>(colorList[i * 3 + 0] * 255, 255),
					rgbaSaturate<real>(colorList[i * 3 + 1] * 255, 255),
					rgbaSaturate<real>(colorList[i * 3 + 2] * 255, 255));
				break;
			}
		}
	}

	void drawTriangleIndexListGouraudZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ColorList & colorList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == colorList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleGouraudZBufferRW16(
				//	surface,
				//	zbuffer,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 0]] * 255, 255),
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 1]] * 255, 255),
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 2]] * 255, 255));
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleGouraudZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 0]] * 255, 255),
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 1]] * 255, 255),
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 2]] * 255, 255));
				break;
			}
		}
	}

	void drawTriangleIndexListGouraudZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ColorList & colorList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == colorList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleGouraudZBufferRW32(
					surface,
					zbuffer,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 0]] * 255, 255),
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 1]] * 255, 255),
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 2]] * 255, 255));
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleGouraudZBufferRW32(
					surface,
					clipper,
					zbuffer,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 0]] * 255, 255),
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 1]] * 255, 255),
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 2]] * 255, 255));
				break;
			}
		}
	}

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
		ClipStateList & retClipStateList)
	{
		/**********************************************************************
		*		0
		* -------------
		*	2       1
		**********************************************************************/

		Vec4<real> v3 = vec3ClipZ(v0, v1, camera.nz);
		Vec2<real> t3 = vec2Intersect(t0, t1, v0.z, v1.z, camera.nz);

		Vec4<real> v4 = vec3ClipZ(v0, v2, camera.nz);
		Vec2<real> t4 = vec2Intersect(t0, t2, v0.z, v2.z, camera.nz);

		retVertexList.push_back(v0);
		retVertexList.push_back(v3);
		retVertexList.push_back(v4);
		retUVList.push_back(t0);
		retUVList.push_back(t3);
		retUVList.push_back(t4);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

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
		ClipStateList & retClipStateList)
	{
		/**********************************************************************
		*	1       2
		* -------------
		*		0
		**********************************************************************/

		Vec4<real> v3 = vec3ClipZ(v0, v1, camera.nz);
		Vec2<real> t3 = vec2Intersect(t0, t1, v0.z, v1.z, camera.nz);

		Vec4<real> v4 = vec3ClipZ(v0, v2, camera.nz);
		Vec2<real> t4 = vec2Intersect(t0, t2, v0.z, v2.z, camera.nz);

		retVertexList.push_back(v3);
		retVertexList.push_back(v1);
		retVertexList.push_back(v2);
		retUVList.push_back(t3);
		retUVList.push_back(t1);
		retUVList.push_back(t2);
		retClipStateList.push_back(CLIP_STATE_NONE);

		retVertexList.push_back(v3);
		retVertexList.push_back(v2);
		retVertexList.push_back(v4);
		retUVList.push_back(t3);
		retUVList.push_back(t2);
		retUVList.push_back(t4);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

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
		ClipStateList & retClipStateList)
	{
		if(CLIP_STATE_CULLED == clipTriangleAtCameraFarZ(v0, v1, v2, camera))
		{
			return CLIP_STATE_CULLED;
		}

		if(v0.z > camera.nz)
		{
			if(v1.z > camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleTextureAtCameraNearZSingle(v2, v0, v1, t2, t0, t1, camera, retVertexList, retUVList, retClipStateList);
				}
			}
			else if(v1.z == camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleTextureAtCameraNearZSingle(v2, v0, v1, t2, t0, t1, camera, retVertexList, retUVList, retClipStateList);
				}
			}
			else
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleTextureAtCameraNearZSingle(v1, v2, v0, t1, t2, t0, camera, retVertexList, retUVList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return clipTriangleTextureAtCameraNearZDouble(v0, v1, v2, t0, t1, t2, camera, retVertexList, retUVList, retClipStateList);
				}
				else
				{
					return clipTriangleTextureAtCameraNearZDouble(v0, v1, v2, t0, t1, t2, camera, retVertexList, retUVList, retClipStateList);
				}
			}
		}
		else if(v0.z == camera.nz)
		{
			if(v1.z > camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleTextureAtCameraNearZDouble(v1, v2, v0, t1, t2, t0, camera, retVertexList, retUVList, retClipStateList);
				}
			}
			else if(v1.z == camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleTextureAtCameraNearZDouble(v2, v0, v1, t2, t0, t1, camera, retVertexList, retUVList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
		else
		{
			if(v1.z > camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleTextureAtCameraNearZSingle(v0, v1, v2, t0, t1, t2, camera, retVertexList, retUVList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return clipTriangleTextureAtCameraNearZDouble(v1, v2, v0, t1, t2, t0, camera, retVertexList, retUVList, retClipStateList);
				}
				else
				{
					return clipTriangleTextureAtCameraNearZDouble(v1, v2, v0, t1, t2, t0, camera, retVertexList, retUVList, retClipStateList);
				}
			}
			else if(v1.z == camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleTextureAtCameraNearZDouble(v2, v0, v1, t2, t0, t1, camera, retVertexList, retUVList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleTextureAtCameraNearZDouble(v2, v0, v1, t2, t0, t1, camera, retVertexList, retUVList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
	}

	void clipTriangleListTextureAtCamera(
		VertexList & vertexList,
		UVList & uvList,
		ClipStateList & clipStateList,
		const CAMERA & camera)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				CLIP_STATE state = clipTriangleTextureAtCamera(
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					uvList[i * 3 + 0],
					uvList[i * 3 + 1],
					uvList[i * 3 + 2],
					camera,
					vertexList,
					uvList,
					clipStateList);

				clipStateList[i] = state;
			}
		}

		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);
	}

	CLIP_STATE clipTriangleIndexTextureAtCameraNearZDouble(
		VertexList & vertexList,
		UVList & uvList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList)
	{
		_ASSERT(v0_i < vertexList.size());
		_ASSERT(v1_i < vertexList.size());
		_ASSERT(v2_i < vertexList.size());

		/**********************************************************************
		*		0
		* -------------
		*	2       1
		**********************************************************************/

		size_t v3_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v1_i], camera.nz));
		uvList.push_back(vec2Intersect(uvList[v0_i], uvList[v1_i], vertexList[v0_i].z, vertexList[v1_i].z, camera.nz));

		size_t v4_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v2_i], camera.nz));
		uvList.push_back(vec2Intersect(uvList[v0_i], uvList[v2_i], vertexList[v0_i].z, vertexList[v2_i].z, camera.nz));

		retVertexIndexList.push_back(v0_i);
		retVertexIndexList.push_back(v3_i);
		retVertexIndexList.push_back(v4_i);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

	CLIP_STATE clipTriangleIndexTextureAtCameraNearZSingle(
		VertexList & vertexList,
		UVList & uvList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList)
	{
		_ASSERT(v0_i < vertexList.size());
		_ASSERT(v1_i < vertexList.size());
		_ASSERT(v2_i < vertexList.size());

		/**********************************************************************
		*	1       2
		* -------------
		*		0
		**********************************************************************/

		size_t v3_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v1_i], camera.nz));
		uvList.push_back(vec2Intersect(uvList[v0_i], uvList[v1_i], vertexList[v0_i].z, vertexList[v1_i].z, camera.nz));

		size_t v4_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v2_i], camera.nz));
		uvList.push_back(vec2Intersect(uvList[v0_i], uvList[v2_i], vertexList[v0_i].z, vertexList[v2_i].z, camera.nz));

		retVertexIndexList.push_back(v3_i);
		retVertexIndexList.push_back(v1_i);
		retVertexIndexList.push_back(v2_i);
		retClipStateList.push_back(CLIP_STATE_NONE);

		retVertexIndexList.push_back(v3_i);
		retVertexIndexList.push_back(v2_i);
		retVertexIndexList.push_back(v4_i);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

	CLIP_STATE clipTriangleIndexTextureAtCamera(
		VertexList & vertexList,
		UVList & uvList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList)
	{
		if(CLIP_STATE_CULLED == clipTriangleAtCameraFarZ(vertexList[v0_i], vertexList[v1_i], vertexList[v2_i], camera))
		{
			return CLIP_STATE_CULLED;
		}

		if(vertexList[v0_i].z > camera.nz)
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleIndexTextureAtCameraNearZSingle(vertexList, uvList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleIndexTextureAtCameraNearZSingle(vertexList, uvList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexTextureAtCameraNearZSingle(vertexList, uvList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return clipTriangleIndexTextureAtCameraNearZDouble(vertexList, uvList, v0_i, v1_i, v2_i, camera, retVertexIndexList, retClipStateList);
				}
				else
				{
					return clipTriangleIndexTextureAtCameraNearZDouble(vertexList, uvList, v0_i, v1_i, v2_i, camera, retVertexIndexList, retClipStateList);
				}
			}
		}
		else if(vertexList[v0_i].z == camera.nz)
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleIndexTextureAtCameraNearZDouble(vertexList, uvList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexTextureAtCameraNearZDouble(vertexList, uvList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
		else
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexTextureAtCameraNearZSingle(vertexList, uvList, v0_i, v1_i, v2_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return clipTriangleIndexTextureAtCameraNearZDouble(vertexList, uvList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
				else
				{
					return clipTriangleIndexTextureAtCameraNearZDouble(vertexList, uvList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexTextureAtCameraNearZDouble(vertexList, uvList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexTextureAtCameraNearZDouble(vertexList, uvList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
	}

	void clipTriangleIndexListTextureAtCamera(
		VertexList & vertexList,
		VertexIndexList & vertexIndexList,
		UVList & uvList,
		ClipStateList & clipStateList,
		const CAMERA & camera)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				CLIP_STATE state = clipTriangleIndexTextureAtCamera(
					vertexList,
					uvList,
					vertexIndexList[i * 3 + 0],
					vertexIndexList[i * 3 + 1],
					vertexIndexList[i * 3 + 2],
					camera,
					vertexIndexList,
					clipStateList);

				clipStateList[i] = state;
			}
		}

		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());
	}

	void drawTriangleListTextureZBufferW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleTextureZBufferW16(
				//	surface,
				//	zbuffer,
				//	texture,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	uvList[i * 3 + 0] * texture_expend,
				//	uvList[i * 3 + 1] * texture_expend,
				//	uvList[i * 3 + 2] * texture_expend));
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleTextureZBufferW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	texture,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	uvList[i * 3 + 0] * texture_expend,
				//	uvList[i * 3 + 1] * texture_expend,
				//	uvList[i * 3 + 2] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleListTextureZBufferW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleTextureZBufferW32(
					surface,
					zbuffer,
					texture,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					uvList[i * 3 + 0] * texture_expend,
					uvList[i * 3 + 1] * texture_expend,
					uvList[i * 3 + 2] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleTextureZBufferW32(
					surface,
					clipper,
					zbuffer,
					texture,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					uvList[i * 3 + 0] * texture_expend,
					uvList[i * 3 + 1] * texture_expend,
					uvList[i * 3 + 2] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleIndexListTextureZBufferW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleTextureZBufferW16(
				//	surface,
				//	zbuffer,
				//	texture,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleTextureZBufferW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	texture,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleIndexListTextureZBufferW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleTextureZBufferW32(
					surface,
					zbuffer,
					texture,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleTextureZBufferW32(
					surface,
					clipper,
					zbuffer,
					texture,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleListTexturePerspectiveLPZBufferW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleTexturePerspectiveLPZBufferW16(
				//	surface,
				//	zbuffer,
				//	texture,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	uvList[i * 3 + 0] * texture_expend,
				//	uvList[i * 3 + 1] * texture_expend,
				//	uvList[i * 3 + 2] * texture_expend));
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleTexturePerspectiveLPZBufferW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	texture,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	uvList[i * 3 + 0] * texture_expend,
				//	uvList[i * 3 + 1] * texture_expend,
				//	uvList[i * 3 + 2] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleListTexturePerspectiveLPZBufferW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleTexturePerspectiveLPZBufferW32(
					surface,
					zbuffer,
					texture,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					uvList[i * 3 + 0] * texture_expend,
					uvList[i * 3 + 1] * texture_expend,
					uvList[i * 3 + 2] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleTexturePerspectiveLPZBufferW32(
					surface,
					clipper,
					zbuffer,
					texture,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					uvList[i * 3 + 0] * texture_expend,
					uvList[i * 3 + 1] * texture_expend,
					uvList[i * 3 + 2] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleIndexListTexturePerspectiveLPZBufferW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleTexturePerspectiveLPZBufferW16(
				//	surface,
				//	zbuffer,
				//	texture,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleTexturePerspectiveLPZBufferW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	texture,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleIndexListTexturePerspectiveLPZBufferW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleTexturePerspectiveLPZBufferW32(
					surface,
					zbuffer,
					texture,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleTexturePerspectiveLPZBufferW32(
					surface,
					clipper,
					zbuffer,
					texture,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleListTextureZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleTextureZBufferRW16(
				//	surface,
				//	zbuffer,
				//	texture,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	uvList[i * 3 + 0] * texture_expend,
				//	uvList[i * 3 + 1] * texture_expend,
				//	uvList[i * 3 + 2] * texture_expend));
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleTextureZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	texture,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	uvList[i * 3 + 0] * texture_expend,
				//	uvList[i * 3 + 1] * texture_expend,
				//	uvList[i * 3 + 2] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleListTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleTextureZBufferRW32(
					surface,
					zbuffer,
					texture,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					uvList[i * 3 + 0] * texture_expend,
					uvList[i * 3 + 1] * texture_expend,
					uvList[i * 3 + 2] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleTextureZBufferRW32(
					surface,
					clipper,
					zbuffer,
					texture,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					uvList[i * 3 + 0] * texture_expend,
					uvList[i * 3 + 1] * texture_expend,
					uvList[i * 3 + 2] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleIndexListTextureZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleTextureZBufferRW16(
				//	surface,
				//	zbuffer,
				//	texture,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleTextureZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	texture,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleIndexListTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleTextureZBufferRW32(
					surface,
					zbuffer,
					texture,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleTextureZBufferRW32(
					surface,
					clipper,
					zbuffer,
					texture,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleListTexturePerspectiveLPZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleTexturePerspectiveLPZBufferRW16(
				//	surface,
				//	zbuffer,
				//	texture,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	uvList[i * 3 + 0] * texture_expend,
				//	uvList[i * 3 + 1] * texture_expend,
				//	uvList[i * 3 + 2] * texture_expend));
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleTexturePerspectiveLPZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	texture,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	uvList[i * 3 + 0] * texture_expend,
				//	uvList[i * 3 + 1] * texture_expend,
				//	uvList[i * 3 + 2] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleListTexturePerspectiveLPZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleTexturePerspectiveLPZBufferRW32(
					surface,
					zbuffer,
					texture,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					uvList[i * 3 + 0] * texture_expend,
					uvList[i * 3 + 1] * texture_expend,
					uvList[i * 3 + 2] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleTexturePerspectiveLPZBufferRW32(
					surface,
					clipper,
					zbuffer,
					texture,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					uvList[i * 3 + 0] * texture_expend,
					uvList[i * 3 + 1] * texture_expend,
					uvList[i * 3 + 2] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleIndexListTexturePerspectiveLPZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint16> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleTexturePerspectiveLPZBufferRW16(
				//	surface,
				//	zbuffer,
				//	texture,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleTexturePerspectiveLPZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	texture,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleIndexListTexturePerspectiveLPZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleTexturePerspectiveLPZBufferRW32(
					surface,
					zbuffer,
					texture,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleTexturePerspectiveLPZBufferRW32(
					surface,
					clipper,
					zbuffer,
					texture,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;
			}
		}
	}

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
		ClipStateList & retClipStateList)
	{
		/**********************************************************************
		*		0
		* -------------
		*	2       1
		**********************************************************************/

		Vec4<real> v3 = vec3ClipZ(v0, v1, camera.nz);
		Vec4<real> c3 = vec3Intersect(c0, c1, v0.z, v1.z, camera.nz);
		Vec2<real> t3 = vec2Intersect(t0, t1, v0.z, v1.z, camera.nz);

		Vec4<real> v4 = vec3ClipZ(v0, v2, camera.nz);
		Vec4<real> c4 = vec3Intersect(c0, c2, v0.z, v2.z, camera.nz);
		Vec2<real> t4 = vec2Intersect(t0, t2, v0.z, v2.z, camera.nz);

		retVertexList.push_back(v0);
		retVertexList.push_back(v3);
		retVertexList.push_back(v4);
		retColorList.push_back(c0);
		retColorList.push_back(c3);
		retColorList.push_back(c4);
		retUVList.push_back(t0);
		retUVList.push_back(t3);
		retUVList.push_back(t4);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

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
		ClipStateList & retClipStateList)
	{
		/**********************************************************************
		*	1       2
		* -------------
		*		0
		**********************************************************************/

		Vec4<real> v3 = vec3ClipZ(v0, v1, camera.nz);
		Vec4<real> c3 = vec3Intersect(c0, c1, v0.z, v1.z, camera.nz);
		Vec2<real> t3 = vec2Intersect(t0, t1, v0.z, v1.z, camera.nz);

		Vec4<real> v4 = vec3ClipZ(v0, v2, camera.nz);
		Vec4<real> c4 = vec3Intersect(c0, c2, v0.z, v2.z, camera.nz);
		Vec2<real> t4 = vec2Intersect(t0, t2, v0.z, v2.z, camera.nz);

		retVertexList.push_back(v3);
		retVertexList.push_back(v1);
		retVertexList.push_back(v2);
		retColorList.push_back(c3);
		retColorList.push_back(c1);
		retColorList.push_back(c2);
		retUVList.push_back(t3);
		retUVList.push_back(t1);
		retUVList.push_back(t2);
		retClipStateList.push_back(CLIP_STATE_NONE);

		retVertexList.push_back(v3);
		retVertexList.push_back(v2);
		retVertexList.push_back(v4);
		retColorList.push_back(c3);
		retColorList.push_back(c2);
		retColorList.push_back(c4);
		retUVList.push_back(t3);
		retUVList.push_back(t2);
		retUVList.push_back(t4);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

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
		ClipStateList & retClipStateList)
	{
		if(CLIP_STATE_CULLED == clipTriangleAtCameraFarZ(v0, v1, v2, camera))
		{
			return CLIP_STATE_CULLED;
		}

		if(v0.z > camera.nz)
		{
			if(v1.z > camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleGouraudTextureAtCameraNearZSingle(v2, v0, v1, c2, c0, c1, t2, t0, t1, camera, retVertexList, retColorList, retUVList, retClipStateList);
				}
			}
			else if(v1.z == camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleGouraudTextureAtCameraNearZSingle(v2, v0, v1, c2, c0, c1, t2, t0, t1, camera, retVertexList, retColorList, retUVList, retClipStateList);
				}
			}
			else
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleGouraudTextureAtCameraNearZSingle(v1, v2, v0, c1, c2, c0, t1, t2, t0, camera, retVertexList, retColorList, retUVList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return clipTriangleGouraudTextureAtCameraNearZDouble(v0, v1, v2, c0, c1, c2, t0, t1, t2, camera, retVertexList, retColorList, retUVList, retClipStateList);
				}
				else
				{
					return clipTriangleGouraudTextureAtCameraNearZDouble(v0, v1, v2, c0, c1, c2, t0, t1, t2, camera, retVertexList, retColorList, retUVList, retClipStateList);
				}
			}
		}
		else if(v0.z == camera.nz)
		{
			if(v1.z > camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleGouraudTextureAtCameraNearZDouble(v1, v2, v0, c1, c2, c0, t1, t2, t0, camera, retVertexList, retColorList, retUVList, retClipStateList);
				}
			}
			else if(v1.z == camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleGouraudTextureAtCameraNearZDouble(v2, v0, v1, c2, c0, c1, t2, t0, t1, camera, retVertexList, retColorList, retUVList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
		else
		{
			if(v1.z > camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleGouraudTextureAtCameraNearZSingle(v0, v1, v2, c0, c1, c2, t0, t1, t2, camera, retVertexList, retColorList, retUVList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return clipTriangleGouraudTextureAtCameraNearZDouble(v1, v2, v0, c1, c2, c0, t1, t2, t0, camera, retVertexList, retColorList, retUVList, retClipStateList);
				}
				else
				{
					return clipTriangleGouraudTextureAtCameraNearZDouble(v1, v2, v0, c1, c2, c0, t1, t2, t0, camera, retVertexList, retColorList, retUVList, retClipStateList);
				}
			}
			else if(v1.z == camera.nz)
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleGouraudTextureAtCameraNearZDouble(v2, v0, v1, c2, c0, c1, t2, t0, t1, camera, retVertexList, retColorList, retUVList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(v2.z > camera.nz)
				{
					return clipTriangleGouraudTextureAtCameraNearZDouble(v2, v0, v1, c2, c0, c1, t2, t0, t1, camera, retVertexList, retColorList, retUVList, retClipStateList);
				}
				else if(v2.z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
	}

	void clipTriangleListGouraudTextureAtCamera(
		VertexList & vertexList,
		ColorList & colorList,
		UVList & uvList,
		ClipStateList & clipStateList,
		const CAMERA & camera)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(colorList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				CLIP_STATE state = clipTriangleGouraudTextureAtCamera(
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					colorList[i * 3 + 0],
					colorList[i * 3 + 1],
					colorList[i * 3 + 2],
					uvList[i * 3 + 0],
					uvList[i * 3 + 1],
					uvList[i * 3 + 2],
					camera,
					vertexList,
					colorList,
					uvList,
					clipStateList);

				clipStateList[i] = state;
			}
		}

		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(colorList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);
	}

	CLIP_STATE clipTriangleIndexGouraudTextureAtCameraNearZDouble(
		VertexList & vertexList,
		ColorList & colorList,
		UVList & uvList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList)
	{
		_ASSERT(v0_i < vertexList.size());
		_ASSERT(v1_i < vertexList.size());
		_ASSERT(v2_i < vertexList.size());

		/**********************************************************************
		*		0
		* -------------
		*	2       1
		**********************************************************************/

		size_t v3_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v1_i], camera.nz));
		colorList.push_back(vec3Intersect(colorList[v0_i], colorList[v1_i], vertexList[v0_i].z, vertexList[v1_i].z, camera.nz));
		uvList.push_back(vec2Intersect(uvList[v0_i], uvList[v1_i], vertexList[v0_i].z, vertexList[v1_i].z, camera.nz));

		size_t v4_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v2_i], camera.nz));
		colorList.push_back(vec3Intersect(colorList[v0_i], colorList[v2_i], vertexList[v0_i].z, vertexList[v2_i].z, camera.nz));
		uvList.push_back(vec2Intersect(uvList[v0_i], uvList[v2_i], vertexList[v0_i].z, vertexList[v2_i].z, camera.nz));

		retVertexIndexList.push_back(v0_i);
		retVertexIndexList.push_back(v3_i);
		retVertexIndexList.push_back(v4_i);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

	CLIP_STATE clipTriangleIndexGouraudTextureAtCameraNearZSingle(
		VertexList & vertexList,
		ColorList & colorList,
		UVList & uvList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList)
	{
		_ASSERT(v0_i < vertexList.size());
		_ASSERT(v1_i < vertexList.size());
		_ASSERT(v2_i < vertexList.size());

		/**********************************************************************
		*	1       2
		* -------------
		*		0
		**********************************************************************/

		size_t v3_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v1_i], camera.nz));
		colorList.push_back(vec3Intersect(colorList[v0_i], colorList[v1_i], vertexList[v0_i].z, vertexList[v1_i].z, camera.nz));
		uvList.push_back(vec2Intersect(uvList[v0_i], uvList[v1_i], vertexList[v0_i].z, vertexList[v1_i].z, camera.nz));

		size_t v4_i = vertexList.size();
		vertexList.push_back(vec3ClipZ(vertexList[v0_i], vertexList[v2_i], camera.nz));
		colorList.push_back(vec3Intersect(colorList[v0_i], colorList[v2_i], vertexList[v0_i].z, vertexList[v2_i].z, camera.nz));
		uvList.push_back(vec2Intersect(uvList[v0_i], uvList[v2_i], vertexList[v0_i].z, vertexList[v2_i].z, camera.nz));

		retVertexIndexList.push_back(v3_i);
		retVertexIndexList.push_back(v1_i);
		retVertexIndexList.push_back(v2_i);
		retClipStateList.push_back(CLIP_STATE_NONE);

		retVertexIndexList.push_back(v3_i);
		retVertexIndexList.push_back(v2_i);
		retVertexIndexList.push_back(v4_i);
		retClipStateList.push_back(CLIP_STATE_NONE);

		return CLIP_STATE_CULLED;
	}

	CLIP_STATE clipTriangleIndexGouraudTextureAtCamera(
		VertexList & vertexList,
		ColorList & colorList,
		UVList & uvList,
		size_t v0_i,
		size_t v1_i,
		size_t v2_i,
		const CAMERA & camera,
		VertexIndexList & retVertexIndexList,
		ClipStateList & retClipStateList)
	{
		if(CLIP_STATE_CULLED == clipTriangleAtCameraFarZ(vertexList[v0_i], vertexList[v1_i], vertexList[v2_i], camera))
		{
			return CLIP_STATE_CULLED;
		}

		if(vertexList[v0_i].z > camera.nz)
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleIndexGouraudTextureAtCameraNearZSingle(vertexList, colorList, uvList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleIndexGouraudTextureAtCameraNearZSingle(vertexList, colorList, uvList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexGouraudTextureAtCameraNearZSingle(vertexList, colorList, uvList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return clipTriangleIndexGouraudTextureAtCameraNearZDouble(vertexList, colorList, uvList, v0_i, v1_i, v2_i, camera, retVertexIndexList, retClipStateList);
				}
				else
				{
					return clipTriangleIndexGouraudTextureAtCameraNearZDouble(vertexList, colorList, uvList, v0_i, v1_i, v2_i, camera, retVertexIndexList, retClipStateList);
				}
			}
		}
		else if(vertexList[v0_i].z == camera.nz)
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else
				{
					return clipTriangleIndexGouraudTextureAtCameraNearZDouble(vertexList, colorList, uvList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return CLIP_STATE_NONE;
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexGouraudTextureAtCameraNearZDouble(vertexList, colorList, uvList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
		else
		{
			if(vertexList[v1_i].z > camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexGouraudTextureAtCameraNearZSingle(vertexList, colorList, uvList, v0_i, v1_i, v2_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return clipTriangleIndexGouraudTextureAtCameraNearZDouble(vertexList, colorList, uvList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
				else
				{
					return clipTriangleIndexGouraudTextureAtCameraNearZDouble(vertexList, colorList, uvList, v1_i, v2_i, v0_i, camera, retVertexIndexList, retClipStateList);
				}
			}
			else if(vertexList[v1_i].z == camera.nz)
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexGouraudTextureAtCameraNearZDouble(vertexList, colorList, uvList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
			else
			{
				if(vertexList[v2_i].z > camera.nz)
				{
					return clipTriangleIndexGouraudTextureAtCameraNearZDouble(vertexList, colorList, uvList, v2_i, v0_i, v1_i, camera, retVertexIndexList, retClipStateList);
				}
				else if(vertexList[v2_i].z == camera.nz)
				{
					return CLIP_STATE_CULLED;
				}
				else
				{
					return CLIP_STATE_CULLED;
				}
			}
		}
	}

	void clipTriangleIndexListGouraudTextureAtCamera(
		VertexList & vertexList,
		VertexIndexList & vertexIndexList,
		ColorList & colorList,
		UVList & uvList,
		ClipStateList & clipStateList,
		const CAMERA & camera)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == colorList.size());
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				CLIP_STATE state = clipTriangleIndexGouraudTextureAtCamera(
					vertexList,
					colorList,
					uvList,
					vertexIndexList[i * 3 + 0],
					vertexIndexList[i * 3 + 1],
					vertexIndexList[i * 3 + 2],
					camera,
					vertexIndexList,
					clipStateList);

				clipStateList[i] = state;
			}
		}

		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == colorList.size());
		_ASSERT(vertexList.size() == uvList.size());
	}

	void drawTriangleListGouraudTextureZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleGouraudTextureZBufferRW16(
				//	surface,
				//	zbuffer,
				//	texture,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	rgbaSaturate<real>(colorList[i * 3 + 0] * 255, 255),
				//	rgbaSaturate<real>(colorList[i * 3 + 1] * 255, 255),
				//	rgbaSaturate<real>(colorList[i * 3 + 2] * 255, 255),
				//	uvList[i * 3 + 0] * texture_expend,
				//	uvList[i * 3 + 1] * texture_expend,
				//	uvList[i * 3 + 2] * texture_expend));
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleGouraudTextureZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	texture,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	rgbaSaturate<real>(colorList[i * 3 + 0] * 255, 255),
				//	rgbaSaturate<real>(colorList[i * 3 + 1] * 255, 255),
				//	rgbaSaturate<real>(colorList[i * 3 + 2] * 255, 255),
				//	uvList[i * 3 + 0] * texture_expend,
				//	uvList[i * 3 + 1] * texture_expend,
				//	uvList[i * 3 + 2] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleListGouraudTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleGouraudTextureZBufferRW32(
					surface,
					zbuffer,
					texture,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					rgbaSaturate<real>(colorList[i * 3 + 0] * 255, 255),
					rgbaSaturate<real>(colorList[i * 3 + 1] * 255, 255),
					rgbaSaturate<real>(colorList[i * 3 + 2] * 255, 255),
					uvList[i * 3 + 0] * texture_expend,
					uvList[i * 3 + 1] * texture_expend,
					uvList[i * 3 + 2] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleGouraudTextureZBufferRW32(
					surface,
					clipper,
					zbuffer,
					texture,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					rgbaSaturate<real>(colorList[i * 3 + 0] * 255, 255),
					rgbaSaturate<real>(colorList[i * 3 + 1] * 255, 255),
					rgbaSaturate<real>(colorList[i * 3 + 2] * 255, 255),
					uvList[i * 3 + 0] * texture_expend,
					uvList[i * 3 + 1] * texture_expend,
					uvList[i * 3 + 2] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleIndexListGouraudTextureZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleGouraudTextureZBufferRW16(
				//	surface,
				//	zbuffer,
				//	texture,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 0]] * 255, 255),
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 1]] * 255, 255),
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 2]] * 255, 255),
				//	uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleGouraudTextureZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	texture,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 0]] * 255, 255),
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 1]] * 255, 255),
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 2]] * 255, 255),
				//	uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;
			}
		}
	}

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
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleGouraudTextureZBufferRW32(
					surface,
					zbuffer,
					texture,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 0]] * 255, 255),
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 1]] * 255, 255),
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 2]] * 255, 255),
					uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleGouraudTextureZBufferRW32(
					surface,
					clipper,
					zbuffer,
					texture,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 0]] * 255, 255),
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 1]] * 255, 255),
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 2]] * 255, 255),
					uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleListGouraudTexturePerspectiveLPZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleGouraudTexturePerspectiveLPZBufferRW16(
				//	surface,
				//	zbuffer,
				//	texture,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	rgbaSaturate<real>(colorList[i * 3 + 0] * 255, 255),
				//	rgbaSaturate<real>(colorList[i * 3 + 1] * 255, 255),
				//	rgbaSaturate<real>(colorList[i * 3 + 2] * 255, 255),
				//	uvList[i * 3 + 0] * texture_expend,
				//	uvList[i * 3 + 1] * texture_expend,
				//	uvList[i * 3 + 2] * texture_expend));
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleGouraudTexturePerspectiveLPZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	texture,
				//	vertexList[i * 3 + 0],
				//	vertexList[i * 3 + 1],
				//	vertexList[i * 3 + 2],
				//	rgbaSaturate<real>(colorList[i * 3 + 0] * 255, 255),
				//	rgbaSaturate<real>(colorList[i * 3 + 1] * 255, 255),
				//	rgbaSaturate<real>(colorList[i * 3 + 2] * 255, 255),
				//	uvList[i * 3 + 0] * texture_expend,
				//	uvList[i * 3 + 1] * texture_expend,
				//	uvList[i * 3 + 2] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleListGouraudTexturePerspectiveLPZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);
		_ASSERT(uvList.size() == clipStateList.size() * 3);

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleGouraudTexturePerspectiveLPZBufferRW32(
					surface,
					zbuffer,
					texture,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					rgbaSaturate<real>(colorList[i * 3 + 0] * 255, 255),
					rgbaSaturate<real>(colorList[i * 3 + 1] * 255, 255),
					rgbaSaturate<real>(colorList[i * 3 + 2] * 255, 255),
					uvList[i * 3 + 0] * texture_expend,
					uvList[i * 3 + 1] * texture_expend,
					uvList[i * 3 + 2] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleGouraudTexturePerspectiveLPZBufferRW32(
					surface,
					clipper,
					zbuffer,
					texture,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					rgbaSaturate<real>(colorList[i * 3 + 0] * 255, 255),
					rgbaSaturate<real>(colorList[i * 3 + 1] * 255, 255),
					rgbaSaturate<real>(colorList[i * 3 + 2] * 255, 255),
					uvList[i * 3 + 0] * texture_expend,
					uvList[i * 3 + 1] * texture_expend,
					uvList[i * 3 + 2] * texture_expend);
				break;
			}
		}
	}

	void drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW16(
		SurfaceRef<uint16> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		SurfaceRef<uint32> texture,
		const Vec2<real> & texture_expend,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ColorList & colorList,
		const UVList & uvList,
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				//drawTriangleGouraudTexturePerspectiveLPZBufferRW16(
				//	surface,
				//	zbuffer,
				//	texture,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 0]] * 255, 255),
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 1]] * 255, 255),
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 2]] * 255, 255),
				//	uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				//drawClippedTriangleGouraudTexturePerspectiveLPZBufferRW16(
				//	surface,
				//	clipper,
				//	zbuffer,
				//	texture,
				//	vertexList[vertexIndexList[i * 3 + 0]],
				//	vertexList[vertexIndexList[i * 3 + 1]],
				//	vertexList[vertexIndexList[i * 3 + 2]],
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 0]] * 255, 255),
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 1]] * 255, 255),
				//	rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 2]] * 255, 255),
				//	uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
				//	uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;
			}
		}
	}

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
		const ClipStateList & clipStateList)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);
		_ASSERT(vertexList.size() == uvList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			switch(clipStateList[i])
			{
			case CLIP_STATE_NONE:
				drawTriangleGouraudTexturePerspectiveLPZBufferRW32(
					surface,
					zbuffer,
					texture,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 0]] * 255, 255),
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 1]] * 255, 255),
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 2]] * 255, 255),
					uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleGouraudTexturePerspectiveLPZBufferRW32(
					surface,
					clipper,
					zbuffer,
					texture,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 0]] * 255, 255),
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 1]] * 255, 255),
					rgbaSaturate<real>(colorList[vertexIndexList[i * 3 + 2]] * 255, 255),
					uvList[vertexIndexList[i * 3 + 0]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 1]] * texture_expend,
					uvList[vertexIndexList[i * 3 + 2]] * texture_expend);
				break;
			}
		}
	}
}
