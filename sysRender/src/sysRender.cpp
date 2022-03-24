#include "sysRender.h"

namespace buEngineSDK {
  sysRender& g_renderAPI() {
    return sysRender::instance();
  }
}
