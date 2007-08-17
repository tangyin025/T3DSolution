/*
 * File: T3DLIB2/t3dlib7.cpp
 */

#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib4.h"
#include "t3dlib5.h"
#include "t3dlib6.h"
#include "t3dlib7.h"

T3DLIB_API void Transform_Object4D_By_Matrix_List(OBJECT4DV1 *		pobj,
												  SIZE_T_ARRAYV1 *	pmat_index,
												  MAT_ARRAYV1 *		pmat_list,
												  SIZE_T_ARRAYV1 *	pmat_index_n,
												  MAT_ARRAYV1 *		pmat_list_n,
												  TRANSFORM_MODE	trans_mode)
{
	VECTOR4D vres;

	int i;
	switch(trans_mode)
	{
	case TRANSFORM_MODE_LOCAL_ONLY:
		assert(pobj->ver_list.length == pmat_index->length);
		assert(pobj->nor_list.length == pmat_index_n->length);

		for(i = 0; i < (int)pobj->ver_list.length; i++)
		{
			VECTOR4D_Copy( &pobj->ver_list.elems[i]._4D,
							Mat_Mul_VECTOR4D_4X4( &vres,
											&pobj->ver_list.elems[i]._4D, &pmat_list->elems[pmat_index->elems[i]]));
		}

		for(i = 0; i < (int)pobj->nor_list.length; i++)
		{
			VECTOR4D_Copy( &pobj->nor_list.elems[i],
							Mat_Mul_VECTOR4D_4X4( &vres,
											&pobj->nor_list.elems[i], &pmat_list_n->elems[pmat_index_n->elems[i]]));
		}
		break;

	case TRANSFORM_MODE_TRANS_ONLY:
		assert(pobj->ver_list_t.length == pmat_index->length);
		assert(pobj->nor_list_t.length == pmat_index_n->length);

		for(i = 0; i < (int)pobj->ver_list_t.length; i++)
		{
			VECTOR4D_Copy( &pobj->ver_list_t.elems[i]._4D,
							Mat_Mul_VECTOR4D_4X4( &vres,
											&pobj->ver_list_t.elems[i]._4D, &pmat_list->elems[pmat_index->elems[i]]));
		}

		for(i = 0; i < (int)pobj->nor_list_t.length; i++)
		{
			VECTOR4D_Copy( &pobj->nor_list_t.elems[i],
							Mat_Mul_VECTOR4D_4X4( &vres,
											&pobj->nor_list_t.elems[i], &pmat_list_n->elems[pmat_index_n->elems[i]]));
		}
		break;

	case TRANSFORM_MODE_LOCAL_TO_TRANS:
		assert(pobj->ver_list_t.size >= pobj->ver_list.length);
		assert(pobj->nor_list_t.size >= pobj->nor_list.length);

		assert(pobj->ver_list.length == pmat_index->length);
		assert(pobj->nor_list.length == pmat_index_n->length);

		pobj->ver_list_t.length = pobj->ver_list.length;
		for(i = 0; i < (int)pobj->ver_list.length; i++)
		{
			memcpy(&pobj->ver_list_t.elems[i], &pobj->ver_list.elems[i], sizeof(pobj->ver_list_t.elems[0])); // !!!

							Mat_Mul_VECTOR4D_4X4( &pobj->ver_list_t.elems[i]._4D,
											&pobj->ver_list.elems[i]._4D, &pmat_list->elems[pmat_index->elems[i]]);
		}

		pobj->nor_list_t.length = pobj->nor_list.length;
		for(i = 0; i < (int)pobj->nor_list.length; i++)
		{
							Mat_Mul_VECTOR4D_4X4( &pobj->nor_list_t.elems[i],
											&pobj->nor_list.elems[i], &pmat_list_n->elems[pmat_index_n->elems[i]]);
		}
		break;

	default:
		assert(0); break;
	}
}

_CTOR_IMPLEMENT(BONE4DV1_TYP);
_DTOR_IMPLEMENT_W1(BONE4DV1_TYP, Destroy_Bone4D, kpos_list.elems);

_CTOR_IMPLEMENT(SKELETON4DV1_TYP);
_DTOR_IMPLEMENT_W1(SKELETON4DV1_TYP, Destroy_Skeleton4D, bone_list.elems);

static int __cdecl Comp_Bone4D_Key(const void * pkey0, const void * pkey1)
{
	return (int)(((BONE4DV1_KEY *)pkey0)->time - ((BONE4DV1_KEY *)pkey1)->time);
}

T3DLIB_API bool Create_Bone4D_From_MsBone(BONE4DV1 * pbone, msBone * pmsBone, size_t max_sub_size /*= 10*/)
{
	assert(NULL == pbone->kpos_list.elems);
	assert(NULL == pbone->krot_list.elems);
	assert(NULL == pbone->subs.elems);

	VECTOR4D_InitXYZ( &pbone->vpos,
					  pmsBone->Position[0],
					  pmsBone->Position[1],
					- pmsBone->Position[2]); // !!!

	VECTOR4D_InitXYZ( &pbone->vrot,
					- pmsBone->Rotation[0],
					- pmsBone->Rotation[1],
					  pmsBone->Rotation[2]); // !!!

	VECTOR4D_InitXYZ(&pbone->vpos_k, 0, 0, 0);

	VECTOR4D_InitXYZ(&pbone->vrot_k, 0, 0, 0);

	if(!Create_Array(&pbone->kpos_list, pmsBone->nNumPositionKeys))
		ON_ERROR_GOTO("create pos key list failed");

	int i;
	for(i = 0; i < pmsBone->nNumPositionKeys; i++)
	{
		BONE4DV1_KEY * pkey;
		if(!Append_Array(&pbone->kpos_list, &pkey))
			ON_ERROR_GOTO("append pos key failed");

		assert((int)pbone->kpos_list.size <= pmsBone->nNumPositionKeys);

		pkey->time = (REAL)pmsBone->pPositionKeys[i].fTime;

		VECTOR4D_InitXYZ(&pkey->vkey,
						  pmsBone->pPositionKeys[i].Position[0],
						  pmsBone->pPositionKeys[i].Position[1],
						- pmsBone->pPositionKeys[i].Position[2]); // !!!
	}

	qsort(&pbone->kpos_list.elems[0],
					pbone->kpos_list.length, sizeof(pbone->kpos_list.elems[0]), Comp_Bone4D_Key);

	if(!Create_Array(&pbone->krot_list, pmsBone->nNumRotationKeys))
		ON_ERROR_GOTO("create rot key list failed");

	for(i = 0; i < pmsBone->nNumRotationKeys; i++)
	{
		BONE4DV1_KEY * pkey;
		if(!Append_Array(&pbone->krot_list, &pkey))
			ON_ERROR_GOTO("append rot key failed");

		assert((int)pbone->krot_list.size <= pmsBone->nNumRotationKeys);

		pkey->time = (REAL)pmsBone->pRotationKeys[i].fTime;

		VECTOR4D_InitXYZ(&pkey->vkey,
						- pmsBone->pRotationKeys[i].Rotation[0],
						- pmsBone->pRotationKeys[i].Rotation[1],
						  pmsBone->pRotationKeys[i].Rotation[2]); // !!!
	}

	qsort(&pbone->krot_list.elems[0],
					pbone->krot_list.length, sizeof(pbone->krot_list.elems[0]), Comp_Bone4D_Key);

	if(!Create_Array(&pbone->subs, max_sub_size))
		ON_ERROR_GOTO("create sub index list failed");

	strcpy(pbone->name, pmsBone->szName);

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

T3DLIB_API bool Create_Skeleton4D_From_MsModel(SKELETON4DV1 * pskel, msModel * pmodel,

											   size_t max_sub_size	/*= 10*/,
											   size_t max_root_size	/*= 10*/)
{
	assert(NULL == pskel->bone_list.elems);
	assert(NULL == pskel->imat_list.elems);
	assert(NULL == pskel->imat_list_n.elems);
	assert(NULL == pskel->kmat_list.elems);
	assert(NULL == pskel->kmat_list_n.elems);
	assert(NULL == pskel->roots.elems);

	if(!Create_Array(&pskel->bone_list, pmodel->nNumBones))
		ON_ERROR_GOTO("create bone list failed");

	if(!Create_Array(&pskel->roots, max_root_size))
		ON_ERROR_GOTO("create root list failed");

	int i;
	for(i = 0; i < pmodel->nNumBones; i++)
	{
		BONE4DV1 * pbone;
		if(!Append_Array(&pskel->bone_list, &pbone))
			ON_ERROR_GOTO("append bone failed");

		INIT_ZERO(*pbone);

		assert((int)pskel->bone_list.size <= pmodel->nNumBones);

		if(!Create_Bone4D_From_MsBone(pbone, &pmodel->pBones[i], max_sub_size))
			ON_ERROR_GOTO("create bone failed");
	}

	for(i = 0; i < pmodel->nNumBones; i++)
	{
		if(0 == strlen(pmodel->pBones[i].szParentName))
		{
			size_t * pindex;
			if(!Append_Array(&pskel->roots, &pindex))
				ON_ERROR_GOTO("append root failed");

			*pindex = i;

			pskel->bone_list.elems[i].parent_i = (size_t)-1;
		}
		else
		{
			int j;
			for(j = 0; j < (int)pskel->bone_list.length; j++)
			{
				if(0 == strcmp(pmodel->pBones[i].szParentName,
								pskel->bone_list.elems[j].name))
				{
					size_t * pindex;
					if(!Append_Array(&pskel->bone_list.elems[j].subs, &pindex))
						ON_ERROR_GOTO("append bone sub failed");

					*pindex = i;

					pskel->bone_list.elems[i].parent_i = j;
					break;
				}
			}

			if(j >= (int)pskel->bone_list.length)
				ON_ERROR_GOTO("cannot find parent bone");
		}
	}

	if(0 == pskel->roots.length)
		ON_ERROR_GOTO("cannot find root bone");

	if(!Create_Array(&pskel->imat_list, pskel->bone_list.length))
		ON_ERROR_GOTO("create inverse matrix list failed");

	if(!Create_Array(&pskel->imat_list_n, pskel->bone_list.length))
		ON_ERROR_GOTO("create inverse matrix_n list failed");

	if(!Create_Array(&pskel->kmat_list, pskel->bone_list.length))
		ON_ERROR_GOTO("create key matrix list failed");

	if(!Create_Array(&pskel->kmat_list_n, pskel->bone_list.length))
		ON_ERROR_GOTO("create key matrix_n list failed");

	return true;

ON_ERROR:
	Destroy_Skeleton4D(pskel);
	return false;
}

T3DLIB_API void Destroy_Skeleton4D(SKELETON4DV1 * pskel)
{
	int i;
	for(i = 0; i < (int)pskel->bone_list.length; i++)
	{
		Destroy_Bone4D(&pskel->bone_list.elems[i]);
	}
	Destroy_Array(&pskel->bone_list);

	Destroy_Array(&pskel->imat_list);
	Destroy_Array(&pskel->imat_list_n);
	Destroy_Array(&pskel->kmat_list);
	Destroy_Array(&pskel->kmat_list_n);
	Destroy_Array(&pskel->roots);
}

static inline VECTOR4D * Build_Vector4D_Key_By_Time(VECTOR4D * pvres, const BONE4DV1_KEY * pkey0, const BONE4DV1_KEY * pkey1, REAL time)
{
	assert(time >= pkey0->time && time <= pkey1->time);

	return VECTOR4D_InitXYZ(pvres,
					LINE2D_INTERSECT(time, pkey0->time, pkey1->time, pkey0->vkey.x, pkey1->vkey.x),
					LINE2D_INTERSECT(time, pkey0->time, pkey1->time, pkey0->vkey.y, pkey1->vkey.y),
					LINE2D_INTERSECT(time, pkey0->time, pkey1->time, pkey0->vkey.z, pkey1->vkey.z));
}

static inline VECTOR4D * Build_Bone4D_VKey_By_Time_Position_Only(VECTOR4D * pvres, const BONE4D_KEY_ARRAYV1 * pkey_list, REAL time)
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

static inline VECTOR4D * Build_Bone4D_VKey_By_Time(VECTOR4D * pvres, const BONE4D_KEY_ARRAYV1 * pkey_list, REAL time)
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
			{
				return Build_Vector4D_Key_By_Time(pvres, &pkey_list->elems[i - 1], &pkey_list->elems[i], time);
			}
		}
	}

	return VECTOR4D_InitXYZ(pvres, 0, 0, 0);
}

T3DLIB_API void Animate_Skeleton4D_By_Time(SKELETON4DV1 * pskel, REAL time)
{
	int i;
	for(i = 0; i < (int)pskel->bone_list.length; i++)
	{
		Build_Bone4D_VKey_By_Time_Position_Only(
						&pskel->bone_list.elems[i].vpos_k, &pskel->bone_list.elems[i].kpos_list, time);

		Build_Bone4D_VKey_By_Time(
						&pskel->bone_list.elems[i].vrot_k, &pskel->bone_list.elems[i].krot_list, time);
	}
}

static void Build_Inverse_Matrix_Skeleton4D_Inside(SKELETON4DV1 * pskel, size_t root, const MATRIX4X4 * pmat, const MATRIX4X4 * pmat_n)
{
	assert(root <= pskel->imat_list.length);
	assert(root <= pskel->imat_list_n.length);

	VECTOR4D vpos;
	VECTOR4D_InitXYZ( &vpos,
					- pskel->bone_list.elems[root].vpos.x,
					- pskel->bone_list.elems[root].vpos.y,
					- pskel->bone_list.elems[root].vpos.z); // !!!

	VECTOR4D vrot;
	VECTOR4D_InitXYZ( &vrot,
					- pskel->bone_list.elems[root].vrot.x,
					- pskel->bone_list.elems[root].vrot.y,
					- pskel->bone_list.elems[root].vrot.z); // !!!

	MATRIX4X4 mmov, mrot;
	Build_Mat_PositionXYZ(&mmov, &vpos);
	Build_Mat_RotationZYX(&mrot, &vrot);

	MATRIX4X4 mres;
	Mat_Mul_4X4(&pskel->imat_list.elems[root], pmat, Mat_Mul_4X4(&mres, &mmov, &mrot)); // !!!

	Mat_Mul_4X4(&pskel->imat_list_n.elems[root], pmat_n, &mrot); // !!!

	int i;
	for(i = 0; i < (int)pskel->bone_list.elems[root].subs.length; i++)
	{
		Build_Inverse_Matrix_Skeleton4D_Inside( pskel,
						pskel->bone_list.elems[root].subs.elems[i], &pskel->imat_list.elems[root], &pskel->imat_list_n.elems[root]);
	}
}

T3DLIB_API void Build_Inverse_Matrix_Skeleton4D(SKELETON4DV1 * pskel)
{
	assert(pskel->imat_list.size >= pskel->bone_list.length);
	assert(pskel->imat_list_n.size >= pskel->bone_list.length);

	pskel->imat_list.length = pskel->bone_list.length;
	pskel->imat_list_n.length = pskel->bone_list.length;

	int i;
	for(i = 0; i < (int)pskel->roots.length; i++)
	{
		Build_Inverse_Matrix_Skeleton4D_Inside(pskel, pskel->roots.elems[i], &MATRIX4X4::IDENTITY, &MATRIX4X4::IDENTITY);
	}
}

static void Build_Animate_Matrix_Skeleton4D_Inside(SKELETON4DV1 * pskel, size_t root, const MATRIX4X4 * pmat, const MATRIX4X4 * pmat_n)
{
	assert(root <= pskel->kmat_list.length);
	assert(root <= pskel->kmat_list_n.length);

	MATRIX4X4 mmov, mrot;
	MATRIX4X4 mkey, mkey_n;
	Mat_Mul_4X4( &mkey,
					Build_Mat_RotationXYZ(&mrot, &pskel->bone_list.elems[root].vrot_k),
					Build_Mat_PositionXYZ(&mmov, &pskel->bone_list.elems[root].vpos_k));

	MATRIX4X4_Copy(&mkey_n, &mrot);

	MATRIX4X4 mloc, mloc_n;
	Mat_Mul_4X4( &mloc,
					Build_Mat_RotationXYZ(&mrot, &pskel->bone_list.elems[root].vrot),
					Build_Mat_PositionXYZ(&mmov, &pskel->bone_list.elems[root].vpos));

	MATRIX4X4_Copy(&mloc_n, &mrot);

	MATRIX4X4 mres;
	Mat_Mul_4X4(&pskel->kmat_list.elems[root], Mat_Mul_4X4(&mres, &mkey, &mloc), pmat); // !!!

	Mat_Mul_4X4(&pskel->kmat_list_n.elems[root], Mat_Mul_4X4(&mres, &mkey_n, &mloc_n), pmat_n); // !!!

	int i;
	for(i = 0; i < (int)pskel->bone_list.elems[root].subs.length; i++)
	{
		Build_Animate_Matrix_Skeleton4D_Inside( pskel,
						pskel->bone_list.elems[root].subs.elems[i], &pskel->kmat_list.elems[root], &pskel->kmat_list_n.elems[root]);
	}
}

T3DLIB_API void Build_Animate_Matrix_Skeleton4D(SKELETON4DV1 * pskel)
{
	assert(pskel->kmat_list.size >= pskel->bone_list.length);
	assert(pskel->kmat_list_n.size >= pskel->bone_list.length);

	pskel->kmat_list.length = pskel->bone_list.length;
	pskel->kmat_list_n.length = pskel->bone_list.length;

	int i;
	for(i = 0; i < (int)pskel->roots.length; i++)
	{
		Build_Animate_Matrix_Skeleton4D_Inside(pskel, pskel->roots.elems[i], &MATRIX4X4::IDENTITY, &MATRIX4X4::IDENTITY);
	}
}

_CTOR_IMPLEMENT(CHARACTER4DV1_TYP);
_DTOR_IMPLEMENT_W1(CHARACTER4DV1_TYP, Destroy_Character4D, skin_list.elems);

static void Destroy_Ver_Bone_Index(SIZE_T_ARRAYV1 * pver_bone_index)
{
	Destroy_Array(pver_bone_index);
}

static bool Create_Ver_Bone_Index_From_MsMesh(SIZE_T_ARRAYV1 * pver_bone_index, msMesh * pmesh)
{
	assert(NULL == pver_bone_index->elems);

	if(!Create_Array(pver_bone_index, pmesh->nNumVertices))
		ON_ERROR_GOTO("create ver bone index failed");

	int i;
	for(i = 0; i < pmesh->nNumVertices; i++)
	{
		size_t * pindex;
		if(!Append_Array(pver_bone_index, &pindex))
			ON_ERROR_GOTO("append ver bone index failed");

		assert((int)pver_bone_index->size <= pmesh->nNumVertices);

		*pindex = pmesh->pVertices[i].nBoneIndex;
	}

	return true;

ON_ERROR:
	Destroy_Ver_Bone_Index(pver_bone_index);
	return false;
}

static void Destroy_Nor_Bone_Index(SIZE_T_ARRAYV1 * pnor_bone_index)
{
	Destroy_Array(pnor_bone_index);
}

static bool Inser_Nor_And_Nor_Bone_Index(NOR_ARRAYV1 * pnor_list, SIZE_T_ARRAYV1 * pnor_bone_index, VECTOR4D * pnor, size_t bone_i, size_t * pres_i)
{
	assert(pnor_list->length == pnor_bone_index->length);

	size_t i;
	for(i = 0; i < pnor_list->length; i++)
	{
		if(VECTOR3D_Equal(&pnor_list->elems[i]._3D, &pnor->_3D))
		{
			if(-1 == pnor_bone_index->elems[i])
			{
				pnor_bone_index->elems[i] = bone_i;
				*pres_i = i;
				return true;
			}

			if(bone_i == pnor_bone_index->elems[i])
			{
				*pres_i = i;
				return true;
			}
		}
	}

	VECTOR4D * pnor_new;
	if(!Append_Array(pnor_list, &pnor_new))
		return false;

	VECTOR4D_Copy(pnor_new, pnor);

	size_t * pindex;
	if(!Append_Array(pnor_bone_index, &pindex))
		return false;

	*pindex = bone_i;

	*pres_i = pnor_list->length - 1;

	return true;
}

static bool Create_Nor_Bone_Index_From_Object4D(SIZE_T_ARRAYV1 * pnor_bone_index, OBJECT4DV1 * pobj, SIZE_T_ARRAYV1 * pver_bone_index)
{
	assert(NULL == pnor_bone_index->elems);

	if(!Create_Array(pnor_bone_index, pobj->nor_list.size))
		ON_ERROR_GOTO("create nor bone index failed");

	pnor_bone_index->length = pobj->nor_list.length;
	memset(pnor_bone_index->elems, -1, pnor_bone_index->length * sizeof(pnor_bone_index->elems[0]));

	int i;
	for(i = 0; i < (int)pobj->tri_list.length; i++)
	{
		size_t nor_i;

		if(!Inser_Nor_And_Nor_Bone_Index( &pobj->nor_list, pnor_bone_index,
						&pobj->nor_list.elems[pobj->tri_list.elems[i].n0_i], pver_bone_index->elems[pobj->tri_list.elems[i].v0_i], &nor_i))
			ON_ERROR_GOTO("insert nor and nor bone index failed");

		pobj->tri_list.elems[i].n0_i = (int)nor_i;

		if(!Inser_Nor_And_Nor_Bone_Index( &pobj->nor_list, pnor_bone_index,
						&pobj->nor_list.elems[pobj->tri_list.elems[i].n1_i], pver_bone_index->elems[pobj->tri_list.elems[i].v1_i], &nor_i))
			ON_ERROR_GOTO("insert nor and nor bone index failed");

		pobj->tri_list.elems[i].n1_i = (int)nor_i;

		if(!Inser_Nor_And_Nor_Bone_Index( &pobj->nor_list, pnor_bone_index,
						&pobj->nor_list.elems[pobj->tri_list.elems[i].n1_i], pver_bone_index->elems[pobj->tri_list.elems[i].v1_i], &nor_i))
			ON_ERROR_GOTO("insert nor and nor bone index failed");

		pobj->tri_list.elems[i].n1_i = (int)nor_i;
	}

	return true;

ON_ERROR:
	Destroy_Nor_Bone_Index(pnor_bone_index);
	return false;
	UNREFERENCED_PARAMETER(pnor_bone_index);
	UNREFERENCED_PARAMETER(pobj);
	UNREFERENCED_PARAMETER(pver_bone_index);
}

T3DLIB_API bool Create_Character4D_From_MsModel(CHARACTER4DV1 * pchar, msModel * pmodel, size_t max_skel_size /*= 10*/)
{
	assert(NULL == pchar->skin_list.elems);
	assert(NULL == pchar->material_list.elems);
	assert(NULL == pchar->skin_material_index.elems);
	assert(NULL == pchar->skel_list.elems);
	assert(NULL == pchar->ver_bone_index_list.elems);
	assert(NULL == pchar->nor_bone_index_list.elems);

	assert(NULL != Create_Material_From_MsMaterial);

	if(!Create_Array(&pchar->skin_list, pmodel->nNumMeshes))
		ON_ERROR_GOTO("create skin list failed");

	int i;
	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		msMesh * pmesh = &pmodel->pMeshes[i];

		OBJECT4DV1 * pskin;
		if(!Append_Array(&pchar->skin_list, &pskin))
			ON_ERROR_GOTO("append skin failed");

		INIT_ZERO(*pskin);

		assert((int)pchar->skel_list.size <= pmodel->nNumMeshes);

		if(!Create_Object4D_From_MsMesh(pskin, pmesh))
			goto ON_ERROR;
	}

	if(!Create_Array(&pchar->material_list, pmodel->nNumMaterials))
		ON_ERROR_GOTO("create material list failed");

	for(i = 0; i < pmodel->nNumMaterials; i++)
	{
		msMaterial * pmsMaterial = &pmodel->pMaterials[i];

		MATERIALV1 * pmat;
		if(!Append_Array(&pchar->material_list, &pmat))
			ON_ERROR_GOTO("append material failed");

		INIT_ZERO(*pmat);

		assert((int)pchar->material_list.size <= pmodel->nNumMaterials);

		if(!Create_Material_From_MsMaterial(pmat, pmsMaterial))
			goto ON_ERROR;
	}

	if(!Create_Array(&pchar->skin_material_index, pmodel->nNumMeshes))
		ON_ERROR_GOTO("create skin material index failed");

	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		size_t * pindex;
		if(!Append_Array(&pchar->skin_material_index, &pindex))
			ON_ERROR_GOTO("append skin material index failed");

		assert((int)pchar->skin_material_index.size <= pmodel->nNumMeshes);

		*pindex = pmodel->pMeshes[i].nMaterialIndex;
	}

	if(!Create_Array(&pchar->ver_bone_index_list, pmodel->nNumMeshes))
		ON_ERROR_GOTO("create ver bone index list failed");

	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		msMesh * pmesh = &pmodel->pMeshes[i];

		SIZE_T_ARRAYV1 * pver_bone_index;
		if(!Append_Array(&pchar->ver_bone_index_list, &pver_bone_index))
			ON_ERROR_GOTO("append ver bone index failed");

		INIT_ZERO(*pver_bone_index);

		assert((int)pchar->ver_bone_index_list.size <= pmodel->nNumMeshes);

		if(!Create_Ver_Bone_Index_From_MsMesh(pver_bone_index, pmesh))
			goto ON_ERROR;
	}

	if(!Create_Array(&pchar->nor_bone_index_list, pmodel->nNumMeshes))
		ON_ERROR_GOTO("create nor bone index list failed");

	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		SIZE_T_ARRAYV1 * pnor_bone_index;
		if(!Append_Array(&pchar->nor_bone_index_list, &pnor_bone_index))
			ON_ERROR_GOTO("append nor bone index failed");

		INIT_ZERO(*pnor_bone_index);

		assert((int)pchar->nor_bone_index_list.size <= pmodel->nNumMeshes);

		if(!Create_Nor_Bone_Index_From_Object4D(pnor_bone_index,
						&pchar->skin_list.elems[i], &pchar->ver_bone_index_list.elems[i]))
			goto ON_ERROR;
	}

	if(!Create_Array(&pchar->skel_list, max_skel_size))
		ON_ERROR_GOTO("create skeleton list failed");

	if(pmodel->nNumBones > 0)
	{
		SKELETON4DV1 * pskel;
		if(!Append_Array(&pchar->skel_list, &pskel))
			ON_ERROR_GOTO("append skeleton fialed");

		INIT_ZERO(*pskel);

		assert(1 == pchar->skel_list.length);

		if(!Create_Skeleton4D_From_MsModel(pskel, pmodel))
			goto ON_ERROR;
	}

	VECTOR4D_InitXYZ(&pchar->vpos, 0, 0, 0);

	VECTOR4D_InitXYZ(&pchar->vrot, 0, 0, 0);

	return true;

ON_ERROR:
	Destroy_Character4D(pchar);
	return false;
}

T3DLIB_API void Destroy_Character4D(CHARACTER4DV1 * pchar)
{
	int i;
	for(i = 0; i < (int)pchar->skin_list.length; i++)
	{
		Destroy_Object4D(&pchar->skin_list.elems[i]);
	}
	Destroy_Array(&pchar->skin_list);

	for(i = 0; i < (int)pchar->material_list.length; i++)
	{
		Destroy_Material(&pchar->material_list.elems[i]);
	}
	Destroy_Array(&pchar->material_list);

	Destroy_Array(&pchar->skin_material_index);

	for(i = 0; i < (int)pchar->skel_list.length; i++)
	{
		Destroy_Skeleton4D(&pchar->skel_list.elems[i]);
	}
	Destroy_Array(&pchar->skel_list);

	for(i = 0; i < (int)pchar->ver_bone_index_list.length; i++)
	{
		Destroy_Ver_Bone_Index(&pchar->ver_bone_index_list.elems[i]);
	}
	Destroy_Array(&pchar->ver_bone_index_list);

	for(i = 0; i < (int)pchar->nor_bone_index_list.length; i++)
	{
		Destroy_Nor_Bone_Index(&pchar->nor_bone_index_list.elems[i]);
	}
	Destroy_Array(&pchar->nor_bone_index_list);
}
