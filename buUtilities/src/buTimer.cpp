#include "buTimer.h"

namespace buEngineSDK {
  using namespace std::chrono;

  uint64 
  buTimer::getMilliseconds() const {
    auto newTime = m_highResClock.now();
    duration<double> dur = newTime - m_startTime;
    return duration_cast<milliseconds>(dur).count();
  }

  uint64
  buTimer::getMicroseconds() const {
    auto newTime = m_highResClock.now();
    duration<double> dur = newTime - m_startTime;
    return duration_cast<microseconds>(dur).count();
  }


  uint64 
  buTimer::getInitialMilliseconds() const {
    nanoseconds startTimeNs = m_startTime.time_since_epoch();
    return duration_cast<milliseconds>(startTimeNs).count();
  }

  void
  buTimer::restartTime() {
    m_startTime = m_highResClock.now();
  }
}