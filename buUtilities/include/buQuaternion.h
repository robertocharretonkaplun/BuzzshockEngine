/**
 * @file buQuaternion.h 
 * @version 1.0
 * @date 09/06/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of representing a quaternion with a vector 3 and a 
 * scalar, I take inspiration from :https://www.vcalc.com/wiki/KurtHeckman/Quaternion+Calculator+Collection
 * @bug None.
 */
#pragma once
#include "buPrerequisitesUtil.h"
#include "buVector3F.h"
#include "buMath.h"

namespace buEngineSDK {
 class BU_UTILITY_EXPORT buQuaternion
 {
 public:
  /**
   * @brief Constructor 
   */
  buQuaternion() = default;

  /**
   * @brief Constructor 
   */
  buQuaternion(float _s, buVector3F _v);

  /**
   * @brief Copy Constructor 
   */
  buQuaternion(const buQuaternion& _q);

  /**
   * @brief Destructor
   */
  ~buQuaternion();

  /** 
   * @brief Method that equals a quaternion 
   * @param const buQuaternion& _q Quaternion
   * @return Quaternion.
   * @bug None.
   */  
  buQuaternion& 
  operator=(const buQuaternion& _q);

  /** 
   * @brief Method in charge of adding another quaternion.
   * @param const buQuaternion& _q Another Quaternion.
   * @return None.
   * @bug None.
   */
  void
  operator+=(const buQuaternion& _q);

  /** 
   * @brief Method that returns the result of the addition of two quaternions.
   * @param const buQuaternion& _q Another Quaternion
   * @return A quaternion.
   * @bug None.
   */
  buQuaternion 
  operator+(const buQuaternion& _q) const;

  /** 
   * @brief Method in charge of subtract another quaternion.
   * @param const buQuaternion& _q Another Quaternion.
   * @return None.
   * @bug None.
   */
  void
  operator-=(const buQuaternion& _q);

  /** 
   * @brief Method that returns the result of the subtraction of two quaternions. 
   * @param const buQuaternion& _q Another Quaternion
   * @return A Quaternion.
   * @bug None.
   */
  buQuaternion 
  operator-(const buQuaternion& _q) const;

   /** 
   * @brief Method that returns the result of the multiplication of two quaternions.
   * @param const buQuaternion& _q Another Quaternion
   * @return A quaternion.
   * @bug None.
   */
  buQuaternion 
  multiply(const buQuaternion& _q) const;

   /** 
   * @brief Method that multiplies directly a quaternion.
   * @param const buQuaternion& _q Another quaternion.
   * @return None.
   * @bug None.
   */
  void 
  operator*=(const buQuaternion& _q);

  /**
   * @brief Method that returns the result of the multiplication of two quaternions.
   * @param const buQuaternion& _q Another Quaternion
   * @return A quaternion.
   * @bug None.
   */
  buQuaternion 
  operator*(const buQuaternion& _q) const;

  /** 
   * @brief Method that multiplies a quaternion with scalar value.
   * @param const float value Scalar value.
   * @return None.
   * @bug None.
   */
  void 
  operator*=(const float value);

  /** 
  * @brief Method that returns a multiplied quaternion by a scalar value.
  * @param const float value Scalar Value.
  * @return A quaternion.
  * @bug None.
  */
  buQuaternion 
  operator*(const float value) const;

  /** 
   * @brief Method that returns a magnitude value from this quaternion.
   * @param None.
   * @return A magnitude value.
   * @bug None.
   */
  FORCEINLINE float
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
   * @brief Method that normalize a quaternion.
   * @param None.
   * @return None.
   * @bug None.
   */
  void
  normalize();

  /** 
   * @brief Method in charge of setting a special form of normalize quaternion
   * by the angles of sin and cos.
   * @param None.
   * @return None.
   * @bug None.
   */
  void 
  convertToNormalizeQuaternion();

  /** 
   * @brief Method in charge of getting the inverso of a quaternion.
   * @param None.
   * @return A quaternion.
   * @bug None.
   */
  buQuaternion 
  conjugate();

  /** 
   * @brief Method in charge of return a inverse quaternion.
   * @param None.
   * @return A quaternion.
   * @bug None.
   */
  buQuaternion 
  inverse();

  /** 
   * @brief Method in charge of returning a rotated quaternion.
   * @param float _angle A scalar number.
   * @param buVector3F& _axis The axis vector.
   * @return A quaternion.
   * @bug None.
   */
  buQuaternion
  rotate(float _angle, buVector3F& _axis);

 public:
  /**
   * @brief Scalar constant value
   */
  float m_val;

  /**
   * @brief Vector that represents an axis.
   */
  buVector3F m_axis;

 };
}