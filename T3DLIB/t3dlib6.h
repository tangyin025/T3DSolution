
#ifndef __T3DLIB6_H__
#define __T3DLIB6_H__

#include "t3dcommon.h"

#include <vector>
//#include <stack>
#include <cmath>
#include "t3dlib4.h"
#include "t3dlib5.h"

namespace t3d
{
	//template <class elemT, class allocatorT = std::allocator<elemT> >
	//class vector : public std::vector<elemT, allocatorT>
	//{
	//protected:
	//	static const size_type increment = 128;

	//	static const size_type max_elements = 3000 * 3 * 3;

	//	size_type num_elements;

	//	typedef std::vector<elemT, allocatorT> base_vector_class;

	//public:
	//	explicit inline vector(unsigned capacity = increment * 4)
	//		: base_vector_class(capacity)
	//		, num_elements(0)
	//	{
	//	}

	//	~vector(void)
	//	{
	//	}

	//public:
	//	inline void push_back(const elemT & elem)
	//	{
	//		if(base_vector_class::size() <= num_elements)
	//		{
	//			base_vector_class::resize(num_elements + increment);
	//		}

	//		base_vector_class::at(num_elements++) = elem;
	//	}

	//	inline void insert(iterator iter_where, const_iterator insert_iter_first, const_iterator insert_iter_last)
	//	{
	//		difference_type insert_length = std::distance(insert_iter_first, insert_iter_last);

	//		assert(insert_length > 0);

	//		difference_type where_pos = std::distance(begin(), iter_where);

	//		difference_type remain_length = size() - where_pos;

	//		resize(size() + insert_length);

	//		memcpy(&*begin() + where_pos, &*begin() + where_pos + insert_length, remain_length * sizeof(reference));

	//		memcpy(&*begin() + where_pos, &*insert_iter_first, insert_length * sizeof(reference));
	//	}

	//	inline size_type size(void) const
	//	{
	//		return num_elements;
	//	}

	//	inline void resize(size_type new_size)
	//	{
	//		assert(new_size <= max_elements);

	//		if(base_vector_class::size() <= new_size)
	//		{
	//			base_vector_class::resize((new_size / increment + 1) * increment);
	//		}

	//		num_elements = new_size;
	//	}

	//	inline void resize(size_type new_size, const elemT & elem)
	//	{
	//		size_type old_size = size();

	//		resize(new_size);

	//		if(old_size < size())
	//		{
	//			iterator elem_iter = begin() + old_size;
	//			for(; elem_iter != end(); elem_iter++)
	//			{
	//				*elem_iter = elem;
	//			}
	//		}
	//	}

	//	inline const_iterator end(void) const
	//	{
	//		return begin() + size();
	//	}

	//	inline iterator end(void)
	//	{
	//		return begin() + size();
	//	}

	//	inline const_reference operator [] (size_type i) const
	//	{
	//		assert(i < size());

	//		return base_vector_class::operator [] (i);
	//	}

	//	inline reference operator [] (size_type i)
	//	{
	//		assert(i < size());

	//		return base_vector_class::operator [] (i);
	//	}

	//	inline void clear(void)
	//	{
	//		resize(0);
	//	}
	//};

	typedef std::vector<Vec4<real> > VertexList;

	typedef std::vector<size_t> VertexIndexList;

	typedef std::vector<Vec4<real> > NormalList;

	typedef std::vector<Vec2<real> > UVList;

	typedef std::vector<Vec4<real> > ColorList;

	//typedef std::stack<VertexList> VertexListStack;

	//typedef std::stack<VertexIndexList> VertexIndexListStack;

	//typedef std::stack<NormalList> NormalListStack;

	//typedef std::stack<UVList> UVListStack;

	class VertexListContext
	{
	private:
		VertexList m_vertexList;

	public:
		const VertexList & getVertexList(void) const;

		VertexList & getVertexList(void);

		void pushVertex(real x, real y, real z);

		void pushVertex(real x, real y, real z, const Mat4<real> & mmat);

		void pushVertex(VertexList::const_reference vertex);

		void pushVertex(VertexList::const_reference vertex, const Mat4<real> & mmat);

		void pushVertexList(VertexList::const_iterator begin, VertexList::const_iterator end);

		void pushVertexList(VertexList::const_iterator begin, VertexList::const_iterator end, const Mat4<real> & mmat);

		void clearVertexList(void);

		void resizeVertexList(VertexList::size_type size);

		VertexList::size_type getVertexListSize(void) const;

		VertexList::reference vertexAt(VertexList::size_type i);

		VertexList::const_reference vertexAt(VertexList::size_type i) const;

		VertexList::iterator getVertexListBegin();

		VertexList::const_iterator getVertexListBegin() const;

		VertexList::iterator getVertexListEnd();

		VertexList::const_iterator getVertexListEnd() const;
	};

	class VertexIndexListContext
	{
	private:
		VertexIndexList m_vertexIndexList;

	public:
		const VertexIndexList & getVertexIndexList(void) const;

		VertexIndexList & getVertexIndexList(void);

		void pushVertexIndex(VertexIndexList::const_reference index);

		void pushVertexIndexList(VertexIndexList::const_iterator begin, VertexIndexList::const_iterator end);

		void clearVertexIndexList(void);

		void resizeVertexIndexList(VertexIndexList::size_type size);

		VertexIndexList::size_type getVertexIndexListSize(void) const;

		VertexIndexList::reference vertexIndexAt(VertexIndexList::size_type i);

		VertexIndexList::const_reference vertexIndexAt(VertexIndexList::size_type i) const;

		VertexIndexList::iterator getVertexIndexListBegin();

		VertexIndexList::const_iterator getVertexIndexListBegin() const;

		VertexIndexList::iterator getVertexIndexListEnd();

		VertexIndexList::const_iterator getVertexIndexListEnd() const;
	};

	class NormalListContext
	{
	private:
		NormalList m_normalList;

	public:
		const NormalList & getNormalList(void) const;

		NormalList & getNormalList(void);

		void pushNormal(real x, real y, real z);

		void pushNormal(real x, real y, real z, const Mat4<real> & mmat);

		void pushNormal(NormalList::const_reference normal);

		void pushNormal(NormalList::const_reference normal, const Mat4<real> & mmat);

		void pushNormalList(NormalList::const_iterator begin, NormalList::const_iterator end);

		void pushNormalList(NormalList::const_iterator begin, NormalList::const_iterator end, const Mat4<real> & mmat);

		void clearNormalList(void);

		void resizeNormalList(NormalList::size_type size);

		NormalList::size_type getNormalListSize(void) const;

		NormalList::reference normalAt(NormalList::size_type i);

		NormalList::const_reference normalAt(NormalList::size_type i) const;

		NormalList::iterator getNormalListBegin();

		NormalList::const_iterator getNormalListBegin() const;

		NormalList::iterator getNormalListEnd();

		NormalList::const_iterator getNormalListEnd() const;
	};

	class UVListContext
	{
	private:
		UVList m_uvList;

	public:
		const UVList & getUVList(void) const;

		UVList & getUVList(void);

		void pushUV(real u, real v);

		void pushUV(UVList::const_reference uv);

		void pushUVList(UVList::const_iterator begin, UVList::const_iterator end);

		void clearUVList(void);

		void resizeUVList(UVList::size_type size);

		UVList::size_type getUVListSize(void) const;

		UVList::reference uvAt(UVList::size_type i);

		UVList::const_reference uvAt(UVList::size_type i) const;

		UVList::iterator getUVListBegin();

		UVList::const_iterator getUVListBegin() const;

		UVList::iterator getUVListEnd();

		UVList::const_iterator getUVListEnd() const;
	};

	class ColorListContext
	{
	private:
		ColorList m_colorList;

	public:
		const ColorList & getColorList(void) const;

		ColorList & getColorList(void);

		void pushColor(real r, real g, real b, real a);

		void pushColor(ColorList::const_reference color);

		void pushColorList(ColorList::const_iterator begin, ColorList::const_iterator end);

		void clearColorList(void);

		void resizeColorList(ColorList::size_type size);

		void resizeColorList(ColorList::size_type size, ColorList::const_reference color);

		ColorList::size_type getColorListSize(void) const;

		ColorList::reference colorAt(ColorList::size_type i);

		ColorList::const_reference colorAt(ColorList::size_type i) const;

		ColorList::iterator getColorListBegin();

		ColorList::const_iterator getColorListBegin() const;

		ColorList::iterator getColorListEnd();

		ColorList::const_iterator getColorListEnd() const;
	};

	class SurfaceContext
	{
	private:
		void * m_surfaceBuffer;

		DWORD m_surfacePitch;

		DWORD m_surfaceWidth;

		DWORD m_surfaceHeight;

	public:
		void setSurfaceBuffer(void * pbuffer);

		void setSurfaceBuffer(void * pbuffer, DWORD pitch, DWORD width, DWORD height);

		void * getSurfaceBuffer(void) const;

		void setSurfacePitch(DWORD pitch);

		DWORD getSurfacePitch(void) const;

		void setSurfaceWidth(DWORD width);

		DWORD getSurfaceWidth(void) const;

		void setSurfaceHeight(DWORD height);

		DWORD getSurfaceHeight(void) const;

	public:
		SurfaceRef<uint16> getSurfaceRef16(void) const;

		SurfaceRef<uint32> getSurfaceRef32(void) const;
	};

	class ZBufferContext
	{
	private:
		void * m_zbufferBuffer;

		DWORD m_zbufferPitch;

		DWORD m_zbufferWidth;

		DWORD m_zbufferHeight;

	public:
		void setZBufferBuffer(void * pbuffer);

		void setZBufferBuffer(void * pbuffer, DWORD pitch, DWORD width, DWORD height);

		void * getZBufferBuffer(void) const;

		void setZBufferPitch(DWORD pitch);

		DWORD getZBufferPitch(void) const;

		void setZBufferWidth(DWORD width);

		DWORD getZBufferWidth(void) const;

		void setZBufferHeight(DWORD height);

		DWORD getZBufferHeight(void) const;

	public:
		SurfaceRef<fixp28> getZBufferRef28(void) const;
	};

	class TextureContext
	{
	private:
		void * m_textureBuffer;

		DWORD m_texturePitch;

		DWORD m_textureWidth;

		DWORD m_textureHeight;

	public:
		void setTextureBuffer(void * pbuffer);

		void setTextureBuffer(void * pbuffer, DWORD pitch, DWORD width, DWORD height);

		void * getTextureBuffer(void) const;

		void setTexturePitch(DWORD pitch);

		DWORD getTexturePitch(void) const;

		void setTextureWidth(DWORD width);

		DWORD getTextureWidth(void) const;

		void setTextureHeight(DWORD height);

		DWORD getTextureHeight(void) const;

	public:
		SurfaceRef<uint16> getTextureRef16(void) const;

		SurfaceRef<uint32> getTextureRef32(void) const;
	};

	//typedef std::vector<TextureContext> TextureContextList;

	//class TextureListContext
	//{
	//protected:
	//	TextureContextList m_textureList;

	//public:
	//	const TextureContextList & getTextureList(void) const;

	//	TextureContextList & getTextureList(void);

	//	void pushTexture(TextureContextList::const_reference texture);

	//	void pushTextureList(TextureContextList::const_iterator begin, TextureContextList::const_iterator end);

	//	void clearTextureList(void);

	//	//void resizeTextureList(TextureContextList::size_type size);

	//	void resizeTextureList(TextureContextList::size_type size, TextureContextList::const_reference texture);

	//	TextureContextList::size_type getTextureListSize(void) const;

	//	TextureContextList::reference textureAt(TextureContextList::size_type i);

	//	TextureContextList::const_reference textureAt(TextureContextList::size_type i) const;

	//	TextureContextList::iterator getTextureListBegin();

	//	TextureContextList::const_iterator getTextureListBegin() const;

	//	TextureContextList::iterator getTextureListEnd();

	//	TextureContextList::const_iterator getTextureListEnd() const;
	//};

	//typedef std::vector<size_t> TextureIndexList;

	//class TextureIndexListContext
	//{
	//protected:
	//	TextureIndexList m_textureIndexList;

	//public:
	//	const TextureIndexList & getTextureIndexList(void) const;

	//	TextureIndexList & getTextureIndexList(void);

	//	void pushTextureIndex(TextureIndexList::const_reference index);

	//	void pushTextureIndexList(TextureIndexList::const_iterator begin, TextureIndexList::const_iterator end);

	//	void clearTextureIndexList(void);

	//	void resizeTextureIndexList(TextureIndexList::size_type size);

	//	TextureIndexList::size_type getTextureIndexListSize(void) const;

	//	TextureIndexList::reference textureIndexAt(TextureIndexList::size_type i);

	//	TextureIndexList::const_reference textureIndexAt(TextureIndexList::size_type i) const;

	//	TextureIndexList::iterator getTextureIndexListBegin();

	//	TextureIndexList::const_iterator getTextureIndexListBegin() const;

	//	TextureIndexList::iterator getTextureIndexListEnd();

	//	TextureIndexList::const_iterator getTextureIndexListEnd() const;
	//};

	class ClipperContext
	{
	private:
		RECT m_clipper;

	public:
		void setClipperRect(const RECT & clipper);

		const RECT & getClipperRect(void) const;
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
	private:
		MATERIAL m_material;

	public:
		void setMaterial(const MATERIAL & material);

		const MATERIAL & getMaterial(void) const;

	public:
		void setAmbient(const Vec4<real> & ambient);

		void setDiffuse(const Vec4<real> & diffuse);

		void setSpecular(const Vec4<real> & specular);

		void setEmissive(const Vec4<real> & emissive);
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
	private:
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
		const LightList & getLightList(void) const;

		LightList & getLightList(void);

		size_t pushLightAmbient(const Vec4<real> & ambient, LIGHT_STATE state = LS_ON);

		size_t pushLightDirectional(const Vec4<real> & diffuse, const Vec4<real> dir, LIGHT_STATE state = LS_ON);

		size_t pushLightPoint(const Vec4<real> & diffuse, const Vec4<real> pos, real kc = 1.0f, real kl = 0.001f, real kq = 0.00001f, LIGHT_STATE state = LS_ON);

		void clearLightList(void);

		void resizeLightList(LightList::size_type size);

		LightList::size_type getLightListSize(void) const;

		LightList::reference lightAt(LightList::size_type i);

		LightList::const_reference lightAt(LightList::size_type i) const;

		LightList::iterator getLightListBegin();

		LightList::const_iterator getLightListBegin() const;

		LightList::iterator getLightListEnd();

		LightList::const_iterator getLightListEnd() const;
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
		//Vec4<real> vpos;
		Mat4<real> mcam;
		Vec2<real> proj;
		real nz;
		real fz;
		RECT viewport;
	};

	class CameraContext
	{
	private:
		CAMERA m_camera;

	public:
		static Mat4<real> buildCameraTransformEular(const Vec4<real> & pos, const Vec4<real> & rot, DWORD rot_seq = RS_ZXY);

		static Mat4<real> buildInverseCameraTransformEular(const Vec4<real> & pos, const Vec4<real> & rot, DWORD rot_seq = RS_ZXY);

		static Mat4<real> buildInverseCameraTransformUVN(const Vec4<real> & pos, const Vec4<real> & target, const Vec4<real> & up);

		static Mat4<real> buildInverseCameraTransformQuat(const Vec4<real> & pos, const Quat<real> & ori);

		static Vec2<real> buildCameraProjectionFOVWidth(real fov, DWORD width, DWORD height);

		static Vec2<real> buildCameraProjectionFOVHeight(real fov, DWORD width, DWORD height);

		static Vec2<real> buildCameraProjectionFOVAuto(real fov, DWORD width, DWORD height);

		static real calculateCameraHalfFovX(const Vec2<real> & proj);

		static real calculateCameraHalfFovY(const Vec2<real> & proj);

		static real calculateCameraMaxHalfFov(const Vec2<real> & proj);

		static Vec4<real> calculateCameraDirection(const Mat4<real> & mcam);

	public:
		//void setCameraPosition(const Vec4<real> & vpos);

		//const Vec4<real> & getCameraPosition(void) const;

		void setCameraMatrix(const Mat4<real> & mcam);

		const Mat4<real> & getCameraMatrix(void) const;

		void setCameraProjection(const Vec2<real> & proj);

		const Vec2<real> & getCameraProjection(void) const;

		void setCameraNearZ(real nz);

		real getCameraNearZ(void) const;

		void setCameraFarZ(real fz);

		real getCameraFarZ(void) const;

		void setViewport(const RECT & viewport);

		const RECT & getViewport(void) const;

		//const CAMERA & getCamera(void) const;

	public:
		Vec4<real> getCameraPosition(void) const;
	};

	enum TRI_STATE
	{
		TS_ACTIVE,
		TS_CULLED,
		TS_CLIPPED,
		//TS_LARGE_CLIPPED,
		TS_BACKFACE,
	};

	typedef std::vector<TRI_STATE> TriStateList;

	class TriangleStateListContext
	{
	private:
		TriStateList m_triStateList;

	public:
		static bool isTriVisible(TRI_STATE state);

	public:
		const TriStateList & getTriStateList(void) const;

		TriStateList & getTriStateList(void);

		void pushTriState(TRI_STATE state);

		void pushTriStateList(TriStateList::const_iterator begin, TriStateList::const_iterator end);

		void clearTriStateList(void);

		void resizeTriStateList(TriStateList::size_type size);

		void resizeTriStateList(TriStateList::size_type size, TriStateList::const_reference state);

		TriStateList::size_type getTriStateListSize(void) const;

		TriStateList::reference triStateAt(TriStateList::size_type i);

		TriStateList::const_reference triStateAt(TriStateList::size_type i) const;

		TriStateList::iterator getTriStateListBegin();

		TriStateList::const_iterator getTriStateListBegin() const;

		TriStateList::iterator getTriStateListEnd();

		TriStateList::const_iterator getTriStateListEnd() const;
	};

	class TriangleContext
		: virtual public VertexListContext
		, virtual public VertexIndexListContext
		, virtual public NormalListContext
		, virtual public UVListContext
		, virtual public ColorListContext
		, virtual public SurfaceContext
		, virtual public ZBufferContext
		, virtual public TextureContext
		//, virtual public TextureListContext
		//, virtual public TextureIndexListContext
		, virtual public ClipperContext
		, virtual public MaterialContext
		, virtual public LightListContext
		, virtual public CameraContext
		, virtual public TriangleStateListContext
	{
	};

	class RenderLineListZBufferRW
		: public TriangleContext
	{
	protected:
		TRI_STATE zClipLineAtCamera(const size_t index);

		TRI_STATE sClipLineAtScreen(const size_t index);

	public:
		void reset(void);

		void worldToCamera(void);

		void zClipAtCamera(void);

		void cameraToScreen(void);

		void sClipAtScreen(void);

		void drawLineList16(const Vec4<real> & color);

		void drawLineList32(const Vec4<real> & color);
	};

	class RenderLineIndexListZBufferRW
		: public TriangleContext
	{
	protected:
		TRI_STATE zClipLineAtCamera(const size_t index);

		TRI_STATE sClipLineAtScreen(const size_t index);

	public:
		void reset(void);

		void worldToCamera(void);

		void zClipAtCamera(void);

		void cameraToScreen(void);

		void sClipAtScreen(void);

		void drawLineIndexList16(const Vec4<real> & color);

		void drawLineIndexList32(const Vec4<real> & color);
	};

	class RenderTriangleListWireZBufferRW
		: public TriangleContext
	{
	protected:
		void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

		void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

		TRI_STATE zClipTriangleAtCamera(const size_t index);

		TRI_STATE sClipTriangleAtScreen(const size_t index);

	public:
		void reset(void);

		void removeBackfaceAtWorld(void);

		void worldToCamera(void);

		void zClipAtCamera(void);

		void cameraToScreen(void);

		void sClipAtScreen(void);

		void drawTriangleList16(const Vec4<real> & color);

		void drawTriangleList32(const Vec4<real> & color);

		void drawTriangleListWithoutThird16(const Vec4<real> & color);

		void drawTriangleListWithoutThird32(const Vec4<real> & color);
	};

	class RenderTriangleIndexListWireZBufferRW
		: public TriangleContext
	{
	protected:
		void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

		void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

		TRI_STATE zClipTriangleAtCamera(const size_t index);

		TRI_STATE sClipTriangleAtScreen(const size_t index);

	public:
		void reset(void);

		void removeBackfaceAtWorld(void);

		void worldToCamera(void);

		void zClipAtCamera(void);

		void cameraToScreen(void);

		void sClipAtScreen(void);

		void drawTriangleIndexList16(const Vec4<real> & color);

		void drawTriangleIndexList32(const Vec4<real> & color);

		void drawTriangleIndexListWithoutThird16(const Vec4<real> & color);

		void drawTriangleIndexListWithoutThird32(const Vec4<real> & color);
	};

	class RenderTriangleListSolidZBufferRW
		: public RenderTriangleListWireZBufferRW
	{
	public:
		void drawTriangleList16(const Vec4<real> & color);

		void drawTriangleList32(const Vec4<real> & color);
	};

	class RenderTriangleIndexListSolidZBufferRW
		: public RenderTriangleIndexListWireZBufferRW
	{
	public:
		void drawTriangleIndexList16(const Vec4<real> & color);

		void drawTriangleIndexList32(const Vec4<real> & color);
	};

	class RenderTriangleListGouraudZBufferRW
		: public TriangleContext
	{
	protected:
		void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

		void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

		TRI_STATE zClipTriangleAtCamera(const size_t index);

		TRI_STATE sClipTriangleAtScreen(const size_t index);

	public:
		void reset(void);

		void removeBackfaceAtWorld(void);

		void lightAtWorld(void);

		void worldToCamera(void);

		void zClipAtCamera(void);

		void cameraToScreen(void);

		void sClipAtScreen(void);

		void drawTriangleList16(void);

		void drawTriangleList32(void);
	};

	class RenderTriangleIndexListGouraudZBufferRW
		: public TriangleContext
	{
	protected:
		void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

		void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

		TRI_STATE zClipTriangleAtCamera(const size_t index);

		TRI_STATE sClipTriangleAtScreen(const size_t index);

	public:
		void reset(void);

		void removeBackfaceAtWorld(void);

		void lightAtWorld(void);

		void worldToCamera(void);

		void zClipAtCamera(void);

		void cameraToScreen(void);

		void sClipAtScreen(void);

		void drawTriangleIndexList16(void);

		void drawTriangleIndexList32(void);
	};

	class RenderTriangleListTextureZBufferRW
		: public TriangleContext
	{
	protected:
		void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

		void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

		TRI_STATE zClipTriangleAtCamera(const size_t index);

		TRI_STATE sClipTriangleAtScreen(const size_t index);

	public:
		void reset(void);

		void removeBackfaceAtWorld(void);

		void worldToCamera(void);

		void zClipAtCamera(void);

		void cameraToScreen(void);

		void sClipAtScreen(void);

		void drawTriangleListZBufferW16(void);

		void drawTriangleListZBufferW32(void);

		void drawTriangleList16(void);

		void drawTriangleList32(void);
	};

	class RenderTriangleIndexListTextureZBufferRW
		: public TriangleContext
	{
	protected:
		void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

		void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

		TRI_STATE zClipTriangleAtCamera(const size_t index);

		TRI_STATE sClipTriangleAtScreen(const size_t index);

	public:
		void reset(void);

		void removeBackfaceAtWorld(void);

		void worldToCamera(void);

		void zClipAtCamera(void);

		void cameraToScreen(void);

		void sClipAtScreen(void);

		void drawTriangleIndexListZBufferW16(void);

		void drawTriangleIndexListZBufferW32(void);

		void drawTriangleIndexList16(void);

		void drawTriangleIndexList32(void);
	};

	class RenderTriangleListTexturePerspectiveLPZBufferRW
		: public RenderTriangleListTextureZBufferRW
	{
	public:
		void drawTriangleListZBufferW16(void);

		void drawTriangleListZBufferW32(void);

		void drawTriangleList16(void);

		void drawTriangleList32(void);
	};

	class RenderTriangleIndexListTexturePerspectiveLPZBufferRW
		: public RenderTriangleIndexListTextureZBufferRW
	{
	public:
		void drawTriangleIndexListZBufferW16(void);

		void drawTriangleIndexListZBufferW32(void);

		void drawTriangleIndexList16(void);

		void drawTriangleIndexList32(void);
	};

	class RenderTriangleListGouraudTextureZBufferRW
		: public TriangleContext
	{
	protected:
		void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

		void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

		TRI_STATE zClipTriangleAtCamera(const size_t index);

		TRI_STATE sClipTriangleAtScreen(const size_t index);

	public:
		void reset(void);

		void removeBackfaceAtWorld(void);

		void lightAtWorld(void);

		void worldToCamera(void);

		void zClipAtCamera(void);

		void cameraToScreen(void);

		void sClipAtScreen(void);

		void drawTriangleList16(void);

		void drawTriangleList32(void);
	};

	class RenderTriangleIndexListGouraudTextureZBufferRW
		: public TriangleContext
	{
	protected:
		void zClipTriangleAtCameraNearZDouble(const size_t index, DWORD clip_mask_nz);

		void zClipTriangleAtCameraNearZSingle(const size_t index, DWORD clip_mask_nz);

		TRI_STATE zClipTriangleAtCamera(const size_t index);

		TRI_STATE sClipTriangleAtScreen(const size_t index);

	public:
		void reset(void);

		void removeBackfaceAtWorld(void);

		void lightAtWorld(void);

		void worldToCamera(void);

		void zClipAtCamera(void);

		void cameraToScreen(void);

		void sClipAtScreen(void);

		void drawTriangleIndexList16(void);

		void drawTriangleIndexList32(void);
	};

	class RenderTriangleListGouraudTexturePerspectiveLPZBufferRW
		: public RenderTriangleListGouraudTextureZBufferRW
	{
	public:
		void drawTriangleList16(void);

		void drawTriangleList32(void);
	};

	class RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW
		: public RenderTriangleIndexListGouraudTextureZBufferRW
	{
	public:
		void drawTriangleIndexList16(void);

		void drawTriangleIndexList32(void);
	};

	class RenderContext
		: public RenderLineListZBufferRW
		, public RenderLineIndexListZBufferRW
		//, public RenderTriangleListWireZBufferRW
		//, public RenderTriangleIndexListWireZBufferRW
		, public RenderTriangleListSolidZBufferRW
		, public RenderTriangleIndexListSolidZBufferRW
		, public RenderTriangleListGouraudZBufferRW
		, public RenderTriangleIndexListGouraudZBufferRW
		//, public RenderTriangleListTextureZBufferRW
		//, public RenderTriangleIndexListTextureZBufferRW
		//, public RenderTriangleListGouraudTextureZBufferRW
		//, public RenderTriangleIndexListGouraudTextureZBufferRW
		, public RenderTriangleListTexturePerspectiveLPZBufferRW
		, public RenderTriangleIndexListTexturePerspectiveLPZBufferRW
		, public RenderTriangleListGouraudTexturePerspectiveLPZBufferRW
		, public RenderTriangleIndexListGouraudTexturePerspectiveLPZBufferRW
	{
	public:
		RenderContext(void);

		virtual ~RenderContext(void);

	public:
		virtual void drawLineListZBufferRW(const Vec4<real> & color) = 0;

		virtual void drawLineIndexListZBufferRW(const Vec4<real> & color) = 0;

		virtual void drawTriangleListWireZBufferRW(const Vec4<real> & color) = 0;

		virtual void drawTriangleIndexListWireZBufferRW(const Vec4<real> & color) = 0;

		virtual void drawTriangleListWireZBufferRWWithoutThird(const Vec4<real> & color) = 0;

		virtual void drawTriangleIndexListWireZBufferRWWithoutThird(const Vec4<real> & color) = 0;

		virtual void drawTriangleListWireZBufferRWWithBackface(const Vec4<real> & color) = 0;

		virtual void drawTriangleIndexListWireZBufferRWWithBackface(const Vec4<real> & color) = 0;

		virtual void drawTriangleListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color) = 0;

		virtual void drawTriangleIndexListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color) = 0;

		virtual void drawTriangleListSolidZBufferRW(const Vec4<real> & color) = 0;

		virtual void drawTriangleIndexListSolidZBufferRW(const Vec4<real> & color) = 0;

		virtual void drawTriangleListSolidZBufferRWWithBackface(const Vec4<real> & color) = 0;

		virtual void drawTriangleIndexListSolidZBufferRWWithBackface(const Vec4<real> & color) = 0;

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

	class RenderContext16
		: virtual public RenderContext
	{
	public:
		void drawLineListZBufferRW(const Vec4<real> & color);

		void drawLineIndexListZBufferRW(const Vec4<real> & color);

		void drawTriangleListWireZBufferRW(const Vec4<real> & color);

		void drawTriangleIndexListWireZBufferRW(const Vec4<real> & color);

		void drawTriangleListWireZBufferRWWithoutThird(const Vec4<real> & color);

		void drawTriangleIndexListWireZBufferRWWithoutThird(const Vec4<real> & color);

		void drawTriangleListWireZBufferRWWithBackface(const Vec4<real> & color);

		void drawTriangleIndexListWireZBufferRWWithBackface(const Vec4<real> & color);

		void drawTriangleListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color);

		void drawTriangleIndexListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color);

		void drawTriangleListSolidZBufferRW(const Vec4<real> & color);

		void drawTriangleIndexListSolidZBufferRW(const Vec4<real> & color);

		void drawTriangleListSolidZBufferRWWithBackface(const Vec4<real> & color);

		void drawTriangleIndexListSolidZBufferRWWithBackface(const Vec4<real> & color);

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
		void drawLineListZBufferRW(const Vec4<real> & color);

		void drawLineIndexListZBufferRW(const Vec4<real> & color);

		void drawTriangleListWireZBufferRW(const Vec4<real> & color);

		void drawTriangleIndexListWireZBufferRW(const Vec4<real> & color);

		void drawTriangleListWireZBufferRWWithoutThird(const Vec4<real> & color);

		void drawTriangleIndexListWireZBufferRWWithoutThird(const Vec4<real> & color);

		void drawTriangleListWireZBufferRWWithBackface(const Vec4<real> & color);

		void drawTriangleIndexListWireZBufferRWWithBackface(const Vec4<real> & color);

		void drawTriangleListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color);

		void drawTriangleIndexListWireZBufferRWWithBackfaceWithoutThird(const Vec4<real> & color);

		void drawTriangleListSolidZBufferRW(const Vec4<real> & color);

		void drawTriangleIndexListSolidZBufferRW(const Vec4<real> & color);

		void drawTriangleListSolidZBufferRWWithBackface(const Vec4<real> & color);

		void drawTriangleIndexListSolidZBufferRWWithBackface(const Vec4<real> & color);

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
}

#endif // __T3DLIB6_H__
