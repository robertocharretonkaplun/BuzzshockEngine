/**
 * @file buCoreVieport.h
 * @version 1.0
 * @date 08/07/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of initialize the virtual methods for the buDXviewport
 * class.
 */
#pragma once
#include "buPrerequisitesCore.h"

namespace buEngineSDK {
 class buCoreViewport {
 public:
  /**
    * @brief Default constructor
    */
  buCoreViewport() = default;
 	/**
 	 * @brief Destructor
 	 */
 	~buCoreViewport() {};
  /**
   * @brief Virtual method that initialize the object.
   */
  virtual void 
  init(float width, float height, float minDepth, float maxDepth, 
       float topLeftX, float topLeftY) = 0;
 };
}
