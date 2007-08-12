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

	BONE4DV1_KEY_ARRAYV1	kpos_list;	// note : the keys need to be sort, so dont use link
	BONE4DV1_KEY_ARRAYV1	krot_list;

	size_t					parent_i;
	SIZE_T_ARRAYV1			subs;

	char					name[MS_MAX_NAME];

	_CTOR_DECLARE(BONE4DV1_TYP);
	_DTOR_DECLARE(BONE4DV1_TYP);

} BONE4DV1, * BONE4DV1_PTR;

typedef struct T3DLIB_API BONE4DV1_FRAME_TYP
{
	BONE4DV1_KEY			kpos;
	BONE4DV1_KEY			krot;

} BONE4DV1_FRAME, * BONE4DV1_FRAME_PTR;

typedef struct T3DLIB_API ARRAYV1<BONE4DV1> BONE_ARRAYV1, * BONE_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<BONE4DV1_FRAME> BONE_SINGLE_ARRAYV1, * BONE_SINGLE_ARRAYV1_PTR;
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
												size_t max_key_size = 10,
												size_t max_sub_size = 10);

T3DLIB_API void Destroy_Skeleton4D(SKELETON4DV1 * pske);

T3DLIB_API void Bone4D_Print(BONE4DV1 * pbone);

T3DLIB_API void Skeleton4D_Print(SKELETON4DV1 * pske);

T3DLIB_API void Animate_Skeleton4D_By_Time(SKELETON4DV1 * pske, REAL time);

typedef struct T3DLIB_API ARRAYV1<OBJECT4DV1> OBJ_ARRAYV1, * OBJ_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<MATERIALV1> MATERIAL_ARRAYV1, * MATERIAL_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<SKELETON4DV1> SKELETON_ARRAYV1, * SKELETON_ARRAYV1_PTR;
typedef struct T3DLIB_API ARRAYV1<SIZE_T_ARRAYV1> BONE_INDEX_ARRAYV1, * BONE_INDEX_ARRAYV1_PTR;

typedef struct T3DLIB_API CHARACTER4DV1_TYP
{
	unsigned int		state;
	unsigned int		attr;

	OBJ_ARRAYV1			skin_list;
	MATERIAL_ARRAYV1	material_list;
	SKELETON_ARRAYV1	skeleton_list;
	BONE_INDEX_ARRAYV1	bone_index_list;

	VECTOR4D			vpos;
	VECTOR4D			vrot;

	unsigned char		name[MS_MAX_NAME];

	_CTOR_DECLARE(CHARACTER4DV1_TYP);
	_DTOR_DECLARE(CHARACTER4DV1_TYP);

} CHARACTER4DV1, * CHARACTER4DV1_PTR;

extern T3DLIB_API bool (* Create_Character4D_From_MsModel)(CHARACTER4DV1 * pcharacter, msModel * pmodel);
extern T3DLIB_API void (* Light_Character4D)(CHARACTER4DV1 * pcharacter, LIGHT4DV1 * plight);
extern T3DLIB_API bool (* Clip_Character4D_Gouraud_Texture)(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam);
extern T3DLIB_API void (* Draw_Character4D_Gouraud_Texture_ZBufferRW)(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam);

T3DLIB_API bool Init_T3dlib7(int bpp);

T3DLIB_API bool Create_Bone_Index_From_MsMesh(SIZE_T_ARRAYV1 * pindices, msMesh * pmesh, size_t max_index_size = 3000);

T3DLIB_API void Destroy_Bone_Index(SIZE_T_ARRAYV1 * pindex);

T3DLIB_API bool Create_Character4D_From_MsModel16(CHARACTER4DV1 * pcharacter, msModel * pmodel);

T3DLIB_API bool Create_Character4D_From_MsModel32(CHARACTER4DV1 * pcharacter, msModel * pmodel);

T3DLIB_API void Destroy_Character4D(CHARACTER4DV1 * pcharacter);

T3DLIB_API void Reset_Character4D(CHARACTER4DV1 * pcharacter);

T3DLIB_API void Undate_Character4D_Absolute_UV(CHARACTER4DV1 * pcharacter, msModel * pmodel);

T3DLIB_API void Model_To_World_Character4D(CHARACTER4DV1 * pcharacter, VECTOR4D * vpos_ptr = NULL, VECTOR4D * vrot_ptr = NULL);

T3DLIB_API void Light_Character4D16(CHARACTER4DV1 * pcharacter, LIGHT4DV1 * plight);

T3DLIB_API void Light_Character4D32(CHARACTER4DV1 * pcharacter, LIGHT4DV1 * plight);

T3DLIB_API void World_To_Camera_Character4D(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam);

T3DLIB_API void Remove_Character4D_Backface_At_World(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam);

T3DLIB_API bool Clip_Character4D_Gouraud_Texture16(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam);

T3DLIB_API bool Clip_Character4D_Gouraud_Texture32(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam);

T3DLIB_API void Camera_To_Perspective_Character4D(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam);

T3DLIB_API void Perspective_To_Screen_Character4D(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam);

T3DLIB_API void Draw_Character4D_Gouraud_Texture_ZBufferRW16(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam);

T3DLIB_API void Draw_Character4D_Gouraud_Texture_ZBufferRW32(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam);

#endif // __T3DLIB7_H__
