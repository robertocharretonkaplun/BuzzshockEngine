/**
 * @file buRadians.h
 * @version 1.0
 * @date 11/06/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of returning a radian value.
 * @bug None.
 */
#pragma once
#include "buPrerequisitesUtil.h"

namespace buEngineSDK {
 class BU_UTILITY_EXPORT buRadians
 {
 public:
  /**
   * @brief Default Constructor
   */
  buRadians() = default;

  /**
   * @brief Constructor
   */
  buRadians(float _r);

  /**
   * @brief Copy constructor
   */
  buRadians(const buRadians& _r);

  /**
   * @brief Destructor 
   */
  ~buRadians();

  /** 
  * @brief Method that returns the degree of the value.
  * @param None.
  * @return Degree value.
  * @bug None.
  */
  float 
  getDegree();

  /** 
   * @brief 
   * @param 
   * @return 
   * @bug 
   */
  float 
  getRadians();

 public:
  /**
   * @brief Radians value.
   */
  float m_radians;

 };
}
