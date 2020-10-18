#include "buCameraManager.h"

namespace buEngineSDK {
  BU_CORE_EXPORT buCameraManager& g_CameraManager() {
    return buCameraManager::instance();
  }
}