/*
 * File: T3DLIB2/t3dlib6.cpp
 */

#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib4.h"
#include "t3dlib5.h"
#include "t3dlib6.h"

T3DLIB_API void (* Draw_Object4D)(SURFACEV1 * psurface, OBJECT4DV1 * pobj, CAM4DV1 * pcam) = NULL;

T3DLIB_API bool Init_T3dlib6(int bpp)
{
	switch(bpp)
	{
	case 16:
		Draw_Object4D	= Draw_Object4D16;
		break;

	case 32:
		Draw_Object4D	= Draw_Object4D32;
		break;

	default:
		ON_ERROR_GOTO(SFORMAT1(gbuffer, "unsupported color bip: %d", bpp));
	}
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Create_Material_From_MsModel(MATERIALV1 * pmaterial, msModel * pmodel, const char * material_name)
{
	return false;
	UNREFERENCED_PARAMETER(pmaterial);
	UNREFERENCED_PARAMETER(pmodel);
	UNREFERENCED_PARAMETER(material_name);
}

T3DLIB_API void Destroy_Material(MATERIALV1 * pmaterial)
{
	UNREFERENCED_PARAMETER(pmaterial);
}

T3DLIB_API bool Create_Object4D_From_MsModel(OBJECT4DV1 * pobj, msModel * pmodel, const char * mesh_name,
											 size_t max_tri_size /*= 1000*/,
											 size_t max_ver_size /*= 3000*/,
											 size_t max_nor_size /*= 3000*/)
{
	return false;
	UNREFERENCED_PARAMETER(pobj);
	UNREFERENCED_PARAMETER(pmodel);
	UNREFERENCED_PARAMETER(mesh_name);
	UNREFERENCED_PARAMETER(max_tri_size);
	UNREFERENCED_PARAMETER(max_ver_size);
	UNREFERENCED_PARAMETER(max_nor_size);
}

T3DLIB_API void Destroy_Object4D(OBJECT4DV1 * pobj)
{
	UNREFERENCED_PARAMETER(pobj);
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
