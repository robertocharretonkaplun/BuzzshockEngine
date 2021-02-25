#include "buPrerequisitesUtil.h"
#pragma once

namespace buEngineSDK {
	class buTime
	{
	public:
		/**
		 * @brief Default constructor
		 */
		buTime(float _time = 0.0f) : m_time(_time) {}

		/**
		 * @brief Default destructor
		 */
		~buTime() = default;
		
		/**
		 * @brief Method in charge of getting the current time
		 */
		float 
		getCurrentTime();

		/**
		 * @brief Method in charge of getting the actual time value in seconds
		 */
		float
		getSeconds() const {return m_time;}

		/**
		 * @brief Method in charge of getting the current time in milliseconds.
		 */
		float
		getMilliseconds() const { return m_time * 1000.0f; }

		/**
		 * @brief Method in charge of getting the current time step by step.
		 */
		float 
		getDeltaTime();

		/**
		 * @brief Method in charge of getting the current date 
		 */
		const String 
		currDateTime();
	private:
		void 
		update();

	private:
		float m_time = 0.0f;
	};
}