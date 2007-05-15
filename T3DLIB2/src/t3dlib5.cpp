/**
 * File: T3DLIB2/t3dlib5.cpp
 */

#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib4.h"
#include "t3dlib5.h"

_CTOR_IMPLEMENT(RENDERCONTEXTV1_TYP);
_DTOR_IMPLEMENT(RENDERCONTEXTV1_TYP, foo);

T3DLIB_API void (* Draw_HLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_VLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_HLine_Alpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_VLine_Alpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_HLine_Alpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_VLine_Alpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_HLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_VLine)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Line)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Line_Zbuffer)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Line_Alpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Line_Zbuffer_Alpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Line)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Line_Zbuffer)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Line_Alpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Line_Zbuffer_Alpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Rectangle)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Rectangle_Alpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Rectangle)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
T3DLIB_API void (* Draw_Clipped_Rectangle_Alpha)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;

T3DLIB_API bool Init_T3dlib5(int bpp)
{
	switch(bpp)
	{
	case 16:
		Draw_HLine						= Draw_HLine16;
		Draw_VLine						= Draw_VLine16;
		Draw_HLine_Alpha				= Draw_HLine_Alpha16;
		Draw_VLine_Alpha				= Draw_VLine_Alpha16;
		Draw_Clipped_HLine				= Draw_Clipped_HLine16;
		Draw_Clipped_VLine				= Draw_Clipped_VLine16;
		Draw_Clipped_HLine_Alpha		= Draw_Clipped_HLine_Alpha16;
		Draw_Clipped_VLine_Alpha		= Draw_Clipped_VLine_Alpha16;
		Draw_Line						= Draw_Line16;
		Draw_Line_Zbuffer				= Draw_Line_Zbuffer16;
		Draw_Line_Alpha					= Draw_Line_Alpha16;
		Draw_Line_Zbuffer_Alpha			= Draw_Line_Zbuffer_Alpha16;
		Draw_Clipped_Line				= Draw_Clipped_Line16;
		Draw_Clipped_Line_Zbuffer		= Draw_Clipped_Line_Zbuffer16;
		Draw_Clipped_Line_Alpha			= Draw_Clipped_Line_Alpha16;
		Draw_Clipped_Line_Zbuffer_Alpha	= Draw_Clipped_Line_Zbuffer_Alpha16;
		Draw_Rectangle					= Draw_Rectangle16;
		Draw_Rectangle_Alpha			= Draw_Rectangle_Alpha16;
		Draw_Clipped_Rectangle			= Draw_Clipped_Rectangle16;
		Draw_Clipped_Rectangle_Alpha	= Draw_Clipped_Rectangle_Alpha16;
		break;

	case 32:
		Draw_HLine						= Draw_HLine32;
		Draw_VLine						= Draw_VLine32;
		Draw_HLine_Alpha				= Draw_HLine_Alpha32;
		Draw_VLine_Alpha				= Draw_VLine_Alpha32;
		Draw_Clipped_HLine				= Draw_Clipped_HLine32;
		Draw_Clipped_VLine				= Draw_Clipped_VLine32;
		Draw_Clipped_HLine_Alpha		= Draw_Clipped_HLine_Alpha32;
		Draw_Clipped_VLine_Alpha		= Draw_Clipped_VLine_Alpha32;
		Draw_Line						= Draw_Line32;
		Draw_Line_Zbuffer				= Draw_Line_Zbuffer32;
		Draw_Line_Alpha					= Draw_Line_Alpha32;
		Draw_Line_Zbuffer_Alpha			= Draw_Line_Zbuffer_Alpha32;
		Draw_Clipped_Line				= Draw_Clipped_Line32;
		Draw_Clipped_Line_Zbuffer		= Draw_Clipped_Line_Zbuffer32;
		Draw_Clipped_Line_Alpha			= Draw_Clipped_Line_Alpha32;
		Draw_Clipped_Line_Zbuffer_Alpha	= Draw_Clipped_Line_Zbuffer_Alpha32;
		Draw_Rectangle					= Draw_Rectangle32;
		Draw_Rectangle_Alpha			= Draw_Rectangle_Alpha32;
		Draw_Clipped_Rectangle			= Draw_Clipped_Rectangle32;
		Draw_Clipped_Rectangle_Alpha	= Draw_Clipped_Rectangle_Alpha32;
		break;

	default:
		ON_ERROR_GOTO(SFORMAT1(gbuffer, "unsupported color bip: %d", bpp));
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

T3DLIB_API void Draw_HLine_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
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

T3DLIB_API void Draw_HLine_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
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

T3DLIB_API void Draw_VLine_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
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

T3DLIB_API void Draw_VLine_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
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

T3DLIB_API void Draw_Clipped_HLine_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_HLine(prc, &cv0, &cv1))
		Draw_HLine_Alpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_HLine_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_HLine(prc, &cv0, &cv1))
		Draw_HLine_Alpha32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_VLine_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_VLine(prc, &cv0, &cv1))
		Draw_VLine_Alpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_VLine_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_VLine(prc, &cv0, &cv1))
		Draw_VLine_Alpha32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Line16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	int dx = x1 - x0;
	int dy = y1 - y0;
	int ix = _16BIT_BYTES;
	int	iy = prc->s_pitch;
	if(dx < 0) { NEG(dx); NEG(ix); }
	if(dy < 0) { NEG(dy); NEG(iy); }

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	int dx2 = dx << 1;
	int dy2 = dy << 1;
	int i, error;
	if(dx > dy)
	{
		error = dy2 - dx;
		for(i = 0; i < dx; i++)
		{
			*(unsigned short *)ps = (unsigned short)pv0->c_diff;
			if(error >= 0)
			{
				ps += iy;
				error -= dx2;
			}
			ps += ix;
			error += dy2;
		}
	}
	else
	{
		error = dx2 - dy;
		for(i = 0; i < dy; i++)
		{
			*(unsigned short *)ps = (unsigned short)pv0->c_diff;
			if(error >= 0)
			{
				ps += ix;
				error -= dy2;
			}
			ps += iy;
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
	int ix = _32BIT_BYTES;
	int	iy = prc->s_pitch;
	if(dx < 0) { NEG(dx); NEG(ix); }
	if(dy < 0) { NEG(dy); NEG(iy); }

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	int dx2 = dx << 1;
	int dy2 = dy << 1;
	int i, error;
	if(dx > dy)
	{
		error = dy2 - dx;
		for(i = 0; i < dx; i++)
		{
			*(unsigned int *)ps = pv0->c_diff;
			if(error >= 0)
			{
				ps += iy;
				error -= dx2;
			}
			ps += ix;
			error += dy2;
		}
	}
	else
	{
		error = dx2 - dy;
		for(i = 0; i < dy; i++)
		{
			*(unsigned int *)ps = pv0->c_diff;
			if(error >= 0)
			{
				ps += ix;
				error -= dy2;
			}
			ps += iy;
			error += dx2;
		}
	}
}

T3DLIB_API void Draw_Line_Zbuffer16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;
	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	FIXP28 z1 = (FIXP28)(1 / pv1->z * FIXP28_MAG);

	int dx = x1 - x0;
	int dy = y1 - y0;
	FIXP28 zdx = 0;
	FIXP28 zdy = 0;
	if(dx != 0) zdx = (z1 - z0) / dx;
	if(dy != 0) zdy = (z1 - z0) / dy;

	int ixs = _16BIT_BYTES;
	int	iys = prc->s_pitch;
	int ixz = _ZBUFF_BYTES;
	int iyz = prc->z_pitch;
	if(dx < 0) { NEG(dx); NEG(ixs); NEG(ixz); }
	if(dy < 0) { NEG(dy); NEG(iys); NEG(iyz); }

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	unsigned char * pz = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);
	int dx2 = dx << 1;
	int dy2 = dy << 1;
	int i, error;
	if(dx > dy)
	{
		error = dy2 - dx;
		for(i = 0; i < dx; i++)
		{
			if(z0 > _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
			{
				*(unsigned short *)ps = (unsigned short)pv0->c_diff;
				*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
			}

			if(error >= 0)
			{
				ps += iys;
				pz += iyz;
				z0 += zdy;
				error -= dx2;
			}
			ps += ixs;
			pz += ixz;
			z0 += zdx;
			error += dy2;
		}
	}
	else
	{
		error = dx2 - dy;
		for(i = 0; i < dy; i++)
		{
			if(z0 > _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
			{
				*(unsigned short *)ps = (unsigned short)pv0->c_diff;
				*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
			}

			if(error >= 0)
			{
				ps += ixs;
				pz += ixz;
				z0 += zdx;
				error -= dy2;
			}
			ps += iys;
			pz += iyz;
			z0 += zdy;
			error += dx2;
		}
	}
}

T3DLIB_API void Draw_Line_Zbuffer32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;
	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	FIXP28 z1 = (FIXP28)(1 / pv1->z * FIXP28_MAG);

	int dx = x1 - x0;
	int dy = y1 - y0;
	FIXP28 zdx = 0;
	FIXP28 zdy = 0;
	if(dx != 0) zdx = (z1 - z0) / dx;
	if(dy != 0) zdy = (z1 - z0) / dy;

	int ixs = _32BIT_BYTES;
	int	iys = prc->s_pitch;
	int ixz = _ZBUFF_BYTES;
	int iyz = prc->z_pitch;
	if(dx < 0) { NEG(dx); NEG(ixs); NEG(ixz); }
	if(dy < 0) { NEG(dy); NEG(iys); NEG(iyz); }

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	unsigned char * pz = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);
	int dx2 = dx << 1;
	int dy2 = dy << 1;
	int i, error;
	if(dx > dy)
	{
		error = dy2 - dx;
		for(i = 0; i < dx; i++)
		{
			if(z0 > _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
			{
				*(unsigned int *)ps = pv0->c_diff;
				*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
			}

			if(error >= 0)
			{
				ps += iys;
				pz += iyz;
				z0 += zdy;
				error -= dx2;
			}
			ps += ixs;
			pz += ixz;
			z0 += zdx;
			error += dy2;
		}
	}
	else
	{
		error = dx2 - dy;
		for(i = 0; i < dy; i++)
		{
			if(z0 > _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
			{
				*(unsigned int *)ps = pv0->c_diff;
				*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
			}

			if(error >= 0)
			{
				ps += ixs;
				pz += ixz;
				z0 += zdx;
				error -= dy2;
			}
			ps += iys;
			pz += iyz;
			z0 += zdy;
			error += dx2;
		}
	}
}

T3DLIB_API void Draw_Line_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	int dx = x1 - x0;
	int dy = y1 - y0;
	int ix = _16BIT_BYTES;
	int	iy = prc->s_pitch;
	if(dx < 0) { NEG(dx); NEG(ix); }
	if(dy < 0) { NEG(dy); NEG(iy); }

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	int dx2 = dx << 1;
	int dy2 = dy << 1;
	int i, error;
	if(dx > dy)
	{
		error = dy2 - dx;
		for(i = 0; i < dx; i++)
		{
			*(unsigned short *)ps = ALPHA16_COMB(
					prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)ps);

			if(error >= 0)
			{
				ps += iy;
				error -= dx2;
			}
			ps += ix;
			error += dy2;
		}
	}
	else
	{
		error = dx2 - dy;
		for(i = 0; i < dy; i++)
		{
			*(unsigned short *)ps = ALPHA16_COMB(
					prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)ps);

			if(error >= 0)
			{
				ps += ix;
				error -= dy2;
			}
			ps += iy;
			error += dx2;
		}
	}
}

T3DLIB_API void Draw_Line_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	int dx = x1 - x0;
	int dy = y1 - y0;
	int ix = _32BIT_BYTES;
	int	iy = prc->s_pitch;
	if(dx < 0) { NEG(dx); NEG(ix); }
	if(dy < 0) { NEG(dy); NEG(iy); }

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	int dx2 = dx << 1;
	int dy2 = dy << 1;
	int i, error;
	if(dx > dy)
	{
		error = dy2 - dx;
		for(i = 0; i < dx; i++)
		{
			*(unsigned int *)ps = ALPHA32_COMB(
					prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)ps);

			if(error >= 0)
			{
				ps += iy;
				error -= dx2;
			}
			ps += ix;
			error += dy2;
		}
	}
	else
	{
		error = dx2 - dy;
		for(i = 0; i < dy; i++)
		{
			*(unsigned int *)ps = ALPHA32_COMB(
					prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)ps);

			if(error >= 0)
			{
				ps += ix;
				error -= dy2;
			}
			ps += iy;
			error += dx2;
		}
	}
}

T3DLIB_API void Draw_Line_Zbuffer_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;
	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	FIXP28 z1 = (FIXP28)(1 / pv1->z * FIXP28_MAG);

	int dx = x1 - x0;
	int dy = y1 - y0;
	FIXP28 zdx = 0;
	FIXP28 zdy = 0;
	if(dx != 0) zdx = (z1 - z0) / dx;
	if(dy != 0) zdy = (z1 - z0) / dy;

	int ixs = _16BIT_BYTES;
	int	iys = prc->s_pitch;
	int ixz = _ZBUFF_BYTES;
	int iyz = prc->z_pitch;
	if(dx < 0) { NEG(dx); NEG(ixs); NEG(ixz); }
	if(dy < 0) { NEG(dy); NEG(iys); NEG(iyz); }

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_BYTES_SHIFT);
	unsigned char * pz = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);
	int dx2 = dx << 1;
	int dy2 = dy << 1;
	int i, error;
	if(dx > dy)
	{
		error = dy2 - dx;
		for(i = 0; i < dx; i++)
		{
			if(z0 > _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
			{
				*(unsigned short *)ps = ALPHA16_COMB(
						prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)ps);

				*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
			}

			if(error >= 0)
			{
				ps += iys;
				pz += iyz;
				z0 += zdy;
				error -= dx2;
			}
			ps += ixs;
			pz += ixz;
			z0 += zdx;
			error += dy2;
		}
	}
	else
	{
		error = dx2 - dy;
		for(i = 0; i < dy; i++)
		{
			if(z0 > _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
			{
				*(unsigned short *)ps = ALPHA16_COMB(
						prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)ps);

				*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
			}

			if(error >= 0)
			{
				ps += ixs;
				pz += ixz;
				z0 += zdx;
				error -= dy2;
			}
			ps += iys;
			pz += iyz;
			z0 += zdy;
			error += dx2;
		}
	}
}

T3DLIB_API void Draw_Line_Zbuffer_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;
	FIXP28 z0 = (FIXP28)(1 / pv0->z * FIXP28_MAG);
	FIXP28 z1 = (FIXP28)(1 / pv1->z * FIXP28_MAG);

	int dx = x1 - x0;
	int dy = y1 - y0;
	FIXP28 zdx = 0;
	FIXP28 zdy = 0;
	if(dx != 0) zdx = (z1 - z0) / dx;
	if(dy != 0) zdy = (z1 - z0) / dy;

	int ixs = _32BIT_BYTES;
	int	iys = prc->s_pitch;
	int ixz = _ZBUFF_BYTES;
	int iyz = prc->z_pitch;
	if(dx < 0) { NEG(dx); NEG(ixs); NEG(ixz); }
	if(dy < 0) { NEG(dy); NEG(iys); NEG(iyz); }

	unsigned char * ps = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_BYTES_SHIFT);
	unsigned char * pz = prc->z_pbuffer + (y0 << prc->z_pitch_shift) + (x0 << _ZBUFF_BYTES_SHIFT);
	int dx2 = dx << 1;
	int dy2 = dy << 1;
	int i, error;
	if(dx > dy)
	{
		error = dy2 - dx;
		for(i = 0; i < dx; i++)
		{
			if(z0 > _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
			{
				*(unsigned int *)ps = ALPHA32_COMB(
						prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)ps);

				*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
			}

			if(error >= 0)
			{
				ps += iys;
				pz += iyz;
				z0 += zdy;
				error -= dx2;
			}
			ps += ixs;
			pz += ixz;
			z0 += zdx;
			error += dy2;
		}
	}
	else
	{
		error = dx2 - dy;
		for(i = 0; i < dy; i++)
		{
			if(z0 > _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
			{
				*(unsigned int *)ps = ALPHA32_COMB(
						prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)ps);

				*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z0);
			}

			if(error >= 0)
			{
				ps += ixs;
				pz += ixz;
				z0 += zdx;
				error -= dy2;
			}
			ps += iys;
			pz += iyz;
			z0 += zdy;
			error += dx2;
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
		cx0 = LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmax_clip_y;
		break;

	case CLIP_REGION_W:
		cx0 = prc->fmin_clip_x;
		cy0 = LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
		break;

	case CLIP_REGION_E:
		cx0 = prc->fmax_clip_x;
		cy0 = LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
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
			cy0 = LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
		}
		break;

	case CLIP_REGION_SW:
		cx0 = LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmax_clip_y;
		if(cx0 < prc->fmin_clip_x || cx0 > prc->fmax_clip_x)
		{
			cx0 = prc->fmin_clip_x;
			cy0 = LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
		}
		break;

	case CLIP_REGION_SE:
		cx0 = LINE2D_INTERSECT(prc->fmin_clip_y, pv0->y, pv1->y, pv0->x, pv1->x);
		cy0 = prc->fmax_clip_y;
		if(cx0 < prc->fmin_clip_x || cx0 > prc->fmax_clip_x)
		{
			cx0 = prc->fmax_clip_x;
			cy0 = LINE2D_INTERSECT(prc->fmin_clip_x, pv0->x, pv1->x, pv0->y, pv1->y);
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
		cx1 = LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmax_clip_y;
		break;

	case CLIP_REGION_W:
		cx1 = prc->fmin_clip_x;
		cy1 = LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
		break;

	case CLIP_REGION_E:
		cx1 = prc->fmax_clip_x;
		cy1 = LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
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
			cy1 = LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
		}
		break;

	case CLIP_REGION_SW:
		cx1 = LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmax_clip_y;
		if(cx1 < prc->fmin_clip_x || cx1 > prc->fmax_clip_x)
		{
			cx1 = prc->fmin_clip_x;
			cy1 = LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
		}
		break;

	case CLIP_REGION_SE:
		cx1 = LINE2D_INTERSECT(prc->fmin_clip_y, pv1->y, pv0->y, pv1->x, pv0->x);
		cy1 = prc->fmax_clip_y;
		if(cx1 < prc->fmin_clip_x || cx1 > prc->fmax_clip_x)
		{
			cx1 = prc->fmax_clip_x;
			cy1 = LINE2D_INTERSECT(prc->fmin_clip_x, pv1->x, pv0->x, pv1->y, pv0->y);
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

T3DLIB_API void Draw_Clipped_Line_Zbuffer16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line(prc, &cv0, &cv1))
		Draw_Line_Zbuffer16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Line_Zbuffer32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line(prc, &cv0, &cv1))
		Draw_Line_Zbuffer32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Line_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line(prc, &cv0, &cv1))
		Draw_Line_Alpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Line_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line(prc, &cv0, &cv1))
		Draw_Line_Alpha32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Line_Zbuffer_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line(prc, &cv0, &cv1))
		Draw_Line_Zbuffer_Alpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Line_Zbuffer_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Line(prc, &cv0, &cv1))
		Draw_Line_Zbuffer_Alpha32(prc, &cv0, &cv1);
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

T3DLIB_API void Draw_Rectangle_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
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

T3DLIB_API void Draw_Rectangle_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
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

T3DLIB_API void Draw_Clipped_Rectangle_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle(prc, &cv0, &cv1))
		Draw_Rectangle_Alpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_Rectangle_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	if(Clip_Rectangle(prc, &cv0, &cv1))
		Draw_Rectangle_Alpha32(prc, &cv0, &cv1);
}
