/* FILE: main.cpp
	定义了一个基本的 t3dlib 应用程序的框架，适用于 win32 或 mfc 应用程序
*/

#include <t3dlib1.h>	// ddraw 封装
#include <t3dlib8.h>	// 渲染上下文

#pragma comment(lib, "winmm.lib") // windows 媒体库

using t3d::real;

#ifdef _DEBUG
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__ )
#endif

// ----------------------------------------------------------------------------------------------------
// 全局变量
// ----------------------------------------------------------------------------------------------------

TCHAR szWindowClass[] = _T("SAMPLE");	// 窗口类
t3d::DDrawPtr g_ddraw;					// direct draw
t3d::DDSurfacePtr g_ddsurface;			// direct draw surface，用作后缓存
t3d::ZBufferPtr g_zbuffer;				// zbuffer
t3d::RenderContextPtr g_rc;				// 渲染上下文

// ----------------------------------------------------------------------------------------------------
// 预定义函数
// ----------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void OnFrame(void);

void BltBacksurfaceToDC(HDC hdc, const CRect & rect);

// ----------------------------------------------------------------------------------------------------
// _tWinMain
// ----------------------------------------------------------------------------------------------------

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
	wcex.hbrBackground = NULL; // (HBRUSH)(COLOR_WINDOW+1)
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(NULL, IDC_ICON);
	RegisterClassEx(&wcex);

	// 获得可执行文件名
	TCHAR szModuleFileName[MAX_PATH];
	GetModuleFileName(NULL, szModuleFileName, sizeof(szModuleFileName) / sizeof(szModuleFileName[0]));

	try
	{
		// 创建窗口
		HWND hWnd = CreateWindow(szWindowClass, szModuleFileName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
		if(hWnd)
		{
			// 显示及更新窗口
			ShowWindow(hWnd, nCmdShow);
			UpdateWindow(hWnd);

			// 进入消息循环
			MSG msg;
			msg.message = ~(UINT)WM_QUIT;
			while(msg.message != WM_QUIT)
			{
				// 取出一个消息
				if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					// 转换及分发消息
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					// 渲染一帧
					OnFrame();

					// 直接更新窗口 client 区域，没有必要再弄个 OnPaint 了
					HDC hdc = GetDC(hWnd);
					CRect rect;
					GetClientRect(hWnd, &rect);
					BltBacksurfaceToDC(hdc, rect);
					ReleaseDC(hWnd, hdc);
				}
			}
		}
	}
	catch(t3d::Exception & e)
	{
		// 报告异常信息
		::MessageBox(NULL, e.getFullDesc().c_str(), _T("Exception"), MB_OK);
	}

	return 0;
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(hPrevInstance);
}

// ----------------------------------------------------------------------------------------------------
// WndProc
// ----------------------------------------------------------------------------------------------------

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
			if(ddsd.ddpfPixelFormat.dwRGBBitCount == 16
				&& ddsd.ddpfPixelFormat.dwRBitMask == RGB16_RED_MASK
				&& ddsd.ddpfPixelFormat.dwGBitMask == RGB16_GREEN_MASK
				&& ddsd.ddpfPixelFormat.dwBBitMask == RGB16_BLUE_MASK)
			{
				g_rc = t3d::RenderContextPtr(new t3d::RenderContext16());
			}
			else if(ddsd.ddpfPixelFormat.dwRGBBitCount == 32
				&& ddsd.ddpfPixelFormat.dwRBitMask == RGB32_RED_MASK
				&& ddsd.ddpfPixelFormat.dwGBitMask == RGB32_GREEN_MASK
				&& ddsd.ddpfPixelFormat.dwBBitMask == RGB32_BLUE_MASK)
			{
				g_rc = t3d::RenderContextPtr(new t3d::RenderContext32());
			}
			else
			{
				T3D_CUSEXCEPT(_T("unsupported pixel format"));
			}

			return 0;
		}

	case WM_SIZE:
		if((SIZE_RESTORED == wParam || SIZE_MAXIMIZED == wParam) && g_ddraw.get())
		{
			// 渲染上下文必须被创建
			_ASSERT(g_ddraw);
			_ASSERT(g_rc);

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

			// 注意：
			// 其实在这个地方还有很多事情要做，如更新相机的 viewport 和 projection 等
			// 详情参见 Demo1_2/main.cpp 的 MyGameBase::onFrame

			// 设置窗口区域无效，将有后缓存更新
			InvalidateRect(hWnd, NULL, FALSE);
			return 0;
		}
		break;

	case WM_PAINT:
		{
			// 后缓存必须已经被创建
			_ASSERT(g_ddsurface);

			// 这里要做的是将后缓存更新到 windows DC 上
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			CRect rect;
			GetClientRect(hWnd, &rect);
			BltBacksurfaceToDC(hdc, rect);
			EndPaint(hWnd, &ps);
			return 0;
		}

	case WM_DESTROY:
		{
			// 退出应用程序指令
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

// ----------------------------------------------------------------------------------------------------
// OnFrame
// ----------------------------------------------------------------------------------------------------

void OnFrame(void)
{
	// 清理后缓存
	g_rc->fillSurface(g_rc->getClipperRect(), t3d::vec3Build<real>(0.8f, 0.8f, 0.8f));

	// 清理 zbuffer
	g_rc->fillZbuffer(g_rc->getClipperRect(), 0);

	// 注意：
	// 由于本实例只使用了 t3dlib，没有使用 myGame，所以很多事情做起来十分麻烦
	// 详情参见 Demo1_2/main.cpp 的 MyGameBase::onFrame

	// 用于计算 fps 的集合
	static DWORD last_time = ::timeGetTime();
	static DWORD past_time = 0;
	static DWORD past_frames = 0;
	static real fps = 0;

	// 平均采样法计算 fps
	DWORD curr_time = ::timeGetTime();
	past_time += curr_time - last_time;
	past_frames += 1;
	if(past_time > 1000)
	{
		fps = (real)past_frames / (real)past_time * 1000;
		past_time = 0;
		past_frames = 0;
	}
	last_time = curr_time;

	// 输出 fps
	TCHAR buffer[MAX_PATH];
	_stprintf_s(buffer, _T("fps: %.1f"), fps);
	HDC hdc = g_ddsurface->getDC();
	::TextOut(hdc, 10, 10, buffer, _tcslen(buffer));
	g_ddsurface->releaseDC(hdc);
}

// ----------------------------------------------------------------------------------------------------
// BltBacksurfaceToDC
// ----------------------------------------------------------------------------------------------------

void BltBacksurfaceToDC(HDC hdc, const CRect & rect)
{
	// 将后缓存的内容复制到指定 dc
	HDC hdcSrc = g_ddsurface->getDC();
	BitBlt(hdc, rect.left, rect.top, rect.Width(), rect.Height(), hdcSrc, 0, 0, SRCCOPY);
	g_ddsurface->releaseDC(hdcSrc);
}
