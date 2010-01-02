
#include "stdafx.h"
#include "myWindow.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <crtdbg.h>

namespace my
{
	std::basic_string<charT> WinException::GetErrorCodeStr(DWORD dwCode)
	{
		LPVOID lpMsg;
		if(0 == ::FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, dwCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsg, 0, NULL))
		{
			return GetErrorCodeStr(::GetLastError());
		}

		std::basic_string<charT> ret((charT *)lpMsg);
		::LocalFree(lpMsg);
		return ret;
	}

	WinException::WinException(const std::basic_string<charT> & file, int line, DWORD dwCode)
		: t3d::Exception(file, line)
		, m_code(dwCode)
	{
	}

	std::basic_string<charT> WinException::what(void) const throw()
	{
		return GetErrorCodeStr(m_code);
	}

	std::basic_string<charT> WindowBase::getWindowMessageStr(UINT message)
	{
		const charT * pstr;
		switch(message)
		{
		case WM_NULL:
			pstr = _T("WM_NULL"); break;
		case WM_CREATE:
			pstr = _T("WM_CREATE"); break;
		case WM_DESTROY:
			pstr = _T("WM_DESTROY"); break;
		case WM_MOVE:
			pstr = _T("WM_MOVE"); break;
		case WM_SIZE:
			pstr = _T("WM_SIZE"); break;
		case WM_ACTIVATE:
			pstr = _T("WM_ACTIVATE"); break;
		case WM_SETFOCUS:
			pstr = _T("WM_SETFOCUS"); break;
		case WM_KILLFOCUS:
			pstr = _T("WM_KILLFOCUS"); break;
		case WM_ENABLE:
			pstr = _T("WM_ENABLE"); break;
		case WM_SETREDRAW:
			pstr = _T("WM_SETREDRAW"); break;
		case WM_SETTEXT:
			pstr = _T("WM_SETTEXT"); break;
		case WM_GETTEXT:
			pstr = _T("WM_GETTEXT"); break;
		case WM_GETTEXTLENGTH:
			pstr = _T("WM_GETTEXTLENGTH"); break;
		case WM_PAINT:
			pstr = _T("WM_PAINT"); break;
		case WM_CLOSE:
			pstr = _T("WM_CLOSE"); break;
#ifndef _WIN32_WCE
		case WM_QUERYENDSESSION:
			pstr = _T("WM_QUERYENDSESSION"); break;
		case WM_QUERYOPEN:
			pstr = _T("WM_QUERYOPEN"); break;
		case WM_ENDSESSION:
			pstr = _T("WM_ENDSESSION"); break;
#endif
		case WM_QUIT:
			pstr = _T("WM_QUIT"); break;
		case WM_ERASEBKGND:
			pstr = _T("WM_ERASEBKGND"); break;
		case WM_SYSCOLORCHANGE:
			pstr = _T("WM_SYSCOLORCHANGE"); break;
		case WM_SHOWWINDOW:
			pstr = _T("WM_SHOWWINDOW"); break;
		case WM_WININICHANGE:
			pstr = _T("WM_WININICHANGE"); break;
#if(WINVER >= 0x0400)
		//case WM_SETTINGCHANGE:
		//	pstr = _T("WM_SETTINGCHANGE"); break;
#endif /* WINVER >= 0x0400 */
		case WM_DEVMODECHANGE:
			pstr = _T("WM_DEVMODECHANGE"); break;
		case WM_ACTIVATEAPP:
			pstr = _T("WM_ACTIVATEAPP"); break;
		case WM_FONTCHANGE:
			pstr = _T("WM_FONTCHANGE"); break;
		case WM_TIMECHANGE:
			pstr = _T("WM_TIMECHANGE"); break;
		case WM_CANCELMODE:
			pstr = _T("WM_CANCELMODE"); break;
		case WM_SETCURSOR:
			pstr = _T("WM_SETCURSOR"); break;
		case WM_MOUSEACTIVATE:
			pstr = _T("WM_MOUSEACTIVATE"); break;
		case WM_CHILDACTIVATE:
			pstr = _T("WM_CHILDACTIVATE"); break;
		case WM_QUEUESYNC:
			pstr = _T("WM_QUEUESYNC"); break;
		case WM_GETMINMAXINFO:
			pstr = _T("WM_GETMINMAXINFO"); break;
		case WM_PAINTICON:
			pstr = _T("WM_PAINTICON"); break;
		case WM_ICONERASEBKGND:
			pstr = _T("WM_ICONERASEBKGND"); break;
		case WM_NEXTDLGCTL:
			pstr = _T("WM_NEXTDLGCTL"); break;
		case WM_SPOOLERSTATUS:
			pstr = _T("WM_SPOOLERSTATUS"); break;
		case WM_DRAWITEM:
			pstr = _T("WM_DRAWITEM"); break;
		case WM_MEASUREITEM:
			pstr = _T("WM_MEASUREITEM"); break;
		case WM_DELETEITEM:
			pstr = _T("WM_DELETEITEM"); break;
		case WM_VKEYTOITEM:
			pstr = _T("WM_VKEYTOITEM"); break;
		case WM_CHARTOITEM:
			pstr = _T("WM_CHARTOITEM"); break;
		case WM_SETFONT:
			pstr = _T("WM_SETFONT"); break;
		case WM_GETFONT:
			pstr = _T("WM_GETFONT"); break;
		case WM_SETHOTKEY:
			pstr = _T("WM_SETHOTKEY"); break;
		case WM_GETHOTKEY:
			pstr = _T("WM_GETHOTKEY"); break;
		case WM_QUERYDRAGICON:
			pstr = _T("WM_QUERYDRAGICON"); break;
		case WM_COMPAREITEM:
			pstr = _T("WM_COMPAREITEM"); break;
#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
		case WM_GETOBJECT:
			pstr = _T("WM_GETOBJECT"); break;
#endif
#endif /* WINVER >= 0x0500 */
		case WM_COMPACTING:
			pstr = _T("WM_COMPACTING"); break;
		case WM_COMMNOTIFY:
			pstr = _T("WM_COMMNOTIFY"); break;
		case WM_WINDOWPOSCHANGING:
			pstr = _T("WM_WINDOWPOSCHANGING"); break;
		case WM_WINDOWPOSCHANGED:
			pstr = _T("WM_WINDOWPOSCHANGED"); break;
		case WM_POWER:
			pstr = _T("WM_POWER"); break;
		case WM_COPYDATA:
			pstr = _T("WM_COPYDATA"); break;
		case WM_CANCELJOURNAL:
			pstr = _T("WM_CANCELJOURNAL"); break;
#if(WINVER >= 0x0400)
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0400)
		case WM_NOTIFY:
			pstr = _T("WM_NOTIFY"); break;
		case WM_INPUTLANGCHANGEREQUEST:
			pstr = _T("WM_INPUTLANGCHANGEREQUEST"); break;
		case WM_INPUTLANGCHANGE:
			pstr = _T("WM_INPUTLANGCHANGE"); break;
		case WM_TCARD:
			pstr = _T("WM_TCARD"); break;
		case WM_HELP:
			pstr = _T("WM_HELP"); break;
		case WM_USERCHANGED:
			pstr = _T("WM_USERCHANGED"); break;
		case WM_NOTIFYFORMAT:
			pstr = _T("WM_NOTIFYFORMAT"); break;
		case WM_CONTEXTMENU:
			pstr = _T("WM_CONTEXTMENU"); break;
		case WM_STYLECHANGING:
			pstr = _T("WM_STYLECHANGING"); break;
		case WM_STYLECHANGED:
			pstr = _T("WM_STYLECHANGED"); break;
		case WM_DISPLAYCHANGE:
			pstr = _T("WM_DISPLAYCHANGE"); break;
		case WM_GETICON:
			pstr = _T("WM_GETICON"); break;
		case WM_SETICON:
			pstr = _T("WM_SETICON"); break;
#endif /* WINVER >= 0x0400 */
		case WM_NCCREATE:
			pstr = _T("WM_NCCREATE"); break;
		case WM_NCDESTROY:
			pstr = _T("WM_NCDESTROY"); break;
		case WM_NCCALCSIZE:
			pstr = _T("WM_NCCALCSIZE"); break;
		case WM_NCHITTEST:
			pstr = _T("WM_NCHITTEST"); break;
		case WM_NCPAINT:
			pstr = _T("WM_NCPAINT"); break;
		case WM_NCACTIVATE:
			pstr = _T("WM_NCACTIVATE"); break;
		case WM_GETDLGCODE:
			pstr = _T("WM_GETDLGCODE"); break;
#ifndef _WIN32_WCE
		case WM_SYNCPAINT:
			pstr = _T("WM_SYNCPAINT"); break;
#endif
		case WM_NCMOUSEMOVE:
			pstr = _T("WM_NCMOUSEMOVE"); break;
		case WM_NCLBUTTONDOWN:
			pstr = _T("WM_NCLBUTTONDOWN"); break;
		case WM_NCLBUTTONUP:
			pstr = _T("WM_NCLBUTTONUP"); break;
		case WM_NCLBUTTONDBLCLK:
			pstr = _T("WM_NCLBUTTONDBLCLK"); break;
		case WM_NCRBUTTONDOWN:
			pstr = _T("WM_NCRBUTTONDOWN"); break;
		case WM_NCRBUTTONUP:
			pstr = _T("WM_NCRBUTTONUP"); break;
		case WM_NCRBUTTONDBLCLK:
			pstr = _T("WM_NCRBUTTONDBLCLK"); break;
		case WM_NCMBUTTONDOWN:
			pstr = _T("WM_NCMBUTTONDOWN"); break;
		case WM_NCMBUTTONUP:
			pstr = _T("WM_NCMBUTTONUP"); break;
		case WM_NCMBUTTONDBLCLK:
			pstr = _T("WM_NCMBUTTONDBLCLK"); break;
#if(_WIN32_WINNT >= 0x0500)
		case WM_NCXBUTTONDOWN:
			pstr = _T("WM_NCXBUTTONDOWN"); break;
		case WM_NCXBUTTONUP:
			pstr = _T("WM_NCXBUTTONUP"); break;
		case WM_NCXBUTTONDBLCLK:
			pstr = _T("WM_NCXBUTTONDBLCLK"); break;
#endif /* _WIN32_WINNT >= 0x0500 */
#if(_WIN32_WINNT >= 0x0501)
		case WM_INPUT:
			pstr = _T("WM_INPUT"); break;
#endif /* _WIN32_WINNT >= 0x0501 */
		case WM_KEYFIRST:
			pstr = _T("WM_KEYFIRST"); break;
		//case WM_KEYDOWN:
		//	pstr = _T("WM_KEYDOWN"); break;
		case WM_KEYUP:
			pstr = _T("WM_KEYUP"); break;
		case WM_CHAR:
			pstr = _T("WM_CHAR"); break;
		case WM_DEADCHAR:
			pstr = _T("WM_DEADCHAR"); break;
		case WM_SYSKEYDOWN:
			pstr = _T("WM_SYSKEYDOWN"); break;
		case WM_SYSKEYUP:
			pstr = _T("WM_SYSKEYUP"); break;
		case WM_SYSCHAR:
			pstr = _T("WM_SYSCHAR"); break;
		case WM_SYSDEADCHAR:
			pstr = _T("WM_SYSDEADCHAR"); break;
#if(_WIN32_WINNT >= 0x0501)
		case WM_UNICHAR:
			pstr = _T("WM_UNICHAR"); break;
		//case WM_KEYLAST:
		//	pstr = _T("WM_KEYLAST"); break;
#else
		case WM_KEYLAST:
			pstr = _T("WM_KEYLAST"); break;
#endif /* _WIN32_WINNT >= 0x0501 */
#if(WINVER >= 0x0400)
		case WM_IME_STARTCOMPOSITION:
			pstr = _T("WM_IME_STARTCOMPOSITION"); break;
		case WM_IME_ENDCOMPOSITION:
			pstr = _T("WM_IME_ENDCOMPOSITION"); break;
		case WM_IME_COMPOSITION:
			pstr = _T("WM_IME_COMPOSITION"); break;
		//case WM_IME_KEYLAST:
		//	pstr = _T("WM_IME_KEYLAST"); break;
#endif /* WINVER >= 0x0400 */
		case WM_INITDIALOG:
			pstr = _T("WM_INITDIALOG"); break;
		case WM_COMMAND:
			pstr = _T("WM_COMMAND"); break;
		case WM_SYSCOMMAND:
			pstr = _T("WM_SYSCOMMAND"); break;
		case WM_TIMER:
			pstr = _T("WM_TIMER"); break;
		case WM_HSCROLL:
			pstr = _T("WM_HSCROLL"); break;
		case WM_VSCROLL:
			pstr = _T("WM_VSCROLL"); break;
		case WM_INITMENU:
			pstr = _T("WM_INITMENU"); break;
		case WM_INITMENUPOPUP:
			pstr = _T("WM_INITMENUPOPUP"); break;
		case WM_MENUSELECT:
			pstr = _T("WM_MENUSELECT"); break;
		case WM_MENUCHAR:
			pstr = _T("WM_MENUCHAR"); break;
		case WM_ENTERIDLE:
			pstr = _T("WM_ENTERIDLE"); break;
#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
		case WM_MENURBUTTONUP:
			pstr = _T("WM_MENURBUTTONUP"); break;
		case WM_MENUDRAG:
			pstr = _T("WM_MENUDRAG"); break;
		case WM_MENUGETOBJECT:
			pstr = _T("WM_MENUGETOBJECT"); break;
		case WM_UNINITMENUPOPUP:
			pstr = _T("WM_UNINITMENUPOPUP"); break;
		case WM_MENUCOMMAND:
			pstr = _T("WM_MENUCOMMAND"); break;
#ifndef _WIN32_WCE
#if(_WIN32_WINNT >= 0x0500)
		case WM_CHANGEUISTATE:
			pstr = _T("WM_CHANGEUISTATE"); break;
		case WM_UPDATEUISTATE:
			pstr = _T("WM_UPDATEUISTATE"); break;
		case WM_QUERYUISTATE:
			pstr = _T("WM_QUERYUISTATE"); break;
#if(_WIN32_WINNT >= 0x0501)
#endif /* _WIN32_WINNT >= 0x0501 */
#endif /* _WIN32_WINNT >= 0x0500 */
#endif
#endif
#endif /* WINVER >= 0x0500 */
		case WM_CTLCOLORMSGBOX:
			pstr = _T("WM_CTLCOLORMSGBOX"); break;
		case WM_CTLCOLOREDIT:
			pstr = _T("WM_CTLCOLOREDIT"); break;
		case WM_CTLCOLORLISTBOX:
			pstr = _T("WM_CTLCOLORLISTBOX"); break;
		case WM_CTLCOLORBTN:
			pstr = _T("WM_CTLCOLORBTN"); break;
		case WM_CTLCOLORDLG:
			pstr = _T("WM_CTLCOLORDLG"); break;
		case WM_CTLCOLORSCROLLBAR:
			pstr = _T("WM_CTLCOLORSCROLLBAR"); break;
		case WM_CTLCOLORSTATIC:
			pstr = _T("WM_CTLCOLORSTATIC"); break;
		case MN_GETHMENU:
			pstr = _T("MN_GETHMENU"); break;
		case WM_MOUSEFIRST:
			pstr = _T("WM_MOUSEFIRST"); break;
		//case WM_MOUSEMOVE:
		//	pstr = _T("WM_MOUSEMOVE"); break;
		case WM_LBUTTONDOWN:
			pstr = _T("WM_LBUTTONDOWN"); break;
		case WM_LBUTTONUP:
			pstr = _T("WM_LBUTTONUP"); break;
		case WM_LBUTTONDBLCLK:
			pstr = _T("WM_LBUTTONDBLCLK"); break;
		case WM_RBUTTONDOWN:
			pstr = _T("WM_RBUTTONDOWN"); break;
		case WM_RBUTTONUP:
			pstr = _T("WM_RBUTTONUP"); break;
		case WM_RBUTTONDBLCLK:
			pstr = _T("WM_RBUTTONDBLCLK"); break;
		case WM_MBUTTONDOWN:
			pstr = _T("WM_MBUTTONDOWN"); break;
		case WM_MBUTTONUP:
			pstr = _T("WM_MBUTTONUP"); break;
		case WM_MBUTTONDBLCLK:
			pstr = _T("WM_MBUTTONDBLCLK"); break;
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
		case WM_MOUSEWHEEL:
			pstr = _T("WM_MOUSEWHEEL"); break;
#endif
#if (_WIN32_WINNT >= 0x0500)
		case WM_XBUTTONDOWN:
			pstr = _T("WM_XBUTTONDOWN"); break;
		case WM_XBUTTONUP:
			pstr = _T("WM_XBUTTONUP"); break;
		case WM_XBUTTONDBLCLK:
			pstr = _T("WM_XBUTTONDBLCLK"); break;
#endif
#if (_WIN32_WINNT >= 0x0500)
		case WM_MOUSELAST:
			pstr = _T("WM_MOUSELAST"); break;
#elif (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
		case WM_MOUSELAST:
			pstr = _T("WM_MOUSELAST"); break;
#else
		//case WM_MOUSELAST:
		//	pstr = _T("WM_MOUSELAST"); break;
#endif /* (_WIN32_WINNT >= 0x0500) */
#if(_WIN32_WINNT >= 0x0400)
#endif /* _WIN32_WINNT >= 0x0400 */
#if(_WIN32_WINNT >= 0x0500)
#endif /* _WIN32_WINNT >= 0x0500 */
		case WM_PARENTNOTIFY:
			pstr = _T("WM_PARENTNOTIFY"); break;
		case WM_ENTERMENULOOP:
			pstr = _T("WM_ENTERMENULOOP"); break;
		case WM_EXITMENULOOP:
			pstr = _T("WM_EXITMENULOOP"); break;
#if(WINVER >= 0x0400)
		case WM_NEXTMENU:
			pstr = _T("WM_NEXTMENU"); break;
		case WM_SIZING:
			pstr = _T("WM_SIZING"); break;
		case WM_CAPTURECHANGED:
			pstr = _T("WM_CAPTURECHANGED"); break;
		case WM_MOVING:
			pstr = _T("WM_MOVING"); break;
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0400)
		case WM_POWERBROADCAST:
			pstr = _T("WM_POWERBROADCAST"); break;
#ifndef _WIN32_WCE
#endif
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0400)
		case WM_DEVICECHANGE:
			pstr = _T("WM_DEVICECHANGE"); break;
#endif /* WINVER >= 0x0400 */
		case WM_MDICREATE:
			pstr = _T("WM_MDICREATE"); break;
		case WM_MDIDESTROY:
			pstr = _T("WM_MDIDESTROY"); break;
		case WM_MDIACTIVATE:
			pstr = _T("WM_MDIACTIVATE"); break;
		case WM_MDIRESTORE:
			pstr = _T("WM_MDIRESTORE"); break;
		case WM_MDINEXT:
			pstr = _T("WM_MDINEXT"); break;
		case WM_MDIMAXIMIZE:
			pstr = _T("WM_MDIMAXIMIZE"); break;
		case WM_MDITILE:
			pstr = _T("WM_MDITILE"); break;
		case WM_MDICASCADE:
			pstr = _T("WM_MDICASCADE"); break;
		case WM_MDIICONARRANGE:
			pstr = _T("WM_MDIICONARRANGE"); break;
		case WM_MDIGETACTIVE:
			pstr = _T("WM_MDIGETACTIVE"); break;
		case WM_MDISETMENU:
			pstr = _T("WM_MDISETMENU"); break;
		case WM_ENTERSIZEMOVE:
			pstr = _T("WM_ENTERSIZEMOVE"); break;
		case WM_EXITSIZEMOVE:
			pstr = _T("WM_EXITSIZEMOVE"); break;
		case WM_DROPFILES:
			pstr = _T("WM_DROPFILES"); break;
		case WM_MDIREFRESHMENU:
			pstr = _T("WM_MDIREFRESHMENU"); break;
#if(WINVER >= 0x0400)
		case WM_IME_SETCONTEXT:
			pstr = _T("WM_IME_SETCONTEXT"); break;
		case WM_IME_NOTIFY:
			pstr = _T("WM_IME_NOTIFY"); break;
		case WM_IME_CONTROL:
			pstr = _T("WM_IME_CONTROL"); break;
		case WM_IME_COMPOSITIONFULL:
			pstr = _T("WM_IME_COMPOSITIONFULL"); break;
		case WM_IME_SELECT:
			pstr = _T("WM_IME_SELECT"); break;
		case WM_IME_CHAR:
			pstr = _T("WM_IME_CHAR"); break;
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0500)
		case WM_IME_REQUEST:
			pstr = _T("WM_IME_REQUEST"); break;
#endif /* WINVER >= 0x0500 */
#if(WINVER >= 0x0400)
		case WM_IME_KEYDOWN:
			pstr = _T("WM_IME_KEYDOWN"); break;
		case WM_IME_KEYUP:
			pstr = _T("WM_IME_KEYUP"); break;
#endif /* WINVER >= 0x0400 */
#if((_WIN32_WINNT >= 0x0400) || (WINVER >= 0x0500))
		case WM_MOUSEHOVER:
			pstr = _T("WM_MOUSEHOVER"); break;
		case WM_MOUSELEAVE:
			pstr = _T("WM_MOUSELEAVE"); break;
#endif
#if(WINVER >= 0x0500)
		case WM_NCMOUSEHOVER:
			pstr = _T("WM_NCMOUSEHOVER"); break;
		case WM_NCMOUSELEAVE:
			pstr = _T("WM_NCMOUSELEAVE"); break;
#endif /* WINVER >= 0x0500 */
#if(_WIN32_WINNT >= 0x0501)
		case WM_WTSSESSION_CHANGE:
			pstr = _T("WM_WTSSESSION_CHANGE"); break;
		case WM_TABLET_FIRST:
			pstr = _T("WM_TABLET_FIRST"); break;
		case WM_TABLET_LAST:
			pstr = _T("WM_TABLET_LAST"); break;
#endif /* _WIN32_WINNT >= 0x0501 */
		case WM_CUT:
			pstr = _T("WM_CUT"); break;
		case WM_COPY:
			pstr = _T("WM_COPY"); break;
		case WM_PASTE:
			pstr = _T("WM_PASTE"); break;
		case WM_CLEAR:
			pstr = _T("WM_CLEAR"); break;
		case WM_UNDO:
			pstr = _T("WM_UNDO"); break;
		case WM_RENDERFORMAT:
			pstr = _T("WM_RENDERFORMAT"); break;
		case WM_RENDERALLFORMATS:
			pstr = _T("WM_RENDERALLFORMATS"); break;
		case WM_DESTROYCLIPBOARD:
			pstr = _T("WM_DESTROYCLIPBOARD"); break;
		case WM_DRAWCLIPBOARD:
			pstr = _T("WM_DRAWCLIPBOARD"); break;
		case WM_PAINTCLIPBOARD:
			pstr = _T("WM_PAINTCLIPBOARD"); break;
		case WM_VSCROLLCLIPBOARD:
			pstr = _T("WM_VSCROLLCLIPBOARD"); break;
		case WM_SIZECLIPBOARD:
			pstr = _T("WM_SIZECLIPBOARD"); break;
		case WM_ASKCBFORMATNAME:
			pstr = _T("WM_ASKCBFORMATNAME"); break;
		case WM_CHANGECBCHAIN:
			pstr = _T("WM_CHANGECBCHAIN"); break;
		case WM_HSCROLLCLIPBOARD:
			pstr = _T("WM_HSCROLLCLIPBOARD"); break;
		case WM_QUERYNEWPALETTE:
			pstr = _T("WM_QUERYNEWPALETTE"); break;
		case WM_PALETTEISCHANGING:
			pstr = _T("WM_PALETTEISCHANGING"); break;
		case WM_PALETTECHANGED:
			pstr = _T("WM_PALETTECHANGED"); break;
		case WM_HOTKEY:
			pstr = _T("WM_HOTKEY"); break;
#if(WINVER >= 0x0400)
		case WM_PRINT:
			pstr = _T("WM_PRINT"); break;
		case WM_PRINTCLIENT:
			pstr = _T("WM_PRINTCLIENT"); break;
#endif /* WINVER >= 0x0400 */
#if(_WIN32_WINNT >= 0x0500)
		case WM_APPCOMMAND:
			pstr = _T("WM_APPCOMMAND"); break;
#endif /* _WIN32_WINNT >= 0x0500 */
#if(_WIN32_WINNT >= 0x0501)
		case WM_THEMECHANGED:
			pstr = _T("WM_THEMECHANGED"); break;
#endif /* _WIN32_WINNT >= 0x0501 */
#if(WINVER >= 0x0400)
		case WM_HANDHELDFIRST:
			pstr = _T("WM_HANDHELDFIRST"); break;
		case WM_HANDHELDLAST:
			pstr = _T("WM_HANDHELDLAST"); break;
		case WM_AFXFIRST:
			pstr = _T("WM_AFXFIRST"); break;
		case WM_AFXLAST:
			pstr = _T("WM_AFXLAST"); break;
#endif /* WINVER >= 0x0400 */
		case WM_PENWINFIRST:
			pstr = _T("WM_PENWINFIRST"); break;
		case WM_PENWINLAST:
			pstr = _T("WM_PENWINLAST"); break;
#if(WINVER >= 0x0400)
		case WM_APP:
			pstr = _T("WM_APP"); break;
#endif /* WINVER >= 0x0400 */
		case WM_USER:
			pstr = _T("WM_USER"); break;
		default:
			std::basic_ostringstream<charT> osstr;
			osstr << _T("unknown window message: ") << std::hex << std::showbase << message;
			return osstr.str();
		}

		return std::basic_string<charT>(pstr);
	}

	WindowBase::WindowBase(HWND hwnd /*= NULL*/)
		: m_hwnd(hwnd)
	{
	}

	WindowBase::~WindowBase(void)
	{
	}

	void WindowBase::showWindow(int nShow /*= SW_NORMAL*/)
	{
		::ShowWindow(m_hwnd, nShow);

		if(!::UpdateWindow(m_hwnd))
			T3D_WINEXCEPT(::GetLastError());
	}

	std::basic_string<charT> WindowBase::getWindowText(void) const
	{
		static const size_t def_size = 512;
		static const size_t inc_size = 512;

		assert(inc_size <= def_size);
		size_t new_size = def_size - inc_size;
		size_t ret_size = def_size;
		charT * buffer = NULL;

		while(ret_size >= new_size)
		{
			new_size += inc_size;
			buffer = (charT *)realloc(buffer, new_size * sizeof(charT));
			if(NULL == buffer)
				T3D_CUSEXCEPT(_T("realloc buffer failed"));

			ret_size = ::GetWindowText(m_hwnd, buffer, (int)new_size);
			if(0 == ret_size)
				T3D_WINEXCEPT(::GetLastError());
		}

		return std::basic_string<charT>(buffer);
	}

	void WindowBase::setWindowText(const std::basic_string<charT> winTitle)
	{
		if(!::SetWindowText(m_hwnd, winTitle.c_str()))
			T3D_WINEXCEPT(::GetLastError());
	}

	DWORD WindowBase::getWindowStyle(void) const
	{
		return ::GetWindowLong(m_hwnd, GWL_STYLE);
	}

	void WindowBase::setWindowStyle(DWORD dwStyle)
	{
		if(0 == ::SetWindowLong(m_hwnd, GWL_STYLE, (LONG)dwStyle))
			T3D_WINEXCEPT(::GetLastError());

		if(0 == ::SetWindowPos(m_hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER))
			T3D_WINEXCEPT(::GetLastError());
	}

	DWORD WindowBase::getWindowExtansionStyle(void) const
	{
		return ::GetWindowLong(m_hwnd, GWL_EXSTYLE);
	}

	void WindowBase::setWindowExtansionStyle(DWORD dwExStyle)
	{
		if(0 == ::SetWindowLong(m_hwnd, GWL_EXSTYLE, (LONG)dwExStyle))
			T3D_WINEXCEPT(::GetLastError());

		if(!::SetWindowPos(m_hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOZORDER))
			T3D_WINEXCEPT(::GetLastError());
	}

	RECT WindowBase::getWindowRect(void) const
	{
		RECT rect;
		if(!::GetWindowRect(m_hwnd, &rect))
			T3D_WINEXCEPT(::GetLastError());
		return rect;
	}

	void WindowBase::setWindowRect(const RECT & rect)
	{
		if(!::SetWindowPos(m_hwnd, HWND_TOP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0))
			T3D_WINEXCEPT(::GetLastError());
	}

	RECT WindowBase::getClientRect(void) const
	{
		RECT clientRect;
		if(!::GetClientRect(m_hwnd, &clientRect))
			T3D_WINEXCEPT(::GetLastError());

		RECT adjustRect = clientRect;
		if(!::AdjustWindowRectEx(&adjustRect, getWindowStyle(), NULL != ::GetMenu(m_hwnd), getWindowExtansionStyle()))
			T3D_WINEXCEPT(::GetLastError());

		RECT windowRect = getWindowRect();
		if(!::OffsetRect(&clientRect, windowRect.left - adjustRect.left, windowRect.top - adjustRect.top))
			T3D_WINEXCEPT(::GetLastError());
		return clientRect;
	}

	void WindowBase::setClientRect(const RECT & rect)
	{
		RECT adjustRect = rect;
		if(!::AdjustWindowRectEx(&adjustRect, getWindowStyle(), NULL != ::GetMenu(m_hwnd), getWindowExtansionStyle()))
			T3D_WINEXCEPT(::GetLastError());

		setWindowRect(adjustRect);
	}

	void WindowBase::centerWindow(void)
	{
		RECT desktopRect;
		if(!::GetWindowRect(::GetDesktopWindow(), &desktopRect))
			T3D_WINEXCEPT(::GetLastError());

		RECT windowRect = getWindowRect();
		int x = ((desktopRect.right - desktopRect.left) - (windowRect.right - windowRect.left)) / 2;
		int y = ((desktopRect.bottom - desktopRect.top) - (windowRect.bottom - windowRect.top)) / 2;

		if(!::SetWindowPos(m_hwnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE))
			T3D_WINEXCEPT(::GetLastError());
	}

	BOOL Window::isRegisteredWindowClass(const std::basic_string<charT> winClass, HINSTANCE moduleHandle)
	{
		WNDCLASSEX wcex;
		return ::GetClassInfoEx(moduleHandle, winClass.c_str(), &wcex);
	}

	void Window::registerWindowClass(const std::basic_string<charT> winClass, HINSTANCE moduleHandle)
	{
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(wcex);
		wcex.style = CS_CLASSDC;
		wcex.lpfnWndProc = Application::onProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = moduleHandle;
		wcex.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
		wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW),
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = winClass.c_str();
		wcex.hIconSm = ::LoadIcon(NULL, IDI_APPLICATION);

		if(NULL == ::RegisterClassEx(&wcex))
		{
			T3D_WINEXCEPT(::GetLastError());
		}
	}

	Window::Window(const std::basic_string<charT> winClass, const std::basic_string<charT> winTitle, const Application * app)
	{
		if(NULL == (m_hwnd = ::CreateWindowEx(0, winClass.c_str(), winTitle.c_str(),
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, app->getHandle(), NULL)))
		{
			T3D_WINEXCEPT(::GetLastError());
		}
	}

	Window::~Window(void)
	{
		//assert(!::IsWindow(m_hwnd));
	}

	void Window::addMessageListener(MessageListener * listener)
	{
		assert(NULL != listener);
		m_msgListenerList.push_back(listener);
	}

	HWND Window::getHandle(void) const
	{
		return m_hwnd;
	}

	LRESULT Window::onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		assert(hwnd == m_hwnd);

		MessageListenerList::iterator iter = m_msgListenerList.begin();

		for(; iter != m_msgListenerList.end(); iter++)
		{
			LRESULT lres;
			if((*iter)->notifyMessage(this, message, wparam, lparam, lres))
			{
				return lres;
			}
		}

		return ::DefWindowProc(hwnd, message, wparam, lparam);
	}

	Application * Application::s_ptr = NULL;

	HINSTANCE Application::getModuleHandle(const std::basic_string<charT> moduleName /*= _T("")*/)
	{
		HINSTANCE hinst;
		if(moduleName.empty())
			hinst = ::GetModuleHandle(NULL);
		else
			hinst = ::GetModuleHandle(moduleName.c_str());

		if(!hinst)
			T3D_WINEXCEPT(::GetLastError());

		return hinst;
	}

	LRESULT CALLBACK Application::onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		WindowPtrMap & wndMap = getSingleton().m_wndMap;

		WindowPtrMap::iterator iter = wndMap.find(hwnd);

		if(iter != wndMap.end())
		{
			LRESULT res = iter->second->onProc(hwnd, message, wparam, lparam);

			if(WM_NCDESTROY == message)
			{
				wndMap.erase(iter);

				if(wndMap.empty())
				{
					::PostQuitMessage(0);
				}
			}

			return res;
		}

		return ::DefWindowProc(hwnd, message, wparam, lparam);
	}

	Application::Application(HINSTANCE hinst)
		: m_hinst(hinst)
	{
		assert(NULL == s_ptr);
		s_ptr = this;

		assert(NULL != m_hinst);
	}

	Application::~Application(void)
	{
		while(!m_wndMap.empty())
		{
			WindowPtrMap::iterator iter = m_wndMap.begin();

			assert(m_wndMap.end() != iter);

			WindowPtr win = iter->second;

			m_wndMap.erase(iter); // ??? if not do this will lead unknown error at following ::MessageBox(...)

			::DestroyWindow(win->getHandle());
		}

		s_ptr = NULL;
	}

	Window * Application::createWindow(const std::basic_string<charT> winClass, const std::basic_string<charT> winTitle)
	{
		if(!Window::isRegisteredWindowClass(winClass, getHandle()))
		{
			Window::registerWindowClass(winClass, getHandle());
		}

		WindowPtr ptr(new Window(winClass, winTitle, this));

		assert(m_wndMap.end() == m_wndMap.find(ptr->getHandle()));

		m_wndMap[ptr->getHandle()] = ptr;

		return ptr.get();
	}

	HINSTANCE Application::getHandle(void) const
	{
		return m_hinst;
	}

	void Application::addIdleListener(IdleListener * listener)
	{
		assert(NULL != listener);
		m_idleListenerList.push_back(listener);
	}

	int Application::run(void)
	{
		MSG msg;
		memset(&msg, 0, sizeof(msg));

		while(WM_QUIT != msg.message)
		{
			if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				if(!m_idleListenerList.empty())
				{
					IdleListenerList::iterator iter = m_idleListenerList.begin();
					for(; iter != m_idleListenerList.end(); iter++)
					{
						(*iter)->nodifyIdle();
					}
				}
				else
				{
					::WaitMessage();
				}
			}
		}

		return (int)msg.wParam;
	}
}
