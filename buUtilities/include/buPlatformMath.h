/**
 * @file buPlatformMath.h
 * @version 1.0
 * @date 01/06/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of setting the basic mathematic
 * @bugs None.
 */
#pragma once
#include "buPrerequisitesUtil.h"

namespace buEngineSDK {
  class buPlatformMath
  {
  public:
   /** 
    * @brief Method that return a quick sqrt value.
    * @param _v Value.
    * @return quick sqrt.
    */
   static FORCEINLINE float
     Q_rsqrt(float _v) {
     long i;
     float x2, y;
     const float threehalfs = 1.5F;

     x2 = _v * 0.5f;
     y = _v;
     i = *(long*)&y;
     i = 0x5f3759df - (i >> 1);
     y = *(float*)&i;
     y = y * (threehalfs - (x2 * y * y));

     return y;
   }

   /**
    * @brief Method that return the sqrt value from the std library.
    * @param Value
    * @return sqrt float value.
    * @bug None.
    */
   static float
   sqrt(float _v) {
   	return std::sqrt(_v);
   }

   /**
    * @brief Method that return the sqr from the buEngine.
    * @param _v Value of the constant.
    * @return A sqr value.
    */
   static FORCEINLINE float
     sqr(float _v) {
     return _v * _v;
   }

   /**
    * @brief Method that return the sqrtf value from the std library.
    * @param Value
    * @return sqrtf float value.
    * @bug None.
    */
   static float
   sqrtf(float _v) {
   	return std::sqrtf(_v);
   }

   /** 
    * @brief Method that return the inverse sqrt fromt the buEngine.
    * @param _v Value of the constant.
    * @return A inverse sqrt value.
    */
   static float 
   invSqrt(float _v) {
     return 1.0f / sqrt(_v);
   }

   /**
    * @brief Method that return the pow value from the std library.
    * @param float _x Constant.
    * @param float _y Constant.
    * @return pow float value.
    * @bug None.
    */
   static float 
   pow(float _x, float _y) {
   	return std::pow(_x, _y);
   }

   /**
    * @brief Method that return the powf value from the std library.
    * @param float _x Constant.
    * @param float _y Constant.
    * @return powf float value.
    * @bug None.
    */
   static float 
   powf(float _x, float _y) {
   	return std::powf(_x, _y);
   }

   /**
    * @brief Method that return the cos value from the std lib.
    * @param float _v scalar value.
    * @return cos value.
    * @bug None.
    */
   static float
   cos(float _v) {
   	return std::cos(_v);
   }

   /**
    * @brief Method that return the sin value from the std lib.
    * @param float _v scalar value.
    * @return sin value.
    * @bug None.
    */
   static float
   sin(float _v) {
   	return std::sin(_v);
   }

   /**
    * @brief Method that return the tan value from the std lib.
    * @param float _v scalar value.
    * @return tan value.
    * @bug None.
    */
   static float
   tan(float _v) {
   	return std::tan(_v);
   }

   /**
    * @brief Method that return the cons float value from the std lib.
    * @param float _v scalar value.
    * @return cosf value.
    * @bug None.
    */
   static float
   cosf(float _v) {
   	return std::cosf(_v);
   }

   /**
    * @brief Method that return the sin float value from the std lib.
    * @param float _v scalar value.
    * @return sinf value.
    * @bug None.
    */
   static float
   sinf(float _v) {
   	return std::sinf(_v);
   }

   /**
    * @brief Method that return the tan float value from the std lib.
    * @param float _v scalar value.
    * @return tanf value.
    * @bug None.
    */
   static float 
   tanf(float _v) {
    return std::tanf(_v);
   }

   /**
    * @brief 
    * @param 
    * @return 
    * @bug 
    */
   static float 
   cot(float _v) {
     return tan(6.283185307f - _v);
   }

   /** 
    * @brief Method that return a factorial value.
    * @param _v scalar value.
    * @return A factorial.
    */
   static int
   factorial(int _v) {
     int32 F = 1;
     for (int i = 1; i <= _v; ++i) {
       F = F * i;
     }
     return F;
   }

   /** 
    * @brief Method in charge of getting the value a Maclaurin series.
    * @param _number Number of terms.
    * @param _angle Angle value.
    * @return A sin value.
    */
   static float
   sinTaylor(int _number, float _angle) {
     float sin = 0.0f;

     for (int k = 0; k < _number; ++k) {
       sin = sin + pow(-1.0f, (float)k) * pow(_angle, 2.0f * (float)k + 1.0f) /
         factorial(2 * k + 1);
     }
     return sin;
   }

   /**
    * @brief Method in charge of getting the value a Maclaurin series.
    * @param _number Number of terms.
    * @param _angle Angle value.
    * @return A cos value.
    */
   static float
   cosTaylor(int _number, float _angle) {
     float cos = 0.0f;

     for (int k = 0; k < _number; ++k) {
       cos = cos + pow(-1.0f, (float)k) * pow(_angle, 2.0f * (float)k) / factorial(2 * k);
     }
     return cos;
   }
  
   static float log(float _v) {
     return std::log(_v);
   }

   float box_muller(float m, float s)	{
     float x1, x2, w, y1;
     static float y2;
     static int use_last = 0;

     if (use_last) {
       y1 = y2;
       use_last = 0;
     }
     else {
       while (w >= 1.0) {
         //x1 = 2.0 * ranf() - 1.0;
         //x2 = 2.0 * ranf() - 1.0;
         w = x1 * x1 + x2 * x2;
       } 

       w = sqrt((-2.0 * log(w)) / w);
       y1 = x1 * w;
       y2 = x2 * w;
       use_last = 1;
     }

     return(m + y1 * s);
   }
  };
}
