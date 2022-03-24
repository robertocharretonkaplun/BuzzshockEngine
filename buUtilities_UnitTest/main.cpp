/**
 * @file main.cpp
 * @version 1.0
 * @date 05/06/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief File in charge of realising the unit testing of the utilities.
 * @bug None.
 */
#define GTEST_HAS_TR1_TUPLE 0
#define GTEST_USE_OWN_TR1_TUPLE 0
#include <gtest/gtest.h>
#include<buPrerequisitesUtil.h>
#include "buMath.h"
#include "buVector2I.h"
#include "buVector2F.h"
#include "buVector3I.h"
#include "buVector3F.h"
#include "buVector4I.h"
#include "buVector4F.h"
#include "buMatrix4x4.h"
#include "buQuaternion.h"
#include "buRay.h"
#include "buSphere.h"
#include "buBox.h"
#include "buRectangle.h"
#include "buRadians.h"
#include "buDegrees.h"
#include "buPluggin.h"

using namespace buEngineSDK;

int 
main(int argc, char** argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

static __forceinline float
Q_rsqrt(float number) {
  long i;
  float x2, y;
  const float threehalfs = 1.5F;
  
  x2 = number * 0.5f;
  y = number;
  i = *(long*)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float*)&i;
  y = y * (threehalfs - (x2 * y * y));

  return y;
}

static __forceinline float
WinInvSqrt(float F) {
  return 1.0f / buMath::sqrt(F);
}

/** 
 * @brief Testing in charge of asserting that the buVector2I works fine.
 * @param buUtilities For testing initialization requirements.
 * @param Vector2I_Test Name of the unit test.
 * @return None
 * @bug None.
 */
TEST(buUtilities, Vector2I_Test)
{
 // ARRENGE - Vector normal initialization 
 buVector2I A(1, 2);
 // ARRENGE - Vector initialization from vector
 buVector2I initFromC(4, 5);
 buVector2I B(initFromC);
 // ARRENGE - General Vectors
 buVector2I vector1(3, 4);
 buVector2I vector2(6, 8);

 // ACT - Addition
 buVector2I C = vector1 + vector2;
 // ACT - Subtraction
 buVector2I D = vector1 - vector2;
 // ACT - Multiplication
 buVector2I E = vector1 * 5;
 // ACT - Division
 buVector2I F = vector2 / 2;
 // ACT - Vector Cross Product
 buVector2I Vector1CrossVector2 = vector1.cross(vector2);

 // ASSERT - Vector normal initialization 
 GTEST_ASSERT_EQ(A.x, 1);
 GTEST_ASSERT_EQ(A.y, 2);
 // ASSERT - Vector initialization from vector
 GTEST_ASSERT_EQ(B.x, 4);
 GTEST_ASSERT_EQ(B.y, 5);
 // ASSERT - Vector Addition
 GTEST_ASSERT_EQ(C.x, 9);
 GTEST_ASSERT_EQ(C.y, 12);
 // ASSERT - Vector subtraction
 GTEST_ASSERT_EQ(D.x, -3);
 GTEST_ASSERT_EQ(D.y, -4);
 // ASSERT - Vector Multiplication
 GTEST_ASSERT_EQ(E.x, 15);
 GTEST_ASSERT_EQ(E.y, 20);
 // ASSERT - Vector Division
 GTEST_ASSERT_EQ(F.x, 3);
 GTEST_ASSERT_EQ(F.y, 4);
 // ASSERT - Vector Cross Product
 GTEST_ASSERT_EQ(Vector1CrossVector2.x, 24);
 GTEST_ASSERT_EQ(Vector1CrossVector2.y, 24);
}

/** 
 * @brief Testing in charge of asserting that the buVector2F works fine.
 * @param buUtilities For testing initialization requirements.
 * @param  Vector2F_Test Name of the unit test.
 * @return None.
 * @bug None.
 */
TEST(buUtilities, Vector2F_Test) {
 // ARRENGE - Vector normal initialization 
 buVector2F A(1.0f, 2.0f);
 // ARRENGE - Vector initialization from vector
 buVector2F initFromC(4.0f, 5.0f);
 buVector2F B(initFromC);
 // ARRENGE - General Vectors
 buVector2F vector1(3.0f, 4.0f);
 buVector2F vector2(6.0f, 8.0f);

 // ACT - Addition
 buVector2F C = vector1 + vector2;
 // ACT - Subtraction
 buVector2F D = vector1 - vector2;
 // ACT - Multiplication
 buVector2F E = vector1 * 5;
 // ACT - Division
 buVector2F F = vector2 / 2;
 // ACT - Vector Dot Product
 float dotProduct1 = vector1.dot(vector2);
 float dotProduct2 = vector1 * vector2;
 // ACT - Vector Cross Product
 buVector2F Vector1CrossVector2 = vector1.cross(vector2);
 // ACT - Vector magnitude
 float Magnitude = vector1.magnitude();
 // ACT - Vector normalized
 vector1.normalize();

 // ASSERT - Vector normal initialization 
 GTEST_ASSERT_EQ(A.x, 1.0f);
 GTEST_ASSERT_EQ(A.y, 2.0f);
 // ASSERT - Vector initialization from vector
 GTEST_ASSERT_EQ(B.x, 4.0f);
 GTEST_ASSERT_EQ(B.y, 5.0f);
 // ASSERT - Vector Addition
 GTEST_ASSERT_EQ(C.x, 9.0f);
 GTEST_ASSERT_EQ(C.y, 12.0f);
 // ASSERT - Vector subtraction
 GTEST_ASSERT_EQ(D.x, -3.0f);
 GTEST_ASSERT_EQ(D.y, -4.0f);
 // ASSERT - Vector Multiplication
 GTEST_ASSERT_EQ(E.x, 15.0f);
 GTEST_ASSERT_EQ(E.y, 20.0f);
 // ASSERT - Vector Division
 GTEST_ASSERT_EQ(F.x, 3.0f);
 GTEST_ASSERT_EQ(F.y, 4.0f);
 // ASSERT - Vector Dot Product
 GTEST_ASSERT_EQ(dotProduct1, 50.0f);
 GTEST_ASSERT_EQ(dotProduct2, 50.0f);
 // ASSERT - Vector Cross Product
 GTEST_ASSERT_EQ(Vector1CrossVector2.x, 24.0f);
 GTEST_ASSERT_EQ(Vector1CrossVector2.y, 24.0f);
 // ASSERT - Vector magnitude
 GTEST_ASSERT_EQ(Magnitude, 5.0f);
 // ASSERT - Vector
 GTEST_ASSERT_EQ(vector1.x, 0.6f);
 GTEST_ASSERT_EQ(vector1.y, 0.8f);
}

/** 
 * @brief Testing in charge of asserting that the buVector3I works fine.
 * @param buUtilities For testing initialization requirements.
 * @param Vector3I_Test Name of the unit test.
 * @return None.
 * @bug None.
 */
TEST(buUtilities, Vector3I_Test) {
 // ARRENGE - Vector normal initialization 
 buVector3I A(1, 2, 3);
 // ARRENGE - Vector initialization from vector
 buVector3I initFromC(2, 3, 1);
 buVector3I B(initFromC);
 // ARRENGE - General Vectors
 buVector3I vector1(2, 3, 1);
 buVector3I vector2(1, 2, 0);

 // ACT - Addition
 buVector3I C = vector1 + vector2;
 // ACT - Subtraction
 buVector3I D = vector1 - vector2;
 // ACT - Multiplication
 buVector3I E = vector1 * 5;
 // ACT - Division
 buVector3I F = vector2 / 2;
 // ACT - Vector Cross Product
 buVector3I Vector1CrossVector2 = vector1.cross(vector2);
 // ASSERT - Vector normal initialization 
 GTEST_ASSERT_EQ(A.x, 1);
 GTEST_ASSERT_EQ(A.y, 2);
 GTEST_ASSERT_EQ(A.z, 3);
 // ASSERT - Vector initialization from vector
 GTEST_ASSERT_EQ(B.x, 2);
 GTEST_ASSERT_EQ(B.y, 3);
 GTEST_ASSERT_EQ(B.z, 1);
 // ASSERT - Vector Addition
 GTEST_ASSERT_EQ(C.x, 3);
 GTEST_ASSERT_EQ(C.y, 5);
 GTEST_ASSERT_EQ(C.z, 1);
 // ASSERT - Vector subtraction
 GTEST_ASSERT_EQ(D.x, 1);
 GTEST_ASSERT_EQ(D.y, 1);
 GTEST_ASSERT_EQ(D.z, 1);
 // ASSERT - Vector Multiplication
 GTEST_ASSERT_EQ(E.x, 10);
 GTEST_ASSERT_EQ(E.y, 15);
 GTEST_ASSERT_EQ(E.z, 5);
 // ASSERT - Vector Division
 GTEST_ASSERT_EQ(F.x, 0);
 GTEST_ASSERT_EQ(F.y, 1);
 GTEST_ASSERT_EQ(F.z, 0);
 // ASSERT - Vector Cross Product
 GTEST_ASSERT_EQ(Vector1CrossVector2.x, -2);
 GTEST_ASSERT_EQ(Vector1CrossVector2.y, 1);
 GTEST_ASSERT_EQ(Vector1CrossVector2.z, 1);
}

/** 
 * @brief Testing in charge of asserting that the buVector3F works fine.
 * @param buUtilities For testing initialization requirements.
 * @param Vector3F_Test Name of the unit test.
 * @return None.
 * @bug The magnitude assert has some problems.
 */
TEST(buUtilities, Vector3F_Test) {
 // ARRENGE - Vector normal initialization 
 buVector3F A(1.0f, 2.0f, 3.0f);
 // ARRENGE - Vector initialization from vector
 buVector3F initFromC(2.0f, 3.0f, 1.0f);
 buVector3F B(initFromC);
 // ARRENGE - General Vectors
 buVector3F vector1(2.0f, 3.0f, 1.0f);
 buVector3F vector2(1.0f, 2.0f, 0.0f);

 // ACT - Addition
 buVector3F C = vector1 + vector2;
 // ACT - Subtraction
 buVector3F D = vector1 - vector2;
 // ACT - Multiplication
 buVector3F E = vector1 * 5.0f;
 // ACT - Division
 buVector3F F = vector2 / 2;
 // ACT - Vector Dot Product
 float dotProduct1 = vector1.dot(vector2);
 float dotProduct2 = vector1 * vector2;
 // ACT - Vector Cross Product
 buVector3F Vector1CrossVector2 = vector1.cross(vector2);
 // ACT - Vector magnitude
 float Magnitude = E.magnitude();
 // ACT - Vector normalized
 vector1.normalize();

 // ASSERT - Vector normal initialization 
 GTEST_ASSERT_EQ(A.x, 1.0f);
 GTEST_ASSERT_EQ(A.y, 2.0f);
 GTEST_ASSERT_EQ(A.z, 3.0f);
 // ASSERT - Vector initialization from vector
 GTEST_ASSERT_EQ(B.x, 2.0f);
 GTEST_ASSERT_EQ(B.y, 3.0f);
 GTEST_ASSERT_EQ(B.z, 1.0f);
 // ASSERT - Vector Addition
 GTEST_ASSERT_EQ(C.x, 3.0f);
 GTEST_ASSERT_EQ(C.y, 5.0f);
 GTEST_ASSERT_EQ(C.z, 1.0f);
 // ASSERT - Vector subtraction
 GTEST_ASSERT_EQ(D.x, 1.0f);
 GTEST_ASSERT_EQ(D.y, 1.0f);
 GTEST_ASSERT_EQ(D.z, 1.0f);
 // ASSERT - Vector Multiplication
 GTEST_ASSERT_EQ(E.x, 10.0f);
 GTEST_ASSERT_EQ(E.y, 15.0f);
 GTEST_ASSERT_EQ(E.z, 5.0f);
 // ASSERT - Vector Division
 GTEST_ASSERT_EQ(F.x, 0.5f);
 GTEST_ASSERT_EQ(F.y, 1.0f);
 GTEST_ASSERT_EQ(F.z, 0.0f);
 // ASSERT - Vector Dot Product
 GTEST_ASSERT_EQ(dotProduct1, 8.0f);
 GTEST_ASSERT_EQ(dotProduct2, 8.0f);
 // ASSERT - Vector Cross Product
 GTEST_ASSERT_EQ(Vector1CrossVector2.x, -2.0f);
 GTEST_ASSERT_EQ(Vector1CrossVector2.y, 1.0f);
 GTEST_ASSERT_EQ(Vector1CrossVector2.z, 1.0f);
 // ASSERT - Vector magnitude
 float comparador = 18.708286f;
 EXPECT_FLOAT_EQ(Magnitude, comparador);
 // ASSERT - Vector normalizado
 //EXPECT_FLOAT_EQ(vector1.x, 0.5345f);
 //EXPECT_FLOAT_EQ(vector1.y, 0.8017f);
 //EXPECT_FLOAT_EQ(vector1.z, 0.2672f);
 CHAR buffer[4096] = { 0 };
 RTTIEmptyType<buVector3F> obj;
 obj.toMemory(buVector3F(5, 15, 20), buffer);

 buVector3F empty;
 obj.fromMemory(empty, buffer);
}

/** 
 * @brief Testing in charge of asserting that the buVector4I works fine.
 * @param buUtilities For testing initialization requirements.
 * @param Vector4I_Test Name of the unit test.
 * @return None.
 * @bug None.
 */
TEST(buUtilities, Vector4I_Test) {\
 // ARRENGE
 buVector4I vector1(1, 2, 3, 4);
 buVector4I vector2(5, 6, 7, 8);
 // ACT - Vector addition
 buVector4I vectorAddition = vector1 + vector2;
 // ACT - Vector subtraction
 buVector4I vectorSubtraction = vector2 - vector1;
 // ACTR - Vector Multiplication
 buVector4I vectorMultiplication = vector1 * 5;
 // ACT - Vector Division
 buVector4I vectorDivision = vector1 / 2;
 
 // ASSERT - Vector 1 Initialization
 GTEST_ASSERT_EQ(1, vector1.x);
 GTEST_ASSERT_EQ(2, vector1.y);
 GTEST_ASSERT_EQ(3, vector1.z);
 GTEST_ASSERT_EQ(4, vector1.w);
 // ASSERT - Vector 2 Initialization
 GTEST_ASSERT_EQ(5, vector2.x);
 GTEST_ASSERT_EQ(6, vector2.y);
 GTEST_ASSERT_EQ(7, vector2.z);
 GTEST_ASSERT_EQ(8, vector2.w);
 // ASSERT - Vector Addition
 GTEST_ASSERT_EQ(6, vectorAddition.x);
 GTEST_ASSERT_EQ(8, vectorAddition.y);
 GTEST_ASSERT_EQ(10, vectorAddition.z);
 GTEST_ASSERT_EQ(12, vectorAddition.w);
 // ASSERT - Vector Subtraction
 GTEST_ASSERT_EQ(4, vectorSubtraction.x);
 GTEST_ASSERT_EQ(4, vectorSubtraction.y);
 GTEST_ASSERT_EQ(4, vectorSubtraction.z);
 GTEST_ASSERT_EQ(4, vectorSubtraction.w);
 // ASSERT - Vector Multiplication
 GTEST_ASSERT_EQ(5, vectorMultiplication.x);
 GTEST_ASSERT_EQ(10, vectorMultiplication.y);
 GTEST_ASSERT_EQ(15, vectorMultiplication.z);
 GTEST_ASSERT_EQ(20, vectorMultiplication.w);
 // ASSERT - Vector Division
 GTEST_ASSERT_EQ(0, vectorDivision.x);
 GTEST_ASSERT_EQ(1, vectorDivision.y);
 GTEST_ASSERT_EQ(1, vectorDivision.z);
 GTEST_ASSERT_EQ(2, vectorDivision.w);
}

/** 
 * @brief Testing in charge of asserting that the buVector4F works fine.
 * @param buUtilities For testing initialization requirements.
 * @param Vector4F_Test Name of the unit test.
 * @return None.
 * @bug None.
 */
TEST(buUtilities, Vector4F_Test) {
  // ARRENGE
  buVector4F vector1(1, 2, 3, 4);
  buVector4F vector2(5, 6, 7, 8);

  // ACT - Vector addition
  buVector4F vectorAddition = vector1 + vector2;
  // ACT - Vector subtraction
  buVector4F vectorSubtraction = vector2 - vector1;
  // ACTR - Vector Multiplication
  buVector4F vectorMultiplication = vector1 * 5;
  // ACT - Vector Division
  buVector4F vectorDivision = vector1 / 2;

  // ASSERT - Vector 1 Initialization
  GTEST_ASSERT_EQ(1, vector1.x);
  GTEST_ASSERT_EQ(2, vector1.y);
  GTEST_ASSERT_EQ(3, vector1.z);
  GTEST_ASSERT_EQ(4, vector1.w);
  // ASSERT - Vector 2 Initialization
  GTEST_ASSERT_EQ(5, vector2.x);
  GTEST_ASSERT_EQ(6, vector2.y);
  GTEST_ASSERT_EQ(7, vector2.z);
  GTEST_ASSERT_EQ(8, vector2.w);
  // ASSERT - Vector Addition
  GTEST_ASSERT_EQ(6, vectorAddition.x);
  GTEST_ASSERT_EQ(8, vectorAddition.y);
  GTEST_ASSERT_EQ(10, vectorAddition.z);
  GTEST_ASSERT_EQ(12, vectorAddition.w);
  // ASSERT - Vector Subtraction
  GTEST_ASSERT_EQ(4, vectorSubtraction.x);
  GTEST_ASSERT_EQ(4, vectorSubtraction.y);
  GTEST_ASSERT_EQ(4, vectorSubtraction.z);
  GTEST_ASSERT_EQ(4, vectorSubtraction.w);
  // ASSERT - Vector Multiplication
  GTEST_ASSERT_EQ(5, vectorMultiplication.x);
  GTEST_ASSERT_EQ(10, vectorMultiplication.y);
  GTEST_ASSERT_EQ(15, vectorMultiplication.z);
  GTEST_ASSERT_EQ(20, vectorMultiplication.w);
  // ASSERT - Vector Division
  GTEST_ASSERT_EQ(0.5f, vectorDivision.x);
  GTEST_ASSERT_EQ(1, vectorDivision.y);
  GTEST_ASSERT_EQ(1.5, vectorDivision.z);
  GTEST_ASSERT_EQ(2, vectorDivision.w);
}

/**
 * @brief Testing in charge of asserting that the Matrix4x4 works fine.
 * @param buUtilities For testing initialization requirements.
 * @param Matrix4x4_Test Name of the unit test.
 * @return None.
 * @bug None.
 */
TEST(buUtilities, Matrix4x4_Test) {
  // ARRANGE - Matrix determinant
  buMatrix4x4 detMat(
    1.0f, 3.0f, 1.0f, 4.0f, 
    3.0f, 9.0f, 5.0f, 15.0f,
    0.0f, 2.0f, 1.0f, 1.0f, 
    0.0f, 4.0f, 2.0f, 3.0f);
  // ARRANGE - Matrix Addition + Matrix subtraction
  buMatrix4x4 A(
    5.0f, 7.0f,  9.0f, 10.0f,
    2.0f, 3.0f,  3.0f, 8.0f,
    8.0f, 10.0f, 2.0f, 3.0f,
    3.0f, 3.0f,  4.0f, 8.0f);

  buMatrix4x4 B(
    3.0f,  10.0f, 12.0f, 18.0f,
    12.0f, 1.0f,  4.0f,  9.0f,
    9.0f,  10.0f, 12.0f, 2.0f,
    3.0f,  12.0f, 4.0f,  10.0f);

  buMatrix4x4 matrixT(
    10, 20, 10, 2,
    4,  5,  6,  3,
    2,  3,  5,  4,
    0,  0,  0,  1);

  // ACT - Matrix determinant
  float determinant = detMat.determinant();
  
  // ACT - Matrix addition
   buMatrix4x4 matrixAdd = A + B;

  // ACT - Matrix subtraction
   buMatrix4x4 matrixSub = A - B;

   // ACT - Matrix multiplication
   buMatrix4x4 matrixMul = A * B;

   // ACT - Matrix transpose
   matrixT.transpose();

  // ASSERT - Matrix determinant
  EXPECT_FLOAT_EQ(-4, determinant);

  // ASSERT - Matrix addition
  EXPECT_FLOAT_EQ(8,  matrixAdd.m_x0);
  EXPECT_FLOAT_EQ(14, matrixAdd.m_x1);
  EXPECT_FLOAT_EQ(17, matrixAdd.m_x2);
  EXPECT_FLOAT_EQ(6,  matrixAdd.m_x3);

  EXPECT_FLOAT_EQ(17, matrixAdd.m_y0);
  EXPECT_FLOAT_EQ(4,  matrixAdd.m_y1);
  EXPECT_FLOAT_EQ(20, matrixAdd.m_y2);
  EXPECT_FLOAT_EQ(15, matrixAdd.m_y3);

  EXPECT_FLOAT_EQ(21, matrixAdd.m_z0);
  EXPECT_FLOAT_EQ(7,  matrixAdd.m_z1);
  EXPECT_FLOAT_EQ(14, matrixAdd.m_z2);
  EXPECT_FLOAT_EQ(8,  matrixAdd.m_z3);
  
  EXPECT_FLOAT_EQ(28,  matrixAdd.m_w0);
  EXPECT_FLOAT_EQ(17,  matrixAdd.m_w1);
  EXPECT_FLOAT_EQ(5,   matrixAdd.m_w2);
  EXPECT_FLOAT_EQ(18,  matrixAdd.m_w3);

  // ASSERT - Matrix subtraction
  EXPECT_FLOAT_EQ(2,   matrixSub.m_x0);
  EXPECT_FLOAT_EQ(-10, matrixSub.m_x1);
  EXPECT_FLOAT_EQ(-1,  matrixSub.m_x2);
  EXPECT_FLOAT_EQ(0,   matrixSub.m_x3);

  EXPECT_FLOAT_EQ(-3,  matrixSub.m_y0);
  EXPECT_FLOAT_EQ(2,   matrixSub.m_y1);
  EXPECT_FLOAT_EQ(0,   matrixSub.m_y2);
  EXPECT_FLOAT_EQ(-9,  matrixSub.m_y3);

  EXPECT_FLOAT_EQ(-3,  matrixSub.m_z0);
  EXPECT_FLOAT_EQ(-1,  matrixSub.m_z1);
  EXPECT_FLOAT_EQ(-10, matrixSub.m_z2);
  EXPECT_FLOAT_EQ(0,   matrixSub.m_z3);

  EXPECT_FLOAT_EQ(-8,  matrixSub.m_w0);
  EXPECT_FLOAT_EQ(-1,  matrixSub.m_w1);
  EXPECT_FLOAT_EQ(1,   matrixSub.m_w2);
  EXPECT_FLOAT_EQ(-2,  matrixSub.m_w3);

  // ASSERT - Matrix multiplication
  EXPECT_FLOAT_EQ(210.0f, matrixMul.m_x0);
  EXPECT_FLOAT_EQ(93.0f,  matrixMul.m_x1);
  EXPECT_FLOAT_EQ(171.0f, matrixMul.m_x2);
  EXPECT_FLOAT_EQ(105.0f, matrixMul.m_x3);

  EXPECT_FLOAT_EQ(267.0f, matrixMul.m_y0);
  EXPECT_FLOAT_EQ(149.0f, matrixMul.m_y1);
  EXPECT_FLOAT_EQ(146.0f, matrixMul.m_y2);
  EXPECT_FLOAT_EQ(169.0f, matrixMul.m_y3);

  EXPECT_FLOAT_EQ(236.0f, matrixMul.m_z0);
  EXPECT_FLOAT_EQ(104.0f, matrixMul.m_z1);
  EXPECT_FLOAT_EQ(172.0f, matrixMul.m_z2);
  EXPECT_FLOAT_EQ(128.0f, matrixMul.m_z3);

  EXPECT_FLOAT_EQ(271.0f, matrixMul.m_w0);
  EXPECT_FLOAT_EQ(149.0f, matrixMul.m_w1);
  EXPECT_FLOAT_EQ(268.0f, matrixMul.m_w2);
  EXPECT_FLOAT_EQ(169.0f, matrixMul.m_w3);

  // ASSERT - Matrix Traspose
  EXPECT_FLOAT_EQ(10, matrixT.m_x0);
  EXPECT_FLOAT_EQ(20, matrixT.m_x1);
  EXPECT_FLOAT_EQ(10, matrixT.m_x2);
  EXPECT_FLOAT_EQ(2,  matrixT.m_x3);
                  
  EXPECT_FLOAT_EQ(4, matrixT.m_y0);
  EXPECT_FLOAT_EQ(5, matrixT.m_y1);
  EXPECT_FLOAT_EQ(6, matrixT.m_y2);
  EXPECT_FLOAT_EQ(3, matrixT.m_y3);
                     
  EXPECT_FLOAT_EQ(2, matrixT.m_z0);
  EXPECT_FLOAT_EQ(3, matrixT.m_z1);
  EXPECT_FLOAT_EQ(5, matrixT.m_z2);
  EXPECT_FLOAT_EQ(4, matrixT.m_z3);
                     
  EXPECT_FLOAT_EQ(0, matrixT.m_w0);
  EXPECT_FLOAT_EQ(0, matrixT.m_w1);
  EXPECT_FLOAT_EQ(0, matrixT.m_w2);
  EXPECT_FLOAT_EQ(1, matrixT.m_w3);
}

/** 
 * @brief Testing in charge of asserting that the Quaternion works fine. 
 * @param buUtilities For testing initialization requirements.
 * @param Quaternion_Test Name of the unit test.
 * @return None.
 * @bug None.
 */
TEST(buUtilities, Quaternion_Test) {
  // ARRENGE - Initialization
  buVector3F axis(1, 0, 0);
  buQuaternion q(90.0f, axis);
  buQuaternion q2(10.0f, axis);
  buQuaternion q3(20.0f, axis);

  // ACT - Add quaternions
  buQuaternion quaternionAdd = q + q2;
  // ACT - Sub quaternions
  buQuaternion quaternionSub = q - q2;
  // ACT - Mul quaternions
  buQuaternion quaternionMul = q * q2;
  // ACT - Mag of quaternion
  float quaternionMag = q.magnitude();
  // ACT - Multiply quaternion with a scalar
  buQuaternion quaternionMulByScalar = q * 2;
  // ACT - Normalize a quaternion
  q3.normalize();

  // ASSERT - Initialization
  EXPECT_FLOAT_EQ(1.0f, q.m_axis.x);
  EXPECT_FLOAT_EQ(0.0f, q.m_axis.y);
  EXPECT_FLOAT_EQ(0.0f, q.m_axis.z);
  EXPECT_FLOAT_EQ(90.0f, q.m_val);
  // ASSERT - Add quaternion
  EXPECT_FLOAT_EQ(2, quaternionAdd.m_axis.x);
  EXPECT_FLOAT_EQ(0, quaternionAdd.m_axis.y);
  EXPECT_FLOAT_EQ(0, quaternionAdd.m_axis.z);
  EXPECT_FLOAT_EQ(100, quaternionAdd.m_val);
  // ASSERT - Sub quaternion
  EXPECT_FLOAT_EQ(0, quaternionSub.m_axis.x);
  EXPECT_FLOAT_EQ(0, quaternionSub.m_axis.y);
  EXPECT_FLOAT_EQ(0, quaternionSub.m_axis.z);
  EXPECT_FLOAT_EQ(80, quaternionSub.m_val);
  // ASSERT - Mul quaternion
  EXPECT_FLOAT_EQ(100, quaternionMul.m_axis.x);
  EXPECT_FLOAT_EQ(0, quaternionMul.m_axis.y);
  EXPECT_FLOAT_EQ(0, quaternionMul.m_axis.z);
  EXPECT_FLOAT_EQ(899, quaternionMul.m_val);
  // ASSERT - Mag of quaternion
  EXPECT_FLOAT_EQ(90.00555538409837f, quaternionMag);
  // ASSERT - Multiply quaternion with a scalar 
  EXPECT_FLOAT_EQ(2, quaternionMulByScalar.m_axis.x);
  EXPECT_FLOAT_EQ(0, quaternionMulByScalar.m_axis.y);
  EXPECT_FLOAT_EQ(0, quaternionMulByScalar.m_axis.z);
  EXPECT_FLOAT_EQ(180, quaternionMulByScalar.m_val);
  // ASSERT - Normalize a quaternion
  EXPECT_FLOAT_EQ(0.049937617f, q3.m_axis.x);
  EXPECT_FLOAT_EQ(0, q3.m_axis.y);
  EXPECT_FLOAT_EQ(0, q3.m_axis.z);
  EXPECT_FLOAT_EQ(0.99875236f, q3.m_val);
}

/**
 * @brief Testing in charge of asserting that the Ray works fine.
 * @param buUtilities For testing initialization requirements.
 * @param Ray_Test Name of the unit test.
 * @return None.
 * @bug None.
 */
TEST(buUtilities, Ray_Test) {
  // ARRANGE Initialization
  buVector3F origin(0, 0, 0);
  buVector3F direction(1, 1, 0);
  buRay r1(origin, direction, 10);

  // ACT - Get ray point
  buVector3F point = r1.Ray(direction, 10);

  // ASSERT - Initialization
  EXPECT_FLOAT_EQ(10, r1.m_distance);
  EXPECT_FLOAT_EQ(0, r1.m_origin.x);
  EXPECT_FLOAT_EQ(0, r1.m_origin.y);
  EXPECT_FLOAT_EQ(0, r1.m_origin.z);
  // ASSERT - Get ray point
  EXPECT_FLOAT_EQ(11, point.x);
  EXPECT_FLOAT_EQ(11, point.y);
  EXPECT_FLOAT_EQ(10, point.z);
}

/**
 * @brief Testing in charge of asserting that the sphere works fine.
 * @param buUtilities For testing initialization requirements.
 * @param Sphere_Test Name of the unit test.
 * @return None.
 * @bug None.
 */
TEST(buUtilities, Sphere_Test) {
  // ARRANGE - Initialization
  buVector3F center(5,5,5);
  buSphere s(center, 30);

  // ASSERT - Initialization
  EXPECT_FLOAT_EQ(5, s.m_center.x);
  EXPECT_FLOAT_EQ(5, s.m_center.y);
  EXPECT_FLOAT_EQ(5, s.m_center.z);
  EXPECT_FLOAT_EQ(30, s.m_radius);
}

/**
 * @brief Testing in charge of asserting that the box works fine.
 * @param buUtilities For testing initialization requirements.
 * @param Box_Test Name of the unit test.
 * @return None.
 * @bug None.
 */
TEST(buUtilities, Box_Test) {
  // ARRANGE - Initialization
  buBox b(2, 3, 5, 5, 5);

  // ACT - box volume
  float volume = b.getVolume();

  // ASSERT - Initialization
  EXPECT_FLOAT_EQ(2, b.m_x);
  EXPECT_FLOAT_EQ(3, b.m_y);
  EXPECT_FLOAT_EQ(5, b.m_width);
  EXPECT_FLOAT_EQ(5, b.m_height);
  EXPECT_FLOAT_EQ(5, b.m_length);
  // ASSERT - box volume
  EXPECT_FLOAT_EQ(125, volume);
}

/**
 * @brief Testing in charge of asserting that the rectangle works fine.
 * @param buUtilities For testing initialization requirements.
 * @param Rectangle_Test Name of the unit test.
 * @return None.
 * @bug None.
 */
TEST(buUtilities, Rectangle_Test) {
  // ARRANGE - Initialization
  buRectangle r(0, 0, 5, 3);
  
  // ACT - Area of rectangle
  float area = r.getArea();
  // ACT - Perimeter of rectangle
  float perimeter = r.getPerimeter();

  // ASSERT - Initialization
  EXPECT_FLOAT_EQ(0, r.m_x);
  EXPECT_FLOAT_EQ(0, r.m_y);
  EXPECT_FLOAT_EQ(5, r.m_width);
  EXPECT_FLOAT_EQ(3, r.m_lenght);
  // ASSERT - Area of rectangle
  EXPECT_FLOAT_EQ(15, area);
  // ASSERT - Perimeter of rectangle
  EXPECT_FLOAT_EQ(34, perimeter);

}

/**
 * @brief Testing in charge of asserting that the talyor works fine.
 * @param buUtilities For testing initialization requirements.
 * @param TaylorSeries_Test Name of the unit test.
 */
TEST(buUtilities, TaylorSeries_Test) {
  // ARRANGE

  // ACT - cos taylor 
  float cos = buMath::cosTaylor(8, 1.0f);
  // ACT - sin taylor 
  float sin = buMath::sinTaylor(8, 1.0f);
  // ASSERT - cos taylor
  EXPECT_FLOAT_EQ(0.5403022f, cos);
  // ASSERT - sin taylor
  EXPECT_FLOAT_EQ(0.841471f, sin);
}
