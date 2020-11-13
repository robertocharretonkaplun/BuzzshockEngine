/**
 * @file 
 * @version 
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once
#include <buPrerequisitesDX.h>
#include <d3d11.h>
#include "buCoreTexture2D.h"
#include "buCoreRenderTargetView.h"
#include "buCommons.h"
namespace buEngineSDK {
 class buDXTexture2D : public buCoreTexture2D {
 public:
  /**
   * @brief 
   */
  buDXTexture2D();
  /**
   * @brief 
   */
  ~buDXTexture2D();
  /*
  * @brief
  * @param
  * @return
  * @bug
  */
  void
  init(String filepath, uint32 texFormat, uint32 usage, int32 width,
    int32 height, int32 mipLevels, int32 arraysize, int32 samplerDescCount,
       int32 samplerDescQuality, uint32 bindflags, uint32 CPUAccessFlags,
       uint32 miscFlags) override;

  /**
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  void 
  init(String _filepath, int32 width, int32 height, TextureType::E textureType) override;
 public:
   String m_name;
  /*
   * @brief 
   */
   ID3D11Texture2D* m_texture;
   /**
    * @brief 
    */
   D3D11_TEXTURE2D_DESC m_descriptor;
   /**
    * @brief
    */
   ID3D11ShaderResourceView* m_shaderSubresource;

   SPtr<buCoreRenderTargetView> m_renderTarget;
   ID3D11RenderTargetView* m_renderTargetView;
   CD3D11_SHADER_RESOURCE_VIEW_DESC m_shaderResourceViewDesc;
   D3D11_RENDER_TARGET_VIEW_DESC m_renderTargetViewDesc;
   /**
   * @brief 
   */
   uint32 m_width;
   /**
    * @brief 
    */
   uint32 m_height;

   /**
    * @brief 
    */
   unsigned char* image;
 };
}
