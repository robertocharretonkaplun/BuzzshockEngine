/**
* @file buVector4I.h 
* @version 1.0
* @date 05/06/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
* @brief Class in charge of providing a 4D int vector
* @bug None.
*/
#pragma once

#include "buPrerequisitesUtil.h"
#include "buMath.h"
#include "buSerializer.h"

namespace buEngineSDK {
 class BU_UTILITY_EXPORT buVector4I
 {
 public:
  /**
   * @brief Default constructor for the class
   * @param
   * @return
   * @bug
   */
  buVector4I() = default;

  /**
   * @brief Constructor in charge of reciving two points for the vector.
   * @param
   * @return
   * @bug
   */
  buVector4I(int32 _x, int32 _y, int32 _z, int32 _w);

  /**
   * @brief Destructor
   * @param
   * @return
   * @bug
   */
  //~buVector4I();

  /**
   * @brief Copy constructors
   * @param
   * @return
   * @bug
   */
  //buVector4I(const buVector4I& _v);

  /**
   * @brief Constructor to equal a vector
   * @param
   * @return
   * @bug
   */
  //buVector4I& 
  //operator=(const buVector4I& _v);

  /**
   * @brief Method for addition of another vector
   * @param
   * @return
   * @bug
   */
  buVector4I& 
  operator+=(const buVector4I& _v);

  /**
   * @brief  Method that return a third vector representing the addition of
   * two 2D vectors
   * @param
   * @return
   * @bug
   */
  buVector4I 
  operator+(const buVector4I& _v) const;

  /**
   * @brief Method for substract another vector
   * @param
   * @return
   * @bug
   */
  buVector4I& 
  operator-=(const buVector4I& _v);

  /**
   * @brief Method that return a third vector representing the substraction of
   * two 2D vectors
   * @param
   * @return
   * @bug
   */
  buVector4I 
  operator-(const buVector4I& _v) const;

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
  buVector4I 
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
  buVector4I 
  operator/(const int32 _a) const;
 
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
   * @brief Member in charge of storing the point of the w - coordinate.
   */
  int32 w;
  
  /**
   * @brief Member in charge of giving an integer point with zero values.
   */
  static const buVector4I Zero;
  
 };
 BU_ALLOW_MEMCPY_SERIALIZATION(buVector4I);
}

