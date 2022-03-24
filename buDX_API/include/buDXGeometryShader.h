#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "buCoreGeometryShader.h"

namespace buEngineSDK {
 class buDXGeometryShader : public buCoreGeometryShader
 {
 public:
  /**
   * @brief 
   */
  buDXGeometryShader() = default;
  /**
   * @brief 
   */
  ~buDXGeometryShader();
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
  ID3D11GeometryShader* m_geometryShader = nullptr;
  /**
   * @brief 
   */
  ID3DBlob* m_compileGeometryShader = nullptr;
 };
}
