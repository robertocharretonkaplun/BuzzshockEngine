#pragma once
#include "buPrerequisitesUtil.h"
#include "buVector4F.h"
#include "buVector3F.h"

namespace buEngineSDK {
  class BU_UTILITY_EXPORT buMatrix3x3
  {
  public:
   /**
    * @brief Default Constructor
    */
   buMatrix3x3() ;

   /**
    * @brief Constructor
    */
   buMatrix3x3(float x0, float y0, float z0,
               float x1, float y1, float z1,
               float x2, float y2, float z2);

   /**
    * @brief Vector initalization Contructor
    */
   buMatrix3x3(buVector4F& Vx,
     buVector4F& Vy,
     buVector4F& Vz);

   /**
    * @brief Copy constructor
    */
   buMatrix3x3(const buMatrix3x3& _mat);
   
   /**
    * @brief Destructor
    */
   ~buMatrix3x3();
   
   /**
    * @brief Method for addition of another matrix, 
    * Take inspiration from this site: https://ncalculators.com/matrix/4x4-matrix-addition-subtraction-calculator.htm
    * @param const buMatrix3x3& _mat Matrix.
    */
   buMatrix3x3&
   operator+=(const buMatrix3x3& _mat);

   /**
    * @brief  Method that return a third matrix representing the addition of
    * two 4x4 matrix.
    * @param const buMatrix3x3& _mat Matrix.
    * @return A matrix.
    */
   buMatrix3x3
   operator+(const buMatrix3x3& _mat) const;

   /** 
    * @brief Method that subtracts another matrix 
    * @param const buMatrix3x3& _mat Matrix.
    */
   buMatrix3x3&
   operator-=(const buMatrix3x3& _mat);

   /** 
    * @brief Method that return a third matrix representing the subtraction of
    * two 4x4 matrix.
    * @param const buMatrix3x3& _mat Matrix.
    * @return A matrix.
    */
   buMatrix3x3
    operator-(const buMatrix3x3& _mat) const;

   /**
    * @brief Method that multiply another matrix
    * @param const buMatrix3x3& _mat Matrix.
    */
   buMatrix3x3&
   operator*=(const buMatrix3x3& _mat);

   /**
    * @brief Method that return a third matrix representing the multplication of
    * two 4x4 matrix.
    * @param const buMatrix3x3& _mat Matrix.
    * @return A matrix.
    */
   buMatrix3x3
   operator*(const buMatrix3x3& _mat) const;

   /**
    * @brief Method that provides the determinant value of the matrix.
    */
   float 
   determinant();

   /** 
    * @brief Method in charge of transposing trhe current matrix.
    */
   void
   transpose();
  public:
   /**
    * @brief Constant values for the X column.
    */
   float m_x0, m_x1, m_x2;

   /**
    * @brief Constant values for the Y column.
    */
   float m_y0, m_y1, m_y2;

   /**
    * @brief Constant values for the Z column.
    */
   float m_z0, m_z1, m_z2;

   /**
    * @brief Member in charge of giving an integer point with zero values.
    */
   static const buMatrix3x3 ZERO;

   /**
    * @brief Member in charge of setting a Identity matrix
    */
   static const buMatrix3x3 IDENTITY;

  };
}
