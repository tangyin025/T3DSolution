
#ifndef __T3DLIB1_H__
#define __T3DLIB1_H__

#include "t3dcommon.h"

#include <string>
#include <climits>
#include <windows.h>
#include <ddraw.h>

namespace t3d
{
	class T3DLIB_API DDraw
	{
	public:
		static std::basic_string<charT> getResultStr(HRESULT hres);

		class T3DLIB_API Exception : public t3d::Exception
		{
		public:
			Exception(const std::basic_string<charT> & file, int line, HRESULT hres);

		public:
			std::basic_string<charT> what(void) const throw();

		protected:
			HRESULT m_hres;
		};

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
		DDraw();

		virtual ~DDraw();

	public:
		void setCooperativeLevel(HWND hwnd, DWORD level);

		void setDisplayMode(DWORD width, DWORD height, DWORD bpp, DWORD refreshRate = 0);

		//void restoreDisplayMode(void);

		void waitForVerticalBlank(DWORD flags = WF_BEGIN);

		class Clipper;

		Clipper * createWindowClipper(HWND hwnd);

		Clipper * createMemoryClipper(const RECT rect[], size_t rect_size);

		class Surface;

		Surface * createWindowSurface(void);

		Surface * createMemorySurface(DWORD width, DWORD height);

	protected:
		LPDIRECTDRAW7 m_lpddraw;

	public:
		class T3DLIB_API Clipper
		{
			friend class Surface;

		protected:
			Clipper(const DDraw * ddraw);

		public:
			virtual ~Clipper();

		protected:
			LPDIRECTDRAWCLIPPER m_lpddclipper;
		};

		class T3DLIB_API WindowClipper : public Clipper
		{
		public:
			WindowClipper(const DDraw * ddraw, HWND hwnd);
		};

		class T3DLIB_API MemoryClipper : public Clipper
		{
		public:
			MemoryClipper(const DDraw * ddraw, const RECT rect[], size_t rect_size);
		};

		class T3DLIB_API Surface
		{
		protected:
			Surface(const DDraw * ddraw);

		public:
			virtual ~Surface();

		public:
			void setClipper(Clipper * clipper);

			DDPIXELFORMAT getPixelFormat(void);

			DDSURFACEDESC2 lock(const RECT * prect = NULL);

			void unlock(const RECT * prect = NULL);

			void blt(const RECT * dst_rect, const Surface * src_surf, const RECT * src_rect, DWORD flag = DDBLT_DONOTWAIT);

			void fill(const RECT * dst_rect, DWORD color);

			HDC getDC(void);

			void releaseDC(HDC hdc);

			//void restore(void);

		protected:
			LPDIRECTDRAWSURFACE7 m_lpddsurface;
		};

		class T3DLIB_API WindowSurface : public Surface
		{
		public:
			WindowSurface(const DDraw * ddraw);
		};

		class T3DLIB_API MemorySurface : public Surface
		{
		public:
			MemorySurface(const DDraw * ddraw, DWORD width, DWORD height);
		};
	};
}

#endif // __T3DLIB1_H__
