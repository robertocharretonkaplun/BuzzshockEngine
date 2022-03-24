/**
 * @brief Class in charge of setting the client information related to sockets
 * and address where the information will be sende on the server
 */
#pragma once
#include <buPrerequisitesCore.h>

namespace buEngineSDK {
	class buCoreClient {
	public:
		/**
		 * @brief Default constructor
		 */
		buCoreClient() = default;
		/**
		 * @brief Default Constructor
		 */
		~buCoreClient() = default;

		/**
		 * @brief Virtual method in charge of initialize the client.
		 */
		virtual void
			create() {};

	private:

	};
}