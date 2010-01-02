
#ifndef __MYWINDOW_H__
#define __MYWINDOW_H__

#include "myCommon.h"
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#include <boost/shared_ptr.hpp>

namespace my
{
	class WinException : public t3d::Exception
	{
	public:
		static std::basic_string<charT> GetErrorCodeStr(DWORD dwCode);

	public:
		WinException(const std::basic_string<charT> & file, int line, DWORD dwCode);

	public:
		std::basic_string<charT> what(void) const throw();

	protected:
		DWORD m_code;
	};

#define T3D_WINEXCEPT(code) { throw my::WinException( _T(__FILE__), __LINE__, (code) ); }

	class WindowBase
	{
	public:
		static std::basic_string<charT> getWindowMessageStr(UINT message);

	protected:
		HWND m_hwnd;

	public:
		WindowBase(HWND hwnd = NULL);

		virtual ~WindowBase(void);

	public:
		void showWindow(int nShow = SW_NORMAL);

		std::basic_string<charT> getWindowText(void) const;

		void setWindowText(const std::basic_string<charT> winTitle);

		DWORD getWindowStyle(void) const;

		void setWindowStyle(DWORD dwStyle);

		DWORD getWindowExtansionStyle(void) const;

		void setWindowExtansionStyle(DWORD dwExStyle);

		RECT getWindowRect(void) const;

		void setWindowRect(const RECT & rect);

		RECT getClientRect(void) const;

		void setClientRect(const RECT & rect);

		void centerWindow(void);
	};

	class Application;

	class Window : public WindowBase
	{
		friend Application;

	public:
		class MessageListener
		{
		public:
			virtual bool notifyMessage(Window * win, UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lResult) = 0;
		};

	public:
		static BOOL isRegisteredWindowClass(const std::basic_string<charT> winClass, HINSTANCE moduleHandle);

		static void registerWindowClass(const std::basic_string<charT> winClass, HINSTANCE moduleHandle);

	protected:
		typedef std::vector<MessageListener *> MessageListenerList;

		MessageListenerList m_msgListenerList;

	protected:
		Window(const std::basic_string<charT> winClass, const std::basic_string<charT> winTitle, const Application * app);

	public:
		~Window(void);

	public:
		void addMessageListener(MessageListener * listener);

		HWND getHandle(void) const;

		LRESULT onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	};

	typedef boost::shared_ptr<Window> WindowPtr;

	class Application
	{
	public:
		class IdleListener
		{
		public:
			virtual void nodifyIdle(void) = 0;
		};

	protected:
		typedef std::vector<IdleListener *> IdleListenerList;

		IdleListenerList m_idleListenerList;

		typedef std::map<HWND, WindowPtr> WindowPtrMap;

		WindowPtrMap m_wndMap;

		HINSTANCE m_hinst;

	public:
		static Application * s_ptr;

		static Application & getSingleton(void)
		{
			assert(NULL != s_ptr); return *s_ptr;
		}

		static HINSTANCE getModuleHandle(const std::basic_string<charT> moduleName = _T(""));

		static LRESULT CALLBACK onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	public:
		Application(HINSTANCE hinst);

		virtual ~Application(void);

	public:
		Window * createWindow(const std::basic_string<charT> winClass, const std::basic_string<charT> winTitle);

		HINSTANCE getHandle(void) const;

		void addIdleListener(IdleListener * listener);

		int run(void);
	};

	typedef boost::shared_ptr<Application> ApplicationPtr;
}

#endif // __MYWINDOW_H__
