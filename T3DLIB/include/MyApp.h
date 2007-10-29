/*
 * File: MyApp.h
 */

#ifndef __MYAPP_H__
#define __MYAPP_H__

#include <Windows.h>
#include <exception>
#include <string>
#include <list>
#include <map>

#include "t3dCommons.h"

/*
 * disable: <type1> needs to have dll-interface to be used by clients of <type2>
 */
#pragma warning(disable : 4251)

/*
 * disable: non dll-interface <type1> used as base for dll-interface <type2>
 */
#pragma warning(disable : 4275)

// ============================================================================
// MyException
// ============================================================================

class T3DLIB_API MyException : public std::exception
{
public:
	MyException(const char * szInfo);

	virtual ~MyException();

public:
	virtual const char * what(void) const throw();

protected:
	std::string m_info;
};

// ============================================================================
// MyWindow
// ============================================================================

class T3DLIB_API MyWindow
{
	friend class MyMessageArray;

protected:
	static std::string class_name;

protected:
	virtual LRESULT OnProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

public:
	MyWindow(std::string name = MyWindow::class_name);

	virtual ~MyWindow();

protected:
	HWND m_hwnd;
};

// ============================================================================
// MyMessageArray
// ============================================================================

class T3DLIB_API MyMessageArray
{
public:
	virtual LRESULT OnProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

public:
	MyMessageArray();

	virtual ~MyMessageArray();

public:
	void loop(void);

	MyWindow * addWindow(MyWindow * wnd);

protected:
	std::map<HWND, MyWindow *> m_singleWnd;
	std::map<HWND, MyWindow *> m_activeWnd;
};

extern T3DLIB_API MyMessageArray g_msgArr;

// ============================================================================
// MyApplication
// ============================================================================

class T3DLIB_API MyApplication
{
public:
	static int			s_nShow;
	static HINSTANCE	s_hInst;

public:
	MyApplication(int nShow = SW_NORMAL, HINSTANCE	hInst = NULL);

	virtual ~MyApplication();

public:
	virtual void run(void);
};

// ============================================================================
// MyWndProc
// ============================================================================

LRESULT T3DLIB_API CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

#pragma warning(default : 4251)

#pragma warning(default : 4275)

#endif // __MYAPP_H__
