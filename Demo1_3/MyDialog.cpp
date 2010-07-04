
#include "stdafx.h"
#include "MyDialog.h"
#include "resource.h"
#include "MyGameEx.h"

static const charT SPLASH_IMAGE_NAME[] = _T("splash.jpg");

MyDialog::MyDialog(const my::Config & cfg, HINSTANCE hInstance /*= ::GetModuleHandle(NULL)*/, HWND hWndParent /*= NULL*/)
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
			std::basic_string<charT> filePath = my::ResourceMgr::getSingleton().findFile(SPLASH_IMAGE_NAME);
			if(!filePath.empty())
			{
				m_image = my::ImagePtr(new my::Image(filePath));
			}

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
			if(CB_ERR == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO1), CB_SELECTSTRING, (WPARAM)-1, (LPARAM)str_printf(_T("%dx%d"), m_cfg.getInt(_T("width")), m_cfg.getInt(_T("height"))).c_str()))
			{
				// for use customized resolution
				VERIFY(::SetDlgItemInt(m_hdlg, IDC_EDIT1, m_cfg.getInt(_T("width")), FALSE));
				VERIFY(::SetDlgItemInt(m_hdlg, IDC_EDIT2, m_cfg.getInt(_T("height")), FALSE));
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
			if(CB_ERR == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO2), CB_SETCURSEL, m_cfg.getInt(_T("screenmode")), 0))
			{
				VERIFY(0 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO2), CB_SETCURSEL, 0, 0));
			}

			// initialize combo box3 with aspect ratio mode
			VERIFY(MyGameEx::ASPECT_RATIO_STRETCHED == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO3), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("Stretch mode")));
			VERIFY(MyGameEx::ASPECT_RATIO_STANDARD == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO3), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("4 : 3")));
			VERIFY(MyGameEx::ASPECT_RATIO_WIDESCREEN == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO3), CB_INSERTSTRING, (WPARAM)-1, (LPARAM)_T("16 : 9")));

			// select the specified aspect ratio mode
			if(CB_ERR == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO3), CB_SETCURSEL, m_cfg.getInt(_T("aspectratio")), 0))
			{
				VERIFY(0 == ::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO3), CB_SETCURSEL, 0, 0));
			}

			// initialize check box1 with save configuration option
			VERIFY(::CheckDlgButton(m_hdlg, IDC_CHECK1, m_save_configuration));
		}
		break;

	case WM_PAINT:
		{
			// get custom control imageRect
			CRect imageRect;
			VERIFY(::GetWindowRect(::GetDlgItem(hwndDlg, IDC_STATIC1), &imageRect));
			::ScreenToClient(hwndDlg, (LPPOINT)&imageRect.left);
			::ScreenToClient(hwndDlg, (LPPOINT)&imageRect.right);

			// draw this image to screen
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwndDlg, &ps);
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
				errorMsg = str_printf(_T("lost %s"), SPLASH_IMAGE_NAME);
				::DrawText(hdc, errorMsg.c_str(), errorMsg.length(), &imageRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			}
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
				m_cfg.setInt(_T("width"), ::GetDlgItemInt(m_hdlg, IDC_EDIT1, NULL, FALSE));
				m_cfg.setInt(_T("height"), ::GetDlgItemInt(m_hdlg, IDC_EDIT2, NULL, FALSE));

				// update screen mode
				m_cfg.setInt(_T("screenmode"), (my::Game::SCREEN_MODE)::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO2), CB_GETCURSEL, 0, 0));

				// update aspect ratio mode
				m_cfg.setInt(_T("aspectratio"), (MyGameEx::ASPECT_RATIO)::SendMessage(::GetDlgItem(m_hdlg, IDC_COMBO3), CB_GETCURSEL, 0, 0));

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
