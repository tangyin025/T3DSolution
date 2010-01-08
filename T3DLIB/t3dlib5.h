
#ifndef __T3DLIB5_H__
#define __T3DLIB5_H__

#include "t3dcommon.h"
#include <windows.h>
#include "t3dlib4.h"
#include <atltypes.h>

#define RGB16_RED_SHIFT		11
#define RGB16_GREEN_SHIFT	5
#define	RGB16_BLUE_SHIFT	0

#define RGB16_RED_RSHIFT	3
#define RGB16_GREEN_RSHIFT	2
#define	RGB16_BLUE_RSHIFT	3

#define RGB16_RED_MASK		0xF800
#define RGB16_GREEN_MASK	0x07E0
#define	RGB16_BLUE_MASK		0x001F

#define RGB32_RED_SHIFT		16
#define RGB32_GREEN_SHIFT	8
#define	RGB32_BLUE_SHIFT	0

#define RGB32_RED_RSHIFT	0
#define RGB32_GREEN_RSHIFT	0
#define	RGB32_BLUE_RSHIFT	0

#define RGB32_RED_MASK		0x00FF0000
#define RGB32_GREEN_MASK	0x0000FF00
#define	RGB32_BLUE_MASK		0x000000FF

#define _RGB16GETR(v)		(((v) & RGB16_RED_MASK)		>> (RGB16_RED_SHIFT		- RGB16_RED_RSHIFT))
#define _RGB16GETG(v)		(((v) & RGB16_GREEN_MASK)	>> (RGB16_GREEN_SHIFT	- RGB16_GREEN_RSHIFT))
#define _RGB16GETB(v)		(((v) & RGB16_BLUE_MASK)	>> (RGB16_BLUE_SHIFT	- RGB16_BLUE_RSHIFT))

#define _RGB32GETR(v)		(((v) & RGB32_RED_MASK)		>> (RGB32_RED_SHIFT		- RGB32_RED_RSHIFT))
#define _RGB32GETG(v)		(((v) & RGB32_GREEN_MASK)	>> (RGB32_GREEN_SHIFT	- RGB32_GREEN_RSHIFT))
#define _RGB32GETB(v)		(((v) & RGB32_BLUE_MASK)	>> (RGB32_BLUE_SHIFT	- RGB32_BLUE_RSHIFT))

#define _RGB16BIT(r, g, b)	((((r) >> RGB16_RED_RSHIFT) << RGB16_RED_SHIFT) | (((g) >> RGB16_GREEN_RSHIFT) << RGB16_GREEN_SHIFT) | (((b) >> RGB16_BLUE_RSHIFT) << RGB16_BLUE_SHIFT))

#define _RGB32BIT(r, g, b)	((((r) >> RGB32_RED_RSHIFT) << RGB32_RED_SHIFT) | (((g) >> RGB32_GREEN_RSHIFT) << RGB32_GREEN_SHIFT) | (((b) >> RGB32_BLUE_RSHIFT) << RGB32_BLUE_SHIFT))

#define _COLORADD(lhs, rhs)	color_add_table[(lhs)][(rhs)]

#define _COLORMUL(lhs, rhs)	color_mul_table[(lhs)][(rhs)]

namespace t3d
{
	inline void memSet16(uint16 * dest, uint16 value, size_t count)
	{
		__asm
		{
			mov		edi,	dest;
			mov		ax,		value;
			mov		ecx,	count;
			rep		stosw;
		}
	}

	inline void memSet32(uint32 * dest, uint32 value, size_t count)
	{
		__asm
		{
			mov		edi,	dest;
			mov		eax,	value;
			mov		ecx,	count;
			rep		stosd;
		}
	}

	extern const unsigned char color_add_table[UCHAR_MAX + 1][UCHAR_MAX + 1];

	extern const unsigned char color_mul_table[UCHAR_MAX + 1][UCHAR_MAX + 1];

	template <typename elem_t>
	class ConstSurfaceRef
	{
	public:
		inline ConstSurfaceRef(elem_t * p, LONG pitch)
			: _p(p), _pitch(pitch)
		{
			assert(NULL != _p);
		}

	public:
		inline const elem_t * operator [] (int y) const
		{
			return (elem_t *)((byte *)_p + _pitch * y);
		}

		inline const elem_t * ptr(void) const
		{
			return _p;
		}

	protected:
		elem_t * _p;

		LONG _pitch;
	};

	template <typename elem_t>
	class SurfaceRef : public ConstSurfaceRef<elem_t>
	{
	public:
		inline SurfaceRef(elem_t * p, LONG pitch)
			: ConstSurfaceRef<elem_t>(p, pitch)
		{
		}

	public:
		inline elem_t * operator [] (int y) const
		{
			return (elem_t *)((byte *)_p + _pitch * y);
		}

		inline elem_t * ptr(void) const
		{
			return _p;
		}
	};

	void fillZBuffer28(
		SurfaceRef<fixp28> zbuffer,
		const CRect & rect,
		real value_inv);

	void fillSurface16(
		SurfaceRef<uint16> surface,
		const CRect & rect,
		const Vec4<real> & color);

	void fillSurface32(
		SurfaceRef<uint32> surface,
		const CRect & rect,
		const Vec4<real> & color);

	void drawHorizonLine32(
		SurfaceRef<uint32> surface,
		const Vec4<real> & v0,
		int width,
		const Vec4<real> & color);

	void drawClippedHorizonLine32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		const Vec4<real> & v0,
		int width,
		const Vec4<real> & color);

	void drawVerticalLine32(
		SurfaceRef<uint32> surface,
		const Vec4<real> & v0,
		int height,
		const Vec4<real> & color);

	void drawClippedVerticalLine32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		const Vec4<real> & v0,
		int height,
		const Vec4<real> & color);

	bool clipLineZBuffer(
		const RECT & clipper,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		Vec4<real> & vres0,
		Vec4<real> & vres1);

	void drawLineZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & color);

	void drawClippedLineZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & color);

	void drawScanSolidZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		const Vec4<fixp16> & color);

	void drawClippedScanSolidZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		const Vec4<fixp16> & color);

	void drawScanGouraudZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		fixp16 lx,
		fixp16 rx,
		int y0,
		fixp28 lz,
		fixp28 rz,
		Vec4<fixp16> lc,
		const Vec4<fixp16> & rc);

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
		const Vec4<fixp16> & rc);

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
		const Vec2<fixp16> & rt);

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
		const Vec2<fixp16> & rt);

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
		const Vec2<fixp16> & rt);

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
		const Vec2<fixp16> & rt);

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
		const Vec2<fixp16> & rt);

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
		const Vec2<fixp16> & rt);

	void drawTriangleSolidZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & color);

	void drawClippedTriangleSolidZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & color);

	void drawTriangleGouraudZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & c0,
		const Vec4<real> & c1,
		const Vec4<real> & c2);

	void drawClippedTriangleGouraudZBufferRW32(
		SurfaceRef<uint32> surface,
		const RECT & clipper,
		SurfaceRef<fixp28> zbuffer,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec4<real> & c0,
		const Vec4<real> & c1,
		const Vec4<real> & c2);

	void drawTriangleTextureZBufferW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2);

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
		const Vec2<real> & t2);

	void drawTriangleTextureZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2);

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
		const Vec2<real> & t2);

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
		const Vec2<real> & t2);

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
		const Vec2<real> & t2);

	void drawTriangleTexturePerspectiveLPZBufferW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2);

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
		const Vec2<real> & t2);

	void drawTriangleTexturePerspectiveLPZBufferRW32(
		SurfaceRef<uint32> surface,
		SurfaceRef<fixp28> zbuffer,
		ConstSurfaceRef<uint32> texture,
		const Vec4<real> & v0,
		const Vec4<real> & v1,
		const Vec4<real> & v2,
		const Vec2<real> & t0,
		const Vec2<real> & t1,
		const Vec2<real> & t2);

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
		const Vec2<real> & t2);

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
		const Vec2<real> & t2);

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
		const Vec2<real> & t2);
}

#endif // __T3DLIB5_H__
