/**
 * @file buDXViewport.h 
 * @version 1.0
 * @date 08/07/2020
 * @authr Roberto CharretonKaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of setting the DX data for the viewport.
 * @bug None.
 */
#pragma once
#include <d3d11.h>
#include "buCoreViewport.h"

namespace buEngineSDK {
 class buDXViewport : public buCoreViewport
 {
  public:
   /**
    * @brief
    */
    buDXViewport();    
   /**
    * @brief 
    */
   ~buDXViewport();
   /**
    * @brief 
    */
    /**
   * @brief
   */
   void
   init(float width, float height, float minDepth, float maxDepth,
      	float topLeftX, float topLeftY) override;
  public:
   /**
    * @brief 
    */
   D3D11_VIEWPORT m_viewport;
   /**
    * @brief 
    */
   float m_width = 0;
   /**
    * @brief 
    */
   float m_height = 0;
   /**
    * @brief 
    */
   float m_minDepth = 0;
   /**
    * @brief 
    */
   float m_maxDepth = 0;
   /**
    * @brief 
    */
   float m_topLeftX = 0;
   /**
    * @brief 
    */
   float m_topLeftY = 0;
 };
}