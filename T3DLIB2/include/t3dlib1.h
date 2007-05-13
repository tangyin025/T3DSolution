/**
 * File: T3DLIB2/t3dlib1.h
 */

#ifndef __T3DLIB1_H__
#define __T3DLIB1_H__

#include "t3dcommons.h"

T3DLIB_API void foo(void * pvoid = NULL);

#define MAX_BUFFER_SIZE				MAX_PATH
#define TEXT_BKMODE_OPAQUE			OPAQUE
#define TEXT_BKMODE_TRANSPARENT		TRANSPARENT
#define SAFE_FREE(p)				{ if(p != NULL) { free(p);		p = NULL; } }
#define SAFE_DELETE(p)				{ if(p != NULL) { delete p;		p = NULL; } }
#define SAFE_DELETES(p)				{ if(p != NULL) { delete[] p;	p = NULL; } }
#define SAFE_FCLOSE(p)				{ if(p != NULL) { fclose(p);	p = NULL; } }
#define SAFE_RELEASE(p)				{ if(p != NULL) { p->Release();	p = NULL; } }
#define ON_ERROR_GOTO(e)			{ Set_Last_Error((e), __FILE__, __LINE__) ; goto ON_ERROR; }

#define SET_BIT(byte, option)		((byte) |= (option))
#define RESET_BIT(byte, option)		((byte) &= ~(option))

#define SFORMAT0(pbuf, sfmt)						(sprintf((pbuf), (sfmt)), pbuf)
#define SFORMAT1(pbuf, sfmt, arg1)					(sprintf((pbuf), (sfmt), arg1), pbuf)
#define SFORMAT2(pbuf, sfmt, arg1, arg2)			(sprintf((pbuf), (sfmt), arg1, arg2), pbuf)
#define SFORMAT3(pbuf, sfmt, arg1, arg2, arg3)		(sprintf((pbuf), (sfmt), arg1, arg2, arg3), pbuf)

#ifdef _DEBUG
#define _WARNING(e)									{ if(e) { _RPT0(_CRT_WARN, "warn: " #e "\n"); } }
#define _CTOR_DECLARE(class_name)					class_name::class_name()
#define _CTOR_IMPLEMENT(class_name)					class_name::class_name() { memset(this, 0, sizeof(*this)); }
#define _DTOR_DECLARE(class_name)					class_name::~class_name()
#define _DTOR_IMPLEMENT(class_name, destroy_func)	class_name::~class_name() { destroy_func(this); }
#define _DTOR_IMPLEMENT_W1(class_name, destroy_func, warn_memb1) \
													class_name::~class_name() { _WARNING(warn_memb1 != NULL); destroy_func(this); }
#define _DTOR_IMPLEMENT_W2(class_name, destroy_func, warn_memb1, warn_memb2) \
													class_name::~class_name() { _WARNING(warn_memb1 != NULL); _WARNING(warn_memb2 != NULL); destroy_func(this); }
#define _DTOR_IMPLEMENT_W3(class_name, destroy_func, warn_memb1, warn_memb2, warn_memb3) \
													class_name::~class_name() { _WARNING(warn_memb1 != NULL); _WARNING(warn_memb2 != NULL); _WARNING(warn_memb3 != NULL); destroy_func(this); }
#else
#define _WARNING(e)
#define _CTOR_DECLARE(class_name)
#define _CTOR_IMPLEMENT(class_name)
#define _DTOR_DECLARE(class_name)
#define _DTOR_IMPLEMENT(class_name, destroy_func)
#define _DTOR_IMPLEMENT_W1(class_name, destory_func, warn_memb1)
#define _DTOR_IMPLEMENT_W2(class_name, destory_func, warn_memb1, warn_memb2)
#define _DTOR_IMPLEMENT_W3(class_name, destory_func, warn_memb1, warn_memb2, warn_memb3)
#endif

typedef struct T3DLIB_API ERRORREP_TYP
{
	char	message[MAX_BUFFER_SIZE];
	char	file[MAX_BUFFER_SIZE];
	int		line;

} ERRORREP, * ERRORREP_PTR;

typedef struct T3DLIB_API DDRAWV1_TYP
{
	LPDIRECTDRAW7 lpddraw;

	_CTOR_DECLARE(DDRAWV1_TYP);
	_DTOR_DECLARE(DDRAWV1_TYP);

} DDRAWV1, * DDRAWV1_PTR;

typedef struct T3DLIB_API DDCLIPPERV1_TYP
{
	LPDIRECTDRAWCLIPPER lpddclipper;

	_CTOR_DECLARE(DDCLIPPERV1_TYP);
	_DTOR_DECLARE(DDCLIPPERV1_TYP);

} DDCLIPPERV1, * DDCLIPPERV1_PTR;

typedef struct T3DLIB_API DDSURFACEV1_TYP
{
	LPDIRECTDRAWSURFACE7	lpddsurface;
	int						bpp;
	RECT					rect;

	_CTOR_DECLARE(DDSURFACEV1_TYP);
	_DTOR_DECLARE(DDSURFACEV1_TYP);

} DDSURFACEV1, * DDSURFACEV1_PTR;

typedef struct T3DLIB_API TEXTDCV1_TYP
{
	DDSURFACEV1 *		pddsurface;
	HDC					hdc;
	COLORREF			last_color;
	COLORREF			last_bkcolor;
	int					last_bkmode;

	_CTOR_DECLARE(TEXTDCV1_TYP);
	_DTOR_DECLARE(TEXTDCV1_TYP);

} TEXTDCV1, * TEXTDCV1_PTR;

T3DLIB_API char * Set_Last_Error(const char * pmessage, const char * pfile, const int line);

T3DLIB_API char * Get_Last_Error(char * pmessage, char * pfile = NULL, int * pline = NULL);

T3DLIB_API char * Get_DDraw_Error(char * pbuffer, const HRESULT hresult);

T3DLIB_API bool Create_DDraw(DDRAWV1 * pddraw);

T3DLIB_API bool Create_Fullscreen_DDSurface(const DDRAWV1 * pddraw, DDSURFACEV1 * pddsprimary, DDSURFACEV1 * pddsback);

T3DLIB_API bool Create_Windowed_DDSurface(const DDRAWV1 * pddraw, DDSURFACEV1 * pddsprimary);

T3DLIB_API bool Create_Memoried_DDSurface(const DDRAWV1 * pddraw, DDSURFACEV1 * pddsback, const int width, const int height);

T3DLIB_API bool Create_Videoied_DDSurface(const DDRAWV1 * pddraw, DDSURFACEV1 * pddsback, const int width, const int height);

T3DLIB_API bool Create_Windowed_DDClipper(const DDRAWV1 * pddraw, DDCLIPPERV1 * pddclipper, const HWND hwnd);

T3DLIB_API bool Create_Memoried_DDClipper(const DDRAWV1 * pddraw, DDCLIPPERV1 * pddclipper, const RECT * prect, const int num_rect);

T3DLIB_API void Destroy_DDraw(DDRAWV1 * pddraw);

T3DLIB_API void Destroy_DDClipper(DDCLIPPERV1 * pddclipper);

T3DLIB_API void Destroy_DDSurface(DDSURFACEV1 * pddsurface);

T3DLIB_API bool Attach_DDSurface_DDClipper(DDSURFACEV1 * pddsurface, const DDCLIPPERV1 * pddclipper);

T3DLIB_API bool Set_Fullscreen_Cooperative_Level(DDRAWV1 * pddraw, const HWND hwnd);

T3DLIB_API bool Set_Normal_Cooperative_Level(DDRAWV1 * pddraw);

T3DLIB_API bool Set_Display_Model(DDRAWV1 * pddraw, const int width, const int height, const int bpp);

T3DLIB_API bool Set_DDSurface_Color_Key(DDSURFACEV1 * pddsurface, const DWORD color_value);

T3DLIB_API bool Flip_DDSurface(DDSURFACEV1 * pddsprimary);

T3DLIB_API bool Blit_DDSurface(DDSURFACEV1 * pddsdest, RECT * prdest, DDSURFACEV1 * pddssrc, RECT * prsrc);

T3DLIB_API bool Blit_DDSurface_Src_Color_Key(DDSURFACEV1 * pddsdest, RECT * prdest, DDSURFACEV1 * pddssrc, RECT * prsrc);

T3DLIB_API bool Blit_DDSurface_Fast(DDSURFACEV1 * pddsdest, const int x, const int y, DDSURFACEV1 * pddssrc, RECT * prsrc);

T3DLIB_API bool Fill_DDSurface(DDSURFACEV1 * pddsurface, RECT * prect, unsigned int color);

T3DLIB_API bool Wait_For_VSynchronize(DDRAWV1 * ddraw, DWORD flags = DDWAITVB_BLOCKBEGIN);

T3DLIB_API bool Begin_Text_DC(DDSURFACEV1 * pddsurface, TEXTDCV1 * ptdc);

T3DLIB_API bool End_Text_DC(TEXTDCV1 * ptdc);

T3DLIB_API void Set_Text_BKColor(TEXTDCV1 * ptdc, COLORREF color);

T3DLIB_API void Set_Text_BKMode(TEXTDCV1 * ptdc, int mode);

T3DLIB_API void Set_Text_Color(TEXTDCV1 * ptdc, COLORREF color);

T3DLIB_API bool Text_Out(TEXTDCV1 * ptdc, char * text, int x, int y);

extern T3DLIB_API ERRORREP		gerror;
extern T3DLIB_API char			gbuffer[MAX_BUFFER_SIZE];
extern T3DLIB_API HRESULT		gresult;

#define MAX_COLOR_PALETTE		(256)
#define _08BIT_SHIFT			(0)
#define _16BIT_SHIFT			(1)
#define _32BIT_SHIFT			(2)
#define _08BIT_BYTES			(1 << _08BIT_SHIFT)
#define _16BIT_BYTES			(1 << _16BIT_SHIFT)
#define _32BIT_BYTES			(1 << _32BIT_SHIFT)
#define MIN_COLOR_BPP			(8)
#define MAX_COLOR_BPP			(32)
#define MIN_RECOMMENDED_WIDTH	(2)
#define MAX_RECOMMENDED_WIDTH	(2048)
#define MIN_RECOMMENDED_PITCH	(MIN_RECOMMENDED_WIDTH << _16BIT_SHIFT)
#define MAX_RECOMMENDED_PITCH	(MAX_RECOMMENDED_WIDTH << _32BIT_SHIFT)
#define BITMAP_ID				(0x4D42) // (('B' << 0) | ('M' << 8))

#define _16BIT_GETR(c)			(0x1F & ((c) >> 11))
#define _16BIT_GETG(c)			(0x3F & ((c) >> 5))
#define _16BIT_GETB(c)			(0x1F & ((c) >> 0))
#define _32BIT_GETR(c)			(0xFF & ((c) >> 16))
#define _32BIT_GETG(c)			(0xFF & ((c) >> 8))
#define _32BIT_GETB(c)			(0xFF & ((c) >> 0))
#define _RGB16BIT(r, g, b)		(((r) << 11) | ((g) << 5) | ((b) << 0))
#define _RGB32BIT(r, g, b)		(((r) << 16) | ((g) << 8) | ((b) << 0))

#pragma warning(disable : 4201)
typedef struct T3DLIB_API XRGB16_TYP
{
	union
	{
		unsigned short val;

		struct
		{
			unsigned b : 5;
			unsigned g : 6;
			unsigned r : 5;
			//unsigned x : 0;
		};
	};

} XRGB16, * XRGB16_PTR;

typedef struct T3DLIB_API XRGB32_TYP
{
	union
	{
		unsigned int val;

		struct
		{
			unsigned char b;
			unsigned char g;
			unsigned char r;
			unsigned char x;
		};
	};

} XRGB32, * XRGB32_PTR;

typedef struct T3DLIB_API BITMAPV1_TYP
{
	BITMAPFILEHEADER	bitmapfileheader;
	BITMAPINFOHEADER	bitmapinfoheader;
	PALETTEENTRY		palette[MAX_COLOR_PALETTE];
	unsigned char *		pbuffer;

	_CTOR_DECLARE(BITMAPV1_TYP);
	_DTOR_DECLARE(BITMAPV1_TYP);

} BITMAPV1, * BITMAPV1_PTR;

typedef struct T3DLIB_API SURFACEV1_TYP
{
	unsigned char *		pbuffer;
	long				pitch;
	int					width;
	int					height;
	int					pitch_shift;
	int					color_shift;

} SURFACEV1, * SURFACEV1_PTR;

typedef struct T3DLIB_API IMAGEV1_TYP
{
	union
	{
		struct
		{
			unsigned char *		pbuffer;
			long				pitch;
			int					width;
			int					height;
			int					pitch_shift;
			int					color_shift;
		};

		struct
		{
			SURFACEV1 _SURFACE;
		};
	};

	_CTOR_DECLARE(IMAGEV1_TYP);
	_DTOR_DECLARE(IMAGEV1_TYP);

} IMAGEV1, * IMAGEV1_PTR;
#pragma warning(default : 4201)

typedef struct T3DLIB_API TEXTUREV1_TYP
{
	//XRGB32 *			pbuffer;
	unsigned char *		pbuffer;
	long				pitch;
	int					width;
	int					height;
	int					pitch_shift;
	int					color_shift;

	_CTOR_DECLARE(TEXTUREV1_TYP);
	_DTOR_DECLARE(TEXTUREV1_TYP);

} TEXTUREV1, * TEXTUREV1_PTR;

T3DLIB_API bool Init_T3dlib1(int bpp);

T3DLIB_API bool Compute_Color_Shift(int * pcshift, const int bpp);

T3DLIB_API bool Compute_Pitch_Shift(int * ppshift, const long pitch);

T3DLIB_API bool Get_Recommended_Pitch(long * precommend, const long pitch);

T3DLIB_API bool Get_Recommended_Width(int * precommend, const int width);

T3DLIB_API unsigned int Create_RGBI16(int r, int g, int b);

T3DLIB_API unsigned int Create_RGBI32(int r, int g, int b);

T3DLIB_API unsigned int Create_RGBF16(float fr, float fg, float fb);

T3DLIB_API unsigned int Create_RGBF32(float fr, float fg, float fb);

T3DLIB_API bool Create_Bitmap_From_File(BITMAPV1 * pbitmap, const char * fname);

T3DLIB_API bool Lock_DDSurface(const DDSURFACEV1 * pddsurface, SURFACEV1 * psurface);

T3DLIB_API bool Unlock_DDSurface(const DDSURFACEV1 * pddsurface);

T3DLIB_API bool Create_Image16(IMAGEV1 * pimage, const int width, const int height);

T3DLIB_API bool Create_Image32(IMAGEV1 * pimage, const int width, const int height);

T3DLIB_API bool Create_Texture16(TEXTUREV1 * ptexture, const int width, const int height);

T3DLIB_API bool Create_Texture32(TEXTUREV1 * ptexture, const int width, const int height);

T3DLIB_API bool Load_Surface_From_Bitmap16(SURFACEV1 * psurface, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height);

T3DLIB_API bool Load_Surface_From_Bitmap32(SURFACEV1 * psurface, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height);

T3DLIB_API bool Load_Image_From_Bitmap16(IMAGEV1 * pimage, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height);

T3DLIB_API bool Load_Image_From_Bitmap32(IMAGEV1 * pimage, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height);

T3DLIB_API bool Load_Texture_From_Bitmap16(TEXTUREV1 * ptexture, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height);

T3DLIB_API bool Load_Texture_From_Bitmap32(TEXTUREV1 * ptexture, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height);

T3DLIB_API void Destroy_Bitmap(BITMAPV1 * pbitmap);

T3DLIB_API void Destroy_Image(IMAGEV1 * pimage);

T3DLIB_API void Destroy_Texture(TEXTUREV1 * ptexture);

extern T3DLIB_API int COLOR_SHIFT_TABLE[MAX_COLOR_BPP + 1];
extern T3DLIB_API int PITCH_SHIFT_TABLE[MAX_RECOMMENDED_PITCH + 1];

extern T3DLIB_API unsigned int (* Create_RGBI)(int r, int g, int b);
extern T3DLIB_API unsigned int (* Create_RGBF)(float fr, float fg, float fb);
extern T3DLIB_API bool (* Create_Image)(IMAGEV1 * pimage, const int width, const int height);
extern T3DLIB_API bool (* Create_Texture)(TEXTUREV1 * ptexture, const int width, const int height);
extern T3DLIB_API bool (* Load_Surface_From_Bitmap)(SURFACEV1 * psurface, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height);
extern T3DLIB_API bool (* Load_Image_From_Bitmap)(IMAGEV1 * pimage, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height);
extern T3DLIB_API bool (* Load_Texture_From_Bitmap)(TEXTUREV1 * ptexture, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height);

inline void Mem_Set_Word(void * dest, unsigned short value, long count)
{
	assert(count > 0);

	_asm
	{
		mov		edi,	dest;
		mov		ax,		value;
		mov		ecx,	count;
		rep		stosw;

	} // _asm
}

inline void Mem_Set_Quad(void * dest, unsigned int value, long count)
{
	assert(count > 0);

	_asm
	{
		mov		edi,	dest;
		mov		eax,	value;
		mov		ecx,	count;
		rep		stosd;

	} // _asm
}

//inline void Mem_Cpy_Word(void * dest, const void * src, long count)
//{
//	assert(abs((long)((short *)dest - (short *)src)) >= count);
//
//	_asm
//	{
//		mov		edi,	dest;
//		mov		esi,	src;
//		mov		ecx,	count;
//		rep		movsw;
//
//	} // _asm
//}

//inline void Mem_Cpy_Quad(void * dest, const void * src, long count)
//{
//	assert(abs((long)((int *)dest - (int *)src)) >= count);
//
//	_asm
//	{
//		mov		edi,	dest;
//		mov		esi,	src;
//		mov		ecx,	count;
//		rep		movsd;
//
//	} // _asm
//}

#endif // __T3DLIB1_H__
