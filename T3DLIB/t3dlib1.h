
#ifndef __T3DLIB1_H__
#define __T3DLIB1_H__

#include "t3dcommon.h"
#include <string>
#include <ddraw.h>
#include <atlbase.h>
#include <boost/shared_ptr.hpp>

namespace t3d
{
	class DDException : public Exception
	{
	public:
		static std::basic_string<charT> GetResultStr(HRESULT hres);

	public:
		DDException(const std::basic_string<charT> & file, int line, HRESULT hres);

	public:
		std::basic_string<charT> what(void) const throw();

	protected:
		HRESULT m_hres;
	};

	class DDraw;

	class DDClipper
	{
		friend DDraw;

	public:
		CComPtr<IDirectDrawClipper> m_ddclipper;

	protected:
		DDClipper(DDraw * ddraw);

	public:
		virtual ~DDClipper(void);

		void SetHWnd(HWND hWnd);

		void SetClipList(LPRGNDATA lpClipList);
	};

	typedef boost::shared_ptr<DDClipper> DDClipperPtr;

	class DDSurface
	{
		friend DDraw;

	public:
		CComPtr<IDirectDrawSurface7> m_ddsurface;

	protected:
		DDSurface(DDraw * ddraw, DDSURFACEDESC2 & ddsd);

	public:
		virtual ~DDSurface(void);

	public:
		void SetClipper(DDClipper * ddclipper);

		DDPIXELFORMAT GetPixelFormat(void);

		DDSURFACEDESC2 Lock(LPRECT lpDestRect = NULL, DWORD dwFlags = DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR);

		void Unlock(LPRECT lpRect = NULL);

		void Blt(LPRECT lpDestRect, DDSurface * dsurface, LPRECT lpSrcRect, DWORD dwFlags = DDBLT_DONOTWAIT, LPDDBLTFX lpDDBltFx = NULL);

		void Fill(LPRECT lpDestRect, DWORD color);

		void Restore(void);

		HDC GetDC(void);

		void ReleaseDC(HDC hdc);
	};

	typedef boost::shared_ptr<DDSurface> DDSurfacePtr;

	class DDraw
	{
	public:
		CComPtr<IDirectDraw7> m_ddraw;

	public:
		enum COOPERATIVE_LEVEL
		{
			CL_NORMAL		= DDSCL_NORMAL,
			CL_EXCLUSIVE	= DDSCL_ALLOWMODEX | DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_MULTITHREADED,
		};

		enum WAITBLANK_FLAG
		{
			WF_BEGIN		= DDWAITVB_BLOCKBEGIN,
			WF_END			= DDWAITVB_BLOCKEND,
		};

	public:
		DDraw(void);

		virtual ~DDraw(void);

	public:
		void SetCooperativeLevel(HWND hWnd, DWORD dwFlags = CL_NORMAL);

		void SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwRefreshRate = 0);

		void RestoreDisplayMode(void);

		void WaitForVerticalBlank(DWORD dwFlags = WF_BEGIN);

		DDClipperPtr CreateWindowClipper(HWND hWnd);

		DDClipperPtr CreateMemoryClipper(LPRECT lpRect, DWORD dwCount);

		DDSurfacePtr CreateWindowSurface(void);

		DDSurfacePtr CreateMemorySurface(DWORD dwWidth, DWORD dwHeight);
	};

	typedef boost::shared_ptr<DDraw> DDrawPtr;
}

#endif // __T3DLIB1_H__
