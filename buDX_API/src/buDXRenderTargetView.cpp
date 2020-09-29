#include "buDXRenderTargetView.h"

namespace buEngineSDK {
  buDXRenderTargetView::buDXRenderTargetView() {
    m_renderTargetView = nullptr;
  }

  buDXRenderTargetView::~buDXRenderTargetView() {
    SAFE_RELEASE(m_renderTargetView);
  }
  
  void
  buDXRenderTargetView::init() {
  }
}