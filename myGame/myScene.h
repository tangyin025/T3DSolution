
#ifndef __MYSCENE_H__
#define __MYSCENE_H__

#include "myCommon.h"
#include <boost/shared_ptr.hpp>
#include "myUtility.h"

namespace my
{
	class CustomShaderObject
	{
	public:
		virtual void draw(t3d::RenderContext * rc) = 0;

	public:
		virtual ~CustomShaderObject(void);
	};

	typedef boost::shared_ptr<CustomShaderObject> CustomShaderObjectPtr;

	typedef std::vector<CustomShaderObjectPtr> CustomShaderObjectPtrList;

	class CustomShaderObjectPtrListContext
	{
	private:
		CustomShaderObjectPtrList m_customShaderObjList;

	public:
		const CustomShaderObjectPtrList & getCustomShaderObjList(void) const;

		CustomShaderObjectPtrList & getCustomShaderObjList(void);

		void pushCustomShaderObj(CustomShaderObjectPtrList::const_reference obj);

		void pushCustomShaderObjList(CustomShaderObjectPtrList::const_iterator begin, CustomShaderObjectPtrList::const_iterator end);

		void clearCustomShaderObjList(void);

		void resizeCustomShaderObjList(CustomShaderObjectPtrList::size_type size);

		CustomShaderObjectPtrList::size_type getCustomShaderObjListSize(void) const;

		CustomShaderObjectPtrList::reference customShaderObjAt(CustomShaderObjectPtrList::size_type i);

		CustomShaderObjectPtrList::const_reference customShaderObjAt(CustomShaderObjectPtrList::size_type i) const;

		CustomShaderObjectPtrList::iterator getCustomShaderObjListBegin(void);

		CustomShaderObjectPtrList::const_iterator getCustomShaderObjListBegin(void) const;

		CustomShaderObjectPtrList::iterator getCustomShaderObjListEnd(void);

		CustomShaderObjectPtrList::const_iterator getCustomShaderObjListEnd(void) const;

	public:
		void draw(t3d::RenderContext * rc);
	};

	class BSPNode;

	typedef boost::shared_ptr<BSPNode> BSPNodePtr;

	class BSPNode
		: public Object
	{
	public:
		t3d::Vec4<real> planePoint;

		t3d::Vec4<real> planeNormal;

		BSPNodePtr front;

		BSPNodePtr back;

		CustomShaderObjectPtrListContext m_customShaderObjList;

	public:
		size_t getTriangleCount(void) const;

		const t3d::Vec4<real> & getTriangleVertex0(size_t i) const;

		const t3d::Vec4<real> & getTriangleVertex1(size_t i) const;

		const t3d::Vec4<real> & getTriangleVertex2(size_t i) const;

		const t3d::Vec4<real> & getTriangleNormal0(size_t i) const;

		const t3d::Vec4<real> & getTriangleNormal1(size_t i) const;

		const t3d::Vec4<real> & getTriangleNormal2(size_t i) const;

		const t3d::Vec2<real> & getTriangleUV0(size_t i) const;

		const t3d::Vec2<real> & getTriangleUV1(size_t i) const;

		const t3d::Vec2<real> & getTriangleUV2(size_t i) const;

	public:
		void drawWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawWireZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawWireZBufferRWWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawWireZBufferRWWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawWireZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawWireZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawWireZBufferRWWithBackfaceWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color);

		void drawWireZBufferRWWithBackfaceWithoutThird(
			t3d::RenderContext * rc,
			const t3d::Vec4<real> & color,
			const t3d::Mat4<real> & mmat);

		void drawGouraudZBufferRW(
			t3d::RenderContext * rc);

		void drawGouraudZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawGouraudZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawGouraudZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawTextureZBufferW(
			t3d::RenderContext * rc);

		void drawTextureZBufferW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTextureZBufferWWithBackface(
			t3d::RenderContext * rc);

		void drawTextureZBufferWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTexturePerspectiveLPZBufferW(
			t3d::RenderContext * rc);

		void drawTexturePerspectiveLPZBufferW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTexturePerspectiveLPZBufferWWithBackface(
			t3d::RenderContext * rc);

		void drawTexturePerspectiveLPZBufferWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTextureZBufferRW(
			t3d::RenderContext * rc);

		void drawTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTextureZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawTextureZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc);

		void drawTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawTexturePerspectiveLPZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat);

		void drawGouraudTextureZBufferRW(
			t3d::RenderContext * rc);

		void drawGouraudTextureZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawGouraudTextureZBufferRWWithBackface(
			t3d::RenderContext * rc);

		void drawGouraudTextureZBufferRWWithBackface(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);

		void drawGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc);

		void drawGouraudTexturePerspectiveLPZBufferRW(
			t3d::RenderContext * rc,
			const t3d::Mat4<real> & mmat,
			const t3d::Mat4<real> & mrot);
	};

	void splitTriangleVertexNormalUVUp(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexNormalUVDown(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexNormalUVLeft(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	void splitTriangleVertexNormalUVRight(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	bool splitTriangleVertexNormalUV(
		t3d::VertexList & lVertexList,
		t3d::NormalList & lNormalList,
		t3d::UVList & lUVList,
		t3d::VertexList & rVertexList,
		t3d::NormalList & rNormalList,
		t3d::UVList & rUVList,
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & v2,
		const t3d::Vec4<real> & n0,
		const t3d::Vec4<real> & n1,
		const t3d::Vec4<real> & n2,
		const t3d::Vec2<real> & t0,
		const t3d::Vec2<real> & t1,
		const t3d::Vec2<real> & t2,
		const t3d::Vec4<real> & planePoint,
		const t3d::Vec4<real> & planeNormal);

	BSPNodePtr buildBSPScene(
		const t3d::VertexList & vertexList,
		const t3d::NormalList & normalList,
		const t3d::UVList & uvList);

	void insertObjectToBSPScene(
		BSPNodePtr node,
		const CustomShaderObjectPtr & customShaderObj,
		const t3d::VertexList & objVertexList);

	//void insertObjectToBSPScene(
	//	BSPNodePtr node,
	//	CustomShaderObjectPtrList::const_iterator begin, CustomShaderObjectPtrList::const_iterator end);

	//void insertObjectToBSPScene(
	//	BSPNodePtr node,
	//	const CustomShaderObjectPtrList & objPtrList);

	//typedef std::vector<ObjectBasePtr> ObjectBasePtrList;

	//ObjectBasePtrList buildBoneAssignmentIndexObjectPtrListFromOgreMesh(
	//	IOStream * meshStream);

	//void pushVertexByDirectionProject(
	//	t3d::RenderContext * rc,
	//	const t3d::Vec4<real> & dir,
	//	const t3d::Vec4<real> & planePoint,
	//	const t3d::Vec4<real> & planeNormal,
	//	t3d::VertexList::const_iterator begin,
	//	t3d::VertexList::const_iterator end,
	//	const t3d::Mat4<real> & mmat);

	//void pushVertexByPointProject(
	//	t3d::RenderContext * rc,
	//	const t3d::Vec4<real> & point,
	//	const t3d::Vec4<real> & planePoint,
	//	const t3d::Vec4<real> & planeNormal,
	//	t3d::VertexList::const_iterator begin,
	//	t3d::VertexList::const_iterator end,
	//	const t3d::Mat4<real> & mmat);
}

#endif // __MYSCENE_H__
