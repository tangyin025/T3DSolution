
#pragma once

#include "MyResource.h"
#include <atlwin.h>
#include "resource.h"

class MyConfig : public my::Config
{
protected:
	std::basic_string<t3d::charT> m_cfgPath;

public:
	void SetConfigPath(const std::basic_string<t3d::charT> & path)
	{
		m_cfgPath = path;
	}

	const std::basic_string<t3d::charT> & GetConfigPath(void) const
	{
		return m_cfgPath;
	}

public:
	MyConfig(void);

	void Load(void);

	void Save(void);
};

class MyDialog
	: public CDialogImpl<MyDialog, CWindow>
{
public:
	enum { IDD = IDD_DIALOG1 };

public:
	MyConfig m_cfg;

	int m_save_configuration;

	my::ImagePtr m_image;

public:
	MyDialog(void);

	BEGIN_MSG_MAP(MyDialog)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDC_COMBO1, CBN_SELCHANGE, OnCombo1SelChange)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnCombo1SelChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};
