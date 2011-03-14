
#include "stdafx.h"
#include "t3dlib7.h"

namespace t3d
{
	Bone & incrementBone(
		Bone & bone,
		const Bone & bone0,
		const Bone & bone1)
	{
		bone.setPosition(
			vec3Add(bone0.getPosition(), bone1.getPosition()));

		bone.setOrientation(
			bone0.getOrientation() * bone1.getOrientation());

		return bone;
	}

	Bone & intersectBone(
		Bone & bone,
		const Bone & bone0,
		const Bone & bone1,
		real value0,
		real value1,
		real clipper)
	{
		bone.setPosition(
			vec3Intersect(
				bone0.getPosition(),
				bone1.getPosition(),
				value0,
				value1,
				clipper));

		bone.setOrientation(
			quatIntersect(
				bone0.getOrientation(),
				bone1.getOrientation(),
				value0,
				value1,
				clipper).normalize()); // ***

		return bone;
	}

	BoneNodeList & incrementBoneNodeList(
		BoneNodeList & ret,
		const BoneNodeList & lhs,
		const BoneNodeList & rhs,
		size_t root_i)
	{
		_ASSERT(ret.size() == lhs.size());
		_ASSERT(ret.size() == rhs.size());

		incrementBone(
			ret[root_i],
			lhs[root_i],
			rhs[root_i]);

		return incrementBoneNodeList(
			ret,
			lhs,
			rhs,
			ret[root_i].getChildListBegin(),
			ret[root_i].getChildListEnd());
	}

	BoneNodeList & incrementBoneNodeList(
		BoneNodeList & ret,
		const BoneNodeList & lhs,
		const BoneNodeList & rhs,
		BoneIndexList::const_iterator begin,
		BoneIndexList::const_iterator end)
	{
		_ASSERT(ret.size() == lhs.size());
		_ASSERT(ret.size() == rhs.size());

		BoneIndexList::const_iterator bone_index_iter = begin;
		for(; bone_index_iter != end; bone_index_iter++)
		{
			incrementBoneNodeList(
				ret,
				lhs,
				rhs,
				*bone_index_iter);
		}

		return ret;
	}

	BoneNodeList & intersectBoneNodeList(
		BoneNodeList & ret,
		const BoneNodeList & lhs,
		const BoneNodeList & rhs,
		real value0,
		real value1,
		real clipper,
		size_t root_i)
	{
		_ASSERT(ret.size() == lhs.size());
		_ASSERT(ret.size() == rhs.size());

		intersectBone(ret[root_i], lhs[root_i], rhs[root_i], value0, value1, clipper);

		return intersectBoneNodeList(
				ret,
				lhs,
				rhs,
				value0,
				value1,
				clipper,
				ret[root_i].getChildListBegin(),
				ret[root_i].getChildListEnd());
	}

	BoneNodeList & intersectBoneNodeList(
		BoneNodeList & ret,
		const BoneNodeList & lhs,
		const BoneNodeList & rhs,
		real value0,
		real value1,
		real clipper,
		BoneIndexList::const_iterator begin,
		BoneIndexList::const_iterator end)
	{
		_ASSERT(ret.size() == lhs.size());
		_ASSERT(ret.size() == rhs.size());

		BoneIndexList::const_iterator bone_index_iter = begin;
		for(; bone_index_iter != end; bone_index_iter++)
		{
			intersectBoneNodeList(
				ret,
				lhs,
				rhs,
				value0,
				value1,
				clipper,
				*bone_index_iter);
		}

		return ret;
	}

	Bone & intersectBoneKeyFrame(
		Bone & bone,
		const BoneKeyFrame & boneKeyFrame0,
		const BoneKeyFrame & boneKeyFrame1,
		real time)
	{
		return intersectBone(
			bone,
			boneKeyFrame0,
			boneKeyFrame1,
			boneKeyFrame0.getTime(),
			boneKeyFrame1.getTime(),
			time);
	}

	real getBoneKeyFrameListMinTime(const BoneKeyFrameList & boneKeyFrameList)
	{
		_ASSERT(boneKeyFrameList.size() > 0);

		return boneKeyFrameList.front().getTime();
	}

	real getBoneKeyFrameListMaxTime(const BoneKeyFrameList & boneKeyFrameList)
	{
		_ASSERT(boneKeyFrameList.size() > 0);

		return boneKeyFrameList.back().getTime();
	}

	Bone & intersectBoneKeyFrameList(
		Bone & bone,
		const BoneKeyFrameList & boneKeyFrameList,
		real time)
	{
		if(time < getBoneKeyFrameListMinTime(boneKeyFrameList))
		{
			return bone = boneKeyFrameList.front();
		}

		BoneKeyFrameList::const_iterator boneKeyFrame_iter = boneKeyFrameList.begin() + 1;
		for(; boneKeyFrame_iter != boneKeyFrameList.end(); boneKeyFrame_iter++)
		{
			if(time < boneKeyFrame_iter->getTime())
			{
				return intersectBoneKeyFrame(
					bone,
					*(boneKeyFrame_iter - 1),
					*(boneKeyFrame_iter - 0),
					time);
			}
		}

		_ASSERT(time >= getBoneKeyFrameListMaxTime(boneKeyFrameList));

		return bone = boneKeyFrameList.back();
	}

	real getBoneAnimationNodeListMinTime(
		const BoneAnimationNodeList & boneAnimationNodeList)
	{
		real minTime = REAL_MIN;
		BoneAnimationNodeList::const_iterator bone_anim_iter = boneAnimationNodeList.begin();
		for(; bone_anim_iter != boneAnimationNodeList.end(); bone_anim_iter++)
		{
			minTime = std::max(minTime, bone_anim_iter->getMinTime());
		}

		return minTime;
	}

	real getBoneAnimationNodeListMaxTime(
		const BoneAnimationNodeList & boneAnimationNodeList)
	{
		real maxTime = REAL_MAX;
		BoneAnimationNodeList::const_iterator bone_anim_iter = boneAnimationNodeList.begin();
		for(; bone_anim_iter != boneAnimationNodeList.end(); bone_anim_iter++)
		{
			maxTime = std::min(maxTime, bone_anim_iter->getMaxTime());
		}

		return maxTime;
	}

	BoneNodeList & buildBoneNodeListFromBoneAnimationNodeList(
		BoneNodeList & boneNodeList,
		const BoneAnimationNodeList & boneAnimationNodeList,
		size_t root_i,
		real time)
	{
		_ASSERT(boneNodeList.size() == boneAnimationNodeList.size());

		intersectBoneKeyFrameList(
			boneNodeList[root_i],
			boneAnimationNodeList[root_i].getBoneKeyFrameList(),
			time);

		BoneIndexList::const_iterator bone_index_iter = boneNodeList[root_i].getChildListBegin();
		for(; bone_index_iter != boneNodeList[root_i].getChildListEnd(); bone_index_iter++)
		{
			buildBoneNodeListFromBoneAnimationNodeList(
				boneNodeList,
				boneAnimationNodeList,
				*bone_index_iter,
				time);
		}

		return boneNodeList;
	}

	BoneTransform & buildBoneTransformFromBone(
		BoneTransform & boneTransform,
		const Bone & bone,
		const Mat4<real> & mParentRot,
		const Mat4<real> & mParentMat)
	{
		Mat4<real> mrot = buildRotationMatrixFromQuatLH(bone.getOrientation());

		boneTransform.setRotationTransform(mrot * mParentRot);

		boneTransform.setTransform(mrot * mat3Mov(bone.getPosition()) * mParentMat);

		return boneTransform;
	}

	BoneTransformList & buildBoneTransformListFromBoneNodeList(
		BoneTransformList & boneTransformList,
		const BoneNodeList & boneNodeList,
		const Mat4<real> & mParentRot,
		const Mat4<real> & mParentMat,
		size_t root_i)
	{
		_ASSERT(root_i < boneNodeList.size());

		_ASSERT(boneTransformList.size() == boneNodeList.size());

		buildBoneTransformFromBone(
			boneTransformList[root_i],
			boneNodeList[root_i],
			mParentRot,
			mParentMat);

		return buildBoneTransformListFromBoneNodeList(
			boneTransformList,
			boneNodeList,
			boneTransformList[root_i].getRotationTransform(),
			boneTransformList[root_i].getTransform(),
			boneNodeList[root_i].getChildListBegin(),
			boneNodeList[root_i].getChildListEnd());
	}

	BoneTransformList & buildBoneTransformListFromBoneNodeList(
		BoneTransformList & boneTransformList,
		const BoneNodeList & boneNodeList,
		const Mat4<real> & mParentRot,
		const Mat4<real> & mParentMat,
		BoneIndexList::const_iterator begin,
		BoneIndexList::const_iterator end)
	{
		_ASSERT(boneTransformList.size() == boneNodeList.size());

		BoneIndexList::const_iterator bone_index_iter = begin;
		for(; bone_index_iter != end; bone_index_iter++)
		{
			buildBoneTransformListFromBoneNodeList(
				boneTransformList,
				boneNodeList,
				mParentRot,
				mParentMat,
				*bone_index_iter);
		}

		return boneTransformList;
	}

	BoneTransform & buildBoneInverseTransformFromBone(
		BoneTransform & inverseBoneTransform,
		const Bone & bone,
		const Mat4<real> & mParentInverseRot,
		const Mat4<real> & mParentInverseMat)
	{
		Mat4<real> mrot = buildInverseRotationMatrixFromQuatLH(bone.getOrientation());

		inverseBoneTransform.setRotationTransform(mParentInverseRot * mrot);

		inverseBoneTransform.setTransform(mParentInverseMat * mat3InverseMov(bone.getPosition()) * mrot);

		return inverseBoneTransform;
	}

	BoneTransformList & buildBoneInverseTransformListFromBoneNodeList(
		BoneTransformList & inverseBoneTransformList,
		const BoneNodeList & boneNodeList,
		const Mat4<real> & mParentInverseRot,
		const Mat4<real> & mParentInverseMat,
		size_t root_i)
	{
		_ASSERT(root_i < boneNodeList.size());

		_ASSERT(inverseBoneTransformList.size() == boneNodeList.size());

		buildBoneInverseTransformFromBone(
			inverseBoneTransformList[root_i],
			boneNodeList[root_i],
			mParentInverseRot,
			mParentInverseMat);

		return buildBoneInverseTransformListFromBoneNodeList(
			inverseBoneTransformList,
			boneNodeList,
			inverseBoneTransformList[root_i].getRotationTransform(),
			inverseBoneTransformList[root_i].getTransform(),
			boneNodeList[root_i].getChildListBegin(),
			boneNodeList[root_i].getChildListEnd());
	}

	BoneTransformList & buildBoneInverseTransformListFromBoneNodeList(
		BoneTransformList & inverseBoneTransformList,
		const BoneNodeList & boneNodeList,
		const Mat4<real> & mParentInverseRot,
		const Mat4<real> & mParentInverseMat,
		BoneIndexList::const_iterator begin,
		BoneIndexList::const_iterator end)
	{
		_ASSERT(inverseBoneTransformList.size() == boneNodeList.size());

		BoneIndexList::const_iterator bone_index_iter = begin;
		for(; bone_index_iter != end; bone_index_iter++)
		{
			buildBoneInverseTransformListFromBoneNodeList(
				inverseBoneTransformList,
				boneNodeList,
				mParentInverseRot,
				mParentInverseMat,
				*bone_index_iter);
		}

		return inverseBoneTransformList;
	}

	BoneTransform & combineVertexBoneTransform(
		BoneTransform & res,
		const BoneTransform & lhs,
		const BoneTransform & rhs)
	{
		res.setTransform(lhs.getTransform() * rhs.getTransform());
		return res;
	}

	BoneTransform & combineVertexNormalBoneTransform(
		BoneTransform & res,
		const BoneTransform & lhs,
		const BoneTransform & rhs)
	{
		res.setTransform(lhs.getTransform() * rhs.getTransform());
		res.setRotationTransform(lhs.getRotationTransform() * rhs.getRotationTransform());
		return res;
	}

	BoneTransformList & combineVertexBoneTransformList(
		BoneTransformList & res,
		const BoneTransformList & lhs,
		const BoneTransformList & rhs)
	{
		_ASSERT(res.size() == lhs.size());
		_ASSERT(res.size() == rhs.size());

		for(size_t i = 0; i < lhs.size(); i++)
		{
			combineVertexBoneTransform(res[i], lhs[i], rhs[i]);
		}
		return res;
	}

	BoneTransformList & combineVertexNormalBoneTransformList(
		BoneTransformList & res,
		const BoneTransformList & lhs,
		const BoneTransformList & rhs)
	{
		_ASSERT(res.size() == lhs.size());
		_ASSERT(res.size() == rhs.size());

		for(size_t i = 0; i < lhs.size(); i++)
		{
			combineVertexNormalBoneTransform(res[i], lhs[i], rhs[i]);
		}
		return res;
	}

	Vec4<real> bindVertexFromBoneTransform(
		const Vec4<real> & vertex,
		const BoneTransform & boneTransform,
		real weight)
	{
		_ASSERT(weight <= 1);

		return vertex * boneTransform.getTransform() * weight;
	}

	Vec4<real> bindNormalFromBoneTransform(
		const Vec4<real> & normal,
		const BoneTransform & boneTransform,
		real weight)
	{
		_ASSERT(weight <= 1);

		return normal * boneTransform.getRotationTransform() * weight;
	}

	void bindVertexListFromBoneTransformList(
		VertexList & vertexList,
		const VertexList & origVertexList,
		const BoneAssignmentList & boneAssignmentList,
		const BoneTransformList & boneTransformList)
	{
		vertexList.clear();
		vertexList.resize(origVertexList.size(), Vec4<real>(0, 0, 0, 1));

		BoneAssignmentList::const_iterator assignment_iter = boneAssignmentList.begin();
		for(; assignment_iter != boneAssignmentList.end(); assignment_iter++)
		{
			_ASSERT(assignment_iter->vertex_i < origVertexList.size());

			_ASSERT(assignment_iter->bone_i < boneTransformList.size());

			vec3AddSelf(vertexList[assignment_iter->vertex_i],
				bindVertexFromBoneTransform(
					origVertexList[assignment_iter->vertex_i], boneTransformList[assignment_iter->bone_i], assignment_iter->weight));
		}
	}

	void bindVertexListNormalListFromBoneTransformList(
		VertexList & vertexList,
		NormalList & normalList,
		const VertexList & origVertexList,
		const NormalList & origNormalList,
		const BoneAssignmentList & boneAssignmentList,
		const BoneTransformList & boneTransformList)
	{
		_ASSERT(origVertexList.size() == origNormalList.size());

		vertexList.clear();
		vertexList.resize(origVertexList.size(), Vec4<real>(0, 0, 0, 1));

		normalList.clear();
		normalList.resize(origNormalList.size(), Vec4<real>(0, 0, 0, 1));

		BoneAssignmentList::const_iterator assignment_iter = boneAssignmentList.begin();
		for(; assignment_iter != boneAssignmentList.end(); assignment_iter++)
		{
			_ASSERT(assignment_iter->vertex_i < origVertexList.size());

			_ASSERT(assignment_iter->bone_i < boneTransformList.size());

			vec3AddSelf(vertexList[assignment_iter->vertex_i],
				bindVertexFromBoneTransform(
					origVertexList[assignment_iter->vertex_i], boneTransformList[assignment_iter->bone_i], assignment_iter->weight));

			vec3AddSelf(normalList[assignment_iter->vertex_i],
				bindNormalFromBoneTransform(
					origNormalList[assignment_iter->vertex_i], boneTransformList[assignment_iter->bone_i], assignment_iter->weight));
		}

		NormalList::iterator normal_iter = normalList.begin();
		for(; normal_iter != normalList.end(); normal_iter++)
		{
			vec3NormalizeSelf(*normal_iter);
		}
	}
}
