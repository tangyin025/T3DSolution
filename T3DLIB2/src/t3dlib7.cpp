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
_DTOR_IMPLEMENT_W1(BONE4DV1_TYP, Destroy_Bone4D, pos_key_list.elems);

_CTOR_IMPLEMENT(SKELETON4DV1_TYP);
_DTOR_IMPLEMENT_W1(SKELETON4DV1_TYP, Destroy_Skeleton4D, bone_list.elems);

T3DLIB_API bool Create_Bone4D_From_MsBone(	BONE4DV1 * pbone, msBone * pmsbone,

												size_t max_key_size /*= 10*/,
												size_t max_sub_size /*= 10*/)
{
	assert(NULL == pbone->pos_key_list.elems);
	assert(NULL == pbone->rot_key_list.elems);
	assert(NULL == pbone->subs.elems);

	VECTOR4D_InitXYZ(&pbone->vpos, pmsbone->Position[0], pmsbone->Position[1], pmsbone->Position[2]);
	VECTOR4D_InitXYZ(&pbone->vrot, pmsbone->Rotation[0], pmsbone->Rotation[1], pmsbone->Rotation[2]);

	if(!Create_Array(&pbone->pos_key_list, max_key_size))
		ON_ERROR_GOTO("create key pos list failed");

	int i;
	for(i = 0; i < pmsbone->nNumPositionKeys; i++)
	{
		BONE4DV1_KEY * pkey;
		if(!Append_Array(&pbone->pos_key_list, &pkey))
			ON_ERROR_GOTO("append key pos failed");
		INIT_ZERO(*pkey);

		pkey->time = pmsbone->pPositionKeys[i].fTime;

		VECTOR4D_InitXYZ(&pkey->vkey,
						pmsbone->pPositionKeys[i].Position[0],
						pmsbone->pPositionKeys[i].Position[1],
						pmsbone->pPositionKeys[i].Position[2]);
	}

	qsort(&pbone->pos_key_list.elems[0], pbone->pos_key_list.length,
					sizeof(pbone->pos_key_list.elems[0]), Comp_Bone4D_Key);

	if(!Create_Array(&pbone->rot_key_list, max_key_size))
		ON_ERROR_GOTO("create key rot list failed");

	for(i = 0; i < pmsbone->nNumRotationKeys; i++)
	{
		BONE4DV1_KEY * pkey;
		if(!Append_Array(&pbone->rot_key_list, &pkey))
			ON_ERROR_GOTO("append key rot failed");
		INIT_ZERO(*pkey);

		pkey->time = pmsbone->pRotationKeys[i].fTime;

		VECTOR4D_InitXYZ(&pkey->vkey,
						pmsbone->pRotationKeys[i].Rotation[0],
						pmsbone->pRotationKeys[i].Rotation[1],
						pmsbone->pRotationKeys[i].Rotation[2]);
	}

	qsort(&pbone->rot_key_list.elems[0], pbone->rot_key_list.length,
					sizeof(pbone->rot_key_list.elems[0]), Comp_Bone4D_Key);

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
	Destroy_Array(&pbone->pos_key_list);
	Destroy_Array(&pbone->rot_key_list);
	Destroy_Array(&pbone->subs);
	INIT_ZERO(*pbone);
}

T3DLIB_API bool Create_Skeleton4D_From_MsModel(SKELETON4DV1 * pske, msModel * pmodel, const char * bone_name,

											   size_t max_bone_size /*= 30*/,
											   size_t max_key_size /*= 10*/,
											   size_t max_sub_size /*= 10*/)
{
	assert(NULL == pske->bone_list.elems);

	if(!Create_Array(&pske->bone_list, max_bone_size))
		ON_ERROR_GOTO("create bone list failed");

	int i, j;
	for(i = 0; i < pmodel->nNumBones; i++)
	{
		BONE4DV1 * pbone;
		if(!Append_Array(&pske->bone_list, &pbone))
			ON_ERROR_GOTO("append first bone failed");
		INIT_ZERO(*pbone);

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

	for(i = 0; i < pske->bone_list_t.length; i++)
	{
		Destroy_Bone4D(&pske->bone_list_t.elems[i]);
	}
	Destroy_Array(&pske->bone_list_t);

	INIT_ZERO(pske);
}

T3DLIB_API void Bone4D_Print(BONE4DV1 * pbone)
{
	printf("{ bone: %s, pos key: %u, rot key: %u }", pbone->name, pbone->pos_key_list.length, pbone->rot_key_list.length);

	//int i;
	//for(i = 0; i < (int)pbone->pos_key_list.length; i++)
	//	printf(" %.2f", pbone->pos_key_list.elems[i].time);

	//for(i = 0; i < (int)pbone->rot_key_list.length; i++)
	//	printf(" %.2f", pbone->rot_key_list.elems[i].time);
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

T3DLIB_API void Animate_Skeleton4D_By_Time(SKELETON4DV1 * pske, REAL time)
{
	assert(NULL != pske->bone_list_t.elems);
	assert(pske->bone_list_t.size >= pske->bone_list.length);

	pske->bone_list_t.length = pske->bone_list.length;

	int i;
	for(i = 0; i < (int)pske->bone_list.length; i++)
	{
		INIT_ZERO(pske->bone_list_t.elems[i]);
		VECTOR4D vkey;

		VECTOR3D_Add(&pske->bone_list_t.elems[i].vpos._3D,
			&pske->bone_list.elems[i].vpos._3D, &Build_Bone4D_VKey_By_Time(&vkey, &pske->bone_list.elems[i].pos_key_list, time)->_3D);
		pske->bone_list_t.elems[i].vpos.w = 1;

		VECTOR3D_Add(&pske->bone_list_t.elems[i].vrot._3D,
			&pske->bone_list.elems[i].vrot._3D, &Build_Bone4D_VKey_By_Time(&vkey, &pske->bone_list.elems[i].rot_key_list, time)->_3D);
		pske->bone_list_t.elems[i].vrot.w = 1;
	}
}
