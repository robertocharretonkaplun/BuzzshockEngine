/**
 * @file buCoreGraphicsAPI.h 
 * @version 1.0
 * @date 25/06/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of the usage of the virtual functions of buDX_API
 * @bug None.
 */
#pragma once

#include <buPrerequisitesCore.h> 
#include <buModule.h>
#include <buCoreViewport.h>
#include <buCoreTexture2D.h>
#include <buCoreSwapchain.h>
#include <buCoreRenderTargetView.h>
#include <buCoreVertexShader.h>
#include <buCorePixelShader.h>
#include <buCoreInputLayout.h>
#include <buCoreBuffer.h>
#include <buCoreDepthStencilView.h>
#include <buCoreSampler.h>
#include <buCoreModelLoader.h>
#include <buCommons.h>
//#include <buImgui.h>
namespace buEngineSDK {

 class BU_CORE_EXPORT buCoreGraphicsAPI : public buModule<buCoreGraphicsAPI>
 {
  public:
  /**
   * @brief Default constructor
   */
  buCoreGraphicsAPI() = default;

  /**
   * @brief Destructor
   */
  ~buCoreGraphicsAPI() = default;

  /**
   * @brief Instances of this object.
   */
  FORCEINLINE void 
  setObject(buCoreGraphicsAPI* _api) {
    buCoreGraphicsAPI::_instance() = _api;
  }

  /** 
   * @brief Virtual method that works as a testing initialization for the plugin.
   */
  virtual void 
  testFunc() {}
 
  /** 
   * @brief Virtual method that clean the objects in the app.
   */
  virtual void 
  cleanUp() {};

  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  virtual void
  update() {};

  /** 
   * @brief Virtual method that draw the render data on screen. 
   * @param _depthStencilView Reference to a buCoreDepthStencilView object.
   * @param _renderTargetView Reference to a buCoreRenderTargetView object.
   * @param _vertexShader Reference to a buCoreVertexShader object.
   * @param _inputLayout Reference to a buCoreInputLayout object.
   * @param _pixelShader Reference to a buCorePixelShader object.
   * @param _neverChanges Reference to a buCoreBuffer object.
   * @param _changeOnResize Reference to a buCoreBuffer object.
   * @param _ChangeEveryFrame Reference to a buCoreBuffer object.
   * @param _meshTexture Reference to a buCoreTexture2D object.
   * @param _sampler Reference to a buCoreSampler object.
   */
  virtual void 
  render(WeakSPtr<buCoreDepthStencilView> /*_depthStencilView*/, 
         WeakSPtr<buCoreRenderTargetView> /*_renderTargetView*/,
         WeakSPtr<buCoreVertexShader> /*_vertexShader*/,
         WeakSPtr<buCoreInputLayout> /*_inputLayout*/,
         WeakSPtr<buCorePixelShader> /*_pixelShader*/,
         WeakSPtr<buCoreBuffer> /*_neverChanges*/,
         WeakSPtr<buCoreBuffer> /*_changeOnResize*/,
         WeakSPtr<buCoreBuffer> /*_ChangeEveryFrame*/,
         WeakSPtr<buCoreTexture2D> /*_meshTexture*/,
         WeakSPtr<buCoreSampler> /*_sampler*/) {};

  /**
   * @brief 
   */
  virtual void 
  initialize(void* /*_window*/, uint32 /*_width*/, uint32 /*_height*/) {};

  /**
   * @brief 
   */
  virtual bool 
  createDeviceAndSwapChain(void* /*_window*/) { return false; };

  /** 
   * @brief Virtual method that creates a temporal reference to a viewport object.
   * @return A smart pointer to the object.
   */
  virtual SPtr<buCoreViewport>
  createViewport(float /*width*/, float /*height*/) { return nullptr; }

  /**
   * @brief Virtual method that creates a temporal reference to a texture2D object.
   * @return A smart pointer to the object.
   */
  virtual SPtr<buCoreTexture2D>
  createTexture2D(int32 /*width*/, int32 /*height*/, TextureType::E _textureType, WString _filename) { return nullptr; };
  
  virtual SPtr<buCoreTexture2D>
  createTexture2D(int32 /*width*/, int32 /*height*/, uint32, uint32, uint32) { return nullptr; };

  /**
   * @brief Virtual method that creates a temporal reference to a swap chain object.
   * @return A smart pointer to the object.
   */
  virtual SPtr<buCoreSwapchain>
  createSwapchain() { return nullptr; };

  /**
   * @brief Virtual method that creates a temporal reference to a vertex shader object.
   * @return A smart pointer to the object.
   */
  virtual SPtr<buCoreVertexShader>
  createVertexShader(WString _fileName) { return nullptr; };

  /** 
    * @brief Virtual method that creates a temporal reference to a pixel shader object.
    * @return A smart pointer to the object.
    */
  virtual SPtr<buCorePixelShader>
  createPixelShader(WString _fileName) { return nullptr; };

  /**
   * @brief Virtual method that creates a temporal reference to a 
   * input layout object.
   * @return A smart pointer object.
   */
  virtual SPtr<buCoreInputLayout>
  createInputLayout(WeakSPtr<buCoreVertexShader> _vertexShader, 
                    Vector<String> _semanticNames) { return nullptr; };

  /** 
    * @brief Virtual method that creates a temporal reference to a buffer object.
    * @return A smart pointer object.
    */
   virtual SPtr<buCoreBuffer>
   createBuffer(uint32 /*byteWidth*/, 
                uint32 /*bindFlags*/,
                uint32 /*offset*/,
                void* /*bufferData*/ ) { return nullptr; };
   /**
    * @brief Virtual method that creates a temporal reference to a const buffer object. 
    */
   virtual SPtr<buCoreBuffer>
   createBuffer(uint32 /*byteWidth*/) { return nullptr; };

   /** 
    * @brief Virtual method that creates a temporal reference to a depth stencil
    * view object.
    * @return A smart pointer object.
    */
   virtual SPtr<buCoreDepthStencilView>
   createDepthStencilView() { return nullptr; };

   /**
    * @brief Virtual method that creates a temporal reference to a sampler object.
    * @return A smart pointer object
    * @bug 
    */
   virtual SPtr<buCoreSampler>
   createSampler() { return nullptr; };

   /**
    * @brief Virtual method that creates a texture from a shader resource view;
    */
   virtual bool
   createShaderResourceView(WeakSPtr<buCoreTexture2D> /*_texture*/) { return false; };

   /**
    * @brief Virtual method in charge of loading a texture from file
    */
   virtual SPtr<buCoreTexture2D>
   loadImageFromFile(String /*_filepath*/, 
                     int32 /*width*/,
                     int32 /*height*/, 
                     TextureType::E textureType) { return nullptr; };
   
   virtual SPtr<buCoreModelLoader>
   loadMesh(String _filepath) {return nullptr;};

   virtual void 
   setShaderSubresource(WeakSPtr<buCoreTexture2D>) { };

   /**
    * @brief Virtual method in charge of setting the subresource data for the 
    * texture.
    */
   virtual void 
   PSSetShaderResources(WeakSPtr<buCoreTexture2D> /*_texture*/,
                        uint32 /*_startSlot*/,
                        uint32 /*_numViews*/) {};
   /** 
    * @brief Virtual method that creates a temporal reference to a vertex shader 
    * object. 
    * @return A smart pointer object.
    */
   virtual void
   setVertexShader(WeakSPtr<buCoreVertexShader> /*_vertexShader*/) {};

   /** 
    * @brief Virtual method that creates a temporal reference to a input layout 
    * object.
    * @return A smart pointer object.
    */
   virtual void
   setInputLayout(WeakSPtr<buCoreInputLayout> /*_inputLayout*/) {};

   /**
    * @brief Virtual method that creates a temporal reference to a pixel shader
    * object.
    * @return A smart pointer object.
    */
   virtual void
   setPixelhader(WeakSPtr<buCorePixelShader> /*_pixelShader*/) {};

   /** 
    * @brief Virtual method that draw the vertex or index data.
    * @param _numVertices Vertex or index amount.
    */
   virtual void 
   drawIndexed(uint32 /*_numVertices*/, 
               uint32 /*_startIndexLocation*/, 
               uint32 /*_baseVertexLocation*/) { };
      
   /**
    * @brief Virtual method that creates the depth stencil texture from the 
    * graphics API.
    */
   virtual bool 
   createDepthStencilView(WeakSPtr<buCoreTexture2D> /*_texture*/,
                          WeakSPtr<buCoreDepthStencilView> /*_depthStencilView*/) 
                          { return false; }

   /**
    * @brief Virtual method that creates the vertex shader.
    */
   virtual bool 
   createVertexShader(WeakSPtr<buCoreVertexShader> /*_vertexShader*/) { return false;}

   /**
    * @brief Virtual method that creates the input layout.
    */
   virtual bool
   createInputLayout(WeakSPtr<buCoreVertexShader> /*_vertexShader*/, 
                     WeakSPtr<buCoreInputLayout> /*_inputLayout*/) { return false; }
   
   /**
    * @brief Virtual method that creates the vertex shader.
    */
   virtual bool
   createPixelShader(WeakSPtr<buCorePixelShader> /*_pixelShader*/) { return false;}

   /**
    * @brief Virtual Method that creates the sampler state.
    */
   virtual bool
   createSamplerState(WeakSPtr<buCoreSampler> /*_sampler*/) { return false;};

   /**
    * @brief Virtual method that sets the vertex buffers.
    */
   virtual void
   setVertexBuffers(WeakSPtr<buCoreBuffer> /*_buffer*/) { };
   
   /**
    * @brief Virtual method that sets the index buffers.
    */
   virtual void
   setIndexBuffer(WeakSPtr<buCoreBuffer> /*_buffer*/,
                  uint32 /*_format*/,
                  uint32 /*_offset*/) { };
      
   /*
    * @brief Virtual method that sets the viewport
    */
   virtual void 
   setViewport(WeakSPtr<buCoreViewport> /*_viewport*/) { }

   /**
    * @brief Virtual method that sets the render target
    */
   virtual void
   setRenderTargets(int32 /*_numViews*/,
                    WeakSPtr<buCoreTexture2D> /*_renderTargetView*/,
                    WeakSPtr<buCoreDepthStencilView> /*_depthStencilView*/) { };

   /**
    * @brief Virtual method that clears the render target view.
    */
   virtual void
   clearRenderTargetView(WeakSPtr<buCoreTexture2D> /*_renderTargetView*/,
                         float /*_color*/[4]) { };

   /**
    * @brief Virtual method that clears the depth stencil view.
    */
   virtual void
   clearDepthStencilView(WeakSPtr<buCoreDepthStencilView> /*_depthStencilView*/, 
                         uint32 /*_clearFlags*/, 
                         float /*depth*/,
                         int32 /*stencil*/) { };

   /**
    * @brief Method that sets the primitive topology of the object.
    */
   virtual void
   setPrimitiveTopology(uint32 /*_topology*/) { };

   /**
    * @brief Virtual method that update the subresource of a buffer
    */
   virtual void
   updateSubresource(WeakSPtr<buCoreBuffer> /*_buffer*/,
                     uint32 /*DstSubresource*/,
                     void* /*pDstBox*/,
                     void* /*pSrcData*/,
                     uint32 /*SrcRowPitch*/,
                     uint32 /*SrcDepthPitch*/) {};

   /**
    * @brief Virtual method that sets the constant buffer.
    */
   virtual void
   VSsetConstantBuffers(WeakSPtr<buCoreBuffer> /*_buffer*/, 
                        uint32 /*_startSlot*/,    
                        uint32 /*_numBuffers*/) { };

   /**
    * @brief Virtual method that sets the constant buffer.
    */
   virtual void
   PSsetConstantBuffers(WeakSPtr<buCoreBuffer> /*_buffer*/, 
                        uint32 /*_startSlot*/,    
                        uint32 /*_numBuffers*/) { };

   /**
    * @brief Virtual method that sets the sampler.
    */
   virtual void
   PSsetSamplers(WeakSPtr<buCoreSampler> /*_sampler*/, 
                 uint32 /*_startSlot*/,
                 uint32 /*_numSamplers*/) {};

   /** 
    * @brief Virtual method that presents the information on the screen.
    */
   virtual void
   present(uint32 /*_syncInterval*/, uint32 /*_flag*/) {};

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   virtual void*
   getDevice() {return nullptr; };

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   virtual void*
   getDeviceContext() {return nullptr; };

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   virtual void*
   getSwapchain() {return nullptr; };

   virtual Vector<void*>
   getShaderResource() {return Vector<void*>();};
 private:

 };
 /**
  * @brief Export method for the class instance.
  */
 BU_CORE_EXPORT buCoreGraphicsAPI&
 g_graphicsAPI();

 /**
  * @brief Specific member uses as a instance to the class.
  */
 using fnGraphicsAPIProt = buCoreGraphicsAPI * (*)();
}
