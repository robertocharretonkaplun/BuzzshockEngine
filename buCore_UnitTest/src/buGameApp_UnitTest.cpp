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
    auto& graphMan = g_graphicsAPI();

    // Initialize the GBuffer
   // WString GBufferFileName = L"GBuffer.fx";
   // m_gBufferVS = graphMan.createVertexShader(GBufferFileName); // Put the entry point
   // m_gBufferIL = graphMan.createInputLayout(m_gBufferVS,
   //   { "POSITION" , "TEXCOORD", "NORMAL", "TANGENT"});
   // m_gBufferPS = graphMan.createPixelShader(GBufferFileName);
   // PosTex = m_graphicsAPI->createTexture2D(m_screenWidth, m_screenHeight);
   // PosRT = m_graphicsAPI->createRenderTarget(PosTex);
   // AlbedoTex = m_graphicsAPI->createTexture2D(m_screenWidth, m_screenHeight);
   // AlbedoRT = m_graphicsAPI->createRenderTarget(AlbedoTex);
   // NormalTex = m_graphicsAPI->createTexture2D(m_screenWidth, m_screenHeight);
   // NormalRT = m_graphicsAPI->createRenderTarget(NormalTex);
   // MetallicTex = m_graphicsAPI->createTexture2D(m_screenWidth, m_screenHeight);
   // MetallicRT = m_graphicsAPI->createRenderTarget(MetallicTex);
   // RoughnessTex = m_graphicsAPI->createTexture2D(m_screenWidth, m_screenHeight);
   // RoughnessRT = m_graphicsAPI->createRenderTarget(RoughnessTex);

    // Initialize 
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

    BonesTranform = graphMan.createBuffer(sizeof(cbBonesTranform));
    // Create light
    m_light.init();

    // Create sampler
    sampler = graphMan.createSampler();

    m_cubeMap = graphMan.createTexture2D(m_screenWidth, 
                                         m_screenHeight, 
                                         TextureType::E::CUBE_MAP, 
                                         L"Data/Textures/galileo_cross.dds");

    //m_sysAudioAPI->createNewAudioResource("TestSound_Mono", AudioType::E::MONO);

    m_resourceManager->loadMesh("Data/Models/Primitives/sphere.obj");

  }

  void 
  buGameApp_UnitTest::onDestroy() {
    m_graphicsAPI->cleanUp();
    //m_sysAudioAPI.de;
    // Shutdown module
    buCoreGraphicsAPI::shutDown();
    sysAudioAPI::shutDown();
    //delete graphicAPI;
    m_directXPlug.destroy();
    m_audioPlug.destroy();
  }

  void 
  buGameApp_UnitTest::onUpdate(float _deltaTime) {
    m_graphicsAPI->update();

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
    // Update light
    buVector4F viewDir(Eye.x, Eye.y, Eye.z, 1.0f);
    buVector4F lightPos(m_lightPos, 0);
    buVector4F LightColor(m_LightColor, 0);
    buVector4F surfColor(m_surfColor, 0);
    buVector4F constants(m_constants[0], 0, 0, 0);
    LB.viewPosition = viewDir;
    LB.LightPos = lightPos;
    LB.LightColor = LightColor;
    LB.surfColor = surfColor;
    LB.LightIntensity = constants;
    
    m_light.update(LB);
    // Set Mesh transform
    buVector3F scale(m_Scale[0] * m_EngineScale, 
                     m_Scale[1] * m_EngineScale, 
                     m_Scale[2] * m_EngineScale);
    buVector3F rotation(m_Rotation[0], m_Rotation[1], m_Rotation[2]);
    if (m_isRotating) {
      m_angle += _deltaTime;
    }   

    buVector3F position(m_position[0], m_position[1], m_position[2]);
    
    //m_meshTransform.update(position, rotation, scale, m_angle);
    auto goNum = m_resourceManager->getGameObjects().size();
    auto gameobjects = m_resourceManager->getGameObjects();
    // Render the go
      gameobjects[0].update(buVector3F(lightPos.x, lightPos.y, lightPos.z), buVector3F::Zero, buVector3F(2,2,2), 0);
    if (goNum>=2) {
      gameobjects[val].update(position, rotation, scale, m_angle);
    }
    //m_sysAudioAPI->playAudioResource(0, m_audioState);
  }


  void 
  buGameApp_UnitTest::onRender() {

    m_cameraManager.render();
    cbBonesTranform cbBonestransform;
    auto goNum = m_resourceManager->getGameObjects().size();
    auto gameobjects = m_resourceManager->getGameObjects();
    //
    //if (-1 < currModel->m_currAnimation) {
    //  for (uint32 i = 0; i < currModel->m_bonesTransforms.size(); ++i) {
    //    cbBonestransform.boneTransform[i] = currModel->m_bonesTransforms[i];
    //  }
    //  m_graphicsAPI->updateSubresource(BonesTranform,
    //    0,
    //    nullptr,
    //    &cbBonestransform,
    //    0,
    //    0);
    //}
    
    // Update light
    m_light.render();
    // Update Audio
    //m_audioTest.update();
    // Update variables that change once per frame
    // Set Vertex Shader


    // Set Bones Transform constant buffer
    m_graphicsAPI->VSsetConstantBuffers(BonesTranform, 2, 1);
    m_graphicsAPI->setVertexShader(vertexShader);
    // Set the input layout
    m_graphicsAPI->setInputLayout(inputLayout);
    // Set Pixel shader
    m_graphicsAPI->setPixelhader(pixelShader);
    // Set samplers
    m_graphicsAPI->PSsetSamplers(sampler, 0, 1);
    // Update shader resource cubemap
    m_graphicsAPI->PSSetShaderResources(m_cubeMap, 4, 1);

    // Render the go
      gameobjects[0].render(TopologyType::E::BU_PRIMITIVE_TOPOLOGY_LINELIST);
    if (goNum >=2) {
      for (uint32 currGO = 1; currGO < goNum; currGO++) {
        gameobjects[currGO].render(TopologyType::E::BU_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
      }
    }
  }
}
