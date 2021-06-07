/**
 * @brief Class in charge of setting the client information related to sockets 
 * and address where the information will be sende on the server
 */
#pragma once
#include "PrerequisitesConnect.h"

namespace buEngineSDK {
	class buCOClient {
	public:
		/**
		 * @brief Default constructor
		 */
		buCOClient() = default;
		/**
		 * @brief Default Constructor
		 */
		~buCOClient() = default;

		/**
		 * @brief Virtual method in charge of initialize the client.
		 */
		virtual void
		create() {};

	private:

	};
}