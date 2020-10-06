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
#include <d3dcompiler.h>
#include "buCoreVertexShader.h"

namespace buEngineSDK {
 class buDXVertexShader : public buCoreVertexShader
 {
 public:
  /**
   * @brief 
   */
  buDXVertexShader() = default;
  /**
   * @brief 
   */
  ~buDXVertexShader();
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  void
  init(WString _fileName) override;
  /**
   * @brief
   * @param
   * @return
   * @bug
   */
  bool
  compileShaderFromFile(WString szFileName, String szEntryPoint,
                        String szShaderModel, ID3DBlob** ppBlobOut);
  public:
  /**
   * @brief 
   */
  ID3D11VertexShader* m_vertexShader = nullptr;
  /**
   * @brief 
   */
  ID3DBlob* m_compileVertexShader = nullptr;
 };
}
