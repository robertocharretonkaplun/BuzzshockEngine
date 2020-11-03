#include "sysAudioAPI.h"

namespace buEngineSDK {
  sysAudioAPI& g_audioAPI() {
    return sysAudioAPI::instance();
  }
}
