/*
 * File: MyApp.h
 */

#ifndef __MY_APP_H__
#define __MY_APP_H__

#include "t3dCommons.h"

#include <Windows.h>
#include <exception>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <boost/shared_ptr.hpp>

/*
 * Note : use /MD[d] for server and client to use dll std::string
 */

//T3DLIB_TEMPLATE class T3DLIB_API std::basic_string<char>;

#if !defined _MT || !defined _DLL
#error need for export std::string must use /MD[d]
#endif

// ============================================================================
// str_printf
// ============================================================================

std::string T3DLIB_API str_printf(char * format, ...);

// ============================================================================
// MyException
// ============================================================================

class T3DLIB_API MyException /*: public std::exception*/
{
public:
	MyException(const std::string info);

	MyException(const std::string info, const std::string file, int line);

	virtual ~MyException();

public:
	virtual const std::string what(void) const throw();

	virtual const std::string getFullDesc(void) const throw();

protected:
	std::string m_info;
	std::string m_file;
	int m_line;
};

#define MY_EXCEPT(x)	throw(MyException(x, __FILE__, __LINE__))

// ============================================================================
// MyWindowBase
// ============================================================================

class T3DLIB_API MyWindowBase
{
	friend class MyMessageArray;

public:
	MyWindowBase(const std::string the_class_name, const std::string the_window_name);

	virtual ~MyWindowBase();

protected:
	virtual LRESULT OnProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

public:
	HWND get_HWND(void);

protected:
	void set_HWND(HWND hwnd);	// only be used by MyMessageArray

	void Register(void);		// only be used by MyMessageArray

	void Create(void);			// only be used by MyMessageArray

	void Destroy(void);			// only be used by MyMessageArray

protected:
	std::string class_name;
	std::string window_name;
	HWND m_hwnd;
};

typedef boost::shared_ptr<MyWindowBase> MyWindowBasePtr;

// ============================================================================
// MyMessageArray
// ============================================================================

class T3DLIB_API MyApplication;

class T3DLIB_API MyMessageArray
{
public:
	MyMessageArray(MyApplication * app);

	virtual ~MyMessageArray();

public:
	virtual LRESULT OnProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

public:
	int loop(void);

	MyWindowBasePtr addWindow(MyWindowBasePtr wnd);

protected:
	virtual LRESULT OnCreate(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	virtual LRESULT OnDestroy(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

protected:
	std::map<HWND, MyWindowBasePtr> m_singleWnd;
	std::map<HWND, MyWindowBasePtr> m_activeWnd;
	MyApplication * m_app;
};

extern T3DLIB_API boost::shared_ptr<MyMessageArray> g_msgArr;

// ============================================================================
// MyApplication
// ============================================================================

class T3DLIB_API MyApplication
{
public:
	MyApplication();

	virtual ~MyApplication();

public:
	virtual int run(void);

	virtual void OnIdle(void);
};

// ============================================================================
// MyWndProc
// ============================================================================

LRESULT T3DLIB_API CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

// ============================================================================
// MyWindow
// ============================================================================

class T3DLIB_API MyWindow : public MyWindowBase
{
public:
	MyWindow(const std::string the_class_name = "MY_WINDOW", const std::string the_window_name = "My_Window")
		: MyWindowBase(the_class_name, the_window_name)
	{
	}

	virtual ~MyWindow()
	{
	}

protected:
	virtual LRESULT OnProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		return MyWindowBase::OnProc(hwnd, message, wparam, lparam);
	}

public:
	static LONG GetRectWidth(RECT rect)
	{
		return rect.right - rect.left;
	}

	static LONG GetRectHeight(RECT rect)
	{
		return rect.bottom - rect.top;
	}

	void ShowWindow(int nShow = SW_NORMAL)
	{
		assert(NULL != m_hwnd);
		::ShowWindow(m_hwnd, nShow);
		if(!::UpdateWindow(m_hwnd))
			MY_EXCEPT("update window failed");
	}

	std::string GetWindowText(void)
	{
		char buffer[MAX_BUFFER_SIZE];
		if(!::GetWindowText(m_hwnd, buffer, MAX_BUFFER_SIZE))
			MY_EXCEPT("get window text failed");
		return std::string(buffer);
	}

	void SetWindowText(const std::string text)
	{
		if(!::SetWindowText(m_hwnd, text.c_str()))
			MY_EXCEPT("set window text failed");
	}

	DWORD GetWindowStyle(void)
	{
		assert(NULL != m_hwnd);
		return (DWORD)::GetWindowLong(m_hwnd, GWL_STYLE);
	}

	void SetWindowStyle(DWORD style)
	{
		assert(NULL != m_hwnd);
		if(0 == ::SetWindowLong(m_hwnd, GWL_STYLE, (LONG)style))
			MY_EXCEPT("set window style failed");
		if(0 == ::SetWindowPos(m_hwnd, 0, 0, 0, 0, 0,
				SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER))
			MY_EXCEPT("set window position failed");
	}

	DWORD GetWindowExstyle(void)
	{
		assert(NULL != m_hwnd);
		return (DWORD)::GetWindowLong(m_hwnd, GWL_EXSTYLE);
	}

	void SetWindowExstyle(DWORD exstyle)
	{
		assert(NULL != m_hwnd);
		if(0 == ::SetWindowLong(m_hwnd, GWL_EXSTYLE, (LONG)exstyle))
			MY_EXCEPT("set window extension style failed");
		if(0 == ::SetWindowPos(m_hwnd, 0, 0, 0, 0, 0,
				SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER))
			MY_EXCEPT("set window position failed");
	}

	RECT GetWindowRect(void)
	{
		assert(NULL != m_hwnd);
		RECT rect;
		if(!::GetWindowRect(m_hwnd, &rect))
			MY_EXCEPT("get window rect failed");
		return rect;
	}

	void SetWindowRect(RECT rect)
	{
		assert(NULL != m_hwnd);
		if(!::SetWindowPos(m_hwnd, HWND_TOP, rect.left, rect.top,
				GetRectWidth(rect), GetRectHeight(rect), 0))
			MY_EXCEPT("set window position failed");
	}

	RECT GetClientRectOriginal(void)
	{
		assert(NULL != m_hwnd);
		RECT rect;
		if(!::GetClientRect(m_hwnd, &rect))
			MY_EXCEPT("get client rect failed");
		return rect;
	}

	RECT GetClientRect(void)
	{
		assert(NULL != m_hwnd);
		RECT rect = GetClientRectOriginal();
		RECT radj = rect;
		if(!::AdjustWindowRectEx(&radj,
				GetWindowStyle(), ::GetMenu(m_hwnd) != NULL, GetWindowExstyle()))
			MY_EXCEPT("adjust window rect failed");
		RECT rwnd = GetWindowRect();
		if(!::OffsetRect(&rect, rwnd.left - radj.left, rwnd.top - radj.top))
			MY_EXCEPT("offset client rect failed");
		return rect;
	}

	void SetClientRect(RECT rect)
	{
		assert(NULL != m_hwnd);
		if(!::AdjustWindowRectEx(&rect,
				GetWindowStyle(), ::GetMenu(m_hwnd) != NULL, GetWindowExstyle()))
			MY_EXCEPT("adjust window rect failed");
		SetWindowRect(rect);
	}

	void CenterWindow(void)
	{
		assert(NULL != m_hwnd);
		RECT desktop_rect;
		if(!::GetWindowRect(::GetDesktopWindow(), &desktop_rect))
			MY_EXCEPT("get desktop window rect failed");
		RECT window_rect = GetWindowRect();
		if(!::SetWindowPos(m_hwnd, HWND_TOP,
				(GetRectWidth(desktop_rect) - GetRectWidth(window_rect)) / 2,
				(GetRectHeight(desktop_rect) - GetRectHeight(window_rect)) / 2,
				0, 0, SWP_NOSIZE))
			MY_EXCEPT("center window failed");
	}
};

typedef boost::shared_ptr<MyWindow> MyWindowPtr;

#endif // __MY_APP_H__
