#include "buDXVertexShader.h"

namespace buEngineSDK {
  buDXVertexShader::~buDXVertexShader() {
    SAFE_RELEASE(m_vertexShader);
  }

  void
  buDXVertexShader::init(WString _fileName,
                         String _entryPoint,
                         String _shaderModel) {
    compileShaderFromFile(_fileName, 
                          _entryPoint, 
                          _shaderModel, 
                          &m_compileVertexShader);
  }

  bool
  buDXVertexShader::compileShaderFromFile(WString szFileName,
                                          String szEntryPoint,
                                          String szShaderModel,
                                          ID3DBlob** ppBlobOut) {
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
