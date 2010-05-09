
#pragma once

#include "MyState.h"
#include "MyUI.h"

class MyWindow
	: public my::GameWnd
{
public:
	MyWindow(HWND hwnd);

	~MyWindow(void);

public:
	LRESULT onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
};

class MyGame
	: public my::Game
	, public MyStateChart
{
	friend class MyLoadState;

	friend class MyGameState;

public:
	static MyGame * getSingletonPtr(void)
	{
		return dynamic_cast<MyGame *>(my::Game::getSingletonPtr());
	}

	static MyGame & getSingleton(void)
	{
		return * getSingletonPtr();
	}

public:
	MyGame(void) throw();

	~MyGame(void);

public:
	my::Window * newWindow(HWND hwnd);

	bool onInit(const CONFIG_DESC & cfg);

	bool onFrame(void);

	void onShutdown(void);
};

class MyStateBase
	: public MyState
{
public:
	MyStateBase(void);

	~MyStateBase(void);

public:
	virtual bool doFrame(void) = 0;
};

typedef boost::shared_ptr<MyStateBase> MyStateBasePtr;

class MyLoadState
	: public MyStateBase
	, public my::Thread
{
protected:
	MyGame * m_game;

	MyUIProgressBarBoxPtr m_progressBox;

	bool m_exitFlag;

public:
	static const std::basic_string<charT> s_name;

public:
	void setExitFlag(bool exitFlag = true)
	{
		m_exitFlag = exitFlag;
	}

	bool getExitFlag(void)
	{
		return m_exitFlag;
	}

public:
	MyLoadState(MyGame * game);

	~MyLoadState(void);

	void enterState(void);

	void leaveState(void);

	bool doFrame(void);

	DWORD onProc(void);
};

typedef boost::shared_ptr<MyLoadState> MyLoadStatePtr;

class MyGameState
	: public MyStateBase
{
	friend MyLoadState;

protected:
	MyGame * m_game;

	my::FPSManagerPtr m_fpsMgr;

	my::TimerPtr m_timer;

	my::GridPtr m_grid;

	my::EulerCameraPtr m_eulerCam;

public:
	static const std::basic_string<charT> s_name;

public:
	MyGameState(MyGame * game);

	~MyGameState(void);

	void enterState(void);

	void leaveState(void);

	bool doFrame(void);
};

typedef boost::shared_ptr<MyGameState> MyGameStatePtr;
