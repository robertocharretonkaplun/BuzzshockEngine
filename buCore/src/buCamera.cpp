#include "buCamera.h"

namespace buEngineSDK {
  buCamera::buCamera(String _name, uint32 _id) {
    auto& graphMan = g_graphicsAPI();
    // Store the camera name and ID
    m_name = _name;
    m_id = _id;
    // Create constant buffers
    m_cameraBuffer = graphMan.createBuffer(sizeof(CBCamera));
  }

  void 
  buCamera::update(buVector3F _eye, buVector3F _up, buVector3F _at, 
    float _angle, float _aspectRatio, float _near, float _far) {
    // Set look at matrix
    m_cameraData.view.lookAtMatrixLH(_eye, _at, _up);
    // Set perspective matrix
    m_cameraData.projection.perspectiveMatrixfovLH(_angle, _aspectRatio, _near, _far);
  }

  void 
  buCamera::render() {
    auto& graphMan = g_graphicsAPI();
    
    graphMan.updateSubresource(m_cameraBuffer,
      0,
      nullptr,
      &m_cameraData,
      0,
      0);
    // Set the constant buffers
    graphMan.VSsetConstantBuffers(m_cameraBuffer, 0, 1);
  }
}