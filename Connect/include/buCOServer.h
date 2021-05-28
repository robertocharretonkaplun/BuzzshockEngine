/**
 * @brief Class in charge of setting the server information related to sockets 
 * and address where the information will be sended.
 */
#pragma once
#include "PrerequisitesConnect.h"

namespace buEngineSDK {
	class buCOServer {
	public:
		/**
		 * @brief Default constructor
		 */
		buCOServer();
		/**
		 * @brief Default Constructor
		 */
		~buCOServer();

		/**
		 * @brief Virtual method in charge of initialize the server.
		 */
		virtual void
		create() {};

	private:

	};
}