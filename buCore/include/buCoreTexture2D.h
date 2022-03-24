/**
 * @file buCoreTexture2D.h
 * @version 1.0
 * @date 08/07/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of providing virtual methods for the buDXTexture2D class.
 */
#pragma once
#include"buPrerequisitesCore.h"
#include "buCommons.h"
namespace buEngineSDK {
 class buCoreTexture2D {
  public:
  /**
   * @brief Default constructor
   */
  buCoreTexture2D() = default;
  /**
   * @brief Destructor
   */
  ~buCoreTexture2D() {};
  /* 
   * @brief virtual Method that initialize the texture object.
   */
  virtual void
  init(String filepath, uint32 texFormat, uint32 usage, int32 width,
    int32 height, int32 mipLevels, int32 arraysize, int32 samplerDescCount,
       int32 samplerDescQuality, uint32 bindflags, uint32 CPUAccessFlags,
       uint32 miscFlags) = 0;

  /**
   * @brief Virtual method that initialize a texture loaded from file.
   */
  virtual void 
  init(String _filepath, int32 width, int32 height, TextureType::E textureType) = 0;
 };
}
