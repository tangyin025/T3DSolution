
#include "StdAfx.h"
#include "MyProgress.h"

MyJob::MyJob(real weight)
	: m_weight(weight)
{
}

MyJob::~MyJob(void)
{
}

void MyProgress::pushJob(MyJobPtr job)
{
	m_jobList.push_back(job);
}

void MyProgress::pushJobList(MyJobList::const_iterator begin, MyJobList::const_iterator end)
{
	m_jobList.insert(m_jobList.end(), begin, end);
}

MyJobList::const_iterator MyProgress::getJobListBegin(void) const
{
	return m_jobList.begin();
}

MyJobList::iterator MyProgress::getJobListBegin(void)
{
	return m_jobList.begin();
}

MyJobList::const_iterator MyProgress::getJobListEnd(void) const
{
	return m_jobList.end();
}

MyJobList::iterator MyProgress::getJobListEnd(void)
{
	return m_jobList.end();
}

size_t MyProgress::getJobListSize(void) const
{
	return m_jobList.size();
}

MyProgress::MyProgress(void)
{
}

MyProgress::~MyProgress(void)
{
}

LoadBoneAssignmentIndexObjectJob::LoadBoneAssignmentIndexObjectJob(my::BoneAssignmentIndexObjectFromOgreMeshPtr & ref, const std::basic_string<t3d::charT> & str, real weight /*= 1*/)
	: MyJob(weight)
	, m_ref(ref)
	, m_str(str)
{
}

bool LoadBoneAssignmentIndexObjectJob::doJob(void)
{
	m_ref = my::BoneAssignmentIndexObjectFromOgreMeshPtr(new my::BoneAssignmentIndexObjectFromOgreMesh(
		my::IOStreamPtr(new my::FileStream(my::ResourceMgr::getSingleton().findFileOrException(m_str)))));

	return true;
}

LoadObjectJob::LoadObjectJob(my::ObjectFromOgreMeshPtr & ref, const std::basic_string<t3d::charT> str, real weight /*= 1*/)
	: MyJob(weight)
	, m_ref(ref)
	, m_str(str)
{
}

bool LoadObjectJob::doJob(void)
{
	m_ref = my::ObjectFromOgreMeshPtr(new my::ObjectFromOgreMesh(
		my::IOStreamPtr(new my::FileStream(my::ResourceMgr::getSingleton().findFileOrException(m_str)))));

	return true;
}

LoadImageJob::LoadImageJob(my::ImagePtr & ref, const std::basic_string<t3d::charT> str, real weight /*= 1*/)
	: MyJob(weight)
	, m_ref(ref)
	, m_str(str)
{
}

bool LoadImageJob::doJob(void)
{
	m_ref = my::ColorConversion::getSingleton().convertImage(
		my::ImagePtr(new my::Image(my::ResourceMgr::getSingleton().findFileOrException(m_str))));

	return true;
}

LoadWavJob::LoadWavJob(my::WavPtr & ref, const std::basic_string<t3d::charT> str, t3d::DSound * dsound, real weight /*= 1*/)
	: MyJob(weight)
	, m_ref(ref)
	, m_str(str)
	, m_dsound(dsound)
{
}

bool LoadWavJob::doJob(void)
{
	m_ref = my::WavPtr(new my::Wav(
		m_dsound, my::ResourceMgr::getSingleton().findFileOrException(m_str)));

	return true;
}

LoadMp3Job::LoadMp3Job(my::Mp3Ptr & ref, const std::basic_string<t3d::charT> str, t3d::DSoundPtr dsound, real weight /*= 1*/)
	: MyJob(weight)
	, m_ref(ref)
	, m_str(str)
	, m_dsound(dsound)
{
}

bool LoadMp3Job::doJob(void)
{
	m_ref = my::Mp3Ptr(new my::Mp3(
		m_dsound, my::IOStreamPtr(new my::FileStream(my::ResourceMgr::getSingleton().findFileOrException(m_str)))));

	return true;
}
