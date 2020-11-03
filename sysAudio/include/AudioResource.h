#pragma once
#include "PrerequisitesAudio.h"

namespace buEngineSDK {
	class AudioResource
	{
	public:
		AudioResource() = default;
		~AudioResource() = default;

		virtual void 
		init() {}

		virtual void
		update() {}

		virtual void
		render() {}

		virtual void 
		destroy() {}
	};
}