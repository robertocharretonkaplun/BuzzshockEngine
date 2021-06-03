/**
 * @brief This class is in charge of creating all the virtual methods that will 
 * be necessary to create, implement, use, and manage the connect features from
 * the tool.
 * This class works as a module for future instances in the engine, so it will be
 * necessary to be manage as a module when you call it in Connect_API -> Director
 * class.
 *
 */
#pragma once
#include "PrerequisitesConnect.h"
#include "buModule.h"
#include "buCOServer.h"
#include "buCOUser.h"

namespace buEngineSDK {
	class BU_CONNECT_EXPORT buCODirector : public buModule<buCODirector>
	{
	public:
		/**
		 * @brief Default constructor
		 */
		buCODirector() = default;
		
		/**
		 * @brief Default destructor
		 */
		~buCODirector() = default;

		/**
		 * @brief Method in charge of creating an instances of the class
		 */
		FORCEINLINE void
			setObject(buCODirector* _api) {
			buCODirector::_instance() = _api;
		}
		
	public:
		/**
		 * @brief Virtual method in charge of creating a server from the connect project.
		 */
		virtual void
		createServer() {};

		/**
		 * @brief Method in charge of creating a virtual method for the initialization
		 * of a lobby with server features and  objects
		 */
		virtual void
		createLobby() {};

		/**
		 * @brief Method in charge of creating a client from the connect project.
		 */
		virtual void
		createClient() {};

		/**
		 * @brief Method in charge of creating the information of an invidivial user.
		 */
		virtual void
		createUser() {};

		/**
		 * @brief Method in charge of creating a virtual method for the Nucleus (Server)
		 * from NVIDIA Omniverse data.
		 */
		virtual void
		createNucleus() {};

		/**
	   * @brief Method in charge of creating a virtual method for the creation of a 
		 * Connector from NVIDIA Omniverse.
		 */
		virtual void
		createConnector() {};

		/**
		 * @brief Virtual method in charge of getting the server status of the tool.
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

	/**
	 * @brief Export method for the class instance.
	 */
	BU_CONNECT_EXPORT buCODirector&
		g_connect();

	/**
	 * @brief Specific member uses as a instance to the class.
	 */
	using fnConnectProt = buCODirector * (*)();
}