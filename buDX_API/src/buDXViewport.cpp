#include "buDXViewport.h"

namespace buEngineSDK {
  buDXViewport::buDXViewport() {
  }
  buDXViewport::~buDXViewport() {
  }
  void 
  buDXViewport::init(float width, float height, float minDepth,
                     float maxDepth, float topLeftX, float topLeftY)
  {
    m_width = width;
    m_height = height;
    m_minDepth = minDepth;
    m_maxDepth = maxDepth;
    m_topLeftX = topLeftX;
    m_topLeftY = topLeftY;

    // Set the members in the DX structure
    m_viewport.Width = m_width;
    m_viewport.Height = m_height;
    m_viewport.MinDepth = m_minDepth;
    m_viewport.MaxDepth = m_maxDepth;
    m_viewport.TopLeftX = m_topLeftX;
    m_viewport.TopLeftY = m_topLeftY;
  }
}
