#include "..\include\buDXSwapchain.h"

buEngineSDK::buDXSwapchain::buDXSwapchain()
{
  m_swapchain = nullptr;
  memset(&m_descriptor,0, sizeof(m_descriptor));
}

buEngineSDK::buDXSwapchain::~buDXSwapchain()
{
  SAFE_RELEASE(m_swapchain);
}

void buEngineSDK::buDXSwapchain::init(uint32 bufferCount, uint32 width, 
                                      uint32 height, uint32 format, 
                                      uint32 numerator, uint32 denominator,
                                      uint32 bufferUsage, void* outputWindow,
                                      uint32 count, uint32 quality,
                                      bool windowed)
{
  
  m_descriptor.BufferCount = bufferCount;
  m_descriptor.BufferDesc.Width = width;
  m_descriptor.BufferDesc.Height = height;
  m_descriptor.BufferDesc.Format = (DXGI_FORMAT)format;
  m_descriptor.BufferDesc.RefreshRate.Numerator = numerator;
  m_descriptor.BufferDesc.RefreshRate.Denominator = denominator;
  m_descriptor.BufferUsage = bufferUsage;
  m_descriptor.OutputWindow = (HWND)outputWindow;
  m_descriptor.SampleDesc.Count = count;
  m_descriptor.SampleDesc.Quality = quality;
  m_descriptor.Windowed = windowed;
}
