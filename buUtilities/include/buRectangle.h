/**
 * @file buRectangle.h
 * @version 1.0 
 * @date 11/06/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once
#include "buPrerequisitesUtil.h"

namespace buEngineSDK {
 class BU_UTILITY_EXPORT buRectangle
 {
 public:
  /**
   * @brief Default constructor 
   */
  buRectangle() = default;
  
  /**
   * @brief Constructor
   */
  buRectangle(float _x, float _y, float _width, float _lenght);
  
  /**
   * @brief Destructor
   */
  ~buRectangle();
  
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  float 
  getArea();
  
  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  float
  getPerimeter();
  
 public:
   /**
    * @brief Position in x coordinate
    */
   float m_x = 0.0f;

   /**
    * @brief Position in y coordinate
    */
   float m_y = 0.0f;

  /**
   * @brief Width value of the rectangle.
   */
  float m_width = 0.0f;
  
  /**
   * @brief Lenght of the rectangle.
   */
  float m_lenght = 0.0f;

 };
}
