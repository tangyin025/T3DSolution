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

T3DLIB_API bool Create_Bone4D_From_MsBone(	BONE4DV1 * pbone, msBone * pmsbone,

												size_t max_key_size /*= 10*/,
												size_t max_sub_size /*= 10*/)
{
	assert(NULL == pbone->kpos_list.elems);
	assert(NULL == pbone->krot_list.elems);
	assert(NULL == pbone->subs.elems);

	VECTOR4D_InitXYZ( &pbone->vpos,
					pmsbone->Position[0],
					pmsbone->Position[1],
					- pmsbone->Position[2]); // !!!

	VECTOR4D_InitXYZ(&pbone->vrot,
					- pmsbone->Rotation[0],
					- pmsbone->Rotation[1],
					pmsbone->Rotation[2]); // !!!

	if(!Create_Array(&pbone->kpos_list, pmsbone->nNumPositionKeys))
		ON_ERROR_GOTO("create key pos list failed");

	int i;
	for(i = 0; i < pmsbone->nNumPositionKeys; i++)
	{
		BONE4DV1_KEY * pkey;
		if(!Append_Array(&pbone->kpos_list, &pkey))
			ON_ERROR_GOTO("append key pos failed");
		INIT_ZERO(*pkey);

		assert((int)pbone->kpos_list.size <= pmsbone->nNumPositionKeys);

		pkey->time = pmsbone->pPositionKeys[i].fTime;

		VECTOR4D_InitXYZ(&pkey->vkey,
						pmsbone->pPositionKeys[i].Position[0],
						pmsbone->pPositionKeys[i].Position[1],
						- pmsbone->pPositionKeys[i].Position[2]); // !!!
	}

	qsort(&pbone->kpos_list.elems[0],
					pbone->kpos_list.length, sizeof(pbone->kpos_list.elems[0]), Comp_Bone4D_Key);

	if(!Create_Array(&pbone->krot_list, pmsbone->nNumRotationKeys))
		ON_ERROR_GOTO("create key rot list failed");

	for(i = 0; i < pmsbone->nNumRotationKeys; i++)
	{
		BONE4DV1_KEY * pkey;
		if(!Append_Array(&pbone->krot_list, &pkey))
			ON_ERROR_GOTO("append key rot failed");
		INIT_ZERO(*pkey);

		assert((int)pbone->krot_list.size <= pmsbone->nNumRotationKeys);

		pkey->time = pmsbone->pRotationKeys[i].fTime;

		VECTOR4D_InitXYZ(&pkey->vkey,
						- pmsbone->pRotationKeys[i].Rotation[0],
						- pmsbone->pRotationKeys[i].Rotation[1],
						pmsbone->pRotationKeys[i].Rotation[2]); // !!!
	}

	qsort(&pbone->krot_list.elems[0],
					pbone->krot_list.length, sizeof(pbone->krot_list.elems[0]), Comp_Bone4D_Key);

	if(!Create_Array(&pbone->subs, max_sub_size))
		ON_ERROR_GOTO("create sub list failed");

	strcpy(pbone->name, pmsbone->szName);
	return true;

ON_ERROR:
	Destroy_Bone4D(pbone);
	return false;
	UNREFERENCED_PARAMETER(max_key_size);
}

T3DLIB_API void Destroy_Bone4D(BONE4DV1 * pbone)
{
	Destroy_Array(&pbone->kpos_list);
	Destroy_Array(&pbone->krot_list);
	Destroy_Array(&pbone->subs);
	INIT_ZERO(*pbone);
}

T3DLIB_API bool Create_Skeleton4D_From_MsModel(SKELETON4DV1 * pske, msModel * pmodel,

											   size_t max_key_size /*= 10*/,
											   size_t max_sub_size /*= 10*/)
{
	assert(NULL == pske->bone_list.elems);
	assert(NULL == pske->bone_list_k.elems);
	assert(NULL == pske->imat_list.elems);
	assert(NULL == pske->imat_list_n.elems);
	assert(NULL == pske->kmat_list.elems);
	assert(NULL == pske->kmat_list_n.elems);

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

		if(!Create_Bone4D_From_MsBone(pbone, &pmodel->pBones[i], max_key_size, max_sub_size))
			ON_ERROR_GOTO("load bone from msBone failed");
	}

	pske->root = (size_t)-1;

	for(i = 0; i < pmodel->nNumBones; i++)
	{
		if(0 == strlen(pmodel->pBones[i].szParentName))
		{
			if(-1 != pske->root)
				ON_ERROR_GOTO("more than one root find");

			pske->root = i;
		}
		else
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
	}

	if(-1 == pske->root)
		ON_ERROR_GOTO("cannot find root node");

	if(!Create_Array(&pske->bone_list_k, pske->bone_list.size))
		ON_ERROR_GOTO("create bone_list_k failed");

	if(!Create_Array(&pske->imat_list, pske->bone_list.size))
		ON_ERROR_GOTO("create imat_list failed");

	if(!Create_Array(&pske->imat_list_n, pske->bone_list.size))
		ON_ERROR_GOTO("create imat_list_n failed");

	if(!Create_Array(&pske->kmat_list, pske->bone_list.size))
		ON_ERROR_GOTO("create kmat_list failed");

	if(!Create_Array(&pske->kmat_list_n, pske->bone_list.size))
		ON_ERROR_GOTO("create kmat_list_n failed");

	Animate_Skeleton4D_By_Time(pske, 1);

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

	Destroy_Array(&pske->bone_list_k);
	Destroy_Array(&pske->imat_list);
	Destroy_Array(&pske->imat_list_n);
	Destroy_Array(&pske->kmat_list);
	Destroy_Array(&pske->kmat_list_n);

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
	assert(root < pbones->length);

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
	assert(time >= pkey0->time && time <= pkey1->time);

	return VECTOR4D_InitXYZ(pvres,
					LINE2D_INTERSECT(time, pkey0->time, pkey1->time, pkey0->vkey.x, pkey1->vkey.x),
					LINE2D_INTERSECT(time, pkey0->time, pkey1->time, pkey0->vkey.y, pkey1->vkey.y),
					LINE2D_INTERSECT(time, pkey0->time, pkey1->time, pkey0->vkey.z, pkey1->vkey.z)); // !!!
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
	assert(NULL != pske->bone_list_k.elems);
	assert(pske->bone_list_k.size >= pske->bone_list.length);

	pske->bone_list_k.length = pske->bone_list.length;

	int i;
	for(i = 0; i < (int)pske->bone_list.length; i++)
	{
		Build_Bone4D_VKey_By_Time_Position_Only(&pske->bone_list_k.elems[i].vpos, &pske->bone_list.elems[i].kpos_list, time);

		Build_Bone4D_VKey_By_Time(&pske->bone_list_k.elems[i].vrot, &pske->bone_list.elems[i].krot_list, time);
	}

	pske->time = time;
}

static void Build_Reverse_Mat_Skeleton4D_Inside(SKELETON4DV1 * pske, size_t root, const MATRIX4X4 * pmat, const MATRIX4X4 * pmat_n)
{
	assert(root <= pske->imat_list.length);

	VECTOR4D vpos;
	VECTOR4D_InitXYZ( &vpos,
					-pske->bone_list.elems[root].vpos.x,
					-pske->bone_list.elems[root].vpos.y,
					-pske->bone_list.elems[root].vpos.z);

	VECTOR4D vrot;
	VECTOR4D_InitXYZ( &vrot,
					-pske->bone_list.elems[root].vrot.x,
					-pske->bone_list.elems[root].vrot.y,
					-pske->bone_list.elems[root].vrot.z);

	MATRIX4X4 mmov, mrot;
	Build_Mat_PositionXYZ(&mmov, &vpos);
	Build_Mat_RotationZYX(&mrot, &vrot);

	MATRIX4X4 mres_n;
	MATRIX4X4_Copy(&mres_n, &mrot);
	Mat_Mul_4X4(&pske->imat_list_n.elems[root], pmat_n, &mres_n); // !!!

	MATRIX4X4 mres;
	Mat_Mul_4X4(&mres, &mmov, &mrot);
	Mat_Mul_4X4(&pske->imat_list.elems[root], pmat, &mres); // !!!

	int i;
	for(i = 0; i < (int)pske->bone_list.elems[root].subs.length; i++)
	{
		Build_Reverse_Mat_Skeleton4D_Inside( pske,
						pske->bone_list.elems[root].subs.elems[i], &pske->imat_list.elems[root], &pske->imat_list_n.elems[root]);
	}
}

T3DLIB_API void Build_Reverse_Mat_Skeleton4D(SKELETON4DV1 * pske)
{
	assert(pske->imat_list.size >= pske->bone_list.length);
	assert(pske->imat_list_n.size >= pske->bone_list.length);

	pske->imat_list.length = pske->bone_list.length;
	memset(pske->imat_list.elems, 0, pske->imat_list.length * sizeof(pske->imat_list.elems[0]));

	pske->imat_list_n.length = pske->bone_list.length;
	memset(pske->imat_list_n.elems, 0, pske->imat_list_n.length * sizeof(pske->imat_list_n.elems[0]));

	Build_Reverse_Mat_Skeleton4D_Inside(pske, pske->root, &MATRIX4X4::IDENTITY, &MATRIX4X4::IDENTITY);
}

static void Build_Animate_Mat_Skeleton4D_Inside(SKELETON4DV1 * pske, size_t root, const MATRIX4X4 * pmat, const MATRIX4X4 * pmat_n)
{
	assert(root <= pske->kmat_list.length);

	MATRIX4X4 mmov, mrot;
	Build_Mat_RotationXYZ(&mrot, &pske->bone_list_k.elems[root].vrot);
	Build_Mat_PositionXYZ(&mmov, &pske->bone_list_k.elems[root].vpos);

	MATRIX4X4 mkey_n;
	MATRIX4X4_Copy(&mkey_n, &mrot);

	MATRIX4X4 mkey;
	Mat_Mul_4X4(&mkey, &mrot, &mmov);

	Build_Mat_RotationXYZ(&mrot, &pske->bone_list.elems[root].vrot);
	Build_Mat_PositionXYZ(&mmov, &pske->bone_list.elems[root].vpos);

	MATRIX4X4 mloc_n;
	MATRIX4X4_Copy(&mloc_n, &mrot);

	MATRIX4X4 mloc;
	Mat_Mul_4X4(&mloc, &mrot, &mmov);

	MATRIX4X4 mres_n;
	Mat_Mul_4X4(&mres_n, &mkey_n, &mloc_n);
	Mat_Mul_4X4( &pske->kmat_list_n.elems[root], &mres_n, pmat_n); // !!!

	MATRIX4X4 mres;
	Mat_Mul_4X4(&mres, &mkey, &mloc);
	Mat_Mul_4X4( &pske->kmat_list.elems[root], &mres, pmat); // !!!

	int i;
	for(i = 0; i < (int)pske->bone_list.elems[root].subs.length; i++)
	{
		Build_Animate_Mat_Skeleton4D_Inside( pske,
						pske->bone_list.elems[root].subs.elems[i], &pske->kmat_list.elems[root], &pske->kmat_list_n.elems[root]);
	}
}

T3DLIB_API void Build_Animate_Mat_Skeleton4D(SKELETON4DV1 * pske)
{
	assert(pske->kmat_list.size >= pske->bone_list.length);
	assert(pske->kmat_list_n.size >= pske->bone_list.length);

	pske->kmat_list.length = pske->bone_list.length;
	memset(pske->kmat_list.elems, 0, pske->kmat_list.length * sizeof(pske->kmat_list.elems[0]));

	pske->kmat_list_n.length = pske->bone_list.length;
	memset(pske->kmat_list_n.elems, 0, pske->kmat_list_n.length * sizeof(pske->kmat_list_n.elems[0]));

	assert(pske->bone_list_k.length == pske->bone_list.length);

	Build_Animate_Mat_Skeleton4D_Inside(pske, pske->root, &MATRIX4X4::IDENTITY, &MATRIX4X4::IDENTITY);
}

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

T3DLIB_API bool Create_Ver_Bone_Index_From_MsMesh(SIZE_T_ARRAYV1 * pbone_index, msMesh * pmesh,

												  size_t max_index_size /*= 3000*/)
{
	assert(NULL == pbone_index->elems);

	if(!Create_Array(pbone_index, pmesh->nNumVertices))
		ON_ERROR_GOTO("cannot create bone index");

	int i;
	for(i = 0; i < pmesh->nNumVertices; i++)
	{
		size_t * pindex;
		if(!Append_Array(pbone_index, &pindex))
			ON_ERROR_GOTO("append bone index failed");

		assert((int)pbone_index->size <= pmesh->nNumVertices);

		*pindex = pmesh->pVertices[i].nBoneIndex;
	}

	return true;

ON_ERROR:
	Destroy_Ver_Bone_Index(pbone_index);
	return false;
	UNREFERENCED_PARAMETER(max_index_size);
}

T3DLIB_API void Destroy_Ver_Bone_Index(SIZE_T_ARRAYV1 * pbone_index)
{
	Destroy_Array(pbone_index);
	INIT_ZERO(*pbone_index);
}

static inline bool Append_Nor_Bone_Index(NOR_ARRAYV1 * pnor_list,
										 SIZE_T_ARRAYV1 * pbone_index, VECTOR4D * pvnor, size_t bone_i, size_t * pres_i)
{
	assert(pnor_list->length == pbone_index->length);

	size_t i;
	for(i = 0; i < pnor_list->length; i++)
	{
		if(VECTOR3D_Equal(&pnor_list->elems[i]._3D, &pvnor->_3D))
		{
			if(-1 == pbone_index->elems[i])
			{
				pbone_index->elems[i] = bone_i;
				*pres_i = i;
				return true;
			}

			if(bone_i == pbone_index->elems[i])
			{
				*pres_i = i;
				return true;
			}
		}
	}

	VECTOR4D * pnor;
	if(!Append_Array(pnor_list, &pnor))
		return false;

	VECTOR4D_Copy(pnor, pvnor);

	size_t * pindex;
	if(!Append_Array(pbone_index, &pindex))
		return false;

	*pindex = bone_i;
	*pres_i = pnor_list->length - 1;

	return true;
}

T3DLIB_API bool Create_Nor_Bone_Index_And_Rebuild_By_Object4D(SIZE_T_ARRAYV1 * pnor_bone_index,
															  SIZE_T_ARRAYV1 * pver_bone_index,
															  OBJECT4DV1 * pobj,

															  size_t max_index_size /*= 3000*/)
{
	assert(NULL == pnor_bone_index->elems);
	assert(pver_bone_index->length == pobj->ver_list.length);

	if(!Create_Array(pnor_bone_index, pobj->nor_list.size))
		ON_ERROR_GOTO("cannot create bone index");

	pnor_bone_index->length = pobj->nor_list.length;
	memset(pnor_bone_index->elems, -1, pnor_bone_index->length * sizeof(pnor_bone_index->elems[0]));

	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		size_t nor_i;
		if(!Append_Nor_Bone_Index(&pobj->nor_list, pnor_bone_index,
						&pobj->nor_list.elems[pobj->tri_list.elems[i].n0_i],
						pver_bone_index->elems[pobj->tri_list.elems[i].v0_i], &nor_i))
			ON_ERROR_GOTO("append nor bone index failed");

		pobj->tri_list.elems[i].n0_i = (int)nor_i;

		if(!Append_Nor_Bone_Index(&pobj->nor_list, pnor_bone_index,
						&pobj->nor_list.elems[pobj->tri_list.elems[i].n1_i],
						pver_bone_index->elems[pobj->tri_list.elems[i].v1_i], &nor_i))
			ON_ERROR_GOTO("append nor bone index failed");

		pobj->tri_list.elems[i].n1_i = (int)nor_i;

		if(!Append_Nor_Bone_Index(&pobj->nor_list, pnor_bone_index,
						&pobj->nor_list.elems[pobj->tri_list.elems[i].n2_i],
						pver_bone_index->elems[pobj->tri_list.elems[i].v2_i], &nor_i))
			ON_ERROR_GOTO("append nor bone index failed");

		pobj->tri_list.elems[i].n2_i = (int)nor_i;
	}

	return true;

ON_ERROR:
	Destroy_Nor_Bone_Index(pnor_bone_index);
	return false;

	UNREFERENCED_PARAMETER(max_index_size);
}

T3DLIB_API void Destroy_Nor_Bone_Index(SIZE_T_ARRAYV1 * pbone_index)
{
	Destroy_Array(pbone_index);
	INIT_ZERO(*pbone_index);
}

T3DLIB_API bool Create_Character4D_From_MsModel16(CHARACTER4DV1 * pcharacter, msModel * pmodel)
{
	assert(NULL == pcharacter->skin_list.elems);
	assert(NULL == pcharacter->skin_ver_bone_index_list.elems);
	assert(NULL == pcharacter->skin_nor_bone_index_list.elems);
	assert(NULL == pcharacter->material_list.elems);

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

	if(!Create_Array(&pcharacter->skin_ver_bone_index_list, pmodel->nNumMeshes))
		ON_ERROR_GOTO("cannot create skin ver bone list");

	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		SIZE_T_ARRAYV1 * pindices;
		if(!Append_Array(&pcharacter->skin_ver_bone_index_list, &pindices))
			ON_ERROR_GOTO("append bone indices failed");
		INIT_ZERO(*pindices);

		assert((int)pcharacter->skin_ver_bone_index_list.size <= pmodel->nNumMeshes);

		if(!Create_Ver_Bone_Index_From_MsMesh(pindices, &pmodel->pMeshes[i]))
			goto ON_ERROR;
	}

	if(!Create_Array(&pcharacter->skin_nor_bone_index_list, pmodel->nNumMeshes))
		ON_ERROR_GOTO("cannot create skin nor bone list");

	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		SIZE_T_ARRAYV1 * pindices;
		if(!Append_Array(&pcharacter->skin_nor_bone_index_list, &pindices))
			ON_ERROR_GOTO("append nor bone indices failed");
		INIT_ZERO(*pindices);

		assert((int)pcharacter->skin_nor_bone_index_list.size <= pmodel->nNumMeshes);

		if(!Create_Nor_Bone_Index_And_Rebuild_By_Object4D(pindices,
						&pcharacter->skin_ver_bone_index_list.elems[i], &pcharacter->skin_list.elems[i]))
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

	return true;

ON_ERROR:
	Destroy_Character4D(pcharacter);
	return false;

	UNREFERENCED_PARAMETER(pcharacter);
	UNREFERENCED_PARAMETER(pmodel);
}

T3DLIB_API bool Create_Character4D_From_MsModel32(CHARACTER4DV1 * pcharacter, msModel * pmodel)
{
	assert(NULL == pcharacter->skin_list.elems);
	assert(NULL == pcharacter->skin_ver_bone_index_list.elems);
	assert(NULL == pcharacter->skin_nor_bone_index_list.elems);
	assert(NULL == pcharacter->material_list.elems);

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

	if(!Create_Array(&pcharacter->skin_ver_bone_index_list, pmodel->nNumMeshes))
		ON_ERROR_GOTO("cannot create skin ver bone list");

	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		SIZE_T_ARRAYV1 * pindices;
		if(!Append_Array(&pcharacter->skin_ver_bone_index_list, &pindices))
			ON_ERROR_GOTO("append bone indices failed");
		INIT_ZERO(*pindices);

		assert((int)pcharacter->skin_ver_bone_index_list.size <= pmodel->nNumMeshes);

		if(!Create_Ver_Bone_Index_From_MsMesh(pindices, &pmodel->pMeshes[i]))
			goto ON_ERROR;
	}

	if(!Create_Array(&pcharacter->skin_nor_bone_index_list, pmodel->nNumMeshes))
		ON_ERROR_GOTO("cannot create skin nor bone list");

	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		SIZE_T_ARRAYV1 * pindices;
		if(!Append_Array(&pcharacter->skin_nor_bone_index_list, &pindices))
			ON_ERROR_GOTO("append nor bone indices failed");
		INIT_ZERO(*pindices);

		assert((int)pcharacter->skin_nor_bone_index_list.size <= pmodel->nNumMeshes);

		if(!Create_Nor_Bone_Index_And_Rebuild_By_Object4D(pindices,
						&pcharacter->skin_ver_bone_index_list.elems[i], &pcharacter->skin_list.elems[i]))
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

	for(i = 0; i < (int)pcharacter->skin_ver_bone_index_list.length; i++)
	{
		Destroy_Ver_Bone_Index(&pcharacter->skin_ver_bone_index_list.elems[i]);
	}
	Destroy_Array(&pcharacter->skin_ver_bone_index_list);

	for(i = 0; i < (int)pcharacter->skin_nor_bone_index_list.length; i++)
	{
		Destroy_Nor_Bone_Index(&pcharacter->skin_nor_bone_index_list.elems[i]);
	}
	Destroy_Array(&pcharacter->skin_nor_bone_index_list);

	for(i = 0; i < (int)pcharacter->material_list.length; i++)
	{
		Destroy_Material(&pcharacter->material_list.elems[i]);
	}
	Destroy_Array(&pcharacter->material_list);

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

T3DLIB_API void Undate_Character4D_Absolute_UV(CHARACTER4DV1 * pcharacter, msModel * pmodel)
{
	assert(pcharacter->skin_list.length == pcharacter->material_list.length);

	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		if(MATERIAL_ATTR_TEXTURE & pcharacter->material_list.elems[i].attr)
		{
			Undate_Object4D_Absolute_UV(&pcharacter->skin_list.elems[i], pmodel, &pcharacter->material_list.elems[i]);
		}
	}
}

T3DLIB_API void Model_To_World_Character4D(CHARACTER4DV1 * pcharacter,

										   VECTOR4D * vpos_ptr /*= NULL*/,
										   VECTOR4D * vrot_ptr /*= NULL*/,
										   TRANSFORM_MODE trans_mode /*= TRANSFORM_MODE_LOCAL_TO_TRANS*/)
{
	if(NULL == vpos_ptr)
		vpos_ptr = &pcharacter->vpos;

	if(NULL == vrot_ptr)
		vrot_ptr = &pcharacter->vrot;

	int i;
	for(i = 0; i < (int)pcharacter->skin_list.length; i++)
	{
		Model_To_World_Object4D(&pcharacter->skin_list.elems[i], vpos_ptr, vrot_ptr, trans_mode);
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
		if(MATERIAL_ATTR_TEXTURE & pcharacter->material_list.elems[i].attr)
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
		if(MATERIAL_ATTR_TEXTURE & pcharacter->material_list.elems[i].attr)
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
		if(MATERIAL_ATTR_TEXTURE & pcharacter->material_list.elems[i].attr)
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
		if(MATERIAL_ATTR_TEXTURE & pcharacter->material_list.elems[i].attr)
		{
			Draw_Object4D_Gouraud_Texture_ZBufferRW32(&pcharacter->skin_list.elems[i], pcam, &pcharacter->material_list.elems[i]);
		}
		else
		{
			Draw_Object4D_Wire_ZBufferRW32(&pcharacter->skin_list.elems[i], pcam);
		}
	}
}

T3DLIB_API void Transform_Object4D_With_Bone_Index(OBJECT4DV1 * pobj,
												   SIZE_T_ARRAYV1 * pver_bone_index, MAT_ARRAYV1 * pmat_list,
												   SIZE_T_ARRAYV1 * pnor_bone_index, MAT_ARRAYV1 * pmat_list_n,

												   TRANSFORM_MODE trans_mode /*= TRANSFORM_MODE_LOCAL_TO_TRANS*/)
{
	assert(pver_bone_index->length == pobj->ver_list.length);
	assert(pnor_bone_index->length == pobj->nor_list.length);

	assert(pobj->ver_list_t.size >= pobj->ver_list.length);
	assert(pobj->nor_list_t.size >= pobj->nor_list.length);

	VECTOR4D vres;

	int i;
	switch(trans_mode)
	{
	case TRANSFORM_MODE_LOCAL_ONLY:
		for(i = 0; i < (int)pobj->ver_list.length; i++)
		{
			assert(pver_bone_index->elems[i] < pmat_list->length);

			VECTOR4D_Copy(&pobj->ver_list.elems[i]._4D,
							Mat_Mul_VECTOR4D_4X4(&vres, &pobj->ver_list.elems[i]._4D, &pmat_list->elems[pver_bone_index->elems[i]]));
		}

		for(i = 0; i < (int)pobj->nor_list.length; i++)
		{
			VECTOR4D_Copy(&pobj->nor_list.elems[i],
							Mat_Mul_VECTOR4D_4X4(&vres, &pobj->nor_list.elems[i], &pmat_list_n->elems[pnor_bone_index->elems[i]]));
		}
		break;

	case TRANSFORM_MODE_TRANS_ONLY:
		for(i = 0; i < (int)pobj->ver_list_t.length; i++)
		{
			assert(pver_bone_index->elems[i] < pmat_list->length);

			VECTOR4D_Copy(&pobj->ver_list_t.elems[i]._4D,
							Mat_Mul_VECTOR4D_4X4(&vres, &pobj->ver_list_t.elems[i]._4D, &pmat_list->elems[pver_bone_index->elems[i]]));
		}

		for(i = 0; i < (int)pobj->nor_list_t.length; i++)
		{
			VECTOR4D_Copy(&pobj->nor_list_t.elems[i],
							Mat_Mul_VECTOR4D_4X4(&vres, &pobj->nor_list_t.elems[i], &pmat_list_n->elems[pnor_bone_index->elems[i]]));
		}
		break;

	case TRANSFORM_MODE_LOCAL_TO_TRANS:
		pobj->ver_list_t.length = pobj->ver_list.length;
		for(i = 0; i < (int)pobj->ver_list_t.length; i++)
		{
			assert(pver_bone_index->elems[i] < pmat_list->length);

			memcpy(&pobj->ver_list_t.elems[i], &pobj->ver_list.elems[i], sizeof(pobj->ver_list.elems[0])); // !!!

			Mat_Mul_VECTOR4D_4X4(&pobj->ver_list_t.elems[i]._4D, &pobj->ver_list.elems[i]._4D, &pmat_list->elems[pver_bone_index->elems[i]]);
		}

		pobj->nor_list_t.length = pobj->nor_list.length;
		for(i = 0; i < (int)pobj->nor_list_t.length; i++)
		{
			Mat_Mul_VECTOR4D_4X4(&pobj->nor_list_t.elems[i], &pobj->nor_list.elems[i], &pmat_list_n->elems[pnor_bone_index->elems[i]]);
		}
		break;

	default:
		assert(0); break;
	}
}
