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

#ifdef T3DLIB_EXPORTS
#define T3DLIB_TEMPLATE template
#else
#define T3DLIB_TEMPLATE extern template
#endif

#ifndef T3DLIB_EXPORTS
#pragma warning(disable : 4231)
#endif

// ============================================================================
// MyException
// ============================================================================

class T3DLIB_API std::exception;
T3DLIB_TEMPLATE class T3DLIB_API std::allocator<char>;
T3DLIB_TEMPLATE class T3DLIB_API std::basic_string<char, std::char_traits<char>, std::allocator<char> >;

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

T3DLIB_TEMPLATE struct T3DLIB_API std::less<HWND>;
T3DLIB_TEMPLATE class T3DLIB_API std::allocator<std::pair<const HWND,MyWindow *> >;
T3DLIB_TEMPLATE class T3DLIB_API std::allocator<std::_Tree_ptr<std::_Tmap_traits<HWND, MyWindow *, std::less<HWND>, std::allocator<std::pair<const HWND, MyWindow *> >, false> >::_Nodeptr>;
T3DLIB_TEMPLATE class T3DLIB_API std::allocator<std::_Tree_nod<std::_Tmap_traits<HWND, MyWindow *, std::less<HWND>, std::allocator<std::pair<const HWND, MyWindow *> >, false> >::_Node>;
T3DLIB_TEMPLATE class T3DLIB_API std::map<HWND, MyWindow *>;

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

#ifndef T3DLIB_EXPORTS
#pragma warning(default : 4231)
#endif

#endif // __MYAPP_H__
