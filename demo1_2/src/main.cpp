/*
 * File: demo1_2/main.cpp
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

#define DEMO_VERSION		"1_2"
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
char		err_buffer[MAX_BUFFER_SIZE];
char		err_file[MAX_BUFFER_SIZE];
int			err_line;

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

#define ON_ERROR_RETURN(e) \
{ \
	Log_Write("%s, %s, %d\n", (e), __FILE__, __LINE__); \
	if(strlen(Get_Last_Error(err_buffer, err_file, &err_line)) > 0) \
	{ \
		Log_Write("%s, %s, %d\n", err_buffer, err_file, err_line); \
	} \
	return false; \
}

#define FPS_INTERVAL_TIME		(1000)
#define	USE_FLIP_MODE			(0)
#define USE_SYNC_MODE			(0)
#define USE_MEMS_MODE			(1)

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
TEXTDCV1		tdc;
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

BITMAPV1		btmp;
DDSURFACEV1		stmp;
IMAGEV1			texture;
ZBUFFERV1		zbuffer;

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

	INIT_ZERO(fps);
	INIT_ZERO(tdc);
	INIT_ZERO(ddraw);
	INIT_ZERO(ddsprimary);
	INIT_ZERO(ddsback);
	INIT_ZERO(ddcprimary);
	INIT_ZERO(ddcback);
	INIT_ZERO(dinput);
	INIT_ZERO(dimouse);
	INIT_ZERO(dimouse_state);
	INIT_ZERO(dikey);
	INIT_ZERO(dikey_state);
	INIT_ZERO(dsound);
	INIT_ZERO(dmperf);

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

	if(!Init_T3dlib1(ddsprimary.bpp)
		|| !Init_T3dlib4(ddsprimary.bpp)
		|| !Init_T3dlib5(ddsprimary.bpp)
		|| !Init_T3dlib6(ddsprimary.bpp))
		ON_ERROR_RETURN("init t3dlibs failed");

	// ================================================================================
	// TODO: Game init here
	// ================================================================================

	INIT_ZERO(btmp);
	INIT_ZERO(stmp);
	INIT_ZERO(texture);
	INIT_ZERO(zbuffer);

	if(!Create_ZBuffer(&zbuffer, resolutions[resolution_index].width, resolutions[resolution_index].height))
		ON_ERROR_RETURN("create zbuffer failed");

	if(!Create_Bitmap_From_File(&btmp, "heada.bmp"))
		ON_ERROR_RETURN("load bitmap file failed");

	if(!Create_Image(&texture, btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
		ON_ERROR_RETURN("create texture failed");

	if(!Load_Image_From_Bitmap(&texture, &btmp, 0, 0, texture.width, texture.height))
		ON_ERROR_RETURN("load texture failed");

	if(!Create_Memoried_DDSurface(&ddraw, &stmp, btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
		return false;

	SURFACEV1 surf;
	Lock_DDSurface(&stmp, &surf);
	if(!Load_Surface_From_Bitmap(&surf, &btmp, 0, 0, texture.width, texture.height))
		return false;
	Unlock_DDSurface(&stmp);

	Destroy_Bitmap(&btmp);

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

	Destroy_ZBuffer(&zbuffer);
	Destroy_Image(&texture);
	Destroy_DDSurface(&stmp);

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

	if(!Fill_DDSurface(&ddsback, &ddsback.rect, Create_RGBI(150, 150, 200)))
		ON_ERROR_RETURN("fill surface failed");

	SURFACEV1 surf;
	if(!Lock_DDSurface(&ddsback, &surf))
		return false;
//
//	RENDERCONTEXTV1 rc;
//	rc.s_pbuffer = surf.pbuffer;
//	rc.s_pitch = surf.pitch;
//	rc.s_pitch_shift = surf.pitch_shift;
//	rc.s_color_shift = surf.color_shift;
//
//	VERTEXV1 v0, v1, v2, v3;
//	//memset(&v0, 0, sizeof(v0));
//	//memset(&v1, 0, sizeof(v1));
//	//memset(&v2, 0, sizeof(v2));
//	//memset(&v3, 0, sizeof(v3));
//	VECTOR4D_InitXYZW(&v0._4D, 100, 100, 0, 0);
//	VECTOR4D_InitXYZW(&v1._4D, 200, 100, 0, 0);
//	VECTOR4D_InitXYZW(&v2._4D, 200, 200, 0, 0);
//	VECTOR4D_InitXYZW(&v3._4D, 100, 200, 0, 0);
//
//	v0.c_diff = Create_RGBI(255, 0, 0);
//	v1.c_diff = Create_RGBI(255, 0, 0);
//	v2.c_diff = Create_RGBI(255, 0, 0);
//	v3.c_diff = Create_RGBI(255, 0, 0);
//	//rc.c_ambi = Create_RGBI(255, 0, 0);
//
//	Draw_HLine(&rc, &v0, &v1);
//	Draw_VLine(&rc, &v1, &v2);
//	Draw_HLine(&rc, &v2, &v3);
//	Draw_VLine(&rc, &v3, &v0);
//
//	VECTOR3D_Add(&v0._4D._3D, 50);
//	VECTOR3D_Add(&v2._4D._3D, 50);
//	v0.c_diff = Create_RGBI(0, 255, 255);
//	//rc.c_ambi = Create_RGBI(0, 255, 255);
//	//Draw_Rectangle(&rc, &v0, &v2);
//
//	rc.fmin_clip_x = 101.0f;
//	rc.fmax_clip_x = 199.0f;
//	rc.fmin_clip_y = 101.0f;
//	rc.fmax_clip_y = 199.0f;
//	//Draw_Clipped_Rectangle(&rc, &v0, &v2);
//
//	rc.c_src_alpha = Create_RGBI(100, 100, 100);
//	rc.c_dst_alpha = Create_RGBI(155, 155, 155);
//	VECTOR4D_InitXYZW(&v0._4D, 0, 0, 0, 0);
//	VECTOR4D_InitXYZW(&v2._4D, 640, 480, 0, 0);
//	//Draw_Rectangle_SrcAlpha(&rc, &v0, &v2);
//	//Draw_Clipped_Rectangle_SrcAlpha(&rc, &v0, &v2);
//
//	VECTOR4D_InitXYZW(&v0._4D, 150, 50, 0, 0);
//	VECTOR4D_InitXYZW(&v2._4D, 250, 200, 0, 0);
//	////rc.c_ambi = Create_RGBI(255, 255, 255);
//	v0.c_diff = Create_RGBI(255, 255, 255);
//	Draw_Clipped_Line(&rc, &v0, &v2);
//
//	VECTOR4D_InitXYZW(&v0._4D, 150, 150, 0, 0);
//	VECTOR4D_InitXYZW(&v2._4D, 250, 250, 0, 0);
//	v0.c_diff = Create_RGBI(0, 255, 0);
//	Draw_Clipped_HLine_SrcAlpha(&rc, &v0, &v2);
//	Draw_Clipped_VLine_SrcAlpha(&rc, &v0, &v2);
//
//	Clear_ZBuffer(&zbuffer);
//	rc.z_pbuffer		= zbuffer.pbuffer;
//	rc.z_pitch			= zbuffer.pitch;
//	rc.z_pitch_shift	= zbuffer.pitch_shift;
//	rc.z_color_shift	= zbuffer.color_shift;
//	VECTOR4D_InitXYZW(&v0._4D, 100, 200, 100, 0);
//	VECTOR4D_InitXYZW(&v2._4D, 300, 500, 100, 0);
//	v0.c_diff = Create_RGBI(255, 0, 0);
//	//Draw_Line_ZbufferRW(&rc, &v0, &v2);
//	VECTOR4D_InitXYZW(&v0._4D, 100, 200, 200, 0);
//	VECTOR4D_InitXYZW(&v2._4D, 300, 500, 50, 0);
//	v0.c_diff = Create_RGBI(0, 0, 255);
//	//Draw_Line_ZbufferR_SrcAlpha(&rc, &v0, &v2);
//	Draw_Line_ZbufferRW(&rc, &v0, &v2);
//
//	//Wait_For_VSynchronize(&ddraw);
//	//static REAL rz = 200;
//	//if(rz >= 50) rz -= 1;
//	//else rz = 200;
//	//VECTOR4D_InitXYZW(&v0._4D, 100, 200, rz, 0);
//	VECTOR4D_InitXYZW(&v0._4D, 100, 200, 100, 0);
//	VECTOR4D_InitXYZW(&v1._4D, 300, 500, 0, 0);
//	v0.c_diff = Create_RGBI(255, 255, 255);
//	rc.c_src_alpha = Create_RGBI(200, 200, 200);
//	rc.c_dst_alpha = Create_RGBI(55, 55, 55);
////	Draw_Rectangle_ZBufferR_SrcAlpha(&rc, &v0, &v1);
//
//	VECTOR4D_InitXYZW(&v0._4D, 100, 100, 0, 0);
//	VECTOR4D_InitXYZW(&v1._4D, 200, 300, 0, 0);
//	Draw_Clipped_Line_SrcAlpha(&rc, &v0, &v1);
//	//Draw_Line_SrcAlpha(&rc, &v0, &v1);
//
//	VERTEXV1T tv0, tv1;
//	VECTOR4D_InitXYZW(&tv0._4D, 0, 0, 100, 0);
//	VECTOR4D_InitXYZW(&tv1._4D, 800, 600, 0, 0);
//	tv0.u = 0;
//	tv0.v = 0;
//	tv1.u = 1 * FIXP16_MAG * texture.width;
//	tv1.v = 1 * FIXP16_MAG * texture.height;
//	tv0.c_diff = Create_RGBI(255, 255, 255);
//	rc.t_pbuffer		= texture.pbuffer;
//	rc.t_pitch			= texture.pitch;
//	rc.t_pitch_shift	= texture.pitch_shift;
//	rc.z_color_shift	= texture.color_shift;
//	rc.c_src_key		= Create_RGBI(0, 0, 0);
//	//rc.c_src_alpha		= Create_RGBI(255, 255, 255);
//	//rc.c_dst_alpha		= Create_RGBI(0, 0, 0);
//	rc.fmin_clip_x = 101.0f;
//	rc.fmax_clip_x = 599.0f;
//	rc.fmin_clip_y = 101.0f;
//	rc.fmax_clip_y = 499.0f;
//	//Draw_Rectangle_Texture_SrcKey(&rc, &tv0, &tv1);
//	//Draw_Clipped_Rectangle_Texture_SrcKey(&rc, &tv0, &tv1);
////	Draw_Rectangle_ZbufferR_TextureAlpha(&rc, &tv0, &tv1);
//	//Draw_Clipped_Rectangle_ZbufferR_TextureAlpha(&rc, &tv0, &tv1);
//	//Draw_Clipped_Rectangle_Texture_ZBufferW(&rc, &tv0, &tv1);
//	//for(int i = 0; i < texture.height; i++)
//	//	memcpy(rc.s_pbuffer + (i << rc.s_pitch_shift), texture.pbuffer + (i << texture.pitch_shift), texture.width << texture.color_shift);
//
//	//VECTOR2D_InitXY(&rc.v[0]._2D, 200, 200);
//	//VECTOR2D_InitXY(&rc.v[1]._2D, 100, 100);
//	//Draw_HLine(&rc);
//	//Draw_VLine(&rc);
//	//Draw_Rectangle(&rc);
//	//rc.c_diff[0] = Create_RGBI(255, 0, 0);
//	//rc.fmin_clip_x = 101.0f;
//	//rc.fmax_clip_x = 199.0f;
//	//rc.fmin_clip_y = 101.0f;
//	//rc.fmax_clip_y = 199.0f;
//	////VECTOR2D_InitXY(&rc.v[0]._2D, 200, 130);
//	////VECTOR2D_InitXY(&rc.v[1]._2D, 100, 100);
//	////Draw_Clipped_HLine(&rc);
//	////VECTOR2D_InitXY(&rc.v[0]._2D, 130, 200);
//	////VECTOR2D_InitXY(&rc.v[1]._2D, 100, 101);
//	////Draw_Clipped_VLine(&rc);
//	//VECTOR2D_InitXY(&rc.v[0]._2D, 200, 200);
//	//VECTOR2D_InitXY(&rc.v[1]._2D, 101, 101);
//	////Draw_Line(&rc);
//	////Draw_Clipped_Line(&rc);
//	//Draw_Clipped_Rectangle(&rc);
//
//	////VECTOR2D_InitXY(&rc.v[0]._2D, 200, 200);
//	////VECTOR2D_InitXY(&rc.v[1]._2D, 300, 300);
//	////Draw_Line(&rc);
//	////VECTOR2D_InitXY(&rc.v[0]._2D, 300, 300);
//	////VECTOR2D_InitXY(&rc.v[1]._2D, 400, 200);
//	////Draw_Line(&rc);
//	////VECTOR2D_InitXY(&rc.v[0]._2D, 400, 200);
//	////VECTOR2D_InitXY(&rc.v[1]._2D, 200, 200);
//	////Draw_Line(&rc);
//
//	//VECTOR2D_InitXY(&rc.v[0]._2D, 0, 0);
//	//VECTOR2D_InitXY(&rc.v[1]._2D, 640, 480);
//	////rc.c_alpha_src = Create_RGBI(255, 255, 255);
//	////rc.c_alpha_dest = Create_RGBI(0, 0, 0);
//	//rc.c_diff[0] = Create_RGBI(0, 255, 255);
//	//rc.c_src_alpha = Create_RGBI(100, 100, 100);
//	//rc.c_dst_alpha = Create_RGBI(155, 155, 155);
//	//Draw_Rectangle_SrcAlpha(&rc);
//	////Draw_Clipped_Rectangle_SrcAlpha(&rc);
//
//	//for(int i = 0; i < 100000; i++)
//	//{
//	//	float f1 = PI;
//	//	float f3 = 5.5f;
//	//	//float f2 = 1.0f / f1;
//	//	//f3 *= f2;
//	//	//f3 *= f2;
//	//	f3 /= f1;
//	//	f3 /= f1;
//	//}
//
//	//VECTOR4D_InitXYZ(&v0._4D, 300, 300, 0);
//	//VECTOR4D_InitXYZ(&v1._4D, 500, 400, 0);
//	//v0.c_diff = Create_RGBI(255, 0, 0);
//	//v1.c_diff = Create_RGBI(255, 255, 255);
//	//Draw_Line(&rc, &v0, &v1);
//	//Draw_Line(&rc, &v1, &v0);
//
//	//VECTOR4D_InitXYZ(&v0._4D, 300, 300, 0);
//	//VECTOR4D_InitXYZ(&v1._4D, 500, 400, 0);
//	//VECTOR4D_InitXYZ(&v2._4D, 200, 350, 0);
//	//v0.c_diff = Create_RGBI(0, 255, 0);
//	//Draw_Triangle32(&rc, &v0, &v1, &v2);
//
//	//VECTOR4D_InitXYZ(&v0._4D, 300, 300, 0);
//	//VECTOR4D_InitXYZ(&v1._4D, 500, 400, 0);
//	//VECTOR4D_InitXYZ(&v2._4D, 500, 350, 0);
//	//v0.c_diff = Create_RGBI(255, 0, 0);
//	//Draw_Triangle32(&rc, &v0, &v1, &v2);
//
//	VECTOR4D_InitXYZW(&v0._4D, 300, 300, 0, 0);
//	VECTOR4D_InitXYZW(&v1._4D, 500, 300, 0, 0);
//	VECTOR4D_InitXYZW(&v2._4D, 500, 500, 0, 0);
//	VECTOR4D_InitXYZW(&v3._4D, 300, 500, 0, 0);
//	v0.c_diff = Create_RGBI(255, 0, 0);
//	v1.c_diff = Create_RGBI(255, 0, 0);
//	v2.c_diff = Create_RGBI(255, 0, 0);
//	v3.c_diff = Create_RGBI(255, 0, 0);
//	Draw_HLine(&rc, &v0, &v1);
//	Draw_VLine(&rc, &v1, &v2);
//	Draw_HLine(&rc, &v2, &v3);
//	Draw_VLine(&rc, &v3, &v0);
//	rc.fmin_clip_x = v0.x + 1;
//	rc.fmax_clip_x = v2.x - 1;
//	rc.fmin_clip_y = v0.y + 1;
//	rc.fmax_clip_y = v2.y - 1;
//	//rc.fmin_clip_x = 0;
//	//rc.fmax_clip_x = 799;
//	//rc.fmin_clip_y = 0;
//	//rc.fmax_clip_y = 599;
//
//	//VECTOR4D_InitXYZ(&v0._4D, 300, 200, 0);
//	//VECTOR4D_InitXYZ(&v1._4D, 550, 550, 0);
//	//VECTOR4D_InitXYZ(&v2._4D, 200, 350, 0);
//
//	//VECTOR4D_InitXYZ(&v0._4D, 300, 200, 0);
//	//VECTOR4D_InitXYZ(&v1._4D, 200, 550, 0);
//	//VECTOR4D_InitXYZ(&v2._4D, 550, 350, 0);
//	//v0.c_diff = Create_RGBI(0, 0, 0);
//	//Draw_Triangle32(&rc, &v0, &v1, &v2);
//	//v0.c_diff = Create_RGBI(255, 255, 255);
//	//Draw_Clipped_Triangle32(&rc, &v0, &v1, &v2);
//
//	VECTOR4D_InitXYZ(&v0._4D, 300, 250, 0);
//	VECTOR4D_InitXYZ(&v1._4D, 500, 200, 0);
//	VECTOR4D_InitXYZ(&v2._4D, 400, 400, 0);
//	v0.c_diff = Create_RGBI(0, 0, 0);
//	Draw_Triangle32(&rc, &v0, &v1, &v2);
//	v0.c_diff = Create_RGBI(255, 255, 255);
//	Draw_Clipped_Triangle32(&rc, &v0, &v1, &v2);

	static REAL x = 400, y = 300;
	if(IS_KEY_DOWN(dikey_state, DIK_UP))
		y--;
	else if(IS_KEY_DOWN(dikey_state, DIK_DOWN))
		y++;
	if(IS_KEY_DOWN(dikey_state, DIK_LEFT))
		x--;
	else if(IS_KEY_DOWN(dikey_state, DIK_RIGHT))
		x++;

	RENDERCONTEXTV1 rc;
	rc.s_pbuffer = surf.pbuffer;
	rc.s_pitch = surf.pitch;
	rc.s_pitch_shift = surf.pitch_shift;
	rc.s_color_shift = surf.color_shift;

	VERTEXV1T v0, v1, v2, v3;

	VECTOR4D_InitXYZW(&v0._4D, 400 - 100, 300 - 100, 0, 0);
	VECTOR4D_InitXYZW(&v1._4D, 400 + 100, 300 - 100, 0, 0);
	VECTOR4D_InitXYZW(&v2._4D, 400 + 100, 300 + 100, 0, 0);
	VECTOR4D_InitXYZW(&v3._4D, 400 - 100, 300 + 100, 0, 0);
	v0.c_diff = Create_RGBI(255, 0, 0);
	v1.c_diff = Create_RGBI(255, 0, 0);
	v2.c_diff = Create_RGBI(255, 0, 0);
	v3.c_diff = Create_RGBI(255, 0, 0);
	Draw_HLine(&rc, &v0._VERTEXV1, &v1._VERTEXV1);
	Draw_VLine(&rc, &v1._VERTEXV1, &v2._VERTEXV1);
	Draw_HLine(&rc, &v2._VERTEXV1, &v3._VERTEXV1);
	Draw_VLine(&rc, &v3._VERTEXV1, &v0._VERTEXV1);
	rc.fmin_clip_x = v0.x + 1;
	rc.fmax_clip_x = v2.x - 1;
	rc.fmin_clip_y = v0.y + 1;
	rc.fmax_clip_y = v2.y - 1;

	//VECTOR4D_InitXYZW(&v0._4D, 300, 200, 0, 0);
	//VECTOR4D_InitXYZW(&v1._4D, 400, 200, 0, 0);
	//VECTOR4D_InitXYZW(&v2._4D, 300, 100, 0, 0);

	//v0.c_diff = Create_RGBI(255, 255, 0);
	//Draw_Triangle32(&rc, &v0, &v1, &v2);

	rc.t_pbuffer = texture.pbuffer;
	rc.t_pitch = texture.pitch;
	rc.t_pitch_shift = texture.pitch_shift;
	rc.t_color_shift = texture.color_shift;

	Clear_ZBuffer(&zbuffer);
	rc.z_pbuffer		= zbuffer.pbuffer;
	rc.z_pitch			= zbuffer.pitch;
	rc.z_pitch_shift	= zbuffer.pitch_shift;
	rc.z_color_shift	= zbuffer.color_shift;

	const int t_num = 100;
	const int t_rad = 100;

	VECTOR4D_InitXYZW(&v0._4D, x, y, 0, 0);
	v0.u = texture.width * FIXP16_MAG / 2;
	v0.v = texture.height * FIXP16_MAG / 2;

	v1.x = cos(DEG_TO_RAD(0)) * t_rad + v0.x;
	v1.y = sin(DEG_TO_RAD(0)) * t_rad + v0.y;

	v1.u = (FIXP16)((cos(DEG_TO_RAD(0)) + 1) / 2 * texture.width * FIXP16_MAG);
	v1.v = (FIXP16)((sin(DEG_TO_RAD(0)) + 1) / 2 * texture.height * FIXP16_MAG);

	v0.c_diff = Create_RGBI(255, 255, 255);
	v1.c_diff = Create_RGBI(255, 255, 255);
	v2.c_diff = Create_RGBI(255, 255, 255);

	for(int i = 1; i <= t_num; i++)
	{
		v2.x = cos(DEG_TO_RAD((float)i / t_num * 360)) * t_rad + v0.x;
		v2.y = sin(DEG_TO_RAD((float)i / t_num * 360)) * t_rad + v0.y; // note: the y axis was reverted!

		v2.u = (FIXP16)((cos(DEG_TO_RAD((float)i / t_num * 360)) + 1) / 2 * texture.width * FIXP16_MAG);
		v2.v = (FIXP16)((sin(DEG_TO_RAD((float)i / t_num * 360)) + 1) / 2 * texture.height * FIXP16_MAG);

		if(i % 2)
		{
			//Draw_Triangle(&rc, &v0._VERTEXV1, &v1._VERTEXV1, &v2._VERTEXV1);
			Draw_Triangle_Gouraud_Texture_ZBufferRW(&rc, &v0, &v1, &v2);

			//Draw_Clipped_Triangle(&rc, &v0, &v1, &v2);
			//Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW(&rc, &v0, &v1, &v2);
		}

		v1 = v2;
	}

	//VECTOR4D_InitXYZ(&v0._4D, 100, 200, 10);
	//VECTOR4D_InitXYZ(&v1._4D, 300, 400, 10);
	//v0.u = 0, v0.v = 0;
	//v1.u = texture.width * FIXP16_MAG;
	//v1.v = texture.height * FIXP16_MAG;
	//rc.c_src_key = 0;
	//Draw_Rectangle_Texture_ZBufferW(&rc, &v0, &v1);

	////VECTOR4D_InitXYZ(&v0._4D, 400, 200, 0);
	////VECTOR4D_InitXYZ(&v1._4D, 300, 400, 0);
	////VECTOR4D_InitXYZ(&v2._4D, 500, 400, 0);

	////VECTOR4D_InitXYZ(&v0._4D, 400, 10, 500);
	////VECTOR4D_InitXYZ(&v1._4D, 10, 590, 50);
	////VECTOR4D_InitXYZ(&v2._4D, 790, 590, 500);

	////v0.u = texture.width << FIXP16_SHIFT >> 1;
	////v0.v = 0;
	////v1.u = 0;
	////v1.v = texture.height << FIXP16_SHIFT;
	////v2.u = texture.width << FIXP16_SHIFT;
	////v2.v = texture.height << FIXP16_SHIFT;

	//VECTOR4D_InitXYZ(&v0._4D, 10, 200, 500);
	//VECTOR4D_InitXYZ(&v1._4D, 790, 10, 50);
	//VECTOR4D_InitXYZ(&v2._4D, 400, 590, 500);

	//v0.u = 0;
	//v0.v = 0;
	//v1.u = texture.width << FIXP16_SHIFT;
	//v1.v = 0;
	//v2.u = texture.width << FIXP16_SHIFT >> 1;
	//v2.v = texture.height << FIXP16_SHIFT;

	//v0.c_diff = Create_RGBI(255, 0, 0);
	//v1.c_diff = Create_RGBI(0, 255, 0);
	//v2.c_diff = Create_RGBI(0, 0, 255);
	//Draw_Triangle_Gouraud_Texture_ZBufferRW32(&rc, &v0, &v1, &v2);

	Unlock_DDSurface(&ddsback);
	//Blit_DDSurface(&ddsback, &stmp.rect, &stmp, &stmp.rect);

	// ================================================================================
	// END TODO.
	// ================================================================================

	// ================================================================================
	// TODO: Game text here
	// ================================================================================

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
