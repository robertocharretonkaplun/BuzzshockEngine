#include "buGameApp_UnitTest.h"
#include <buMath.h>

namespace buEngineSDK
{
  buGameApp_UnitTest::buGameApp_UnitTest() {
    m_World = buMatrix4x4(0.2f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.2f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.2f, 0.0f,
                          0.0f, 0.0f, 0.0f, 0.2f);
    m_view = buMatrix4x4::ZERO;
    m_projection = buMatrix4x4::ZERO;
  }

  buGameApp_UnitTest::~buGameApp_UnitTest() {
  }

  void 
  buGameApp_UnitTest::onCreate() {
    // Initialize 
    auto& graphMan = g_graphicsAPI();
    WString shaderFileName = L"Normal.fx";
    // Create Vertex Shader
    vertexShader = graphMan.createVertexShader(shaderFileName); // Put the entry point

    // Create input layout
    inputLayout = graphMan.createInputLayout(vertexShader, 
      { "POSITION" , "TEXCOORD", "NORMAL", "TANGENT", "BLENDINDICES", "BLENDWEIGHT"});

    // Create Pixel shader 
    pixelShader = graphMan.createPixelShader(shaderFileName);
  
    // Create Never Changes
    neverChanges = graphMan.createBuffer(sizeof(CBNeverChanges));
    // Create Change On Resize
    changeOnResize = graphMan.createBuffer(sizeof(CBChangeOnResize));
    // Create Change Every Frame
    changeEveryFrame = graphMan.createBuffer(sizeof(CBChangesEveryFrame));

    BonesTranform = graphMan.createBuffer(sizeof(cbBonesTranform));
    
    // Create sampler
    sampler = graphMan.createSampler();

    // Load texture
    meshTexture = m_graphicsAPI->loadImageFromFile("a.png",
                                                   m_screenWidth,
                                                   m_screenHeight);

    normalTexture = m_graphicsAPI->loadImageFromFile("n.png",
                                                   m_screenWidth,
                                                   m_screenHeight);
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

    // Set View Direction
    buVector4F viewDir(Eye.x, Eye.y, Eye.z, 1.0f);
    cb.viewDirection = viewDir;

    // Set Mesh transform
    buVector3F scale(m_Scale[0] * m_EngineScale, 
                     m_Scale[1] * m_EngineScale, 
                     m_Scale[2] * m_EngineScale);
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
    
    // Update variables that change once per frame
    
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

    auto meshNum = currModel->m_meshes.size();

    for (uint32 i = 0; i < meshNum; ++i) {
      auto& currMesh = currModel->m_meshes[i];
      // Set Mesh texture
      m_graphicsAPI->PSSetShaderResources(meshTexture, 0, 1);
      m_graphicsAPI->PSSetShaderResources(normalTexture, 1, 1);
      // Set primitive topology
      m_graphicsAPI->setPrimitiveTopology(currMesh.m_topology);
      // Set vertex buffer
      m_graphicsAPI->setVertexBuffers(currModel->m_vertexBuffer);
      // Set Index buffer
      m_graphicsAPI->setIndexBuffer(currModel->m_indexBuffer, 
                                    Format::E::BU_FORMAT_R32_UINT,
                                    0);
      // Draw
      m_graphicsAPI->drawIndexed(currMesh.m_numIndices, currMesh.m_baseIndex, 0);
    }
  }
}
