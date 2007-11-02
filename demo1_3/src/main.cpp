/*
 * File: demo1_3/main.cpp
 */

// ////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
// ////////////////////////////////////////////////////////////////////////////////////

#include "t3dPrecompiledHeader.h"
#include "t3dlib1.h"
#include "t3dlib2.h"
#include "t3dlib3.h"
#include "t3dlib4.h"
#include "t3dlib5.h"
#include "t3dlib6.h"
#include "t3dlib7.h"
#include "t3dlib8.h"
#include "t3dlib9.h"
#include "MyApp.h"
#include "MyGame.h"
#pragma comment(lib, "winmm.lib")

// ////////////////////////////////////////////////////////////////////////////////////
// CLASSES
// ////////////////////////////////////////////////////////////////////////////////////

class DemoWindow : public MyWindow
{
protected:
	virtual LRESULT OnProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		return ::DefWindowProc(hwnd, message, wparam, lparam);
	}
};

class DemoApplication : public MyApplication
{
public:
	virtual int run(void)
	{
		rect.left = 0;
		rect.top = 0;
		rect.right = 800;
		rect.bottom = 600;

		wnd = MyWindowPtr(new DemoWindow);
		g_msgArr->addWindow(wnd);

		wnd->SetWindowText("demo1_3");
		wnd->SetClientRect(rect);
		wnd->CenterWindow();

		ddraw = t3dDDrawPtr(new t3dDDraw);

		ddraw->set_coop_level(t3dDDraw::normal);

		prim = ddraw->create_screen_surface();
		prim->set_clipper(ddraw->create_screen_clipper(wnd));

		back = ddraw->create_memory_surface(MyWindow::GetRectWidth(rect), MyWindow::GetRectHeight(rect));
		back->set_clipper(ddraw->create_single_clipper(rect));

		t3d_INIT(prim->get_BPP());

		obj.load("Box1_2.ms3d.txt", "Box01");

		wnd->ShowWindow();

		fps.init();

		return MyApplication::run();
	}

	virtual void OnIdle(void)
	{
		fps.OnFrame();

		back->fill(rect, Create_RGBI(128, 128, 128));

		back->text_out(str_printf("%.2f fps", fps.get_FPS()), 10, 10);

		prim->blit(wnd->GetClientRect(), back, rect);
	}

protected:
	t3dDDrawPtr ddraw;
	t3dSurfacePtr prim;
	t3dSurfacePtr back;

	MyWindowPtr wnd;
	RECT rect;

	t3dFPS fps;
	t3dObject obj;
};

// ////////////////////////////////////////////////////////////////////////////////////
// WinMain
// ////////////////////////////////////////////////////////////////////////////////////

int APIENTRY WinMain(HINSTANCE	hInstance,
					 HINSTANCE	hPrevInstance,
					 LPSTR		lpCmdLine,
					 int		nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try
	{
		DemoApplication app;
		app.run();
	}
	catch(std::exception & e)
	{
		::MessageBoxA(NULL, e.what(), "Exception!", MB_OK);
	}

	return 0;
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
}
