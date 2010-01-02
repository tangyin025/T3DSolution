
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
		static std::basic_string<charT> GetResultStr(HRESULT hres);

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
		void SetCooperativeLevel(HWND hwnd, DWORD dwFlags);

		void SetDataFormat(LPCDIDATAFORMAT lpdf);

		void SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph);

		void Acquire(void);

		void GetDeviceState(DWORD cbData, LPVOID lpvData);
	};

	class DIKeyboard : public DIDevice
	{
	protected:
		BYTE m_state[256];

	public:
		DIKeyboard(DInput * dinput, REFGUID rguid);

	public:
		void Update(void)
		{
			GetDeviceState(sizeof(m_state), m_state);
		}

		const BYTE * GetKeyState(void) const
		{
			return m_state;
		}

		BYTE IsKeyDown(DWORD dwIndex) const
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
		void Update(void)
		{
			GetDeviceState(sizeof(m_state), (LPVOID)&m_state);
		}

		const DIMOUSESTATE & GetMouseState(void) const
		{
			return m_state;
		}

		LONG GetX(void) const
		{
			return m_state.lX;
		}

		LONG GetY(void) const
		{
			return m_state.lY;
		}

		LONG GetZ(void) const
		{
			return m_state.lZ;
		}

		BYTE IsButtonDown(DWORD dwIndex) const
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
		void Update(void)
		{
			GetDeviceState(sizeof(m_state), (LPVOID)&m_state);
		}

		const DIJOYSTATE & GetJoyState(void) const
		{
			return m_state;
		}

		LONG GetX(void) const
		{
			return m_state.lX;
		}

		LONG GetY(void) const
		{
			return m_state.lY;
		}

		LONG GetZ(void) const
		{
			return m_state.lZ;
		}

		LONG GetRx(void) const
		{
			return m_state.lRx;
		}

		LONG GetRy(void) const
		{
			return m_state.lRy;
		}

		LONG GetRz(void) const
		{
			return m_state.lRz;
		}

		LONG GetU(void) const
		{
			return m_state.rglSlider[0];
		}

		LONG GetV(void) const
		{
			return m_state.rglSlider[1];
		}

		DWORD GetPOV0(void) const
		{
			return m_state.rgdwPOV[0];
		}

		DWORD GetPOV1(void) const
		{
			return m_state.rgdwPOV[1];
		}

		DWORD GetPOV2(void) const
		{
			return m_state.rgdwPOV[2];
		}

		DWORD GetPOV3(void) const
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

		void EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags);

		void FindJoystickList(std::vector<DIDEVICEINSTANCE> & DIDeviceInstList, const std::basic_string<charT> & DeviceName = _T(""), DWORD dwMaxDeviceCount = 1);

		DIKeyboardPtr CreateSysKeyboard(void);

		DIMousePtr CreateSysMouse(void);

		DIJoystickPtr CreateJoystick(
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
