/**
 * @file buDegrees.h
 * @version 1.0
 * @date 11/06/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of returning a degree value.
 * @bug None.
 */
#pragma once
#include "buPrerequisitesUtil.h"

namespace buEngineSDK {
  class BU_UTILITY_EXPORT buDegrees
  {
  public:
   /**
    * @brief Default constructor
    */
   buDegrees() = default;

   /**
    * @brief Constructor
    */
   buDegrees(float _d);

   /**
    * @brief Copy constructor
    */
   buDegrees(const buDegrees& _d);

   /**
    * @brief Constructor
    */
   ~buDegrees();

   /**
    * @brief Method that returns the radian of the value.
    * @param None.
    * @return Radian value.
    * @bug None.
    */
   float
   getRadians();

   /** 
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   float
   getDegrees();

  public:
   /**
    * @brief Degrees value.
    */
   float m_degrees;

  };
}
