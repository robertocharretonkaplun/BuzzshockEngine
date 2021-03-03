#include "buPrerequisitesUtil.h"
#include <chrono>
#include "buTimer.h"
#pragma once

namespace buEngineSDK {
	class BU_UTILITY_EXPORT buTime
	{
	public:
		/**
		 * @brief Default constructor
		 */
		buTime() = default;

		buTime(float _time);

		/**
		 * @brief Default destructor
		 */
		~buTime() = default;
		
		/**
		 * @brief Method in charge of getting the actual time value in micro seconds
		 */
		float
		getMicroseconds() const {return m_lastFrameTime; }

		/**
		 * @brief Method in charge of getting the current time in milliseconds.
		 */
		float
		getMilliseconds() const { return m_lastFrameTime; }

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

		void
		update();
	private:

	private:
		float m_time = 0.0f;
		float m_startTime = 0.0f;
		float m_lastFrameTime = 0.0f;
		SPtr<buTimer> m_timer;
		
	};
}
