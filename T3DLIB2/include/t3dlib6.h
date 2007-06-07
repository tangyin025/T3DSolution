/*
 * File: T3DLIB2/t3dlib6.h
 */

#ifndef __T3DLIB6_H__
#define __T3DLIB6_H__

#include "t3dcommons.h"
#include "msModel.h"

#define ARRAYV1_INCREMENT_SIZE			(10)

template <typename ELEM_T>
struct ARRAYV1
{
	ELEM_T * elems;
	size_t size;
	size_t length;

	_CTOR_DECLARE(ARRAYV1);
	_DTOR_DECLARE(ARRAYV1);
};

_CTOR_IMPLEMENT_T1(ARRAYV1, ELEM_T);
_DTOR_IMPLEMENT_T1_W1(ARRAYV1, ELEM_T, Destroy_Array, elems);

template <typename ELEM_T>
bool Create_Array(ARRAYV1<ELEM_T> * parr, const size_t max_size)
{
	assert(parr->elems == NULL);

	ELEM_T * p = NULL;
	if(NULL == (p = (ELEM_T *)malloc((max_size) * sizeof(*p))))
		ON_ERROR_GOTO("malloc memory failed");

	parr->elems = p;
	parr->size = max_size;
	parr->length = 0;
	return true;

ON_ERROR:
	SAFE_FREE(p);
	return false;
}

template <typename ELEM_T>
void Destroy_Array(ARRAYV1<ELEM_T> * parr)
{
	SAFE_FREE(parr->elems);
	memset(parr, 0, sizeof(*parr));
}

template <typename ELEM_T>
inline void Clear_Array(ARRAYV1<ELEM_T> * parr)
{
	parr->length = 0;
}

template <typename ELEM_T>
inline bool Append_Array(ARRAYV1<ELEM_T> * parr, ELEM_T ** ppelem)
{
	ELEM_T * p = NULL;
	if(parr->length >= parr->size)
	{
		if(NULL == (p = (ELEM_T *)realloc(parr->elems, (parr->size + ARRAYV1_INCREMENT_SIZE) * sizeof(*p))))
			ON_ERROR_GOTO("realloc memory failed");

		parr->elems = p;
		parr->size += ARRAYV1_INCREMENT_SIZE;
	}

	*ppelem = &parr->elems[parr->length++];
	return true;

ON_ERROR:
	SAFE_FREE(p);
	return false;
}

typedef struct MATERIALV1_TYP
{
	unsigned int	state;
	unsigned int	attr;
	unsigned int	c_ambi;
	unsigned int	c_diff;
	unsigned int	c_spec;
 	unsigned int	c_emis;
	IMAGEV1			texture;

} MATERIALV1, * MATERIALV1_PTR;

#pragma warning(disable : 4201)
typedef struct TRIANGLEV1_TYP
{
	unsigned int state;
	unsigned int attr;
	union
	{
		struct
		{
			int v0_i, v1_i, v2_i;
			int n0_i, n1_i, n2_i;
		};

		struct
		{
			int vers[3];
			int nors[3];
		};
	};

} TRIANGLEV1, * TRIANGLEV1_PTR;

typedef struct T3DLIB_API ARRAYV1<VECTOR4D> NOR_ARRAYV1, * NOR_ARRAYV1_PTR;

typedef struct T3DLIB_API ARRAYV1<VERTEXV1T> VER_ARRAYV1, * VER_ARRAYV1_PTR;

typedef struct T3DLIB_API ARRAYV1<TRIANGLEV1> TRI_ARRAYV1, * TRI_ARRAYV1_PTR;

typedef struct T3DLIB_API OBJECT4DV1_TYP
{
	unsigned int		state;
	unsigned int		attr;
	VECTOR4D			vpos;
	VECTOR4D			vrot;
	TRI_ARRAYV1			tri_list;
	VER_ARRAYV1			ver_list;
	VER_ARRAYV1			ver_list_t;
	NOR_ARRAYV1			nor_list;
	NOR_ARRAYV1			nor_list_t;
	MATERIALV1 *		pmaterial;

} OBJECT4DV1, * OBJECT4DV1_PTR;

typedef enum T3DLIB_API CAM4DV1_MODE_TYP
{
	CAM4DV1_MODE_EULAR,
	CAM4DV1_MODE_UVN,

} CAM4DV1_MODE, * CAM4DV1_MODE_PTR;

typedef struct T3DLIB_API CAM4DV1_TYP
{
	CAM4DV1_MODE	mode;
	MATRIX4X4		mcam;
	VECTOR4D		vpos;
	VECTOR4D		vrot;
	VECTOR4D		vtag;
	VECTOR4D		u;
	VECTOR4D		v;
	VECTOR4D		n;
	REAL			fov;
	REAL			min_clip_z;
	REAL			max_clip_z;

	struct VIEWPLANE_TYP
	{
		REAL		dist, width, height;

	} viewplane;

	struct VIEWPORT_TYP
	{
		REAL		x, y, width, height;

	} viewport;

} CAM4DV1, * CAM4DV1_PTR;
#pragma warning(default : 4201)

extern T3DLIB_API void (* Draw_Object4D)(SURFACEV1 * psurface, OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API bool Init_T3dlib6(int bpp);

T3DLIB_API bool Create_Material_From_MsModel(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name);

T3DLIB_API void Destroy_Material(MATERIALV1 * pmaterial);

T3DLIB_API bool Create_Object4D_From_MsModel(OBJECT4DV1 * pobj, msModel * pmodel, const char * mesh_name,
											 size_t max_tri_size = 1000,
											 size_t max_ver_size = 3000,
											 size_t max_nor_size = 3000);

T3DLIB_API void Destroy_Object4D(OBJECT4DV1 * pobj);

T3DLIB_API void Model_To_World_Object4D(OBJECT4DV1 * pobj);

T3DLIB_API void World_To_Camera_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Camera_To_Perspective_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Perspective_To_Screen_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D16(SURFACEV1 * psurface, OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D32(SURFACEV1 * psurface, OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API bool Clip_Triangle_From_Camera(TRI_ARRAYV1 * ptris, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam);

#endif // __T3DLIB6_H__
