#include "buGameApp_UnitTest.h"
#include <buMath.h>

namespace buEngineSDK
{
  buGameApp_UnitTest::buGameApp_UnitTest() {
    m_World = buMatrix4x4::IDENTITY;
    m_view = buMatrix4x4::ZERO;
    m_projection = buMatrix4x4::ZERO;
  }

  buGameApp_UnitTest::~buGameApp_UnitTest() {
  }

  void 
  buGameApp_UnitTest::onCreate() {
    auto& graphMan = g_graphicsAPI();
    // Initialize 
    // Create the back buffer
    Log("GraphMan - Creating backbuffer ...");
    backBuffer = graphMan.createTexture2D(m_screenWidth,
                                          m_screenHeight, 
                                          DXGI_FORMAT_D24_UNORM_S8_UINT,
                                          D3D11_BIND_DEPTH_STENCIL,
                                          1);

    // Create depth stencil texture
    Log("GraphMan - Creating depth Stenil ...");
    depthStencil = graphMan.createTexture2D(m_screenWidth,
                                            m_screenHeight, 
                                            DXGI_FORMAT_D24_UNORM_S8_UINT,
                                            D3D11_BIND_DEPTH_STENCIL,
                                            1);

    // Create depth stencil View
    Log("GraphMan - Creating depth Stenil View...");
    depthStencilView = graphMan.createDepthStencilView();

    // Create render target view
    Log("GraphMan - Creating Render Target View...");
    renderTargetView = graphMan.createRenderTargetView();

    // Create Viewport
    viewport = graphMan.createViewport((float)m_screenWidth, 
                                       (float)m_screenHeight,
                                       0.0f,
                                       1.0f,
                                       0.0f,
                                       0.0f);

    // Create Vertex Shader
    Log("GraphMan - Creating Vertex Shader...");
    vertexShader = graphMan.createVertexShader();
    vertexShader->init(L"Data/Shaders/CubeProjectFor.fx", "VS", "vs_5_0");

    // Create input layout
    Log("GraphMan - Creating Input Layout...");
    inputLayout = graphMan.createInputLayout();
    Vector<INPUT_LAYOUT_DESC> layoutDesc;
    layoutDesc.resize(4);
    // Positions
    layoutDesc[0].semanticName = "POSITION";
    layoutDesc[0].semanticIndex = 0;
    layoutDesc[0].format = DXGI_FORMAT_R32G32B32_FLOAT;
    layoutDesc[0].inputSlot = 0;
    layoutDesc[0].alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    layoutDesc[0].inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    layoutDesc[0].instanceDataStepRate = 0;
    // texcoords
    layoutDesc[1].semanticName = "TEXCOORD";
    layoutDesc[1].semanticIndex = 0;
    layoutDesc[1].format = DXGI_FORMAT_R32G32_FLOAT;
    layoutDesc[1].inputSlot = 0;
    layoutDesc[1].alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    layoutDesc[1].inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    layoutDesc[1].instanceDataStepRate = 0;
    // Bones
    layoutDesc[2].semanticName = "BLENDINDICES";
    layoutDesc[2].semanticIndex = 0;
    layoutDesc[2].format = DXGI_FORMAT_R32G32B32A32_UINT;
    layoutDesc[2].inputSlot = 0;
    layoutDesc[2].alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    layoutDesc[2].inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    layoutDesc[2].instanceDataStepRate = 0;
    // Weights
    layoutDesc[3].semanticName = "BLENDWEIGHT";
    layoutDesc[3].semanticIndex = 0;
    layoutDesc[3].format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    layoutDesc[3].inputSlot = 0;
    layoutDesc[3].alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    layoutDesc[3].inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    layoutDesc[3].instanceDataStepRate = 0;

    inputLayout->init(&layoutDesc[0], layoutDesc.size());

    // Create Pixel shader 
    Log("GraphMan - Creating Pixel Shader...");
    pixelShader = graphMan.createPixelShader();
    pixelShader->init(L"Data/Shaders/CubeProjectFor.fx", "PS", "ps_5_0");

    //Log("Resource Manager - Loading Mesh from file [Data/Models/AdvanceDancing.fbx]");
    //m_resourceManager->loadMesh("Data/Models/AdvanceDancing.fbx");
    //m_GONames.push_back(m_resourceManager->getModel()->TexName);
  
    // Create Never Changes
    Log("GraphMan - Creating Constant Buffers...");
    neverChanges = graphMan.createBuffer(sizeof(CBNeverChanges),
                                         D3D11_BIND_CONSTANT_BUFFER, 
                                         0,
                                         nullptr);
    // Create Change On Resize
    changeOnResize = graphMan.createBuffer(sizeof(CBChangeOnResize), 
                                           D3D11_BIND_CONSTANT_BUFFER, 
                                           0,
                                           nullptr);
    // Create Change Every Frame
    changeEveryFrame = graphMan.createBuffer(sizeof(CBChangesEveryFrame), 
                                             D3D11_BIND_CONSTANT_BUFFER, 
                                             0,
                                             nullptr);

    BonesTranform = graphMan.createBuffer(sizeof(cbBonesTranform),
                                          D3D11_BIND_CONSTANT_BUFFER, 
                                          0,
                                          nullptr);

    // Sampler
    Log("GraphMan - Creating Samplers...");
    sampler = graphMan.createSampler();
    sampler->init(D3D11_FILTER_MIN_MAG_MIP_LINEAR,
                  D3D11_TEXTURE_ADDRESS_WRAP,
                  D3D11_TEXTURE_ADDRESS_WRAP,
                  D3D11_TEXTURE_ADDRESS_WRAP,
                  D3D11_COMPARISON_NEVER,
                  0,
                  D3D11_FLOAT32_MAX);

    //m_graphicsAPI->createDeviceAndSwapChain(m_window);
    m_graphicsAPI->createTextureForBackBuffer(backBuffer);
    //m_graphicsAPI->createTexture(depthStencil);
    m_graphicsAPI->createDepthStencilView(depthStencil, depthStencilView);
    m_graphicsAPI->createRenderTargetView(backBuffer, renderTargetView);
   //m_graphicsAPI->setShaderSubresource(backBuffer);
    m_graphicsAPI->createVertexShader(vertexShader);
    m_graphicsAPI->createInputLayout(vertexShader, inputLayout);
    m_graphicsAPI->createPixelShader(pixelShader);
    // Load texture
    Log("Resource Manager - Loading Image from file [Data/Textures/1KDiff.jpeg]");
    meshTexture = m_graphicsAPI->loadImageFromFile("Data/Textures/1KDiff.jpeg",
                                                   m_screenWidth,
                                                   m_screenHeight);

    
    // Create sampler
    m_graphicsAPI->createSamplerState(sampler);
    // Create view matrix
    m_World = buMatrix4x4(0.2f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.2f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.2f, 0.0f,
                          0.0f, 0.0f, 0.0f, 0.2f);

    
  }

  void 
  buGameApp_UnitTest::onDestroy() {
    m_graphicsAPI->cleanUp();
    // Shutdown module
    buCoreGraphicsAPI::shutDown();
    //delete graphicAPI;
    m_directXPlug.destroy();
  }

  void 
  buGameApp_UnitTest::onUpdate(float _deltaTime) {
    m_graphicsAPI->update();

    auto currModel = m_resourceManager->getModel();
    currModel->update(_deltaTime);

    // Initialize View matrix
    buVector3F Eye(m_eye[0], m_eye[1], m_eye[2]);
    buVector3F At(m_at[0], m_at[1], m_at[2]);
    buVector3F Up(m_up[0], m_up[1], m_up[2]);

    m_view.lookAtMatrixLH(Eye, At, Up);

    // Initialize the projection matrix
    m_projection.perspectiveMatrixfovLH(buDegrees(45).getRadians(),
      static_cast<float>(m_screenWidth) /
      static_cast<float>(m_screenHeight),
      m_near,
      m_far);

    // Set Mesh transform
    buVector3F scale(m_Scale[0] * m_EngineScale, m_Scale[1] * m_EngineScale, m_Scale[2] * m_EngineScale);
    m_World.scaleMatrix(scale);
    buVector3F rotation(m_Rotation[0], m_Rotation[1], m_Rotation[2]);
    m_World.rotateMatrix(rotation, m_angle);
    if (m_isRotating) {
      m_angle += _deltaTime;
    }
    else {
      m_angle = 0;
    }

    buVector3F position(m_position[0], m_position[1], m_position[2]);
    m_World.translateMatrix(position);
    //m_World.transpose();
    m_meshColor.x = 1; //(buMath::sinf(_deltaTime * 1.0f) + 1.0f) * 0.5f;
    m_meshColor.y = 1; //(buMath::cosf(_deltaTime * 3.0f) + 1.0f) * 0.5f;
    m_meshColor.z = 1; //(buMath::sinf(_deltaTime * 5.0f) + 1.0f) * 0.5f;
  }


  void 
  buGameApp_UnitTest::onRender() {
    CBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = m_view;
    m_graphicsAPI->updateSubresource(neverChanges,
      0,
      nullptr,
      &cbNeverChanges,
      0,
      0);

    CBChangeOnResize cbChangesOnResize;
    cbChangesOnResize.mProjection = m_projection;
    m_graphicsAPI->updateSubresource(changeOnResize,
      0,
      nullptr,
      &cbChangesOnResize,
      0,
      0);

    cbBonesTranform cbBonestransform;
    auto currModel = m_resourceManager->getModel();

    if (-1 < currModel->m_currAnimation)
    {
      for (uint32 i = 0; i < currModel->m_bonesTransforms.size(); ++i) {
        cbBonestransform.boneTransform[i] = currModel->m_bonesTransforms[i];
      }
      m_graphicsAPI->updateSubresource(BonesTranform,
        0,
        nullptr,
        &cbBonestransform,
        0,
        0);
    }

    // Set viewport
    m_graphicsAPI->setViewport(viewport);
    // Set Render Targets
    m_graphicsAPI->setRenderTargets(1, renderTargetView, depthStencilView);
    // Clear the back buffer 
    m_graphicsAPI->clearRenderTargetView(renderTargetView, ClearColor);
    // Clear depth stencil view
    m_graphicsAPI->clearDepthStencilView(depthStencilView,
      D3D11_CLEAR_DEPTH,
      1.0f,
      0);
    // Update variables that change once per frame
    CBChangesEveryFrame cb;
    //m_World.transpose();
    cb.mWorld = m_World;
    cb.vMeshColor = m_meshColor;

    m_graphicsAPI->updateSubresource(changeEveryFrame, 0, nullptr, &cb, 0, 0);
    // Set Vertex Shader
    m_graphicsAPI->setVertexShader(vertexShader);
    // Set never changes constant buffers
    m_graphicsAPI->VSsetConstantBuffers(neverChanges, 0, 1);
    // Set changes on resize constant buffersm_numVertices
    m_graphicsAPI->VSsetConstantBuffers(changeOnResize, 1, 1);
    // Set change every frame constant buffers
    m_graphicsAPI->VSsetConstantBuffers(changeEveryFrame, 2, 1);
    // Set Bones Transform constant buffer
    m_graphicsAPI->VSsetConstantBuffers(BonesTranform, 3, 1);
    // Set the input layout
    m_graphicsAPI->setInputLayout(inputLayout);
    // Set Pixel shader
    m_graphicsAPI->setPixelhader(pixelShader);
    // Set change every frame buffer.
    m_graphicsAPI->PSsetConstantBuffers(changeEveryFrame, 2, 1);
    // Set samplers
    m_graphicsAPI->PSsetSamplers(sampler, 0, 1);

    //auto currModel = m_resourceManager->getModel();
    auto meshNum = currModel->m_meshes.size();

    for (uint32 i = 0; i < meshNum; ++i) {
      auto& currMesh = currModel->m_meshes[i];
      // Set Mesh texture
      m_graphicsAPI->PSSetShaderResources(meshTexture, 0, 1);
      // Set primitive topology
      m_graphicsAPI->setPrimitiveTopology(currMesh.m_topology);
      // Set vertex buffer
      m_graphicsAPI->setVertexBuffers(currModel->m_vertexBuffer);
      // Set Index buffer
      m_graphicsAPI->setIndexBuffer(currModel->m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
      // Draw
      m_graphicsAPI->drawIndexed(currMesh.m_numIndices, currMesh.m_baseIndex, 0);
    }

    //// Present
    //m_graphicsAPI->present(0, 0);
  }
}
