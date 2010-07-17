
#include "stdafx.h"
#include "mySkeleton.h"
#include "myMath.h"

namespace my
{
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
		_ASSERT(bone_i < getBoneAnimationNodeListSize());

		return m_boneAnimationNodeList[bone_i];
	}

	t3d::BoneAnimationNodeList::reference SkeletonAnimation::boneAnimationNodeAt(t3d::BoneAnimationNodeList::size_type bone_i)
	{
		_ASSERT(bone_i < getBoneAnimationNodeListSize());

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

	t3d::BoneNodeList & SkeletonAnimation::gotoAnimation(t3d::BoneNodeList & boneNodeList, size_t root_i, real time)
	{
		_ASSERT(boneNodeList.size() == getBoneAnimationNodeListSize());
		_ASSERT(boneNodeList[root_i].getParent() == boneAnimationNodeAt(root_i).getParent());
		_ASSERT(boneNodeList[root_i].getChildList() == boneAnimationNodeAt(root_i).getChildList());

		t3d::updateBoneNodeListFromBoneAnimationNodeList(
			boneNodeList,
			getBoneAnimationNodeList(),
			root_i,
			time);

		return boneNodeList;
	}

	void SkeletonAnimationNode::setNextAnimationName(const std::basic_string<char> & nextAnimationName)
	{
		m_nextAnimationName = nextAnimationName;
	}

	const std::basic_string<char> & SkeletonAnimationNode::getNextAnimationName(void) const
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
		_ASSERT(bone_i < getBoneNodeListSize());

		return m_boneNodeList[bone_i];
	}

	t3d::BoneNodeList::reference SkeletonAnimationManager::boneNodeAt(t3d::BoneNodeList::size_type bone_i)
	{
		_ASSERT(bone_i < getBoneNodeListSize());

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

	void SkeletonAnimationManager::insertSkeletonAnimationNode(SkeletonAnimationMap::key_type animationName, const SkeletonAnimationMap::referent_type & skeletonAnimationNode)
	{
		_ASSERT(!isSkeletonAnimationNodeExistent(animationName));

		m_skeletonAnimationMap.insert(SkeletonAnimationMap::value_type(animationName, skeletonAnimationNode));
	}

	bool SkeletonAnimationManager::isSkeletonAnimationNodeExistent(SkeletonAnimationMap::key_type animationName) const
	{
		return m_skeletonAnimationMap.end() != m_skeletonAnimationMap.find(animationName);
	}

	const SkeletonAnimationMap::referent_type & SkeletonAnimationManager::getSkeletonAnimationNode(SkeletonAnimationMap::key_type animationName) const
	{
		_ASSERT(isSkeletonAnimationNodeExistent(animationName));

		return m_skeletonAnimationMap.find(animationName)->second;
	}

	SkeletonAnimationMap::referent_type & SkeletonAnimationManager::getSkeletonAnimationNode(SkeletonAnimationMap::key_type animationName)
	{
		_ASSERT(isSkeletonAnimationNodeExistent(animationName));

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

	const t3d::BoneNodeList & SkeletonAnimationManager::gotoAnimation(const std::basic_string<char> & animationName, size_t root_i, real time)
	{
		_ASSERT(isSkeletonAnimationNodeExistent(animationName));

		SkeletonAnimationNode & skeletonAnimationNode = getSkeletonAnimationNode(animationName);

		_ASSERT(getBoneNodeListSize() == skeletonAnimationNode.getBoneAnimationNodeListSize());

		_ASSERT(time >= skeletonAnimationNode.getMinTime());

		if(time >= skeletonAnimationNode.getMaxTime())
		{
			return gotoAnimation(skeletonAnimationNode.getNextAnimationName(), root_i, time - skeletonAnimationNode.getMaxTime());
		}

		setCurrentAnimationName(animationName);

		setCurrentAnimationTime(time);

		return skeletonAnimationNode.gotoAnimation(getBoneNodeList(), root_i, time);
	}
}
