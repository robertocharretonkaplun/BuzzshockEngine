/**
 * @file 
 * @version 
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once

namespace buEngineSDK {
 class buCoreDeviceContext
 {
 public:
 	/**
 	 * @brief Constructor
 	 */
 	buCoreDeviceContext() = default;
 	/**
 	 * @brief Destructor
 	 */
 	~buCoreDeviceContext() {};
 
 private:
  /**
   * @brief 
   */
  ID3D11DeviceContext* m_deviceContext;
 };
}