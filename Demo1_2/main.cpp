
// ���� c++ ���ļ�

#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/shared_array.hpp>

#include <crtdbg.h>
#ifdef _DEBUG
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__ )
#endif

// ���� 3d ͼ�ο�
#include "t3dlib1.h"
#include "t3dlib2.h"
#include "t3dlib3.h"
#include "t3dlib4.h"
#include "t3dlib5.h"
#include "t3dlib6.h"

// ���� my �ķ�װ
#include "libc.h"				// c ��ʽ string ����
#include "myGame.h"				// Ӧ�ó����װ
#include "myUtility.h"			// ����ģ�ͻ���
#include "myPhysics.h"			// ��������
#include "myCollision.h"		// ��ײϵͳ
#include "myScene.h"
//
//// ���� windows ��ý���
//#pragma comment(lib, "winmm.lib")

using t3d::charT;				// unicode ֧��
using t3d::real;				// ʵ��

class MyGame
	: public my::Game			// ����ʵ�ֻ���֡ѭ���Ļ���Ӧ�ó����ܣ����Ѿ�ʵ���˳����� primary��back surface �ṹ
	, public my::DrawnHelper			// ���Ի��Ƴ�������Σ��� sphere��box��plane ��
	, public my::ErrorListener	// ʵ�ֽ��ܴ�����Ϣ�Ľӿڣ���Щ������Ϣͨ�������� my �ķ�װ��Ҳ����ʹ�� REPORT_ERROR �������ӿڱ���
	, public my::Window::MessageListener
{
protected:
	my::ConsoleSimulatorPtr m_consoleSim;	// һ�����ƿ���̨��ģ������������ surface ���������̨��Ϣ
	my::TimerPtr m_timer;					// ����ʱ��Ĺ��ߣ���Ҫ���Ծ�ȷ֡���ʼ���
	my::FPSManagerPtr m_fpsMgr;				// ���� fps �Ĺ��ߣ�ģ��֡���ʼ���
	my::GridPtr m_grid;						// ��������Ĺ���
	my::EularCameraPtr m_eularCam;			// ŷ�����
	my::ImagePtr m_defaultTexture;			// Ĭ����ͼ

	/** ΪʲôҪʹ�� ptr������ֱ�ӹ��캯����
	ӦΪĳЩ�����ڽ���ʱ���������Ⱦ��������� my::Game �ڹ��캯��ʱ����û�г�ʼ��һЩ������ SingleTon ����
	ֻ���� my::Game::onInit(...) ֮����Щǰ�������ų��죬
	����ͨ����ʹ�� ptr���� onInit(...) ����ٹ���
	*/

	// ======================================== TODO: BEGIN ========================================

	// �Զ����Ա
	my::BoneAssignmentIndexObjectPtr m_jackModel;

	my::ImagePtr m_jackTexture;

	my::SkeletonAnimationsFromOgreSkeletonPtr m_jackSkeleton;

	t3d::BoneNodeList m_jackBoneNodeList;

	t3d::BoneTransformList m_jackBoneTransformList;

	t3d::DSBufferPtr m_dsbuffer;

	my::ObjectBasePtr m_obj;

	// ======================================== TODO: END   ========================================

public:
	/** ʵ�� my::Game::onInit �ӿ�
	ͨ����Ӧ�ó����ʼ��ʱ����ܻ��������ӿڣ�����Ӧ��������ʵ���Զ���ĳ�ʼ������
	*/
	virtual bool onInit(void)
	{
		// ��ʼ������̨ģ����
		m_consoleSim = my::ConsoleSimulatorPtr(new my::ConsoleSimulator(10));

		// ���Լ�ע��Ϊ my::ErrorReporter �ļ�����
		my::ErrorReporter::getSingleton().addErrorListener(this);

		// ��ʼ������ʼ timer
		m_timer = my::TimerPtr(new my::Timer());
		m_timer->start();

		// ��ʼ�� fps ������
		m_fpsMgr = my::FPSManagerPtr(new my::FPSManager());
		m_fpsMgr->start();

		// ��ʼ������
		m_grid = my::GridPtr(new my::Grid());

		// ����ŷ�����
		m_eularCam = my::EularCameraPtr(new my::EularCamera());
		m_eularCam->setDefaultPosition(my::Vec4<real>(50, 50, -50));
		m_eularCam->setDefaultRotation(my::Vec4<real>(DEG_TO_RAD(45), DEG_TO_RAD(-45), DEG_TO_RAD(0)));
		m_eularCam->reset();

		// ���ý������·����������ݷ�ʽʱҪע�⵱ǰ·����λ��
		m_resourceMgr->registerDir(_T("../../common/medias"));

		// load ��һ����ͼ
		my::ImagePtr tmpImage;
		tmpImage = my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("checker5x5.bmp"))));
		m_defaultTexture = my::ImagePtr(my::ColorConversion::getSingleton().convertImage(tmpImage.get()));

		// tmp stream
		my::IOStreamPtr tmpStream;

		// ======================================== TODO: BEGIN ========================================

		//// �Զ����ʼ��
		//tmpStream = my::IOStreamPtr(my::ResourceMgr::getSingleton().openIOStream(_T("jack_hres.mesh.xml")));
		//m_jackModel = my::BoneAssignmentIndexObjectPtr(new my::BoneAssignmentIndexObjectFromOgreMesh(tmpStream.get()));

		//tmpImage = my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(_T("jack_texture.png"))));
		//m_jackTexture = my::ImagePtr(my::ColorConversion::getSingleton().convertImage(tmpImage.get()));

		//tmpStream = my::IOStreamPtr(my::ResourceMgr::getSingleton().openIOStream(_T("jack_anim_stand.skeleton.xml")));
		//m_jackSkeleton = my::SkeletonAnimationsFromOgreSkeletonPtr(new my::SkeletonAnimationsFromOgreSkeleton(tmpStream.get()));
		//m_jackSkeleton->getSkeletonAnimation("clip1").setNextAnimationName("clip2");
		//m_jackSkeleton->getSkeletonAnimation("clip2").setNextAnimationName("clip1");
		//m_jackSkeleton->getSkeletonAnimation("clip3").setNextAnimationName("clip4");
		//m_jackSkeleton->getSkeletonAnimation("clip4").setNextAnimationName("clip3");
		//m_jackSkeleton->setCurrentAnimationName("clip3");
		//m_jackSkeleton->setCurrentAnimationTime(0);

		//m_jackBoneNodeList = m_jackSkeleton->getOrigBoneNodeList();

		//m_jackBoneTransformList.resize(m_jackSkeleton->getOrigBoneNodeListSize());

		////// load ��������
		////my::WavPtr tmpWav = my::WavPtr(new my::Wav(my::ResourceMgr::getSingleton().findFileOrException(_T("stationthrob.wav"))));
		////m_dsbuffer = t3d::DSBufferPtr(my::createDSoundBufferForWholeWav(m_dsound.get(), tmpWav.get()));
		////my::copyWholeWavBufferToDSoundBuffer(m_dsbuffer.get(), tmpWav.get());
		////m_dsbuffer->play();

		//tmpStream = my::IOStreamPtr(my::ResourceMgr::getSingleton().openIOStream(_T("bsp_test_scene.mesh.xml")));
		//m_obj = my::ObjectBasePtr(new my::ObjectFromOgreMesh(tmpStream.get()));

		tmpStream = my::IOStreamPtr(my::ResourceMgr::getSingleton().openIOStream(_T("bsp_test_scene (shared gemetry).mesh.xml")));
		m_obj = my::ObjectBasePtr(new my::BoneAssignmentIndexObjectFromOgreMesh(tmpStream.get()));

		// ======================================== TODO: END   ========================================

		m_pwnd->setMessageListener(this);

		return true;
	}

	/** ʵ�� my::Game::onShutdown �ӿ�
	�����������Լ������Ķ��������ڻ�����ȫ��ʹ�� smart_ptr�����Կ�ܲ���Ҫ shutdown
	����ܻ��ǻ����˳�Ӧ�ó���ʱ����������ӿڣ������Զ��������
	*/
	virtual void onShutdown(void)
	{
	}

	/** ʵ�� my::Game::onFrame �ӿ�
	*/
	virtual bool onFrame(void)
	{
		// ����û����� space �� return false ����Ӧ�ó���
		if(m_keyboard->isKeyDown(DIK_ESCAPE))
			return false;

		// ��þ�ȷ֡ʱ�䣬����һ�� getElapsedTime �����֮���ʱ��
		// ע�⣺Ϊ��ֹ������֡ʱ����̫����������������������������ó�����С�� 30 ֡ / ��
		const real elapsedTime = std::min((real)m_timer->getElapsedTime(), (real)0.033);

		// �ۼ� fps ������
		// fps ��������ͨ�����ϲ��������֡���ʵģ�����û�� timer ����������ͨӦ���Ѿ��㹻��
		m_fpsMgr->addFrame();

		// ���û�����������ŷ�����������ͷ�λ
		m_eularCam->update(m_keyboard.get(), m_mouse.get(), elapsedTime);

		// ���� zbuffer
		m_rc->setClipperRect(m_rback);

		m_rc->fillZbuffer(m_rback, 0);

		// ���ﴴ��һ���ȴ���С�� clipper ���򣬽����ڲ��� 3d ��Ⱦ�� clipper bug
		// ���������Ⱦ������ clipper ��ͨ���㷨ʵ�ֵģ��������㷨��ǿ�����ص�֮��ͼʱԽ�� clipper ����
		// ����Խ�������������Խ���ͼ������Сһ���ֿ�����΢���⣬��Խ�絼��ϵͳ����������
		CRect clipper(m_rback.left + 10, m_rback.top + 10, m_rback.right - 10, m_rback.bottom - 10);

		m_rc->setClipperRect(clipper);

		// ���� back surface
		m_rc->fillSurface(m_rback, my::Color(0.8f, 0.8f, 0.8f));

		// ������Ⱦ�����ĵ� camera
		m_rc->setCameraMatrix(t3d::CameraContext::buildInverseCameraTransformEular(m_eularCam->getPosition(), m_eularCam->getRotation()));
		m_rc->setViewport(clipper);
		m_rc->setCameraProjection(t3d::CameraContext::buildCameraProjectionFOVAuto(DEG_TO_RAD(90), clipper.right - clipper.left, clipper.bottom - clipper.top));
		m_rc->setCameraNearZ(1);
		m_rc->setCameraFarZ(10000);

		// ��Ⱦ����
		m_grid->drawZBufferRW(m_rc.get());

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

		//// �Զ�����Ⱦ
		//const t3d::BoneNodeList & boneNodeList =
		//	m_jackSkeleton->gotoAnimation(m_jackSkeleton->getCurrentAnimationName(), m_jackSkeleton->getCurrentAnimationTime() + elapsedTime);

		//t3d::STreeNode::IndexList::const_iterator root_iter = m_jackSkeleton->getRootIndexListBegin();
		//for(; root_iter != m_jackSkeleton->getRootIndexListEnd(); root_iter++)
		//{
		//	// �� banding position ����
		//	t3d::incrementBoneNodeList(
		//		m_jackBoneNodeList,
		//		m_jackSkeleton->getOrigBoneNodeList(),
		//		boneNodeList,
		//		*root_iter);

		//	// ��ȡ��ǰ������ transform matrix
		//	t3d::updateBoneTransformListFromBoneNodeList(
		//		m_jackBoneTransformList,
		//		m_jackBoneNodeList,
		//		*root_iter,
		//		my::Mat4<real>::IDENTITY,
		//		my::Mat4<real>::IDENTITY);
		//}

		//// ��ȡ���� transform matrix
		//t3d::combineVertexNormalBoneTransformList(
		//	m_jackBoneTransformList,
		//	m_jackSkeleton->getOrigBoneInverseTransformList(),
		//	m_jackBoneTransformList);

		//t3d::bindVertexListNormalListFromBoneTransformList(
		//	m_jackModel->getVertexList(),
		//	m_jackModel->getNormalList(),
		//	m_jackModel->getOriginalVertexList(),
		//	m_jackModel->getOriginalNormalList(),
		//	m_jackModel->getBoneAssignmentList(),
		//	m_jackBoneTransformList);

		//m_rc->setTextureBuffer(m_jackTexture->getBits(), m_jackTexture->getPitch(), m_jackTexture->getWidth(), m_jackTexture->getHeight());
		////m_jackModel->drawGouraudTextureZBufferRW(m_rc.get());
		////m_jackModel->drawWireZBufferRW(m_rc.get(), my::Color::BLUE);
		//m_jackModel->drawGouraudZBufferRW(m_rc.get());

		//m_obj->drawWireZBufferRW(m_rc.get(), my::Color::BLUE);
		//m_obj->drawWireZBufferRWWithBackface(m_rc.get(), my::Color::BLUE);
		//m_obj->drawZBufferRW(m_rc.get(), my::Color::BLUE);
		//m_obj->drawZBufferRWWithBackface(m_rc.get(), my::Color::BLUE);
		m_obj->drawGouraudZBufferRWWithBackface(m_rc.get());

		// ======================================== TODO: END   ========================================

		//// ���� back surface
		//m_sback->unlock();

		// ���������Ϣ����֡���ʡ������λ��
		std::basic_string<charT> strTmp;
		HDC hdc = m_sback->getDC();

		strTmp = str_printf(_T("fps: %.1f"), 1 / elapsedTime);
		::TextOut(hdc, 10, 10, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("fps: %.1f"), m_fpsMgr->getFPS());
		::TextOut(hdc, 10, 30, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("cam.pos: %f, %f, %f"),
			m_eularCam->getPosition().x, m_eularCam->getPosition().y, m_eularCam->getPosition().z);
		::TextOut(hdc, 10, 50, strTmp.c_str(), (int)strTmp.length());

		strTmp = str_printf(_T("cam.rot: %f, %f, %f"),
			RAD_TO_DEG(m_eularCam->getRotation().x), RAD_TO_DEG(m_eularCam->getRotation().y), RAD_TO_DEG(m_eularCam->getRotation().z));
		::TextOut(hdc, 10, 70, strTmp.c_str(), (int)strTmp.length());

		m_sback->releaseDC(hdc);

		// ���ƿ���̨ģ����
		m_consoleSim->draw(m_sback.get(), 10, 10);

		return true;
	}

	void onReport(const std::basic_string<charT> & info)
	{
		// ��������Ϣ��ӡ������̨ģ������������΢�����ж��Է�ֹ��Ӧ�ظ���Ϣ
		if(m_consoleSim->m_lines.empty() || info != m_consoleSim->m_lines.back())
		{
			m_consoleSim->report(info);
		}
	}

	BOOL notifyMessage(LRESULT & lResult, my::Window * win, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch(message)
		{
		case WM_KEYDOWN:
			switch(wparam)
			{
			case VK_F1:
				prepareConfig(my::GameBase::CONFIG_DESC(640, 480, SM_WINDOWED));
				break;

			case VK_F2:
				prepareConfig(my::GameBase::CONFIG_DESC(800, 600, SM_WINDOWED));
				break;

			case VK_F3:
				prepareConfig(my::GameBase::CONFIG_DESC(1024, 768, SM_WINDOWED));
				break;

			case VK_F4:
				prepareConfig(my::GameBase::CONFIG_DESC(1280, 1024, SM_WINDOWED));
				break;
			}
			lResult = 0;
			return TRUE;
		}

		return FALSE;
	}
};

int APIENTRY WinMain(
	HINSTANCE	/*hInstance*/,
	HINSTANCE	/*hPrevInstance*/,
	LPSTR		/*lpCmdLine*/,
	int			/*nCmdShow*/)
{
	try
	{
		// ����һ��Ӧ�ó����� 800 x 600 ����ģʽ����
		MyGame game;
		return game.run(my::Game::CONFIG_DESC(800, 600, my::Game::SM_WINDOWED));
	}
	catch(t3d::Exception & e)
	{
		::MessageBox(NULL, e.getFullDesc().c_str(), _T("Exception"), MB_OK);
	}

	return -1;
}
