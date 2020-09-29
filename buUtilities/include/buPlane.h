/**
* @file buPlane.h
* @version 1.0
* @date 06/06/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
* @brief Class in charge of providing a plane.
* @bug None.
*/
#pragma once
#include "buPrerequisitesUtil.h"
#include "buVector4F.h"
#include "buVector3F.h"


namespace buEngineSDK {
  class BU_UTILITY_EXPORT buPlane
  {
  public:
   /**
    * @brief Default constructor
    */
   buPlane() = default;
  
   /**
    * @brief Constructor 
    */
   buPlane(const buVector4F& V);
  
    /**
    * @brief Constructor 
    */
   buPlane(float X, float Y, float Z, float W);
  
   /**
    * @brief Constructor
    * @param _v1 First point in the plane.
    * @param _v2 Second point in the plane.
    * @param _v3 Third point in the plane.
    * @return None.
    * @bug None. 
    */
   buPlane(const buVector3F& _v1, const buVector3F& _v2, const buVector3F& _v3);
  
   /**
    * @brief Destructor
    */
   ~buPlane();
  
   /**
    * @brief Calculates distance between plan and a point in the space.
    * @param V Represents the other point
    * @return A positive number if it is in front of the plane and 
    * a negative number if it is behind the plane.
    * @bug None.
    */
   float
   planDot(const buVector3F& V) const;
  
   /**
    * @brief Method that returns a inverse plane.
    * @param None.
    * @return A flip plane.
    * @bug None.
    */
   buPlane
    flip() const;
  
  public:
   /**
    * @brief Member in charge of storing the point of the x.
    */
   float x;
   
   /**
    * @brief Member in charge of storing the point of the y.
    */
   float y;
   
   /**
    * @brief Member in charge of storing the point of the z.
    */
   float z;
   
   /**
    * @brief Member in charge of storing the point of the w.
    */
   float w;
  
  };
}
