
#include "stdafx.h"
#include "MyDialog.h"
#include "resource.h"

MyDialog::MyDialog(HWND hWndParent /*= NULL*/)
	: my::ModelDialog(::GetModuleHandle(NULL), (LPCTSTR)IDD_DIALOG1, hWndParent)
{
}

MyDialog::~MyDialog(void)
{
}
