
#include "stdafx.h"
#include "myScene.h"
//#include <tinyxml.h>

namespace my
{
	//CustomShaderObject::~CustomShaderObject(void)
	//{
	//}

	//const CustomShaderObjectPtrList & CustomShaderObjectPtrListContext::getCustomShaderObjList(void) const
	//{
	//	return m_customShaderObjList;
	//}

	//CustomShaderObjectPtrList & CustomShaderObjectPtrListContext::getCustomShaderObjList(void)
	//{
	//	return m_customShaderObjList;
	//}

	//void CustomShaderObjectPtrListContext::pushCustomShaderObj(CustomShaderObjectPtrList::const_reference obj)
	//{
	//	m_customShaderObjList.push_back(obj);
	//}

	//void CustomShaderObjectPtrListContext::pushCustomShaderObjList(CustomShaderObjectPtrList::const_iterator begin, CustomShaderObjectPtrList::const_iterator end)
	//{
	//	m_customShaderObjList.insert(getCustomShaderObjListBegin(), begin, end);
	//}

	//void CustomShaderObjectPtrListContext::clearCustomShaderObjList(void)
	//{
	//	m_customShaderObjList.clear();
	//}

	//void CustomShaderObjectPtrListContext::resizeCustomShaderObjList(CustomShaderObjectPtrList::size_type size)
	//{
	//	m_customShaderObjList.resize(size);
	//}

	//CustomShaderObjectPtrList::size_type CustomShaderObjectPtrListContext::getCustomShaderObjListSize(void) const
	//{
	//	return m_customShaderObjList.size();
	//}

	//CustomShaderObjectPtrList::reference CustomShaderObjectPtrListContext::customShaderObjAt(CustomShaderObjectPtrList::size_type i)
	//{
	//	_ASSERT(i < getCustomShaderObjListSize());

	//	return m_customShaderObjList[i];
	//}

	//CustomShaderObjectPtrList::const_reference CustomShaderObjectPtrListContext::customShaderObjAt(CustomShaderObjectPtrList::size_type i) const
	//{
	//	_ASSERT(i < getCustomShaderObjListSize());

	//	return m_customShaderObjList[i];
	//}

	//CustomShaderObjectPtrList::iterator CustomShaderObjectPtrListContext::getCustomShaderObjListBegin(void)
	//{
	//	return m_customShaderObjList.begin();
	//}

	//CustomShaderObjectPtrList::const_iterator CustomShaderObjectPtrListContext::getCustomShaderObjListBegin(void) const
	//{
	//	return m_customShaderObjList.begin();
	//}

	//CustomShaderObjectPtrList::iterator CustomShaderObjectPtrListContext::getCustomShaderObjListEnd(void)
	//{
	//	return m_customShaderObjList.end();
	//}

	//CustomShaderObjectPtrList::const_iterator CustomShaderObjectPtrListContext::getCustomShaderObjListEnd(void) const
	//{
	//	return m_customShaderObjList.end();
	//}

	//void CustomShaderObjectPtrListContext::draw(t3d::RenderContext * rc) const
	//{
	//	CustomShaderObjectPtrList::const_iterator obj_iter = getCustomShaderObjListBegin();
	//	for(; obj_iter != getCustomShaderObjListEnd(); obj_iter++)
	//	{
	//		(*obj_iter)->draw(rc);
	//	}
	//}

	//size_t BSPNode::getTriangleCount(void) const
	//{
	//	_ASSERT(false); return 0;
	//}

	//const t3d::Vec4<real> & BSPNode::getTriangleVertex0(size_t i) const
	//{
	//	_ASSERT(false); return my::Vec4<real>::ZERO;
	//	UNREFERENCED_PARAMETER(i);
	//}

	//const t3d::Vec4<real> & BSPNode::getTriangleVertex1(size_t i) const
	//{
	//	_ASSERT(false); return my::Vec4<real>::ZERO;
	//	UNREFERENCED_PARAMETER(i);
	//}

	//const t3d::Vec4<real> & BSPNode::getTriangleVertex2(size_t i) const
	//{
	//	_ASSERT(false); return my::Vec4<real>::ZERO;
	//	UNREFERENCED_PARAMETER(i);
	//}

	//const t3d::Vec4<real> & BSPNode::getTriangleNormal0(size_t i) const
	//{
	//	_ASSERT(false); return my::Vec4<real>::ZERO;
	//	UNREFERENCED_PARAMETER(i);
	//}

	//const t3d::Vec4<real> & BSPNode::getTriangleNormal1(size_t i) const
	//{
	//	_ASSERT(false); return my::Vec4<real>::ZERO;
	//	UNREFERENCED_PARAMETER(i);
	//}

	//const t3d::Vec4<real> & BSPNode::getTriangleNormal2(size_t i) const
	//{
	//	_ASSERT(false); return my::Vec4<real>::ZERO;
	//	UNREFERENCED_PARAMETER(i);
	//}

	//const t3d::Vec2<real> & BSPNode::getTriangleUV0(size_t i) const
	//{
	//	_ASSERT(false); return my::Vec2<real>::ZERO;
	//	UNREFERENCED_PARAMETER(i);
	//}

	//const t3d::Vec2<real> & BSPNode::getTriangleUV1(size_t i) const
	//{
	//	_ASSERT(false); return my::Vec2<real>::ZERO;
	//	UNREFERENCED_PARAMETER(i);
	//}

	//const t3d::Vec2<real> & BSPNode::getTriangleUV2(size_t i) const
	//{
	//	_ASSERT(false); return my::Vec2<real>::ZERO;
	//	UNREFERENCED_PARAMETER(i);
	//}

	typedef void (ObjectBase::*ObjectDrawFunc)(t3d::RenderContext * rc) const;

	template <ObjectDrawFunc pFunc>
	class CustomShaderObjectDrawer
	{
	public:
		CustomShaderObjectDrawer(void)
		{
		}

	public:
		void draw(t3d::RenderContext * rc, const ObjectBase * obj) const
		{
			(obj->*pFunc)(rc);
		}
	};

	typedef void (ObjectBase::*ObjectDrawFuncRC)(t3d::RenderContext * rc, const t3d::Vec4<real> & color) const;

	template <ObjectDrawFuncRC pFunc>
	class CustomShaderObjectDrawerRC
	{
	public:
		CustomShaderObjectDrawerRC(const t3d::Vec4<real> & color)
			: m_color(color)
		{
		}

	public:
		void draw(t3d::RenderContext * rc, const ObjectBase * obj) const
		{
			(obj->*pFunc)(rc, m_color);
		}

	protected:
		const t3d::Vec4<real> & m_color;
	};

	typedef void (ObjectBase::*ObjectDrawFuncRCM)(t3d::RenderContext * rc, const t3d::Vec4<real> & color, const t3d::Mat4<real> & mmat) const;

	template <ObjectDrawFuncRCM pFunc>
	class CustomShaderObjectDrawerRCM
	{
	public:
		CustomShaderObjectDrawerRCM(const t3d::Vec4<real> & color, const t3d::Mat4<real> & mmat)
			: m_color(color)
			, m_mmat(mmat)
		{
		}

	public:
		void draw(t3d::RenderContext * rc, const ObjectBase * obj) const
		{
			(obj->*pFunc)(rc, m_color, m_mmat);
		}

	protected:
		const t3d::Vec4<real> & m_color;

		const t3d::Mat4<real> & m_mmat;
	};

	typedef void (ObjectBase::*ObjectDrawFuncRM)(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat) const;

	template <ObjectDrawFuncRM pFunc>
	class CustomShaderObjectDrawerRM
	{
	public:
		CustomShaderObjectDrawerRM(const t3d::Mat4<real> & mmat)
			: m_mmat(mmat)
		{
		}

	public:
		void draw(t3d::RenderContext * rc, const ObjectBase * obj) const
		{
			(obj->*pFunc)(rc, m_mmat);
		}

	protected:
		const t3d::Mat4<real> & m_mmat;
	};

	typedef void (ObjectBase::*ObjectDrawFuncRMM)(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const;

	template <ObjectDrawFuncRMM pFunc>
	class CustomShaderObjectDrawerRMM
	{
	public:
		CustomShaderObjectDrawerRMM(const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot)
			: m_mmat(mmat)
			, m_mrot(mrot)
		{
		}

	public:
		void draw(t3d::RenderContext * rc, const ObjectBase * obj) const
		{
			(obj->*pFunc)(rc, m_mmat, m_mrot);
		}

	protected:
		const t3d::Mat4<real> & m_mmat;

		const t3d::Mat4<real> & m_mrot;
	};

	template <class CustomShaderObjectDrawerClass>
	void drawBSPSceneBackToFront(
		t3d::RenderContext * rc,
		const BSPNode & node,
		const t3d::Vec4<real> & cameraPos,
		const t3d::Vec4<real> & cameraDir,
		real cameraHalfFov,
		const CustomShaderObjectDrawerClass & drawer)
	{
		real distance = calculatePointPlaneDistance(cameraPos, node.planePoint, node.planeNormal);

		real angle = acos(t3d::vec3CosTheta(cameraDir, node.planeNormal));

		if(distance > 0)
		{
			if(angle + cameraHalfFov > DEG_TO_RAD(90))
			{
				if(NULL != node.back)
				{
					drawBSPSceneBackToFront(rc, *node.back, cameraPos, cameraDir, cameraHalfFov, drawer);
				}

				drawer.draw(rc, node.m_obj.get());
			}

			if(NULL != node.front)
			{
				drawBSPSceneBackToFront(rc, *node.front, cameraPos, cameraDir, cameraHalfFov, drawer);
			}
		}
		else
		{
			if(angle - cameraHalfFov < DEG_TO_RAD(90))
			{
				if(NULL != node.front)
				{
					drawBSPSceneBackToFront(rc, *node.front, cameraPos, cameraDir, cameraHalfFov, drawer);
				}
			}

			if(NULL != node.back)
			{
				drawBSPSceneBackToFront(rc, *node.back, cameraPos, cameraDir, cameraHalfFov, drawer);
			}
		}
	}

	template <class CustomShaderObjectDrawerClass>
	void drawBSPSceneFrontToBack(
		t3d::RenderContext * rc,
		const BSPNode & node,
		const t3d::Vec4<real> & cameraPos,
		const t3d::Vec4<real> & cameraDir,
		real cameraHalfFov,
		const CustomShaderObjectDrawerClass & drawer)
	{
		real distance = calculatePointPlaneDistance(cameraPos, node.planePoint, node.planeNormal);

		real angle = acos(t3d::vec3CosTheta(cameraDir, node.planeNormal));

		if(distance > 0)
		{
			if(NULL != node.front)
			{
				drawBSPSceneFrontToBack(rc, *node.front, cameraPos, cameraDir, cameraHalfFov, drawer);
			}

			if(angle + cameraHalfFov > DEG_TO_RAD(90))
			{
				drawer.draw(rc, node.m_obj.get());

				if(NULL != node.back)
				{
					drawBSPSceneFrontToBack(rc, *node.back, cameraPos, cameraDir, cameraHalfFov, drawer);
				}
			}
		}
		else
		{
			if(NULL != node.back)
			{
				drawBSPSceneFrontToBack(rc, *node.back, cameraPos, cameraDir, cameraHalfFov, drawer);
			}

			if(angle - cameraHalfFov < DEG_TO_RAD(90))
			{
				if(NULL != node.front)
				{
					drawBSPSceneFrontToBack(rc, *node.front, cameraPos, cameraDir, cameraHalfFov, drawer);
				}
			}
		}
	}

	void BSPNode::drawWireZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRC<&ObjectBase::drawWireZBufferRW>(color));
	}

	void BSPNode::drawWireZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRCM<&ObjectBase::drawWireZBufferRW>(color, mmat));
	}

	void BSPNode::drawWireZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRC<&ObjectBase::drawWireZBufferRWWithBackface>(color));
	}

	void BSPNode::drawWireZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRCM<&ObjectBase::drawWireZBufferRWWithBackface>(color, mmat));
	}

	void BSPNode::drawZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRC<&ObjectBase::drawZBufferRW>(color));
	}

	void BSPNode::drawZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRCM<&ObjectBase::drawZBufferRW>(color, mmat));
	}

	void BSPNode::drawZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRC<&ObjectBase::drawZBufferRWWithBackface>(color));
	}

	void BSPNode::drawZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRCM<&ObjectBase::drawZBufferRWWithBackface>(color, mmat));
	}

	void BSPNode::drawGouraudZBufferRW(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawGouraudZBufferRW>());
	}

	void BSPNode::drawGouraudZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRMM<&ObjectBase::drawGouraudZBufferRW>(mmat, mrot));
	}

	void BSPNode::drawGouraudZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawGouraudZBufferRWWithBackface>());
	}

	void BSPNode::drawGouraudZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRMM<&ObjectBase::drawGouraudZBufferRWWithBackface>(mmat, mrot));
	}

	void BSPNode::drawTextureZBufferW(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneBackToFront(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawTextureZBufferW>());
	}

	void BSPNode::drawTextureZBufferW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		drawBSPSceneBackToFront(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRM<&ObjectBase::drawTextureZBufferW>(mmat));
	}

	void BSPNode::drawTextureZBufferWWithBackface(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneBackToFront(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawTextureZBufferWWithBackface>());
	}

	void BSPNode::drawTextureZBufferWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		drawBSPSceneBackToFront(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRM<&ObjectBase::drawTextureZBufferWWithBackface>(mmat));
	}

	void BSPNode::drawTexturePerspectiveLPZBufferW(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneBackToFront(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawTexturePerspectiveLPZBufferW>());
	}

	void BSPNode::drawTexturePerspectiveLPZBufferW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		drawBSPSceneBackToFront(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRM<&ObjectBase::drawTexturePerspectiveLPZBufferW>(mmat));
	}

	void BSPNode::drawTexturePerspectiveLPZBufferWWithBackface(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneBackToFront(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawTexturePerspectiveLPZBufferWWithBackface>());
	}

	void BSPNode::drawTexturePerspectiveLPZBufferWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		drawBSPSceneBackToFront(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRM<&ObjectBase::drawTexturePerspectiveLPZBufferWWithBackface>(mmat));
	}

	void BSPNode::drawTextureZBufferRW(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawTextureZBufferRW>());
	}

	void BSPNode::drawTextureZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRM<&ObjectBase::drawTextureZBufferRW>(mmat));
	}

	void BSPNode::drawTextureZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawTextureZBufferRWWithBackface>());
	}

	void BSPNode::drawTextureZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRM<&ObjectBase::drawTextureZBufferRWWithBackface>(mmat));
	}

	void BSPNode::drawTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawTexturePerspectiveLPZBufferRW>());
	}

	void BSPNode::drawTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRM<&ObjectBase::drawTexturePerspectiveLPZBufferRW>(mmat));
	}

	void BSPNode::drawTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawTexturePerspectiveLPZBufferRWWithBackface>());
	}

	void BSPNode::drawTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRM<&ObjectBase::drawTexturePerspectiveLPZBufferRWWithBackface>(mmat));
	}

	void BSPNode::drawGouraudTextureZBufferRW(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawGouraudTextureZBufferRW>());
	}

	void BSPNode::drawGouraudTextureZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRMM<&ObjectBase::drawGouraudTextureZBufferRW>(mmat, mrot));
	}

	void BSPNode::drawGouraudTextureZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawGouraudTextureZBufferRWWithBackface>());
	}

	void BSPNode::drawGouraudTextureZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRMM<&ObjectBase::drawGouraudTextureZBufferRWWithBackface>(mmat, mrot));
	}

	void BSPNode::drawGouraudTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawGouraudTexturePerspectiveLPZBufferRW>());
	}

	void BSPNode::drawGouraudTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRMM<&ObjectBase::drawGouraudTexturePerspectiveLPZBufferRW>(mmat, mrot));
	}

	void BSPNode::drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawer<&ObjectBase::drawGouraudTexturePerspectiveLPZBufferRWWithBackface>());
	}

	void BSPNode::drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		drawBSPSceneFrontToBack(
			rc,
			*this,
			rc->getCameraPosition(),
			rc->getCameraDirection(),
			t3d::CameraContext::calculateCameraMaxHalfFov(rc->getCameraProjection()),
			CustomShaderObjectDrawerRMM<&ObjectBase::drawGouraudTexturePerspectiveLPZBufferRWWithBackface>(mmat, mrot));
	}

	BSPNodePtr buildBSPScene(
		const t3d::VertexList & vertexList,
		const t3d::NormalList & normalList,
		const t3d::UVList & uvList)
	{
		if(vertexList.empty())
			return BSPNodePtr();

		_ASSERT(vertexList.size() == normalList.size());
		_ASSERT(vertexList.size() == uvList.size());
		_ASSERT(0 == vertexList.size() % 3);

		BSPNodePtr node(new BSPNode());

		t3d::VertexList frontVertexList;
		t3d::NormalList frontNormalList;
		t3d::UVList frontUVList;

		t3d::VertexList backVertexList;
		t3d::NormalList backNormalList;
		t3d::UVList backUVList;

		node->planePoint = vertexList[0];

		node->planeNormal = calculateTriangleNormal(vertexList[0], vertexList[1], vertexList[2]);

		ObjectPtr obj(new Object());

		for(size_t i = 0; i < vertexList.size(); i += 3)
		{
			if(!splitTriangleVertexNormalUV(
				frontVertexList,
				frontNormalList,
				frontUVList,
				backVertexList,
				backNormalList,
				backUVList,
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
				obj->pushVertex(vertexList[i + 0]);
				obj->pushVertex(vertexList[i + 1]);
				obj->pushVertex(vertexList[i + 2]);

				obj->pushNormal(normalList[i + 0]);
				obj->pushNormal(normalList[i + 1]);
				obj->pushNormal(normalList[i + 2]);

				obj->pushUV(uvList[i + 0]);
				obj->pushUV(uvList[i + 1]);
				obj->pushUV(uvList[i + 2]);
			}
		}

		_ASSERT(!obj->getVertexList().empty());

		node->m_obj = obj;

		node->front = buildBSPScene(frontVertexList, frontNormalList, frontUVList);

		node->back = buildBSPScene(backVertexList, backNormalList, backUVList);

		return node;
	}

	//size_t balanceBSPNode(BSPNodePtr & node, int l_deepth, int r_deepth)
	//{
	//	if(l_deepth - r_deepth > 1)
	//	{
	//		_ASSERT(NULL != node);
	//		_ASSERT(NULL != node->front);

	//		BSPNodePtr tmpNode = node->front;
	//		node->front = node->front->back;
	//		tmpNode->back = node;
	//		node = tmpNode;

	//		return balanceBSPNode(node, l_deepth - 1, r_deepth + 1);
	//	}
	//	else if(r_deepth - l_deepth > 1)
	//	{
	//		_ASSERT(NULL != node);
	//		_ASSERT(NULL != node->back);

	//		BSPNodePtr tmpNode = node->back;
	//		node->back = node->back->front;
	//		tmpNode->front = node;
	//		node = tmpNode;

	//		return balanceBSPNode(node, l_deepth + 1, r_deepth - 1);
	//	}

	//	return std::max(l_deepth, r_deepth);
	//}

	//BSPNodePtr buildBalanceBSPScene(
	//	int & deepth,
	//	const t3d::VertexList & vertexList,
	//	const t3d::NormalList & normalList,
	//	const t3d::UVList & uvList)
	//{
	//	if(vertexList.empty())
	//	{
	//		deepth = 1;
	//		return BSPNodePtr();
	//	}

	//	_ASSERT(vertexList.size() == normalList.size());
	//	_ASSERT(vertexList.size() == uvList.size());
	//	_ASSERT(0 == vertexList.size() % 3);

	//	BSPNodePtr node(new BSPNode());

	//	t3d::VertexList frontVertexList;
	//	t3d::NormalList frontNormalList;
	//	t3d::UVList frontUVList;

	//	t3d::VertexList backVertexList;
	//	t3d::NormalList backNormalList;
	//	t3d::UVList backUVList;

	//	node->planePoint = vertexList[0];

	//	node->planeNormal = calculateTriangleNormal(vertexList[0], vertexList[1], vertexList[2]);

	//	for(size_t i = 0; i < vertexList.size(); i += 3)
	//	{
	//		if(!splitTriangleVertexNormalUV(
	//			frontVertexList,
	//			frontNormalList,
	//			frontUVList,
	//			backVertexList,
	//			backNormalList,
	//			backUVList,
	//			vertexList[i + 0],
	//			vertexList[i + 1],
	//			vertexList[i + 2],
	//			normalList[i + 0],
	//			normalList[i + 1],
	//			normalList[i + 2],
	//			uvList[i + 0],
	//			uvList[i + 1],
	//			uvList[i + 2],
	//			node->planePoint,
	//			node->planeNormal))
	//		{
	//			node->m_obj.pushVertex(vertexList[i + 0]);
	//			node->m_obj.pushVertex(vertexList[i + 1]);
	//			node->m_obj.pushVertex(vertexList[i + 2]);

	//			node->m_obj.pushNormal(normalList[i + 0]);
	//			node->m_obj.pushNormal(normalList[i + 1]);
	//			node->m_obj.pushNormal(normalList[i + 2]);

	//			node->m_obj.pushUV(uvList[i + 0]);
	//			node->m_obj.pushUV(uvList[i + 1]);
	//			node->m_obj.pushUV(uvList[i + 2]);
	//		}
	//	}

	//	_ASSERT(!node->m_obj.getVertexList().empty());

	//	int l_deepth;
	//	node->front = buildBalanceBSPScene(l_deepth, frontVertexList, frontNormalList, frontUVList);

	//	int r_deepth;
	//	node->back = buildBalanceBSPScene(r_deepth, backVertexList, backNormalList, backUVList);

	//	if(l_deepth != r_deepth)
	//	{
	//		deepth = balanceBSPNode(node, l_deepth, r_deepth) + 1;
	//	}
	//	else
	//	{
	//		deepth = l_deepth + 1;
	//	}

	//	return node;
	//}

	//void insertObjectToBSPScene(
	//	BSPNodePtr node,
	//	const CustomShaderObjectPtr & customShaderObj,
	//	const t3d::VertexList & objVertexList)
	//{
	//	if(node->m_obj.getVertexList().empty())
	//	{
	//		_ASSERT(NULL == node->front);
	//		_ASSERT(NULL == node->back);

	//		node->m_customShaderObjList.pushCustomShaderObj(customShaderObj);
	//	}
	//	else
	//	{
	//		_ASSERT(!node->m_obj.getVertexList().empty());

	//		bool haveFrontVertex = false;
	//		bool haveBackVertex = false;

	//		t3d::VertexList::const_iterator vert_iter = objVertexList.begin();
	//		for(; vert_iter != objVertexList.end(); vert_iter++)
	//		{
	//			real distance = calculatePointPlaneDistance(*vert_iter, node->planePoint, node->planeNormal);

	//			if(distance > DISTANCE_ZERO_LIMIT)
	//			{
	//				haveFrontVertex = true;
	//			}
	//			else if(distance < -DISTANCE_ZERO_LIMIT)
	//			{
	//				haveBackVertex = true;
	//			}
	//		}

	//		if(haveFrontVertex)
	//		{
	//			if(haveBackVertex)
	//			{
	//				node->m_customShaderObjList.pushCustomShaderObj(customShaderObj);
	//			}
	//			else
	//			{
	//				if(NULL == node->front)
	//					node->front = BSPNodePtr(new BSPNode());
	//					
	//				insertObjectToBSPScene(node->front, customShaderObj, objVertexList);
	//			}
	//		}
	//		else
	//		{
	//			if(haveBackVertex)
	//			{
	//				if(NULL == node->back)
	//					node->back = BSPNodePtr(new BSPNode());
	//					
	//				insertObjectToBSPScene(node->back, customShaderObj, objVertexList);
	//			}
	//			else
	//			{
	//				node->m_customShaderObjList.pushCustomShaderObj(customShaderObj);
	//			}
	//		}
	//	}
	//}

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
	//	IOStreamPtr meshStream)
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

	//			tmpObj.pushUV((real)u, (real)(/*1 -*/ v)); // ***
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

	//						_ASSERT(objPtr->getOriginalVertexList().size() == objPtr->getOriginalNormalList().size());
	//						_ASSERT(objPtr->getOriginalVertexList().size() == objPtr->getUVListSize());

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

	void LODTriNode::prepareVertexList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos) const
	{
		_ASSERT(3 == getVertexListSize());

		if(t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(0), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(1), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(2), cameraPos)) < minDistanceSquare)
		{
			lchild->prepareVertexList(rc, cameraPos);

			rchild->prepareVertexList(rc, cameraPos);
		}
		else
		{
			rc->pushVertexList(getVertexListBegin(), getVertexListEnd());
		}
	}

	void LODTriNode::prepareVertexList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos,
		const t3d::Mat4<real> & mmat) const
	{
		_ASSERT(3 == getVertexListSize());

		if(t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(0), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(1), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(2), cameraPos)) < minDistanceSquare)
		{
			lchild->prepareVertexList(rc, cameraPos);

			rchild->prepareVertexList(rc, cameraPos);
		}
		else
		{
			rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);
		}
	}

	void LODTriNode::prepareVertexNormalList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos) const
	{
		_ASSERT(3 == getVertexListSize());
		_ASSERT(getVertexListSize() == getNormalListSize());

		if(t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(0), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(1), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(2), cameraPos)) < minDistanceSquare)
		{
			lchild->prepareVertexNormalList(rc, cameraPos);

			rchild->prepareVertexNormalList(rc, cameraPos);
		}
		else
		{
			rc->pushVertexList(getVertexListBegin(), getVertexListEnd());
			rc->pushNormalList(getNormalListBegin(), getNormalListEnd());
		}
	}

	void LODTriNode::prepareVertexNormalList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(3 == getVertexListSize());
		_ASSERT(getVertexListSize() == getNormalListSize());

		if(t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(0), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(1), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(2), cameraPos)) < minDistanceSquare)
		{
			lchild->prepareVertexNormalList(rc, cameraPos);

			rchild->prepareVertexNormalList(rc, cameraPos);
		}
		else
		{
			rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);
			rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);
		}
	}

	void LODTriNode::prepareVertexUVList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos) const
	{
		_ASSERT(3 == getVertexListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		if(t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(0), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(1), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(2), cameraPos)) < minDistanceSquare)
		{
			lchild->prepareVertexUVList(rc, cameraPos);

			rchild->prepareVertexUVList(rc, cameraPos);
		}
		else
		{
			rc->pushVertexList(getVertexListBegin(), getVertexListEnd());
			rc->pushUVList(getUVListBegin(), getUVListEnd());
		}
	}

	void LODTriNode::prepareVertexUVList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos,
		const t3d::Mat4<real> & mmat) const
	{
		_ASSERT(3 == getVertexListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		if(t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(0), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(1), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(2), cameraPos)) < minDistanceSquare)
		{
			lchild->prepareVertexUVList(rc, cameraPos);

			rchild->prepareVertexUVList(rc, cameraPos);
		}
		else
		{
			rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);
			rc->pushUVList(getUVListBegin(), getUVListEnd());
		}
	}

	void LODTriNode::prepareVertexNormalUVList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos) const
	{
		_ASSERT(3 == getVertexListSize());
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		if(t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(0), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(1), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(2), cameraPos)) < minDistanceSquare)
		{
			lchild->prepareVertexNormalUVList(rc, cameraPos);

			rchild->prepareVertexNormalUVList(rc, cameraPos);
		}
		else
		{
			rc->pushVertexList(getVertexListBegin(), getVertexListEnd());
			rc->pushNormalList(getNormalListBegin(), getNormalListEnd());
			rc->pushUVList(getUVListBegin(), getUVListEnd());
		}
	}

	void LODTriNode::prepareVertexNormalUVList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		_ASSERT(3 == getVertexListSize());
		_ASSERT(getVertexListSize() == getNormalListSize());
		_ASSERT(getVertexListSize() == getUVListSize());

		if(t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(0), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(1), cameraPos)) < minDistanceSquare
			|| t3d::vec3LengthSquare(t3d::vec3Sub(vertexAt(2), cameraPos)) < minDistanceSquare)
		{
			lchild->prepareVertexNormalUVList(rc, cameraPos);

			rchild->prepareVertexNormalUVList(rc, cameraPos);
		}
		else
		{
			rc->pushVertexList(getVertexListBegin(), getVertexListEnd(), mmat);
			rc->pushNormalList(getNormalListBegin(), getNormalListEnd(), mrot);
			rc->pushUVList(getUVListBegin(), getUVListEnd());
		}
	}

	void LODTriNodeList::prepareVertexList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos) const
	{
		const_iterator iter = begin();
		for(; iter != end(); iter++)
		{
			(*iter)->prepareVertexList(rc, cameraPos);
		}
	}

	void LODTriNodeList::prepareVertexList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos,
		const t3d::Mat4<real> & mmat) const
	{
		const_iterator iter = begin();
		for(; iter != end(); iter++)
		{
			(*iter)->prepareVertexList(rc, cameraPos, mmat);
		}
	}

	void LODTriNodeList::prepareVertexNormalList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos) const
	{
		const_iterator iter = begin();
		for(; iter != end(); iter++)
		{
			(*iter)->prepareVertexNormalList(rc, cameraPos);
		}
	}

	void LODTriNodeList::prepareVertexNormalList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		const_iterator iter = begin();
		for(; iter != end(); iter++)
		{
			(*iter)->prepareVertexNormalList(rc, cameraPos, mmat, mrot);
		}
	}

	void LODTriNodeList::prepareVertexUVList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos) const
	{
		const_iterator iter = begin();
		for(; iter != end(); iter++)
		{
			(*iter)->prepareVertexUVList(rc, cameraPos);
		}
	}

	void LODTriNodeList::prepareVertexUVList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos,
		const t3d::Mat4<real> & mmat) const
	{
		const_iterator iter = begin();
		for(; iter != end(); iter++)
		{
			(*iter)->prepareVertexUVList(rc, cameraPos, mmat);
		}
	}

	void LODTriNodeList::prepareVertexNormalUVList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos) const
	{
		const_iterator iter = begin();
		for(; iter != end(); iter++)
		{
			(*iter)->prepareVertexNormalUVList(rc, cameraPos);
		}
	}

	void LODTriNodeList::prepareVertexNormalUVList(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & cameraPos,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		const_iterator iter = begin();
		for(; iter != end(); iter++)
		{
			(*iter)->prepareVertexNormalUVList(rc, cameraPos, mmat, mrot);
		}
	}

	void LODTriNodeList::drawWireZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		rc->clearVertexList();
		prepareVertexList(rc, rc->getCameraPosition());

		rc->drawTriangleListWireZBufferRW(color);
	}

	void LODTriNodeList::drawWireZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		prepareVertexList(rc, rc->getCameraPosition(), mmat);

		rc->drawTriangleListWireZBufferRW(color);
	}

	void LODTriNodeList::drawWireZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		rc->clearVertexList();
		prepareVertexList(rc, rc->getCameraPosition());

		rc->drawTriangleListWireZBufferRWWithBackface(color);
	}

	void LODTriNodeList::drawWireZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		prepareVertexList(rc, rc->getCameraPosition(), mmat);

		rc->drawTriangleListWireZBufferRWWithBackface(color);
	}

	void LODTriNodeList::drawZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		rc->clearVertexList();
		prepareVertexList(rc, rc->getCameraPosition());

		rc->drawTriangleListZBufferRW(color);
	}

	void LODTriNodeList::drawZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		prepareVertexList(rc, rc->getCameraPosition(), mmat);

		rc->drawTriangleListZBufferRW(color);
	}

	void LODTriNodeList::drawZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color) const
	{
		rc->clearVertexList();
		prepareVertexList(rc, rc->getCameraPosition());

		rc->drawTriangleListZBufferRWWithBackface(color);
	}

	void LODTriNodeList::drawZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Vec4<real> & color,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		prepareVertexList(rc, rc->getCameraPosition(), mmat);

		rc->drawTriangleListZBufferRWWithBackface(color);
	}

	void LODTriNodeList::drawGouraudZBufferRW(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearNormalList();
		prepareVertexNormalList(rc, rc->getCameraPosition());

		rc->drawTriangleListGouraudZBufferRW();
	}

	void LODTriNodeList::drawGouraudZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		rc->clearVertexList();
		rc->clearNormalList();
		prepareVertexNormalList(rc, rc->getCameraPosition(), mmat, mrot);

		rc->drawTriangleListGouraudZBufferRW();
	}

	void LODTriNodeList::drawGouraudZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearNormalList();
		prepareVertexNormalList(rc, rc->getCameraPosition());

		rc->drawTriangleListGouraudZBufferRWWithBackface();
	}

	void LODTriNodeList::drawGouraudZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		rc->clearVertexList();
		rc->clearNormalList();
		prepareVertexNormalList(rc, rc->getCameraPosition(), mmat, mrot);

		rc->drawTriangleListGouraudZBufferRWWithBackface();
	}

	void LODTriNodeList::drawTextureZBufferW(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition());

		rc->drawTriangleListTextureZBufferW();
	}

	void LODTriNodeList::drawTextureZBufferW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition(), mmat);

		rc->drawTriangleListTextureZBufferW();
	}

	void LODTriNodeList::drawTextureZBufferWWithBackface(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition());

		rc->drawTriangleListTextureZBufferWWithBackface();
	}

	void LODTriNodeList::drawTextureZBufferWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition(), mmat);

		rc->drawTriangleListTextureZBufferWWithBackface();
	}

	void LODTriNodeList::drawTexturePerspectiveLPZBufferW(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition());

		rc->drawTriangleListTexturePerspectiveLPZBufferW();
	}

	void LODTriNodeList::drawTexturePerspectiveLPZBufferW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition(), mmat);

		rc->drawTriangleListTexturePerspectiveLPZBufferW();
	}

	void LODTriNodeList::drawTexturePerspectiveLPZBufferWWithBackface(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition());

		rc->drawTriangleListTexturePerspectiveLPZBufferWWithBackface();
	}

	void LODTriNodeList::drawTexturePerspectiveLPZBufferWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition(), mmat);

		rc->drawTriangleListTexturePerspectiveLPZBufferWWithBackface();
	}

	void LODTriNodeList::drawTextureZBufferRW(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition());

		rc->drawTriangleListTextureZBufferRW();
	}

	void LODTriNodeList::drawTextureZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition(), mmat);

		rc->drawTriangleListTextureZBufferRW();
	}

	void LODTriNodeList::drawTextureZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition());

		rc->drawTriangleListTextureZBufferRWWithBackface();
	}

	void LODTriNodeList::drawTextureZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition(), mmat);

		rc->drawTriangleListTextureZBufferRWWithBackface();
	}

	void LODTriNodeList::drawTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition());

		rc->drawTriangleListTexturePerspectiveLPZBufferRW();
	}

	void LODTriNodeList::drawTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition(), mmat);

		rc->drawTriangleListTexturePerspectiveLPZBufferRW();
	}

	void LODTriNodeList::drawTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition());

		rc->drawTriangleListTexturePerspectiveLPZBufferRWWithBackface();
	}

	void LODTriNodeList::drawTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat) const
	{
		rc->clearVertexList();
		rc->clearUVList();
		prepareVertexUVList(rc, rc->getCameraPosition(), mmat);

		rc->drawTriangleListTexturePerspectiveLPZBufferRWWithBackface();
	}

	void LODTriNodeList::drawGouraudTextureZBufferRW(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearNormalList();
		rc->clearUVList();
		prepareVertexNormalUVList(rc, rc->getCameraPosition());

		rc->drawTriangleListGouraudTextureZBufferRW();
	}

	void LODTriNodeList::drawGouraudTextureZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		rc->clearVertexList();
		rc->clearNormalList();
		rc->clearUVList();
		prepareVertexNormalUVList(rc, rc->getCameraPosition(), mmat, mrot);

		rc->drawTriangleListGouraudTextureZBufferRW();
	}

	void LODTriNodeList::drawGouraudTextureZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearNormalList();
		rc->clearUVList();
		prepareVertexNormalUVList(rc, rc->getCameraPosition());

		rc->drawTriangleListGouraudTextureZBufferRWWithBackface();
	}

	void LODTriNodeList::drawGouraudTextureZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		rc->clearVertexList();
		rc->clearNormalList();
		rc->clearUVList();
		prepareVertexNormalUVList(rc, rc->getCameraPosition(), mmat, mrot);

		rc->drawTriangleListGouraudTextureZBufferRWWithBackface();
	}

	void LODTriNodeList::drawGouraudTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearNormalList();
		rc->clearUVList();
		prepareVertexNormalUVList(rc, rc->getCameraPosition());

		rc->drawTriangleListGouraudTexturePerspectiveLPZBufferRW();
	}

	void LODTriNodeList::drawGouraudTexturePerspectiveLPZBufferRW(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		rc->clearVertexList();
		rc->clearNormalList();
		rc->clearUVList();
		prepareVertexNormalUVList(rc, rc->getCameraPosition(), mmat, mrot);

		rc->drawTriangleListGouraudTexturePerspectiveLPZBufferRW();
	}

	void LODTriNodeList::drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc) const
	{
		rc->clearVertexList();
		rc->clearNormalList();
		rc->clearUVList();
		prepareVertexNormalUVList(rc, rc->getCameraPosition());

		rc->drawTriangleListGouraudTexturePerspectiveLPZBufferRWWithBackface();
	}

	void LODTriNodeList::drawGouraudTexturePerspectiveLPZBufferRWWithBackface(
		t3d::RenderContext * rc,
		const t3d::Mat4<real> & mmat,
		const t3d::Mat4<real> & mrot) const
	{
		rc->clearVertexList();
		rc->clearNormalList();
		rc->clearUVList();
		prepareVertexNormalUVList(rc, rc->getCameraPosition(), mmat, mrot);

		rc->drawTriangleListGouraudTexturePerspectiveLPZBufferRWWithBackface();
	}

	static t3d::Vec2<real> splitLODLine(
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec2<real> & ret0,
		const t3d::Vec2<real> & ret1)
	{
		if(v0.x < v1.x)
		{
			return t3d::vec2Mid(ret0, ret1);
		}
		else if(v0.x > v1.x)
		{
			return t3d::vec2Mid(ret1, ret0);
		}

		if(v0.y < v1.y)
		{
			return t3d::vec2Mid(ret0, ret1);
		}
		else if(v0.y > v1.y)
		{
			return t3d::vec2Mid(ret1, ret0);
		}

		if(v0.z < v1.z)
		{
			return t3d::vec2Mid(ret0, ret1);
		}
		else if(v0.z > v1.z)
		{
			return t3d::vec2Mid(ret1, ret0);
		}

		_ASSERT(t3d::vec3IsEqual(v0, v1));

		return t3d::vec2Mid(ret0, ret1);
	}

	static t3d::Vec4<real> splitLODLine(
		const t3d::Vec4<real> & v0,
		const t3d::Vec4<real> & v1,
		const t3d::Vec4<real> & ret0,
		const t3d::Vec4<real> & ret1)
	{
		if(v0.x < v1.x)
		{
			return t3d::vec3Mid(ret0, ret1);
		}
		else if(v0.x > v1.x)
		{
			return t3d::vec3Mid(ret1, ret0);
		}

		if(v0.y < v1.y)
		{
			return t3d::vec3Mid(ret0, ret1);
		}
		else if(v0.y > v1.y)
		{
			return t3d::vec3Mid(ret1, ret0);
		}

		if(v0.z < v1.z)
		{
			return t3d::vec3Mid(ret0, ret1);
		}
		else if(v0.z > v1.z)
		{
			return t3d::vec3Mid(ret1, ret0);
		}

		_ASSERT(t3d::vec3IsEqual(v0, v1));

		return t3d::vec3Mid(ret0, ret1);
	}

	static LODTriNodePtr buildLODTriNodeInside(
		const t3d::Vec4<real> v0,
		const t3d::Vec4<real> v1,
		const t3d::Vec4<real> v2,
		const t3d::Vec4<real> n0,
		const t3d::Vec4<real> n1,
		const t3d::Vec4<real> n2,
		const t3d::Vec2<real> t0,
		const t3d::Vec2<real> t1,
		const t3d::Vec2<real> t2,
		real levelDistance)
	{
		_ASSERT(t3d::vec3Length(t3d::vec3Sub(v0, v1)) >= t3d::vec3Length(t3d::vec3Sub(v1, v2)));
		_ASSERT(t3d::vec3Length(t3d::vec3Sub(v0, v1)) >= t3d::vec3Length(t3d::vec3Sub(v2, v0)));

		real maxLength = t3d::vec3Length(t3d::vec3Sub(v0, v1));

		real minDistance = levelDistance * floor(maxLength / levelDistance);

		t3d::Vec4<real> v3 = splitLODLine(v0, v1, v0, v1);
		t3d::Vec4<real> n3 = splitLODLine(v0, v1, n0, n1);
		t3d::Vec2<real> t3 = splitLODLine(v0, v1, t0, t1);

		LODTriNodePtr retNode(new LODTriNode());
		retNode->pushVertex(v0);
		retNode->pushVertex(v1);
		retNode->pushVertex(v2);
		retNode->pushNormal(n0);
		retNode->pushNormal(n1);
		retNode->pushNormal(n2);
		retNode->pushUV(t0);
		retNode->pushUV(t1);
		retNode->pushUV(t2);
		retNode->lchild = buildLODTriNode(v0, v3, v2, n0, n3, n2, t0, t3, t2, levelDistance);
		retNode->rchild = buildLODTriNode(v3, v1, v2, n3, n1, n2, t3, t1, t2, levelDistance);
		retNode->minDistanceSquare = minDistance * minDistance;

		return retNode;
	}

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
		real levelDistance)
	{
		real len01 = t3d::vec3Length(t3d::vec3Sub(v0, v1));
		real len12 = t3d::vec3Length(t3d::vec3Sub(v1, v2));
		real len20 = t3d::vec3Length(t3d::vec3Sub(v2, v0));

		if(len01 > len12)
		{
			if(len01 > len20)
			{
				if(len01 > levelDistance)
				{
					return buildLODTriNodeInside(v0, v1, v2, n0, n1, n2, t0, t1, t2, levelDistance);
				}
			}
			else
			{
				if(len20 > levelDistance)
				{
					return buildLODTriNodeInside(v2, v0, v1, n2, n0, n1, t2, t0, t1, levelDistance);
				}
			}
		}
		else
		{
			if(len12 > len20)
			{
				if(len12 > levelDistance)
				{
					return buildLODTriNodeInside(v1, v2, v0, n1, n2, n0, t1, t2, t0, levelDistance);
				}
			}
			else
			{
				if(len20 > levelDistance)
				{
					return buildLODTriNodeInside(v2, v0, v1, n2, n0, n1, t2, t0, t1, levelDistance);
				}
			}
		}

		LODTriNodePtr retNode(new LODTriNode());
		retNode->pushVertex(v0);
		retNode->pushVertex(v1);
		retNode->pushVertex(v2);
		retNode->pushNormal(n0);
		retNode->pushNormal(n1);
		retNode->pushNormal(n2);
		retNode->pushUV(t0);
		retNode->pushUV(t1);
		retNode->pushUV(t2);
		retNode->minDistanceSquare = 0;

		return retNode;
	}

	BSPNodePtr buildBSPSceneWithLODTriNode(
		const t3d::VertexList & vertexList,
		const t3d::NormalList & normalList,
		const t3d::UVList & uvList,
		real levelDistance)
	{
		if(vertexList.empty())
			return BSPNodePtr();

		_ASSERT(vertexList.size() == normalList.size());
		_ASSERT(vertexList.size() == uvList.size());
		_ASSERT(0 == vertexList.size() % 3);

		BSPNodePtr node(new BSPNode());

		t3d::VertexList frontVertexList;
		t3d::NormalList frontNormalList;
		t3d::UVList frontUVList;

		t3d::VertexList backVertexList;
		t3d::NormalList backNormalList;
		t3d::UVList backUVList;

		node->planePoint = vertexList[0];

		node->planeNormal = calculateTriangleNormal(vertexList[0], vertexList[1], vertexList[2]);

		LODTriNodeListPtr lodTriList(new LODTriNodeList());

		for(size_t i = 0; i < vertexList.size(); i += 3)
		{
			if(!splitTriangleVertexNormalUV(
				frontVertexList,
				frontNormalList,
				frontUVList,
				backVertexList,
				backNormalList,
				backUVList,
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
				lodTriList->push_back(buildLODTriNode(
					vertexList[i + 0],
					vertexList[i + 1],
					vertexList[i + 2],
					normalList[i + 0],
					normalList[i + 1],
					normalList[i + 2],
					uvList[i + 0],
					uvList[i + 1],
					uvList[i + 2],
					levelDistance));
			}
		}

		_ASSERT(!lodTriList->empty());

		node->m_obj = lodTriList;

		node->front = buildBSPSceneWithLODTriNode(frontVertexList, frontNormalList, frontUVList, levelDistance);

		node->back = buildBSPSceneWithLODTriNode(backVertexList, backNormalList, backUVList, levelDistance);

		return node;
	}

	void CustomShaderBasePtrList::draw(t3d::RenderContext * rc) const
	{
		const_iterator obj_iter = begin();
		for(; obj_iter != end(); obj_iter++)
		{
			(*obj_iter)->draw(rc);
		}
	}

	void CustomShaderBasePtrList::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		const_iterator obj_iter = begin();
		for(; obj_iter != end(); obj_iter++)
		{
			(*obj_iter)->draw(rc, mmat, mrot);
		}
	}

	void CustomShaderObjectWireZBufferRW::draw(t3d::RenderContext * rc) const
	{
		drawWireZBufferRW(rc, m_color);
	}

	void CustomShaderObjectWireZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		drawWireZBufferRW(rc, m_color, mmat); mrot;
	}

	void CustomShaderObjectWireZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		drawWireZBufferRWWithBackface(rc, m_color);
	}

	void CustomShaderObjectWireZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		drawWireZBufferRWWithBackface(rc, m_color, mmat); mrot;
	}

	void CustomShaderObjectZBufferRW::draw(t3d::RenderContext * rc) const
	{
		drawZBufferRW(rc, m_color);
	}

	void CustomShaderObjectZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		drawZBufferRW(rc, m_color, mmat); mrot;
	}

	void CustomShaderObjectZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		drawZBufferRWWithBackface(rc, m_color);
	}

	void CustomShaderObjectZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		drawZBufferRWWithBackface(rc, m_color, mmat); mrot;
	}

	void CustomShaderObjectGouraudZBufferRW::draw(t3d::RenderContext * rc) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		drawGouraudZBufferRW(rc);
	}

	void CustomShaderObjectGouraudZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		drawGouraudZBufferRW(rc, mmat, mrot);
	}

	void CustomShaderObjectGouraudZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		drawGouraudZBufferRWWithBackface(rc);
	}

	void CustomShaderObjectGouraudZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		drawGouraudZBufferRWWithBackface(rc, mmat, mrot);
	}

	void CustomShaderObjectTextureZBufferW::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferW(rc);
	}

	void CustomShaderObjectTextureZBufferW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferW(rc, mmat); mrot;
	}

	void CustomShaderObjectTextureZBufferWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferWWithBackface(rc);
	}

	void CustomShaderObjectTextureZBufferWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferWWithBackface(rc, mmat); mrot;
	}

	void CustomShaderObjectTexturePerspectiveLPZBufferW::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferW(rc);
	}

	void CustomShaderObjectTexturePerspectiveLPZBufferW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferW(rc, mmat); mrot;
	}

	void CustomShaderObjectTexturePerspectiveLPZBufferWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferWWithBackface(rc);
	}

	void CustomShaderObjectTexturePerspectiveLPZBufferWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferWWithBackface(rc, mmat); mrot;
	}

	void CustomShaderObjectTextureZBufferRW::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferRW(rc);
	}

	void CustomShaderObjectTextureZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferRW(rc, mmat); mrot;
	}

	void CustomShaderObjectTextureZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferRWWithBackface(rc);
	}

	void CustomShaderObjectTextureZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferRWWithBackface(rc, mmat); mrot;
	}

	void CustomShaderObjectTexturePerspectiveLPZBufferRW::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferRW(rc);
	}

	void CustomShaderObjectTexturePerspectiveLPZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferRW(rc, mmat); mrot;
	}

	void CustomShaderObjectTexturePerspectiveLPZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferRWWithBackface(rc);
	}

	void CustomShaderObjectTexturePerspectiveLPZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferRWWithBackface(rc, mmat); mrot;
	}

	void CustomShaderObjectGouraudTextureZBufferRW::draw(t3d::RenderContext * rc) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTextureZBufferRW(rc);
	}

	void CustomShaderObjectGouraudTextureZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTextureZBufferRW(rc, mmat, mrot);
	}

	void CustomShaderObjectGouraudTextureZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTextureZBufferRWWithBackface(rc);
	}

	void CustomShaderObjectGouraudTextureZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTextureZBufferRWWithBackface(rc, mmat, mrot);
	}

	void CustomShaderObjectGouraudTexturePerspectiveLPZBufferRW::draw(t3d::RenderContext * rc) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTexturePerspectiveLPZBufferRW(rc);
	}

	void CustomShaderObjectGouraudTexturePerspectiveLPZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTexturePerspectiveLPZBufferRW(rc, mmat, mrot);
	}

	void CustomShaderObjectGouraudTexturePerspectiveLPZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTexturePerspectiveLPZBufferRWWithBackface(rc);
	}

	void CustomShaderObjectGouraudTexturePerspectiveLPZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTexturePerspectiveLPZBufferRWWithBackface(rc, mmat, mrot);
	}

	void CustomShaderIndexObjectWireZBufferRW::draw(t3d::RenderContext * rc) const
	{
		drawWireZBufferRW(rc, m_color);
	}

	void CustomShaderIndexObjectWireZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		drawWireZBufferRW(rc, m_color, mmat); mrot;
	}

	void CustomShaderIndexObjectWireZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		drawWireZBufferRWWithBackface(rc, m_color);
	}

	void CustomShaderIndexObjectWireZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		drawWireZBufferRWWithBackface(rc, m_color, mmat); mrot;
	}

	void CustomShaderIndexObjectZBufferRW::draw(t3d::RenderContext * rc) const
	{
		drawZBufferRW(rc, m_color);
	}

	void CustomShaderIndexObjectZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		drawZBufferRW(rc, m_color, mmat); mrot;
	}

	void CustomShaderIndexObjectZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		drawZBufferRWWithBackface(rc, m_color);
	}

	void CustomShaderIndexObjectZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		drawZBufferRWWithBackface(rc, m_color, mmat); mrot;
	}

	void CustomShaderIndexObjectGouraudZBufferRW::draw(t3d::RenderContext * rc) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		drawGouraudZBufferRW(rc);
	}

	void CustomShaderIndexObjectGouraudZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		drawGouraudZBufferRW(rc, mmat, mrot);
	}

	void CustomShaderIndexObjectGouraudZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		drawGouraudZBufferRWWithBackface(rc);
	}

	void CustomShaderIndexObjectGouraudZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		drawGouraudZBufferRWWithBackface(rc, mmat, mrot);
	}

	void CustomShaderIndexObjectTextureZBufferW::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferW(rc);
	}

	void CustomShaderIndexObjectTextureZBufferW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferW(rc, mmat); mrot;
	}

	void CustomShaderIndexObjectTextureZBufferWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferWWithBackface(rc);
	}

	void CustomShaderIndexObjectTextureZBufferWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferWWithBackface(rc, mmat); mrot;
	}

	void CustomShaderIndexObjectTexturePerspectiveLPZBufferW::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferW(rc);
	}

	void CustomShaderIndexObjectTexturePerspectiveLPZBufferW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferW(rc, mmat); mrot;
	}

	void CustomShaderIndexObjectTexturePerspectiveLPZBufferWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferWWithBackface(rc);
	}

	void CustomShaderIndexObjectTexturePerspectiveLPZBufferWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferWWithBackface(rc, mmat); mrot;
	}

	void CustomShaderIndexObjectTextureZBufferRW::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferRW(rc);
	}

	void CustomShaderIndexObjectTextureZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferRW(rc, mmat); mrot;
	}

	void CustomShaderIndexObjectTextureZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferRWWithBackface(rc);
	}

	void CustomShaderIndexObjectTextureZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTextureZBufferRWWithBackface(rc, mmat); mrot;
	}

	void CustomShaderIndexObjectTexturePerspectiveLPZBufferRW::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferRW(rc);
	}

	void CustomShaderIndexObjectTexturePerspectiveLPZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferRW(rc, mmat); mrot;
	}

	void CustomShaderIndexObjectTexturePerspectiveLPZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferRWWithBackface(rc);
	}

	void CustomShaderIndexObjectTexturePerspectiveLPZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawTexturePerspectiveLPZBufferRWWithBackface(rc, mmat); mrot;
	}

	void CustomShaderIndexObjectGouraudTextureZBufferRW::draw(t3d::RenderContext * rc) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTextureZBufferRW(rc);
	}

	void CustomShaderIndexObjectGouraudTextureZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTextureZBufferRW(rc, mmat, mrot);
	}

	void CustomShaderIndexObjectGouraudTextureZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTextureZBufferRWWithBackface(rc);
	}

	void CustomShaderIndexObjectGouraudTextureZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTextureZBufferRWWithBackface(rc, mmat, mrot);
	}

	void CustomShaderIndexObjectGouraudTexturePerspectiveLPZBufferRW::draw(t3d::RenderContext * rc) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTexturePerspectiveLPZBufferRW(rc);
	}

	void CustomShaderIndexObjectGouraudTexturePerspectiveLPZBufferRW::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTexturePerspectiveLPZBufferRW(rc, mmat, mrot);
	}

	void CustomShaderIndexObjectGouraudTexturePerspectiveLPZBufferRWWithBackface::draw(t3d::RenderContext * rc) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTexturePerspectiveLPZBufferRWWithBackface(rc);
	}

	void CustomShaderIndexObjectGouraudTexturePerspectiveLPZBufferRWWithBackface::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		rc->setAmbient(m_material->getAmbient());
		rc->setDiffuse(m_material->getDiffuse());
		rc->setTextureBuffer(
			m_texture->getBits(),
			m_texture->getPitch(),
			m_texture->getWidth(),
			m_texture->getHeight());
		drawGouraudTexturePerspectiveLPZBufferRWWithBackface(rc, mmat, mrot);
	}

	void BackToFrontCustomShaderBSPNode::draw(t3d::RenderContext * rc) const
	{
		const t3d::Vec4<real> & cameraPos = rc->getCameraPosition();

		const t3d::Vec4<real> & cameraDir = rc->getCameraDirection();

		real distance = calculatePointPlaneDistance(cameraPos, planePoint, planeNormal);

		real angle = acos(t3d::vec3CosTheta(cameraDir, planeNormal));

		real cameraHalfFov = rc->getCameraMaxHalfFov();

		_ASSERT(self);

		if(distance > 0)
		{
			if(angle + cameraHalfFov > DEG_TO_RAD(90))
			{
				if(back)
				{
					back->draw(rc);
				}

				self->draw(rc);
			}

			if(front)
			{
				front->draw(rc);
			}
		}
		else
		{
			if(angle - cameraHalfFov < DEG_TO_RAD(90))
			{
				if(front)
				{
					front->draw(rc);
				}
			}

			if(back)
			{
				back->draw(rc);
			}
		}
	}

	void BackToFrontCustomShaderBSPNode::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		const t3d::Vec4<real> & cameraPos = rc->getCameraPosition();

		const t3d::Vec4<real> & cameraDir = rc->getCameraDirection();

		real distance = calculatePointPlaneDistance(cameraPos, planePoint, planeNormal);

		real angle = acos(t3d::vec3CosTheta(cameraDir, planeNormal));

		real cameraHalfFov = rc->getCameraMaxHalfFov();

		_ASSERT(self);

		if(distance > 0)
		{
			if(angle + cameraHalfFov > DEG_TO_RAD(90))
			{
				if(back)
				{
					back->draw(rc, mmat, mrot);
				}

				self->draw(rc, mmat, mrot);
			}

			if(front)
			{
				front->draw(rc, mmat, mrot);
			}
		}
		else
		{
			if(angle - cameraHalfFov < DEG_TO_RAD(90))
			{
				if(front)
				{
					front->draw(rc, mmat, mrot);
				}
			}

			if(back)
			{
				back->draw(rc, mmat, mrot);
			}
		}
	}

	void FrontToBackCustomShaderBSPNode::draw(t3d::RenderContext * rc) const
	{
		const t3d::Vec4<real> & cameraPos = rc->getCameraPosition();

		const t3d::Vec4<real> & cameraDir = rc->getCameraDirection();

		real distance = calculatePointPlaneDistance(cameraPos, planePoint, planeNormal);

		real angle = acos(t3d::vec3CosTheta(cameraDir, planeNormal));

		real cameraHalfFov = rc->getCameraMaxHalfFov();

		_ASSERT(self);

		if(distance > 0)
		{
			if(front)
			{
				front->draw(rc);
			}

			if(angle + cameraHalfFov > DEG_TO_RAD(90))
			{
				self->draw(rc);

				if(back)
				{
					back->draw(rc);
				}
			}
		}
		else
		{
			if(back)
			{
				back->draw(rc);
			}

			if(angle - cameraHalfFov < DEG_TO_RAD(90))
			{
				if(front)
				{
					front->draw(rc);
				}
			}
		}
	}

	void FrontToBackCustomShaderBSPNode::draw(t3d::RenderContext * rc, const t3d::Mat4<real> & mmat, const t3d::Mat4<real> & mrot) const
	{
		const t3d::Vec4<real> & cameraPos = rc->getCameraPosition();

		const t3d::Vec4<real> & cameraDir = rc->getCameraDirection();

		real distance = calculatePointPlaneDistance(cameraPos, planePoint, planeNormal);

		real angle = acos(t3d::vec3CosTheta(cameraDir, planeNormal));

		real cameraHalfFov = rc->getCameraMaxHalfFov();

		_ASSERT(self);

		if(distance > 0)
		{
			if(front)
			{
				front->draw(rc, mmat, mrot);
			}

			if(angle + cameraHalfFov > DEG_TO_RAD(90))
			{
				self->draw(rc, mmat, mrot);

				if(back)
				{
					back->draw(rc, mmat, mrot);
				}
			}
		}
		else
		{
			if(back)
			{
				back->draw(rc, mmat, mrot);
			}

			if(angle - cameraHalfFov < DEG_TO_RAD(90))
			{
				if(front)
				{
					front->draw(rc, mmat, mrot);
				}
			}
		}
	}

	FrontToBackCustomShaderBSPNodePtr buildFrontToBackBspSceneGouraudTexturePerspectiveLPZBufferRW(
		const t3d::VertexList & vertexList,
		const t3d::NormalList & normalList,
		const t3d::UVList & uvList,
		MaterialPtr material,
		ImagePtr texture)
	{
		if(vertexList.empty())
		{
			return FrontToBackCustomShaderBSPNodePtr();
		}

		_ASSERT(vertexList.size() == normalList.size());
		_ASSERT(vertexList.size() == uvList.size());
		_ASSERT(0 == vertexList.size() % 3);

		FrontToBackCustomShaderBSPNodePtr ret_node(
			new FrontToBackCustomShaderBSPNode(vertexList[0], calculateTriangleNormal(vertexList[0], vertexList[1], vertexList[2])));

		CustomShaderObjectPtr self_node(
			new CustomShaderObjectGouraudTexturePerspectiveLPZBufferRW(material, texture));

		t3d::VertexList frontVertexList;
		t3d::NormalList frontNormalList;
		t3d::UVList frontUVList;

		t3d::VertexList backVertexList;
		t3d::NormalList backNormalList;
		t3d::UVList backUVList;

		size_t i = 0;
		for(; i < vertexList.size(); i+= 3)
		{
			if(!splitTriangleVertexNormalUV(
				frontVertexList,
				frontNormalList,
				frontUVList,
				backVertexList,
				backNormalList,
				backUVList,
				vertexList[i + 0],
				vertexList[i + 1],
				vertexList[i + 2],
				normalList[i + 0],
				normalList[i + 1],
				normalList[i + 2],
				uvList[i + 0],
				uvList[i + 1],
				uvList[i + 2],
				ret_node->planePoint,
				ret_node->planeNormal))
			{
				self_node->pushVertex(vertexList[i + 0]);
				self_node->pushVertex(vertexList[i + 1]);
				self_node->pushVertex(vertexList[i + 2]);

				self_node->pushNormal(normalList[i + 0]);
				self_node->pushNormal(normalList[i + 1]);
				self_node->pushNormal(normalList[i + 2]);

				self_node->pushUV(uvList[i + 0]);
				self_node->pushUV(uvList[i + 1]);
				self_node->pushUV(uvList[i + 2]);
			}
		}

		_ASSERT(!self_node->getVertexList().empty());

		ret_node->self = self_node;

		ret_node->front = buildFrontToBackBspSceneGouraudTexturePerspectiveLPZBufferRW(
			frontVertexList,
			frontNormalList,
			frontUVList,
			material,
			texture);

		ret_node->back = buildFrontToBackBspSceneGouraudTexturePerspectiveLPZBufferRW(
			backVertexList,
			backNormalList,
			backUVList,
			material,
			texture);

		return ret_node;
	}
}
