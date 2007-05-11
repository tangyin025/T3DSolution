/**
 * File: T3DLIB2/t3dlib5.h
 */

#ifndef __T3DLIB5_H__
#define __T3DLIB5_H__

#include "t3dcommons.h"

#define MAX_VERTEX_NUM			(3)
#define MAX_TEXTURE_NUM			(2)

#define CLIP_REGION_C			(0x00)
#define CLIP_REGION_N			(0x01)
#define CLIP_REGION_S			(0x02)
#define CLIP_REGION_W			(0x04)
#define CLIP_REGION_E			(0x08)
#define CLIP_REGION_NW			(0x05)
#define CLIP_REGION_NE			(0x09)
#define CLIP_REGION_SW			(0x06)
#define CLIP_REGION_SE			(0x0A)

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
	//int					min_clip_x;
	//int					max_clip_x;
	//int					min_clip_y;
	//int					max_clip_y;
	REAL				fmin_clip_x;
	REAL				fmax_clip_x;
	REAL				fmin_clip_y;
	REAL				fmax_clip_y;
	//VECTOR4D			v[MAX_VERTEX_NUM];
	//unsigned int		c_diff[MAX_VERTEX_NUM];
	//unsigned int		c_spec[MAX_VERTEX_NUM];
	unsigned char *		t_pbuffer[MAX_TEXTURE_NUM];
	long				t_pitch[MAX_TEXTURE_NUM];
	int					t_pitch_shift[MAX_TEXTURE_NUM];
	int					t_color_shift[MAX_TEXTURE_NUM];
	//FIXP16				t_u[MAX_TEXTURE_NUM][MAX_VERTEX_NUM];
	//FIXP16				t_v[MAX_TEXTURE_NUM][MAX_VERTEX_NUM];
	unsigned int		c_key;
	unsigned int		c_src_alpha;
	unsigned int		c_dst_alpha;

	_CTOR_DECLARE(RENDERCONTEXTV1_TYP);
	_DTOR_DECLARE(RENDERCONTEXTV1_TYP);

} RENDERCONTEXTV1, * RENDERCONTEXTV1_PTR;

extern T3DLIB_API void (* Draw_Rectangle)(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Rectangle_Alpha)(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Rectangle)(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Rectangle_Alpha)(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_HLine)(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_VLine)(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_HLine)(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_VLine)(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Line)(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Line)(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API bool Init_T3dlib5(int bpp);

T3DLIB_API void Draw_HLine16(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_HLine32(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_VLine16(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_VLine32(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_HLine16(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_HLine32(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_VLine16(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_VLine32(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Line16(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Line32(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API bool Clip_Line(register RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Line16(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Line32(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle16(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle32(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle_Alpha16(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle_Alpha32(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API bool Clip_Rectangle(register RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle16(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle32(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_Alpha16(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_Alpha32(register RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

#endif // __T3DLIB5_H__
