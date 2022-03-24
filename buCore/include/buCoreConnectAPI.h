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
#include <buPrerequisitesCore.h>
#include <buModule.h>

namespace buEngineSDK {
	class BU_CORE_EXPORT buCoreConnectAPI : public buModule<buCoreConnectAPI>
	{
	public:
		/**
		 * @brief Default constructor
		 */
		buCoreConnectAPI() = default;
		
		/**
		 * @brief Default destructor
		 */
		~buCoreConnectAPI() = default;

		/**
		 * @brief Method in charge of creating an instances of the class
		 */
		FORCEINLINE void
			setObject(buCoreConnectAPI* _api) {
			buCoreConnectAPI::_instance() = _api;
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


		virtual String
		getLobbyName() { return ""; };
	private:

	};

	/**
	 * @brief Export method for the class instance.
	 */
	BU_CORE_EXPORT buCoreConnectAPI&
	g_connectAPI();

	/**
	 * @brief Specific member uses as a instance to the class.
	 */
	using fnConnectAPIProt = buCoreConnectAPI * (*)();
}