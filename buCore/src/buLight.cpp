#include "buLight.h"

namespace buEngineSDK {
  void
  buLight::init() {
    auto& graphMan = g_graphicsAPI();
    m_lightBuffer = graphMan.createBuffer(sizeof(LightBuffer));
  }

  void
  buLight::update(LightBuffer _lb){
    LB = _lb;
    auto& graphMan = g_graphicsAPI();
    graphMan.updateSubresource(m_lightBuffer, 0, nullptr, &LB, 0, 0);
  }

  void
  buLight::render() {
    auto& graphMan = g_graphicsAPI();
    graphMan.PSsetConstantBuffers(m_lightBuffer, BufferSlot::E::LIGHT, 1);
  }

}