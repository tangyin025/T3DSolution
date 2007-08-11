/*
 * File: T3DLIB2/t3dlib7.h
 */

#ifndef __T3DLIB7_H__
#define __T3DLIB7_H__

#include "t3dcommons.h"

typedef struct T3DLIB_API BONE4DV1_KEY_TYP
{
	REAL	time;

	union
	{
		VECTOR4D	vpos;

		VECTOR4D	vrot;
	};

} BONE4DV1_KEY, * BONE4DV1_KEY_PTR;

typedef struct T3DLIB_API ARRAYV1<BONE4DV1_KEY> BONE4DV1_KEY_ARRAYV1, * BONE4DV1_KEY_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<size_t> SIZE_T_ARRAYV1, * SIZE_T_ARRAYV1_PTR;

typedef struct T3DLIB_API BONE4DV1_TYP
{
	VECTOR4D				vpos;
	VECTOR4D				vrot;

	BONE4DV1_KEY_ARRAYV1	kpos_list;	// note : the keys need to be sort, so dont use link
	BONE4DV1_KEY_ARRAYV1	krot_list;

	size_t					parent_i;
	SIZE_T_ARRAYV1			subs;

	char					name[MS_MAX_NAME];

	_CTOR_DECLARE(BONE4DV1_TYP);
	_DTOR_DECLARE(BONE4DV1_TYP);

} BONE4DV1, * BONE4DV1_PTR;

typedef struct T3DLIB_API ARRAYV1<BONE4DV1> BONE4DV1_ARRAYV1, * BONE4DV1_ARRAYV1_PTR;

typedef struct T3DLIB_API SKELETON4DV1_TYP
{
	unsigned int			state;
	unsigned int			attr;

	BONE4DV1_ARRAYV1		bone_list;
	BONE4DV1_ARRAYV1		bone_list_t;
	size_t					root;

	char					name[MS_MAX_NAME];

	_CTOR_DECLARE(SKELETON4DV1_TYP);
	_DTOR_DECLARE(SKELETON4DV1_TYP);

} SKELETON4DV1, * SKELETON4DV1_PTR;

T3DLIB_API bool Create_Bone4D_From_MsBone(	BONE4DV1 * pbone, msBone * pmsbone,
												size_t max_bkey_size = 10,
												size_t max_bsub_size = 10);

T3DLIB_API void Destroy_Bone4D(BONE4DV1 * pbone);

T3DLIB_API bool Create_Skeleton4D_From_MsModel(	SKELETON4DV1 * pske, msModel * pmodel, const char * bone_name,
												size_t max_bone_size = 30,
												size_t max_bkey_size = 10,
												size_t max_bsub_size = 10);

T3DLIB_API void Destroy_Skeleton4D(SKELETON4DV1 * pske);

T3DLIB_API void Bone4D_Print(BONE4DV1 * pbone);

T3DLIB_API void Skeleton4D_Print(SKELETON4DV1 * pske);

#endif // __T3DLIB7_H__
