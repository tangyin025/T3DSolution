
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

	class VertexListContext
	{
	protected:
		VertexList m_vertexList;

	public:
		const VertexList & getVertexList(void) const
		{
			return m_vertexList;
		}

		VertexList & getVertexList(void)
		{
			return m_vertexList;
		}

		void pushVertex(real x, real y, real z)
		{
			pushVertex(vec3Build(x, y, z));
		}

		void pushVertex(real x, real y, real z, const Mat4<real> & mmat)
		{
			pushVertex(vec3Build(x, y, z), mmat);
		}

		void pushVertex(VertexList::const_reference vertex)
		{
			m_vertexList.push_back(vertex);
		}

		void pushVertex(VertexList::const_reference vertex, const Mat4<real> & mmat)
		{
			m_vertexList.push_back(vertex * mmat);
		}

		void pushVertexList(VertexList::const_iterator begin, VertexList::const_iterator end)
		{
			m_vertexList.insert(getVertexListEnd(), begin, end);
		}

		void pushVertexList(VertexList::const_iterator begin, VertexList::const_iterator end, const Mat4<real> & mmat)
		{
			_ASSERT(std::distance(begin, end) >= 0);

			const VertexList::size_type previous_size = getVertexListSize();
			const VertexList::difference_type inserted_size = previous_size + std::distance(begin, end);

			resizeVertexList(inserted_size);
			for(VertexList::difference_type i = previous_size; i < inserted_size; i++)
			{
				vertexAt(i) = *(begin + i) * mmat;
			}
		}

		void clearVertexList(void)
		{
			m_vertexList.clear();
		}

		void resizeVertexList(VertexList::size_type size)
		{
			m_vertexList.resize(size);
		}

		VertexList::size_type getVertexListSize(void) const
		{
			return m_vertexList.size();
		}

		VertexList::reference vertexAt(VertexList::size_type i)
		{
			_ASSERT(i < getVertexListSize());

			return m_vertexList[i];
		}

		VertexList::const_reference vertexAt(VertexList::size_type i) const
		{
			_ASSERT(i < getVertexListSize());

			return m_vertexList[i];
		}

		VertexList::iterator getVertexListBegin()
		{
			return m_vertexList.begin();
		}

		VertexList::const_iterator getVertexListBegin() const
		{
			return m_vertexList.begin();
		}

		VertexList::iterator getVertexListEnd()
		{
			return m_vertexList.end();
		}

		VertexList::const_iterator getVertexListEnd() const
		{
			return m_vertexList.end();
		}
	};

	class VertexIndexListContext
	{
	protected:
		VertexIndexList m_vertexIndexList;

	public:
		const VertexIndexList & getVertexIndexList(void) const
		{
			return m_vertexIndexList;
		}

		VertexIndexList & getVertexIndexList(void)
		{
			return m_vertexIndexList;
		}

		void pushVertexIndex(VertexIndexList::const_reference index)
		{
			m_vertexIndexList.push_back(index);
		}

		void pushVertexIndexList(VertexIndexList::const_iterator begin, VertexIndexList::const_iterator end)
		{
			m_vertexIndexList.insert(getVertexIndexListEnd(), begin, end);
		}

		void clearVertexIndexList(void)
		{
			m_vertexIndexList.clear();
		}

		void resizeVertexIndexList(VertexIndexList::size_type size)
		{
			m_vertexIndexList.resize(size);
		}

		VertexIndexList::size_type getVertexIndexListSize(void) const
		{
			return m_vertexIndexList.size();
		}

		VertexIndexList::reference vertexIndexAt(VertexIndexList::size_type i)
		{
			_ASSERT(i < getVertexIndexListSize());

			return m_vertexIndexList[i];
		}

		VertexIndexList::const_reference vertexIndexAt(VertexIndexList::size_type i) const
		{
			_ASSERT(i < getVertexIndexListSize());

			return m_vertexIndexList[i];
		}

		VertexIndexList::iterator getVertexIndexListBegin()
		{
			return m_vertexIndexList.begin();
		}

		VertexIndexList::const_iterator getVertexIndexListBegin() const
		{
			return m_vertexIndexList.begin();
		}

		VertexIndexList::iterator getVertexIndexListEnd()
		{
			return m_vertexIndexList.end();
		}

		VertexIndexList::const_iterator getVertexIndexListEnd() const
		{
			return m_vertexIndexList.end();
		}
	};

	class NormalListContext
	{
	protected:
		NormalList m_normalList;

	public:
		const NormalList & getNormalList(void) const
		{
			return m_normalList;
		}

		NormalList & getNormalList(void)
		{
			return m_normalList;
		}

		void pushNormal(real x, real y, real z)
		{
			pushNormal(vec3Build(x, y, z));
		}

		void pushNormal(real x, real y, real z, const Mat4<real> & mmat)
		{
			pushNormal(vec3Build(x, y, z), mmat);
		}

		void pushNormal(NormalList::const_reference normal)
		{
			m_normalList.push_back(normal);
		}

		void pushNormal(NormalList::const_reference normal, const Mat4<real> & mmat)
		{
			m_normalList.push_back(normal * mmat);
		}

		void pushNormalList(NormalList::const_iterator begin, NormalList::const_iterator end)
		{
			m_normalList.insert(getNormalListEnd(), begin, end);
		}

		void pushNormalList(NormalList::const_iterator begin, NormalList::const_iterator end, const Mat4<real> & mmat)
		{
			_ASSERT(std::distance(begin, end) >= 0);

			const NormalList::size_type previous_size = getNormalListSize();
			const NormalList::difference_type inserted_size = previous_size + std::distance(begin, end);

			resizeNormalList(inserted_size);
			for(NormalList::difference_type i = previous_size; i < inserted_size; i++)
			{
				normalAt(i) = *(begin + i) * mmat;
			}
		}

		void clearNormalList(void)
		{
			m_normalList.clear();
		}

		void resizeNormalList(NormalList::size_type size)
		{
			m_normalList.resize(size);
		}

		NormalList::size_type getNormalListSize(void) const
		{
			return m_normalList.size();
		}

		NormalList::reference normalAt(NormalList::size_type i)
		{
			_ASSERT(i < getNormalListSize());

			return m_normalList[i];
		}

		NormalList::const_reference normalAt(NormalList::size_type i) const
		{
			_ASSERT(i < getNormalListSize());

			return m_normalList[i];
		}

		NormalList::iterator getNormalListBegin()
		{
			return m_normalList.begin();
		}

		NormalList::const_iterator getNormalListBegin() const
		{
			return m_normalList.begin();
		}

		NormalList::iterator getNormalListEnd()
		{
			return m_normalList.end();
		}

		NormalList::const_iterator getNormalListEnd() const
		{
			return m_normalList.end();
		}
	};

	class UVListContext
	{
	protected:
		UVList m_uvList;

	public:
		const UVList & getUVList(void) const
		{
			return m_uvList;
		}

		UVList & getUVList(void)
		{
			return m_uvList;
		}

		void pushUV(real u, real v)
		{
			pushUV(Vec2<real>(u, v));
		}

		void pushUV(UVList::const_reference uv)
		{
			m_uvList.push_back(uv);
		}

		void pushUVList(UVList::const_iterator begin, UVList::const_iterator end)
		{
			m_uvList.insert(getUVListEnd(), begin, end);
		}

		void clearUVList(void)
		{
			m_uvList.clear();
		}

		void resizeUVList(UVList::size_type size)
		{
			m_uvList.resize(size);
		}

		UVList::size_type getUVListSize(void) const
		{
			return m_uvList.size();
		}

		UVList::reference uvAt(UVList::size_type i)
		{
			_ASSERT(i < getUVListSize());

			return m_uvList[i];
		}

		UVList::const_reference uvAt(UVList::size_type i) const
		{
			_ASSERT(i < getUVListSize());

			return m_uvList[i];
		}

		UVList::iterator getUVListBegin()
		{
			return m_uvList.begin();
		}

		UVList::const_iterator getUVListBegin() const
		{
			return m_uvList.begin();
		}

		UVList::iterator getUVListEnd()
		{
			return m_uvList.end();
		}

		UVList::const_iterator getUVListEnd() const
		{
			return m_uvList.end();
		}
	};

	class ColorListContext
	{
	protected:
		ColorList m_colorList;

	public:
		const ColorList & getColorList(void) const
		{
			return m_colorList;
		}

		ColorList & getColorList(void)
		{
			return m_colorList;
		}

		void pushColor(real r, real g, real b, real a)
		{
			pushColor(Vec4<real>(r, g, b, a));
		}

		void pushColor(ColorList::const_reference color)
		{
			m_colorList.push_back(color);
		}

		void pushColorList(ColorList::const_iterator begin, ColorList::const_iterator end)
		{
			m_colorList.insert(getColorListEnd(), begin, end);
		}

		void clearColorList(void)
		{
			m_colorList.clear();
		}

		void resizeColorList(ColorList::size_type size)
		{
			m_colorList.resize(size);
		}

		void resizeColorList(ColorList::size_type size, ColorList::const_reference color)
		{
			m_colorList.resize(size, color);
		}

		ColorList::size_type getColorListSize(void) const
		{
			return m_colorList.size();
		}

		ColorList::reference colorAt(ColorList::size_type i)
		{
			_ASSERT(i < getColorListSize());

			return m_colorList[i];
		}

		ColorList::const_reference colorAt(ColorList::size_type i) const
		{
			_ASSERT(i < getColorListSize());

			return m_colorList[i];
		}

		ColorList::iterator getColorListBegin()
		{
			return m_colorList.begin();
		}

		ColorList::const_iterator getColorListBegin() const
		{
			return m_colorList.begin();
		}

		ColorList::iterator getColorListEnd()
		{
			return m_colorList.end();
		}

		ColorList::const_iterator getColorListEnd() const
		{
			return m_colorList.end();
		}
	};

	inline void resetColorList(ColorList & colorList, size_t size, const Vec4<real> & color = Vec4<real>(0, 0, 0, 0))
	{
		colorList.clear();
		colorList.resize(size, color);
	}

	class SurfaceContext
	{
	protected:
		void * m_surfaceBuffer;

		LONG m_surfacePitch;

		DWORD m_surfaceWidth;

		DWORD m_surfaceHeight;

	public:
		void setSurfaceBuffer(void * pbuffer)
		{
			m_surfaceBuffer = pbuffer;
		}

		void setSurfaceBuffer(void * pbuffer, LONG pitch, DWORD width, DWORD height)
		{
			setSurfaceBuffer(pbuffer);
			setSurfacePitch(pitch);
			setSurfaceWidth(width);
			setSurfaceHeight(height);
		}

		void * getSurfaceBuffer(void) const
		{
			return m_surfaceBuffer;
		}

		void setSurfacePitch(LONG pitch)
		{
			m_surfacePitch = pitch;
		}

		LONG getSurfacePitch(void) const
		{
			return m_surfacePitch;
		}

		void setSurfaceWidth(DWORD width)
		{
			m_surfaceWidth = width;
		}

		DWORD getSurfaceWidth(void) const
		{
			return m_surfaceWidth;
		}

		void setSurfaceHeight(DWORD height)
		{
			m_surfaceHeight = height;
		}

		DWORD getSurfaceHeight(void) const
		{
			return m_surfaceHeight;
		}

	public:
		SurfaceRef<uint16> getSurfaceRef16(void) const
		{
			return SurfaceRef<uint16>(static_cast<uint16*>(m_surfaceBuffer), m_surfacePitch);
		}

		SurfaceRef<uint32> getSurfaceRef32(void) const
		{
			return SurfaceRef<uint32>(static_cast<uint32*>(m_surfaceBuffer), m_surfacePitch);
		}
	};

	class ZBufferContext
	{
	protected:
		void * m_zbufferBuffer;

		LONG m_zbufferPitch;

		DWORD m_zbufferWidth;

		DWORD m_zbufferHeight;

	public:
		void setZBufferBuffer(void * pbuffer)
		{
			m_zbufferBuffer = pbuffer;
		}

		void setZBufferBuffer(void * pbuffer, LONG pitch, DWORD width, DWORD height)
		{
			setZBufferBuffer(pbuffer);
			setZBufferPitch(pitch);
			setZBufferWidth(width);
			setZBufferHeight(height);
		}

		void * getZBufferBuffer(void) const
		{
			return m_zbufferBuffer;
		}

		void setZBufferPitch(LONG pitch)
		{
			m_zbufferPitch = pitch;
		}

		LONG getZBufferPitch(void) const
		{
			return m_zbufferPitch;
		}

		void setZBufferWidth(DWORD width)
		{
			m_zbufferWidth = width;
		}

		DWORD getZBufferWidth(void) const
		{
			return m_zbufferWidth;
		}

		void setZBufferHeight(DWORD height)
		{
			m_zbufferHeight = height;
		}

		DWORD getZBufferHeight(void) const
		{
			return m_zbufferHeight;
		}

	public:
		SurfaceRef<fixp28> getZBufferRef28(void) const
		{
			return SurfaceRef<fixp28>(static_cast<fixp28*>(m_zbufferBuffer), m_zbufferPitch);
		}
	};

	class TextureContext
	{
	protected:
		void * m_textureBuffer;

		LONG m_texturePitch;

		DWORD m_textureWidth;

		DWORD m_textureHeight;

	public:
		void setTextureBuffer(void * pbuffer)
		{
			m_textureBuffer = pbuffer;
		}

		void setTextureBuffer(void * pbuffer, LONG pitch, DWORD width, DWORD height)
		{
			setTextureBuffer(pbuffer);
			setTexturePitch(pitch);
			setTextureWidth(width);
			setTextureHeight(height);
		}

		void * getTextureBuffer(void) const
		{
			return m_textureBuffer;
		}

		void setTexturePitch(LONG pitch)
		{
			m_texturePitch = pitch;
		}

		LONG getTexturePitch(void) const
		{
			return m_texturePitch;
		}

		void setTextureWidth(DWORD width)
		{
			m_textureWidth = width;
		}

		DWORD getTextureWidth(void) const
		{
			return m_textureWidth;
		}

		void setTextureHeight(DWORD height)
		{
			m_textureHeight = height;
		}

		DWORD getTextureHeight(void) const
		{
			return m_textureHeight;
		}

	public:
		SurfaceRef<uint16> getTextureRef16(void) const
		{
			return SurfaceRef<uint16>(static_cast<uint16*>(m_textureBuffer), m_texturePitch);
		}

		SurfaceRef<uint32> getTextureRef32(void) const
		{
			return SurfaceRef<uint32>(static_cast<uint32*>(m_textureBuffer), m_texturePitch);
		}
	};

	class ClipperContext
	{
	protected:
		CRect m_clipper;

	public:
		void setClipperRect(const CRect & clipper)
		{
			m_clipper = clipper;
		}

		const CRect & getClipperRect(void) const
		{
			return m_clipper;
		}
	};

	struct MATERIAL
	{
		Vec4<real> ambient;
		Vec4<real> diffuse;
		Vec4<real> specular;
		Vec4<real> emissive;
	};

	class MaterialContext
	{
	protected:
		MATERIAL m_material;

	public:
		void setMaterial(const MATERIAL & material)
		{
			m_material = material;
		}

		const MATERIAL & getMaterial(void) const
		{
			return m_material;
		}

	public:
		void setAmbient(const Vec4<real> & ambient)
		{
			m_material.ambient = ambient;
		}

		void setDiffuse(const Vec4<real> & diffuse)
		{
			m_material.diffuse = diffuse;
		}

		void setSpecular(const Vec4<real> & specular)
		{
			m_material.specular = specular;
		}

		void setEmissive(const Vec4<real> & emissive)
		{
			m_material.emissive = emissive;
		}
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

	class LightListContext
	{
	protected:
		LightList m_lightList;

	public:
		static LIGHT buildLightAmbient(const Vec4<real> & ambient, LIGHT_STATE state = LS_ON);

		static LIGHT buildLightDirectional(const Vec4<real> & diffuse, const Vec4<real> & dir, LIGHT_STATE state = LS_ON);

		static LIGHT buildLightPoint(const Vec4<real> & diffuse, const Vec4<real> & pos, real kc = 1.0f, real kl = 0.001f, real kq = 0.00001f, LIGHT_STATE state = LS_ON);

	public:
		static Vec4<real> lightVertexAmbient(const LIGHT & light, const MATERIAL & material, const Vec4<real> & vertex, const Vec4<real> & normal);

		static Vec4<real> lightVertexDirectional(const LIGHT & light, const MATERIAL & material, const Vec4<real> & vertex, const Vec4<real> & normal);

		static Vec4<real> lightVertexPoint(const LIGHT & light, const MATERIAL & material, const Vec4<real> & vertex, const Vec4<real> & normal);

	public:
		const LightList & getLightList(void) const
		{
			return m_lightList;
		}

		LightList & getLightList(void)
		{
			return m_lightList;
		}

		size_t pushLightAmbient(const Vec4<real> & ambient, LIGHT_STATE state = LS_ON)
		{
			m_lightList.push_back(buildLightAmbient(ambient, state));

			return getLightListSize() - 1;
		};

		size_t pushLightDirectional(const Vec4<real> & diffuse, const Vec4<real> dir, LIGHT_STATE state = LS_ON)
		{
			m_lightList.push_back(buildLightDirectional(diffuse, dir, state));

			return getLightListSize() - 1;
		};

		size_t pushLightPoint(const Vec4<real> & diffuse, const Vec4<real> pos, real kc = 1.0f, real kl = 0.001f, real kq = 0.00001f, LIGHT_STATE state = LS_ON)
		{
			m_lightList.push_back(buildLightPoint(diffuse, pos, kc, kl, kq, state));

			return getLightListSize() - 1;
		};

		void clearLightList(void)
		{
			m_lightList.clear();
		}

		void resizeLightList(LightList::size_type size)
		{
			m_lightList.resize(size);
		}

		LightList::size_type getLightListSize(void) const
		{
			return m_lightList.size();
		}

		LightList::reference lightAt(LightList::size_type i)
		{
			_ASSERT(i < getLightListSize());

			return m_lightList[i];
		}

		LightList::const_reference lightAt(LightList::size_type i) const
		{
			_ASSERT(i < getLightListSize());

			return m_lightList[i];
		}

		LightList::iterator getLightListBegin()
		{
			return m_lightList.begin();
		}

		LightList::const_iterator getLightListBegin() const
		{
			return m_lightList.begin();
		}

		LightList::iterator getLightListEnd()
		{
			return m_lightList.end();
		}

		LightList::const_iterator getLightListEnd() const
		{
			return m_lightList.end();
		}
	};

	enum ROTATION_SEQ
	{
		RS_XYZ,
		RS_XZY,
		RS_YXZ,
		RS_YZX,
		RS_ZXY,
		RS_ZYX,
	};

	struct CAMERA
	{
		Mat4<real> mcam;
		Vec2<real> proj;
		real nz;
		real fz;
		CRect viewport;
	};

	class CameraContext
	{
	protected:
		CAMERA m_camera;

	public:
		static Mat4<real> buildCameraTransformEular(const Vec4<real> & pos, const Vec4<real> & rot, DWORD rot_seq = RS_ZXY);

		static Mat4<real> buildInverseCameraTransformEular(const Vec4<real> & pos, const Vec4<real> & rot, DWORD rot_seq = RS_ZXY);

		static Mat4<real> buildInverseCameraTransformUVN(const Vec4<real> & pos, const Vec4<real> & target, const Vec4<real> & up);

		static Mat4<real> buildInverseCameraTransformQuat(const Vec4<real> & pos, const Quat<real> & ori);

		static Vec2<real> buildCameraProjectionFOVWidth(real fov, DWORD width, DWORD height);

		static Vec2<real> buildCameraProjectionFOVHeight(real fov, DWORD width, DWORD height);

		static Vec2<real> buildCameraProjectionFOVAuto(real fov, DWORD width, DWORD height);

	public:
		static real calculateCameraHalfFovX(const Vec2<real> & proj)
		{
			return atan(1 / proj.x);
		}

		static real calculateCameraHalfFovY(const Vec2<real> & proj)
		{
			return atan(1 / proj.y);
		}

		static real calculateCameraMinHalfFov(const Vec2<real> & proj)
		{
			return proj.x > proj.y ? calculateCameraHalfFovX(proj) : calculateCameraHalfFovY(proj);
		}

		static real calculateCameraMaxHalfFov(const Vec2<real> & proj)
		{
			return proj.x < proj.y ? calculateCameraHalfFovX(proj) : calculateCameraHalfFovY(proj);
		}

		static Vec4<real> calculateCameraDirection(const Mat4<real> & mcam)
		{
			return Vec4<real>(0, 0, 1, 1) * mat4GetRotationScalePart(mcam.inverse());
		}

	public:
		void setCameraMatrix(const Mat4<real> & mcam)
		{
			m_camera.mcam = mcam;
		}

		const Mat4<real> & getCameraMatrix(void) const
		{
			return m_camera.mcam;
		}

		void setCameraProjection(const Vec2<real> & proj)
		{
			m_camera.proj = proj;
		}

		const Vec2<real> & getCameraProjection(void) const
		{
			return m_camera.proj;
		}

		void setCameraNearZ(real nz)
		{
			m_camera.nz = nz;
		}

		real getCameraNearZ(void) const
		{
			return m_camera.nz;
		}

		void setCameraFarZ(real fz)
		{
			m_camera.fz = fz;
		}

		real getCameraFarZ(void) const
		{
			return m_camera.fz;
		}

		void setViewport(const CRect & viewport)
		{
			m_camera.viewport = viewport;
		}

		const CRect & getViewport(void) const
		{
			return m_camera.viewport;
		}

		Vec4<real> getCameraPosition(void) const
		{
			return mat3GetRow3(getCameraMatrix().inverse());
		}

		const CAMERA & getCamera(void) const
		{
			return m_camera;
		}

		CAMERA & getCamera(void)
		{
			return m_camera;
		}
	};

	//enum TRI_STATE
	//{
	//	TS_ACTIVE,
	//	TS_CULLED,
	//	TS_CLIPPED,
	//	//TS_LARGE_CLIPPED,
	//	TS_BACKFACE,
	//};

	//typedef std::vector<TRI_STATE> TriStateList;

	//class TriangleStateListContext
	//{
	//protected:
	//	TriStateList m_triStateList;

	//public:
	//	static bool isTriVisible(TRI_STATE state);

	//public:
	//	const TriStateList & getTriStateList(void) const;

	//	TriStateList & getTriStateList(void);

	//	void pushTriState(TRI_STATE state);

	//	void pushTriStateList(TriStateList::const_iterator begin, TriStateList::const_iterator end);

	//	void clearTriStateList(void);

	//	void resizeTriStateList(TriStateList::size_type size);

	//	void resizeTriStateList(TriStateList::size_type size, TriStateList::const_reference state);

	//	TriStateList::size_type getTriStateListSize(void) const;

	//	TriStateList::reference triStateAt(TriStateList::size_type i);

	//	TriStateList::const_reference triStateAt(TriStateList::size_type i) const;

	//	TriStateList::iterator getTriStateListBegin();

	//	TriStateList::const_iterator getTriStateListBegin() const;

	//	TriStateList::iterator getTriStateListEnd();

	//	TriStateList::const_iterator getTriStateListEnd() const;
	//};

	enum CLIP_STATE
	{
		CLIP_STATE_NONE,
		CLIP_STATE_CULLED,
		CLIP_STATE_SCLIPPED
	};

	typedef std::vector<CLIP_STATE> ClipStateList;

	class ClipStateListContext
	{
	protected:
		ClipStateList m_clipStateList;

	public:
		const ClipStateList & getClipStateList(void) const
		{
			return m_clipStateList;
		}

		ClipStateList & getClipStateList(void)
		{
			return m_clipStateList;
		}

		void pushClipState(CLIP_STATE state)
		{
			m_clipStateList.push_back(state);
		}

		void pushClipStateList(ClipStateList::const_iterator begin, ClipStateList::const_iterator end)
		{
			m_clipStateList.insert(getClipStateListBegin(), begin, end);
		}

		void clearClipStateList(void)
		{
			m_clipStateList.clear();
		}

		void resizeClipStateList(ClipStateList::size_type size, CLIP_STATE state)
		{
			m_clipStateList.resize(size, state);
		}

		ClipStateList::size_type getClipStateListSize(void) const
		{
			return m_clipStateList.size();
		}

		ClipStateList::const_reference clipStateAt(ClipStateList::size_type i) const
		{
			_ASSERT(i < getClipStateListSize());

			return m_clipStateList[i];
		}

		ClipStateList::reference clipStateAt(ClipStateList::size_type i)
		{
			_ASSERT(i < getClipStateListSize());

			return m_clipStateList[i];
		}

		ClipStateList::const_iterator getClipStateListBegin() const
		{
			return m_clipStateList.begin();
		}

		ClipStateList::iterator getClipStateListBegin()
		{
			return m_clipStateList.begin();
		}

		ClipStateList::const_iterator getClipStateListEnd() const
		{
			return m_clipStateList.end();
		}

		ClipStateList::iterator getClipStateListEnd()
		{
			return m_clipStateList.end();
		}
	};

	inline void resetClipStateList(ClipStateList & clipStateList, size_t size, CLIP_STATE state = CLIP_STATE_NONE)
	{
		clipStateList.clear();
		clipStateList.resize(size, state);
	}

	class TriangleContext
		: public VertexListContext
		, public VertexIndexListContext
		, public NormalListContext
		, public UVListContext
		, public ColorListContext
		, public SurfaceContext
		, public ZBufferContext
		, public TextureContext
		, public ClipperContext
		, public MaterialContext
		, public LightListContext
		, public CameraContext
		//, public TriangleStateListContext
		, public ClipStateListContext
	{
	};

	//class RenderLineListZBufferRW
	//	: public TriangleContext
	//{
	//protected:
	//	TRI_STATE zClipLineAtCamera(const size_t index);

	//	TRI_STATE sClipLineAtScreen(const size_t index);

	//public:
	//	void reset(void);

	//	void worldToCamera(void);

	//	void zClipAtCamera(void);

	//	void cameraToScreen(void);

	//	void sClipAtScreen(void);

	//	void drawLineList16(const Vec4<real> & color);

	//	void drawLineList32(const Vec4<real> & color);
	//};

	//class RenderLineIndexListZBufferRW
	//	: public TriangleContext
	//{
	//protected:
	//	TRI_STATE zClipLineAtCamera(const size_t index);

	//	TRI_STATE sClipLineAtScreen(const size_t index);

	//public:
	//	void reset(void);

	//	void worldToCamera(void);

	//	void zClipAtCamera(void);

	//	void cameraToScreen(void);

	//	void sClipAtScreen(void);

	//	void drawLineIndexList16(const Vec4<real> & color);

	//	void drawLineIndexList32(const Vec4<real> & color);
	//};

	//class RenderTriangleListWireZBufferRW
	//	: public TriangleContext
	//{
	//protected:
	//	void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

	//	void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

	//	TRI_STATE zClipTriangleAtCamera(const size_t index);

	//	TRI_STATE sClipTriangleAtScreen(const size_t index);

	//public:
	//	void reset(void);

	//	void removeBackfaceAtWorld(void);

	//	void worldToCamera(void);

	//	void zClipAtCamera(void);

	//	void cameraToScreen(void);

	//	void sClipAtScreen(void);

	//	void drawTriangleList16(const Vec4<real> & color);

	//	void drawTriangleList32(const Vec4<real> & color);

	//	void drawTriangleListWithoutThird16(const Vec4<real> & color);

	//	void drawTriangleListWithoutThird32(const Vec4<real> & color);
	//};

	//class RenderTriangleIndexListWireZBufferRW
	//	: public TriangleContext
	//{
	//protected:
	//	void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

	//	void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

	//	TRI_STATE zClipTriangleAtCamera(const size_t index);

	//	TRI_STATE sClipTriangleAtScreen(const size_t index);

	//public:
	//	void reset(void);

	//	void removeBackfaceAtWorld(void);

	//	void worldToCamera(void);

	//	void zClipAtCamera(void);

	//	void cameraToScreen(void);

	//	void sClipAtScreen(void);

	//	void drawTriangleIndexList16(const Vec4<real> & color);

	//	void drawTriangleIndexList32(const Vec4<real> & color);

	//	void drawTriangleIndexListWithoutThird16(const Vec4<real> & color);

	//	void drawTriangleIndexListWithoutThird32(const Vec4<real> & color);
	//};

	//class RenderTriangleListZBufferRW
	//	: public RenderTriangleListWireZBufferRW
	//{
	//public:
	//	void drawTriangleList16(const Vec4<real> & color);

	//	void drawTriangleList32(const Vec4<real> & color);
	//};

	//class RenderTriangleIndexListZBufferRW
	//	: public RenderTriangleIndexListWireZBufferRW
	//{
	//public:
	//	void drawTriangleIndexList16(const Vec4<real> & color);

	//	void drawTriangleIndexList32(const Vec4<real> & color);
	//};

	//class RenderTriangleListGouraudZBufferRW
	//	: public TriangleContext
	//{
	//protected:
	//	void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

	//	void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

	//	TRI_STATE zClipTriangleAtCamera(const size_t index);

	//	TRI_STATE sClipTriangleAtScreen(const size_t index);

	//public:
	//	void reset(void);

	//	void removeBackfaceAtWorld(void);

	//	void lightAtWorld(void);

	//	void worldToCamera(void);

	//	void zClipAtCamera(void);

	//	void cameraToScreen(void);

	//	void sClipAtScreen(void);

	//	void drawTriangleList16(void);

	//	void drawTriangleList32(void);
	//};

	//class RenderTriangleIndexListGouraudZBufferRW
	//	: public TriangleContext
	//{
	//protected:
	//	void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

	//	void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

	//	TRI_STATE zClipTriangleAtCamera(const size_t index);

	//	TRI_STATE sClipTriangleAtScreen(const size_t index);

	//public:
	//	void reset(void);

	//	void removeBackfaceAtWorld(void);

	//	void lightAtWorld(void);

	//	void worldToCamera(void);

	//	void zClipAtCamera(void);

	//	void cameraToScreen(void);

	//	void sClipAtScreen(void);

	//	void drawTriangleIndexList16(void);

	//	void drawTriangleIndexList32(void);
	//};

	//class RenderTriangleListTextureZBufferRW
	//	: public TriangleContext
	//{
	//protected:
	//	void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

	//	void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

	//	TRI_STATE zClipTriangleAtCamera(const size_t index);

	//	TRI_STATE sClipTriangleAtScreen(const size_t index);

	//public:
	//	void reset(void);

	//	void removeBackfaceAtWorld(void);

	//	void worldToCamera(void);

	//	void zClipAtCamera(void);

	//	void cameraToScreen(void);

	//	void sClipAtScreen(void);

	//	void drawTriangleListZBufferW16(void);

	//	void drawTriangleListZBufferW32(void);

	//	void drawTriangleList16(void);

	//	void drawTriangleList32(void);
	//};

	//class RenderTriangleIndexListTextureZBufferRW
	//	: public TriangleContext
	//{
	//protected:
	//	void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

	//	void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

	//	TRI_STATE zClipTriangleAtCamera(const size_t index);

	//	TRI_STATE sClipTriangleAtScreen(const size_t index);

	//public:
	//	void reset(void);

	//	void removeBackfaceAtWorld(void);

	//	void worldToCamera(void);

	//	void zClipAtCamera(void);

	//	void cameraToScreen(void);

	//	void sClipAtScreen(void);

	//	void drawTriangleIndexListZBufferW16(void);

	//	void drawTriangleIndexListZBufferW32(void);

	//	void drawTriangleIndexList16(void);

	//	void drawTriangleIndexList32(void);
	//};

	//class RenderTriangleListTexturePerspectiveLPZBufferRW
	//	: public RenderTriangleListTextureZBufferRW
	//{
	//public:
	//	void drawTriangleListZBufferW16(void);

	//	void drawTriangleListZBufferW32(void);

	//	void drawTriangleList16(void);

	//	void drawTriangleList32(void);
	//};

	//class RenderTriangleIndexListTexturePerspectiveLPZBufferRW
	//	: public RenderTriangleIndexListTextureZBufferRW
	//{
	//public:
	//	void drawTriangleIndexListZBufferW16(void);

	//	void drawTriangleIndexListZBufferW32(void);

	//	void drawTriangleIndexList16(void);

	//	void drawTriangleIndexList32(void);
	//};

	//class RenderTriangleListGouraudTextureZBufferRW
	//	: public TriangleContext
	//{
	//protected:
	//	void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

	//	void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

	//	TRI_STATE zClipTriangleAtCamera(const size_t index);

	//	TRI_STATE sClipTriangleAtScreen(const size_t index);

	//public:
	//	void reset(void);

	//	void removeBackfaceAtWorld(void);

	//	void lightAtWorld(void);

	//	void worldToCamera(void);

	//	void zClipAtCamera(void);

	//	void cameraToScreen(void);

	//	void sClipAtScreen(void);

	//	void drawTriangleList16(void);

	//	void drawTriangleList32(void);
	//};

	//class RenderTriangleIndexListGouraudTextureZBufferRW
	//	: public TriangleContext
	//{
	//protected:
	//	void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

	//	void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

	//	TRI_STATE zClipTriangleAtCamera(const size_t index);

	//	TRI_STATE sClipTriangleAtScreen(const size_t index);

	//public:
	//	void reset(void);

	//	void removeBackfaceAtWorld(void);

	//	void lightAtWorld(void);

	//	void worldToCamera(void);

	//	void zClipAtCamera(void);

	//	void cameraToScreen(void);

	//	void sClipAtScreen(void);

	//	void drawTriangleIndexList16(void);

	//	void drawTriangleIndexList32(void);
	//};

	//class RenderTriangleListGouraudTexturePerspectiveLPZBufferRW
	//	: public RenderTriangleListGouraudTextureZBufferRW
	//{
	//public:
	//	void drawTriangleList16(void);

	//	void drawTriangleList32(void);
	//};

	//class RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW
	//	: public RenderTriangleIndexListGouraudTextureZBufferRW
	//{
	//public:
	//	void drawTriangleIndexList16(void);

	//	void drawTriangleIndexList32(void);
	//};

	class RenderContext
		: public TriangleContext
		//, public RenderLineListZBufferRW
		//, public RenderLineIndexListZBufferRW
		//, public RenderTriangleListZBufferRW
		//, public RenderTriangleIndexListZBufferRW
		//, public RenderTriangleListGouraudZBufferRW
		//, public RenderTriangleIndexListGouraudZBufferRW
		//, public RenderTriangleListTexturePerspectiveLPZBufferRW
		//, public RenderTriangleIndexListTexturePerspectiveLPZBufferRW
		//, public RenderTriangleListGouraudTexturePerspectiveLPZBufferRW
		//, public RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW
	{
	public:
		RenderContext(void);

		virtual ~RenderContext(void);

	public:
		void fillZbuffer(const CRect & rect, real value_inv);

	public:
		virtual void fillSurface(const CRect & rect, const Vec4<real> & color) = 0;

	public:
		virtual void drawLineListZBufferRW(const Vec4<real> & color) = 0;

		virtual void drawLineIndexListZBufferRW(const Vec4<real> & color) = 0;

		virtual void drawTriangleListWireZBufferRW(const Vec4<real> & color) = 0;

		virtual void drawTriangleIndexListWireZBufferRW(const Vec4<real> & color) = 0;

		//virtual void drawTriangleListWireZBufferRWWithoutThird(const Vec4<real> & color) = 0;

		//virtual void drawTriangleIndexListWireZBufferRWWithoutThird(const Vec4<real> & color) = 0;

		virtual void drawTriangleListWireZBufferRWWithBackface(const Vec4<real> & color) = 0;

		virtual void drawTriangleIndexListWireZBufferRWWithBackface(const Vec4<real> & color) = 0;

		//virtual void drawTriangleListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color) = 0;

		//virtual void drawTriangleIndexListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color) = 0;

		virtual void drawTriangleListZBufferRW(const Vec4<real> & color) = 0;

		virtual void drawTriangleIndexListZBufferRW(const Vec4<real> & color) = 0;

		virtual void drawTriangleListZBufferRWWithBackface(const Vec4<real> & color) = 0;

		virtual void drawTriangleIndexListZBufferRWWithBackface(const Vec4<real> & color) = 0;

		virtual void drawTriangleListGouraudZBufferRW(void) = 0;

		virtual void drawTriangleIndexListGouraudZBufferRW(void) = 0;

		virtual void drawTriangleListGouraudZBufferRWWithBackface(void) = 0;

		virtual void drawTriangleIndexListGouraudZBufferRWWithBackface(void) = 0;

		virtual void drawTriangleListTextureZBufferW(void) = 0;

		virtual void drawTriangleIndexListTextureZBufferW(void) = 0;

		virtual void drawTriangleListTextureZBufferWWithBackface(void) = 0;

		virtual void drawTriangleIndexListTextureZBufferWWithBackface(void) = 0;

		virtual void drawTriangleListTexturePerspectiveLPZBufferW(void) = 0;

		virtual void drawTriangleIndexListTexturePerspectiveLPZBufferW(void) = 0;

		virtual void drawTriangleListTexturePerspectiveLPZBufferWWithBackface(void) = 0;

		virtual void drawTriangleIndexListTexturePerspectiveLPZBufferWWithBackface(void) = 0;

		virtual void drawTriangleListTextureZBufferRW(void) = 0;

		virtual void drawTriangleIndexListTextureZBufferRW(void) = 0;

		virtual void drawTriangleListTextureZBufferRWWithBackface(void) = 0;

		virtual void drawTriangleIndexListTextureZBufferRWWithBackface(void) = 0;

		virtual void drawTriangleListTexturePerspectiveLPZBufferRW(void) = 0;

		virtual void drawTriangleIndexListTexturePerspectiveLPZBufferRW(void) = 0;

		virtual void drawTriangleListTexturePerspectiveLPZBufferRWWithBackface(void) = 0;

		virtual void drawTriangleIndexListTexturePerspectiveLPZBufferRWWithBackface(void) = 0;

		virtual void drawTriangleListGouraudTextureZBufferRW(void) = 0;

		virtual void drawTriangleIndexListGouraudTextureZBufferRW(void) = 0;

		virtual void drawTriangleListGouraudTextureZBufferRWWithBackface(void) = 0;

		virtual void drawTriangleIndexListGouraudTextureZBufferRWWithBackface(void) = 0;

		virtual void drawTriangleListGouraudTexturePerspectiveLPZBufferRW(void) = 0;

		virtual void drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW(void) = 0;

		virtual void drawTriangleListGouraudTexturePerspectiveLPZBufferRWWithBackface(void) = 0;

		virtual void drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRWWithBackface(void) = 0;
	};

	typedef boost::shared_ptr<RenderContext> RenderContextPtr;

	class RenderContext16
		: virtual public RenderContext
	{
	public:
		void fillSurface(const CRect & rect, const Vec4<real> & color);

	public:
		void drawLineListZBufferRW(const Vec4<real> & color);

		void drawLineIndexListZBufferRW(const Vec4<real> & color);

		void drawTriangleListWireZBufferRW(const Vec4<real> & color);

		void drawTriangleIndexListWireZBufferRW(const Vec4<real> & color);

		//void drawTriangleListWireZBufferRWWithoutThird(const Vec4<real> & color);

		//void drawTriangleIndexListWireZBufferRWWithoutThird(const Vec4<real> & color);

		void drawTriangleListWireZBufferRWWithBackface(const Vec4<real> & color);

		void drawTriangleIndexListWireZBufferRWWithBackface(const Vec4<real> & color);

		//void drawTriangleListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color);

		//void drawTriangleIndexListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color);

		void drawTriangleListZBufferRW(const Vec4<real> & color);

		void drawTriangleIndexListZBufferRW(const Vec4<real> & color);

		void drawTriangleListZBufferRWWithBackface(const Vec4<real> & color);

		void drawTriangleIndexListZBufferRWWithBackface(const Vec4<real> & color);

		void drawTriangleListGouraudZBufferRW(void);

		void drawTriangleIndexListGouraudZBufferRW(void);

		void drawTriangleListGouraudZBufferRWWithBackface(void);

		void drawTriangleIndexListGouraudZBufferRWWithBackface(void);

		void drawTriangleListTextureZBufferW(void);

		void drawTriangleIndexListTextureZBufferW(void);

		void drawTriangleListTextureZBufferWWithBackface(void);

		void drawTriangleIndexListTextureZBufferWWithBackface(void);

		void drawTriangleListTexturePerspectiveLPZBufferW(void);

		void drawTriangleIndexListTexturePerspectiveLPZBufferW(void);

		void drawTriangleListTexturePerspectiveLPZBufferWWithBackface(void);

		void drawTriangleIndexListTexturePerspectiveLPZBufferWWithBackface(void);

		void drawTriangleListTextureZBufferRW(void);

		void drawTriangleIndexListTextureZBufferRW(void);

		void drawTriangleListTextureZBufferRWWithBackface(void);

		void drawTriangleIndexListTextureZBufferRWWithBackface(void);

		void drawTriangleListTexturePerspectiveLPZBufferRW(void);

		void drawTriangleIndexListTexturePerspectiveLPZBufferRW(void);

		void drawTriangleListTexturePerspectiveLPZBufferRWWithBackface(void);

		void drawTriangleIndexListTexturePerspectiveLPZBufferRWWithBackface(void);

		void drawTriangleListGouraudTextureZBufferRW(void);

		void drawTriangleIndexListGouraudTextureZBufferRW(void);

		void drawTriangleListGouraudTextureZBufferRWWithBackface(void);

		void drawTriangleIndexListGouraudTextureZBufferRWWithBackface(void);

		void drawTriangleListGouraudTexturePerspectiveLPZBufferRW(void);

		void drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW(void);

		void drawTriangleListGouraudTexturePerspectiveLPZBufferRWWithBackface(void);

		void drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRWWithBackface(void);
	};

	class RenderContext32
		: virtual public RenderContext
	{
	public:
		void fillSurface(const CRect & rect, const Vec4<real> & color);

	public:
		void drawLineListZBufferRW(const Vec4<real> & color);

		void drawLineIndexListZBufferRW(const Vec4<real> & color);

		void drawTriangleListWireZBufferRW(const Vec4<real> & color);

		void drawTriangleIndexListWireZBufferRW(const Vec4<real> & color);

		//void drawTriangleListWireZBufferRWWithoutThird(const Vec4<real> & color);

		//void drawTriangleIndexListWireZBufferRWWithoutThird(const Vec4<real> & color);

		void drawTriangleListWireZBufferRWWithBackface(const Vec4<real> & color);

		void drawTriangleIndexListWireZBufferRWWithBackface(const Vec4<real> & color);

		//void drawTriangleListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color);

		//void drawTriangleIndexListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color);

		void drawTriangleListZBufferRW(const Vec4<real> & color);

		void drawTriangleIndexListZBufferRW(const Vec4<real> & color);

		void drawTriangleListZBufferRWWithBackface(const Vec4<real> & color);

		void drawTriangleIndexListZBufferRWWithBackface(const Vec4<real> & color);

		void drawTriangleListGouraudZBufferRW(void);

		void drawTriangleIndexListGouraudZBufferRW(void);

		void drawTriangleListGouraudZBufferRWWithBackface(void);

		void drawTriangleIndexListGouraudZBufferRWWithBackface(void);

		void drawTriangleListTextureZBufferW(void);

		void drawTriangleIndexListTextureZBufferW(void);

		void drawTriangleListTextureZBufferWWithBackface(void);

		void drawTriangleIndexListTextureZBufferWWithBackface(void);

		void drawTriangleListTexturePerspectiveLPZBufferW(void);

		void drawTriangleIndexListTexturePerspectiveLPZBufferW(void);

		void drawTriangleListTexturePerspectiveLPZBufferWWithBackface(void);

		void drawTriangleIndexListTexturePerspectiveLPZBufferWWithBackface(void);

		void drawTriangleListTextureZBufferRW(void);

		void drawTriangleIndexListTextureZBufferRW(void);

		void drawTriangleListTextureZBufferRWWithBackface(void);

		void drawTriangleIndexListTextureZBufferRWWithBackface(void);

		void drawTriangleListTexturePerspectiveLPZBufferRW(void);

		void drawTriangleIndexListTexturePerspectiveLPZBufferRW(void);

		void drawTriangleListTexturePerspectiveLPZBufferRWWithBackface(void);

		void drawTriangleIndexListTexturePerspectiveLPZBufferRWWithBackface(void);

		void drawTriangleListGouraudTextureZBufferRW(void);

		void drawTriangleIndexListGouraudTextureZBufferRW(void);

		void drawTriangleListGouraudTextureZBufferRWWithBackface(void);

		void drawTriangleIndexListGouraudTextureZBufferRWWithBackface(void);

		void drawTriangleListGouraudTexturePerspectiveLPZBufferRW(void);

		void drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRW(void);

		void drawTriangleListGouraudTexturePerspectiveLPZBufferRWWithBackface(void);

		void drawTriangleIndexListGouraudTexturePerspectiveLPZBufferRWWithBackface(void);
	};

	void transformVertexList(
		VertexList & vertexList,
		const Mat4<real> & mmat);

	//void transformVertexIndexList(
	//	VertexList & vertexList,
	//	VertexIndexList & vertexIndexList,
	//	const Mat4<real> & mmat);

	void transformLineList(
		VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat);

	void transformLineIndexList(
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
		const Vec4<real> & cameraPosition);

	void removeTriangleListBackfaceAtWorld(
		const VertexList & vertexList,
		ClipStateList & clipStateList,
		const Vec4<real> & cameraPosition);

	void removeTriangleIndexListBackfaceAtWorld(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const Vec4<real> & cameraPosition);

	void transformTriangleList(
		VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat);

	void transformTriangleIndexList(
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
		SurfaceRef<uint32> texture,
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
		SurfaceRef<uint32> texture,
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
		SurfaceRef<uint32> texture,
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
		SurfaceRef<uint32> texture,
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
