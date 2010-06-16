
#include "stdafx.h"
#include "myWindow.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "libc.h"

namespace my
{
	std::basic_string<charT> WinException::GetErrorCodeStr(DWORD dwCode)
	{
		std::basic_string<charT> ret;
		ret.resize(MAX_PATH);
		ret.resize(::FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwCode, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), &ret[0], ret.size(), NULL));

		if(ret.empty())
		{
			return _T("unknown windows error");
		}

		return ret;
	}

	WinException::WinException(const std::basic_string<charT> & file, int line, DWORD dwCode)
		: t3d::Exception(file, line)
		, m_code(dwCode)
	{
	}

	CriticalSection::CriticalSection(void)
	{
		::InitializeCriticalSection(&m_section);
	}

	CriticalSection::~CriticalSection(void)
	{
		::DeleteCriticalSection(&m_section);
	}

	void CriticalSection::enter(void)
	{
		::EnterCriticalSection(&m_section);
	}

	void CriticalSection::leave(void)
	{
		::LeaveCriticalSection(&m_section);
	}

	BOOL CriticalSection::TryEnterCriticalSection(void)
	{
		return ::TryEnterCriticalSection(&m_section);
	}

	DWORD WINAPI Thread::ThreadProc(__in LPVOID lpParameter)
	{
		Thread * pThread = reinterpret_cast<Thread *>(lpParameter);

		return pThread->onProc();
	}

	Thread::Thread(void)
		: m_hThread(NULL)
	{
	}

	Thread::~Thread(void)
	{
		if(NULL != m_hThread)
		{
			_ASSERT(WAIT_TIMEOUT != ::WaitForSingleObject(m_hThread, 0));

			//// The thread object remains in the system until the thread has terminated
			//// and all handles to it have been closed through a call to CloseHandle.
			//::CloseHandle(m_hThread);
		}
	}

	void Thread::CreateThread(DWORD dwCreationFlags /*= CREATE_SUSPENDED*/)
	{
		_ASSERT(NULL == m_hThread);

		if(NULL == (m_hThread = ::CreateThread(NULL, 0, ThreadProc, this, dwCreationFlags, NULL)))
		{
			T3D_WINEXCEPT(::GetLastError());
		}
	}

	void Thread::ResumeThread(void)
	{
		_ASSERT(NULL != m_hThread);

		if(-1 == ::ResumeThread(m_hThread))
		{
			T3D_WINEXCEPT(::GetLastError());
		}
	}

	void Thread::SuspendThread(void)
	{
		_ASSERT(NULL != m_hThread);

		if(-1 == ::SuspendThread(m_hThread))
		{
			T3D_WINEXCEPT(::GetLastError());
		}
	}

	void Thread::SetThreadPriority(int nPriority)
	{
		_ASSERT(NULL != m_hThread);

		if(!::SetThreadPriority(m_hThread, nPriority))
		{
			T3D_WINEXCEPT(::GetLastError());
		}
	}

	int Thread::GetThreadPriority(void)
	{
		_ASSERT(NULL != m_hThread);

		int nRet = ::GetThreadPriority(m_hThread);

		if(THREAD_PRIORITY_ERROR_RETURN == nRet)
		{
			T3D_WINEXCEPT(::GetLastError());
		}

		return nRet;
	}

	void Thread::TerminateThread(DWORD dwExitCode)
	{
		_ASSERT(!"you should not use TerminateThread anymore");

		_ASSERT(NULL != m_hThread);

		if(!::TerminateThread(m_hThread, dwExitCode))
		{
			//T3D_WINEXCEPT(::GetLastError());
		}
	}

	bool Thread::WaitForThreadStopped(DWORD dwMilliseconds /*= INFINITE*/)
	{
		if(WAIT_TIMEOUT == ::WaitForSingleObject(m_hThread, dwMilliseconds))
		{
			return false;
		}

		return true;
	}

	//DWORD Thread::onProc(void)
	//{
	//	return 0;
	//}

	ProfileBase::~ProfileBase(void)
	{
	}

	ProfileInt::ProfileInt(int nDefault)
		: m_value(nDefault)
	{
	}

	void ProfileInt::load(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName)
	{
		m_value = ::GetPrivateProfileInt(lpAppName, lpKeyName, m_value, lpFileName);
	}

	void ProfileInt::save(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName) const
	{
		::WritePrivateProfileString(lpAppName, lpKeyName, str_printf(_T("%d"), m_value).c_str(), lpFileName);
	}

	ProfileString::ProfileString(LPCTSTR lpDefault)
		: m_value(lpDefault)
	{
	}

	void ProfileString::load(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName)
	{
		std::basic_string<charT> tmpValue;
		for(tmpValue.resize(512); tmpValue.size() == ::GetPrivateProfileString(
			lpAppName, lpKeyName, m_value.c_str(), &tmpValue[0], tmpValue.size(), lpFileName) + 1; tmpValue.resize(tmpValue.size() + 512))
		{
		}
		m_value = tmpValue;
	}

	void ProfileString::save(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpFileName) const
	{
		::WritePrivateProfileString(lpAppName, lpKeyName, m_value.c_str(), lpFileName);
	}

	Config::Config(LPCTSTR lpAppName /*= _T("Config")*/)
		: m_appName(lpAppName)
	{
	}

	void Config::addInt(LPCTSTR lpKeyName, int nDefault)
	{
		_ASSERT(end() == find(lpKeyName));

		insert(value_type(lpKeyName, ProfileBasePtr(new ProfileInt(nDefault))));
	}

	void Config::setInt(LPCTSTR lpKeyName, int nValue)
	{
		_ASSERT(end() != find(lpKeyName));

		return (std::tr1::dynamic_pointer_cast<ProfileInt, ProfileBase>(find(lpKeyName)->second))->setValue(nValue);
	}

	int Config::getInt(LPCTSTR lpKeyName) const
	{
		_ASSERT(end() != find(lpKeyName));

		return (std::tr1::dynamic_pointer_cast<ProfileInt, ProfileBase>(find(lpKeyName)->second))->getValue();
	}

	int Config::getIntOrDefault(LPCTSTR lpKeyName, int nDefault) const
	{
		const_iterator profile_iter = find(lpKeyName);
		if(end() == profile_iter)
		{
			return nDefault;
		}
		return (std::tr1::dynamic_pointer_cast<ProfileInt, ProfileBase>(profile_iter->second))->getValue();
	}

	void Config::addString(LPCTSTR lpKeyName, LPCTSTR lpDefault)
	{
		_ASSERT(end() == find(lpKeyName));

		insert(value_type(lpKeyName, ProfileBasePtr(new ProfileString(lpDefault))));
	}

	void Config::setString(LPCTSTR lpKeyName, LPCTSTR lpValue)
	{
		_ASSERT(end() != find(lpKeyName));

		return (std::tr1::dynamic_pointer_cast<ProfileString, ProfileBase>(find(lpKeyName)->second))->setValue(lpValue);
	}

	const std::basic_string<charT> & Config::getString(LPCTSTR lpKeyName) const
	{
		_ASSERT(end() != find(lpKeyName));

		return (std::tr1::dynamic_pointer_cast<ProfileString, ProfileBase>(find(lpKeyName)->second))->getValue();
	}

	const std::basic_string<charT> & Config::getStringOrDefault(LPCTSTR lpKeyName, const std::basic_string<charT> & strDefault) const
	{
		const_iterator profile_iter = find(lpKeyName);
		if(end() == profile_iter)
		{
			return strDefault;
		}
		return (std::tr1::dynamic_pointer_cast<ProfileString, ProfileBase>(profile_iter->second))->getValue();
	}

	void Config::load(LPCTSTR lpFileName)
	{
		iterator profile_iter = begin();
		for(; profile_iter != end(); profile_iter++)
		{
			profile_iter->second->load(getAppName().c_str(), profile_iter->first.c_str(), lpFileName);
		}
	}

	void Config::save(LPCTSTR lpFileName) const
	{
		const_iterator profile_iter = begin();
		for(; profile_iter != end(); profile_iter++)
		{
			profile_iter->second->save(getAppName().c_str(), profile_iter->first.c_str(), lpFileName);
		}
	}

	DialogMap Dialog::s_dlgMap;

	INT_PTR CALLBACK Dialog::DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if(uMsg == WM_INITDIALOG)
		{
			Dialog * pDialog = reinterpret_cast<Dialog *>(lParam);

			_ASSERT(NULL == pDialog->m_hdlg);

			pDialog->m_hdlg = hwndDlg;

			_ASSERT(s_dlgMap.end() == s_dlgMap.find(hwndDlg));

			s_dlgMap.insert(DialogMap::value_type(hwndDlg, pDialog));
		}

		DialogMap::iterator dlgIter = s_dlgMap.find(hwndDlg);

		if(dlgIter != s_dlgMap.end())
		{
			return dlgIter->second->onProc(hwndDlg, uMsg, wParam, lParam);
		}

		return FALSE;
	}

	INT_PTR Dialog::onProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		_ASSERT(m_hdlg == hwndDlg);

		switch(uMsg)
		{
		case WM_NCDESTROY:
			{
				DialogMap::iterator dlgIter = s_dlgMap.find(m_hdlg);

				_ASSERT(dlgIter != s_dlgMap.end());

				s_dlgMap.erase(dlgIter);

				m_hdlg = NULL;

				return FALSE;
			}

		case WM_INITDIALOG:
			{
				Window(hwndDlg).centerWindow();
				return TRUE;
			}

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case IDOK:
			case IDCANCEL:
				endDialog(wParam);
				return TRUE;
			}
			break;
		}

		return FALSE;
		UNREFERENCED_PARAMETER(lParam);
	}

	Dialog::Dialog(HINSTANCE hInstance, LPCTSTR lpTemplateName, HWND hWndParent /*= NULL*/)
		: m_hInstance(hInstance)
		, m_lpTemplateName(lpTemplateName)
		, m_hWndParent(hWndParent)
		, m_hdlg(NULL)
	{
	}

	Dialog::~Dialog(void)
	{
		//_ASSERT(NULL == m_hdlg);
	}

	INT_PTR Dialog::doModel(void)
	{
		INT_PTR nResult = ::DialogBoxParam(
			m_hInstance, m_lpTemplateName, m_hWndParent, my::Dialog::DialogProc, (LPARAM)this);

		return nResult;
	}

	void Dialog::endDialog(INT_PTR nResult)
	{
		_ASSERT(NULL != m_hdlg);

		VERIFY(EndDialog(m_hdlg, nResult));
	}

	std::basic_string<charT> WinException::what(void) const throw()
	{
		return GetErrorCodeStr(m_code);
	}

	std::basic_string<charT> Window::getWindowMessageStr(UINT message)
	{
		switch(message)
		{
		case WM_NULL:
			return std::basic_string<charT>(_T("WM_NULL"));
		case WM_CREATE:
			return std::basic_string<charT>(_T("WM_CREATE"));
		case WM_DESTROY:
			return std::basic_string<charT>(_T("WM_DESTROY"));
		case WM_MOVE:
			return std::basic_string<charT>(_T("WM_MOVE"));
		case WM_SIZE:
			return std::basic_string<charT>(_T("WM_SIZE"));
		case WM_ACTIVATE:
			return std::basic_string<charT>(_T("WM_ACTIVATE"));
		case WM_SETFOCUS:
			return std::basic_string<charT>(_T("WM_SETFOCUS"));
		case WM_KILLFOCUS:
			return std::basic_string<charT>(_T("WM_KILLFOCUS"));
		case WM_ENABLE:
			return std::basic_string<charT>(_T("WM_ENABLE"));
		case WM_SETREDRAW:
			return std::basic_string<charT>(_T("WM_SETREDRAW"));
		case WM_SETTEXT:
			return std::basic_string<charT>(_T("WM_SETTEXT"));
		case WM_GETTEXT:
			return std::basic_string<charT>(_T("WM_GETTEXT"));
		case WM_GETTEXTLENGTH:
			return std::basic_string<charT>(_T("WM_GETTEXTLENGTH"));
		case WM_PAINT:
			return std::basic_string<charT>(_T("WM_PAINT"));
		case WM_CLOSE:
			return std::basic_string<charT>(_T("WM_CLOSE"));
#ifndef _WIN32_WCE
		case WM_QUERYENDSESSION:
			return std::basic_string<charT>(_T("WM_QUERYENDSESSION"));
		case WM_QUERYOPEN:
			return std::basic_string<charT>(_T("WM_QUERYOPEN"));
		case WM_ENDSESSION:
			return std::basic_string<charT>(_T("WM_ENDSESSION"));
#endif
		case WM_QUIT:
			return std::basic_string<charT>(_T("WM_QUIT"));
		case WM_ERASEBKGND:
			return std::basic_string<charT>(_T("WM_ERASEBKGND"));
		case WM_SYSCOLORCHANGE:
			return std::basic_string<charT>(_T("WM_SYSCOLORCHANGE"));
		case WM_SHOWWINDOW:
			return std::basic_string<charT>(_T("WM_SHOWWINDOW"));
		case WM_WININICHANGE:
			return std::basic_string<charT>(_T("WM_WININICHANGE"));
#if(WINVER >= 0x0400)
		//case WM_SETTINGCHANGE:
		//	return std::basic_string<charT>(_T("WM_SETTINGCHANGE"));
#endif /* WINVER >= 0x0400 */
		case WM_DEVMODECHANGE:
			return std::basic_string<charT>(_T("WM_DEVMODECHANGE"));
		case WM_ACTIVATEAPP:
			return std::basic_string<charT>(_T("WM_ACTIVATEAPP"));
		case WM_FONTCHANGE:
			return std::basic_string<charT>(_T("WM_FONTCHANGE"));
		case WM_TIMECHANGE:
			return std::basic_string<charT>(_T("WM_TIMECHANGE"));
		case WM_CANCELMODE:
			return std::basic_string<charT>(_T("WM_CANCELMODE"));
		case WM_SETCURSOR:
			return std::basic_string<charT>(_T("WM_SETCURSOR"));
		case WM_MOUSEACTIVATE:
			return std::basic_string<charT>(_T("WM_MOUSEACTIVATE"));
		case WM_CHILDACTIVATE:
			return std::basic_string<charT>(_T("WM_CHILDACTIVATE"));
		case WM_QUEUESYNC:
			return std::basic_string<charT>(_T("WM_QUEUESYNC"));
		case WM_GETMINMAXINFO:
			return std::basic_string<charT>(_T("WM_GETMINMAXINFO"));
		case WM_PAINTICON:
			return std::basic_string<charT>(_T("WM_PAINTICON"));
		case WM_ICONERASEBKGND:
			return std::basic_string<charT>(_T("WM_ICONERASEBKGND"));
		case WM_NEXTDLGCTL:
			return std::basic_string<charT>(_T("WM_NEXTDLGCTL"));
		case WM_SPOOLERSTATUS:
			return std::basic_string<charT>(_T("WM_SPOOLERSTATUS"));
		case WM_DRAWITEM:
			return std::basic_string<charT>(_T("WM_DRAWITEM"));
		case WM_MEASUREITEM:
			return std::basic_string<charT>(_T("WM_MEASUREITEM"));
		case WM_DELETEITEM:
			return std::basic_string<charT>(_T("WM_DELETEITEM"));
		case WM_VKEYTOITEM:
			return std::basic_string<charT>(_T("WM_VKEYTOITEM"));
		case WM_CHARTOITEM:
			return std::basic_string<charT>(_T("WM_CHARTOITEM"));
		case WM_SETFONT:
			return std::basic_string<charT>(_T("WM_SETFONT"));
		case WM_GETFONT:
			return std::basic_string<charT>(_T("WM_GETFONT"));
		case WM_SETHOTKEY:
			return std::basic_string<charT>(_T("WM_SETHOTKEY"));
		case WM_GETHOTKEY:
			return std::basic_string<charT>(_T("WM_GETHOTKEY"));
		case WM_QUERYDRAGICON:
			return std::basic_string<charT>(_T("WM_QUERYDRAGICON"));
		case WM_COMPAREITEM:
			return std::basic_string<charT>(_T("WM_COMPAREITEM"));
#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
		case WM_GETOBJECT:
			return std::basic_string<charT>(_T("WM_GETOBJECT"));
#endif
#endif /* WINVER >= 0x0500 */
		case WM_COMPACTING:
			return std::basic_string<charT>(_T("WM_COMPACTING"));
		case WM_COMMNOTIFY:
			return std::basic_string<charT>(_T("WM_COMMNOTIFY"));
		case WM_WINDOWPOSCHANGING:
			return std::basic_string<charT>(_T("WM_WINDOWPOSCHANGING"));
		case WM_WINDOWPOSCHANGED:
			return std::basic_string<charT>(_T("WM_WINDOWPOSCHANGED"));
		case WM_POWER:
			return std::basic_string<charT>(_T("WM_POWER"));
		case WM_COPYDATA:
			return std::basic_string<charT>(_T("WM_COPYDATA"));
		case WM_CANCELJOURNAL:
			return std::basic_string<charT>(_T("WM_CANCELJOURNAL"));
#if(WINVER >= 0x0400)
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0400)
		case WM_NOTIFY:
			return std::basic_string<charT>(_T("WM_NOTIFY"));
		case WM_INPUTLANGCHANGEREQUEST:
			return std::basic_string<charT>(_T("WM_INPUTLANGCHANGEREQUEST"));
		case WM_INPUTLANGCHANGE:
			return std::basic_string<charT>(_T("WM_INPUTLANGCHANGE"));
		case WM_TCARD:
			return std::basic_string<charT>(_T("WM_TCARD"));
		case WM_HELP:
			return std::basic_string<charT>(_T("WM_HELP"));
		case WM_USERCHANGED:
			return std::basic_string<charT>(_T("WM_USERCHANGED"));
		case WM_NOTIFYFORMAT:
			return std::basic_string<charT>(_T("WM_NOTIFYFORMAT"));
		case WM_CONTEXTMENU:
			return std::basic_string<charT>(_T("WM_CONTEXTMENU"));
		case WM_STYLECHANGING:
			return std::basic_string<charT>(_T("WM_STYLECHANGING"));
		case WM_STYLECHANGED:
			return std::basic_string<charT>(_T("WM_STYLECHANGED"));
		case WM_DISPLAYCHANGE:
			return std::basic_string<charT>(_T("WM_DISPLAYCHANGE"));
		case WM_GETICON:
			return std::basic_string<charT>(_T("WM_GETICON"));
		case WM_SETICON:
			return std::basic_string<charT>(_T("WM_SETICON"));
#endif /* WINVER >= 0x0400 */
		case WM_NCCREATE:
			return std::basic_string<charT>(_T("WM_NCCREATE"));
		case WM_NCDESTROY:
			return std::basic_string<charT>(_T("WM_NCDESTROY"));
		case WM_NCCALCSIZE:
			return std::basic_string<charT>(_T("WM_NCCALCSIZE"));
		case WM_NCHITTEST:
			return std::basic_string<charT>(_T("WM_NCHITTEST"));
		case WM_NCPAINT:
			return std::basic_string<charT>(_T("WM_NCPAINT"));
		case WM_NCACTIVATE:
			return std::basic_string<charT>(_T("WM_NCACTIVATE"));
		case WM_GETDLGCODE:
			return std::basic_string<charT>(_T("WM_GETDLGCODE"));
#ifndef _WIN32_WCE
		case WM_SYNCPAINT:
			return std::basic_string<charT>(_T("WM_SYNCPAINT"));
#endif
		case WM_NCMOUSEMOVE:
			return std::basic_string<charT>(_T("WM_NCMOUSEMOVE"));
		case WM_NCLBUTTONDOWN:
			return std::basic_string<charT>(_T("WM_NCLBUTTONDOWN"));
		case WM_NCLBUTTONUP:
			return std::basic_string<charT>(_T("WM_NCLBUTTONUP"));
		case WM_NCLBUTTONDBLCLK:
			return std::basic_string<charT>(_T("WM_NCLBUTTONDBLCLK"));
		case WM_NCRBUTTONDOWN:
			return std::basic_string<charT>(_T("WM_NCRBUTTONDOWN"));
		case WM_NCRBUTTONUP:
			return std::basic_string<charT>(_T("WM_NCRBUTTONUP"));
		case WM_NCRBUTTONDBLCLK:
			return std::basic_string<charT>(_T("WM_NCRBUTTONDBLCLK"));
		case WM_NCMBUTTONDOWN:
			return std::basic_string<charT>(_T("WM_NCMBUTTONDOWN"));
		case WM_NCMBUTTONUP:
			return std::basic_string<charT>(_T("WM_NCMBUTTONUP"));
		case WM_NCMBUTTONDBLCLK:
			return std::basic_string<charT>(_T("WM_NCMBUTTONDBLCLK"));
#if(_WIN32_WINNT >= 0x0500)
		case WM_NCXBUTTONDOWN:
			return std::basic_string<charT>(_T("WM_NCXBUTTONDOWN"));
		case WM_NCXBUTTONUP:
			return std::basic_string<charT>(_T("WM_NCXBUTTONUP"));
		case WM_NCXBUTTONDBLCLK:
			return std::basic_string<charT>(_T("WM_NCXBUTTONDBLCLK"));
#endif /* _WIN32_WINNT >= 0x0500 */
#if(_WIN32_WINNT >= 0x0501)
		case WM_INPUT:
			return std::basic_string<charT>(_T("WM_INPUT"));
#endif /* _WIN32_WINNT >= 0x0501 */
		case WM_KEYFIRST:
			return std::basic_string<charT>(_T("WM_KEYFIRST"));
		//case WM_KEYDOWN:
		//	return std::basic_string<charT>(_T("WM_KEYDOWN"));
		case WM_KEYUP:
			return std::basic_string<charT>(_T("WM_KEYUP"));
		case WM_CHAR:
			return std::basic_string<charT>(_T("WM_CHAR"));
		case WM_DEADCHAR:
			return std::basic_string<charT>(_T("WM_DEADCHAR"));
		case WM_SYSKEYDOWN:
			return std::basic_string<charT>(_T("WM_SYSKEYDOWN"));
		case WM_SYSKEYUP:
			return std::basic_string<charT>(_T("WM_SYSKEYUP"));
		case WM_SYSCHAR:
			return std::basic_string<charT>(_T("WM_SYSCHAR"));
		case WM_SYSDEADCHAR:
			return std::basic_string<charT>(_T("WM_SYSDEADCHAR"));
#if(_WIN32_WINNT >= 0x0501)
		case WM_UNICHAR:
			return std::basic_string<charT>(_T("WM_UNICHAR"));
		//case WM_KEYLAST:
		//	return std::basic_string<charT>(_T("WM_KEYLAST"));
#else
		case WM_KEYLAST:
			return std::basic_string<charT>(_T("WM_KEYLAST"));
#endif /* _WIN32_WINNT >= 0x0501 */
#if(WINVER >= 0x0400)
		case WM_IME_STARTCOMPOSITION:
			return std::basic_string<charT>(_T("WM_IME_STARTCOMPOSITION"));
		case WM_IME_ENDCOMPOSITION:
			return std::basic_string<charT>(_T("WM_IME_ENDCOMPOSITION"));
		case WM_IME_COMPOSITION:
			return std::basic_string<charT>(_T("WM_IME_COMPOSITION"));
		//case WM_IME_KEYLAST:
		//	return std::basic_string<charT>(_T("WM_IME_KEYLAST"));
#endif /* WINVER >= 0x0400 */
		case WM_INITDIALOG:
			return std::basic_string<charT>(_T("WM_INITDIALOG"));
		case WM_COMMAND:
			return std::basic_string<charT>(_T("WM_COMMAND"));
		case WM_SYSCOMMAND:
			return std::basic_string<charT>(_T("WM_SYSCOMMAND"));
		case WM_TIMER:
			return std::basic_string<charT>(_T("WM_TIMER"));
		case WM_HSCROLL:
			return std::basic_string<charT>(_T("WM_HSCROLL"));
		case WM_VSCROLL:
			return std::basic_string<charT>(_T("WM_VSCROLL"));
		case WM_INITMENU:
			return std::basic_string<charT>(_T("WM_INITMENU"));
		case WM_INITMENUPOPUP:
			return std::basic_string<charT>(_T("WM_INITMENUPOPUP"));
		case WM_MENUSELECT:
			return std::basic_string<charT>(_T("WM_MENUSELECT"));
		case WM_MENUCHAR:
			return std::basic_string<charT>(_T("WM_MENUCHAR"));
		case WM_ENTERIDLE:
			return std::basic_string<charT>(_T("WM_ENTERIDLE"));
#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
		case WM_MENURBUTTONUP:
			return std::basic_string<charT>(_T("WM_MENURBUTTONUP"));
		case WM_MENUDRAG:
			return std::basic_string<charT>(_T("WM_MENUDRAG"));
		case WM_MENUGETOBJECT:
			return std::basic_string<charT>(_T("WM_MENUGETOBJECT"));
		case WM_UNINITMENUPOPUP:
			return std::basic_string<charT>(_T("WM_UNINITMENUPOPUP"));
		case WM_MENUCOMMAND:
			return std::basic_string<charT>(_T("WM_MENUCOMMAND"));
#ifndef _WIN32_WCE
#if(_WIN32_WINNT >= 0x0500)
		case WM_CHANGEUISTATE:
			return std::basic_string<charT>(_T("WM_CHANGEUISTATE"));
		case WM_UPDATEUISTATE:
			return std::basic_string<charT>(_T("WM_UPDATEUISTATE"));
		case WM_QUERYUISTATE:
			return std::basic_string<charT>(_T("WM_QUERYUISTATE"));
#if(_WIN32_WINNT >= 0x0501)
#endif /* _WIN32_WINNT >= 0x0501 */
#endif /* _WIN32_WINNT >= 0x0500 */
#endif
#endif
#endif /* WINVER >= 0x0500 */
		case WM_CTLCOLORMSGBOX:
			return std::basic_string<charT>(_T("WM_CTLCOLORMSGBOX"));
		case WM_CTLCOLOREDIT:
			return std::basic_string<charT>(_T("WM_CTLCOLOREDIT"));
		case WM_CTLCOLORLISTBOX:
			return std::basic_string<charT>(_T("WM_CTLCOLORLISTBOX"));
		case WM_CTLCOLORBTN:
			return std::basic_string<charT>(_T("WM_CTLCOLORBTN"));
		case WM_CTLCOLORDLG:
			return std::basic_string<charT>(_T("WM_CTLCOLORDLG"));
		case WM_CTLCOLORSCROLLBAR:
			return std::basic_string<charT>(_T("WM_CTLCOLORSCROLLBAR"));
		case WM_CTLCOLORSTATIC:
			return std::basic_string<charT>(_T("WM_CTLCOLORSTATIC"));
		case MN_GETHMENU:
			return std::basic_string<charT>(_T("MN_GETHMENU"));
		case WM_MOUSEFIRST:
			return std::basic_string<charT>(_T("WM_MOUSEFIRST"));
		//case WM_MOUSEMOVE:
		//	return std::basic_string<charT>(_T("WM_MOUSEMOVE"));
		case WM_LBUTTONDOWN:
			return std::basic_string<charT>(_T("WM_LBUTTONDOWN"));
		case WM_LBUTTONUP:
			return std::basic_string<charT>(_T("WM_LBUTTONUP"));
		case WM_LBUTTONDBLCLK:
			return std::basic_string<charT>(_T("WM_LBUTTONDBLCLK"));
		case WM_RBUTTONDOWN:
			return std::basic_string<charT>(_T("WM_RBUTTONDOWN"));
		case WM_RBUTTONUP:
			return std::basic_string<charT>(_T("WM_RBUTTONUP"));
		case WM_RBUTTONDBLCLK:
			return std::basic_string<charT>(_T("WM_RBUTTONDBLCLK"));
		case WM_MBUTTONDOWN:
			return std::basic_string<charT>(_T("WM_MBUTTONDOWN"));
		case WM_MBUTTONUP:
			return std::basic_string<charT>(_T("WM_MBUTTONUP"));
		case WM_MBUTTONDBLCLK:
			return std::basic_string<charT>(_T("WM_MBUTTONDBLCLK"));
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
		case WM_MOUSEWHEEL:
			return std::basic_string<charT>(_T("WM_MOUSEWHEEL"));
#endif
#if (_WIN32_WINNT >= 0x0500)
		case WM_XBUTTONDOWN:
			return std::basic_string<charT>(_T("WM_XBUTTONDOWN"));
		case WM_XBUTTONUP:
			return std::basic_string<charT>(_T("WM_XBUTTONUP"));
		case WM_XBUTTONDBLCLK:
			return std::basic_string<charT>(_T("WM_XBUTTONDBLCLK"));
#endif
#if (_WIN32_WINNT >= 0x0500)
		case WM_MOUSELAST:
			return std::basic_string<charT>(_T("WM_MOUSELAST"));
#elif (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
		case WM_MOUSELAST:
			return std::basic_string<charT>(_T("WM_MOUSELAST"));
#else
		//case WM_MOUSELAST:
		//	return std::basic_string<charT>(_T("WM_MOUSELAST"));
#endif /* (_WIN32_WINNT >= 0x0500) */
#if(_WIN32_WINNT >= 0x0400)
#endif /* _WIN32_WINNT >= 0x0400 */
#if(_WIN32_WINNT >= 0x0500)
#endif /* _WIN32_WINNT >= 0x0500 */
		case WM_PARENTNOTIFY:
			return std::basic_string<charT>(_T("WM_PARENTNOTIFY"));
		case WM_ENTERMENULOOP:
			return std::basic_string<charT>(_T("WM_ENTERMENULOOP"));
		case WM_EXITMENULOOP:
			return std::basic_string<charT>(_T("WM_EXITMENULOOP"));
#if(WINVER >= 0x0400)
		case WM_NEXTMENU:
			return std::basic_string<charT>(_T("WM_NEXTMENU"));
		case WM_SIZING:
			return std::basic_string<charT>(_T("WM_SIZING"));
		case WM_CAPTURECHANGED:
			return std::basic_string<charT>(_T("WM_CAPTURECHANGED"));
		case WM_MOVING:
			return std::basic_string<charT>(_T("WM_MOVING"));
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0400)
		case WM_POWERBROADCAST:
			return std::basic_string<charT>(_T("WM_POWERBROADCAST"));
#ifndef _WIN32_WCE
#endif
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0400)
		case WM_DEVICECHANGE:
			return std::basic_string<charT>(_T("WM_DEVICECHANGE"));
#endif /* WINVER >= 0x0400 */
		case WM_MDICREATE:
			return std::basic_string<charT>(_T("WM_MDICREATE"));
		case WM_MDIDESTROY:
			return std::basic_string<charT>(_T("WM_MDIDESTROY"));
		case WM_MDIACTIVATE:
			return std::basic_string<charT>(_T("WM_MDIACTIVATE"));
		case WM_MDIRESTORE:
			return std::basic_string<charT>(_T("WM_MDIRESTORE"));
		case WM_MDINEXT:
			return std::basic_string<charT>(_T("WM_MDINEXT"));
		case WM_MDIMAXIMIZE:
			return std::basic_string<charT>(_T("WM_MDIMAXIMIZE"));
		case WM_MDITILE:
			return std::basic_string<charT>(_T("WM_MDITILE"));
		case WM_MDICASCADE:
			return std::basic_string<charT>(_T("WM_MDICASCADE"));
		case WM_MDIICONARRANGE:
			return std::basic_string<charT>(_T("WM_MDIICONARRANGE"));
		case WM_MDIGETACTIVE:
			return std::basic_string<charT>(_T("WM_MDIGETACTIVE"));
		case WM_MDISETMENU:
			return std::basic_string<charT>(_T("WM_MDISETMENU"));
		case WM_ENTERSIZEMOVE:
			return std::basic_string<charT>(_T("WM_ENTERSIZEMOVE"));
		case WM_EXITSIZEMOVE:
			return std::basic_string<charT>(_T("WM_EXITSIZEMOVE"));
		case WM_DROPFILES:
			return std::basic_string<charT>(_T("WM_DROPFILES"));
		case WM_MDIREFRESHMENU:
			return std::basic_string<charT>(_T("WM_MDIREFRESHMENU"));
#if(WINVER >= 0x0400)
		case WM_IME_SETCONTEXT:
			return std::basic_string<charT>(_T("WM_IME_SETCONTEXT"));
		case WM_IME_NOTIFY:
			return std::basic_string<charT>(_T("WM_IME_NOTIFY"));
		case WM_IME_CONTROL:
			return std::basic_string<charT>(_T("WM_IME_CONTROL"));
		case WM_IME_COMPOSITIONFULL:
			return std::basic_string<charT>(_T("WM_IME_COMPOSITIONFULL"));
		case WM_IME_SELECT:
			return std::basic_string<charT>(_T("WM_IME_SELECT"));
		case WM_IME_CHAR:
			return std::basic_string<charT>(_T("WM_IME_CHAR"));
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0500)
		case WM_IME_REQUEST:
			return std::basic_string<charT>(_T("WM_IME_REQUEST"));
#endif /* WINVER >= 0x0500 */
#if(WINVER >= 0x0400)
		case WM_IME_KEYDOWN:
			return std::basic_string<charT>(_T("WM_IME_KEYDOWN"));
		case WM_IME_KEYUP:
			return std::basic_string<charT>(_T("WM_IME_KEYUP"));
#endif /* WINVER >= 0x0400 */
#if((_WIN32_WINNT >= 0x0400) || (WINVER >= 0x0500))
		case WM_MOUSEHOVER:
			return std::basic_string<charT>(_T("WM_MOUSEHOVER"));
		case WM_MOUSELEAVE:
			return std::basic_string<charT>(_T("WM_MOUSELEAVE"));
#endif
#if(WINVER >= 0x0500)
		case WM_NCMOUSEHOVER:
			return std::basic_string<charT>(_T("WM_NCMOUSEHOVER"));
		case WM_NCMOUSELEAVE:
			return std::basic_string<charT>(_T("WM_NCMOUSELEAVE"));
#endif /* WINVER >= 0x0500 */
#if(_WIN32_WINNT >= 0x0501)
		case WM_WTSSESSION_CHANGE:
			return std::basic_string<charT>(_T("WM_WTSSESSION_CHANGE"));
		case WM_TABLET_FIRST:
			return std::basic_string<charT>(_T("WM_TABLET_FIRST"));
		case WM_TABLET_LAST:
			return std::basic_string<charT>(_T("WM_TABLET_LAST"));
#endif /* _WIN32_WINNT >= 0x0501 */
		case WM_CUT:
			return std::basic_string<charT>(_T("WM_CUT"));
		case WM_COPY:
			return std::basic_string<charT>(_T("WM_COPY"));
		case WM_PASTE:
			return std::basic_string<charT>(_T("WM_PASTE"));
		case WM_CLEAR:
			return std::basic_string<charT>(_T("WM_CLEAR"));
		case WM_UNDO:
			return std::basic_string<charT>(_T("WM_UNDO"));
		case WM_RENDERFORMAT:
			return std::basic_string<charT>(_T("WM_RENDERFORMAT"));
		case WM_RENDERALLFORMATS:
			return std::basic_string<charT>(_T("WM_RENDERALLFORMATS"));
		case WM_DESTROYCLIPBOARD:
			return std::basic_string<charT>(_T("WM_DESTROYCLIPBOARD"));
		case WM_DRAWCLIPBOARD:
			return std::basic_string<charT>(_T("WM_DRAWCLIPBOARD"));
		case WM_PAINTCLIPBOARD:
			return std::basic_string<charT>(_T("WM_PAINTCLIPBOARD"));
		case WM_VSCROLLCLIPBOARD:
			return std::basic_string<charT>(_T("WM_VSCROLLCLIPBOARD"));
		case WM_SIZECLIPBOARD:
			return std::basic_string<charT>(_T("WM_SIZECLIPBOARD"));
		case WM_ASKCBFORMATNAME:
			return std::basic_string<charT>(_T("WM_ASKCBFORMATNAME"));
		case WM_CHANGECBCHAIN:
			return std::basic_string<charT>(_T("WM_CHANGECBCHAIN"));
		case WM_HSCROLLCLIPBOARD:
			return std::basic_string<charT>(_T("WM_HSCROLLCLIPBOARD"));
		case WM_QUERYNEWPALETTE:
			return std::basic_string<charT>(_T("WM_QUERYNEWPALETTE"));
		case WM_PALETTEISCHANGING:
			return std::basic_string<charT>(_T("WM_PALETTEISCHANGING"));
		case WM_PALETTECHANGED:
			return std::basic_string<charT>(_T("WM_PALETTECHANGED"));
		case WM_HOTKEY:
			return std::basic_string<charT>(_T("WM_HOTKEY"));
#if(WINVER >= 0x0400)
		case WM_PRINT:
			return std::basic_string<charT>(_T("WM_PRINT"));
		case WM_PRINTCLIENT:
			return std::basic_string<charT>(_T("WM_PRINTCLIENT"));
#endif /* WINVER >= 0x0400 */
#if(_WIN32_WINNT >= 0x0500)
		case WM_APPCOMMAND:
			return std::basic_string<charT>(_T("WM_APPCOMMAND"));
#endif /* _WIN32_WINNT >= 0x0500 */
#if(_WIN32_WINNT >= 0x0501)
		case WM_THEMECHANGED:
			return std::basic_string<charT>(_T("WM_THEMECHANGED"));
#endif /* _WIN32_WINNT >= 0x0501 */
#if(WINVER >= 0x0400)
		case WM_HANDHELDFIRST:
			return std::basic_string<charT>(_T("WM_HANDHELDFIRST"));
		case WM_HANDHELDLAST:
			return std::basic_string<charT>(_T("WM_HANDHELDLAST"));
		case WM_AFXFIRST:
			return std::basic_string<charT>(_T("WM_AFXFIRST"));
		case WM_AFXLAST:
			return std::basic_string<charT>(_T("WM_AFXLAST"));
#endif /* WINVER >= 0x0400 */
		case WM_PENWINFIRST:
			return std::basic_string<charT>(_T("WM_PENWINFIRST"));
		case WM_PENWINLAST:
			return std::basic_string<charT>(_T("WM_PENWINLAST"));
#if(WINVER >= 0x0400)
		case WM_APP:
			return std::basic_string<charT>(_T("WM_APP"));
#endif /* WINVER >= 0x0400 */
		case WM_USER:
			return std::basic_string<charT>(_T("WM_USER"));
		}
		return std::basic_string<charT>(_T("unknown window message"));
	}

	BOOL Window::isRegisteredWindowClass(const std::basic_string<charT> winClass, HINSTANCE moduleHandle)
	{
		WNDCLASSEX wcex;
		return ::GetClassInfoEx(moduleHandle, winClass.c_str(), &wcex);
	}

	void Window::registerWindowClass(const std::basic_string<charT> winClass, HINSTANCE moduleHandle)
	{
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(wcex);
		wcex.style = CS_CLASSDC;
		wcex.lpfnWndProc = Application::WindowProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = moduleHandle;
		wcex.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
		wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW),
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = winClass.c_str();
		wcex.hIconSm = ::LoadIcon(NULL, IDI_APPLICATION);

		if(NULL == ::RegisterClassEx(&wcex))
		{
			T3D_WINEXCEPT(::GetLastError());
		}
	}

	Window::Window(HWND hwnd)
		: m_hwnd(hwnd)
	{
		_ASSERT(NULL != m_hwnd);
	}

	Window::~Window(void)
	{
		//_ASSERT(NULL == m_hwnd);
	}

	LRESULT Window::onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		_ASSERT(hwnd == m_hwnd);

		switch(message)
		{
		case WM_NCDESTROY:
			{
				WindowPtrMap & wndMap = Application::getSingleton().m_wndMap;

				WindowPtrMap::iterator wndIter = wndMap.find(hwnd);

				_ASSERT(wndIter != wndMap.end());

				m_hwnd = NULL; // *** must be accessed before destructor

				wndMap.erase(wndIter);

				if(wndMap.empty())
				{
					::PostQuitMessage(0);
				}

				return 0;
			}
		}

		return ::DefWindowProc(hwnd, message, wparam, lparam);
	}

	HWND Window::getHandle(void) const
	{
		return m_hwnd;
	}

	void Window::showWindow(int nShow /*= SW_NORMAL*/)
	{
		::ShowWindow(m_hwnd, nShow);
	}

	void Window::updateWindow(void)
	{
		VERIFY(::UpdateWindow(m_hwnd));
	}

	std::basic_string<charT> Window::getWindowText(void) const
	{
		std::basic_string<charT> ret;
		ret.resize(MAX_PATH);
		ret.resize(::GetWindowText(m_hwnd, &ret[0], ret.size()));

		return ret;
	}

	void Window::setWindowText(const std::basic_string<charT> winTitle)
	{
		VERIFY(::SetWindowText(m_hwnd, winTitle.c_str()));
	}

	DWORD Window::getWindowStyle(void) const
	{
		return ::GetWindowLong(m_hwnd, GWL_STYLE);
	}

	void Window::setWindowStyle(DWORD dwStyle)
	{
		::SetWindowLong(m_hwnd, GWL_STYLE, (LONG)dwStyle);

		//VERIFY(NULL != ::SetWindowPos(m_hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER));
	}

	DWORD Window::getWindowExStyle(void) const
	{
		return ::GetWindowLong(m_hwnd, GWL_EXSTYLE);
	}

	void Window::setWindowExtansionStyle(DWORD dwExStyle)
	{
		::SetWindowLong(m_hwnd, GWL_EXSTYLE, (LONG)dwExStyle);

		//VERIFY(NULL != ::SetWindowPos(m_hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER));
	}

	CRect Window::getWindowRect(void) const
	{
		CRect rect;
		VERIFY(::GetWindowRect(m_hwnd, &rect));
		return rect;
	}

	void Window::setWindowRect(const CRect & rect)
	{
		VERIFY(::SetWindowPos(m_hwnd, HWND_TOP, rect.left, rect.top, rect.Width(), rect.Height(), 0));
	}

	CRect Window::getClientRect(void) const
	{
		CRect rect;
		VERIFY(::GetClientRect(m_hwnd, &rect));
		return rect;
	}

	void Window::adjustClientRect(const CRect & rect)
	{
		CRect adjustRect = rect;
		VERIFY(::AdjustWindowRectEx(&adjustRect, getWindowStyle(), NULL != ::GetMenu(m_hwnd), getWindowExStyle()));
		setWindowRect(adjustRect);
	}

	CRect & Window::screenToClientSelf(CRect & rect)
	{
		VERIFY(::ScreenToClient(m_hwnd, &rect.TopLeft()));
		VERIFY(::ScreenToClient(m_hwnd, &rect.BottomRight()));
		return rect;
	}

	CRect & Window::clientToScreenSelf(CRect & rect)
	{
		VERIFY(::ClientToScreen(m_hwnd, &rect.TopLeft()));
		VERIFY(::ClientToScreen(m_hwnd, &rect.BottomRight()));
		return rect;
	}

	void Window::setWindowPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
	{
		VERIFY(NULL != ::SetWindowPos(m_hwnd, hWndInsertAfter, x, y, cx, cy, uFlags));
	}

	void Window::centerWindow(void)
	{
		HWND hWndParent = ::GetParent(getHandle());
		if(NULL == hWndParent)
		{
			hWndParent = ::GetDesktopWindow();
		}

		CRect parentRect;
		VERIFY(::GetWindowRect(hWndParent, &parentRect));

		CRect windowRect = getWindowRect();
		int x = ((parentRect.Width()) - (windowRect.Width())) / 2;
		int y = ((parentRect.Height()) - (windowRect.Height())) / 2;

		setWindowPos(NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	void Window::destroyWindow(void)
	{
		::DestroyWindow(m_hwnd);
	}

	HDC Window::getDC(void)
	{
		return ::GetDC(m_hwnd);
	}

	void Window::releaseDC(HDC hdc)
	{
		VERIFY(1 == ::ReleaseDC(m_hwnd, hdc));
	}

	void Window::InvalidateRect(CONST RECT * lpRect /*= NULL*/, BOOL bErase /*= FALSE*/)
	{
		VERIFY(::InvalidateRect(m_hwnd, lpRect, bErase));
	}

	void Window::postMessage(UINT Msg, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/)
	{
		VERIFY(::PostMessage(m_hwnd, Msg, wParam, lParam));
	}

	LRESULT Window::sendMessage(UINT Msg, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/)
	{
		return ::SendMessage(m_hwnd, Msg, wParam, lParam);
	}

	Application * Application::s_ptr = NULL;

	LRESULT CALLBACK Application::WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		if(NULL != s_ptr)
		{
			WindowPtrMap & wndMap = getSingleton().m_wndMap;

			if(WM_CREATE == message)
			{
				_ASSERT(wndMap.end() == wndMap.find(hwnd));

				wndMap.insert(WindowPtrMap::value_type(hwnd, WindowPtr(getSingleton().newWindow(hwnd))));
			}

			WindowPtrMap::iterator iter = wndMap.find(hwnd);

			if(iter != wndMap.end())
			{
				return iter->second->onProc(hwnd, message, wparam, lparam);
			}
		}
		return ::DefWindowProc(hwnd, message, wparam, lparam);
	}

	Application::Application(HINSTANCE hInstance /*= NULL*/)
		: m_hinst(hInstance)
	{
		//_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));

		if(NULL == m_hinst)
		{
			m_hinst = ::GetModuleHandle(NULL);
		}

		_ASSERT(NULL != m_hinst);

		s_ptr = this;
	}

	Application::~Application(void)
	{
		//while(!m_wndMap.empty())
		//{
		//	m_wndMap.begin()->second->destroyWindow();
		//}

		s_ptr = NULL;
	}

	Window * Application::newWindow(HWND hwnd)
	{
		return new Window(hwnd);
	}

	void Application::onIdle(void)
	{
		::WaitMessage();
	}

	Window * Application::createWindow(const std::basic_string<charT> winTitle, const std::basic_string<charT> winClass)
	{
		if(!Window::isRegisteredWindowClass(winClass, getHandle()))
		{
			Window::registerWindowClass(winClass, getHandle());
		}

		HWND hwnd = ::CreateWindowEx(
			0, winClass.c_str(), winTitle.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, getHandle(), NULL);

		if(NULL == hwnd)
		{
			return NULL;
		}

		_ASSERT(m_wndMap.end() != m_wndMap.find(hwnd));

		return m_wndMap[hwnd].get();
	}

	HINSTANCE Application::getHandle(void) const
	{
		return m_hinst;
	}

	std::basic_string<charT> Application::getModuleFileName(void) const
	{
		std::basic_string<charT> ret;
		ret.resize(MAX_PATH);
		ret.resize(::GetModuleFileName(getHandle(), &ret[0], ret.size()));

		return ret;
	}

	int Application::run(void)
	{
		MSG msg = {0};

		while(WM_QUIT != msg.message)
		{
			if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				onIdle();
			}
		}

		return (int)msg.wParam;
	}
}
