
#pragma once

#include <myUtility.h>

class MyJob
{
protected:
	real m_weight;

public:
	real getWeight(void) const
	{
		return m_weight;
	}

public:
	MyJob(real weight);

	virtual ~MyJob(void);

	virtual bool doJob(void) = 0;
};

typedef std::tr1::shared_ptr<MyJob> MyJobPtr;

typedef std::vector<MyJobPtr> MyJobList;

class MyProgress
{
protected:
	MyJobList m_jobList;

public:
	void pushJob(MyJobPtr job);

	void pushJobList(MyJobList::const_iterator begin, MyJobList::const_iterator end);

	MyJobList::const_iterator getJobListBegin(void) const;

	MyJobList::iterator getJobListBegin(void);

	MyJobList::const_iterator getJobListEnd(void) const;

	MyJobList::iterator getJobListEnd(void);

	size_t getJobListSize(void) const;

public:
	MyProgress(void);

	virtual ~MyProgress(void);
};

template <class SIMPLE_CLASS>
class SimpleCreateObjJob : public MyJob
{
protected:
	typedef std::tr1::shared_ptr<SIMPLE_CLASS> SIMPLE_CLASS_PTR;

	SIMPLE_CLASS_PTR & m_ref;

public:
	SimpleCreateObjJob(SIMPLE_CLASS_PTR & ref, real weight = 1)
		: MyJob(weight)
		, m_ref(ref)
	{
	}

	bool doJob(void)
	{
		m_ref = SIMPLE_CLASS_PTR(new SIMPLE_CLASS());

		return true;
	}
};

class LoadBoneAssignmentIndexObjectJob : public MyJob
{
protected:
	my::BoneAssignmentIndexObjectFromOgreMeshPtr & m_ref;

	const std::basic_string<t3d::charT> m_str;

public:
	LoadBoneAssignmentIndexObjectJob(my::BoneAssignmentIndexObjectFromOgreMeshPtr & ref, const std::basic_string<t3d::charT> & str, real weight = 1);

	bool doJob(void);
};

class LoadObjectJob : public MyJob
{
protected:
	my::ObjectFromOgreMeshPtr & m_ref;

	const std::basic_string<t3d::charT> m_str;

public:
	LoadObjectJob(my::ObjectFromOgreMeshPtr & ref, const std::basic_string<t3d::charT> str, real weight = 1);

	bool doJob(void);
};

class LoadImageJob : public MyJob
{
protected:
	my::ImagePtr & m_ref;

	const std::basic_string<t3d::charT> m_str;

public:
	LoadImageJob(my::ImagePtr & ref, const std::basic_string<t3d::charT> str, real weight = 1);

	bool doJob(void);
};

class LoadWavJob : public MyJob
{
protected:
	my::WavPtr & m_ref;

	const std::basic_string<t3d::charT> m_str;

	t3d::DSound * m_dsound;

public:
	LoadWavJob(my::WavPtr & ref, const std::basic_string<t3d::charT> str, t3d::DSound * dsound, real weight = 1);

	bool doJob(void);
};

class LoadMp3Job : public MyJob
{
protected:
	my::Mp3Ptr & m_ref;

	const std::basic_string<t3d::charT> m_str;

	t3d::DSoundPtr m_dsound;

public:
	LoadMp3Job(my::Mp3Ptr & ref, const std::basic_string<t3d::charT> str, t3d::DSoundPtr dsound, real weight = 1);

	bool doJob(void);
};
