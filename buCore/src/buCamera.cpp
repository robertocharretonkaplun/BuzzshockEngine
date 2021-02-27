#include "buCamera.h"

namespace buEngineSDK {
  buCamera::buCamera(String _name, uint32 _id) {
    auto& graphMan = g_graphicsAPI();
    // Store the camera name and ID
    m_name = _name;
    m_id = _id;
    // Create constant buffers
    m_cameraBuffer = graphMan.createBuffer(sizeof(CBCamera));

    //m_cameraPos = { 0.0f,0.0f ,0.0f };
    //m_cameraTar = { 0.0f,0.0f ,0.0f };
    //m_cameraDir = m_cameraPos - m_cameraTar;
    //m_cameraDir.normalize();
    //
    //m_up = { 0.0f, 1.0f ,0.0f };
    //m_cameraRight = m_up.cross(m_cameraDir);
    //m_right.normalize();
    //m_cameraUp = m_cameraDir.cross(m_cameraRight);
  }

  void 
  buCamera::update(buVector3F _eye, buVector3F _up, buVector3F _at, 
    float _angle, float _aspectRatio, float _near, float _far) {
    // Set look at matrix
    //m_cameraData.view.lookAtMatrixLH(_eye, _at, _up);
    buVector3F tmp = _eye + _at;
    m_cameraData.view.lookAtMatrixLH(_eye, tmp, _up);

    // Set perspective matrix
    if (m_cameraType == CameraType::E::PROJECTION_TYPE) {
      m_cameraData.projection.perspectiveMatrixfovLH(_angle, _aspectRatio, _near, _far);
    }

    ////m_front = {m_cameraData.view.}
    //m_right = { m_cameraData.view.m_x0, m_cameraData.view.m_y0, m_cameraData.view.m_z0 };
    //m_up = {m_cameraData.view.}
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
    graphMan.VSsetConstantBuffers(m_cameraBuffer, BufferSlot::E::CAMERA, 1);
  }

  void
  buCamera::drawUI() {
    ImGui::Begin("CameraActor");
    ImGui::Separator();
    ImGui::Text("Camera Settings");
    ImGui::Separator();
    ImGui::End();
  }
}