
#include "stdafx.h"
#include "MyConfig.h"
#include "MyDialog.h"
#include "MyGameBase.h"

class MyGame : public MyGameBase
{
protected:
	my::FPSManagerPtr m_fpsMgr;

	my::TimerPtr m_timer;

	my::GridPtr m_grid;

	my::EulerCameraPtr m_eulerCam;

public:
	bool doInit(void)
	{
		// initialize fps manager
		m_fpsMgr = my::FPSManagerPtr(new my::FPSManager());
		m_fpsMgr->start();

		// initialize timer
		m_timer = my::TimerPtr(new my::Timer());
		m_timer->start();

		// initialize grid
		m_grid = my::GridPtr(new my::Grid());

		// initialize euler camera
		m_eulerCam = my::EulerCameraPtr(new my::EulerCamera());
		m_eulerCam->setDefaultPosition(my::Vec4<real>(-50, 50, -50));
		m_eulerCam->setDefaultRotation(my::Vec4<real>(DEG_TO_RAD(45), DEG_TO_RAD(45), DEG_TO_RAD(0)));
		m_eulerCam->reset();

		// simulate times occupied process
		MyLoadStatePtr loadState = getCurrentState<MyLoadState>();
		int count = 100;
		for(int i = 1; i <= count; i += 1)
		{
			// if user specified to exit application, stop any job
			if(loadState->getExitFlag())
			{
				return false;
			}

			// update progress percent
			loadState->setPercent((real)i / count);

			// sleep some time as if doing the job
			::Sleep(30);
		}

		return true;
	}

	bool doFrame(void)
	{
		// exit application by return false with user input 'escape'
		if(m_keyboard->isKeyDown(DIK_ESCAPE))
		{
			return false;
		}

		// fps manager, witch calculated fps by incremented frame
		// the precision of this fps manager witch depend on sampling second was low, but its enough
		m_fpsMgr->addFrame();

		// the high precision timer, witch calculate time interval between last frame by cpu count
		// to avoid to too many time interval that crash the physical engine, set the max interval as 30 / 1 second
		const real elapsedTime = std::min((real)m_timer->getElapsedTime(), (real)0.033);

		//// here i created the clipper region smaller than the window, only used to test the clipper bug
		//// because of the software simulating, the algorithm of cutting polygon is implemented by software,
		//// so the unstrong algorithm will lead edge overflow, and even crash the application
		//// reducing the clipper region will somehow avoid this phenomenon
		//CRect clipper(m_rback);
		//clipper.DeflateRect(10, 10);
		//m_rc->setClipperRect(clipper);

		// clear back surface with gray color
		m_rc->fillSurface(m_rc->getClipperRect(), my::Color(0.8f, 0.8f, 0.8f));

		// clear zbuffer with infinite distance
		m_rc->fillZbuffer(m_rc->getClipperRect(), 0);

		// set render context camera
		m_rc->setViewport(m_rc->getClipperRect());
		m_rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), m_rc->getClipperRect().Width(), m_rc->getClipperRect().Height()));
		m_rc->setCameraNearZ(1);
		m_rc->setCameraFarZ(10000);

		// update euler cameras position and orientation by user input
		m_eulerCam->update(m_keyboard.get(), m_mouse.get(), elapsedTime);
		m_rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEuler(m_eulerCam->getPosition(), m_eulerCam->getRotation()));

		// set render context lights
		my::Vec4<real> l_pos(-30, 30, -30);
		l_pos *= t3d::mat3RotZXY(m_eulerCam->getRotation()) * t3d::mat3Mov(m_eulerCam->getPosition());
		m_rc->clearLightList();
		m_rc->pushLightAmbient(my::Vec4<real>(0.2f, 0.2f, 0.2f));
		m_rc->pushLightPoint(my::Vec4<real>(1, 1, 1), l_pos); //my::Vec4<real>(100, 100, -100));

		// set render context material
		m_rc->setAmbient(my::Color::WHITE);
		m_rc->setDiffuse(my::Color::WHITE);

		// draw default grid, with use to test distance of the scene
		m_grid->drawZBufferRW(m_rc.get());

		// general information output
		std::basic_string<charT> strTmp;
		HDC hdc = m_backSurface->getDC();

		int textx = m_rc->getClipperRect().left + 10;
		int texty = m_rc->getClipperRect().top + 10;

		strTmp = str_printf(_T("fps: %.1f"), m_fpsMgr->getFPS());
		::TextOut(hdc, textx, texty, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("fps: %.1f"), 1 / elapsedTime);
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		t3d::Vec4<real> camPos = t3d::CameraContext::calculateCameraPosition(m_rc->getCameraMatrix());
		strTmp = str_printf(_T("cam.pos: %f, %f, %f"),
			camPos.x, camPos.y, camPos.z);
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("cam.rot: %f, %f, %f"),
			RAD_TO_DEG(m_eulerCam->getRotation().x), RAD_TO_DEG(m_eulerCam->getRotation().y), RAD_TO_DEG(m_eulerCam->getRotation().z));
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		m_backSurface->releaseDC(hdc);

		return true;
	}
};

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
		my::ResourceMgr::getSingleton().addDir(_T("."));
		my::ResourceMgr::getSingleton().addDir(_T("..\\..\\Common\\medias"));

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
