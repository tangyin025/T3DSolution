
#ifndef __T3DLIB2_H__
#define __T3DLIB2_H__

#include "t3dcommon.h"
#include <string>
#include <dinput.h>
#include <atlbase.h>
#include <cassert>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace t3d
{
	class DIException : public Exception
	{
	public:
		static std::basic_string<charT> getResultStr(HRESULT hres);

	public:
		DIException(const std::basic_string<charT> & file, int line, HRESULT hres);

	public:
		std::basic_string<charT> what(void) const throw();

	protected:
		HRESULT m_hres;
	};

	class DInput;

	class DIDevice
	{
		friend DInput;

	public:
		CComPtr<IDirectInputDevice8> m_didevice;

	public:
		enum COOPERATIVE_LEVEL
		{
			CL_NORMAL = DISCL_NONEXCLUSIVE | DISCL_BACKGROUND,
		};

	public:
		DIDevice(DInput * dinput, REFGUID rguid);

		virtual ~DIDevice(void);

	public:
		void setCooperativeLevel(HWND hwnd, DWORD dwFlags);

		void setDataFormat(LPCDIDATAFORMAT lpdf);

		void setProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph);

		void acquire(void);

		void getDeviceState(DWORD cbData, LPVOID lpvData);
	};

	class DIKeyboard : public DIDevice
	{
	protected:
		BYTE m_state[256];

	public:
		DIKeyboard(DInput * dinput, REFGUID rguid);

	public:
		void update(void)
		{
			getDeviceState(sizeof(m_state), m_state);
		}

		const BYTE * getKeyState(void) const
		{
			return m_state;
		}

		BYTE isKeyDown(DWORD dwIndex) const
		{
			assert(dwIndex < sizeof(m_state));

			return m_state[dwIndex];
		}
	};

	typedef boost::shared_ptr<DIKeyboard> DIKeyboardPtr;

	class DIMouse : public DIDevice
	{
	protected:
		DIMOUSESTATE m_state;

	public:
		DIMouse(DInput * dinput, REFGUID rguid);

	public:
		void update(void)
		{
			getDeviceState(sizeof(m_state), (LPVOID)&m_state);
		}

		const DIMOUSESTATE & getMouseState(void) const
		{
			return m_state;
		}

		LONG getX(void) const
		{
			return m_state.lX;
		}

		LONG getY(void) const
		{
			return m_state.lY;
		}

		LONG getZ(void) const
		{
			return m_state.lZ;
		}

		BYTE isButtonDown(DWORD dwIndex) const
		{
			assert(dwIndex < sizeof(m_state.rgbButtons) / sizeof(m_state.rgbButtons[0]));

			return m_state.rgbButtons[dwIndex];
		}
	};

	typedef boost::shared_ptr<DIMouse> DIMousePtr;

	class DIJoystick : public DIDevice
	{
	protected:
		DIJOYSTATE m_state;

	public:
		DIJoystick(
			DInput * dinput,
			REFGUID rguid,
			LONG min_x,
			LONG max_x,
			LONG min_y,
			LONG max_y,
			LONG min_z,
			LONG max_z,
			real dead_zone);

	public:
		void update(void)
		{
			getDeviceState(sizeof(m_state), (LPVOID)&m_state);
		}

		const DIJOYSTATE & getJoyState(void) const
		{
			return m_state;
		}

		LONG getX(void) const
		{
			return m_state.lX;
		}

		LONG getY(void) const
		{
			return m_state.lY;
		}

		LONG getZ(void) const
		{
			return m_state.lZ;
		}

		LONG getRx(void) const
		{
			return m_state.lRx;
		}

		LONG getRy(void) const
		{
			return m_state.lRy;
		}

		LONG getRz(void) const
		{
			return m_state.lRz;
		}

		LONG getU(void) const
		{
			return m_state.rglSlider[0];
		}

		LONG getV(void) const
		{
			return m_state.rglSlider[1];
		}

		DWORD getPOV0(void) const
		{
			return m_state.rgdwPOV[0];
		}

		DWORD getPOV1(void) const
		{
			return m_state.rgdwPOV[1];
		}

		DWORD getPOV2(void) const
		{
			return m_state.rgdwPOV[2];
		}

		DWORD getPOV3(void) const
		{
			return m_state.rgdwPOV[3];
		}

		BYTE isButtonDown(DWORD dwIndex) const
		{
			assert(dwIndex < sizeof(m_state.rgbButtons) / sizeof(m_state.rgbButtons[0]));

			return m_state.rgbButtons[dwIndex];
		}
	};

	typedef boost::shared_ptr<DIJoystick> DIJoystickPtr;

	class DInput
	{
	public:
		CComPtr<IDirectInput8> m_dinput;

	public:
		DInput(HINSTANCE hinst);

		virtual ~DInput(void);

		void enumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags);

		void findJoystickList(std::vector<DIDEVICEINSTANCE> & DIDeviceInstList, const std::basic_string<charT> & DeviceName = _T(""), DWORD dwMaxDeviceCount = 1);

		DIKeyboardPtr createSysKeyboard(void);

		DIMousePtr createSysMouse(void);

		DIJoystickPtr createJoystick(
			REFGUID rguid,
			LONG min_x = -255,
			LONG max_x =  255,
			LONG min_y = -255,
			LONG max_y =  255,
			LONG min_z = -255,
			LONG max_z =  255,
			real dead_zone = 10);
	};

	typedef boost::shared_ptr<DInput> DInputPtr;
}

#endif // __T3DLIB2_H__
