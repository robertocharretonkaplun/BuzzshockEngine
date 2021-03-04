#include "buSocket.h"

namespace buEngineSDK {
  void 
  buSocket::init() {
    // Initialize windsock
    WSADATA some_kind_of_data;
    WSAStartup(MAKEWORD(2, 2), &some_kind_of_data);

    // Create Server Socket
    sockaddr_in listen_address;
    listen_address.sin_family = AF_INET;
    listen_address.sin_port = htons(666);
    listen_address.sin_addr.S_un.S_addr = INADDR_ANY;

    SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);

    bind(listen_socket, (sockaddr*)&listen_address, sizeof(listen_address));

    listen(listen_socket, SOMAXCONN);

    // Wait for connection

    SOCKET client = accept(listen_socket, nullptr, nullptr);

    char buffer[1024]{ 0 };

    recv(client, buffer, sizeof(buffer), 0);

    std::cout << buffer << std::endl;

    // Pause
    closesocket(client);
    WSACleanup();

  }
}