/**
 * @file buDXDevice.h
 * @version 1.0
 * @date 02/07/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of providing a virtual function to the graphics API.
 */
#pragma once
#include <d3d11.h>
#include <buCoreDevice.h>

namespace buEngineSDK {
 class buDXDevice : public buCoreDevice
 {
 public:
  /**
   * @brief Default Constructor
   */
  buDXDevice() = default;
  /**
   * @brief Destructors
   */
  ~buDXDevice() = default;
  /**
   * @brief
   * @param
   * @return
   * @bug
   */
  void
  destroy() override;
  /**
   * @brief
   * @param
   * @return
   * @bug
   */
  void*
  getInterface() override;

  /**
  * @brief
  * @param
  * @return
  * @bug
  */
  virtual void
  createRenderTargetView() override;
 private:
  /**
   * @brief
   */
  ID3D11Device* m_device;
 };
}
