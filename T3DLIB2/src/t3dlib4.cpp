/**
 * File: T3DLIB2/t3dlib4.cpp
 */

#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib4.h"

const MATRIX2X2_TYP MATRIX2X2::IDENTITY = {	1.0f, 0.0f,
											0.0f, 1.0f, };

//const MATRIX3X2_TYP MATRIX3X2::IDENTITY = {	1.0f, 0.0f,
//											0.0f, 1.0f,
//											0.0f, 0.0f, };

const MATRIX3X2_TYP MATRIX3X2::IDENTITY = {	1.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f, };

const MATRIX3X3_TYP MATRIX3X3::IDENTITY = {	1.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 1.0f, };

//const MATRIX4X3_TYP MATRIX4X3::IDENTITY = {	1.0f, 0.0f, 0.0f,
//											0.0f, 1.0f, 0.0f,
//											0.0f, 0.0f, 1.0f,
//											0.0f, 0.0f, 0.0f, };

const MATRIX4X3_TYP MATRIX4X3::IDENTITY = {	1.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 1.0f, 0.0f, };

const MATRIX4X4_TYP MATRIX4X4::IDENTITY = {	1.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 1.0f, };

T3DLIB_API unsigned char COLOR_TABLE_ADD16G[MAX_COLOR_INTENSITY16G][MAX_COLOR_INTENSITY16G];
T3DLIB_API unsigned char COLOR_TABLE_ADD[MAX_COLOR_INTENSITY32][MAX_COLOR_INTENSITY32];
T3DLIB_API unsigned char COLOR_TABLE_MUL16G[MAX_COLOR_INTENSITY16G][MAX_COLOR_INTENSITY16G];
T3DLIB_API unsigned char COLOR_TABLE_MUL[MAX_COLOR_INTENSITY32][MAX_COLOR_INTENSITY32];

T3DLIB_API bool Init_T3dlib4(int bpp)
{
	unsigned int i, j;
	switch(bpp)
	{
	case 16:
		for(i = 0; i < MAX_COLOR_INTENSITY16; i++)
		{
			for(j = 0; j < MAX_COLOR_INTENSITY16; j++)
			{
				COLOR_TABLE_ADD[i][j] = (unsigned char)MIN(i + j, MAX_COLOR_INTENSITY16 - 1);
				COLOR_TABLE_MUL[i][j] = (unsigned char)((float)i * (float)j / (MAX_COLOR_INTENSITY16 - 1) + 0.5f);
			}
		}
		for(i = 0; i < MAX_COLOR_INTENSITY16G; i++)
		{
			for(j = 0; j < MAX_COLOR_INTENSITY16G; j++)
			{
				COLOR_TABLE_ADD16G[i][j] = (unsigned char)MIN(i + j, MAX_COLOR_INTENSITY16G - 1);
				COLOR_TABLE_MUL16G[i][j] = (unsigned char)((float)i * (float)j / (MAX_COLOR_INTENSITY16G - 1) + 0.5f);
			}
		}
		break;

	case 32:
		for(i = 0; i < MAX_COLOR_INTENSITY32; i++)
		{
			for(j = 0; j < MAX_COLOR_INTENSITY32; j++)
			{
				COLOR_TABLE_ADD[i][j] = (unsigned char)MIN(i + j, MAX_COLOR_INTENSITY32 - 1);
				COLOR_TABLE_MUL[i][j] = (unsigned char)((float)i * (float)j / (MAX_COLOR_INTENSITY32 - 1) + 0.5f);
			}
		}
		break;

	default:
		ON_ERROR_GOTO((sprintf(gbuffer, "unsupported color bip: %d", bpp), gbuffer));
	}
	return true;

ON_ERROR:
	return false;
}
