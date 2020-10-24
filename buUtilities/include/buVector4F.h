/**
 * @file buVector4F.h 
 * @version 1.0
 * @date 05/06/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of providing a 4D float vector.
 * @bug None.
 */
#pragma once
#include "buPrerequisitesUtil.h"
#include "buMath.h"

namespace buEngineSDK {
 class BU_UTILITY_EXPORT buVector4F
 {
 public:
  /**
   * @brief Default constructor for the class
   * @param
   * @return
   * @bug
   */
  buVector4F() = default;

  /**
   * @brief Constructor in charge of reciving two points for the vector.
   * @param
   * @return
   * @bug
   */
  buVector4F(float _x, float _y, float _z, float _w);

  /**
   * @brief Destructor
   * @param
   * @return
   * @bug
   */
  ~buVector4F();

  /**
   * @brief Copy constructors
   * @param
   * @return
   * @bug
   */
  buVector4F(const buVector4F& _v);

  /**
   * @brief 
   */
  buVector4F(float _arr[4]);

  buVector4F(float _arr[3],  float _const);

  /**
   * @brief Constructor to equal a vector
   * @param
   * @return
   * @bug
   */
  buVector4F& 
  operator=(const buVector4F& _v);

  /**
   * @brief Method for addition of another vector
   * @param
   * @return
   * @bug
   */
  buVector4F& 
  operator+=(const buVector4F& _v);

  /**
   * @brief  Method that return a third vector representing the addition of
   * two 2D vectors
   * @param
   * @return
   * @bug
   */
  buVector4F 
  operator+(const buVector4F& _v) const;

  /**
   * @brief Method for substract another vector
   * @param
   * @return
   * @bug
   */
  buVector4F& 
  operator-=(const buVector4F& _v);

  /**
   * @brief Method that return a third vector representing the substraction of
   * two 2D vectors
   * @param
   * @return
   * @bug
   */
  buVector4F 
  operator-(const buVector4F& _v) const;

  /**
   * @brief Method that multiply a vector with a scalar number
   * @param
   * @return
   * @bug
   */
  void 
  operator*=(const float _a);

  /**
   * @brief Method that return a third vector representing the multiplication
   * of a vector with a scalar number.
   * @param
   * @return
   * @bug
   */
  buVector4F 
  operator*(const float _a) const;

  /**
   * @brief Method that devides a vector with a scalar number.
   * @param
   * @return
   * @bug
   */
  void 
  operator/=(const float _a);

  /**
   * @brief Method that return a third vector representing the division of
   * a vector with a scalar number.
   * @param
   * @return
   * @bug
   */
  buVector4F 
  operator/(const float _a) const;
 
 public:
  /**
   * @brief Member in charge of storing the point of the x - coordinate.
   */
  float x = 0.0f;
  
  /**
   * @brief Member in charge of storing the point of the y - coordinate.
   */
  float y = 0.0f;
  
  /**
   * @brief Member in charge of storing the point of the z - coordinate.
   */
  float z = 0.0f;
  
  /**
   * @brief Member in charge of storing the point of the w - coordinate.
   */
  float w = 0.0f;
  
  /**
   * @brief Member in charge of giving an integer point with zero values.
   */
  static const buVector4F Zero;
  
 };
}

