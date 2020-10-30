#include "buGameApp_UnitTest.h"
#include <buMath.h>

namespace buEngineSDK
{
  buGameApp_UnitTest::buGameApp_UnitTest() {
  }

  buGameApp_UnitTest::~buGameApp_UnitTest() {
  }

  void 
  buGameApp_UnitTest::onCreate() {
    // Initialize 
    auto& graphMan = g_graphicsAPI();
    WString shaderFileName = L"Normal.fx";
    // Create Vertex Shader
    vertexShader = graphMan.createVertexShader(shaderFileName); // Put the entry point

    // Create input layout
    inputLayout = graphMan.createInputLayout(vertexShader, 
      { "POSITION" , "TEXCOORD", "NORMAL", "TANGENT", "BLENDINDICES", "BLENDWEIGHT"});

    // Create Pixel shader 
    pixelShader = graphMan.createPixelShader(shaderFileName);
    
    m_cameraManager.AddCamera("CameraTest");
    m_cameraManager.SetActiveCamera(0);
    // Create Change Every Frame
    changeEveryFrame = graphMan.createBuffer(sizeof(CBChangesEveryFrame));

    BonesTranform = graphMan.createBuffer(sizeof(cbBonesTranform));
    
    // Create sampler
    sampler = graphMan.createSampler();

    m_cubeMap = graphMan.loadDDSFromFile(L"Data/Textures/galileo_cross.dds", m_screenWidth, m_screenHeight);

  }

  void 
  buGameApp_UnitTest::onDestroy() {
    m_graphicsAPI->cleanUp();
    // Shutdown module
    buCoreGraphicsAPI::shutDown();
    //delete graphicAPI;
    m_directXPlug.destroy();
  }

  void 
  buGameApp_UnitTest::onUpdate(float _deltaTime) {
    m_graphicsAPI->update();

    auto currModel = m_resourceManager->getModel();
    currModel->update(_deltaTime);

    // Initialize View matrix
    buVector3F Eye(m_eye[0], m_eye[1], m_eye[2]);
    buVector3F At(m_at[0], m_at[1], m_at[2]);
    buVector3F Up(m_up[0], m_up[1], m_up[2]);

    m_cameraManager.update(Eye, Up, At,
      buDegrees(45).getRadians(),
      static_cast<float>(m_screenWidth) /
      static_cast<float>(m_screenHeight),
      m_near,
      m_far);

    // Set View Direction
    buVector4F viewDir(Eye.x, Eye.y, Eye.z, 1.0f);
    cb.viewDirection = viewDir;
    buVector4F lightPos(m_lightPos, 0);
    cb.LightPos = lightPos; 
    buVector4F LightColor(m_LightColor, 0);
    cb.LightColor = LightColor;
    buVector4F surfColor(m_surfColor, 0);
    cb.surfColor = surfColor;
    buVector4F constants(m_constants[0], 0, 0, 0);
    cb.constants = constants;
    // Set Mesh transform
    buVector3F scale(m_Scale[0] * m_EngineScale, 
                     m_Scale[1] * m_EngineScale, 
                     m_Scale[2] * m_EngineScale);
    buVector3F rotation(m_Rotation[0], m_Rotation[1], m_Rotation[2]);
    if (m_isRotating) {
      m_angle += _deltaTime;
    }   

    buVector3F position(m_position[0], m_position[1], m_position[2]);
    
    m_meshTransform.update(position, rotation, scale, m_angle);
  }


  void 
  buGameApp_UnitTest::onRender() {
    m_cameraManager.render();
    cbBonesTranform cbBonestransform;
    auto currModel = m_resourceManager->getModel();

    if (-1 < currModel->m_currAnimation) {
      for (uint32 i = 0; i < currModel->m_bonesTransforms.size(); ++i) {
        cbBonestransform.boneTransform[i] = currModel->m_bonesTransforms[i];
      }
      m_graphicsAPI->updateSubresource(BonesTranform,
        0,
        nullptr,
        &cbBonestransform,
        0,
        0);
    }
    
    // Update variables that change once per frame
    auto goNum = m_resourceManager->getGameObjects().size();
    auto gameobjects = m_resourceManager->getGameObjects();
    
    cb.mWorld = m_meshTransform.m_world;

    m_graphicsAPI->updateSubresource(changeEveryFrame, 0, nullptr, &cb, 0, 0);
    // Set Vertex Shader
    m_graphicsAPI->setVertexShader(vertexShader);
    // Set change every frame constant buffers
    m_graphicsAPI->VSsetConstantBuffers(changeEveryFrame, 1, 1);
    // Set Bones Transform constant buffer
    m_graphicsAPI->VSsetConstantBuffers(BonesTranform, 2, 1);
    // Set the input layout
    m_graphicsAPI->setInputLayout(inputLayout);
    // Set Pixel shader
    m_graphicsAPI->setPixelhader(pixelShader);
    // Set change every frame buffer.
    m_graphicsAPI->PSsetConstantBuffers(changeEveryFrame, 1, 1);
    // Set samplers
    m_graphicsAPI->PSsetSamplers(sampler, 0, 1);

    auto meshNum = currModel->m_meshes.size();
    // Render the go
    for (uint32 currGO = 0; currGO < goNum; currGO++) {
      auto &currGameObject = gameobjects[currGO];
      gameobjects[val].m_isActive = m_renderObjects;
      gameobjects[val].m_isSelected = m_selectedObject;
      // Render if the go is active
      if (currGameObject.m_isActive) {
        for (uint32 i = 0; i < meshNum; ++i) {
          auto& currMesh = currModel->m_meshes[i];
          // Set Mesh texture
          for (uint32 j = 0; j < currModel->m_textures.size() ; j++) {
            auto& currTexture = currModel->m_textures[j];
            m_graphicsAPI->PSSetShaderResources(currTexture, j, 1);
          }
           m_graphicsAPI->PSSetShaderResources(m_cubeMap, 4, 1);
          // Set primitive topology
          m_graphicsAPI->setPrimitiveTopology(currMesh.m_topology);
          // Set vertex buffer
          m_graphicsAPI->setVertexBuffers(currModel->m_vertexBuffer);
          // Set Index buffer
          m_graphicsAPI->setIndexBuffer(currModel->m_indexBuffer, 
                                        Format::E::BU_FORMAT_R32_UINT,
                                        0);
          // Draw
          m_graphicsAPI->drawIndexed(currMesh.m_numIndices, currMesh.m_baseIndex, 0);
        }

      }
    }
  }
}
