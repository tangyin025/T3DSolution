
#include "stdafx.h"
#include "t3dlib1.h"

#include <cassert>
#include <crtdbg.h>
#include <boost/shared_ptr.hpp>

#pragma comment(lib, "DDraw.lib")
#pragma comment(lib, "dxguid.lib")

#ifdef MYGAME_EXPORTS
BOOL APIENTRY DllMain(HANDLE	hModule,
					  DWORD		ul_reason_for_call,
					  LPVOID	lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		//_CrtDumpMemoryLeaks(); // dont use like this, because some glabol obj havent been destroyed yet !!!
		break;
	}

	return TRUE;
	hModule;
	lpReserved;
}
#endif

namespace t3d
{
	std::basic_string<charT> DDraw::getResultStr(HRESULT hres)
	{
		const charT * pstr;
		switch(hres)
		{
		case DD_OK:
			pstr = _T("DD_OK"); break;
		case DDERR_ALREADYINITIALIZED:
			pstr = _T("DDERR_ALREADYINITIALIZED"); break;
		case DDERR_BLTFASTCANTCLIP:
			pstr = _T("DDERR_BLTFASTCANTCLIP"); break;
		case DDERR_CANNOTATTACHSURFACE:
			pstr = _T("DDERR_CANNOTATTACHSURFACE"); break;
		case DDERR_CANNOTDETACHSURFACE:
			pstr = _T("DDERR_CANNOTDETACHSURFACE"); break;
		case DDERR_CANTCREATEDC:
			pstr = _T("DDERR_CANTCREATEDC"); break;
		case DDERR_CANTDUPLICATE:
			pstr = _T("DDERR_CANTDUPLICATE"); break;
		case DDERR_CANTLOCKSURFACE:
			pstr = _T("DDERR_CANTLOCKSURFACE"); break;
		case DDERR_CANTPAGELOCK:
			pstr = _T("DDERR_CANTPAGELOCK"); break;
		case DDERR_CANTPAGEUNLOCK:
			pstr = _T("DDERR_CANTPAGEUNLOCK"); break;
		case DDERR_CLIPPERISUSINGHWND:
			pstr = _T("DDERR_CLIPPERISUSINGHWND"); break;
		case DDERR_COLORKEYNOTSET:
			pstr = _T("DDERR_COLORKEYNOTSET"); break;
		case DDERR_CURRENTLYNOTAVAIL:
			pstr = _T("DDERR_CURRENTLYNOTAVAIL"); break;
		case DDERR_DDSCAPSCOMPLEXREQUIRED:
			pstr = _T("DDERR_DDSCAPSCOMPLEXREQUIRED"); break;
		case DDERR_DCALREADYCREATED:
			pstr = _T("DDERR_DCALREADYCREATED"); break;
		case DDERR_DEVICEDOESNTOWNSURFACE:
			pstr = _T("DDERR_DEVICEDOESNTOWNSURFACE"); break;
		case DDERR_DIRECTDRAWALREADYCREATED:
			pstr = _T("DDERR_DIRECTDRAWALREADYCREATED"); break;
		case DDERR_EXCEPTION:
			pstr = _T("DDERR_EXCEPTION"); break;
		case DDERR_EXCLUSIVEMODEALREADYSET:
			pstr = _T("DDERR_EXCLUSIVEMODEALREADYSET"); break;
		case DDERR_EXPIRED:
			pstr = _T("DDERR_EXPIRED"); break;
		case DDERR_GENERIC:
			pstr = _T("DDERR_GENERIC"); break;
		case DDERR_HEIGHTALIGN:
			pstr = _T("DDERR_HEIGHTALIGN"); break;
		case DDERR_HWNDALREADYSET:
			pstr = _T("DDERR_HWNDALREADYSET"); break;
		case DDERR_HWNDSUBCLASSED:
			pstr = _T("DDERR_HWNDSUBCLASSED"); break;
		case DDERR_IMPLICITLYCREATED:
			pstr = _T("DDERR_IMPLICITLYCREATED"); break;
		case DDERR_INCOMPATIBLEPRIMARY:
			pstr = _T("DDERR_INCOMPATIBLEPRIMARY"); break;
		case DDERR_INVALIDCAPS:
			pstr = _T("DDERR_INVALIDCAPS"); break;
		case DDERR_INVALIDCLIPLIST:
			pstr = _T("DDERR_INVALIDCLIPLIST"); break;
		case DDERR_INVALIDDIRECTDRAWGUID:
			pstr = _T("DDERR_INVALIDDIRECTDRAWGUID"); break;
		case DDERR_INVALIDMODE:
			pstr = _T("DDERR_INVALIDMODE"); break;
		case DDERR_INVALIDOBJECT:
			pstr = _T("DDERR_INVALIDOBJECT"); break;
		case DDERR_INVALIDPARAMS:
			pstr = _T("DDERR_INVALIDPARAMS"); break;
		case DDERR_INVALIDPIXELFORMAT:
			pstr = _T("DDERR_INVALIDPIXELFORMAT"); break;
		case DDERR_INVALIDPOSITION:
			pstr = _T("DDERR_INVALIDPOSITION"); break;
		case DDERR_INVALIDRECT:
			pstr = _T("DDERR_INVALIDRECT"); break;
		case DDERR_INVALIDSTREAM:
			pstr = _T("DDERR_INVALIDSTREAM"); break;
		case DDERR_INVALIDSURFACETYPE:
			pstr = _T("DDERR_INVALIDSURFACETYPE"); break;
		case DDERR_LOCKEDSURFACES:
			pstr = _T("DDERR_LOCKEDSURFACES"); break;
		case DDERR_MOREDATA:
			pstr = _T("DDERR_MOREDATA"); break;
		case DDERR_NEWMODE:
			pstr = _T("DDERR_NEWMODE"); break;
		case DDERR_NO3D:
			pstr = _T("DDERR_NO3D"); break;
		case DDERR_NOALPHAHW:
			pstr = _T("DDERR_NOALPHAHW"); break;
		case DDERR_NOBLTHW:
			pstr = _T("DDERR_NOBLTHW"); break;
		case DDERR_NOCLIPLIST:
			pstr = _T("DDERR_NOCLIPLIST"); break;
		case DDERR_NOCLIPPERATTACHED:
			pstr = _T("DDERR_NOCLIPPERATTACHED"); break;
		case DDERR_NOCOLORCONVHW:
			pstr = _T("DDERR_NOCOLORCONVHW"); break;
		case DDERR_NOCOLORKEY:
			pstr = _T("DDERR_NOCOLORKEY"); break;
		case DDERR_NOCOLORKEYHW:
			pstr = _T("DDERR_NOCOLORKEYHW"); break;
		case DDERR_NOCOOPERATIVELEVELSET:
			pstr = _T("DDERR_NOCOOPERATIVELEVELSET"); break;
		case DDERR_NODC:
			pstr = _T("DDERR_NODC"); break;
		case DDERR_NODDROPSHW:
			pstr = _T("DDERR_NODDROPSHW"); break;
		case DDERR_NODIRECTDRAWHW:
			pstr = _T("DDERR_NODIRECTDRAWHW"); break;
		case DDERR_NODIRECTDRAWSUPPORT:
			pstr = _T("DDERR_NODIRECTDRAWSUPPORT"); break;
		case DDERR_NODRIVERSUPPORT:
			pstr = _T("DDERR_NODRIVERSUPPORT"); break;
		case DDERR_NOEMULATION:
			pstr = _T("DDERR_NOEMULATION"); break;
		case DDERR_NOEXCLUSIVEMODE:
			pstr = _T("DDERR_NOEXCLUSIVEMODE"); break;
		case DDERR_NOFLIPHW:
			pstr = _T("DDERR_NOFLIPHW"); break;
		case DDERR_NOFOCUSWINDOW:
			pstr = _T("DDERR_NOFOCUSWINDOW"); break;
		case DDERR_NOGDI:
			pstr = _T("DDERR_NOGDI"); break;
		case DDERR_NOHWND:
			pstr = _T("DDERR_NOHWND"); break;
		case DDERR_NOMIPMAPHW:
			pstr = _T("DDERR_NOMIPMAPHW"); break;
		case DDERR_NOMIRRORHW:
			pstr = _T("DDERR_NOMIRRORHW"); break;
		case DDERR_NOMONITORINFORMATION:
			pstr = _T("DDERR_NOMONITORINFORMATION"); break;
		case DDERR_NONONLOCALVIDMEM:
			pstr = _T("DDERR_NONONLOCALVIDMEM"); break;
		case DDERR_NOOPTIMIZEHW:
			pstr = _T("DDERR_NOOPTIMIZEHW"); break;
		case DDERR_NOOVERLAYDEST:
			pstr = _T("DDERR_NOOVERLAYDEST"); break;
		case DDERR_NOOVERLAYHW:
			pstr = _T("DDERR_NOOVERLAYHW"); break;
		case DDERR_NOPALETTEATTACHED:
			pstr = _T("DDERR_NOPALETTEATTACHED"); break;
		case DDERR_NOPALETTEHW:
			pstr = _T("DDERR_NOPALETTEHW"); break;
		case DDERR_NORASTEROPHW:
			pstr = _T("DDERR_NORASTEROPHW"); break;
		case DDERR_NOROTATIONHW:
			pstr = _T("DDERR_NOROTATIONHW"); break;
		case DDERR_NOSTEREOHARDWARE:
			pstr = _T("DDERR_NOSTEREOHARDWARE"); break;
		case DDERR_NOSTRETCHHW:
			pstr = _T("DDERR_NOSTRETCHHW"); break;
		case DDERR_NOSURFACELEFT:
			pstr = _T("DDERR_NOSURFACELEFT"); break;
		case DDERR_NOT4BITCOLOR:
			pstr = _T("DDERR_NOT4BITCOLOR"); break;
		case DDERR_NOT4BITCOLORINDEX:
			pstr = _T("DDERR_NOT4BITCOLORINDEX"); break;
		case DDERR_NOT8BITCOLOR:
			pstr = _T("DDERR_NOT8BITCOLOR"); break;
		case DDERR_NOTAOVERLAYSURFACE:
			pstr = _T("DDERR_NOTAOVERLAYSURFACE"); break;
		case DDERR_NOTEXTUREHW:
			pstr = _T("DDERR_NOTEXTUREHW"); break;
		case DDERR_NOTFLIPPABLE:
			pstr = _T("DDERR_NOTFLIPPABLE"); break;
		case DDERR_NOTFOUND:
			pstr = _T("DDERR_NOTFOUND"); break;
		case DDERR_NOTINITIALIZED:
			pstr = _T("DDERR_NOTINITIALIZED"); break;
		case DDERR_NOTLOADED:
			pstr = _T("DDERR_NOTLOADED"); break;
		case DDERR_NOTLOCKED:
			pstr = _T("DDERR_NOTLOCKED"); break;
		case DDERR_NOTPAGELOCKED:
			pstr = _T("DDERR_NOTPAGELOCKED"); break;
		case DDERR_NOTPALETTIZED:
			pstr = _T("DDERR_NOTPALETTIZED"); break;
		case DDERR_NOVSYNCHW:
			pstr = _T("DDERR_NOVSYNCHW"); break;
		case DDERR_NOZBUFFERHW:
			pstr = _T("DDERR_NOZBUFFERHW"); break;
		case DDERR_NOZOVERLAYHW:
			pstr = _T("DDERR_NOZOVERLAYHW"); break;
		case DDERR_OUTOFCAPS:
			pstr = _T("DDERR_OUTOFCAPS"); break;
		case DDERR_OUTOFMEMORY:
			pstr = _T("DDERR_OUTOFMEMORY"); break;
		case DDERR_OUTOFVIDEOMEMORY:
			pstr = _T("DDERR_OUTOFVIDEOMEMORY"); break;
		case DDERR_OVERLAPPINGRECTS:
			pstr = _T("DDERR_OVERLAPPINGRECTS"); break;
		case DDERR_OVERLAYCANTCLIP:
			pstr = _T("DDERR_OVERLAYCANTCLIP"); break;
		case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
			pstr = _T("DDERR_OVERLAYCOLORKEYONLYONEACTIVE"); break;
		case DDERR_OVERLAYNOTVISIBLE:
			pstr = _T("DDERR_OVERLAYNOTVISIBLE"); break;
		case DDERR_PALETTEBUSY:
			pstr = _T("DDERR_PALETTEBUSY"); break;
		case DDERR_PRIMARYSURFACEALREADYEXISTS:
			pstr = _T("DDERR_PRIMARYSURFACEALREADYEXISTS"); break;
		case DDERR_REGIONTOOSMALL:
			pstr = _T("DDERR_REGIONTOOSMALL"); break;
		case DDERR_SURFACEALREADYATTACHED:
			pstr = _T("DDERR_SURFACEALREADYATTACHED"); break;
		case DDERR_SURFACEALREADYDEPENDENT:
			pstr = _T("DDERR_SURFACEALREADYDEPENDENT"); break;
		case DDERR_SURFACEBUSY:
			pstr = _T("DDERR_SURFACEBUSY"); break;
		case DDERR_SURFACEISOBSCURED:
			pstr = _T("DDERR_SURFACEISOBSCURED"); break;
		case DDERR_SURFACELOST:
			pstr = _T("DDERR_SURFACELOST"); break;
		case DDERR_SURFACENOTATTACHED:
			pstr = _T("DDERR_SURFACENOTATTACHED"); break;
		case DDERR_TESTFINISHED:
			pstr = _T("DDERR_TESTFINISHED"); break;
		case DDERR_TOOBIGHEIGHT:
			pstr = _T("DDERR_TOOBIGHEIGHT"); break;
		case DDERR_TOOBIGSIZE:
			pstr = _T("DDERR_TOOBIGSIZE"); break;
		case DDERR_TOOBIGWIDTH:
			pstr = _T("DDERR_TOOBIGWIDTH"); break;
		case DDERR_UNSUPPORTED:
			pstr = _T("DDERR_UNSUPPORTED"); break;
		case DDERR_UNSUPPORTEDFORMAT:
			pstr = _T("DDERR_UNSUPPORTEDFORMAT"); break;
		case DDERR_UNSUPPORTEDMASK:
			pstr = _T("DDERR_UNSUPPORTEDMASK"); break;
		case DDERR_UNSUPPORTEDMODE:
			pstr = _T("DDERR_UNSUPPORTEDMODE"); break;
		case DDERR_VERTICALBLANKINPROGRESS:
			pstr = _T("DDERR_VERTICALBLANKINPROGRESS"); break;
		case DDERR_VIDEONOTACTIVE:
			pstr = _T("DDERR_VIDEONOTACTIVE"); break;
		case DDERR_WASSTILLDRAWING:
			pstr = _T("DDERR_WASSTILLDRAWING"); break;
		case DDERR_WRONGMODE:
			pstr = _T("DDERR_WRONGMODE"); break;
		case DDERR_XALIGN:
			pstr = _T("DDERR_XALIGN"); break;
		default:
			pstr = _T("unknown ddraw error result"); break;
		}
		return std::basic_string<charT>(pstr);
	}

	t3d::DDraw::Exception::Exception(const std::basic_string<charT> & file, int line, HRESULT hres)
		: t3d::Exception(file, line)
		, m_hres(hres)
	{
	}

	std::basic_string<charT> t3d::DDraw::Exception::what(void) const throw()
	{
		return getResultStr(m_hres);
	}

#define T3D_DDEXCEPT(hres) { throw t3d::DDraw::Exception(_T(__FILE__), __LINE__, (hres)); }

	DDraw::DDraw()
		: m_lpddraw(NULL)
	{
		HRESULT hres;
		if(FAILED(hres = DirectDrawCreateEx(NULL, (LPVOID *)&m_lpddraw, IID_IDirectDraw7, NULL)))
			T3D_DDEXCEPT(hres);
	}

	DDraw::~DDraw()
	{
		SAFE_RELEASE(m_lpddraw);
	}

	void DDraw::setCooperativeLevel(HWND hwnd, DWORD level)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpddraw->SetCooperativeLevel(hwnd, level)))
			T3D_DDEXCEPT(hres);
	}

	void DDraw::setDisplayMode(DWORD width, DWORD height, DWORD bpp, DWORD refreshRate /*= 0*/)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpddraw->SetDisplayMode(width, height, bpp, refreshRate, 0)))
			T3D_DDEXCEPT(hres);
	}

	//void DDraw::restoreDisplayMode(void)
	//{
	//	HRESULT hres;
	//	if(FAILED(hres = m_lpddraw->RestoreDisplayMode()))
	//		T3D_DDEXCEPT(hres);
	//}

	void DDraw::waitForVerticalBlank(DWORD flags /*= WF_BEGIN*/)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpddraw->WaitForVerticalBlank(flags, NULL)))
			T3D_DDEXCEPT(hres);
	}

	DDraw::Clipper * DDraw::createWindowClipper(HWND hwnd)
	{
		return new WindowClipper(this, hwnd);
	}

	DDraw::Clipper * DDraw::createMemoryClipper(const RECT rect[], size_t rect_size)
	{
		return new MemoryClipper(this, rect, rect_size);
	}

	DDraw::Surface * DDraw::createWindowSurface(void)
	{
		return new WindowSurface(this);
	}

	DDraw::Surface * DDraw::createMemorySurface(DWORD width, DWORD height)
	{
		return new MemorySurface(this, width, height);
	}

	DDraw::Clipper::Clipper(const DDraw * ddraw)
		: m_lpddclipper(NULL)
	{
		assert(NULL != ddraw);
		assert(NULL != ddraw->m_lpddraw);

		HRESULT hres;
		if(FAILED(hres = ddraw->m_lpddraw->CreateClipper(0, &m_lpddclipper, NULL)))
			T3D_DDEXCEPT(hres);
	}

	DDraw::Clipper::~Clipper()
	{
		SAFE_RELEASE(m_lpddclipper);
	}

	DDraw::WindowClipper::WindowClipper(const DDraw * ddraw, HWND hwnd)
		: Clipper(ddraw)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpddclipper->SetHWnd(0, hwnd)))
			T3D_DDEXCEPT(hres);
	}

	DDraw::MemoryClipper::MemoryClipper(const DDraw * ddraw, const RECT rect[], size_t rect_size)
		: Clipper(ddraw)
	{
		const size_t rgnd_size = sizeof(RGNDATAHEADER) + rect_size * sizeof(RECT);

		boost::shared_ptr<RGNDATA> rgnd_ptr((LPRGNDATA)malloc(rgnd_size));
		if(NULL == rgnd_ptr.get())
			T3D_CUSEXCEPT(_T("malloc RGNDATA failed"));

		memset(rgnd_ptr.get(), 0, rgnd_size);
		rgnd_ptr->rdh.dwSize			= sizeof(rgnd_ptr->rdh);
		rgnd_ptr->rdh.iType				= RDH_RECTANGLES;
		rgnd_ptr->rdh.nCount			= (DWORD)rect_size;
		rgnd_ptr->rdh.nRgnSize			= (DWORD)rect_size * sizeof(RECT);
		rgnd_ptr->rdh.rcBound.left		=  6400;
		rgnd_ptr->rdh.rcBound.top		=  6400;
		rgnd_ptr->rdh.rcBound.right		= -6400;
		rgnd_ptr->rdh.rcBound.bottom	= -6400;

		for(size_t i = 0; i < rect_size; i++)
		{
			rgnd_ptr->rdh.rcBound.left		= std::min(rgnd_ptr->rdh.rcBound.left,	rect[i].left);
			rgnd_ptr->rdh.rcBound.top		= std::min(rgnd_ptr->rdh.rcBound.top,	rect[i].top);
			rgnd_ptr->rdh.rcBound.right		= std::max(rgnd_ptr->rdh.rcBound.right,	rect[i].right);
			rgnd_ptr->rdh.rcBound.bottom	= std::max(rgnd_ptr->rdh.rcBound.bottom,	rect[i].bottom);
		}
		memcpy(rgnd_ptr->Buffer, rect, rect_size * sizeof(RECT));

		HRESULT hres;
		if(FAILED(hres = m_lpddclipper->SetClipList(rgnd_ptr.get(), 0)))
			T3D_DDEXCEPT(hres);
	}

	DDraw::Surface::Surface(const DDraw * ddraw)
		: m_lpddsurface(NULL)
	{
		assert(NULL != ddraw);
		assert(NULL != ddraw->m_lpddraw);

		ddraw;
	}

	DDraw::Surface::~Surface()
	{
		SAFE_RELEASE(m_lpddsurface);
	}

	void DDraw::Surface::setClipper(Clipper * clipper)
	{
		assert(NULL != m_lpddsurface);

		assert(NULL != clipper);
		assert(NULL != clipper->m_lpddclipper);

		HRESULT hres;
		if(FAILED(hres = m_lpddsurface->SetClipper(clipper->m_lpddclipper)))
			T3D_DDEXCEPT(hres);
	}

	DDPIXELFORMAT DDraw::Surface::getPixelFormat(void)
	{
		assert(NULL != m_lpddsurface);

		DDPIXELFORMAT ddpf;
		ddpf.dwSize = sizeof(ddpf);

		HRESULT hres;
		if(FAILED(hres = m_lpddsurface->GetPixelFormat(&ddpf)))
			T3D_DDEXCEPT(hres);

		return ddpf;
	}

	DDSURFACEDESC2 DDraw::Surface::lock(const RECT * prect /*= NULL*/)
	{
		assert(NULL != m_lpddsurface);

		DDSURFACEDESC2 ddsd;
		ddsd.dwSize = sizeof(ddsd);

		HRESULT hres;
		if(FAILED(hres = m_lpddsurface->Lock(const_cast<RECT *>(prect), &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, 0)))
			T3D_DDEXCEPT(hres);

		return ddsd;
	}

	void DDraw::Surface::unlock(const RECT * prect /*= NULL*/)
	{
		assert(NULL != m_lpddsurface);

		HRESULT hres;
		if(FAILED(hres = m_lpddsurface->Unlock(const_cast<RECT *>(prect))))
			T3D_DDEXCEPT(hres);
	}

	void DDraw::Surface::blt(const RECT * dst_rect, const Surface * src_surf, const RECT * src_rect, DWORD flag /*= DDBLT_DONOTWAIT*/)
	{
		assert(NULL != m_lpddsurface);

		HRESULT hres;
		if(FAILED(hres = m_lpddsurface->Blt(const_cast<RECT *>(dst_rect), src_surf->m_lpddsurface, const_cast<RECT *>(src_rect), flag, NULL)))
			T3D_DDEXCEPT(hres);
	}

	void DDraw::Surface::fill(const RECT * dst_rect, DWORD color)
	{
		assert(NULL != m_lpddsurface);

		DDBLTFX ddbf;
		memset(&ddbf, 0, sizeof(ddbf));
		ddbf.dwSize = sizeof(ddbf);
		ddbf.dwFillColor = color;

		HRESULT hres;
		if(FAILED(hres = m_lpddsurface->Blt(const_cast<RECT *>(dst_rect), NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbf)))
			T3D_DDEXCEPT(hres);
	}

	HDC DDraw::Surface::getDC(void)
	{
		assert(NULL != m_lpddsurface);

		HDC hdc;
		HRESULT hres;
		if(FAILED(hres = m_lpddsurface->GetDC(&hdc)))
			T3D_DDEXCEPT(hres);

		return hdc;
	}

	void DDraw::Surface::releaseDC(HDC hdc)
	{
		assert(NULL != m_lpddsurface);

		HRESULT hres;
		if(FAILED(hres = m_lpddsurface->ReleaseDC(hdc)))
			T3D_DDEXCEPT(hres);
	}

	//void DDraw::Surface::restore(void)
	//{
	//	assert(NULL != m_lpddsurface);

	//	HRESULT hres;
	//	if(FAILED(hres = m_lpddsurface->Restore()))
	//		T3D_DDEXCEPT(hres);
	//}

	DDraw::WindowSurface::WindowSurface(const DDraw * ddraw)
		: Surface(ddraw)
	{
		DDSURFACEDESC2 ddsd;
		memset(&ddsd, 0, sizeof(ddsd));
		ddsd.dwSize				= sizeof(ddsd);
		ddsd.dwFlags			= DDSD_CAPS;
		ddsd.ddsCaps.dwCaps		= DDSCAPS_PRIMARYSURFACE;
		ddsd.dwBackBufferCount	= 0;

		HRESULT hres;
		if(FAILED(hres = ddraw->m_lpddraw->CreateSurface(&ddsd, &m_lpddsurface, NULL)))
			T3D_DDEXCEPT(hres);
	}

	DDraw::MemorySurface::MemorySurface(const DDraw * ddraw, DWORD width, DWORD height)
		: Surface(ddraw)
	{
		DDSURFACEDESC2 ddsd;
		memset(&ddsd, 0, sizeof(ddsd));
		ddsd.dwSize				= sizeof(ddsd);
		ddsd.dwFlags			= DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		ddsd.ddsCaps.dwCaps		= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
		ddsd.dwWidth			= width;
		ddsd.dwHeight			= height;

		HRESULT hres;
		if(FAILED(hres = ddraw->m_lpddraw->CreateSurface(&ddsd, &m_lpddsurface, NULL)))
			T3D_DDEXCEPT(hres);
	}
}
