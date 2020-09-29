/**
 * @file buSphere.h
 * @version 1.0
 * @date 10/06/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug None.
 */
#pragma once
#include "buPrerequisitesUtil.h"
#include "buVector3F.h"

namespace buEngineSDK {
 class BU_UTILITY_EXPORT buSphere
 {
 public:
  /**
   * @brief Default Constructor 
   */
  buSphere() = default;
  
  /**
   * @brief Constructor
   */
  buSphere(buVector3F& _center, float _radius); 
  
  /**
   * @brief Copy constructor
   */
  buSphere(const buSphere& _s);
  
  /**
   * @brief Destructor 
   */
  ~buSphere();
  
 public:
  /**
  * @brief 
  */
  buVector3F m_center;
  
  /**
  * @brief 
  */
  float m_radius;

 };
}
