
#ifndef __MYSKELETON_H__
#define __MYSKELETON_H__

#include "myCommon.h"

#include "t3dlib7.h"

namespace my
{
	//class MYGAME_API BoneAnimation
	//{
	//protected:
	//	t3d::BoneKeyFrameList m_boneKeyFrameList;

	//public:
	//	void pushBoneKeyFrame(t3d::BoneKeyFrameList::const_reference boneKeyFrame);

	//	void pushBoneKeyFrameList(t3d::BoneKeyFrameList::const_iterator begin, t3d::BoneKeyFrameList::const_iterator end);

	//	t3d::BoneKeyFrameList::size_type getBoneKeyFrameListSize(void) const;

	//	void resizeBoneKeyFrameList(t3d::BoneKeyFrameList::size_type size);

	//	void clearBoneKeyFrameList(void);

	//	t3d::BoneKeyFrameList::reference boneKeyFrameAt(t3d::BoneKeyFrameList::size_type i);

	//	t3d::BoneKeyFrameList::const_reference boneKeyFrameAt(t3d::BoneKeyFrameList::size_type i) const;

	//	t3d::BoneKeyFrameList & getBoneKeyFrameList(void);

	//	const t3d::BoneKeyFrameList & getBoneKeyFrameList(void) const;

	//	real getMinTime(void) const;

	//	real getMaxTime(void) const;
	//};

	//typedef std::vector<BoneAnimation> BoneAnimationList;

	//MYGAME_API t3d::BoneNodeList & updateBoneNodeListFromBoneAnimationList(
	//	t3d::BoneNodeList & boneNodeList,
	//	const BoneAnimationList & boneAnimationList,
	//	real time);

	//class MYGAME_API SkeletonAnimationNodeBase
	//{
	//protected:
	//	BoneAnimationList m_boneAnimationList;

	//public:
	//	void pushBoneAnimation(BoneAnimationList::const_reference boneAnimation);

	//	void pushBoneAnimationList(BoneAnimationList::const_iterator begin, BoneAnimationList::const_iterator end);

	//	BoneAnimationList::size_type getBoneAnimationListSize(void) const;

	//	void resizeBoneAnimationList(BoneAnimationList::size_type size);

	//	void clearBoneAnimationList(void);

	//	BoneAnimationList::reference boneAnimationAt(BoneAnimationList::size_type i);

	//	BoneAnimationList::const_reference boneAnimationAt(BoneAnimationList::size_type i) const;

	//	BoneAnimationList & getBoneAnimationList(void);

	//	const BoneAnimationList & getBoneAnimationList(void) const;

	//	real calculateMinTime(void) const;

	//	real calculateMaxTime(void) const;
	//};

	//class MYGAME_API SkeletonAnimationNode : public SkeletonAnimationNodeBase
	//{
	//protected:
	//	std::basic_string<char> m_nextAnimationName;

	//	real m_minTime;

	//	real m_maxTime;

	//public:
	//	void setNextAnimationName(const std::basic_string<char> & nextAnimationName);

	//	const std::basic_string<char> getNextAnimationName(void) const;

	//	void setMinTime(real time);

	//	real getMinTime(void) const;

	//	void setMaxTime(real time);

	//	real getMaxTime(void) const;

	//	SkeletonAnimationNode(
	//		const std::basic_string<char> & nextAnimationName,
	//		real minTime,
	//		real maxTime);
	//};

	//typedef std::map<std::basic_string<char>, SkeletonAnimationNode> SkeletonAnimationNodeMap;

	//class MYGAME_API SkeletonAnimation
	//{
	//protected:
	//	t3d::BoneNodeList m_origBoneNodeList;

	//	t3d::BoneTransformList m_origBoneInverseTransformList;

	//	t3d::BoneNodeList m_boneNodeList;

	//	t3d::BoneTransformList m_boneTransformList;

	//	SkeletonAnimationNodeMap m_skeletonAnimationNodeMap;

	//	std::basic_string<char> m_currentAnimationName;

	//	real m_currentAnimationTime;

	//public:
	//	static const char * tmpSkeletonAnimationNodeName;

	//public:
	//	void pushOrigBoneNode(t3d::BoneNodeList::const_reference origBoneNode);

	//	void pushOrigBoneNodeList(t3d::BoneNodeList::const_iterator begin, t3d::BoneNodeList::const_iterator end);

	//	t3d::BoneNodeList::size_type getOrigBoneNodeListSize(void) const;

	//	void resizeOrigBoneNodeList(t3d::BoneNodeList::size_type size);

	//	void clearOrigBoneNodeList(void);

	//	t3d::BoneNodeList::reference origBoneNodeAt(t3d::BoneNodeList::size_type i);

	//	t3d::BoneNodeList::const_reference origBoneNodeAt(t3d::BoneNodeList::size_type i) const;

	//	t3d::BoneNodeList & getOrigBoneNodeList(void);

	//	const t3d::BoneNodeList & getOrigBoneNodeList(void) const;

	//	void pushOrigBoneInverseTransform(t3d::BoneTransformList::const_reference origBoneInverseTransform);

	//	void pushOrigBoneInverseTransformList(t3d::BoneTransformList::const_iterator begin, t3d::BoneTransformList::const_iterator end);

	//	t3d::BoneTransformList::size_type getOrigBoneInverseTransformListSize(void) const;

	//	void resizeOrigBoneInverseTransformList(t3d::BoneTransformList::size_type size);

	//	void clearOrigBoneInverseTransformList(void);

	//	t3d::BoneTransformList::reference origBoneInverseTransformAt(t3d::BoneTransformList::size_type i);

	//	t3d::BoneTransformList::const_reference origBoneInverseTransformAt(t3d::BoneTransformList::size_type i) const;

	//	t3d::BoneTransformList & getOrigBoneInverseTransformList(void);

	//	const t3d::BoneTransformList & getOrigBoneInverseTransformList(void) const;

	//	void pushBoneNode(t3d::BoneNodeList::const_reference origBoneNode);

	//	void pushBoneNodeList(t3d::BoneNodeList::const_iterator begin, t3d::BoneNodeList::const_iterator end);

	//	t3d::BoneNodeList::size_type getBoneNodeListSize(void) const;

	//	void resizeBoneNodeList(t3d::BoneNodeList::size_type size);

	//	void clearBoneNodeList(void);

	//	t3d::BoneNodeList::reference boneNodeAt(t3d::BoneNodeList::size_type i);

	//	t3d::BoneNodeList::const_reference boneNodeAt(t3d::BoneNodeList::size_type i) const;

	//	t3d::BoneNodeList & getBoneNodeList(void);

	//	const t3d::BoneNodeList & getBoneNodeList(void) const;

	//	void pushBoneTransform(t3d::BoneTransformList::const_reference boneTransform);

	//	void pushBoneTransformList(t3d::BoneTransformList::const_iterator begin, t3d::BoneTransformList::const_iterator end);

	//	t3d::BoneTransformList::size_type getBoneTransformListSize(void) const;

	//	void resizeBoneTransformList(t3d::BoneTransformList::size_type size);

	//	void clearBoneTransformList(void);

	//	t3d::BoneTransformList::reference boneTransformAt(t3d::BoneTransformList::size_type i);

	//	t3d::BoneTransformList::const_reference boneTransformAt(t3d::BoneTransformList::size_type i) const;

	//	t3d::BoneTransformList & getBoneTransformList(void);

	//	const t3d::BoneTransformList & getBoneTransformList(void) const;

	//	void setSkeletonAnimationNode(const std::basic_string<char> & animationName, const SkeletonAnimationNode & skeletonAnimationNode);

	//	bool isSkeletonAnimationNodeExistent(const std::basic_string<char> & animationName) const;

	//	SkeletonAnimationNode & getSkeletonAnimationNode(const std::basic_string<char> & animationName);

	//	const SkeletonAnimationNode & getSkeletonAnimationNode(const std::basic_string<char> & animationName) const;

	//	void setCurrentAnimationName(const std::basic_string<char> & animationName);

	//	const std::basic_string<char> getCurrentAnimationName(void) const;

	//	void setCurrentAnimationTime(real time);

	//	real getCurrentAnimationTime(void) const;

	//	const t3d::BoneNodeList & gotoAnimation(const std::basic_string<char> & animationName, real time);

	//	const t3d::BoneNodeList & stepAnimation(const std::basic_string<char> & animationName, real duration, real tmpSkeletonAnimationTime = 0.1f);

	//	const t3d::BoneTransformList & getCombinedVertexBoneTransformList(const t3d::BoneNodeList & boneNodeList);

	//	const t3d::BoneTransformList & getCombinedVertexNormalBoneTransformList(const t3d::BoneNodeList & boneNodeList);

	//	const t3d::BoneTransformList & stepAnimationAndCombineVertexBoneTransformList(const std::basic_string<char> & animationName, real duration);

	//	const t3d::BoneTransformList & stepAnimationAndCombineVertexNormalBoneTransformList(const std::basic_string<char> & animationName, real duration);
	//};

	class MYGAME_API SkeletonAnimation
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

	class MYGAME_API SkeletonAnimationManager
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
