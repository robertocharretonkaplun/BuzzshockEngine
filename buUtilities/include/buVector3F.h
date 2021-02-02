#pragma once
#include "buPrerequisitesUtil.h"
#include "buMath.h"

namespace buEngineSDK {
 class BU_UTILITY_EXPORT buVector3F
 {
 public:
  /**
   * @brief Default constructor for the class
   * @param
   * @return
   * @bug
   */
  buVector3F() = default;

  /**
   * @brief Constructor in charge of reciving two points for the vector.
   * @param
   * @return
   * @bug
   */
  buVector3F(float _x, float _y, float _z);

  /**
   * @brief Destructor
   * @param
   * @return
   * @bug
   */
  ~buVector3F();

  /**
   * @brief Copy constructors
   * @param
   * @return
   * @bug
   */
  buVector3F(const buVector3F& _v);

  /**
   * @brief Constructor to equal a vector
   * @param
   * @return
   * @bug
   */
  buVector3F& 
  operator=(const buVector3F& _v);

  /**
   * @brief Method for addition of another vector
   * @param
   * @return
   * @bug
   */
  buVector3F&
  operator+=(const buVector3F& _v);

  /**
   * @brief  Method that return a third vector representing the addition of
   * two 2D vectors
   * @param
   * @return
   * @bug
   */
  buVector3F
  operator+(const buVector3F& _v) const;

  /**
   * @brief Method for substract another vector
   * @param
   * @return
   * @bug
   */
  buVector3F& 
  operator-=(const buVector3F& _v);

  /**
   * @brief Method that return a third vector representing the substraction of
   * two 2D vectors
   * @param
   * @return
   * @bug
   */
  buVector3F
  operator-(const buVector3F& _v) const;

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
  buVector3F 
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
  buVector3F
  operator/(const float _a) const;

  /**
   * @brief Method that return a scalar from the multiplication of two vectors.
   * @param
   * @return
   * @bug
   */
  float
  dot(const buVector3F& _v) const;

  /**
   * @brief Method that return a scalar from the multiplication of two vectors
   * directly.
   * @param
   * @return
   * @bug
   */
  float 
  operator*(const buVector3F& _v) const;

  /**
   * @brief Method that return a vector from the cross product of two vectors.
   * @param
   * @return
   * @bug
   */
  buVector3F 
  cross(const buVector3F& _v) const;

  /**
   * @brief Method that stores the result of a cross product of two vectors.
   * @param
   * @return
   * @bug
   */
  void
  operator%=(const buVector3F _v);

  /**
   * @brief Method that return a third vector representing the cross product
   * of two 2D vectors
   * @param
   * @return
   * @bug
   */
  buVector3F 
  operator%(const buVector3F& _v) const;

  /**
   * @brief Method that return a scalar from the current vector.
   * @param
   * @return
   * @bug
   */
  float
  magnitude();

  /**
   * @brief
   * @param
   * @return
   * @bug
   */
  FORCEINLINE float
  sqrMagnitude();

  /**
   * @brief Method that normalize the current vector.
   * @param
   * @return
   * @bug
   */
  void
  normalize();
  
  float *
  data();

 public:
  /**
   * @brief Member in charge of storing the point of the x - coordinate.
   */
  float x;
  
  /**
   * @brief Member in charge of storing the point of the y - coordinate.
   */
  float y;
  
  /**
   * @brief Member in charge of storing the point of the z - coordinate.
   */
  float z;
  
  /**
   * @brief Member in charge of giving an integer point with zero values.
   */
  static const buVector3F Zero;

 };
}
