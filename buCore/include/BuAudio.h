/**
* @file BuAudio.h
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
#include <buPrerequisitesCore.h>
#include "AL\include\al.h"
#include "AL\include\alc.h"
#include "AL\AudioFile\AudioFile.h"

#define OpenAL_ErrorCheck(message)\
{\
	ALenum error = alGetError();\
	if(error != AL_NO_ERROR)\
	{\
		std::cerr << "OpenAL Error: " << error << " with call for " << #message << std::endl;\
	}\
}\

#define alec(FUNCTION_CALL)\
FUNCTION_CALL;\
OpenAL_ErrorCheck(FUNCTION_CALL)


namespace buEngineSDK {
	class BU_CORE_EXPORT buAudio
	{
	public:
		buAudio();
		~buAudio() = default;
		void update();
		void destroy();

	public:
		const ALCchar* defaultDeviceString;// = alcGetString(nullptr, ALC_CAPTURE_DEVICE_SPECIFIER);
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
	private:
		
	};
}