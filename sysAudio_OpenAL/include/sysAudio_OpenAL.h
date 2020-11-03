#pragma once
#include <sysAudioAPI.h>
#include <AudioResource_OAL.h>

namespace buEngineSDK {
	class sysAudio_OpenAL : public sysAudioAPI
	{
	public:
		sysAudio_OpenAL() = default;
		~sysAudio_OpenAL() = default;

		SPtr<AudioResource>
		createNewAudio() override;
	private:

	};
	/**
	* @brief Plugging exportation data method.
	* @return Instance of audio.
	*/
	extern "C" BU_PLUGIN_EXPORT sysAudio_OpenAL *
		createAudioAPI() {
		auto pAudio = new sysAudio_OpenAL();
		return pAudio;
	}
}