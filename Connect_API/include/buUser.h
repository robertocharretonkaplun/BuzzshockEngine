#pragma once
#include <buCoreUser.h>

namespace buEngineSDK {
	enum userType	{
		Default = 0,
		Server = 1,
		Client = 2,
	};
	class buUser : public buCoreUser {
	public:
		buUser() = default;
		~buUser() = default;

		/**
		 * @brief Method in charge of initialize the user information.
		 */
		void
		create() override;
	private:

	};
}