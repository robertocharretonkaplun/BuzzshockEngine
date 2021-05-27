#include "buCODirector.h"

namespace buEngineSDK {
  buCODirector& g_connect() {
    return buCODirector::instance();
  }
}