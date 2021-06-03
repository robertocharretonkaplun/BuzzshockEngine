#include "buServer.h"

namespace buEngineSDK {
  void 
  buServer::create() {
  }

  ServerStatus 
  buServer::getServerStatus() {
    return m_status;
  }

  ServerInitType 
  buServer::getServerInitType() {
    return m_initType;
  }
}