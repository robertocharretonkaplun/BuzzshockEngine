#pragma once

#include "buPrerequisitesUtil.h"
#include "buPlatformMath.h"
#if BU_PLATFORM == BU_PLATFORM_LINUX
#include "buLinuxMath.h"
#endif

namespace buEngineSDK {
  using buMath = buPlatformMath;
}
