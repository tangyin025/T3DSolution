
#ifndef __T3DLIB1_H__
#define __T3DLIB1_H__

#include "t3dcommon.h"
#include <string>
#include <ddraw.h>
#include <atlbase.h>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

namespace t3d
{
	class DDException : public Exception
	{
	public:
		static std::basic_string<charT> getResultStr(HRESULT hres);

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

		void setHWnd(HWND hWnd);

		void setClipList(LPRGNDATA lpClipList);
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
		void setClipper(DDClipper * ddclipper);

		DDPIXELFORMAT getPixelFormat(void);

		DDSURFACEDESC2 lock(LPRECT lpDestRect = NULL, DWORD dwFlags = DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR);

		void unlock(LPRECT lpRect = NULL);

		void blt(LPRECT lpDestRect, DDSurface * srcSurface, LPRECT lpSrcRect, DWORD dwFlags = DDBLT_DONOTWAIT, LPDDBLTFX lpDDBltFx = NULL);

		void bltFast(DWORD dwX, DWORD dwY, DDSurface * srcSurface, LPRECT lpSrcRect, DWORD dwTrans = DDBLTFAST_NOCOLORKEY);

		void fill(LPRECT lpDestRect, DWORD color);

		void restore(void);

		HDC getDC(void);

		void releaseDC(HDC hdc);
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
		void setCooperativeLevel(HWND hWnd, DWORD dwFlags = CL_NORMAL);

		void setDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwRefreshRate = 0);

		DDSURFACEDESC2 getDisplayMode(void);

		void restoreDisplayMode(void);

		void waitForVerticalBlank(DWORD dwFlags = WF_BEGIN);

		DDClipperPtr createWindowClipper(HWND hWnd);

		DDClipperPtr createMemoryClipper(LPRECT lpRect, DWORD dwCount);

		DDSurfacePtr createWindowSurface(void);

		DDSurfacePtr createMemorySurface(DWORD dwWidth, DWORD dwHeight);
	};

	typedef boost::shared_ptr<DDraw> DDrawPtr;

	class ZBuffer
	{
	public:
		boost::shared_array<fixp28> m_buffer;

		LONG m_lPitch;

	public:
		ZBuffer(DWORD dwWidth, DWORD dwHeight);

		virtual ~ZBuffer(void);

		const fixp28 * getBuffer(void) const;

		fixp28 * getBuffer(void);

		LONG getPitch(void);
	};

	typedef boost::shared_ptr<ZBuffer> ZBufferPtr;
}

#endif // __T3DLIB1_H__
