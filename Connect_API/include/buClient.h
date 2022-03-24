#pragma once
#include <buCoreClient.h>
namespace buEngineSDK {
	class buClient : public buCoreClient
	{
	public:
		/**
		 * @brief Default Constructor
		 */
		buClient()  = default;

		/**
		 * @brief Default Destructor
		 */
		~buClient() = default;

		/**
		 * @brief Virtual method in charge of initialize the server.
		 */
		void
		create() override;
		
	private:

	};
}