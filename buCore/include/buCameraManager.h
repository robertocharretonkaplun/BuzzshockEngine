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

  virtual void 
  update() {};
  
  virtual void
  render() {};

  virtual void 
  AddCamera(String _name) {};
  
  virtual void
  SetActiveCamera(uint32 _id) {};

  virtual void 
  DeleteCamera(String _name) {};

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