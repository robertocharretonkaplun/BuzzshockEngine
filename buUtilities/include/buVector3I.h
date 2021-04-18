/**
* @file buVector3I.h
* @version 1.0
* @date 05/06/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
* @brief Class in charge of providing a 3D vector.
* @bug None.
*/
#pragma once
#include "buPrerequisitesUtil.h"
#include "buMath.h"
#include "buSerializer.h"

namespace buEngineSDK {
 class BU_UTILITY_EXPORT buVector3I
 {
 public:
  /**
   * @brief Default constructor for the class
   * @param
   * @return
   * @bug
   */
  buVector3I() = default;
  
  /**
   * @brief Constructor in charge of reciving two points for the vector.
   * @param
   * @return
   * @bug
   */
  buVector3I(int32 _x, int32 _y, int32 _z);
  
  /**
   * @brief Destructor
   * @param
   * @return
   * @bug
   */
  //~buVector3I();
  
  /**
   * @brief Copy constructors
   * @param
   * @return
   * @bug
   */
  //buVector3I(const buVector3I& _v);
  
  /**
   * @brief Constructor to equal a vector
   * @param
   * @return
   * @bug
   */
  //buVector3I&
  //operator=(const buVector3I& _v);
  
  /**
   * @brief Method for addition of another vector
   * @param
   * @return
   * @bug
   */
  buVector3I& 
  operator+=(const buVector3I& _v);
  
  /**
   * @brief  Method that return a third vector representing the addition of
   * two 2D vectors
   * @param
   * @return
   * @bug
   */
  buVector3I 
  operator+(const buVector3I& _v) const;
  
  /**
   * @brief Method for substract another vector
   * @param
   * @return
   * @bug
   */
  buVector3I&
  operator-=(const buVector3I& _v);
  
  /**
   * @brief Method that return a third vector representing the substraction of
   * two 2D vectors
   * @param
   * @return
   * @bug
   */
  buVector3I 
  operator-(const buVector3I& _v) const;
  
  /**
   * @brief Method that multiply a vector with a scalar number
   * @param
   * @return
   * @bug
   */
  void 
  operator*=(const int32 _a);
  
  /**
   * @brief Method that return a third vector representing the multiplication
   * of a vector with a scalar number.
   * @param
   * @return
   * @bug
   */
  buVector3I 
  operator*(const int32 _a) const;
  
  /**
   * @brief Method that devides a vector with a scalar number.
   * @param
   * @return
   * @bug
   */
  void 
  operator/=(const int32 _a);
  
  /**
   * @brief Method that return a third vector representing the division of
   * a vector with a scalar number.
   * @param
   * @return
   * @bug
   */
  buVector3I 
  operator/(const int32 _a) const;
  
  /**
   * @brief Method that return a vector from the cross product of two vectors.
   * @param
   * @return
   * @bug
   */
  buVector3I 
  cross(const buVector3I& _v) const;
  
  /**
   * @brief Method that stores the result of a cross product of two vectors.
   * @param
   * @return
   * @bug
   */
  void 
  operator%=(const buVector3I _v);
  
  /**
   * @brief Method that return a third vector representing the cross product
   * of two 2D vectors
   * @param
   * @return
   * @bug
   */
  buVector3I
  operator%(const buVector3I& _v) const;
  
 public:
  /**
   * @brief Member in charge of storing the point of the x - coordinate.
   */
  int32 x;
  
  /**
   * @brief Member in charge of storing the point of the y - coordinate.
   */
  int32 y;
  
  /**
   * @brief Member in charge of storing the point of the z - coordinate.
   */
  int32 z;
  
  /**
   * @brief Member in charge of giving an integer point with zero values.
   */
  static const buVector3I Zero;

 };
 BU_ALLOW_MEMCPY_SERIALIZATION(buVector3I);
}
