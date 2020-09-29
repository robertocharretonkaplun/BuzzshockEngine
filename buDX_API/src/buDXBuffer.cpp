#include "..\include\buDXBuffer.h"

namespace buEngineSDK {
  buDXBuffer::buDXBuffer() {
    m_buffer = nullptr;
    memset(&m_descriptor, 0, sizeof(m_descriptor));
    memset(&m_subresourceData, 0, sizeof(m_subresourceData));
  }
  
  buDXBuffer::~buDXBuffer() {
    SAFE_RELEASE(m_buffer);
  }

  void 
  buDXBuffer::init(uint32 Usage, uint32 ByteWidth, uint32 BindFlags, 
                   uint32 CPUAccessFlags, uint32 startSlot, 
                   uint32 numBuffers, uint32 stride = 0, uint32 offset = 0,
                   void* bufferData = nullptr) {
    m_descriptor.Usage = (D3D11_USAGE)Usage;
    m_descriptor.ByteWidth = ByteWidth;
    m_descriptor.BindFlags = BindFlags;
    m_descriptor.CPUAccessFlags = CPUAccessFlags;

    if (bufferData != nullptr) {
      m_subresourceData.pSysMem = bufferData;
      m_startSlot = startSlot;
      m_numBuffers = numBuffers;
      m_stride = stride;
      m_offset = offset;
    }
    else {
      m_bufferData = bufferData;
    }
  }
}
