#pragma once
#include "PrerequisitesAudio.h"

namespace AudioType {
	enum E {
		MONO = 0,
		STEREO = 1,
	};
}

namespace buEngineSDK {
	class AudioResource
	{
	public:
		AudioResource() = default;
		~AudioResource() = default;

		virtual void 
		init(String filename, AudioType::E audioType) {}

		virtual void
		update() {}

		virtual void
		render() {}

		virtual void 
		destroy() {}

		virtual void
		playAudio(uint32 sourceState) {}
	};
}