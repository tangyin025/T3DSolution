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
	int clip_count_min = 0;
	int clip_count_max = 0;
	REAL ftmp;

	ftmp = pvers->elems[ptri->v0_i].z * (REAL)0.5 * pcam->viewplane.width / CAM4DV1_VIEWPLANE_DIST;
	if(pvers->elems[ptri->v0_i].x <= -ftmp)
		clip_count_min++;
	else if(pvers->elems[ptri->v0_i].x >= ftmp)
		clip_count_max++;

	ftmp = pvers->elems[ptri->v1_i].z * (REAL)0.5 * pcam->viewplane.width / CAM4DV1_VIEWPLANE_DIST;
	if(pvers->elems[ptri->v1_i].x <= -ftmp)
		clip_count_min++;
	else if(pvers->elems[ptri->v1_i].x >= ftmp)
		clip_count_max++;

	ftmp = pvers->elems[ptri->v2_i].z * (REAL)0.5 * pcam->viewplane.width / CAM4DV1_VIEWPLANE_DIST;
	if(pvers->elems[ptri->v2_i].x <= -ftmp)
		clip_count_min++;
	else if(pvers->elems[ptri->v2_i].x >= ftmp)
		clip_count_max++;

	if(clip_count_min > 0 || clip_count_max > 0)
	{
		if(clip_count_min >= 3 || clip_count_max >= 3)
		{
			ptri->state = TRI_STATE_CULLED;
		}
		else
		{
			ptri->state = TRI_STATE_CLIPPED;
		}
	}

	UNREFERENCED_PARAMETER(pnors);
}

static void Clip_Triangle_YPlane(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam)
{
	int clip_count_min = 0;
	int clip_count_max = 0;
	REAL ftmp;

	ftmp = pvers->elems[ptri->v0_i].z * (REAL)0.5 * pcam->viewplane.height / CAM4DV1_VIEWPLANE_DIST;
	if(pvers->elems[ptri->v0_i].y <= -ftmp)
		clip_count_min++;
	else if(pvers->elems[ptri->v0_i].y >= ftmp)
		clip_count_max++;

	ftmp = pvers->elems[ptri->v1_i].z * (REAL)0.5 * pcam->viewplane.height / CAM4DV1_VIEWPLANE_DIST;
	if(pvers->elems[ptri->v1_i].y <= -ftmp)
		clip_count_min++;
	else if(pvers->elems[ptri->v1_i].y >= ftmp)
		clip_count_max++;

	ftmp = pvers->elems[ptri->v2_i].z * (REAL)0.5 * pcam->viewplane.height / CAM4DV1_VIEWPLANE_DIST;
	if(pvers->elems[ptri->v2_i].y <= -ftmp)
		clip_count_min++;
	else if(pvers->elems[ptri->v2_i].y >= ftmp)
		clip_count_max++;

	if(clip_count_min > 0 || clip_count_max > 0)
	{
		if(clip_count_min >= 3 || clip_count_max >= 3)
		{
			ptri->state = TRI_STATE_CULLED;
		}
		else
		{
			ptri->state = TRI_STATE_CLIPPED;
		}
	}

	UNREFERENCED_PARAMETER(pnors);
}

static bool Clip_Triangle_ZPlane_Near1(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	size_t i = ptri - &ptris->elems[0];

	TRIANGLEV1 * pt0;
	if(!Append_Array(ptris, &pt0))
		return false;
	memcpy(pt0, ptri, sizeof(*pt0));

	ptri = &ptris->elems[i]; // !!!

	if(pvers->elems[ptri->v0_i].z < pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v0_i;
		pt0->v1_i = ptri->v1_i;
		pt0->v2_i = ptri->v2_i;

		pt0->c_diff0 = ptri->c_diff0;
		pt0->c_diff1 = ptri->c_diff1;
		pt0->c_diff2 = ptri->c_diff2;
	}
	else if(pvers->elems[ptri->v1_i].z < pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v1_i;
		pt0->v1_i = ptri->v2_i;
		pt0->v2_i = ptri->v0_i;

		pt0->c_diff0 = ptri->c_diff1;
		pt0->c_diff1 = ptri->c_diff2;
		pt0->c_diff2 = ptri->c_diff0;
	}
	else
	{
		assert(pvers->elems[ptri->v2_i].z < pcam->min_clip_z);
		pt0->v0_i = ptri->v2_i;
		pt0->v1_i = ptri->v0_i;
		pt0->v2_i = ptri->v1_i;

		pt0->c_diff0 = ptri->c_diff2;
		pt0->c_diff1 = ptri->c_diff0;
		pt0->c_diff2 = ptri->c_diff1;
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

	TRIANGLEV1 * pt1;
	if(!Append_Array(ptris, &pt1))
		return false;
	memcpy(pt1, ptri, sizeof(*pt1));

	pt0 = &ptris->elems[ptris->length - 2]; // !!!

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
	size_t i = ptri - &ptris->elems[0];

	TRIANGLEV1 * pt0;
	if(!Append_Array(ptris, &pt0))
		return false;
	memcpy(pt0, ptri, sizeof(*pt0));

	ptri = &ptris->elems[i]; // !!!

	if(pvers->elems[ptri->v0_i].z >= pcam->min_clip_z) // !!!
	{
		pt0->v0_i = ptri->v1_i;
		pt0->v1_i = ptri->v2_i;
		pt0->v2_i = ptri->v0_i;

		pt0->c_diff0 = ptri->c_diff1;
		pt0->c_diff1 = ptri->c_diff2;
		pt0->c_diff2 = ptri->c_diff0;
	}
	else if(pvers->elems[ptri->v1_i].z >= pcam->min_clip_z) // !!!
	{
		pt0->v0_i = ptri->v2_i;
		pt0->v1_i = ptri->v0_i;
		pt0->v2_i = ptri->v1_i;

		pt0->c_diff0 = ptri->c_diff2;
		pt0->c_diff1 = ptri->c_diff0;
		pt0->c_diff2 = ptri->c_diff1;
	}
	else
	{
		assert(pvers->elems[ptri->v2_i].z >= pcam->min_clip_z); // !!!
		pt0->v0_i = ptri->v0_i;
		pt0->v1_i = ptri->v1_i;
		pt0->v2_i = ptri->v2_i;

		pt0->c_diff0 = ptri->c_diff0;
		pt0->c_diff1 = ptri->c_diff1;
		pt0->c_diff2 = ptri->c_diff2;
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
	size_t i = ptri - &ptris->elems[0];

	TRIANGLEV1 * pt0;
	if(!Append_Array(ptris, &pt0))
		return false;
	memcpy(pt0, ptri, sizeof(*pt0));

	ptri = &ptris->elems[i]; // !!!

	if(pvers->elems[ptri->v0_i].z < pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v0_i;
		pt0->v1_i = ptri->v1_i;
		pt0->v2_i = ptri->v2_i;

		pt0->c_diff0 = ptri->c_diff0;
		pt0->c_diff1 = ptri->c_diff1;
		pt0->c_diff2 = ptri->c_diff2;
	}
	else if(pvers->elems[ptri->v1_i].z < pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v1_i;
		pt0->v1_i = ptri->v2_i;
		pt0->v2_i = ptri->v0_i;

		pt0->c_diff0 = ptri->c_diff1;
		pt0->c_diff1 = ptri->c_diff2;
		pt0->c_diff2 = ptri->c_diff0;
	}
	else
	{
		assert(pvers->elems[ptri->v2_i].z < pcam->min_clip_z);
		pt0->v0_i = ptri->v2_i;
		pt0->v1_i = ptri->v0_i;
		pt0->v2_i = ptri->v1_i;

		pt0->c_diff0 = ptri->c_diff2;
		pt0->c_diff1 = ptri->c_diff0;
		pt0->c_diff2 = ptri->c_diff1;
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

	unsigned int c_diff0 = _RGB16BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v1_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_16BIT_GETR(pt0->c_diff1),
										(REAL)_16BIT_GETR(pt0->c_diff0)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v1_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_16BIT_GETG(pt0->c_diff1),
										(REAL)_16BIT_GETG(pt0->c_diff0)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v1_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_16BIT_GETB(pt0->c_diff1),
										(REAL)_16BIT_GETB(pt0->c_diff0)));

	TRIANGLEV1 * pt1;
	if(!Append_Array(ptris, &pt1))
		return false;
	memcpy(pt1, ptri, sizeof(*pt1));

	pt0 = &ptris->elems[ptris->length - 2]; // !!!

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

	unsigned int c_diff1 = _RGB16BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_16BIT_GETR(pt0->c_diff2),
										(REAL)_16BIT_GETR(pt0->c_diff0)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_16BIT_GETG(pt0->c_diff2),
										(REAL)_16BIT_GETG(pt0->c_diff0)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_16BIT_GETB(pt0->c_diff2),
										(REAL)_16BIT_GETB(pt0->c_diff0)));

	pt0->v0_i = (int)pvers->length - 2;
	pt1->v0_i = (int)pvers->length - 2;
	pt1->v1_i = pt0->v2_i;
	pt1->v2_i = (int)pvers->length - 1;

	pt0->c_diff0 = c_diff0;
	pt1->c_diff0 = c_diff0;
	pt1->c_diff1 = pt0->c_diff2;
	pt1->c_diff2 = c_diff1;

	ptri->state = TRI_STATE_CULLED;
	return true;
	UNREFERENCED_PARAMETER(pnors);
}

static bool Clip_Triangle_ZPlane_Near1_Gouraud_Texture32(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	size_t i = ptri - &ptris->elems[0];

	TRIANGLEV1 * pt0;
	if(!Append_Array(ptris, &pt0))
		return false;
	memcpy(pt0, ptri, sizeof(*pt0));

	ptri = &ptris->elems[i]; // !!!

	if(pvers->elems[ptri->v0_i].z < pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v0_i;
		pt0->v1_i = ptri->v1_i;
		pt0->v2_i = ptri->v2_i;

		pt0->c_diff0 = ptri->c_diff0;
		pt0->c_diff1 = ptri->c_diff1;
		pt0->c_diff2 = ptri->c_diff2;
	}
	else if(pvers->elems[ptri->v1_i].z < pcam->min_clip_z)
	{
		pt0->v0_i = ptri->v1_i;
		pt0->v1_i = ptri->v2_i;
		pt0->v2_i = ptri->v0_i;

		pt0->c_diff0 = ptri->c_diff1;
		pt0->c_diff1 = ptri->c_diff2;
		pt0->c_diff2 = ptri->c_diff0;
	}
	else
	{
		assert(pvers->elems[ptri->v2_i].z < pcam->min_clip_z);
		pt0->v0_i = ptri->v2_i;
		pt0->v1_i = ptri->v0_i;
		pt0->v2_i = ptri->v1_i;

		pt0->c_diff0 = ptri->c_diff2;
		pt0->c_diff1 = ptri->c_diff0;
		pt0->c_diff2 = ptri->c_diff1;
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

	unsigned int c_diff0 = _RGB32BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v1_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_32BIT_GETR(pt0->c_diff1),
										(REAL)_32BIT_GETR(pt0->c_diff0)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v1_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_32BIT_GETG(pt0->c_diff1),
										(REAL)_32BIT_GETG(pt0->c_diff0)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v1_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_32BIT_GETB(pt0->c_diff1),
										(REAL)_32BIT_GETB(pt0->c_diff0)));

	TRIANGLEV1 * pt1;
	if(!Append_Array(ptris, &pt1))
		return false;
	memcpy(pt1, ptri, sizeof(*pt1));

	pt0 = &ptris->elems[ptris->length - 2]; // !!!

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

	unsigned int c_diff1 = _RGB32BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_32BIT_GETR(pt0->c_diff2),
										(REAL)_32BIT_GETR(pt0->c_diff0)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_32BIT_GETG(pt0->c_diff2),
										(REAL)_32BIT_GETG(pt0->c_diff0)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_32BIT_GETB(pt0->c_diff2),
										(REAL)_32BIT_GETB(pt0->c_diff0)));

	pt0->v0_i = (int)pvers->length - 2;
	pt1->v0_i = (int)pvers->length - 2;
	pt1->v1_i = pt0->v2_i;
	pt1->v2_i = (int)pvers->length - 1;

	pt0->c_diff0 = c_diff0;
	pt1->c_diff0 = c_diff0;
	pt1->c_diff1 = pt0->c_diff2;
	pt1->c_diff2 = c_diff1;

	ptri->state = TRI_STATE_CULLED;
	return true;
	UNREFERENCED_PARAMETER(pnors);
}

static bool Clip_Triangle_ZPlane_Near2_Gouraud_Texture16(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	size_t i = ptri - &ptris->elems[0];

	TRIANGLEV1 * pt0;
	if(!Append_Array(ptris, &pt0))
		return false;
	memcpy(pt0, ptri, sizeof(*pt0));

	ptri = &ptris->elems[i]; // !!!

	if(pvers->elems[ptri->v0_i].z >= pcam->min_clip_z) // !!!
	{
		pt0->v0_i = ptri->v1_i;
		pt0->v1_i = ptri->v2_i;
		pt0->v2_i = ptri->v0_i;

		pt0->c_diff0 = ptri->c_diff1;
		pt0->c_diff1 = ptri->c_diff2;
		pt0->c_diff2 = ptri->c_diff0;
	}
	else if(pvers->elems[ptri->v1_i].z >= pcam->min_clip_z) // !!!
	{
		pt0->v0_i = ptri->v2_i;
		pt0->v1_i = ptri->v0_i;
		pt0->v2_i = ptri->v1_i;

		pt0->c_diff0 = ptri->c_diff2;
		pt0->c_diff1 = ptri->c_diff0;
		pt0->c_diff2 = ptri->c_diff1;
	}
	else
	{
		assert(pvers->elems[ptri->v2_i].z >= pcam->min_clip_z); // !!!
		pt0->v0_i = ptri->v0_i;
		pt0->v1_i = ptri->v1_i;
		pt0->v2_i = ptri->v2_i;

		pt0->c_diff0 = ptri->c_diff0;
		pt0->c_diff1 = ptri->c_diff1;
		pt0->c_diff2 = ptri->c_diff2;
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

	unsigned int c_diff0 = _RGB16BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_16BIT_GETR(pt0->c_diff2),
										(REAL)_16BIT_GETR(pt0->c_diff0)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_16BIT_GETG(pt0->c_diff2),
										(REAL)_16BIT_GETG(pt0->c_diff0)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_16BIT_GETB(pt0->c_diff2),
										(REAL)_16BIT_GETB(pt0->c_diff0)));

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

	unsigned int c_diff1 = _RGB16BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v1_i].z,
										(REAL)_16BIT_GETR(pt0->c_diff2),
										(REAL)_16BIT_GETR(pt0->c_diff1)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v1_i].z,
										(REAL)_16BIT_GETG(pt0->c_diff2),
										(REAL)_16BIT_GETG(pt0->c_diff1)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v1_i].z,
										(REAL)_16BIT_GETB(pt0->c_diff2),
										(REAL)_16BIT_GETB(pt0->c_diff1)));

	pt0->v0_i = (int)pvers->length - 2;
	pt0->v1_i = (int)pvers->length - 1;

	pt0->c_diff0 = c_diff0;
	pt0->c_diff1 = c_diff1;

	ptri->state = TRI_STATE_CULLED;
	return true;
	UNREFERENCED_PARAMETER(pnors);
}

static bool Clip_Triangle_ZPlane_Near2_Gouraud_Texture32(TRIANGLEV1 * ptri, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam, TRI_ARRAYV1 * ptris)
{
	size_t i = ptri - &ptris->elems[0];

	TRIANGLEV1 * pt0;
	if(!Append_Array(ptris, &pt0))
		return false;
	memcpy(pt0, ptri, sizeof(*pt0));

	ptri = &ptris->elems[i]; // !!!

	if(pvers->elems[ptri->v0_i].z >= pcam->min_clip_z) // !!!
	{
		pt0->v0_i = ptri->v1_i;
		pt0->v1_i = ptri->v2_i;
		pt0->v2_i = ptri->v0_i;

		pt0->c_diff0 = ptri->c_diff1;
		pt0->c_diff1 = ptri->c_diff2;
		pt0->c_diff2 = ptri->c_diff0;
	}
	else if(pvers->elems[ptri->v1_i].z >= pcam->min_clip_z) // !!!
	{
		pt0->v0_i = ptri->v2_i;
		pt0->v1_i = ptri->v0_i;
		pt0->v2_i = ptri->v1_i;

		pt0->c_diff0 = ptri->c_diff2;
		pt0->c_diff1 = ptri->c_diff0;
		pt0->c_diff2 = ptri->c_diff1;
	}
	else
	{
		assert(pvers->elems[ptri->v2_i].z >= pcam->min_clip_z); // !!!
		pt0->v0_i = ptri->v0_i;
		pt0->v1_i = ptri->v1_i;
		pt0->v2_i = ptri->v2_i;

		pt0->c_diff0 = ptri->c_diff0;
		pt0->c_diff1 = ptri->c_diff1;
		pt0->c_diff2 = ptri->c_diff2;
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

	unsigned int c_diff0 = _RGB32BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_32BIT_GETR(pt0->c_diff2),
										(REAL)_32BIT_GETR(pt0->c_diff0)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_32BIT_GETG(pt0->c_diff2),
										(REAL)_32BIT_GETG(pt0->c_diff0)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v0_i].z,
										(REAL)_32BIT_GETB(pt0->c_diff2),
										(REAL)_32BIT_GETB(pt0->c_diff0)));

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

	unsigned int c_diff1 = _RGB32BIT(
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v1_i].z,
										(REAL)_32BIT_GETR(pt0->c_diff2),
										(REAL)_32BIT_GETR(pt0->c_diff1)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v1_i].z,
										(REAL)_32BIT_GETG(pt0->c_diff2),
										(REAL)_32BIT_GETG(pt0->c_diff1)),
					(unsigned int)LINE2D_INTERSECT(	pcam->min_clip_z,
										pvers->elems[pt0->v2_i].z,
										pvers->elems[pt0->v1_i].z,
										(REAL)_32BIT_GETB(pt0->c_diff2),
										(REAL)_32BIT_GETB(pt0->c_diff1)));

	pt0->v0_i = (int)pvers->length - 2;
	pt0->v1_i = (int)pvers->length - 1;

	pt0->c_diff0 = c_diff0;
	pt0->c_diff1 = c_diff1;

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

T3DLIB_API bool (* Create_Material_From_MsMaterial)(MATERIALV1 * pmaterial, msMaterial * pmsMaterial) = NULL;
T3DLIB_API bool (* Create_Material_From_MsModel_By_Name)(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name) = NULL;
T3DLIB_API bool (* Clip_Object4D_Gouraud_Texture)(OBJECT4DV1 * pobj, CAM4DV1 * pcam) = NULL;
T3DLIB_API void (* Draw_Object4D_Wire)(OBJECT4DV1 * pobj, CAM4DV1 * pcam) = NULL;
T3DLIB_API void (* Draw_Object4D_Wire_ZBufferRW)(OBJECT4DV1 * pobj, CAM4DV1 * pcam) = NULL;
T3DLIB_API void (* Draw_Object4D)(OBJECT4DV1 * pobj, CAM4DV1 * pcam) = NULL;
T3DLIB_API void (* Draw_Object4D_Gouraud_Texture_ZBufferRW)(OBJECT4DV1 * pobj, CAM4DV1 * pcam, MATERIALV1 * pmaterial) = NULL;
T3DLIB_API void (* Light_Object4D)(OBJECT4DV1 * pobj, LIGHT4DV1 * plight, MATERIALV1 * pmaterial) = NULL;

T3DLIB_API bool Init_T3dlib6(int bpp)
{
	switch(bpp)
	{
	case 16:
		Create_Material_From_MsMaterial	= Create_Material_From_MsMaterial16;
		Create_Material_From_MsModel_By_Name	= Create_Material_From_MsModel_By_Name16;
		Clip_Object4D_Gouraud_Texture	= Clip_Object4D_Gouraud_Texture16;
		Draw_Object4D_Wire				= Draw_Object4D_Wire16;
		Draw_Object4D_Wire_ZBufferRW	= Draw_Object4D_Wire_ZBufferRW16;
		Draw_Object4D					= Draw_Object4D16;
		Draw_Object4D_Gouraud_Texture_ZBufferRW	= Draw_Object4D_Gouraud_Texture_ZBufferRW16;
		Light_Object4D					= Light_Object4D16;
		break;

	case 32:
		Create_Material_From_MsMaterial	= Create_Material_From_MsMaterial32;
		Create_Material_From_MsModel_By_Name	= Create_Material_From_MsModel_By_Name32;
		Clip_Object4D_Gouraud_Texture	= Clip_Object4D_Gouraud_Texture32;
		Draw_Object4D_Wire				= Draw_Object4D_Wire32;
		Draw_Object4D_Wire_ZBufferRW	= Draw_Object4D_Wire_ZBufferRW32;
		Draw_Object4D					= Draw_Object4D32;
		Draw_Object4D_Gouraud_Texture_ZBufferRW	= Draw_Object4D_Gouraud_Texture_ZBufferRW32;
		Light_Object4D					= Light_Object4D32;
		break;

	default:
		ON_ERROR_GOTO(SFORMAT1(gbuffer, "unsupported color bpp: %d", bpp));
	}
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API MATRIX4X4 * Build_Mat_PositionXYZ(MATRIX4X4 * pmres, const VECTOR4D * vpos_ptr)
{
	MATRIX4X4_Init4X4(pmres,
					1,				0,				0,				0,
					0,				1,				0,				0,
					0,				0,				1,				0,
					vpos_ptr->x,	vpos_ptr->y,	vpos_ptr->z,	1);

	return pmres;
}

T3DLIB_API MATRIX4X4 * Build_Mat_RotationXYZ(MATRIX4X4 * pmres, const VECTOR4D * vrot_ptr)
{
	MATRIX4X4 mx, my, mz, mtmp;
	int rot_seq = 0;

	if(!IS_ZERO_FLOAT(vrot_ptr->x))
	{
		MATRIX4X4_Init3X3(	&mx,
							1,					0,					0,
							0,					cos(vrot_ptr->x),	sin(vrot_ptr->x),
							0,					-sin(vrot_ptr->x),	cos(vrot_ptr->x));
		rot_seq |= 0x01;
	}

	if(!IS_ZERO_FLOAT(vrot_ptr->y))
	{
		MATRIX4X4_Init3X3(	&my,
							cos(vrot_ptr->y),	0,					-sin(vrot_ptr->y),
							0,					1,					0,
							sin(vrot_ptr->y),	0,					cos(vrot_ptr->y));
		rot_seq |= 0x02;
	}

	if(!IS_ZERO_FLOAT(vrot_ptr->z))
	{
		MATRIX4X4_Init3X3(	&mz,
							cos(vrot_ptr->z),	sin(vrot_ptr->z),	0,
							-sin(vrot_ptr->z),	cos(vrot_ptr->z),	0,
							0,					0,					1);
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

T3DLIB_API CAM4DV1 * CAM4DV1_Init(	CAM4DV1 * pcam, REAL width, REAL height,
									REAL				viewport_x	/*= 0*/,
									REAL				viewport_y	/*= 0*/,
									REAL				min_clip_z	/*= 10*/,
									REAL				max_clip_z	/*= 1000*/,
									REAL				fov			/*= DEG_TO_RAD(90)*/,
									VIEWPORT_FIX_MODE	fix_mode	/*= VIEWPORT_FIX_MODE_HEIGHT*/,
									SURFACEV1 *			psurf		/*= NULL*/,
									ZBUFFERV1 *			pzbuf		/*= NULL*/)
{
	//INIT_ZERO(*pcam);
	pcam->mode				= CAM4DV1_MODE_UNKNOWN;
	pcam->fov				= fov;
	pcam->min_clip_z		= min_clip_z;
	pcam->max_clip_z		= max_clip_z;
	pcam->viewport.x		= floor(viewport_x);
	pcam->viewport.y		= floor(viewport_y);
	pcam->viewport.width	= floor(width);
	pcam->viewport.height	= floor(height);

	switch(fix_mode)
	{
	case VIEWPORT_FIX_MODE_WIDTH:
		pcam->viewplane.width	= tan(fov / 2) * 2 * CAM4DV1_VIEWPLANE_DIST;
		assert(pcam->viewplane.width > 0);
		pcam->viewplane.height	= pcam->viewport.height / pcam->viewport.width * pcam->viewplane.width;
		break;

	case VIEWPORT_FIX_MODE_HEIGHT:
		pcam->viewplane.height	= tan(fov / 2) * 2 * CAM4DV1_VIEWPLANE_DIST;
		assert(pcam->viewplane.height > 0);
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

T3DLIB_API MATRIX4X4 * Build_Camera4D_Mat_Euler(MATRIX4X4 * pmres, CAM4DV1 * pcam, int rot_seq /*= ROTATION_SEQ_ZXY*/)
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

T3DLIB_API bool Create_Material_From_MsMaterial16(MATERIALV1 * pmaterial, msMaterial * pmsMaterial)
{
	BITMAPV1 btmp;
	INIT_ZERO(btmp);

	pmaterial->c_ambi = _RGB16BIT(	(int)(pmsMaterial->Ambient[0] * (MAX_COLOR_INTENSITY16 - 1)),
									(int)(pmsMaterial->Ambient[1] * (MAX_COLOR_INTENSITY16G - 1)),
									(int)(pmsMaterial->Ambient[2] * (MAX_COLOR_INTENSITY16 - 1)));

	pmaterial->c_diff = _RGB16BIT(	(int)(pmsMaterial->Diffuse[0] * (MAX_COLOR_INTENSITY16 - 1)),
									(int)(pmsMaterial->Diffuse[1] * (MAX_COLOR_INTENSITY16G - 1)),
									(int)(pmsMaterial->Diffuse[2] * (MAX_COLOR_INTENSITY16 - 1)));

	pmaterial->c_spec = _RGB16BIT(	(int)(pmsMaterial->Specular[0] * (MAX_COLOR_INTENSITY16 - 1)),
									(int)(pmsMaterial->Specular[1] * (MAX_COLOR_INTENSITY16G - 1)),
									(int)(pmsMaterial->Specular[2] * (MAX_COLOR_INTENSITY16 - 1)));

	pmaterial->c_emis = _RGB16BIT(	(int)(pmsMaterial->Emissive[0] * (MAX_COLOR_INTENSITY16 - 1)),
									(int)(pmsMaterial->Emissive[1] * (MAX_COLOR_INTENSITY16G - 1)),
									(int)(pmsMaterial->Emissive[2] * (MAX_COLOR_INTENSITY16 - 1)));

	if(0 != strcmp(pmsMaterial->szDiffuseTexture, ""))
	{
		if(!Create_Bitmap_From_File(&btmp, pmsMaterial->szDiffuseTexture))
			ON_ERROR_GOTO(SFORMAT1(gbuffer, "load bitmap %s failed", pmsMaterial->szDiffuseTexture));

		if(!Create_Image16(&pmaterial->texture,
				btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
			ON_ERROR_GOTO("create image failed");

		if(!Load_Image_From_Bitmap16(&pmaterial->texture, &btmp, 0, 0,
				btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
			ON_ERROR_GOTO("load image failed");

		Destroy_Bitmap(&btmp);

		SET_BIT(pmaterial->attr, MATERIAL_ATTR_TEXTURE);
	}

	if(0 != pmaterial->c_ambi)
		SET_BIT(pmaterial->attr, MATERIAL_ATTR_AMBIENT);

	if(0 != pmaterial->c_diff)
		SET_BIT(pmaterial->attr, MATERIAL_ATTR_DIFFUSE);

	if(0 != pmaterial->c_spec)
		SET_BIT(pmaterial->attr, MATERIAL_ATTR_SPECULAR);

	if(0 != pmaterial->c_emis)
		SET_BIT(pmaterial->attr, MATERIAL_ATTR_EMISSIVE);

	strcpy(pmaterial->name, pmsMaterial->szName);
	return true;

ON_ERROR:
	Destroy_Bitmap(&btmp);
	Destroy_Material(pmaterial);
	return false;
}

T3DLIB_API bool Create_Material_From_MsMaterial32(MATERIALV1 * pmaterial, msMaterial * pmsMaterial)
{
	BITMAPV1 btmp;
	INIT_ZERO(btmp);

	pmaterial->c_ambi = _RGB32BIT(	(int)(pmsMaterial->Ambient[0] * (MAX_COLOR_INTENSITY32 - 1)),
									(int)(pmsMaterial->Ambient[1] * (MAX_COLOR_INTENSITY32 - 1)),
									(int)(pmsMaterial->Ambient[2] * (MAX_COLOR_INTENSITY32 - 1)));

	pmaterial->c_diff = _RGB32BIT(	(int)(pmsMaterial->Diffuse[0] * (MAX_COLOR_INTENSITY32 - 1)),
									(int)(pmsMaterial->Diffuse[1] * (MAX_COLOR_INTENSITY32 - 1)),
									(int)(pmsMaterial->Diffuse[2] * (MAX_COLOR_INTENSITY32 - 1)));

	pmaterial->c_spec = _RGB32BIT(	(int)(pmsMaterial->Specular[0] * (MAX_COLOR_INTENSITY32 - 1)),
									(int)(pmsMaterial->Specular[1] * (MAX_COLOR_INTENSITY32 - 1)),
									(int)(pmsMaterial->Specular[2] * (MAX_COLOR_INTENSITY32 - 1)));

	pmaterial->c_emis = _RGB32BIT(	(int)(pmsMaterial->Emissive[0] * (MAX_COLOR_INTENSITY32 - 1)),
									(int)(pmsMaterial->Emissive[1] * (MAX_COLOR_INTENSITY32 - 1)),
									(int)(pmsMaterial->Emissive[2] * (MAX_COLOR_INTENSITY32 - 1)));

	if(0 != strcmp(pmsMaterial->szDiffuseTexture, ""))
	{
		if(!Create_Bitmap_From_File(&btmp, pmsMaterial->szDiffuseTexture))
			ON_ERROR_GOTO(SFORMAT1(gbuffer, "load bitmap %s failed", pmsMaterial->szDiffuseTexture));

		if(!Create_Image32(&pmaterial->texture,
				btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
			ON_ERROR_GOTO("create image failed");

		if(!Load_Image_From_Bitmap32(&pmaterial->texture, &btmp, 0, 0,
				btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
			ON_ERROR_GOTO("load image failed");

		Destroy_Bitmap(&btmp);

		SET_BIT(pmaterial->attr, MATERIAL_ATTR_TEXTURE);
	}

	if(0 != pmaterial->c_ambi)
		SET_BIT(pmaterial->attr, MATERIAL_ATTR_AMBIENT);

	if(0 != pmaterial->c_diff)
		SET_BIT(pmaterial->attr, MATERIAL_ATTR_DIFFUSE);

	if(0 != pmaterial->c_spec)
		SET_BIT(pmaterial->attr, MATERIAL_ATTR_SPECULAR);

	if(0 != pmaterial->c_emis)
		SET_BIT(pmaterial->attr, MATERIAL_ATTR_EMISSIVE);

	strcpy(pmaterial->name, pmsMaterial->szName);
	return true;

ON_ERROR:
	Destroy_Bitmap(&btmp);
	Destroy_Material(pmaterial);
	return false;
}

T3DLIB_API bool Create_Object4D_From_MsMesh(OBJECT4DV1 * pobj, msMesh * pmesh,

											size_t max_tri_size /*= 3000*/,
											size_t max_ver_size /*= 3000*/,
											size_t max_nor_size /*= 3000*/)
{
	assert(NULL == pobj->tri_list.elems);
	assert(NULL == pobj->ver_list.elems);
	assert(NULL == pobj->ver_list_t.elems);
	assert(NULL == pobj->nor_list.elems);
	assert(NULL == pobj->nor_list_t.elems);

	if(!Create_Array(&pobj->tri_list, max_tri_size))
		ON_ERROR_GOTO("create triangle list failed");

	int i;
	for(i = 0; i < pmesh->nNumTriangles; i++)
	{
		TRIANGLEV1 * ptri;
		if(!Append_Array(&pobj->tri_list, &ptri))
			ON_ERROR_GOTO("append triangle list failed");
		INIT_ZERO(*ptri);

		ptri->v0_i = pmesh->pTriangles[i].nVertexIndices[0];
		ptri->v1_i = pmesh->pTriangles[i].nVertexIndices[2]; // !!!
		ptri->v2_i = pmesh->pTriangles[i].nVertexIndices[1]; // !!!

		ptri->n0_i = pmesh->pTriangles[i].nNormalIndices[0];
		ptri->n1_i = pmesh->pTriangles[i].nNormalIndices[2]; // !!!
		ptri->n2_i = pmesh->pTriangles[i].nNormalIndices[1]; // !!!

		ptri->state = TRI_STATE_ACTIVE;
	}

	if(!Create_Array(&pobj->ver_list, max_ver_size))
		ON_ERROR_GOTO("create vertex list failed");

	for(i = 0; i < pmesh->nNumVertices; i++)
	{
		VERTEXV1T * pver;
		if(!Append_Array(&pobj->ver_list, &pver))
			ON_ERROR_GOTO("append vertex list failed");
		INIT_ZERO(*pver);

		VECTOR4D_InitXYZ( &pver->_4D,
						(REAL)pmesh->pVertices[i].Vertex[0],
						(REAL)pmesh->pVertices[i].Vertex[1],
						-(REAL)pmesh->pVertices[i].Vertex[2]); // !!!

		//pver->u = (FIXP16)(pmesh->pVertices[i].u * FIXP16_MAG);
		//pver->v = (FIXP16)(pmesh->pVertices[i].v * FIXP16_MAG);
			// !!! note: the u, v should be absolutely coordinate with texture's width and height
	}

	if(!Create_Array(&pobj->ver_list_t, pobj->ver_list.size))
		ON_ERROR_GOTO("create vertex_t list failed");

	if(!Create_Array(&pobj->nor_list, max_nor_size))
		ON_ERROR_GOTO("create normal list failed");

	for(i = 0; i < pmesh->nNumNormals; i++)
	{
		VECTOR4D * pnor;
		if(!Append_Array(&pobj->nor_list, &pnor))
			ON_ERROR_GOTO("append normal list failed");
		memset(pnor, 0, sizeof(*pnor));

		VECTOR4D_InitXYZ( pnor,
						(REAL)pmesh->pNormals[i][0],
						(REAL)pmesh->pNormals[i][1],
						-(REAL)pmesh->pNormals[i][2]); // !!!
	}

	if(!Create_Array(&pobj->nor_list_t, pobj->nor_list.size))
		ON_ERROR_GOTO("create normal_t list failed");

	pobj->tri_orig_num = pobj->tri_list.length;

	strcpy(pobj->name, pmesh->szName);
	return true;

ON_ERROR:
	Destroy_Object4D(pobj);
	return false;
}

T3DLIB_API bool Create_Material_From_MsModel_By_Name16(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name)
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
			return Create_Material_From_MsMaterial16(pmaterial, pmat);
		}
	}
	ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot find material %s", material_name));

ON_ERROR:
	Destroy_Bitmap(&btmp);
	Destroy_Material(pmaterial);
	return false;
}

T3DLIB_API bool Create_Material_From_MsModel_By_Name32(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name)
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
			return Create_Material_From_MsMaterial32(pmaterial, pmat);
		}
	}
	ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot find material %s", material_name));

ON_ERROR:
	Destroy_Bitmap(&btmp);
	Destroy_Material(pmaterial);
	return false;
}

T3DLIB_API void Destroy_Material(MATERIALV1 * pmaterial)
{
	Destroy_Image(&pmaterial->texture);
	INIT_ZERO(*pmaterial);
}

T3DLIB_API bool Create_Object4D_From_MsModel_By_Name(OBJECT4DV1 * pobj, msModel * pmodel, const char * mesh_name,

													 size_t max_tri_size /*= 3000*/,
													 size_t max_ver_size /*= 3000*/,
													 size_t max_nor_size /*= 3000*/)
{
	assert(pobj->tri_list.elems == NULL);
	assert(pobj->ver_list.elems == NULL);
	assert(pobj->ver_list_t.elems == NULL);
	assert(pobj->nor_list.elems == NULL);
	assert(pobj->nor_list_t.elems == NULL);

	int i;
	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		msMesh * pmesh = &pmodel->pMeshes[i];
		if(0 == strcmp(pmesh->szName, mesh_name))
		{
			if(!Create_Object4D_From_MsMesh(pobj, pmesh, max_tri_size, max_ver_size, max_nor_size))
				return false;

			if(pmesh->nMaterialIndex >= 0 && pmodel->nNumMaterials > 0)
			{
				if(pmesh->nMaterialIndex > pmodel->nNumMaterials - 1)
					ON_ERROR_GOTO("material index overflow");

				strcpy(pobj->material_name, pmodel->pMaterials[pmesh->nMaterialIndex].szName);
			}

			return true;
		}
	}
	ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot find mesh %s", mesh_name));

ON_ERROR:
	Destroy_Object4D(pobj);
	return false;
}

T3DLIB_API void Undate_Object4D_Absolute_UV(OBJECT4DV1 * pobj, msModel * pmodel, MATERIALV1 * pmaterial)
{
	assert(pmaterial->texture.pbuffer != NULL);

	int i, j;
	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		msMesh * pmesh = &pmodel->pMeshes[i];
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
	{
		memset(pobj->tri_list.elems[i].diffs, 0, sizeof(pobj->tri_list.elems[i].diffs));
		memset(pobj->tri_list.elems[i].specs, 0, sizeof(pobj->tri_list.elems[i].specs));

		pobj->tri_list.elems[i].state = TRI_STATE_ACTIVE;
	}
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

T3DLIB_API void Model_To_World_Object4D(OBJECT4DV1 * pobj, VECTOR4D * vpos_ptr /*= NULL*/, VECTOR4D * vrot_ptr /*= NULL*/)
{
	assert(pobj->ver_list_t.size >= pobj->ver_list.size);
	assert(pobj->ver_list_t.length == 0);

	if(NULL == vpos_ptr)
		vpos_ptr = &pobj->vpos;

	if(NULL == vrot_ptr)
		vrot_ptr = &pobj->vrot;

	int i;
	if(IS_ZERO_FLOAT(vrot_ptr->x)
		&& IS_ZERO_FLOAT(vrot_ptr->y)
		&& IS_ZERO_FLOAT(vrot_ptr->z))
	{
		pobj->ver_list_t.length = pobj->ver_list.length;
		for(i = 0; i < (int)pobj->ver_list.length; i++)
		{
			memcpy(&pobj->ver_list_t.elems[i], &pobj->ver_list.elems[i], sizeof(*pobj->ver_list.elems));
			VECTOR3D_Add(&pobj->ver_list_t.elems[i]._3D, &vpos_ptr->_3D);
		}

		pobj->nor_list_t.length = pobj->nor_list.length;
		for(i = 0; i < (int)pobj->nor_list.length; i++)
		{
			memcpy(&pobj->nor_list_t.elems[i], &pobj->nor_list.elems[i], sizeof(*pobj->ver_list.elems));
			VECTOR3D_Add(&pobj->nor_list_t.elems[i]._3D, &vpos_ptr->_3D);
		}
	}
	else
	{
		MATRIX4X4 mrot, mmov, mres;
		Mat_Mul_4X4(&mres,
			Build_Mat_RotationXYZ(&mrot, vrot_ptr), Build_Mat_PositionXYZ(&mmov, vpos_ptr));

		pobj->ver_list_t.length = pobj->ver_list.length;
		for(i = 0; i < (int)pobj->ver_list.length; i++)
		{
			memcpy(&pobj->ver_list_t.elems[i], &pobj->ver_list.elems[i], sizeof(*pobj->ver_list.elems));
			Mat_Mul_VECTOR4D_4X4(&pobj->ver_list_t.elems[i]._4D, &pobj->ver_list.elems[i]._4D, &mres);
		}

		pobj->nor_list_t.length = pobj->nor_list.length;
		for(i = 0; i < (int)pobj->nor_list.length; i++)
		{
			memcpy(&pobj->nor_list_t.elems[i], &pobj->nor_list.elems[i], sizeof(*pobj->ver_list.elems));
			Mat_Mul_VECTOR4D_4X4(&pobj->nor_list_t.elems[i], &pobj->nor_list.elems[i], &mres);
		}
	}
}

T3DLIB_API void Remove_Object4D_Backface_At_World(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
		{
			VECTOR4D v0, v1, v3, v4;
			VECTOR3D_Cross(&v3._3D,
							VECTOR3D_Sub(&v0._3D,
											&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._3D,
											&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._3D),
							VECTOR3D_Sub(&v1._3D,
											&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._3D,
											&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._3D));
			VECTOR3D_Sub(&v4._3D,
							&pcam->vpos._3D, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._3D);

			if(VECTOR3D_Dot(&v3._3D, &v4._3D) <= 0)
			{
				pobj->tri_list.elems[i].state = TRI_STATE_BACKFACE;
			}
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

T3DLIB_API void Remove_Object4D_Backface_At_Perspective(OBJECT4DV1 * pobj)
{
	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
		{
			VECTOR2D v0, v1;
			if(VECTOR2D_Cross(
							VECTOR2D_Sub(&v0,
											&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._2D,
											&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._2D),
							VECTOR2D_Sub(&v1,
											&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._2D,
											&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._2D)) >= 0) // !!!
			{
				pobj->tri_list.elems[i].state = TRI_STATE_BACKFACE;
			}
		}
	}
}

T3DLIB_API void Perspective_To_Screen_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pobj->ver_list_t.length; i++)
	{
		pobj->ver_list_t.elems[i].x =
			((REAL)0.5 * pcam->viewplane.width + pobj->ver_list_t.elems[i].x)
				/ pcam->viewplane.width * VIEWPORT_LIMIT_END(pcam->viewport.width) + VIEWPORT_LIMIT_BEG(pcam->viewport.x);		// !!!

		pobj->ver_list_t.elems[i].y =
			((REAL)0.5 * pcam->viewplane.height - pobj->ver_list_t.elems[i].y)
				/ pcam->viewplane.height * VIEWPORT_LIMIT_END(pcam->viewport.height) + VIEWPORT_LIMIT_BEG(pcam->viewport.y);	// !!!
	}
}

T3DLIB_API void Draw_Object4D_Wire16(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	assert(pcam->psurf != NULL);
	assert(pcam->psurf->color_shift == _16BIT_BYTES_SHIFT);

	RENDERCONTEXTV1 rc;
	INIT_ZERO(rc);

	memcpy(&rc._SURFACE, pcam->psurf, sizeof(rc._SURFACE));

	rc.fmin_clip_x = pcam->viewport.x;
	rc.fmin_clip_y = pcam->viewport.y;
	rc.fmax_clip_x = pcam->viewport.x + pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.y + pcam->viewport.height - 1;

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

			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = pobj->tri_list.elems[i].c_diff1;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = pobj->tri_list.elems[i].c_diff2;

			Draw_Line16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Line16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Line16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
			break;

		case TRI_STATE_CLIPPED:

			//pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
			//pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = pobj->tri_list.elems[i].c_diff1;
			//pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = pobj->tri_list.elems[i].c_diff2;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = Create_RGBI(255, 0, 0);

			Draw_Clipped_Line16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Clipped_Line16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Clipped_Line16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
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

	memcpy(&rc._SURFACE, pcam->psurf, sizeof(rc._SURFACE));

	rc.fmin_clip_x = pcam->viewport.x;
	rc.fmin_clip_y = pcam->viewport.y;
	rc.fmax_clip_x = pcam->viewport.x + pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.y + pcam->viewport.height - 1;

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

			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = pobj->tri_list.elems[i].c_diff1;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = pobj->tri_list.elems[i].c_diff2;

			Draw_Line32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Line32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Line32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
			break;

		case TRI_STATE_CLIPPED:

			//pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
			//pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = pobj->tri_list.elems[i].c_diff1;
			//pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = pobj->tri_list.elems[i].c_diff2;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = Create_RGBI(255, 0, 0);
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = Create_RGBI(255, 0, 0);

			Draw_Clipped_Line32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Clipped_Line32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Clipped_Line32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
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

	memcpy(&rc._SURFACE, pcam->psurf, sizeof(rc._SURFACE));
	memcpy(&rc._ZBUFFER, pcam->pzbuf, sizeof(rc._ZBUFFER));

	rc.fmin_clip_x = pcam->viewport.x;
	rc.fmin_clip_y = pcam->viewport.y;
	rc.fmax_clip_x = pcam->viewport.x + pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.y + pcam->viewport.height - 1;

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

			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = pobj->tri_list.elems[i].c_diff1;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = pobj->tri_list.elems[i].c_diff2;

			Draw_Line_ZbufferRW16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Line_ZbufferRW16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Line_ZbufferRW16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
			break;

		case TRI_STATE_CLIPPED:

			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = pobj->tri_list.elems[i].c_diff1;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = pobj->tri_list.elems[i].c_diff2;

			Draw_Clipped_Line_ZbufferRW16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Clipped_Line_ZbufferRW16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Clipped_Line_ZbufferRW16(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
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

	memcpy(&rc._SURFACE, pcam->psurf, sizeof(rc._SURFACE));
	memcpy(&rc._ZBUFFER, pcam->pzbuf, sizeof(rc._ZBUFFER));

	rc.fmin_clip_x = pcam->viewport.x;
	rc.fmin_clip_y = pcam->viewport.y;
	rc.fmax_clip_x = pcam->viewport.x + pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.y + pcam->viewport.height - 1;

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

			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = pobj->tri_list.elems[i].c_diff1;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = pobj->tri_list.elems[i].c_diff2;

			Draw_Line_ZbufferRW32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Line_ZbufferRW32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Line_ZbufferRW32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
			break;

		case TRI_STATE_CLIPPED:

			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = pobj->tri_list.elems[i].c_diff1;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = pobj->tri_list.elems[i].c_diff2;

			Draw_Clipped_Line_ZbufferRW32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1);
			Draw_Clipped_Line_ZbufferRW32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			Draw_Clipped_Line_ZbufferRW32(&rc, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1, &pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1);
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

	memcpy(&rc._SURFACE, pcam->psurf, sizeof(rc._SURFACE));

	rc.fmin_clip_x = pcam->viewport.x;
	rc.fmin_clip_y = pcam->viewport.y;
	rc.fmax_clip_x = pcam->viewport.x + pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.y + pcam->viewport.height - 1;

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

			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;

			Draw_Triangle16(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			break;

		case TRI_STATE_CLIPPED:

//			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = Create_RGBI(255, 0, 0);

			Draw_Clipped_Triangle16(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
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

	memcpy(&rc._SURFACE, pcam->psurf, sizeof(rc._SURFACE));

	rc.fmin_clip_x = pcam->viewport.x;
	rc.fmin_clip_y = pcam->viewport.y;
	rc.fmax_clip_x = pcam->viewport.x + pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.y + pcam->viewport.height - 1;

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

			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;

			Draw_Triangle32(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
			break;

		case TRI_STATE_CLIPPED:

//			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = Create_RGBI(255, 0, 0);

			Draw_Clipped_Triangle32(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i]._VERTEXV1,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]._VERTEXV1);
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

	memcpy(&rc._SURFACE, pcam->psurf, sizeof(rc._SURFACE));
	memcpy(&rc._ZBUFFER, pcam->pzbuf, sizeof(rc._ZBUFFER));
	memcpy(&rc._TEXTURE, &pmaterial->texture, sizeof(rc._TEXTURE));

	rc.fmin_clip_x = pcam->viewport.x;
	rc.fmin_clip_y = pcam->viewport.y;
	rc.fmax_clip_x = pcam->viewport.x + pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.y + pcam->viewport.height - 1;

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

			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = pobj->tri_list.elems[i].c_diff1;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = pobj->tri_list.elems[i].c_diff2;

			Draw_Triangle_Gouraud_Texture_ZBufferRW16(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i],
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i],
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]);
			break;

		case TRI_STATE_CLIPPED:

			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = pobj->tri_list.elems[i].c_diff1;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = pobj->tri_list.elems[i].c_diff2;

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

	memcpy(&rc._SURFACE, pcam->psurf, sizeof(rc._SURFACE));
	memcpy(&rc._ZBUFFER, pcam->pzbuf, sizeof(rc._ZBUFFER));
	memcpy(&rc._TEXTURE, &pmaterial->texture, sizeof(rc._TEXTURE));

	rc.fmin_clip_x = pcam->viewport.x;
	rc.fmin_clip_y = pcam->viewport.y;
	rc.fmax_clip_x = pcam->viewport.x + pcam->viewport.width - 1;
	rc.fmax_clip_y = pcam->viewport.y + pcam->viewport.height - 1;

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

			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = pobj->tri_list.elems[i].c_diff1;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = pobj->tri_list.elems[i].c_diff2;

			Draw_Triangle_Gouraud_Texture_ZBufferRW32(&rc,
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i],
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i],
							&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i]);
			break;

		case TRI_STATE_CLIPPED:

			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i].c_diff = pobj->tri_list.elems[i].c_diff0;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i].c_diff = pobj->tri_list.elems[i].c_diff1;
			pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i].c_diff = pobj->tri_list.elems[i].c_diff2;

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

static inline unsigned int Light_VertexT_By_Ambient16(VERTEXV1T * pver, VECTOR4D * pnor, LIGHT4DV1 * plight, MATERIALV1 * pmaterial)
{
	{
		// I(d)ambient = I0ambient * Clambient

		return RGB16_MUL(plight->intensity, pmaterial->c_ambi);
	}

	UNREFERENCED_PARAMETER(pver);
	UNREFERENCED_PARAMETER(pnor);
}

static inline unsigned int Light_VertexT_By_Direct16(VERTEXV1T * pver, VECTOR4D * pnor, LIGHT4DV1 * plight, MATERIALV1 * pmaterial)
{
	REAL dot = VECTOR3D_Dot(&pnor->_3D, &plight->vdir._3D);

	if(dot < 0)
	{
		// I(d)dir = I0dir * Cldir (n . l)

		return RGB16_MUL(RGB16_MUL(plight->intensity, pmaterial->c_diff), Create_RGBF16(-dot, -dot, -dot));
	}

	return 0;
	UNREFERENCED_PARAMETER(pver);
}

static inline unsigned int Light_VertexT_By_Point16(VERTEXV1T * pver, VECTOR4D * pnor, LIGHT4DV1 * plight, MATERIALV1 * pmaterial)
{
	VECTOR4D dir;
	REAL dot = VECTOR3D_Dot(&pnor->_3D, VECTOR3D_Sub(&dir._3D, &pver->_3D, &plight->vpos._3D));
	REAL len = VECTOR3D_Length(&dir._3D);

	if(dot < 0 && len > 0)
	{
		//               I0point * Clpoint
		// I(d)point = --------------------- (n . l)
		//             kc + kl * d + kq * d2

		dot /= len * (plight->kc + plight->kl * len + plight->kq * len * len);

		return RGB16_MUL(RGB16_MUL(plight->intensity, pmaterial->c_diff), Create_RGBF16(-dot, -dot, -dot));
	}

	return 0;
}

static inline unsigned int Light_VertexT_By_Ambient32(VERTEXV1T * pver, VECTOR4D * pnor, LIGHT4DV1 * plight, MATERIALV1 * pmaterial)
{
	{
		// I(d)ambient = I0ambient * Clambient

		return RGB32_MUL(plight->intensity, pmaterial->c_ambi);
	}

	UNREFERENCED_PARAMETER(pver);
	UNREFERENCED_PARAMETER(pnor);
}

static inline unsigned int Light_VertexT_By_Direct32(VERTEXV1T * pver, VECTOR4D * pnor, LIGHT4DV1 * plight, MATERIALV1 * pmaterial)
{
	REAL dot = VECTOR3D_Dot(&pnor->_3D, &plight->vdir._3D);

	if(dot < 0)
	{
		// I(d)dir = I0dir * Cldir (n . l)

		return RGB32_MUL(RGB32_MUL(plight->intensity, pmaterial->c_diff), Create_RGBF32(-dot, -dot, -dot));
	}

	return 0;
	UNREFERENCED_PARAMETER(pver);
}

static inline unsigned int Light_VertexT_By_Point32(VERTEXV1T * pver, VECTOR4D * pnor, LIGHT4DV1 * plight, MATERIALV1 * pmaterial)
{
	VECTOR4D dir;
	REAL dot = VECTOR3D_Dot(&pnor->_3D, VECTOR3D_Sub(&dir._3D, &pver->_3D, &plight->vpos._3D));
	REAL len = VECTOR3D_Length(&dir._3D);

	if(dot < 0 && len > 0)
	{
		//               I0point * Clpoint
		// I(d)point = --------------------- (n . l)
		//             kc + kl * d + kq * d2

		dot /= len * (plight->kc + plight->kl * len + plight->kq * len * len);

		return RGB32_MUL(RGB32_MUL(plight->intensity, pmaterial->c_diff), Create_RGBF32(-dot, -dot, -dot));
	}

	return 0;
}

T3DLIB_API void Light_Object4D16(OBJECT4DV1 * pobj, LIGHT4DV1 * plight, MATERIALV1 * pmaterial)
{
	int i;
	switch(plight->mode)
	{
	case LIGHT4DV1_MODE_AMBIENT:
		for(i = 0; i < (int)pobj->tri_list.length; i++)
		{
			if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
			{
				unsigned int ctmp;
				ctmp = Light_VertexT_By_Ambient16(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n0_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff0 = RGB16_ADD(pobj->tri_list.elems[i].c_diff0, ctmp);

				ctmp = Light_VertexT_By_Ambient16(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n1_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff1 = RGB16_ADD(pobj->tri_list.elems[i].c_diff1, ctmp);

				ctmp = Light_VertexT_By_Ambient16(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n2_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff2 = RGB16_ADD(pobj->tri_list.elems[i].c_diff2, ctmp);
			}
		}
		break;

	case LIGHT4DV1_MODE_DIRECT:
		for(i = 0; i < (int)pobj->tri_list.length; i++)
		{
			if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
			{
				unsigned int ctmp;
				ctmp = Light_VertexT_By_Direct16(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n0_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff0 = RGB16_ADD(pobj->tri_list.elems[i].c_diff0, ctmp);

				ctmp = Light_VertexT_By_Direct16(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n1_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff1 = RGB16_ADD(pobj->tri_list.elems[i].c_diff1, ctmp);

				ctmp = Light_VertexT_By_Direct16(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n2_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff2 = RGB16_ADD(pobj->tri_list.elems[i].c_diff2, ctmp);
			}
		}
		break;

	case LIGHT4DV1_MODE_POINT:
		for(i = 0; i < (int)pobj->tri_list.length; i++)
		{
			if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
			{
				unsigned int ctmp;
				ctmp = Light_VertexT_By_Point16(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n0_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff0 = RGB16_ADD(pobj->tri_list.elems[i].c_diff0, ctmp);

				ctmp = Light_VertexT_By_Point16(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n1_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff1 = RGB16_ADD(pobj->tri_list.elems[i].c_diff1, ctmp);

				ctmp = Light_VertexT_By_Point16(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n2_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff2 = RGB16_ADD(pobj->tri_list.elems[i].c_diff2, ctmp);
			}
		}
		break;

	default:
		break;
	}
}

T3DLIB_API void Light_Object4D32(OBJECT4DV1 * pobj, LIGHT4DV1 * plight, MATERIALV1 * pmaterial)
{
	int i;
	switch(plight->mode)
	{
	case LIGHT4DV1_MODE_AMBIENT:
		for(i = 0; i < (int)pobj->tri_list.length; i++)
		{
			if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
			{
				unsigned int ctmp;
				ctmp = Light_VertexT_By_Ambient32(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n0_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff0 = RGB32_ADD(pobj->tri_list.elems[i].c_diff0, ctmp);

				ctmp = Light_VertexT_By_Ambient32(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n1_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff1 = RGB32_ADD(pobj->tri_list.elems[i].c_diff1, ctmp);

				ctmp = Light_VertexT_By_Ambient32(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n2_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff2 = RGB32_ADD(pobj->tri_list.elems[i].c_diff2, ctmp);
			}
		}
		break;

	case LIGHT4DV1_MODE_DIRECT:
		for(i = 0; i < (int)pobj->tri_list.length; i++)
		{
			if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
			{
				unsigned int ctmp;
				ctmp = Light_VertexT_By_Direct32(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n0_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff0 = RGB32_ADD(pobj->tri_list.elems[i].c_diff0, ctmp);

				ctmp = Light_VertexT_By_Direct32(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n1_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff1 = RGB32_ADD(pobj->tri_list.elems[i].c_diff1, ctmp);

				ctmp = Light_VertexT_By_Direct32(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n2_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff2 = RGB32_ADD(pobj->tri_list.elems[i].c_diff2, ctmp);
			}
		}
		break;

	case LIGHT4DV1_MODE_POINT:
		for(i = 0; i < (int)pobj->tri_list.length; i++)
		{
			if(IS_VALID_TRIANGLE(pobj->tri_list.elems[i].state))
			{
				unsigned int ctmp;
				ctmp = Light_VertexT_By_Point32(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v0_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n0_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff0 = RGB32_ADD(pobj->tri_list.elems[i].c_diff0, ctmp);

				ctmp = Light_VertexT_By_Point32(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v1_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n1_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff1 = RGB32_ADD(pobj->tri_list.elems[i].c_diff1, ctmp);

				ctmp = Light_VertexT_By_Point32(
								&pobj->ver_list_t.elems[pobj->tri_list.elems[i].v2_i],
								&pobj->nor_list_t.elems[pobj->tri_list.elems[i].n2_i], plight, pmaterial);
				pobj->tri_list.elems[i].c_diff2 = RGB32_ADD(pobj->tri_list.elems[i].c_diff2, ctmp);
			}
		}
		break;

	default:
		break;
	}
}
