
#include "stdafx.h"
#include "MyDialog.h"
#include "MyGameEx.h"

MyDialog::MyDialog(const my::Config & cfg)
	: m_cfg(cfg)
	, m_save_configuration(BST_UNCHECKED)
{
}

LRESULT MyDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// initialize dialog title
	SetWindowText(_T("User Configuration"));

	// initialize splash image
	std::basic_string<charT> filePath = my::ResourceMgr::getSingleton().findFile(_T("splash.jpg"));
	if(!filePath.empty())
	{
		m_image = my::ImagePtr(new my::Image(filePath));
	}

	// initialize combo box1 with resolutions
	VERIFY(0 == GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("320x240")));
	VERIFY(1 == GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("640x480")));
	VERIFY(2 == GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("800x600")));
	VERIFY(3 == GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1024x768")));
	VERIFY(4 == GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1280x800")));
	VERIFY(5 == GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1280x1024")));
	VERIFY(6 == GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1366x768")));
	VERIFY(7 == GetDlgItem(IDC_COMBO1).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1680x1050")));

	// select the specified resolution
	if(CB_ERR == GetDlgItem(IDC_COMBO1).SendMessage(CB_SELECTSTRING, (WPARAM)-1, (LPARAM)str_printf(_T("%dx%d"), m_cfg.getInt(_T("width")), m_cfg.getInt(_T("height"))).c_str()))
	{
		// for use customized resolution
		VERIFY(SetDlgItemInt(IDC_EDIT1, m_cfg.getInt(_T("width")), FALSE));
		VERIFY(SetDlgItemInt(IDC_EDIT2, m_cfg.getInt(_T("height")), FALSE));
	}
	else
	{
		SendMessage(WM_COMMAND, MAKEWPARAM(IDC_COMBO1, CBN_SELCHANGE), (LPARAM)GetDlgItem(IDC_COMBO1).m_hWnd);
	}

	// initialize combo box2 with screen modes
	VERIFY(my::Game::SCREEN_MODE_WINDOWED == GetDlgItem(IDC_COMBO2).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("Windowed mode")));
	VERIFY(my::Game::SCREEN_MODE_FULLSCREEN16 == GetDlgItem(IDC_COMBO2).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("16bpp full screen")));
	VERIFY(my::Game::SCREEN_MODE_FULLSCREEN32 == GetDlgItem(IDC_COMBO2).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("32bpp full screen")));

	// select the specified screen mode
	if(CB_ERR == GetDlgItem(IDC_COMBO2).SendMessage(CB_SETCURSEL, m_cfg.getInt(_T("screenmode")), 0))
	{
		VERIFY(0 == GetDlgItem(IDC_COMBO2).SendMessage(CB_SETCURSEL, 0, 0));
	}

	// initialize combo box3 with aspect ratio mode
	VERIFY(MyGame::ASPECT_RATIO_STRETCHED == GetDlgItem(IDC_COMBO3).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("Stretch mode")));
	VERIFY(MyGame::ASPECT_RATIO_STANDARD == GetDlgItem(IDC_COMBO3).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("4 : 3")));
	VERIFY(MyGame::ASPECT_RATIO_WIDESCREEN == GetDlgItem(IDC_COMBO3).SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("16 : 9")));

	// select the specified aspect ratio mode
	if(CB_ERR == GetDlgItem(IDC_COMBO3).SendMessage(CB_SETCURSEL, m_cfg.getInt(_T("aspectratio")), 0))
	{
		VERIFY(0 == GetDlgItem(IDC_COMBO3).SendMessage(CB_SETCURSEL, 0, 0));
	}

	// initialize check box1 with save configuration option
	VERIFY(CheckDlgButton(IDC_CHECK1, m_save_configuration));

	CenterWindow();
	return TRUE;
}

LRESULT MyDialog::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	EndDialog(IDCANCEL);
	return 0;
}

LRESULT MyDialog::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// get custom control imageRect
	CRect imageRect;
	VERIFY(GetDlgItem(IDC_STATIC1).GetWindowRect(&imageRect));
	ScreenToClient(&imageRect);

	// draw this image to screen
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(&ps);
	if(NULL != m_image)
	{
		int mode = ::SetStretchBltMode(hdc, HALFTONE);
		m_image->m_image.StretchBlt(hdc, imageRect.left, imageRect.top, imageRect.Width(), imageRect.Height(), SRCCOPY);
		::SetStretchBltMode(hdc, mode);
	}
	else
	{
		// output error message if it lost the specified splash image
		std::basic_string<charT> errorMsg;
		errorMsg = str_printf(_T("lost image file"));
		::DrawText(hdc, errorMsg.c_str(), errorMsg.length(), &imageRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}
	EndPaint(&ps);
	return 0;
}

LRESULT MyDialog::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	// update resolution
	m_cfg.setInt(_T("width"), GetDlgItemInt(IDC_EDIT1, NULL, FALSE));
	m_cfg.setInt(_T("height"), GetDlgItemInt(IDC_EDIT2, NULL, FALSE));

	// update screen mode
	m_cfg.setInt(_T("screenmode"), (my::Game::SCREEN_MODE)GetDlgItem(IDC_COMBO2).SendMessage(CB_GETCURSEL, 0, 0));

	// update aspect ratio mode
	m_cfg.setInt(_T("aspectratio"), (MyGame::ASPECT_RATIO)GetDlgItem(IDC_COMBO3).SendMessage(CB_GETCURSEL, 0, 0));

	// update save configuration option
	m_save_configuration = IsDlgButtonChecked(IDC_CHECK1);

	EndDialog(wID);
	return 0;
}

LRESULT MyDialog::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT MyDialog::OnCombo1SelChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	// update current selected resolution to edit box
	CWindow combo1 = GetDlgItem(IDC_COMBO1);
	int nIndex = combo1.SendMessage(CB_GETCURSEL, 0, 0);
	_ASSERT(CB_ERR != nIndex);
	std::basic_string<charT> strTmp;
	strTmp.resize(combo1.SendMessage(CB_GETLBTEXTLEN, nIndex, 0));
	VERIFY(CB_ERR != combo1.SendMessage(CB_GETLBTEXT, nIndex, (LPARAM)&strTmp[0]));
	int nWidth, nHeight;
	VERIFY(2 == _stscanf_s(strTmp.c_str(), _T("%dx%d"), &nWidth, &nHeight));
	VERIFY(SetDlgItemInt(IDC_EDIT1, nWidth, FALSE));
	VERIFY(SetDlgItemInt(IDC_EDIT2, nHeight, FALSE));
	return 0;
}
