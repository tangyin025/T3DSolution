
#include "stdafx.h"
#include "t3dlib2.h"
#include "t3dlib4.h"

#pragma comment(lib, "dinput8.lib")

namespace t3d
{
	std::basic_string<charT> DInput::getResultStr(HRESULT hres)
	{
		const charT * pstr;
		switch(hres)
		{
		case DI_BUFFEROVERFLOW:
			pstr = _T("DI_BUFFEROVERFLOW"); break;
		case DI_DOWNLOADSKIPPED:
			pstr = _T("DI_DOWNLOADSKIPPED"); break;
		case DI_EFFECTRESTARTED:
			pstr = _T("DI_EFFECTRESTARTED"); break;
		//case DI_NOEFFECT:
		//	pstr = _T("DI_NOEFFECT"); break;
		//case DI_NOTATTACHED:
		//	pstr = _T("DI_NOTATTACHED"); break;
		case DI_OK:
			pstr = _T("DI_OK"); break;
		case DI_POLLEDDEVICE:
			pstr = _T("DI_POLLEDDEVICE"); break;
		//case DI_PROPNOEFFECT:
		//	pstr = _T("DI_PROPNOEFFECT"); break;
		case DI_TRUNCATED:
			pstr = _T("DI_TRUNCATED"); break;
		case DI_TRUNCATEDANDRESTARTED:
			pstr = _T("DI_TRUNCATEDANDRESTARTED"); break;
		case DIERR_ACQUIRED:
			pstr = _T("DIERR_ACQUIRED"); break;
		case DIERR_ALREADYINITIALIZED:
			pstr = _T("DIERR_ALREADYINITIALIZED"); break;
		case DIERR_BADDRIVERVER:
			pstr = _T("DIERR_BADDRIVERVER"); break;
		case DIERR_BETADIRECTINPUTVERSION:
			pstr = _T("DIERR_BETADIRECTINPUTVERSION"); break;
		case DIERR_DEVICEFULL:
			pstr = _T("DIERR_DEVICEFULL"); break;
		case DIERR_DEVICENOTREG:
			pstr = _T("DIERR_DEVICENOTREG"); break;
		case DIERR_EFFECTPLAYING:
			pstr = _T("DIERR_EFFECTPLAYING"); break;
		case DIERR_HASEFFECTS:
			pstr = _T("DIERR_HASEFFECTS"); break;
		case DIERR_GENERIC:
			pstr = _T("DIERR_GENERIC"); break;
		case DIERR_HANDLEEXISTS:
			pstr = _T("DIERR_HANDLEEXISTS"); break;
		case DIERR_INCOMPLETEEFFECT:
			pstr = _T("DIERR_INCOMPLETEEFFECT"); break;
		case DIERR_INPUTLOST:
			pstr = _T("DIERR_INPUTLOST"); break;
		case DIERR_INVALIDPARAM:
			pstr = _T("DIERR_INVALIDPARAM"); break;
		case DIERR_MOREDATA:
			pstr = _T("DIERR_MOREDATA"); break;
		case DIERR_NOAGGREGATION:
			pstr = _T("DIERR_NOAGGREGATION"); break;
		case DIERR_NOINTERFACE:
			pstr = _T("DIERR_NOINTERFACE"); break;
		case DIERR_NOTACQUIRED:
			pstr = _T("DIERR_NOTACQUIRED"); break;
		case DIERR_NOTBUFFERED:
			pstr = _T("DIERR_NOTBUFFERED"); break;
		case DIERR_NOTDOWNLOADED:
			pstr = _T("DIERR_NOTDOWNLOADED"); break;
		case DIERR_NOTEXCLUSIVEACQUIRED:
			pstr = _T("DIERR_NOTEXCLUSIVEACQUIRED"); break;
		case DIERR_NOTFOUND:
			pstr = _T("DIERR_NOTFOUND"); break;
		case DIERR_NOTINITIALIZED:
			pstr = _T("DIERR_NOTINITIALIZED"); break;
		//case DIERR_OBJECTNOTFOUND:
		//	pstr = _T("DIERR_OBJECTNOTFOUND"); break;
		case DIERR_OLDDIRECTINPUTVERSION:
			pstr = _T("DIERR_OLDDIRECTINPUTVERSION"); break;
		//case DIERR_OTHERAPPHASPRIO:
		//	pstr = _T("DIERR_OTHERAPPHASPRIO"); break;
		case DIERR_OUTOFMEMORY:
			pstr = _T("DIERR_OUTOFMEMORY"); break;
		//case DIERR_READONLY:
		//	pstr = _T("DIERR_READONLY"); break;
		case DIERR_REPORTFULL:
			pstr = _T("DIERR_REPORTFULL"); break;
		case DIERR_UNPLUGGED:
			pstr = _T("DIERR_UNPLUGGED"); break;
		case DIERR_UNSUPPORTED:
			pstr = _T("DIERR_UNSUPPORTED"); break;
		case E_HANDLE:
			pstr = _T("E_HANDLE"); break;
		case E_PENDING:
			pstr = _T("E_PENDING"); break;
		default:
			pstr = _T("unknown dinput result"); break;
		}

		return std::basic_string<charT>(pstr);
	}

	t3d::DInput::Exception::Exception(const std::basic_string<charT> & file, int line, HRESULT hres)
		: t3d::Exception(file, line)
		, m_hres(hres)
	{
	}

	std::basic_string<charT> t3d::DInput::Exception::what(void) const throw()
	{
		return getResultStr(m_hres);
	}

#define T3D_DIEXCEPT(hres) { throw t3d::DInput::Exception(_T(__FILE__), __LINE__, (hres)); }

	DInput::DInput(HINSTANCE hinst)
		: m_lpdinput(NULL)
	{
		HRESULT hres;
		if(FAILED(hres = ::DirectInput8Create(
				hinst, DIRECTINPUT_HEADER_VERSION, IID_IDirectInput8, (LPVOID *)&m_lpdinput, NULL)))
			T3D_DIEXCEPT(hres);
	}

	DInput::~DInput(void)
	{
		SAFE_RELEASE(m_lpdinput);
	}

	DInput::Device::Device(DInput * input, REFGUID rguid)
	{
		HRESULT hres;
		if(FAILED(hres = input->m_lpdinput->CreateDevice(rguid, &m_lpdidevice, NULL)))
			T3D_DIEXCEPT(hres);
	}

	DInput::Device::~Device(void)
	{
		SAFE_RELEASE(m_lpdidevice);
	}

	void DInput::Device::setCooperativeLevel(HWND hwnd, DWORD level)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdidevice->SetCooperativeLevel(hwnd, level)))
			T3D_DIEXCEPT(hres);
	}

	void DInput::Device::setDataFormat(LPCDIDATAFORMAT lpdf)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdidevice->SetDataFormat(lpdf)))
			T3D_DIEXCEPT(hres);
	}

	void DInput::Device::setProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdidevice->SetProperty(rguidProp, pdiph)))
			T3D_DIEXCEPT(hres);
	}

	void DInput::Device::acquire(void)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdidevice->Acquire()))
			T3D_DIEXCEPT(hres);
	}

	void DInput::Device::getDeviceState(LPVOID data, DWORD data_size)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdidevice->GetDeviceState(data_size, data)))
			T3D_DIEXCEPT(hres);
	}

	DInput::Keyboard::Keyboard(DInput * input, const GUID & guid, HWND hwnd, DWORD level)
		: Device(input, guid)
	{
		setDataFormat(&c_dfDIKeyboard);
		setCooperativeLevel(hwnd, level);
		acquire();
	}

	void DInput::Keyboard::update(void)
	{
		getDeviceState(&m_state, sizeof(m_state));
	}

	DInput::Mouse::Mouse(DInput * input, const GUID & guid, HWND hwnd, DWORD level)
		: Device(input, guid)
	{
		setDataFormat(&c_dfDIMouse);
		setCooperativeLevel(hwnd, level);
		acquire();
	}

	void DInput::Mouse::update(void)
	{
		getDeviceState(&m_state, sizeof(m_state));
	}

	DInput::Joystick::Joystick(
				DInput * input,
				const GUID & guid,
				HWND hwnd,
				DWORD level,
				LONG min_x,
				LONG max_x,
				LONG min_y,
				LONG max_y,
				LONG min_z,
				LONG max_z,
				real dead_zone)
		: Device(input, guid)
	{
		setDataFormat(&c_dfDIJoystick);
		setCooperativeLevel(hwnd, level);

		assert(min_x <= max_x && min_y <= max_y);

		DIPROPRANGE dipr;
		memset(&dipr, 0, sizeof(dipr));
		dipr.diph.dwSize = sizeof(dipr);
		dipr.diph.dwHeaderSize = sizeof(dipr.diph);

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

		assert(dead_zone >= 0 && dead_zone <= 100);

		DIPROPDWORD dipd;
		memset(&dipd, 0, sizeof(dipd));
		dipd.diph.dwSize = sizeof(dipd);
		dipd.diph.dwHeaderSize = sizeof(dipd.diph);

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

		acquire();
	}

	void DInput::Joystick::update(void)
	{
		getDeviceState(&m_state, sizeof(m_state));
	}

	DInput::EnumDevicesInterface::~EnumDevicesInterface(void)
	{
	}

	DInput::Keyboard * DInput::createSysKeyboard(HWND hwnd, DWORD level /*= Device::CL_NORMAL*/)
	{
		return new Keyboard(this, GUID_SysKeyboard, hwnd, level);
	}

	DInput::Mouse * DInput::createSysMouse(HWND hwnd, DWORD level /*= Device::CL_NORMAL*/)
	{
		return new Mouse(this, GUID_SysMouse, hwnd, level);
	}

	void DInput::enumDevices(DWORD dwDevType, EnumDevicesInterface * EnumDevicesObject)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdinput->EnumDevices(dwDevType, DIEnumDevicesCallback, EnumDevicesObject, DIEDFL_ATTACHEDONLY)))
			T3D_DIEXCEPT(hres);
	}

	class FirstJoystickFinder : public DInput::EnumDevicesInterface
	{
	public:
		FirstJoystickFinder(const std::basic_string<charT> & device_name)
			: m_joystickName(device_name)
		{
		}

		bool isNeededDevice(const DIDEVICEINSTANCE & device_instance)
		{
			if(device_instance.dwDevType & DI8DEVTYPE_JOYSTICK)
			{
				if(m_joystickName.empty() || m_joystickName == device_instance.tszInstanceName)
				{
					m_instanceList.push_back(device_instance);

					return true;
				}
			}

			return false;
		}

	public:
		std::basic_string<charT> m_joystickName;

		std::vector<DIDEVICEINSTANCE> m_instanceList;
	};

	bool DInput::findFirstJoystick(DIDEVICEINSTANCE & return_instance, const std::basic_string<charT> & device_name /*= std::basic_string<charT>()*/)
	{
		FirstJoystickFinder finder(device_name);

		enumDevices(DI8DEVCLASS_GAMECTRL, &finder);

		if(!finder.m_instanceList.empty())
		{
			return_instance = finder.m_instanceList.front();

			return true;
		}

		return false;
	}

	class JoystickListFinder : public DInput::EnumDevicesInterface
	{
	public:
		JoystickListFinder(void)
		{
		}

		bool isNeededDevice(const DIDEVICEINSTANCE & device_instance)
		{
			if(device_instance.dwDevType & DI8DEVTYPE_JOYSTICK)
			{
				m_instanceList.push_back(device_instance);
			}

			return false;
		}

	public:
		std::vector<DIDEVICEINSTANCE> m_instanceList;
	};

	void DInput::findJoystickList(std::vector<DIDEVICEINSTANCE> & return_instance_list)
	{
		JoystickListFinder finder;

		enumDevices(DI8DEVCLASS_GAMECTRL, &finder);

		return_instance_list.insert(return_instance_list.end(), finder.m_instanceList.begin(), finder.m_instanceList.end());
	}

	DInput::Joystick * DInput::createJoystick(
			HWND hwnd,
			const DIDEVICEINSTANCE & device_instance,
			DWORD level /*= Device::CL_NORMAL*/,
			LONG min_x /*= -255*/,
			LONG max_x /*=  255*/,
			LONG min_y /*= -255*/,
			LONG max_y /*=  255*/,
			LONG min_z /*= -255*/,
			LONG max_z /*=  255*/,
			real dead_zone /*= 10*/)
	{
		assert(device_instance.dwDevType & DI8DEVTYPE_JOYSTICK);

		return new Joystick(this, device_instance.guidInstance, hwnd, level, min_x, max_x, min_y, max_y, min_z, max_z, dead_zone);
	}

	BOOL CALLBACK DInput::DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
	{
		EnumDevicesInterface * EnumDevicesObject = (EnumDevicesInterface *)pvRef;

		return EnumDevicesObject->isNeededDevice(*lpddi) ? DIENUM_STOP : DIENUM_CONTINUE;
	}
}
