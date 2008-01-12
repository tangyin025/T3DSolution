/*
 * File: T3DLIB/t3dlib2.h
 */

#ifndef __T3DLIB_H__
#define __T3DLIB_H__

#include "t3dCommons.h"

#define IS_KEY_DOWN(dikey_state, key)		((dikey_state).state[(key)])

typedef struct DIKEYSTATEV1_TYP
{
	char state[256];

} DIKEYSTATEV1, * DIKEYSTATEV1_PTR;

typedef struct T3DLIB_API DINPUTV1_TYP
{
	LPDIRECTINPUT8A	lpdinput;

	_CTOR_DECLARE(DINPUTV1_TYP);
	_DTOR_DECLARE(DINPUTV1_TYP);

} DINPUTV1, * DINPUTV1_PTR;

typedef struct T3DLIB_API DIMOUSEV1_TYP
{
	LPDIRECTINPUTDEVICE8A lpdimouse;

	_CTOR_DECLARE(DIMOUSEV1_TYP);
	_DTOR_DECLARE(DIMOUSEV1_TYP);

} DIMOUSEV1, * DIMOUSEV1_PTR;

typedef struct T3DLIB_API DIKEYV1_TYP
{
	LPDIRECTINPUTDEVICE8A lpdikey;

	_CTOR_DECLARE(DIKEYV1_TYP);
	_DTOR_DECLARE(DIKEYV1_TYP);

} DIKEYV1, * DIKEYV1_PTR;

typedef struct T3DLIB_API DIJOYV1_TYP
{
	LPDIRECTINPUTDEVICE8A lpdijoy;

	_CTOR_DECLARE(DIJOYV1_TYP);
	_DTOR_DECLARE(DIJOYV1_TYP);

} DIJOYV1, * DIJOYV1_PTR;

typedef struct T3DLIB_API DIJOYINFONODEV1_TYP
{
	static int	joynode_count;
	char		product_name[MAX_BUFFER_SIZE];
	char		instance_name[MAX_BUFFER_SIZE];
	GUID		instance_guid;

	DIJOYINFONODEV1_TYP * next;

} DIJOYINFONODEV1, * DIJOYINFONODEV1_PTR;

T3DLIB_API char * Get_DInput_Error(char * pbuffer, const HRESULT hresult);

T3DLIB_API bool Create_DInput(DINPUTV1 * pdinput, HINSTANCE hinstance);

T3DLIB_API bool Create_DIMouse(DINPUTV1 * pdinput, DIMOUSEV1 * pdimouse);

T3DLIB_API bool Set_DIMouse_Cooperative_Level(DIMOUSEV1 * pdimouse, const HWND hwnd, DWORD level = DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

T3DLIB_API bool Create_DIKey(DINPUTV1 * pdinput, DIKEYV1 * pdikey);

T3DLIB_API bool Set_DIKey_Cooperative_Level(DIKEYV1 * pdikey, const HWND hwnd, DWORD level = DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

T3DLIB_API bool DIEnum_Joysticks(DINPUTV1 * pdinput, LPDIENUMDEVICESCALLBACKA pfunc, LPVOID pdata);

T3DLIB_API bool Create_DIJoy(	DINPUTV1 * pdinput, DIJOYV1 * pdijoy, const HWND hwnd, const DIJOYINFONODEV1 * pnode,
								const int min_x = -255,
								const int max_x =  255,
								const int min_y = -255,
								const int max_y =  255, const int dead_zone = 10);

T3DLIB_API void Destroy_DInput(DINPUTV1 * pdinput);

T3DLIB_API void Destroy_DIMouse(DIMOUSEV1 * pdimouse);

T3DLIB_API void Destroy_DIKey(DIKEYV1 * pdikey);

T3DLIB_API void Destroy_DIJoy(DIJOYV1 * pdijoy);

T3DLIB_API bool Read_DIMouse_State(DIMOUSEV1 * pdimouse, DIMOUSESTATE * pstate);

T3DLIB_API bool Read_DIKey_State(DIKEYV1 * pdikey, DIKEYSTATEV1 * pstate);

T3DLIB_API bool Read_DIJoy_State(DIJOYV1 * pdijoy, DIJOYSTATE * pstate);

#endif // __T3DLIB_H__
