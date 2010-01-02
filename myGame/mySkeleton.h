
#ifndef __MYSKELETON_H__
#define __MYSKELETON_H__

#include "myCommon.h"
#include <t3dlib7.h>
#include <map>

namespace my
{
	class SkeletonAnimation
	{
	public:
		t3d::BoneAnimationNodeList m_boneAnimationNodeList;

		std::basic_string<char> m_nextAnimationName;

	public:
		void pushBoneAnimationNode(t3d::BoneAnimationNodeList::const_reference boneAnimation);

		void pushBoneAnimationNodeList(t3d::BoneAnimationNodeList::const_iterator begin, t3d::BoneAnimationNodeList::const_iterator end);

		t3d::BoneAnimationNodeList::const_iterator getBoneAnimationNodeListBegin(void) const;

		t3d::BoneAnimationNodeList::iterator getBoneAnimationNodeListBegin(void);

		t3d::BoneAnimationNodeList::const_iterator getBoneAnimationNodeListEnd(void) const;

		t3d::BoneAnimationNodeList::iterator getBoneAnimationNodeListEnd(void);

		t3d::BoneAnimationNodeList::size_type getBoneAnimationNodeListSize(void) const;

		void resizeBoneAnimationNodeList(t3d::BoneAnimationNodeList::size_type size);

		void clearBoneAnimationNodeList(void);

		t3d::BoneAnimationNodeList::const_reference boneAnimationNodeAt(t3d::BoneAnimationNodeList::size_type bone_i) const;

		t3d::BoneAnimationNodeList::reference boneAnimationNodeAt(t3d::BoneAnimationNodeList::size_type bone_i);

		const t3d::BoneAnimationNodeList & getBoneAnimationNodeList(void) const;

		t3d::BoneAnimationNodeList & getBoneAnimationNodeList(void);

		real getMinTime(void) const;

		real getMaxTime(void) const;

		void setNextAnimationName(const std::basic_string<char> & nextAnimationName);

		const std::basic_string<char> & getNextAnimationName(void) const;
	};

	typedef std::map<std::basic_string<char>, SkeletonAnimation> SkeletonAnimationMap;

	class SkeletonAnimationManager
	{
	protected:
		t3d::BoneNodeList m_boneNodeList;

		SkeletonAnimationMap m_skeletonAnimationMap;

		std::basic_string<char> m_currentAnimationName;

		real m_currentAnimationTime;

	public:
		void pushBoneNode(t3d::BoneNodeList::const_reference boneNode);

		void pushBoneNodeList(t3d::BoneNodeList::const_iterator begin, t3d::BoneNodeList::const_iterator end);

		t3d::BoneNodeList::const_iterator getBoneNodeListBegin(void) const;

		t3d::BoneNodeList::iterator getBoneNodeListBegin(void);

		t3d::BoneNodeList::const_iterator getBoneNodeListEnd(void) const;

		t3d::BoneNodeList::iterator getBoneNodeListEnd(void);

		t3d::BoneNodeList::size_type getBoneNodeListSize(void) const;

		void resizeBoneNodeList(t3d::BoneNodeList::size_type size);

		void clearBoneNodeList(void);

		t3d::BoneNodeList::const_reference boneNodeAt(t3d::BoneNodeList::size_type bone_i) const;

		t3d::BoneNodeList::reference boneNodeAt(t3d::BoneNodeList::size_type bone_i);

		const t3d::BoneNodeList & getBoneNodeList(void) const;

		t3d::BoneNodeList & getBoneNodeList(void);

		void insertSkeletonAnimation(SkeletonAnimationMap::key_type animationName, const SkeletonAnimationMap::referent_type & skeletonAnimation);

		bool isSkeletonAnimationExistent(SkeletonAnimationMap::key_type animationName) const;

		const SkeletonAnimationMap::referent_type & getSkeletonAnimation(SkeletonAnimationMap::key_type animationName) const;

		SkeletonAnimationMap::referent_type & getSkeletonAnimation(SkeletonAnimationMap::key_type animationName);

		SkeletonAnimationMap::const_iterator getSkeletonAnimationMapBegin(void) const;

		SkeletonAnimationMap::iterator getSkeletonAnimationMapBegin(void);

		SkeletonAnimationMap::const_iterator getSkeletonAnimationMapEnd(void) const;

		SkeletonAnimationMap::iterator getSkeletonAnimationMapEnd(void);

		SkeletonAnimationMap::size_type getSkeletonAnimationMapSize(void) const;

		void clearSkeletonAnimationMap(void);

		void setCurrentAnimationName(const std::basic_string<char> & animationName);

		const std::basic_string<char> getCurrentAnimationName(void) const;

		void setCurrentAnimationTime(real time);

		real getCurrentAnimationTime(void) const;

	public:
		const t3d::BoneNodeList & gotoAnimation(const std::basic_string<char> & animationName, real time);
	};
}

#endif // __MYSKELETON_H__
