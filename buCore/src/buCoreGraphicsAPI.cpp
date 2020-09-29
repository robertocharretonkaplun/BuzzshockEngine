#include "buCoreGraphicsAPI.h"

namespace buEngineSDK {
  buCoreGraphicsAPI& g_graphicsAPI() {
    return buCoreGraphicsAPI::instance();
  }
}
