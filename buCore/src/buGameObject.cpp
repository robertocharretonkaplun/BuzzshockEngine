#include "buGameObject.h"

namespace buEngineSDK {
  void 
  buGameObject::init() {
    auto& graphMan = g_graphicsAPI();
    // Create Change Every Frame
    changeEveryFrame = graphMan.createBuffer(sizeof(CBChangesEveryFrame));
    
  }
  void
  buGameObject::update(buVector3F _pos, buVector3F _rot,
                       buVector3F _scal, float _angle) {
    auto& graphMan = g_graphicsAPI();
    m_transform.update(_pos, _rot, _scal, _angle);
    cb.mWorld = m_transform.m_world;
    graphMan.updateSubresource(changeEveryFrame, 0, nullptr, &cb, 0, 0);
    
  }

  void
  buGameObject::render(TopologyType::E _typology) {
    auto& graphMan = g_graphicsAPI();

    // Set change every frame constant buffers
    graphMan.VSsetConstantBuffers(changeEveryFrame, 1, 1);
    //graphMan.VSsetConstantBuffers(m_lightBuffer, 3, 1);
    
    // Set change every frame buffer.
    graphMan.PSsetConstantBuffers(changeEveryFrame, 1, 1);
    // Render if the go is active
    if (m_isActive) {
      for (uint32 i = 0; i < m_model.m_meshes.size(); ++i) {
        auto& currMesh = m_model.m_meshes[i];
        // Set Mesh texture
        for (uint32 j = 0; j < m_model.m_textures.size(); j++) {
          auto& currTexture = m_model.m_textures[j];
          graphMan.PSSetShaderResources(currTexture, j, 1);
        }
        // Set primitive topology
        graphMan.setPrimitiveTopology(_typology);
        // Set vertex buffer
        graphMan.setVertexBuffers(m_model.m_vertexBuffer);
        // Set Index buffer
        graphMan.setIndexBuffer(m_model.m_indexBuffer,
          Format::E::BU_FORMAT_R32_UINT,
          0);
        // Draw
        graphMan.drawIndexed(currMesh.m_numIndices, currMesh.m_baseIndex, 0);
      }

    }
  }
}