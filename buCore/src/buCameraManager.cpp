#include "buCameraManager.h"

namespace buEngineSDK {
  BU_CORE_EXPORT buCameraManager& 
  g_CameraManager() {
    return buCameraManager::instance();
  }


  void 
  buCameraManager::update(buVector3F _eye,
    buVector3F _up,
    buVector3F _at,
    float _angle,
    float _aspectRatio,
    float _near,
    float _far) {
    for (int i = 0; i < m_cameras.size(); i++) {
      m_cameras[i].update(_eye,_up, _at, _angle, _aspectRatio, _near, _far);
    }
  }

  void
  buCameraManager::render() {
    for (int i = 0; i < m_cameras.size(); i++) {
        m_cameras[i].render();
    }
  }

  void 
  buCameraManager::AddCamera(String _name) {
    // Create a temp camera to be stored in the vector
    buCamera currCamera(_name, m_cameraCounter);
    // Store the current camera
    m_cameras.push_back(currCamera);
    // Increment the camera counter value for the id
    m_cameraCounter++;
  }

  void 
  buCameraManager::SetActiveCamera(uint32 _id) {
    // Set the main camera from ID 
    for (int i = 0; i < m_cameras.size(); i++) {
      if (m_cameras[i].m_id == _id) {
        m_cameras[i].m_isCameraActive = true;
      }
    }
  }

  buCamera& buCameraManager::GetActiveCamera() {
    for (int i = 0; i < m_cameras.size(); i++) {
      if (m_cameras[i].m_isCameraActive) {
        return m_cameras[i];
      }
    }
    //return buCamera();
  }

  void 
  buCameraManager::DeleteCamera(uint32 _id) {
    // Delete the camera from the vector 
    for (int i = 0; i < m_cameras.size(); i++) {
      if (m_cameras[i].m_id == _id) {
        m_cameras.erase(m_cameras.begin() + i);
      }
    }
  }
}