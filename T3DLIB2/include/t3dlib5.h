/**
 * File: T3DLIB2/t3dlib5.h
 */

#ifndef __T3DLIB5_H__
#define __T3DLIB5_H__

#include "t3dcommons.h"

#define MAX_VERTEX_NUM			(3)
#define MAX_TEXTURE_NUM			(2)

#pragma warning(disable : 4201)
typedef struct T3DLIB_API TEXTCOORV1_TYP
{
	union
	{
		struct
		{
			FIXP16 u;
			FIXP16 v;
		};

		struct
		{
			VECTOR2DI _2DI;
		};
	};

} TEXTCOORV1, * TEXTCOORV1_PTR;

typedef struct T3DLIB_API VERTEXV1_TYP
{
	union
	{
		struct
		{
			REAL x, y, z, w;
			unsigned int c_diff;
			unsigned int c_spec;
		};

		struct
		{
			VECTOR4D _VECTOR4D;
		};
	};

} VERTEXV1, * VERTEXV1_PTR;

typedef struct T3DLIB_API VERTEXV1T_TYP
{
	union
	{
		struct
		{
			REAL x, y, z, w;
			unsigned int c_diff;
			unsigned int c_spec;
			TEXTCOORV1 t[MAX_TEXTURE_NUM];
		};

		struct
		{
			VECTOR4D _VECTOR4D;
		};

		struct
		{
			VERTEXV1 _VERTEXV1;
		};
	};

} VERTEXV1T, * VERTEXV1T_PTR;
#pragma warning(default : 4201)

typedef struct T3DLIB_API RENDERCONTEXTV1_TYP
{
	unsigned char *		s_pbuffer;
	long				s_pitch;
	int					s_pitch_shift;
	int					s_color_shift;

	unsigned char *		z_pbuffer;
	long				z_pitch;
	int					z_pitch_shift;
	int					z_color_shift;

	unsigned char *		t_pbuffer[MAX_TEXTURE_NUM];
	long				t_pitch[MAX_TEXTURE_NUM];
	int					t_pitch_shift[MAX_TEXTURE_NUM];
	int					t_color_shift[MAX_TEXTURE_NUM];

	unsigned int		c_ambi;
	unsigned int		c_src_key;
	unsigned int		c_src_alpha;
	unsigned int		c_dst_alpha;

	REAL				fmin_clip_x;
	REAL				fmax_clip_x;
	REAL				fmin_clip_y;
	REAL				fmax_clip_y;

	_CTOR_DECLARE(RENDERCONTEXTV1_TYP);
	_DTOR_DECLARE(RENDERCONTEXTV1_TYP);

} RENDERCONTEXTV1, * RENDERCONTEXTV1_PTR;

extern T3DLIB_API void (* Draw_Rectangle)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Rectangle_Alpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Rectangle)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Rectangle_Alpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_HLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_VLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_HLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_VLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Line)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Line)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API bool Init_T3dlib5(int bpp);

T3DLIB_API void Draw_HLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_HLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_VLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_VLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_HLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_HLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_VLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_VLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Line16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Line32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API bool Clip_Line(const RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Line16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Line32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API bool Clip_Rectangle(const RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

#endif // __T3DLIB5_H__
