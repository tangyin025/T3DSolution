
#ifndef __MYSCENE_H__
#define __MYSCENE_H__

#include "myCommon.h"
#include <boost/shared_ptr.hpp>
#include "myUtility.h"

namespace my
{
	//class CustomShaderObject
	//{
	//public:
	//	virtual void draw(t3d::RenderContext * rc) const = 0;

	//public:
	//	virtual ~CustomShaderObject(void);
	//};

	//typedef boost::shared_ptr<CustomShaderObject> CustomShaderObjectPtr;

	//typedef std::vector<CustomShaderObjectPtr> CustomShaderObjectPtrList;

	//class CustomShaderObjectPtrListContext
	//{
	//private:
	//	CustomShaderObjectPtrList m_customShaderObjList;

	//public:
	//	const CustomShaderObjectPtrList & getCustomShaderObjList(void) const;

	//	CustomShaderObjectPtrList & getCustomShaderObjList(void);

	//	void pushCustomShaderObj(CustomShaderObjectPtrList::const_reference obj);

	//	void pushCustomShaderObjList(CustomShaderObjectPtrList::const_iterator begin, CustomShaderObjectPtrList::const_iterator end);

	//	void clearCustomShaderObjList(void);

	//	void resizeCustomShaderObjList(CustomShaderObjectPtrList::size_type size);

	//	CustomShaderObjectPtrList::size_type getCustomShaderObjListSize(void) const;

	//	CustomShaderObjectPtrList::reference customShaderObjAt(CustomShaderObjectPtrList::size_type i);

	//	CustomShaderObjectPtrList::const_reference customShaderObjAt(CustomShaderObjectPtrList::size_type i) const;

	//	CustomShaderObjectPtrList::iterator getCustomShaderObjListBegin(void);

	//	CustomShaderObjectPtrList::const_iterator getCustomShaderObjListBegin(void) const;

	//	CustomShaderObjectPtrList::iterator getCustomShaderObjListEnd(void);

	//	CustomShaderObjectPtrList::const_iterator getCustomShaderObjListEnd(void) const;

	//public:
	//	void draw(t3d::RenderContext * rc) const;
	//};

	class BSPNode;

	typedef boost::shared_ptr<BSPNode> BSPNodePtr;

	class BSPNode
		//: public ObjectBase
	{
	public:
		t3d::Vec4<real> planePoint;

		t3d::Vec4<real> planeNormal;

		BSPNodePtr front;

		BSPNodePtr back;

		//CustomShaderObjectPtrListContext m_customShaderObjList;

		ObjectBasePtr m_obj;

	public:
		void drawWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) const;

		void drawWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) const;

		void drawWireZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) const;

		void drawWireZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) const;

		void drawZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) const;

		void drawZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) const;

		void drawZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) const;

		void drawZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) const;

		void drawGouraudZBufferRW(
			t3d::RenderContext * rc) const;

		void drawGouraudZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

		void drawGouraudZBufferRWWithBackface(
			t3d::RenderContext * rc) const;

		void drawGouraudZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

		void drawTextureZBufferW(
			t3d::RenderContext * rc) const;

		void drawTextureZBufferW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTextureZBufferWWithBackface(
			t3d::RenderContext * rc) const;

		void drawTextureZBufferWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTexturePerspectiveLPZBufferW(
			t3d::RenderContext * rc) const;

		void drawTexturePerspectiveLPZBufferW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTexturePerspectiveLPZBufferWWithBackface(
			t3d::RenderContext * rc) const;

		void drawTexturePerspectiveLPZBufferWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTextureZBufferRW(
			t3d::RenderContext * rc) const;

		void drawTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTextureZBufferRWWithBackface(
			t3d::RenderContext * rc) const;

		void drawTextureZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc) const;

		void drawTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc) const;

		void drawTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawGouraudTextureZBufferRW(
			t3d::RenderContext * rc) const;

		void drawGouraudTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

		void drawGouraudTextureZBufferRWWithBackface(
			t3d::RenderContext * rc) const;

		void drawGouraudTextureZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

		void drawGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc) const;

		void drawGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

		void drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc) const;

		void drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;
	};

	BSPNodePtr buildBSPScene(
		const t3d::VertexList & vertexList,
		const t3d::NormalList & normalList,
		const t3d::UVList & uvList);

	//BSPNodePtr buildBalanceBSPScene(
	//	int & deepth,
	//	const t3d::VertexList & vertexList,
	//	const t3d::NormalList & normalList,
	//	const t3d::UVList & uvList);

	//void insertObjectToBSPScene(
	//	BSPNodePtr node,
	//	const CustomShaderObjectPtr & customShaderObj,
	//	const t3d::VertexList & objVertexList);

	//void insertObjectToBSPScene(
	//	BSPNodePtr node,
	//	CustomShaderObjectPtrList::const_iterator begin, CustomShaderObjectPtrList::const_iterator end);

	//void insertObjectToBSPScene(
	//	BSPNodePtr node,
	//	const CustomShaderObjectPtrList & objPtrList);

	//typedef std::vector<ObjectBasePtr> ObjectBasePtrList;

	//ObjectBasePtrList buildBoneAssignmentIndexObjectPtrListFromOgreMesh(
	//	IOStreamPtr meshStream);

	class LODTriNode;

	typedef boost::shared_ptr<LODTriNode> LODTriNodePtr;

	class LODTriNode
		: public t3d::VertexListContext
		, public t3d::NormalListContext
		, public t3d::UVListContext
	{
	public:
		real minDistanceSquare;

		LODTriNodePtr lchild;

		LODTriNodePtr rchild;

	public:
		void prepareVertexList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos) const;

		void prepareVertexList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos,
			const t3d::Mat4<real> & mmat) const;

		void prepareVertexNormalList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos) const;

		void prepareVertexNormalList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

		void prepareVertexUVList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos) const;

		void prepareVertexUVList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos,
			const t3d::Mat4<real> & mmat) const;

		void prepareVertexNormalUVList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos) const;

		void prepareVertexNormalUVList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;
	};

	class LODTriNodeList
		: public ObjectBase
		, public std::vector<LODTriNodePtr>
	{
	public:
		void prepareVertexList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos) const;

		void prepareVertexList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos,
			const t3d::Mat4<real> & mmat) const;

		void prepareVertexNormalList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos) const;

		void prepareVertexNormalList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

		void prepareVertexUVList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos) const;

		void prepareVertexUVList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos,
			const t3d::Mat4<real> & mmat) const;

		void prepareVertexNormalUVList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos) const;

		void prepareVertexNormalUVList(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & cameraPos,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

	public:
		void drawWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) const;

		void drawWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) const;

		void drawWireZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) const;

		void drawWireZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) const;

		void drawZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) const;

		void drawZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) const;

		void drawZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color) const;

		void drawZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat) const;

		void drawGouraudZBufferRW(
			t3d::RenderContext * rc) const;

		void drawGouraudZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

		void drawGouraudZBufferRWWithBackface(
			t3d::RenderContext * rc) const;

		void drawGouraudZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

		void drawTextureZBufferW(
			t3d::RenderContext * rc) const;

		void drawTextureZBufferW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTextureZBufferWWithBackface(
			t3d::RenderContext * rc) const;

		void drawTextureZBufferWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTexturePerspectiveLPZBufferW(
			t3d::RenderContext * rc) const;

		void drawTexturePerspectiveLPZBufferW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTexturePerspectiveLPZBufferWWithBackface(
			t3d::RenderContext * rc) const;

		void drawTexturePerspectiveLPZBufferWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTextureZBufferRW(
			t3d::RenderContext * rc) const;

		void drawTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTextureZBufferRWWithBackface(
			t3d::RenderContext * rc) const;

		void drawTextureZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc) const;

		void drawTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc) const;

		void drawTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat) const;

		void drawGouraudTextureZBufferRW(
			t3d::RenderContext * rc) const;

		void drawGouraudTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

		void drawGouraudTextureZBufferRWWithBackface(
			t3d::RenderContext * rc) const;

		void drawGouraudTextureZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

		void drawGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc) const;

		void drawGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;

		void drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc) const;

		void drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot) const;
	};

	typedef boost::shared_ptr<LODTriNodeList> LODTriNodeListPtr;

	LODTriNodePtr buildLODTriNode(
		const t3d::Vec4<real> v0,
		const t3d::Vec4<real> v1,
		const t3d::Vec4<real> v2,
		const t3d::Vec4<real> n0,
		const t3d::Vec4<real> n1,
		const t3d::Vec4<real> n2,
		const t3d::Vec2<real> t0,
		const t3d::Vec2<real> t1,
		const t3d::Vec2<real> t2,
		real levelDistance);

	BSPNodePtr buildBSPSceneWithLODTriNode(
		const t3d::VertexList & vertexList,
		const t3d::NormalList & normalList,
		const t3d::UVList & uvList,
		real levelDistance);

	class CustomShaderObject
	{
	public:
		virtual ~CustomShaderObject(void)
		{
		}

	public:
		virtual void draw(t3d::RenderContext * rc) const = 0;

		virtual void draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const = 0;
	};

	typedef boost::shared_ptr<CustomShaderObject> CustomShaderObjectPtr;

	class CustomShaderObjectPtrList
		: public CustomShaderObject
		, public std::vector<CustomShaderObjectPtr>
	{
	public:
		void draw(t3d::RenderContext * rc) const
		{
			const_iterator obj_iter = begin();
			for(; obj_iter != end(); obj_iter++)
			{
				(*obj_iter)->draw(rc);
			}
		}

		void draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
		{
			const_iterator obj_iter = begin();
			for(; obj_iter != end(); obj_iter++)
			{
				(*obj_iter)->draw(rc, mmat, mrot);
			}
		}
	};

#define DEFINE_CUSTOM_SHADER_OBJECT_RCM(expr) \
	class CustomShaderObject##expr \
		: public CustomShaderObject \
		, public Object \
	{ \
	protected: \
		t3d::Vec4<real> m_color; \
	public: \
		CustomShaderObject##expr(const t3d::Vec4<real> & color) \
			: m_color(color) \
		{ \
		} \
		void draw(t3d::RenderContext * rc) const \
		{ \
			draw##expr(rc, m_color); \
		} \
		void draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const \
		{ \
			draw##expr(rc, m_color, mmat); mrot; \
		} \
	}

#define DEFINE_CUSTOM_SHADER_OBJECT_RMM(expr) \
	class CustomShaderObject##expr \
		: public CustomShaderObject \
		, public Object \
	{ \
	public: \
		CustomShaderObject##expr(void) \
		{ \
		} \
		void draw(t3d::RenderContext * rc) const \
		{ \
			draw##expr(rc); \
		} \
		void draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const \
		{ \
			draw##expr(rc, mmat, mrot); \
		} \
	}

#define DEFINE_CUSTOM_SHADER_OBJECT_RM(expr) \
	class CustomShaderObject##expr \
		: public CustomShaderObject \
		, public Object \
	{ \
	public: \
		CustomShaderObject##expr(void) \
		{ \
		} \
		void draw(t3d::RenderContext * rc) const \
		{ \
			draw##expr(rc); \
		} \
		void draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const \
		{ \
			draw##expr(rc, mmat); mrot; \
		} \
	}

	DEFINE_CUSTOM_SHADER_OBJECT_RCM(WireZBufferRW);

	DEFINE_CUSTOM_SHADER_OBJECT_RCM(WireZBufferRWWithBackface);

	DEFINE_CUSTOM_SHADER_OBJECT_RCM(ZBufferRW);

	DEFINE_CUSTOM_SHADER_OBJECT_RCM(ZBufferRWWithBackface);

	DEFINE_CUSTOM_SHADER_OBJECT_RMM(GouraudZBufferRW);

	DEFINE_CUSTOM_SHADER_OBJECT_RMM(GouraudZBufferRWWithBackface);

	DEFINE_CUSTOM_SHADER_OBJECT_RM(TextureZBufferW);

	DEFINE_CUSTOM_SHADER_OBJECT_RM(TextureZBufferWWithBackface);

	DEFINE_CUSTOM_SHADER_OBJECT_RM(TexturePerspectiveLPZBufferW);

	DEFINE_CUSTOM_SHADER_OBJECT_RM(TexturePerspectiveLPZBufferWWithBackface);

	DEFINE_CUSTOM_SHADER_OBJECT_RM(TextureZBufferRW);

	DEFINE_CUSTOM_SHADER_OBJECT_RM(TextureZBufferRWWithBackface);

	DEFINE_CUSTOM_SHADER_OBJECT_RM(TexturePerspectiveLPZBufferRW);

	DEFINE_CUSTOM_SHADER_OBJECT_RM(TexturePerspectiveLPZBufferRWWithBackface);

	DEFINE_CUSTOM_SHADER_OBJECT_RMM(GouraudTextureZBufferRW);

	DEFINE_CUSTOM_SHADER_OBJECT_RMM(GouraudTextureZBufferRWWithBackface);

	DEFINE_CUSTOM_SHADER_OBJECT_RMM(GouraudTexturePerspectiveLPZBufferRW);

	DEFINE_CUSTOM_SHADER_OBJECT_RMM(GouraudTexturePerspectiveLPZBufferRWWithBackface);

	class CustomShaderBSPNode
		: public CustomShaderObject
	{
	protected:
		t3d::Vec4<real> planePoint;

		t3d::Vec4<real> planeNormal;

		CustomShaderObjectPtr front;

		CustomShaderObjectPtr self;

		CustomShaderObjectPtr back;

	public:
		CustomShaderBSPNode(
			const t3d::Vec4<real> & _planePoint,
			const t3d::Vec4<real> & _planeNormal)
			: planePoint(_planePoint)
			, planeNormal(_planeNormal)
		{
		}
	};

	class BackToFrontCustomShaderBSPNode
		: public CustomShaderBSPNode
	{
	public:
		BackToFrontCustomShaderBSPNode(
			const t3d::Vec4<real> & _planePoint,
			const t3d::Vec4<real> & _planeNormal)
			: CustomShaderBSPNode(_planePoint, _planeNormal)
		{
		}

		void draw(t3d::RenderContext * rc) const;

		void draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const;
	};

	class FrontToBackCustomShaderBSPNode
		: public CustomShaderBSPNode
	{
	public:
		FrontToBackCustomShaderBSPNode(
			const t3d::Vec4<real> & _planePoint,
			const t3d::Vec4<real> & _planeNormal)
			: CustomShaderBSPNode(_planePoint, _planeNormal)
		{
		}

		void draw(t3d::RenderContext * rc) const;

		void draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const;
	};
}

#endif // __MYSCENE_H__
