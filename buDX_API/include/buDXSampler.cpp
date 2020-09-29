#include "buDXSampler.h"

namespace buEngineSDK {
  buDXSampler::buDXSampler() {
    m_sampler = nullptr;
    memset(&m_descriptor, 0, sizeof(m_descriptor));
  }

  buDXSampler::~buDXSampler() {
    SAFE_RELEASE(m_sampler);
  }

  void 
  buDXSampler::init(uint32 _filter, uint32 _addressU, uint32 _addressV, 
                    uint32 _addressW, uint32 _comparisonFunc, 
                    float _minLOD, float _maxLOD)
  {
    m_filter = _filter;
    m_addressU = _addressU;
    m_addressV = _addressV;
    m_addressW = _addressW;
    m_comparisonFunc = _comparisonFunc;
    m_minLOD = _minLOD;
    m_maxLOD = _maxLOD;

    m_descriptor.Filter = (D3D11_FILTER)m_filter;
    m_descriptor.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)m_addressU;
    m_descriptor.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)m_addressV;
    m_descriptor.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)m_addressW;
    m_descriptor.ComparisonFunc = (D3D11_COMPARISON_FUNC)m_comparisonFunc;
    m_descriptor.MinLOD = m_minLOD;
    m_descriptor.MaxLOD = m_maxLOD;
  }
}
