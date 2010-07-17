/* file: Demo1_1/main.cpp
 * define the basic framework of t3dlib, applicable for both win32 and MFC application
 */

#include <t3dlib1.h>
#include <t3dlib6.h>
#include <atlwin.h>

#pragma comment(lib, "winmm.lib")

class CMyWindow
	: public CWindowImpl<CMyWindow, CWindow, CWinTraits<WS_OVERLAPPEDWINDOW, 0> >
{
protected:
	t3d::DDrawPtr m_ddraw;

	t3d::DDSurfacePtr m_ddsurface;

	t3d::ZBufferPtr m_zbuffer;

	t3d::RenderContextPtr m_rc;

public:
	DECLARE_WND_CLASS_EX(GetWndClassName(), CS_HREDRAW | CS_VREDRAW, -1)

	BEGIN_MSG_MAP(CMyWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()

	LRESULT OnCreate(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
	{
		// create direct draw
		m_ddraw = t3d::DDrawPtr(new t3d::DDraw());
		m_ddraw->setCooperativeLevel(m_hWnd);

		// gain current display mode
		DDSURFACEDESC2 ddsd = m_ddraw->getDisplayMode();
		if(!(ddsd.ddpfPixelFormat.dwFlags & DDPF_RGB))
		{
			T3D_CUSEXCEPT(_T("unsupported pixel format"));
		}

		// create the render context according to current pixel mode
		// NOTE: it will crash the system when user changed current desktop color
		// bit when after this application runing
		if(ddsd.ddpfPixelFormat.dwRBitMask == RGB16_RED_MASK
			&& ddsd.ddpfPixelFormat.dwGBitMask == RGB16_GREEN_MASK
			&& ddsd.ddpfPixelFormat.dwBBitMask == RGB16_BLUE_MASK)
		{
			m_rc = t3d::RenderContextPtr(new t3d::RenderContext16());
		}
		else if(ddsd.ddpfPixelFormat.dwRBitMask == RGB32_RED_MASK
			&& ddsd.ddpfPixelFormat.dwGBitMask == RGB32_GREEN_MASK
			&& ddsd.ddpfPixelFormat.dwBBitMask == RGB32_BLUE_MASK)
		{
			m_rc = t3d::RenderContextPtr(new t3d::RenderContext32());
		}
		else
		{
			T3D_CUSEXCEPT(_T("unsupported pixel format"));
		}

		bHandled = TRUE;
		return 0;
	}

	LRESULT OnSize(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
	{
		if(SIZE_RESTORED == wParam || SIZE_MAXIMIZED == wParam)
		{
			// confirm ddraw & render context must be created
			_ASSERT(NULL != m_ddraw);
			_ASSERT(NULL != m_rc);

			// gain new window size
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			// create background surface and attach to render context
			m_ddsurface = m_ddraw->createMemorySurface(width, height);
			CRect rectMem(0, 0, width, height);
			m_ddsurface->setClipper(m_ddraw->createMemoryClipper(&rectMem, 1).get());
			DDSURFACEDESC2 ddsd = m_ddsurface->lock(NULL);
			m_rc->setSurfaceBuffer(ddsd.lpSurface, ddsd.lPitch, ddsd.dwWidth, ddsd.dwHeight);
			m_ddsurface->unlock();

			// create background zbuffer and attach to render context
			m_zbuffer = t3d::ZBufferPtr(new t3d::ZBuffer(width, height));
			m_rc->setZBufferBuffer(m_zbuffer->getBuffer(), m_zbuffer->getPitch(), width, height);

			// set render clipper rect
			m_rc->setClipperRect(rectMem);

			// invalidate window client area to force a redraw action
			InvalidateRect(NULL, FALSE);

			bHandled = TRUE;
		}
		return 0;
	}

	LRESULT OnPaint(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
	{
		// confirm the background surface must be created
		_ASSERT(NULL != m_ddsurface);

		// render a frame
		DoRender();

		// copy background surface to window dc
		CRect clientRect;
		GetClientRect(&clientRect);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(&ps);
		HDC hdcSrc = m_ddsurface->getDC();
		BitBlt(hdc, clientRect.left, clientRect.top, clientRect.Width(), clientRect.Height(), hdcSrc, 0, 0, SRCCOPY);
		m_ddsurface->releaseDC(hdcSrc);
		EndPaint(&ps);

		bHandled = TRUE;
		return 0;
	}

	void OnFinalMessage(HWND hwnd)
	{
		// exit the application
		::PostQuitMessage(0);
	}

	void DoRender(void)
	{
		// clear background surface & zbuffer
		m_rc->fillSurface(m_rc->getClipperRect(), t3d::vec3Build<t3d::real>(0.8f, 0.8f, 0.8f));
		m_rc->fillZbuffer(m_rc->getClipperRect(), 0);

		// definition set of fps utility
		static DWORD last_time = ::timeGetTime();
		static DWORD past_time = 0;
		static DWORD past_frames = 0;
		static t3d::real fps = 0;

		// calculate fps by sampling per second
		DWORD curr_time = ::timeGetTime();
		past_time += curr_time - last_time;
		past_frames += 1;
		if(past_time > 1000)
		{
			fps = (t3d::real)past_frames / (t3d::real)past_time * 1000;
			past_time = 0;
			past_frames = 0;
		}
		last_time = curr_time;

		// text out the fps information
		TCHAR buffer[MAX_PATH];
		_stprintf_s(buffer, _T("fps: %.1f"), fps);
		HDC hdc = m_ddsurface->getDC();
		::TextOut(hdc, 10, 10, buffer, _tcslen(buffer));
		m_ddsurface->releaseDC(hdc);

		// NOTE: there are still far more process could be done,
		// such as adjust camera's position, update camera's viewport & projection, ...
		// for more information, please refer the project "Demo1_2"
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR lpCmdLine,
					   int nCmdShow)
{
	// check memory leak
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));

	// declare main window
	CMyWindow myWnd;
	try
	{
		// gain current mode file name
		TCHAR szModuleFileName[MAX_PATH];
		GetModuleFileName(NULL, szModuleFileName, sizeof(szModuleFileName) / sizeof(szModuleFileName[0]));

		// create the main window
		if(NULL == myWnd.Create(NULL, CMyWindow::rcDefault, szModuleFileName))
		{
			return -1;
		}

		// update the main window
		myWnd.ShowWindow(nCmdShow);
		myWnd.UpdateWindow();

		// entering the main message looping
		MSG msg;
		msg.message = WM_NULL;
		while(msg.message != WM_QUIT)
		{
			if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				// invalid main window client if no message in the message queue
				myWnd.InvalidateRect(NULL, FALSE);
				myWnd.UpdateWindow();
			}
		}
		return (int)msg.wParam;
	}
	catch(t3d::Exception & e)
	{
		// report the exception information
		::MessageBox(NULL, e.getFullDesc().c_str(), _T("Exception"), MB_OK);
		exit(-1);
	}
}
