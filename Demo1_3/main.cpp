
#include "stdafx.h"
#include "MyConfig.h"
#include "MyDialog.h"
#include "MyGame.h"

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
		my::ResourceMgr::getSingleton().addDir(_T("..\\..\\Common\\medias"));
		my::ResourceMgr::getSingleton().addDir(_T("."));

		// show configuration dialog
		int ret = 0;
		MyConfig cfg(MyConfig::LoadFromFile(strConfigPath));
		MyDialog dlg(cfg, game.getHandle());
		if(IDOK == dlg.doModel())
		{
			// run the instance
			if(0 == (ret = game.run(dlg.m_cfg)))
			{
				if(BST_CHECKED == dlg.m_save_configuration)
				{
					MyConfig::SaveToFile(dlg.m_cfg, strConfigPath);
				}
			}
		}
		return ret;
	}
	catch(t3d::Exception & e)
	{
		// report error message
		::MessageBox(NULL != game.m_pwnd ? game.m_pwnd->getHandle() : NULL, e.getFullDesc().c_str(), _T("Exception"), MB_OK);
		exit(1);
	}
}
