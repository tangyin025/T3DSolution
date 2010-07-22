
#pragma once

#include "MyState.h"
#include "MyUI.h"
#include <myPhysics.h>

class MyWindow
	: public my::GameWnd
{
public:
	MyWindow(HWND hwnd);

	~MyWindow(void);

public:
	LRESULT onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
};

class MyGameEx
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
	static MyGameEx * getSingletonPtr(void)
	{
		return dynamic_cast<MyGameEx *>(my::Game::getSingletonPtr());
	}

	static MyGameEx & getSingleton(void)
	{
		return * getSingletonPtr();
	}

public:
	MyGameEx(void) throw();

	~MyGameEx(void);

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
public:
	static const std::basic_string<charT> s_name;

protected:
	MyGameEx * m_game;

	MyUIProgressBarBoxPtr m_progressBox;

	my::CriticalSection m_progressBoxLock;

	bool m_exitFlag;

	my::CriticalSection m_exitFlagLock;

	// //////////////////////////////////////////////////////////////////////////////////////////

	my::Mp3Ptr m_mp3;

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

	void setPercent(real percent)
	{
		my::CriticalSectionLock lock(m_progressBoxLock);
		m_progressBox->setPercent(percent);
	}

	real getPercent(void)
	{
		my::CriticalSectionLock lock(m_progressBoxLock);
		return m_progressBox->getPercent();
	}

public:
	MyLoadState(MyGameEx * game);

	~MyLoadState(void);

	void enterState(void);

	void leaveState(void);

	bool doFrame(void);

	DWORD onProc(void);
};

typedef std::tr1::shared_ptr<MyLoadState> MyLoadStatePtr;

class MyGameState
	: public MyFrameState
	, public my::World
{
	friend class MyLoadState;

public:
	static const std::basic_string<charT> s_name;

protected:
	MyGameEx * m_game;

	my::FPSManagerPtr m_fpsMgr;

	my::TimerPtr m_timer;

	my::GridPtr m_grid;

	my::EulerCameraPtr m_eulerCam;

	// //////////////////////////////////////////////////////////////////////////////////////////

	my::IndexObjectPtr m_obj;

	my::ObjectPtr m_lstObj;

	my::ImagePtr m_objImg;

	my::WavPtr m_wav;

	my::Mp3Ptr m_mp3;

	t3d::DS3DBufferPtr m_ds3dbuffer;

	t3d::DS3DListenerPtr m_ds3dListener;

	// //////////////////////////////////////////////////////////////////////////////////////////

public:
	MyGameState(MyGameEx * game);

	~MyGameState(void);

	void enterState(void);

	void leaveState(void);

	unsigned generateContacts(my::Contact * contacts, unsigned limits);

	bool doFrame(void);
};

typedef std::tr1::shared_ptr<MyGameState> MyGameStatePtr;
