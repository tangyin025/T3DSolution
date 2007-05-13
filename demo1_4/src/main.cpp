/**
 * File: demo1_4/main.cpp
 */

// ////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
// ////////////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib2.h"
#include "t3dlib3.h"
#include "t3dlib4.h"
#include "t3dlib5.h"
#include "t3dlib6.h"
#include "t3dlib7.h"
#include "t3dlib8.h"
#include "t3dlib9.h"
#pragma comment(lib, "winmm.lib")

// ////////////////////////////////////////////////////////////////////////////////////
// DEFINES
// ////////////////////////////////////////////////////////////////////////////////////

#define DEMO_VERSION		"1_4"
#define CLASS_NAME			"DEMO" DEMO_VERSION
#define WND_NAME			"demo" DEMO_VERSION

#define BPP_TYPE_16BIT		(16)
#define BPP_TYPE_32BIT		(32)
#define BPP_TYPE_WND		(0)
#define DEFAULT_RESOLUTION	(5) // 5 - 800 x 600 x win

// ////////////////////////////////////////////////////////////////////////////////////
// TYPES
// ////////////////////////////////////////////////////////////////////////////////////

typedef struct RESOLUTION_TYP
{
	int	width;
	int height;
	int bpp_type;

} RESOLUTION, * RESOLUTION_PTR;

static const RESOLUTION resolutions[] =
{
	{ 640,	480,	BPP_TYPE_16BIT,	},	// 0
	{ 640,	480,	BPP_TYPE_32BIT,	},	// 1
	{ 640,	480,	BPP_TYPE_WND,	},	// 2

	{ 800,	600,	BPP_TYPE_16BIT,	},	// 3
	{ 800,	600,	BPP_TYPE_32BIT,	},	// 4
	{ 800,	600,	BPP_TYPE_WND,	},	// 5

	{ 1024,	768,	BPP_TYPE_16BIT,	},	// 6
	{ 1024,	768,	BPP_TYPE_32BIT,	},	// 7
	{ 1024,	768,	BPP_TYPE_WND,	},	// 8

	{ 1280,	1024,	BPP_TYPE_16BIT,	},	// 9
	{ 1280,	1024,	BPP_TYPE_32BIT,	},	// 10
	{ 1280,	1024,	BPP_TYPE_WND,	},	// 11
};

// ////////////////////////////////////////////////////////////////////////////////////
// PREDECLARES
// ////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

bool				Log_Open(char * fname);
bool				Log_Write(char * format, ...);
void				Log_Close(void);

bool				Game_Init(void);
void				Game_Destroy(void);
bool				Game_Frame(void);

// ////////////////////////////////////////////////////////////////////////////////////
// GLOBALS
// ////////////////////////////////////////////////////////////////////////////////////

int			resolution_index;
FILE *		log_file			= NULL;

HWND		wnd_handle;
SIZE		wnd_offset;
SIZE		client_offset;

DWORD		wnd_style			= WS_OVERLAPPEDWINDOW;
DWORD		wnd_style_full		= WS_POPUP | WS_VISIBLE;
DWORD		wnd_exstyle			= 0;
DWORD		wnd_exstyle_full	= WS_EX_TOPMOST;

// ////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTS
// ////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------
// WinMain
// ------------------------------------------------------------------------------------

int APIENTRY WinMain(HINSTANCE	hInstance,
					 HINSTANCE	hPrevInstance,
					 LPSTR		lpCmdLine,
					 int		nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		NULL,
		//(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	RegisterClassEx(&wc);

	wnd_handle = CreateWindowEx(wnd_exstyle, CLASS_NAME, WND_NAME, wnd_style,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if(wnd_handle == NULL)
	{
		UnregisterClass(CLASS_NAME, hInstance);
		return 1;
	}

	if(!Game_Init())
	{
		Game_Destroy();
		UnregisterClass(CLASS_NAME, hInstance);
		return 2;
	}

	ShowWindow(wnd_handle, nCmdShow);
	UpdateWindow(wnd_handle);
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//WaitMessage();
			if(!Game_Frame())
				PostMessage(wnd_handle, WM_DESTROY, NULL, NULL);
		}
	}

	UnregisterClass(CLASS_NAME, hInstance);
	return (int)msg.wParam;
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
}

// ------------------------------------------------------------------------------------
// WinProc
// ------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch(message)
	{
	case WM_DESTROY:
		Game_Destroy();
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
	return 0;
}

// ------------------------------------------------------------------------------------
// Log_Open
// ------------------------------------------------------------------------------------

bool Log_Open(char * fname)
{
	if(NULL == (log_file = fopen(fname, "w")))
		return false;
	return true;
}

// ------------------------------------------------------------------------------------
// Log_Write
// ------------------------------------------------------------------------------------

bool Log_Write(char * format, ...)
{
	va_list arg_list;
	int res;

	va_start(arg_list, format);
	res = vfprintf(log_file, format, arg_list);
	va_end(arg_list);

	if(res >= 0)
	{
		fflush(log_file);
		return true;
	}
	return false;
}

// ------------------------------------------------------------------------------------
// Log_Close
// ------------------------------------------------------------------------------------

void Log_Close(void)
{
	if(log_file != NULL)
		fclose(log_file);
}

// ////////////////////////////////////////////////////////////////////////////////////
// DEFINES
// ////////////////////////////////////////////////////////////////////////////////////

#define ON_ERROR_RETURN(e)		{	Log_Write("%s, %s, %d\n", \
											(e), __FILE__, __LINE__); \
									if(strlen(gerror.message) > 0) { Log_Write("%s, %s, %d\n", \
										gerror.message, gerror.file, gerror.line); } return false; }

#define FPS_INTERVAL_TIME		(1000)
#define	USE_FLIP_MODE			(0)
#define USE_SYNC_MODE			(0)
#define USE_MEMS_MODE			(0)

// ////////////////////////////////////////////////////////////////////////////////////
// TYPES
// ////////////////////////////////////////////////////////////////////////////////////

typedef struct FPSV1_TYP
{
	unsigned int	last_time;
	unsigned int	pass_time;
	unsigned int	frames;
	float			fps;

	FPSV1_TYP()
	{
		memset(this, 0, sizeof(*this));
	}

	~FPSV1_TYP()
	{
		;
	}

} FPSV1, * FPSV1_PTR;

// ////////////////////////////////////////////////////////////////////////////////////
// GLOBALS
// ////////////////////////////////////////////////////////////////////////////////////

FPSV1			fps;
DDRAWV1			ddraw;
DDSURFACEV1		ddsprimary;
DDSURFACEV1		ddsback;
DDCLIPPERV1		ddcprimary;
DDCLIPPERV1		ddcback;
DINPUTV1		dinput;
DIMOUSEV1		dimouse;
DIMOUSESTATE	dimouse_state;
DIKEYV1			dikey;
DIKEYSTATEV1	dikey_state;
DSOUNDV1		dsound;
DMPERFORMANCEV1	dmperf;

// ================================================================================
// TODO: Game define here
// ================================================================================

// ================================================================================
// END TODO.
// ================================================================================

// ////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTS
// ////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------
// Game_Init
// ------------------------------------------------------------------------------------

bool Game_Init(void)
{
	/**********************************************************************************
	 * Config file format:					|	Config file example:
	 *										|	File: Config.ini
	 * [CLASS_NAME]							|	[DEMO1_2]
	 * config_name=config_value				|	resolution=5
	 * ...									|
	 * [EOF]								|	[EOF]
	 **********************************************************************************/

	char szConfigFile[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, szConfigFile);
	strcat(szConfigFile, "Config.ini");
	resolution_index = GetPrivateProfileInt(WND_NAME,
			"resolution", DEFAULT_RESOLUTION, szConfigFile);

	// ================================================================================
	// TODO: Game config here
	// ================================================================================

	// ================================================================================
	// END TODO.
	// ================================================================================

	assert(resolution_index >= 0
			&& resolution_index < sizeof(resolutions) / sizeof(RESOLUTION));

	if(!Log_Open(WND_NAME ".log"))
		return false;

	if(!Create_DDraw(&ddraw))
		ON_ERROR_RETURN("create ddraw failed");

	if(resolutions[resolution_index].bpp_type == BPP_TYPE_WND)
	{
		if(0 == SetWindowLong(wnd_handle, GWL_STYLE, wnd_style))
			ON_ERROR_RETURN("set window style failed");

		if(0 == SetWindowLong(wnd_handle, GWL_EXSTYLE, wnd_exstyle))
			ON_ERROR_RETURN("set window style failed");

		RECT rect = {0, 0, resolutions[resolution_index].width, resolutions[resolution_index].height};
		if(0 == AdjustWindowRectEx(&rect, wnd_style, GetMenu(wnd_handle) != NULL, wnd_exstyle))
			ON_ERROR_RETURN("adjust window rect failed");

		client_offset.cx = -rect.left;
		client_offset.cy = -rect.top;

		RECT desk;
		int wx, wy;
		GetWindowRect(GetDesktopWindow(), &desk);
		wx = ((desk.right - desk.left) - (rect.right - rect.left)) / 2;
		wy = ((desk.bottom - desk.top) - (rect.bottom - rect.top)) / 2;
		if(0 == SetWindowPos(wnd_handle, HWND_TOP, wx, wy, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW))
			ON_ERROR_RETURN("set window position failed");

		if(!Set_Normal_Cooperative_Level(&ddraw))
			ON_ERROR_RETURN("set cooperative level failed");

		if(!Create_Windowed_DDSurface(&ddraw, &ddsprimary))
			ON_ERROR_RETURN("create window surface failed");

		if(!Create_Windowed_DDClipper(&ddraw, &ddcprimary, wnd_handle))
			ON_ERROR_RETURN("create window clipper failed");

		if(!Attach_DDSurface_DDClipper(&ddsprimary, &ddcprimary))
			ON_ERROR_RETURN("attach window clipper failed");

#if USE_MEMS_MODE
		if(!Create_Memoried_DDSurface(&ddraw, &ddsback,
				resolutions[resolution_index].width, resolutions[resolution_index].height))
#else
		if(!Create_Videoied_DDSurface(&ddraw, &ddsback,
				resolutions[resolution_index].width, resolutions[resolution_index].height))
#endif // USE_MEMS_MODE
			ON_ERROR_RETURN("create memory surface failed");
	}
	else
	{
		if(0 == SetWindowLong(wnd_handle, GWL_STYLE, wnd_style_full))
			ON_ERROR_RETURN("set window style failed");

		RECT rect = {0, 0, resolutions[resolution_index].width, resolutions[resolution_index].height};
		if(0 == AdjustWindowRectEx(&rect, wnd_style, GetMenu(wnd_handle) != NULL, wnd_exstyle))
			ON_ERROR_RETURN("adjust window rect failed");

		client_offset.cx = 0;
		client_offset.cy = 0;

		if(0 == SetWindowPos(wnd_handle, HWND_TOPMOST, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW))
			ON_ERROR_RETURN("set window position failed");

		if(!Set_Fullscreen_Cooperative_Level(&ddraw, wnd_handle))
			ON_ERROR_RETURN("set cooperative level failed");

		if(!Set_Display_Model(&ddraw,
				resolutions[resolution_index].width,
				resolutions[resolution_index].height,
				resolutions[resolution_index].bpp_type))
			ON_ERROR_RETURN("set display mode failed");

#if USE_FLIP_MODE
		if(!Create_Fullscreen_DDSurface(&ddraw, &ddsprimary, &ddsback))
			ON_ERROR_RETURN("create full screen surfaces failed");
#else
		if(!Create_Windowed_DDSurface(&ddraw, &ddsprimary))
			ON_ERROR_RETURN("create window surface failed");

#if USE_MEMS_MODE
		if(!Create_Memoried_DDSurface(&ddraw, &ddsback,
				resolutions[resolution_index].width, resolutions[resolution_index].height))
#else
		if(!Create_Videoied_DDSurface(&ddraw, &ddsback,
				resolutions[resolution_index].width, resolutions[resolution_index].height))
#endif // USE_MEMS_MODE
			ON_ERROR_RETURN("create memory surface failed");
#endif // USE_FLIP_MODE
	}

	if(!Create_Memoried_DDClipper(&ddraw, &ddcback, &ddsback.rect, 1))
		ON_ERROR_RETURN("create memory clipper failed");

	if(!Attach_DDSurface_DDClipper(&ddsback, &ddcback))
		ON_ERROR_RETURN("attach memory clipper failed");

	if(!Create_DInput(&dinput, GetModuleHandle(NULL)))
		ON_ERROR_RETURN("create direct input failed");

	if(!Create_DIMouse(&dinput, &dimouse, wnd_handle))
		ON_ERROR_RETURN("create mouse input failed");

	if(!Create_DIKey(&dinput, &dikey, wnd_handle))
		ON_ERROR_RETURN("create keyboard input failed");

	if(!Create_DSound(&dsound, wnd_handle))
		ON_ERROR_RETURN("create direct sound failed");

	if(!Create_DMPerformance(&dsound, &dmperf, wnd_handle))
		ON_ERROR_RETURN("create direct music perf failed");

	if(!Init_T3dlib1(ddsprimary.bpp))
		ON_ERROR_RETURN("init t3dlib1 failed");

	// ================================================================================
	// TODO: Game init here
	// ================================================================================

	// ================================================================================
	// END TODO.
	// ================================================================================

	return true;
}

// ------------------------------------------------------------------------------------
// Game_Destroy
// ------------------------------------------------------------------------------------

void Game_Destroy(void)
{
	// ================================================================================
	// TODO: Game destroy here
	// ================================================================================

	// ================================================================================
	// END TODO.
	// ================================================================================

	Destroy_DMPerformance(&dmperf);
	Destroy_DSound(&dsound);
	Destroy_DIKey(&dikey);
	Destroy_DIMouse(&dimouse);
	Destroy_DInput(&dinput);
	Destroy_DDClipper(&ddcback);
	Destroy_DDSurface(&ddsback);
	Destroy_DDClipper(&ddcprimary);
	Destroy_DDSurface(&ddsprimary);
	Destroy_DDraw(&ddraw);
	Log_Close();
}

// ------------------------------------------------------------------------------------
// Game_Frame
// ------------------------------------------------------------------------------------

bool Game_Frame(void)
{
	if(!Read_DIMouse_State(&dimouse, &dimouse_state))
		ON_ERROR_RETURN("read mouse state failed");

	if(!Read_DIKey_State(&dikey, &dikey_state))
		ON_ERROR_RETURN("read keyboard state failed");

	if(IS_KEY_DOWN(dikey_state, DIK_ESCAPE))
		return false;

	unsigned int curr_time = timeGetTime();
	fps.pass_time += curr_time - fps.last_time;
	fps.last_time = curr_time;
	fps.frames++;
	if(fps.pass_time > FPS_INTERVAL_TIME)
	{
		fps.fps			= (float)fps.frames / (float)fps.pass_time * 1000.0f;
		fps.pass_time	= 0;
		fps.frames		= 0;
	}

	// ================================================================================
	// TODO: Game logic here
	// ================================================================================

	// ================================================================================
	// END TODO.
	// ================================================================================

	// ================================================================================
	// TODO: Game render here
	// ================================================================================

	//if(!Fill_DDSurface(&ddsback, &ddsback.rect, Create_RGBI(150, 150, 200)))
	//	ON_ERROR_RETURN("fill surface failed");

	// ================================================================================
	// END TODO.
	// ================================================================================

	// ================================================================================
	// TODO: Game text here
	// ================================================================================

	TEXTDCV1 tdc;
	char buffer[MAX_PATH];
	if(!Begin_Text_DC(&ddsback, &tdc))
		ON_ERROR_RETURN("begin text dc failed");
	Set_Text_BKColor(&tdc, RGB(255, 255, 255));
	Set_Text_BKMode(&tdc, TEXT_BKMODE_OPAQUE);
	Set_Text_Color(&tdc, RGB(0, 0, 0));
	sprintf(buffer, "%.1f fps", fps.fps);
	Text_Out(&tdc, buffer, 10, 10);
	End_Text_DC(&tdc);

	// ================================================================================
	// END TODO.
	// ================================================================================

	if(resolutions[resolution_index].bpp_type == BPP_TYPE_WND)
	{
#if USE_SYNC_MODE
		if(!Wait_For_VSynchronize(&ddraw))
			ON_ERROR_RETURN("wait sync failed");
#endif // USE_SYNC_MODE

		RECT rect;
		RECT client;
		GetWindowRect(wnd_handle, &rect);
		GetClientRect(wnd_handle, &client);
		OffsetRect(&client, rect.left + client_offset.cx, rect.top + client_offset.cy);
		//if(!Blit_DDSurface_Fast(&ddsprimary, client.left, client.top, &ddsback, &ddsback.rect))
		if(!Blit_DDSurface(&ddsprimary, &client, &ddsback, &ddsback.rect))
			ON_ERROR_RETURN("blit surface failed");
	}
	else
	{
#if USE_FLIP_MODE
		if(!Flip_DDSurface(&ddsprimary))
			ON_ERROR_RETURN("flit surface failed");
#else
#if USE_SYNC_MODE
		if(!Wait_For_VSynchronize(&ddraw))
			ON_ERROR_RETURN("wait sync failed");
#endif // USE_SYNC_MODE

		if(!Blit_DDSurface_Fast(&ddsprimary, 0, 0, &ddsback, &ddsback.rect))
		//if(!Blit_DDSurface(&ddsprimary, &ddsprimary.rect, &ddsback, &ddsback.rect))
			ON_ERROR_RETURN("blit surface failed");
#endif // USE_FLIP_MODE
	}
	return true;
}
