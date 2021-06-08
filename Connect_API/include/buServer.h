#pragma once
#include <buCoreServer.h>

namespace buEngineSDK {
	class buServer : public buCoreServer
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
		ServerInitType m_initType = ServerInitType::BASIC;
		ServerStatus m_status = ServerStatus::OFFLINE;
		uint32 m_sesionID = 0;
		String m_sesionName = "Default Session";
		
	};
}