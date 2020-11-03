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

		virtual SPtr<AudioResource>
		createNewAudio() { return nullptr; }

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