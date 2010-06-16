
#ifndef __MYWINDOW_H__
#define __MYWINDOW_H__

#include "myCommon.h"
#include <crtdbg.h>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#include <atltypes.h>
#include <memory>

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

	class CriticalSection
	{
	protected:
		CRITICAL_SECTION m_section;

	public:
		CriticalSection(void);

		~CriticalSection(void);

		void enter(void);

		void leave(void);

		BOOL TryEnterCriticalSection(void);
	};

	class Thread
	{
	protected:
		HANDLE m_hThread;

	protected:
		static DWORD WINAPI ThreadProc(__in LPVOID lpParameter);

	public:
		Thread(void);

		~Thread(void);

		void CreateThread(DWORD dwCreationFlags = CREATE_SUSPENDED);

		void ResumeThread(void);

		void SuspendThread(void);

		void SetThreadPriority(int nPriority);

		int GetThreadPriority(void);

		void TerminateThread(DWORD dwExitCode);

		bool WaitForThreadStopped(DWORD dwMilliseconds = INFINITE);

	public:
		virtual DWORD onProc(void) = 0;
	};

	class ProfileBase
	{
	public:
		virtual ~ProfileBase(void);

	public:
		virtual void load(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName) = 0;

		virtual void save(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName) const = 0;
	};

	typedef std::tr1::shared_ptr<ProfileBase> ProfileBasePtr;

	class ProfileInt : public ProfileBase
	{
	protected:
		int m_value;

	public:
		void setValue(int nValue)
		{
			m_value = nValue;
		}

		int getValue(void) const
		{
			return m_value;
		}

	public:
		ProfileInt(int nDefault);

	public:
		void load(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName);

		void save(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName) const;
	};

	class ProfileString : public ProfileBase
	{
	protected:
		std::basic_string<charT> m_value;

	public:
		void setValue(LPCTSTR lpValue)
		{
			m_value = lpValue;
		}

		const std::basic_string<charT> & getValue(void) const
		{
			return m_value;
		}

	public:
		ProfileString(LPCTSTR lpDefault);

	public:
		void load(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName);

		void save(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName) const;
	};

	class Config : protected std::map<std::basic_string<charT>, ProfileBasePtr>
	{
	protected:
		std::basic_string<charT> m_appName;

	public:
		void setAppName(LPCTSTR lpAppName)
		{
			m_appName = lpAppName;
		}

		const std::basic_string<charT> & getAppName(void) const
		{
			return m_appName;
		}

	public:
		Config(LPCTSTR lpAppName = _T("Config"));

	public:
		void addInt(LPCTSTR lpKeyName, int nDefault);

		void setInt(LPCTSTR lpKeyName, int nValue);

		int getInt(LPCTSTR lpKeyName) const;

		int getIntOrDefault(LPCTSTR lpKeyName, int nDefault) const;

		void addString(LPCTSTR lpKeyName, LPCTSTR lpDefault);

		void setString(LPCTSTR lpKeyName, LPCTSTR lpValue);

		const std::basic_string<charT> & getString(LPCTSTR lpKeyName) const;

		const std::basic_string<charT> & getStringOrDefault(LPCTSTR lpKeyName, const std::basic_string<charT> & strDefault) const;

	public:
		void load(LPCTSTR lpFileName);

		void save(LPCTSTR lpFileName) const;
	};

	class Dialog;

	typedef std::map<HWND, Dialog *> DialogMap;

	class Dialog
	{
	public:
		static DialogMap s_dlgMap;

		static INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		HINSTANCE m_hInstance;

		LPCTSTR m_lpTemplateName;

		HWND m_hWndParent;

		HWND m_hdlg;

	public:
		virtual INT_PTR onProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		Dialog(HINSTANCE hInstance, LPCTSTR lpTemplateName, HWND hWndParent = NULL);

		~Dialog(void);

		INT_PTR doModel(void);

		void endDialog(INT_PTR nResult);
	};

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
		Window(HWND hwnd);

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

		void InvalidateRect(CONST RECT * lpRect = NULL, BOOL bErase = FALSE);

		void postMessage(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0);

		LRESULT sendMessage(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0);
	};

	typedef std::tr1::shared_ptr<Window> WindowPtr;

	typedef std::map<HWND, WindowPtr> WindowPtrMap;

	class Application
	{
	public:
		static Application * s_ptr;

		static Application * getSingletonPtr(void)
		{
			_ASSERT(NULL != s_ptr); return s_ptr;
		}

		static Application & getSingleton(void)
		{
			return * getSingletonPtr();
		}

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	public:
		WindowPtrMap m_wndMap;

		HINSTANCE m_hinst;

	public:
		Application(HINSTANCE hInstance = NULL);

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

	typedef std::tr1::shared_ptr<Application> ApplicationPtr;
}

#endif // __MYWINDOW_H__
