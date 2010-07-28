
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

	// the global instance
	MyGame game;

	try
	{
		// parser the application path and obtain the ini file path
		std::basic_string<charT> strConfigPath = game.getModuleFileName();
		std::basic_string<charT>::size_type rpos = strConfigPath.rfind(_T('.'));
		std::basic_string<charT>::size_type lpos = strConfigPath.rfind(_T('\\'));
		std::basic_string<charT> strCurrentDir;
		strCurrentDir.resize(MAX_PATH);
		strCurrentDir.resize(::GetCurrentDirectory(strCurrentDir.size(), &strCurrentDir[0]));
		if(lpos >= rpos || 0 == strCurrentDir.size() || MAX_PATH == strCurrentDir.size())
		{
			T3D_CUSEXCEPT(_T("The current directory or application's path is invalid."));
		}
		strConfigPath = strCurrentDir + strConfigPath.substr(lpos, rpos - lpos) + _T(".ini");

		// initialize searching path
		my::ResourceMgr::getSingleton().addDir(_T("."));
		my::ResourceMgr::getSingleton().addDir(_T("..\\..\\Common\\medias\\demo1_3"));

		// initialize configuration
		my::Config cfg(_T("config"));
		cfg.addInt(_T("width"), 800);
		cfg.addInt(_T("height"), 600);
		cfg.addInt(_T("screenmode"), my::Game::SCREEN_MODE_WINDOWED);
		cfg.addInt(_T("aspectratio"), MyGame::ASPECT_RATIO_STRETCHED);
		cfg.load(strConfigPath.c_str());

		// show configuration dialog
		int ret = 0;
		MyDialog dlg(cfg);
		if(IDOK == dlg.DoModal())
		{
			// run the instance
			if(0 == (ret = game.run(dlg.m_cfg)))
			{
				if(BST_CHECKED == dlg.m_save_configuration)
				{
					// save configuration to user profile
					cfg.save(strConfigPath.c_str());
				}
			}
		}
		return ret;
	}
	catch(t3d::Exception & e)
	{
		// report error message
		::MessageBox(NULL != game.m_wnd ? game.m_wnd->m_hWnd : NULL, e.getFullDesc().c_str(), _T("Exception"), MB_OK);
		exit(1);
	}
}
