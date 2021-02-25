#include "buTime.h"
#include <chrono>
#if BU_PLATFORM == BU_PLATFORM_WIN32
#include <Windows.h>
#endif

namespace buEngineSDK {
  float 
  buTime::getCurrentTime() {
    
    return 0.0f;
  }

  float
  buTime::getDeltaTime() {

    return 0.0f;
  }


  const String
    buTime::currDateTime() {
    time_t     now = time(NULL);
    struct tm  tstruct;
    char       buf[80];
    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "%Y-%m-%d|%X", &tstruct);
    return buf;
  }
  
  void 
  buTime::update() {
    // Update the game time
    static float t = 0.0f;
    static uint32 dwTimeStart = 0;
    uint32 dwTimeCur = GetTickCount();
    if (dwTimeStart == 0)
      dwTimeStart = dwTimeCur;
    t = (dwTimeCur - dwTimeStart) / 1000.0f;

    std::chrono::high_resolution_clock timer;
    auto start = timer.now();
  }
}