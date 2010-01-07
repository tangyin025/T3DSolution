
#include <t3dlib1.h>
#include <t3dlib6.h>
#include <atltypes.h>

using t3d::real;

#ifdef _DEBUG
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__ )
#endif

TCHAR szWindowClass[] = _T("SAMPLE");

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void OnFrame(HWND hwnd);

void DoRender(void);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDC_ICON);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = /*(HBRUSH)(COLOR_WINDOW+1)*/NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(NULL, IDC_ICON);
	RegisterClassEx(&wcex);

	TCHAR szModuleFileName[MAX_PATH];
	GetModuleFileName(NULL, szModuleFileName, sizeof(szModuleFileName) / sizeof(szModuleFileName[0]));

	try
	{
		HWND hWnd = CreateWindow(szWindowClass, szModuleFileName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
		if(hWnd)
		{
			ShowWindow(hWnd, nCmdShow);
			UpdateWindow(hWnd);

			MSG msg;
			msg.message = ~WM_QUIT;
			while(msg.message != WM_QUIT)
			{
				if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					OnFrame(hWnd);
				}
			}
		}
	}
	catch(t3d::Exception & e)
	{
		MessageBox(NULL, e.getFullDesc().c_str(), _T("Exception"), MB_OK);
	}

	return 0;
}

t3d::DDrawPtr g_ddraw;

t3d::DDSurfacePtr g_ddsurface;

t3d::ZBufferPtr g_zbuffer;

t3d::RenderContextPtr g_rc;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		{
			g_ddraw = t3d::DDrawPtr(new t3d::DDraw());
			g_ddraw->setCooperativeLevel(hWnd);
			DDSURFACEDESC2 ddsd = g_ddraw->getDisplayMode();
			if( !(ddsd.ddpfPixelFormat.dwFlags & DDPF_RGB) )
			{
				T3D_CUSEXCEPT(_T("unsupported pixel format"));
			}
			switch(ddsd.ddpfPixelFormat.dwRGBBitCount)
			{
			case 16:
				if(ddsd.ddpfPixelFormat.dwRBitMask != 0xF800
					|| ddsd.ddpfPixelFormat.dwGBitMask != 0x07E0
					|| ddsd.ddpfPixelFormat.dwBBitMask != 0x001F)
				{
					T3D_CUSEXCEPT(_T("unsupported pixel format"));
				}
				g_rc = t3d::RenderContextPtr(new t3d::RenderContext16());
				break;

			case 32:
				g_rc = t3d::RenderContextPtr(new t3d::RenderContext32());
				break;

			default:
				T3D_CUSEXCEPT(_T("unsupported pixel format"));
			}
			return 0;
		}

	case WM_SIZE:
		if(SIZE_RESTORED == wParam && g_ddraw.get())
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			g_ddsurface = g_ddraw->createMemorySurface(width, height);
			CRect rectMem(0, 0, width, height);
			g_ddsurface->setClipper(g_ddraw->createMemoryClipper(&rectMem, 1).get());
			g_zbuffer = t3d::ZBufferPtr(new t3d::ZBuffer(width, height));
			DoRender();
			return 0;
		}
		break;

	case WM_PAINT:
		{
			assert(g_ddsurface.get());

			CRect clientRect;
			GetClientRect(hWnd, &clientRect);
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			HDC hdcSrc = g_ddsurface->getDC();
			BitBlt(hdc, clientRect.left, clientRect.top, clientRect.Width(), clientRect.Height(), hdcSrc, 0, 0, SRCCOPY);
			g_ddsurface->releaseDC(hdcSrc);
			EndPaint(hWnd, &ps);
			return 0;
		}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void OnFrame(HWND hwnd)
{
	assert(hwnd);

	DoRender();

	InvalidateRect(hwnd, NULL, FALSE);
}

void DoRender(void)
{
	DDSURFACEDESC2 ddsd = g_ddsurface->lock(NULL);
	g_rc->setSurfaceBuffer(ddsd.lpSurface, ddsd.lPitch, ddsd.dwWidth, ddsd.dwHeight);
	g_ddsurface->unlock();

	CRect rectSurface(0, 0, g_rc->getSurfaceWidth(), g_rc->getSurfaceHeight());

	g_rc->setZBufferBuffer(g_zbuffer->getBuffer(), g_zbuffer->getPitch(), rectSurface.Width(), rectSurface.Height());

	CRect rectClipper = rectSurface;

	rectClipper.DeflateRect(1, 1);

	g_rc->setClipperRect(rectClipper);

	g_rc->fillSurface(rectSurface, t3d::vec3Build<real>(0.8f, 0.8f, 0.8f));

	g_rc->fillZbuffer(rectSurface, 0);
}
