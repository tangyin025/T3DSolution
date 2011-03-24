
#include "stdafx.h"
#include "t3dlib2.h"
#include "t3dlib4.h"

#pragma comment(lib, "dinput8.lib")

namespace t3d
{
#define CASE_RETURN_STRING(branch) case branch: return std::basic_string<charT>(_T( #branch ));

	std::basic_string<charT> DIException::getResultStr(HRESULT hres)
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
		return getResultStr(m_hres);
	}

#define T3D_DIEXCEPT(hres) { throw DIException( _T(__FILE__), __LINE__, (hres) ); }

#define FAILED_DIEXCEPT(expr) { HRESULT hres; if( FAILED( hres = (expr) ) ) T3D_DIEXCEPT(hres) }

	DIDevice::DIDevice(DInput * dinput, REFGUID rguid)
	{
		FAILED_DIEXCEPT(dinput->m_dinput->CreateDevice(rguid, &m_didevice, NULL));
	}

	DIDevice::~DIDevice(void)
	{
	}

	void DIDevice::setCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		FAILED_DIEXCEPT(m_didevice->SetCooperativeLevel(hwnd, dwFlags));
	}

	void DIDevice::setDataFormat(LPCDIDATAFORMAT lpdf)
	{
		FAILED_DIEXCEPT(m_didevice->SetDataFormat(lpdf));
	}

	void DIDevice::setProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph)
	{
		FAILED_DIEXCEPT(m_didevice->SetProperty(rguidProp, pdiph));
	}

	bool DIDevice::acquire(void)
	{
		HRESULT hres = m_didevice->Acquire();

		if(DIERR_OTHERAPPHASPRIO == hres)
		{
			return false;
		}
		else if(FAILED(hres))
		{
			T3D_DIEXCEPT(hres);
		}

		return true;
	}

	void DIDevice::getDeviceState(DWORD cbData, LPVOID lpvData)
	{
		FAILED_DIEXCEPT(m_didevice->GetDeviceState(cbData, lpvData));
	}

	DIKeyboard::DIKeyboard(DInput * dinput, REFGUID rguid)
		: DIDevice(dinput, rguid)
	{
		setDataFormat(&c_dfDIKeyboard);
	}

	DIMouse::DIMouse(DInput * dinput, REFGUID rguid)
		: DIDevice(dinput, rguid)
	{
		setDataFormat(&c_dfDIMouse);
	}

	DIJoystick::DIJoystick(
			DInput * dinput,
			REFGUID rguid,
			LONG min_x,
			LONG max_x,
			LONG min_y,
			LONG max_y,
			LONG min_z,
			LONG max_z,
			real dead_zone)
			: DIDevice(dinput, rguid)
	{
		setDataFormat(&c_dfDIJoystick);

		_ASSERT(min_x <= max_x && min_y <= max_y);

		DIPROPRANGE dipr = {sizeof(dipr), sizeof(dipr.diph)};
		dipr.diph.dwObj = DIJOFS_X;
		dipr.diph.dwHow = DIPH_BYOFFSET;
		dipr.lMin = min_x;
		dipr.lMax = max_x;
		setProperty(DIPROP_RANGE, &dipr.diph);

		dipr.diph.dwObj = DIJOFS_Y;
		dipr.diph.dwHow = DIPH_BYOFFSET;
		dipr.lMin = min_y;
		dipr.lMax = max_y;
		setProperty(DIPROP_RANGE, &dipr.diph);

		dipr.diph.dwObj = DIJOFS_Z;
		dipr.diph.dwHow = DIPH_BYOFFSET;
		dipr.lMin = min_z;
		dipr.lMax = max_z;
		setProperty(DIPROP_RANGE, &dipr.diph);

		dipr.diph.dwObj = DIJOFS_RZ;
		dipr.diph.dwHow = DIPH_BYOFFSET;
		dipr.lMin = min_z;
		dipr.lMax = max_z;
		setProperty(DIPROP_RANGE, &dipr.diph);

		_ASSERT(dead_zone >= 0 && dead_zone <= 100);

		DIPROPDWORD dipd  = {sizeof(dipd), sizeof(dipd.diph)};
		dipd.diph.dwObj = DIJOFS_X;
		dipd.diph.dwHow = DIPH_BYOFFSET;
		dipd.dwData = real_to_int(dead_zone * 100);
		setProperty(DIPROP_DEADZONE, &dipd.diph);

		dipd.diph.dwObj = DIJOFS_Y;
		dipd.diph.dwHow = DIPH_BYOFFSET;
		dipd.dwData = real_to_int(dead_zone * 100);
		setProperty(DIPROP_DEADZONE, &dipd.diph);

		dipd.diph.dwObj = DIJOFS_Z;
		dipd.diph.dwHow = DIPH_BYOFFSET;
		dipd.dwData = real_to_int(dead_zone * 100);
		setProperty(DIPROP_DEADZONE, &dipd.diph);

		dipd.diph.dwObj = DIJOFS_RZ;
		dipd.diph.dwHow = DIPH_BYOFFSET;
		dipd.dwData = real_to_int(dead_zone * 100);
		setProperty(DIPROP_DEADZONE, &dipd.diph);
	}

	DInput::DInput(HINSTANCE hinst)
	{
		FAILED_DIEXCEPT(DirectInput8Create(hinst, DIRECTINPUT_HEADER_VERSION, IID_IDirectInput8, (LPVOID *)&m_dinput, NULL));
	}

	DInput::~DInput(void)
	{
	}

	void DInput::enumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
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

		BOOL findDIJoystick(LPCDIDEVICEINSTANCE lpddi)
		{
			if(lpddi->dwDevType & DI8DEVTYPE_JOYSTICK)
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
		return ((DIJoystickFinder *)pvRef)->findDIJoystick(lpddi);
	}

	void DInput::findJoystickList(std::vector<DIDEVICEINSTANCE> & DIDeviceInstList, const std::basic_string<charT> & DeviceName /*= _T("")*/, DWORD dwMaxDeviceCount /*= 1*/)
	{
		DIJoystickFinder finder(DIDeviceInstList, DeviceName, dwMaxDeviceCount);

		enumDevices(DI8DEVCLASS_GAMECTRL, DIJoystickFinderCallback, &finder, DIEDFL_ATTACHEDONLY);
	}

	DIKeyboardPtr DInput::createSysKeyboard(void)
	{
		return DIKeyboardPtr(new DIKeyboard(this, GUID_SysKeyboard));
	}

	DIMousePtr DInput::createSysMouse(void)
	{
		return DIMousePtr(new DIMouse(this, GUID_SysMouse));
	}

	DIJoystickPtr DInput::createJoystick(
		REFGUID rguid,
		LONG min_x /*= -255*/,
		LONG max_x /*=  255*/,
		LONG min_y /*= -255*/,
		LONG max_y /*=  255*/,
		LONG min_z /*= -255*/,
		LONG max_z /*=  255*/,
		real dead_zone /*= 10*/)
	{
		return DIJoystickPtr(new DIJoystick(this, rguid, min_x, max_x, min_y, max_y, min_z, max_z, dead_zone));
	}
}
