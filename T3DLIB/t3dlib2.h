
#ifndef __T3DLIB2_H__
#define __T3DLIB2_H__

#include "t3dcommon.h"

#include <string>
#include <cassert>
#include <dinput.h>
#include <vector>

namespace t3d
{
	class T3DLIB_API DInput
	{
	public:
		static std::basic_string<charT> getResultStr(HRESULT hres);

		class T3DLIB_API Exception : public t3d::Exception
		{
		public:
			Exception(const std::basic_string<charT> & file, int line, HRESULT hres);

		public:
			std::basic_string<charT> what(void) const throw();

		protected:
			HRESULT m_hres;
		};

	public:
		DInput(HINSTANCE hinst);

		virtual ~DInput(void);

	protected:
		LPDIRECTINPUT8 m_lpdinput;

	public:
		class T3DLIB_API Device
		{
		public:
			enum COOPERATIVE_LEVEL
			{
				CL_NORMAL = DISCL_NONEXCLUSIVE | DISCL_BACKGROUND,
			};

		public:
			Device(DInput * input, REFGUID rguid);

			virtual ~Device(void);

		public:
			void setCooperativeLevel(HWND hwnd, DWORD level);

			void setDataFormat(LPCDIDATAFORMAT lpdf);

			void setProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph);

			void acquire(void);

			void getDeviceState(LPVOID data, DWORD data_size);

		protected:
			LPDIRECTINPUTDEVICE8 m_lpdidevice;
		};

		class T3DLIB_API Keyboard : public Device
		{
		public:
			Keyboard(DInput * input, const GUID & guid, HWND hwnd, DWORD level);

		public:
			void update(void);

			inline const byte * getKeyState(void) const
			{
				return m_state;
			}

			inline byte isKeyDown(DWORD index) const
			{
				assert(index < sizeof(m_state));

				return getKeyState()[index];
			}

		protected:
			byte m_state[256];
		};

		class T3DLIB_API Mouse : public Device
		{
		public:
			Mouse(DInput * input, const GUID & guid, HWND hwnd, DWORD level);

		public:
			void update(void);

			inline const DIMOUSESTATE & getMouseState(void) const
			{
				return m_state;
			}

			inline LONG getX(void) const
			{
				return getMouseState().lX;
			}

			inline LONG getY(void) const
			{
				return getMouseState().lY;
			}

			inline LONG getZ(void) const
			{
				return getMouseState().lZ;
			}

			inline byte isButtonDown(DWORD index) const
			{
				assert(index < sizeof(m_state.rgbButtons) / sizeof(m_state.rgbButtons[0]));

				return getMouseState().rgbButtons[index];
			}

		protected:
			DIMOUSESTATE m_state;
		};

		class T3DLIB_API Joystick : public Device
		{
		public:
			Joystick(
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
				real dead_zone);

		public:
			void update(void);

			inline const DIJOYSTATE & getJoyState(void) const
			{
				return m_state;
			}

			inline LONG getX(void) const
			{
				return getJoyState().lX;
			}

			inline LONG getY(void) const
			{
				return getJoyState().lY;
			}

			inline LONG getZ(void) const
			{
				return getJoyState().lZ;
			}

			inline LONG getRx(void) const
			{
				return getJoyState().lRx;
			}

			inline LONG getRy(void) const
			{
				return getJoyState().lRy;
			}

			inline LONG getRz(void) const
			{
				return getJoyState().lRz;
			}

			inline LONG getU(void) const
			{
				return getJoyState().rglSlider[0];
			}

			inline LONG getV(void) const
			{
				return getJoyState().rglSlider[1];
			}

			inline DWORD getPOV0(void) const
			{
				return getJoyState().rgdwPOV[0];
			}

			inline DWORD getPOV1(void) const
			{
				return getJoyState().rgdwPOV[1];
			}

			inline DWORD getPOV2(void) const
			{
				return getJoyState().rgdwPOV[2];
			}

			inline DWORD getPOV3(void) const
			{
				return getJoyState().rgdwPOV[3];
			}

			inline byte isButtonDown(DWORD index) const
			{
				assert(index < sizeof(m_state.rgbButtons) / sizeof(m_state.rgbButtons[0]));

				return getJoyState().rgbButtons[index];
			}

		protected:
			DIJOYSTATE m_state;
		};

		class T3DLIB_API EnumDevicesInterface
		{
		public:
			virtual ~EnumDevicesInterface(void);

			virtual bool isNeededDevice(const DIDEVICEINSTANCE & device_instance) = 0;
		};

	public:
		Keyboard * createSysKeyboard(HWND hwnd, DWORD level = Device::CL_NORMAL);

		Mouse * createSysMouse(HWND hwnd, DWORD level = Device::CL_NORMAL);

		void enumDevices(DWORD dwDevType, EnumDevicesInterface * EnumDevicesObject);

		bool findFirstJoystick(DIDEVICEINSTANCE & return_instance, const std::basic_string<charT> & device_name = std::basic_string<charT>());

		void findJoystickList(std::vector<DIDEVICEINSTANCE> & return_instance_list);

		Joystick * createJoystick(
			HWND hwnd,
			const DIDEVICEINSTANCE & device_instance,
			DWORD level = Device::CL_NORMAL,
			LONG min_x = -255,
			LONG max_x =  255,
			LONG min_y = -255,
			LONG max_y =  255,
			LONG min_z = -255,
			LONG max_z =  255,
			real dead_zone = 10);

	protected:
		static BOOL CALLBACK DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
	};
}

#endif // __T3DLIB2_H__
