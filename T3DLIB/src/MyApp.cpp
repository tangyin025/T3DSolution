/*
 * File: MyApp.cpp
 */

#include "t3dPrecompiledHeader.h"
#include "MyApp.h"

// ============================================================================
// MyException
// ============================================================================

MyException::MyException(const std::string info)
	: m_info(info)
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
// MyWindowBase
// ============================================================================

MyWindowBase::MyWindowBase(const std::string the_class_name, const std::string the_window_name)
	: class_name(the_class_name), window_name(the_window_name), m_hwnd(NULL)
{
}

MyWindowBase::~MyWindowBase()
{
}

LRESULT MyWindowBase::OnProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	assert(hwnd == m_hwnd);

	return ::DefWindowProc(hwnd, message, wparam, lparam);
}

HWND MyWindowBase::get_hwnd(void)
{
	return m_hwnd;
}

void MyWindowBase::set_hwnd(HWND hwnd)
{
	m_hwnd = hwnd;
}

void MyWindowBase::Register(void)
{
	assert(!class_name.empty());

	WNDCLASSEX wc;
	if(!::GetClassInfoEx(::GetModuleHandle(NULL), class_name.c_str(), &wc))
	{
		WNDCLASSEX tmp = { sizeof(wc), CS_CLASSDC, MyWndProc, 0, 0,
			::GetModuleHandle(NULL),
			::LoadIcon(NULL, IDI_APPLICATION),
			::LoadCursor(NULL, IDC_ARROW),
			(HBRUSH)(COLOR_WINDOW + 1), NULL, class_name.c_str(),
			::LoadIcon(NULL, IDI_APPLICATION) };

		if(NULL == ::RegisterClassEx(&tmp))
		{
			throw MyException("cannot register window class");
		}
	}
}

void MyWindowBase::Create(void)
{
	assert(NULL == m_hwnd);

	HWND hwnd;
	if(NULL == (hwnd =
		::CreateWindowEx(0, class_name.c_str(), window_name.c_str(), WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, ::GetModuleHandle(NULL), NULL)))
	{
		throw MyException("create window failed");
	}

	assert(hwnd == m_hwnd);
}

void MyWindowBase::Destroy(void)
{
	assert(NULL != m_hwnd);

	if(!::DestroyWindow(m_hwnd))
		throw MyException("destroy window failed");
}

// ============================================================================
// MyMessageArray
// ============================================================================

static /*__declspec(thread)*/ MyWindowBasePtr g_wndHook;

MyMessageArray::MyMessageArray(MyApplication * app)
	: m_app(app)
{
	assert(NULL != m_app);
}

MyMessageArray::~MyMessageArray()
{
	if(!m_activeWnd.empty())
	{
		std::list<MyWindowBasePtr> wndList;
		std::map<HWND, MyWindowBasePtr>::const_iterator map_iter;
		for(map_iter = m_activeWnd.begin(); map_iter != m_activeWnd.end(); map_iter++)
		{
			wndList.push_back(map_iter->second);
		}

		std::list<MyWindowBasePtr>::iterator list_iter;
		for(list_iter = wndList.begin(); list_iter != wndList.end(); list_iter++)
		{
			(*list_iter)->Destroy();
		}
	}
}

LRESULT MyMessageArray::OnProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch(message)
	{
	case WM_CREATE:
		return OnCreate(hwnd, message, wparam, lparam);

	case WM_DESTROY:
		return OnDestroy(hwnd, message, wparam, lparam);

	default:
		break;
	}

	if(m_activeWnd.end() != m_activeWnd.find(hwnd))
	{
		return m_activeWnd[hwnd]->OnProc(hwnd, message, wparam, lparam);
	}

	if(m_singleWnd.end() != m_singleWnd.find(hwnd))
	{
		return m_singleWnd[hwnd]->OnProc(hwnd, message, wparam, lparam);
	}

	return ::DefWindowProc(hwnd, message, wparam, lparam);
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
				m_app->OnIdle();
			}
		}
	}
}

MyWindowBasePtr MyMessageArray::addWindow(MyWindowBasePtr wnd)
{
	assert(g_wndHook == NULL);
	g_wndHook = wnd;

	wnd->Register();
	wnd->Create();

	assert(g_wndHook != NULL);
	g_wndHook = MyWindowBasePtr((MyWindowBase *)NULL);

	assert(m_activeWnd.end() == m_activeWnd.find(wnd->get_hwnd()));
	assert(m_singleWnd.end() != m_singleWnd.find(wnd->get_hwnd()));

	m_activeWnd[wnd->get_hwnd()] = wnd;
	m_singleWnd.erase(wnd->get_hwnd());
	return wnd;
}

LRESULT MyMessageArray::OnCreate(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	assert(g_wndHook != NULL);
	assert(m_singleWnd.end() == m_singleWnd.find(hwnd));

	assert(NULL == g_wndHook->get_hwnd());
	g_wndHook->set_hwnd(hwnd);

	m_singleWnd[hwnd] = g_wndHook;
	return g_wndHook->OnProc(hwnd, message, wparam, lparam);
}

LRESULT MyMessageArray::OnDestroy(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if(m_activeWnd.end() != m_activeWnd.find(hwnd))
	{
		LRESULT res = m_activeWnd[hwnd]->OnProc(hwnd, message, wparam, lparam);
		m_activeWnd.erase(hwnd);

		if(m_activeWnd.empty())
		{
			::PostQuitMessage(0);
		}

		return res;
	}

	assert(m_singleWnd.end() != m_singleWnd.find(hwnd));
	return m_singleWnd[hwnd]->OnProc(hwnd, message, wparam, lparam);
}

boost::shared_ptr<MyMessageArray> g_msgArr;

// ============================================================================
// MyApplication
// ============================================================================

MyApplication::MyApplication()
{
	assert(g_msgArr == NULL);
	g_msgArr = boost::shared_ptr<MyMessageArray>(new MyMessageArray(this));
}

MyApplication::~MyApplication()
{
}

void MyApplication::run(void)
{
	g_msgArr->loop();
}

void MyApplication::OnIdle(void)
{
	::WaitMessage();
}

// ============================================================================
// MyWndProc
// ============================================================================

LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	assert(g_msgArr != NULL);

	return g_msgArr->OnProc(hwnd, message, wparam, lparam);
}

// ============================================================================
// MyWindow
// ============================================================================

/*
// ////////////////////////////////////////////////////////////////////////////////////
// CLASSES
// ////////////////////////////////////////////////////////////////////////////////////

class DemoWindow : public MyWindow
{
protected:
	virtual LRESULT OnProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch(message)
		{
		case WM_CREATE:
			ShowWindow();
			return 0;

		default:
			break;
		}

		return MyWindow::OnProc(hwnd, message, wparam, lparam);
	}
};

class DemoApplication : public MyApplication
{
public:
	virtual void run(void)
	{
		g_msgArr->addWindow(MyWindowBasePtr(new DemoWindow));

		MyApplication::run();
	}
};

// ////////////////////////////////////////////////////////////////////////////////////
// WinMain
// ////////////////////////////////////////////////////////////////////////////////////

int APIENTRY WinMain(HINSTANCE	hInstance,
					 HINSTANCE	hPrevInstance,
					 LPSTR		lpCmdLine,
					 int		nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try
	{
		DemoApplication app;
		app.run();
	}
	catch(std::exception & e)
	{
		::MessageBoxA(NULL, e.what(), "Exception!", MB_OK);
	}

	return 0;
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
}
*/
