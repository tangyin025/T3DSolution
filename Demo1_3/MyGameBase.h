
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

class MyGameBase
	: public my::Game
	, public MyStateChart
{
	friend class MyLoadState;

	friend class MyGameState;

public:
	enum ASPECT_RATIO
	{
		ASPECT_RATIO_STRETCHED = 0,
		ASPECT_RATIO_STANDARD,
		ASPECT_RATIO_WIDESCREEN
	};

public:
	static MyGameBase * getSingletonPtr(void)
	{
		return dynamic_cast<MyGameBase *>(my::Game::getSingletonPtr());
	}

	static MyGameBase & getSingleton(void)
	{
		return * getSingletonPtr();
	}

public:
	virtual bool doInit(void) = 0;

	virtual bool doFrame(void) = 0;

public:
	MyGameBase(void) throw();

	~MyGameBase(void);

public:
	my::Window * newWindow(HWND hwnd);

	bool onInit(const my::Config & cfg);

	bool onFrame(void);

	void onShutdown(void);
};

class MyFrameState
	: public MyState
{
public:
	MyFrameState(void);

	~MyFrameState(void);

public:
	virtual bool doFrame(void) = 0;
};

typedef std::tr1::shared_ptr<MyFrameState> MyStateBasePtr;

class MyLoadState
	: public MyFrameState
	, public my::Thread
{
protected:
	MyGameBase * m_game;

	MyUIProgressBarBoxPtr m_progressBox;

	my::CriticalSection m_progressBoxLock;

	bool m_exitFlag;

	my::CriticalSection m_exitFlagLock;

public:
	static const std::basic_string<charT> s_name;

public:
	void setExitFlag(bool exitFlag = true)
	{
		m_exitFlagLock.enter();
		m_exitFlag = exitFlag;
		m_exitFlagLock.leave();
	}

	bool getExitFlag(void)
	{
		m_exitFlagLock.enter();
		bool flag = m_exitFlag;
		m_exitFlagLock.leave();
		return flag;
	}

	void setPercent(real percent)
	{
		m_progressBoxLock.enter();
		m_progressBox->setPercent(percent);
		m_progressBoxLock.leave();
	}

	real getPercent(void)
	{
		m_progressBoxLock.enter();
		real percent = m_progressBox->getPercent();
		m_progressBoxLock.leave();
		return percent;
	}

public:
	MyLoadState(MyGameBase * game);

	~MyLoadState(void);

	void enterState(void);

	void leaveState(void);

	bool doFrame(void);

	DWORD onProc(void);
};

typedef std::tr1::shared_ptr<MyLoadState> MyLoadStatePtr;

class MyGameState
	: public MyFrameState
{
protected:
	MyGameBase * m_game;

public:
	static const std::basic_string<charT> s_name;

public:
	MyGameState(MyGameBase * game);

	~MyGameState(void);

	bool doFrame(void);
};

typedef std::tr1::shared_ptr<MyGameState> MyGameStatePtr;
