#include "sysAudio_OpenAL.h"

namespace buEngineSDK {
  void 
  sysAudio_OpenAL::createNewAudioResource(String filename, AudioType::E audioType) {
    AudioResource_OAL* audioResource = new AudioResource_OAL();
    audioResource->init(filename, audioType);
    m_audioResources.push_back(audioResource);

    //return audioResource;
  }

  void 
  sysAudio_OpenAL::update() {

  }

  void 
  sysAudio_OpenAL::render() {

  }

  void 
  sysAudio_OpenAL::destroy() {

  }

  void 
  sysAudio_OpenAL::updateAudioResource(uint32 _startSlot) {
    m_audioResources[_startSlot]->update();
  }

  void
  sysAudio_OpenAL::setAudioResource(uint32 _startSlot) {
    m_audioResources[_startSlot]->render();
  }
  
  void 
  sysAudio_OpenAL::destroyAudioResource(uint32 _startSlot) {
    m_audioResources.erase(m_audioResources.begin() + _startSlot);
  }
  
  void 
  sysAudio_OpenAL::playAudioResource(uint32 _startSlot, uint32 sourceState) {
    m_audioResources[_startSlot]->playAudio(sourceState);
  }
}

