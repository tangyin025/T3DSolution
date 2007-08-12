/*
 * File: T3DLIB2/t3dlib7.cpp
 */

#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib4.h"
#include "t3dlib5.h"
#include "t3dlib6.h"
#include "t3dlib7.h"

static int __cdecl Comp_Bone4D_Key(const void * pkey0, const void * pkey1)
{
	return (int)(((BONE4DV1_KEY *)pkey0)->time - ((BONE4DV1_KEY *)pkey1)->time);
}

_CTOR_IMPLEMENT(BONE4DV1_TYP);
_DTOR_IMPLEMENT_W1(BONE4DV1_TYP, Destroy_Bone4D, kpos_list.elems);

_CTOR_IMPLEMENT(SKELETON4DV1_TYP);
_DTOR_IMPLEMENT_W1(SKELETON4DV1_TYP, Destroy_Skeleton4D, bone_list.elems);

_CTOR_IMPLEMENT(CHARACTER4DV1_TYP);
_DTOR_IMPLEMENT_W1(CHARACTER4DV1_TYP, Destroy_Character4D, skin_list.elems);

T3DLIB_API bool (* Create_Character4D_From_MsModel)(CHARACTER4DV1 * pcharacter, msModel * pmodel) = NULL;
T3DLIB_API void (* Light_Character4D)(CHARACTER4DV1 * pcharacter, LIGHT4DV1 * plight) = NULL;
T3DLIB_API bool (* Clip_Character4D_Gouraud_Texture)(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam) = NULL;
T3DLIB_API void (* Draw_Character4D_Gouraud_Texture_ZBufferRW)(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam) = NULL;

T3DLIB_API bool Init_T3dlib7(int bpp)
{
	switch(bpp)
	{
	case 16:
		Create_Character4D_From_MsModel	= Create_Character4D_From_MsModel16;
		Light_Character4D				= Light_Character4D16;
		Clip_Character4D_Gouraud_Texture	= Clip_Character4D_Gouraud_Texture16;
		Draw_Character4D_Gouraud_Texture_ZBufferRW	= Draw_Character4D_Gouraud_Texture_ZBufferRW16;
		break;

	case 32:
		Create_Character4D_From_MsModel	= Create_Character4D_From_MsModel32;
		Light_Character4D				= Light_Character4D32;
		Clip_Character4D_Gouraud_Texture	= Clip_Character4D_Gouraud_Texture32;
		Draw_Character4D_Gouraud_Texture_ZBufferRW	= Draw_Character4D_Gouraud_Texture_ZBufferRW32;
		break;

	default:
		ON_ERROR_GOTO(SFORMAT1(gbuffer, "unsupported color bpp: %d", bpp));
	}
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Create_Bone4D_From_MsBone(	BONE4DV1 * pbone, msBone * pmsbone,

												size_t max_key_size /*= 10*/,
												size_t max_sub_size /*= 10*/)
{
	assert(NULL == pbone->kpos_list.elems);
	assert(NULL == pbone->krot_list.elems);
	assert(NULL == pbone->subs.elems);

	VECTOR4D_InitXYZ(&pbone->vpos, pmsbone->Position[0], pmsbone->Position[1], pmsbone->Position[2]);
	VECTOR4D_InitXYZ(&pbone->vrot, pmsbone->Rotation[0], pmsbone->Rotation[1], pmsbone->Rotation[2]);

	if(!Create_Array(&pbone->kpos_list, max_key_size))
		ON_ERROR_GOTO("create key pos list failed");

	int i;
	for(i = 0; i < pmsbone->nNumPositionKeys; i++)
	{
		BONE4DV1_KEY * pkey;
		if(!Append_Array(&pbone->kpos_list, &pkey))
			ON_ERROR_GOTO("append key pos failed");
		INIT_ZERO(*pkey);

		pkey->time = pmsbone->pPositionKeys[i].fTime;

		VECTOR4D_InitXYZ(&pkey->vkey,
						pmsbone->pPositionKeys[i].Position[0],
						pmsbone->pPositionKeys[i].Position[1],
						pmsbone->pPositionKeys[i].Position[2]);
	}

	qsort(&pbone->kpos_list.elems[0], pbone->kpos_list.length,
					sizeof(pbone->kpos_list.elems[0]), Comp_Bone4D_Key);

	if(!Create_Array(&pbone->krot_list, max_key_size))
		ON_ERROR_GOTO("create key rot list failed");

	for(i = 0; i < pmsbone->nNumRotationKeys; i++)
	{
		BONE4DV1_KEY * pkey;
		if(!Append_Array(&pbone->krot_list, &pkey))
			ON_ERROR_GOTO("append key rot failed");
		INIT_ZERO(*pkey);

		pkey->time = pmsbone->pRotationKeys[i].fTime;

		VECTOR4D_InitXYZ(&pkey->vkey,
						pmsbone->pRotationKeys[i].Rotation[0],
						pmsbone->pRotationKeys[i].Rotation[1],
						pmsbone->pRotationKeys[i].Rotation[2]);
	}

	qsort(&pbone->krot_list.elems[0], pbone->krot_list.length,
					sizeof(pbone->krot_list.elems[0]), Comp_Bone4D_Key);

	if(!Create_Array(&pbone->subs, max_sub_size))
		ON_ERROR_GOTO("create sub list failed");

	strcpy(pbone->name, pmsbone->szName);
	assert(0 == pbone->subs.length);
	return true;

ON_ERROR:
	Destroy_Bone4D(pbone);
	return false;
}

T3DLIB_API void Destroy_Bone4D(BONE4DV1 * pbone)
{
	Destroy_Array(&pbone->kpos_list);
	Destroy_Array(&pbone->krot_list);
	Destroy_Array(&pbone->subs);
	INIT_ZERO(*pbone);
}

T3DLIB_API bool Create_Skeleton4D_From_MsModel(SKELETON4DV1 * pske, msModel * pmodel, const char * bone_name,

											   size_t max_key_size /*= 10*/,
											   size_t max_sub_size /*= 10*/)
{
	assert(NULL == pske->bone_list.elems);

	if(!Create_Array(&pske->bone_list, pmodel->nNumBones))
		ON_ERROR_GOTO("create bone list failed");

	int i, j;
	for(i = 0; i < pmodel->nNumBones; i++)
	{
		BONE4DV1 * pbone;
		if(!Append_Array(&pske->bone_list, &pbone))
			ON_ERROR_GOTO("append first bone failed");
		INIT_ZERO(*pbone);

		assert((int)pske->bone_list.size <= pmodel->nNumBones);

		Create_Bone4D_From_MsBone(pbone, &pmodel->pBones[i], max_key_size, max_sub_size);
	}

	for(i = 0; i < pmodel->nNumBones; i++)
	{
		for(j = 0; j < (int)pske->bone_list.length; j++)
		{
			BONE4DV1 * pbone = &pske->bone_list.elems[j];

			if(0 == strcmp(pmodel->pBones[i].szParentName, pbone->name))
			{
				size_t * psub;
				if(!Append_Array(&pbone->subs, &psub))
					ON_ERROR_GOTO("append bone sub failed");
				*psub = i;

				pske->bone_list.elems[i].parent_i = j;
				break;
			}
		}
	}

	if(!Create_Array(&pske->bone_list_t, pske->bone_list.size))
		ON_ERROR_GOTO("create bone_list_t failed");

	strcpy(pske->name, bone_name);
	return true;

ON_ERROR:
	Destroy_Skeleton4D(pske);
	return false;
}

T3DLIB_API void Destroy_Skeleton4D(SKELETON4DV1 * pske)
{
	size_t i;
	for(i = 0; i < pske->bone_list.length; i++)
	{
		Destroy_Bone4D(&pske->bone_list.elems[i]);
	}
	Destroy_Array(&pske->bone_list);
	Destroy_Array(&pske->bone_list_t);
	INIT_ZERO(pske);
}

T3DLIB_API void Bone4D_Print(BONE4DV1 * pbone)
{
	printf("{ bone: %s, pos key: %u, rot key: %u }", pbone->name, pbone->kpos_list.length, pbone->krot_list.length);

	//int i;
	//for(i = 0; i < (int)pbone->kpos_list.length; i++)
	//	printf(" %.2f", pbone->kpos_list.elems[i].time);

	//for(i = 0; i < (int)pbone->krot_list.length; i++)
	//	printf(" %.2f", pbone->krot_list.elems[i].time);
}

static void Bone4D_Tree_Print(BONE_ARRAYV1 * pbones, size_t root, int indent)
{
	int i;
	for(i = 0; i < indent; i++)
		printf("\t");

	Bone4D_Print(&pbones->elems[root]);
	printf("\n");

	for(i = 0; i < (int)pbones->elems[root].subs.length; i++)
	{
		Bone4D_Tree_Print(pbones, pbones->elems[root].subs.elems[i], indent + 1);
	}
}

T3DLIB_API void Skeleton4D_Print(SKELETON4DV1 * pske)
{
	Bone4D_Tree_Print(&pske->bone_list, pske->root, 0);
}

static inline VECTOR4D * Build_Vector4D_Key_By_Time(VECTOR4D * pvres, const BONE4DV1_KEY * pkey0, const BONE4DV1_KEY * pkey1, REAL time)
{
	return VECTOR4D_InitXYZ(pvres,
					LINE2D_INTERSECT(time, pkey0->time, pkey1->time, pkey0->vkey.x, pkey1->vkey.x),
					LINE2D_INTERSECT(time, pkey0->time, pkey1->time, pkey0->vkey.y, pkey1->vkey.y),
					LINE2D_INTERSECT(time, pkey0->time, pkey1->time, pkey0->vkey.z, pkey1->vkey.z));
}

static inline VECTOR4D * Build_Bone4D_VKey_By_Time(VECTOR4D * pvres, const BONE4DV1_KEY_ARRAYV1 * pkey_list, REAL time)
{
	if(pkey_list->length == 0)
	{
		return VECTOR4D_InitXYZ(pvres, 0, 0, 0);
	}

	if(pkey_list->length == 1)
	{
		return VECTOR4D_Copy(pvres, &pkey_list->elems[0].vkey);
	}

	int i;
	for(i = 1; i < (int)pkey_list->length; i++)
	{
		if(time >= pkey_list->elems[i - 1].time && time <= pkey_list->elems[i].time)
			return Build_Vector4D_Key_By_Time(pvres, &pkey_list->elems[i - 1], &pkey_list->elems[i], time);
	}

	return VECTOR4D_InitXYZ(pvres, 0, 0, 0);
}

static inline VECTOR4D * Build_Bone4D_VKey_By_Time_Position_Only(VECTOR4D * pvres, const BONE4DV1_KEY_ARRAYV1 * pkey_list, REAL time)
{
	if(pkey_list->length == 0)
	{
		return VECTOR4D_InitXYZ(pvres, 0, 0, 0);
	}

	if(pkey_list->length == 1)
	{
		return VECTOR4D_Copy(pvres, &pkey_list->elems[0].vkey);
	}

	int i;
	for(i = 1; i < (int)pkey_list->length; i++)
	{
		if(time >= pkey_list->elems[i - 1].time && time <= pkey_list->elems[i].time)
		{
			if(IS_ZERO_FLOAT(pkey_list->elems[i - 1].vkey.x)
				&& IS_ZERO_FLOAT(IS_ZERO_FLOAT(pkey_list->elems[i - 1].vkey.y))
				&& IS_ZERO_FLOAT(IS_ZERO_FLOAT(pkey_list->elems[i - 1].vkey.z))
					&& IS_ZERO_FLOAT(IS_ZERO_FLOAT(pkey_list->elems[i].vkey.x))
					&& IS_ZERO_FLOAT(IS_ZERO_FLOAT(pkey_list->elems[i].vkey.y))
					&& IS_ZERO_FLOAT(IS_ZERO_FLOAT(pkey_list->elems[i].vkey.z)))
			{
				return VECTOR4D_InitXYZ(pvres, 0, 0, 0);
			}
			else
			{
				return Build_Vector4D_Key_By_Time(pvres, &pkey_list->elems[i - 1], &pkey_list->elems[i], time);
			}
		}
	}

	return VECTOR4D_InitXYZ(pvres, 0, 0, 0);
}

T3DLIB_API void Animate_Skeleton4D_By_Time(SKELETON4DV1 * pske, REAL time)
{
	assert(NULL != pske->bone_list_t.elems);
	assert(pske->bone_list_t.size >= pske->bone_list.length);

	pske->bone_list_t.length = pske->bone_list.length;

	int i;
	for(i = 0; i < (int)pske->bone_list.length; i++)
	{
		Build_Bone4D_VKey_By_Time_Position_Only(&pske->bone_list_t.elems[i].kpos.vkey, &pske->bone_list.elems[i].kpos_list, time);
		pske->bone_list_t.elems[i].kpos.time = time;

		Build_Bone4D_VKey_By_Time(&pske->bone_list_t.elems[i].krot.vkey, &pske->bone_list.elems[i].krot_list, time);
		pske->bone_list_t.elems[i].krot.time = time;
	}
}

T3DLIB_API bool Create_Character4D_From_MsModel16(CHARACTER4DV1 * pcharacter, msModel * pmodel)
{
	assert(NULL == pcharacter->skin_list.elems);
	assert(NULL == pcharacter->material_list.elems);
	assert(NULL == pcharacter->skeleton_list.elems);

	if(!Create_Array(&pcharacter->skin_list, pmodel->nNumMeshes))
		ON_ERROR_GOTO("cannot create skin list");

	int i;
	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		msMesh * pmesh = &pmodel->pMeshes[i];

		OBJECT4DV1 * pskin;
		if(!Append_Array(&pcharacter->skin_list, &pskin))
			ON_ERROR_GOTO("cannot append skin");
		INIT_ZERO(*pskin);

		assert((int)pcharacter->skin_list.size <= pmodel->nNumMeshes);

		if(!Create_Object4D_From_MsMesh(pskin, pmesh))
			goto ON_ERROR;
	}

	if(!Create_Array(&pcharacter->material_list, pmodel->nNumMeshes))
		ON_ERROR_GOTO("cannot create material list");

	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		msMesh * pmesh = &pmodel->pMeshes[i];

		MATERIALV1 * pmaterial;
		if(!Append_Array(&pcharacter->material_list, &pmaterial))
			ON_ERROR_GOTO("cannot append material");
		INIT_ZERO(*pmaterial);

		assert((int)pcharacter->material_list.size <= pmodel->nNumMeshes);

		if(pmesh->nMaterialIndex < 0 || pmesh->nMaterialIndex > pmodel->nNumMaterials - 1)
			ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot read material for %s", pmesh->szName));

		if(!Create_Material_From_MsMaterial16(pmaterial, &pmodel->pMaterials[pmesh->nMaterialIndex]))
			goto ON_ERROR;

		strcpy(pcharacter->skin_list.elems[i].name, pmaterial->name);
	}

ON_ERROR:
	Destroy_Character4D(pcharacter);
	return false;
}

T3DLIB_API bool Create_Character4D_From_MsModel32(CHARACTER4DV1 * pcharacter, msModel * pmodel)
{
	assert(NULL == pcharacter->skin_list.elems);
	assert(NULL == pcharacter->material_list.elems);
	assert(NULL == pcharacter->skeleton_list.elems);

	if(!Create_Array(&pcharacter->skin_list, pmodel->nNumMeshes))
		ON_ERROR_GOTO("cannot create skin list");

	int i;
	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		msMesh * pmesh = &pmodel->pMeshes[i];

		OBJECT4DV1 * pskin;
		if(!Append_Array(&pcharacter->skin_list, &pskin))
			ON_ERROR_GOTO("cannot append skin");
		INIT_ZERO(*pskin);

		assert((int)pcharacter->skin_list.size <= pmodel->nNumMeshes);

		if(!Create_Object4D_From_MsMesh(pskin, pmesh))
			goto ON_ERROR;
	}

	if(!Create_Array(&pcharacter->material_list, pmodel->nNumMeshes))
		ON_ERROR_GOTO("cannot create material list");

	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		msMesh * pmesh = &pmodel->pMeshes[i];

		MATERIALV1 * pmaterial;
		if(!Append_Array(&pcharacter->material_list, &pmaterial))
			ON_ERROR_GOTO("cannot append material");
		INIT_ZERO(*pmaterial);

		assert((int)pcharacter->material_list.size <= pmodel->nNumMeshes);

		if(pmesh->nMaterialIndex < 0 || pmesh->nMaterialIndex > pmodel->nNumMaterials - 1)
			ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot read material for %s", pmesh->szName));

		if(!Create_Material_From_MsMaterial32(pmaterial, &pmodel->pMaterials[pmesh->nMaterialIndex]))
			goto ON_ERROR;

		strcpy(pcharacter->skin_list.elems[i].name, pmaterial->name);
	}

	return true;

ON_ERROR:
	Destroy_Character4D(pcharacter);
	return false;
}

T3DLIB_API void Destroy_Character4D(CHARACTER4DV1 * pcharacter)
{
	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		Destroy_Object4D(&pcharacter->skin_list.elems[i]);
	}
	Destroy_Array(&pcharacter->skin_list);

	for(i = 0; i < (int)pcharacter->material_list.length; i++)
	{
		Destroy_Material(&pcharacter->material_list.elems[i]);
	}
	Destroy_Array(&pcharacter->material_list);

	for(i = 0; i < (int)pcharacter->skeleton_list.length; i++)
	{
		Destroy_Skeleton4D(&pcharacter->skeleton_list.elems[i]);
	}
	Destroy_Array(&pcharacter->skeleton_list);

	INIT_ZERO(*pcharacter);
}

T3DLIB_API void Reset_Character4D(CHARACTER4DV1 * pcharacter)
{
	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		Reset_Object4D(&pcharacter->skin_list.elems[i]);
	}
}

T3DLIB_API void Model_To_World_Character4D(CHARACTER4DV1 * pcharacter, VECTOR4D * vpos_ptr /*= NULL*/, VECTOR4D * vrot_ptr /*= NULL*/)
{
	if(NULL == vpos_ptr)
		vpos_ptr = &pcharacter->vpos;

	if(NULL == vrot_ptr)
		vrot_ptr = &pcharacter->vrot;

	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		Model_To_World_Object4D(&pcharacter->skin_list.elems[i], vpos_ptr, vrot_ptr);
	}
}

T3DLIB_API void Remove_Character4D_Backface_At_World(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		Remove_Object4D_Backface_At_World(&pcharacter->skin_list.elems[i], pcam);
	}
}

T3DLIB_API void Light_Character4D16(CHARACTER4DV1 * pcharacter, LIGHT4DV1 * plight)
{
	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		Light_Object4D16(&pcharacter->skin_list.elems[i], plight, &pcharacter->material_list.elems[i]);
	}
}

T3DLIB_API void Light_Character4D32(CHARACTER4DV1 * pcharacter, LIGHT4DV1 * plight)
{
	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		Light_Object4D32(&pcharacter->skin_list.elems[i], plight, &pcharacter->material_list.elems[i]);
	}
}

T3DLIB_API void World_To_Camera_Character4D(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		World_To_Camera_Object4D(&pcharacter->skin_list.elems[i], pcam);
	}
}

T3DLIB_API bool Clip_Character4D_Gouraud_Texture16(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		if(MATERIAL_ATTR_TEXTURE | pcharacter->material_list.elems[i].attr)
		{
			if(!Clip_Object4D_Gouraud_Texture16(&pcharacter->skin_list.elems[i], pcam))
				return false;
		}
		else
		{
			if(!Clip_Object4D(&pcharacter->skin_list.elems[i], pcam))
				return false;
		}
	}

	return true;
}

T3DLIB_API bool Clip_Character4D_Gouraud_Texture32(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		if(MATERIAL_ATTR_TEXTURE | pcharacter->material_list.elems[i].attr)
		{
			if(!Clip_Object4D_Gouraud_Texture32(&pcharacter->skin_list.elems[i], pcam))
				return false;
		}
		else
		{
			if(!Clip_Object4D(&pcharacter->skin_list.elems[i], pcam))
				return false;
		}
	}

	return true;
}

T3DLIB_API void Camera_To_Perspective_Character4D(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		Camera_To_Perspective_Object4D(&pcharacter->skin_list.elems[i], pcam);
	}
}

T3DLIB_API void Perspective_To_Screen_Character4D(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		Perspective_To_Screen_Object4D(&pcharacter->skin_list.elems[i], pcam);
	}
}

T3DLIB_API void Draw_Character4D_Gouraud_Texture_ZBufferRW16(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		if(MATERIAL_ATTR_TEXTURE | pcharacter->material_list.elems[i].attr)
		{
			Draw_Object4D_Gouraud_Texture_ZBufferRW16(&pcharacter->skin_list.elems[i], pcam, &pcharacter->material_list.elems[i]);
		}
		else
		{
			Draw_Object4D_Wire_ZBufferRW16(&pcharacter->skin_list.elems[i], pcam);
		}
	}
}

T3DLIB_API void Draw_Character4D_Gouraud_Texture_ZBufferRW32(CHARACTER4DV1 * pcharacter, CAM4DV1 * pcam)
{
	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		if(MATERIAL_ATTR_TEXTURE | pcharacter->material_list.elems[i].attr)
		{
			Draw_Object4D_Gouraud_Texture_ZBufferRW32(&pcharacter->skin_list.elems[i], pcam, &pcharacter->material_list.elems[i]);
		}
		else
		{
			Draw_Object4D_Wire_ZBufferRW32(&pcharacter->skin_list.elems[i], pcam);
		}
	}
}
