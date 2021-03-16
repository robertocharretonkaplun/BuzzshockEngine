#include "buPrerequisitesUtil.h"
#include <WS2tcpip.h>
#include <thread>
#include <buLogger.h>
#pragma comment (lib, "Ws2_32.lib")

namespace buEngineSDK {

	class BU_UTILITY_EXPORT buSocket {
	public:
		/**
		 * @brief Default constructor
		 */
		buSocket() = default;	

		/**
		 * @brief Default destructor 
		 */
		~buSocket() = default;

		/**
		 * @brief Method that is in charge of creating a temporal client for testing 
		 * porpuses.
		 */
		void
		initClient();

		/**
		 * @brief Method that is in charge of creating a temporal server for testing
		 * porpuses.
		 */
		void
		initServer();

		/**
		 * @brief Method that realize the resource of the socket information
		 */
		void
		destroy();

		/**
		 * @brief Method in charge of initialize the winsocket
		 */
		void
		initializeWinSock();

		/**
		 * @brief Method that creates the connection with the socket
		 */
		void
		createConnectionSocket();

		/**
		 * @brief 
		 */
		void
		createServerSocket();

		/**
		 * @brief Method that send the information to the server 
		 */
		void
		sendData(String _msg);

		/**
		 * @brief Method that recive the information from the client. This function
		 * is important to get info from clients and inputs + comands with other services.
		 */
		void
		getData();

		/**
		 * @brief Method in charge of cleaning up the socket value.
		 */
		void 
		cleanUp();


		
	private:
		uint32 m_status;
		SOCKET m_socket;
		SOCKET m_listen_socket;
		SOCKET m_connection_socket;
		WSADATA m_data;
		sockaddr_in m_connect_address;
		sockaddr_in m_listen_address;
	};
}