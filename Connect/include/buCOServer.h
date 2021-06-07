/**
 * @brief Class in charge of setting the server information related to sockets 
 * and address where the information will be sended.
 */
#pragma once
#include "PrerequisitesConnect.h"

namespace buEngineSDK {
	enum ServerInitType {
		Default = 0,
		Basic = 1,
		Advanced = 2,
	};

	enum ServerStatus {
		Default = 0,
		Offline = 1,
		Waiting = 2,
		Connecting = 3,
		Ready = 4,
		Online = 5,
	};

	class buCOServer {
	public:
		/**
		 * @brief Default constructor
		 */
		buCOServer() = default;
		/**
		 * @brief Default Constructor
		 */
		~buCOServer() = default;

		/**
		 * @brief Virtual method in charge of initialize the server.
		 */
		virtual void
		create() {};

		/**
		 * @brief Virtual method in charge of returning the status of the server
		 */
		virtual ServerStatus 
		getServerStatus() {return ServerStatus(); }

		/**
		 * @brief Virtual method in charge of returning the server initialization
		 * type.
		 */
		virtual ServerInitType
		getServerInitType() { return ServerInitType(); }
	private:

	};
}