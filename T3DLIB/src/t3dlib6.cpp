
#include "stdafx.h"
#include "t3dlib6.h"
#include "t3dlib9.h"

#define CLIP_MASK_V0	0x01
#define CLIP_MASK_V1	0x02
#define CLIP_MASK_V2	0x04

namespace t3d
{
	VertexList & transformVertexList(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const Mat4<real> & mmat)
	{
		retVertexList.resize(vertexList.size());

		for(size_t i = 0; i < retVertexList.size(); i++)
		{
			retVertexList[i] = vertexList[i] * mmat;
		}

		return retVertexList;
	}

	VertexList & transformVertexListSelf(
		VertexList & vertexList,
		const Mat4<real> & mmat)
	{
		VertexList::iterator vert_iter = vertexList.begin();
		for(; vert_iter != vertexList.end(); vert_iter++)
		{
			(*vert_iter) *= mmat;
		}

		return vertexList;
	}

	VertexList & transformLineList(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 2);

		retVertexList.resize(vertexList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				retVertexList[i * 2 + 0] = vertexList[i * 2 + 0] * mmat;
				retVertexList[i * 2 + 1] = vertexList[i * 2 + 1] * mmat;
			}
		}

		return retVertexList;
	}

	VertexList & transformLineListSelf(
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

		return vertexList;
	}

	VertexList & transformLineIndexList(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 2);

		return transformVertexList(retVertexList, vertexList, mmat);
	}

	VertexList & transformLineIndexListSelf(
		VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 2);

		return transformVertexListSelf(vertexList, mmat);
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
				drawLineZBufferRW16(
					surface,
					zbuffer,
					vertexList[i * 2 + 0],
					vertexList[i * 2 + 1],
					color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedLineZBufferRW16(
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
				drawLineZBufferRW16(
					surface,
					zbuffer,
					vertexList[vertexIndexList[i * 2 + 0]],
					vertexList[vertexIndexList[i * 2 + 1]],
					color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedLineZBufferRW16(
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
		const Vec4<real> & eye)
	{
		return vec3Dot(vec3Cross(vec3Sub(v1, v0), vec3Sub(v2, v0)), vec3Sub(eye, v0)) <= 0 ? CLIP_STATE_CULLED : CLIP_STATE_NONE;
	}

	void removeTriangleListBackfaceAtWorld(
		const VertexList & vertexList,
		ClipStateList & clipStateList,
		const Vec4<real> & eye)
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
					eye);
			}
		}
	}

	void removeTriangleIndexListBackfaceAtWorld(
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		ClipStateList & clipStateList,
		const Vec4<real> & eye)
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
					eye);
			}
		}
	}

	VertexList & transformTriangleList(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat)
	{
		_ASSERT(vertexList.size() == clipStateList.size() * 3);

		retVertexList.resize(vertexList.size());

		size_t i = 0;
		for(; i < clipStateList.size(); i++)
		{
			_ASSERT(CLIP_STATE_SCLIPPED != clipStateList[i]);

			if(CLIP_STATE_NONE == clipStateList[i])
			{
				retVertexList[i * 3 + 0] = vertexList[i * 3 + 0] * mmat;
				retVertexList[i * 3 + 1] = vertexList[i * 3 + 1] * mmat;
				retVertexList[i * 3 + 2] = vertexList[i * 3 + 2] * mmat;
			}
		}

		return retVertexList;
	}

	VertexList & transformTriangleListSelf(
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

		return vertexList;
	}

	VertexList & transformTriangleIndexList(
		VertexList & retVertexList,
		const VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);

		return transformVertexList(retVertexList, vertexList, mmat);
	}

	VertexList & transformTriangleIndexListSelf(
		VertexList & vertexList,
		const VertexIndexList & vertexIndexList,
		const ClipStateList & clipStateList,
		const Mat4<real> & mmat)
	{
		_ASSERT(vertexIndexList.size() == clipStateList.size() * 3);

		return transformVertexListSelf(vertexList, mmat);
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
				drawLineZBufferRW16(surface, zbuffer, vertexList[i * 3 + 0], vertexList[i * 3 + 1], color * 255);
				drawLineZBufferRW16(surface, zbuffer, vertexList[i * 3 + 1], vertexList[i * 3 + 2], color * 255);
				drawLineZBufferRW16(surface, zbuffer, vertexList[i * 3 + 2], vertexList[i * 3 + 0], color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedLineZBufferRW16(surface, clipper, zbuffer, vertexList[i * 3 + 0], vertexList[i * 3 + 1], color * 255);
				drawClippedLineZBufferRW16(surface, clipper, zbuffer, vertexList[i * 3 + 1], vertexList[i * 3 + 2], color * 255);
				drawClippedLineZBufferRW16(surface, clipper, zbuffer, vertexList[i * 3 + 2], vertexList[i * 3 + 0], color * 255);
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
				drawLineZBufferRW16(surface, zbuffer, vertexList[vertexIndexList[i * 3 + 0]], vertexList[vertexIndexList[i * 3 + 1]], color * 255);
				drawLineZBufferRW16(surface, zbuffer, vertexList[vertexIndexList[i * 3 + 1]], vertexList[vertexIndexList[i * 3 + 2]], color * 255);
				drawLineZBufferRW16(surface, zbuffer, vertexList[vertexIndexList[i * 3 + 2]], vertexList[vertexIndexList[i * 3 + 0]], color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedLineZBufferRW16(surface, clipper, zbuffer, vertexList[vertexIndexList[i * 3 + 0]], vertexList[vertexIndexList[i * 3 + 1]], color * 255);
				drawClippedLineZBufferRW16(surface, clipper, zbuffer, vertexList[vertexIndexList[i * 3 + 1]], vertexList[vertexIndexList[i * 3 + 2]], color * 255);
				drawClippedLineZBufferRW16(surface, clipper, zbuffer, vertexList[vertexIndexList[i * 3 + 2]], vertexList[vertexIndexList[i * 3 + 0]], color * 255);
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
				drawTriangleZBufferRW16(
					surface,
					zbuffer,
					vertexList[i * 3 + 0],
					vertexList[i * 3 + 1],
					vertexList[i * 3 + 2],
					color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleZBufferRW16(
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
				drawTriangleZBufferRW16(
					surface,
					zbuffer,
					vertexList[vertexIndexList[i * 3 + 0]],
					vertexList[vertexIndexList[i * 3 + 1]],
					vertexList[vertexIndexList[i * 3 + 2]],
					color * 255);
				break;

			case CLIP_STATE_SCLIPPED:
				drawClippedTriangleZBufferRW16(
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
				drawTriangleGouraudZBufferRW16(
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
				drawClippedTriangleGouraudZBufferRW16(
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
				drawTriangleGouraudZBufferRW16(
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
				drawClippedTriangleGouraudZBufferRW16(
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
				drawTriangleTextureZBufferW16(
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
				drawClippedTriangleTextureZBufferW16(
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
				drawTriangleTextureZBufferW16(
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
				drawClippedTriangleTextureZBufferW16(
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
				drawTriangleTexturePerspectiveLPZBufferW16(
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
				drawClippedTriangleTexturePerspectiveLPZBufferW16(
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
				drawTriangleTexturePerspectiveLPZBufferW16(
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
				drawClippedTriangleTexturePerspectiveLPZBufferW16(
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
				drawTriangleTextureZBufferRW16(
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
				drawClippedTriangleTextureZBufferRW16(
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
				drawTriangleTextureZBufferRW16(
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
				drawClippedTriangleTextureZBufferRW16(
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
				drawTriangleTexturePerspectiveLPZBufferRW16(
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
				drawClippedTriangleTexturePerspectiveLPZBufferRW16(
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
				drawTriangleTexturePerspectiveLPZBufferRW16(
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
				drawClippedTriangleTexturePerspectiveLPZBufferRW16(
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
		SurfaceRef<uint16> texture,
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
				drawTriangleGouraudTextureZBufferRW16(
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
				drawClippedTriangleGouraudTextureZBufferRW16(
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
		SurfaceRef<uint16> texture,
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
				drawTriangleGouraudTextureZBufferRW16(
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
				drawClippedTriangleGouraudTextureZBufferRW16(
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
		SurfaceRef<uint16> texture,
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
				drawTriangleGouraudTexturePerspectiveLPZBufferRW16(
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
				drawClippedTriangleGouraudTexturePerspectiveLPZBufferRW16(
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
		SurfaceRef<uint16> texture,
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
				drawTriangleGouraudTexturePerspectiveLPZBufferRW16(
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
				drawClippedTriangleGouraudTexturePerspectiveLPZBufferRW16(
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
