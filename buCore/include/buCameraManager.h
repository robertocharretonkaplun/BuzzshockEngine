#pragma once
#include <buPrerequisitesCore.h>
#include <buModule.h>
#include <buCamera.h>

namespace buEngineSDK {
  class BU_CORE_EXPORT buCameraManager : public buModule<buCameraManager>
  {
  public: 
    buCameraManager() = default;
    ~buCameraManager() = default;

    /**
     * @brief Instances of this object.
     */
    FORCEINLINE void 
    setObject(buCameraManager* _api) {
      buCameraManager::_instance() = _api;
    }

    void 
    update(buVector3F _eye,
					 buVector3F _up, 
					 buVector3F _at,
					 float _angle,
					 float _aspectRatio, 
					 float _near, 
					 float _far);
  
    void
    render();

    void 
    AddCamera(String _name);
  
    void
    SetActiveCamera(uint32 _id);

    buCamera & 
    GetActiveCamera();

    void 
    DeleteCamera(uint32 _id);

  private:
    Vector<buCamera> m_cameras;
    uint32 m_cameraCounter;
  };
  /**
   * @brief Export method for the class instance.
   */
  BU_CORE_EXPORT buCameraManager&
    g_CameraManager();

  /**
   * @brief Specific member uses as a instance to the class.
   */
  using fnCameraManagerProt = buCameraManager * (*)();
}

