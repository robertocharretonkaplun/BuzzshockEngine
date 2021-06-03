#pragma once
#include "buCOServer.h"

namespace buEngineSDK {
	class buServer : public buCOServer
	{
	public:
		buServer()  = default;
		~buServer() = default;

		/**
		 * @brief Virtual method in charge of initialize the server.
		 */
		void
		create() override;

		/**
		 * @brief Method in charge of returning the status of the server
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
		ServerInitType m_initType = ServerInitType::Basic;
		ServerStatus m_status = ServerStatus::Offline;
	};
}