
#pragma once

#include "MyState.h"

class MyGame
	: public my::Game
	, public MyStateChart
{
	friend class MyLoadState;

	friend class MyGameState;

protected:
	my::FPSManagerPtr m_fpsMgr;

	my::TimerPtr m_timer;

	my::GridPtr m_grid;

	my::EulerCameraPtr m_eulerCam;

public:
	MyGame(void) throw();

	~MyGame(void);

public:
	virtual bool onInit(const CONFIG_DESC & cfg);

	virtual bool onFrame(void);

	virtual void onShutdown(void);
};

class MyStateBase
	: public MyState
{
public:
	MyStateBase(void);

	~MyStateBase(void);

public:
	virtual bool onFrame(void) = 0;
};

class MyLoadState
	: public MyStateBase
	, public my::Thread
{
protected:
	MyGame * m_game;

public:
	static const std::basic_string<charT> s_name;

public:
	MyLoadState(MyGame * game);

	~MyLoadState(void);

	void enterState(void);

	void leaveState(void);

	bool onFrame(void);

	DWORD onProc(void);
};

typedef boost::shared_ptr<MyLoadState> MyLoadStatePtr;

class MyGameState
	: public MyStateBase
{
protected:
	MyGame * m_game;

public:
	static const std::basic_string<charT> s_name;

public:
	MyGameState(MyGame * game);

	~MyGameState(void);

	void enterState(void);

	void leaveState(void);

	bool onFrame(void);
};

typedef boost::shared_ptr<MyGameState> MyGameStatePtr;
