#include "sysAudio_OpenAL.h"

namespace buEngineSDK {
  SPtr<AudioResource> 
  sysAudio_OpenAL::createNewAudio() {
    auto pAudioResource = std::make_shared<AudioResource>();

    auto audioResource = reinterpret_cast<AudioResource_OAL*>(pAudioResource.get());
    audioResource->init();
    return pAudioResource;
  }
}

