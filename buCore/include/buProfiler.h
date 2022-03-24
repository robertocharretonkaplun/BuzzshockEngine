#pragma once
#include <buPrerequisitesCore.h>
#include <buTimer.h>
#include <buCommons.h>
namespace buEngineSDK {
	class BU_CORE_EXPORT buProfiler
	{
	public:
		buProfiler() = default;
		~buProfiler() = default;

		void
		ui();
	private:
		// Timer for benchmarking 
		buTimer m_timer;
	};
}