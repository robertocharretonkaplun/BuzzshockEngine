#pragma once
#include <buPrerequisitesDX.h>
#include "buImgui.h"


namespace buEngineSDK {
  class buDXImgui : public buImgui
  {
  public:
    buDXImgui();
    ~buDXImgui();
    /**
     * @brief
     */
    void
    init(void* _window, void* _device, void* _deviceContext) override;

    /**
     * @brief
     */
    void
    update() override;

    /**
     * @brief
     */
    void
    render() override;
  private:

  };
}