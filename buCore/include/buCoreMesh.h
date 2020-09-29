/**
 * @file buCoreMesh.h 
 * @version 1.0
 * @date 05/08/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of providing virtual methods for the buDxMesh
 */
#pragma once
#include <buPrerequisitesCore.h>
#include <buCoreBuffer.h>
#include <buVector4F.h>
#include <buVector3F.h>
#include <buVector2F.h>
#include <buMatrix4x4.h>
#include <assimp\include\assimp\scene.h>

namespace buEngineSDK {
class buCoreModel;

	struct Bone {
		buMatrix4x4 offset = buMatrix4x4::ZERO;
		buMatrix4x4 transform = buMatrix4x4::IDENTITY;
	};

	struct SkeletalMesh {
		uint32 m_numBones = 0;
		Map<String, int32> m_bonesMap;
		Vector<Bone> m_bonesInfo;
	};

	class buCoreMesh {
	public:
		friend class buCoreModel;
		/**
		 * @brief Default Constructor 
		 */
		buCoreMesh() = default;
		/**
		 * @brief Default Destructor 
		 */
		~buCoreMesh() = default;
		/**
		 * @brief Method that creates the meshes from the model.
		 */
		void
		init();
		/**
		 * @brief 
		 */
		

	public:
		uint32 m_topology = 0;
		uint32 m_baseVertex = 0;
		uint32 m_numVertex = 0;
		uint32 m_baseIndex = 0;
		uint32 m_numIndices = 0;
		buCoreModel * m_model;
		Vector<buMatrix4x4> m_boneTransforms;
	};
}
