#include "BuAudio.h"

namespace buEngineSDK {
  buAudio::buAudio() {
    // Initialize Open AL
    device = alcOpenDevice(NULL); // open default device
    if (device != NULL) {
      context = alcCreateContext(device, NULL); // create context
      if (context != NULL) {
        alcMakeContextCurrent(context); // set active context
      }
    }


    std::cout << "OpenAL Device: " << alcGetString(device, ALC_DEVICE_SPECIFIER) << std::endl;
    OpenAL_ErrorCheck(device);
    // Create a listener in 3D space (ie the player)
    alec(alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f));
    alec(alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f));
    ALfloat forwardAndUpVectors[] = {
      /*Forward = */ 1.0f, 0.0f, 0.0f,
      /*Up = */ 0.0f, 1.0f, 0.0f,
    };

    alec(alListenerfv(AL_ORIENTATION, forwardAndUpVectors));

    // Create buffers to store the sound data
    if (!monoSoundFile.load("../dependencies/TestSound_Mono.wav")) {
      std::cerr << "Failed to load the test mono sound file." << std::endl;
    }

    monoSoundFile.writePCMToBuffer(monoPCMDataBytes);

    auto convertFileToOpenALFormat = [](const AudioFile<float>& audioFile) {
      int bitDepth = audioFile.getBitDepth();
      if (bitDepth == 16) {
        return audioFile.isStereo() ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
      }
      else if (bitDepth == 8) {
        return audioFile.isStereo() ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
      }
      else {
        return -1;
      }
    };

    alec(alGenBuffers(1, &monoSoundBuffer));
    alec(alBufferData(monoSoundBuffer,
      convertFileToOpenALFormat(monoSoundFile),
      monoPCMDataBytes.data(),
      monoPCMDataBytes.size(),
      monoSoundFile.getSampleRate()));

    if (!stereoSoundFile.load("../dependencies/TestSound.wav")) {
      std::cerr << "Failed to load the test stereo sound file." << std::endl;
    }

    stereoSoundFile.writePCMToBuffer(stereoPCMDataBytes);

    alec(alGenBuffers(1, &stereoSoundBuffer));
    alec(alBufferData(stereoSoundBuffer,
      convertFileToOpenALFormat(stereoSoundFile),
      stereoPCMDataBytes.data(),
      stereoPCMDataBytes.size(),
      stereoSoundFile.getSampleRate()));

    // Create a sound source for mono that plays our mono sound
    alec(alGenSources(1, &monoSource));
    alec(alSource3f(monoSource, AL_POSITION, 1.0f, 0.0f, 0.0f));
    alec(alSource3f(monoSource, AL_VELOCITY, 0.0f, 0.0f, 0.0f));
    alec(alSourcef(monoSource, AL_PITCH, 1.0f));
    alec(alSourcef(monoSource, AL_GAIN, 1.0f));
    alec(alSourcei(monoSource, AL_LOOPING, AL_FALSE));
    alec(alSourcei(monoSource, AL_BUFFER, monoSoundBuffer));

    // Create a sound source for mono that plays our mono sound
    
    alec(alGenSources(1, &stereoSource));
    alec(alSource3f(stereoSource, AL_POSITION, 1.0f, 0.0f, 0.0f));
    alec(alSource3f(stereoSource, AL_VELOCITY, 0.0f, 0.0f, 0.0f));
    alec(alSourcef(stereoSource, AL_PITCH, 1.0f));
    alec(alSourcef(stereoSource, AL_GAIN, 1.0f));
    alec(alSourcei(stereoSource, AL_LOOPING, AL_FALSE));
    alec(alSourcei(stereoSource, AL_BUFFER, stereoSoundBuffer));
    
  }
  void buAudio::update()
  {

    // Play the mono sound source
    alec(alSourcePlay(monoSource));
    ALint sourceState;

    alec(alGetSourcei(monoSource, AL_SOURCE_STATE, &sourceState));

    //while (sourceState == AL_PLAYING) {
    //  // Loop until we are done
    //  alec(alGetSourcei(monoSource, AL_SOURCE_STATE, &sourceState));
    //}
    // Play the stereo sound source
    alec(alSourcePlay(stereoSource));
    alec(alGetSourcei(stereoSource, AL_SOURCE_STATE, &sourceState));
    switch (sourceState)
    {
    case AL_INITIAL:
      break;
    case AL_PLAYING:
      alec(alGetSourcei(monoSource, AL_SOURCE_STATE, &sourceState));
      alec(alGetSourcei(stereoSource, AL_SOURCE_STATE, &sourceState));
      break;
    case AL_PAUSED:
      break;
    case AL_STOPPED:
      break;
    default:
      break;
    }


    while (sourceState == AL_PLAYING) {
      // Loop until we are done
    }

    
  }
  void buAudio::destroy() {
    // Clean our resources
    alec(alDeleteSources(1, &monoSource));
    alec(alDeleteSources(1, &stereoSource));
    alec(alDeleteBuffers(1, &monoSoundBuffer));
    alec(alDeleteBuffers(1, &stereoSoundBuffer));
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
  }
}