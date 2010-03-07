
#include "stdafx.h"
#include "MyConfig.h"
#include "MyDialog.h"

int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	// check memory leak
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));

	// common control supported
	INITCOMMONCONTROLSEX InitCtrls = {sizeof(InitCtrls)};
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	// parser the application file path to obtain the ini file path
	my::Game game;
	std::basic_string<charT> strConfigPath = game.getModuleFileName();
	std::basic_string<charT>::size_type rpos = strConfigPath.rfind(_T('.'));
	std::basic_string<charT>::size_type lpos = strConfigPath.rfind(_T('\\'));
	std::basic_string<charT> strCurrentDir;
	strCurrentDir.resize(MAX_PATH);
	strCurrentDir.resize(::GetCurrentDirectory(strCurrentDir.size(), &strCurrentDir[0]));
	if(lpos >= rpos || 0 == strCurrentDir.size() || MAX_PATH == strCurrentDir.size())
	{
		::MessageBox(NULL, _T("The current directory or application's path is invalid."), _T("Error"), MB_OK);
		return 0;
	}
	strConfigPath = strCurrentDir + strConfigPath.substr(lpos, rpos - lpos) + _T(".ini");

	// show configuration dialog
	MyConfig cfg(MyConfig::LoadFromFile(strConfigPath));
	MyDialog dlg(cfg, game.getHandle());
	if(IDOK == dlg.doModel())
	{
		if(BST_CHECKED == dlg.m_save_configuration)
		{
			MyConfig::SaveToFile(dlg.m_cfg, strConfigPath);
		}
	}
	return 0;
}
