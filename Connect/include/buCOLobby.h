/**
 * @brief Class in charge of creating a lobby that will create a server and 
 * has the capability to add clients to the sesion.
 * This class will have all the information of the sesion, server information and
 * client information, also, it will keep record of all the data sended to 
 * multiple apps.
 */
#pragma once
#include "PrerequisitesConnect.h"

namespace buEngineSDK {
	class buCOLobby
	{
	public:
		/**
		 * @brief Default constructor
		 */
		buCOLobby() = default;

		/**
		 * @brief Default destructor
		 */
		~buCOLobby() = default;

		/**
		 * @brief Virtual method in charge of creating the basic initializations 
		 * of a lobby.
		 */
		virtual void
		create() {};

	private:

	};
}
