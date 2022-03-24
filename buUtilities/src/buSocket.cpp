#include "buSocket.h"

namespace buEngineSDK {
  void
  buSocket::initClient() {
    buLogger logError;

    m_status = WSAStartup(MAKEWORD(2, 2), &m_data);
    if (m_status != 0) {
      logError.LogError("Error initializing the winsocket", m_status);
      WSACleanup();
    }
    // Create connection socket
    m_connect_address.sin_family = AF_INET;
    m_connect_address.sin_port = htons(666);
    m_status = inet_pton(AF_INET, "127.0.0.1", &m_connect_address.sin_addr);
    if (m_status == WSAEAFNOSUPPORT) {
      logError.LogError("Error connecting the server", m_status);
    }
    m_connection_socket = socket(AF_INET, SOCK_STREAM, 0);
    m_status = connect(m_connection_socket, (sockaddr*)&m_connect_address, sizeof(m_connect_address));
    if (m_status == SOCKET_ERROR) {
      logError.LogError("Error connecting to server", m_status);
      closesocket(m_connection_socket);
      WSACleanup();
    }
    // Send data to server
    std::string MSG = "Test Client message...";
    m_status = send(m_connection_socket, MSG.c_str(), MSG.size() + 1, 0);
    if (m_status != 0) {
      logError.LogError("Error sending data to server", m_status);
    }

    // Cleanup
    closesocket(m_connection_socket);
    WSACleanup();
  }

  void 
  buSocket::initServer() {

    WSAStartup(MAKEWORD(2, 2), &m_data);

    // Create Server Socket

    m_listen_address.sin_family = AF_INET;
    m_listen_address.sin_port = htons(666);
    m_listen_address.sin_addr.S_un.S_addr = INADDR_ANY;

    m_listen_socket = socket(AF_INET, SOCK_STREAM, 0);

    bind(m_listen_socket, (sockaddr*)&m_listen_address, sizeof(m_listen_address));

    listen(m_listen_socket, SOMAXCONN);

    // Wait for connection

    m_socket = accept(m_listen_socket, nullptr, nullptr);

    char buffer[1024]{ 0 };

    recv(m_socket, buffer, sizeof(buffer), 0);

    std::cout << buffer << std::endl;

    // Pause
    closesocket(m_socket);
    WSACleanup();
  }
  
  void
  buSocket::destroy() {
  }
  
  void
  buSocket::initializeWinSock() {
    m_status = WSAStartup(MAKEWORD(2, 2), &m_data);
    if (m_status != 0) {
      std::cout << "ERROR INITIALIZING WINSOCK \n";
      WSACleanup();
      buLogger logError;
      logError.LogError("Error");
    }
  }
  
  void 
  buSocket::createConnectionSocket() {
    
    m_connect_address.sin_family = AF_INET;
    m_connect_address.sin_port = htons(666);
    inet_pton(AF_INET, "127.0.0.1", &m_connect_address.sin_addr);

    m_connection_socket = socket(AF_INET, SOCK_STREAM, 0);
    m_status = connect(m_connection_socket, (sockaddr*)&m_connect_address, sizeof(m_connect_address));
    if (m_status == SOCKET_ERROR) {
      std::cout << "CONNECTION ERROR \n";
      closesocket(m_connection_socket);
      WSACleanup();
    }
  }

  void
  buSocket::createServerSocket() {
    m_listen_address.sin_family = AF_INET;
    m_listen_address.sin_port = htons(666);
    m_listen_address.sin_addr.S_un.S_addr = INADDR_ANY;

    m_listen_socket = socket(AF_INET, SOCK_STREAM, 0);

    bind(m_listen_socket, (sockaddr*)&m_listen_address, sizeof(m_listen_address));

    listen(m_listen_socket, SOMAXCONN);
  }

  void
  buSocket::sendData(String _msg) {
    send(m_connection_socket, _msg.c_str(), _msg.size() + 1, 0);
  }

  
  void
  buSocket::getData() {
    SOCKET client = accept(m_listen_socket, nullptr, nullptr);

    char buffer[1024]{ 0 };

    recv(client, buffer, sizeof(buffer), 0);

    std::cout << buffer << std::endl;
  }

  void
  buSocket::cleanUp() {
    WSACleanup();
  }
}