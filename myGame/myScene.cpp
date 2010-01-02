
#include "stdafx.h"
#include "myScene.h"
#include <tinyxml.h>

namespace my
{
	//void CustomShaderObject::setObject(const ObjectBasePtr & obj)
	//{
	//	m_obj = obj;
	//}

	//const ObjectBasePtr & CustomShaderObject::getObject(void) const
	//{
	//	return m_obj;
	//}

	//CustomShaderObject::CustomShaderObject(const ObjectBasePtr & obj)
	//	: m_obj(obj)
	//{
	//}

	CustomShaderObject::~CustomShaderObject(void)
	{
	}

	const CustomShaderObjectPtrList & CustomShaderObjectPtrListContext::getCustomShaderObjList(void) const
	{
		return m_customShaderObjList;
	}

	CustomShaderObjectPtrList & CustomShaderObjectPtrListContext::getCustomShaderObjList(void)
	{
		return m_customShaderObjList;
	}

	void CustomShaderObjectPtrListContext::pushCustomShaderObj(CustomShaderObjectPtrList::const_reference obj)
	{
		getCustomShaderObjList().push_back(obj);
	}

	void CustomShaderObjectPtrListContext::pushCustomShaderObjList(CustomShaderObjectPtrList::const_iterator begin, CustomShaderObjectPtrList::const_iterator end)
	{
		getCustomShaderObjList().insert(getCustomShaderObjListBegin(), begin, end);
	}

	void CustomShaderObjectPtrListContext::clearCustomShaderObjList(void)
	{
		getCustomShaderObjList().clear();
	}

	void CustomShaderObjectPtrListContext::resizeCustomShaderObjList(CustomShaderObjectPtrList::size_type size)
	{
		getCustomShaderObjList().resize(size);
	}

	CustomShaderObjectPtrList::size_type CustomShaderObjectPtrListContext::getCustomShaderObjListSize(void) const
	{
		return getCustomShaderObjList().size();
	}

	CustomShaderObjectPtrList::reference CustomShaderObjectPtrListContext::customShaderObjAt(CustomShaderObjectPtrList::size_type i)
	{
		assert(i < getCustomShaderObjListSize());

		return getCustomShaderObjList()[i];
	}

	CustomShaderObjectPtrList::const_reference CustomShaderObjectPtrListContext::customShaderObjAt(CustomShaderObjectPtrList::size_type i) const
	{
		assert(i < getCustomShaderObjListSize());

		return getCustomShaderObjList()[i];
	}

	CustomShaderObjectPtrList::iterator CustomShaderObjectPtrListContext::getCustomShaderObjListBegin(void)
	{
		return getCustomShaderObjList().begin();
	}

	CustomShaderObjectPtrList::const_iterator CustomShaderObjectPtrListContext::getCustomShaderObjListBegin(void) const
	{
		return getCustomShaderObjList().begin();
	}

	CustomShaderObjectPtrList::iterator CustomShaderObjectPtrListContext::getCustomShaderObjListEnd(void)
	{
		return getCustomShaderObjList().end();
	}

	CustomShaderObjectPtrList::const_iterator CustomShaderObjectPtrListContext::getCustomShaderObjListEnd(void) const
	{
		return getCustomShaderObjList().end();
	}

	void CustomShaderObjectPtrListContext::draw(t3d::RenderContext * rc)
	{
		CustomShaderObjectPtrList::const_iterator obj_iter = getCustomShaderObjListBegin();
		for(; obj_iter != getCustomShaderObjListEnd(); obj_iter++)
		{
			(*obj_iter)->draw(rc);
		}
	}

	//void ObjectList::drawWireZBufferRW(
	//	t3d::RenderContext * rc,
	//	const t3d::Vec4<real> & color)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawWireZBufferRW(rc, color);
	//	}
	//}

	//void ObjectList::drawWireZBufferRW(
	//	t3d::RenderContext * rc,
	//	const t3d::Vec4<real> & color,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawWireZBufferRW(rc, color, mmat);
	//	}
	//}

	//void ObjectList::drawWireZBufferRWWithoutThird(
	//	t3d::RenderContext * rc,
	//	const t3d::Vec4<real> & color)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawWireZBufferRWWithoutThird(rc, color);
	//	}
	//}

	//void ObjectList::drawWireZBufferRWWithoutThird(
	//	t3d::RenderContext * rc,
	//	const t3d::Vec4<real> & color,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawWireZBufferRWWithoutThird(rc, color, mmat);
	//	}
	//}

	//void ObjectList::drawWireZBufferRWWithBackface(
	//	t3d::RenderContext * rc,
	//	const t3d::Vec4<real> & color)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawWireZBufferRWWithBackface(rc, color);
	//	}
	//}

	//void ObjectList::drawWireZBufferRWWithBackface(
	//	t3d::RenderContext * rc,
	//	const t3d::Vec4<real> & color,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawWireZBufferRWWithBackface(rc, color, mmat);
	//	}
	//}

	//void ObjectList::drawWireZBufferRWWithBackfaceWithoutThird(
	//	t3d::RenderContext * rc,
	//	const t3d::Vec4<real> & color)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawWireZBufferRWWithBackfaceWithoutThird(rc, color);
	//	}
	//}

	//void ObjectList::drawWireZBufferRWWithBackfaceWithoutThird(
	//	t3d::RenderContext * rc,
	//	const t3d::Vec4<real> & color,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawWireZBufferRWWithBackfaceWithoutThird(rc, color, mmat);
	//	}
	//}

	//void ObjectList::drawGouraudZBufferRW(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawGouraudZBufferRW(rc);
	//	}
	//}

	//void ObjectList::drawGouraudZBufferRW(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat,
	//	const t3d::Mat4<real> & mrot)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawGouraudZBufferRW(rc, mmat, mrot);
	//	}
	//}

	//void ObjectList::drawGouraudZBufferRWWithBackface(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawGouraudZBufferRWWithBackface(rc);
	//	}
	//}

	//void ObjectList::drawGouraudZBufferRWWithBackface(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat,
	//	const t3d::Mat4<real> & mrot)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawGouraudZBufferRWWithBackface(rc, mmat, mrot);
	//	}
	//}

	//void ObjectList::drawTextureZBufferW(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTextureZBufferW(rc);
	//	}
	//}

	//void ObjectList::drawTextureZBufferW(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTextureZBufferW(rc, mmat);
	//	}
	//}

	//void ObjectList::drawTextureZBufferWWithBackface(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTextureZBufferWWithBackface(rc);
	//	}
	//}

	//void ObjectList::drawTextureZBufferWWithBackface(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTextureZBufferWWithBackface(rc, mmat);
	//	}
	//}

	//void ObjectList::drawTexturePerspectiveLPZBufferW(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTexturePerspectiveLPZBufferW(rc);
	//	}
	//}

	//void ObjectList::drawTexturePerspectiveLPZBufferW(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTexturePerspectiveLPZBufferW(rc, mmat);
	//	}
	//}

	//void ObjectList::drawTexturePerspectiveLPZBufferWWithBackface(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTexturePerspectiveLPZBufferWWithBackface(rc);
	//	}
	//}

	//void ObjectList::drawTexturePerspectiveLPZBufferWWithBackface(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTexturePerspectiveLPZBufferWWithBackface(rc, mmat);
	//	}
	//}

	//void ObjectList::drawTextureZBufferRW(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTextureZBufferRW(rc);
	//	}
	//}

	//void ObjectList::drawTextureZBufferRW(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTextureZBufferRW(rc, mmat);
	//	}
	//}

	//void ObjectList::drawTextureZBufferRWWithBackface(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTextureZBufferRWWithBackface(rc);
	//	}
	//}

	//void ObjectList::drawTextureZBufferRWWithBackface(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTextureZBufferRWWithBackface(rc, mmat);
	//	}
	//}

	//void ObjectList::drawTexturePerspectiveLPZBufferRW(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTexturePerspectiveLPZBufferRW(rc);
	//	}
	//}

	//void ObjectList::drawTexturePerspectiveLPZBufferRW(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTexturePerspectiveLPZBufferRW(rc, mmat);
	//	}
	//}

	//void ObjectList::drawTexturePerspectiveLPZBufferRWWithBackface(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTexturePerspectiveLPZBufferRWWithBackface(rc);
	//	}
	//}

	//void ObjectList::drawTexturePerspectiveLPZBufferRWWithBackface(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawTexturePerspectiveLPZBufferRWWithBackface(rc, mmat);
	//	}
	//}

	//void ObjectList::drawGouraudTextureZBufferRW(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawGouraudTextureZBufferRW(rc);
	//	}
	//}

	//void ObjectList::drawGouraudTextureZBufferRW(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat,
	//	const t3d::Mat4<real> & mrot)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawGouraudTextureZBufferRW(rc, mmat, mrot);
	//	}
	//}

	//void ObjectList::drawGouraudTextureZBufferRWWithBackface(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawGouraudTextureZBufferRWWithBackface(rc);
	//	}
	//}

	//void ObjectList::drawGouraudTextureZBufferRWWithBackface(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat,
	//	const t3d::Mat4<real> & mrot)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawGouraudTextureZBufferRWWithBackface(rc, mmat, mrot);
	//	}
	//}

	//void ObjectList::drawGouraudTexturePerspectiveLPZBufferRW(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawGouraudTexturePerspectiveLPZBufferRW(rc);
	//	}
	//}

	//void ObjectList::drawGouraudTexturePerspectiveLPZBufferRW(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat,
	//	const t3d::Mat4<real> & mrot)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawGouraudTexturePerspectiveLPZBufferRW(rc, mmat, mrot);
	//	}
	//}

	//void ObjectList::drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
	//	t3d::RenderContext * rc)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawGouraudTexturePerspectiveLPZBufferRWWithBackface(rc);
	//	}
	//}

	//void ObjectList::drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
	//	t3d::RenderContext * rc,
	//	const t3d::Mat4<real> & mmat,
	//	const t3d::Mat4<real> & mrot)
	//{
	//	ObjectBasePtrList::const_iterator obj_iter = getObjListBegin();
	//	for(; obj_iter != getObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->drawGouraudTexturePerspectiveLPZBufferRWWithBackface(rc, mmat, mrot);
	//	}
	//}

	//const ObjectBasePtrList & ObjectListContext::getObjList(void) const
	//{
	//	return m_objList;
	//}

	//ObjectBasePtrList & ObjectListContext::getObjList(void)
	//{
	//	return m_objList;
	//}

	//void ObjectListContext::pushObj(ObjectBasePtrList::const_reference obj)
	//{
	//	getObjList().push_back(obj);
	//}

	//void ObjectListContext::pushObjList(ObjectBasePtrList::const_iterator begin, ObjectBasePtrList::const_iterator end)
	//{
	//	getObjList().insert(getObjListBegin(), begin, end);
	//}

	//void ObjectListContext::clearObjList(void)
	//{
	//	getObjList().clear();
	//}

	//void ObjectListContext::resizeObjList(ObjectBasePtrList::size_type size)
	//{
	//	getObjList().resize(size);
	//}

	//ObjectBasePtrList::size_type ObjectListContext::getObjListSize(void) const
	//{
	//	return getObjList().size();
	//}

	//ObjectBasePtrList::reference ObjectListContext::objAt(ObjectBasePtrList::size_type i)
	//{
	//	assert(i < getObjListSize());

	//	return getObjList()[i];
	//}

	//ObjectBasePtrList::const_reference ObjectListContext::objAt(ObjectBasePtrList::size_type i) const
	//{
	//	assert(i < getObjListSize());

	//	return getObjList()[i];
	//}

	//ObjectBasePtrList::iterator ObjectListContext::getObjListBegin(void)
	//{
	//	return getObjList().begin();
	//}

	//ObjectBasePtrList::const_iterator ObjectListContext::getObjListBegin(void) const
	//{
	//	return getObjList().end();
	//}

	//ObjectBasePtrList::iterator ObjectListContext::getObjListEnd(void)
	//{
	//	return getObjList().end();
	//}

	//ObjectBasePtrList::const_iterator ObjectListContext::getObjListEnd(void) const
	//{
	//	return getObjList().end();
	//}

	size_t BSPNode::getTriangleCount(void) const
	{
		assert(false); return 0;
	}

	const t3d::Vec4<real> & BSPNode::getTriangleVertex0(size_t i) const
	{
		assert(false); return my::Vec4<real>::ZERO;
		UNREFERENCED_PARAMETER(i);
	}

	const t3d::Vec4<real> & BSPNode::getTriangleVertex1(size_t i) const
	{
		assert(false); return my::Vec4<real>::ZERO;
		UNREFERENCED_PARAMETER(i);
	}

	const t3d::Vec4<real> & BSPNode::getTriangleVertex2(size_t i) const
	{
		assert(false); return my::Vec4<real>::ZERO;
		UNREFERENCED_PARAMETER(i);
	}

	const t3d::Vec4<real> & BSPNode::getTriangleNormal0(size_t i) const
	{
		assert(false); return my::Vec4<real>::ZERO;
		UNREFERENCED_PARAMETER(i);
	}

	const t3d::Vec4<real> & BSPNode::getTriangleNormal1(size_t i) const
	{
		assert(false); return my::Vec4<real>::ZERO;
		UNREFERENCED_PARAMETER(i);
	}

	const t3d::Vec4<real> & BSPNode::getTriangleNormal2(size_t i) const
	{
		assert(false); return my::Vec4<real>::ZERO;
		UNREFERENCED_PARAMETER(i);
	}

	const t3d::Vec2<real> & BSPNode::getTriangleUV0(size_t i) const
	{
		assert(false); return my::Vec2<real>::ZERO;
		UNREFERENCED_PARAMETER(i);
	}

	const t3d::Vec2<real> & BSPNode::getTriangleUV1(size_t i) const
	{
		assert(false); return my::Vec2<real>::ZERO;
		UNREFERENCED_PARAMETER(i);
	}

	const t3d::Vec2<real> & BSPNode::getTriangleUV2(size_t i) const
	{
		assert(false); return my::Vec2<real>::ZERO;
		UNREFERENCED_PARAMETER(i);
	}

#define DISTANCE_ZERO_LIMIT REAL_ZERO_LIMIT

#pragma warning(disable: 4100)
	void BSPNode::drawWireZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color)
	{
		assert(false);
	}

	void BSPNode::drawWireZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat)
	{
		assert(false);
	}

	void BSPNode::drawWireZBufferRWWithoutThird(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color)
	{
		assert(false);
	}

	void BSPNode::drawWireZBufferRWWithoutThird(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat)
	{
		assert(false);
	}

	void BSPNode::drawWireZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color)
	{
		assert(false);
	}

	void BSPNode::drawWireZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat)
	{
		assert(false);
	}

	void BSPNode::drawWireZBufferRWWithBackfaceWithoutThird(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color)
	{
		assert(false);
	}

	void BSPNode::drawWireZBufferRWWithBackfaceWithoutThird(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat)
	{
		assert(false);
	}

	void BSPNode::drawGouraudZBufferRW(
		t3d::RenderContext * rc)
	{
		assert(false);
	}

	void BSPNode::drawGouraudZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot)
	{
		assert(false);
	}

	void BSPNode::drawGouraudZBufferRWWithBackface(
		t3d::RenderContext * rc)
	{
		assert(false);
	}

	void BSPNode::drawGouraudZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot)
	{
		assert(false);
	}

	void BSPNode::drawTextureZBufferW(
		t3d::RenderContext * rc)
	{
		if(!getVertexList().empty())
		{
			t3d::Vec4<real> cameraPos = rc->getCameraPosition();

			t3d::Vec4<real> cameraDir = t3d::CameraContext::calculateCameraDirection(rc->getCameraMatrix());

			real cameraHalfFov = t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection());

			real dis = calculatePointPlaneDistance(cameraPos, planePoint, planeNormal);

			real angle = acos(t3d::vec3CosTheta(cameraDir, planeNormal));

			if(dis > DISTANCE_ZERO_LIMIT)
			{
				if(angle + cameraHalfFov > DEG_TO_RAD(90))
				{
					if(NULL != back)
						back->drawTextureZBufferW(rc);

					Object::drawTextureZBufferWWithBackface(rc);
				}

				m_customShaderObjList.draw(rc);

				if(NULL != front)
					front->drawTextureZBufferW(rc);
			}
			else if(dis < -DISTANCE_ZERO_LIMIT)
			{
				if(angle - cameraHalfFov < DEG_TO_RAD(90))
				{
					if(NULL != front)
						front->drawTextureZBufferW(rc);

					//Object::drawTextureZBufferWWithBackface(rc);
				}

				m_customShaderObjList.draw(rc);

				if(NULL != back)
					back->drawTextureZBufferW(rc);
			}
			else
			{
				if(angle < DEG_TO_RAD(90))
				{
					if(angle + cameraHalfFov > DEG_TO_RAD(90))
					{
						if(NULL != back)
							back->drawTextureZBufferW(rc);
					}

					m_customShaderObjList.draw(rc);

					if(NULL != front)
						front->drawTextureZBufferW(rc);
				}
				else
				{
					if(angle - cameraHalfFov < DEG_TO_RAD(90))
					{
						if(NULL != front)
							front->drawTextureZBufferW(rc);
					}

					m_customShaderObjList.draw(rc);

					if(NULL != back)
						back->drawTextureZBufferW(rc);
				}
			}
		}
		else
		{
			m_customShaderObjList.draw(rc);
		}
	}

	void BSPNode::drawTextureZBufferW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat)
	{
		assert(false);
	}

	void BSPNode::drawTextureZBufferWWithBackface(
		t3d::RenderContext * rc)
	{
		assert(false);
	}

	void BSPNode::drawTextureZBufferWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat)
	{
		assert(false);
	}

	void BSPNode::drawTexturePerspectiveLPZBufferW(
		t3d::RenderContext * rc)
	{
		assert(false);
	}

	void BSPNode::drawTexturePerspectiveLPZBufferW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat)
	{
		assert(false);
	}

	void BSPNode::drawTexturePerspectiveLPZBufferWWithBackface(
		t3d::RenderContext * rc)
	{
		assert(false);
	}

	void BSPNode::drawTexturePerspectiveLPZBufferWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat)
	{
		assert(false);
	}

	void BSPNode::drawTextureZBufferRW(
		t3d::RenderContext * rc)
	{
		assert(false);
	}

	void BSPNode::drawTextureZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat)
	{
		assert(false);
	}

	void BSPNode::drawTextureZBufferRWWithBackface(
		t3d::RenderContext * rc)
	{
		assert(false);
	}

	void BSPNode::drawTextureZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat)
	{
		assert(false);
	}

	void BSPNode::drawTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc)
	{
		assert(false);
	}

	void BSPNode::drawTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat)
	{
		assert(false);
	}

	void BSPNode::drawTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc)
	{
		assert(false);
	}

	void BSPNode::drawTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat)
	{
		assert(false);
	}

	void BSPNode::drawGouraudTextureZBufferRW(
		t3d::RenderContext * rc)
	{
		assert(false);
	}

	void BSPNode::drawGouraudTextureZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot)
	{
		assert(false);
	}

	void BSPNode::drawGouraudTextureZBufferRWWithBackface(
		t3d::RenderContext * rc)
	{
		assert(false);
	}

	void BSPNode::drawGouraudTextureZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot)
	{
		assert(false);
	}

	void BSPNode::drawGouraudTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc)
	{
		if(!getVertexList().empty())
		{
			t3d::Vec4<real> cameraPos = rc->getCameraPosition();

			t3d::Vec4<real> cameraDir = t3d::CameraContext::calculateCameraDirection(rc->getCameraMatrix());

			real cameraHalfFov = t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection());

			real dis = calculatePointPlaneDistance(cameraPos, planePoint, planeNormal);

			real angle = acos(t3d::vec3CosTheta(cameraDir, planeNormal));

			if(dis > DISTANCE_ZERO_LIMIT)
			{
				if(NULL != front)
					front->drawGouraudTexturePerspectiveLPZBufferRW(rc);

				m_customShaderObjList.draw(rc);

				if(angle + cameraHalfFov > DEG_TO_RAD(90))
				{
					Object::drawGouraudTexturePerspectiveLPZBufferRWWithBackface(rc);

					if(NULL != back)
						back->drawGouraudTexturePerspectiveLPZBufferRW(rc);
				}
			}
			else if(dis < -DISTANCE_ZERO_LIMIT)
			{
				if(NULL != back)
					back->drawGouraudTexturePerspectiveLPZBufferRW(rc);

				m_customShaderObjList.draw(rc);

				if(angle - cameraHalfFov < DEG_TO_RAD(90))
				{
					//Object::drawGouraudTexturePerspectiveLPZBufferRWWithBackface(rc);

					if(NULL != front)
						front->drawGouraudTexturePerspectiveLPZBufferRW(rc);
				}
			}
			else
			{
				if(angle < DEG_TO_RAD(90))
				{
					if(NULL != front)
						front->drawGouraudTexturePerspectiveLPZBufferRW(rc);

					m_customShaderObjList.draw(rc);

					if(angle + cameraHalfFov > DEG_TO_RAD(90))
					{
						if(NULL != back)
							back->drawGouraudTexturePerspectiveLPZBufferRW(rc);
					}
				}
				else
				{
					if(NULL != back)
						back->drawGouraudTexturePerspectiveLPZBufferRW(rc);

					m_customShaderObjList.draw(rc);

					if(angle - cameraHalfFov < DEG_TO_RAD(90))
					{
						if(NULL != front)
							front->drawGouraudTexturePerspectiveLPZBufferRW(rc);
					}
				}
			}
		}
		else
		{
			m_customShaderObjList.draw(rc);
		}
	}

	void BSPNode::drawGouraudTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot)
	{
		assert(false);
	}
#pragma warning(default: 4100)

#define INSERT_VERTEX_NORMAL_UV_TO_LEFT(index0, index1, index2) \
	if(isValidTriangle(v##index0, v##index1, v##index2)) { \
		lVertexList.push_back(v##index0); \
		lVertexList.push_back(v##index1); \
		lVertexList.push_back(v##index2); \
		lNormalList.push_back(n##index0); \
		lNormalList.push_back(n##index1); \
		lNormalList.push_back(n##index2); \
		lUVList.push_back(t##index0); \
		lUVList.push_back(t##index1); \
		lUVList.push_back(t##index2); \
	}

#define INSERT_VERTEX_NORMAL_UV_TO_RIGHT(index0, index1, index2) \
	if(isValidTriangle(v##index0, v##index1, v##index2)) { \
		rVertexList.push_back(v##index0); \
		rVertexList.push_back(v##index1); \
		rVertexList.push_back(v##index2); \
		rNormalList.push_back(n##index0); \
		rNormalList.push_back(n##index1); \
		rNormalList.push_back(n##index2); \
		rUVList.push_back(t##index0); \
		rUVList.push_back(t##index1); \
		rUVList.push_back(t##index2); \
	}

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
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v1, v0);
		t3d::Vec4<real> dir2 = t3d::vec3Sub(v2, v0);

		real intersection1 = calculateLinePlaneIntersection(v0, dir1, planePoint, planeNormal);
		real intersection2 = calculateLinePlaneIntersection(v0, dir2, planePoint, planeNormal);

		assert(intersection1 > 0 && intersection1 < 1);
		assert(intersection2 > 0 && intersection2 < 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v0, t3d::vec3Mul(dir1, intersection1));
		t3d::Vec4<real> v4 = t3d::vec3Add(v0, t3d::vec3Mul(dir2, intersection2));

		t3d::Vec4<real> n3 = t3d::vec3Add(n0, t3d::vec3Mul(t3d::vec3Sub(n1, n0), intersection1));
		t3d::Vec4<real> n4 = t3d::vec3Add(n0, t3d::vec3Mul(t3d::vec3Sub(n2, n0), intersection2));

		t3d::Vec2<real> t3 = t0 + (t1 - t0) * intersection1;
		t3d::Vec2<real> t4 = t0 + (t2 - t0) * intersection2;

		INSERT_VERTEX_NORMAL_UV_TO_LEFT(0, 3, 4);

		INSERT_VERTEX_NORMAL_UV_TO_RIGHT(3, 1, 2);

		INSERT_VERTEX_NORMAL_UV_TO_RIGHT(3, 2, 4);
	}

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
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v1, v0);
		t3d::Vec4<real> dir2 = t3d::vec3Sub(v2, v0);

		real intersection1 = calculateLinePlaneIntersection(v0, dir1, planePoint, planeNormal);
		real intersection2 = calculateLinePlaneIntersection(v0, dir2, planePoint, planeNormal);

		assert(intersection1 > 0 && intersection1 < 1);
		assert(intersection2 > 0 && intersection2 < 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v0, t3d::vec3Mul(dir1, intersection1));
		t3d::Vec4<real> v4 = t3d::vec3Add(v0, t3d::vec3Mul(dir2, intersection2));

		t3d::Vec4<real> n3 = t3d::vec3Add(n0, t3d::vec3Mul(t3d::vec3Sub(n1, n0), intersection1));
		t3d::Vec4<real> n4 = t3d::vec3Add(n0, t3d::vec3Mul(t3d::vec3Sub(n2, n0), intersection2));

		t3d::Vec2<real> t3 = t0 + (t1 - t0) * intersection1;
		t3d::Vec2<real> t4 = t0 + (t2 - t0) * intersection2;

		INSERT_VERTEX_NORMAL_UV_TO_LEFT(1, 2, 3);

		INSERT_VERTEX_NORMAL_UV_TO_LEFT(2, 4, 3);

		INSERT_VERTEX_NORMAL_UV_TO_RIGHT(3, 4, 0);
	}

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
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v2, v1);

		real intersection1 = calculateLinePlaneIntersection(v1, dir1, planePoint, planeNormal);

		assert(intersection1 > 0 && intersection1 < 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v1, t3d::vec3Mul(dir1, intersection1));

		t3d::Vec4<real> n3 = t3d::vec3Add(n1, t3d::vec3Mul(t3d::vec3Sub(n2, n1), intersection1));

		t3d::Vec2<real> t3 = t1 + (t2 - t1) * intersection1;

		INSERT_VERTEX_NORMAL_UV_TO_LEFT(1, 3, 0);

		INSERT_VERTEX_NORMAL_UV_TO_RIGHT(0, 3, 2);
	}

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
		const t3d::Vec4<real> & planeNormal)
	{
		t3d::Vec4<real> dir1 = t3d::vec3Sub(v2, v1);

		real intersection1 = calculateLinePlaneIntersection(v1, dir1, planePoint, planeNormal);

		assert(intersection1 > 0 && intersection1 < 1);

		t3d::Vec4<real> v3 = t3d::vec3Add(v1, t3d::vec3Mul(dir1, intersection1));

		t3d::Vec4<real> n3 = t3d::vec3Add(n1, t3d::vec3Mul(t3d::vec3Sub(n2, n1), intersection1));

		t3d::Vec2<real> t3 = t1 + (t2 - t1) * intersection1;

		INSERT_VERTEX_NORMAL_UV_TO_LEFT(2, 0, 3);

		INSERT_VERTEX_NORMAL_UV_TO_RIGHT(3, 0, 1);
	}

#define INSERT_TRIANGLE_VERTEX_NORMAL_UV_UP(index0, index1, index2) \
	splitTriangleVertexNormalUVUp( \
		lVertexList, lNormalList, lUVList, rVertexList, rNormalList, rUVList, \
		v##index0, \
		v##index1, \
		v##index2, \
		n##index0, \
		n##index1, \
		n##index2, \
		t##index0, \
		t##index1, \
		t##index2, \
		planePoint, planeNormal);

#define INSERT_TRIANGLE_VERTEX_NORMAL_UV_DOWN(index0, index1, index2) \
	splitTriangleVertexNormalUVDown( \
		lVertexList, lNormalList, lUVList, rVertexList, rNormalList, rUVList, \
		v##index0, \
		v##index1, \
		v##index2, \
		n##index0, \
		n##index1, \
		n##index2, \
		t##index0, \
		t##index1, \
		t##index2, \
		planePoint, planeNormal);

#define INSERT_TRIANGLE_VERTEX_NORMAL_UV_LEFT(index0, index1, index2) \
	splitTriangleVertexNormalUVLeft( \
		lVertexList, lNormalList, lUVList, rVertexList, rNormalList, rUVList, \
		v##index0, \
		v##index1, \
		v##index2, \
		n##index0, \
		n##index1, \
		n##index2, \
		t##index0, \
		t##index1, \
		t##index2, \
		planePoint, planeNormal);

#define INSERT_TRIANGLE_VERTEX_NORMAL_UV_RIGHT(index0, index1, index2) \
	splitTriangleVertexNormalUVRight( \
		lVertexList, lNormalList, lUVList, rVertexList, rNormalList, rUVList, \
		v##index0, \
		v##index1, \
		v##index2, \
		n##index0, \
		n##index1, \
		n##index2, \
		t##index0, \
		t##index1, \
		t##index2, \
		planePoint, planeNormal);

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
		const t3d::Vec4<real> & planeNormal)
	{
		real d0 = calculatePointPlaneDistance(v0, planePoint, planeNormal);
		real d1 = calculatePointPlaneDistance(v1, planePoint, planeNormal);
		real d2 = calculatePointPlaneDistance(v2, planePoint, planeNormal);

		if(d0 > DISTANCE_ZERO_LIMIT)
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_LEFT(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_DOWN(2, 0, 1);
				}
				else
				{
					INSERT_VERTEX_NORMAL_UV_TO_LEFT(0, 1, 2);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_DOWN(1, 2, 0);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_UP(0, 1, 2);
				}
				else
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_LEFT(2, 0, 1);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_LEFT(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_LEFT(1, 2, 0);
				}
				else
				{
					INSERT_VERTEX_NORMAL_UV_TO_LEFT(0, 1, 2);
				}
			}
		}
		else if(d0 < -DISTANCE_ZERO_LIMIT)
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_DOWN(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_UP(1, 2, 0);
				}
				else
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_RIGHT(2, 0, 1);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_UP(2, 0, 1);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_RIGHT(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_NORMAL_UV_TO_RIGHT(0, 1, 2);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_LEFT(1, 2, 0);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_RIGHT(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_NORMAL_UV_TO_RIGHT(0, 1, 2);
				}
			}
		}
		else
		{
			if(d1 > DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_LEFT(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_LEFT(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_NORMAL_UV_TO_LEFT(0, 1, 2);
				}
			}
			else if(d1 < -DISTANCE_ZERO_LIMIT)
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_TRIANGLE_VERTEX_NORMAL_UV_RIGHT(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_RIGHT(0, 1, 2);
				}
				else
				{
					INSERT_VERTEX_NORMAL_UV_TO_RIGHT(0, 1, 2);
				}
			}
			else
			{
				if(d2 > DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_LEFT(0, 1, 2);
				}
				else if(d2 < -DISTANCE_ZERO_LIMIT)
				{
					INSERT_VERTEX_NORMAL_UV_TO_RIGHT(0, 1, 2);
				}
				else
				{
					return false;
				}
			}
		}

		return true;
	}

	BSPNodePtr buildBSPScene(
		const t3d::VertexList & vertexList,
		const t3d::NormalList & normalList,
		const t3d::UVList & uvList)
	{
		if(vertexList.empty())
			return BSPNodePtr();

		BSPNodePtr node = BSPNodePtr(new BSPNode());

		assert(vertexList.size() == normalList.size());
		assert(vertexList.size() == uvList.size());
		assert(0 == vertexList.size() % 3);

		t3d::VertexList lVertexList;
		t3d::NormalList lNormalList;
		t3d::UVList lUVList;

		t3d::VertexList rVertexList;
		t3d::NormalList rNormalList;
		t3d::UVList rUVList;

		node->planePoint = vertexList[0];

		node->planeNormal = calculateTriangleNormal(vertexList[0], vertexList[1], vertexList[2]);

		for(size_t i = 0; i < vertexList.size(); i += 3)
		{
			if(!splitTriangleVertexNormalUV(
				lVertexList,
				lNormalList,
				lUVList,
				rVertexList,
				rNormalList,
				rUVList,
				vertexList[i + 0],
				vertexList[i + 1],
				vertexList[i + 2],
				normalList[i + 0],
				normalList[i + 1],
				normalList[i + 2],
				uvList[i + 0],
				uvList[i + 1],
				uvList[i + 2],
				node->planePoint,
				node->planeNormal))
			{
				node->pushVertex(vertexList[i + 0]);
				node->pushVertex(vertexList[i + 1]);
				node->pushVertex(vertexList[i + 2]);

				node->pushNormal(normalList[i + 0]);
				node->pushNormal(normalList[i + 1]);
				node->pushNormal(normalList[i + 2]);

				node->pushUV(uvList[i + 0]);
				node->pushUV(uvList[i + 1]);
				node->pushUV(uvList[i + 2]);
			}
		}

		assert(!node->getVertexList().empty());

		node->front = buildBSPScene(lVertexList, lNormalList, lUVList);

		node->back = buildBSPScene(rVertexList, rNormalList, rUVList);

		return node;
	}

	void insertObjectToBSPScene(
		BSPNodePtr node,
		const CustomShaderObjectPtr & customShaderObj,
		const t3d::VertexList & objVertexList)
	{
		if(node->getVertexList().empty())
		{
			assert(NULL == node->front);
			assert(NULL == node->back);

			node->m_customShaderObjList.pushCustomShaderObj(customShaderObj);
		}
		else
		{
			assert(!node->getVertexList().empty());

			bool haveFrontVertex = false;
			bool haveBackVertex = false;

			t3d::VertexList::const_iterator vert_iter = objVertexList.begin();
			for(; vert_iter != objVertexList.end(); vert_iter++)
			{
				real distance = calculatePointPlaneDistance(*vert_iter, node->planePoint, node->planeNormal);

				if(distance > DISTANCE_ZERO_LIMIT)
				{
					haveFrontVertex = true;
				}
				else if(distance < -DISTANCE_ZERO_LIMIT)
				{
					haveBackVertex = true;
				}
			}

			if(haveFrontVertex)
			{
				if(haveBackVertex)
				{
					node->m_customShaderObjList.pushCustomShaderObj(customShaderObj);
				}
				else
				{
					if(NULL == node->front)
						node->front = BSPNodePtr(new BSPNode());
						
					insertObjectToBSPScene(node->front, customShaderObj, objVertexList);
				}
			}
			else
			{
				if(haveBackVertex)
				{
					if(NULL == node->back)
						node->back = BSPNodePtr(new BSPNode());
						
					insertObjectToBSPScene(node->back, customShaderObj, objVertexList);
				}
				else
				{
					node->m_customShaderObjList.pushCustomShaderObj(customShaderObj);
				}
			}
		}
	}

	//void insertObjectToBSPScene(
	//	BSPNodePtr node,
	//	CustomShaderObjectPtrList::const_iterator begin, CustomShaderObjectPtrList::const_iterator end)
	//{
	//	CustomShaderObjectPtrList::const_iterator obj_iter = begin;
	//	for(; obj_iter != end; obj_iter++)
	//	{
	//		insertObjectToBSPScene(node, *obj_iter);
	//	}
	//}

	//void insertObjectToBSPScene(
	//	BSPNodePtr node,
	//	const CustomShaderObjectPtrList & customShaderObjPtrList)
	//{
	//	insertObjectToBSPScene(node, customShaderObjPtrList.begin(), customShaderObjPtrList.end());
	//}

	//#define DEFINE_XML_ELEMENT(elem_v, elem_p, elem_s)	\
	//	TiXmlElement * elem_v = elem_p->FirstChildElement(#elem_s); \
	//	if(NULL == elem_v) \
	//		T3D_CUSEXCEPT(_T("cannot find ") _T(#elem_s));

	//#define DEFINE_XML_ELEMENT_SIMPLE(elem_v, elem_p) \
	//	DEFINE_XML_ELEMENT(elem_v, elem_p, elem_v)

	//#define DEFINE_XML_ATTRIBUTE_CHAR(attr_v, elem_p, attr_s) \
	//	const char * attr_v; \
	//	if(NULL == (attr_v = elem_p->Attribute(#attr_s))) \
	//		T3D_CUSEXCEPT(_T("cannot read ") _T(#elem_p) _T(".") _T(#attr_s));

	//#define DEFINE_XML_ATTRIBUTE_CHAR_SIMPLE(attr_v, elem_p) \
	//	DEFINE_XML_ATTRIBUTE_CHAR(attr_v, elem_p, attr_v)

	//#define DEFINE_XML_ATTRIBUTE_INT(attr_v, elem_p, attr_s) \
	//	int attr_v; \
	//	if(NULL == (elem_p->Attribute(#attr_s, &attr_v))) \
	//		T3D_CUSEXCEPT(_T("cannot read ") _T(#elem_p) _T(".") _T(#attr_s));

	//#define DEFINE_XML_ATTRIBUTE_INT_SIMPLE(attr_v, elem_p) \
	//	DEFINE_XML_ATTRIBUTE_INT(attr_v, elem_p, attr_v)

	//#define DEFINE_XML_ATTRIBUTE_DOUBLE(attr_v, elem_p, attr_s) \
	//	double attr_v; \
	//	if(NULL == (elem_p->Attribute(#attr_s, &attr_v))) \
	//		T3D_CUSEXCEPT(_T("cannot read ") _T(#elem_p) _T(".") _T(#attr_s));

	//#define DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(attr_v, elem_p) \
	//	DEFINE_XML_ATTRIBUTE_DOUBLE(attr_v, elem_p, attr_v)

	//#define DEFINE_XML_ATTRIBUTE_BOOL(attr_v, elem_p, attr_s) \
	//	bool attr_v; \
	//	{ DEFINE_XML_ATTRIBUTE_CHAR(__tmp, elem_p, attr_s); \
	//		attr_v = (0 == strcmp(__tmp, "true")); }

	//#define DEFINE_XML_ATTRIBUTE_BOOL_SIMPLE(attr_v, elem_p) \
	//	DEFINE_XML_ATTRIBUTE_BOOL(attr_v, elem_p, attr_v)

	//ObjectBasePtrList buildBoneAssignmentIndexObjectPtrListFromOgreMesh(
	//	IOStream * meshStream)
	//{
	//	TiXmlDocument doc;
	//	doc.LoadFile(static_cast<FILE *>(meshStream->getHandle()), TIXML_DEFAULT_ENCODING);

	//	DEFINE_XML_ELEMENT_SIMPLE(mesh, (&doc));

	//	DEFINE_XML_ELEMENT_SIMPLE(sharedgeometry, mesh);

	//	DEFINE_XML_ATTRIBUTE_INT_SIMPLE(vertexcount, sharedgeometry);

	//	if(vertexcount < 0)
	//		T3D_CUSEXCEPT(_T("invalid sharedgeometry.vertexcount"));

	//	DEFINE_XML_ELEMENT_SIMPLE(vertexbuffer, sharedgeometry);

	//	DEFINE_XML_ATTRIBUTE_BOOL_SIMPLE(positions, vertexbuffer);

	//	DEFINE_XML_ATTRIBUTE_BOOL_SIMPLE(normals, vertexbuffer);

	//	DEFINE_XML_ATTRIBUTE_INT_SIMPLE(texture_coords, vertexbuffer);

	//	BoneAssignmentIndexObject tmpObj;

	//	if(positions)
	//	{
	//		TiXmlElement * vertex = vertexbuffer->FirstChildElement("vertex");
	//		for(; vertex != NULL; vertex = vertex->NextSiblingElement("vertex"))
	//		{
	//			DEFINE_XML_ELEMENT_SIMPLE(position, vertex);

	//			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(x, position);

	//			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(y, position);

	//			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(z, position);

	//			tmpObj.pushOriginalVertex((real)x, (real)y, (real)-z); // ***
	//		}

	//		if((int)tmpObj.getOriginalVertexList().size() != vertexcount)
	//			T3D_CUSEXCEPT(_T("cannot match vertex count"));
	//	}

	//	if(normals)
	//	{
	//		TiXmlElement * vertex = vertexbuffer->FirstChildElement("vertex");
	//		for(; vertex != NULL; vertex = vertex->NextSiblingElement("vertex"))
	//		{
	//			DEFINE_XML_ELEMENT_SIMPLE(normal, vertex);

	//			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(x, normal);

	//			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(y, normal);

	//			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(z, normal);

	//			tmpObj.pushOriginalNormal((real)x, (real)y, (real)-z); // ***
	//		}

	//		if((int)tmpObj.getOriginalNormalList().size() != vertexcount)
	//			T3D_CUSEXCEPT(_T("cannot match normal count"));
	//	}

	//	if(texture_coords > 0)
	//	{
	//		TiXmlElement * vertex = vertexbuffer->FirstChildElement("vertex");
	//		for(; vertex != NULL; vertex = vertex->NextSiblingElement("vertex"))
	//		{
	//			DEFINE_XML_ELEMENT_SIMPLE(texcoord, vertex);

	//			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(u, texcoord);

	//			if(u < 0)
	//			{
	//				if(u > -EPSILON_E6)
	//					u = 0;
	//				else
	//					T3D_CUSEXCEPT(_T("invalid texcoord.u"));
	//			}
	//			else if(u > 1)
	//			{
	//				if(u < 1 + EPSILON_E6)
	//					u = 1;
	//				else
	//					T3D_CUSEXCEPT(_T("invalid texcoord.u"));
	//			}

	//			DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(v, texcoord);

	//			if(v < 0)
	//			{
	//				if(v > -EPSILON_E6)
	//					v = 0;
	//				else
	//					T3D_CUSEXCEPT(_T("invalid texcoord.u"));
	//			}
	//			else if(v > 1)
	//			{
	//				if(v < 1 + EPSILON_E6)
	//					v = 1;
	//				else
	//					T3D_CUSEXCEPT(_T("invalid texcoord.u"));
	//			}

	//			tmpObj.pushUV((real)u, (real)(1 - v)); // ***
	//		}

	//		if((int)tmpObj.getUVListSize() != vertexcount)
	//			T3D_CUSEXCEPT(_T("cannot match uv count"));
	//	}

	//	DEFINE_XML_ELEMENT_SIMPLE(boneassignments, mesh);

	//	TiXmlElement * vertexboneassignment = boneassignments->FirstChildElement("vertexboneassignment");
	//	for(; vertexboneassignment != NULL; vertexboneassignment = vertexboneassignment->NextSiblingElement("vertexboneassignment"))
	//	{
	//		DEFINE_XML_ATTRIBUTE_INT_SIMPLE(vertexindex, vertexboneassignment);

	//		DEFINE_XML_ATTRIBUTE_INT_SIMPLE(boneindex, vertexboneassignment);

	//		DEFINE_XML_ATTRIBUTE_DOUBLE_SIMPLE(weight, vertexboneassignment);

	//		tmpObj.pushBoneAssignment(vertexindex, boneindex, (real)weight);
	//	}

	//	DEFINE_XML_ELEMENT_SIMPLE(submeshes, mesh);

	//	ObjectBasePtrList objPtrList;

	//	TiXmlElement * submesh = submeshes->FirstChildElement("submesh");
	//	for(; submesh != NULL; submesh = submesh->NextSiblingElement("submesh"))
	//	{
	//		DEFINE_XML_ELEMENT_SIMPLE(faces, submesh);

	//		DEFINE_XML_ATTRIBUTE_INT(face_count, faces, count);

	//		BoneAssignmentIndexObjectPtr objPtr(new BoneAssignmentIndexObject());

	//		if(face_count > 0)
	//		{
	//			size_t prevVertexIndexSize = objPtr->getVertexIndexList().size();

	//			TiXmlElement * face = faces->FirstChildElement("face");
	//			for(; face != NULL; face = face->NextSiblingElement("face"))
	//			{
	//				int v[3];
	//				if(NULL == (face->Attribute("v1", &v[0])))
	//					T3D_CUSEXCEPT(_T("cannot read face.v1"));

	//				if(v[0] < 0 || v[0] >= vertexcount)
	//					T3D_CUSEXCEPT(_T("invalid face.v1"));

	//				if(NULL == (face->Attribute("v2", &v[1])))
	//					T3D_CUSEXCEPT(_T("cannot read face.v2"));

	//				if(v[1] < 0 || v[1] >= vertexcount)
	//					T3D_CUSEXCEPT(_T("invalid face.v2"));

	//				if(NULL == (face->Attribute("v3", &v[2])))
	//					T3D_CUSEXCEPT(_T("cannot read face.v3"));

	//				if(v[2] < 0 || v[2] >= vertexcount)
	//					T3D_CUSEXCEPT(_T("invalid face.v3"));

	//				std::swap(v[1], v[2]); // ***

	//				size_t i = 0;
	//				for(; i < 3; i++)
	//				{
	//					int tmpVertexIndex = v[i];
	//					t3d::VertexList::reference tmpVertex = tmpObj.getOriginalVertexList()[tmpVertexIndex];
	//					t3d::NormalList::reference tmpNormal = tmpObj.getOriginalNormalList()[tmpVertexIndex];
	//					t3d::UVList::reference tmpUV = tmpObj.uvAt(tmpVertexIndex);

	//					size_t newIndex;
	//					size_t j = 0;
	//					for(; j < objPtr->getOriginalVertexList().size(); j++)
	//					{
	//						if(t3d::vec3IsEqual(tmpVertex, objPtr->getOriginalVertexList()[j])
	//							&& t3d::vec3IsEqual(tmpNormal, objPtr->getOriginalNormalList()[j])
	//							&& tmpUV == objPtr->uvAt(j))
	//						{
	//							newIndex = j;
	//							break;
	//						}
	//					}

	//					if(j < objPtr->getOriginalVertexList().size())
	//					{
	//						objPtr->pushVertexIndex(newIndex);
	//					}
	//					else
	//					{
	//						objPtr->pushOriginalVertex(tmpVertex);
	//						objPtr->pushOriginalNormal(tmpNormal);
	//						objPtr->pushUV(tmpUV);

	//						assert(objPtr->getOriginalVertexList().size() == objPtr->getOriginalNormalList().size());
	//						assert(objPtr->getOriginalVertexList().size() == objPtr->getUVListSize());

	//						newIndex = objPtr->getOriginalVertexList().size() - 1;

	//						t3d::BoneAssignmentList::const_iterator bone_assign_iter = tmpObj.getBoneAssignmentListBegin();
	//						for(; bone_assign_iter != tmpObj.getBoneAssignmentListEnd(); bone_assign_iter++)
	//						{
	//							if(tmpVertexIndex == (int)bone_assign_iter->vertex_i)
	//							{
	//								objPtr->pushBoneAssignment(newIndex, bone_assign_iter->bone_i, bone_assign_iter->weight);
	//							}
	//						}

	//						objPtr->pushVertexIndex(newIndex);
	//					}
	//				}
	//			}

	//			if((int)(objPtr->getVertexIndexList().size() - prevVertexIndexSize) != face_count * 3)
	//				T3D_CUSEXCEPT(_T("cannot match face count"));

	//			objPtr->getVertexList() = objPtr->getOriginalVertexList();

	//			objPtr->getNormalList() = objPtr->getOriginalNormalList();

	//			objPtrList.push_back(objPtr);
	//		}
	//	}

	//	return objPtrList;
	//}

	//void pushVertexByDirectionProject(
	//	t3d::RenderContext * rc,
	//	const t3d::Vec4<real> & dir,
	//	const t3d::Vec4<real> & planePoint,
	//	const t3d::Vec4<real> & planeNormal,
	//	t3d::VertexList::const_iterator begin,
	//	t3d::VertexList::const_iterator end,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	t3d::VertexList::const_iterator vert_iter = begin;
	//	for(; vert_iter != end; vert_iter++)
	//	{
	//		rc->pushVertex(calculateLinePlaneIntersectionPoint(
	//			*vert_iter * mmat,
	//			dir,
	//			planePoint,
	//			planeNormal));
	//	}
	//}

	//void pushVertexByPointProject(
	//	t3d::RenderContext * rc,
	//	const t3d::Vec4<real> & point,
	//	const t3d::Vec4<real> & planePoint,
	//	const t3d::Vec4<real> & planeNormal,
	//	t3d::VertexList::const_iterator begin,
	//	t3d::VertexList::const_iterator end,
	//	const t3d::Mat4<real> & mmat)
	//{
	//	t3d::VertexList::const_iterator vert_iter = begin;
	//	for(; vert_iter != end; vert_iter++)
	//	{
	//		t3d::Vec4<real> tmpVert = *vert_iter * mmat;
	//		rc->pushVertex(calculateLinePlaneIntersectionPoint(
	//			tmpVert,
	//			t3d::vec3Sub(tmpVert, point),
	//			planePoint,
	//			planeNormal));
	//	}
	//}
}
