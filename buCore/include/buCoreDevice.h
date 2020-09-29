/**
 * @file buCoreDevice.h 
 * @version 1.0
 * @date 02/07/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of providing a virtual function to the graphics API.
 */
#pragma once
#include <buPrerequisitesCore.h>
namespace buEngineSDK {
 class buCoreDevice
 {
 public:
  /**
   * @brief Default Constructor 
   */
  buCoreDevice() = default;
  /**
   * @brief Destructors
   */
  ~buCoreDevice() = default;
 /** 
  * @brief 
  * @param 
  * @return 
  * @bug 
  */
  virtual void
  destroy() {};
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug  
   */
  virtual void* 
  getInterface() {};

  /** 
  * @brief 
  * @param 
  * @return 
  * @bug 
  */
  virtual void 
  createRenderTargetView() {};
 private:
   /**
    * @brief 
    */
   //ID3D11Device* m_device;
 };
}
