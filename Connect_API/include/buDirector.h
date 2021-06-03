/**
 * @brief This class is in charge of creating all the methods that will
 * be necessary to create, implement, use, and manage the connect features from
 * the tool.
 * This class works as a module for future instances in the engine, so it will be
 * necessary to be manage as a module when you call it in Connect_API -> Director
 * class.
 */
#pragma once
#include "buCODirector.h"
#include "buServer.h"
namespace buEngineSDK {
	class buDirector : public buCODirector
	{
	public:
		/**
		 * @brief Default constructor
		 */
		buDirector() = default;
		
		/**
		 * @brief Default destructor
		 */
		~buDirector() = default;

	public:
		/**
		 * @brief Method in charge of creating a server from the connect project.
		 */
		void
		createServer() override;
		/**
		 * @brief Method in charge of creating a method for the initialization
		 * of a lobby with server features and  objects
		 */
		void
		createLobby() override;

		/**
		 * @brief Method in charge of creating a client from the connect project.
		 */
		void
		createClient() override;

		/**
		 * @brief Method in charge of creating the information of an invidivial user.
		 */
		void
		createUser() override;

		/**
		 * @brief Method in charge of creating a method for the Nucleus (Server)
		 * from NVIDIA Omniverse data.
		 */
		void
		createNucleus() override;

		/**
	   * @brief Method in charge of creating a method for the creation of a 
		 * Connector from NVIDIA Omniverse.
		 */
		void
		createConnector() override;

		/**
		 * @brief Method in charge of getting the server status of the tool.
		 */
		ServerStatus 
		getServerStatus() override;

		/**
		 * @brief Method in charge of returning the server initialization
		 * type.
		 */
		ServerInitType
		getServerInitType() override;
	private:
	private:
		buServer m_server;
	};
	/**
	* @brief Plugging exportation data method.
	* @return Instance of audio.
	*/
	extern "C" BU_PLUGIN_EXPORT buDirector *
		createConnectAPI() {
		auto pDirector = new buDirector();
		return pDirector;
	}
}