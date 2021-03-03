#include "buTime.h"

#if BU_PLATFORM == BU_PLATFORM_WIN32
#include <Windows.h>
#endif

namespace buEngineSDK {
  buTime::buTime(float _time) : m_time(_time) {}

  float
  buTime::getDeltaTime() {

    static float t = 0.0f;
    static uint32 dwTimeStart = 0;
    uint32 dwTimeCur = GetTickCount();
    if (dwTimeStart == 0)
      dwTimeStart = dwTimeCur;
    t = (dwTimeCur - dwTimeStart) / 1000.0f;

    std::chrono::high_resolution_clock timer;
    auto start = timer.now();
    auto stop = timer.now();
    m_time = std::chrono::duration_cast<std::chrono::milliseconds>
      (stop - start).count() / 1000.0f;
    return m_time;
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
  
}
