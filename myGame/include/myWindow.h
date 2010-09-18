
#ifndef __MYWINDOW_H__
#define __MYWINDOW_H__

#include "myCommon.h"
#include <crtdbg.h>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#include <atltypes.h>
#include <atlwin.h>
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

	class CriticalSectionLock
	{
	protected:
		CriticalSection & m_cs;

	public:
		CriticalSectionLock(CriticalSection & cs)
			: m_cs(cs)
		{
			m_cs.enter();
		}

		~CriticalSectionLock(void)
		{
			m_cs.leave();
		}
	};

	class Event
	{
	public:
		HANDLE m_hevent;

	public:
		Event(
			LPSECURITY_ATTRIBUTES lpEventAttributes = NULL,
			BOOL bManualReset = FALSE,
			BOOL bInitialState = FALSE,
			LPCTSTR lpName = NULL);

		~Event(void);

		void ResetEvent(void);

		void SetEvent(void);

		bool WaitEvent(DWORD dwMilliseconds = INFINITE);
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

	typedef boost::shared_ptr<ProfileBase> ProfileBasePtr;

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

		virtual ~Config(void);

	public:
		void addInt(const std::basic_string<t3d::charT> & keyName, int nDefault);

		void setInt(const std::basic_string<t3d::charT> & keyName, int nValue);

		int getInt(const std::basic_string<t3d::charT> & keyName) const;

		int getIntOrDefault(const std::basic_string<t3d::charT> & keyName, int nDefault) const;

		void addString(const std::basic_string<t3d::charT> & keyName, LPCTSTR lpDefault);

		void setString(const std::basic_string<t3d::charT> & keyName, LPCTSTR lpValue);

		const std::basic_string<charT> & getString(const std::basic_string<t3d::charT> & keyName) const;

		const std::basic_string<charT> & getStringOrDefault(const std::basic_string<t3d::charT> & keyName, const std::basic_string<charT> & strDefault) const;

	public:
		void load(const std::basic_string<charT> & fileName);

		void save(const std::basic_string<charT> & fileName) const;
	};

	//class Dialog;

	//typedef std::map<HWND, Dialog *> DialogMap;

	//class Dialog
	//{
	//public:
	//	static DialogMap s_dlgMap;

	//	static INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//public:
	//	HINSTANCE m_hInstance;

	//	LPCTSTR m_lpTemplateName;

	//	HWND m_hWndParent;

	//	HWND m_hdlg;

	//public:
	//	virtual INT_PTR onProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//public:
	//	Dialog(HINSTANCE hInstance, LPCTSTR lpTemplateName, HWND hWndParent = NULL);

	//	~Dialog(void);

	//	INT_PTR doModel(void);

	//	void endDialog(INT_PTR nResult);
	//};

	class Window
		: public CWindowImpl<Window, CWindow, CWinTraits<WS_OVERLAPPEDWINDOW, 0> >
	{
	public:
		static std::basic_string<charT> getWindowMessageStr(UINT message);

	public:
		LONG SetStyle(LONG dwStyle);

		LONG SetExStyle(LONG dwExStyle);

		BOOL AdjustClientRect(const CRect & rect);

	public:
		DECLARE_WND_CLASS_EX(GetWndClassName(), CS_HREDRAW | CS_VREDRAW, -1)

		BEGIN_MSG_MAP(Window)
		END_MSG_MAP()

		void OnFinalMessage(HWND hwnd);
	};

	typedef boost::shared_ptr<Window> WindowPtr;

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

	public:
		WindowPtr m_wnd;

		HINSTANCE m_hinst;

	public:
		Application(HINSTANCE hInstance = ::GetModuleHandle(NULL));

		virtual ~Application(void);

		HINSTANCE getHandle(void) const;

		static std::basic_string<charT> getModuleFileName(void);

		virtual WindowPtr newWindow(void);

		int run(void);

	public:
		virtual void onIdle(void);
	};

	typedef boost::shared_ptr<Application> ApplicationPtr;
}

#endif // __MYWINDOW_H__
