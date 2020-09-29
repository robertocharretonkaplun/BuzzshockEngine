/**
 * @file 
 * @version 
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once
#include <d3d11.h>
#include "buCoreSwapchain.h"

namespace buEngineSDK {
	class buDXSwapchain : public buCoreSwapchain
	{
	public:
	 /**
    * @brief 
    */
   buDXSwapchain();
   /**
    * @brief 
    */
   ~buDXSwapchain();
   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   void
   init(uint32 bufferCount, uint32 width, uint32 height, uint32 format, 
        uint32 numerator, uint32 denominator, uint32 bufferUsage, 
        void* outputWindow, uint32 count, uint32 quality, bool windowed) override;
  public:
    /**
     * @brief 
     */
    IDXGISwapChain* m_swapchain;
    /**
     * @brief 
     */
    DXGI_SWAP_CHAIN_DESC m_descriptor;
	};
}