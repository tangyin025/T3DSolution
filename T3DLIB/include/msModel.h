/*
 * File: T3DLIB/msModel.h
 */

#ifndef __MS3D_H__
#define __MS3D_H__

#include "t3dcommons.h"

#define MS_MAX_NAME             (32)
#define MS_MAX_PATH             (256)

typedef enum T3DLIB_API msFlag_t
{
	eSelected		= 1,
	eSelected2		= 2,
	eHidden			= 4,
	eDirty			= 8,
	eAveraged		= 16,
	eKeepVertex		= 32,
	eHasAlpha		= 0x40,
	eSphereMap		= 0x80,

} msFlag;

typedef struct T3DLIB_API msVertex_t
{
	int				nFlags;
	float			Vertex[3];
	float			u, v;
	int				nBoneIndex;

} msVertex;

//typedef struct T3DLIB_API msVertexEx_t
//{
//	int				nBoneIndices[3];
//	int				nBoneWeights[3];
//
//} msVertexEx;

typedef struct T3DLIB_API msTriangle_t
{
	int				nFlags;
	int				nVertexIndices[3];
	int				nNormalIndices[3];
//	float			Normal[3];
	int				nSmoothingGroup;

} msTriangle;

//typedef struct T3DLIB_API msTriangleEx_t
//{
//	float			Normals[3][3];
//	float			TexCoords[3][2];
//
//} msTriangleEx;

typedef struct T3DLIB_API msMesh_t
{
	int				nFlags;
	char			szName[MS_MAX_NAME];
	int				nMaterialIndex;

	int				nNumVertices;
//	int				nNumAllocedVertices;
	msVertex *		pVertices;

	int				nNumNormals;
//	int				nNumAllocedNormals;
	float			(* pNormals)[3];

	int				nNumTriangles;
//	int				nNumAllocedTriangles;
	msTriangle *	pTriangles;

//	char *			pszComment;
//	msVertexEx *	pVertexExs;
//	msTriangleEx *	pTriangleExs;

} msMesh;

typedef struct T3DLIB_API msMaterial
{
//	int				nFlags;
	char			szName[MS_MAX_NAME];
	float			Ambient[4];
	float			Diffuse[4];
	float			Specular[4];
	float			Emissive[4];
	float			fShininess;
	float			fTransparency;
	char			szDiffuseTexture[MS_MAX_PATH];
	char			szAlphaTexture[MS_MAX_PATH];
//	int				nName;
//	char *			pszComment;

} msMaterial;

typedef struct T3DLIB_API msPositionKey
{
	float			fTime;
	float			Position[3];

} msPositionKey;

typedef struct T3DLIB_API msRotationKey
{
	float			fTime;
	float			Rotation[3];

} msRotationKey;

typedef struct T3DLIB_API msBone
{
	int				nFlags;
	char			szName[MS_MAX_NAME];
	char			szParentName[MS_MAX_NAME];
	float			Position[3];
	float			Rotation[3];

	int				nNumPositionKeys;
//	int				nNumAllocedPositionKeys;
	msPositionKey *	pPositionKeys;

	int				nNumRotationKeys;
//	int				nNumAllocedRotationKeys;
	msRotationKey *	pRotationKeys;
//	char *			pszComment;

} msBone;

typedef struct T3DLIB_API msModel_t
{
	int				nNumMeshes;
//	int				nNumAllocedMeshes;
	msMesh *		pMeshes;

	int				nNumMaterials;
//	int				nNumAllocedMaterials;
	msMaterial *	pMaterials;

	int				nNumBones;
//	int				nNumAllocedBones;
	msBone *		pBones;

	int				nFrame;
	int				nTotalFrames;

//	float			Position[3];
//	float			Rotation[3];

//	float			CameraPosition[3];
//	float			CameraRotationXY[2];

//	char *			pszComment;

	_CTOR_DECLARE(msModel_t);
	_DTOR_DECLARE(msModel_t);

} msModel;

T3DLIB_API bool Create_MsModel_From_File(msModel * pmode, const char * fname);

T3DLIB_API void Destroy_MsModel(msModel * pmode);

#endif // __MS3D_H__
