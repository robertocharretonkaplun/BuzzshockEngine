#include "buDXGraphicsAPI.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
namespace buEngineSDK {
  buDXGraphicsAPI::buDXGraphicsAPI() {
    // m_swapchainDesc;
    m_swapchain = nullptr;
    m_device = nullptr;
    m_deviceContext = nullptr;
    //g_hInst = nullptr;
  }

  buDXGraphicsAPI::~buDXGraphicsAPI() {
    SAFE_RELEASE(m_swapchain);
    SAFE_RELEASE(m_deviceContext);
    SAFE_RELEASE(m_device);
  }

  void 
  buDXGraphicsAPI::testFunc() {
    std::cout << "TestFunc in DX API" << std::endl;
  }

  void 
  buDXGraphicsAPI::cleanUp() {
    SAFE_RELEASE(m_deviceContext);
    //SAFE_RELEASE(g_pVertexBuffer);
    //SAFE_RELEASE(g_pVertexLayout);
    ///SAFE_RELEASE(g_pVertexShader);
    //SAFE_RELEASE(g_pPixelShader);
    //SAFE_RELEASE(m_renderTargetView);
    SAFE_RELEASE(m_device);
    SAFE_RELEASE(m_swapchain);
  }

  void 
  buDXGraphicsAPI::update() {
    // Update our time
  }

  void 
  buDXGraphicsAPI::render(WeakSPtr<buCoreDepthStencilView> _depthStencilView,
    WeakSPtr<buCoreRenderTargetView> _renderTargetView,
    WeakSPtr<buCoreVertexShader> _vertexShader,
    WeakSPtr<buCoreInputLayout> _inputLayout,
    WeakSPtr<buCorePixelShader> _pixelShader,
    WeakSPtr<buCoreBuffer> _neverChanges,
    WeakSPtr<buCoreBuffer> _changeOnResize,
    WeakSPtr<buCoreBuffer> _ChangeEveryFrame,
    WeakSPtr<buCoreTexture2D> _meshTexture,
    WeakSPtr<buCoreSampler> _sampler) {

  }

  void 
  buDXGraphicsAPI::initialize(void* _window, uint32 _width, uint32 _height) {
    m_width = _width;
    m_height = _height;
    createDeviceAndSwapChain(_window);
  }

  bool 
  buDXGraphicsAPI::createDeviceAndSwapChain(void* _window) {
    HRESULT hr = S_FALSE;
    uint32 createDeviceFlags = D3D11_CREATE_DEVICE_SWITCH_TO_REF;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_SWITCH_TO_REF;
#endif

    Vector<D3D_DRIVER_TYPE> driverTypes =
    {
      D3D_DRIVER_TYPE_HARDWARE,
      D3D_DRIVER_TYPE_WARP,
      D3D_DRIVER_TYPE_REFERENCE
    };

    Vector<D3D_FEATURE_LEVEL> featureLevels =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    DXGI_SWAP_CHAIN_DESC swapchainDesc;
    memset(&swapchainDesc, 0, sizeof(swapchainDesc));
    swapchainDesc.BufferCount = 1;
    swapchainDesc.BufferDesc.Width = m_width;
    swapchainDesc.BufferDesc.Height = m_height;
    swapchainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapchainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapchainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapchainDesc.OutputWindow = reinterpret_cast<HWND>(_window);
    swapchainDesc.SampleDesc.Count = 1;
    swapchainDesc.SampleDesc.Quality = 0;
    swapchainDesc.Windowed = TRUE;

    D3D_FEATURE_LEVEL selectedFeatureLevel;

    for (auto& driverType : driverTypes) {
      hr = D3D11CreateDeviceAndSwapChain(nullptr,
                                         driverType,
                                         nullptr,
                                         (UINT)createDeviceFlags,
                                         featureLevels.data(),
                                         (UINT)featureLevels.size(),
                                         (UINT)D3D11_SDK_VERSION,
                                         &swapchainDesc,
                                         &m_swapchain,
                                         &m_device,
                                         &selectedFeatureLevel,
                                         &m_deviceContext);
      if (static_cast<int>(hr)) {
        break;
      }
    }

   // m_swapchain->SetFullscreenState(true, nullptr);
    return static_cast<int>(hr);
  }

  bool 
  buDXGraphicsAPI::createTextureForBackBuffer(
    WeakSPtr<buCoreTexture2D> _backbuffer) {
    if (_backbuffer.expired()) {
      return false;
    }
    auto bbObj = _backbuffer.lock();
    auto tmpBB = reinterpret_cast<buDXTexture2D*>(bbObj.get());
    //ID3D11Texture2D* pBackBuffer = nullptr;
    return static_cast<int>(m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D),
      (void**)&tmpBB->m_texture));
  }

  SPtr<buCoreViewport>
  buDXGraphicsAPI::createViewport(float width, float height) {
    auto pviewport = std::make_shared<buDXViewport>();
    auto viewport = reinterpret_cast<buDXViewport*>(pviewport.get());
    viewport->init(width, height, 0.0f, 1.0f, 0.0f, 0.0f);
    return pviewport;
    //return SPtr<buCoreViewport>();
  }

  SPtr<buCoreTexture2D> 
  buDXGraphicsAPI::createTexture2D(int32 width, int32 height ) {
    auto ptexture2D = std::make_shared<buDXTexture2D>();
    auto texture = reinterpret_cast<buDXTexture2D*>(ptexture2D.get());


    texture->init("",
                  DXGI_FORMAT_D24_UNORM_S8_UINT,
                  D3D11_USAGE_DEFAULT,
                  width,
                  height,
                  1,
                  1,
                  1,
                  0,
                  D3D11_BIND_DEPTH_STENCIL,
                  0,
                  0);


    m_device->CreateTexture2D(&texture->m_descriptor,
                              nullptr,
                              &texture->m_texture);

    return ptexture2D;
  }

  SPtr<buCoreTexture2D> buDXGraphicsAPI::createTexture2D(int32 width,
                                                         int32 height, 
                                                         uint32 format,
                                                         uint32 usage, 
                                                         uint32 bindflags) {
    auto ptexture2D = std::make_shared<buDXTexture2D>();
    auto texture = reinterpret_cast<buDXTexture2D*>(ptexture2D.get());


    texture->init("",
      format,
      usage,
      width,
      height,
      1,
      1,
      1,
      0,
      bindflags,
      0,
      0);


    m_device->CreateTexture2D(&texture->m_descriptor,
      nullptr,
      &texture->m_texture);

    return ptexture2D;
  }

  SPtr<buCoreSwapchain> 
  buDXGraphicsAPI::createSwapchain() {
    auto swapchain = std::make_shared<buDXSwapchain>();
    return swapchain;
  }

  SPtr<buCoreRenderTargetView> 
  buDXGraphicsAPI::createRenderTargetView() {
    auto renderTargetView = std::make_shared<buDXRenderTargetView>();
    return renderTargetView;
  }

  SPtr<buCoreVertexShader> 
  buDXGraphicsAPI::createVertexShader(WString _fileName) {
    auto vertexShader = std::make_shared<buDXVertexShader>();
    auto tmpVertexShader = reinterpret_cast<buDXVertexShader*>(vertexShader.get());

    tmpVertexShader->init(_fileName);
    
    HRESULT hr = m_device->CreateVertexShader(
      tmpVertexShader->m_compileVertexShader->GetBufferPointer(),
      tmpVertexShader->m_compileVertexShader->GetBufferSize(),
      nullptr,
      &tmpVertexShader->m_vertexShader);

    return vertexShader;
  }

  SPtr<buCorePixelShader> 
  buDXGraphicsAPI::createPixelShader(WString _fileName) {
    auto pixelShader = std::make_shared<buDXPixelShader>();
    auto tmpPixelShader = reinterpret_cast<buDXPixelShader*>(pixelShader.get());

    tmpPixelShader->init(_fileName);

    // Create the pixel shader
    static_cast<int>(m_device->CreatePixelShader(
      tmpPixelShader->m_compilePixelShader->GetBufferPointer(),
      tmpPixelShader->m_compilePixelShader->GetBufferSize(),
      nullptr,
      &tmpPixelShader->m_pixelShader));

    return pixelShader;
  }

  SPtr<buCoreInputLayout>
  buDXGraphicsAPI::createInputLayout(WeakSPtr<buCoreVertexShader> _vertexShader, 
                                     Vector<String> _semanticNames) {
    auto inputLayout = std::make_shared<buDXInputLayout>();
    auto tmpInputLayout = reinterpret_cast<buDXInputLayout*>(inputLayout.get());

    
    // Vertex Shader
    if (_vertexShader.expired()) {
      return nullptr;
    }
    auto vsObj = _vertexShader.lock();
    auto tmpVS = reinterpret_cast<buDXVertexShader*>(vsObj.get());


    // Create the input layout
    tmpInputLayout->init(_semanticNames);
    static_cast<int>(m_device->CreateInputLayout(tmpInputLayout->m_descriptor.data(),
      (UINT)tmpInputLayout->m_descriptor.size(),
      tmpVS->m_compileVertexShader->GetBufferPointer(),
      tmpVS->m_compileVertexShader->GetBufferSize(),
      &tmpInputLayout->m_inputLayout));


    return inputLayout;
  }

  SPtr<buCoreBuffer> 
  buDXGraphicsAPI::createBuffer(uint32 byteWidth, 
                                uint32 bindFlags,
                                uint32 offset,
                                void* bufferData) {
    auto buffer = std::make_shared<buDXBuffer>();
    auto tmpBuffer = reinterpret_cast<buDXBuffer*>(buffer.get());
    tmpBuffer->init(D3D11_USAGE_DEFAULT,
                    byteWidth,
                    bindFlags,
                    0,
                    0,
                    1,
                    offset,
                    0,
                    bufferData);

    if (nullptr == tmpBuffer->m_bufferData) {
      m_device->CreateBuffer(&tmpBuffer->m_descriptor,
                             nullptr,
                             &tmpBuffer->m_buffer);
      return buffer;
    }
    else {
      m_device->CreateBuffer(&tmpBuffer->m_descriptor,
                             &tmpBuffer->m_subresourceData,
                             &tmpBuffer->m_buffer);
      return buffer;
    }
    return buffer;
  }

  SPtr<buCoreBuffer> buDXGraphicsAPI::createBuffer(uint32 byteWidth) {
    auto buffer = std::make_shared<buDXBuffer>();
    auto tmpBuffer = reinterpret_cast<buDXBuffer*>(buffer.get());
    tmpBuffer->init(D3D11_USAGE_DEFAULT,
                    byteWidth,
                    D3D11_BIND_CONSTANT_BUFFER,
                    0,
                    0,
                    1,
                    0,
                    0,
                    nullptr);

    if (nullptr == tmpBuffer->m_bufferData) {
      m_device->CreateBuffer(&tmpBuffer->m_descriptor,
                             nullptr,
                             &tmpBuffer->m_buffer);
      return buffer;
    }
    else {
      m_device->CreateBuffer(&tmpBuffer->m_descriptor,
                             &tmpBuffer->m_subresourceData,
                             &tmpBuffer->m_buffer);
      return buffer;
    }
    return buffer;
  }

  SPtr<buCoreDepthStencilView>
  buDXGraphicsAPI::createDepthStencilView() {
    auto depthStencilView = std::make_shared<buDXDepthStencilView>();
    return depthStencilView;
  }

  SPtr<buCoreSampler> 
  buDXGraphicsAPI::createSampler() {
    auto sampler = std::make_shared<buDXSampler>();
    auto tmpSampler = reinterpret_cast<buDXSampler*>(sampler.get());

    tmpSampler->init(D3D11_FILTER_MIN_MAG_MIP_LINEAR,
      D3D11_TEXTURE_ADDRESS_WRAP,
      D3D11_TEXTURE_ADDRESS_WRAP,
      D3D11_TEXTURE_ADDRESS_WRAP,
      D3D11_COMPARISON_NEVER,
      0,
      D3D11_FLOAT32_MAX);

    static_cast<int>(m_device->CreateSamplerState(&tmpSampler->m_descriptor,
      &tmpSampler->m_sampler));

    return sampler;
  }

  void
  buDXGraphicsAPI::setVertexShader(WeakSPtr<buCoreVertexShader> _vertexShader) {
    if (_vertexShader.expired()) {
      return;
    }
    auto VSObj = _vertexShader.lock();
    auto tmpVS = reinterpret_cast<buDXVertexShader*>(VSObj.get());
    m_deviceContext->VSSetShader(tmpVS->m_vertexShader, nullptr, 0);
  }

  void
  buDXGraphicsAPI::setInputLayout(WeakSPtr<buCoreInputLayout> _inputLayout) {
    if (_inputLayout.expired()) {
      return;
    }
    auto ILObj = _inputLayout.lock();
    auto tmpIL = reinterpret_cast<buDXInputLayout*>(ILObj.get());
    m_deviceContext->IASetInputLayout(tmpIL->m_inputLayout);
  }

  void 
  buDXGraphicsAPI::setPixelhader(WeakSPtr<buCorePixelShader> _pixelShader) {
    if (_pixelShader.expired()) {
      return;
    }
    auto PSObj = _pixelShader.lock();
    auto tmpPS = reinterpret_cast<buDXPixelShader*>(PSObj.get());
    m_deviceContext->PSSetShader(tmpPS->m_pixelShader, nullptr, 0);
  }

  void 
  buDXGraphicsAPI::drawIndexed(uint32 _numVertices,
    uint32 _startIndexLocation,
    uint32 _baseVertexLocation) {
    m_deviceContext->DrawIndexed(_numVertices, 
                                 _startIndexLocation,
                                 _baseVertexLocation);
  }

  void
  buDXGraphicsAPI::present(uint32 _syncInterval, uint32 _flag) {
    m_swapchain->Present(_syncInterval, _flag);
  }

  bool 
  buDXGraphicsAPI::createDepthStencilView(
    WeakSPtr<buCoreTexture2D> _texture,
    WeakSPtr<buCoreDepthStencilView> _depthStencilView) {
    // Depth stencil
    if (_texture.expired()) {
      return false;
    }
    auto textureObj = _texture.lock();
    auto texture = reinterpret_cast<buDXTexture2D*>(textureObj.get());
    // Depth Stencil view
    if (_depthStencilView.expired()) {
      return false;
    }
    auto DSVObj = _depthStencilView.lock();
    auto tmpDSV = reinterpret_cast<buDXDepthStencilView*>(DSVObj.get());
    tmpDSV->init(texture->m_descriptor.Format, D3D11_DSV_DIMENSION_TEXTURE2D, 0);
    return static_cast<int>(m_device->CreateDepthStencilView(texture->m_texture,
      &tmpDSV->m_descriptor,
      &tmpDSV->m_depthStencilView));
  }

  SPtr<buCoreRenderTargetView> buDXGraphicsAPI::createRenderTarget(WeakSPtr<buCoreTexture2D> _texture)
  {
    auto pRenderTargetView = std::make_shared<buDXRenderTargetView>();
    auto renderTargetView = reinterpret_cast<buDXRenderTargetView*>(pRenderTargetView.get());

    auto textureObj = _texture.lock();
    auto texture = reinterpret_cast<buDXTexture2D*>(textureObj.get());

    D3D11_RENDER_TARGET_VIEW_DESC d;
    ZeroMemory(&d, sizeof(d));

    d.Format = texture->m_descriptor.Format;
    d.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
    d.Texture2DArray.ArraySize = 1;
    d.Texture2DArray.FirstArraySlice = 0;

    static_cast<int>(m_device->CreateRenderTargetView(texture->m_texture,
      &d,
      &renderTargetView->m_renderTargetView));

    return pRenderTargetView;
  }

  bool 
  buDXGraphicsAPI::createRenderTargetView(WeakSPtr<buCoreTexture2D> _texture,
    WeakSPtr<buCoreRenderTargetView> _renderTargetView) {
    // Back buffer texture
    if (_texture.expired()) {
      return false;
    }
    auto textureObj = _texture.lock();
    auto texture = reinterpret_cast<buDXTexture2D*>(textureObj.get());

    // Render target view
    if (_renderTargetView.expired()) {
      return false;
    }
    auto RTVObj = _renderTargetView.lock();
    auto tmpRTV = reinterpret_cast<buDXRenderTargetView*>(RTVObj.get());


    return static_cast<int>(m_device->CreateRenderTargetView(texture->m_texture,
      nullptr,
      &tmpRTV->m_renderTargetView));
  }

  bool
  buDXGraphicsAPI::createVertexShader(WeakSPtr<buCoreVertexShader> _vertexShader) {
    if (_vertexShader.expired()) {
      return false;
    }
    auto vsObj = _vertexShader.lock();
    auto tmpVS = reinterpret_cast<buDXVertexShader*>(vsObj.get());

    // Create the vertex shader
    HRESULT hr = m_device->CreateVertexShader(      
      tmpVS->m_compileVertexShader->GetBufferPointer(),
      tmpVS->m_compileVertexShader->GetBufferSize(),
      nullptr,
      &tmpVS->m_vertexShader);

    return hr == S_OK;
  }

  bool 
  buDXGraphicsAPI::createInputLayout(WeakSPtr<buCoreVertexShader> _vertexShader,
                                     WeakSPtr<buCoreInputLayout> _inputLayout) {
    // Vertex Shader
    if (_vertexShader.expired()) {
      return false;
    }
    auto vsObj = _vertexShader.lock();
    auto tmpVS = reinterpret_cast<buDXVertexShader*>(vsObj.get());

    // Input layout
    if (_inputLayout.expired()) {
      return false;
    }
    auto ILObj = _inputLayout.lock();
    auto tmpIL = reinterpret_cast<buDXInputLayout*>(ILObj.get());

    // Create the input layout
    return static_cast<int>(m_device->CreateInputLayout(tmpIL->m_descriptor.data(),
      (UINT)tmpIL->m_descriptor.size(),
      tmpVS->m_compileVertexShader->GetBufferPointer(),
      tmpVS->m_compileVertexShader->GetBufferSize(),
      &tmpIL->m_inputLayout));
  }

  bool
  buDXGraphicsAPI::createPixelShader(WeakSPtr<buCorePixelShader> _pixelShader) {
    if (_pixelShader.expired()) {
      return false;
    }
    auto PSObj = _pixelShader.lock();
    auto tmpPS = reinterpret_cast<buDXPixelShader*>(PSObj.get());

    // Create the pixel shader
    return static_cast<int>(m_device->CreatePixelShader(
      tmpPS->m_compilePixelShader->GetBufferPointer(),
      tmpPS->m_compilePixelShader->GetBufferSize(),
      nullptr,
      &tmpPS->m_pixelShader));
  }

  bool 
  buDXGraphicsAPI::createSamplerState(WeakSPtr<buCoreSampler> _sampler) {
    if (_sampler.expired()) {
      return false;
    }
    auto SObj = _sampler.lock();
    auto tmpS = reinterpret_cast<buDXSampler*>(SObj.get());
    return static_cast<int>(m_device->CreateSamplerState(&tmpS->m_descriptor,
                                                         &tmpS->m_sampler));
  }

  bool 
  buDXGraphicsAPI::createShaderResourceView(WeakSPtr<buCoreTexture2D> _texture) {
    if (_texture.expired()) {
      return false;
    }
    auto textureObj = _texture.lock();
    auto texture = reinterpret_cast<buDXTexture2D*>(textureObj.get());
    return static_cast<int>(m_device->CreateShaderResourceView(texture->m_texture,
      nullptr, reinterpret_cast<ID3D11ShaderResourceView**>(texture->image)));
  }

  void 
  buDXGraphicsAPI::PSSetShaderResources(WeakSPtr<buCoreTexture2D> _texture, 
                                        uint32 _startSlot,
                                        uint32 _numViews) {
    if (_texture.expired()) {
      return;
    }
    auto textureObj = _texture.lock();
    auto texture = reinterpret_cast<buDXTexture2D*>(textureObj.get());

    m_deviceContext->PSSetShaderResources(_startSlot, 
                                          _numViews, 
                                          &texture->m_shaderSubresource);
  }

  SPtr<buCoreTexture2D>
  buDXGraphicsAPI::loadImageFromFile(String _filepath, 
                                     int32 width, 
                                     int32 height,
                                     TextureType::E textureType) {

    auto ptexture2D = std::make_shared<buDXTexture2D>();

    auto texture = reinterpret_cast<buDXTexture2D*>(ptexture2D.get());

    String texturePath;
    String folderPath = "Data/Textures/";
   // folderPath += _filepath;
    FILE* f = stbi__fopen(_filepath.c_str(), "rb");
    // If the texture path wasnt loaded correctly
    if (!f) {
      texturePath = "Data/Textures/DefaultTexture.png";
    }
    else {
      texturePath = _filepath;
      //texturePath = folderPath;
    }


    texture->image = stbi_load(texturePath.c_str(), &width, &height, nullptr, 4);

    if (texture->image == nullptr) {
      return nullptr;
    }
    texture->init(_filepath, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, textureType);

    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = texture->image;
    subResource.SysMemPitch = width * 4;
    subResource.SysMemSlicePitch = width * height * 4;

    m_device->CreateTexture2D(&texture->m_descriptor,
      &subResource,
      &texture->m_texture);

    CD3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    shaderResourceViewDesc.Format = texture->m_descriptor.Format;
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    
    shaderResourceViewDesc.Texture2D.MipLevels = texture->m_descriptor.MipLevels;
    shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;



    m_device->CreateShaderResourceView(texture->m_texture,
      &shaderResourceViewDesc,
      &texture->m_shaderSubresource);
    


    stbi_image_free(texture->image);
    m_ShaderResources.push_back(texture->m_shaderSubresource);
    return ptexture2D;
  }

  SPtr<buCoreTexture2D> buDXGraphicsAPI::loadDDSFromFile(WString _filepath,
    int32 width, int32 height) {
    auto ptexture2D = std::make_shared<buDXTexture2D>();

    auto texture = reinterpret_cast<buDXTexture2D*>(ptexture2D.get());
    
    DirectX::CreateDDSTextureFromFileEx(m_device,
      _filepath.c_str(),
      0,
      D3D11_USAGE_DEFAULT,
      D3D11_BIND_SHADER_RESOURCE,
      0,
      D3D11_RESOURCE_MISC_TEXTURECUBE,
      false,
      (ID3D11Resource**)&texture->m_texture,
      &texture->m_shaderSubresource);

   
    m_ShaderResources.push_back(texture->m_shaderSubresource);
    return ptexture2D;
  
  }

  SPtr<buCoreModelLoader>
  buDXGraphicsAPI::loadMesh(String _filepath) {
    /*auto meshloader = std::make_shared<buCoreModelLoader>();
    auto loader = reinterpret_cast<buCoreModelLoader*>(meshloader.get());
    loader->loadMesh(_filepath);

    return meshloader;*/
    return nullptr;
  }

  void buDXGraphicsAPI::setShaderSubresource(WeakSPtr<buCoreTexture2D> _texture)
  {
    if (_texture.expired()) {
      return;
    }
    auto textureObj = _texture.lock();
    auto texture = reinterpret_cast<buDXTexture2D*>(textureObj.get());

    CD3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    shaderResourceViewDesc.Format =  texture->m_descriptor.Format;
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Texture2D.MipLevels = texture->m_descriptor.MipLevels;
    shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;

    m_device->CreateShaderResourceView(texture->m_texture,
      &shaderResourceViewDesc,
      &texture->m_shaderSubresource);
    m_ShaderResources.push_back(texture->m_shaderSubresource);
  }

  void
  buDXGraphicsAPI::setVertexBuffers(WeakSPtr<buCoreBuffer> _buffer) {
    if (_buffer.expired()) {
      return;
    }
    auto bufferObj = _buffer.lock();
    auto tmpBuffer = reinterpret_cast<buDXBuffer*>(bufferObj.get());
    m_deviceContext->IASetVertexBuffers(tmpBuffer->m_startSlot,
      tmpBuffer->m_numBuffers,
      &tmpBuffer->m_buffer,
      (UINT*)&tmpBuffer->m_stride,
      (UINT*)&tmpBuffer->m_offset);
  }

  void 
  buDXGraphicsAPI::setIndexBuffer(WeakSPtr<buCoreBuffer> _buffer,
                                  uint32 _format,
                                  uint32 _offset) {
    if (_buffer.expired()) {
      return;
    }
    auto bufferObj = _buffer.lock();
    auto tmpBuffer = reinterpret_cast<buDXBuffer*>(bufferObj.get());
    m_deviceContext->IASetIndexBuffer(tmpBuffer->m_buffer,
      (DXGI_FORMAT)_format,
      _offset);
  }

  void 
  buDXGraphicsAPI::setViewport(WeakSPtr<buCoreViewport> _viewport) {
    if (_viewport.expired()) {
      return;
    }
    auto vpObj = _viewport.lock();
    auto tmpvp = reinterpret_cast<buDXViewport*>(vpObj.get());

    m_deviceContext->RSSetViewports(1, &tmpvp->m_viewport);
  }

  void 
  buDXGraphicsAPI::setRenderTargets(int32 _numViews,
    WeakSPtr<buCoreRenderTargetView> _renderTargetView,
    WeakSPtr<buCoreDepthStencilView> _depthStencilView) {
    if (_depthStencilView.expired()) {
      return;
    }

    auto DSVObj = _depthStencilView.lock();
    auto tmpDSV = reinterpret_cast<buDXDepthStencilView*>(DSVObj.get());
    if (_renderTargetView.expired()) {
      return;
    }
    auto RTVObj = _renderTargetView.lock();
    auto tmpRTV = reinterpret_cast<buDXRenderTargetView*>(RTVObj.get());
    m_deviceContext->OMSetRenderTargets(_numViews,
      &tmpRTV->m_renderTargetView,
      tmpDSV->m_depthStencilView);
  }

  void 
  buDXGraphicsAPI::clearRenderTargetView(
    WeakSPtr<buCoreRenderTargetView> _renderTargetView, float _color[4]) {
    if (_renderTargetView.expired()) {
      return;
    }
    auto RTVObj = _renderTargetView.lock();
    auto tmpRTV = reinterpret_cast<buDXRenderTargetView*>(RTVObj.get());

    m_deviceContext->ClearRenderTargetView(tmpRTV->m_renderTargetView, _color);
  }

  void 
  buDXGraphicsAPI::clearDepthStencilView(
    WeakSPtr<buCoreDepthStencilView> _depthStencilView,
    uint32 _clearFlags,
    float depth,
    int32 stencil) {
    if (_depthStencilView.expired()) {
      return;
    }

    auto DSVObj = _depthStencilView.lock();
    auto tmpDSV = reinterpret_cast<buDXDepthStencilView*>(DSVObj.get());
    m_deviceContext->ClearDepthStencilView(tmpDSV->m_depthStencilView,
      _clearFlags,
      depth,
      (UINT8)stencil);
  }

  void 
  buDXGraphicsAPI::setPrimitiveTopology(uint32 _topology) {
    m_deviceContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)_topology);
  }

  void
  buDXGraphicsAPI::updateSubresource(WeakSPtr<buCoreBuffer> _buffer,
                                          uint32 DstSubresource,
                                          void* pDstBox,
                                          void* pSrcData,
                                          uint32 SrcRowPitch,
                                          uint32 SrcDepthPitch) {
    if (_buffer.expired()) {
      return;
    }
    auto bufferObj = _buffer.lock();
    auto tmpbuffer = reinterpret_cast<buDXBuffer*>(bufferObj.get());
    m_deviceContext->UpdateSubresource(tmpbuffer->m_buffer,
      DstSubresource,
      (D3D11_BOX*)pDstBox,
      pSrcData,
      (UINT)SrcRowPitch,
      (UINT)SrcDepthPitch);
  }

  void 
  buDXGraphicsAPI::VSsetConstantBuffers(WeakSPtr<buCoreBuffer> _buffer,
                                             uint32 _startSlot,
                                             uint32 _numBuffers) {
    if (_buffer.expired()) {
      return;
    }
    auto bufferObj = _buffer.lock();
    auto tmpbuffer = reinterpret_cast<buDXBuffer*>(bufferObj.get());
    m_deviceContext->VSSetConstantBuffers(_startSlot,
      _numBuffers,
      &tmpbuffer->m_buffer);
  }

  void 
  buDXGraphicsAPI::PSsetConstantBuffers(WeakSPtr<buCoreBuffer> _buffer,
                                             uint32 _startSlot,
                                             uint32 _numBuffers) {
    if (_buffer.expired()) {
      return;
    }
    auto bufferObj = _buffer.lock();
    auto tmpbuffer = reinterpret_cast<buDXBuffer*>(bufferObj.get());
    m_deviceContext->PSSetConstantBuffers(_startSlot,
      _numBuffers,
      &tmpbuffer->m_buffer);
  }

  void 
  buDXGraphicsAPI::PSsetSamplers(WeakSPtr<buCoreSampler> _sampler,
                                      uint32 _startSlot,
                                      uint32 _numSamplers) {
    if (_sampler.expired()) {
      return;
    }
    auto samplerObj = _sampler.lock();
    auto tmpSampler = reinterpret_cast<buDXSampler*>(samplerObj.get());
    m_deviceContext->PSSetSamplers(_startSlot, _numSamplers, &tmpSampler->m_sampler);
  }

  void* 
  buDXGraphicsAPI::getDevice() {
    return reinterpret_cast<ID3D11Device*> (m_device);
  }

  void* 
  buDXGraphicsAPI::getDeviceContext() {
    return reinterpret_cast<ID3D11DeviceContext*> (m_deviceContext);
  }

  void* 
  buDXGraphicsAPI::getSwapchain() {
    return reinterpret_cast<IDXGISwapChain*> (m_swapchain);
  }

  Vector<void*> 
  buDXGraphicsAPI::getShaderResource() {
    return m_ShaderResources;
  }

}
