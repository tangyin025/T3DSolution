/*
 * File: T3DLIB/msModel.cpp
 */

#include "t3dPrecompiledHeader.h"
#include "msModel.h"

__declspec(thread) static char gline[MAX_BUFFER_SIZE];

_CTOR_IMPLEMENT(msModel_t);
_DTOR_IMPLEMENT_W1(msModel_t, Destroy_MsModel, pMeshes);

static bool Is_Empty_Line(const char * pbuff)
{
	const char * p = pbuff;
	while(*p)
	{
		if(*p != ' ' && *p != '\t' && *p != '\r' && *p != '\n')
			return false;
		p++;
	}
	return true;
}

static bool Is_Comment_Line(const char * pbuff)
{
	static const char * comment = "//";
	static const size_t comment_len = strlen(comment);
	return 0 == strncmp(pbuff, comment, comment_len);
}

static bool Get_Next_Valid_Line(char * pbuff, int buff_size, FILE * pfile)
{
	while(fgets(pbuff, buff_size, pfile))
	{
		if(!Is_Empty_Line(pbuff) && !Is_Comment_Line(pbuff))
			return true;
	}
	return false;
}

static bool Load_MsVertex(msVertex * pVertex, FILE * pfile)
{
	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read vertex data");

	if(7 != sscanf(gline, "%d %f %f %f %f %f %d", &pVertex->nFlags,
			&pVertex->Vertex[0], &pVertex->Vertex[1], &pVertex->Vertex[2], &pVertex->u, &pVertex->v, &pVertex->nBoneIndex))
		ON_ERROR_GOTO("read vertex data failed");
	return true;

ON_ERROR:
	return false;
}

static bool Load_MsNormal(float pNormal[3], FILE * pfile)
{
	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read normal data");

	if(3 != sscanf(gline, "%f %f %f", &pNormal[0], &pNormal[1], &pNormal[2]))
		ON_ERROR_GOTO("read normal data failed");
	return true;

ON_ERROR:
	return false;
}

static bool Load_MsTriangles(msTriangle * pTriangle, FILE * pfile)
{
	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read triangle data");

	if(8 != sscanf(gline, "%d %d %d %d %d %d %d %d", &pTriangle->nFlags,
			&pTriangle->nVertexIndices[0], &pTriangle->nVertexIndices[1], &pTriangle->nVertexIndices[2],
			&pTriangle->nNormalIndices[0], &pTriangle->nNormalIndices[1], &pTriangle->nNormalIndices[2], &pTriangle->nSmoothingGroup))
		ON_ERROR_GOTO("read triangle data failed");
	return true;

ON_ERROR:
	return false;
}

static bool Load_MsPositionKey(msPositionKey * pPositionKey, FILE * pfile)
{
	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read PositionKey data");

	if(4 != sscanf(gline, "%f %f %f %f", &pPositionKey->fTime,
			&pPositionKey->Position[0], &pPositionKey->Position[1], &pPositionKey->Position[2]))
		ON_ERROR_GOTO("read PositionKey data failed");
	return true;

ON_ERROR:
	return false;
}

static bool Load_MsRotationKey(msRotationKey * pRotationKey, FILE * pfile)
{
	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read RotationKey data");

	if(4 != sscanf(gline, "%f %f %f %f", &pRotationKey->fTime,
			&pRotationKey->Rotation[0], &pRotationKey->Rotation[1], &pRotationKey->Rotation[2]))
		ON_ERROR_GOTO("read RotationKey data failed");
	return true;

ON_ERROR:
	return false;
}

static bool Create_And_Load_MsMesh(msMesh * pmesh, FILE * pfile)
{
	assert(pmesh->pVertices == NULL);
	assert(pmesh->pNormals == NULL);
	assert(pmesh->pTriangles == NULL);

	int i;
	msVertex * pVertices = NULL;
	int nVertices = 0;
	float (* pNormals)[3] = NULL;
	int nNormals = 0;
	msTriangle * pTriangles = NULL;
	int nTriangles = 0;

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read mesh");

	if(3 != sscanf(gline, "\"%[^\"]\" %d %d", pmesh->szName, &pmesh->nFlags, &pmesh->nMaterialIndex))
		ON_ERROR_GOTO("read mesh name failed");

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read mesh");

	if(1 != sscanf(gline, "%d", &nVertices))
		ON_ERROR_GOTO("read vertices failed");

	if(NULL == (pVertices = (msVertex *)malloc(sizeof(*pVertices) * nVertices)))
		ON_ERROR_GOTO("malloc vertices failed");

	for(i = 0; i < nVertices; i++)
	{
		if(!Load_MsVertex(&pVertices[i], pfile))
			ON_ERROR_GOTO("load vertex failed");
	}

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read mesh");

	if(1 != sscanf(gline, "%d", &nNormals))
		ON_ERROR_GOTO("read normals failed");

	assert(sizeof(*pNormals) == sizeof(float) * 3);
	if(NULL == (pNormals = (float (*) [3])malloc(sizeof(*pNormals) * nNormals)))
		ON_ERROR_GOTO("malloc normals failed");

	for(i = 0; i < nNormals; i++)
	{
		if(!Load_MsNormal(pNormals[i], pfile))
			goto ON_ERROR;
	}

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read mesh");

	if(1 != sscanf(gline, "%d", &nTriangles))
		ON_ERROR_GOTO("read triangles failed");

	if(NULL == (pTriangles = (msTriangle *)malloc(sizeof(*pTriangles) * nTriangles)))
		ON_ERROR_GOTO("malloc triangles failed");

	for(i = 0; i < nTriangles; i++)
	{
		if(!Load_MsTriangles(&pTriangles[i], pfile))
			goto ON_ERROR;
	}

	pmesh->nNumVertices		= nVertices;
	pmesh->pVertices		= pVertices;
	pmesh->nNumNormals		= nNormals;
	pmesh->pNormals			= pNormals;
	pmesh->nNumTriangles	= nTriangles;
	pmesh->pTriangles		= pTriangles;
	return true;

ON_ERROR:
	SAFE_FREE(pVertices);
	SAFE_FREE(pNormals);
	SAFE_FREE(pTriangles);
	return false;
}

static void Destroy_MsMesh(msMesh * pmesh)
{
	SAFE_FREE(pmesh->pVertices);
	SAFE_FREE(pmesh->pNormals);
	SAFE_FREE(pmesh->pTriangles);
}

static bool Create_And_Load_MsMaterial(msMaterial * pmaterial, FILE * pfile)
{
	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read material name");

	if(1 != sscanf(gline, "\"%[^\"]\"", pmaterial->szName))
		ON_ERROR_GOTO("read material name failed");

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read ambient color");

	if(4 != sscanf(gline, "%f %f %f %f",
			&pmaterial->Ambient[0], &pmaterial->Ambient[1], &pmaterial->Ambient[2], &pmaterial->Ambient[3]))
		ON_ERROR_GOTO("read ambient color failed");

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read diffuse color");

	if(4 != sscanf(gline, "%f %f %f %f",
			&pmaterial->Diffuse[0], &pmaterial->Diffuse[1], &pmaterial->Diffuse[2], &pmaterial->Diffuse[3]))
		ON_ERROR_GOTO("read diffuse color failed");

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read specular color");

	if(4 != sscanf(gline, "%f %f %f %f",
			&pmaterial->Specular[0], &pmaterial->Specular[1], &pmaterial->Specular[2], &pmaterial->Specular[3]))
		ON_ERROR_GOTO("read specular color failed");

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read emissive color");

	if(4 != sscanf(gline, "%f %f %f %f",
			&pmaterial->Emissive[0], &pmaterial->Emissive[1], &pmaterial->Emissive[2], &pmaterial->Emissive[3]))
		ON_ERROR_GOTO("read emissive color failed");

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read shininess");

	if(1 != sscanf(gline, "%f", &pmaterial->fShininess))
		ON_ERROR_GOTO("read shininess failed");

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read transparency");

	if(1 != sscanf(gline, "%f", &pmaterial->fTransparency))
		ON_ERROR_GOTO("read transparency failed");

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read diffuse texture");

	if(1 != sscanf(gline, "\"%[^\"]\"", pmaterial->szDiffuseTexture))
		INIT_ZERO(pmaterial->szDiffuseTexture);

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read alpha texture");

	if(1 != sscanf(gline, "\"%[^\"]\"", pmaterial->szAlphaTexture))
		INIT_ZERO(pmaterial->szAlphaTexture);
	return true;

ON_ERROR:
	return false;
}

static void Destroy_MsMaterial(msMaterial * pMaterial)
{
	pMaterial;
}

static bool Create_And_Load_MsBone(msBone * pbone, FILE * pfile)
{
	int i;
	msPositionKey * pPositionKeys = NULL;
	int nPositionKeys = 0;
	msRotationKey * pRotationKeys = NULL;
	int nRotationKeys = 0;

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read bone name");

	if(1 != sscanf(gline, "\"%[^\"]\"", pbone->szName))
		ON_ERROR_GOTO("read bone name failed");

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read parent bone name");

	strcpy(pbone->szParentName, "");
	sscanf(gline, "\"%[^\"]\"", pbone->szParentName);

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read bone data");

	if(7 != sscanf(gline, "%d %f %f %f %f %f %f", &pbone->nFlags,
			&pbone->Position[0], &pbone->Position[1], &pbone->Position[2],
			&pbone->Rotation[0], &pbone->Rotation[1], &pbone->Rotation[2]))
		ON_ERROR_GOTO("read bone data failed");

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read PositionKeys");

	if(1 != sscanf(gline, "%d", &nPositionKeys))
		ON_ERROR_GOTO("read PositionKeys failed");

	if(NULL == (pPositionKeys = (msPositionKey *)malloc(sizeof(*pPositionKeys) * nPositionKeys)))
		ON_ERROR_GOTO("malloc PositionKeys failed");

	for(i = 0; i < nPositionKeys; i++)
	{
		if(!Load_MsPositionKey(&pPositionKeys[i], pfile))
			goto ON_ERROR;
	}

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read RotationKeys");

	if(1 != sscanf(gline, "%d", &nRotationKeys))
		ON_ERROR_GOTO("read RotationKeys failed");

	if(NULL == (pRotationKeys = (msRotationKey *)malloc(sizeof(*pRotationKeys) * nRotationKeys)))
		ON_ERROR_GOTO("malloc RotationKeys failed");

	for(i = 0; i < nRotationKeys; i++)
	{
		if(!Load_MsRotationKey(&pRotationKeys[i], pfile))
			goto ON_ERROR;
	}

	pbone->nNumPositionKeys	= nPositionKeys;
	pbone->pPositionKeys	= pPositionKeys;
	pbone->nNumRotationKeys	= nRotationKeys;
	pbone->pRotationKeys	= pRotationKeys;
	return true;

ON_ERROR:
	SAFE_FREE(pPositionKeys);
	SAFE_FREE(pRotationKeys);
	return false;
}

static void Destroy_MsBone(msBone * pbone)
{
	SAFE_FREE(pbone->pPositionKeys);
	SAFE_FREE(pbone->pRotationKeys);
}

static bool Load_Frame_Info(msModel * pmodel, FILE * pfile)
{
	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read frames info");

	if(1 != sscanf(gline, "Frames: %d", &pmodel->nTotalFrames))
		ON_ERROR_GOTO("read frames failed");

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read frame info");

	if(1 != sscanf(gline, "Frame: %d", &pmodel->nFrame))
		ON_ERROR_GOTO("read frame failed");
	return true;

ON_ERROR:
	return false;
}

static bool Load_Mesh_Info(msModel * pmodel, FILE * pfile)
{
	assert(pmodel->nNumMeshes == 0);
	assert(pmodel->pMeshes == NULL);

	msMesh * pMeshes = NULL;
	int nMeshes = 0;
	int i;

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read mesh info");

	if(1 != sscanf(gline, "Meshes: %d", &nMeshes))
		ON_ERROR_GOTO("read meshes failed");

	if(NULL == (pMeshes = (msMesh *)malloc(sizeof(*pMeshes) * nMeshes)))
		ON_ERROR_GOTO("malloc meshes failed");

	memset(pMeshes, 0, sizeof(*pMeshes) * nMeshes);
	for(i = 0; i < nMeshes; i++)
	{
		if(!Create_And_Load_MsMesh(&pMeshes[i], pfile))
			goto ON_ERROR;
	}

	pmodel->nNumMeshes = nMeshes;
	pmodel->pMeshes = pMeshes;
	return true;

ON_ERROR:
	for(i = 0; i < nMeshes; i++)
	{
		Destroy_MsMesh(&pMeshes[i]);
	}
	SAFE_FREE(pMeshes);
	return false;
}

static bool Load_Material_Info(msModel * pmodel, FILE * pfile)
{
	assert(pmodel->nNumMaterials == 0);
	assert(pmodel->pMaterials == NULL);

	msMaterial * pMaterials = NULL;
	int nMaterials = 0;
	int i;

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read material info");

	if(1 != sscanf(gline, "Materials: %d", &nMaterials))
		ON_ERROR_GOTO("read materials failed");

	if(NULL == (pMaterials = (msMaterial *)malloc(sizeof(*pMaterials) * nMaterials)))
		ON_ERROR_GOTO("malloc materials failed");

	memset(pMaterials, 0, sizeof(*pMaterials) * nMaterials);
	for(i = 0; i < nMaterials; i++)
	{
		if(!Create_And_Load_MsMaterial(&pMaterials[i], pfile))
			goto ON_ERROR;
	}

	pmodel->nNumMaterials = nMaterials;
	pmodel->pMaterials = pMaterials;
	return true;

ON_ERROR:
	for(i = 0; i < nMaterials; i++)
	{
		Destroy_MsMaterial(&pMaterials[i]);
	}
	SAFE_FREE(pMaterials);
	return false;
}

static bool Load_Bone_Info(msModel * pmodel, FILE * pfile)
{
	assert(pmodel->nNumBones == 0);
	assert(pmodel->pBones == NULL);

	msBone * pBones = NULL;
	int nBones = 0;
	int i;

	if(!Get_Next_Valid_Line(gline, sizeof(gline), pfile))
		ON_ERROR_GOTO("cannot read bone info");

	if(1 != sscanf(gline, "Bones: %d", &nBones))
		ON_ERROR_GOTO("read bones failed");

	if(NULL == (pBones = (msBone *)malloc(sizeof(*pBones) * nBones)))
		ON_ERROR_GOTO("malloc bones failed");

	memset(pBones, 0, sizeof(*pBones) * nBones);
	for(i = 0; i < nBones; i++)
	{
		if(!Create_And_Load_MsBone(&pBones[i], pfile))
			goto ON_ERROR;
	}

	pmodel->nNumBones = nBones;
	pmodel->pBones = pBones;
	return true;

ON_ERROR:
	for(i = 0; i < nBones; i++)
	{
		Destroy_MsBone(&pBones[i]);
	}
	SAFE_FREE(pBones);
	return false;
}

T3DLIB_API bool Create_MsModel_From_File(msModel * pmodel, const char * fname)
{
	assert(pmodel->pMeshes == NULL);
	assert(pmodel->pMaterials == NULL);
	assert(pmodel->pBones == NULL);

	FILE * pfile = NULL;
	if(NULL == (pfile = fopen(fname, "r")))
		ON_ERROR_GOTO(SFORMAT1(gbuffer, "open %s failed", fname));

	if(!Load_Frame_Info(pmodel, pfile)
		|| !Load_Mesh_Info(pmodel, pfile)
		|| !Load_Material_Info(pmodel, pfile)
		|| !Load_Bone_Info(pmodel, pfile))
		goto ON_ERROR;
		// the last error have already write to global by these subroutines

	fclose(pfile);
	return true;

ON_ERROR:
	SAFE_FCLOSE(pfile);
	Destroy_MsModel(pmodel);
	return false;
}

T3DLIB_API void Destroy_MsModel(msModel * pmodel)
{
	int i;
	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		Destroy_MsMesh(&pmodel->pMeshes[i]);
	}
	SAFE_FREE(pmodel->pMeshes);
	pmodel->nNumMeshes = 0;

	for(i = 0; i < pmodel->nNumMaterials; i++)
	{
		Destroy_MsMaterial(&pmodel->pMaterials[i]);
	}
	SAFE_FREE(pmodel->pMaterials);
	pmodel->nNumMaterials = 0;

	for(i = 0; i < pmodel->nNumBones; i++)
	{
		Destroy_MsBone(&pmodel->pBones[i]);
	}
	SAFE_FREE(pmodel->pBones);
	pmodel->nNumBones = 0;
}
