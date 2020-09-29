/**
 * @file buBox.h
 * @version 1.0
 * @date 10/06/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of providing a box.
 * @bug None.
 */
#pragma once
#include "buPrerequisitesUtil.h"
#include "buVector3F.h"

namespace buEngineSDK {
  class BU_UTILITY_EXPORT buBox
  {
   public:
   /**
    * @brief Default constructor
    */
   buBox() = default;
  
   /**
    * @brief Constructor
    */
   buBox(float _x, float _y, float _width, float _height, float _lenght);
   
   /**
   * @brief Constructor in charge of initialize a box with the basic information of a vector.
   * @param _v Vector component for the intialization of the width, height and lenght.
   */
   buBox(float _x, float _y, const buVector3F& _v);
   
   /**
    * @brief Copy constructor
    */
   buBox(const buBox& _b);
   
   /**
    * @brief Destructor
    */
   ~buBox();
   
   /**
   * @brief Method that returns the volume of the box.
   * @param None.
   * @return A volume.
   * @bug None.
   */
   float
   getVolume();
   
   public:
   /**
    * @brief Position in x coordinate 
    */
   float m_x;

   /**
    * @brief Position in y coordinate
    */
   float m_y;

   /**
    * @brief
    */
   float m_width;
   
   /**
    * @brief
    */
   float m_height;
   
   /**
    * @brief
    */
   float m_length;
  
  };
}
