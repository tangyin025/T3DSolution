/*
 * File: T3DLIB/t3dlib5.cpp
 */

#include "t3dPrecompiledHeader.h"
#include "t3dlib1.h"
#include "t3dlib4.h"
#include "t3dlib5.h"

typedef struct SCANCONTEXT_TYP
{
	REAL		lx, rx, lx_inc, rx_inc;
	int			lu, ru, lu_inc, ru_inc;
	int			lv, rv, lv_inc, rv_inc;
	VECTOR4DI	lc, rc, lc_inc, rc_inc;
	FIXP28		lz, rz, lz_inc, rz_inc;

} SCANCONTEXT, * SCANCONTEXT_PTR;

static void Draw_Scan16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
	int y;
	for(y = y_beg; y < y_end; y++)
	{
		int s_beg = (int)sc.lx;
		int s_end = (int)sc.rx;
		unsigned char * ps = prc->s_pbuffer + (s_beg << _16BIT_BYTES_SHIFT) + (y << prc->s_pitch_shift);
		int dx = s_end - s_beg;

		if(dx > 0)
		{
			Mem_Set_Word(ps, (unsigned short)sc.lc.x, dx);
		}

		sc.lx += sc.lx_inc;
		sc.rx += sc.rx_inc;
	}
}

static void Draw_Scan32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
	int y;
	for(y = y_beg; y < y_end; y++)
	{
		int s_beg = (int)sc.lx;
		int s_end = (int)sc.rx;
		unsigned char * ps = prc->s_pbuffer + (s_beg << _32BIT_BYTES_SHIFT) + (y << prc->s_pitch_shift);
		int dx = s_end - s_beg;

		if(dx > 0)
		{
			Mem_Set_Quad(ps, sc.lc.x, dx);
		}

		sc.lx += sc.lx_inc;
		sc.rx += sc.rx_inc;
	}
}

static void Draw_Scan_ZBufferRW16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_ZB
#define __draw_16
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Scan_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_ZB
#define __draw_32
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Scan_Texture_ZBufferRW16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_ZB
#define __draw_16
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Scan_Texture_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_ZB
#define __draw_32
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Scan_Texture_PerspectiveLP_ZBufferRW16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_ZB
#define __draw_16
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Scan_Texture_PerspectiveLP_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_ZB
#define __draw_32
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Scan_Gouraud_ZBufferRW16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_GR
#define __draw_ZB
#define __draw_16
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Scan_Gouraud_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_GR
#define __draw_ZB
#define __draw_32
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Scan_Gouraud_Texture_ZBufferRW16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_GR
#define __draw_ZB
#define __draw_16
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Scan_Gouraud_Texture_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_GR
#define __draw_ZB
#define __draw_32
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Scan_Gouraud_Texture_PerspectiveLP_ZBufferRW16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_GR
#define __draw_ZB
#define __draw_16
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Scan_Gouraud_Texture_PerspectiveLP_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_GR
#define __draw_ZB
#define __draw_32
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Clipped_Scan16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
	int y;
	for(y = y_beg; y < y_end; y++)
	{
		int s_beg = (int)MAX(sc.lx, prc->fmin_clip_x);
		int s_end = (int)MIN(sc.rx, prc->fmax_clip_x + 1);
		unsigned char * ps = prc->s_pbuffer + (s_beg << _16BIT_BYTES_SHIFT) + (y << prc->s_pitch_shift);
		int dx = s_end - s_beg;

		if(dx > 0)
		{
			Mem_Set_Word(ps, (unsigned short)sc.lc.x, dx);
		}

		sc.lx += sc.lx_inc;
		sc.rx += sc.rx_inc;
	}
}

static void Draw_Clipped_Scan32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
	int y;
	for(y = y_beg; y < y_end; y++)
	{
		int s_beg = (int)MAX(sc.lx, prc->fmin_clip_x);
		int s_end = (int)MIN(sc.rx, prc->fmax_clip_x + 1);
		unsigned char * ps = prc->s_pbuffer + (s_beg << _32BIT_BYTES_SHIFT) + (y << prc->s_pitch_shift);
		int dx = s_end - s_beg;

		if(dx > 0)
		{
			Mem_Set_Quad(ps, sc.lc.x, dx);
		}

		sc.lx += sc.lx_inc;
		sc.rx += sc.rx_inc;
	}
}

static void Draw_Clipped_Scan_ZBufferRW16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_ZB
#define __draw_16
#define __draw_CLIP
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Clipped_Scan_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_ZB
#define __draw_32
#define __draw_CLIP
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Clipped_Scan_Texture_ZBufferRW16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_ZB
#define __draw_16
#define __draw_CLIP
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Clipped_Scan_Texture_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_ZB
#define __draw_32
#define __draw_CLIP
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Clipped_Scan_Texture_PerspectiveLP_ZBufferRW16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_ZB
#define __draw_16
#define __draw_CLIP
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Clipped_Scan_Texture_PerspectiveLP_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_ZB
#define __draw_32
#define __draw_CLIP
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Clipped_Scan_Gouraud_ZBufferRW16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_GR
#define __draw_ZB
#define __draw_16
#define __draw_CLIP
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Clipped_Scan_Gouraud_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_GR
#define __draw_ZB
#define __draw_32
#define __draw_CLIP
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_GR
#define __draw_ZB
#define __draw_16
#define __draw_CLIP
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_GR
#define __draw_ZB
#define __draw_32
#define __draw_CLIP
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Clipped_Scan_Gouraud_Texture_PerspectiveLP_ZBufferRW16(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_GR
#define __draw_ZB
#define __draw_16
#define __draw_CLIP
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

static void Draw_Clipped_Scan_Gouraud_Texture_PerspectiveLP_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_GR
#define __draw_ZB
#define __draw_32
#define __draw_CLIP
#include "t3dlib5.Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW.hpp"
}

_CTOR_IMPLEMENT(RENDERCONTEXTV1_TYP);
_DTOR_IMPLEMENT(RENDERCONTEXTV1_TYP, foo);

T3DLIB_API void (* Draw_HLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_VLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_HLine_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_VLine_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_HLine_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_VLine_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_HLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_VLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Line)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Line_ZbufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Line_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Line_ZbufferR_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Line)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Line_ZbufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Line_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Line_ZbufferR_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Rectangle)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Rectangle_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Rectangle_Texture_SrcKey)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1) = NULL;
T3DLIB_API void (* Draw_Rectangle_Texture_ZBufferW)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1) = NULL;
T3DLIB_API void (* Draw_Rectangle_ZBufferR_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Rectangle_ZbufferR_TextureAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Rectangle)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Rectangle_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Rectangle_Texture_SrcKey)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Rectangle_Texture_ZBufferW)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Rectangle_ZBufferR_SrcAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Rectangle_ZbufferR_TextureAlpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1) = NULL;
T3DLIB_API void (* Draw_Triangle)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2) = NULL;
T3DLIB_API void (* Draw_Triangle_ZBufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2) = NULL;
T3DLIB_API void (* Draw_Triangle_Texture_ZBufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2) = NULL;
T3DLIB_API void (* Draw_Triangle_Texture_PerspectiveLP_ZBufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2) = NULL;
T3DLIB_API void (* Draw_Triangle_Gouraud_ZBufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2) = NULL;
T3DLIB_API void (* Draw_Triangle_Gouraud_Texture_ZBufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2) = NULL;
T3DLIB_API void (* Draw_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2) = NULL;
T3DLIB_API void (* Draw_Clipped_Triangle)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2) = NULL;
T3DLIB_API void (* Draw_Clipped_Triangle_ZBufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2) = NULL;
T3DLIB_API void (* Draw_Clipped_Triangle_Texture_ZBufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2) = NULL;
T3DLIB_API void (* Draw_Clipped_Triangle_Texture_PerspectiveLP_ZBufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2) = NULL;
T3DLIB_API void (* Draw_Clipped_Triangle_Gouraud_ZBufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2) = NULL;
T3DLIB_API void (* Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2) = NULL;
T3DLIB_API void (* Draw_Clipped_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW)(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2) = NULL;

T3DLIB_API bool Init_T3dlib5(int bpp)
{
	switch(bpp)
	{
	case 16:
		Draw_HLine										= Draw_HLine16;
		Draw_VLine										= Draw_VLine16;
		Draw_HLine_SrcAlpha								= Draw_HLine_SrcAlpha16;
		Draw_VLine_SrcAlpha								= Draw_VLine_SrcAlpha16;
		Draw_Clipped_HLine								= Draw_Clipped_HLine16;
		Draw_Clipped_VLine								= Draw_Clipped_VLine16;
		Draw_Clipped_HLine_SrcAlpha						= Draw_Clipped_HLine_SrcAlpha16;
		Draw_Clipped_VLine_SrcAlpha						= Draw_Clipped_VLine_SrcAlpha16;
		Draw_Line										= Draw_Line16;
		Draw_Line_ZbufferRW								= Draw_Line_ZbufferRW16;
		Draw_Line_SrcAlpha								= Draw_Line_SrcAlpha16;
		Draw_Line_ZbufferR_SrcAlpha						= Draw_Line_ZbufferR_SrcAlpha16;
		Draw_Clipped_Line								= Draw_Clipped_Line16;
		Draw_Clipped_Line_ZbufferRW						= Draw_Clipped_Line_ZbufferRW16;
		Draw_Clipped_Line_SrcAlpha						= Draw_Clipped_Line_SrcAlpha16;
		Draw_Clipped_Line_ZbufferR_SrcAlpha				= Draw_Clipped_Line_ZbufferR_SrcAlpha16;
		Draw_Rectangle									= Draw_Rectangle16;
		Draw_Rectangle_SrcAlpha							= Draw_Rectangle_SrcAlpha16;
		Draw_Rectangle_Texture_SrcKey					= Draw_Rectangle_Texture_SrcKey16;
		Draw_Rectangle_Texture_ZBufferW					= Draw_Rectangle_Texture_ZBufferW16;
		Draw_Rectangle_ZBufferR_SrcAlpha				= Draw_Rectangle_ZBufferR_SrcAlpha16;
		Draw_Rectangle_ZbufferR_TextureAlpha			= Draw_Rectangle_ZbufferR_TextureAlpha16;
		Draw_Clipped_Rectangle							= Draw_Clipped_Rectangle16;
		Draw_Clipped_Rectangle_SrcAlpha					= Draw_Clipped_Rectangle_SrcAlpha16;
		Draw_Clipped_Rectangle_Texture_SrcKey			= Draw_Clipped_Rectangle_Texture_SrcKey16;
		Draw_Clipped_Rectangle_Texture_ZBufferW			= Draw_Clipped_Rectangle_Texture_ZBufferW16;
		Draw_Clipped_Rectangle_ZBufferR_SrcAlpha		= Draw_Clipped_Rectangle_ZBufferR_SrcAlpha16;
		Draw_Clipped_Rectangle_ZbufferR_TextureAlpha	= Draw_Clipped_Rectangle_ZbufferR_TextureAlpha16;
		Draw_Triangle									= Draw_Triangle16;
		Draw_Triangle_ZBufferRW							= Draw_Triangle_ZBufferRW16;
		Draw_Triangle_Texture_ZBufferRW					= Draw_Triangle_Texture_ZBufferRW16;
		Draw_Triangle_Texture_PerspectiveLP_ZBufferRW	= Draw_Triangle_Texture_PerspectiveLP_ZBufferRW16;
		Draw_Triangle_Gouraud_ZBufferRW					= Draw_Triangle_Gouraud_ZBufferRW16;
		Draw_Triangle_Gouraud_Texture_ZBufferRW			= Draw_Triangle_Gouraud_Texture_ZBufferRW16;
		Draw_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW	= Draw_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW16;
		Draw_Clipped_Triangle							= Draw_Clipped_Triangle16;
		Draw_Clipped_Triangle_ZBufferRW					= Draw_Clipped_Triangle_ZBufferRW16;
		Draw_Clipped_Triangle_Texture_ZBufferRW			= Draw_Clipped_Triangle_Texture_ZBufferRW16;
		Draw_Clipped_Triangle_Texture_PerspectiveLP_ZBufferRW	= Draw_Clipped_Triangle_Texture_PerspectiveLP_ZBufferRW16;
		Draw_Clipped_Triangle_Gouraud_ZBufferRW			= Draw_Clipped_Triangle_Gouraud_ZBufferRW16;
		Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW	= Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW16;
		Draw_Clipped_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW	= Draw_Clipped_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW16;
		break;

	case 32:
		Draw_HLine										= Draw_HLine32;
		Draw_VLine										= Draw_VLine32;
		Draw_HLine_SrcAlpha								= Draw_HLine_SrcAlpha32;
		Draw_VLine_SrcAlpha								= Draw_VLine_SrcAlpha32;
		Draw_Clipped_HLine								= Draw_Clipped_HLine32;
		Draw_Clipped_VLine								= Draw_Clipped_VLine32;
		Draw_Clipped_HLine_SrcAlpha						= Draw_Clipped_HLine_SrcAlpha32;
		Draw_Clipped_VLine_SrcAlpha						= Draw_Clipped_VLine_SrcAlpha32;
		Draw_Line										= Draw_Line32;
		Draw_Line_ZbufferRW								= Draw_Line_ZbufferRW32;
		Draw_Line_SrcAlpha								= Draw_Line_SrcAlpha32;
		Draw_Line_ZbufferR_SrcAlpha						= Draw_Line_ZbufferR_SrcAlpha32;
		Draw_Clipped_Line								= Draw_Clipped_Line32;
		Draw_Clipped_Line_ZbufferRW						= Draw_Clipped_Line_ZbufferRW32;
		Draw_Clipped_Line_SrcAlpha						= Draw_Clipped_Line_SrcAlpha32;
		Draw_Clipped_Line_ZbufferR_SrcAlpha				= Draw_Clipped_Line_ZbufferR_SrcAlpha32;
		Draw_Rectangle									= Draw_Rectangle32;
		Draw_Rectangle_SrcAlpha							= Draw_Rectangle_SrcAlpha32;
		Draw_Rectangle_Texture_SrcKey					= Draw_Rectangle_Texture_SrcKey32;
		Draw_Rectangle_Texture_ZBufferW					= Draw_Rectangle_Texture_ZBufferW32;
		Draw_Rectangle_ZBufferR_SrcAlpha				= Draw_Rectangle_ZBufferR_SrcAlpha32;
		Draw_Rectangle_ZbufferR_TextureAlpha			= Draw_Rectangle_ZbufferR_TextureAlpha32;
		Draw_Clipped_Rectangle							= Draw_Clipped_Rectangle32;
		Draw_Clipped_Rectangle_SrcAlpha					= Draw_Clipped_Rectangle_SrcAlpha32;
		Draw_Clipped_Rectangle_Texture_SrcKey			= Draw_Clipped_Rectangle_Texture_SrcKey32;
		Draw_Clipped_Rectangle_Texture_ZBufferW			= Draw_Clipped_Rectangle_Texture_ZBufferW32;
		Draw_Clipped_Rectangle_ZBufferR_SrcAlpha		= Draw_Clipped_Rectangle_ZBufferR_SrcAlpha32;
		Draw_Clipped_Rectangle_ZbufferR_TextureAlpha	= Draw_Clipped_Rectangle_ZbufferR_TextureAlpha32;
		Draw_Triangle									= Draw_Triangle32;
		Draw_Triangle_ZBufferRW							= Draw_Triangle_ZBufferRW32;
		Draw_Triangle_Texture_ZBufferRW					= Draw_Triangle_Texture_ZBufferRW32;
		Draw_Triangle_Texture_PerspectiveLP_ZBufferRW	= Draw_Triangle_Texture_PerspectiveLP_ZBufferRW16;
		Draw_Triangle_Gouraud_ZBufferRW					= Draw_Triangle_Gouraud_ZBufferRW32;
		Draw_Triangle_Gouraud_Texture_ZBufferRW			= Draw_Triangle_Gouraud_Texture_ZBufferRW32;
		Draw_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW	= Draw_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW16;
		Draw_Clipped_Triangle							= Draw_Clipped_Triangle32;
		Draw_Clipped_Triangle_ZBufferRW					= Draw_Clipped_Triangle_ZBufferRW32;
		Draw_Clipped_Triangle_Texture_ZBufferRW			= Draw_Clipped_Triangle_Texture_ZBufferRW32;
		Draw_Clipped_Triangle_Texture_PerspectiveLP_ZBufferRW	= Draw_Clipped_Triangle_Texture_PerspectiveLP_ZBufferRW32;
		Draw_Clipped_Triangle_Gouraud_ZBufferRW			= Draw_Clipped_Triangle_Gouraud_ZBufferRW32;
		Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW	= Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW32;
		Draw_Clipped_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW	= Draw_Clipped_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW32;
		break;

	default:
		ON_ERROR_GOTO(SFORMAT1(gbuffer, "unsupported color bpp: %d", bpp));
	}
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API void Draw_HLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int x1 = (int)pv1->x;
	int y0 = (int)pv0->y;

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	int dx = x1 - x0;
	if(dx < 0)
	{
		ps += (dx + 1) << _16BIT_BYTES_SHIFT;
		dx = -dx;
	}

	Mem_Set_Word(ps, (unsigned short)pv0->c_diff, dx);
}

T3DLIB_API void Draw_HLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int x1 = (int)pv1->x;
	int y0 = (int)pv0->y;

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	int dx = x1 - x0;
	if(dx < 0)
	{
		ps += (dx + 1) << _32BIT_BYTES_SHIFT;
		dx = -dx;
	}

	Mem_Set_Quad(ps, pv0->c_diff, dx);
}

T3DLIB_API void Draw_VLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int y1 = (int)pv1->y;

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	int dy = y1 - y0;
	if(dy < 0)
	{
		ps += (dy + 1) << prc->s_pitch_shift;
		dy = -dy;
	}

	while(dy--)
	{
		*(unsigned short *)ps = (unsigned short)pv0->c_diff;
		ps += prc->s_pitch;
	}
}

T3DLIB_API void Draw_VLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int y1 = (int)pv1->y;

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	int dy = y1 - y0;
	if(dy < 0)
	{
		ps += (dy + 1) << prc->s_pitch_shift;
		dy = -dy;
	}

	while(dy--)
	{
		*(unsigned int *)ps = pv0->c_diff;
		ps += prc->s_pitch;
	}
}

T3DLIB_API void Draw_HLine_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int x1 = (int)pv1->x;
	int y0 = (int)pv0->y;

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	int dx = x1 - x0;
	if(dx < 0)
	{
		ps += (dx + 1) << _16BIT_BYTES_SHIFT;
		dx = -dx;
	}

	while(dx--)
	{
		*(unsigned short *)ps = ALPHA16_COMB(
				prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)ps);

		ps += _16BIT_BYTES;
	}
}

T3DLIB_API void Draw_HLine_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int x1 = (int)pv1->x;
	int y0 = (int)pv0->y;

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	int dx = x1 - x0;
	if(dx < 0)
	{
		ps += (dx + 1) << _32BIT_BYTES_SHIFT;
		dx = -dx;
	}

	while(dx--)
	{
		*(unsigned int *)ps = ALPHA32_COMB(
				prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)ps);

		ps += _32BIT_BYTES;
	}
}

T3DLIB_API void Draw_VLine_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int y1 = (int)pv1->y;

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	int dy = y1 - y0;
	if(dy < 0)
	{
		ps += (dy + 1) << prc->s_pitch_shift;
		dy = -dy;
	}

	while(dy--)
	{
		*(unsigned short *)ps = ALPHA16_COMB(
				prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)ps);

		ps += prc->s_pitch;
	}
}

T3DLIB_API void Draw_VLine_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int y1 = (int)pv1->y;

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	int dy = y1 - y0;
	if(dy < 0)
	{
		ps += (dy + 1) << prc->s_pitch_shift;
		dy = -dy;
	}

	while(dy--)
	{
		*(unsigned int *)ps = ALPHA32_COMB(
				prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)ps);

		ps += prc->s_pitch;
	}
}

T3DLIB_API bool Clip_HLine(const RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1)
{
	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(pv0->x < prc->fmin_clip_x)
		reg0 |= CLIP_REGION_W;
	else if(pv0->x > prc->fmax_clip_x)
		reg0 |= CLIP_REGION_E;

	if(pv1->x < prc->fmin_clip_x - 1.0f)
		reg1 |= CLIP_REGION_W;
	else if(pv1->x > prc->fmax_clip_x + 1.0f)
		reg1 |= CLIP_REGION_E;

	if(reg0 & reg1)
		return false;

	switch(reg0)
	{
	case CLIP_REGION_W:
		pv0->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_E:
		pv0->x = prc->fmax_clip_x;
		break;

	default:
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_W:
		pv1->x = prc->fmin_clip_x - 1.0f;
		break;

	case CLIP_REGION_E:
		pv1->x = prc->fmax_clip_x + 1.0f;
		break;

	default:
		break;
	}

	if(pv0->y >= prc->fmin_clip_y && pv0->y <= prc->fmax_clip_y)
	{
		return true;
	}
	return false;
}

T3DLIB_API bool Clip_VLine(const RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1)
{
	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(pv0->y < prc->fmin_clip_y)
		reg0 |= CLIP_REGION_W;
	else if(pv0->y > prc->fmax_clip_y)
		reg0 |= CLIP_REGION_E;

	if(pv1->y < prc->fmin_clip_y - 1.0f)
		reg1 |= CLIP_REGION_W;
	else if(pv1->y > prc->fmax_clip_y + 1.0f)
		reg1 |= CLIP_REGION_E;

	if(reg0 & reg1)
		return false;

	switch(reg0)
	{
	case CLIP_REGION_W:
		pv0->y = prc->fmin_clip_y;
		break;

	case CLIP_REGION_E:
		pv0->y = prc->fmax_clip_y;
		break;

	default:
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_W:
		pv1->y = prc->fmin_clip_y - 1.0f;
		break;

	case CLIP_REGION_E:
		pv1->y = prc->fmax_clip_y + 1.0f;
		break;

	default:
		break;
	}

	if(pv0->x >= prc->fmin_clip_x && pv0->x <= prc->fmax_clip_x)
	{
		return true;
	}
	return false;
}

T3DLIB_API void Draw_Clipped_HLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_HLine(prc, &cv0, &cv1))
		Draw_HLine16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_HLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_HLine(prc, &cv0, &cv1))
		Draw_HLine32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_VLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_VLine(prc, &cv0, &cv1))
		Draw_VLine16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_VLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_VLine(prc, &cv0, &cv1))
		Draw_VLine32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_HLine_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_HLine(prc, &cv0, &cv1))
		Draw_HLine_SrcAlpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_HLine_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_HLine(prc, &cv0, &cv1))
		Draw_HLine_SrcAlpha32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_VLine_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_VLine(prc, &cv0, &cv1))
		Draw_VLine_SrcAlpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_VLine_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_VLine(prc, &cv0, &cv1))
		Draw_VLine_SrcAlpha32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Line16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	int dx = x1 - x0;
	int dy = y1 - y0;

	register int dx2 = abs(dx) << 1;
	register int dy2 = abs(dy) << 1;

	if(abs(dx) > abs(dy))
	{
		if(dx < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);
		}

		int s_pitch;
		if(dy < 0)
		{
			s_pitch = -prc->s_pitch;
		}
		else
		{
			s_pitch = prc->s_pitch;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);

		int error = dy2 - dx;
		assert(dx >= 0);
		while(dx--)
		{
			*(unsigned short *)ps = (short)pv0->c_diff;

			if(error >= 0)
			{
				ps += s_pitch;
				error -= dx2;
			}

			ps += _16BIT_BYTES;
			error += dy2;
		}
	}
	else
	{
		if(dy < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);
		}

		int s_bytes;
		if(dx < 0)
		{
			s_bytes = -_16BIT_BYTES;
		}
		else
		{
			s_bytes = _16BIT_BYTES;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);

		int error = dx2 - dy;
		assert(dy >= 0);
		while(dy--)
		{
			*(unsigned short *)ps = (short)pv0->c_diff;

			if(error >= 0)
			{
				ps += s_bytes;
				error -= dy2;
			}

			ps += prc->s_pitch;
			error += dx2;
		}
	}
}

T3DLIB_API void Draw_Line32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	int dx = x1 - x0;
	int dy = y1 - y0;

	register int dx2 = abs(dx) << 1;
	register int dy2 = abs(dy) << 1;

	if(abs(dx) > abs(dy))
	{
		if(dx < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);
		}

		int s_pitch;
		if(dy < 0)
		{
			s_pitch = -prc->s_pitch;
		}
		else
		{
			s_pitch = prc->s_pitch;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);

		int error = dy2 - dx;
		assert(dx >= 0);
		while(dx--)
		{
			*(unsigned int *)ps = pv0->c_diff;

			if(error >= 0)
			{
				ps += s_pitch;
				error -= dx2;
			}

			ps += _32BIT_BYTES;
			error += dy2;
		}
	}
	else
	{
		if(dy < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);
		}

		int s_bytes;
		if(dx < 0)
		{
			s_bytes = -_32BIT_BYTES;
		}
		else
		{
			s_bytes = _32BIT_BYTES;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);

		int error = dx2 - dy;
		assert(dy >= 0);
		while(dy--)
		{
			*(unsigned int *)ps = pv0->c_diff;

			if(error >= 0)
			{
				ps += s_bytes;
				error -= dy2;
			}

			ps += prc->s_pitch;
			error += dx2;
		}
	}
}

T3DLIB_API void Draw_Line_ZbufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	int dx = x1 - x0;
	int dy = y1 - y0;

	register int dx2 = abs(dx) << 1;
	register int dy2 = abs(dy) << 1;

	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	FIXP28 z1 = (FIXP28)(1 / pv1->z * FIXP28_MAG);

	if(abs(dx) > abs(dy))
	{
		if(dx < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);

			SWAP(z0, z1, itmp);
		}

		int s_pitch;
		int z_pitch;
		if(dy < 0)
		{
			s_pitch = -prc->s_pitch;
			z_pitch = -prc->z_pitch;
		}
		else
		{
			s_pitch = prc->s_pitch;
			z_pitch = prc->z_pitch;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);

		unsigned char * pz = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);

		if(dx > 0)
		{
			FIXP28 dz = (z1 - z0) / dx;

			int error = dy2 - dx;
			while(dx--)
			{
				if(z0 >= _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
				{
					*(unsigned short *)ps = (unsigned short)pv0->c_diff;

					*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
				}

				if(error >= 0)
				{
					ps += s_pitch;
					error -= dx2;

					pz += z_pitch;
				}

				ps += _16BIT_BYTES;
				error += dy2;

				pz += _ZBUFF_BYTES;
				z0 += dz;
			}
		}
	}
	else
	{
		if(dy < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);

			SWAP(z0, z1, itmp);
		}

		int s_bytes;
		int z_bytes;
		if(dx < 0)
		{
			s_bytes = -_16BIT_BYTES;
			z_bytes = -_ZBUFF_BYTES;
		}
		else
		{
			s_bytes = _16BIT_BYTES;
			z_bytes = _ZBUFF_BYTES;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);

		unsigned char * pz = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);

		if(dy > 0)
		{
			FIXP28 dz = (z1 - z0) / dy;

			int error = dx2 - dy;
			while(dy--)
			{
				if(z0 >= _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
				{
					*(unsigned short *)ps = (unsigned short)pv0->c_diff;

					*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
				}

				if(error >= 0)
				{
					ps += s_bytes;
					error -= dy2;

					pz += z_bytes;
				}

				ps += prc->s_pitch;
				error += dx2;

				pz += prc->z_pitch;
				z0 += dz;
			}
		}
	}
}

T3DLIB_API void Draw_Line_ZbufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	int dx = x1 - x0;
	int dy = y1 - y0;

	register int dx2 = abs(dx) << 1;
	register int dy2 = abs(dy) << 1;

	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	FIXP28 z1 = (FIXP28)(1 / pv1->z * FIXP28_MAG);

	if(abs(dx) > abs(dy))
	{
		if(dx < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);

			SWAP(z0, z1, itmp);
		}

		int s_pitch;
		int z_pitch;
		if(dy < 0)
		{
			s_pitch = -prc->s_pitch;
			z_pitch = -prc->z_pitch;
		}
		else
		{
			s_pitch = prc->s_pitch;
			z_pitch = prc->z_pitch;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);

		unsigned char * pz = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);

		if(dx > 0)
		{
			FIXP28 dz = (z1 - z0) / dx;

			int error = dy2 - dx;
			while(dx--)
			{
				if(z0 >= _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
				{
					*(unsigned int *)ps = pv0->c_diff;

					*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
				}

				if(error >= 0)
				{
					ps += s_pitch;
					error -= dx2;

					pz += z_pitch;
				}

				ps += _32BIT_BYTES;
				error += dy2;

				pz += _ZBUFF_BYTES;
				z0 += dz;
			}
		}
	}
	else
	{
		if(dy < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);

			SWAP(z0, z1, itmp);
		}

		int s_bytes;
		int z_bytes;
		if(dx < 0)
		{
			s_bytes = -_32BIT_BYTES;
			z_bytes = -_ZBUFF_BYTES;
		}
		else
		{
			s_bytes = _32BIT_BYTES;
			z_bytes = _ZBUFF_BYTES;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);

		unsigned char * pz = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);

		if(dy > 0)
		{
			FIXP28 dz = (z1 - z0) / dy;

			int error = dx2 - dy;
			while(dy--)
			{
				if(z0 >= _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
				{
					*(unsigned int *)ps = pv0->c_diff;

					*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
				}

				if(error >= 0)
				{
					ps += s_bytes;
					error -= dy2;

					pz += z_bytes;
				}

				ps += prc->s_pitch;
				error += dx2;

				pz += prc->z_pitch;
				z0 += dz;
			}
		}
	}
}

T3DLIB_API void Draw_Line_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	int dx = x1 - x0;
	int dy = y1 - y0;

	register int dx2 = abs(dx) << 1;
	register int dy2 = abs(dy) << 1;

	if(abs(dx) > abs(dy))
	{
		if(dx < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);
		}

		int s_pitch;
		if(dy < 0)
		{
			s_pitch = -prc->s_pitch;
		}
		else
		{
			s_pitch = prc->s_pitch;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);

		int error = dy2 - dx;
		assert(dx >= 0);
		while(dx--)
		{
			*(unsigned short *)ps = ALPHA16_COMB(
					prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)ps);

			if(error >= 0)
			{
				ps += s_pitch;
				error -= dx2;
			}

			ps += _16BIT_BYTES;
			error += dy2;
		}
	}
	else
	{
		if(dy < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);
		}

		int s_bytes;
		if(dx < 0)
		{
			s_bytes = -_16BIT_BYTES;
		}
		else
		{
			s_bytes = _16BIT_BYTES;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);

		int error = dx2 - dy;
		assert(dy >= 0);
		while(dy--)
		{
			*(unsigned short *)ps = ALPHA16_COMB(
					prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)ps);

			if(error >= 0)
			{
				ps += s_bytes;
				error -= dy2;
			}

			ps += prc->s_pitch;
			error += dx2;
		}
	}
}

T3DLIB_API void Draw_Line_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	int dx = x1 - x0;
	int dy = y1 - y0;

	register int dx2 = abs(dx) << 1;
	register int dy2 = abs(dy) << 1;

	if(abs(dx) > abs(dy))
	{
		if(dx < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);
		}

		int s_pitch;
		if(dy < 0)
		{
			s_pitch = -prc->s_pitch;
		}
		else
		{
			s_pitch = prc->s_pitch;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);

		int error = dy2 - dx;
		assert(dx >= 0);
		while(dx--)
		{
			*(unsigned int *)ps = ALPHA32_COMB(
					prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)ps);

			if(error >= 0)
			{
				ps += s_pitch;
				error -= dx2;
			}

			ps += _32BIT_BYTES;
			error += dy2;
		}
	}
	else
	{
		if(dy < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);
		}

		int s_bytes;
		if(dx < 0)
		{
			s_bytes = -_32BIT_BYTES;
		}
		else
		{
			s_bytes = _32BIT_BYTES;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);

		int error = dx2 - dy;
		assert(dy >= 0);
		while(dy--)
		{
			*(unsigned int *)ps = ALPHA32_COMB(
					prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)ps);

			if(error >= 0)
			{
				ps += s_bytes;
				error -= dy2;
			}

			ps += prc->s_pitch;
			error += dx2;
		}
	}
}

T3DLIB_API void Draw_Line_ZbufferR_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	int dx = x1 - x0;
	int dy = y1 - y0;

	register int dx2 = abs(dx) << 1;
	register int dy2 = abs(dy) << 1;

	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	FIXP28 z1 = (FIXP28)(1 / pv1->z * FIXP28_MAG);

	if(abs(dx) > abs(dy))
	{
		if(dx < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);

			SWAP(z0, z1, itmp);
		}

		int s_pitch;
		int z_pitch;
		if(dy < 0)
		{
			s_pitch = -prc->s_pitch;
			z_pitch = -prc->z_pitch;
		}
		else
		{
			s_pitch = prc->s_pitch;
			z_pitch = prc->z_pitch;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);

		unsigned char * pz = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);

		if(dx > 0)
		{
			FIXP28 dz = (z1 - z0) / dx;

			int error = dy2 - dx;
			while(dx--)
			{
				if(z0 >= _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
				{
					*(unsigned short *)ps = ALPHA16_COMB(
							prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)ps);

					//*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
				}

				if(error >= 0)
				{
					ps += s_pitch;
					error -= dx2;

					pz += z_pitch;
				}

				ps += _16BIT_BYTES;
				error += dy2;

				pz += _ZBUFF_BYTES;
				z0 += dz;
			}
		}
	}
	else
	{
		if(dy < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);

			SWAP(z0, z1, itmp);
		}

		int s_bytes;
		int z_bytes;
		if(dx < 0)
		{
			s_bytes = -_16BIT_BYTES;
			z_bytes = -_ZBUFF_BYTES;
		}
		else
		{
			s_bytes = _16BIT_BYTES;
			z_bytes = _ZBUFF_BYTES;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);

		unsigned char * pz = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);

		if(dy > 0)
		{
			FIXP28 dz = (z1 - z0) / dy;

			int error = dx2 - dy;
			while(dy--)
			{
				if(z0 >= _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
				{
					*(unsigned short *)ps = ALPHA16_COMB(
							prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)ps);

					//*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
				}

				if(error >= 0)
				{
					ps += s_bytes;
					error -= dy2;

					pz += z_bytes;
				}

				ps += prc->s_pitch;
				error += dx2;

				pz += prc->z_pitch;
				z0 += dz;
			}
		}
	}
}

T3DLIB_API void Draw_Line_ZbufferR_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	int dx = x1 - x0;
	int dy = y1 - y0;

	register int dx2 = abs(dx) << 1;
	register int dy2 = abs(dy) << 1;

	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	FIXP28 z1 = (FIXP28)(1 / pv1->z * FIXP28_MAG);

	if(abs(dx) > abs(dy))
	{
		if(dx < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);

			SWAP(z0, z1, itmp);
		}

		int s_pitch;
		int z_pitch;
		if(dy < 0)
		{
			s_pitch = -prc->s_pitch;
			z_pitch = -prc->z_pitch;
		}
		else
		{
			s_pitch = prc->s_pitch;
			z_pitch = prc->z_pitch;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);

		unsigned char * pz = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);

		if(dx > 0)
		{
			FIXP28 dz = (z1 - z0) / dx;

			int error = dy2 - dx;
			while(dx--)
			{
				if(z0 >= _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
				{
					*(unsigned int *)ps = ALPHA32_COMB(
							prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)ps);

					//*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
				}

				if(error >= 0)
				{
					ps += s_pitch;
					error -= dx2;

					pz += z_pitch;
				}

				ps += _32BIT_BYTES;
				error += dy2;

				pz += _ZBUFF_BYTES;
				z0 += dz;
			}
		}
	}
	else
	{
		if(dy < 0)
		{
			int itmp;
			SWAP(x0, x1, itmp);
			SWAP(y0, y1, itmp);

			NEG(dx);
			NEG(dy);

			SWAP(z0, z1, itmp);
		}

		int s_bytes;
		int z_bytes;
		if(dx < 0)
		{
			s_bytes = -_32BIT_BYTES;
			z_bytes = -_ZBUFF_BYTES;
		}
		else
		{
			s_bytes = _32BIT_BYTES;
			z_bytes = _ZBUFF_BYTES;
		}

		unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);

		unsigned char * pz = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);

		if(dy > 0)
		{
			FIXP28 dz = (z1 - z0) / dy;

			int error = dx2 - dy;
			while(dy--)
			{
				if(z0 >= _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
				{
					*(unsigned int *)ps = ALPHA32_COMB(
							prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)ps);

					//*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
				}

				if(error >= 0)
				{
					ps += s_bytes;
					error -= dy2;

					pz += z_bytes;
				}

				ps += prc->s_pitch;
				error += dx2;

				pz += prc->z_pitch;
				z0 += dz;
			}
		}
	}
}

T3DLIB_API bool Clip_Line(const RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1)
{
	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(pv0->x < prc->fmin_clip_x)
		reg0 |= CLIP_REGION_W;
	else if(pv0->x > prc->fmax_clip_x)
		reg0 |= CLIP_REGION_E;

	if(pv0->y < prc->fmin_clip_y)
		reg0 |= CLIP_REGION_N;
	else if(pv0->y > prc->fmax_clip_y)
		reg0 |= CLIP_REGION_S;

	if(pv1->x < prc->fmin_clip_x)
		reg1 |= CLIP_REGION_W;
	else if(pv1->x > prc->fmax_clip_x)
		reg1 |= CLIP_REGION_E;

	if(pv1->y < prc->fmin_clip_y)
		reg1 |= CLIP_REGION_N;
	else if(pv1->y > prc->fmax_clip_y)
		reg1 |= CLIP_REGION_S;

	if(reg0 == 0 && reg1 == 0)
		return true;

	if(reg0 & reg1)
		return false;

	REAL cx0, cy0;
	REAL cx1, cy1;

	switch(reg0)
	{
	case CLIP_REGION_N:
		cx0 = LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmin_clip_y;
		break;

	case CLIP_REGION_S:
		cx0 = LINE2D_INTERSECT(prc->fmax_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmax_clip_y;
		break;

	case CLIP_REGION_W:
		cx0 = prc->fmin_clip_x;
		cy0 = LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
		break;

	case CLIP_REGION_E:
		cx0 = prc->fmax_clip_x;
		cy0 = LINE2D_INTERSECT(prc->fmax_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
		break;

	case CLIP_REGION_NW:
		cx0 = LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmin_clip_y;
		if(cx0 < prc->fmin_clip_x || cx0 > prc->fmax_clip_x)
		{
			cx0 = prc->fmin_clip_x;
			cy0 = LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
		}
		break;

	case CLIP_REGION_NE:
		cx0 = LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmin_clip_y;
		if(cx0 < prc->fmin_clip_x || cx0 > prc->fmax_clip_x)
		{
			cx0 = prc->fmax_clip_x;
			cy0 = LINE2D_INTERSECT(prc->fmax_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
		}
		break;

	case CLIP_REGION_SW:
		cx0 = LINE2D_INTERSECT(prc->fmax_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmax_clip_y;
		if(cx0 < prc->fmin_clip_x || cx0 > prc->fmax_clip_x)
		{
			cx0 = prc->fmin_clip_x;
			cy0 = LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
		}
		break;

	case CLIP_REGION_SE:
		cx0 = LINE2D_INTERSECT(prc->fmax_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmax_clip_y;
		if(cx0 < prc->fmin_clip_x || cx0 > prc->fmax_clip_x)
		{
			cx0 = prc->fmax_clip_x;
			cy0 = LINE2D_INTERSECT(prc->fmax_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
		}
		break;

	default:
		cx0 = pv0->x;
		cy0 = pv0->y;
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_N:
		cx1 = LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmin_clip_y;
		break;

	case CLIP_REGION_S:
		cx1 = LINE2D_INTERSECT(prc->fmax_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmax_clip_y;
		break;

	case CLIP_REGION_W:
		cx1 = prc->fmin_clip_x;
		cy1 = LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
		break;

	case CLIP_REGION_E:
		cx1 = prc->fmax_clip_x;
		cy1 = LINE2D_INTERSECT(prc->fmax_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
		break;

	case CLIP_REGION_NW:
		cx1 = LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmin_clip_y;
		if(cx1 < prc->fmin_clip_x || cx1 > prc->fmax_clip_x)
		{
			cx1 = prc->fmin_clip_x;
			cy1 = LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
		}
		break;

	case CLIP_REGION_NE:
		cx1 = LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmin_clip_y;
		if(cx1 < prc->fmin_clip_x || cx1 > prc->fmax_clip_x)
		{
			cx1 = prc->fmax_clip_x;
			cy1 = LINE2D_INTERSECT(prc->fmax_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
		}
		break;

	case CLIP_REGION_SW:
		cx1 = LINE2D_INTERSECT(prc->fmax_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmax_clip_y;
		if(cx1 < prc->fmin_clip_x || cx1 > prc->fmax_clip_x)
		{
			cx1 = prc->fmin_clip_x;
			cy1 = LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
		}
		break;

	case CLIP_REGION_SE:
		cx1 = LINE2D_INTERSECT(prc->fmax_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmax_clip_y;
		if(cx1 < prc->fmin_clip_x || cx1 > prc->fmax_clip_x)
		{
			cx1 = prc->fmax_clip_x;
			cy1 = LINE2D_INTERSECT(prc->fmax_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
		}
		break;

	default:
		cx1 = pv1->x;
		cy1 = pv1->y;
		break;
	}

	if(	cx0 >= prc->fmin_clip_x && cx0 <= prc->fmax_clip_x &&
		cy0 >= prc->fmin_clip_y && cy0 <= prc->fmax_clip_y &&
		cx1 >= prc->fmin_clip_x && cx1 <= prc->fmax_clip_x &&
		cy1 >= prc->fmin_clip_y && cy1 <= prc->fmax_clip_y)
	{
		pv0->x = cx0;
		pv0->y = cy0;
		pv1->x = cx1;
		pv1->y = cy1;
		return true;
	}
	return false;
}

T3DLIB_API bool Clip_Line_Zbuffer(const RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1)
{
	//VERTEXV1 cv0, cv1;
	//memcpy(&cv0, pv0, sizeof(*pv0));
	//memcpy(&cv1, pv1, sizeof(*pv1));

	//if(Clip_Line(prc, &cv0, &cv1))
	//{
	//	cv0.z = 1 / LINE2D_INTERSECT(cv0.x, pv1->x, pv0->x, 1 / pv1->z, 1 / pv0->z);
	//	cv1.z = 1 / LINE2D_INTERSECT(cv1.x, pv1->x, pv0->x, 1 / pv1->z, 1 / pv0->z);

	//	memcpy(pv0, &cv0, sizeof(*pv0));
	//	memcpy(pv1, &cv1, sizeof(*pv1));
	//	return true;
	//}
	//return false;

	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(pv0->x < prc->fmin_clip_x)
		reg0 |= CLIP_REGION_W;
	else if(pv0->x > prc->fmax_clip_x)
		reg0 |= CLIP_REGION_E;

	if(pv0->y < prc->fmin_clip_y)
		reg0 |= CLIP_REGION_N;
	else if(pv0->y > prc->fmax_clip_y)
		reg0 |= CLIP_REGION_S;

	if(pv1->x < prc->fmin_clip_x)
		reg1 |= CLIP_REGION_W;
	else if(pv1->x > prc->fmax_clip_x)
		reg1 |= CLIP_REGION_E;

	if(pv1->y < prc->fmin_clip_y)
		reg1 |= CLIP_REGION_N;
	else if(pv1->y > prc->fmax_clip_y)
		reg1 |= CLIP_REGION_S;

	if(reg0 == 0 && reg1 == 0)
		return true;

	if(reg0 & reg1)
		return false;

	REAL cx0, cy0, cz0; // ***
	REAL cx1, cy1, cz1; // ***

	switch(reg0)
	{
	case CLIP_REGION_N:
		cx0 = LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmin_clip_y;
		cz0 = 1 / LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, 1 / pv0->z, 1 / pv1->z); // ***
		break;

	case CLIP_REGION_S:
		cx0 = LINE2D_INTERSECT(prc->fmax_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmax_clip_y;
		cz0 = 1 / LINE2D_INTERSECT(prc->fmax_clip_y, pv0->y, pv1->y, 1 / pv0->z, 1 / pv1->z); // ***
		break;

	case CLIP_REGION_W:
		cx0 = prc->fmin_clip_x;
		cy0 = LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
		cz0 = 1 / LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, 1 / pv0->z, 1 / pv1->z); // ***
		break;

	case CLIP_REGION_E:
		cx0 = prc->fmax_clip_x;
		cy0 = LINE2D_INTERSECT(prc->fmax_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
		cz0 = 1 / LINE2D_INTERSECT(prc->fmax_clip_x, pv0->x, pv1->x, 1 / pv0->z, 1 / pv1->z); // ***
		break;

	case CLIP_REGION_NW:
		cx0 = LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmin_clip_y;
		cz0 = 1 / LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, 1 / pv0->z, 1 / pv1->z); // ***
		if(cx0 < prc->fmin_clip_x || cx0 > prc->fmax_clip_x)
		{
			cx0 = prc->fmin_clip_x;
			cy0 = LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
			cz0 = 1 / LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, 1 / pv0->z, 1 / pv1->z); // ***
		}
		break;

	case CLIP_REGION_NE:
		cx0 = LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmin_clip_y;
		cz0 = 1 / LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, 1 / pv0->z, 1 / pv1->z); // ***
		if(cx0 < prc->fmin_clip_x || cx0 > prc->fmax_clip_x)
		{
			cx0 = prc->fmax_clip_x;
			cy0 = LINE2D_INTERSECT(prc->fmax_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
			cz0 = 1 / LINE2D_INTERSECT(prc->fmax_clip_x, pv0->x, pv1->x, 1 / pv0->z, 1 / pv1->z); // ***
		}
		break;

	case CLIP_REGION_SW:
		cx0 = LINE2D_INTERSECT(prc->fmax_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmax_clip_y;
		cz0 = 1 / LINE2D_INTERSECT(prc->fmax_clip_y, pv0->y, pv1->y, 1 / pv0->z, 1 / pv1->z); // ***
		if(cx0 < prc->fmin_clip_x || cx0 > prc->fmax_clip_x)
		{
			cx0 = prc->fmin_clip_x;
			cy0 = LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
			cz0 = 1 / LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, 1 / pv0->z, 1 / pv1->z); // ***
		}
		break;

	case CLIP_REGION_SE:
		cx0 = LINE2D_INTERSECT(prc->fmax_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmax_clip_y;
		cz0 = 1 / LINE2D_INTERSECT(prc->fmax_clip_y, pv0->y, pv1->y, 1 / pv0->z, 1 / pv1->z); // ***
		if(cx0 < prc->fmin_clip_x || cx0 > prc->fmax_clip_x)
		{
			cx0 = prc->fmax_clip_x;
			cy0 = LINE2D_INTERSECT(prc->fmax_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
			cz0 = 1 / LINE2D_INTERSECT(prc->fmax_clip_x, pv0->x, pv1->x, 1 / pv0->z, 1 / pv1->z); // ***
		}
		break;

	default:
		cx0 = pv0->x;
		cy0 = pv0->y;
		cz0 = pv0->z; // ***
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_N:
		cx1 = LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmin_clip_y;
		cz1 = 1 / LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, 1 / pv1->z, 1 / pv0->z); // ***
		break;

	case CLIP_REGION_S:
		cx1 = LINE2D_INTERSECT(prc->fmax_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmax_clip_y;
		cz1 = 1 / LINE2D_INTERSECT(prc->fmax_clip_y, pv1->y, pv0->y, 1 / pv1->z, 1 / pv0->z); // ***
		break;

	case CLIP_REGION_W:
		cx1 = prc->fmin_clip_x;
		cy1 = LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
		cz1 = 1 / LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, 1 / pv1->z, 1 / pv0->z); // ***
		break;

	case CLIP_REGION_E:
		cx1 = prc->fmax_clip_x;
		cy1 = LINE2D_INTERSECT(prc->fmax_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
		cz1 = 1 / LINE2D_INTERSECT(prc->fmax_clip_x, pv1->x, pv0->x, 1 / pv1->z, 1 / pv0->z); // ***
		break;

	case CLIP_REGION_NW:
		cx1 = LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmin_clip_y;
		cz1 = 1 / LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, 1 / pv1->z, 1 / pv0->z); // ***
		if(cx1 < prc->fmin_clip_x || cx1 > prc->fmax_clip_x)
		{
			cx1 = prc->fmin_clip_x;
			cy1 = LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
			cz1 = 1 / LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, 1 / pv1->z, 1 / pv0->z); // ***
		}
		break;

	case CLIP_REGION_NE:
		cx1 = LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmin_clip_y;
		cz1 = 1 / LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, 1 / pv1->z, 1 / pv0->z); // ***
		if(cx1 < prc->fmin_clip_x || cx1 > prc->fmax_clip_x)
		{
			cx1 = prc->fmax_clip_x;
			cy1 = LINE2D_INTERSECT(prc->fmax_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
			cz1 = 1 / LINE2D_INTERSECT(prc->fmax_clip_x, pv1->x, pv0->x, 1 / pv1->z, 1 / pv0->z); // ***
		}
		break;

	case CLIP_REGION_SW:
		cx1 = LINE2D_INTERSECT(prc->fmax_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmax_clip_y;
		cz1 = 1 / LINE2D_INTERSECT(prc->fmax_clip_y, pv1->y, pv0->y, 1 / pv1->z, 1 / pv0->z); // ***
		if(cx1 < prc->fmin_clip_x || cx1 > prc->fmax_clip_x)
		{
			cx1 = prc->fmin_clip_x;
			cy1 = LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
			cz1 = 1 / LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, 1 / pv1->z, 1 / pv0->z); // ***
		}
		break;

	case CLIP_REGION_SE:
		cx1 = LINE2D_INTERSECT(prc->fmax_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmax_clip_y;
		cz1 = 1 / LINE2D_INTERSECT(prc->fmax_clip_y, pv1->y, pv0->y, 1 / pv1->z, 1 / pv0->z); // ***
		if(cx1 < prc->fmin_clip_x || cx1 > prc->fmax_clip_x)
		{
			cx1 = prc->fmax_clip_x;
			cy1 = LINE2D_INTERSECT(prc->fmax_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
			cz1 = 1 / LINE2D_INTERSECT(prc->fmax_clip_x, pv1->x, pv0->x, 1 / pv1->z, 1 / pv0->z); // ***
		}
		break;

	default:
		cx1 = pv1->x;
		cy1 = pv1->y;
		cz1 = pv1->z; // ***
		break;
	}

	if(	cx0 >= prc->fmin_clip_x && cx0 <= prc->fmax_clip_x &&
		cy0 >= prc->fmin_clip_y && cy0 <= prc->fmax_clip_y &&
		cx1 >= prc->fmin_clip_x && cx1 <= prc->fmax_clip_x &&
		cy1 >= prc->fmin_clip_y && cy1 <= prc->fmax_clip_y)
	{
		pv0->x = cx0;
		pv0->y = cy0;
		pv0->z = cz0; // ***
		pv1->x = cx1;
		pv1->y = cy1;
		pv1->z = cz1; // ***
		return true;
	}
	return false;
}

T3DLIB_API void Draw_Clipped_Line16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line(prc, &cv0, &cv1))
		Draw_Line16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Line32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line(prc, &cv0, &cv1))
		Draw_Line32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Line_ZbufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line_Zbuffer(prc, &cv0, &cv1))
		Draw_Line_ZbufferRW16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Line_ZbufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line_Zbuffer(prc, &cv0, &cv1))
		Draw_Line_ZbufferRW32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Line_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line(prc, &cv0, &cv1))
		Draw_Line_SrcAlpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Line_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line(prc, &cv0, &cv1))
		Draw_Line_SrcAlpha32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Line_ZbufferR_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line_Zbuffer(prc, &cv0, &cv1))
		Draw_Line_ZbufferR_SrcAlpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Line_ZbufferR_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line_Zbuffer(prc, &cv0, &cv1))
		Draw_Line_ZbufferR_SrcAlpha32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Rectangle16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	int dx = x1 - x0;
	int dy = y1 - y0;
	if(dx < 0)
	{
		p += dx << _16BIT_BYTES_SHIFT;
		dx = -dx;
	}
	if(dy < 0)
	{
		p += dy << prc->s_pitch_shift;
		dy = -dy;
	}
	while(dy--)
	{
		Mem_Set_Word(p, (unsigned short)pv0->c_diff, dx);
		p += prc->s_pitch;
	}
}

T3DLIB_API void Draw_Rectangle32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	int dx = x1 - x0;
	int dy = y1 - y0;
	if(dx < 0)
	{
		p += dx << _32BIT_BYTES_SHIFT;
		dx = -dx;
	}
	if(dy < 0)
	{
		p += dy << prc->s_pitch_shift;
		dy = -dy;
	}
	while(dy--)
	{
		Mem_Set_Quad(p, pv0->c_diff, dx);
		p += prc->s_pitch;
	}
}

T3DLIB_API void Draw_Rectangle_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	int dx = x1 - x0;
	int dy = y1 - y0;
	if(dx < 0)
	{
		p += dx << _16BIT_BYTES_SHIFT;
		dx = -dx;
	}
	if(dy < 0)
	{
		p += dy << prc->s_pitch_shift;
		dy = -dy;
	}
	while(dy--)
	{
		int c = dx;
		unsigned char * s = p;
		while(c--)
		{
			*(unsigned short *)s = ALPHA16_COMB(
					prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)s);

			s += _16BIT_BYTES;
		}
		p += prc->s_pitch;
	}
}

T3DLIB_API void Draw_Rectangle_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	int dx = x1 - x0;
	int dy = y1 - y0;
	if(dx < 0)
	{
		p += dx << _32BIT_BYTES_SHIFT;
		dx = -dx;
	}
	if(dy < 0)
	{
		p += dy << prc->s_pitch_shift;
		dy = -dy;
	}
	while(dy--)
	{
		int c = dx;
		unsigned char * s = p;
		while(c--)
		{
			*(unsigned int *)s = ALPHA32_COMB(
					prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)s);

			s += _32BIT_BYTES;
		}
		p += prc->s_pitch;
	}
}

T3DLIB_API void Draw_Rectangle_Texture_SrcKey16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1)
{
	int itmp;
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;
	FIXP16 u0 = pv0->u;
	FIXP16 v0 = pv0->v;
	FIXP16 u1 = pv1->u;
	FIXP16 v1 = pv1->v;

	if(x0 > x1) { SWAP(x0, x1, itmp); SWAP(u0, u1, itmp); }
	if(y0 > y1) { SWAP(y0, y1, itmp); SWAP(v0, v1, itmp); }
	int dx = x1 - x0;
	int dy = y1 - y0;
	FIXP16 du = 0;
	FIXP16 dv = 0;
	if(dx != 0) { du = (u1 - u0) / dx; }
	if(dy != 0) { dv = (v1 - v0) / dy; }

	unsigned char * psl = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	FIXP28 sv = v0;
	while(dy--)
	{
		unsigned char * ps = psl;
		unsigned char * pt = prc->t_pbuffer + (sv >> FIXP16_SHIFT << prc->t_pitch_shift);
		FIXP28 su = u0;
		int count = dx;
		while(count--)
		{
			unsigned int src_color = *(unsigned short *)(pt + (su >> FIXP16_SHIFT << _16BIT_BYTES_SHIFT));
			if(prc->c_src_key != src_color)
			{
				*(unsigned short *)ps = (unsigned short)src_color;
			}
			ps += _16BIT_BYTES;
			su += du;
		}
		psl += prc->s_pitch;
		sv += dv;
	}
}

T3DLIB_API void Draw_Rectangle_Texture_SrcKey32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1)
{
	int itmp;
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;
	FIXP16 u0 = pv0->u;
	FIXP16 v0 = pv0->v;
	FIXP16 u1 = pv1->u;
	FIXP16 v1 = pv1->v;

	if(x0 > x1) { SWAP(x0, x1, itmp); SWAP(u0, u1, itmp); }
	if(y0 > y1) { SWAP(y0, y1, itmp); SWAP(v0, v1, itmp); }
	int dx = x1 - x0;
	int dy = y1 - y0;
	FIXP16 du = 0;
	FIXP16 dv = 0;
	if(dx != 0) { du = (u1 - u0) / dx; }
	if(dy != 0) { dv = (v1 - v0) / dy; }

	unsigned char * psl = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	FIXP28 sv = v0;
	while(dy--)
	{
		unsigned char * ps = psl;
		unsigned char * pt = prc->t_pbuffer + (sv >> FIXP16_SHIFT << prc->t_pitch_shift);
		FIXP28 su = u0;
		int count = dx;
		while(count--)
		{
			unsigned int src_color = *(unsigned int *)(pt + (su >> FIXP16_SHIFT << _32BIT_BYTES_SHIFT));
			if(prc->c_src_key != src_color)
			{
				*(unsigned int *)ps = src_color;
			}
			ps += _32BIT_BYTES;
			su += du;
		}
		psl += prc->s_pitch;
		sv += dv;
	}
}

T3DLIB_API void Draw_Rectangle_Texture_ZBufferW16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1)
{
	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	int itmp;
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;
	FIXP16 u0 = pv0->u;
	FIXP16 v0 = pv0->v;
	FIXP16 u1 = pv1->u;
	FIXP16 v1 = pv1->v;

	if(x0 > x1) { SWAP(x0, x1, itmp); SWAP(u0, u1, itmp); }
	if(y0 > y1) { SWAP(y0, y1, itmp); SWAP(v0, v1, itmp); }
	int dx = x1 - x0;
	int dy = y1 - y0;
	FIXP16 du = 0;
	FIXP16 dv = 0;
	if(dx != 0) { du = (u1 - u0) / dx; }
	if(dy != 0) { dv = (v1 - v0) / dy; }

	unsigned char * psl = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	unsigned char * pzl = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);
	FIXP28 sv = v0;
	while(dy--)
	{
		unsigned char * ps = psl;
		unsigned char * pz = pzl;
		unsigned char * pt = prc->t_pbuffer + (sv >> FIXP16_SHIFT << prc->t_pitch_shift);
		FIXP28 su = u0;
		int count = dx;
		while(count--)
		{
			*(unsigned short *)ps = *(unsigned short *)(pt + (su >> FIXP16_SHIFT << _16BIT_BYTES_SHIFT));
			*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);

			ps += _16BIT_BYTES;
			pz += _ZBUFF_BYTES;
			su += du;
		}
		psl += prc->s_pitch;
		pzl += prc->z_pitch;
		sv += dv;
	}
}

T3DLIB_API void Draw_Rectangle_Texture_ZBufferW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1)
{
	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	int itmp;
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;
	FIXP16 u0 = pv0->u;
	FIXP16 v0 = pv0->v;
	FIXP16 u1 = pv1->u;
	FIXP16 v1 = pv1->v;

	if(x0 > x1) { SWAP(x0, x1, itmp); SWAP(u0, u1, itmp); }
	if(y0 > y1) { SWAP(y0, y1, itmp); SWAP(v0, v1, itmp); }
	int dx = x1 - x0;
	int dy = y1 - y0;
	FIXP16 du = 0;
	FIXP16 dv = 0;
	if(dx != 0) { du = (u1 - u0) / dx; }
	if(dy != 0) { dv = (v1 - v0) / dy; }

	unsigned char * psl = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	unsigned char * pzl = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);
	FIXP28 sv = v0;
	while(dy--)
	{
		unsigned char * ps = psl;
		unsigned char * pz = pzl;
		unsigned char * pt = prc->t_pbuffer + (sv >> FIXP16_SHIFT << prc->t_pitch_shift);
		FIXP28 su = u0;
		int count = dx;
		while(count--)
		{
			*(unsigned int *)ps = *(unsigned int *)(pt + (su >> FIXP16_SHIFT << _32BIT_BYTES_SHIFT));
			*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);

			ps += _32BIT_BYTES;
			pz += _ZBUFF_BYTES;
			su += du;
		}
		psl += prc->s_pitch;
		pzl += prc->z_pitch;
		sv += dv;
	}
}

T3DLIB_API void Draw_Rectangle_ZBufferR_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	int itmp;
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	if(x0 > x1) { SWAP(x0, x1, itmp); }
	if(y0 > y1) { SWAP(y0, y1, itmp); }
	int dx = x1 - x0;
	int dy = y1 - y0;

	unsigned char * psl = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	unsigned char * pzl = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);
	while(dy--)
	{
		unsigned char * ps = psl;
		unsigned char * pz = pzl;
		int count = dx;
		while(count--)
		{
			if(z0 >= *(FIXP28 *)pz)
			{
				*(unsigned short *)ps = ALPHA16_COMB(
						prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)ps);
			}
			ps += _16BIT_BYTES;
			pz += _ZBUFF_BYTES;
		}
		psl += prc->s_pitch;
		pzl += prc->z_pitch;
	}
}

T3DLIB_API void Draw_Rectangle_ZBufferR_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	int itmp;
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	if(x0 > x1) { SWAP(x0, x1, itmp); }
	if(y0 > y1) { SWAP(y0, y1, itmp); }
	int dx = x1 - x0;
	int dy = y1 - y0;

	unsigned char * psl = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	unsigned char * pzl = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);
	while(dy--)
	{
		unsigned char * ps = psl;
		unsigned char * pz = pzl;
		int count = dx;
		while(count--)
		{
			if(z0 >= *(FIXP28 *)pz)
			{
				*(unsigned int *)ps = ALPHA32_COMB(
						prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)ps);
			}
			ps += _32BIT_BYTES;
			pz += _ZBUFF_BYTES;
		}
		psl += prc->s_pitch;
		pzl += prc->z_pitch;
	}
}

T3DLIB_API void Draw_Rectangle_ZbufferR_TextureAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1)
{
	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	int itmp;
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;
	FIXP16 u0 = pv0->u;
	FIXP16 v0 = pv0->v;
	FIXP16 u1 = pv1->u;
	FIXP16 v1 = pv1->v;

	if(x0 > x1) { SWAP(x0, x1, itmp); SWAP(u0, u1, itmp); }
	if(y0 > y1) { SWAP(y0, y1, itmp); SWAP(v0, v1, itmp); }
	int dx = x1 - x0;
	int dy = y1 - y0;
	FIXP16 du = 0;
	FIXP16 dv = 0;
	if(dx != 0) { du = (u1 - u0) / dx; }
	if(dy != 0) { dv = (v1 - v0) / dy; }

	unsigned char * psl = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	unsigned char * pzl = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);
	FIXP28 sv = v0;
	while(dy--)
	{
		unsigned char * ps = psl;
		unsigned char * pz = pzl;
		unsigned char * pt = prc->t_pbuffer + (sv >> FIXP16_SHIFT << prc->t_pitch_shift);
		FIXP28 su = u0;
		int count = dx;
		while(count--)
		{
			if(z0 >= *(FIXP28 *)pz)
			{
				unsigned int src_alpha = *(unsigned short *)(pt + (su >> FIXP16_SHIFT << _16BIT_BYTES_SHIFT));
				if(src_alpha)
				{
					*(unsigned short *)ps = ALPHA16_COMB_UDST(src_alpha, pv0->c_diff, *(unsigned short *)ps);
				}
			}
			ps += _16BIT_BYTES;
			pz += _ZBUFF_BYTES;
			su += du;
		}
		psl += prc->s_pitch;
		pzl += prc->z_pitch;
		sv += dv;
	}
}

T3DLIB_API void Draw_Rectangle_ZbufferR_TextureAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1)
{
	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	int itmp;
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;
	FIXP16 u0 = pv0->u;
	FIXP16 v0 = pv0->v;
	FIXP16 u1 = pv1->u;
	FIXP16 v1 = pv1->v;

	if(x0 > x1) { SWAP(x0, x1, itmp); SWAP(u0, u1, itmp); }
	if(y0 > y1) { SWAP(y0, y1, itmp); SWAP(v0, v1, itmp); }
	int dx = x1 - x0;
	int dy = y1 - y0;
	FIXP16 du = 0;
	FIXP16 dv = 0;
	if(dx != 0) { du = (u1 - u0) / dx; }
	if(dy != 0) { dv = (v1 - v0) / dy; }

	unsigned char * psl = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	unsigned char * pzl = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);
	FIXP28 sv = v0;
	while(dy--)
	{
		unsigned char * ps = psl;
		unsigned char * pz = pzl;
		unsigned char * pt = prc->t_pbuffer + (sv >> FIXP16_SHIFT << prc->t_pitch_shift);
		FIXP28 su = u0;
		int count = dx;
		while(count--)
		{
			if(z0 >= *(FIXP28 *)pz)
			{
				unsigned int src_alpha = *(unsigned int *)(pt + (su >> FIXP16_SHIFT << _32BIT_BYTES_SHIFT));
				if(src_alpha)
				{
					*(unsigned int *)ps = ALPHA32_COMB_UDST(src_alpha, pv0->c_diff, *(unsigned int *)ps);
				}
			}
			ps += _32BIT_BYTES;
			pz += _ZBUFF_BYTES;
			su += du;
		}
		psl += prc->s_pitch;
		pzl += prc->z_pitch;
		sv += dv;
	}
}

T3DLIB_API bool Clip_Rectangle(const RENDERCONTEXTV1 * prc, VERTEXV1 * pv0, VERTEXV1 * pv1)
{
	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(pv0->x < prc->fmin_clip_x)
		reg0 |= CLIP_REGION_W;
	else if(pv0->x > prc->fmax_clip_x + 1.0f)
		reg0 |= CLIP_REGION_E;
	if(pv0->y < prc->fmin_clip_y)
		reg0 |= CLIP_REGION_N;
	else if(pv0->y > prc->fmax_clip_y + 1.0f)
		reg0 |= CLIP_REGION_S;

	if(pv1->x < prc->fmin_clip_x)
		reg1 |= CLIP_REGION_W;
	else if(pv1->x > prc->fmax_clip_x + 1.0f)
		reg1 |= CLIP_REGION_E;
	if(pv1->y < prc->fmin_clip_y)
		reg1 |= CLIP_REGION_N;
	else if(pv1->y > prc->fmax_clip_y + 1.0f)
		reg1 |= CLIP_REGION_S;

	if(reg0 == 0 && reg1 == 0)
		return true;

	if(reg0 & reg1)
		return false;

	switch(reg0)
	{
	case CLIP_REGION_N:
		pv0->y = prc->fmin_clip_y;
		break;

	case CLIP_REGION_S:
		pv0->y = prc->fmax_clip_y + 1.0f;
		break;

	case CLIP_REGION_W:
		pv0->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_E:
		pv0->x = prc->fmax_clip_x + 1.0f;
		break;

	case CLIP_REGION_NW:
		pv0->y = prc->fmin_clip_y;
		pv0->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_NE:
		pv0->y = prc->fmin_clip_y;
		pv0->x = prc->fmax_clip_x + 1.0f;
		break;

	case CLIP_REGION_SW:
		pv0->y = prc->fmax_clip_y + 1.0f;
		pv0->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_SE:
		pv0->y = prc->fmax_clip_y + 1.0f;
		pv0->x = prc->fmax_clip_x + 1.0f;
		break;

	default:
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_N:
		pv1->y = prc->fmin_clip_y;
		break;

	case CLIP_REGION_S:
		pv1->y = prc->fmax_clip_y + 1.0f;
		break;

	case CLIP_REGION_W:
		pv1->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_E:
		pv1->x = prc->fmax_clip_x + 1.0f;
		break;

	case CLIP_REGION_NW:
		pv1->y = prc->fmin_clip_y;
		pv1->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_NE:
		pv1->y = prc->fmin_clip_y;
		pv1->x = prc->fmax_clip_x + 1.0f;
		break;

	case CLIP_REGION_SW:
		pv1->y = prc->fmax_clip_y + 1.0f;
		pv1->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_SE:
		pv1->y = prc->fmax_clip_y + 1.0f;
		pv1->x = prc->fmax_clip_x + 1.0f;
		break;

	default:
		break;
	}
	return true;
}

T3DLIB_API bool Clip_Rectangle_Texture(const RENDERCONTEXTV1 * prc, VERTEXV1T * pv0, VERTEXV1T * pv1)
{
	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(pv0->x < prc->fmin_clip_x)
		reg0 |= CLIP_REGION_W;
	else if(pv0->x > prc->fmax_clip_x + 1.0f)
		reg0 |= CLIP_REGION_E;
	if(pv0->y < prc->fmin_clip_y)
		reg0 |= CLIP_REGION_N;
	else if(pv0->y > prc->fmax_clip_y + 1.0f)
		reg0 |= CLIP_REGION_S;

	if(pv1->x < prc->fmin_clip_x)
		reg1 |= CLIP_REGION_W;
	else if(pv1->x > prc->fmax_clip_x + 1.0f)
		reg1 |= CLIP_REGION_E;
	if(pv1->y < prc->fmin_clip_y)
		reg1 |= CLIP_REGION_N;
	else if(pv1->y > prc->fmax_clip_y + 1.0f)
		reg1 |= CLIP_REGION_S;

	if(reg0 == 0 && reg1 == 0)
		return true;

	if(reg0 & reg1)
		return false;

	switch(reg0)
	{
	case CLIP_REGION_N:
		pv0->v = (FIXP16)LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, pv0->v, pv1->v);
		pv0->y = prc->fmin_clip_y;
		break;

	case CLIP_REGION_S:
		pv0->v = (FIXP16)LINE2D_INTERSECT(prc->fmax_clip_y + 1.0f, pv0->y, pv1->y, pv0->v, pv1->v);
		pv0->y = prc->fmax_clip_y + 1.0f;
		break;

	case CLIP_REGION_W:
		pv0->u = (FIXP16)LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->u, pv1->u);
		pv0->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_E:
		pv0->u = (FIXP16)LINE2D_INTERSECT(prc->fmax_clip_x + 1.0f, pv0->x, pv1->x, pv0->u, pv1->u);
		pv0->x = prc->fmax_clip_x + 1.0f;
		break;

	case CLIP_REGION_NW:
		pv0->v = (FIXP16)LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, pv0->v, pv1->v);
		pv0->u = (FIXP16)LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->u, pv1->u);
		pv0->y = prc->fmin_clip_y;
		pv0->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_NE:
		pv0->v = (FIXP16)LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, pv0->v, pv1->v);
		pv0->u = (FIXP16)LINE2D_INTERSECT(prc->fmax_clip_x + 1.0f, pv0->x, pv1->x, pv0->u, pv1->u);
		pv0->y = prc->fmin_clip_y;
		pv0->x = prc->fmax_clip_x + 1.0f;
		break;

	case CLIP_REGION_SW:
		pv0->v = (FIXP16)LINE2D_INTERSECT(prc->fmax_clip_y + 1.0f, pv0->y, pv1->y, pv0->v, pv1->v);
		pv0->u = (FIXP16)LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->u, pv1->u);
		pv0->y = prc->fmax_clip_y + 1.0f;
		pv0->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_SE:
		pv0->v = (FIXP16)LINE2D_INTERSECT(prc->fmax_clip_y + 1.0f, pv0->y, pv1->y, pv0->v, pv1->v);
		pv0->u = (FIXP16)LINE2D_INTERSECT(prc->fmax_clip_x + 1.0f, pv0->x, pv1->x, pv0->u, pv1->u);
		pv0->y = prc->fmax_clip_y + 1.0f;
		pv0->x = prc->fmax_clip_x + 1.0f;
		break;

	default:
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_N:
		pv1->v = (FIXP16)LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, pv1->v, pv0->v);
		pv1->y = prc->fmin_clip_y;
		break;

	case CLIP_REGION_S:
		pv1->v = (FIXP16)LINE2D_INTERSECT(prc->fmax_clip_y + 1.0f, pv1->y, pv0->y, pv1->v, pv0->v);
		pv1->y = prc->fmax_clip_y + 1.0f;
		break;

	case CLIP_REGION_W:
		pv1->u = (FIXP16)LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->u, pv0->u);
		pv1->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_E:
		pv1->u = (FIXP16)LINE2D_INTERSECT(prc->fmax_clip_x + 1.0f, pv1->x, pv0->x, pv1->u, pv0->u);
		pv1->x = prc->fmax_clip_x + 1.0f;
		break;

	case CLIP_REGION_NW:
		pv1->v = (FIXP16)LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, pv1->v, pv0->v);
		pv1->u = (FIXP16)LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->u, pv0->u);
		pv1->y = prc->fmin_clip_y;
		pv1->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_NE:
		pv1->v = (FIXP16)LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, pv1->v, pv0->v);
		pv1->u = (FIXP16)LINE2D_INTERSECT(prc->fmax_clip_x + 1.0f, pv1->x, pv0->x, pv1->u, pv0->u);
		pv1->y = prc->fmin_clip_y;
		pv1->x = prc->fmax_clip_x + 1.0f;
		break;

	case CLIP_REGION_SW:
		pv1->v = (FIXP16)LINE2D_INTERSECT(prc->fmax_clip_y + 1.0f, pv1->y, pv0->y, pv1->v, pv0->v);
		pv1->u = (FIXP16)LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->u, pv0->u);
		pv1->y = prc->fmax_clip_y + 1.0f;
		pv1->x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_SE:
		pv1->v = (FIXP16)LINE2D_INTERSECT(prc->fmax_clip_y + 1.0f, pv1->y, pv0->y, pv1->v, pv0->v);
		pv1->u = (FIXP16)LINE2D_INTERSECT(prc->fmax_clip_x + 1.0f, pv1->x, pv0->x, pv1->u, pv0->u);
		pv1->y = prc->fmax_clip_y + 1.0f;
		pv1->x = prc->fmax_clip_x + 1.0f;
		break;

	default:
		break;
	}
	return true;
}

T3DLIB_API void Draw_Clipped_Rectangle16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle(prc, &cv0, &cv1))
		Draw_Rectangle16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Rectangle32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle(prc, &cv0, &cv1))
		Draw_Rectangle32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Rectangle_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle(prc, &cv0, &cv1))
		Draw_Rectangle_SrcAlpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Rectangle_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle(prc, &cv0, &cv1))
		Draw_Rectangle_SrcAlpha32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Rectangle_Texture_SrcKey16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1)
{
	VERTEXV1T cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle_Texture(prc, &cv0, &cv1))
		Draw_Rectangle_Texture_SrcKey16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Rectangle_Texture_SrcKey32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1)
{
	VERTEXV1T cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle_Texture(prc, &cv0, &cv1))
		Draw_Rectangle_Texture_SrcKey32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Rectangle_Texture_ZBufferW16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1)
{
	VERTEXV1T cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle_Texture(prc, &cv0, &cv1))
		Draw_Rectangle_Texture_ZBufferW16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Rectangle_Texture_ZBufferW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1)
{
	VERTEXV1T cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle_Texture(prc, &cv0, &cv1))
		Draw_Rectangle_Texture_ZBufferW32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Rectangle_ZBufferR_SrcAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle(prc, &cv0, &cv1))
		Draw_Rectangle_ZBufferR_SrcAlpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Rectangle_ZBufferR_SrcAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle(prc, &cv0, &cv1))
		Draw_Rectangle_ZBufferR_SrcAlpha32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Rectangle_ZbufferR_TextureAlpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1)
{
	VERTEXV1T cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle_Texture(prc, &cv0, &cv1))
		Draw_Rectangle_ZbufferR_TextureAlpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Rectangle_ZbufferR_TextureAlpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1)
{
	VERTEXV1T cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle_Texture(prc, &cv0, &cv1))
		Draw_Rectangle_ZbufferR_TextureAlpha32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Triangle16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2)
{
#define __draw_func Draw_Scan16
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2)
{
#define __draw_func Draw_Scan32
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle_ZBufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2)
{
#define __draw_func Draw_Scan_ZBufferRW16
#define __draw_ZB
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2)
{
#define __draw_func Draw_Scan_ZBufferRW32
#define __draw_ZB
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle_Texture_ZBufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Texture_ZBufferRW16
#define __draw_UV
#define __draw_ZB
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle_Texture_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Texture_ZBufferRW32
#define __draw_UV
#define __draw_ZB
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle_Texture_PerspectiveLP_ZBufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Texture_PerspectiveLP_ZBufferRW16
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_ZB
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle_Texture_PerspectiveLP_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Texture_PerspectiveLP_ZBufferRW32
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_ZB
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle_Gouraud_ZBufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2)
{
#define __draw_func Draw_Scan_Gouraud_ZBufferRW16
#define __draw_GR
#define __draw_ZB
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle_Gouraud_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2)
{
#define __draw_func Draw_Scan_Gouraud_ZBufferRW32
#define __draw_GR
#define __draw_ZB
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle_Gouraud_Texture_ZBufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Gouraud_Texture_ZBufferRW16
#define __draw_UV
#define __draw_GR
#define __draw_ZB
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle_Gouraud_Texture_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Gouraud_Texture_ZBufferRW32
#define __draw_UV
#define __draw_GR
#define __draw_ZB
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Gouraud_Texture_PerspectiveLP_ZBufferRW16
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_GR
#define __draw_ZB
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Gouraud_Texture_PerspectiveLP_ZBufferRW32
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_GR
#define __draw_ZB
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2)
{
#define __draw_func Draw_Scan16
#define __draw_func_clipped Draw_Clipped_Scan16
#define __draw_CLIP
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2)
{
#define __draw_func Draw_Scan32
#define __draw_func_clipped Draw_Clipped_Scan32
#define __draw_CLIP
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle_ZBufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2)
{
#define __draw_func Draw_Scan_ZBufferRW16
#define __draw_func_clipped Draw_Clipped_Scan_ZBufferRW16
#define __draw_ZB
#define __draw_CLIP
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2)
{
#define __draw_func Draw_Scan_ZBufferRW32
#define __draw_func_clipped Draw_Clipped_Scan_ZBufferRW32
#define __draw_ZB
#define __draw_CLIP
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle_Texture_ZBufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Texture_ZBufferRW16
#define __draw_func_clipped Draw_Clipped_Scan_Texture_ZBufferRW16
#define __draw_UV
#define __draw_ZB
#define __draw_CLIP
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle_Texture_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Texture_ZBufferRW32
#define __draw_func_clipped Draw_Clipped_Scan_Texture_ZBufferRW32
#define __draw_UV
#define __draw_ZB
#define __draw_CLIP
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle_Texture_PerspectiveLP_ZBufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Texture_PerspectiveLP_ZBufferRW16
#define __draw_func_clipped Draw_Clipped_Scan_Texture_PerspectiveLP_ZBufferRW16
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_ZB
#define __draw_CLIP
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle_Texture_PerspectiveLP_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Texture_PerspectiveLP_ZBufferRW32
#define __draw_func_clipped Draw_Clipped_Scan_Texture_PerspectiveLP_ZBufferRW32
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_ZB
#define __draw_CLIP
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle_Gouraud_ZBufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2)
{
#define __draw_func Draw_Scan_Gouraud_ZBufferRW16
#define __draw_func_clipped Draw_Clipped_Scan_Gouraud_ZBufferRW16
#define __draw_GR
#define __draw_ZB
#define __draw_CLIP
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle_Gouraud_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1, const VERTEXV1 * pv2)
{
#define __draw_func Draw_Scan_Gouraud_ZBufferRW32
#define __draw_func_clipped Draw_Clipped_Scan_Gouraud_ZBufferRW32
#define __draw_GR
#define __draw_ZB
#define __draw_CLIP
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Gouraud_Texture_ZBufferRW16
#define __draw_func_clipped Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW16
#define __draw_UV
#define __draw_GR
#define __draw_ZB
#define __draw_CLIP
#define __draw_16
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Gouraud_Texture_ZBufferRW32
#define __draw_func_clipped Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW32
#define __draw_UV
#define __draw_GR
#define __draw_ZB
#define __draw_CLIP
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW16(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Gouraud_Texture_PerspectiveLP_ZBufferRW16
#define __draw_func_clipped Draw_Clipped_Scan_Gouraud_Texture_PerspectiveLP_ZBufferRW16
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_GR
#define __draw_ZB
#define __draw_CLIP
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}

T3DLIB_API void Draw_Clipped_Triangle_Gouraud_Texture_PerspectiveLP_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
#define __draw_func Draw_Scan_Gouraud_Texture_PerspectiveLP_ZBufferRW32
#define __draw_func_clipped Draw_Clipped_Scan_Gouraud_Texture_PerspectiveLP_ZBufferRW32
#define __draw_UV
#define __draw_UV_PerspectiveLP
#define __draw_GR
#define __draw_ZB
#define __draw_CLIP
#define __draw_32
#include "t3dlib5.Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW.hpp"
}
