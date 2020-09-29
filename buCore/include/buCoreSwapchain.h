/**
 * @file 
 * @version 
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once
#include "buPrerequisitesCore.h"

namespace buEngineSDK {
 class buCoreSwapchain {
 public:
  /**
   * @brief 
   */
  buCoreSwapchain() = default;
  /**
   * @brief 
   */
  ~buCoreSwapchain() {};
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  virtual void
  init(uint32 bufferCount, uint32 width, uint32 height, uint32 format, 
       uint32 numerator, uint32 denominator, uint32 bufferUsage, 
       void* outputWindow, uint32 count, uint32 quality, bool windowed) = 0;
 };
}
