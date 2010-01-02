
#include "stdafx.h"
#include "t3dlib2.h"
#include "t3dlib4.h"

#pragma comment(lib, "dinput8.lib")

namespace t3d
{
#define CASE_RETURN_STRING(branch) case branch: return std::basic_string<charT>(_T( #branch ));

	std::basic_string<charT> DIException::GetResultStr(HRESULT hres)
	{
		switch(hres)
		{
		CASE_RETURN_STRING(DI_BUFFEROVERFLOW)
		CASE_RETURN_STRING(DI_DOWNLOADSKIPPED)
		CASE_RETURN_STRING(DI_EFFECTRESTARTED)
		//CASE_RETURN_STRING(DI_NOEFFECT)
		//CASE_RETURN_STRING(DI_NOTATTACHED)
		CASE_RETURN_STRING(DI_OK)
		CASE_RETURN_STRING(DI_POLLEDDEVICE)
		//CASE_RETURN_STRING(DI_PROPNOEFFECT)
		CASE_RETURN_STRING(DI_TRUNCATED)
		CASE_RETURN_STRING(DI_TRUNCATEDANDRESTARTED)
		CASE_RETURN_STRING(DIERR_ACQUIRED)
		CASE_RETURN_STRING(DIERR_ALREADYINITIALIZED)
		CASE_RETURN_STRING(DIERR_BADDRIVERVER)
		CASE_RETURN_STRING(DIERR_BETADIRECTINPUTVERSION)
		CASE_RETURN_STRING(DIERR_DEVICEFULL)
		CASE_RETURN_STRING(DIERR_DEVICENOTREG)
		CASE_RETURN_STRING(DIERR_EFFECTPLAYING)
		CASE_RETURN_STRING(DIERR_HASEFFECTS)
		CASE_RETURN_STRING(DIERR_GENERIC)
		CASE_RETURN_STRING(DIERR_HANDLEEXISTS)
		CASE_RETURN_STRING(DIERR_INCOMPLETEEFFECT)
		CASE_RETURN_STRING(DIERR_INPUTLOST)
		CASE_RETURN_STRING(DIERR_INVALIDPARAM)
		CASE_RETURN_STRING(DIERR_MOREDATA)
		CASE_RETURN_STRING(DIERR_NOAGGREGATION)
		CASE_RETURN_STRING(DIERR_NOINTERFACE)
		CASE_RETURN_STRING(DIERR_NOTACQUIRED)
		CASE_RETURN_STRING(DIERR_NOTBUFFERED)
		CASE_RETURN_STRING(DIERR_NOTDOWNLOADED)
		CASE_RETURN_STRING(DIERR_NOTEXCLUSIVEACQUIRED)
		CASE_RETURN_STRING(DIERR_NOTFOUND)
		CASE_RETURN_STRING(DIERR_NOTINITIALIZED)
		//CASE_RETURN_STRING(DIERR_OBJECTNOTFOUND)
		CASE_RETURN_STRING(DIERR_OLDDIRECTINPUTVERSION)
		//CASE_RETURN_STRING(DIERR_OTHERAPPHASPRIO)
		CASE_RETURN_STRING(DIERR_OUTOFMEMORY)
		//CASE_RETURN_STRING(DIERR_READONLY)
		CASE_RETURN_STRING(DIERR_REPORTFULL)
		CASE_RETURN_STRING(DIERR_UNPLUGGED)
		CASE_RETURN_STRING(DIERR_UNSUPPORTED)
		CASE_RETURN_STRING(E_HANDLE)
		CASE_RETURN_STRING(E_PENDING)
		}
		return std::basic_string<charT>(_T("unknown dinput result"));
	}

	DIException::DIException(const std::basic_string<charT> & file, int line, HRESULT hres)
		: Exception(file, line)
		, m_hres(hres)
	{
	}

	std::basic_string<charT> DIException::what(void) const throw()
	{
		return GetResultStr(m_hres);
	}

#define T3D_DIEXCEPT(hres) { throw DIException( _T(__FILE__), __LINE__, (hres) ); }

#define FAILED_DIEXCEPT(expr) { HRESULT hres; if( FAILED( hres = (expr) ) ) T3D_DIEXCEPT(hres) }

	DIDevice::DIDevice(LPDIRECTINPUT8 lpdinput, REFGUID rguid)
	{
		FAILED_DIEXCEPT(lpdinput->CreateDevice(rguid, &m_didevice, NULL));
	}

	DIDevice::~DIDevice(void)
	{
	}

	void DIDevice::SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		FAILED_DIEXCEPT(m_didevice->SetCooperativeLevel(hwnd, dwFlags));
	}

	void DIDevice::SetDataFormat(LPCDIDATAFORMAT lpdf)
	{
		FAILED_DIEXCEPT(m_didevice->SetDataFormat(lpdf));
	}

	void DIDevice::SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph)
	{
		FAILED_DIEXCEPT(m_didevice->SetProperty(rguidProp, pdiph));
	}

	void DIDevice::Acquire(void)
	{
		FAILED_DIEXCEPT(m_didevice->Acquire());
	}

	void DIDevice::GetDeviceState(DWORD cbData, LPVOID lpvData)
	{
		FAILED_DIEXCEPT(m_didevice->GetDeviceState(cbData, lpvData));
	}

	DIKeyboard::DIKeyboard(LPDIRECTINPUT8 lpdinput, REFGUID rguid)
		: DIDevice(lpdinput, rguid)
	{
		SetDataFormat(&c_dfDIKeyboard);
	}

	DIMouse::DIMouse(LPDIRECTINPUT8 lpdinput, REFGUID rguid)
		: DIDevice(lpdinput, rguid)
	{
		SetDataFormat(&c_dfDIMouse);
	}

	DIJoystick::DIJoystick(
			LPDIRECTINPUT8 lpdinput,
			REFGUID rguid,
			LONG min_x,
			LONG max_x,
			LONG min_y,
			LONG max_y,
			LONG min_z,
			LONG max_z,
			real dead_zone)
			: DIDevice(lpdinput, rguid)
	{
		SetDataFormat(&c_dfDIJoystick);

		assert(min_x <= max_x && min_y <= max_y);

		DIPROPRANGE dipr;
		memset(&dipr, 0, sizeof(dipr));
		dipr.diph.dwSize = sizeof(dipr);
		dipr.diph.dwHeaderSize = sizeof(dipr.diph);

		dipr.diph.dwObj = DIJOFS_X;
		dipr.diph.dwHow = DIPH_BYOFFSET;
		dipr.lMin = min_x;
		dipr.lMax = max_x;
		SetProperty(DIPROP_RANGE, &dipr.diph);

		dipr.diph.dwObj = DIJOFS_Y;
		dipr.diph.dwHow = DIPH_BYOFFSET;
		dipr.lMin = min_y;
		dipr.lMax = max_y;
		SetProperty(DIPROP_RANGE, &dipr.diph);

		dipr.diph.dwObj = DIJOFS_Z;
		dipr.diph.dwHow = DIPH_BYOFFSET;
		dipr.lMin = min_z;
		dipr.lMax = max_z;
		SetProperty(DIPROP_RANGE, &dipr.diph);

		dipr.diph.dwObj = DIJOFS_RZ;
		dipr.diph.dwHow = DIPH_BYOFFSET;
		dipr.lMin = min_z;
		dipr.lMax = max_z;
		SetProperty(DIPROP_RANGE, &dipr.diph);

		assert(dead_zone >= 0 && dead_zone <= 100);

		DIPROPDWORD dipd;
		memset(&dipd, 0, sizeof(dipd));
		dipd.diph.dwSize = sizeof(dipd);
		dipd.diph.dwHeaderSize = sizeof(dipd.diph);

		dipd.diph.dwObj = DIJOFS_X;
		dipd.diph.dwHow = DIPH_BYOFFSET;
		dipd.dwData = real_to_int(dead_zone * 100);
		SetProperty(DIPROP_DEADZONE, &dipd.diph);

		dipd.diph.dwObj = DIJOFS_Y;
		dipd.diph.dwHow = DIPH_BYOFFSET;
		dipd.dwData = real_to_int(dead_zone * 100);
		SetProperty(DIPROP_DEADZONE, &dipd.diph);

		dipd.diph.dwObj = DIJOFS_Z;
		dipd.diph.dwHow = DIPH_BYOFFSET;
		dipd.dwData = real_to_int(dead_zone * 100);
		SetProperty(DIPROP_DEADZONE, &dipd.diph);

		dipd.diph.dwObj = DIJOFS_RZ;
		dipd.diph.dwHow = DIPH_BYOFFSET;
		dipd.dwData = real_to_int(dead_zone * 100);
		SetProperty(DIPROP_DEADZONE, &dipd.diph);
	}

	DInput::DInput(HINSTANCE hinst)
	{
		FAILED_DIEXCEPT(DirectInput8Create(hinst, DIRECTINPUT_HEADER_VERSION, IID_IDirectInput8, (LPVOID *)&m_dinput, NULL));
	}

	DInput::~DInput(void)
	{
	}

	void DInput::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
	{
		SUCCEEDED_VERIFY(m_dinput->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags));
	}

	class DIJoystickFinder
	{
	public:
		std::vector<DIDEVICEINSTANCE> & m_DIDeviceInstList;

	protected:
		std::basic_string<charT> m_DeviceName;

		DWORD m_MaxDeviceCount;

	public:
		DIJoystickFinder(std::vector<DIDEVICEINSTANCE> & DIDeviceInstList, const std::basic_string<charT> & DeviceName, DWORD dwMaxDeviceCount)
			: m_DIDeviceInstList(DIDeviceInstList)
			, m_DeviceName(DeviceName)
			, m_MaxDeviceCount(dwMaxDeviceCount)
		{
		}

		BOOL FindDIJoystick(LPCDIDEVICEINSTANCE lpddi)
		{
			if(lpddi->dwDevType & DI8DEVTYPEJOYSTICK_STANDARD)
			{
				if(m_DeviceName.empty() || lpddi->tszInstanceName == m_DeviceName)
				{
					m_DIDeviceInstList.push_back(*lpddi);
				}
			}

			return m_DIDeviceInstList.size() < m_MaxDeviceCount ? DIENUM_CONTINUE : DIENUM_STOP;
		}
	};

	BOOL CALLBACK DIJoystickFinderCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
	{
		return ((DIJoystickFinder *)pvRef)->FindDIJoystick(lpddi);
	}

	void DInput::FindJoystickList(std::vector<DIDEVICEINSTANCE> & DIDeviceInstList, const std::basic_string<charT> & DeviceName /*= _T("")*/, DWORD dwMaxDeviceCount /*= 1*/)
	{
		DIJoystickFinder finder(DIDeviceInstList, DeviceName, dwMaxDeviceCount);

		EnumDevices(DI8DEVCLASS_GAMECTRL, DIJoystickFinderCallback, &finder, DIEDFL_ATTACHEDONLY);
	}

	DIKeyboardPtr DInput::CreateSysKeyboard(void)
	{
		return DIKeyboardPtr(new DIKeyboard(m_dinput, GUID_SysKeyboard));
	}

	DIMousePtr DInput::CreateSysMouse(void)
	{
		return DIMousePtr(new DIMouse(m_dinput, GUID_SysMouse));
	}

	DIJoystickPtr DInput::CreateJoystick(
		REFGUID rguid,
		LONG min_x /*= -255*/,
		LONG max_x /*=  255*/,
		LONG min_y /*= -255*/,
		LONG max_y /*=  255*/,
		LONG min_z /*= -255*/,
		LONG max_z /*=  255*/,
		real dead_zone /*= 10*/)
	{
		return DIJoystickPtr(new DIJoystick(m_dinput, rguid, min_x, max_x, min_y, max_y, min_z, max_z, dead_zone));
	}
}
