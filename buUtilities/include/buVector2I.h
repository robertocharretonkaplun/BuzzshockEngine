/**
* @file buVector2I.h
* @version 1.0
* @date 05/06/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
* @brief Class in charge of providing a 2D vector of int32 values.  
* @bug
*/
#pragma once
#include "buPrerequisitesUtil.h"
#include "buMath.h"
#include "buSerializer.h"
namespace buEngineSDK {
 class BU_UTILITY_EXPORT buVector2I
 {
 public:
  /**
   * @brief Default constructor for the class
   * @param 
   * @return
   * @bug 
   */
  buVector2I() = default;
  /**
   * @brief Constructor in charge of reciving two points for the vector.
   * @param 
   * @return 
   * @bug 
   */
  buVector2I(int32 _x, int32 _y);
  /**
   * @brief Destructor
   * @param 
   * @return 
   * @bug 
   */
  //~buVector2I();
  /**
   * @brief Copy constructors 
   * @param 
   * @return 
   * @bug 
   */
  //buVector2I(const buVector2I& _v);
  /**
   * @brief Constructor to equal a vector
   * @param 
   * @return 
   * @bug 
   */
  //buVector2I& 
  //operator=(const buVector2I& _v);
  /**
   * @brief Method for addition of another vector
   * @param 
   * @return 
   * @bug 
   */
  buVector2I&
  operator+=(const buVector2I& _v);
  /**
   * @brief  Method that return a third vector representing the addition of
   * two 2D vectors
   * @param 
   * @return 
   * @bug 
   */
  buVector2I 
  operator+(const buVector2I& _v) const;
  /**
   * @brief Method for substract another vector
   * @param 
   * @return 
   * @bug 
   */
  buVector2I&
  operator-=(const buVector2I& _v);
  /**
   * @brief Method that return a third vector representing the substraction of 
   * two 2D vectors
   * @param 
   * @return 
   * @bug 
   */
  buVector2I
  operator-(const buVector2I& _v) const;
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
  buVector2I 
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
  buVector2I 
  operator/(const int32 _a) const;
  /**
   * @brief Method that return a vector from the cross product of two vectors.
   * @param 
   * @return 
   * @bug 
   */
  buVector2I
  cross(const buVector2I& _v) const;
  /**
   * @brief Method that stores the result of a cross product of two vectors.
   * @param 
   * @return 
   * @bug 
   */
  void 
  operator%=(const buVector2I _v);
  /**
   * @brief Method that return a third vector representing the cross product
   * of two 2D vectors
   * @param 
   * @return 
   * @bug 
   */
  buVector2I
  operator%(const buVector2I& _v) const;
  
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
   * @brief Member in charge of giving an integer point with zero values.
   */
  static const buVector2I Zero;
 };
 BU_ALLOW_MEMCPY_SERIALIZATION(buVector2I);
}
