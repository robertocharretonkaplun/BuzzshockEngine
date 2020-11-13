#include "buDXTexture2D.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
namespace buEngineSDK {
  buDXTexture2D::buDXTexture2D() {
    m_texture = nullptr;
    m_renderTarget = nullptr;
    memset(&m_descriptor,0, sizeof(m_descriptor));
    memset(&m_shaderResourceViewDesc, 0, sizeof(m_shaderResourceViewDesc));
    memset(&m_renderTargetViewDesc, 0, sizeof(m_renderTargetViewDesc));
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
                      TextureType::E textureType) {

    m_name = _filepath;
    m_descriptor.Width = (UINT)width;
    m_descriptor.Height = (UINT)height;
    m_descriptor.MipLevels = 1;
    m_descriptor.SampleDesc.Count = 1;
    m_descriptor.Usage = D3D11_USAGE_DEFAULT;
    m_descriptor.CPUAccessFlags = 0;

    switch (textureType) {
    case TextureType::DEFAULT:
      // Set array size
      m_descriptor.ArraySize = 1;
      // Set the bind flag
      m_descriptor.BindFlags = D3D11_BIND_SHADER_RESOURCE;
      // Set the format
      m_descriptor.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      // Fill the shader resource desc
      m_shaderResourceViewDesc.Format = m_descriptor.Format;
      m_shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

      m_shaderResourceViewDesc.Texture2D.MipLevels = m_descriptor.MipLevels;
      m_shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
      break;
    case TextureType::DEPTH_STENCIL:
      // ref: https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-depth-stencil
      // Set array size
      m_descriptor.ArraySize = 1;
      // Set the bind flag
      m_descriptor.BindFlags = D3D11_BIND_DEPTH_STENCIL;
      // Set the format
      m_descriptor.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
      break;
    case TextureType::RENDER_TARGET:
      // Ref: http://www.hlsl.co.uk/blog/2014/11/19/creating-a-render-target-in-directx11
      #pragma region RenderTarget
        // Set array size
        m_descriptor.ArraySize = 1;
        // Set the bind flag
        m_descriptor.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        // Set the format
        m_descriptor.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        // Fill the render target view descriptor
        m_renderTargetViewDesc.Format = m_descriptor.Format;
        m_renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        m_renderTargetViewDesc.Texture2D.MipSlice = 0;
        // Fill the shader resource descriptor
        m_shaderResourceViewDesc.Format = m_descriptor.Format;
        m_shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        m_shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
        m_shaderResourceViewDesc.Texture2D.MipLevels = m_descriptor.MipLevels;
        #pragma endregion
      break;
    case TextureType::CUBE_MAP:
      m_descriptor.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      m_descriptor.ArraySize = 6;
      m_descriptor.BindFlags = D3D11_BIND_SHADER_RESOURCE;
      m_descriptor.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
      break;
    default:
      break;
    }

      // Define what type of texture is loaded
      

  }
}
