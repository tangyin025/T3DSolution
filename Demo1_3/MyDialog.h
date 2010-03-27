
#pragma once

#include "MyConfig.h"
#include "MyResource.h"

class MyDialog : public my::Dialog
{
public:
	MyConfig m_cfg;

	int m_save_configuration;

	my::ImagePtr m_image;

public:
	MyDialog(const MyConfig & cfg, HINSTANCE hInstance = ::GetModuleHandle(NULL), HWND hWndParent = NULL);

	~MyDialog(void);

	INT_PTR onProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
