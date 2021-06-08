#pragma once
#include <buPrerequisitesUtil.h>
#include <buCoreLobby.h>
#include <buCoreServer.h>
namespace buEngineSDK {
	class buLobby : public buCoreLobby {
	public:
		buLobby () = default;
		~buLobby ()= default;

		/**
		 * @brief Method in charge of creating the basic initializations 
		 * of a lobby.
		 */
		void
		create() override;
	private:
		String m_lobbyName = "Lobby";
		String m_hostName = "Host";
		uint32 m_hostID = 0000;
		String m_password = "admin123";
		uint32 m_clientCount = 5;
		uint32 m_maxClientCount = 64;
		ServerStatus m_serverStatus = ServerStatus::OFFLINE;

	};
}