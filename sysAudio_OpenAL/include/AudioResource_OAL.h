/**
* @file AudioResource_OAL.h
* @version 02Nov2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
* @brief Class in charge of set the basic initializations for the audio resource
* Tutorial ref: https://www.youtube.com/watch?v=WvND0djMcfE&ab_channel=enigmatutorials
* OpenAL Website ref: http://www.openal.org
* OpenAL Ref: https://github.com/kcat/openal-soft
* AudioFile Ref: https://github.com/adamstark/AudioFile (It has copyright) 
* Paper about OpenAL ref:
* https://research.ncl.ac.uk/game/mastersdegree/workshops/audio/Sound%20Workshop.pdf
* OpenAL Specifications ref: https://openal.org/documentation/openal-1.1-specification.pdf
*/
#pragma once
#include <AudioResource.h>
#include <PrerequisitesAudio.h>
#include "AL\include\al.h"
#include "AL\include\alc.h"
#include "AL\AudioFile\AudioFile.h"

namespace buEngineSDK {
	class AudioResource_OAL : public AudioResource
	{
	public:
		AudioResource_OAL() = default;
		~AudioResource_OAL();

		void 
		init(String filename, AudioType::E audioType) override;

		void
		update() override;

		void
		render() override;

		void 
		destroy() override;

		void
		playAudio(uint32 sourceState) override;
	private:
		ALCdevice* device;
		ALCcontext* context;
		AudioFile<float> monoSoundFile;
		Vector<uint8_t> monoPCMDataBytes;
		ALuint monoSoundBuffer;
		ALuint monoSource;
		AudioFile<float> stereoSoundFile;
		Vector<uint8_t> stereoPCMDataBytes;
		ALuint stereoSoundBuffer;
		ALuint stereoSource;
		AudioType::E m_audioType;
		bool m_playAudio = false;
	};
}