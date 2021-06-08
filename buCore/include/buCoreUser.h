/**
 * @brief Class in charge of setting the client information in a object.
 */
#pragma once
#include <buPrerequisitesCore.h>

namespace buEngineSDK {
	class buCoreUser
	{
	public:
		/**
		 * @brief Default constructor
		 */
		buCoreUser() = default;
		/**
		 * @brief Default destructor
		 */
		~buCoreUser() = default;

		/**
		 * @brief Method in charge of initialize the user information.
		 */
		virtual void
		create() {};


	private:

	};
}