#include "buCoreModel.h"

namespace buEngineSDK {
  void 
  buCoreModel::update(const float& deltaTime) {

    if (-1 < m_currAnimation) {
      m_animationTime += deltaTime;
      float time_in_ticks = m_animationTime * 
                            m_scene->mAnimations[m_currAnimation]->mTicksPerSecond;
      float animation_time = fmod(time_in_ticks, 
                             (float)m_scene->mAnimations[m_currAnimation]->mDuration);

      // Animate the bones
      //boneTransform(animation_time);
      animator(animation_time);
    }
  }

  void
    buCoreModel::animator(const float& animationTime) {
    if (-1 < m_currAnimation) {
      boneTransform(animationTime);
      // Store the bone transforms
      for (uint32 i = 0; i < m_skeleton->m_numBones; ++i) {
        m_bonesTransforms[i] = m_skeleton->m_bonesInfo[i].transform;
      }
    }
  }

  void
  buCoreModel::boneTransform(const float& animationTime) {
    buMatrix4x4 identity = buMatrix4x4::IDENTITY;
    readNodeHierarchy(animationTime, m_scene->mRootNode, identity);
  }

  void
    buCoreModel::readNodeHierarchy(const float& p_animation_time,  void* p_node, const buMatrix4x4& parent_transform)
  {
    auto node = reinterpret_cast<aiNode*>(p_node);
    String node_name(node->mName.data);

    const aiAnimation* animation = m_scene->mAnimations[m_currAnimation];
    buMatrix4x4 node_transform;
    std::memcpy(&node_transform, &node->mTransformation, sizeof(buMatrix4x4));
    const aiNodeAnim* node_anim = findNodeAnim(animation, node_name);

    if (node_anim)
    {

      //scaling
      //aiVector3D scaling_vector = node_anim->mScalingKeys[2].mValue;
      buVector3F scaling_vector = calcInterpolatedScaling(p_animation_time, node_anim);
      buMatrix4x4 scaling_matr;
      scaling_matr.scaleMatrix(scaling_vector);
      //rotation
      //aiQuaternion rotate_quat = node_anim->mRotationKeys[2].mValue;
      buMatrix4x4 rotate_matr = calcInterpolatedRotation(p_animation_time, node_anim);
      //translation
      //aiVector3D translate_vector = node_anim->mPositionKeys[2].mValue;
      buVector3F translate_vector = calcInterpolatedPosition(p_animation_time, node_anim);
      buMatrix4x4 translate_matr;
      translate_matr.translateMatrix(translate_vector);

      node_transform = scaling_matr * rotate_matr * translate_matr;
    }
    buMatrix4x4 global_transform = parent_transform * node_transform;

    if (m_skeleton->m_bonesMap.find(node_name) != m_skeleton->m_bonesMap.end()) {// true if node_name exist in bone_mapping
      uint32 bone_index = m_skeleton->m_bonesMap[node_name];

      aiMatrix4x4 GTransform = m_scene-> mRootNode->mTransformation;
      GTransform.Transpose();
      GTransform.Inverse();

      buMatrix4x4 globalInversTransform;
     // std::memcpy(&globalInversTransform, &GTransform, sizeof(buMatrix4x4));

      m_skeleton->m_bonesInfo[bone_index].transform =
        globalInversTransform *
        global_transform *
        m_skeleton->m_bonesInfo[bone_index].offset;

    }

    for (uint32 i = 0; i < node->mNumChildren; ++i) {
      readNodeHierarchy(p_animation_time, node->mChildren[i], global_transform);
    }

  }

  const aiNodeAnim*
    buCoreModel::findNodeAnim(const aiAnimation* p_animation,
      const String& p_node_name) {
    // channel in animation contains aiNodeAnim (aiNodeAnim its transformation for bones)
    // numChannels == numBones
    for (uint32 i = 0; i < p_animation->mNumChannels; ++i) {
      const aiNodeAnim* node_anim = p_animation->mChannels[i];
      if (String(node_anim->mNodeName.data) == p_node_name) {
        return node_anim;
      }
    }
    return nullptr;
  }

  buVector3F
    buCoreModel::calcInterpolatedScaling(const float& p_animation_time,
      const aiNodeAnim* p_node_anim) {
    buVector3F scaling;
    if (p_node_anim->mNumScalingKeys == 1) {
      std::memcpy(&scaling, &p_node_anim->mScalingKeys[0].mValue, sizeof(buVector3F));
      return scaling;
    }

    uint32 scaling_index = findScaling(p_animation_time, p_node_anim);
    uint32 next_scaling_index = scaling_index + 1;
    BU_ASSERT(next_scaling_index < p_node_anim->mNumScalingKeys);
    float delta_time = (float)(p_node_anim->mScalingKeys[next_scaling_index].mTime -
      p_node_anim->mScalingKeys[scaling_index].mTime);

    float factor = (p_animation_time -
      (float)p_node_anim->mScalingKeys[scaling_index].mTime) /
      delta_time;
    BU_ASSERT(factor >= 0.0f && factor <= 1.0f);
    aiVector3D start = p_node_anim->mScalingKeys[scaling_index].mValue;
    aiVector3D end = p_node_anim->mScalingKeys[next_scaling_index].mValue;
    aiVector3D delta = end - start;
    aiVector3D lastScaling = start + factor * delta;
    std::memcpy(&scaling, &lastScaling, sizeof(buVector3F));   
    return scaling;

  }

  //*
  uint32
    buCoreModel::findScaling(const float& p_animation_time,
      const aiNodeAnim* p_node_anim) {
    for (uint32 i = 0; i < p_node_anim->mNumScalingKeys - 1; ++i) {
      if (p_animation_time < (float)p_node_anim->mScalingKeys[i + 1].mTime) {
        return i;
      }
    }

    BU_ASSERT(0);
    return 0;
  }

  buMatrix4x4
    buCoreModel::calcInterpolatedRotation(const float& p_animation_time,
      const aiNodeAnim* p_node_anim) {
    buMatrix4x4 final;
    buMatrix3x3 inter;
    if (p_node_anim->mNumRotationKeys == 1) {
      std::memcpy(&inter,
        &p_node_anim->mRotationKeys[0].mValue.GetMatrix(),
        sizeof(buMatrix3x3));
      final.to4x4(inter);
      return final;
    }


    uint32 rotation_index = findRotation(p_animation_time, p_node_anim);
    uint32 next_rotation_index = rotation_index + 1;
    BU_ASSERT(next_rotation_index < p_node_anim->mNumRotationKeys);

    float delta_time = (float)(p_node_anim->mRotationKeys[next_rotation_index].mTime -
      p_node_anim->mRotationKeys[rotation_index].mTime);

    float factor = (p_animation_time -
      (float)p_node_anim->mRotationKeys[rotation_index].mTime) /
      delta_time;

    BU_ASSERT(factor >= 0.0f && factor <= 1.0f);
    aiQuaternion start_quat = p_node_anim->mRotationKeys[rotation_index].mValue;
    aiQuaternion end_quat = p_node_anim->mRotationKeys[next_rotation_index].mValue;

    return nlerp(start_quat, end_quat, factor);
  }

  uint32
    buCoreModel::findRotation(const float& p_animation_time,
      const aiNodeAnim* p_node_anim) {
    for (uint32 i = 0; i < p_node_anim->mNumRotationKeys - 1; ++i) {
      if (p_animation_time < (float)p_node_anim->mRotationKeys[i + 1].mTime) {
        return i;
      }
    }

    BU_ASSERT(0);
    return 0;
  }

  buVector3F
    buCoreModel::calcInterpolatedPosition(const float& p_animation_time,
      const aiNodeAnim* p_node_anim) {
    buVector3F pos;
    if (p_node_anim->mNumPositionKeys == 1) {
      std::memcpy(&pos, &p_node_anim->mPositionKeys[0].mValue, sizeof(buVector3F));
      return pos;
    }

    uint32 position_index = findPosition(p_animation_time, p_node_anim);
    uint32 next_position_index = position_index + 1;
    BU_ASSERT(next_position_index < p_node_anim->mNumPositionKeys);
    float delta_time = (float)(p_node_anim->mPositionKeys[next_position_index].mTime -
      p_node_anim->mPositionKeys[position_index].mTime);
    float factor = (p_animation_time -
      (float)p_node_anim->mPositionKeys[position_index].mTime) /
      delta_time;
    BU_ASSERT(factor >= 0.0f && factor <= 1.0f);
    aiVector3D start = p_node_anim->mPositionKeys[position_index].mValue;
    aiVector3D end = p_node_anim->mPositionKeys[next_position_index].mValue;
    aiVector3D delta = end - start;
    aiVector3D final = start + factor * delta;
    std::memcpy(&pos, &final, sizeof(buVector3F));
    return pos;
  }

  uint32
    buCoreModel::findPosition(const float& p_animation_time,
      const aiNodeAnim* p_node_anim) {
    for (uint32 i = 0; i < p_node_anim->mNumPositionKeys - 1; ++i) {
      if (p_animation_time < (float)p_node_anim->mPositionKeys[i + 1].mTime) {
        return i;
      }
    }

    BU_ASSERT(0);
    return 0;
  }

  buMatrix4x4
    buCoreModel::nlerp(aiQuaternion a, aiQuaternion b, const float& blend) {
    //cout << a.w + a.x + a.y + a.z << endl;
    a.Normalize();
    b.Normalize();

    aiQuaternion result;
    float dot_product = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    float one_minus_blend = 1.0f - blend;

    if (dot_product < 0.0f) {
      result.x = a.x * one_minus_blend + blend * -b.x;
      result.y = a.y * one_minus_blend + blend * -b.y;
      result.z = a.z * one_minus_blend + blend * -b.z;
      result.w = a.w * one_minus_blend + blend * -b.w;
    }
    else {
      result.x = a.x * one_minus_blend + blend * b.x;
      result.y = a.y * one_minus_blend + blend * b.y;
      result.z = a.z * one_minus_blend + blend * b.z;
      result.w = a.w * one_minus_blend + blend * b.w;
    }
    result.Normalize();
    buMatrix3x3 temp;
    std::memcpy(&temp, &result.GetMatrix(), sizeof(buMatrix3x3));
    buMatrix4x4 final;
    final.to4x4(temp);
    final.transpose();
    return final;
  }
  
  
}