/*
 * File: MyApp.cpp
 */

#include "t3dPrecompiledHeader.h"
#include "MyApp.h"

// ============================================================================
// MyException
// ============================================================================

MyException::MyException(const char * szInfo)
	: m_info(szInfo)
{
}

MyException::~MyException()
{
}

const char * MyException::what(void) const throw()
{
	return m_info.c_str();
}

// ============================================================================
// MyWindow
// ============================================================================

std::string MyWindow::class_name = "T3DLIB_WINDOW";

LRESULT MyWindow::OnProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	assert(hwnd == m_hwnd);

	return ::DefWindowProc(hwnd, message, wparam, lparam);
}

MyWindow::MyWindow(std::string name /*= MyWindow::class_name*/)
	: m_hwnd(NULL)
{
	WNDCLASSEX wc;
	if(!::GetClassInfoEx(MyApplication::s_hInst, class_name.c_str(), &wc))
	{
		WNDCLASSEX tmp = { sizeof(wc), CS_CLASSDC, MyWndProc, 0, 0,
			::GetModuleHandle(NULL),
			::LoadIcon(NULL, IDI_APPLICATION),
			::LoadCursor(NULL, IDC_ARROW),
			(HBRUSH)(COLOR_WINDOW + 1), NULL, class_name.c_str(),
			::LoadIcon(NULL, IDI_APPLICATION) };

		memcpy(&wc, &tmp, sizeof(wc));

		if(NULL == ::RegisterClassEx(&wc))
		{
			throw MyException("cannot register window class");
		}
	}

	assert(NULL == m_hwnd);

	HWND hwnd;
	if(NULL == (hwnd =
		::CreateWindowEx(0, class_name.c_str(), name.c_str(), WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, MyApplication::s_hInst, this)))
	{
		throw MyException("create window failed");
	}

	assert(hwnd == m_hwnd);

	::ShowWindow(m_hwnd, MyApplication::s_nShow);
	::UpdateWindow(m_hwnd);

	//static int i = 0;
	//if(++i > 2)
	//{
	//	::DestroyWindow(m_hwnd);
	//	throw MyException("test for 3rd window exception");
	//}
}

MyWindow::~MyWindow()
{
}

// ============================================================================
// MyMessageArray
// ============================================================================

LRESULT MyMessageArray::OnProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	LRESULT res;
	MyWindow * wnd;
	switch(message)
	{
	case WM_CREATE:
		assert(m_singleWnd.end() == m_singleWnd.find(hwnd));
		wnd = static_cast<MyWindow *>(((CREATESTRUCT *)lparam)->lpCreateParams);
		assert(NULL == wnd->m_hwnd);
		wnd->m_hwnd = hwnd;
		res = wnd->OnProc(hwnd, message, wparam, lparam);
		m_singleWnd[hwnd] = wnd;
		return res;

	case WM_DESTROY:
		if(m_activeWnd.end() != m_activeWnd.find(hwnd))
		{
			wnd = m_activeWnd[hwnd];
			res = wnd->OnProc(hwnd, message, wparam, lparam);
			delete wnd;
			m_activeWnd.erase(hwnd);

			if(m_activeWnd.empty())
			{
				::PostQuitMessage(0);
			}
		}
		else
		{
			assert(m_singleWnd.end() != m_singleWnd.find(hwnd));
			res = DefWindowProc(hwnd, message, wparam, lparam);
		}
		return res;

	default:
		if(m_activeWnd.end() != m_activeWnd.find(hwnd))
		{
			res = m_activeWnd[hwnd]->OnProc(hwnd, message, wparam, lparam);
		}
		else
		{
			//assert(m_singleWnd.end() != m_singleWnd.find(hwnd));
			res = DefWindowProc(hwnd, message, wparam, lparam);
		}
		return res;
	}
}

MyMessageArray::MyMessageArray()
{
}

MyMessageArray::~MyMessageArray()
{
	if(!m_activeWnd.empty())
	{
		std::list<MyWindow *> wndList;
		std::map<HWND, MyWindow *>::const_iterator map_iter;
		for(map_iter = m_activeWnd.begin(); map_iter != m_activeWnd.end(); map_iter++)
		{
			wndList.push_back(map_iter->second);
		}

		std::list<MyWindow *>::iterator list_iter;
		for(list_iter = wndList.begin(); list_iter != wndList.end(); list_iter++)
		{
			::DestroyWindow((*list_iter)->m_hwnd);
		}
	}
}

void MyMessageArray::loop(void)
{
	if(!m_activeWnd.empty())
	{
		MSG msg;
		msg.message = WM_QUIT + 1;

		while(WM_QUIT != msg.message)
		{
			if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				::WaitMessage();
			}
		}
	}
}

MyWindow * MyMessageArray::addWindow(MyWindow * wnd)
{
	assert(m_activeWnd.end() == m_activeWnd.find(wnd->m_hwnd));
	assert(m_singleWnd.end() != m_singleWnd.find(wnd->m_hwnd));

	m_activeWnd[wnd->m_hwnd] = wnd;
	m_singleWnd.erase(wnd->m_hwnd);
	return wnd;
}

MyMessageArray g_msgArr;

// ============================================================================
// MyApplication
// ============================================================================

int MyApplication::s_nShow = SW_NORMAL;

HINSTANCE MyApplication::s_hInst = NULL;

MyApplication::	MyApplication(int nShow /*= SW_NORMAL*/, HINSTANCE	hInst /*= NULL*/)
{
	if(NULL != hInst)
	{
		s_hInst = hInst;
	}
	else
	{
		s_hInst = ::GetModuleHandle(NULL);
	}
	s_nShow = nShow;
}

MyApplication::~MyApplication()
{
}

void MyApplication::run(void)
{
	//g_msgArr.addWindow(new MyWindow("win1"));
	//g_msgArr.addWindow(new MyWindow("win2"));
	//g_msgArr.addWindow(new MyWindow("win3"));

	g_msgArr.loop();
}

// ============================================================================
// MyWndProc
// ============================================================================

LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return g_msgArr.OnProc(hwnd, message, wparam, lparam);
}

// ////////////////////////////////////////////////////////////////////////////////////
// WinMain
// ////////////////////////////////////////////////////////////////////////////////////
/*
int APIENTRY WinMain(HINSTANCE	hInstance,
					 HINSTANCE	hPrevInstance,
					 LPSTR		lpCmdLine,
					 int		nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try
	{
		MyApplication app(hInstance, nCmdShow);
		app.run();
	}
	catch(std::exception & e)
	{
		::MessageBoxA(NULL, e.what(), "Exception!", MB_OK);
	}

	return 0;
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
}
*/
