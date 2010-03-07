
#include "StdAfx.h"
#include "MyConfig.h"

MyConfig MyConfig::LoadFromFile(const std::basic_string<charT> & fileName)
{
	return MyConfig(
		::GetPrivateProfileInt(_T("config"), _T("width"), 800, fileName.c_str()),
		::GetPrivateProfileInt(_T("config"), _T("height"), 600, fileName.c_str()),
		(my::Game::SCREEN_MODE)::GetPrivateProfileInt(_T("config"), _T("screenmode"), my::Game::SCREEN_MODE_WINDOWED, fileName.c_str()),
		(MyConfig::ASPECT_RATIO)::GetPrivateProfileInt(_T("config"), _T("aspectratio"), MyConfig::ASPECT_RATIO_STRETCHED, fileName.c_str()));
}

void MyConfig::SaveToFile(const MyConfig & config, const std::basic_string<charT> & fileName)
{
	::WritePrivateProfileString(_T("config"), _T("width"), str_printf(_T("%d"), config.width).c_str(), fileName.c_str());
	::WritePrivateProfileString(_T("config"), _T("height"), str_printf(_T("%d"), config.height).c_str(), fileName.c_str());
	::WritePrivateProfileString(_T("config"), _T("screenmode"), str_printf(_T("%d"), config.smode).c_str(), fileName.c_str());
	::WritePrivateProfileString(_T("config"), _T("aspectratio"), str_printf(_T("%d"), config.aspect_ratio_mode).c_str(), fileName.c_str());
}
