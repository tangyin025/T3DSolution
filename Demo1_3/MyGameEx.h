
#pragma once

#include "MyState.h"
#include "MyUI.h"
#include <myPhysics.h>

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
	, public my::ErrorListener
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

protected:
	my::FPSManagerPtr m_fpsMgr;

	my::TimerPtr m_timer;

	my::ConsoleSimulatorPtr m_consoleSim;

	my::EulerCameraPtr m_eulerCam;

	my::FontPtr m_font;

public:
	MyGame(void) throw();

	~MyGame(void);

public:
	my::WindowPtr newWindow(void);

	bool onInit(const my::Config & cfg);

	void onReport(const std::basic_string<charT> & info);

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
	virtual bool doFrame(real elapsedTime) = 0;
};

typedef boost::shared_ptr<MyFrameState> MyStateBasePtr;

class MyLoadState
	: public MyFrameState
	, public my::Thread
{
public:
	static const std::basic_string<charT> s_name;

protected:
	MyUIProgressBarBoxPtr m_progressBox;

	my::CriticalSection m_progressBoxLock;

	bool m_exitFlag;

	my::CriticalSection m_exitFlagLock;

public:
	void setExitFlagSync(bool exitFlag = true)
	{
		my::CriticalSectionLock lock(m_exitFlagLock);
		m_exitFlag = exitFlag;
	}

	bool getExitFlagSync(void)
	{
		my::CriticalSectionLock lock(m_exitFlagLock);
		return m_exitFlag;
	}

	void updateTitleSync(const std::basic_string<t3d::charT> & text)
	{
		my::CriticalSectionLock lock(m_progressBoxLock);
		m_progressBox->setTitleText(text);
	}

	void updateProgressSync(real percent)
	{
		my::CriticalSectionLock lock(m_progressBoxLock);
		m_progressBox->setPercent(percent);
	}

public:
	MyLoadState(void);

	~MyLoadState(void);

	void enterState(void);

	void leaveState(void);

	bool doFrame(real elapsedTime);

	DWORD onProc(void);
};

typedef boost::shared_ptr<MyLoadState> MyLoadStatePtr;

class TPSCharacter
{
public:
	t3d::Vec4<real> move;

	my::RigidBodyPtr body;

	my::CollisionSphere sphere;
};

class CharacterMonitorHander
{
public:
	my::ParticlePtr particle;

	my::ParticleAnchoredSpringPtr spring;

	my::ParticleCableConstraintPtr cable;
};

class MyGameState
	: public MyFrameState
	, public my::ParticleWorld
	, public my::World
	, public my::DrawnHelper
{
	friend class MyLoadState;

	friend class MyWorld;

public:
	static const std::basic_string<charT> s_name;

protected:
	TPSCharacter m_character;

	CharacterMonitorHander m_hander;

	my::CollisionPlane m_ground;

protected:
	my::ObjectFromOgreMeshPtr m_scene;

	my::FrontToBackCustomShaderBSPNodePtr m_scene_bsp;

	typedef std::vector<my::BoneAssignmentIndexObjectFromOgreMeshPtr> BoneAssignmentIndexObjectFromOgreMeshPtrList;

	BoneAssignmentIndexObjectFromOgreMeshPtrList m_jack_bone_assignments;

	typedef std::vector<my::CustomShaderIndexObjectPtr> CustomShaderIndexObjectPtrList;

	CustomShaderIndexObjectPtrList m_jack_meshs;

	typedef std::vector<t3d::ConnectionEdgeList> ConnectionEdgeListList;

	ConnectionEdgeListList m_jack_connection_edges;

	my::SkeletonAnimationsFromOgreSkeletonPtr m_jack_skel;

	my::IndexSphereObjectPtr m_sky_sphere;

	my::ImagePtr m_sky_sphere_tex;

	my::Mp3Ptr m_music;

protected:
	t3d::real m_jack_intersection_offset;

	t3d::BoneNodeList m_jack_combine_bone_node_list;

	t3d::BoneNodeList m_jack_bone_node_list;

	t3d::BoneTransformList m_jack_bone_transform_list;

	t3d::VertexList m_jack_silhouette_edge_list;

	t3d::VertexList m_jack_shadow_volume;

public:
	MyGameState(void);

	~MyGameState(void);

	void enterState(void);

	void leaveState(void);

	void integrate(real duration);

	unsigned generateContacts(my::Contact * contacts, unsigned limits);

	void runPhysics(real duration);

	bool doFrame(real elapsedTime);
};

typedef boost::shared_ptr<MyGameState> MyGameStatePtr;
