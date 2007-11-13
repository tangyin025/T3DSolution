/*
 * File: demo1_3/main.cpp
 */

// ////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
// ////////////////////////////////////////////////////////////////////////////////////

#include "t3dPrecompiledHeader.h"
#include "MyGame.h"

// ////////////////////////////////////////////////////////////////////////////////////
// CLASSES
// ////////////////////////////////////////////////////////////////////////////////////

// ====================================================================================
// DemoGame
// ====================================================================================

class DemoGame : public MyGame
{
public:
	DemoGame(std::string appName)
		: MyGame(appName)
	{
	}

	~DemoGame()
	{
	}

protected:
	void do_INIT(void)
	{
	}

	void do_DRAW(void)
	{
		//m_back->fill(m_back->m_ddsurface.rect, Create_RGBI(128, 128, 128));
		//m_zbuf->clear();

		m_back->text_out(str_printf("%.1f fps", m_fps->get_FPS()), 10, 10);
	}
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
		DemoGame app("demo1_3");
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
