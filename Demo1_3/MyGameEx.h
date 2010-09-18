
#pragma once

#include "MyState.h"
#include "MyUI.h"
#include "MyProgress.h"
#include <myPhysics.h>
#include "t3dlib8.h"

class MyWindow
	: public my::GameWnd
{
public:
	BEGIN_MSG_MAP(MyWindow)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	MESSAGE_HANDLER(WM_USER + 0, OnUser0)
	CHAIN_MSG_MAP(my::GameWnd)
	END_MSG_MAP()

	LRESULT OnClose(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);

	LRESULT OnUser0(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
};

class MyGame
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
	my::WindowPtr newWindow(void);

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

typedef boost::shared_ptr<MyFrameState> MyStateBasePtr;

class MyLoadState
	: public MyFrameState
	, public MyProgress
	, public my::Thread
{
public:
	static const std::basic_string<charT> s_name;

protected:
	MyUIProgressBarBoxPtr m_progressBox;

	my::CriticalSection m_progressBoxLock;

	bool m_exitFlag;

	my::CriticalSection m_exitFlagLock;

	// //////////////////////////////////////////////////////////////////////////////////////////

	// //////////////////////////////////////////////////////////////////////////////////////////

public:
	void setExitFlag(bool exitFlag = true)
	{
		my::CriticalSectionLock lock(m_exitFlagLock);
		m_exitFlag = exitFlag;
	}

	bool getExitFlag(void)
	{
		my::CriticalSectionLock lock(m_exitFlagLock);
		return m_exitFlag;
	}

public:
	MyLoadState(void);

	~MyLoadState(void);

	void enterState(void);

	void leaveState(void);

	bool doFrame(void);

	DWORD onProc(void);
};

typedef boost::shared_ptr<MyLoadState> MyLoadStatePtr;

class MyGameState
	: public MyFrameState
	, public my::World
{
	friend class MyLoadState;

public:
	static const std::basic_string<charT> s_name;

protected:

	// //////////////////////////////////////////////////////////////////////////////////////////

	my::FPSManagerPtr m_fpsMgr;

	my::TimerPtr m_timer;

	my::GridPtr m_grid;

	my::EulerCameraPtr m_eulerCam;

	// //////////////////////////////////////////////////////////////////////////////////////////

public:
	MyGameState(void);

	~MyGameState(void);

	void enterState(void);

	void leaveState(void);

	unsigned generateContacts(my::Contact * contacts, unsigned limits);

	bool doFrame(void);
};

typedef boost::shared_ptr<MyGameState> MyGameStatePtr;
