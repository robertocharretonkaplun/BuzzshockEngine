#include <buCoreConfig.h>

namespace buEngineSDK {
  buVector2F AppOptions::s_resolution = buVector2F(1350, 700);
  String AppOptions::s_windowName = "Buzzshock Engine";

  AppOptions& g_AppOptions() {
    return AppOptions::instance();
  }
}
