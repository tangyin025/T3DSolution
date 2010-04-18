
#pragma once

class MyGame : public my::Game
{
public:
	MyGame(void) throw();

	~MyGame(void);

public:
	virtual bool onInit(const CONFIG_DESC & cfg);

	virtual bool onFrame(void);

	virtual void onShutdown(void);

protected:
	my::FPSManagerPtr m_fpsMgr;

	my::TimerPtr m_timer;

	my::GridPtr m_grid;

	my::EulerCameraPtr m_eulerCam;
};
