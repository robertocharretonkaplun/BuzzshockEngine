#pragma once
#include "PrerequisitesAudio.h"
#include "AudioResource.h"
#include <buModule.h>

namespace buEngineSDK {
	class BU_AUDIO_EXPORT sysAudioAPI : public buModule<sysAudioAPI>
	{
	public:
		/**
		 * @brief Default constructor
		 */
		sysAudioAPI() = default;
		/**
		 * @brief Default Destructor
		 */
		~sysAudioAPI() = default;
		
		/**
		 * @brief Instances of this object.
		 */
		FORCEINLINE void
			setObject(sysAudioAPI* _api) {
			sysAudioAPI::_instance() = _api;
		}

		virtual void
		update() {}

		virtual void
		render() {}

		virtual void 
		destroy() {}

		virtual void
		createNewAudioResource(String filename, AudioType::E audioType) { }

		virtual void
		updateAudioResource(uint32 _startSlot) {}
		
		virtual void
		setAudioResource(uint32 _startSlot) {}

		virtual void
		destroyAudioResource(uint32 _startSlot) { }
		
		virtual void
		playAudioResource(uint32 _startSlot, uint32 sourceState) { }
	};
	/**
 * @brief Export method for the class instance.
 */
	BU_AUDIO_EXPORT sysAudioAPI&
		g_audioAPI();

	/**
	 * @brief Specific member uses as a instance to the class.
	 */
	using fnAudioAPIProt = sysAudioAPI * (*)();
}