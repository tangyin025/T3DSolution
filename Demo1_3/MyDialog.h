
#pragma once

#include "MyResource.h"

class MyDialog : public my::Dialog
{
public:
	my::Config m_cfg;

	int m_save_configuration;

	my::ImagePtr m_image;

public:
	MyDialog(const my::Config & cfg, HINSTANCE hInstance = ::GetModuleHandle(NULL), HWND hWndParent = NULL);

	~MyDialog(void);

	INT_PTR onProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
