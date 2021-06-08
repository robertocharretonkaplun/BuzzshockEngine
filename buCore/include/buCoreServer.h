/**
 * @brief Class in charge of setting the server information related to sockets 
 * and address where the information will be sended.
 */
#pragma once
#include <buPrerequisitesCore.h>

namespace buEngineSDK {
	enum ServerInitType {
		BASIC = 0,
		ADVANCED = 1,
	};

	enum ServerStatus {
		OFFLINE = 0,
		WAITING = 1,
		CONNECTING = 2,
		READY = 3,
		ONLINE = 4,
	};

	enum ServerAction {
		GET = 0,
		PUT = 1,
		POST = 2,
	};

	enum SessionType {
		BASICC = 0, // Host + 4 clients / users
		EXTRA = 1, // Host + 6 clients / users
		PREFERRED = 2, // Host + 8 clients / users
		CUSTOM = 3, // Host + any amount of clients / users (limit 64 - must define)
	};

	class buCoreServer {
	public:
		/**
		 * @brief Default constructor
		 */
		buCoreServer() = default;
		/**
		 * @brief Default Constructor
		 */
		~buCoreServer() = default;

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