#pragma once
#include <sysAudioAPI.h>
#include <AudioResource_OAL.h>

namespace buEngineSDK {
	class sysAudio_OpenAL : public sysAudioAPI
	{
	public:
		sysAudio_OpenAL() = default;
		~sysAudio_OpenAL() = default;

		void
		createNewAudioResource(String filename, AudioType::E audioType) override;

		void
		update() override;

		void
		render() override;

		void 
		destroy() override;

		void
		updateAudioResource(uint32 _startSlot) override;

		void
		setAudioResource(uint32 _startSlot) override;

		void
		destroyAudioResource(uint32 _startSlot) override;

		void
		playAudioResource(uint32 _startSlot, uint32 sourceState) override;
	private:
		Vector<AudioResource_OAL*> m_audioResources;
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