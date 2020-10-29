#include "buDXTexture2D.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
namespace buEngineSDK {
  buDXTexture2D::buDXTexture2D() {
    m_texture = nullptr;
    memset(&m_descriptor,0, sizeof(m_descriptor));
  }

  buDXTexture2D::~buDXTexture2D() {
    
    SAFE_RELEASE(m_texture);
  }

  void 
  buDXTexture2D::init(String filepath, uint32 texFormat, uint32 usage, 
                      int32 width, int32 height, int32 mipLevels,
                      int32 arraysize, int32 samplerDescCount, 
                      int32 samplerDescQuality, uint32 bindflags,
                      uint32 CPUAccessFlags, uint32 miscFlags)
  {
    m_descriptor.Width = (UINT)width;
    m_descriptor.Height = (UINT)height;
    m_descriptor.MipLevels = mipLevels;
    m_descriptor.ArraySize = arraysize;
    m_descriptor.Format = (DXGI_FORMAT)texFormat;
    m_descriptor.SampleDesc.Count = samplerDescCount;
    m_descriptor.SampleDesc.Quality = samplerDescQuality;
    m_descriptor.Usage = (D3D11_USAGE)usage;
    m_descriptor.BindFlags = bindflags;
    m_descriptor.CPUAccessFlags = CPUAccessFlags;
    m_descriptor.MiscFlags = miscFlags;
  }

  void 
  buDXTexture2D::init(String _filepath, 
                      int32 width, 
                      int32 height,
                      uint32 format) {
    if ("" != _filepath) {
      m_name = _filepath;
      m_descriptor.Width = (UINT)width;
      m_descriptor.Height = (UINT)height;
      m_descriptor.MipLevels = 1;
      m_descriptor.ArraySize = 1;
      m_descriptor.Format = (DXGI_FORMAT)format;
      m_descriptor.SampleDesc.Count = 1;
      m_descriptor.Usage = D3D11_USAGE_DEFAULT;
      m_descriptor.BindFlags = D3D11_BIND_SHADER_RESOURCE;
      m_descriptor.CPUAccessFlags = 0;
    }
  }
}
