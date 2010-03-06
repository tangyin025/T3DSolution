
#pragma once

class MyConfig : public my::Game::CONFIG_DESC
{
public:
	enum ASPECT_RATIO
	{
		ASPECT_RATIO_STRETCHED = 0,
		ASPECT_RATIO_STANDARD,
		ASPECT_RATIO_WIDESCREEN
	};

	ASPECT_RATIO aspect_ratio_mode;

public:
	MyConfig(DWORD width, DWORD height, my::Game::SCREEN_MODE smode, ASPECT_RATIO _aspect_ratio_mode)
		: my::Game::CONFIG_DESC(width, height, smode)
		, aspect_ratio_mode(_aspect_ratio_mode)
	{
	}

public:
	static MyConfig LoadFromFile(const std::basic_string<charT> & fileName);

	static void SaveToFile(const MyConfig & config, const std::basic_string<charT> & fileName);
};
