/**
 * @file buCoreConfig.h
 * @version 
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once
#include <buPrerequisitesCore.h>
#include <buModule.h>
#include <buVector2F.h>

namespace buEngineSDK {
  class BU_CORE_EXPORT AppOptions : public buModule<AppOptions> {
  public:
    /**
   * @brief Instances of this object.
   */
  FORCEINLINE void 
  setObject(AppOptions* _api) {
    AppOptions::_instance() = _api;
  }
    static buVector2F s_resolution;
    static String s_windowName;
  };

  /**
  * @brief Export method for the class instance.
  */
  BU_CORE_EXPORT AppOptions&
    g_AppOptions();
  using fnAppOptionsProt = AppOptions * (*)();
}