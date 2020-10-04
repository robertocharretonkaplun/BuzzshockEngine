/**
 * @file buDXGraphicsAPI.h 
 * @version 
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once
#include <buCoreGraphicsAPI.h>
//#include <DDSTextureLoader.h> // External lib for loading textures
#include <buVector2F.h>
#include <buVector3F.h>
#include <buVector4F.h>
#include "buMatrix4x4.h"
#include "buDXViewport.h"
#include "buDXTexture2D.h"
#include "buDXSwapchain.h"
#include "buDXRenderTargetView.h"
#include "buDXVertexShader.h"
#include "buDXPixelShader.h"
#include "buDXInputLayout.h"
#include "buDXBuffer.h"
#include "buDXDepthStencilView.h"
#include "buDXSampler.h"
//#include "buDXImgui.h"
// Assimp


namespace buEngineSDK {
  struct SimpleVertex {
    buVector3F Pos;
    buVector2F Tex;
  };

  struct CBNeverChanges {
    buMatrix4x4 mView;
  };

  struct CBChangeOnResize {
    buMatrix4x4 mProjection;
  };

  struct CBChangesEveryFrame {
    buMatrix4x4 mWorld;
    buVector4F vMeshColor;
  };

 class buDXGraphicsAPI : public buCoreGraphicsAPI {
  public:
   
   buDXGraphicsAPI();
   ~buDXGraphicsAPI();
  
   /**
    * @brief Test method to check if the linking between libs works.
    */
   void
   testFunc() override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   void 
   cleanUp() override;
   
   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   void
   update() override;
   
   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   void 
   render(WeakSPtr<buCoreDepthStencilView> _depthStencilView, 
          WeakSPtr<buCoreRenderTargetView> _renderTargetView,
          WeakSPtr<buCoreVertexShader> _vertexShader,
          WeakSPtr<buCoreInputLayout> _inputLayout,
          WeakSPtr<buCorePixelShader> _pixelShader, 
          WeakSPtr<buCoreBuffer> _neverChanges, 
          WeakSPtr<buCoreBuffer> _changeOnResize, 
          WeakSPtr<buCoreBuffer> _ChangeEveryFrame,
          WeakSPtr<buCoreTexture2D> _meshTexture,
          WeakSPtr<buCoreSampler> _sampler) override;
   
   /**
    * @brief 
    */
   void 
   initialize(void* _window, uint32 _width, uint32 _height) override;
   
   /**
    * @brief 
    */
   bool 
   createDeviceAndSwapChain(void* _window) override;
   
   /**
    * @brief Method that creates the back buffer texture, this is a 
    * very specific method for his implementation.
    */
   bool 
   createTextureForBackBuffer(WeakSPtr<buCoreTexture2D> _backbuffer) override;

   /**
   * @brief
   * @param
   * @return
   * @bug
   */
   SPtr<buCoreViewport>
   createViewport(float width, float height, float minDepth,
                  float maxDepth, float topLeftX, float topLeftY) override;
   
   /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
   SPtr<buCoreTexture2D> 
   createTexture2D(int32 width, 
                   int32 height,
                   uint32 format,
                   uint32 bindflags,
                   uint32 miplevels) override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   SPtr<buCoreSwapchain>
   createSwapchain() override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   SPtr<buCoreRenderTargetView>
   createRenderTargetView() override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   SPtr<buCoreVertexShader>
   createVertexShader() override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   SPtr<buCorePixelShader>
   createPixelShader() override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   SPtr<buCoreInputLayout>
   createInputLayout() override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   SPtr<buCoreBuffer>
   createBuffer(uint32 byteWidth, 
                uint32 bindFlags,
                uint32 offset,
                void* bufferData) override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   SPtr<buCoreDepthStencilView>
   createDepthStencilView() override;

   /**
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   SPtr<buCoreSampler>
   createSampler() override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   void
   setVertexShader(WeakSPtr<buCoreVertexShader> _vertexShader) override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   void
   setInputLayout(WeakSPtr<buCoreInputLayout> _inputLayout) override;

   /**
    * @brief
    * @param
    * @return
    * @bug
    */
   void
   setPixelhader(WeakSPtr<buCorePixelShader> _pixelShader) override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   void 
   drawIndexed(uint32 _numVertices, 
               uint32 _startIndexLocation, 
               uint32 _baseVertexLocation) override;
   
   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   void
   present(uint32 _syncInterval, uint32 _flag) override;

   /**
    * @brief Method that creates the depth stencil texture from the 
    * graphics API.
    */
   bool 
   createDepthStencilView(WeakSPtr<buCoreTexture2D> _texture,
                          WeakSPtr<buCoreDepthStencilView> _depthStencilView) 
                          override;

   /**
    * @brief Method that creates the render target view.
    */
   bool
   createRenderTargetView(WeakSPtr<buCoreTexture2D> _texture, 
                          WeakSPtr<buCoreRenderTargetView> _renderTargetView)
   override;

   /**
    * @brief Method that creates the vertex shader.
    */
   bool 
   createVertexShader(WeakSPtr<buCoreVertexShader> _vertexShader) override;

   /**
    * @brief Method that creates the input layout.
    */
   bool
   createInputLayout(WeakSPtr<buCoreVertexShader> _vertexShader, 
                     WeakSPtr<buCoreInputLayout> _inputLayout) override;

   /**
    * @brief Method that creates the vertex shader.
    */
   bool
   createPixelShader(WeakSPtr<buCorePixelShader> _pixelShader) override;

   /**
    * @brief Method that creates the sampler state.
    */
   bool
   createSamplerState(WeakSPtr<buCoreSampler> _sampler) override;

   /**
    * @brief Method that creates a texture from a shader resource view;
    */
   bool 
   createShaderResourceView(WeakSPtr<buCoreTexture2D> _texture) override;
   
   /**
    * @brief Method in charge of setting the subresource data for the 
    * texture.
    */
   void 
   PSSetShaderResources(WeakSPtr<buCoreTexture2D> _texture,
                        uint32 _startSlot,
                        uint32 _numViews) override;

   /**
    * @brief Method in charge of loading a texture from file
    */
   SPtr<buCoreTexture2D>
   loadImageFromFile(String _filepath, int32 width, int32 height) override;

   SPtr<buCoreModelLoader>
   loadMesh(String _filepath) override;

   void 
   setShaderSubresource(WeakSPtr<buCoreTexture2D> texture) override;

   /**
    * @brief Method that sets the vertex buffers.
    */
   void
   setVertexBuffers(WeakSPtr<buCoreBuffer> _buffer) override;

   /**
    * @brief Method that sets the index buffers.
    */
   void
   setIndexBuffer(WeakSPtr<buCoreBuffer> _buffer, 
                  uint32 _format,
                  uint32 _offset) override;

   /*
    * @brief Method that sets the viewport.
    */
   void
   setViewport(WeakSPtr<buCoreViewport> _viewport) override;

   /**
    * @brief Method that sets the render target.
    */
   void
   setRenderTargets(int32 _numViews,
                    WeakSPtr<buCoreRenderTargetView> _renderTargetView,
                    WeakSPtr<buCoreDepthStencilView> _depthStencilView) override;

   /**
    * @brief Method that clears the render target view.
    */
   void
   clearRenderTargetView(WeakSPtr<buCoreRenderTargetView> _renderTargetView,
                         float _color[4]) override;

   /**
    * @brief Method that clears the depth stencil view.
    */
   void
   clearDepthStencilView(WeakSPtr<buCoreDepthStencilView> _depthStencilView, 
                         uint32 _clearFlags, 
                         float depth,
                         int32 stencil) override;

   /**
    * @brief Method that sets the primitive topology of the object.
    */
   void
   setPrimitiveTopology(uint32 _topology) override;

   /**
    * @brief Method that update the sub resource of a buffer.
    */
   void
   updateSubresource(WeakSPtr<buCoreBuffer> _buffer,
                     uint32 DstSubresource,
                     void *pDstBox,
                     void *pSrcData,
                     uint32 SrcRowPitch,
                     uint32 SrcDepthPitch) override;

   /**
    * @brief Method that sets the vertex constant buffer.
    */
   void
   VSsetConstantBuffers(WeakSPtr<buCoreBuffer> _buffer, 
                        uint32 _startSlot,    
                        uint32 _numBuffers) override;

   /**
    * @brief Method that sets the pixel constant buffer.
    */
   void
   PSsetConstantBuffers(WeakSPtr<buCoreBuffer> _buffer, 
                        uint32 _startSlot,    
                        uint32 _numBuffers) override;

   /**
    * @brief  Method that sets the sampler.
    */
   void
   PSsetSamplers(WeakSPtr<buCoreSampler> _sampler, 
                 uint32 _startSlot,
                 uint32 _numSamplers) override;

    /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   void*
   getDevice() override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   void*
   getDeviceContext() override;

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   void*
   getSwapchain() override;

   /**
    * @brief 
    */
   Vector<void*>
   getShaderResource() override;
  private:
   /**
    * @brief Device ID.
    */
   ID3D11Device* m_device = nullptr;
   
   /**
    * @brief Device Context ID.
    */
   ID3D11DeviceContext* m_deviceContext = nullptr;
   
   /**
    * @brief Swap Chain ID.
    */
   IDXGISwapChain* m_swapchain = nullptr;

   /**
    * @brief Member in charge of storing the screen width of the game.
    */
   uint32 m_width = 0;
   
   /**
    * @brief Member in charge of storing the screen height of the game.
    */
   uint32 m_height = 0;
   
   Vector<void*> m_ShaderResources;
};
 
 /** 
  * @brief Plugging exportation data method. 
  * @return Instance of DX.
  */
 extern "C" BU_PLUGIN_EXPORT buDXGraphicsAPI*
 createGraphicAPI() {
 	auto pDX = new buDXGraphicsAPI();
 	return pDX;
 }
}
