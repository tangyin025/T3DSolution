/*
 * File: T3DLIB/t3dlib6.h
 */

#ifndef __T3DLIB6_H__
#define __T3DLIB6_H__

#include "t3dCommons.h"
#include "msModel.h"

#define ARRAYV1_INCREMENT_SIZE			(10)
#define CAM4DV1_VIEWPLANE_DIST			(1)

#define ROTATION_SEQ_XYZ				(0)
#define ROTATION_SEQ_XZY				(1)
#define ROTATION_SEQ_YXZ				(2)
#define ROTATION_SEQ_YZX				(3)
#define ROTATION_SEQ_ZXY				(4)
#define ROTATION_SEQ_ZYX				(5)

#define UVN_MODE_SIMPLE					(0)
#define UVN_MODE_SPHERICAL				(1)

#define TRI_STATE_NULL					(0)
#define TRI_STATE_ACTIVE				(1)
#define TRI_STATE_CULLED				(2)
#define TRI_STATE_CLIPPED				(3)
#define TRI_STATE_BACKFACE				(4)

#define IS_VALID_TRIANGLE(s)			((s) == TRI_STATE_ACTIVE || (s) == TRI_STATE_CLIPPED)

#define MATERIAL_ATTR_AMBIENT			(0x01)
#define MATERIAL_ATTR_DIFFUSE			(0x02)
#define MATERIAL_ATTR_SPECULAR			(0x04)
#define MATERIAL_ATTR_EMISSIVE			(0x08)
#define MATERIAL_ATTR_TEXTURE			(0x10)

#define VIEWPORT_LIMIT_BEG(f)			(f)
#define VIEWPORT_LIMIT_END(f)			((f) - (REAL)EPSILON_E3) // !!! E5 ~ E6 will still have bug

typedef enum T3DLIB_API CAM4DV1_MODE_TYP
{
	CAM4DV1_MODE_UNKNOWN = 0,
	CAM4DV1_MODE_EULAR,
	CAM4DV1_MODE_UVN,

} CAM4DV1_MODE, * CAM4DV1_MODE_PTR;

typedef enum T3DLIB_API VIEWPORT_FIX_MODE_TYP
{
	VIEWPORT_FIX_MODE_WIDTH,
	VIEWPORT_FIX_MODE_HEIGHT,

} VIEWPORT_FIX_MODE, * VIEWPORT_FIX_MODE_PTR;

typedef enum T3DLIB_API TRANSFORM_MODE_TYP
{
	TRANSFORM_MODE_LOCAL_ONLY,
	TRANSFORM_MODE_TRANS_ONLY,
	TRANSFORM_MODE_LOCAL_TO_TRANS,

} TRANSFORM_MODE, * TRANSFORM_MODE_PTR;

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
inline bool Append_Array(ARRAYV1<ELEM_T> * parr, ELEM_T ** ppelem, size_t _increment_size = ARRAYV1_INCREMENT_SIZE)
{
	ELEM_T * p = NULL;
	if(parr->length >= parr->size)
	{
		if(NULL == (p = (ELEM_T *)realloc(parr->elems, (parr->size + _increment_size) * sizeof(*p))))
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

	struct VIEWPORT_TYP
	{
		REAL		x, y;
		REAL		width, height;

	} viewport;

	struct VIEWPLANE_TYP
	{
		//REAL		dist;
		REAL		width, height;

	} viewplane;

	SURFACEV1 *		psurf;
	ZBUFFERV1 *		pzbuf;

} CAM4DV1, * CAM4DV1_PTR;

typedef struct T3DLIB_API MATERIALV1_TYP
{
	unsigned int	state;
	unsigned int	attr;
	unsigned int	c_ambi;
	unsigned int	c_diff;
	unsigned int	c_spec;
 	unsigned int	c_emis;
	IMAGEV1			texture;

	char			name[MS_MAX_NAME];

	_CTOR_DECLARE(MATERIALV1_TYP);
	_DTOR_DECLARE(MATERIALV1_TYP);

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

			unsigned int c_diff0, c_diff1, c_diff2;
			unsigned int c_spec0, c_spec1, c_spec2;
		};

		struct
		{
			int vers[3];
			int nors[3];

			unsigned int diffs[3];
			unsigned int specs[3];
		};
	};

} TRIANGLEV1, * TRIANGLEV1_PTR;
#pragma warning(default : 4201)

typedef struct T3DLIB_API ARRAYV1<VECTOR4D> NOR_ARRAYV1, * NOR_ARRAYV1_PTR;

typedef struct T3DLIB_API ARRAYV1<VERTEXV1T> VER_ARRAYV1, * VER_ARRAYV1_PTR;

typedef struct T3DLIB_API ARRAYV1<TRIANGLEV1> TRI_ARRAYV1, * TRI_ARRAYV1_PTR;

typedef struct T3DLIB_API OBJECT4DV1_TYP
{
	unsigned int		state;
	unsigned int		attr;
	VECTOR4D			vpos;
	VECTOR4D			vrot;
	size_t				tri_orig_num;
	TRI_ARRAYV1			tri_list;
	VER_ARRAYV1			ver_list;
	VER_ARRAYV1			ver_list_t;
	NOR_ARRAYV1			nor_list;
	NOR_ARRAYV1			nor_list_t;
	//MATERIALV1 *		pmaterial;

	char				name[MS_MAX_NAME];
	char				material_name[MS_MAX_NAME];

	_CTOR_DECLARE(OBJECT4DV1_TYP);
	_DTOR_DECLARE(OBJECT4DV1_TYP);

} OBJECT4DV1, * OBJECT4DV1_PTR;

extern T3DLIB_API bool (* Create_Material_From_MsMaterial)(MATERIALV1 * pmaterial, msMaterial * pmsMaterial);
extern T3DLIB_API bool (* Create_Material_From_MsModel_By_Name)(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name);
extern T3DLIB_API bool (* Clip_Object4D_Gouraud_Texture)(OBJECT4DV1 * pobj, CAM4DV1 * pcam);
extern T3DLIB_API void (* Draw_Object4D_Wire)(OBJECT4DV1 * pobj, CAM4DV1 * pcam);
extern T3DLIB_API void (* Draw_Object4D_Wire_ZBufferRW)(OBJECT4DV1 * pobj, CAM4DV1 * pcam);
extern T3DLIB_API void (* Draw_Object4D)(OBJECT4DV1 * pobj, CAM4DV1 * pcam);
extern T3DLIB_API void (* Draw_Object4D_ZBufferRW)(OBJECT4DV1 * pobj, CAM4DV1 * pcam);
extern T3DLIB_API void (* Draw_Object4D_Texture_ZBufferRW)(OBJECT4DV1 * pobj, CAM4DV1 * pcam, MATERIALV1 * pmaterial);
extern T3DLIB_API void (* Draw_Object4D_Gouraud_ZBufferRW)(OBJECT4DV1 * pobj, CAM4DV1 * pcam);
extern T3DLIB_API void (* Draw_Object4D_Gouraud_Texture_ZBufferRW)(OBJECT4DV1 * pobj, CAM4DV1 * pcam, MATERIALV1 * pmaterial);

T3DLIB_API bool Init_T3dlib6(int bpp);

T3DLIB_API MATRIX4X4 * Build_Mat_PositionXYZ(MATRIX4X4 * pmres, const VECTOR4D * vpos_ptr);

T3DLIB_API MATRIX4X4 * Build_Mat_RotationXYZ(MATRIX4X4 * pmres, const VECTOR4D * vrot_ptr);

T3DLIB_API MATRIX4X4 * Build_Mat_RotationZYX(MATRIX4X4 * pmres, const VECTOR4D * vrot_ptr);

T3DLIB_API CAM4DV1 * CAM4DV1_Init(	CAM4DV1 * pcam, REAL width, REAL height,
									REAL				viewport_x	= 0,
									REAL				viewport_y	= 0,
									REAL				min_clip_z	= 10,
									REAL				max_clip_z	= 1000,
									REAL				fov			= DEG_TO_RAD(90),
									VIEWPORT_FIX_MODE	fix_mode	= VIEWPORT_FIX_MODE_HEIGHT,
									SURFACEV1 *			psurf		= NULL,
									ZBUFFERV1 *			pzbuf		= NULL);

T3DLIB_API MATRIX4X4 * Build_Camera4D_Mat_Euler(MATRIX4X4 * pmres, CAM4DV1 * pcam, int rot_seq = ROTATION_SEQ_ZXY);

T3DLIB_API MATRIX4X4 * Build_Camera4D_Mat_UVN(MATRIX4X4 * pmres, CAM4DV1 * pcam, int uvn_mode);

T3DLIB_API bool Create_Material_From_MsMaterial16(MATERIALV1 * pmaterial, msMaterial * pmsMaterial);

T3DLIB_API bool Create_Material_From_MsMaterial32(MATERIALV1 * pmaterial, msMaterial * pmsMaterial);

T3DLIB_API void Destroy_Material(MATERIALV1 * pmaterial);

T3DLIB_API bool Create_Object4D_From_MsMesh(OBJECT4DV1 * pobj, msMesh * pmesh,
											size_t max_tri_size = 3000,
											size_t max_ver_size = 3000,
											size_t max_nor_size = 3000);

T3DLIB_API void Destroy_Object4D(OBJECT4DV1 * pobj);

T3DLIB_API bool Create_Material_From_MsModel_By_Name16(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name);

T3DLIB_API bool Create_Material_From_MsModel_By_Name32(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name);

T3DLIB_API bool Create_Object4D_From_MsModel_By_Name(OBJECT4DV1 * pobj, msModel * pmodel, const char * mesh_name,
													 size_t max_tri_size = 3000,
													 size_t max_ver_size = 3000,
													 size_t max_nor_size = 3000);

T3DLIB_API void Undate_Object4D_Absolute_UV(OBJECT4DV1 * pobj, msModel * pmodel, MATERIALV1 * pmaterial);

T3DLIB_API void Reset_Object4D(OBJECT4DV1 * pobj);

T3DLIB_API void Transform_Object4D_Without_Normal(OBJECT4DV1 * pobj, const MATRIX4X4 * pmat, TRANSFORM_MODE trans_mode);

T3DLIB_API void Transform_Object4D(OBJECT4DV1 * pobj, const MATRIX4X4 * pmat, const MATRIX4X4 * pmat_n, TRANSFORM_MODE trans_mode);

T3DLIB_API void Model_To_World_Object4D_Without_Normal(OBJECT4DV1 * pobj,
										VECTOR4D * vpos_ptr = NULL,
										VECTOR4D * vrot_ptr = NULL,
										TRANSFORM_MODE trans_mode = TRANSFORM_MODE_LOCAL_TO_TRANS);

T3DLIB_API void Model_To_World_Object4D(OBJECT4DV1 * pobj,
										VECTOR4D * vpos_ptr = NULL,
										VECTOR4D * vrot_ptr = NULL,
										TRANSFORM_MODE trans_mode = TRANSFORM_MODE_LOCAL_TO_TRANS);

T3DLIB_API void Remove_Object4D_Backface_At_World(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void World_To_Camera_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API bool Clip_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API bool Clip_Object4D_Gouraud_Texture16(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API bool Clip_Object4D_Gouraud_Texture32(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Camera_To_Perspective_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Remove_Object4D_Backface_At_Perspective(OBJECT4DV1 * pobj);

T3DLIB_API void Perspective_To_Screen_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D_Wire16(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D_Wire32(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D_Wire_ZBufferRW16(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D_Wire_ZBufferRW32(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D16(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D32(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D_ZBufferRW16(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D_ZBufferRW32(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D_Texture_ZBufferRW16(OBJECT4DV1 * pobj, CAM4DV1 * pcam, MATERIALV1 * pmaterial);

T3DLIB_API void Draw_Object4D_Texture_ZBufferRW32(OBJECT4DV1 * pobj, CAM4DV1 * pcam, MATERIALV1 * pmaterial);

T3DLIB_API void Draw_Object4D_Gouraud_ZBufferRW16(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D_Gouraud_ZBufferRW32(OBJECT4DV1 * pobj, CAM4DV1 * pcam);

T3DLIB_API void Draw_Object4D_Gouraud_Texture_ZBufferRW16(OBJECT4DV1 * pobj, CAM4DV1 * pcam, MATERIALV1 * pmaterial);

T3DLIB_API void Draw_Object4D_Gouraud_Texture_ZBufferRW32(OBJECT4DV1 * pobj, CAM4DV1 * pcam, MATERIALV1 * pmaterial);

#define LIGHT_STATE_NULL				(0)
#define LIGHT_STATE_ACTIVE				(1)
#define LIGHT_STATE_CULLED				(2)

typedef enum T3DLIB_API LIGHT4DV1_MODE_TYP
{
	LIGHT4DV1_MODE_UNKNOWN = 0,
	LIGHT4DV1_MODE_AMBIENT,
	LIGHT4DV1_MODE_DIRECT,
	LIGHT4DV1_MODE_POINT,

} LIGHT4DV1_MODE, * LIGHT4DV1_MODE_PTR;

typedef struct T3DLIB_API LIGHT4DV1_TYP
{
	LIGHT4DV1_MODE	mode;
	int				state;
	int				attr;
	VECTOR4D		vpos;
	VECTOR4D		vdir;
	VECTOR4D		vtag;

	union
	{
		unsigned int	intensity;

		unsigned int	color;
	};

	REAL			kc, kl, kq;

} LIGHT4DV1, * LIGHT4DV1_PTR;

extern T3DLIB_API void (* Light_Object4D)(OBJECT4DV1 * pobj, LIGHT4DV1 * plight, MATERIALV1 * pmaterial);

T3DLIB_API void Light_Object4D16(OBJECT4DV1 * pobj, LIGHT4DV1 * plight, MATERIALV1 * pmaterial);

T3DLIB_API void Light_Object4D32(OBJECT4DV1 * pobj, LIGHT4DV1 * plight, MATERIALV1 * pmaterial);

#endif // __T3DLIB6_H__
