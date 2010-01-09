
#include "stdafx.h"
#include "t3dlib5.h"
#include <cmath>

#define CLIP_REGION_C		0x00
#define CLIP_REGION_N		0x01
#define CLIP_REGION_S		0x02
#define CLIP_REGION_W		0x04
#define CLIP_REGION_E		0x08
#define CLIP_REGION_NW		0x05
#define CLIP_REGION_NE		0x09
#define CLIP_REGION_SW		0x06
#define CLIP_REGION_SE		0x0A

#pragma warning(disable: 4244)

namespace t3d
{
	const unsigned char color_add_table[UCHAR_MAX + 1][UCHAR_MAX + 1] = {
#include "color_add_table.hpp"
	};

	const unsigned char color_mul_table[UCHAR_MAX + 1][UCHAR_MAX + 1] = {
#include "color_mul_table.hpp"
	};

#define _COLORADD(lhs, rhs)	color_add_table[(lhs)][(rhs)]

#define _COLORMUL(lhs, rhs)	color_mul_table[(lhs)][(rhs)]

	void fillZBuffer28(
		SurfaceRef<fixp28> zbuffer,
		const CRect & rect,
		real value_inv)
	{
		for(int i = rect.top; i < rect.bottom; i++)
		{
			memSet32((uint32 *)&zbuffer[i][rect.left], (uint32)real_to_fixp28(value_inv), rect.Width());
		}
	}

	void fillSurface16(
		SurfaceRef<uint16> surface,
		const CRect & rect,
		const Vec4<real> & color)
	{
		for(int i = rect.top; i < rect.bottom; i++)
		{
			memSet16(&surface[i][rect.left], _RGB16BIT(real_to_int(color.x * 255), real_to_int(color.y * 255), real_to_int(color.z * 255)), rect.Width());
		}
	}

	void fillSurface32(
		SurfaceRef<uint32> surface,
		const CRect & rect,
		const Vec4<real> & color)
	{
		for(int i = rect.top; i < rect.bottom; i++)
		{
			memSet32(&surface[i][rect.left], _RGB32BIT(real_to_int(color.x * 255), real_to_int(color.y * 255), real_to_int(color.z * 255)), rect.Width());
		}
	}

	void drawHorizonLine32(
		SurfaceRef<uint32> surface,
		const Vec4<real> & v0,
		int width,
		const Vec4<real> & color)
	{
		assert(width >= 0);

		int x0 = real_to_int(v0.x);
		int y0 = real_to_int(v0.y);

		memSet32(&surface[x0][y0],
			_RGB32BIT(real_to_int(color.x), real_to_int(color.y), real_to_int(color.z)), width);
	}

	void drawClippedHorizonLine32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		const Vec4<real> & v0,
		int width,
		const Vec4<real> & color)
	{
		assert(width >= 0);

		if(v0.y >= clipper.top && v0.y < clipper.bottom)
		{
			if(v0.x < clipper.right)
			{
				int clippedWidth = width;
				int x0 = real_to_int(v0.x);
				int y0 = real_to_int(v0.y);

				if(x0 < clipper.left)
				{
					clippedWidth -= clipper.left - x0;
					x0 = clipper.left;
				}

				if(clippedWidth > 0)
				{
					memSet32(&surface[x0][y0],
						_RGB32BIT(real_to_int(color.x), real_to_int(color.y), real_to_int(color.z)), clippedWidth);
				}
			}
		}
	}

	void drawVerticalLine32(
		SurfaceRef<uint32> surface,
		const Vec4<real> & v0,
		int height,
		const Vec4<real> & color)
	{
		assert(height >= 0);

		int x0 = real_to_int(v0.x);
		int y0 = real_to_int(v0.y);

		for(int y1 = y0 + height; y0 < y1; y0++)
		{
			surface[x0][y0] =
				_RGB32BIT(real_to_int(color.x), real_to_int(color.y), real_to_int(color.z));
		}
	}

	void drawClippedVerticalLine32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		const Vec4<real> & v0,
		int height,
		const Vec4<real> & color)
	{
		assert(height >= 0);

		if(v0.x >= clipper.left && v0.x < clipper.right)
		{
			if(v0.y < clipper.bottom)
			{
				int clippedHeight = height;
				int x0 = real_to_int(v0.x);
				int y0 = real_to_int(v0.y);

				if(y0 < clipper.top)
				{
					clippedHeight -= clipper.top - y0;
					y0 = clipper.left;
				}

				if(clippedHeight > 0)
				{
					for(int y1 = y0 + clippedHeight; y0 < y1; y0++)
					{
						surface[x0][y0] =
							_RGB32BIT(real_to_int(color.x), real_to_int(color.y), real_to_int(color.z));
					}
				}
			}
		}
	}

	bool clipLineZBuffer(
		const RECT & clipper,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		Vec4<real> & vres0,
		Vec4<real> & vres1)
	{
		int reg0 = CLIP_REGION_C;
		int reg1 = CLIP_REGION_C;

		if(v0.x < clipper.left)
			reg0 |= CLIP_REGION_W;
		else if(v0.x > clipper.right - 1)
			reg0 |= CLIP_REGION_E;

		if(v0.y < clipper.top)
			reg0 |= CLIP_REGION_N;
		else if(v0.y > clipper.bottom - 1)
			reg0 |= CLIP_REGION_S;

		if(v1.x < clipper.left)
			reg1 |= CLIP_REGION_W;
		else if(v1.x > clipper.right - 1)
			reg1 |= CLIP_REGION_E;

		if(v1.y < clipper.top)
			reg1 |= CLIP_REGION_N;
		else if(v1.y > clipper.bottom - 1)
			reg1 |= CLIP_REGION_S;

		if(reg0 == 0 && reg1 == 0)
		{
			vres0 = v0;
			vres1 = v1;
			return true;
		}

		if(reg0 & reg1)
		{
			return false;
		}

		switch(reg0)
		{
		case CLIP_REGION_N:
			vres0.x = LINE2D_INTERSECT(clipper.top, v0.y, v1.y, v0.x, v1.x);
			vres0.y = clipper.top;
			vres0.z = 1 / LINE2D_INTERSECT(clipper.top, v0.y, v1.y, 1 / v0.z, 1 / v1.z);
			break;

		case CLIP_REGION_S:
			vres0.x = LINE2D_INTERSECT(clipper.bottom - 1, v0.y, v1.y, v0.x, v1.x);
			vres0.y = clipper.bottom - 1;
			vres0.z = 1 / LINE2D_INTERSECT(clipper.bottom - 1, v0.y, v1.y, 1 / v0.z, 1 / v1.z);
			break;

		case CLIP_REGION_W:
			vres0.x = clipper.left;
			vres0.y = LINE2D_INTERSECT(clipper.left, v0.x, v1.x, v0.y, v1.y);
			vres0.z = 1 / LINE2D_INTERSECT(clipper.left, v0.x, v1.x, 1 / v0.z, 1 / v1.z);
			break;

		case CLIP_REGION_E:
			vres0.x = clipper.right - 1;
			vres0.y = LINE2D_INTERSECT(clipper.right - 1, v0.x, v1.x, v0.y, v1.y);
			vres0.z = 1 / LINE2D_INTERSECT(clipper.right - 1, v0.x, v1.x, 1 / v0.z, 1 / v1.z);
			break;

		case CLIP_REGION_NW:
			vres0.x = LINE2D_INTERSECT(clipper.top, v0.y, v1.y, v0.x, v1.x);
			vres0.y = clipper.top;
			vres0.z = 1 / LINE2D_INTERSECT(clipper.top, v0.y, v1.y, 1 / v0.z, 1 / v1.z);
			if(vres0.x < clipper.left || vres0.x > clipper.right - 1)
			{
				vres0.x = clipper.left;
				vres0.y = LINE2D_INTERSECT(clipper.left, v0.x, v1.x, v0.y, v1.y);
				vres0.z = 1 / LINE2D_INTERSECT(clipper.left, v0.x, v1.x, 1 / v0.z, 1 / v1.z);
			}
			break;

		case CLIP_REGION_NE:
			vres0.x = LINE2D_INTERSECT(clipper.top, v0.y, v1.y, v0.x, v1.x);
			vres0.y = clipper.top;
			vres0.z = 1 / LINE2D_INTERSECT(clipper.top, v0.y, v1.y, 1 / v0.z, 1 / v1.z);
			if(vres0.x < clipper.left || vres0.x > clipper.right - 1)
			{
				vres0.x = clipper.right - 1;
				vres0.y = LINE2D_INTERSECT(clipper.right - 1, v0.x, v1.x, v0.y, v1.y);
				vres0.z = 1 / LINE2D_INTERSECT(clipper.right - 1, v0.x, v1.x, 1 / v0.z, 1 / v1.z);
			}
			break;

		case CLIP_REGION_SW:
			vres0.x = LINE2D_INTERSECT(clipper.bottom - 1, v0.y, v1.y, v0.x, v1.x);
			vres0.y = clipper.bottom - 1;
			vres0.z = 1 / LINE2D_INTERSECT(clipper.bottom - 1, v0.y, v1.y, 1 / v0.z, 1 / v1.z);
			if(vres0.x < clipper.left || vres0.x > clipper.right - 1)
			{
				vres0.x = clipper.left;
				vres0.y = LINE2D_INTERSECT(clipper.left, v0.x, v1.x, v0.y, v1.y);
				vres0.z = 1 / LINE2D_INTERSECT(clipper.left, v0.x, v1.x, 1 / v0.z, 1 / v1.z);
			}
			break;

		case CLIP_REGION_SE:
			vres0.x = LINE2D_INTERSECT(clipper.bottom - 1, v0.y, v1.y, v0.x, v1.x);
			vres0.y = clipper.bottom - 1;
			vres0.z = 1 / LINE2D_INTERSECT(clipper.bottom - 1, v0.y, v1.y, 1 / v0.z, 1 / v1.z);
			if(vres0.x < clipper.left || vres0.x > clipper.right - 1)
			{
				vres0.x = clipper.right - 1;
				vres0.y = LINE2D_INTERSECT(clipper.right - 1, v0.x, v1.x, v0.y, v1.y);
				vres0.z = 1 / LINE2D_INTERSECT(clipper.right - 1, v0.x, v1.x, 1 / v0.z, 1 / v1.z);
			}
			break;

		default:
			vres0.x = v0.x;
			vres0.y = v0.y;
			vres0.z = v0.z;
			break;
		}

		switch(reg1)
		{
		case CLIP_REGION_N:
			vres1.x = LINE2D_INTERSECT(clipper.top, v1.y, v0.y, v1.x, v0.x);
			vres1.y = clipper.top;
			vres1.z = 1 / LINE2D_INTERSECT(clipper.top, v1.y, v0.y, 1 / v1.z, 1 / v0.z);
			break;

		case CLIP_REGION_S:
			vres1.x = LINE2D_INTERSECT(clipper.bottom - 1, v1.y, v0.y, v1.x, v0.x);
			vres1.y = clipper.bottom - 1;
			vres1.z = 1 / LINE2D_INTERSECT(clipper.bottom - 1, v1.y, v0.y, 1 / v1.z, 1 / v0.z);
			break;

		case CLIP_REGION_W:
			vres1.x = clipper.left;
			vres1.y = LINE2D_INTERSECT(clipper.left, v1.x, v0.x, v1.y, v0.y);
			vres1.z = 1 / LINE2D_INTERSECT(clipper.left, v1.x, v0.x, 1 / v1.z, 1 / v0.z);
			break;

		case CLIP_REGION_E:
			vres1.x = clipper.right - 1;
			vres1.y = LINE2D_INTERSECT(clipper.right - 1, v1.x, v0.x, v1.y, v0.y);
			vres1.z = 1 / LINE2D_INTERSECT(clipper.right - 1, v1.x, v0.x, 1 / v1.z, 1 / v0.z);
			break;

		case CLIP_REGION_NW:
			vres1.x = LINE2D_INTERSECT(clipper.top, v1.y, v0.y, v1.x, v0.x);
			vres1.y = clipper.top;
			vres1.z = 1 / LINE2D_INTERSECT(clipper.top, v1.y, v0.y, 1 / v1.z, 1 / v0.z);
			if(vres1.x < clipper.left || vres1.x > clipper.right - 1)
			{
				vres1.x = clipper.left;
				vres1.y = LINE2D_INTERSECT(clipper.left, v1.x, v0.x, v1.y, v0.y);
				vres1.z = 1 / LINE2D_INTERSECT(clipper.left, v1.x, v0.x, 1 / v1.z, 1 / v0.z);
			}
			break;

		case CLIP_REGION_NE:
			vres1.x = LINE2D_INTERSECT(clipper.top, v1.y, v0.y, v1.x, v0.x);
			vres1.y = clipper.top;
			vres1.z = 1 / LINE2D_INTERSECT(clipper.top, v1.y, v0.y, 1 / v1.z, 1 / v0.z);
			if(vres1.x < clipper.left || vres1.x > clipper.right - 1)
			{
				vres1.x = clipper.right - 1;
				vres1.y = LINE2D_INTERSECT(clipper.right - 1, v1.x, v0.x, v1.y, v0.y);
				vres1.z = 1 / LINE2D_INTERSECT(clipper.right - 1, v1.x, v0.x, 1 / v1.z, 1 / v0.z);
			}
			break;

		case CLIP_REGION_SW:
			vres1.x = LINE2D_INTERSECT(clipper.bottom - 1, v1.y, v0.y, v1.x, v0.x);
			vres1.y = clipper.bottom - 1;
			vres1.z = 1 / LINE2D_INTERSECT(clipper.bottom - 1, v1.y, v0.y, 1 / v1.z, 1 / v0.z);
			if(vres1.x < clipper.left || vres1.x > clipper.right - 1)
			{
				vres1.x = clipper.left;
				vres1.y = LINE2D_INTERSECT(clipper.left, v1.x, v0.x, v1.y, v0.y);
				vres1.z = 1 / LINE2D_INTERSECT(clipper.left, v1.x, v0.x, 1 / v1.z, 1 / v0.z);
			}
			break;

		case CLIP_REGION_SE:
			vres1.x = LINE2D_INTERSECT(clipper.bottom - 1, v1.y, v0.y, v1.x, v0.x);
			vres1.y = clipper.bottom - 1;
			vres1.z = 1 / LINE2D_INTERSECT(clipper.bottom - 1, v1.y, v0.y, 1 / v1.z, 1 / v0.z);
			if(vres1.x < clipper.left || vres1.x > clipper.right - 1)
			{
				vres1.x = clipper.right - 1;
				vres1.y = LINE2D_INTERSECT(clipper.right - 1, v1.x, v0.x, v1.y, v0.y);
				vres1.z = 1 / LINE2D_INTERSECT(clipper.right - 1, v1.x, v0.x, 1 / v1.z, 1 / v0.z);
			}
			break;

		default:
			vres1.x = v1.x;
			vres1.y = v1.y;
			vres1.z = v1.z;
			break;
		}

		if(	vres0.x >= clipper.left && vres0.x <= clipper.right - 1 &&
			vres0.y >= clipper.top && vres0.y <= clipper.bottom - 1 &&
			vres1.x >= clipper.left && vres1.x <= clipper.right - 1 &&
			vres1.y >= clipper.top && vres1.y <= clipper.bottom - 1)
		{
			vres0.w = v0.w;
			vres1.w = v1.w;
			return true;
		}
		return false;
	}

	void drawLineZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & color)
	{
		int x0;
		int y0;
		fixp28 z0;
		int x1;
		int y1;
		fixp28 z1;

		if(v0.x < v1.x)
		{
			x0 = real_to_int(v0.x);
			y0 = real_to_int(v0.y);
			z0 = real_to_fixp28(1 / v0.z);
			x1 = real_to_int(v1.x);
			y1 = real_to_int(v1.y);
			z1 = real_to_fixp28(1 / v1.z);
		}
		else
		{
			x0 = real_to_int(v1.x);
			y0 = real_to_int(v1.y);
			z0 = real_to_fixp28(1 / v1.z);
			x1 = real_to_int(v0.x);
			y1 = real_to_int(v0.y);
			z1 = real_to_fixp28(1 / v0.z);
		}

		if(y0 < y1)
		{
			/****************************************************************************
			* 0
			*   \
			*     1
			****************************************************************************/

			int dx = x1 - x0;
			int dy = y1 - y0;

			if(dx > dy)
			{
				fixp28 dz = (z1 - z0) / dx;
				for(int error = dy * 2 - dx; x0 <= x1; x0++, error += dy * 2, z0 += dz)
				{
					if(z0 > zbuffer[y0][x0])
					{
						surface[y0][x0] = _RGB32BIT(real_to_int(color.x), real_to_int(color.y), real_to_int(color.z));
						zbuffer[y0][x0] = z0;
					}

					if(error >= 0)
					{
						y0++;
						error -= dx * 2;
					}
				}
			}
			else
			{
				fixp28 dz = (z1 - z0) / dy;
				for(int error = dx * 2 - dy; y0 <= y1; y0++, error += dx * 2, z0 += dz)
				{
					if(z0 > zbuffer[y0][x0])
					{
						surface[y0][x0] = _RGB32BIT(real_to_int(color.x), real_to_int(color.y), real_to_int(color.z));
						zbuffer[y0][x0] = z0;
					}

					if(error >= 0)
					{
						x0++;
						error -= dy * 2;
					}
				}
			}
		}
		else
		{
			/****************************************************************************
			*     1
			*   /
			* 0
			****************************************************************************/

			int dx = x1 - x0;
			int dy = y0 - y1;

			if(dx > dy)
			{
				fixp28 dz = (z1 - z0) / dx;
				for(int error = dy * 2 - dx; x0 <= x1; x0++, error += dy * 2, z0 += dz)
				{
					if(z0 > zbuffer[y0][x0])
					{
						surface[y0][x0] = _RGB32BIT(real_to_int(color.x), real_to_int(color.y), real_to_int(color.z));
						zbuffer[y0][x0] = z0;
					}

					if(error >= 0)
					{
						y0--;
						error -= dx * 2;
					}
				}
			}
			else
			{
				if(0 == dy) // ***
				{
					assert(0 == dx); return;
				}

				fixp28 dz = (z1 - z0) / dy;
				for(int error = dx * 2 - dy; y0 >= y1; y0--, error += dx * 2, z0 += dz) // ***
				{
					if(z0 > zbuffer[y0][x0])
					{
						surface[y0][x0] = _RGB32BIT(real_to_int(color.x), real_to_int(color.y), real_to_int(color.z));
						zbuffer[y0][x0] = z0;
					}

					if(error >= 0)
					{
						x0++;
						error -= dy * 2;
					}
				}
			}
		}
	}

	void drawClippedLineZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & color)
	{
		Vec4<real> vres0, vres1;
		if(clipLineZBuffer(clipper, v0, v1, vres0, vres1))
		{
			drawLineZBufferRW32(surface, zbuffer, vres0, vres1, color);
		}
	}

	void drawScanSolidZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		const Vec4<fixp16> & color)
	{
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_32bit
#include "draw_scan.hpp"
	}

	void drawClippedScanSolidZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		const Vec4<fixp16> & color)
	{
#define __draw_clipped
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_32bit
#include "draw_scan.hpp"
	}

	void drawScanGouraudZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		Vec4<fixp16> lc,
		const Vec4<fixp16> & rc)
	{
#define __draw_gouraud
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_32bit
#include "draw_scan.hpp"
	}

	void drawClippedScanGouraudZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		Vec4<fixp16> lc,
		const Vec4<fixp16> & rc)
	{
#define __draw_clipped
#define __draw_gouraud
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_32bit
#include "draw_scan.hpp"
	}

	void drawScanTextureZBufferW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		Vec2<fixp16> lt,
		const Vec2<fixp16> & rt)
	{
#define __draw_texture
#define __draw_zbuffer_w
#define __draw_32bit
#include "draw_scan.hpp"
	}

	void drawClippedScanTextureZBufferW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		Vec2<fixp16> lt,
		const Vec2<fixp16> & rt)
	{
#define __draw_clipped
#define __draw_texture
#define __draw_zbuffer_w
#define __draw_32bit
#include "draw_scan.hpp"
	}

	void drawScanTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		Vec2<fixp16> lt,
		const Vec2<fixp16> & rt)
	{
#define __draw_texture
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_32bit
#include "draw_scan.hpp"
	}

	void drawClippedScanTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		Vec2<fixp16> lt,
		const Vec2<fixp16> & rt)
	{
#define __draw_clipped
#define __draw_texture
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_32bit
#include "draw_scan.hpp"
	}

	void drawScanGouraudTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		Vec4<fixp16> lc,
		const Vec4<fixp16> & rc,
		Vec2<fixp16> lt,
		const Vec2<fixp16> & rt)
	{
#define __draw_gouraud
#define __draw_texture
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_32bit
#include "draw_scan.hpp"
	}

	void drawClippedScanGouraudTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		Vec4<fixp16> lc,
		const Vec4<fixp16> & rc,
		Vec2<fixp16> lt,
		const Vec2<fixp16> & rt)
	{
#define __draw_clipped
#define __draw_gouraud
#define __draw_texture
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_32bit
#include "draw_scan.hpp"
	}

	void drawTriangleSolidZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & color)
	{
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_func drawScanSolidZBufferRW32
#define __draw_clipped_func drawClippedScanSolidZBufferRW32
#include "draw_triangle.hpp"
	}

	void drawClippedTriangleSolidZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & color)
	{
#define __draw_clipped
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_func drawScanSolidZBufferRW32
#define __draw_clipped_func drawClippedScanSolidZBufferRW32
#include "draw_triangle.hpp"
	}

	void drawTriangleGouraudZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & c0,
		const Vec4<real> & c1,
		const Vec4<real> & c2)
	{
#define __draw_gouraud
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_func drawScanGouraudZBufferRW32
#include "draw_triangle.hpp"
	}

	void drawClippedTriangleGouraudZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & c0,
		const Vec4<real> & c1,
		const Vec4<real> & c2)
	{
#define __draw_clipped
#define __draw_gouraud
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_func drawScanGouraudZBufferRW32
#define __draw_clipped_func drawClippedScanGouraudZBufferRW32
#include "draw_triangle.hpp"
	}

	void drawTriangleTextureZBufferW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2)
	{
#define __draw_texture
#define __draw_zbuffer_w
#define __draw_func drawScanTextureZBufferW32
#include "draw_triangle.hpp"
	}

	void drawClippedTriangleTextureZBufferW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2)
	{
#define __draw_clipped
#define __draw_texture
#define __draw_zbuffer_w
#define __draw_func drawScanTextureZBufferW32
#define __draw_clipped_func drawClippedScanTextureZBufferW32
#include "draw_triangle.hpp"
	}

	void drawTriangleTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2)
	{
#define __draw_texture
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_func drawScanTextureZBufferRW32
#include "draw_triangle.hpp"
	}

	void drawClippedTriangleTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2)
	{
#define __draw_clipped
#define __draw_texture
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_func drawScanTextureZBufferRW32
#define __draw_clipped_func drawClippedScanTextureZBufferRW32
#include "draw_triangle.hpp"
	}

	void drawTriangleGouraudTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & c0,
		const Vec4<real> & c1,
		const Vec4<real> & c2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2)
	{
#define __draw_gouraud
#define __draw_texture
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_func drawScanGouraudTextureZBufferRW32
#include "draw_triangle.hpp"
	}

	void drawClippedTriangleGouraudTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & c0,
		const Vec4<real> & c1,
		const Vec4<real> & c2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2)
	{
#define __draw_clipped
#define __draw_gouraud
#define __draw_texture
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_func drawScanGouraudTextureZBufferRW32
#define __draw_clipped_func drawClippedScanGouraudTextureZBufferRW32
#include "draw_triangle.hpp"
	}

	void drawTriangleTexturePerspectiveLPZBufferW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2)
	{
#define __draw_texture
#define __draw_texture_perspective_lp
#define __draw_zbuffer_w
#define __draw_func drawScanTextureZBufferW32
#include "draw_triangle.hpp"
	}

	void drawClippedTriangleTexturePerspectiveLPZBufferW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2)
	{
#define __draw_clipped
#define __draw_texture
#define __draw_texture_perspective_lp
#define __draw_zbuffer_w
#define __draw_func drawScanTextureZBufferW32
#define __draw_clipped_func drawClippedScanTextureZBufferW32
#include "draw_triangle.hpp"
	}

	void drawTriangleTexturePerspectiveLPZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2)
	{
#define __draw_texture
#define __draw_texture_perspective_lp
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_func drawScanTextureZBufferRW32
#include "draw_triangle.hpp"
	}

	void drawClippedTriangleTexturePerspectiveLPZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2)
	{
#define __draw_clipped
#define __draw_texture
#define __draw_texture_perspective_lp
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_func drawScanTextureZBufferRW32
#define __draw_clipped_func drawClippedScanTextureZBufferRW32
#include "draw_triangle.hpp"
	}

	void drawTriangleGouraudTexturePerspectiveLPZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & c0,
		const Vec4<real> & c1,
		const Vec4<real> & c2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2)
	{
#define __draw_gouraud
#define __draw_texture
#define __draw_texture_perspective_lp
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_func drawScanGouraudTextureZBufferRW32
#include "draw_triangle.hpp"
	}

	void drawClippedTriangleGouraudTexturePerspectiveLPZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & c0,
		const Vec4<real> & c1,
		const Vec4<real> & c2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2)
	{
#define __draw_clipped
#define __draw_gouraud
#define __draw_texture
#define __draw_texture_perspective_lp
#define __draw_zbuffer_r
#define __draw_zbuffer_w
#define __draw_func drawScanGouraudTextureZBufferRW32
#define __draw_clipped_func drawClippedScanGouraudTextureZBufferRW32
#include "draw_triangle.hpp"
	}
}
