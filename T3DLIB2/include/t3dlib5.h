/**
 * File: T3DLIB2/t3dlib5.h
 */

#ifndef __T3DLIB5_H__
#define __T3DLIB5_H__

#include "t3dcommons.h"

#define TRI_VERTEX_NUM			(3)
#define TRI_TEXTURE_NUM			(2)

#define CLIP_REGION_C			(0x00)
#define CLIP_REGION_N			(0x01)
#define CLIP_REGION_S			(0x02)
#define CLIP_REGION_W			(0x04)
#define CLIP_REGION_E			(0x08)
#define CLIP_REGION_NW			(0x05)
#define CLIP_REGION_NE			(0x09)
#define CLIP_REGION_SW			(0x06)
#define CLIP_REGION_SE			(0x0A)

#define LINE2D_INTERSECT(ca, a0, a1, b0, b1)	((b0) + ((b1) - (b0)) * ((ca) - (a0)) / ((a1) - (a0)))

#pragma warning(disable : 4201)
typedef struct T3DLIB_API TEXTCOORV1_TYP
{
	union
	{
		__declspec(align(16)) FIXP16 _M[2];

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
		__declspec(align(16)) REAL _M[4];

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
		__declspec(align(16)) REAL _M[4];

		struct
		{
			REAL x, y, z, w;
			unsigned int c_diff;
			unsigned int c_spec;
			FIXP16 u,	v;
			FIXP16 u1,	v1;
		};

		struct
		{
			VECTOR4D _VECTOR4D;
		};

		struct
		{
			VERTEXV1	_VERTEXV1;
			TEXTCOORV1	_TEXTCOOR[TRI_TEXTURE_NUM];
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

	unsigned char *		t_pbuffer;
	long				t_pitch;
	int					t_pitch_shift;
	int					t_color_shift;

	unsigned char *		t1_pbuffer;
	long				t1_pitch;
	int					t1_pitch_shift;
	int					t1_color_shift;

	//unsigned int		c_ambi;
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

extern T3DLIB_API void (* Draw_HLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_VLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_HLine_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_VLine_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_HLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_VLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_HLine_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_VLine_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Line)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Line_ZbufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Line_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Line_ZbufferR_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Line)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Line_ZbufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Line_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Line_ZbufferR_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Rectangle)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Rectangle_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Rectangle_Texture_SrcKey)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);
extern T3DLIB_API void (* Draw_Rectangle_Texture_ZBufferW)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);
extern T3DLIB_API void (* Draw_Rectangle_ZBufferR_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Rectangle_ZbufferR_TextureAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);
extern T3DLIB_API void (* Draw_Clipped_Rectangle)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Rectangle_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Rectangle_Texture_SrcKey)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);
extern T3DLIB_API void (* Draw_Clipped_Rectangle_Texture_ZBufferW)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);
extern T3DLIB_API void (* Draw_Clipped_Rectangle_ZBufferR_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);
extern T3DLIB_API void (* Draw_Clipped_Rectangle_ZbufferR_TextureAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

T3DLIB_API bool Init_T3dlib5(int bpp);

T3DLIB_API void Draw_HLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_HLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_VLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_VLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_HLine_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_HLine_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_VLine_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_VLine_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API bool Clip_HLine(const RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1);

T3DLIB_API bool Clip_VLine(const RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_HLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_HLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_VLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_VLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_HLine_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_HLine_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_VLine_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_VLine_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Line16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Line32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Line_ZbufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Line_ZbufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Line_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Line_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Line_ZbufferR_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Line_ZbufferR_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API bool Clip_Line(const RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Line16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Line32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Line_ZbufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Line_ZbufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Line_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Line_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Line_ZbufferR_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Line_ZbufferR_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle_Texture_SrcKey16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

T3DLIB_API void Draw_Rectangle_Texture_SrcKey32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

T3DLIB_API void Draw_Rectangle_Texture_ZBufferW16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

T3DLIB_API void Draw_Rectangle_Texture_ZBufferW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

T3DLIB_API void Draw_Rectangle_ZBufferR_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle_ZBufferR_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Rectangle_ZbufferR_TextureAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

T3DLIB_API void Draw_Rectangle_ZbufferR_TextureAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

T3DLIB_API bool Clip_Rectangle(const RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1);

T3DLIB_API bool Clip_Rectangle_Texture(const RENDERCONTEXTV1 * prc, VERTEXV1T * pv0, VERTEXV1T * pv1);

T3DLIB_API void Draw_Clipped_Rectangle16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_Texture_SrcKey16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_Texture_SrcKey32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_Texture_ZBufferW16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_Texture_ZBufferW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_ZBufferR_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_ZBufferR_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_ZbufferR_TextureAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

T3DLIB_API void Draw_Clipped_Rectangle_ZbufferR_TextureAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1);

#endif // __T3DLIB5_H__
