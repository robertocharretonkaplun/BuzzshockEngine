#include "buTime.h"

namespace buEngineSDK {
  const String 
  buTime::currDateTime() {
    time_t     now = time(NULL);
    struct tm  tstruct;
    char       buf[80];
    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
  }
}