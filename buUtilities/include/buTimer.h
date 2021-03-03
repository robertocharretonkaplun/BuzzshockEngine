/**
 * Ref1: https://stackoverflow.com/questions/1825720/c-high-precision-time-measurement-in-windows
 * Ref2: https://stackoverflow.com/questions/16299029/resolution-of-stdchronohigh-resolution-clock-doesnt-correspond-to-measureme
 */
#pragma once
#include "buPrerequisitesUtil.h"
#include <chrono>

namespace buEngineSDK {
	using std::chrono::high_resolution_clock;
	using std::chrono::time_point;
	class BU_UTILITY_EXPORT buTimer {

	public:
		/**
		 * @brief Default constructor
		 */
		buTimer() = default;
		
		/**
		 * @brief Default destructor
		 */
		~buTimer() = default;

		/**
		 * @brief Method that get the milliseconds from the start time to the new time.
		 */
    uint64
    getMilliseconds() const;

		/**
		 * @brief Method that get the microseconds from the start time to the new time.
		 */
    uint64
    getMicroseconds() const;

    uint64
    getInitialMilliseconds() const;

    void
    restartTime();
	private:
		high_resolution_clock m_highResClock;

		time_point<high_resolution_clock> m_startTime;
	};
}