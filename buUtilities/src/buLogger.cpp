#include "buLogger.h"

namespace buEngineSDK {
  const String buLogger::m_fileName = "Data/Logs/Log.txt";
  buLogger* buLogger::m_this = NULL;
  std::ofstream buLogger::m_logfile;

  void
  buLogger::Log(String _message/*, MessageType::E _type*/) {
    m_logfile.open(m_fileName.c_str(), std::ios::out | std::ios::app);
    m_logfile << m_time.currDateTime() << ":\t";
    m_logfile << _message << "\n";
    m_logfile.close();
  }

  void 
  buLogger::LogError(String _message) {
    m_logfile.open(m_fileName.c_str(), std::ios::out | std::ios::app);
    m_logfile << m_time.currDateTime() << ":\t";
    //m_logfile << _message;
    m_logfile << "Error in line: \t" <<  __LINE__ << ", in file [ "<< __FILE__ << " ]";
    m_logfile.close();
  }

  buLogger& 
  buLogger::operator<<(const String& sMessage) {
    m_logfile << "\n" << m_time.currDateTime() << ":\t";
    m_logfile << sMessage << "\n";
    return *this;
  }

  Vector<String> buLogger::GetLogDataFromFile()
  {
    Vector<String> logs;
    std::ifstream logFile("Data/Logs/Log.txt");
    String line;
    while (std::getline(logFile, line))
    {
      logs.push_back(line);
    }
    return logs;
  }

  buLogger* 
  buLogger::GetLogger() {
    if (m_this == nullptr) {
      m_this = new buLogger();
      //m_logfile.open(m_fileName.c_str(), std::ios::out | std::ios::app);
    }
    return m_this;
  }
}