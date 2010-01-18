
#ifndef __MYWINDOW_H__
#define __MYWINDOW_H__

#include "myCommon.h"
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#include <atltypes.h>
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

		DWORD getWindowExStyle(void) const;

		void setWindowExtansionStyle(DWORD dwExStyle);

		CRect getWindowRect(void) const;

		void setWindowRect(const CRect & rect);

		CRect getClientRect(void) const;

		void adjustClientRect(const CRect & rect);

		CRect & screenToClientSelf(CRect & rect);

		CRect & clientToScreenSelf(CRect & rect);

		void centerWindow(void);

		void destroyWindow(void);

		HDC getDC(void);

		void releaseDC(HDC hdc);
	};

	class Application;

	class Window : public WindowBase
	{
		friend Application;

	public:
		static BOOL isRegisteredWindowClass(const std::basic_string<charT> winClass, HINSTANCE moduleHandle);

		static void registerWindowClass(const std::basic_string<charT> winClass, HINSTANCE moduleHandle);

	public:
		class MessageListener
		{
		public:
			virtual BOOL notifyMessage(LRESULT & lResult, Window * win, UINT message, WPARAM wparam, LPARAM lparam) = 0;
		};

	protected:
		MessageListener * m_pMessageListener;

	protected:
		Window(const std::basic_string<charT> winClass, const std::basic_string<charT> winTitle, const Application * app);

	public:
		~Window(void);

	public:
		void setMessageListener(MessageListener * pMessageListener);

		HWND getHandle(void) const;

		LRESULT onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	};

	typedef boost::shared_ptr<Window> WindowPtr;

	typedef std::map<HWND, WindowPtr> WindowPtrMap;

	class Application
	{
	public:
		static Application * s_ptr;

		static Application & getSingleton(void)
		{
			assert(NULL != s_ptr); return *s_ptr;
		}

		static LRESULT CALLBACK onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	public:
		class IdleListener
		{
		public:
			virtual BOOL nodifyIdle(void) = 0;
		};

	protected:
		IdleListener * m_pIdleListener;

	public:
		WindowPtrMap m_wndMap;

		HINSTANCE m_hinst;

	public:
		Application(HINSTANCE hinst = NULL);

		virtual ~Application(void);

	public:
		Window * createWindow(const std::basic_string<charT> winClass, const std::basic_string<charT> winTitle);

		HINSTANCE getHandle(void) const;

		std::basic_string<charT> getModuleFileName(void) const;

		void setIdleListener(IdleListener * pIdleListener);

		int run(void);
	};

	typedef boost::shared_ptr<Application> ApplicationPtr;
}

#endif // __MYWINDOW_H__
