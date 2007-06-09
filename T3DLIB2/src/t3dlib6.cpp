/*
 * File: T3DLIB2/t3dlib6.cpp
 */

#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib4.h"
#include "t3dlib5.h"
#include "t3dlib6.h"

_CTOR_IMPLEMENT(MATERIALV1_TYP);
_DTOR_IMPLEMENT_W1(MATERIALV1_TYP, Destroy_Material, texture.pbuffer);

_CTOR_IMPLEMENT(OBJECT4DV1_TYP);
_DTOR_IMPLEMENT_W1(OBJECT4DV1_TYP, Destroy_Object4D, tri_list.elems);

T3DLIB_API bool (* Create_Material_From_MsModel)(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name) = NULL;
T3DLIB_API void (* Draw_Object4D)(SURFACEV1 * psurface, OBJECT4DV1 * pobj, CAM4DV1 * pcam) = NULL;

T3DLIB_API bool Init_T3dlib6(int bpp)
{
	switch(bpp)
	{
	case 16:
		Create_Material_From_MsModel	= Create_Material_From_MsModel16;
		Draw_Object4D					= Draw_Object4D16;
		break;

	case 32:
		Create_Material_From_MsModel	= Create_Material_From_MsModel32;
		Draw_Object4D					= Draw_Object4D32;
		break;

	default:
		ON_ERROR_GOTO(SFORMAT1(gbuffer, "unsupported color bip: %d", bpp));
	}
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Create_Material_From_MsModel16(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name)
{
	assert(pmaterial->texture.pbuffer == NULL);

	BITMAPV1 btmp;
	INIT_ZERO(btmp);
	int i;
	for(i = 0; i < pmodel->nNumMaterials; i++)
	{
		msMaterial * pmat = &pmodel->pMaterials[i];
		if(0 == strcmp(pmat->szName, material_name))
		{
			pmaterial->c_ambi = _RGB16BIT(	(int)(pmat->Ambient[0] * (MAX_COLOR_INTENSITY16 - 1)),
											(int)(pmat->Ambient[1] * (MAX_COLOR_INTENSITY16G - 1)),
											(int)(pmat->Ambient[2] * (MAX_COLOR_INTENSITY16 - 1)));

			pmaterial->c_diff = _RGB16BIT(	(int)(pmat->Diffuse[0] * (MAX_COLOR_INTENSITY16 - 1)),
											(int)(pmat->Diffuse[1] * (MAX_COLOR_INTENSITY16G - 1)),
											(int)(pmat->Diffuse[2] * (MAX_COLOR_INTENSITY16 - 1)));

			pmaterial->c_spec = _RGB16BIT(	(int)(pmat->Specular[0] * (MAX_COLOR_INTENSITY16 - 1)),
											(int)(pmat->Specular[1] * (MAX_COLOR_INTENSITY16G - 1)),
											(int)(pmat->Specular[2] * (MAX_COLOR_INTENSITY16 - 1)));

			pmaterial->c_emis = _RGB16BIT(	(int)(pmat->Emissive[0] * (MAX_COLOR_INTENSITY16 - 1)),
											(int)(pmat->Emissive[1] * (MAX_COLOR_INTENSITY16G - 1)),
											(int)(pmat->Emissive[2] * (MAX_COLOR_INTENSITY16 - 1)));

			if(0 != strcmp(pmat->szDiffuseTexture, ""))
			{
				if(!Create_Bitmap_From_File(&btmp, pmat->szDiffuseTexture))
					ON_ERROR_GOTO(SFORMAT1(gbuffer, "load bitmap %s failed", pmat->szDiffuseTexture));

				if(!Create_Image16(&pmaterial->texture,
						btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
					ON_ERROR_GOTO("create image failed");

				if(!Load_Image_From_Bitmap16(&pmaterial->texture, &btmp, 0, 0,
						btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
					ON_ERROR_GOTO("load image failed");

				Destroy_Bitmap(&btmp);
			}
			return true;
		}
	}
	ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot find material %s", material_name));

ON_ERROR:
	Destroy_Image(&pmaterial->texture);
	Destroy_Bitmap(&btmp);
	return false;
}

T3DLIB_API bool Create_Material_From_MsModel32(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name)
{
	assert(pmaterial->texture.pbuffer == NULL);

	BITMAPV1 btmp;
	INIT_ZERO(btmp);
	int i;
	for(i = 0; i < pmodel->nNumMaterials; i++)
	{
		msMaterial * pmat = &pmodel->pMaterials[i];
		if(0 == strcmp(pmat->szName, material_name))
		{
			pmaterial->c_ambi = _RGB32BIT(	(int)(pmat->Ambient[0] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Ambient[1] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Ambient[2] * (MAX_COLOR_INTENSITY32 - 1)));

			pmaterial->c_diff = _RGB32BIT(	(int)(pmat->Diffuse[0] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Diffuse[1] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Diffuse[2] * (MAX_COLOR_INTENSITY32 - 1)));

			pmaterial->c_spec = _RGB32BIT(	(int)(pmat->Specular[0] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Specular[1] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Specular[2] * (MAX_COLOR_INTENSITY32 - 1)));

			pmaterial->c_emis = _RGB32BIT(	(int)(pmat->Emissive[0] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Emissive[1] * (MAX_COLOR_INTENSITY32 - 1)),
											(int)(pmat->Emissive[2] * (MAX_COLOR_INTENSITY32 - 1)));

			if(0 != strcmp(pmat->szDiffuseTexture, ""))
			{
				if(!Create_Bitmap_From_File(&btmp, pmat->szDiffuseTexture))
					ON_ERROR_GOTO(SFORMAT1(gbuffer, "load bitmap %s failed", pmat->szDiffuseTexture));

				if(!Create_Image32(&pmaterial->texture,
						btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
					ON_ERROR_GOTO("create image failed");

				if(!Load_Image_From_Bitmap32(&pmaterial->texture, &btmp, 0, 0,
						btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
					ON_ERROR_GOTO("load image failed");

				Destroy_Bitmap(&btmp);
			}
			return true;
		}
	}
	ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot find material %s", material_name));

ON_ERROR:
	Destroy_Image(&pmaterial->texture);
	Destroy_Bitmap(&btmp);
	return false;
}

T3DLIB_API void Destroy_Material(MATERIALV1 * pmaterial)
{
	Destroy_Image(&pmaterial->texture);
	INIT_ZERO(*pmaterial);
}

T3DLIB_API bool Create_Object4D_From_MsModel(OBJECT4DV1 * pobj, msModel * pmodel, const char * mesh_name,
											 size_t max_tri_size /*= 1000*/,
											 size_t max_ver_size /*= 3000*/,
											 size_t max_nor_size /*= 3000*/)
{
	assert(pobj->tri_list.elems == NULL);
	assert(pobj->ver_list.elems == NULL);
	assert(pobj->ver_list_t.elems == NULL);
	assert(pobj->nor_list.elems == NULL);
	assert(pobj->nor_list_t.elems == NULL);

	int i, j;
	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		msMesh * pmesh = &pmodel->pMeshes[i];
		if(0 == strcmp(pmesh->szName, mesh_name))
		{
			if(!Create_Array(&pobj->tri_list, max_tri_size))
				ON_ERROR_GOTO("create triangle list failed");

			for(j = 0; j < pmesh->nNumTriangles; j++)
			{
				TRIANGLEV1 * ptri;
				if(!Append_Array(&pobj->tri_list, &ptri))
					ON_ERROR_GOTO("append triangle list failed");

				ptri->v0_i = pmesh->pTriangles[i].nVertexIndices[0];
				ptri->v1_i = pmesh->pTriangles[i].nVertexIndices[1];
				ptri->v2_i = pmesh->pTriangles[i].nVertexIndices[2];

				ptri->n0_i = pmesh->pTriangles[i].nNormalIndices[0];
				ptri->n1_i = pmesh->pTriangles[i].nNormalIndices[1];
				ptri->n2_i = pmesh->pTriangles[i].nNormalIndices[2];
			}

			if(!Create_Array(&pobj->ver_list, max_ver_size))
				ON_ERROR_GOTO("create vertex list failed");

			for(j = 0; j < pmesh->nNumVertices; j++)
			{
				VERTEXV1T * pver;
				if(!Append_Array(&pobj->ver_list, &pver))
					ON_ERROR_GOTO("append vertex list failed");

				pver->x = (REAL)pmesh->pVertices[i].Vertex[0];
				pver->y = (REAL)pmesh->pVertices[i].Vertex[1];
				pver->z = (REAL)pmesh->pVertices[i].Vertex[2];

				pver->u = (FIXP16)(pmesh->pVertices[i].u * FIXP16_MAG);
				pver->v = (FIXP16)(pmesh->pVertices[i].v * FIXP16_MAG);
			}

			if(!Create_Array(&pobj->ver_list_t, max_ver_size))
				ON_ERROR_GOTO("create vertex_t list failed");

			if(!Create_Array(&pobj->nor_list, max_nor_size))
				ON_ERROR_GOTO("create normal list failed");

			for(j = 0; j < pmesh->nNumNormals; j++)
			{
				VECTOR4D * pnor;
				if(!Append_Array(&pobj->nor_list, &pnor))
					ON_ERROR_GOTO("append normal list failed");

				VECTOR4D_InitXYZ(	pnor,
									(REAL)pmesh->pNormals[i][0],
									(REAL)pmesh->pNormals[i][1],
									(REAL)pmesh->pNormals[i][2]);
			}

			if(!Create_Array(&pobj->nor_list_t, max_nor_size))
				ON_ERROR_GOTO("create normal_t list failed");
			return true;
		}
	}
	ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot find mesh %s", mesh_name));

ON_ERROR:
	Destroy_Array(&pobj->tri_list);
	Destroy_Array(&pobj->ver_list);
	Destroy_Array(&pobj->ver_list_t);
	Destroy_Array(&pobj->nor_list);
	Destroy_Array(&pobj->nor_list_t);
	return false;
}

T3DLIB_API void Destroy_Object4D(OBJECT4DV1 * pobj)
{
	Destroy_Array(&pobj->tri_list);
	Destroy_Array(&pobj->ver_list);
	Destroy_Array(&pobj->ver_list_t);
	Destroy_Array(&pobj->nor_list);
	Destroy_Array(&pobj->nor_list_t);
	INIT_ZERO(*pobj);
}

T3DLIB_API void Model_To_World_Object4D(OBJECT4DV1 * pobj)
{
	UNREFERENCED_PARAMETER(pobj);
}

T3DLIB_API void World_To_Camera_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	UNREFERENCED_PARAMETER(pobj);
	UNREFERENCED_PARAMETER(pcam);
}

T3DLIB_API void Camera_To_Perspective_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	UNREFERENCED_PARAMETER(pobj);
	UNREFERENCED_PARAMETER(pcam);
}

T3DLIB_API void Perspective_To_Screen_Object4D(OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	UNREFERENCED_PARAMETER(pobj);
	UNREFERENCED_PARAMETER(pcam);
}

T3DLIB_API void Draw_Object4D16(SURFACEV1 * psurface, OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	UNREFERENCED_PARAMETER(psurface);
	UNREFERENCED_PARAMETER(pobj);
	UNREFERENCED_PARAMETER(pcam);
}

T3DLIB_API void Draw_Object4D32(SURFACEV1 * psurface, OBJECT4DV1 * pobj, CAM4DV1 * pcam)
{
	UNREFERENCED_PARAMETER(psurface);
	UNREFERENCED_PARAMETER(pobj);
	UNREFERENCED_PARAMETER(pcam);
}

T3DLIB_API bool Clip_Triangle_From_Camera(TRI_ARRAYV1 * ptris, VER_ARRAYV1 * pvers, NOR_ARRAYV1 * pnors, CAM4DV1 * pcam)
{
	return false;
	UNREFERENCED_PARAMETER(ptris);
	UNREFERENCED_PARAMETER(pvers);
	UNREFERENCED_PARAMETER(pnors);
	UNREFERENCED_PARAMETER(pcam);
}
