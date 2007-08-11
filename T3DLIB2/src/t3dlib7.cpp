/*
 * File: T3DLIB2/t3dlib7.cpp
 */

#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib4.h"
#include "t3dlib5.h"
#include "t3dlib6.h"
#include "t3dlib7.h"

_CTOR_IMPLEMENT(BONE4DV1_TYP);
_DTOR_IMPLEMENT_W1(BONE4DV1_TYP, Destroy_Bone4D, kpos_list.elems);

_CTOR_IMPLEMENT(SKELETON4DV1_TYP);
_DTOR_IMPLEMENT_W1(SKELETON4DV1_TYP, Destroy_Skeleton4D, bone_list.elems);

T3DLIB_API bool Create_Bone4D_From_MsBone(	BONE4DV1 * pbone, msBone * pmsbone,

												size_t max_bkey_size /*= 10*/,
												size_t max_bsub_size /*= 10*/)
{
	assert(NULL == pbone->kpos_list.elems);
	assert(NULL == pbone->krot_list.elems);
	assert(NULL == pbone->subs.elems);

	VECTOR4D_InitXYZ(&pbone->vpos, pmsbone->Position[0], pmsbone->Position[1], pmsbone->Position[2]);
	VECTOR4D_InitXYZ(&pbone->vrot, pmsbone->Rotation[0], pmsbone->Rotation[1], pmsbone->Rotation[2]);

	if(!Create_Array(&pbone->kpos_list, max_bkey_size))
		ON_ERROR_GOTO("create key pos list failed");

	int i;
	for(i = 0; i < pmsbone->nNumPositionKeys; i++)
	{
		BONE4DV1_KEY * pkey;
		if(!Append_Array(&pbone->kpos_list, &pkey))
			ON_ERROR_GOTO("append key pos failed");
		INIT_ZERO(*pkey);

		pkey->time = pmsbone->pPositionKeys[i].fTime;

		VECTOR4D_InitXYZ(&pkey->vpos,
						pmsbone->pPositionKeys[i].Position[0],
						pmsbone->pPositionKeys[i].Position[1],
						pmsbone->pPositionKeys[i].Position[2]);
	}

	if(!Create_Array(&pbone->krot_list, max_bkey_size))
		ON_ERROR_GOTO("create key rot list failed");

	for(i = 0; i < pmsbone->nNumRotationKeys; i++)
	{
		BONE4DV1_KEY * pkey;
		if(!Append_Array(&pbone->krot_list, &pkey))
			ON_ERROR_GOTO("append key rot failed");
		INIT_ZERO(*pkey);

		pkey->time = pmsbone->pRotationKeys[i].fTime;

		VECTOR4D_InitXYZ(&pkey->vpos,
						pmsbone->pRotationKeys[i].Rotation[0],
						pmsbone->pRotationKeys[i].Rotation[1],
						pmsbone->pRotationKeys[i].Rotation[2]);
	}

	if(!Create_Array(&pbone->subs, max_bsub_size))
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

											   size_t max_bone_size /*= 30*/,
											   size_t max_bkey_size /*= 10*/,
											   size_t max_bsub_size /*= 10*/)
{
	assert(NULL == pske->bone_list.elems);
	assert(NULL == pske->bone_list_t.elems);

	if(!Create_Array(&pske->bone_list, max_bone_size))
		ON_ERROR_GOTO("create bone list failed");

	BONE4DV1 * pbone;
	if(!Append_Array(&pske->bone_list, &pbone))
		ON_ERROR_GOTO("append first bone failed");
	INIT_ZERO(*pbone);

	int i, j;
	for(i = 0; i < pmodel->nNumBones; i++)
	{
		if(0 == strlen(pmodel->pBones[i].szParentName))
		{
			if(!Create_Bone4D_From_MsBone(pbone, &pmodel->pBones[i], max_bkey_size, max_bsub_size))
				goto ON_ERROR;

			pske->root = pbone - &pske->bone_list.elems[0];
			break;
		}
	}

	for(i = 0; i < (int)pske->bone_list.length; i++)
	{
		for(j = 0; j < pmodel->nNumBones; j++)
		{
			if(0 == strcmp(pske->bone_list.elems[i].name, pmodel->pBones[j].szParentName))
			{
				if(!Append_Array(&pske->bone_list, &pbone))
					ON_ERROR_GOTO("append bone failed");
				INIT_ZERO(*pbone);

				if(!Create_Bone4D_From_MsBone(pbone, &pmodel->pBones[j], max_bkey_size, max_bsub_size))
					goto ON_ERROR;

				pbone->parent_i = i;

				size_t * psub;
				if(!Append_Array(&pske->bone_list.elems[i].subs, &psub))
					ON_ERROR_GOTO("append bone sub failed");
				*psub = pbone - &pske->bone_list.elems[0];
			}
		}
	}

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
	printf("{ bone: %s, pos key: %u, rot key: %u }", pbone->name, pbone->kpos_list.length, pbone->krot_list.length);
}

static void Bone4D_Tree_Print(BONE4DV1_ARRAYV1 * pbones, size_t root, int indent)
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
