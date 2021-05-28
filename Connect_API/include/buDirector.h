#pragma once
#include "buCODirector.h"
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

	private:

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