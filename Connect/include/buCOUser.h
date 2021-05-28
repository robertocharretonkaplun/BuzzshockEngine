/**
 * @brief Class in charge of setting the client information in a object. 
 */
#pragma once
#include "PrerequisitesConnect.h"

namespace buEngineSDK {
	class buCOUser
	{
	public:
		/**
		 * @brief Default constructor
		 */
		buCOUser() = default;
		/**
		 * @brief Default destructor
		 */
		~buCOUser() = default;

		/**
		 * @brief Method in charge of initialize the user information.
		 */
		virtual void
		create() {};


	private:

	};
}