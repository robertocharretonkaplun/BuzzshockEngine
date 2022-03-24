#include "buCoreConnectAPI.h"

namespace buEngineSDK {
  buCoreConnectAPI& g_connectAPI() {
    return buCoreConnectAPI::instance();
  }
}