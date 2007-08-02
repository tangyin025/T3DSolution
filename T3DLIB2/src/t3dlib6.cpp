/*
 * File: T3DLIB2/t3dlib6.cpp
 */

#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib4.h"
#include "t3dlib5.h"
#include "t3dlib6.h"

static void Clip_Triangle_XPlane(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam)
{
	int clip_count = 0;
	if(abs(pvers->elems[ptri->v0_i].x)
			> pvers->elems[ptri->v0_i].z * (REAL)0.5 * pcam->viewplane.width / CAM4DV1_VIEWPLANE_DIST)
		clip_count++;

	if(abs(pvers->elems[ptri->v1_i].x)
			> pvers->elems[ptri->v1_i].z * (REAL)0.5 * pcam->viewplane.width / CAM4DV1_VIEWPLANE_DIST)
		clip_count++;

	if(abs(pvers->elems[ptri->v2_i].x)
			> pvers->elems[ptri->v2_i].z * (REAL)0.5 * pcam->viewplane.width / CAM4DV1_VIEWPLANE_DIST)
		clip_count++;

	switch(clip_count)
	{
	case 3:
		ptri->state = TRI_STATE_CULLED;
		break;

	case 1:
	case 2:
		ptri->state = TRI_STATE_CLIPPED;
		break;

	default:
		assert(clip_count == 0);
		break;
	}
	UNREFERENCED_PARAMETER(pnors);
}

static void Clip_Triangle_YPlane(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam)
{
	int clip_count = 0;
	if(abs(pvers->elems[ptri->v0_i].y)
			> pvers->elems[ptri->v0_i].z * (REAL)0.5 * pcam->viewplane.height / CAM4DV1_VIEWPLANE_DIST)
		clip_count++;

	if(abs(pvers->elems[ptri->v1_i].y)
			> pvers->elems[ptri->v1_i].z * (REAL)0.5 * pcam->viewplane.height / CAM4DV1_VIEWPLANE_DIST)
		clip_count++;

	if(abs(pvers->elems[ptri->v2_i].y)
			> pvers->elems[ptri->v2_i].z * (REAL)0.5 * pcam->viewplane.height / CAM4DV1_VIEWPLANE_DIST)
		clip_count++;

	switch(clip_count)
	{
	case 3:
		ptri->state = TRI_STATE_CULLED;
		break;

	case 1:
	case 2:
		ptri->state = TRI_STATE_CLIPPED;
		break;

	default:
		assert(clip_count == 0);
		break;
	}
	UNREFERENCED_PARAMETER(pnors);
}

static bool Clip_Triangle_ZPlane_Near1(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	TRIANGLEV1 * pt0;
	if(!Append_Array(ptris, &pt0))
		return false;
	memcpy(pt0, ptri, sizeof(*pt0));

	if(pvers->elems[ptri->v0_i].z < pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v0_i;
		pt0->v1_i = ptri->v1_i;
		pt0->v2_i = ptri->v2_i;
	}
	else if(pvers->elems[ptri->v1_i].z < pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v1_i;
		pt0->v1_i = ptri->v2_i;
		pt0->v2_i = ptri->v0_i;
	}
	else
	{
		assert(pvers->elems[ptri->v2_i].z < pcam->min_clip_z);
		pt0->v0_i = ptri->v2_i;
		pt0->v1_i = ptri->v0_i;
		pt0->v2_i = ptri->v1_i;
	}

	VERTEXV1T * pv0;
	if(!Append_Array(pvers, &pv0))
		return false;
	memcpy(pv0, &pvers->elems[pt0->v0_i], sizeof(*pv0));
pv0->c_diff = Create_RGBI(0, 255, 255);

	pv0->z = pcam->min_clip_z;
	pv0->x = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v1_i].x,
								pvers->elems[pt0->v0_i].x);

	pv0->y = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v1_i].y,
								pvers->elems[pt0->v0_i].y);

	//pt0->v0_i = (int)pvers->length - 1;
		// !!! note : cannot change the pt0->v0_i, because the following pv1 use the old pt0->v0_i

	TRIANGLEV1 * pt1;
	if(!Append_Array(ptris, &pt1))
		return false;
	memcpy(pt1, ptri, sizeof(*pt1));
	pt0 = &ptris->elems[ptris->length - 2];

	VERTEXV1T * pv1;
	if(!Append_Array(pvers, &pv1))
		return false;
	memcpy(pv1, &pvers->elems[pt0->v0_i], sizeof(*pv1));
pv1->c_diff = Create_RGBI(0, 255, 255);

	pv1->z = pcam->min_clip_z;
	pv1->x = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].x,
								pvers->elems[pt0->v0_i].x);

	pv1->y = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].y,
								pvers->elems[pt0->v0_i].y);

	pt0->v0_i = (int)pvers->length - 2;
	pt1->v0_i = (int)pvers->length - 2;
	pt1->v1_i = pt0->v2_i;
	pt1->v2_i = (int)pvers->length - 1;

	ptri->state = TRI_STATE_CULLED;
	return true;
	UNREFERENCED_PARAMETER(pnors);
}

static bool Clip_Triangle_ZPlane_Near2(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	TRIANGLEV1 * pt0;
	if(!Append_Array(ptris, &pt0))
		return false;
	memcpy(pt0, ptri, sizeof(*pt0));

	if(pvers->elems[ptri->v0_i].z > pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v1_i;
		pt0->v1_i = ptri->v2_i;
		pt0->v2_i = ptri->v0_i;
	}
	else if(pvers->elems[ptri->v1_i].z > pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v2_i;
		pt0->v1_i = ptri->v0_i;
		pt0->v2_i = ptri->v1_i;
	}
	else
	{
		assert(pvers->elems[ptri->v2_i].z > pcam->min_clip_z);
		pt0->v0_i = ptri->v0_i;
		pt0->v1_i = ptri->v1_i;
		pt0->v2_i = ptri->v2_i;
	}

	VERTEXV1T * pv0;
	if(!Append_Array(pvers, &pv0))
		return false;
	memcpy(pv0, &pvers->elems[pt0->v0_i], sizeof(*pv0));
pv0->c_diff = Create_RGBI(0, 255, 255);

	pv0->z = pcam->min_clip_z;
	pv0->x = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].x,
								pvers->elems[pt0->v0_i].x);

	pv0->y = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].y,
								pvers->elems[pt0->v0_i].y);

	VERTEXV1T * pv1;
	if(!Append_Array(pvers, &pv1))
		return false;
	memcpy(pv1, &pvers->elems[pt0->v1_i], sizeof(*pv1));
pv1->c_diff = Create_RGBI(0, 255, 255);

	pv1->z = pcam->min_clip_z;
	pv1->x = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v2_i].x,
								pvers->elems[pt0->v1_i].x);

	pv1->y = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v2_i].y,
								pvers->elems[pt0->v1_i].y);

	pt0->v0_i = (int)pvers->length - 2;
	pt0->v1_i = (int)pvers->length - 1;

	ptri->state = TRI_STATE_CULLED;
	return true;
	UNREFERENCED_PARAMETER(pnors);
}

static bool Clip_Triangle_ZPlane(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	int clip_count_max = 0;
	int clip_count_min = 0;

	if(pvers->elems[ptri->v0_i].z > pcam->max_clip_z)
		clip_count_max++;
	else if(pvers->elems[ptri->v0_i].z < pcam->min_clip_z)
		clip_count_min++;

	if(pvers->elems[ptri->v1_i].z > pcam->max_clip_z)
		clip_count_max++;
	else if(pvers->elems[ptri->v1_i].z < pcam->min_clip_z)
		clip_count_min++;

	if(pvers->elems[ptri->v2_i].z > pcam->max_clip_z)
		clip_count_max++;
	else if(pvers->elems[ptri->v2_i].z < pcam->min_clip_z)
		clip_count_min++;

	if(clip_count_max >= 3 || clip_count_min >= 3)
	{
		ptri->state = TRI_STATE_CULLED;
		return true;
	}

	switch(clip_count_min)
	{
	case 1:
		if(!Clip_Triangle_ZPlane_Near1(ptri, pvers, pnors, pcam, ptris))
			return false;
		break;

	case 2:
		if(!Clip_Triangle_ZPlane_Near2(ptri, pvers, pnors, pcam, ptris))
			return false;
		break;
	}
	return true;
}

static bool Clip_Triangle_ZPlane_Near1_Gouraud_Texture16(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	TRIANGLEV1 * pt0;
	if(!Append_Array(ptris, &pt0))
		return false;
	memcpy(pt0, ptri, sizeof(*pt0));

	if(pvers->elems[ptri->v0_i].z < pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v0_i;
		pt0->v1_i = ptri->v1_i;
		pt0->v2_i = ptri->v2_i;
	}
	else if(pvers->elems[ptri->v1_i].z < pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v1_i;
		pt0->v1_i = ptri->v2_i;
		pt0->v2_i = ptri->v0_i;
	}
	else
	{
		assert(pvers->elems[ptri->v2_i].z < pcam->min_clip_z);
		pt0->v0_i = ptri->v2_i;
		pt0->v1_i = ptri->v0_i;
		pt0->v2_i = ptri->v1_i;
	}

	VERTEXV1T * pv0;
	if(!Append_Array(pvers, &pv0))
		return false;
	memcpy(pv0, &pvers->elems[pt0->v0_i], sizeof(*pv0));

	pv0->z = pcam->min_clip_z;
	pv0->x = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v1_i].x,
								pvers->elems[pt0->v0_i].x);

	pv0->y = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v1_i].y,
								pvers->elems[pt0->v0_i].y);

	pv0->u = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v1_i].u,
								pvers->elems[pt0->v0_i].u);

	pv0->v = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v1_i].v,
								pvers->elems[pt0->v0_i].v);

	pv0->c_diff = _RGB16BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v1_i].z,
										pvers->elems[pt0->v0_i].z,
										_16BIT_GETR(pvers->elems[pt0->v1_i].c_diff),
										_16BIT_GETR(pvers->elems[pt0->v0_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v1_i].z,
										pvers->elems[pt0->v0_i].z,
										_16BIT_GETG(pvers->elems[pt0->v1_i].c_diff),
										_16BIT_GETG(pvers->elems[pt0->v0_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v1_i].z,
										pvers->elems[pt0->v0_i].z,
										_16BIT_GETB(pvers->elems[pt0->v1_i].c_diff),
										_16BIT_GETB(pvers->elems[pt0->v0_i].c_diff)));

	TRIANGLEV1 * pt1;
	if(!Append_Array(ptris, &pt1))
		return false;
	memcpy(pt1, ptri, sizeof(*pt1));
	pt0 = &ptris->elems[ptris->length - 2];

	VERTEXV1T * pv1;
	if(!Append_Array(pvers, &pv1))
		return false;
	memcpy(pv1, &pvers->elems[pt0->v0_i], sizeof(*pv1));

	pv1->z = pcam->min_clip_z;
	pv1->x = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].x,
								pvers->elems[pt0->v0_i].x);

	pv1->y = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].y,
								pvers->elems[pt0->v0_i].y);

	pv1->u = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].u,
								pvers->elems[pt0->v0_i].u);

	pv1->v = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].v,
								pvers->elems[pt0->v0_i].v);

	pv1->c_diff = _RGB16BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										_16BIT_GETR(pvers->elems[pt0->v2_i].c_diff),
										_16BIT_GETR(pvers->elems[pt0->v0_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										_16BIT_GETG(pvers->elems[pt0->v2_i].c_diff),
										_16BIT_GETG(pvers->elems[pt0->v0_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										_16BIT_GETB(pvers->elems[pt0->v2_i].c_diff),
										_16BIT_GETB(pvers->elems[pt0->v0_i].c_diff)));

	pt0->v0_i = (int)pvers->length - 2;
	pt1->v0_i = (int)pvers->length - 2;
	pt1->v1_i = pt0->v2_i;
	pt1->v2_i = (int)pvers->length - 1;

	ptri->state = TRI_STATE_CULLED;
	return true;
	UNREFERENCED_PARAMETER(pnors);
}

static bool Clip_Triangle_ZPlane_Near1_Gouraud_Texture32(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	TRIANGLEV1 * pt0;
	if(!Append_Array(ptris, &pt0))
		return false;
	memcpy(pt0, ptri, sizeof(*pt0));

	if(pvers->elems[ptri->v0_i].z < pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v0_i;
		pt0->v1_i = ptri->v1_i;
		pt0->v2_i = ptri->v2_i;
	}
	else if(pvers->elems[ptri->v1_i].z < pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v1_i;
		pt0->v1_i = ptri->v2_i;
		pt0->v2_i = ptri->v0_i;
	}
	else
	{
		assert(pvers->elems[ptri->v2_i].z < pcam->min_clip_z);
		pt0->v0_i = ptri->v2_i;
		pt0->v1_i = ptri->v0_i;
		pt0->v2_i = ptri->v1_i;
	}

	VERTEXV1T * pv0;
	if(!Append_Array(pvers, &pv0))
		return false;
	memcpy(pv0, &pvers->elems[pt0->v0_i], sizeof(*pv0));

	pv0->z = pcam->min_clip_z;
	pv0->x = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v1_i].x,
								pvers->elems[pt0->v0_i].x);

	pv0->y = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v1_i].y,
								pvers->elems[pt0->v0_i].y);

	pv0->u = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v1_i].u,
								pvers->elems[pt0->v0_i].u);

	pv0->v = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v1_i].v,
								pvers->elems[pt0->v0_i].v);

	pv0->c_diff = _RGB32BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v1_i].z,
										pvers->elems[pt0->v0_i].z,
										_32BIT_GETR(pvers->elems[pt0->v1_i].c_diff),
										_32BIT_GETR(pvers->elems[pt0->v0_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v1_i].z,
										pvers->elems[pt0->v0_i].z,
										_32BIT_GETG(pvers->elems[pt0->v1_i].c_diff),
										_32BIT_GETG(pvers->elems[pt0->v0_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v1_i].z,
										pvers->elems[pt0->v0_i].z,
										_32BIT_GETB(pvers->elems[pt0->v1_i].c_diff),
										_32BIT_GETB(pvers->elems[pt0->v0_i].c_diff)));

	TRIANGLEV1 * pt1;
	if(!Append_Array(ptris, &pt1))
		return false;
	memcpy(pt1, ptri, sizeof(*pt1));
	pt0 = &ptris->elems[ptris->length - 2];

	VERTEXV1T * pv1;
	if(!Append_Array(pvers, &pv1))
		return false;
	memcpy(pv1, &pvers->elems[pt0->v0_i], sizeof(*pv1));

	pv1->z = pcam->min_clip_z;
	pv1->x = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].x,
								pvers->elems[pt0->v0_i].x);

	pv1->y = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].y,
								pvers->elems[pt0->v0_i].y);

	pv1->u = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].u,
								pvers->elems[pt0->v0_i].u);

	pv1->v = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].v,
								pvers->elems[pt0->v0_i].v);

	pv1->c_diff = _RGB32BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										_32BIT_GETR(pvers->elems[pt0->v2_i].c_diff),
										_32BIT_GETR(pvers->elems[pt0->v0_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										_32BIT_GETG(pvers->elems[pt0->v2_i].c_diff),
										_32BIT_GETG(pvers->elems[pt0->v0_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										_32BIT_GETB(pvers->elems[pt0->v2_i].c_diff),
										_32BIT_GETB(pvers->elems[pt0->v0_i].c_diff)));

	pt0->v0_i = (int)pvers->length - 2;
	pt1->v0_i = (int)pvers->length - 2;
	pt1->v1_i = pt0->v2_i;
	pt1->v2_i = (int)pvers->length - 1;

	ptri->state = TRI_STATE_CULLED;
	return true;
	UNREFERENCED_PARAMETER(pnors);
}

static bool Clip_Triangle_ZPlane_Near2_Gouraud_Texture16(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	TRIANGLEV1 * pt0;
	if(!Append_Array(ptris, &pt0))
		return false;
	memcpy(pt0, ptri, sizeof(*pt0));

	if(pvers->elems[ptri->v0_i].z > pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v1_i;
		pt0->v1_i = ptri->v2_i;
		pt0->v2_i = ptri->v0_i;
	}
	else if(pvers->elems[ptri->v1_i].z > pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v2_i;
		pt0->v1_i = ptri->v0_i;
		pt0->v2_i = ptri->v1_i;
	}
	else
	{
		assert(pvers->elems[ptri->v2_i].z > pcam->min_clip_z);
		pt0->v0_i = ptri->v0_i;
		pt0->v1_i = ptri->v1_i;
		pt0->v2_i = ptri->v2_i;
	}

	VERTEXV1T * pv0;
	if(!Append_Array(pvers, &pv0))
		return false;
	memcpy(pv0, &pvers->elems[pt0->v0_i], sizeof(*pv0));

	pv0->z = pcam->min_clip_z;
	pv0->x = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].x,
								pvers->elems[pt0->v0_i].x);

	pv0->y = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].y,
								pvers->elems[pt0->v0_i].y);

	pv0->u = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].u,
								pvers->elems[pt0->v0_i].u);

	pv0->v = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].v,
								pvers->elems[pt0->v0_i].v);

	pv0->c_diff = _RGB16BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										_16BIT_GETR(pvers->elems[pt0->v2_i].c_diff),
										_16BIT_GETR(pvers->elems[pt0->v0_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										_16BIT_GETG(pvers->elems[pt0->v2_i].c_diff),
										_16BIT_GETG(pvers->elems[pt0->v0_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										_16BIT_GETB(pvers->elems[pt0->v2_i].c_diff),
										_16BIT_GETB(pvers->elems[pt0->v0_i].c_diff)));

	VERTEXV1T * pv1;
	if(!Append_Array(pvers, &pv1))
		return false;
	memcpy(pv1, &pvers->elems[pt0->v1_i], sizeof(*pv1));

	pv1->z = pcam->min_clip_z;
	pv1->x = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v2_i].x,
								pvers->elems[pt0->v1_i].x);

	pv1->y = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v2_i].y,
								pvers->elems[pt0->v1_i].y);

	pv1->u = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v2_i].u,
								pvers->elems[pt0->v1_i].u);

	pv1->v = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v2_i].v,
								pvers->elems[pt0->v1_i].v);

	pv1->c_diff = _RGB16BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v1_i].z,
										_16BIT_GETR(pvers->elems[pt0->v2_i].c_diff),
										_16BIT_GETR(pvers->elems[pt0->v1_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v1_i].z,
										_16BIT_GETG(pvers->elems[pt0->v2_i].c_diff),
										_16BIT_GETG(pvers->elems[pt0->v1_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v1_i].z,
										_16BIT_GETB(pvers->elems[pt0->v2_i].c_diff),
										_16BIT_GETB(pvers->elems[pt0->v1_i].c_diff)));

	pt0->v0_i = (int)pvers->length - 2;
	pt0->v1_i = (int)pvers->length - 1;

	ptri->state = TRI_STATE_CULLED;
	return true;
	UNREFERENCED_PARAMETER(pnors);
}

static bool Clip_Triangle_ZPlane_Near2_Gouraud_Texture32(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	TRIANGLEV1 * pt0;
	if(!Append_Array(ptris, &pt0))
		return false;
	memcpy(pt0, ptri, sizeof(*pt0));

	if(pvers->elems[ptri->v0_i].z > pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v1_i;
		pt0->v1_i = ptri->v2_i;
		pt0->v2_i = ptri->v0_i;
	}
	else if(pvers->elems[ptri->v1_i].z > pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v2_i;
		pt0->v1_i = ptri->v0_i;
		pt0->v2_i = ptri->v1_i;
	}
	else
	{
		assert(pvers->elems[ptri->v2_i].z > pcam->min_clip_z);
		pt0->v0_i = ptri->v0_i;
		pt0->v1_i = ptri->v1_i;
		pt0->v2_i = ptri->v2_i;
	}

	VERTEXV1T * pv0;
	if(!Append_Array(pvers, &pv0))
		return false;
	memcpy(pv0, &pvers->elems[pt0->v0_i], sizeof(*pv0));

	pv0->z = pcam->min_clip_z;
	pv0->x = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].x,
								pvers->elems[pt0->v0_i].x);

	pv0->y = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].y,
								pvers->elems[pt0->v0_i].y);

	pv0->u = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].u,
								pvers->elems[pt0->v0_i].u);

	pv0->v = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v0_i].z,
								pvers->elems[pt0->v2_i].v,
								pvers->elems[pt0->v0_i].v);

	pv0->c_diff = _RGB32BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										_32BIT_GETR(pvers->elems[pt0->v2_i].c_diff),
										_32BIT_GETR(pvers->elems[pt0->v0_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										_32BIT_GETG(pvers->elems[pt0->v2_i].c_diff),
										_32BIT_GETG(pvers->elems[pt0->v0_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										_32BIT_GETB(pvers->elems[pt0->v2_i].c_diff),
										_32BIT_GETB(pvers->elems[pt0->v0_i].c_diff)));

	VERTEXV1T * pv1;
	if(!Append_Array(pvers, &pv1))
		return false;
	memcpy(pv1, &pvers->elems[pt0->v1_i], sizeof(*pv1));

	pv1->z = pcam->min_clip_z;
	pv1->x = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v2_i].x,
								pvers->elems[pt0->v1_i].x);

	pv1->y = LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v2_i].y,
								pvers->elems[pt0->v1_i].y);

	pv1->u = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v2_i].u,
								pvers->elems[pt0->v1_i].u);

	pv1->v = (FIXP16)LINE2D_INTERSECT(	pcam->min_clip_z,
								pvers->elems[pt0->v2_i].z,
								pvers->elems[pt0->v1_i].z,
								pvers->elems[pt0->v2_i].v,
								pvers->elems[pt0->v1_i].v);

	pv1->c_diff = _RGB32BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v1_i].z,
										_32BIT_GETR(pvers->elems[pt0->v2_i].c_diff),
										_32BIT_GETR(pvers->elems[pt0->v1_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v1_i].z,
										_32BIT_GETG(pvers->elems[pt0->v2_i].c_diff),
										_32BIT_GETG(pvers->elems[pt0->v1_i].c_diff)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v1_i].z,
										_32BIT_GETB(pvers->elems[pt0->v2_i].c_diff),
										_32BIT_GETB(pvers->elems[pt0->v1_i].c_diff)));

	pt0->v0_i = (int)pvers->length - 2;
	pt0->v1_i = (int)pvers->length - 1;

	ptri->state = TRI_STATE_CULLED;
	return true;
	UNREFERENCED_PARAMETER(pnors);
}

static bool Clip_Triangle_ZPlane_Gouraud_Texture16(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	int clip_count_max = 0;
	int clip_count_min = 0;

	if(pvers->elems[ptri->v0_i].z > pcam->max_clip_z)
		clip_count_max++;
	else if(pvers->elems[ptri->v0_i].z < pcam->min_clip_z)
		clip_count_min++;

	if(pvers->elems[ptri->v1_i].z > pcam->max_clip_z)
		clip_count_max++;
	else if(pvers->elems[ptri->v1_i].z < pcam->min_clip_z)
		clip_count_min++;

	if(pvers->elems[ptri->v2_i].z > pcam->max_clip_z)
		clip_count_max++;
	else if(pvers->elems[ptri->v2_i].z < pcam->min_clip_z)
		clip_count_min++;

	if(clip_count_max >= 3 || clip_count_min >= 3)
	{
		ptri->state = TRI_STATE_CULLED;
		return true;
	}

	switch(clip_count_min)
	{
	case 1:
		if(!Clip_Triangle_ZPlane_Near1_Gouraud_Texture16(ptri, pvers, pnors, pcam, ptris))
			return false;
		break;

	case 2:
		if(!Clip_Triangle_ZPlane_Near2_Gouraud_Texture16(ptri, pvers, pnors, pcam, ptris))
			return false;
		break;
	}
	return true;
}

static bool Clip_Triangle_ZPlane_Gouraud_Texture32(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	int clip_count_max = 0;
	int clip_count_min = 0;

	if(pvers->elems[ptri->v0_i].z > pcam->max_clip_z)
		clip_count_max++;
	else if(pvers->elems[ptri->v0_i].z < pcam->min_clip_z)
		clip_count_min++;

	if(pvers->elems[ptri->v1_i].z > pcam->max_clip_z)
		clip_count_max++;
	else if(pvers->elems[ptri->v1_i].z < pcam->min_clip_z)
		clip_count_min++;

	if(pvers->elems[ptri->v2_i].z > pcam->max_clip_z)
		clip_count_max++;
	else if(pvers->elems[ptri->v2_i].z < pcam->min_clip_z)
		clip_count_min++;

	if(clip_count_max >= 3 || clip_count_min >= 3)
	{
		ptri->state = TRI_STATE_CULLED;
		return true;
	}

	switch(clip_count_min)
	{
	case 1:
		if(!Clip_Triangle_ZPlane_Near1_Gouraud_Texture32(ptri, pvers, pnors, pcam, ptris))
			return false;
		break;

	case 2:
		if(!Clip_Triangle_ZPlane_Near2_Gouraud_Texture32(ptri, pvers, pnors, pcam, ptris))
			return false;
		break;
	}
	return true;
}

_CTOR_IMPLEMENT(MATERIALV1_TYP);
_DTOR_IMPLEMENT_W1(MATERIALV1_TYP, Destroy_Material, texture.pbuffer);

_CTOR_IMPLEMENT(OBJECT4DV1_TYP);
_DTOR_IMPLEMENT_W1(OBJECT4DV1_TYP, Destroy_Object4D, tri_list.elems);

T3DLIB_API bool (* Create_Material_From_MsModel)(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name) = NULL;
T3DLIB_API bool (* Clip_Object4D_Gouraud_Texture)(OBJECT4DV1 * pobj, CAM4DV1 * pcam) = NULL;
T3DLIB_API void (* Draw_Object4D_Wire)(OBJECT4DV1 * pobj, CAM4DV1 * pcam) = NULL;
T3DLIB_API void (* Draw_Object4D_Wire_ZBufferRW)(OBJECT4DV1 * pobj, CAM4DV1 * pcam) = NULL;
T3DLIB_API void (* Draw_Object4D)(OBJECT4DV1 * pobj, CAM4DV1 * pcam) = NULL;
T3DLIB_API void (* Draw_Object4D_Gouraud_Texture_ZBufferRW)(OBJECT4DV1 * pobj, CAM4DV1 * pcam, MATERIALV1 * pmaterial) = NULL;

T3DLIB_API bool Init_T3dlib6(int bpp)
{
	switch(bpp)
	{
	case 16:
		Create_Material_From_MsModel	= Create_Material_From_MsModel16;
		Clip_Object4D_Gouraud_Texture	= Clip_Object4D_Gouraud_Texture16;
		Draw_Object4D_Wire				= Draw_Object4D_Wire16;
		Draw_Object4D_Wire_ZBufferRW	= Draw_Object4D_Wire_ZBufferRW16;
		Draw_Object4D					= Draw_Object4D16;
		Draw_Object4D_Gouraud_Texture_ZBufferRW	= Draw_Object4D_Gouraud_Texture_ZBufferRW16;
		break;

	case 32:
		Create_Material_From_MsModel	= Create_Material_From_MsModel32;
		Clip_Object4D_Gouraud_Texture	= Clip_Object4D_Gouraud_Texture32;
		Draw_Object4D_Wire				= Draw_Object4D_Wire32;
		Draw_Object4D_Wire_ZBufferRW	= Draw_Object4D_Wire_ZBufferRW32;
		Draw_Object4D					= Draw_Object4D32;
		Draw_Object4D_Gouraud_Texture_ZBufferRW	= Draw_Object4D_Gouraud_Texture_ZBufferRW32;
		break;

	default:
		ON_ERROR_GOTO(SFORMAT1(gbuffer, "unsupported color bpp: %d", bpp));
	}
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API MATRIX4X4 * Build_Mat_RotationXYZ(MATRIX4X4 * pmres, const VECTOR4D * pv0)
{
	MATRIX4X4 mx, my, mz, mtmp;
	int rot_seq = 0;

	if(!IS_ZERO_FLOAT(pv0->x))
	{
		MATRIX4X4_Init3X3(	&mx,
							1,				0,				0,
							0,				cos(pv0->x),	sin(pv0->x),
							0,				-sin(pv0->x),	cos(pv0->x));
		rot_seq |= 0x01;
	}

	if(!IS_ZERO_FLOAT(pv0->y))
	{
		MATRIX4X4_Init3X3(	&my,
							cos(pv0->y),	0,				-sin(pv0->y),
							0,				1,				0,
							sin(pv0->y),	0,				cos(pv0->y));
		rot_seq |= 0x02;
	}

	if(!IS_ZERO_FLOAT(pv0->z))
	{
		MATRIX4X4_Init3X3(	&mz,
							cos(pv0->z),	sin(pv0->z),	0,
							-sin(pv0->z),	cos(pv0->z),	0,
							0,				0,				1);
		rot_seq |= 0x04;
	}

	switch(rot_seq)
	{
	case 1: // seq: x
		MATRIX4X4_Copy(pmres, &mx);
		break;

	case 2: // seq: y
		MATRIX4X4_Copy(pmres, &my);
		break;

	case 3: // seq: x, y
		Mat_Mul_4X4(pmres, &mx, &my);
		break;

	case 4: // seq: z
		MATRIX4X4_Copy(pmres, &mz);
		break;

	case 5: // seq: x, z
		Mat_Mul_4X4(pmres, &mx, &mz);
		break;

	case 6: // seq: y, z
		Mat_Mul_4X4(pmres, &my, &mz);
		break;

	case 7: // seq: x, y, z
		Mat_Mul_4X4(pmres, Mat_Mul_4X4(&mtmp, &mx, &my), &mz);
		break;

	default:
		MATRIX4X4_Copy(pmres, &MATRIX4X4::IDENTITY);
		break;
	}
	return pmres;
}

T3DLIB_API CAM4DV1 * CAM4DV1_Init(	CAM4DV1 *			pcam,
									CAM4DV1_MODE		mode,
									REAL				fov,
									REAL				min_clip_z,
									REAL				max_clip_z,
									SURFACEV1 *			psurf,
									ZBUFFERV1 *			pzbuf,
									VIEWPORT_FIX_MODE	fix_mode /*= VIEWPORT_FIX_MODE_HEIGHT*/)
{
	//INIT_ZERO(*pcam);
	pcam->mode				= mode;
	pcam->fov				= fov;
	pcam->min_clip_z		= min_clip_z;
	pcam->max_clip_z		= max_clip_z;
	pcam->viewport.x		= 0;
	pcam->viewport.y		= 0;
	pcam->viewport.width	= (REAL)psurf->width;
	pcam->viewport.height	= (REAL)psurf->height;

	switch(fix_mode)
	{
	case VIEWPORT_FIX_MODE_WIDTH:
		pcam->viewplane.width	= tan(fov / 2) * 2 * CAM4DV1_VIEWPLANE_DIST;
		pcam->viewplane.height	= pcam->viewport.height / pcam->viewport.width * pcam->viewplane.width;
		break;

	case VIEWPORT_FIX_MODE_HEIGHT:
		pcam->viewplane.height	= tan(fov / 2) * 2 * CAM4DV1_VIEWPLANE_DIST;
		pcam->viewplane.width	= pcam->viewport.width / pcam->viewport.height * pcam->viewplane.height;
		break;

	default:
		assert(0);
		break;
	}

	pcam->psurf				= psurf;
	pcam->pzbuf				= pzbuf;
	return pcam;
}

T3DLIB_API MATRIX4X4 * Build_Camera4D_Mat_Euler(MATRIX4X4 * pmres, CAM4DV1 * pcam, int rot_seq)
{
	MATRIX4X4 mx, my, mz, mmov, mrot, mtmp;
	MATRIX4X4_Init4X4(	&mmov,
						1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						-pcam->vpos.x,			-pcam->vpos.y,			-pcam->vpos.z, 1);

	MATRIX4X4_Init3X3(	&mx,
						1,						0,						0,
						0,						 cos(-pcam->vrot.x),	sin(-pcam->vrot.x),
						0,						-sin(-pcam->vrot.x),	cos(-pcam->vrot.x));

	MATRIX4X4_Init3X3(	&my,
						cos(-pcam->vrot.y),		0,						-sin(-pcam->vrot.y),
						0,						1,						0,
						sin(-pcam->vrot.y),		0,						 cos(-pcam->vrot.y));

	MATRIX4X4_Init3X3(	&mz,
						 cos(-pcam->vrot.z),	sin(-pcam->vrot.z),		0,
						-sin(-pcam->vrot.z),	cos(-pcam->vrot.z),		0,
						0,						0,						1);

	switch(rot_seq)
	{
	case ROTATION_SEQ_XYZ:
		Mat_Mul_4X4(&mrot, Mat_Mul_4X4(&mtmp, &mz, &my), &mx);
		break;

	case ROTATION_SEQ_XZY:
		Mat_Mul_4X4(&mrot, Mat_Mul_4X4(&mtmp, &my, &mz), &mx);
		break;

	case ROTATION_SEQ_YXZ:
		Mat_Mul_4X4(&mrot, Mat_Mul_4X4(&mtmp, &mz, &mx), &my);
		break;

	case ROTATION_SEQ_YZX:
		Mat_Mul_4X4(&mrot, Mat_Mul_4X4(&mtmp, &mx, &mz), &my);
		break;

	case ROTATION_SEQ_ZXY:
		Mat_Mul_4X4(&mrot, Mat_Mul_4X4(&mtmp, &my, &mx), &mz);
		break;

	case ROTATION_SEQ_ZYX:
		Mat_Mul_4X4(&mrot, Mat_Mul_4X4(&mtmp, &mx, &my), &mz);
		break;

	default:
		assert(0);
		break;
	}

	return Mat_Mul_4X4(pmres, &mmov, &mrot);
}

T3DLIB_API MATRIX4X4 * Build_Camera4D_Mat_UVN(MATRIX4X4 * pmres, CAM4DV1 * pcam, int uvn_mode)
{
	assert(0);

	return NULL;
	UNREFERENCED_PARAMETER(pmres);
	UNREFERENCED_PARAMETER(pcam);
	UNREFERENCED_PARAMETER(uvn_mode);
}

T3DLIB_API bool Create_Material_From_MsModel16(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name)
{
	assert(pmaterial->texture.pbuffer == NULL);

	BITMAPV1 btmp;
	INIT_ZERO(btmp);
	int i;
	for(i = 0; i < pmodel->nNumMaterials; i++)
	{
		msMaterial * pmat = &pmodel->pMaterials[i];
		if(0 == strcmp(pmat->szName, material_name))
		{
			pmaterial->c_ambi = _RGB16BIT(	(int)(pmat->Ambient[0] * (MAX_COLOR_INTENSITY16 - 1)),
											(int)(pmat->Ambient[1] * (MAX_COLOR_INTENSITY16G - 1)),
											(int)(pmat->Ambient[2] * (MAX_COLOR_INTENSITY16 - 1)));

			pmaterial->c_diff = _RGB16BIT(	(int)(pmat->Diffuse[0] * (MAX_COLOR_INTENSITY16 - 1)),
											(int)(pmat->Diffuse[1] * (MAX_COLOR_INTENSITY16G - 1)),
											(int)(pmat->Diffuse[2] * (MAX_COLOR_INTENSITY16 - 1)));

			pmaterial->c_spec = _RGB16BIT(	(int)(pmat->Specular[0] * (MAX_COLOR_INTENSITY16 - 1)),
											(int)(pmat->Specular[1] * (MAX_COLOR_INTENSITY16G - 1)),
											(int)(pmat->Specular[2] * (MAX_COLOR_INTENSITY16 - 1)));

			pmaterial->c_emis = _RGB16BIT(	(int)(pmat->Emissive[0] * (MAX_COLOR_INTENSITY16 - 1)),
											(int)(pmat->Emissive[1] * (MAX_COLOR_INTENSITY16G - 1)),
											(int)(pmat->Emissive[2] * (MAX_COLOR_INTENSITY16 - 1)));

			if(0 != strcmp(pmat->szDiffuseTexture, ""))
			{
				if(!Create_Bitmap_From_File(&btmp, pmat->szDiffuseTexture))
					ON_ERROR_GOTO(SFORMAT1(gbuffer, "load bitmap %s failed", pmat->szDiffuseTexture));

				if(!Create_Image16(&pmaterial->texture,
						btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
					ON_ERROR_GOTO("create image failed");

				if(!Load_Image_From_Bitmap16(&pmaterial->texture, &btmp, 0, 0,
						btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
					ON_ERROR_GOTO("load image failed");

				Destroy_Bitmap(&btmp);
			}

			strcpy(pmaterial->name, pmat->szName);

			return true;
		}
	}
	ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot find material %s", material_name));

ON_ERROR:
	Destroy_Image(&pmaterial->texture);
	Destroy_Bitmap(&btmp);
	return false;
}

T3DLIB_API bool Create_Material_From_MsModel32(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name)
{
	assert(pmaterial->texture.pbuffer == NULL);

	BITMAPV1 btmp;
	INIT_ZERO(btmp);
	int i;
	for(i = 0; i < pmodel->nNumMaterials; i++)
	{
		msMaterial * pmat = &pmodel->pMaterials[i];
		if(0 == strcmp(pmat->szName, material_name))
		{
			pmaterial->c_ambi = _RGB32BIT(	(int)(pmat->Ambient[0] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Ambient[1] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Ambient[2] * (MAX_COLOR_INTENSITY32 - 1)));

			pmaterial->c_diff = _RGB32BIT(	(int)(pmat->Diffuse[0] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Diffuse[1] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Diffuse[2] * (MAX_COLOR_INTENSITY32 - 1)));

			pmaterial->c_spec = _RGB32BIT(	(int)(pmat->Specular[0] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Specular[1] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Specular[2] * (MAX_COLOR_INTENSITY32 - 1)));

			pmaterial->c_emis = _RGB32BIT(	(int)(pmat->Emissive[0] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Emissive[1] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Emissive[2] * (MAX_COLOR_INTENSITY32 - 1)));

			if(0 != strcmp(pmat->szDiffuseTexture, ""))
			{
				if(!Create_Bitmap_From_File(&btmp, pmat->szDiffuseTexture))
					ON_ERROR_GOTO(SFORMAT1(gbuffer, "load bitmap %s failed", pmat->szDiffuseTexture));

				if(!Create_Image32(&pmaterial->texture,
						btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
					ON_ERROR_GOTO("create image failed");

				if(!Load_Image_From_Bitmap32(&pmaterial->texture, &btmp, 0, 0,
						btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
					ON_ERROR_GOTO("load image failed");

				Destroy_Bitmap(&btmp);
			}

			strcpy(pmaterial->name, pmat->szName);

			return true;
		}
	}
	ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot find material %s", material_name));

ON_ERROR:
	Destroy_Image(&pmaterial->texture);
	Destroy_Bitmap(&btmp);
	return false;
}

T3DLIB_API void Destroy_Material(MATERIALV1 * pmaterial)
{
	Destroy_Image(&pmaterial->texture);
	INIT_ZERO(*pmaterial);
}

T3DLIB_API bool Create_Object4D_From_MsModel(OBJECT4DV1 * pobj, msModel * pmodel, const char * mesh_name,
											 size_t max_tri_size /*= 1000*/,
											 size_t max_ver_size /*= 3000*/,
											 size_t max_nor_size /*= 3000*/)
{
	assert(pobj->tri_list.elems == NULL);
	assert(pobj->ver_list.elems == NULL);
	assert(pobj->ver_list_t.elems == NULL);
	assert(pobj->nor_list.elems == NULL);
	assert(pobj->nor_list_t.elems == NULL);

	int i, j;
	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		msMesh * pmesh = &pmodel->pMeshes[i];
		if(0 == strcmp(pmesh->szName, mesh_name))
		{
			if(!Create_Array(&pobj->tri_list, max_tri_size))
				ON_ERROR_GOTO("create triangle list failed");

			for(j = 0; j < pmesh->nNumTriangles; j++)
			{
				TRIANGLEV1 * ptri;
				if(!Append_Array(&pobj->tri_list, &ptri))
					ON_ERROR_GOTO("append triangle list failed");

				ptri->v0_i = pmesh->pTriangles[j].nVertexIndices[0];
				ptri->v1_i = pmesh->pTriangles[j].nVertexIndices[1];
				ptri->v2_i = pmesh->pTriangles[j].nVertexIndices[2];

				ptri->n0_i = pmesh->pTriangles[j].nNormalIndices[0];
				ptri->n1_i = pmesh->pTriangles[j].nNormalIndices[1];
				ptri->n2_i = pmesh->pTriangles[j].nNormalIndices[2];

				ptri->state = TRI_STATE_ACTIVE;
			}

			if(!Create_Array(&pobj->ver_list, max_ver_size))
				ON_ERROR_GOTO("create vertex list failed");

			for(j = 0; j < pmesh->nNumVertices; j++)
			{
				VERTEXV1T * pver;
				if(!Append_Array(&pobj->ver_list, &pver))
					ON_ERROR_GOTO("append vertex list failed");
				memset(pver, 0, sizeof(*pver));

				VECTOR4D_InitXYZ(	&pver->_4D,
									(REAL)pmesh->pVertices[j].Vertex[0],
									(REAL)pmesh->pVertices[j].Vertex[1],
									(REAL)pmesh->pVertices[j].Vertex[2]);

				//pver->u = (FIXP16)(pmesh->pVertices[j].u * FIXP16_MAG);
				//pver->v = (FIXP16)(pmesh->pVertices[j].v * FIXP16_MAG);
					// !!! note : the u, v should be absolutely coordinate with texture's width and height
			}

			if(!Create_Array(&pobj->ver_list_t, max_ver_size))
				ON_ERROR_GOTO("create vertex_t list failed");

			if(!Create_Array(&pobj->nor_list, max_nor_size))
				ON_ERROR_GOTO("create normal list failed");

			for(j = 0; j < pmesh->nNumNormals; j++)
			{
				VECTOR4D * pnor;
				if(!Append_Array(&pobj->nor_list, &pnor))
					ON_ERROR_GOTO("append normal list failed");

				VECTOR4D_InitXYZ(	pnor,
									(REAL)pmesh->pNormals[j][0],
									(REAL)pmesh->pNormals[j][1],
									(REAL)pmesh->pNormals[j][2]);
			}

			if(!Create_Array(&pobj->nor_list_t, max_nor_size))
				ON_ERROR_GOTO("create normal_t list failed");

			pobj->tri_orig_num = pobj->tri_list.length;

			if(pmesh->nMaterialIndex >= 0)
			{
				assert(pmesh->nMaterialIndex < pmodel->nNumMeshes);
				strcpy(pobj->material_name, pmodel->pMaterials[pmesh->nMaterialIndex].szName);
			}

			strcpy(pobj->name, pmesh->szName);

			return true;
		}
	}
	ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot find mesh %s", mesh_name));

ON_ERROR:
	Destroy_Array(&pobj->tri_list);
	Destroy_Array(&pobj->ver_list);
	Destroy_Array(&pobj->ver_list_t);
	Destroy_Array(&pobj->nor_list);
	Destroy_Array(&pobj->nor_list_t);
	return false;
}

T3DLIB_API void Undate_Object4D_Absolute_UV(OBJECT4DV1 * pobj, msModel * pmode, MATERIALV1 * pmaterial)
{
	assert(pmaterial->texture.pbuffer != NULL);

	int i, j;
	for(i = 0; i < pmode->nNumMeshes; i++)
	{
		msMesh * pmesh = &pmode->pMeshes[i];
		if(0 == strcmp(pmesh->szName, pobj->name))
		{
			assert((int)pobj->ver_list.length == pmesh->nNumVertices);

			for(j = 0; j < (int)pobj->ver_list.length; j++)
			{
				VERTEXV1T * pver = &pobj->ver_list.elems[j];

				pver->u = (FIXP16)(pmesh->pVertices[j].u * FIXP16_MAG * (pmaterial->texture.width - 1));
				pver->v = (FIXP16)(pmesh->pVertices[j].v * FIXP16_MAG * (pmaterial->texture.height - 1));
			}
		}
	}
}

T3DLIB_API void Reset_Object4D(OBJECT4DV1 * pobj)
{
	int i;
	pobj->tri_list.length = pobj->tri_orig_num;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
		pobj->tri_list.elems[i].state = TRI_STATE_ACTIVE;
	Clear_Array(&pobj->ver_list_t);
	Clear_Array(&pobj->nor_list_t);
}

T3DLIB_API void Destroy_Object4D(OBJECT4DV1 * pobj)
{
	Destroy_Array(&pobj->tri_list);
	Destroy_Array(&pobj->ver_list);
	Destroy_Array(&pobj->ver_list_t);
	Destroy_Array(&pobj->nor_list);
	Destroy_Array(&pobj->nor_list_t);
	INIT_ZERO(*pobj);
}

T3DLIB_API void Model_To_World_Object4D(OBJECT4DV1 * pobj)
{
	assert(pobj->ver_list_t.size >= pobj->ver_list.size);
	assert(pobj->ver_list_t.length == 0);

	int i;
	if(IS_ZERO_FLOAT(pobj->vrot.x)
		&& IS_ZERO_FLOAT(pobj->vrot.y)
		&& IS_ZERO_FLOAT(pobj->vrot.z))
	{
		pobj->ver_list_t.length = pobj->ver_list.length;
		for(i = 0; i < (int)pobj->ver_list.length; i++)
		{
			memcpy(&pobj->ver_list_t.elems[i], &pobj->ver_list.elems[i], sizeof(*pobj->ver_list.elems));
			VECTOR3D_Add(	&pobj->ver_list_t.elems[i]._3D,
							&pobj->vpos._3D);
		}
	}
	else
	{
		MATRIX4X4 mrot;
		Build_Mat_RotationXYZ(&mrot, &pobj->vrot);
		mrot.m30 = pobj->vpos.x;
		mrot.m31 = pobj->vpos.y;
		mrot.m32 = pobj->vpos.z;

		pobj->ver_list_t.length = pobj->ver_list.length;
		for(i = 0; i < (int)pobj->ver_list.length; i++)
		{
			memcpy(&pobj->ver_list_t.elems[i], &pobj->ver_list.elems[i], sizeof(*pobj->ver_list.elems));
			Mat_Mul_VECTOR4D_4X4(	&pobj->ver_list_t.elems[i]._4D,
									&pobj->ver_list.elems[i]._4D,
									&mrot);
		}
	}
}

T3DLIB_API void World_To_Camera_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pobj->ver_list_t.length; i++)
	{
		VECTOR4D vtmp;
		Mat_Mul_VECTOR4D_4X4(	&pobj->ver_list_t.elems[i]._4D,
								VECTOR4D_Copy(&vtmp, &pobj->ver_list_t.elems[i]._4D),
								&pcam->mcam);
	}
}
//
//T3DLIB_API bool Clip_Triangle_From_Camera(TRI_ARRAYV1 * ptris, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam)
//{
//	return false;
//	UNREFERENCED_PARAMETER(ptris);
//	UNREFERENCED_PARAMETER(pvers);
//	UNREFERENCED_PARAMETER(pnors);
//	UNREFERENCED_PARAMETER(pcam);
//}

T3DLIB_API bool Clip_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
		{
			Clip_Triangle_XPlane(&pobj->tri_list.elems[i], &pobj->ver_list_t, &pobj->nor_list_t, pcam);
		}
	}

	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
		{
			Clip_Triangle_YPlane(&pobj->tri_list.elems[i], &pobj->ver_list_t, &pobj->nor_list_t, pcam);
		}
	}

	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
		{
			if(!Clip_Triangle_ZPlane(
					&pobj->tri_list.elems[i], &pobj->ver_list_t, &pobj->nor_list_t, pcam, &pobj->tri_list))
				return false;
		}
	}
	return true;
}

T3DLIB_API bool Clip_Object4D_Gouraud_Texture16(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
		{
			Clip_Triangle_XPlane(&pobj->tri_list.elems[i], &pobj->ver_list_t, &pobj->nor_list_t, pcam);
		}
	}

	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
		{
			Clip_Triangle_YPlane(&pobj->tri_list.elems[i], &pobj->ver_list_t, &pobj->nor_list_t, pcam);
		}
	}

	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
		{
			if(!Clip_Triangle_ZPlane_Gouraud_Texture16(
					&pobj->tri_list.elems[i], &pobj->ver_list_t, &pobj->nor_list_t, pcam, &pobj->tri_list))
				return false;
		}
	}
	return true;
}

T3DLIB_API bool Clip_Object4D_Gouraud_Texture32(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
		{
			Clip_Triangle_XPlane(&pobj->tri_list.elems[i], &pobj->ver_list_t, &pobj->nor_list_t, pcam);
		}
	}

	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
		{
			Clip_Triangle_YPlane(&pobj->tri_list.elems[i], &pobj->ver_list_t, &pobj->nor_list_t, pcam);
		}
	}

	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
		{
			if(!Clip_Triangle_ZPlane_Gouraud_Texture32(
					&pobj->tri_list.elems[i], &pobj->ver_list_t, &pobj->nor_list_t, pcam, &pobj->tri_list))
				return false;
		}
	}
	return true;
}

T3DLIB_API void Camera_To_Perspective_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pobj->ver_list_t.length; i++)
	{
		REAL z_inv = CAM4DV1_VIEWPLANE_DIST / pobj->ver_list_t.elems[i].z;
		pobj->ver_list_t.elems[i].x *= z_inv;
		pobj->ver_list_t.elems[i].y *= z_inv;
	}
	UNREFERENCED_PARAMETER(pcam);
}

T3DLIB_API void Perspective_To_Screen_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	REAL aw_inv = (REAL)0.5 * pcam->viewplane.width;
	REAL ah_inv = (REAL)0.5 * pcam->viewplane.height;
	REAL ow_inv = (pcam->viewport.width - 1) / pcam->viewplane.width;
	REAL oh_inv = (pcam->viewport.height - 1) / pcam->viewplane.height;

	int i;
	for(i = 0; i < (int)pobj->ver_list_t.length; i++)
	{
		pobj->ver_list_t.elems[i].x = (aw_inv + pobj->ver_list_t.elems[i].x) * ow_inv;
		pobj->ver_list_t.elems[i].y = (ah_inv - pobj->ver_list_t.elems[i].y) * oh_inv;
	}
}

T3DLIB_API void Draw_Object4D_Wire16(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	assert(pcam->psurf != NULL);
	assert(pcam->psurf->color_shift == _16BIT_BYTES_SHIFT);

	RENDERCONTEXTV1 rc;
	INIT_ZERO(rc);

	rc.s_pbuffer = pcam->psurf->pbuffer + pcam->viewport.x + (pcam->viewport.y << pcam->psurf->pitch_shift);
	rc.s_pitch = pcam->psurf->pitch;
	rc.s_pitch_shift = pcam->psurf->pitch_shift;
	rc.s_color_shift = pcam->psurf->color_shift;

	rc.fmin_clip_x = 0;
	rc.fmin_clip_y = 0;
	rc.fmax_clip_x = pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.height - 1;

	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
unsigned int c0, c1, c2;
		switch(pobj->tri_list.elems[i].state)
		{
		case TRI_STATE_ACTIVE:
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y < rc.fmax_clip_y + 1);

			Draw_Line16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Line16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Line16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
			break;

		case TRI_STATE_CLIPPED:
c0 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff;
c1 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff;
c2 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = Create_RGBI(255, 0, 0);
			Draw_Clipped_Line16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Clipped_Line16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Clipped_Line16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = c0;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = c1;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = c2;
			break;

		default:
			break;
		}
	}
}

T3DLIB_API void Draw_Object4D_Wire32(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	assert(pcam->psurf != NULL);
	assert(pcam->psurf->color_shift == _32BIT_BYTES_SHIFT);

	RENDERCONTEXTV1 rc;
	INIT_ZERO(rc);

	rc.s_pbuffer = pcam->psurf->pbuffer + pcam->viewport.x + (pcam->viewport.y << pcam->psurf->pitch_shift);
	rc.s_pitch = pcam->psurf->pitch;
	rc.s_pitch_shift = pcam->psurf->pitch_shift;
	rc.s_color_shift = pcam->psurf->color_shift;

	rc.fmin_clip_x = 0;
	rc.fmin_clip_y = 0;
	rc.fmax_clip_x = pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.height - 1;

	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
unsigned int c0, c1, c2;
		switch(pobj->tri_list.elems[i].state)
		{
		case TRI_STATE_ACTIVE:
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y < rc.fmax_clip_y + 1);

			Draw_Line32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Line32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Line32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
			break;

		case TRI_STATE_CLIPPED:
c0 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff;
c1 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff;
c2 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = Create_RGBI(255, 0, 0);
			Draw_Clipped_Line32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Clipped_Line32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Clipped_Line32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = c0;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = c1;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = c2;
			break;

		default:
			break;
		}
	}
}

T3DLIB_API void Draw_Object4D_Wire_ZBufferRW16(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	assert(pcam->psurf != NULL);
	assert(pcam->pzbuf != NULL);
	assert(pcam->psurf->color_shift == _16BIT_BYTES_SHIFT);

	RENDERCONTEXTV1 rc;
	INIT_ZERO(rc);

	rc.s_pbuffer = pcam->psurf->pbuffer + pcam->viewport.x + (pcam->viewport.y << pcam->psurf->pitch_shift);
	rc.s_pitch = pcam->psurf->pitch;
	rc.s_pitch_shift = pcam->psurf->pitch_shift;
	rc.s_color_shift = pcam->psurf->color_shift;

	rc.fmin_clip_x = 0;
	rc.fmin_clip_y = 0;
	rc.fmax_clip_x = pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.height - 1;

	rc.z_pbuffer = pcam->pzbuf->pbuffer;
	rc.z_pitch = pcam->pzbuf->pitch;
	rc.z_pitch_shift = pcam->pzbuf->pitch_shift;
	rc.z_color_shift = pcam->pzbuf->color_shift;

	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
unsigned int c0, c1, c2;
		switch(pobj->tri_list.elems[i].state)
		{
		case TRI_STATE_ACTIVE:
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y < rc.fmax_clip_y + 1);

			Draw_Line_ZbufferRW16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Line_ZbufferRW16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Line_ZbufferRW16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
			break;

		case TRI_STATE_CLIPPED:
c0 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff;
c1 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff;
c2 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = Create_RGBI(255, 0, 0);
			Draw_Clipped_Line_ZbufferRW16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Clipped_Line_ZbufferRW16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Clipped_Line_ZbufferRW16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = c0;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = c1;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = c2;
			break;

		default:
			break;
		}
	}
}

T3DLIB_API void Draw_Object4D_Wire_ZBufferRW32(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	assert(pcam->psurf != NULL);
	assert(pcam->pzbuf != NULL);
	assert(pcam->psurf->color_shift == _32BIT_BYTES_SHIFT);

	RENDERCONTEXTV1 rc;
	INIT_ZERO(rc);

	rc.s_pbuffer = pcam->psurf->pbuffer + pcam->viewport.x + (pcam->viewport.y << pcam->psurf->pitch_shift);
	rc.s_pitch = pcam->psurf->pitch;
	rc.s_pitch_shift = pcam->psurf->pitch_shift;
	rc.s_color_shift = pcam->psurf->color_shift;

	rc.fmin_clip_x = 0;
	rc.fmin_clip_y = 0;
	rc.fmax_clip_x = pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.height - 1;

	rc.z_pbuffer = pcam->pzbuf->pbuffer;
	rc.z_pitch = pcam->pzbuf->pitch;
	rc.z_pitch_shift = pcam->pzbuf->pitch_shift;
	rc.z_color_shift = pcam->pzbuf->color_shift;

	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
unsigned int c0, c1, c2;
		switch(pobj->tri_list.elems[i].state)
		{
		case TRI_STATE_ACTIVE:
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y < rc.fmax_clip_y + 1);

			Draw_Line_ZbufferRW32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Line_ZbufferRW32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Line_ZbufferRW32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
			break;

		case TRI_STATE_CLIPPED:
c0 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff;
c1 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff;
c2 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = Create_RGBI(255, 0, 0);
			Draw_Clipped_Line_ZbufferRW32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Clipped_Line_ZbufferRW32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Clipped_Line_ZbufferRW32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = c0;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = c1;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = c2;
			break;

		default:
			break;
		}
	}
}

T3DLIB_API void Draw_Object4D16(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	assert(pcam->psurf != NULL);
	assert(pcam->psurf->color_shift == _16BIT_BYTES_SHIFT);

	RENDERCONTEXTV1 rc;
	INIT_ZERO(rc);

	rc.s_pbuffer = pcam->psurf->pbuffer + pcam->viewport.x + (pcam->viewport.y << pcam->psurf->pitch_shift);
	rc.s_pitch = pcam->psurf->pitch;
	rc.s_pitch_shift = pcam->psurf->pitch_shift;
	rc.s_color_shift = pcam->psurf->color_shift;

	rc.fmin_clip_x = 0;
	rc.fmin_clip_y = 0;
	rc.fmax_clip_x = pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.height - 1;

	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
unsigned int c0, c1, c2;
		switch(pobj->tri_list.elems[i].state)
		{
		case TRI_STATE_ACTIVE:
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y < rc.fmax_clip_y + 1);

			Draw_Triangle16(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			break;

		case TRI_STATE_CLIPPED:
c0 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff;
c1 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff;
c2 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = Create_RGBI(255, 0, 0);
			Draw_Clipped_Triangle16(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = c0;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = c1;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = c2;
			break;

		default:
			break;
		}
	}
}

T3DLIB_API void Draw_Object4D32(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	assert(pcam->psurf != NULL);
	assert(pcam->psurf->color_shift == _32BIT_BYTES_SHIFT);

	RENDERCONTEXTV1 rc;
	INIT_ZERO(rc);

	rc.s_pbuffer = pcam->psurf->pbuffer + pcam->viewport.x + (pcam->viewport.y << pcam->psurf->pitch_shift);
	rc.s_pitch = pcam->psurf->pitch;
	rc.s_pitch_shift = pcam->psurf->pitch_shift;
	rc.s_color_shift = pcam->psurf->color_shift;

	rc.fmin_clip_x = 0;
	rc.fmin_clip_y = 0;
	rc.fmax_clip_x = pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.height - 1;

	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
unsigned int c0, c1, c2;
		switch(pobj->tri_list.elems[i].state)
		{
		case TRI_STATE_ACTIVE:
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y < rc.fmax_clip_y + 1);

			Draw_Triangle32(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			break;

		case TRI_STATE_CLIPPED:
c0 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff;
c1 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff;
c2 = pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = Create_RGBI(255, 0, 0);
			Draw_Clipped_Triangle32(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = c0;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = c1;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = c2;
			break;

		default:
			break;
		}
	}
}

T3DLIB_API void Draw_Object4D_Gouraud_Texture_ZBufferRW16(OBJECT4DV1 * pobj, CAM4DV1 * pcam, MATERIALV1 * pmaterial)
{
	assert(pcam->psurf != NULL);
	assert(pcam->pzbuf != NULL);
	assert(pcam->psurf->color_shift == _16BIT_BYTES_SHIFT);

	RENDERCONTEXTV1 rc;
	INIT_ZERO(rc);

	rc.s_pbuffer = pcam->psurf->pbuffer + pcam->viewport.x + (pcam->viewport.y << pcam->psurf->pitch_shift);
	rc.s_pitch = pcam->psurf->pitch;
	rc.s_pitch_shift = pcam->psurf->pitch_shift;
	rc.s_color_shift = pcam->psurf->color_shift;

	rc.fmin_clip_x = 0;
	rc.fmin_clip_y = 0;
	rc.fmax_clip_x = pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.height - 1;

	rc.t_pbuffer = pmaterial->texture.pbuffer;
	rc.t_pitch = pmaterial->texture.pitch;
	rc.t_pitch_shift = pmaterial->texture.pitch_shift;
	rc.t_color_shift = pmaterial->texture.color_shift;

	rc.z_pbuffer = pcam->pzbuf->pbuffer;
	rc.z_pitch = pcam->pzbuf->pitch;
	rc.z_pitch_shift = pcam->pzbuf->pitch_shift;
	rc.z_color_shift = pcam->pzbuf->color_shift;

	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		switch(pobj->tri_list.elems[i].state)
		{
		case TRI_STATE_ACTIVE:
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y < rc.fmax_clip_y + 1);

			Draw_Triangle_Gouraud_Texture_ZBufferRW16(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i],
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i],
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]);
			break;

		case TRI_STATE_CLIPPED:
			Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW16(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i],
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i],
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]);
			break;

		default:
			break;
		}
	}
}

T3DLIB_API void Draw_Object4D_Gouraud_Texture_ZBufferRW32(OBJECT4DV1 * pobj, CAM4DV1 * pcam, MATERIALV1 * pmaterial)
{
	assert(pcam->psurf != NULL);
	assert(pcam->pzbuf != NULL);
	assert(pcam->psurf->color_shift == _32BIT_BYTES_SHIFT);

	RENDERCONTEXTV1 rc;
	INIT_ZERO(rc);

	rc.s_pbuffer = pcam->psurf->pbuffer + pcam->viewport.x + (pcam->viewport.y << pcam->psurf->pitch_shift);
	rc.s_pitch = pcam->psurf->pitch;
	rc.s_pitch_shift = pcam->psurf->pitch_shift;
	rc.s_color_shift = pcam->psurf->color_shift;

	rc.fmin_clip_x = 0;
	rc.fmin_clip_y = 0;
	rc.fmax_clip_x = pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.height - 1;

	rc.t_pbuffer = pmaterial->texture.pbuffer;
	rc.t_pitch = pmaterial->texture.pitch;
	rc.t_pitch_shift = pmaterial->texture.pitch_shift;
	rc.t_color_shift = pmaterial->texture.color_shift;

	rc.z_pbuffer = pcam->pzbuf->pbuffer;
	rc.z_pitch = pcam->pzbuf->pitch;
	rc.z_pitch_shift = pcam->pzbuf->pitch_shift;
	rc.z_color_shift = pcam->pzbuf->color_shift;

	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		switch(pobj->tri_list.elems[i].state)
		{
		case TRI_STATE_ACTIVE:
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].y < rc.fmax_clip_y + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x >= rc.fmin_clip_x && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].x < rc.fmax_clip_x + 1);
			assert(pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y >= rc.fmin_clip_y && pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].y < rc.fmax_clip_y + 1);

			Draw_Triangle_Gouraud_Texture_ZBufferRW32(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i],
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i],
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]);
			break;

		case TRI_STATE_CLIPPED:
			Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW32(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i],
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i],
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]);
			break;

		default:
			break;
		}
	}
}
