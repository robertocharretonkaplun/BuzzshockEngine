#pragma once
#include "buPrerequisitesUtil.h"
namespace MessageType {
	enum E {
		DEFAULT,
		INFO, 
		WARNING,
		ERROR
	};
}
namespace buEngineSDK {
	class BU_UTILITY_EXPORT buLogger
	{
	public:
		buLogger() = default;
		~buLogger();

		void
		Log(String _message, MessageType::E _type);

	private:

	};
}