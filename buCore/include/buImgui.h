#include "buPrerequisitesCore.h"
#include "buCommons.h"
#pragma once
namespace buEngineSDK {
  class buImgui {
  public:
    buImgui() = default;
    ~buImgui() = default;

    /**
     * @brief
     */
    virtual void
      init(void* _window, void* _device, void* _deviceContext) {};

    /**
     * @brief
     */
    virtual void
      update() {};

    /**
     * @brief
     */
    virtual void
      render() {};

    void
		vec3Control(String label, 
                float* values, 
                float resetValues = 0.0f,
                float columnWidth = 100.0f);
  };
}
