/*
 * File: T3DLIB2/t3dlib1.cpp
 */

#include "t3dheaders.h"
#include "t3dlib1.h"

BOOL APIENTRY DllMain(HANDLE	hModule,
					  DWORD		ul_reason_for_call,
					  LPVOID	lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		_CrtDumpMemoryLeaks();
		break;
	}

	return TRUE;
	hModule;
	lpReserved;
}

T3DLIB_API void foo(void * pvoid /*= NULL*/)
{
	return;
	pvoid;
}

#define GET_DDRAW_ERROR(h)		(Get_DDraw_Error(gbuffer, (h)))

__declspec(thread) ERRORREP			gerror = {{""}, {""}, 0};
__declspec(thread) char				gbuffer[MAX_BUFFER_SIZE] = "";
__declspec(thread) HRESULT			gresult = DD_OK;
__declspec(thread) DDSURFACEDESC2	gddsd;

_CTOR_IMPLEMENT(DDRAWV1_TYP);
_DTOR_IMPLEMENT_W1(DDRAWV1_TYP, Destroy_DDraw, lpddraw);

_CTOR_IMPLEMENT(DDCLIPPERV1_TYP);
_DTOR_IMPLEMENT_W1(DDCLIPPERV1_TYP, Destroy_DDClipper, lpddclipper);

_CTOR_IMPLEMENT(DDSURFACEV1_TYP);
_DTOR_IMPLEMENT_W1(DDSURFACEV1_TYP, Destroy_DDSurface, lpddsurface);

_CTOR_IMPLEMENT(TEXTDCV1_TYP);
_DTOR_IMPLEMENT_W2(TEXTDCV1_TYP, foo, pddsurface, hdc);

T3DLIB_API char * Set_Last_Error(const char * pmessage, const char * pfile, const int line)
{
	gerror.line = line;
	strcpy(gerror.file, pfile);
	return strcpy(gerror.message, pmessage);
}

T3DLIB_API char * Get_Last_Error(char * pmessage, char * pfile /*= NULL*/, int * pline /*= NULL*/)
{
	assert(pmessage != NULL);

	if(pline != NULL)
		*pline = gerror.line;
	if(pfile != NULL)
		strcpy(pfile, gerror.file);
	return strcpy(pmessage, gerror.message);
}

T3DLIB_API char * Get_DDraw_Error(char * pbuffer, const HRESULT hresult)
{
	char * pmessage;
	switch(hresult)
	{
	case DD_OK:
		pmessage = "DD_OK"; break;
	case DDERR_ALREADYINITIALIZED:
		pmessage = "DDERR_ALREADYINITIALIZED"; break;
	case DDERR_BLTFASTCANTCLIP:
		pmessage = "DDERR_BLTFASTCANTCLIP"; break;
	case DDERR_CANNOTATTACHSURFACE:
		pmessage = "DDERR_CANNOTATTACHSURFACE"; break;
	case DDERR_CANNOTDETACHSURFACE:
		pmessage = "DDERR_CANNOTDETACHSURFACE"; break;
	case DDERR_CANTCREATEDC:
		pmessage = "DDERR_CANTCREATEDC"; break;
	case DDERR_CANTDUPLICATE:
		pmessage = "DDERR_CANTDUPLICATE"; break;
	case DDERR_CANTLOCKSURFACE:
		pmessage = "DDERR_CANTLOCKSURFACE"; break;
	case DDERR_CANTPAGELOCK:
		pmessage = "DDERR_CANTPAGELOCK"; break;
	case DDERR_CANTPAGEUNLOCK:
		pmessage = "DDERR_CANTPAGEUNLOCK"; break;
	case DDERR_CLIPPERISUSINGHWND:
		pmessage = "DDERR_CLIPPERISUSINGHWND"; break;
	case DDERR_COLORKEYNOTSET:
		pmessage = "DDERR_COLORKEYNOTSET"; break;
	case DDERR_CURRENTLYNOTAVAIL:
		pmessage = "DDERR_CURRENTLYNOTAVAIL"; break;
	case DDERR_DDSCAPSCOMPLEXREQUIRED:
		pmessage = "DDERR_DDSCAPSCOMPLEXREQUIRED"; break;
	case DDERR_DCALREADYCREATED:
		pmessage = "DDERR_DCALREADYCREATED"; break;
	case DDERR_DEVICEDOESNTOWNSURFACE:
		pmessage = "DDERR_DEVICEDOESNTOWNSURFACE"; break;
	case DDERR_DIRECTDRAWALREADYCREATED:
		pmessage = "DDERR_DIRECTDRAWALREADYCREATED"; break;
	case DDERR_EXCEPTION:
		pmessage = "DDERR_EXCEPTION"; break;
	case DDERR_EXCLUSIVEMODEALREADYSET:
		pmessage = "DDERR_EXCLUSIVEMODEALREADYSET"; break;
	case DDERR_EXPIRED:
		pmessage = "DDERR_EXPIRED"; break;
	case DDERR_GENERIC:
		pmessage = "DDERR_GENERIC"; break;
	case DDERR_HEIGHTALIGN:
		pmessage = "DDERR_HEIGHTALIGN"; break;
	case DDERR_HWNDALREADYSET:
		pmessage = "DDERR_HWNDALREADYSET"; break;
	case DDERR_HWNDSUBCLASSED:
		pmessage = "DDERR_HWNDSUBCLASSED"; break;
	case DDERR_IMPLICITLYCREATED:
		pmessage = "DDERR_IMPLICITLYCREATED"; break;
	case DDERR_INCOMPATIBLEPRIMARY:
		pmessage = "DDERR_INCOMPATIBLEPRIMARY"; break;
	case DDERR_INVALIDCAPS:
		pmessage = "DDERR_INVALIDCAPS"; break;
	case DDERR_INVALIDCLIPLIST:
		pmessage = "DDERR_INVALIDCLIPLIST"; break;
	case DDERR_INVALIDDIRECTDRAWGUID:
		pmessage = "DDERR_INVALIDDIRECTDRAWGUID"; break;
	case DDERR_INVALIDMODE:
		pmessage = "DDERR_INVALIDMODE"; break;
	case DDERR_INVALIDOBJECT:
		pmessage = "DDERR_INVALIDOBJECT"; break;
	case DDERR_INVALIDPARAMS:
		pmessage = "DDERR_INVALIDPARAMS"; break;
	case DDERR_INVALIDPIXELFORMAT:
		pmessage = "DDERR_INVALIDPIXELFORMAT"; break;
	case DDERR_INVALIDPOSITION:
		pmessage = "DDERR_INVALIDPOSITION"; break;
	case DDERR_INVALIDRECT:
		pmessage = "DDERR_INVALIDRECT"; break;
	case DDERR_INVALIDSTREAM:
		pmessage = "DDERR_INVALIDSTREAM"; break;
	case DDERR_INVALIDSURFACETYPE:
		pmessage = "DDERR_INVALIDSURFACETYPE"; break;
	case DDERR_LOCKEDSURFACES:
		pmessage = "DDERR_LOCKEDSURFACES"; break;
	case DDERR_MOREDATA:
		pmessage = "DDERR_MOREDATA"; break;
	case DDERR_NEWMODE:
		pmessage = "DDERR_NEWMODE"; break;
	case DDERR_NO3D:
		pmessage = "DDERR_NO3D"; break;
	case DDERR_NOALPHAHW:
		pmessage = "DDERR_NOALPHAHW"; break;
	case DDERR_NOBLTHW:
		pmessage = "DDERR_NOBLTHW"; break;
	case DDERR_NOCLIPLIST:
		pmessage = "DDERR_NOCLIPLIST"; break;
	case DDERR_NOCLIPPERATTACHED:
		pmessage = "DDERR_NOCLIPPERATTACHED"; break;
	case DDERR_NOCOLORCONVHW:
		pmessage = "DDERR_NOCOLORCONVHW"; break;
	case DDERR_NOCOLORKEY:
		pmessage = "DDERR_NOCOLORKEY"; break;
	case DDERR_NOCOLORKEYHW:
		pmessage = "DDERR_NOCOLORKEYHW"; break;
	case DDERR_NOCOOPERATIVELEVELSET:
		pmessage = "DDERR_NOCOOPERATIVELEVELSET"; break;
	case DDERR_NODC:
		pmessage = "DDERR_NODC"; break;
	case DDERR_NODDROPSHW:
		pmessage = "DDERR_NODDROPSHW"; break;
	case DDERR_NODIRECTDRAWHW:
		pmessage = "DDERR_NODIRECTDRAWHW"; break;
	case DDERR_NODIRECTDRAWSUPPORT:
		pmessage = "DDERR_NODIRECTDRAWSUPPORT"; break;
	case DDERR_NODRIVERSUPPORT:
		pmessage = "DDERR_NODRIVERSUPPORT"; break;
	case DDERR_NOEMULATION:
		pmessage = "DDERR_NOEMULATION"; break;
	case DDERR_NOEXCLUSIVEMODE:
		pmessage = "DDERR_NOEXCLUSIVEMODE"; break;
	case DDERR_NOFLIPHW:
		pmessage = "DDERR_NOFLIPHW"; break;
	case DDERR_NOFOCUSWINDOW:
		pmessage = "DDERR_NOFOCUSWINDOW"; break;
	case DDERR_NOGDI:
		pmessage = "DDERR_NOGDI"; break;
	case DDERR_NOHWND:
		pmessage = "DDERR_NOHWND"; break;
	case DDERR_NOMIPMAPHW:
		pmessage = "DDERR_NOMIPMAPHW"; break;
	case DDERR_NOMIRRORHW:
		pmessage = "DDERR_NOMIRRORHW"; break;
	case DDERR_NOMONITORINFORMATION:
		pmessage = "DDERR_NOMONITORINFORMATION"; break;
	case DDERR_NONONLOCALVIDMEM:
		pmessage = "DDERR_NONONLOCALVIDMEM"; break;
	case DDERR_NOOPTIMIZEHW:
		pmessage = "DDERR_NOOPTIMIZEHW"; break;
	case DDERR_NOOVERLAYDEST:
		pmessage = "DDERR_NOOVERLAYDEST"; break;
	case DDERR_NOOVERLAYHW:
		pmessage = "DDERR_NOOVERLAYHW"; break;
	case DDERR_NOPALETTEATTACHED:
		pmessage = "DDERR_NOPALETTEATTACHED"; break;
	case DDERR_NOPALETTEHW:
		pmessage = "DDERR_NOPALETTEHW"; break;
	case DDERR_NORASTEROPHW:
		pmessage = "DDERR_NORASTEROPHW"; break;
	case DDERR_NOROTATIONHW:
		pmessage = "DDERR_NOROTATIONHW"; break;
	case DDERR_NOSTEREOHARDWARE:
		pmessage = "DDERR_NOSTEREOHARDWARE"; break;
	case DDERR_NOSTRETCHHW:
		pmessage = "DDERR_NOSTRETCHHW"; break;
	case DDERR_NOSURFACELEFT:
		pmessage = "DDERR_NOSURFACELEFT"; break;
	case DDERR_NOT4BITCOLOR:
		pmessage = "DDERR_NOT4BITCOLOR"; break;
	case DDERR_NOT4BITCOLORINDEX:
		pmessage = "DDERR_NOT4BITCOLORINDEX"; break;
	case DDERR_NOT8BITCOLOR:
		pmessage = "DDERR_NOT8BITCOLOR"; break;
	case DDERR_NOTAOVERLAYSURFACE:
		pmessage = "DDERR_NOTAOVERLAYSURFACE"; break;
	case DDERR_NOTEXTUREHW:
		pmessage = "DDERR_NOTEXTUREHW"; break;
	case DDERR_NOTFLIPPABLE:
		pmessage = "DDERR_NOTFLIPPABLE"; break;
	case DDERR_NOTFOUND:
		pmessage = "DDERR_NOTFOUND"; break;
	case DDERR_NOTINITIALIZED:
		pmessage = "DDERR_NOTINITIALIZED"; break;
	case DDERR_NOTLOADED:
		pmessage = "DDERR_NOTLOADED"; break;
	case DDERR_NOTLOCKED:
		pmessage = "DDERR_NOTLOCKED"; break;
	case DDERR_NOTPAGELOCKED:
		pmessage = "DDERR_NOTPAGELOCKED"; break;
	case DDERR_NOTPALETTIZED:
		pmessage = "DDERR_NOTPALETTIZED"; break;
	case DDERR_NOVSYNCHW:
		pmessage = "DDERR_NOVSYNCHW"; break;
	case DDERR_NOZBUFFERHW:
		pmessage = "DDERR_NOZBUFFERHW"; break;
	case DDERR_NOZOVERLAYHW:
		pmessage = "DDERR_NOZOVERLAYHW"; break;
	case DDERR_OUTOFCAPS:
		pmessage = "DDERR_OUTOFCAPS"; break;
	case DDERR_OUTOFMEMORY:
		pmessage = "DDERR_OUTOFMEMORY"; break;
	case DDERR_OUTOFVIDEOMEMORY:
		pmessage = "DDERR_OUTOFVIDEOMEMORY"; break;
	case DDERR_OVERLAPPINGRECTS:
		pmessage = "DDERR_OVERLAPPINGRECTS"; break;
	case DDERR_OVERLAYCANTCLIP:
		pmessage = "DDERR_OVERLAYCANTCLIP"; break;
	case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
		pmessage = "DDERR_OVERLAYCOLORKEYONLYONEACTIVE"; break;
	case DDERR_OVERLAYNOTVISIBLE:
		pmessage = "DDERR_OVERLAYNOTVISIBLE"; break;
	case DDERR_PALETTEBUSY:
		pmessage = "DDERR_PALETTEBUSY"; break;
	case DDERR_PRIMARYSURFACEALREADYEXISTS:
		pmessage = "DDERR_PRIMARYSURFACEALREADYEXISTS"; break;
	case DDERR_REGIONTOOSMALL:
		pmessage = "DDERR_REGIONTOOSMALL"; break;
	case DDERR_SURFACEALREADYATTACHED:
		pmessage = "DDERR_SURFACEALREADYATTACHED"; break;
	case DDERR_SURFACEALREADYDEPENDENT:
		pmessage = "DDERR_SURFACEALREADYDEPENDENT"; break;
	case DDERR_SURFACEBUSY:
		pmessage = "DDERR_SURFACEBUSY"; break;
	case DDERR_SURFACEISOBSCURED:
		pmessage = "DDERR_SURFACEISOBSCURED"; break;
	case DDERR_SURFACELOST:
		pmessage = "DDERR_SURFACELOST"; break;
	case DDERR_SURFACENOTATTACHED:
		pmessage = "DDERR_SURFACENOTATTACHED"; break;
	case DDERR_TESTFINISHED:
		pmessage = "DDERR_TESTFINISHED"; break;
	case DDERR_TOOBIGHEIGHT:
		pmessage = "DDERR_TOOBIGHEIGHT"; break;
	case DDERR_TOOBIGSIZE:
		pmessage = "DDERR_TOOBIGSIZE"; break;
	case DDERR_TOOBIGWIDTH:
		pmessage = "DDERR_TOOBIGWIDTH"; break;
	case DDERR_UNSUPPORTED:
		pmessage = "DDERR_UNSUPPORTED"; break;
	case DDERR_UNSUPPORTEDFORMAT:
		pmessage = "DDERR_UNSUPPORTEDFORMAT"; break;
	case DDERR_UNSUPPORTEDMASK:
		pmessage = "DDERR_UNSUPPORTEDMASK"; break;
	case DDERR_UNSUPPORTEDMODE:
		pmessage = "DDERR_UNSUPPORTEDMODE"; break;
	case DDERR_VERTICALBLANKINPROGRESS:
		pmessage = "DDERR_VERTICALBLANKINPROGRESS"; break;
	case DDERR_VIDEONOTACTIVE:
		pmessage = "DDERR_VIDEONOTACTIVE"; break;
	case DDERR_WASSTILLDRAWING:
		pmessage = "DDERR_WASSTILLDRAWING"; break;
	case DDERR_WRONGMODE:
		pmessage = "DDERR_WRONGMODE"; break;
	case DDERR_XALIGN:
		pmessage = "DDERR_XALIGN"; break;
	default:
		//_ASSERT(0);
		pmessage = "unknown ddraw error result"; break;
	}
	return strcpy(pbuffer, pmessage);
}

T3DLIB_API bool Create_DDraw(DDRAWV1 * pddraw)
{
	assert(pddraw->lpddraw == NULL);

	if(FAILED(gresult = DirectDrawCreateEx(NULL, (LPVOID *)&pddraw->lpddraw, IID_IDirectDraw7, NULL)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Create_Fullscreen_DDSurface(const DDRAWV1 * pddraw, DDSURFACEV1 * pddsprimary, DDSURFACEV1 * pddsback)
{
	assert(pddsprimary->lpddsurface == NULL);
	assert(pddsback->lpddsurface == NULL);

	LPDIRECTDRAWSURFACE7 lpddsprimary	= NULL;
	LPDIRECTDRAWSURFACE7 lpddsback		= NULL;

	memset(&gddsd, 0, sizeof(gddsd));
	gddsd.dwSize			= sizeof(gddsd);
	gddsd.dwFlags			= DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	gddsd.ddsCaps.dwCaps	= DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	gddsd.dwBackBufferCount	= 1;
	if(FAILED(gresult = pddraw->lpddraw->CreateSurface(&gddsd, &lpddsprimary, NULL)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	DDSCAPS2 ddscaps;
	memset(&ddscaps, 0, sizeof(ddscaps));
	ddscaps.dwCaps			= DDSCAPS_BACKBUFFER;
	if(FAILED(gresult = lpddsprimary->GetAttachedSurface(&ddscaps, &lpddsback)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	if(FAILED(gresult = lpddsprimary->GetSurfaceDesc(&gddsd)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	pddsprimary->bpp			= gddsd.ddpfPixelFormat.dwRGBBitCount;
	pddsprimary->rect.right		= gddsd.dwWidth;
	pddsprimary->rect.bottom	= gddsd.dwHeight;

	pddsback->bpp				= gddsd.ddpfPixelFormat.dwRGBBitCount;
	pddsback->rect.right		= gddsd.dwWidth;
	pddsback->rect.bottom		= gddsd.dwHeight;

	pddsprimary->lpddsurface	= lpddsprimary;
	pddsback->lpddsurface		= lpddsback;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpddsback);
	SAFE_RELEASE(lpddsprimary);
	return false;
}

T3DLIB_API bool Create_Windowed_DDSurface(const DDRAWV1 * pddraw, DDSURFACEV1 * pddsprimary)
{
	assert(pddsprimary->lpddsurface == NULL);

	LPDIRECTDRAWSURFACE7 lpddsurface = NULL;
	memset(&gddsd, 0, sizeof(gddsd));
	gddsd.dwSize			= sizeof(gddsd);
	gddsd.dwFlags			= DDSD_CAPS;
	gddsd.ddsCaps.dwCaps	= DDSCAPS_PRIMARYSURFACE;
	gddsd.dwBackBufferCount	= 0;
	if(FAILED(gresult = pddraw->lpddraw->CreateSurface(&gddsd, &lpddsurface, NULL)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	if(FAILED(gresult = lpddsurface->GetSurfaceDesc(&gddsd)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	pddsprimary->bpp			= gddsd.ddpfPixelFormat.dwRGBBitCount;
	pddsprimary->rect.right		= gddsd.dwWidth;
	pddsprimary->rect.bottom	= gddsd.dwHeight;

	pddsprimary->lpddsurface	= lpddsurface;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpddsurface);
	return false;
}

T3DLIB_API bool Create_Memoried_DDSurface(const DDRAWV1 * pddraw, DDSURFACEV1 * pddsback, const int width, const int height)
{
	assert(pddsback->lpddsurface == NULL);

	LPDIRECTDRAWSURFACE7 lpddsurface = NULL;
	int rwidth;
	if(!Get_Recommended_Width(&rwidth, width))
		ON_ERROR_GOTO("cannot get recommended width");

	memset(&gddsd, 0, sizeof(gddsd));
	gddsd.dwSize			= sizeof(gddsd);
	gddsd.dwFlags			= DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	gddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	gddsd.dwWidth			= rwidth;
	gddsd.dwHeight			= height;
	if(FAILED(gresult = pddraw->lpddraw->CreateSurface(&gddsd, &lpddsurface, NULL)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	if(FAILED(gresult = lpddsurface->GetSurfaceDesc(&gddsd)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	pddsback->bpp				= gddsd.ddpfPixelFormat.dwRGBBitCount;
	pddsback->rect.right		= width; //gddsd.dwWidth;
	pddsback->rect.bottom		= gddsd.dwHeight;

	pddsback->lpddsurface		= lpddsurface;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpddsurface);
	return false;
}

T3DLIB_API bool Create_Videoied_DDSurface(const DDRAWV1 * pddraw, DDSURFACEV1 * pddsback, const int width, const int height)
{
	assert(pddsback->lpddsurface == NULL);

	LPDIRECTDRAWSURFACE7 lpddsurface = NULL;
	int rwidth;
	if(!Get_Recommended_Width(&rwidth, width))
		ON_ERROR_GOTO("cannot get recommended width");

	memset(&gddsd, 0, sizeof(gddsd));
	gddsd.dwSize			= sizeof(gddsd);
	gddsd.dwFlags			= DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	gddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
	gddsd.dwWidth			= rwidth;
	gddsd.dwHeight			= height;
	if(FAILED(gresult = pddraw->lpddraw->CreateSurface(&gddsd, &lpddsurface, NULL)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	if(FAILED(gresult = lpddsurface->GetSurfaceDesc(&gddsd)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	pddsback->bpp				= gddsd.ddpfPixelFormat.dwRGBBitCount;
	pddsback->rect.right		= width; //gddsd.dwWidth;
	pddsback->rect.bottom		= gddsd.dwHeight;

	pddsback->lpddsurface		= lpddsurface;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpddsurface);
	return false;
}

T3DLIB_API bool Create_Windowed_DDClipper(const DDRAWV1 * pddraw, DDCLIPPERV1 * pddclipper, const HWND hwnd)
{
	assert(pddclipper->lpddclipper == NULL);

	LPDIRECTDRAWCLIPPER lpddclipper = NULL;
	if(FAILED(gresult = pddraw->lpddraw->CreateClipper(0, &lpddclipper, NULL)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	if(FAILED(gresult = lpddclipper->SetHWnd(0, hwnd)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	pddclipper->lpddclipper = lpddclipper;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpddclipper);
	return false;
}

T3DLIB_API bool Create_Memoried_DDClipper(const DDRAWV1 * pddraw, DDCLIPPERV1 * pddclipper, const RECT * prect, const int num_rect)
{
	assert(pddclipper->lpddclipper == NULL);

	LPDIRECTDRAWCLIPPER	lpddclipper = NULL;
	LPRGNDATA			lprd = NULL;

	if(FAILED(gresult = pddraw->lpddraw->CreateClipper(0, &lpddclipper, NULL)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	if(NULL == (lprd = (LPRGNDATA)malloc(sizeof(RGNDATAHEADER) + num_rect * sizeof(RECT))))
		ON_ERROR_GOTO("malloc LPRGNDATA failed");

	memset(lprd, 0, sizeof(RGNDATAHEADER) + num_rect * sizeof(RECT));
	lprd->rdh.dwSize			= sizeof(lprd->rdh);
	lprd->rdh.iType				= RDH_RECTANGLES;
	lprd->rdh.nCount			= num_rect;
	lprd->rdh.nRgnSize			= num_rect * sizeof(RECT);
	lprd->rdh.rcBound.left		= 6400;
	lprd->rdh.rcBound.top		= 6400;
	lprd->rdh.rcBound.right		= -6400;
	lprd->rdh.rcBound.bottom	= -6400;

	int i;
	for(i = 0; i < num_rect; i++)
	{
		lprd->rdh.rcBound.left		= MIN(lprd->rdh.rcBound.left,	prect[i].left);
		lprd->rdh.rcBound.top		= MIN(lprd->rdh.rcBound.top,	prect[i].top);
		lprd->rdh.rcBound.right		= MAX(lprd->rdh.rcBound.right,	prect[i].right);
		lprd->rdh.rcBound.bottom	= MAX(lprd->rdh.rcBound.bottom,	prect[i].bottom);
	}
	memcpy(lprd->Buffer, prect, num_rect * sizeof(RECT));
	if(FAILED(gresult = lpddclipper->SetClipList(lprd, 0)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	free(lprd);
	pddclipper->lpddclipper = lpddclipper;
	return true;

ON_ERROR:
	SAFE_FREE(lprd);
	SAFE_RELEASE(lpddclipper);
	return false;
}

T3DLIB_API void Destroy_DDraw(DDRAWV1 * pddraw)
{
	SAFE_RELEASE(pddraw->lpddraw);
}

T3DLIB_API void Destroy_DDClipper(DDCLIPPERV1 * pddclipper)
{
	SAFE_RELEASE(pddclipper->lpddclipper);
}

T3DLIB_API void Destroy_DDSurface(DDSURFACEV1 * pddsurface)
{
	SAFE_RELEASE(pddsurface->lpddsurface);
	memset(pddsurface, 0, sizeof(*pddsurface));
}

T3DLIB_API bool Attach_DDSurface_DDClipper(DDSURFACEV1 * pddsurface, const DDCLIPPERV1 * pddclipper)
{
	if(FAILED(gresult = pddsurface->lpddsurface->SetClipper(pddclipper->lpddclipper)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Set_Fullscreen_Cooperative_Level(DDRAWV1 * pddraw, const HWND hwnd)
{
	if(FAILED(gresult = pddraw->lpddraw->SetCooperativeLevel(hwnd, DDSCL_ALLOWMODEX
			| DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE
			| DDSCL_FULLSCREEN | DDSCL_MULTITHREADED)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Set_Normal_Cooperative_Level(DDRAWV1 * pddraw)
{
	if(FAILED(gresult = pddraw->lpddraw->SetCooperativeLevel(NULL, DDSCL_NORMAL)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Set_Display_Model(DDRAWV1 * pddraw, const int width, const int height, const int bpp)
{
	if(FAILED(gresult = pddraw->lpddraw->SetDisplayMode(width, height, bpp, 0, 0)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Set_DDSurface_Color_Key(DDSURFACEV1 * pddsurface, const DWORD color_value)
{
	DDCOLORKEY color_key;
	color_key.dwColorSpaceLowValue	= color_value;
	color_key.dwColorSpaceHighValue	= color_value;
	if(FAILED(gresult = pddsurface->lpddsurface->SetColorKey(DDCKEY_SRCBLT, &color_key)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Flip_DDSurface(DDSURFACEV1 * pddsprimary)
{
	//while(FAILED(/*gresult =*/ psprimary->lpddsurface->Flip(NULL, DDFLIP_WAIT)))
	//	;
	if(FAILED(gresult = pddsprimary->lpddsurface->Flip(NULL, DDFLIP_WAIT)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Blit_DDSurface(DDSURFACEV1 * pddsdest, RECT * prdest, DDSURFACEV1 * pddssrc, RECT * prsrc)
{
	if(FAILED(gresult = pddsdest->lpddsurface->Blt(prdest, pddssrc->lpddsurface, prsrc, DDBLT_DONOTWAIT, NULL)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Blit_DDSurface_Src_Color_Key(DDSURFACEV1 * pddsdest, RECT * prdest, DDSURFACEV1 * pddssrc, RECT * prsrc)
{
	if(FAILED(gresult = pddsdest->lpddsurface->Blt(prdest, pddssrc->lpddsurface, prsrc, DDBLT_DONOTWAIT | DDBLT_KEYSRC, NULL)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Blit_DDSurface_Fast(DDSURFACEV1 * pddsdest, const int x, const int y, DDSURFACEV1 * pddssrc, RECT * prsrc)
{
	if(FAILED(gresult = pddsdest->lpddsurface->BltFast(x, y, pddssrc->lpddsurface, prsrc, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Fill_DDSurface(DDSURFACEV1 * pddsurface, RECT * prect, unsigned int color)
{
	static DDBLTFX ddbf = {0};
	//ZeroMemory(&ddbf, sizeof(ddbf));
	ddbf.dwSize			= sizeof(ddbf);
	ddbf.dwFillColor	= color;
	if(FAILED(gresult = pddsurface->lpddsurface->Blt(prect,
			NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbf)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Wait_For_VSynchronize(DDRAWV1 * ddraw, DWORD flags /*= DDWAITVB_BLOCKBEGIN*/)
{
	if(FAILED(gresult = ddraw->lpddraw->WaitForVerticalBlank(flags, 0)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Begin_Text_DC(DDSURFACEV1 * pddsurface, TEXTDCV1 * ptdc)
{
	assert(pddsurface->lpddsurface != NULL);
	assert(ptdc->pddsurface == NULL);
	assert(ptdc->hdc == NULL);

	HDC hdc;
	if(FAILED(gresult = pddsurface->lpddsurface->GetDC(&hdc)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	ptdc->last_color		= GetTextColor(hdc);
	ptdc->last_bkcolor		= GetBkColor(hdc);
	ptdc->last_bkmode		= GetBkMode(hdc);
	ptdc->hdc				= hdc;
	ptdc->pddsurface		= pddsurface;
	return true;

ON_ERROR:
	if(hdc != NULL)
		pddsurface->lpddsurface->ReleaseDC(hdc);
	return false;
}

T3DLIB_API bool End_Text_DC(TEXTDCV1 * ptdc)
{
	assert(ptdc->pddsurface != NULL);
	assert(ptdc->pddsurface->lpddsurface != NULL);
	assert(ptdc->hdc != NULL);

	SetTextColor(ptdc->hdc, ptdc->last_color);
	SetBkColor(ptdc->hdc, ptdc->last_bkcolor);
	SetBkMode(ptdc->hdc, ptdc->last_bkmode);
	if(FAILED(gresult =
			ptdc->pddsurface->lpddsurface->ReleaseDC(ptdc->hdc)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	ptdc->hdc				= NULL;
	ptdc->pddsurface		= NULL;
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API void Set_Text_BKColor(TEXTDCV1 * ptdc, COLORREF color)
{
	SetBkColor(ptdc->hdc, color);
}

T3DLIB_API void Set_Text_BKMode(TEXTDCV1 * ptdc, int mode)
{
	SetBkMode(ptdc->hdc, mode);
}

T3DLIB_API void Set_Text_Color(TEXTDCV1 * ptdc, COLORREF color)
{
	SetTextColor(ptdc->hdc, color);
}

T3DLIB_API bool Text_Out(TEXTDCV1 * ptdc, char * text, int x, int y)
{
	if(!TextOut(ptdc->hdc, x, y, text, (int)strlen(text)))
		ON_ERROR_GOTO("draw text failed");
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API int COLOR_SHIFT_TABLE[MAX_COLOR_BPP + 1];
T3DLIB_API int PITCH_SHIFT_TABLE[MAX_RECOMMENDED_PITCH + 1];

T3DLIB_API unsigned int (* Create_RGBI)(int r, int g, int b) = NULL;
T3DLIB_API unsigned int (* Create_RGBF)(float fr, float fg, float fb) = NULL;
T3DLIB_API bool (* Create_Image)(IMAGEV1 * pimage, const int width, const int height) = NULL;
T3DLIB_API bool (* Create_Texture)(TEXTUREV1 * ptexture, const int width, const int height) = NULL;
T3DLIB_API bool (* Load_Surface_From_Bitmap)(SURFACEV1 * psurface, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height) = NULL;
T3DLIB_API bool (* Load_Image_From_Bitmap)(IMAGEV1 * pimage, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height) = NULL;
T3DLIB_API bool (* Load_Texture_From_Bitmap)(TEXTUREV1 * ptexture, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height) = NULL;

_CTOR_IMPLEMENT(BITMAPV1_TYP);
_DTOR_IMPLEMENT_W1(BITMAPV1_TYP, Destroy_Bitmap, pbuffer);

_CTOR_IMPLEMENT(IMAGEV1_TYP);
_DTOR_IMPLEMENT_W1(IMAGEV1_TYP, Destroy_Image, pbuffer);

_CTOR_IMPLEMENT(TEXTUREV1_TYP);
_DTOR_IMPLEMENT_W1(TEXTUREV1_TYP, Destroy_Texture, pbuffer);

T3DLIB_API bool Init_T3dlib1(int bpp)
{
	switch(bpp)
	{
	case 16:
		Create_RGBI					= Create_RGBI16;
		Create_RGBF					= Create_RGBF16;
		Create_Image				= Create_Image16;
		Create_Texture				= Create_Texture16;
		Load_Surface_From_Bitmap	= Load_Surface_From_Bitmap16;
		Load_Image_From_Bitmap		= Load_Image_From_Bitmap16;
		Load_Texture_From_Bitmap	= Load_Texture_From_Bitmap16;
		break;

	case 32:
		Create_RGBI					= Create_RGBI32;
		Create_RGBF					= Create_RGBF32;
		Create_Image				= Create_Image32;
		Create_Texture				= Create_Texture32;
		Load_Surface_From_Bitmap	= Load_Surface_From_Bitmap32;
		Load_Image_From_Bitmap		= Load_Image_From_Bitmap32;
		Load_Texture_From_Bitmap	= Load_Texture_From_Bitmap32;
		break;

	default:
		ON_ERROR_GOTO((sprintf(gbuffer, "unsupported color bip: %d", bpp), gbuffer));
	}

	memset(COLOR_SHIFT_TABLE, 0, sizeof(COLOR_SHIFT_TABLE));
	memset(PITCH_SHIFT_TABLE, 0, sizeof(PITCH_SHIFT_TABLE));
	unsigned int i, itmp;
	int count;
	for(i = MIN_COLOR_BPP; i <= MAX_COLOR_BPP; i <<= 1)
	{
		itmp = i >> 3;
		count = 0;
		while(itmp > 1)
		{
			itmp >>= 1;
			count++;
		}
		COLOR_SHIFT_TABLE[i] = count;
	}

	for(i = MIN_RECOMMENDED_PITCH; i <= MAX_RECOMMENDED_PITCH; i <<= 1)
	{
		itmp = i;
		count = 0;
		while(itmp > 1)
		{
			itmp >>= 1;
			count++;
		}
		PITCH_SHIFT_TABLE[i] = count;
	}
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Compute_Color_Shift(int * pcshift, const int bpp)
{
	if(bpp >= MIN_COLOR_BPP && bpp <= MAX_COLOR_BPP)
	{
		return (*pcshift = COLOR_SHIFT_TABLE[bpp]) != 0;
	}
	return false;
}

T3DLIB_API bool Compute_Pitch_Shift(int * ppshift, const long pitch)
{
	if(pitch >= MIN_RECOMMENDED_PITCH && pitch <= MAX_RECOMMENDED_PITCH)
	{
		return (*ppshift = PITCH_SHIFT_TABLE[pitch]) != 0;
	}
	return false;
}

T3DLIB_API bool Get_Recommended_Pitch(long * precommend, const long pitch)
{
	if(pitch > MAX_RECOMMENDED_PITCH)
		return false;

	int i = MIN_RECOMMENDED_PITCH;
	while(i < pitch)
		i <<= 1;
	*precommend = i;
	return true;
}

T3DLIB_API bool Get_Recommended_Width(int * precommend, const int width)
{
	if(width > MAX_RECOMMENDED_WIDTH)
		return false;

	int i = MIN_RECOMMENDED_WIDTH;
	while(i < width)
		i <<= 1;
	*precommend = i;
	return true;
}

T3DLIB_API unsigned int Create_RGBI16(int r, int g, int b)
{
	return _RGB16BIT(r >> 3, g >> 2, b >> 3);
}

T3DLIB_API unsigned int Create_RGBI32(int r, int g, int b)
{
	return _RGB32BIT(r, g, b);
}

T3DLIB_API unsigned int Create_RGBF16(float fr, float fg, float fb)
{
	return _RGB16BIT(
		(int)(fr * (float)0x1F + 0.5f),
		(int)(fg * (float)0x3F + 0.5f),
		(int)(fb * (float)0x1F + 0.5f));
}

T3DLIB_API unsigned int Create_RGBF32(float fr, float fg, float fb)
{
	return _RGB32BIT(
		(int)(fr * (float)0xFF + 0.5f),
		(int)(fg * (float)0xFF + 0.5f),
		(int)(fb * (float)0xFF + 0.5f));
}

T3DLIB_API bool Create_Bitmap_From_File(BITMAPV1 * pbitmap, const char * fname)
{
	assert(pbitmap->pbuffer == NULL);

	FILE * pfile = NULL;
	unsigned char * pbuffer = NULL;
	int i;
	if(NULL == (pfile = fopen(fname, "rb")))
		ON_ERROR_GOTO("open file failed");

	if(1 != fread(&pbitmap->bitmapfileheader, sizeof(pbitmap->bitmapfileheader), 1, pfile))
		ON_ERROR_GOTO("read file header failed");

	if(pbitmap->bitmapfileheader.bfType != BITMAP_ID)
		ON_ERROR_GOTO("not bitmap pfile");

	if(1 != fread(&pbitmap->bitmapinfoheader, sizeof(pbitmap->bitmapinfoheader), 1, pfile))
		ON_ERROR_GOTO("read info header failed");

	if(pbitmap->bitmapinfoheader.biBitCount == 8)
	{
		if(1 != fread(&pbitmap->palette, sizeof(pbitmap->palette), 1, pfile))
			ON_ERROR_GOTO("read palette failed");

		UCHAR ctmp;
		for(i = 0; i < MAX_COLOR_PALETTE; i++)
		{
			SWAP(pbitmap->palette[i].peRed, pbitmap->palette[i].peBlue, ctmp);
			pbitmap->palette[i].peFlags = PC_NOCOLLAPSE;
		}
	}

	if(0 != fseek(pfile, -(long)pbitmap->bitmapinfoheader.biSizeImage, SEEK_END))
		ON_ERROR_GOTO("seek file failed");

	if(NULL == (pbuffer =
			(unsigned char *)malloc(pbitmap->bitmapinfoheader.biSizeImage)))
		ON_ERROR_GOTO("malloc buffer failed");

	if(1 != fread(pbuffer, pbitmap->bitmapinfoheader.biSizeImage, 1, pfile))
		ON_ERROR_GOTO("read buffer failed");

	if(NULL == (pbitmap->pbuffer =
			(unsigned char *)malloc(pbitmap->bitmapinfoheader.biSizeImage)))
		ON_ERROR_GOTO("malloc buffer failed");

	long pitch = pbitmap->bitmapinfoheader.biWidth * (pbitmap->bitmapinfoheader.biBitCount >> 3);
	for(i = 0; i < pbitmap->bitmapinfoheader.biHeight; i++)
	{
		memcpy(	pbitmap->pbuffer + i * pitch,
				pbuffer + (pbitmap->bitmapinfoheader.biHeight - i - 1) * pitch,
				pitch);
	}
	free(pbuffer);
	fclose(pfile);
	return true;

ON_ERROR:
	SAFE_FREE(pbitmap->pbuffer);
	SAFE_FREE(pbuffer);
	SAFE_FCLOSE(pfile);
	return false;
}

T3DLIB_API bool Lock_DDSurface(const DDSURFACEV1 * pddsurface, SURFACEV1 * psurface)
{
	memset(&gddsd, 0, sizeof(gddsd));
	gddsd.dwSize = sizeof(gddsd);
	if(FAILED(gresult = pddsurface->lpddsurface->Lock(NULL, &gddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR , 0)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));

	if(!Compute_Pitch_Shift(&psurface->pitch_shift, gddsd.lPitch))
		ON_ERROR_GOTO("compute pitch shift failed");

	if(!Compute_Color_Shift(&psurface->color_shift, gddsd.ddpfPixelFormat.dwRGBBitCount))
		ON_ERROR_GOTO("compute color shift failed");

	psurface->pbuffer	= (unsigned char *)gddsd.lpSurface;
	psurface->pitch		= gddsd.lPitch;
	psurface->width		= gddsd.dwWidth;
	psurface->height	= gddsd.dwHeight;
	return true;

ON_ERROR:
	pddsurface->lpddsurface->Unlock(NULL);
	return false;
}

T3DLIB_API bool Unlock_DDSurface(const DDSURFACEV1 * pddsurface)
{
	if(FAILED(gresult = pddsurface->lpddsurface->Unlock(NULL)))
		ON_ERROR_GOTO(GET_DDRAW_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Create_Image16(IMAGEV1 * pimage, const int width, const int height)
{
	assert(pimage->pbuffer == NULL);

	long			rpitch;
	int				rpitch_shift;
	unsigned char *	pbuffer = NULL;

	if(!Get_Recommended_Pitch(&rpitch, width * (sizeof(*pimage->pbuffer) << _16BIT_BYTES_SHIFT)))
		ON_ERROR_GOTO("get recommended pitch failed");

	if(!Compute_Pitch_Shift(&rpitch_shift, rpitch))
	{
		assert(false);
		ON_ERROR_GOTO("compute pitch shift failed");
	}

	if(NULL == (pbuffer = (unsigned char *)malloc(rpitch * height)))
		ON_ERROR_GOTO("malloc image failed");

	pimage->pbuffer		= pbuffer;
	pimage->pitch		= rpitch;
	pimage->width		= width;
	pimage->height		= height;
	pimage->pitch_shift	= rpitch_shift;
	pimage->color_shift	= _16BIT_BYTES_SHIFT;
	return true;

ON_ERROR:
	SAFE_FREE(pbuffer);
	return false;
}

T3DLIB_API bool Create_Image32(IMAGEV1 * pimage, const int width, const int height)
{
	assert(pimage->pbuffer == NULL);

	long			rpitch;
	int				rpitch_shift;
	unsigned char *	pbuffer = NULL;

	if(!Get_Recommended_Pitch(&rpitch, width * (sizeof(*pimage->pbuffer) << _32BIT_BYTES_SHIFT)))
		ON_ERROR_GOTO("get recommended pitch failed");

	if(!Compute_Pitch_Shift(&rpitch_shift, rpitch))
	{
		assert(false);
		ON_ERROR_GOTO("compute pitch shift failed");
	}

	if(NULL == (pbuffer = (unsigned char *)malloc(rpitch * height)))
		ON_ERROR_GOTO("malloc image failed");

	pimage->pbuffer		= pbuffer;
	pimage->pitch		= rpitch;
	pimage->width		= width;
	pimage->height		= height;
	pimage->pitch_shift	= rpitch_shift;
	pimage->color_shift	= _32BIT_BYTES_SHIFT;
	return true;

ON_ERROR:
	SAFE_FREE(pbuffer);
	return false;
}

T3DLIB_API bool Create_Texture16(TEXTUREV1 * ptexture, const int width, const int height)
{
	assert(sizeof(XRGB32) == 4);
	assert(ptexture->pbuffer == NULL);

	long			rpitch;
	int				rpitch_shift;
	int				rcolor_shift;
	unsigned char *	pbuffer = NULL;

	if(!Get_Recommended_Pitch(&rpitch, width * sizeof(XRGB32)))
		ON_ERROR_GOTO("get recommended pitch failed");

	if(!Compute_Pitch_Shift(&rpitch_shift, rpitch))
	{
		assert(false);
		ON_ERROR_GOTO("compute pitch shift failed");
	}

	if(!Compute_Color_Shift(&rcolor_shift, sizeof(XRGB32) * 8))
	{
		assert(false);
		ON_ERROR_GOTO("compute color shift failed");
	}

	//if(NULL == (ptexture->ptexture = (XRGB32 *)malloc(height * rpitch)))
	if(NULL == (pbuffer = (unsigned char *)malloc(height * rpitch)))
		ON_ERROR_GOTO("malloc image failed");

	ptexture->pbuffer		= pbuffer;
	ptexture->pitch			= rpitch;
	ptexture->width			= width;
	ptexture->height		= height;
	ptexture->pitch_shift	= rpitch_shift;
	ptexture->color_shift	= rcolor_shift;
	return true;

ON_ERROR:
	SAFE_FREE(pbuffer);
	return false;
}

T3DLIB_API bool Create_Texture32(TEXTUREV1 * ptexture, const int width, const int height)
{
	assert(sizeof(XRGB32) == 4);
	assert(ptexture->pbuffer == NULL);

	long			rpitch;
	int				rpitch_shift;
	int				rcolor_shift;
	unsigned char *	pbuffer = NULL;

	if(!Get_Recommended_Pitch(&rpitch, width * sizeof(XRGB32)))
		ON_ERROR_GOTO("get recommended pitch failed");

	if(!Compute_Pitch_Shift(&rpitch_shift, rpitch))
	{
		assert(false);
		ON_ERROR_GOTO("compute pitch shift failed");
	}

	if(!Compute_Color_Shift(&rcolor_shift, sizeof(XRGB32) * 8))
	{
		assert(false);
		ON_ERROR_GOTO("compute color shift failed");
	}

	//if(NULL == (ptexture->ptexture = (XRGB32 *)malloc(height * rpitch)))
	if(NULL == (pbuffer = (unsigned char *)malloc(height * rpitch)))
		ON_ERROR_GOTO("malloc image failed");

	ptexture->pbuffer		= pbuffer;
	ptexture->pitch			= rpitch;
	ptexture->width			= width;
	ptexture->height		= height;
	ptexture->pitch_shift	= rpitch_shift;
	ptexture->color_shift	= rcolor_shift;
	return true;

ON_ERROR:
	SAFE_FREE(pbuffer);
	return false;
}

T3DLIB_API bool Load_Surface_From_Bitmap16(SURFACEV1 * psurface, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height)
{
	assert(psurface->color_shift == _16BIT_BYTES_SHIFT);
	assert(psurface->pbuffer != NULL);

	assert(	x >= 0 &&
			y >= 0 &&
			x + width	<= pbitmap->bitmapinfoheader.biWidth &&
			y + height	<= pbitmap->bitmapinfoheader.biHeight);

	int si, bi, sj, bj;
	unsigned char * dest, * src;
	unsigned short pixel;
	for(si = 0, bi = y;
		si < psurface->height && bi < y + height; si++, bi++)
	{
		for(sj = 0, bj = x;
			sj < psurface->width && bj < x + width; sj++, bj++)
		{
			dest = psurface->pbuffer + (si << psurface->pitch_shift) + (sj << _16BIT_BYTES_SHIFT);
			src  = pbitmap->pbuffer +
					(bi * pbitmap->bitmapinfoheader.biWidth + bj) * (pbitmap->bitmapinfoheader.biBitCount >> 3);

			switch(pbitmap->bitmapinfoheader.biBitCount)
			{
			case 8:
				pixel = (unsigned short)_RGB16BIT(
							pbitmap->palette[*src].peRed	>> 3,
							pbitmap->palette[*src].peGreen	>> 2,
							pbitmap->palette[*src].peBlue	>> 3);
				break;

			case 16:
				pixel = (unsigned short)_RGB16BIT(
							_16BIT_GETR(*((unsigned short *)src)),
							_16BIT_GETG(*((unsigned short *)src)),
							_16BIT_GETB(*((unsigned short *)src)));
				break;

			case 24:
				pixel = (unsigned short)_RGB16BIT(
							_32BIT_GETR(*((unsigned int *)src))	>> 3,
							_32BIT_GETG(*((unsigned int *)src))	>> 2,
							_32BIT_GETB(*((unsigned int *)src))	>> 3);
				break;

			default:
				ON_ERROR_GOTO("unsurported color bit");
			}

			*((unsigned short *)dest) = pixel;
		}
	}
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Load_Surface_From_Bitmap32(SURFACEV1 * psurface, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height)
{
	assert(psurface->color_shift == _32BIT_BYTES_SHIFT);
	assert(psurface->pbuffer != NULL);

	assert(	x >= 0 &&
			y >= 0 &&
			x + width	<= pbitmap->bitmapinfoheader.biWidth &&
			y + height	<= pbitmap->bitmapinfoheader.biHeight);

	int si, bi, sj, bj;
	unsigned char * dest, * src;
	unsigned int pixel;
	for(si = 0, bi = y;
		si < psurface->height && bi < y + height; si++, bi++)
	{
		for(sj = 0, bj = x;
			sj < psurface->width && bj < x + width; sj++, bj++)
		{
			dest = psurface->pbuffer + (si << psurface->pitch_shift) + (sj << _32BIT_BYTES_SHIFT);
			src  = pbitmap->pbuffer +
					(bi * pbitmap->bitmapinfoheader.biWidth + bj) * (pbitmap->bitmapinfoheader.biBitCount >> 3);

			switch(pbitmap->bitmapinfoheader.biBitCount)
			{
			case 8:
				pixel = (unsigned int)_RGB32BIT(
							pbitmap->palette[*src].peRed,
							pbitmap->palette[*src].peGreen,
							pbitmap->palette[*src].peBlue);
				break;

			case 16:
				pixel = (unsigned int)_RGB32BIT(
							_16BIT_GETR(*((unsigned short *)src)) << 3,
							_16BIT_GETG(*((unsigned short *)src)) << 2,
							_16BIT_GETB(*((unsigned short *)src)) << 3);
				break;

			case 24:
				pixel = (unsigned int)_RGB32BIT(
							_32BIT_GETR(*((unsigned int *)src)),
							_32BIT_GETG(*((unsigned int *)src)),
							_32BIT_GETB(*((unsigned int *)src)));
				break;

			default:
				ON_ERROR_GOTO("unsurported color bit");
			}

			*((unsigned int *)dest) = pixel;
		}
	}
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Load_Image_From_Bitmap16(IMAGEV1 * pimage, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height)
{
	assert(pimage->color_shift == _16BIT_BYTES_SHIFT);
	assert(pimage->pbuffer != NULL);

	assert(	x >= 0 &&
			y >= 0 &&
			x + width	<= pbitmap->bitmapinfoheader.biWidth &&
			y + height	<= pbitmap->bitmapinfoheader.biHeight);

	int si, bi, sj, bj;
	unsigned char * dest, * src;
	unsigned short pixel;
	for(si = 0, bi = y;
		si < pimage->height && bi < y + height; si++, bi++)
	{
		for(sj = 0, bj = x;
			sj < pimage->width && bj < x + width; sj++, bj++)
		{
			dest = pimage->pbuffer + (si << pimage->pitch_shift) + (sj << _16BIT_BYTES_SHIFT);
			src  = pbitmap->pbuffer +
					(bi * pbitmap->bitmapinfoheader.biWidth + bj) * (pbitmap->bitmapinfoheader.biBitCount >> 3);

			switch(pbitmap->bitmapinfoheader.biBitCount)
			{
			case 8:
				pixel = (unsigned short)_RGB16BIT(
							pbitmap->palette[*src].peRed	>> 3,
							pbitmap->palette[*src].peGreen	>> 2,
							pbitmap->palette[*src].peBlue	>> 3);
				break;

			case 16:
				pixel = (unsigned short)_RGB16BIT(
							_16BIT_GETR(*((unsigned short *)src)),
							_16BIT_GETG(*((unsigned short *)src)),
							_16BIT_GETB(*((unsigned short *)src)));
				break;

			case 24:
				pixel = (unsigned short)_RGB16BIT(
							_32BIT_GETR(*((unsigned int *)src))	>> 3,
							_32BIT_GETG(*((unsigned int *)src))	>> 2,
							_32BIT_GETB(*((unsigned int *)src))	>> 3);
				break;

			default:
				ON_ERROR_GOTO("unsurported color bit");
			}

			*((unsigned short *)dest) = pixel;
		}
	}
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Load_Image_From_Bitmap32(IMAGEV1 * pimage, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height)
{
	assert(pimage->color_shift == _32BIT_BYTES_SHIFT);
	assert(pimage->pbuffer != NULL);

	assert(	x >= 0 &&
			y >= 0 &&
			x + width	<= pbitmap->bitmapinfoheader.biWidth &&
			y + height	<= pbitmap->bitmapinfoheader.biHeight);

	int si, bi, sj, bj;
	unsigned char * dest, * src;
	unsigned int pixel;
	for(si = 0, bi = y;
		si < pimage->height && bi < y + height; si++, bi++)
	{
		for(sj = 0, bj = x;
			sj < pimage->width && bj < x + width; sj++, bj++)
		{
			dest = pimage->pbuffer + (si << pimage->pitch_shift) + (sj << _32BIT_BYTES_SHIFT);
			src  = pbitmap->pbuffer +
					(bi * pbitmap->bitmapinfoheader.biWidth + bj) * (pbitmap->bitmapinfoheader.biBitCount >> 3);

			switch(pbitmap->bitmapinfoheader.biBitCount)
			{
			case 8:
				pixel = (unsigned int)_RGB32BIT(
							pbitmap->palette[*src].peRed,
							pbitmap->palette[*src].peGreen,
							pbitmap->palette[*src].peBlue);
				break;

			case 16:
				pixel = (unsigned int)_RGB32BIT(
							_16BIT_GETR(*((unsigned short *)src)) << 3,
							_16BIT_GETG(*((unsigned short *)src)) << 2,
							_16BIT_GETB(*((unsigned short *)src)) << 3);
				break;

			case 24:
				pixel = (unsigned int)_RGB32BIT(
							_32BIT_GETR(*((unsigned int *)src)),
							_32BIT_GETG(*((unsigned int *)src)),
							_32BIT_GETB(*((unsigned int *)src)));
				break;

			default:
				ON_ERROR_GOTO("unsurported color bit");
			}

			*((unsigned int *)dest) = pixel;
		}
	}
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Load_Texture_From_Bitmap16(TEXTUREV1 * ptexture, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height)
{
	assert(ptexture->color_shift == _16BIT_BYTES_SHIFT);
	assert(ptexture->pbuffer != NULL);
	//memset(ptexture->ptexture, 0, ptexture->height << ptexture->pitch_shift);

	int ti, bi, tj, bj;
	XRGB32 * dest;
	unsigned char * src;
	for(ti = 0, bi = y;
		ti < ptexture->height, bi < y + height; ti++, bi++)
	{
		for(tj = 0, bj = x;
			tj < ptexture->width, bj < x + width; tj++, bj++)
		{
			dest = (XRGB32 *)(ptexture->pbuffer + (ti << ptexture->pitch_shift) + (tj << _16BIT_BYTES_SHIFT));
			src  = pbitmap->pbuffer +
					(bi * pbitmap->bitmapinfoheader.biWidth + bj) * (pbitmap->bitmapinfoheader.biBitCount >> 3);
			switch(pbitmap->bitmapinfoheader.biBitCount)
			{
			case 8:
				dest->r = pbitmap->palette[*src].peRed		>> 3;
				dest->g = pbitmap->palette[*src].peGreen	>> 2;
				dest->b = pbitmap->palette[*src].peBlue		>> 3;
				break;

			case 16:
				dest->r = (unsigned char)_16BIT_GETR(*((unsigned short *)src));
				dest->g = (unsigned char)_16BIT_GETG(*((unsigned short *)src));
				dest->b = (unsigned char)_16BIT_GETB(*((unsigned short *)src));
				break;

			case 24:
				dest->r = (unsigned char)_32BIT_GETR(*((unsigned int *)src)) >> 3;
				dest->g = (unsigned char)_32BIT_GETG(*((unsigned int *)src)) >> 2;
				dest->b = (unsigned char)_32BIT_GETB(*((unsigned int *)src)) >> 3;
				break;

			default:
				ON_ERROR_GOTO("unsurported color bit");
			}
		}
	}

ON_ERROR:
	return false;
}

T3DLIB_API bool Load_Texture_From_Bitmap32(TEXTUREV1 * ptexture, const BITMAPV1 * pbitmap, const int x, const int y, const int width, const int height)
{
	assert(ptexture->color_shift == _32BIT_BYTES_SHIFT);
	assert(ptexture->pbuffer != NULL);
	//memset(ptexture->ptexture, 0, ptexture->height << ptexture->pitch_shift);

	int ti, bi, tj, bj;
	XRGB32 * dest;
	unsigned char * src;
	for(ti = 0, bi = y;
		ti < ptexture->height, bi < y + height; ti++, bi++)
	{
		for(tj = 0, bj = x;
			tj < ptexture->width, bj < x + width; tj++, bj++)
		{
			dest = (XRGB32 *)(ptexture->pbuffer + (ti << ptexture->pitch_shift) + (tj << _32BIT_BYTES_SHIFT));
			src  = pbitmap->pbuffer +
					(bi * pbitmap->bitmapinfoheader.biWidth + bj) * (pbitmap->bitmapinfoheader.biBitCount >> 3);
			switch(pbitmap->bitmapinfoheader.biBitCount)
			{
			case 8:
				dest->r = pbitmap->palette[*src].peRed;
				dest->g = pbitmap->palette[*src].peGreen;
				dest->b = pbitmap->palette[*src].peBlue;
				break;

			case 16:
				dest->r = (unsigned char)_16BIT_GETR(*((unsigned short *)src)) << 3;
				dest->g = (unsigned char)_16BIT_GETG(*((unsigned short *)src)) << 2;
				dest->b = (unsigned char)_16BIT_GETB(*((unsigned short *)src)) << 3;
				break;

			case 24:
				dest->r = (unsigned char)_32BIT_GETR(*((unsigned int *)src));
				dest->g = (unsigned char)_32BIT_GETG(*((unsigned int *)src));
				dest->b = (unsigned char)_32BIT_GETB(*((unsigned int *)src));
				break;

			default:
				ON_ERROR_GOTO("unsurported color bit");
			}
		}
	}

ON_ERROR:
	return false;
}

T3DLIB_API void Destroy_Bitmap(BITMAPV1 * pbitmap)
{
	SAFE_FREE(pbitmap->pbuffer);
	memset(pbitmap, 0, sizeof(*pbitmap));
}

T3DLIB_API void Destroy_Image(IMAGEV1 * pimage)
{
	SAFE_FREE(pimage->pbuffer);
	memset(pimage, 0, sizeof(*pimage));
}

T3DLIB_API void Destroy_Texture(TEXTUREV1 * ptexture)
{
	SAFE_FREE(ptexture->pbuffer);
	memset(ptexture, 0, sizeof(*ptexture));
}

_CTOR_IMPLEMENT(ZBUFFERV1_TYP);
_DTOR_IMPLEMENT_W1(ZBUFFERV1_TYP, Destroy_ZBuffer, pbuffer);

T3DLIB_API bool Create_ZBuffer(ZBUFFERV1 * pzbuffer, const int width, const int height)
{
	assert(pzbuffer->pbuffer == NULL);

	unsigned char * pbuffer = NULL;
	long	rpitch;
	int		rpitch_shift;

	if(!Get_Recommended_Pitch(&rpitch, width << _ZBUFF_BYTES_SHIFT))
	{
		assert(false);
		ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot get recommended pitch with width %d", width));
	}

	if(!Compute_Pitch_Shift(&rpitch_shift, rpitch))
	{
		assert(false);
		ON_ERROR_GOTO(SFORMAT1(gbuffer, "cannot compute pitch shift with pitch %d", rpitch));
	}

	if(NULL == (pbuffer = (unsigned char *)malloc(height * rpitch)))
		ON_ERROR_GOTO(SFORMAT0(gbuffer, "malloc zbuffer failed"));

	pzbuffer->pbuffer		= pbuffer;
	pzbuffer->pitch			= rpitch;
	pzbuffer->width			= width;
	pzbuffer->height		= height;
	pzbuffer->pitch_shift	= rpitch_shift;
	pzbuffer->color_shift	= _ZBUFF_BYTES_SHIFT;
	return true;

ON_ERROR:
	SAFE_FREE(pbuffer);
	return false;
}

T3DLIB_API void Clear_ZBuffer(ZBUFFERV1 * pzbuffer)
{
	unsigned char * pz = pzbuffer->pbuffer;
	int count = pzbuffer->height;
	while(count--)
	{
		memset(pz, 0, pzbuffer->width << _ZBUFF_BYTES_SHIFT);
		pz += pzbuffer->pitch;
	}
}

T3DLIB_API void Destroy_ZBuffer(ZBUFFERV1 * pzbuffer)
{
	SAFE_FREE(pzbuffer->pbuffer);
	memset(pzbuffer, 0, sizeof(*pzbuffer));
}
