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
T3DLIB_API void (* Draw_Clipped_Line)(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1) = NULL;
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
		Draw_Clipped_Line				= Draw_Clipped_Line16;
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
		Draw_Clipped_Line				= Draw_Clipped_Line32;
		Draw_Rectangle					= Draw_Rectangle32;
		Draw_Rectangle_Alpha			= Draw_Rectangle_Alpha32;
		Draw_Clipped_Rectangle			= Draw_Clipped_Rectangle32;
		Draw_Clipped_Rectangle_Alpha	= Draw_Clipped_Rectangle_Alpha32;
		break;

	default:
		ON_ERROR_GOTO((sprintf(gbuffer, "unsupported color bip: %d", bpp), gbuffer));
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

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_SHIFT);
	int dx = x1 - x0;
	if(dx < 0)
	{
		p += (dx + 1) << _16BIT_SHIFT;
		dx = -dx;
	}

	Mem_Set_Word(p, (unsigned short)pv0->c_diff, dx);
}

T3DLIB_API void Draw_HLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int x1 = (int)pv1->x;
	int y0 = (int)pv0->y;

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_SHIFT);
	int dx = x1 - x0;
	if(dx < 0)
	{
		p += (dx + 1) << _32BIT_SHIFT;
		dx = -dx;
	}

	Mem_Set_Quad(p, pv0->c_diff, dx);
}

T3DLIB_API void Draw_VLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int y1 = (int)pv1->y;

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_SHIFT);
	int dy = y1 - y0;
	if(dy < 0)
	{
		p += (dy + 1) << prc->s_pitch_shift;
		dy = -dy;
	}

	while(dy--)
	{
		*(unsigned short *)p = (unsigned short)pv0->c_diff;
		p += prc->s_pitch;
	}
}

T3DLIB_API void Draw_VLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int y1 = (int)pv1->y;

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_SHIFT);
	int dy = y1 - y0;
	if(dy < 0)
	{
		p += (dy + 1) << prc->s_pitch_shift;
		dy = -dy;
	}

	while(dy--)
	{
		*(unsigned int *)p = pv0->c_diff;
		p += prc->s_pitch;
	}
}

T3DLIB_API void Draw_HLine_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int x1 = (int)pv1->x;
	int y0 = (int)pv0->y;

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_SHIFT);
	int dx = x1 - x0;
	if(dx < 0)
	{
		p += (dx + 1) << _16BIT_SHIFT;
		dx = -dx;
	}

	while(dx--)
	{
		*(unsigned short *)p = ALPHA16_COMB(
				prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)p);

		p += _16BIT_BYTES;
	}
}

T3DLIB_API void Draw_HLine_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int x1 = (int)pv1->x;
	int y0 = (int)pv0->y;

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_SHIFT);
	int dx = x1 - x0;
	if(dx < 0)
	{
		p += (dx + 1) << _32BIT_SHIFT;
		dx = -dx;
	}

	while(dx--)
	{
		*(unsigned int *)p = ALPHA32_COMB(
				prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)p);

		p += _32BIT_BYTES;
	}
}

T3DLIB_API void Draw_VLine_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int y1 = (int)pv1->y;

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_SHIFT);
	int dy = y1 - y0;
	if(dy < 0)
	{
		p += (dy + 1) << prc->s_pitch_shift;
		dy = -dy;
	}

	while(dy--)
	{
		*(unsigned short *)p = ALPHA16_COMB(
				prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned short *)p);

		p += prc->s_pitch;
	}
}

T3DLIB_API void Draw_VLine_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int y1 = (int)pv1->y;

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_SHIFT);
	int dy = y1 - y0;
	if(dy < 0)
	{
		p += (dy + 1) << prc->s_pitch_shift;
		dy = -dy;
	}

	while(dy--)
	{
		*(unsigned int *)p = ALPHA32_COMB(
				prc->c_src_alpha, pv0->c_diff, prc->c_dst_alpha, *(unsigned int *)p);

		p += prc->s_pitch;
	}
}

T3DLIB_API void Draw_Clipped_HLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(cv0.x < prc->fmin_clip_x)
		reg0 |= CLIP_REGION_W;
	else if(cv0.x > prc->fmax_clip_x)
		reg0 |= CLIP_REGION_E;

	if(cv1.x < prc->fmin_clip_x - 1.0f)
		reg1 |= CLIP_REGION_W;
	else if(cv1.x > prc->fmax_clip_x + 1.0f)
		reg1 |= CLIP_REGION_E;

	if(reg0 & reg1)
		return;

	switch(reg0)
	{
	case CLIP_REGION_W:
		cv0.x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_E:
		cv0.x = prc->fmax_clip_x;
		break;

	default:
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_W:
		cv1.x = prc->fmin_clip_x - 1.0f;
		break;

	case CLIP_REGION_E:
		cv1.x = prc->fmax_clip_x + 1.0f;
		break;

	default:
		break;
	}

	if(cv0.y >= prc->fmin_clip_y && cv0.y <= prc->fmax_clip_y)
		Draw_HLine16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_HLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(cv0.x < prc->fmin_clip_x)
		reg0 |= CLIP_REGION_W;
	else if(cv0.x > prc->fmax_clip_x)
		reg0 |= CLIP_REGION_E;

	if(cv1.x < prc->fmin_clip_x - 1.0f)
		reg1 |= CLIP_REGION_W;
	else if(cv1.x > prc->fmax_clip_x + 1.0f)
		reg1 |= CLIP_REGION_E;

	if(reg0 & reg1)
		return;

	switch(reg0)
	{
	case CLIP_REGION_W:
		cv0.x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_E:
		cv0.x = prc->fmax_clip_x;
		break;

	default:
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_W:
		cv1.x = prc->fmin_clip_x - 1.0f;
		break;

	case CLIP_REGION_E:
		cv1.x = prc->fmax_clip_x + 1.0f;
		break;

	default:
		break;
	}

	if(cv0.y >= prc->fmin_clip_y && cv0.y <= prc->fmax_clip_y)
		Draw_HLine32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_VLine16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(cv0.y < prc->fmin_clip_y)
		reg0 |= CLIP_REGION_W;
	else if(cv0.y > prc->fmax_clip_y)
		reg0 |= CLIP_REGION_E;

	if(cv1.y < prc->fmin_clip_y - 1.0f)
		reg1 |= CLIP_REGION_W;
	else if(cv1.y > prc->fmax_clip_y + 1.0f)
		reg1 |= CLIP_REGION_E;

	if(reg0 & reg1)
		return;

	switch(reg0)
	{
	case CLIP_REGION_W:
		cv0.y = prc->fmin_clip_y;
		break;

	case CLIP_REGION_E:
		cv0.y = prc->fmax_clip_y;
		break;

	default:
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_W:
		cv1.y = prc->fmin_clip_y - 1.0f;
		break;

	case CLIP_REGION_E:
		cv1.y = prc->fmax_clip_y + 1.0f;
		break;

	default:
		break;
	}

	if(cv0.x >= prc->fmin_clip_x && cv0.x <= prc->fmax_clip_x)
		Draw_VLine16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_VLine32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(cv0.y < prc->fmin_clip_y)
		reg0 |= CLIP_REGION_W;
	else if(cv0.y > prc->fmax_clip_y)
		reg0 |= CLIP_REGION_E;

	if(cv1.y < prc->fmin_clip_y - 1.0f)
		reg1 |= CLIP_REGION_W;
	else if(cv1.y > prc->fmax_clip_y + 1.0f)
		reg1 |= CLIP_REGION_E;

	if(reg0 & reg1)
		return;

	switch(reg0)
	{
	case CLIP_REGION_W:
		cv0.y = prc->fmin_clip_y;
		break;

	case CLIP_REGION_E:
		cv0.y = prc->fmax_clip_y;
		break;

	default:
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_W:
		cv1.y = prc->fmin_clip_y - 1.0f;
		break;

	case CLIP_REGION_E:
		cv1.y = prc->fmax_clip_y + 1.0f;
		break;

	default:
		break;
	}

	if(cv0.x >= prc->fmin_clip_x && cv0.x <= prc->fmax_clip_x)
		Draw_VLine32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_HLine_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(cv0.x < prc->fmin_clip_x)
		reg0 |= CLIP_REGION_W;
	else if(cv0.x > prc->fmax_clip_x)
		reg0 |= CLIP_REGION_E;

	if(cv1.x < prc->fmin_clip_x - 1.0f)
		reg1 |= CLIP_REGION_W;
	else if(cv1.x > prc->fmax_clip_x + 1.0f)
		reg1 |= CLIP_REGION_E;

	if(reg0 & reg1)
		return;

	switch(reg0)
	{
	case CLIP_REGION_W:
		cv0.x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_E:
		cv0.x = prc->fmax_clip_x;
		break;

	default:
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_W:
		cv1.x = prc->fmin_clip_x - 1.0f;
		break;

	case CLIP_REGION_E:
		cv1.x = prc->fmax_clip_x + 1.0f;
		break;

	default:
		break;
	}

	if(cv0.y >= prc->fmin_clip_y && cv0.y <= prc->fmax_clip_y)
		Draw_HLine_Alpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_HLine_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(cv0.x < prc->fmin_clip_x)
		reg0 |= CLIP_REGION_W;
	else if(cv0.x > prc->fmax_clip_x)
		reg0 |= CLIP_REGION_E;

	if(cv1.x < prc->fmin_clip_x - 1.0f)
		reg1 |= CLIP_REGION_W;
	else if(cv1.x > prc->fmax_clip_x + 1.0f)
		reg1 |= CLIP_REGION_E;

	if(reg0 & reg1)
		return;

	switch(reg0)
	{
	case CLIP_REGION_W:
		cv0.x = prc->fmin_clip_x;
		break;

	case CLIP_REGION_E:
		cv0.x = prc->fmax_clip_x;
		break;

	default:
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_W:
		cv1.x = prc->fmin_clip_x - 1.0f;
		break;

	case CLIP_REGION_E:
		cv1.x = prc->fmax_clip_x + 1.0f;
		break;

	default:
		break;
	}

	if(cv0.y >= prc->fmin_clip_y && cv0.y <= prc->fmax_clip_y)
		Draw_HLine_Alpha32(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_VLine_Alpha16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(cv0.y < prc->fmin_clip_y)
		reg0 |= CLIP_REGION_W;
	else if(cv0.y > prc->fmax_clip_y)
		reg0 |= CLIP_REGION_E;

	if(cv1.y < prc->fmin_clip_y - 1.0f)
		reg1 |= CLIP_REGION_W;
	else if(cv1.y > prc->fmax_clip_y + 1.0f)
		reg1 |= CLIP_REGION_E;

	if(reg0 & reg1)
		return;

	switch(reg0)
	{
	case CLIP_REGION_W:
		cv0.y = prc->fmin_clip_y;
		break;

	case CLIP_REGION_E:
		cv0.y = prc->fmax_clip_y;
		break;

	default:
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_W:
		cv1.y = prc->fmin_clip_y - 1.0f;
		break;

	case CLIP_REGION_E:
		cv1.y = prc->fmax_clip_y + 1.0f;
		break;

	default:
		break;
	}

	if(cv0.x >= prc->fmin_clip_x && cv0.x <= prc->fmax_clip_x)
		Draw_VLine_Alpha16(prc, &cv0, &cv1);
}

T3DLIB_API void Draw_Clipped_VLine_Alpha32(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	VERTEXV1 cv0, cv1;
	memcpy(&cv0, pv0, sizeof(*pv0));
	memcpy(&cv1, pv1, sizeof(*pv1));

	int reg0 = CLIP_REGION_C;
	int reg1 = CLIP_REGION_C;

	if(cv0.y < prc->fmin_clip_y)
		reg0 |= CLIP_REGION_W;
	else if(cv0.y > prc->fmax_clip_y)
		reg0 |= CLIP_REGION_E;

	if(cv1.y < prc->fmin_clip_y - 1.0f)
		reg1 |= CLIP_REGION_W;
	else if(cv1.y > prc->fmax_clip_y + 1.0f)
		reg1 |= CLIP_REGION_E;

	if(reg0 & reg1)
		return;

	switch(reg0)
	{
	case CLIP_REGION_W:
		cv0.y = prc->fmin_clip_y;
		break;

	case CLIP_REGION_E:
		cv0.y = prc->fmax_clip_y;
		break;

	default:
		break;
	}

	switch(reg1)
	{
	case CLIP_REGION_W:
		cv1.y = prc->fmin_clip_y - 1.0f;
		break;

	case CLIP_REGION_E:
		cv1.y = prc->fmax_clip_y + 1.0f;
		break;

	default:
		break;
	}

	if(cv0.x >= prc->fmin_clip_x && cv0.x <= prc->fmax_clip_x)
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
	if(dx < 0) { dx = -dx; ix = -ix; }
	if(dy < 0) { dy = -dy; iy = -iy; }

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_SHIFT);
	int dx2 = dx << 1;
	int dy2 = dy << 1;
	int i, error;
	if(dx > dy)
	{
		error = dy2 - dx;
		for(i = 0; i < dx; i++)
		{
			*(unsigned short *)p = (unsigned short)pv0->c_diff;
			if(error >= 0)
			{
				p += iy;
				error -= dx2;
			}
			p += ix;
			error += dy2;
		}
	}
	else
	{
		error = dx2 - dy;
		for(i = 0; i < dy; i++)
		{
			*(unsigned short *)p = (unsigned short)pv0->c_diff;
			if(error >= 0)
			{
				p += ix;
				error -= dy2;
			}
			p += iy;
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
	if(dx < 0) { dx = -dx; ix = -ix; }
	if(dy < 0) { dy = -dy; iy = -iy; }

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_SHIFT);
	int dx2 = dx << 1;
	int dy2 = dy << 1;
	int i, error;
	if(dx > dy)
	{
		error = dy2 - dx;
		for(i = 0; i < dx; i++)
		{
			*(unsigned int *)p = pv0->c_diff;
			if(error >= 0)
			{
				p += iy;
				error -= dx2;
			}
			p += ix;
			error += dy2;
		}
	}
	else
	{
		error = dx2 - dy;
		for(i = 0; i < dy; i++)
		{
			*(unsigned int *)p = pv0->c_diff;
			if(error >= 0)
			{
				p += ix;
				error -= dy2;
			}
			p += iy;
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

T3DLIB_API void Draw_Rectangle16(const RENDERCONTEXTV1 * prc, const VERTEXV1 * pv0, const VERTEXV1 * pv1)
{
	int x0 = (int)pv0->x;
	int y0 = (int)pv0->y;
	int x1 = (int)pv1->x;
	int y1 = (int)pv1->y;

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_SHIFT);
	int dx = x1 - x0;
	int dy = y1 - y0;
	if(dx < 0)
	{
		p += dx << _16BIT_SHIFT;
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

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_SHIFT);
	int dx = x1 - x0;
	int dy = y1 - y0;
	if(dx < 0)
	{
		p += dx << _32BIT_SHIFT;
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

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _16BIT_SHIFT);
	int dx = x1 - x0;
	int dy = y1 - y0;
	if(dx < 0)
	{
		p += dx << _16BIT_SHIFT;
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

	unsigned char * p = prc->s_pbuffer + (y0 << prc->s_pitch_shift) + (x0 << _32BIT_SHIFT);
	int dx = x1 - x0;
	int dy = y1 - y0;
	if(dx < 0)
	{
		p += dx << _32BIT_SHIFT;
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
