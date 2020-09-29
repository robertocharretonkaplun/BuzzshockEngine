#include "buDXDepthStencilView.h"

namespace buEngineSDK {
  buDXDepthStencilView::buDXDepthStencilView() {
    m_depthStencilView = nullptr;
    memset(&m_descriptor, 0, sizeof(m_descriptor));
  }

  buDXDepthStencilView::~buDXDepthStencilView() {
    SAFE_RELEASE(m_depthStencilView);
  }
  void
  buDXDepthStencilView::init(uint32 _format, 
                             uint32 _viewDimension,
                             uint32 _mipSlice)
  {
    m_format = _format;
    m_viewDimension = _viewDimension;
    m_mipSlice = _mipSlice;

    m_descriptor.Format = (DXGI_FORMAT)m_format;
    m_descriptor.ViewDimension = (D3D11_DSV_DIMENSION)m_viewDimension;
    m_descriptor.Texture2D.MipSlice = m_mipSlice;
  }
}
