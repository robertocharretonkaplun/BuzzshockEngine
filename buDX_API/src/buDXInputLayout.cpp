#include "buDXInputLayout.h"

namespace buEngineSDK {
  buDXInputLayout::buDXInputLayout() {
    m_inputLayout = nullptr;
  }

  buDXInputLayout::~buDXInputLayout() {
    SAFE_RELEASE(m_inputLayout);
  }

  void 
  buDXInputLayout::init(INPUT_LAYOUT_DESC* _descriptor, uint32 _numElements) {
    for (int32 element = 0; element < _numElements; element++) {
      D3D11_INPUT_ELEMENT_DESC layout;
      layout.SemanticName = _descriptor[element].semanticName.c_str();
      layout.SemanticIndex = _descriptor[element].semanticIndex;
      layout.Format = (DXGI_FORMAT)_descriptor[element].format;
      layout.InputSlot = _descriptor[element].inputSlot;
      layout.AlignedByteOffset = _descriptor[element].alignedByteOffset;
      layout.InputSlotClass = (D3D11_INPUT_CLASSIFICATION)_descriptor[element].inputSlot;
      layout.InstanceDataStepRate = _descriptor[element].instanceDataStepRate;
      m_descriptor.push_back(layout);
    }
  }
}
