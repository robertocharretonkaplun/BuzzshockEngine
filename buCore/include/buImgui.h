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
  };
}
