#include "buLogger.h"

namespace buEngineSDK {
  const String buLogger::m_fileName = "Log.txt";
  buLogger* buLogger::m_this = NULL;
  std::ofstream buLogger::m_logfile;

  buLogger::~buLogger() {
  }

  void
  buLogger::Log(String _message, MessageType::E _type) {
    m_logfile << m_time.currDateTime() << ":\t";
    m_logfile << _message << "\n";
  }

  buLogger& 
  buLogger::operator<<(const String& sMessage) {
    m_logfile << "\n" << m_time.currDateTime() << ":\t";
    m_logfile << sMessage << "\n";
    return *this;
  }

  buLogger* 
  buLogger::GetLogger() {
    if (m_this == nullptr) {
      m_this = new buLogger();
      m_logfile.open(m_fileName.c_str(), std::ios::out | std::ios::app);
    }
    return m_this;
  }
}