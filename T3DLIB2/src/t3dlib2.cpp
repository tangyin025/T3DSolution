/*
 * File: T3DLIB2/t3dlib2.cpp
 */

#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib2.h"

#define GET_DINPUT_ERROR(h)		(Get_DInput_Error(gbuffer, (h)))
#define CARE_UNACQUIRE(o)		{ if((o) != NULL) { (o)->Unacquire(); } }

_CTOR_IMPLEMENT(DINPUTV1_TYP);
_DTOR_IMPLEMENT_W1(DINPUTV1_TYP, Destroy_DInput, lpdinput);

_CTOR_IMPLEMENT(DIMOUSEV1_TYP);
_DTOR_IMPLEMENT_W1(DIMOUSEV1_TYP, Destroy_DIMouse, lpdimouse);

_CTOR_IMPLEMENT(DIKEYV1_TYP);
_DTOR_IMPLEMENT_W1(DIKEYV1_TYP, Destroy_DIKey, lpdikey);

_CTOR_IMPLEMENT(DIJOYV1_TYP);
_DTOR_IMPLEMENT_W1(DIJOYV1_TYP, Destroy_DIJoy, lpdijoy);

T3DLIB_API char * Get_DInput_Error(char * pbuffer, const HRESULT hresult)
{
	char * pmsg = "no message";
	switch(hresult)
	{
	case DI_BUFFEROVERFLOW:
		pmsg = "DI_BUFFEROVERFLOW"; break;
	case DI_DOWNLOADSKIPPED:
		pmsg = "DI_DOWNLOADSKIPPED"; break;
	case DI_EFFECTRESTARTED:
		pmsg = "DI_EFFECTRESTARTED"; break;
	//case DI_NOEFFECT:
	//	pmsg = "DI_NOEFFECT"; break;
	//case DI_NOTATTACHED:
	//	pmsg = "DI_NOTATTACHED"; break;
	case DI_OK:
		pmsg = "DI_OK"; break;
	case DI_POLLEDDEVICE:
		pmsg = "DI_POLLEDDEVICE"; break;
	//case DI_PROPNOEFFECT:
	//	pmsg = "DI_PROPNOEFFECT"; break;
	case DI_SETTINGSNOTSAVED:
		pmsg = "DI_SETTINGSNOTSAVED"; break;
	case DI_TRUNCATED:
		pmsg = "DI_TRUNCATED"; break;
	case DI_TRUNCATEDANDRESTARTED:
		pmsg = "DI_TRUNCATEDANDRESTARTED"; break;
	case DI_WRITEPROTECT:
		pmsg = "DI_WRITEPROTECT"; break;
	case DIERR_ACQUIRED:
		pmsg = "DIERR_ACQUIRED"; break;
	case DIERR_ALREADYINITIALIZED:
		pmsg = "DIERR_ALREADYINITIALIZED"; break;
	case DIERR_BADDRIVERVER:
		pmsg = "DIERR_BADDRIVERVER"; break;
	case DIERR_BETADIRECTINPUTVERSION:
		pmsg = "DIERR_BETADIRECTINPUTVERSION"; break;
	case DIERR_DEVICEFULL:
		pmsg = "DIERR_DEVICEFULL"; break;
	case DIERR_DEVICENOTREG:
		pmsg = "DIERR_DEVICENOTREG"; break;
	case DIERR_EFFECTPLAYING:
		pmsg = "DIERR_EFFECTPLAYING"; break;
	case DIERR_GENERIC:
		pmsg = "DIERR_GENERIC"; break;
	case DIERR_HANDLEEXISTS:
		pmsg = "DIERR_HANDLEEXISTS"; break;
	case DIERR_HASEFFECTS:
		pmsg = "DIERR_HASEFFECTS"; break;
	case DIERR_INCOMPLETEEFFECT:
		pmsg = "DIERR_INCOMPLETEEFFECT"; break;
	case DIERR_INPUTLOST:
		pmsg = "DIERR_INPUTLOST"; break;
	case DIERR_INVALIDPARAM:
		pmsg = "DIERR_INVALIDPARAM"; break;
	case DIERR_MAPFILEFAIL:
		pmsg = "DIERR_MAPFILEFAIL"; break;
	case DIERR_MOREDATA:
		pmsg = "DIERR_MOREDATA"; break;
	case DIERR_NOAGGREGATION:
		pmsg = "DIERR_NOAGGREGATION"; break;
	case DIERR_NOINTERFACE:
		pmsg = "DIERR_NOINTERFACE"; break;
	case DIERR_NOTACQUIRED:
		pmsg = "DIERR_NOTACQUIRED"; break;
	case DIERR_NOTBUFFERED:
		pmsg = "DIERR_NOTBUFFERED"; break;
	case DIERR_NOTDOWNLOADED:
		pmsg = "DIERR_NOTDOWNLOADED"; break;
	case DIERR_NOTEXCLUSIVEACQUIRED:
		pmsg = "DIERR_NOTEXCLUSIVEACQUIRED"; break;
	case DIERR_NOTFOUND:
		pmsg = "DIERR_NOTFOUND"; break;
	case DIERR_NOTINITIALIZED:
		pmsg = "DIERR_NOTINITIALIZED"; break;
	//case DIERR_OBJECTNOTFOUND:
	//	pmsg = "DIERR_OBJECTNOTFOUND"; break;
	case DIERR_OLDDIRECTINPUTVERSION:
		pmsg = "DIERR_OLDDIRECTINPUTVERSION"; break;
	//case DIERR_OTHERAPPHASPRIO:
	//	pmsg = "DIERR_OTHERAPPHASPRIO"; break;
	case DIERR_OUTOFMEMORY:
		pmsg = "DIERR_OUTOFMEMORY"; break;
	//case DIERR_READONLY:
	//	pmsg = "DIERR_READONLY"; break;
	case DIERR_REPORTFULL:
		pmsg = "DIERR_REPORTFULL"; break;
	case DIERR_UNPLUGGED:
		pmsg = "DIERR_UNPLUGGED"; break;
	case DIERR_UNSUPPORTED:
		pmsg = "DIERR_UNSUPPORTED"; break;
	case E_HANDLE:
		pmsg = "E_HANDLE"; break;
	case E_PENDING:
		pmsg = "E_PENDING"; break;
	case E_POINTER:
		pmsg = "E_POINTER"; break;
	default:
		//_ASSERT(0);
		pmsg = "unknown dinput error result"; break;
	}
	return strcpy(pbuffer, pmsg);
}

T3DLIB_API bool Create_DInput(DINPUTV1 * pdinput, HINSTANCE hinstance)
{
	assert(pdinput->lpdinput == NULL);

	if(FAILED(gresult = DirectInput8Create(
			hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID *)&pdinput->lpdinput, NULL)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Create_DIMouse(DINPUTV1 * pdinput, DIMOUSEV1 * pdimouse, const HWND hwnd)
{
	assert(pdimouse->lpdimouse == NULL);

	LPDIRECTINPUTDEVICE8A lpdimouse;
	if(FAILED(gresult = pdinput->lpdinput->CreateDevice(GUID_SysMouse, &lpdimouse, NULL)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	if(FAILED(gresult = lpdimouse->SetDataFormat(&c_dfDIMouse)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	if(FAILED(gresult = lpdimouse->SetCooperativeLevel(
			hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	if(FAILED(gresult = lpdimouse->Acquire()))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	pdimouse->lpdimouse = lpdimouse;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpdimouse);
	return false;
}

T3DLIB_API bool Create_DIKey(DINPUTV1 * pdinput, DIKEYV1 * pdikey, const HWND hwnd)
{
	assert(pdikey->lpdikey == NULL);

	LPDIRECTINPUTDEVICE8A lpdikey;
	if(FAILED(gresult = pdinput->lpdinput->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	if(FAILED(gresult = lpdikey->SetDataFormat(&c_dfDIKeyboard)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	if(FAILED(gresult = lpdikey->SetCooperativeLevel(
			hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	if(FAILED(gresult = lpdikey->Acquire()))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	pdikey->lpdikey = lpdikey;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpdikey);
	return false;
}

T3DLIB_API bool DIEnum_Joysticks(DINPUTV1 * pdinput, LPDIENUMDEVICESCALLBACKA pfunc, LPVOID pdata)
{
	if(FAILED(gresult = pdinput->lpdinput->EnumDevices(
			DI8DEVCLASS_GAMECTRL, pfunc, pdata, DIEDFL_ATTACHEDONLY)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Create_DIJoy(	DINPUTV1 * pdinput, DIJOYV1 * pdijoy, const HWND hwnd, const DIJOYINFONODEV1 * pnode,
								const int min_x /*= -256*/,
								const int max_x /*=  256*/,
								const int min_y /*= -256*/,
								const int max_y /*=  256*/, const int dead_zone /*= 10*/)
{
	LPDIRECTINPUTDEVICE8A lpdijoy = NULL;
	if(FAILED(gresult = pdinput->lpdinput->CreateDevice(pnode->instance_guid, &lpdijoy, NULL)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	if(FAILED(gresult = lpdijoy->SetDataFormat(&c_dfDIJoystick)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	if(FAILED(gresult = lpdijoy->SetCooperativeLevel(
			hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	DIPROPRANGE joy_axis_range;
	ZeroMemory(&joy_axis_range, sizeof(joy_axis_range));
	joy_axis_range.lMin					= min_x;
	joy_axis_range.lMax					= max_x;
	joy_axis_range.diph.dwSize			= sizeof(DIPROPRANGE); 
	joy_axis_range.diph.dwHeaderSize	= sizeof(DIPROPHEADER); 
	joy_axis_range.diph.dwObj			= DIJOFS_X;
	joy_axis_range.diph.dwHow			= DIPH_BYOFFSET;
	if(FAILED(gresult = lpdijoy->SetProperty(DIPROP_RANGE, &joy_axis_range.diph)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	ZeroMemory(&joy_axis_range, sizeof(joy_axis_range));
	joy_axis_range.lMin					= min_y;
	joy_axis_range.lMax					= max_y;
	joy_axis_range.diph.dwSize			= sizeof(DIPROPRANGE); 
	joy_axis_range.diph.dwHeaderSize	= sizeof(DIPROPHEADER); 
	joy_axis_range.diph.dwObj			= DIJOFS_Y;
	joy_axis_range.diph.dwHow			= DIPH_BYOFFSET;
	if(FAILED(gresult = lpdijoy->SetProperty(DIPROP_RANGE, &joy_axis_range.diph)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	DIPROPDWORD dead_band;
	ZeroMemory(&dead_band, sizeof(dead_band));
	dead_band.diph.dwSize			= sizeof(dead_band);
	dead_band.diph.dwHeaderSize		= sizeof(dead_band.diph);
	dead_band.diph.dwObj			= DIJOFS_X;
	dead_band.diph.dwHow			= DIPH_BYOFFSET;
	dead_band.dwData				= dead_zone * 100;
	if(FAILED(gresult = lpdijoy->SetProperty(DIPROP_DEADZONE, &dead_band.diph)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	ZeroMemory(&dead_band, sizeof(dead_band));
	dead_band.diph.dwSize			= sizeof(dead_band);
	dead_band.diph.dwHeaderSize		= sizeof(dead_band.diph);
	dead_band.diph.dwObj			= DIJOFS_Y;
	dead_band.diph.dwHow			= DIPH_BYOFFSET;
	dead_band.dwData				= dead_zone * 100;
	if(FAILED(gresult = lpdijoy->SetProperty(DIPROP_DEADZONE, &dead_band.diph)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	if(FAILED(gresult = lpdijoy->Acquire()))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	pdijoy->lpdijoy = lpdijoy;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpdijoy);
	return false;
}

T3DLIB_API void Destroy_DInput(DINPUTV1 * pdinput)
{
	SAFE_RELEASE(pdinput->lpdinput);
}

T3DLIB_API void Destroy_DIMouse(DIMOUSEV1 * pdimouse)
{
	CARE_UNACQUIRE(pdimouse->lpdimouse);
	SAFE_RELEASE(pdimouse->lpdimouse);
}

T3DLIB_API void Destroy_DIKey(DIKEYV1 * pdikey)
{
	CARE_UNACQUIRE(pdikey->lpdikey);
	SAFE_RELEASE(pdikey->lpdikey);
}

T3DLIB_API void Destroy_DIJoy(DIJOYV1 * pdijoy)
{
	CARE_UNACQUIRE(pdijoy->lpdijoy);
	SAFE_RELEASE(pdijoy->lpdijoy);
}

T3DLIB_API bool Read_DIMouse_State(DIMOUSEV1 * pdimouse, DIMOUSESTATE * pstate)
{
	if(FAILED(gresult = pdimouse->lpdimouse->GetDeviceState(sizeof(*pstate), pstate)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Read_DIKey_State(DIKEYV1 * pdikey, DIKEYSTATEV1 * pstate)
{
	if(FAILED(gresult = pdikey->lpdikey->GetDeviceState(sizeof(pstate->state), pstate->state)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Read_DIJoy_State(DIJOYV1 * pdijoy, DIJOYSTATE * pstate)
{
	if(FAILED(gresult = pdijoy->lpdijoy->Poll()))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));

	if(FAILED(gresult = pdijoy->lpdijoy->GetDeviceState(sizeof(*pstate), pstate)))
		ON_ERROR_GOTO(GET_DINPUT_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}
