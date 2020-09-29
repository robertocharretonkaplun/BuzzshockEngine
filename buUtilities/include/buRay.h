/**
 * @file buRay.h
 * @version 1.0
 * @date 10/06/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of providing a technique that computes the visibility 
 * between two points (a ray). I take inspiration from
 * this site: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays 
 * @bug None.
 */
#pragma once
#include "buPrerequisitesUtil.h"
#include "buVector3F.h"

namespace buEngineSDK {
 class BU_UTILITY_EXPORT buRay
 {
 public:
  /**
   * @brief Default constructor 
   */
  buRay() = default;

  /**
   * @brief Constructor 
   */
  buRay(buVector3F _origin, buVector3F _direction, float _distance);

  /**
   * @brief Copy constructor
   */
  buRay(const buRay& _r);

  /**
   * @brief Destructor
   */
  ~buRay();

  /** 
  * @brief Method in charge of providing a point defined by an origin and 
  * a direction
  * @param buVector3F _direction A direction vector.
  * @param float _distance A scalar value
  * @return A point.
  * @bug None.
  */
  buVector3F Ray(buVector3F _direction, float _distance);

 public:
  /**
   * @brief Is the distance from the origin of the point.
   */
  float m_distance;

  /**
   * @brief Ray origin
   */
  buVector3F m_origin;

  /**
   * @brief Ray direction (Neet to be normalized)
   */
  buVector3F m_direction;
 };
}
