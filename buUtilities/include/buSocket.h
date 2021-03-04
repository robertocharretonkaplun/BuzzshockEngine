#include "buPrerequisitesUtil.h"
#include <WS2tcpip.h>
#include <thread>
#pragma comment (lib, "Ws2_32.lib")

namespace buEngineSDK {

	class buSocket {
	public:
		buSocket();
		~buSocket();

		void
		init();
	private:

	};
}