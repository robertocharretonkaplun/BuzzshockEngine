#include "buDirector.h"

namespace buEngineSDK {
  void 
  buDirector::createServer() {
    m_server.create();
  }
  
  void
  buDirector::createLobby() {
  }
  
  void 
  buDirector::createClient() {
  }

  void 
  buDirector::createUser() {
  }
  
  void 
  buDirector::createNucleus() {
  }

  void 
  buDirector::createConnector() {
  }
  
  ServerStatus 
  buDirector::getServerStatus() {
    return m_server.getServerStatus();
  }
  
  ServerInitType
  buDirector::getServerInitType() {
    return m_server.getServerInitType();
  }
}