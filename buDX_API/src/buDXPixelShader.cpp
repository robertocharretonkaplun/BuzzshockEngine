#include "buDXPixelShader.h"

namespace buEngineSDK {
  buDXPixelShader::buDXPixelShader() {
    m_pixelShader = nullptr;
    m_compilePixelShader = nullptr;
  }

  buDXPixelShader::~buDXPixelShader() {
    SAFE_RELEASE(m_pixelShader);
  }

  void 
  buDXPixelShader::init(WString _fileName, 
                        String _entryPoint,
                        String _shaderModel) {
    CompileShaderFromFile(_fileName, 
                          _entryPoint, 
                          _shaderModel, 
                          &m_compilePixelShader);
  }

  bool 
  buDXPixelShader::CompileShaderFromFile(WString szFileName,
                                         String szEntryPoint,
                                         String szShaderModel, 
                                         ID3DBlob** ppBlobOut)
  {
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if BU_DEBUG_MODE
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob = nullptr;

    hr = D3DCompileFromFile(szFileName.c_str(),
                            nullptr,
                            nullptr,
                            szEntryPoint.c_str(),
                            szShaderModel.c_str(),
                            dwShaderFlags,
                            0,
                            ppBlobOut,
                            &pErrorBlob);
    if (FAILED(hr)) {
      if (nullptr != pErrorBlob)
        //OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        pErrorBlob->Release();
      return false;
    }

    if (nullptr != pErrorBlob) {
      pErrorBlob->Release();
    }

    return true;
  }
}
