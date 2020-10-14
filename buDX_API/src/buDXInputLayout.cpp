#include "buDXInputLayout.h"

namespace buEngineSDK {
  buDXInputLayout::buDXInputLayout() {
    m_inputLayout = nullptr;
  }

  buDXInputLayout::~buDXInputLayout() {
    SAFE_RELEASE(m_inputLayout);
  }

  void 
  buDXInputLayout::init(Vector<String> _semanticNames) {

  //  for (int32 element = 0; element < _semanticNames.size(); element++) {
  //    D3D11_INPUT_ELEMENT_DESC layout;
  //    //layout.SemanticName = _descriptor[element].semanticName.c_str();
  //    layout.SemanticName = _semanticNames[element].c_str();
  //    layout.SemanticIndex = 0;
  //    //layout.Format = (DXGI_FORMAT)_descriptor[element].format;
  //    if (_semanticNames[element] == "POSITION") {
  //      layout.Format = DXGI_FORMAT_R32G32B32_FLOAT;
  //    }
  //    if (_semanticNames[element] == "TEXCOORD") {
  //      layout.Format = DXGI_FORMAT_R32G32_FLOAT;
  //    }
  //    if (_semanticNames[element] == "NORMAL") {
  //      layout.Format = DXGI_FORMAT_R32G32B32_FLOAT;
  //    }
  //    if (_semanticNames[element] == "BLENDINDICES") {
  //      layout.Format = DXGI_FORMAT_R32G32B32A32_UINT;
  //    }
  //    if (_semanticNames[element] == "BLENDWEIGHT") {
  //      layout.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
  //    }
  //    layout.InputSlot = 0;
  //    layout.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
  //    layout.InputSlotClass = (D3D11_INPUT_CLASSIFICATION)
  //      InputClassification::E::BU_INPUT_PER_VERTEX_DATA;
  //    layout.InstanceDataStepRate = 0;
  //    m_descriptor.push_back(layout);
  //  }
  //}

    for (int32 element = 0; element < _semanticNames.size(); element++) {
      D3D11_INPUT_ELEMENT_DESC layout;
      //layout.SemanticName = _descriptor[element].semanticName.c_str();
      layout.SemanticIndex = 0;
      if (_semanticNames[element] == "POSITION") {
        layout.SemanticName = "POSITION";
        layout.Format = DXGI_FORMAT_R32G32B32_FLOAT;
      }
      if (_semanticNames[element] == "TEXCOORD") {
        layout.SemanticName = "TEXCOORD";
        layout.Format = DXGI_FORMAT_R32G32_FLOAT;
      }
      if (_semanticNames[element] == "NORMAL") {
        layout.SemanticName = "NORMAL";
        layout.Format = DXGI_FORMAT_R32G32B32_FLOAT;
      }
      if (_semanticNames[element] == "BLENDINDICES") {
        layout.SemanticName = "BLENDINDICES";
        layout.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      }
      if (_semanticNames[element] == "BLENDWEIGHT") {
        layout.SemanticName = "BLENDWEIGHT";
        layout.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
      }
      layout.InputSlot = 0;
      layout.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
      layout.InputSlotClass = (D3D11_INPUT_CLASSIFICATION)
        InputClassification::E::BU_INPUT_PER_VERTEX_DATA;
      layout.InstanceDataStepRate = 0;
      m_descriptor.push_back(layout);
    }
  }
}
