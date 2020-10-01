#include "buDXResourceManager.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include <assimp\include\assimp\scene.h>
#include <assimp\include\assimp\ai_assert.h>
#include <assimp\include\assimp\cimport.h>
#include <assimp\include\assimp\postprocess.h>
#include <assimp\include\assimp\Importer.hpp>
#include <assimp\include\assimp\material.h>
#include <buNumLimits.h>

namespace buEngineSDK {
  buDXResourceManager::buDXResourceManager()
  {
  }

  buDXResourceManager::~buDXResourceManager()
  {
  }

  void
    buDXResourceManager::loadMesh(String _filepath) {
    const aiScene* Model = aiImportFile(_filepath.c_str(),
      aiProcess_ConvertToLeftHanded |
      aiProcessPreset_TargetRealtime_Fast);
    m_model.TexName = Model->GetShortFilename(_filepath.c_str());

    m_model.m_meshes.reserve(Model->mNumMeshes);

    SkeletalMesh* skeleton = new SkeletalMesh;
    int32 highVertexNum = 0;
    for (uint32 i = 0; i < Model->mNumMeshes; ++i) {
      auto currMesh = Model->mMeshes[i];

      m_model.m_meshes.emplace_back();
      auto& tmpMesh = m_model.m_meshes[m_model.m_meshes.size() - 1];
      tmpMesh.m_topology = currMesh->mPrimitiveTypes;
      tmpMesh.m_baseVertex = m_model.m_vertices.size();
      tmpMesh.m_numVertex = currMesh->mNumVertices;
      tmpMesh.m_baseIndex = m_model.m_indices.size();
      tmpMesh.m_numIndices = currMesh->mNumFaces * 3;

      //Allocate the indices of the mesh
      for (uint32 j = 0; j < currMesh->mNumFaces; ++j) {
        auto& currFace = currMesh->mFaces[j];

        m_model.m_indices.push_back(tmpMesh.m_baseVertex + currFace.mIndices[0]);
        m_model.m_indices.push_back(tmpMesh.m_baseVertex + currFace.mIndices[1]);
        m_model.m_indices.push_back(tmpMesh.m_baseVertex + currFace.mIndices[2]);
      }

      for (uint32 j = 0; j < currMesh->mNumVertices; ++j) {
        auto fullVertex = currMesh->mVertices[j];

        m_model.m_vertices.emplace_back();
        auto& tmpvertex = m_model.m_vertices[m_model.m_vertices.size() - 1];

        //Allocate Vertices
        tmpvertex.Pos.x = fullVertex.x;
        tmpvertex.Pos.y = fullVertex.y;
        tmpvertex.Pos.z = fullVertex.z;

        //Allocate Texture Coordinates
        if (currMesh->HasTextureCoords(0)) {
          auto currTexCoord = currMesh->mTextureCoords[0][j];
          tmpvertex.Tex.x = currTexCoord.x;
          tmpvertex.Tex.y = currTexCoord.y;
        }
      }

      
      // Store Data for animations
      if (currMesh->HasBones()) {
        for (uint32 j = 0; j < currMesh->mNumBones; j++) {
          aiBone* currBone = currMesh->mBones[j];
          uint32 boneIndex = 0;
          String boneName(currBone->mName.data);

          if (skeleton->m_bonesMap.find(boneName) == skeleton->m_bonesMap.end()) {
            boneIndex = skeleton->m_numBones;
            skeleton->m_numBones++;
            Bone bone;
            skeleton->m_bonesInfo.push_back(bone);
          }
          else {
            boneIndex = skeleton->m_bonesMap[boneName];
          }

          skeleton->m_bonesMap[boneName] = boneIndex;
          std::memcpy(&skeleton->m_bonesInfo[boneIndex].offset,
            &currBone->mOffsetMatrix,
            sizeof(buMatrix4x4));
          

          // Store bone weights
          for (uint32 w = 0; w < currBone->mNumWeights; w++) {
            uint32 vertexID = tmpMesh.m_baseVertex + currBone->mWeights[w].mVertexId;
            float weight = currBone->mWeights[w].mWeight;
            if (vertexID > highVertexNum) {
              highVertexNum = vertexID;
            }

            for (uint32 b = 0; b < 4; ++b) {
              if (NumericLimits::MAX_UINT32 == m_model.m_vertices[vertexID].boneIDs[b]) {
                m_model.m_vertices[vertexID].boneIDs[b] = boneIndex;
                m_model.m_vertices[vertexID].boneWeights[b] = weight;
              }
            }
          }
        }
      }
      else {
        for (uint32 j = 0; j < tmpMesh.m_numVertex; j++) {
          uint32 vertexID = tmpMesh.m_baseVertex + j;
          for (uint32 z = 0; z < 4; z++) {
            m_model.m_vertices[vertexID].boneIDs[z] = 0;
            m_model.m_vertices[vertexID].boneWeights[z] = 1;
          }
        }
      }
    }
    m_model.m_scene = Model;
    m_model.m_skeleton = skeleton;

    // Should be on the model loading 
    m_model.m_bonesTransforms.clear();
    m_model.m_bonesTransforms.resize(skeleton->m_numBones);

    


    if (0 < Model->mNumAnimations) {
      m_model.m_currAnimation = 0;
    }

    auto& graphMan = g_graphicsAPI();

    m_model.m_vertexBuffer = graphMan.createBuffer(sizeof(SimpleVertex) * m_model.m_vertices.size(),
      D3D11_BIND_VERTEX_BUFFER,
      sizeof(SimpleVertex),
      m_model.m_vertices.data());

    m_model.m_indexBuffer = graphMan.createBuffer(sizeof(uint32) * m_model.m_indices.size(),
      D3D11_BIND_INDEX_BUFFER,
      0,
      m_model.m_indices.data());
    m_model.m_meshIsLoaded = true;
  }

  buCoreModel*
    buDXResourceManager::getModel() {
    return &m_model;
  }

}
