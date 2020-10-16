/**
 * @file buCoreModel
 * @version 1.0
 * @date 05/08/2020
 * @author RobertoCharreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of providing virtual methods for the buDXModel
 */
#pragma once
#include <buPrerequisitesCore.h>
#include <buCoreMesh.h>
#include <buVector4F.h>
#include <buVector3F.h>
#include <buVector2F.h>
#include <assimp\include\assimp\scene.h>
#include <buNumLimits.h>
#include <buMatrix3x3.h>

namespace buEngineSDK {
	//template<typename V>
	struct SimpleVertex {
		buVector3F Pos;
		buVector2F Tex;
		buVector3F Nor;
		buVector3F Tan;
		uint32 boneIDs[4] = { NumericLimits::MAX_UINT32, NumericLimits::MAX_UINT32, 
													NumericLimits::MAX_UINT32, NumericLimits::MAX_UINT32 };
		float boneWeights[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	};

	struct AnimationsData {
    String name = "Animation";
    float ticks_per_second = 0.0f;
  };

	class BU_CORE_EXPORT buCoreModel {
	public:
		/**
		 * @brief Default Constructor 
		 */
		buCoreModel() = default;

		/**
		 * @brief Default Destructor
		 */
		~buCoreModel() = default;

		/**
		 * @brief Method that creates the model 
		 */
		void 
		init(int32 numMeshes);

		/**
		 * @brief Method in charge of adding meshes to the vector
		 */
		void 
		addMesh(buCoreMesh mesh) {m_meshes.push_back(mesh);};

		void 
		update(const float & deltaTime);

		void 
		animator(const float& animationTime);

		void 
    boneTransform(const float& animationTime);

    void
    readNodeHierarchy(const float& p_animation_time, 
                       void* p_node,
                      const buMatrix4x4& parent_transform);

    const aiNodeAnim* 
    findNodeAnim(const aiAnimation* p_animation, const String& p_node_name);

    buVector3F
    calcInterpolatedScaling(const float& p_animation_time, const aiNodeAnim* p_node_anim);

    uint32
    findScaling(const float& p_animation_time, const aiNodeAnim* p_node_anim);

    buMatrix4x4
    calcInterpolatedRotation(const float& p_animation_time, const aiNodeAnim* p_node_anim);

    uint32
    findRotation(const float& p_animation_time, const aiNodeAnim* p_node_anim);

    buVector3F
    calcInterpolatedPosition(const float& p_animation_time, const aiNodeAnim* p_node_anim);

    uint32
    findPosition(const float& p_animation_time, const aiNodeAnim* p_node_anim);

    buMatrix4x4
    nlerp(aiQuaternion a, aiQuaternion b, const float& blend);
	public:
		/**
		 * @brief Meshes from the model.
		 */
		String TexName;
		Vector<buCoreMesh> m_meshes;
		Vector<SimpleVertex> m_vertices;
		Vector<uint32> m_indices;

		/**
		 * @brief 
		 */
		SPtr<buCoreBuffer> m_vertexBuffer;
		/**
		 * @brief 
		 */
		SPtr<buCoreBuffer> m_indexBuffer;

		SkeletalMesh* m_skeleton = nullptr;
		int32 m_currAnimation = -1;
		Vector<buMatrix4x4> m_bonesTransforms; // Eliminar
		const aiScene* m_scene = nullptr;
		float m_animationTime = 0.0f;
	};
}