/*
 * File: T3DLIB2/t3dlib7.h
 */

#ifndef __T3DLIB7_H__
#define __T3DLIB7_H__

#include "t3dcommons.h"

typedef struct T3DLIB_API BONE4DV1_KEY_TYP
{
	REAL		time;
	VECTOR4D	vkey;

} BONE4DV1_KEY, * BONE4DV1_KEY_PTR;

typedef struct T3DLIB_API ARRAYV1<BONE4DV1_KEY> BONE4DV1_KEY_ARRAYV1, * BONE4DV1_KEY_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<size_t> SIZE_T_ARRAYV1, * SIZE_T_ARRAYV1_PTR;

typedef struct T3DLIB_API BONE4DV1_TYP
{
	VECTOR4D				vpos;
	VECTOR4D				vrot;

	BONE4DV1_KEY_ARRAYV1	pos_key_list;	// note : the keys need to be sort, so dont use link
	BONE4DV1_KEY_ARRAYV1	rot_key_list;

	size_t					parent_i;
	SIZE_T_ARRAYV1			subs;

	char					name[MS_MAX_NAME];

	_CTOR_DECLARE(BONE4DV1_TYP);
	_DTOR_DECLARE(BONE4DV1_TYP);

} BONE4DV1, * BONE4DV1_PTR;

typedef struct T3DLIB_API BONE4DV1_SINGLE_TYP
{
	VECTOR4D				vpos;
	VECTOR4D				vrot;

} BONE4DV1_SINGLE, * BONE4DV1_SINGLE_PTR;

typedef struct T3DLIB_API ARRAYV1<BONE4DV1> BONE_ARRAYV1, * BONE_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<BONE4DV1_SINGLE> BONE_SINGLE_ARRAYV1, * BONE_SINGLE_ARRAYV1_PTR;
//typedef struct T3DLIB_API ARRAYV1<MATRIX4X4> MAT_ARRAYV1, * MAT_ARRAYV1_PTR;

typedef struct T3DLIB_API SKELETON4DV1_TYP
{
	unsigned int		state;
	unsigned int		attr;

	BONE_ARRAYV1		bone_list;
	BONE_SINGLE_ARRAYV1	bone_list_t;
	size_t				root;

	char				name[MS_MAX_NAME];

	_CTOR_DECLARE(SKELETON4DV1_TYP);
	_DTOR_DECLARE(SKELETON4DV1_TYP);

} SKELETON4DV1, * SKELETON4DV1_PTR;

T3DLIB_API bool Create_Bone4D_From_MsBone(	BONE4DV1 * pbone, msBone * pmsbone,
												size_t max_key_size = 10,
												size_t max_sub_size = 10);

T3DLIB_API void Destroy_Bone4D(BONE4DV1 * pbone);

T3DLIB_API bool Create_Skeleton4D_From_MsModel(	SKELETON4DV1 * pske, msModel * pmodel, const char * bone_name,
												size_t max_bone_size = 30,
												size_t max_key_size = 10,
												size_t max_sub_size = 10);

T3DLIB_API void Destroy_Skeleton4D(SKELETON4DV1 * pske);

T3DLIB_API void Bone4D_Print(BONE4DV1 * pbone);

T3DLIB_API void Skeleton4D_Print(SKELETON4DV1 * pske);

T3DLIB_API void Animate_Skeleton4D_By_Time(SKELETON4DV1 * pske, REAL time);

typedef struct T3DLIB_API ARRAYV1<OBJECT4DV1> OBJ_ARRAYV1, * OBJ_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<MATERIALV1> MATERIAL_ARRAYV1, * MATERIAL_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<SKELETON4DV1> SKELETON_ARRAYV1, * SKELETON_ARRAYV1_PTR;

typedef struct T3DLIB_API CHARACTER4DV1_TYP
{
	unsigned int		state;
	unsigned int		attr;

	MATERIAL_ARRAYV1	material_list;
	SKELETON_ARRAYV1	skeleton_list;
	OBJ_ARRAYV1			skin_list;

	VECTOR4D			vpos;
	VECTOR4D			vrot;

	unsigned char		name[MS_MAX_NAME];

} CHARACTER4DV1, * CHARACTER4DV1_PTR;

#endif // __T3DLIB7_H__
