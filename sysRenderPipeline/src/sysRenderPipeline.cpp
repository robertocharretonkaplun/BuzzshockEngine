#include "sysRenderPipeline.h"

namespace buEngineSDK {
  void sysRenderPipeline::init(float width, float height)
  {
  }

  void sysRenderPipeline::createGBuffer(float width, float height)
  {
    auto& graphMan = g_graphicsAPI();
    // Create backbuffer
    m_txBackBuffer_GB = graphMan.createTexture2D((int32)width,
      (int32)height,
      TextureType::BACKBUFFER,
      L"");
    // Create depth stencil texture
    m_txDepthStencil_GB = graphMan.createTexture2D((int32)width,
      (int32)height,
      TextureType::DEFAULT,
      L"");
    // Create depth stencil view
    m_depthStencilView_GB = graphMan.createDepthStencilView();

    // Create viewport
    m_viewport_GB = graphMan.createViewport(width,
      height);
    graphMan.createDepthStencilView(m_txDepthStencil_GB, m_depthStencilView_GB);
    // Create the vertex shader
    WString shaderFileName = L"GBuffer.fx";
    m_vertexShader_GB = graphMan.createVertexShader(shaderFileName);
    // Create the input layout
    m_inputLayout_GB = graphMan.createInputLayout(m_vertexShader_GB,
      { "POSITION" , "TEXCOORD", "NORMAL", "TANGENT" });
    // Create the pixel shader
    m_pixelShader_GB = graphMan.createPixelShader(shaderFileName);
    // Create sampler
    m_sampler_GB = graphMan.createSampler();
    // Create rasterizer
  }

  void sysRenderPipeline::createTemporalPipeline(float width, float height)
  {
  }

  void
  sysRenderPipeline::update() {

  }

  void 
  sysRenderPipeline::render() {

  }

  void 
  sysRenderPipeline::destroy() {

  }
}

