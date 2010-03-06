
#include "stdafx.h"
#include "MyDialog.h"
#include "resource.h"

MyDialog::MyDialog(const MyConfig & cfg, HINSTANCE hInstance /*= ::GetModuleHandle(NULL)*/, HWND hWndParent /*= NULL*/)
	: my::ModelDialog(hInstance, (LPCTSTR)IDD_DIALOG1, hWndParent)
	, m_cfg(cfg)
{
}

INT_PTR MyDialog::onProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("320x240")));
		VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("640x480")));
		VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("800x600")));
		VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1024x768")));
		VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1280x800")));
		VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1280x1024")));
		VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1366x768")));
		VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1680x1050")));
		VERIFY(CB_ERR != ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_SELECTSTRING, (WPARAM)-1, (LPARAM)_T("800x600")));
		::SendMessage(m_hdlg, WM_COMMAND, MAKEWPARAM(IDC_COMBO1, CBN_SELCHANGE), (LPARAM)::GetDlgItem(m_hdlg, IDC_COMBO1));
		break;
	}
	return my::ModelDialog::onProc(hwndDlg, uMsg, wParam, lParam);
}
