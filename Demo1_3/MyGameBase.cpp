
#include "StdAfx.h"
#include "MyGameBase.h"

MyWindow::MyWindow(HWND hwnd)
	: GameWnd(hwnd)
{
}

MyWindow::~MyWindow(void)
{
}

LRESULT MyWindow::onProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch(message)
	{
	case WM_CLOSE:
		if(MyGameBase::getSingleton().getCurrentStateName() == MyLoadState::s_name)
		{
			// for load state, there must be waiting for another thread to prepare for quiting
			MyLoadStatePtr loadState = MyGameBase::getSingleton().getCurrentState<MyLoadState>();
			if(!loadState->getExitFlag())
			{
				loadState->setExitFlag();
			}
			return 0;
		}
		break;
	}
	return GameWnd::onProc(hwnd, message, wparam, lparam);
}

MyGameBase::MyGameBase(void)
{
}

MyGameBase::~MyGameBase(void)
{
}

my::Window * MyGameBase::newWindow(HWND hwnd)
{
	return new MyWindow(hwnd);
}

bool MyGameBase::onInit(const my::Config & cfg)
{
	// predefine config values
	const int cfgWidth = m_rc->getSurfaceWidth();
	const int cfgHeight = m_rc->getSurfaceHeight();

	// calculate aspect ratio
	real aspect_ratio;
	switch(cfg.getInt(_T("aspectratio")))
	{
	default:
		_ASSERT(ASPECT_RATIO_STRETCHED == cfg.getInt(_T("aspectratio")));
		aspect_ratio = (real)cfgWidth / cfgHeight;
		break;

	case ASPECT_RATIO_STANDARD:
		aspect_ratio = (real)4 / 3;
		break;

	case ASPECT_RATIO_WIDESCREEN:
		aspect_ratio = (real)16 / 9;
		break;
	}

	// adjust clipper region by aspect ratio
	LONG lWidth, lHeight;
	CRect clipper;
	if(aspect_ratio < (real)cfgWidth / (real)cfgHeight)
	{
		lHeight = cfgHeight;
		lWidth = (LONG)(lHeight * aspect_ratio + .5f);
		clipper.left = (cfgWidth - lWidth) / 2;
		clipper.top = 0;
		clipper.right = clipper.left + lWidth;
		clipper.bottom = clipper.top + lHeight;
	}
	else
	{
		lWidth = cfgWidth;
		lHeight = (LONG)(lWidth / aspect_ratio + .5f);
		clipper.left = 0;
		clipper.top = (cfgHeight - lHeight) / 2;
		clipper.right = clipper.left + lWidth;
		clipper.bottom = clipper.top + lHeight;
	}

	// validate the clipper region
	_ASSERT(clipper.left	>= m_backSurfaceRect.left);
	_ASSERT(clipper.top		>= m_backSurfaceRect.top);
	_ASSERT(clipper.right	<= m_backSurfaceRect.right);
	_ASSERT(clipper.bottom	<= m_backSurfaceRect.bottom);

	// update clipper region to render context,
	// and later the camera's viewport & projection will be recalculated by this clipper rect
	m_rc->setClipperRect(clipper);

	// create and add load state
	addState(MyLoadState::s_name, MyLoadStatePtr(new MyLoadState(this)));

	// create and add game state
	addState(MyGameState::s_name, MyGameStatePtr(new MyGameState(this)));

	// set current state to load state
	setCurrentState(MyLoadState::s_name);

	// call default parent onInit
	return my::Game::onInit(cfg);
}

bool MyGameBase::onFrame(void)
{
	// get current state and do frame
	if(!getCurrentState<MyFrameState>()->doFrame())
	{
		return false;
	}

	// call default parent onFrame
	return my::Game::onFrame();
}

void MyGameBase::onShutdown(void)
{
	// get current state and do leaveState
	getCurrentState<MyState>()->leaveState();
}

MyFrameState::MyFrameState(void)
{
}

MyFrameState::~MyFrameState(void)
{
}

const std::basic_string<charT> MyLoadState::s_name(_T("MyLoadState"));

MyLoadState::MyLoadState(MyGameBase * game)
	: m_game(game)
	, m_exitFlag(false)
{
}

MyLoadState::~MyLoadState(void)
{
}

void MyLoadState::enterState(void)
{
	// initial progress box
	int barWidth = 250;
	int barHeight = 60;
	CRect clipper = m_game->m_rc->getClipperRect();
	int x = clipper.left + (clipper.Width() - barWidth) / 2;
	int y = clipper.top + (clipper.Height() - barHeight) / 2;
	m_progressBox = MyUIProgressBarBoxPtr(new MyUIProgressBarBox(CRect(CPoint(x, y), CSize(barWidth, barHeight))));

	// begin work thread here
	CreateThread();
	ResumeThread();
}

void MyLoadState::leaveState(void)
{
	_ASSERT(WaitForThreadStopped(0));
}

bool MyLoadState::doFrame(void)
{
	// exit application by return false with user input 'escape'
	if(m_game->m_keyboard->isKeyDown(DIK_ESCAPE))
	{
		// DO NOT USE TerminateThread HERE!
		if(!getExitFlag())
		{
			setExitFlag();
		}
	}

	// exit application by return false with user input 'escape'
	if(WaitForThreadStopped(0))
	{
		if(!getExitFlag())
		{
			m_game->setCurrentState(MyGameState::s_name);
			return true;
		}
		else
		{
			return false;
		}
	}

	// define render context point
	t3d::RenderContext * rc = m_game->m_rc.get();

	// clear back surface with gray color
	rc->fillSurface(rc->getClipperRect(), my::Color::BLACK);

	// draw progress bar
	m_progressBox->setPercent(getPercent());
	m_progressBox->draw(rc);

	// general information output
	std::basic_string<charT> strTmp;
	if(!getExitFlag())
	{
		strTmp = _T("Loading ...");
	}
	else
	{
		strTmp = _T("Exiting ...");
	}
	HDC hdc = m_game->m_backSurface->getDC();
	int bkMode = ::SetBkMode(hdc, TRANSPARENT);
	COLORREF textColor = ::SetTextColor(hdc, RGB(255, 255, 255));
	::DrawText(hdc, strTmp.c_str(), strTmp.length(), &m_progressBox->m_titleRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	::SetTextColor(hdc, textColor);
	::SetBkMode(hdc, bkMode);
	m_game->m_backSurface->releaseDC(hdc);

	// sleep some time to set aside cpu resource to back thread
	::Sleep(33);

	return true;
}

DWORD MyLoadState::onProc(void)
{
	// the thread call back process
	if(!m_game->doInit() && !getExitFlag())
	{
		setExitFlag(true);
	}

	return 0;
}

const std::basic_string<charT> MyGameState::s_name(_T("MyGameState"));

MyGameState::MyGameState(MyGameBase * game)
	: m_game(game)
{
}

MyGameState::~MyGameState(void)
{
}

bool MyGameState::doFrame(void)
{
	// render a really game frame
	return m_game->doFrame();
}
