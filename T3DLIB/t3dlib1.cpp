
#include "stdafx.h"
#include "t3dlib1.h"
#include <cassert>
#include <boost/shared_array.hpp>

#pragma comment(lib, "DDraw.lib")
#pragma comment(lib, "dxguid.lib")

namespace t3d
{
#define CASE_RETURN_STRING(branch) case branch: return std::basic_string<charT>(_T( #branch ));

	std::basic_string<charT> DDException::GetResultStr(HRESULT hres)
	{
		switch(hres)
		{
		CASE_RETURN_STRING(DD_OK)
		CASE_RETURN_STRING(DDERR_ALREADYINITIALIZED)
		CASE_RETURN_STRING(DDERR_BLTFASTCANTCLIP)
		CASE_RETURN_STRING(DDERR_CANNOTATTACHSURFACE)
		CASE_RETURN_STRING(DDERR_CANNOTDETACHSURFACE)
		CASE_RETURN_STRING(DDERR_CANTCREATEDC)
		CASE_RETURN_STRING(DDERR_CANTDUPLICATE)
		CASE_RETURN_STRING(DDERR_CANTLOCKSURFACE)
		CASE_RETURN_STRING(DDERR_CANTPAGELOCK)
		CASE_RETURN_STRING(DDERR_CANTPAGEUNLOCK)
		CASE_RETURN_STRING(DDERR_CLIPPERISUSINGHWND)
		CASE_RETURN_STRING(DDERR_COLORKEYNOTSET)
		CASE_RETURN_STRING(DDERR_CURRENTLYNOTAVAIL)
		CASE_RETURN_STRING(DDERR_DDSCAPSCOMPLEXREQUIRED)
		CASE_RETURN_STRING(DDERR_DCALREADYCREATED)
		CASE_RETURN_STRING(DDERR_DEVICEDOESNTOWNSURFACE)
		CASE_RETURN_STRING(DDERR_DIRECTDRAWALREADYCREATED)
		CASE_RETURN_STRING(DDERR_EXCEPTION)
		CASE_RETURN_STRING(DDERR_EXCLUSIVEMODEALREADYSET)
		CASE_RETURN_STRING(DDERR_EXPIRED)
		CASE_RETURN_STRING(DDERR_GENERIC)
		CASE_RETURN_STRING(DDERR_HEIGHTALIGN)
		CASE_RETURN_STRING(DDERR_HWNDALREADYSET)
		CASE_RETURN_STRING(DDERR_HWNDSUBCLASSED)
		CASE_RETURN_STRING(DDERR_IMPLICITLYCREATED)
		CASE_RETURN_STRING(DDERR_INCOMPATIBLEPRIMARY)
		CASE_RETURN_STRING(DDERR_INVALIDCAPS)
		CASE_RETURN_STRING(DDERR_INVALIDCLIPLIST)
		CASE_RETURN_STRING(DDERR_INVALIDDIRECTDRAWGUID)
		CASE_RETURN_STRING(DDERR_INVALIDMODE)
		CASE_RETURN_STRING(DDERR_INVALIDOBJECT)
		CASE_RETURN_STRING(DDERR_INVALIDPARAMS)
		CASE_RETURN_STRING(DDERR_INVALIDPIXELFORMAT)
		CASE_RETURN_STRING(DDERR_INVALIDPOSITION)
		CASE_RETURN_STRING(DDERR_INVALIDRECT)
		CASE_RETURN_STRING(DDERR_INVALIDSTREAM)
		CASE_RETURN_STRING(DDERR_INVALIDSURFACETYPE)
		CASE_RETURN_STRING(DDERR_LOCKEDSURFACES)
		CASE_RETURN_STRING(DDERR_MOREDATA)
		CASE_RETURN_STRING(DDERR_NEWMODE)
		CASE_RETURN_STRING(DDERR_NO3D)
		CASE_RETURN_STRING(DDERR_NOALPHAHW)
		CASE_RETURN_STRING(DDERR_NOBLTHW)
		CASE_RETURN_STRING(DDERR_NOCLIPLIST)
		CASE_RETURN_STRING(DDERR_NOCLIPPERATTACHED)
		CASE_RETURN_STRING(DDERR_NOCOLORCONVHW)
		CASE_RETURN_STRING(DDERR_NOCOLORKEY)
		CASE_RETURN_STRING(DDERR_NOCOLORKEYHW)
		CASE_RETURN_STRING(DDERR_NOCOOPERATIVELEVELSET)
		CASE_RETURN_STRING(DDERR_NODC)
		CASE_RETURN_STRING(DDERR_NODDROPSHW)
		CASE_RETURN_STRING(DDERR_NODIRECTDRAWHW)
		CASE_RETURN_STRING(DDERR_NODIRECTDRAWSUPPORT)
		CASE_RETURN_STRING(DDERR_NODRIVERSUPPORT)
		CASE_RETURN_STRING(DDERR_NOEMULATION)
		CASE_RETURN_STRING(DDERR_NOEXCLUSIVEMODE)
		CASE_RETURN_STRING(DDERR_NOFLIPHW)
		CASE_RETURN_STRING(DDERR_NOFOCUSWINDOW)
		CASE_RETURN_STRING(DDERR_NOGDI)
		CASE_RETURN_STRING(DDERR_NOHWND)
		CASE_RETURN_STRING(DDERR_NOMIPMAPHW)
		CASE_RETURN_STRING(DDERR_NOMIRRORHW)
		CASE_RETURN_STRING(DDERR_NOMONITORINFORMATION)
		CASE_RETURN_STRING(DDERR_NONONLOCALVIDMEM)
		CASE_RETURN_STRING(DDERR_NOOPTIMIZEHW)
		CASE_RETURN_STRING(DDERR_NOOVERLAYDEST)
		CASE_RETURN_STRING(DDERR_NOOVERLAYHW)
		CASE_RETURN_STRING(DDERR_NOPALETTEATTACHED)
		CASE_RETURN_STRING(DDERR_NOPALETTEHW)
		CASE_RETURN_STRING(DDERR_NORASTEROPHW)
		CASE_RETURN_STRING(DDERR_NOROTATIONHW)
		CASE_RETURN_STRING(DDERR_NOSTEREOHARDWARE)
		CASE_RETURN_STRING(DDERR_NOSTRETCHHW)
		CASE_RETURN_STRING(DDERR_NOSURFACELEFT)
		CASE_RETURN_STRING(DDERR_NOT4BITCOLOR)
		CASE_RETURN_STRING(DDERR_NOT4BITCOLORINDEX)
		CASE_RETURN_STRING(DDERR_NOT8BITCOLOR)
		CASE_RETURN_STRING(DDERR_NOTAOVERLAYSURFACE)
		CASE_RETURN_STRING(DDERR_NOTEXTUREHW)
		CASE_RETURN_STRING(DDERR_NOTFLIPPABLE)
		CASE_RETURN_STRING(DDERR_NOTFOUND)
		CASE_RETURN_STRING(DDERR_NOTINITIALIZED)
		CASE_RETURN_STRING(DDERR_NOTLOADED)
		CASE_RETURN_STRING(DDERR_NOTLOCKED)
		CASE_RETURN_STRING(DDERR_NOTPAGELOCKED)
		CASE_RETURN_STRING(DDERR_NOTPALETTIZED)
		CASE_RETURN_STRING(DDERR_NOVSYNCHW)
		CASE_RETURN_STRING(DDERR_NOZBUFFERHW)
		CASE_RETURN_STRING(DDERR_NOZOVERLAYHW)
		CASE_RETURN_STRING(DDERR_OUTOFCAPS)
		CASE_RETURN_STRING(DDERR_OUTOFMEMORY)
		CASE_RETURN_STRING(DDERR_OUTOFVIDEOMEMORY)
		CASE_RETURN_STRING(DDERR_OVERLAPPINGRECTS)
		CASE_RETURN_STRING(DDERR_OVERLAYCANTCLIP)
		CASE_RETURN_STRING(DDERR_OVERLAYCOLORKEYONLYONEACTIVE)
		CASE_RETURN_STRING(DDERR_OVERLAYNOTVISIBLE)
		CASE_RETURN_STRING(DDERR_PALETTEBUSY)
		CASE_RETURN_STRING(DDERR_PRIMARYSURFACEALREADYEXISTS)
		CASE_RETURN_STRING(DDERR_REGIONTOOSMALL)
		CASE_RETURN_STRING(DDERR_SURFACEALREADYATTACHED)
		CASE_RETURN_STRING(DDERR_SURFACEALREADYDEPENDENT)
		CASE_RETURN_STRING(DDERR_SURFACEBUSY)
		CASE_RETURN_STRING(DDERR_SURFACEISOBSCURED)
		CASE_RETURN_STRING(DDERR_SURFACELOST)
		CASE_RETURN_STRING(DDERR_SURFACENOTATTACHED)
		CASE_RETURN_STRING(DDERR_TESTFINISHED)
		CASE_RETURN_STRING(DDERR_TOOBIGHEIGHT)
		CASE_RETURN_STRING(DDERR_TOOBIGSIZE)
		CASE_RETURN_STRING(DDERR_TOOBIGWIDTH)
		CASE_RETURN_STRING(DDERR_UNSUPPORTED)
		CASE_RETURN_STRING(DDERR_UNSUPPORTEDFORMAT)
		CASE_RETURN_STRING(DDERR_UNSUPPORTEDMASK)
		CASE_RETURN_STRING(DDERR_UNSUPPORTEDMODE)
		CASE_RETURN_STRING(DDERR_VERTICALBLANKINPROGRESS)
		CASE_RETURN_STRING(DDERR_VIDEONOTACTIVE)
		CASE_RETURN_STRING(DDERR_WASSTILLDRAWING)
		CASE_RETURN_STRING(DDERR_WRONGMODE)
		CASE_RETURN_STRING(DDERR_XALIGN)
		}
		return std::basic_string<charT>(_T("unknown ddraw error result"));
	}

	DDException::DDException(const std::basic_string<charT> & file, int line, HRESULT hres)
		: Exception(file, line)
		, m_hres(hres)
	{
	}

	std::basic_string<charT> DDException::what(void) const throw()
	{
		return GetResultStr(m_hres);
	}

#define T3D_DDEXCEPT(hres) { throw DDException( _T(__FILE__), __LINE__, (hres) ); }

#define FAILED_DDEXCEPT(expr) { HRESULT hres; if( FAILED( hres = (expr) ) ) T3D_DDEXCEPT(hres) }

	DDClipper::DDClipper(const DDraw * ddraw)
	{
		FAILED_DDEXCEPT(ddraw->m_ddraw->CreateClipper(0, &m_ddclipper, NULL));
	}

	DDClipper::~DDClipper(void)
	{
	}

	void DDClipper::SetHWnd(HWND hWnd)
	{
		SUCCEEDED_VERIFY(m_ddclipper->SetHWnd(0, hWnd));
	}

	void DDClipper::SetClipList(LPRGNDATA lpClipList)
	{
		SUCCEEDED_VERIFY(m_ddclipper->SetClipList(lpClipList, 0));
	}

	DDSurface::DDSurface(const DDraw * ddraw, DDSURFACEDESC2 & ddsd)
	{
		FAILED_DDEXCEPT(ddraw->m_ddraw->CreateSurface(&ddsd, &m_ddsurface, NULL));
	}

	DDSurface::~DDSurface(void)
	{
	}

	void DDSurface::SetClipper(LPDIRECTDRAWCLIPPER lpDDClipper)
	{
		SUCCEEDED_VERIFY(m_ddsurface->SetClipper(lpDDClipper));
	}

	void DDSurface::GetPixelFormat(LPDDPIXELFORMAT lpDDPixelFormat)
	{
		SUCCEEDED_VERIFY(m_ddsurface->GetPixelFormat(lpDDPixelFormat));
	}

	void DDSurface::Lock(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPRECT lpDestRect /*= NULL*/, DWORD dwFlags /*= DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR*/)
	{
		FAILED_DDEXCEPT(m_ddsurface->Lock(lpDestRect, lpDDSurfaceDesc, dwFlags, NULL));
	}

	void DDSurface::Unlock(LPRECT lpRect /*= NULL*/)
	{
		FAILED_DDEXCEPT(m_ddsurface->Unlock(lpRect));
	}

	void DDSurface::Blt(LPRECT lpDestRect, LPDIRECTDRAWSURFACE7 lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags /*= DDBLT_DONOTWAIT*/, LPDDBLTFX lpDDBltFx /*= NULL*/)
	{
		FAILED_DDEXCEPT(m_ddsurface->Blt(lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx));
	}

	void DDSurface::FILL(LPRECT lpDestRect, DWORD color)
	{
		DDBLTFX ddbf;
		memset(&ddbf, 0, sizeof(ddbf));
		ddbf.dwSize = sizeof(ddbf);
		ddbf.dwFillColor = color;

		Blt(lpDestRect, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbf);
	}

	void DDSurface::Restore(void)
	{
		FAILED_DDEXCEPT(m_ddsurface->Restore());
	}

	HDC DDSurface::GetDC(void)
	{
		HDC hdc;
		FAILED_DDEXCEPT(m_ddsurface->GetDC(&hdc));
		return hdc;
	}

	void DDSurface::ReleaseDC(HDC hdc)
	{
		FAILED_DDEXCEPT(m_ddsurface->ReleaseDC(hdc));
	}

	DDraw::DDraw(void)
	{
		FAILED_DDEXCEPT(DirectDrawCreateEx(NULL, (LPVOID *)&m_ddraw, IID_IDirectDraw7, NULL));
	}

	DDraw::~DDraw(void)
	{
	}

	void DDraw::SetCooperativeLevel( HWND hWnd, DWORD dwFlags)
	{
		FAILED_DDEXCEPT(m_ddraw->SetCooperativeLevel(hWnd, dwFlags));
	}

	void DDraw::SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwRefreshRate /*= 0*/)
	{
		FAILED_DDEXCEPT(m_ddraw->SetDisplayMode(dwWidth, dwHeight, dwBPP, dwRefreshRate, 0));
	}

	void DDraw::RestoreDisplayMode(void)
	{
		FAILED_DDEXCEPT(m_ddraw->RestoreDisplayMode());
	}

	void DDraw::WaitForVerticalBlank(DWORD dwFlags /*= WF_BEGIN*/)
	{
		FAILED_DDEXCEPT(m_ddraw->WaitForVerticalBlank(dwFlags, NULL));
	}

	DDClipperPtr DDraw::CreateWindowClipper(HWND hWnd)
	{
		DDClipperPtr clipper(new DDClipper(this));
		clipper->SetHWnd(hWnd);
		return clipper;
	}

	DDClipperPtr DDraw::CreateMemoryClipper(LPRECT lpRect, DWORD dwCount)
	{
		boost::shared_array<unsigned char> tmpData(new unsigned char[sizeof(RGNDATAHEADER) + sizeof(RECT) * dwCount]);

		LPRGNDATA pRgnd = (LPRGNDATA)tmpData.get();
		if(NULL == pRgnd)
			T3D_CUSEXCEPT(_T("malloc RGNDATA failed"));

		memset(pRgnd, 0, sizeof(RGNDATAHEADER));

		pRgnd->rdh.dwSize			= sizeof(pRgnd->rdh);
		pRgnd->rdh.iType			= RDH_RECTANGLES;
		pRgnd->rdh.nCount			= dwCount;
		pRgnd->rdh.nRgnSize			= dwCount * sizeof(RECT);
		pRgnd->rdh.rcBound.left		=  6400;
		pRgnd->rdh.rcBound.top		=  6400;
		pRgnd->rdh.rcBound.right	= -6400;
		pRgnd->rdh.rcBound.bottom	= -6400;

		for(size_t i = 0; i < dwCount; i++)
		{
			pRgnd->rdh.rcBound.left		= std::min(pRgnd->rdh.rcBound.left, lpRect[i].left);
			pRgnd->rdh.rcBound.top		= std::min(pRgnd->rdh.rcBound.top, lpRect[i].top);
			pRgnd->rdh.rcBound.right	= std::max(pRgnd->rdh.rcBound.right, lpRect[i].right);
			pRgnd->rdh.rcBound.bottom	= std::max(pRgnd->rdh.rcBound.bottom, lpRect[i].bottom);
		}

		memcpy(pRgnd->Buffer, lpRect, sizeof(RECT) * dwCount);

		DDClipperPtr clipper(new DDClipper(this));
		clipper->SetClipList(pRgnd);
		return clipper;
	}

	DDSurfacePtr DDraw::CreateWindowSurface(void)
	{
		DDSURFACEDESC2 ddsd;
		memset(&ddsd, 0, sizeof(ddsd));
		ddsd.dwSize				= sizeof(ddsd);
		ddsd.dwFlags			= DDSD_CAPS;
		ddsd.ddsCaps.dwCaps		= DDSCAPS_PRIMARYSURFACE;
		ddsd.dwBackBufferCount	= 0;

		DDSurfacePtr surface(new DDSurface(this, ddsd));
		return surface;
	}

	DDSurfacePtr DDraw::CreateMemorySurface(DWORD dwWidth, DWORD dwHeight)
	{
		DDSURFACEDESC2 ddsd;
		memset(&ddsd, 0, sizeof(ddsd));
		ddsd.dwSize				= sizeof(ddsd);
		ddsd.dwFlags			= DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		ddsd.ddsCaps.dwCaps		= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
		ddsd.dwWidth			= dwWidth;
		ddsd.dwHeight			= dwHeight;

		DDSurfacePtr surface(new DDSurface(this, ddsd));
		return surface;
	}
}
