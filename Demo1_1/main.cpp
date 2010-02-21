/** FILE: main.cpp
	定义了一个基本的 t3dlib 应用程序的框架，适用于 win32 或 mfc 应用程序
*/

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
	// 运行时内存泄漏检查
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));

	// 定义一个基本的 windows 类
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
		// 创建窗口
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
					// 在没有消息的时候绘制一帧
					OnFrame(hWnd);
				}
			}
		}
	}
	catch(t3d::Exception & e)
	{
		::MessageBox(NULL, e.getFullDesc().c_str(), _T("Exception"), MB_OK);
	}

	return 0;
}

// direct draw
t3d::DDrawPtr g_ddraw;

// direct draw surface 用作后缓存
t3d::DDSurfacePtr g_ddsurface;

// zbuffer
t3d::ZBufferPtr g_zbuffer;

// 渲染上下文
t3d::RenderContextPtr g_rc;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		{
			// 创建 direct draw
			g_ddraw = t3d::DDrawPtr(new t3d::DDraw());
			g_ddraw->setCooperativeLevel(hWnd);

			// 获得当前显示模式
			DDSURFACEDESC2 ddsd = g_ddraw->getDisplayMode();
			if( !(ddsd.ddpfPixelFormat.dwFlags & DDPF_RGB) )
			{
				T3D_CUSEXCEPT(_T("unsupported pixel format"));
			}

			// 创建于当前显示模式兼容的渲染上下文
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
		if((SIZE_RESTORED == wParam || SIZE_MAXIMIZED == wParam) && g_ddraw.get())
		{
			_ASSERT(g_rc.get());

			// 获得当前窗口宽度和高度
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			// “重新”创建对应的后缓存
			g_ddsurface = g_ddraw->createMemorySurface(width, height);
			CRect rectMem(0, 0, width, height);
			g_ddsurface->setClipper(g_ddraw->createMemoryClipper(&rectMem, 1).get());

			// 设置 surface buffer，其实 memory surface 只要设置一次就可以了
			DDSURFACEDESC2 ddsd = g_ddsurface->lock(NULL);
			g_rc->setSurfaceBuffer(ddsd.lpSurface, ddsd.lPitch, ddsd.dwWidth, ddsd.dwHeight);
			g_ddsurface->unlock();

			// “重新”创建 zbuffer
			g_zbuffer = t3d::ZBufferPtr(new t3d::ZBuffer(width, height));

			// 设置 zbuffer
			g_rc->setZBufferBuffer(g_zbuffer->getBuffer(), g_zbuffer->getPitch(), width, height);

			// 更新渲染上下文的 clipper rect
			g_rc->setClipperRect(rectMem);

			/** 注意：
				其实在这个地方还有很多事情要做，如更新相机的 viewport 和 projection 等
				详情参见 Demo1_2/main.cpp 的 MyGame::onFrame
			*/

			// 至少要填充一下那个后缓存吧
			DoRender();
			return 0;
		}
		break;

	case WM_PAINT:
		{
			_ASSERT(g_ddsurface.get());

			// 这里要做的是将后缓存更新到 windows DC 上
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
			// 推出应用程序指令
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void OnFrame(HWND hwnd)
{
	_ASSERT(IsWindow(hwnd));

	// 渲染一帧
	DoRender();

	// 告知窗口无效，需要更新 windows DC，然后参见 WM_PAINT
	InvalidateRect(hwnd, NULL, FALSE);
}

void DoRender(void)
{
	// 清理后缓存
	g_rc->fillSurface(g_rc->getClipperRect(), t3d::vec3Build<real>(0.8f, 0.8f, 0.8f));

	// 清理 zbuffer
	g_rc->fillZbuffer(g_rc->getClipperRect(), 0);

	/** 注意：
		由于本实例只使用了 t3dlib，没有使用 myGame，所以很多事情做起来十分麻烦
		详情参见 Demo1_2/main.cpp 的 MyGame::onFrame
	*/
}
