/*
 * File: T3DLIB/t3dheaders.h
 */

#ifndef __T3DHEADERS_H__
#define __T3DHEADERS_H__

#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_DEPRECATE

#include <memory.h>
//#pragma message("memory.h ok")
#include <assert.h>
//#pragma message("assert.h ok")
#include <stdio.h>
//#pragma message("stdio.h ok")
#include <math.h>
//#pragma message("math.h ok")
#include <xmmintrin.h>
//#pragma message("xmmintrin.h ok")
#include <Windows.h>
//#pragma message("windows.h ok")
#pragma warning(disable : 4201)
#include <mmsystem.h>
#pragma warning(default : 4201)
//#pragma message("mmsystem.h ok")
#include <ddraw.h>
//#pragma message("ddraw.h ok")
#include <dinput.h>
//#pragma message("dinput.h ok")
#include <dsound.h>
//#pragma message("dsound.h ok")
#include <dmusici.h>
//#pragma message("dmusici.h ok")
#include <crtdbg.h>
//#pragma message("crtdbg.h ok")

#ifdef T3DLIB_EXPORTS
#pragma comment(lib, "winmm.lib")
//#pragma message("winmm.lib ok")
#pragma comment(lib, "dxguid.lib")
//#pragma message("dxguid.lib ok")
#pragma comment(lib, "ddraw.lib")
//#pragma message("ddraw.lib ok")
#pragma comment(lib, "dinput8.lib")
//#pragma message("dinput8.lib ok")
#pragma comment(lib, "dsound.lib")
//#pragma message("dsound.lib ok")
#endif // T3DLIB_EXPORTS

//#define T3DLIB_DOUBLE_PRECISION

#endif // __T3DHEADERS_H__
