#include "sysRenderPipeline.h"

namespace buEngineSDK {
  void 
  sysRenderPipeline::onCreate() {
    auto& graphMan = g_graphicsAPI();
    graphMan.initialize(m_window, m_screenWidth, m_screenHeight);
    createTemporalPipeline();
    histogram.init();
    //m_userInterface.init(_window, graphMan.getDevice(), graphMan.getDeviceContext());
  }

  //void 
  //sysRenderPipeline::createGBuffer(float width, float height) {
  //  auto& graphMan = g_graphicsAPI();
  //  // Create backbuffer
  //  m_txBackBuffer_GB = graphMan.createTexture2D((int32)width,
  //    (int32)height,
  //    TextureType::BACKBUFFER,
  //    L"");
  //  // Create depth stencil texture
  //  m_txDepthStencil_GB = graphMan.createTexture2D((int32)width,
  //    (int32)height,
  //    TextureType::DEFAULT,
  //    L"");
  //  // Create depth stencil view
  //  m_depthStencilView_GB = graphMan.createDepthStencilView();
  //
  //  // Create viewport
  //  m_viewport_GB = graphMan.createViewport(width,
  //    height);
  //  graphMan.createDepthStencilView(m_txDepthStencil_GB, m_depthStencilView_GB);
  //  // Create the vertex shader
  //  WString shaderFileName = L"GBuffer.fx";
  //  m_vertexShader_GB = graphMan.createVertexShader(shaderFileName);
  //  // Create the input layout
  //  m_inputLayout_GB = graphMan.createInputLayout(m_vertexShader_GB,
  //    { "POSITION" , "TEXCOORD", "NORMAL", "TANGENT" });
  //  // Create the pixel shader
  //  m_pixelShader_GB = graphMan.createPixelShader(shaderFileName);
  //  // Create sampler
  //  m_sampler_GB = graphMan.createSampler();
  //  // Create rasterizer
  //}

  void 
  sysRenderPipeline::createTemporalPipeline() {
    auto& graphMan = g_graphicsAPI();

    m_txBackBuffer_tmp = graphMan.createTexture2D(m_screenWidth, 
                                          m_screenHeight, 
                                          TextureType::E::BACKBUFFER,
                                          L"");
    
    // Create depth stencil texture
    m_txDepthStencil_tmp = graphMan.createTexture2D(m_screenWidth, 
                                            m_screenHeight,
                                            TextureType::E::DEPTH_STENCIL,
                                            L"");
    
    // Create depth stencil View
    m_depthStencilView_tmp = graphMan.createDepthStencilView();
    
    // Create Viewport
    m_viewport_tmp = graphMan.createViewport((float)m_screenWidth, (float)m_screenHeight);
    
    graphMan.createDepthStencilView(m_txDepthStencil_tmp, m_depthStencilView_tmp);

    WString shaderFileName = L"Normal.fx";
    // Create Vertex Shader
    m_vertexShader_tmp = graphMan.createVertexShader(shaderFileName); // Put the entry point
    
    // Create input layout
    m_inputLayout_tmp = graphMan.createInputLayout(m_vertexShader_tmp, 
      { "POSITION" , "TEXCOORD", "NORMAL", "TANGENT", "BLENDINDICES", "BLENDWEIGHT"});
    
    // Create Pixel shader 
    m_pixelShader_tmp = graphMan.createPixelShader(shaderFileName);
    
    m_cameraManager.AddCamera("CameraTest");
    m_cameraManager.SetActiveCamera(0);
    
    BonesTranform = graphMan.createBuffer(sizeof(cbBonesTranform));
    // Create light
    m_light.init();
    
    // Create sampler
    m_sampler_tmp = graphMan.createSampler();
    
    m_cubeMap = graphMan.createTexture2D(m_screenWidth, 
                                         m_screenHeight, 
                                         TextureType::E::CUBE_MAP, 
                                         L"Data/Textures/galileo_cross.dds");
  }

  void
  sysRenderPipeline::onUpdate(float _deltaTime) {
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
    //lightPos = m_userInterface.setPosition();
    LB.LightPos = lightPos;
    LB.LightColor = LightColor;
    LB.surfColor = surfColor;
    LB.LightIntensity = constants;

    m_light.update(LB);
    
    //m_userInterface.update();
    histogram.drawUI("Histogram 1", "Red");

  }

  void 
  sysRenderPipeline::onRender() {
    auto& graphMan = g_graphicsAPI();
    // Set viewport
    graphMan.setViewport(m_viewport_tmp);
    // Set Render Targets
    graphMan.setRenderTargets(1, m_txBackBuffer_tmp, m_depthStencilView_tmp);
    // Clear the back buffer 
    graphMan.clearRenderTargetView(m_txBackBuffer_tmp, ClearColor);
    // Clear depth stencil view
    graphMan.clearDepthStencilView(m_depthStencilView_tmp,
                                         1, // D3D11_CLEAR_DEPTH
                                         1.0f,
                                         0);
    // Set Camera
    m_cameraManager.render();
    cbBonesTranform cbBonestransform;
    // Update light
    m_light.render();
    // Update Audio
    //m_audioTest.update();
    
    // Set Bones Transform constant buffer
    graphMan.VSsetConstantBuffers(BonesTranform, 2, 1);
    // Set Vertex Shader
    graphMan.setVertexShader(m_vertexShader_tmp);
    // Set the input layout
    graphMan.setInputLayout(m_inputLayout_tmp);
    // Set Pixel shader
    graphMan.setPixelhader(m_pixelShader_tmp);
    // Set samplers
    graphMan.PSsetSamplers(m_sampler_tmp, 0, 1);
    // Update shader resource cubemap
    graphMan.PSSetShaderResources(m_cubeMap, 4, 1);
   // m_userInterface.render();
  }

  void 
  sysRenderPipeline::onDestroy() {
    m_graphicsAPI->cleanUp();
    //m_sysAudioAPI.de;
    // Shutdown module
    buCoreGraphicsAPI::shutDown();
    //sysAudioAPI::shutDown();
    //delete graphicAPI;
    m_directXPlug.destroy();
    //m_audioPlug.destroy();
  }
  
  //buUI sysRenderPipeline::getUI()
  //{
  //  return m_userInterface;
  //}
}

