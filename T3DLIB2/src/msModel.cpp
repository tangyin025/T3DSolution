/*
 * File: ms3d.h
 */

#include "t3dheaders.h"
#include "msModel.h"

__declspec(thread) static char gline[MAX_BUFFER_SIZE];

_CTOR_IMPLEMENT(msModel_t);
_DTOR_IMPLEMENT_W1(msModel_t, Destroy_MsModel, pMeshes);

static bool Get_Next_Valid_Line(char * pbuff, int buff_size, FILE * pfile)
{
	static const char * comment = "//";
	static const size_t comment_len = strlen(comment);
	while(fgets(pbuff, buff_size, pfile))
	{
		if(0 != strlen(pbuff) && 0 != strncmp(pbuff, comment, comment_len))
			return true;
	}
	return false;
}

static bool Create_And_Load_MsMesh(msMesh * pmesh, FILE * pfile)
{
	return false;
	UNREFERENCED_PARAMETER(pmesh);
	UNREFERENCED_PARAMETER(pfile);
}

static void Destroy_MsMesh(msMesh * pmesh)
{
	;
	UNREFERENCED_PARAMETER(pmesh);
}

static bool Create_And_Load_MsMaterial(msMaterial * pmaterial, FILE * pfile)
{
	return false;
	UNREFERENCED_PARAMETER(pmaterial);
	UNREFERENCED_PARAMETER(pfile);
}

static void Destroy_MsMaterial(msMaterial * pMaterial)
{
	;
	UNREFERENCED_PARAMETER(pMaterial);
}

static bool Create_And_Load_MsBone(msBone * pbone, FILE * pfile)
{
	return false;
	UNREFERENCED_PARAMETER(pbone);
	UNREFERENCED_PARAMETER(pfile);
}

static void Destroy_MsBone(msBone * pbone)
{
	;
	UNREFERENCED_PARAMETER(pbone);
}

static bool Load_Frame_Info(msModel * pmodel, FILE * pfile)
{
	if(!Get_Next_Valid_Line(gline, MAX_BUFFER_SIZE, pfile))
		ON_ERROR_GOTO("cannot read frame info");

	if(1 != scanf(gline, "Frames: %d", &pmodel->nTotalFrames))
		ON_ERROR_GOTO("read frames failed");

	if(1 != scanf(gline, "Frame: %d", &pmodel->nFrame))
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

	if(!Get_Next_Valid_Line(gline, MAX_BUFFER_SIZE, pfile))
		ON_ERROR_GOTO("cannot read mesh info");

	if(1 != scanf(gline, "Meshes: %d", &nMeshes))
		ON_ERROR_GOTO("read meshes failed");

	if(NULL == (pMeshes = (msMesh *)malloc(sizeof(*pMeshes) * nMeshes)))
		ON_ERROR_GOTO("malloc meshes failed");
	memset(pMeshes, 0, sizeof(*pMeshes) * nMeshes);

	for(i = 0; i < nMeshes; i++)
	{
		if(!Create_And_Load_MsMesh(&pMeshes[i], pfile))
			ON_ERROR_GOTO("read mesh data failed");
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

	if(!Get_Next_Valid_Line(gline, MAX_BUFFER_SIZE, pfile))
		ON_ERROR_GOTO("cannot read material info");

	if(1 != scanf(gline, "Materials: %d", &nMaterials))
		ON_ERROR_GOTO("read materials failed");

	if(NULL == (pMaterials = (msMaterial *)malloc(sizeof(*pMaterials) * nMaterials)))
		ON_ERROR_GOTO("malloc materials failed");
	memset(pMaterials, 0, sizeof(*pMaterials) * nMaterials);

	for(i = 0; i < nMaterials; i++)
	{
		if(!Create_And_Load_MsMaterial(&pMaterials[i], pfile))
			ON_ERROR_GOTO("read material data failed");
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

	if(!Get_Next_Valid_Line(gline, MAX_BUFFER_SIZE, pfile))
		ON_ERROR_GOTO("cannot read bone info");

	if(1 != scanf(gline, "Bones: %d", &nBones))
		ON_ERROR_GOTO("read bones failed");

	if(NULL == (pBones = (msBone *)malloc(sizeof(*pBones) * nBones)))
		ON_ERROR_GOTO("malloc bones failed");
	memset(pBones, 0, sizeof(*pBones) * nBones);

	for(i = 0; i < nBones; i++)
	{
		if(!Create_And_Load_MsBone(&pBones[i], pfile))
			ON_ERROR_GOTO("read bone data failed");
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

	msModel tmp_model;
	memset(&tmp_model, 0, sizeof(tmp_model));

	FILE * pfile = NULL;
	if(NULL == (pfile = fopen(fname, "r")))
		ON_ERROR_GOTO(SFORMAT1(gbuffer, "open %s failed", fname));

	if(!Load_Frame_Info(&tmp_model, pfile)
		|| !Load_Mesh_Info(&tmp_model, pfile)
		|| !Load_Material_Info(&tmp_model, pfile)
		|| !Load_Bone_Info(&tmp_model, pfile))
		goto ON_ERROR;
		// the last error have already write to global by these subroutines

	fclose(pfile);
	*pmodel = tmp_model;
	return true;

ON_ERROR:
	SAFE_FCLOSE(pfile);
	Destroy_MsModel(&tmp_model);
	return false;
}

T3DLIB_API void Destroy_MsModel(msModel * pmodel)
{
	int i;
	for(i = 0; i < pmodel->nNumMeshes; i++)
	{
		Destroy_MsMesh(&pmodel->pMeshes[i]);
	}

	for(i = 0; i < pmodel->nNumMaterials; i++)
	{
		Destroy_MsMaterial(&pmodel->pMaterials[i]);
	}

	for(i = 0; i < pmodel->nNumBones; i++)
	{
		Destroy_MsBone(&pmodel->pBones[i]);
	}
}
