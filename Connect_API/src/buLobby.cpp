#include "buLobby.h"

namespace buEngineSDK {
    void 
    buLobby::create(String _lobbyName, 
                    String _hostName,
                    uint32 _hostID,
                    String _password, 
                    ServerInitType _type) {
      m_lobbyName = _lobbyName;
      m_hostName = _hostName;
      m_hostID = _hostID;
      m_password = _password;
    }
}