
#ifndef __MYWINDOW_H__
#define __MYWINDOW_H__

#include "myCommon.h"
#include <crtdbg.h>
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

	class Application;

	class Window
	{
		friend Application;

	public:
		static std::basic_string<charT> getWindowMessageStr(UINT message);

		static BOOL isRegisteredWindowClass(const std::basic_string<charT> winClass, HINSTANCE moduleHandle);

		static void registerWindowClass(const std::basic_string<charT> winClass, HINSTANCE moduleHandle);

	protected:
		HWND m_hwnd;

	public:
		Window(HWND hwnd = NULL);

		virtual ~Window(void);

	public:
		virtual LRESULT onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	public:
		HWND getHandle(void) const;

		void showWindow(int nShow = SW_NORMAL);

		void updateWindow(void);

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

		void setWindowPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags);

		void centerWindow(void);

		void destroyWindow(void);

		HDC getDC(void);

		void releaseDC(HDC hdc);
	};

	typedef boost::shared_ptr<Window> WindowPtr;

	typedef std::map<HWND, WindowPtr> WindowPtrMap;

	class Application
	{
	public:
		static Application * s_ptr;

		static Application & getSingleton(void)
		{
			_ASSERT(NULL != s_ptr); return *s_ptr;
		}

		static LRESULT CALLBACK onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	public:
		WindowPtrMap m_wndMap;

		HINSTANCE m_hinst;

	public:
		Application(void);

		virtual ~Application(void);

	public:
		virtual Window * newWindow(HWND hwnd);

		virtual void onIdle(void);

	public:
		Window * createWindow(const std::basic_string<charT> winTitle, const std::basic_string<charT> winClass = _T("MY_WINDOW"));

		HINSTANCE getHandle(void) const;

		std::basic_string<charT> getModuleFileName(void) const;

		int run(void);
	};

	typedef boost::shared_ptr<Application> ApplicationPtr;
}

#endif // __MYWINDOW_H__
