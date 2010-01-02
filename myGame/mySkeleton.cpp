
#include "stdafx.h"
#include "mySkeleton.h"

#include <algorithm>
#include "myMath.h"

namespace my
{
	//void BoneAnimation::pushBoneKeyFrame(t3d::BoneKeyFrameList::const_reference boneKeyFrame)
	//{
	//	m_boneKeyFrameList.push_back(boneKeyFrame);
	//}

	//void BoneAnimation::pushBoneKeyFrameList(t3d::BoneKeyFrameList::const_iterator begin, t3d::BoneKeyFrameList::const_iterator end)
	//{
	//	m_boneKeyFrameList.insert(m_boneKeyFrameList.end(), begin, end);
	//}

	//t3d::BoneKeyFrameList::size_type BoneAnimation::getBoneKeyFrameListSize(void) const
	//{
	//	return m_boneKeyFrameList.size();
	//}

	//void BoneAnimation::resizeBoneKeyFrameList(t3d::BoneKeyFrameList::size_type size)
	//{
	//	m_boneKeyFrameList.resize(size);
	//}

	//void BoneAnimation::clearBoneKeyFrameList(void)
	//{
	//	m_boneKeyFrameList.clear();
	//}

	//t3d::BoneKeyFrameList::reference BoneAnimation::boneKeyFrameAt(t3d::BoneKeyFrameList::size_type i)
	//{
	//	assert(i < getBoneKeyFrameListSize());

	//	return m_boneKeyFrameList[i];
	//}

	//t3d::BoneKeyFrameList::const_reference BoneAnimation::boneKeyFrameAt(t3d::BoneKeyFrameList::size_type i) const
	//{
	//	assert(i < getBoneKeyFrameListSize());

	//	return m_boneKeyFrameList[i];
	//}

	//t3d::BoneKeyFrameList & BoneAnimation::getBoneKeyFrameList(void)
	//{
	//	return m_boneKeyFrameList;
	//}

	//const t3d::BoneKeyFrameList & BoneAnimation::getBoneKeyFrameList(void) const
	//{
	//	return m_boneKeyFrameList;
	//}

	//real BoneAnimation::getMinTime(void) const
	//{
	//	return t3d::getBoneKeyFrameListMinTime(m_boneKeyFrameList);
	//}

	//real BoneAnimation::getMaxTime(void) const
	//{
	//	return t3d::getBoneKeyFrameListMaxTime(m_boneKeyFrameList);
	//}

	//MYGAME_API t3d::BoneNodeList & updateBoneNodeListFromBoneAnimationList(
	//	t3d::BoneNodeList & boneNodeList,
	//	const BoneAnimationList & boneAnimationList,
	//	real time)
	//{
	//	assert(boneNodeList.size() == boneAnimationList.size());

	//	size_t i = 0;
	//	for(; i < boneNodeList.size(); i++)
	//	{
	//		t3d::intersectBoneKeyFrameList(
	//			boneNodeList[i],
	//			boneAnimationList[i].getBoneKeyFrameList(),
	//			time);
	//	}

	//	return boneNodeList;
	//}

	//void SkeletonAnimationNodeBase::pushBoneAnimation(BoneAnimationList::const_reference boneAnimation)
	//{
	//	m_boneAnimationList.push_back(boneAnimation);
	//}

	//void SkeletonAnimationNodeBase::pushBoneAnimationList(BoneAnimationList::const_iterator begin, BoneAnimationList::const_iterator end)
	//{
	//	m_boneAnimationList.insert(m_boneAnimationList.end(), begin, end);
	//}

	//BoneAnimationList::size_type SkeletonAnimationNodeBase::getBoneAnimationListSize(void) const
	//{
	//	return m_boneAnimationList.size();
	//}

	//void SkeletonAnimationNodeBase::resizeBoneAnimationList(BoneAnimationList::size_type size)
	//{
	//	m_boneAnimationList.resize(size);
	//}

	//void SkeletonAnimationNodeBase::clearBoneAnimationList(void)
	//{
	//	m_boneAnimationList.clear();
	//}

	//BoneAnimationList::reference SkeletonAnimationNodeBase::boneAnimationAt(BoneAnimationList::size_type i)
	//{
	//	assert(i < getBoneAnimationListSize());

	//	return m_boneAnimationList[i];
	//}

	//BoneAnimationList::const_reference SkeletonAnimationNodeBase::boneAnimationAt(BoneAnimationList::size_type i) const
	//{
	//	assert(i < getBoneAnimationListSize());

	//	return m_boneAnimationList[i];
	//}

	//BoneAnimationList & SkeletonAnimationNodeBase::getBoneAnimationList(void)
	//{
	//	return m_boneAnimationList;
	//}

	//const BoneAnimationList & SkeletonAnimationNodeBase::getBoneAnimationList(void) const
	//{
	//	return m_boneAnimationList;
	//}

	//real SkeletonAnimationNodeBase::calculateMinTime(void) const
	//{
	//	real minTime = REAL_MIN;
	//	BoneAnimationList::const_iterator bone_animation_iter = m_boneAnimationList.begin();
	//	for(; bone_animation_iter != m_boneAnimationList.end(); bone_animation_iter++)
	//	{
	//		if(bone_animation_iter->getMinTime() < minTime)
	//		{
	//			minTime = bone_animation_iter->getMinTime();
	//		}
	//	}
	//	return minTime;
	//}

	//real SkeletonAnimationNodeBase::calculateMaxTime(void) const
	//{
	//	real maxTime = REAL_MAX;
	//	BoneAnimationList::const_iterator bone_animation_iter = m_boneAnimationList.begin();
	//	for(; bone_animation_iter != m_boneAnimationList.end(); bone_animation_iter++)
	//	{
	//		if(bone_animation_iter->getMaxTime() > maxTime)
	//		{
	//			maxTime = bone_animation_iter->getMaxTime();
	//		}
	//	}
	//	return maxTime;
	//}

	//void SkeletonAnimationNode::setNextAnimationName(const std::basic_string<char> & nextAnimationName)
	//{
	//	m_nextAnimationName = nextAnimationName;
	//}

	//const std::basic_string<char> SkeletonAnimationNode::getNextAnimationName(void) const
	//{
	//	return m_nextAnimationName;
	//}

	//void SkeletonAnimationNode::setMinTime(real time)
	//{
	//	m_minTime = time;
	//}

	//real SkeletonAnimationNode::getMinTime(void) const
	//{
	//	return m_minTime;
	//}

	//void SkeletonAnimationNode::setMaxTime(real time)
	//{
	//	m_maxTime = time;
	//}

	//real SkeletonAnimationNode::getMaxTime(void) const
	//{
	//	return m_maxTime;
	//}

	//SkeletonAnimationNode::SkeletonAnimationNode(
	//	const std::basic_string<char> & nextAnimationName,
	//	real minTime,
	//	real maxTime)
	//	: m_nextAnimationName(nextAnimationName)
	//	, m_minTime(minTime)
	//	, m_maxTime(maxTime)
	//{
	//}

	//const char * SkeletonAnimation::tmpSkeletonAnimationNodeName = "__tmpSkeletonAnimationNodeName__";

	//void SkeletonAnimation::pushOrigBoneNode(t3d::BoneNodeList::const_reference origBoneNode)
	//{
	//	m_origBoneNodeList.push_back(origBoneNode);
	//}

	//void SkeletonAnimation::pushOrigBoneNodeList(t3d::BoneNodeList::const_iterator begin, t3d::BoneNodeList::const_iterator end)
	//{
	//	m_origBoneNodeList.insert(m_origBoneNodeList.end(), begin, end);
	//}

	//t3d::BoneNodeList::size_type SkeletonAnimation::getOrigBoneNodeListSize(void) const
	//{
	//	return m_origBoneNodeList.size();
	//}

	//void SkeletonAnimation::resizeOrigBoneNodeList(t3d::BoneNodeList::size_type size)
	//{
	//	m_origBoneNodeList.resize(size);
	//}

	//void SkeletonAnimation::clearOrigBoneNodeList(void)
	//{
	//	m_origBoneNodeList.clear();
	//}

	//t3d::BoneNodeList::reference SkeletonAnimation::origBoneNodeAt(t3d::BoneNodeList::size_type i)
	//{
	//	assert(i < getOrigBoneNodeListSize());

	//	return m_origBoneNodeList[i];
	//}

	//t3d::BoneNodeList::const_reference SkeletonAnimation::origBoneNodeAt(t3d::BoneNodeList::size_type i) const
	//{
	//	assert(i < getOrigBoneNodeListSize());

	//	return m_origBoneNodeList[i];
	//}

	//t3d::BoneNodeList & SkeletonAnimation::getOrigBoneNodeList(void)
	//{
	//	return m_origBoneNodeList;
	//}

	//const t3d::BoneNodeList & SkeletonAnimation::getOrigBoneNodeList(void) const
	//{
	//	return m_origBoneNodeList;
	//}

	//void SkeletonAnimation::pushOrigBoneInverseTransform(t3d::BoneTransformList::const_reference origBoneInverseTransform)
	//{
	//	m_origBoneInverseTransformList.push_back(origBoneInverseTransform);
	//}

	//void SkeletonAnimation::pushOrigBoneInverseTransformList(t3d::BoneTransformList::const_iterator begin, t3d::BoneTransformList::const_iterator end)
	//{
	//	m_origBoneInverseTransformList.insert(m_origBoneInverseTransformList.end(), begin, end);
	//}

	//t3d::BoneTransformList::size_type SkeletonAnimation::getOrigBoneInverseTransformListSize(void) const
	//{
	//	return m_origBoneInverseTransformList.size();
	//}

	//void SkeletonAnimation::resizeOrigBoneInverseTransformList(t3d::BoneTransformList::size_type size)
	//{
	//	m_origBoneInverseTransformList.resize(size);
	//}

	//void SkeletonAnimation::clearOrigBoneInverseTransformList(void)
	//{
	//	m_origBoneInverseTransformList.clear();
	//}

	//t3d::BoneTransformList::reference SkeletonAnimation::origBoneInverseTransformAt(t3d::BoneTransformList::size_type i)
	//{
	//	assert(i < getOrigBoneInverseTransformListSize());

	//	return m_origBoneInverseTransformList[i];
	//}

	//t3d::BoneTransformList::const_reference SkeletonAnimation::origBoneInverseTransformAt(t3d::BoneTransformList::size_type i) const
	//{
	//	assert(i < getOrigBoneInverseTransformListSize());

	//	return m_origBoneInverseTransformList[i];
	//}

	//t3d::BoneTransformList & SkeletonAnimation::getOrigBoneInverseTransformList(void)
	//{
	//	return m_origBoneInverseTransformList;
	//}

	//const t3d::BoneTransformList & SkeletonAnimation::getOrigBoneInverseTransformList(void) const
	//{
	//	return m_origBoneInverseTransformList;
	//}

	//void SkeletonAnimation::pushBoneNode(t3d::BoneNodeList::const_reference origBoneNode)
	//{
	//	m_boneNodeList.push_back(origBoneNode);
	//}

	//void SkeletonAnimation::pushBoneNodeList(t3d::BoneNodeList::const_iterator begin, t3d::BoneNodeList::const_iterator end)
	//{
	//	m_boneNodeList.insert(m_boneNodeList.end(), begin, end);
	//}

	//t3d::BoneNodeList::size_type SkeletonAnimation::getBoneNodeListSize(void) const
	//{
	//	return m_boneNodeList.size();
	//}

	//void SkeletonAnimation::resizeBoneNodeList(t3d::BoneNodeList::size_type size)
	//{
	//	m_boneNodeList.resize(size);
	//}

	//void SkeletonAnimation::clearBoneNodeList(void)
	//{
	//	m_boneNodeList.clear();
	//}

	//t3d::BoneNodeList::reference SkeletonAnimation::boneNodeAt(t3d::BoneNodeList::size_type i)
	//{
	//	assert(i < getBoneNodeListSize());

	//	return m_boneNodeList[i];
	//}

	//t3d::BoneNodeList::const_reference SkeletonAnimation::boneNodeAt(t3d::BoneNodeList::size_type i) const
	//{
	//	assert(i < getBoneNodeListSize());

	//	return m_boneNodeList[i];
	//}

	//t3d::BoneNodeList & SkeletonAnimation::getBoneNodeList(void)
	//{
	//	return m_boneNodeList;
	//}

	//const t3d::BoneNodeList & SkeletonAnimation::getBoneNodeList(void) const
	//{
	//	return m_boneNodeList;
	//}

	//void SkeletonAnimation::pushBoneTransform(t3d::BoneTransformList::const_reference boneTransform)
	//{
	//	m_boneTransformList.push_back(boneTransform);
	//}

	//void SkeletonAnimation::pushBoneTransformList(t3d::BoneTransformList::const_iterator begin, t3d::BoneTransformList::const_iterator end)
	//{
	//	m_boneTransformList.insert(m_boneTransformList.end(), begin, end);
	//}

	//t3d::BoneTransformList::size_type SkeletonAnimation::getBoneTransformListSize(void) const
	//{
	//	return m_boneTransformList.size();
	//}

	//void SkeletonAnimation::resizeBoneTransformList(t3d::BoneTransformList::size_type size)
	//{
	//	m_boneTransformList.resize(size);
	//}

	//void SkeletonAnimation::clearBoneTransformList(void)
	//{
	//	m_boneTransformList.clear();
	//}

	//t3d::BoneTransformList::reference SkeletonAnimation::boneTransformAt(t3d::BoneTransformList::size_type i)
	//{
	//	assert(i < getBoneTransformListSize());

	//	return m_boneTransformList[i];
	//}

	//t3d::BoneTransformList::const_reference SkeletonAnimation::boneTransformAt(t3d::BoneTransformList::size_type i) const
	//{
	//	assert(i < getBoneTransformListSize());

	//	return m_boneTransformList[i];
	//}

	//t3d::BoneTransformList & SkeletonAnimation::getBoneTransformList(void)
	//{
	//	return m_boneTransformList;
	//}

	//const t3d::BoneTransformList & SkeletonAnimation::getBoneTransformList(void) const
	//{
	//	return m_boneTransformList;
	//}

	//void SkeletonAnimation::setSkeletonAnimationNode(const std::basic_string<char> & animationName, const SkeletonAnimationNode & skeletonAnimationNode)
	//{
	//	assert(!isSkeletonAnimationNodeExistent(animationName));

	//	m_skeletonAnimationNodeMap.insert(SkeletonAnimationNodeMap::value_type(animationName, skeletonAnimationNode));
	//}

	//bool SkeletonAnimation::isSkeletonAnimationNodeExistent(const std::basic_string<char> & animationName) const
	//{
	//	return 0 != m_skeletonAnimationNodeMap.count(animationName);
	//}

	//SkeletonAnimationNode & SkeletonAnimation::getSkeletonAnimationNode(const std::basic_string<char> & animationName)
	//{
	//	assert(isSkeletonAnimationNodeExistent(animationName));

	//	return m_skeletonAnimationNodeMap.find(animationName)->second;
	//}

	//const SkeletonAnimationNode & SkeletonAnimation::getSkeletonAnimationNode(const std::basic_string<char> & animationName) const
	//{
	//	assert(isSkeletonAnimationNodeExistent(animationName));

	//	return m_skeletonAnimationNodeMap.find(animationName)->second;
	//}

	//void SkeletonAnimation::setCurrentAnimationName(const std::basic_string<char> & animationName)
	//{
	//	assert(isSkeletonAnimationNodeExistent(animationName));

	//	m_currentAnimationName = animationName;
	//}

	//const std::basic_string<char> SkeletonAnimation::getCurrentAnimationName(void) const
	//{
	//	assert(isSkeletonAnimationNodeExistent(m_currentAnimationName));

	//	return m_currentAnimationName;
	//}

	//void SkeletonAnimation::setCurrentAnimationTime(real time)
	//{
	//	assert(IS_VALID_FLOAT(time));

	//	m_currentAnimationTime = time;
	//}

	//real SkeletonAnimation::getCurrentAnimationTime(void) const
	//{
	//	assert(IS_VALID_FLOAT(m_currentAnimationTime));

	//	return m_currentAnimationTime;
	//}

	//const t3d::BoneNodeList & SkeletonAnimation::gotoAnimation(const std::basic_string<char> & animationName, real time)
	//{
	//	const SkeletonAnimationNode & skeletonAnimationNode = getSkeletonAnimationNode(animationName);

	//	if(time < skeletonAnimationNode.getMinTime())
	//	{
	//		assert(false);
	//	}

	//	if(time >= skeletonAnimationNode.getMaxTime())
	//	{
	//		return gotoAnimation(skeletonAnimationNode.getNextAnimationName(), time - skeletonAnimationNode.getMaxTime());
	//	}

	//	setCurrentAnimationName(animationName);

	//	setCurrentAnimationTime(time);

	//	return updateBoneNodeListFromBoneAnimationList(
	//		getBoneNodeList(),
	//		skeletonAnimationNode.getBoneAnimationList(),
	//		time);
	//}

	//const t3d::BoneNodeList & SkeletonAnimation::stepAnimation(const std::basic_string<char> & animationName, real duration, real tmpSkeletonAnimationTime /*= 0.1f*/)
	//{
	//	if(animationName != getCurrentAnimationName())
	//	{
	//		if(!isSkeletonAnimationNodeExistent(tmpSkeletonAnimationNodeName))
	//		{
	//			setSkeletonAnimationNode(tmpSkeletonAnimationNodeName, SkeletonAnimationNode(animationName, 0, tmpSkeletonAnimationTime));
	//		}

	//		const SkeletonAnimationNode & nextSkeletonAnimationNode = getSkeletonAnimationNode(animationName);

	//		const t3d::BoneNodeList & currBoneNodeList = getBoneNodeList();

	//		assert(nextSkeletonAnimationNode.getBoneAnimationListSize() == currBoneNodeList.size());

	//		SkeletonAnimationNode & tmpSkeletonAnimationNode = getSkeletonAnimationNode(tmpSkeletonAnimationNodeName);

	//		tmpSkeletonAnimationNode.clearBoneAnimationList();

	//		size_t i = 0;
	//		for(; i < getOrigBoneNodeListSize(); i++)
	//		{
	//			assert(nextSkeletonAnimationNode.boneAnimationAt(i).getBoneKeyFrameListSize() != 0);

	//			tmpSkeletonAnimationNode.pushBoneAnimation(BoneAnimation());

	//			BoneAnimation & boneAnimation = tmpSkeletonAnimationNode.boneAnimationAt(tmpSkeletonAnimationNode.getBoneAnimationListSize() - 1);

	//			boneAnimation.pushBoneKeyFrame(
	//				t3d::BoneKeyFrame(
	//					currBoneNodeList[i].getPosition(),
	//					currBoneNodeList[i].getOrientation(),
	//					0));

	//			boneAnimation.pushBoneKeyFrame(
	//				t3d::BoneKeyFrame(
	//					nextSkeletonAnimationNode.boneAnimationAt(i).boneKeyFrameAt(0).getPosition(),
	//					nextSkeletonAnimationNode.boneAnimationAt(i).boneKeyFrameAt(0).getOrientation(),
	//					tmpSkeletonAnimationTime));
	//		}

	//		tmpSkeletonAnimationNode.setNextAnimationName(animationName);

	//		return gotoAnimation(tmpSkeletonAnimationNodeName, duration);
	//	}

	//	return gotoAnimation(animationName, getCurrentAnimationTime() + duration);
	//}

	//const t3d::BoneTransformList & SkeletonAnimation::getCombinedVertexBoneTransformList(const t3d::BoneNodeList & boneNodeList)
	//{
	//	assert(getOrigBoneNodeListSize() < INT_MAX);

	//	t3d::BoneTransformList tmpBoneTransformList(getOrigBoneNodeListSize());
	//	size_t i = 0;
	//	for(; i < getOrigBoneNodeListSize(); i++)
	//	{
	//		if(origBoneNodeAt(i).isRoot())
	//		{
	//			t3d::updateBoneTransformListFromBoneNodeList(
	//				tmpBoneTransformList,
	//				boneNodeList,
	//				(int)i,
	//				my::Mat4<real>::IDENTITY,
	//				my::Mat4<real>::IDENTITY);
	//		}
	//	}

	//	return t3d::combineVertexBoneTransformList(
	//		getBoneTransformList(),
	//		getOrigBoneInverseTransformList(),
	//		tmpBoneTransformList);
	//}

	//const t3d::BoneTransformList & SkeletonAnimation::getCombinedVertexNormalBoneTransformList(const t3d::BoneNodeList & boneNodeList)
	//{
	//	assert(getOrigBoneNodeListSize() < INT_MAX);

	//	t3d::BoneTransformList tmpBoneTransformList(getOrigBoneNodeListSize());
	//	size_t i = 0;
	//	for(; i < getOrigBoneNodeListSize(); i++)
	//	{
	//		if(origBoneNodeAt(i).isRoot())
	//		{
	//			t3d::updateBoneTransformListFromBoneNodeList(
	//				tmpBoneTransformList,
	//				boneNodeList,
	//				(int)i,
	//				my::Mat4<real>::IDENTITY,
	//				my::Mat4<real>::IDENTITY);
	//		}
	//	}

	//	return t3d::combineVertexNormalBoneTransformList(
	//		getBoneTransformList(),
	//		getOrigBoneInverseTransformList(),
	//		tmpBoneTransformList);
	//}

	//const t3d::BoneTransformList & SkeletonAnimation::stepAnimationAndCombineVertexBoneTransformList(const std::basic_string<char> & animationName, real duration)
	//{
	//	return getCombinedVertexBoneTransformList(stepAnimation(animationName, duration));
	//}

	//const t3d::BoneTransformList & SkeletonAnimation::stepAnimationAndCombineVertexNormalBoneTransformList(const std::basic_string<char> & animationName, real duration)
	//{
	//	return getCombinedVertexNormalBoneTransformList(stepAnimation(animationName, duration));
	//}

	void SkeletonAnimation::pushBoneAnimationNode(t3d::BoneAnimationNodeList::const_reference boneAnimationNode)
	{
		m_boneAnimationNodeList.push_back(boneAnimationNode);
	}

	void SkeletonAnimation::pushBoneAnimationNodeList(t3d::BoneAnimationNodeList::const_iterator begin, t3d::BoneAnimationNodeList::const_iterator end)
	{
		m_boneAnimationNodeList.insert(getBoneAnimationNodeListEnd(), begin, end);
	}

	t3d::BoneAnimationNodeList::const_iterator SkeletonAnimation::getBoneAnimationNodeListBegin(void) const
	{
		return m_boneAnimationNodeList.begin();
	}

	t3d::BoneAnimationNodeList::iterator SkeletonAnimation::getBoneAnimationNodeListBegin(void)
	{
		return m_boneAnimationNodeList.begin();
	}

	t3d::BoneAnimationNodeList::const_iterator SkeletonAnimation::getBoneAnimationNodeListEnd(void) const
	{
		return m_boneAnimationNodeList.end();
	}

	t3d::BoneAnimationNodeList::iterator SkeletonAnimation::getBoneAnimationNodeListEnd(void)
	{
		return m_boneAnimationNodeList.end();
	}

	t3d::BoneAnimationNodeList::size_type SkeletonAnimation::getBoneAnimationNodeListSize(void) const
	{
		return m_boneAnimationNodeList.size();
	}

	void SkeletonAnimation::resizeBoneAnimationNodeList(t3d::BoneAnimationNodeList::size_type size)
	{
		m_boneAnimationNodeList.resize(size);
	}

	void SkeletonAnimation::clearBoneAnimationNodeList(void)
	{
		m_boneAnimationNodeList.clear();
	}

	t3d::BoneAnimationNodeList::const_reference SkeletonAnimation::boneAnimationNodeAt(t3d::BoneAnimationNodeList::size_type bone_i) const
	{
		assert(bone_i < getBoneAnimationNodeListSize());

		return m_boneAnimationNodeList[bone_i];
	}

	t3d::BoneAnimationNodeList::reference SkeletonAnimation::boneAnimationNodeAt(t3d::BoneAnimationNodeList::size_type bone_i)
	{
		assert(bone_i < getBoneAnimationNodeListSize());

		return m_boneAnimationNodeList[bone_i];
	}

	const t3d::BoneAnimationNodeList & SkeletonAnimation::getBoneAnimationNodeList(void) const
	{
		return m_boneAnimationNodeList;
	}

	t3d::BoneAnimationNodeList & SkeletonAnimation::getBoneAnimationNodeList(void)
	{
		return m_boneAnimationNodeList;
	}

	real SkeletonAnimation::getMinTime(void) const
	{
		return t3d::getBoneAnimationNodeListMinTime(m_boneAnimationNodeList);
	}

	real SkeletonAnimation::getMaxTime(void) const
	{
		return t3d::getBoneAnimationNodeListMaxTime(m_boneAnimationNodeList);
	}

	void SkeletonAnimation::setNextAnimationName(const std::basic_string<char> & nextAnimationName)
	{
		m_nextAnimationName = nextAnimationName;
	}

	const std::basic_string<char> & SkeletonAnimation::getNextAnimationName(void) const
	{
		return m_nextAnimationName;
	}

	void SkeletonAnimationManager::pushBoneNode(t3d::BoneNodeList::const_reference boneNode)
	{
		m_boneNodeList.push_back(boneNode);
	}

	void SkeletonAnimationManager::pushBoneNodeList(t3d::BoneNodeList::const_iterator begin, t3d::BoneNodeList::const_iterator end)
	{
		m_boneNodeList.insert(getBoneNodeListEnd(), begin, end);
	}

	t3d::BoneNodeList::const_iterator SkeletonAnimationManager::getBoneNodeListBegin(void) const
	{
		return m_boneNodeList.begin();
	}

	t3d::BoneNodeList::iterator SkeletonAnimationManager::getBoneNodeListBegin(void)
	{
		return m_boneNodeList.begin();
	}

	t3d::BoneNodeList::const_iterator SkeletonAnimationManager::getBoneNodeListEnd(void) const
	{
		return m_boneNodeList.end();
	}

	t3d::BoneNodeList::iterator SkeletonAnimationManager::getBoneNodeListEnd(void)
	{
		return m_boneNodeList.end();
	}

	t3d::BoneNodeList::size_type SkeletonAnimationManager::getBoneNodeListSize(void) const
	{
		return m_boneNodeList.size();
	}

	void SkeletonAnimationManager::resizeBoneNodeList(t3d::BoneNodeList::size_type size)
	{
		m_boneNodeList.resize(size);
	}

	void SkeletonAnimationManager::clearBoneNodeList(void)
	{
		m_boneNodeList.clear();
	}

	t3d::BoneNodeList::const_reference SkeletonAnimationManager::boneNodeAt(t3d::BoneNodeList::size_type bone_i) const
	{
		assert(bone_i < getBoneNodeListSize());

		return m_boneNodeList[bone_i];
	}

	t3d::BoneNodeList::reference SkeletonAnimationManager::boneNodeAt(t3d::BoneNodeList::size_type bone_i)
	{
		assert(bone_i < getBoneNodeListSize());

		return m_boneNodeList[bone_i];
	}

	const t3d::BoneNodeList & SkeletonAnimationManager::getBoneNodeList(void) const
	{
		return m_boneNodeList;
	}

	t3d::BoneNodeList & SkeletonAnimationManager::getBoneNodeList(void)
	{
		return m_boneNodeList;
	}

	void SkeletonAnimationManager::insertSkeletonAnimation(SkeletonAnimationMap::key_type animationName, const SkeletonAnimationMap::referent_type & skeletonAnimation)
	{
		assert(!isSkeletonAnimationExistent(animationName));

		m_skeletonAnimationMap.insert(SkeletonAnimationMap::value_type(animationName, skeletonAnimation));
	}

	bool SkeletonAnimationManager::isSkeletonAnimationExistent(SkeletonAnimationMap::key_type animationName) const
	{
		return m_skeletonAnimationMap.end() != m_skeletonAnimationMap.find(animationName);
	}

	const SkeletonAnimationMap::referent_type & SkeletonAnimationManager::getSkeletonAnimation(SkeletonAnimationMap::key_type animationName) const
	{
		assert(isSkeletonAnimationExistent(animationName));

		return m_skeletonAnimationMap.find(animationName)->second;
	}

	SkeletonAnimationMap::referent_type & SkeletonAnimationManager::getSkeletonAnimation(SkeletonAnimationMap::key_type animationName)
	{
		assert(isSkeletonAnimationExistent(animationName));

		return m_skeletonAnimationMap.find(animationName)->second;
	}

	SkeletonAnimationMap::const_iterator SkeletonAnimationManager::getSkeletonAnimationMapBegin(void) const
	{
		return m_skeletonAnimationMap.begin();
	}

	SkeletonAnimationMap::iterator SkeletonAnimationManager::getSkeletonAnimationMapBegin(void)
	{
		return m_skeletonAnimationMap.begin();
	}

	SkeletonAnimationMap::const_iterator SkeletonAnimationManager::getSkeletonAnimationMapEnd(void) const
	{
		return m_skeletonAnimationMap.end();
	}

	SkeletonAnimationMap::iterator SkeletonAnimationManager::getSkeletonAnimationMapEnd(void)
	{
		return m_skeletonAnimationMap.end();
	}

	SkeletonAnimationMap::size_type SkeletonAnimationManager::getSkeletonAnimationMapSize(void) const
	{
		return m_skeletonAnimationMap.size();
	}

	void SkeletonAnimationManager::clearSkeletonAnimationMap(void)
	{
		m_skeletonAnimationMap.clear();
	}

	void SkeletonAnimationManager::setCurrentAnimationName(const std::basic_string<char> & animationName)
	{
		m_currentAnimationName = animationName;
	}

	const std::basic_string<char> SkeletonAnimationManager::getCurrentAnimationName(void) const
	{
		return m_currentAnimationName;
	}

	void SkeletonAnimationManager::setCurrentAnimationTime(real time)
	{
		m_currentAnimationTime = time;
	}

	real SkeletonAnimationManager::getCurrentAnimationTime(void) const
	{
		return m_currentAnimationTime;
	}

	const t3d::BoneNodeList & SkeletonAnimationManager::gotoAnimation(const std::basic_string<char> & animationName, real time)
	{
		assert(isSkeletonAnimationExistent(animationName));

		SkeletonAnimation & skeletonAnimation = getSkeletonAnimation(animationName);

		assert(getBoneNodeListSize() == skeletonAnimation.getBoneAnimationNodeListSize());

		assert(time >= skeletonAnimation.getMinTime());

		if(time >= skeletonAnimation.getMaxTime())
		{
			return gotoAnimation(skeletonAnimation.getNextAnimationName(), time - skeletonAnimation.getMaxTime());
		}

		setCurrentAnimationName(animationName);

		setCurrentAnimationTime(time);

		size_t i = 0;
		for(; i < getBoneNodeListSize(); i++)
		{
			if(boneNodeAt(i).isRoot())
			{
				t3d::updateBoneNodeListFromBoneAnimationNodeList(
					getBoneNodeList(),
					skeletonAnimation.getBoneAnimationNodeList(),
					i,
					time);
			}
		}

		return getBoneNodeList();
	}
}
