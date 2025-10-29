/** FILE: main.cpp
	������һ�������� my::Game Ӧ�ó���Ŀ��
*/

// ���� my �ķ�װ��
#include "libc.h"				// ��չ string ����
#include "myGame.h"				// Ӧ�ó����װ
#include "myUtility.h"			// ����ģ�ͻ���
#include "myPhysics.h"			// ��������
#include "myCollision.h"		// ��ײϵͳ
#include "myScene.h"			// ��������

// unicode ֧��
using t3d::charT;

// ʵ��
using t3d::real;

// ======================================== TODO: BEGIN ========================================

// ������ط������Լ�����

// ======================================== TODO: END   ========================================

class MyGame
	: public my::Game						// ����ʵ�ֻ���֡ѭ���Ļ���Ӧ�ó����ܣ����Ѿ�ʵ���˳����� primary��back surface �ṹ
	, public my::ErrorListener				// ʵ�ֽ��ܴ�����Ϣ�Ľӿڣ���Щ������Ϣͨ�������� my �ķ�װ�������Ϳ���ʹ�� REPORT_ERROR �������ӿڱ���
	, public my::DrawnHelper				// ���Ի��Ƴ�������εİ����࣬���������Ƽ򵥵� sphere��box��plane ��
{
protected:
	// һ�����ƿ���̨��ģ������������ surface ���������̨��Ϣ
	my::ConsoleSimulatorPtr m_consoleSim;

	// ���ڲ�����֡���ʼ��㹤��
	my::FPSManagerPtr m_fpsMgr;

	// ������Ƶ��֡���ʼ��㹤�ߣ���Ҫ�ṩ��������֧��
	my::TimerPtr m_timer;

	// ��������Ĺ���
	my::GridPtr m_grid;

	// ŷ�������Ĭ�Ͽ���ʹ��ŷ������ڳ��������ɹ۲�
	my::EularCameraPtr m_eularCam;

	// Ĭ����ͼ��Ŀ���Ƿ�ֹ��ͼ��Ⱦʱû����ͼ���³���
	my::ImagePtr m_defaultTexture;

	/** ΪʲôҪʹ�� ptr������ֱ�ӹ��캯����
		ӦΪĳЩ�����ڽ���ʱ���������Ⱦ��������� my::Game �ڹ��캯��ʱ����û�г�ʼ��һЩ������ SingleTon ����
		ֻ���ڿ�ܵ��� my::Game::onInit(...) ʱ����Щǰ�������ų��죬����ͨ����ʹ�� ptr���� onInit(...) ����ٹ���
	*/

	// ======================================== TODO: BEGIN ========================================

	// ������ط������Լ��Ķ���

	t3d::DSBufferPtr m_dsbuffer;
	t3d::DS3DBufferPtr m_ds3dbuffer;
	t3d::DS3DListenerPtr m_ds3dlistener;

	// ======================================== TODO: END   ========================================

public:
	/** ʵ�� my::Game::onInit �ӿ�
		ͨ����Ӧ�ó����ʼ��ʱ����ܻ��������ӿڣ�����Ӧ��������ʵ���Զ���ĳ�ʼ������
	*/
	virtual bool onInit(const CONFIG_DESC & cfg)
	{
		// ��ʼ��ģ�����̨
		m_consoleSim = my::ConsoleSimulatorPtr(new my::ConsoleSimulator(10));

		// ���Լ�ע��Ϊ my::ErrorReporter �ļ�����
		my::ErrorReporter::getSingleton().addErrorListener(this);

		// ��ʼ�� fps ������
		m_fpsMgr = my::FPSManagerPtr(new my::FPSManager());
		m_fpsMgr->start();

		// ��ʼ������ʼ timer
		m_timer = my::TimerPtr(new my::Timer());
		m_timer->start();

		// ��ʼ������
		m_grid = my::GridPtr(new my::Grid());

		// ����ŷ�����
		m_eularCam = my::EularCameraPtr(new my::EularCamera());
		m_eularCam->setDefaultPosition(my::Vec4<real>(-50, 50, -50));
		m_eularCam->setDefaultRotation(my::Vec4<real>(DEG_TO_RAD(45), DEG_TO_RAD(45), DEG_TO_RAD(0)));
		m_eularCam->reset();

		// ���ý������·����������ݷ�ʽʱҪע�⵱ǰ·����λ��
		m_resourceMgr->addDir(_T("."));
		m_resourceMgr->addDir(_T("../../common/medias"));

		// load ��һ����ͼ
		my::IOStreamPtr tmpStream;
		my::ImagePtr tmpImage;
		tmpImage = my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("checker5x5.bmp"))));
		m_defaultTexture = my::ImagePtr(my::ColorConversion::getSingleton().convertImage(tmpImage.get()));

		// ======================================== TODO: BEGIN ========================================

		// ������ط���ʼ���Զ���Ķ���

		// ���� direct sound 3d buffer
		my::WavPtr tmpWav(new my::Wav(my::ResourceMgr::getSingleton().findFileOrException(_T("MusicMono.wav"))));
		m_dsbuffer = my::createDSoundBufferForWholeWav(m_dsound.get(), tmpWav.get(), DSBCAPS_CTRL3D);
		m_ds3dbuffer = m_dsbuffer->getDS3DBuffer();

		// ע�⣬listener ������ primary sound buffer ���ܴ���
		DSBUFFERDESC ddsc = {sizeof(ddsc)};
		ddsc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
		t3d::DSBufferPtr dsbprimary = m_dsound->createSoundBuffer(&ddsc);
		m_ds3dlistener = dsbprimary->getDS3DListener();

		// ���� 3dbuffer parameter
		DS3DBUFFER ds3dbp = {sizeof(ds3dbp)};
		m_ds3dbuffer->getAllParameters(&ds3dbp);
		DS3DLISTENER ds3dlp = {sizeof(ds3dlp)};
		m_ds3dlistener->getAllParameters(&ds3dlp);

		m_ds3dbuffer->setMinDistance(1);
		m_ds3dbuffer->setMaxDistance(50);
		ds3dlp.flDopplerFactor = 0;
		ds3dlp.flRolloffFactor = 0.5;
		m_ds3dlistener->setAllParameters(&ds3dlp);
		m_ds3dlistener->commitDeferredSettings();

		// ��������
		my::copyWholeWavBufferToDSoundBuffer(m_dsbuffer.get(), tmpWav.get());
		m_dsbuffer->play(0, DSBPLAY_LOOPING);

		// ======================================== TODO: END   ========================================

		return true;
	}

	/** ʵ�� my::Game::onShutdown �ӿ�
		��ܻ����˳�Ӧ�ó���ʱ����������ӿڣ������Զ�������٣����ڻ�����ȫ��ʹ�� smart_ptr�����Բ���Ҫ delete
	*/
	virtual void onShutdown(void)
	{
	}

	/** ʵ�� my::Game::onFrame �ӿ�
		��ܻ������߳�û����Ϣ�����ʱ���������ӿڣ�Ӧ�����������֡����������Ⱦ��step ���������
	*/
	virtual bool onFrame(void)
	{
		// ����û����� space �� return false ����Ӧ�ó���
		if(m_keyboard->isKeyDown(DIK_ESCAPE))
			return false;

		// �ۼ� fps ������
		// fps ��������ͨ�����ϲ��������֡���ʵģ�����û�� timer ����������ͨӦ���Ѿ��㹻��
		m_fpsMgr->addFrame();

		// ��þ�ȷ֡ʱ�䣬����һ�� getElapsedTime �����֮���ʱ��
		// ע�⣺Ϊ��ֹ������֡ʱ����̫����������������������������ó�����С�� 30 ֡ / ��
		const real elapsedTime = std::min((real)m_timer->getElapsedTime(), (real)0.033);

		//// ���ﴴ��һ���ȴ���С�� clipper ���򣬽����ڲ�����Ⱦ�� clipper bug
		//// ���������Ⱦ������ clipper ��ͨ���㷨ʵ�ֵģ��������㷨��ǿ�����ᵼ�»�ͼʱԽ�� clipper ����
		//// ����Խ�������������Խ���ͼ������Сһ���ֿ�����΢���⣬��Խ�絼��ϵͳ����������
		//CRect clipper(m_rback);
		//clipper.DeflateRect(10, 10);
		//m_rc->setClipperRect(clipper);

		// ���� back surface
		m_rc->fillSurface(m_rc->getClipperRect(), my::Color(0.8f, 0.8f, 0.8f));

		// ���� zbuffer
		m_rc->fillZbuffer(m_rc->getClipperRect(), 0);

		// ������Ⱦ�����ĵ� camera
		m_rc->setViewport(m_rc->getClipperRect());
		m_rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), m_rc->getClipperRect().Width(), m_rc->getClipperRect().Height()));
		m_rc->setCameraNearZ(1);
		m_rc->setCameraFarZ(10000);

		// ���û�����������ŷ�����������ͷ�λ
		m_eularCam->update(m_keyboard.get(), m_mouse.get(), elapsedTime);
		m_rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEular(m_eularCam->getPosition(), m_eularCam->getRotation()));

		// ������Ⱦ�����ĵ� light
		my::Vec4<real> l_pos(-30, 30, -30);
		l_pos *= t3d::mat3RotZXY(m_eularCam->getRotation()) * t3d::mat3Mov(m_eularCam->getPosition());
		m_rc->clearLightList();
		m_rc->pushLightAmbient(my::Vec4<real>(0.2f, 0.2f, 0.2f));
		m_rc->pushLightPoint(my::Vec4<real>(1, 1, 1), l_pos); //my::Vec4<real>(100, 100, -100));

		// ������Ⱦ�����ĵ� material
		m_rc->setAmbient(my::Color::WHITE);
		m_rc->setDiffuse(my::Color::WHITE);

		// ������Ⱦ�����ĵ� texture
		m_rc->setTextureBuffer(m_defaultTexture->getBits(), m_defaultTexture->getPitch(), m_defaultTexture->getWidth(), m_defaultTexture->getHeight());

		// ======================================== TODO: BEGIN ========================================

		// ����ط��Զ�����Ⱦ���ɸı�֮ǰ��Ⱦ�����ĵ�����

		m_ds3dlistener->setPosition(m_eularCam->getPosition().x, m_eularCam->getPosition().y, m_eularCam->getPosition().z);
		my::Mat4<real> mCameraRotation = t3d::mat4GetRotationScalePart(m_rc->getCameraMatrix().inverse());
		my::Vec4<real> vFront = my::Vec4<real>::UNIT_Z * mCameraRotation;
		my::Vec4<real> vTop = my::Vec4<real>::UNIT_Y * mCameraRotation;
		m_ds3dlistener->setOrientation(vFront.x, vFront.y, vFront.z, vTop.x, vTop.y, vTop.z);
		m_ds3dlistener->commitDeferredSettings();

		// ======================================== TODO: END   ========================================

		// ��Ⱦ����
		m_grid->drawZBufferRW(m_rc.get());

		// ���������Ϣ����֡���ʡ������λ��
		std::basic_string<charT> strTmp;
		HDC hdc = m_sback->getDC();

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
			RAD_TO_DEG(m_eularCam->getRotation().x), RAD_TO_DEG(m_eularCam->getRotation().y), RAD_TO_DEG(m_eularCam->getRotation().z));
		::TextOut(hdc, textx, texty += 20, strTmp.c_str(), (int)strTmp.length());

		m_sback->releaseDC(hdc);

		// ���ƿ���̨ģ����
		m_consoleSim->draw(m_sback.get(), 10, texty += 20);

		return true;
	}

	/** ʵ�� ErrorListener::onReport �ӿ�
		���Խ������Կ�ܵĴ��� message���������ӡ��ģ�����̨
	*/
	virtual void onReport(const std::basic_string<charT> & info)
	{
		// ��������Ϣ��ӡ������̨ģ������������΢�����ж��Է�ֹ��Ӧ�ظ���Ϣ
		if(m_consoleSim->m_lines.empty() || info != m_consoleSim->m_lines.back())
		{
			m_consoleSim->report(info);
		}
	}
};

int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	// ����ʱ�ڴ�й©���
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));

	// ������ط���ȡ�û��Զ���ֱ��ʣ���Ļ���õȣ�����ο� my::Game::SCREEN_MODE
	return MyGame().run(my::Game::CONFIG_DESC(800, 600, my::Game::SM_WINDOWED));

	//// �����ǿ�������򵥵�Ӧ�ó���ģ��
	//my::Application app;
	//my::Window * pwnd = app.createWindow(_T("Hello world"));
	//pwnd->showWindow();
	//pwnd->updateWindow();
	//return app.run();

	//// �����ǿ�������򵥵���Ϸ���ģ��
	//return my::Game().run();
}
