/*
 * File: T3DLIB/t3dlib7.h
 */

#ifndef __T3DLIB7_H__
#define __T3DLIB7_H__

#include "t3dCommons.h"
#include "t3dlib6.h"

typedef struct T3DLIB_API ARRAYV1<size_t> SIZE_T_ARRAYV1, * SIZE_T_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<MATRIX4X4> MAT_ARRAYV1, * MAT_ARRAYV1_PTR;

T3DLIB_API void Transform_Object4D_By_Matrix_List(OBJECT4DV1 *		pobj,
												  SIZE_T_ARRAYV1 *	pmat_index,
												  MAT_ARRAYV1 *		pmat_list,
												  SIZE_T_ARRAYV1 *	pmat_index_n,
												  MAT_ARRAYV1 *		pmat_list_n,
												  TRANSFORM_MODE	trans_mode);

typedef struct T3DLIB_API BONE4DV1_KEY_TYP
{
	REAL		time;
	VECTOR4D	vkey;

} BONE4DV1_KEY, * BONE4DV1_KEY_PTR;

typedef struct T3DLIB_API ARRAYV1<BONE4DV1_KEY> BONE4D_KEY_ARRAYV1, * BONE4D_KEY_ARRAYV1_PTR;

typedef struct T3DLIB_API BONE4DV1_TYP
{
	VECTOR4D			vpos;
	VECTOR4D			vrot;

	VECTOR4D			vpos_k;
	VECTOR4D			vrot_k;

	size_t				parent_i;
	SIZE_T_ARRAYV1		subs;

	BONE4D_KEY_ARRAYV1	kpos_list;
	BONE4D_KEY_ARRAYV1	krot_list;

	unsigned int		state;
	unsigned int		attr;
	char				name[MS_MAX_NAME];

	_CTOR_DECLARE(BONE4DV1_TYP);
	_DTOR_DECLARE(BONE4DV1_TYP);

} BONE4DV1, * BONE4DV1_PTR;

typedef struct T3DLIB_API ARRAYV1<BONE4DV1> BONE4D_ARRAYV1, * BONE4D_ARRAYV1_PTR;

typedef struct T3DLIB_API SKELETON4DV1_TYP
{
	BONE4D_ARRAYV1		bone_list;

	MAT_ARRAYV1			imat_list;
	MAT_ARRAYV1			imat_list_n;

	MAT_ARRAYV1			kmat_list;
	MAT_ARRAYV1			kmat_list_n;

	SIZE_T_ARRAYV1		roots;

	unsigned int		state;
	unsigned int		attr;
	char				name[MS_MAX_NAME];

	_CTOR_DECLARE(SKELETON4DV1_TYP);
	_DTOR_DECLARE(SKELETON4DV1_TYP);

} SKELETON4DV1, SKELETON4DV1_PTR;

T3DLIB_API bool Create_Bone4D_From_MsBone(BONE4DV1 * pbone, msBone * pmsBone, size_t max_sub_size = 10);

T3DLIB_API void Destroy_Bone4D(BONE4DV1 * pbone);

T3DLIB_API bool Create_Skeleton4D_From_MsModel(SKELETON4DV1 * pskel, msModel * pmodel,
											   size_t max_sub_size	= 10,
											   size_t max_root_size	= 10);

T3DLIB_API void Destroy_Skeleton4D(SKELETON4DV1 * pskel);

T3DLIB_API void Animate_Skeleton4D_By_Time(SKELETON4DV1 * pskel, REAL time);

T3DLIB_API void Build_Inverse_Matrix_Skeleton4D(SKELETON4DV1 * pskel);

T3DLIB_API void Build_Animate_Matrix_Skeleton4D(SKELETON4DV1 * pskel);

typedef struct T3DLIB_API ARRAYV1<OBJECT4DV1> OBJECT4D_ARRAYV1, * OBJECT4D_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<MATERIALV1> MATERIAL_ARRAYV1, * MATERIAL_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<SKELETON4DV1> SKELETON4D_ARRAYV1, * SKELETON4D_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<SIZE_T_ARRAYV1> INDEX_ARRAYV1, * INDEX_ARRAYV1_PTR;

typedef struct T3DLIB_API CHARACTER4DV1_TYP
{
	OBJECT4D_ARRAYV1	skin_list;

	MATERIAL_ARRAYV1	material_list;
	SIZE_T_ARRAYV1		skin_material_index;

	SKELETON4D_ARRAYV1	skel_list;
	INDEX_ARRAYV1		ver_bone_index_list;
	INDEX_ARRAYV1		nor_bone_index_list;

	VECTOR4D			vpos;
	VECTOR4D			vrot;

	unsigned int		state;
	unsigned int		attr;
	char				name[MS_MAX_NAME];

	_CTOR_DECLARE(CHARACTER4DV1_TYP);
	_DTOR_DECLARE(CHARACTER4DV1_TYP);

} CHARACTER4DV1, * CHARACTER4DV1_PTR;

T3DLIB_API bool Create_Character4D_From_MsModel(CHARACTER4DV1 * pchar, msModel * pmodel, size_t max_skel_size = 10);

T3DLIB_API void Destroy_Character4D(CHARACTER4DV1 * pchar);

inline void Reset_Character4D(CHARACTER4DV1 * pchar)
{
	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		Reset_Object4D(&pchar->skin_list.elems[i]);
	}
}

inline void Update_Character4D_Absolute_UV(CHARACTER4DV1 * pchar, msModel * pmodel)
{
	assert(pchar->skin_material_index.length == pchar->skin_list.length);

	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		assert(pchar->skin_material_index.elems[i] < pchar->material_list.length);

		MATERIALV1 * pmaterial = &pchar->material_list.elems[pchar->skin_material_index.elems[i]];

		if(MATERIAL_ATTR_TEXTURE & pmaterial->attr)
		{
			Undate_Object4D_Absolute_UV(&pchar->skin_list.elems[i], pmodel, pmaterial);
		}
	}
}

inline void Model_To_World_Character4D(CHARACTER4DV1 * pchar,
									   VECTOR4D * vpos_ptr = NULL,
									   VECTOR4D * vrot_ptr = NULL,
									   TRANSFORM_MODE trans_mode = TRANSFORM_MODE_LOCAL_TO_TRANS)
{
	if(NULL == vpos_ptr)
		vpos_ptr = &pchar->vpos;

	if(NULL == vrot_ptr)
		vrot_ptr = &pchar->vrot;

	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		Model_To_World_Object4D(&pchar->skin_list.elems[i], vpos_ptr, vrot_ptr, trans_mode);
	}
}

inline void Remove_Character4D_Backface_At_World(CHARACTER4DV1 * pchar, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		Remove_Object4D_Backface_At_World(&pchar->skin_list.elems[i], pcam);
	}
}

inline void Light_Character4D(CHARACTER4DV1 * pchar, LIGHT4DV1 * plight)
{
	assert(NULL != Light_Object4D);

	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		Light_Object4D(&pchar->skin_list.elems[i], plight, &pchar->material_list.elems[i]);
	}
}

inline void World_To_Camera_Character4D(CHARACTER4DV1 * pchar, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		World_To_Camera_Object4D(&pchar->skin_list.elems[i], pcam);
	}
}

inline bool Clip_Character4D_Gouraud_Texture(CHARACTER4DV1 * pchar, CAM4DV1 * pcam)
{
	assert(NULL != Clip_Object4D_Gouraud_Texture);

	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		assert(pchar->skin_material_index.elems[i] < pchar->material_list.length);

		if(MATERIAL_ATTR_TEXTURE
			& pchar->material_list.elems[pchar->skin_material_index.elems[i]].attr)
		{
			if(!Clip_Object4D_Gouraud_Texture(&pchar->skin_list.elems[i], pcam))
				return false;
		}
		else
		{
			if(!Clip_Object4D(&pchar->skin_list.elems[i], pcam))
				return false;
		}
	}
	return true;
}

inline void Camera_To_Perspective_Character4D(CHARACTER4DV1 * pchar, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		Camera_To_Perspective_Object4D(&pchar->skin_list.elems[i], pcam);
	}
}

inline void Perspective_To_Screen_Character4D(CHARACTER4DV1 * pchar, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		Perspective_To_Screen_Object4D(&pchar->skin_list.elems[i], pcam);
	}
}

inline void Draw_Character4D_Gouraud_Texture_ZBufferRW(CHARACTER4DV1 * pchar, CAM4DV1 * pcam)
{
	assert(NULL != Draw_Object4D_Gouraud_Texture_ZBufferRW);
	assert(NULL != Draw_Object4D_Wire_ZBufferRW);

	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		assert(pchar->skin_material_index.elems[i] < pchar->material_list.length);

		MATERIALV1 * pmaterial = &pchar->material_list.elems[pchar->skin_material_index.elems[i]];

		if(MATERIAL_ATTR_TEXTURE & pmaterial->attr)
		{
			Draw_Object4D_Gouraud_Texture_ZBufferRW(&pchar->skin_list.elems[i], pcam, pmaterial);
		}
		else
		{
			Draw_Object4D_Wire_ZBufferRW(&pchar->skin_list.elems[i], pcam);
		}
	}
}

inline void Inverse_Character4D(CHARACTER4DV1 * pchar, SKELETON4DV1 * pskel, TRANSFORM_MODE trans_mode)
{
	Build_Inverse_Matrix_Skeleton4D(pskel);

	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		Transform_Object4D_By_Matrix_List( &pchar->skin_list.elems[i],
						&pchar->ver_bone_index_list.elems[i], &pskel->imat_list,
						&pchar->nor_bone_index_list.elems[i], &pskel->imat_list_n, trans_mode);
	}
}

inline void Animate_Character4D_By_Time(CHARACTER4DV1 * pchar, SKELETON4DV1 * pskel, REAL time, TRANSFORM_MODE trans_mode)
{
	Animate_Skeleton4D_By_Time(pskel, time);

	Build_Animate_Matrix_Skeleton4D(pskel);

	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		Transform_Object4D_By_Matrix_List( &pchar->skin_list.elems[i],
						&pchar->ver_bone_index_list.elems[i], &pskel->kmat_list,
						&pchar->nor_bone_index_list.elems[i], &pskel->kmat_list_n, trans_mode);
	}
}

#endif // __T3DLIB7_H__
