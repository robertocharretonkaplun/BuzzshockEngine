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
    // Load SAQ


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

    //m_resourceManager->loadMesh("Data/Models/Primitives/sphere.obj");
    //tmpGO = m_resourceManager->getMesh("Data/Models/Primitives/sphere.obj");
  }

  void 
  buGameApp_UnitTest::onCreateGBuffer() {


    // Graphics API initializations
    auto& graphMan = g_graphicsAPI();
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
    //m_sysAudioAPI->playAudioResource(0, m_audioState);
  }


  void 
  buGameApp_UnitTest::onRender() {
    // Set Camera
    m_cameraManager.render();
    cbBonesTranform cbBonestransform;
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

    // Set Bones Transform constant buffer
    m_graphicsAPI->VSsetConstantBuffers(BonesTranform, 2, 1);
    // Set Vertex Shader
    m_graphicsAPI->setVertexShader(vertexShader);
    // Set the input layout
    m_graphicsAPI->setInputLayout(inputLayout);
    // Set Pixel shader
    m_graphicsAPI->setPixelhader(pixelShader);
    // Set samplers
    m_graphicsAPI->PSsetSamplers(sampler, 0, 1);
    // Update shader resource cubemap
    m_graphicsAPI->PSSetShaderResources(m_cubeMap, 4, 1);
  }
}
