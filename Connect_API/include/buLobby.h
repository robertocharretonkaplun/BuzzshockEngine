#pragma once
#include "buCOLobby.h"

namespace buEngineSDK {
	class buLobby : public buCOLobby {
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

	};
}