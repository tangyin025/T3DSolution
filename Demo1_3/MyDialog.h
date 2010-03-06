
#pragma once

#include "MyConfig.h"

class MyDialog : public my::ModelDialog
{
public:
	MyConfig m_cfg;

public:
	MyDialog(const MyConfig & cfg, HINSTANCE hInstance = ::GetModuleHandle(NULL), HWND hWndParent = NULL);

	INT_PTR onProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
