
#ifndef __T3DLIB7_H__
#define __T3DLIB7_H__

#include "t3dcommon.h"

#include <vector>
#include "t3dlib4.h"
#include "t3dlib6.h"

namespace t3d
{
	typedef std::vector<size_t> BoneIndexList;

	class STreeNode
	{
	public:
		static const size_t invalid_i = SIZE_MAX;

	protected:
		size_t m_parent;

		BoneIndexList m_childs;

	public:
		bool isRoot(void) const;

		void setParent(size_t parent_i);

		size_t getParent(void) const;

		void pushChild(size_t child_i);

		void pushChildList(BoneIndexList::const_iterator begin, BoneIndexList::const_iterator end);

		BoneIndexList::size_type getChildListSize(void) const;

		BoneIndexList::reference childAt(BoneIndexList::size_type i);

		BoneIndexList::const_reference childAt(BoneIndexList::size_type i) const;

		BoneIndexList::iterator getChildListBegin(void);

		BoneIndexList::const_iterator getChildListBegin(void) const;

		BoneIndexList::iterator getChildListEnd(void);

		BoneIndexList::const_iterator getChildListEnd(void) const;

		BoneIndexList & getChildList(void);

		const BoneIndexList & getChildList(void) const;

		STreeNode(size_t parent_i = invalid_i);

	public:
		template <typename node_iter_type>
		static node_iter_type findRootNode(node_iter_type begin, node_iter_type end)
		{
			node_iter_type node_iter = begin;
			for(; node_iter != end; node_iter++)
			{
				if(node_iter->isRoot())
					return node_iter;
			}
			return end;
		}

		template <typename tree_list_type>
		static BoneIndexList getRootIndexList(tree_list_type list)
		{
			BoneIndexList indexList;
			size_t i = 0;
			for(; i < list.size(); i++)
			{
				if(list[i].isRoot())
					indexList.push_back(i);
			}
			return indexList;
		}
	};

	class Bone
	{
	protected:
		Vec4<real> m_pos;

		Quat<real> m_ori;

	public:
		void setPosition(const Vec4<real> & pos);

		const Vec4<real> & getPosition(void) const;

		void setOrientation(const Quat<real> & ori);

		const Quat<real> & getOrientation(void) const;

		Bone(void);

		Bone(
			const Vec4<real> & pos,
			const Quat<real> & ori);
	};

	Bone & incrementBone(
		Bone & bone,
		const Bone & bone0,
		const Bone & bone1);

	Bone & intersectBone(
		Bone & bone,
		const Bone & bone0,
		const Bone & bone1,
		real value0,
		real value1,
		real clipper);

	class BoneNode
		: public Bone
		, public STreeNode
	{
	public:
		BoneNode(void);

		BoneNode(
			const Vec4<real> & pos,
			const Quat<real> & ori,
			size_t parent_i = invalid_i);
	};

	typedef std::vector<BoneNode> BoneNodeList;

	BoneNodeList & incrementBoneNodeList(
		BoneNodeList & ret,
		const BoneNodeList & lhs,
		const BoneNodeList & rhs,
		size_t root_i);

	BoneNodeList & incrementBoneNodeList(
		BoneNodeList & ret,
		const BoneNodeList & lhs,
		const BoneNodeList & rhs,
		BoneIndexList::const_iterator begin,
		BoneIndexList::const_iterator end);

	BoneNodeList & intersectBoneNodeList(
		BoneNodeList & ret,
		const BoneNodeList & lhs,
		const BoneNodeList & rhs,
		real value0,
		real value1,
		real clipper,
		size_t root_i);

	BoneNodeList & intersectBoneNodeList(
		BoneNodeList & ret,
		const BoneNodeList & lhs,
		const BoneNodeList & rhs,
		real value0,
		real value1,
		real clipper,
		BoneIndexList::const_iterator begin,
		BoneIndexList::const_iterator end);

	class BoneKeyFrame : public Bone
	{
	protected:
		real m_time;

	public:
		void setTime(real time);

		real getTime(void) const;

		BoneKeyFrame(void);

		BoneKeyFrame(
			const Vec4<real> & pos,
			const Quat<real> & ori,
			real time);
	};

	Bone & intersectBoneKeyFrame(
		Bone & bone,
		const BoneKeyFrame & boneKeyFrame0,
		const BoneKeyFrame & boneKeyFrame1,
		real time);

	typedef std::vector<BoneKeyFrame> BoneKeyFrameList;

	real getBoneKeyFrameListMinTime(const BoneKeyFrameList & boneKeyFrameList);

	real getBoneKeyFrameListMaxTime(const BoneKeyFrameList & boneKeyFrameList);

	Bone & intersectBoneKeyFrameList(
		Bone & bone,
		const BoneKeyFrameList & boneKeyFrameList,
		real time);

	class BoneAnimation
	{
	protected:
		t3d::BoneKeyFrameList m_boneKeyFrameList;

	public:
		void pushBoneKeyFrame(t3d::BoneKeyFrameList::const_reference boneKeyFrame);

		void pushBoneKeyFrameList(t3d::BoneKeyFrameList::const_iterator begin, t3d::BoneKeyFrameList::const_iterator end);

		t3d::BoneKeyFrameList::size_type getBoneKeyFrameListSize(void) const;

		void resizeBoneKeyFrameList(t3d::BoneKeyFrameList::size_type size);

		void clearBoneKeyFrameList(void);

		t3d::BoneKeyFrameList::reference boneKeyFrameAt(t3d::BoneKeyFrameList::size_type i);

		t3d::BoneKeyFrameList::const_reference boneKeyFrameAt(t3d::BoneKeyFrameList::size_type i) const;

		t3d::BoneKeyFrameList & getBoneKeyFrameList(void);

		const t3d::BoneKeyFrameList & getBoneKeyFrameList(void) const;

		real getMinTime(void) const;

		real getMaxTime(void) const;
	};

	class BoneAnimationNode
		: public BoneAnimation
		, public STreeNode
	{
	public:
		BoneAnimationNode(size_t parent_i = invalid_i);
	};

	typedef std::vector<BoneAnimationNode> BoneAnimationNodeList;

	real getBoneAnimationNodeListMinTime(
		const BoneAnimationNodeList & boneAnimationNodeList);

	real getBoneAnimationNodeListMaxTime(
		const BoneAnimationNodeList & boneAnimationNodeList);

	BoneNodeList & updateBoneNodeListFromBoneAnimationNodeList(
		BoneNodeList & boneNodeList,
		const BoneAnimationNodeList & boneAnimationNodeList,
		size_t root_i,
		real time);

	class BoneTransform
	{
	protected:
		Mat4<real> m_mrot;

		Mat4<real> m_mmat;

	public:
		void setRotationTransform(const Mat4<real> & mrot);

		const Mat4<real> & getRotationTransform(void) const;

		void setTransform(const Mat4<real> & mmat);

		const Mat4<real> & getTransform(void) const;

		BoneTransform(void);

		BoneTransform(
			const Mat4<real> & mrot,
			const Mat4<real> & mmat);
	};

	typedef std::vector<BoneTransform> BoneTransformList;

	BoneTransform & updateBoneTransformFromBone(
		BoneTransform & boneTransform,
		const Bone & bone,
		const Mat4<real> & mrot,
		const Mat4<real> & mmat);

	BoneTransformList & updateBoneTransformListFromBoneNodeList(
		BoneTransformList & boneTransformList,
		const BoneNodeList & boneNodeList,
		const Mat4<real> & mrot,
		const Mat4<real> & mmat,
		size_t root_i);

	BoneTransformList & updateBoneTransformListFromBoneNodeList(
		BoneTransformList & boneTransformList,
		const BoneNodeList & boneNodeList,
		const Mat4<real> & mrot,
		const Mat4<real> & mmat,
		BoneIndexList::const_iterator begin,
		BoneIndexList::const_iterator end);

	BoneTransform & updateBoneInverseTransformFromBone(
		BoneTransform & inverseBoneTransform,
		const Bone & bone,
		const Mat4<real> & mInverseRot,
		const Mat4<real> & mInverseMat);

	BoneTransformList & updateBoneInverseTransformListFromBoneNodeList(
		BoneTransformList & inverseBoneTransformList,
		const BoneNodeList & boneNodeList,
		const Mat4<real> & mInverseRot,
		const Mat4<real> & mInverseMat,
		size_t root_i);

	BoneTransformList & updateBoneInverseTransformListFromBoneNodeList(
		BoneTransformList & inverseBoneTransformList,
		const BoneNodeList & boneNodeList,
		const Mat4<real> & mInverseRot,
		const Mat4<real> & mInverseMat,
		BoneIndexList::const_iterator begin,
		BoneIndexList::const_iterator end);

	BoneTransform & combineVertexBoneTransform(
		BoneTransform & res,
		const BoneTransform & lhs,
		const BoneTransform & rhs);

	BoneTransform & combineVertexNormalBoneTransform(
		BoneTransform & res,
		const BoneTransform & lhs,
		const BoneTransform & rhs);

	BoneTransformList & combineVertexBoneTransformList(
		BoneTransformList & res,
		const BoneTransformList & lhs,
		const BoneTransformList & rhs);

	BoneTransformList & combineVertexNormalBoneTransformList(
		BoneTransformList & res,
		const BoneTransformList & lhs,
		const BoneTransformList & rhs);

	class BoneAssignment
	{
	public:
		size_t vertex_i;
		size_t bone_i;
		real weight;

	public:
		BoneAssignment(
			size_t _vertex_i,
			size_t _bone_i,
			real _weight);
	};

	typedef std::vector<BoneAssignment> BoneAssignmentList;

	Vec4<real> buildVertexFromBoneTransform(
		const Vec4<real> & vertex,
		const BoneTransform & boneTransform,
		real weight);

	Vec4<real> buildNormalFromBoneTransform(
		const Vec4<real> & normal,
		const BoneTransform & boneTransform,
		real weight);

	void bindVertexListFromBoneTransformList(
		VertexList & vertexList,
		const VertexList & origVertexList,
		const BoneAssignmentList & boneAssignmentList,
		const BoneTransformList & boneTransformList);

	void bindVertexListNormalListFromBoneTransformList(
		VertexList & vertexList,
		NormalList & normalList,
		const VertexList & origVertexList,
		const NormalList & origNormalList,
		const BoneAssignmentList & boneAssignmentList,
		const BoneTransformList & boneTransformList);
}

#endif // __T3DLIB7_H__
