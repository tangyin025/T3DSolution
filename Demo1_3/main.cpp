
#include "stdafx.h"
#include "MyDialog.h"
#include "MyGameEx.h"

int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	// check memory leak
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));

	// common control supported
	INITCOMMONCONTROLSEX InitCtrls = {sizeof(InitCtrls)};
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	// parser the application path and obtain the ini file path
	std::basic_string<charT> strConfigPath = MyGame::getModuleFileName();
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

	// initialize configuration
	MyDialog dlg;
	dlg.m_cfg.SetConfigPath(strConfigPath);
	dlg.m_cfg.setAppName(_T("config"));
	dlg.m_cfg.addInt(_T("width"), 800);
	dlg.m_cfg.addInt(_T("height"), 600);
	dlg.m_cfg.addInt(_T("screenmode"), my::Game::SCREEN_MODE_WINDOWED);
	dlg.m_cfg.addInt(_T("aspectratio"), MyGame::ASPECT_RATIO_STRETCHED);
	dlg.m_cfg.Load();

	// initialize searching path
	my::ResourceMgr::getSingleton().addDir(_T("Media"));
	my::ResourceMgr::getSingleton().addDir(_T("..\\Demo1_3\\Media"));

	// show configuration dialog
	int ret = 0;
	if(IDOK == dlg.DoModal())
	{
		// run the instance
		if(0 == (ret = MyGame().run(dlg.m_cfg)))
		{
			if(BST_CHECKED == dlg.m_save_configuration)
			{
				// save configuration to user profile
				dlg.m_cfg.Save();
			}
		}
	}
	return ret;
}
