#pragma once
#include "buPrerequisitesUtil.h"

namespace buEngineSDK {
	class buTime
	{
	public:
		/**
		 * @brief Default constructor
		 */
		buTime() = default;

		/**
		 * @brief Default destructor
		 */
		~buTime() = default;

		/**
		 * @brief Method in charge of getting the current date 
		 */
		const String 
		currDateTime();
	private:

	};
}