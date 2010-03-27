
#include "stdafx.h"
#include "MyDialog.h"
#include "resource.h"

MyDialog::MyDialog(const MyConfig & cfg, HINSTANCE hInstance /*= ::GetModuleHandle(NULL)*/, HWND hWndParent /*= NULL*/)
	: my::Dialog(hInstance, (LPCTSTR)IDD_DIALOG1, hWndParent)
	, m_cfg(cfg)
	, m_save_configuration(BST_UNCHECKED)
{
}

MyDialog::~MyDialog(void)
{
}

INT_PTR MyDialog::onProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			// initialize dialog title
			::SetWindowText(m_hdlg, _T("User Configuration"));

			// initialize splash image
			m_image = my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("002(1).jpg"))));

			// initialize combo box1 with resolutions
			VERIFY(0 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("320x240")));
			VERIFY(1 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("640x480")));
			VERIFY(2 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("800x600")));
			VERIFY(3 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1024x768")));
			VERIFY(4 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1280x800")));
			VERIFY(5 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1280x1024")));
			VERIFY(6 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1366x768")));
			VERIFY(7 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("1680x1050")));

			// select the specified resolution
			if(CB_ERR == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_SELECTSTRING, (WPARAM)-1, (LPARAM)str_printf(_T("%dx%d"), m_cfg.width, m_cfg.height).c_str()))
			{
				// for use customized resolution
				VERIFY(::SetDlgItemInt(m_hdlg, IDC_EDIT1, m_cfg.width, FALSE));
				VERIFY(::SetDlgItemInt(m_hdlg, IDC_EDIT2, m_cfg.height, FALSE));
			}
			else
			{
				::SendMessage(m_hdlg, WM_COMMAND, MAKEWPARAM(IDC_COMBO1, CBN_SELCHANGE), (LPARAM)::GetDlgItem(m_hdlg, IDC_COMBO1));
			}

			// initialize combo box2 with screen modes
			VERIFY(my::Game::SCREEN_MODE_WINDOWED == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO2), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("Windowed mode")));
			VERIFY(my::Game::SCREEN_MODE_FULLSCREEN16 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO2), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("16bpp full screen")));
			VERIFY(my::Game::SCREEN_MODE_FULLSCREEN32 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO2), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("32bpp full screen")));

			// select the specified screen mode
			if(CB_ERR == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO2), CB_SETCURSEL, m_cfg.smode, 0))
			{
				VERIFY(0 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO2), CB_SETCURSEL, 0, 0));
			}

			// initialize combo box3 with aspect ratio mode
			VERIFY(MyConfig::ASPECT_RATIO_STRETCHED == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO3), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("Stretch mode")));
			VERIFY(MyConfig::ASPECT_RATIO_STANDARD == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO3), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("4 : 3")));
			VERIFY(MyConfig::ASPECT_RATIO_WIDESCREEN == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO3), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("16 : 9")));

			// select the specified aspect ratio mode
			if(CB_ERR == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO3), CB_SETCURSEL, m_cfg.aspect_ratio_mode, 0))
			{
				VERIFY(0 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO3), CB_SETCURSEL, 0, 0));
			}

			// initialize check box1 with save configuration option
			VERIFY(::CheckDlgButton(m_hdlg, IDC_CHECK1, m_save_configuration));
		}
		break;

	case WM_PAINT:
		{
			// get window rect
			CRect rect;
			::GetClientRect(hwndDlg, &rect);

			// draw this image to screen
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwndDlg, &ps);
			//m_image->m_image.BitBlt(hdc, 0, 0, SRCCOPY);
			m_image->m_image.StretchBlt(hdc, rect.left, rect.top, rect.Width(), rect.Height(), SRCCOPY);
			EndPaint(hwndDlg, &ps);
		}
		break;

	case WM_COMMAND:
		switch(HIWORD(wParam))
		{
		case 0:
			if(LOWORD(wParam) == IDOK)
			{
				// update resolution
				m_cfg.width = ::GetDlgItemInt(m_hdlg, IDC_EDIT1, NULL, FALSE);
				m_cfg.height = ::GetDlgItemInt(m_hdlg, IDC_EDIT2, NULL, FALSE);

				// update screen mode
				m_cfg.smode = (my::Game::SCREEN_MODE)::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO2), CB_GETCURSEL, 0, 0);

				// update aspect ratio mode
				m_cfg.aspect_ratio_mode = (MyConfig::ASPECT_RATIO)::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO3), CB_GETCURSEL, 0, 0);

				// update save configuration option
				m_save_configuration = ::IsDlgButtonChecked(m_hdlg, IDC_CHECK1);
			}
			break;

		case CBN_SELCHANGE:
			if(LOWORD(wParam) == IDC_COMBO1)
			{
				// update current selected resolution to edit box
				int nIndex = ::SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				_ASSERT(CB_ERR != nIndex);
				std::basic_string<charT> strTmp;
				strTmp.resize(::SendMessage((HWND)lParam, CB_GETLBTEXTLEN, nIndex, 0));
				VERIFY(CB_ERR != ::SendMessage((HWND)lParam, CB_GETLBTEXT, nIndex, (LPARAM)&strTmp[0]));
				int nWidth, nHeight;
				VERIFY(2 == _stscanf_s(strTmp.c_str(), _T("%dx%d"), &nWidth, &nHeight));
				VERIFY(::SetDlgItemInt(m_hdlg, IDC_EDIT1, nWidth, FALSE));
				VERIFY(::SetDlgItemInt(m_hdlg, IDC_EDIT2, nHeight, FALSE));
			}
			break;
		}
		break;
	}
	return my::Dialog::onProc(hwndDlg, uMsg, wParam, lParam);
}
