#include "buMatrix4x4.h"

namespace buEngineSDK {
  const buMatrix4x4 buMatrix4x4::ZERO = buMatrix4x4(0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f);

  const buMatrix4x4 buMatrix4x4::IDENTITY = buMatrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f);

  buMatrix4x4::buMatrix4x4()
  {
    *this = buMatrix4x4::IDENTITY;
  }

  buMatrix4x4::buMatrix4x4(float x0, float y0, float z0, float w0,
    float x1, float y1, float z1, float w1,
    float x2, float y2, float z2, float w2,
    float x3, float y3, float z3, float w3) :
    m_x0(x0), m_y0(y0), m_z0(z0), m_w0(w0),
    m_x1(x1), m_y1(y1), m_z1(z1), m_w1(w1),
    m_x2(x2), m_y2(y2), m_z2(z2), m_w2(w2),
    m_x3(x3), m_y3(y3), m_z3(z3), m_w3(w3) { }

  buMatrix4x4::buMatrix4x4(buVector4F& Vx, buVector4F& Vy,
    buVector4F& Vz, buVector4F& Vw) :
    m_x0(Vx.x), m_y0(Vy.x), m_z0(Vz.x), m_w0(Vw.x),
    m_x1(Vx.y), m_y1(Vy.y), m_z1(Vz.y), m_w1(Vw.y),
    m_x2(Vx.z), m_y2(Vy.z), m_z2(Vz.z), m_w2(Vw.z),
    m_x3(Vx.w), m_y3(Vy.w), m_z3(Vz.w), m_w3(Vw.w) { }

  buMatrix4x4& 
  buMatrix4x4::operator+=(const buMatrix4x4& _mat) {
    *this = *this + _mat;
    return *this;
  }

  buMatrix4x4 
  buMatrix4x4::operator+(const buMatrix4x4& _mat) const {
    return buMatrix4x4(
      m_x0 + _mat.m_x0, m_y0 + _mat.m_y0, m_z0 + _mat.m_z0, m_w0 + _mat.m_w0,
      m_x1 + _mat.m_x1, m_y1 + _mat.m_y1, m_z1 + _mat.m_z1, m_w1 + _mat.m_w1,
      m_x2 + _mat.m_x2, m_y2 + _mat.m_y2, m_z2 + _mat.m_z2, m_w2 + _mat.m_w2,
      m_x3 + _mat.m_x3, m_y3 + _mat.m_y3, m_z3 + _mat.m_z3, m_w3 + _mat.m_w3);
  }

  buMatrix4x4& 
  buMatrix4x4::operator-=(const buMatrix4x4& _mat) {
    *this = *this - _mat;
    return *this;
  }

  buMatrix4x4
  buMatrix4x4::operator-(const buMatrix4x4& _mat) const {
    return buMatrix4x4(
      m_x0 - _mat.m_x0, m_y0 - _mat.m_y0, m_z0 - _mat.m_z0, m_w0 - _mat.m_w0,
      m_x1 - _mat.m_x1, m_y1 - _mat.m_y1, m_z1 - _mat.m_z1, m_w1 - _mat.m_w1,
      m_x2 - _mat.m_x2, m_y2 - _mat.m_y2, m_z2 - _mat.m_z2, m_w2 - _mat.m_w2,
      m_x3 - _mat.m_x3, m_y3 - _mat.m_y3, m_z3 - _mat.m_z3, m_w3 - _mat.m_w3);
  }

  buMatrix4x4&
  buMatrix4x4::operator*=(const buMatrix4x4& _mat) {
    *this = *this * _mat;
    return *this;
  }

  buMatrix4x4 
  buMatrix4x4::operator*(const buMatrix4x4& _mat) const {
    // Row 0
    float x0 = m_x0 * _mat.m_x0 + m_y0 * _mat.m_x1 + m_z0 * _mat.m_x2 + m_w0 * _mat.m_x3;
    float y0 = m_x0 * _mat.m_y0 + m_y0 * _mat.m_y1 + m_z0 * _mat.m_y2 + m_w0 * _mat.m_y3;
    float z0 = m_x0 * _mat.m_z0 + m_y0 * _mat.m_z1 + m_z0 * _mat.m_z2 + m_w0 * _mat.m_z3;
    float w0 = m_x0 * _mat.m_w0 + m_y0 * _mat.m_w1 + m_z0 * _mat.m_w2 + m_w0 * _mat.m_w3;
    // Row 1						
    float x1 = m_x1 * _mat.m_x0 + m_y1 * _mat.m_x1 + m_z1 * _mat.m_x2 + m_w1 * _mat.m_x3;
    float y1 = m_x1 * _mat.m_y0 + m_y1 * _mat.m_y1 + m_z1 * _mat.m_y2 + m_w1 * _mat.m_y3;
    float z1 = m_x1 * _mat.m_z0 + m_y1 * _mat.m_z1 + m_z1 * _mat.m_z2 + m_w1 * _mat.m_z3;
    float w1 = m_x1 * _mat.m_w0 + m_y1 * _mat.m_w1 + m_z1 * _mat.m_w2 + m_w1 * _mat.m_w3;
    // Row 2						
    float x2 = m_x2 * _mat.m_x0 + m_y2 * _mat.m_x1 + m_z2 * _mat.m_x2 + m_w2 * _mat.m_x3;
    float y2 = m_x2 * _mat.m_y0 + m_y2 * _mat.m_y1 + m_z2 * _mat.m_y2 + m_w2 * _mat.m_y3;
    float z2 = m_x2 * _mat.m_z0 + m_y2 * _mat.m_z1 + m_z2 * _mat.m_z2 + m_w2 * _mat.m_z3;
    float w2 = m_x2 * _mat.m_w0 + m_y2 * _mat.m_w1 + m_z2 * _mat.m_w2 + m_w2 * _mat.m_w3;
    // Row 3						
    float x3 = m_x3 * _mat.m_x0 + m_y3 * _mat.m_x1 + m_z3 * _mat.m_x2 + m_w3 * _mat.m_x3;
    float y3 = m_x3 * _mat.m_y0 + m_y3 * _mat.m_y1 + m_z3 * _mat.m_y2 + m_w3 * _mat.m_y3;
    float z3 = m_x3 * _mat.m_z0 + m_y3 * _mat.m_z1 + m_z3 * _mat.m_z2 + m_w3 * _mat.m_z3;
    float w3 = m_x3 * _mat.m_w0 + m_y3 * _mat.m_w1 + m_z3 * _mat.m_w2 + m_w3 * _mat.m_w3;

    return buMatrix4x4(x0, y0, z0, w0,
      x1, y1, z1, w1,
      x2, y2, z2, w2,
      x3, y3, z3, w3);
  }

  float
  buMatrix4x4::determinant() {
    // Get the basic matrix
    buMatrix4x4 tmpMat = *this;
    // Set new vector for future initializations
    buVector4F v0(tmpMat.m_x0, tmpMat.m_y0, tmpMat.m_z0, tmpMat.m_w0);
    buVector4F v1(tmpMat.m_x1, tmpMat.m_y1, tmpMat.m_z1, tmpMat.m_w1);
    buVector4F v2(tmpMat.m_x2, tmpMat.m_y2, tmpMat.m_z2, tmpMat.m_w2);
    buVector4F v3(tmpMat.m_x3, tmpMat.m_y3, tmpMat.m_z3, tmpMat.m_w3);
    // First Step - v3 -> v3 - pow(v2)
    buVector4F TwoV2 = v2 + v2;
    buVector4F newV3 = v3 - TwoV2;
    // Second Step - v2 <-> v1
    buMatrix4x4 tmpMat2(
      v0.x, v0.y, v0.z, v0.w,
      v1.x, v1.y, v1.z, v1.w,
      v2.x, v2.y, v2.z, v2.w,
      newV3.x, newV3.y, newV3.z, newV3.w);

    buVector4F V0(tmpMat2.m_x0, tmpMat2.m_y0, tmpMat2.m_z0, tmpMat2.m_w0);
    buVector4F V2(tmpMat2.m_x1, tmpMat2.m_y1, tmpMat2.m_z1, tmpMat2.m_w1);
    buVector4F V1(tmpMat2.m_x2, tmpMat2.m_y2, tmpMat2.m_z2, tmpMat2.m_w2);
    buVector4F V3(tmpMat2.m_x3, tmpMat2.m_y3, tmpMat2.m_z3, tmpMat2.m_w3);

    // Third Step - v2 -> v2 - pow3(v0)
    buVector4F ThreeV0 = (V0 + V0) + V0;
    buVector4F newV2 = V2 - ThreeV0;

    buMatrix4x4 tmpMatrix3(V0, V1, newV2, V3);

    return (tmpMatrix3.m_x0 - tmpMatrix3.m_y1 - tmpMatrix3.m_z2 - tmpMatrix3.m_w3);
  }

  void
  buMatrix4x4::transpose() {
    buMatrix4x4 tmpMatrix = *this;
    // | x0 | x1 | x2 | x3 |T    | A1 | B1 | C1 | D1 |
  // | y0 | y1 | y2 | y3 |     | A2 | B2 | C2 | D2 |
  // | z0 | z1 | z2 | z3 |  =  | A3 | B3 | C3 | D3 |
  // | w0 | w1 | w2 | z3 |     | A4 | B4 | C4 | D4 |
    // Addition of column x
    m_x0 = tmpMatrix.m_x0;
    m_x1 = tmpMatrix.m_y0;
    m_x2 = tmpMatrix.m_z0;
    m_x3 = tmpMatrix.m_w0;
    // Addition of column y
    m_y0 = tmpMatrix.m_x1;
    m_y1 = tmpMatrix.m_y1;
    m_y2 = tmpMatrix.m_z1;
    m_y3 = tmpMatrix.m_w1;
    // Addition of column z
    m_z0 = tmpMatrix.m_x2;
    m_z1 = tmpMatrix.m_y2;
    m_z2 = tmpMatrix.m_z2;
    m_z3 = tmpMatrix.m_w2;
    // Addition of column w
    m_w0 = tmpMatrix.m_x3;
    m_w1 = tmpMatrix.m_y3;
    m_w2 = tmpMatrix.m_z3;
    m_w3 = tmpMatrix.m_w3;

    //*this = tmpMatrix;
  }

  buMatrix4x4& 
  buMatrix4x4::perspectiveMatrixfovLH(float _fovAngleY,
    float _aspectRatio,
    float _nearZ,
    float _farZ) {
    float h = buMath::cos(_fovAngleY) / buMath::sin(_fovAngleY);
    float w = h / _aspectRatio;
    float fRange = _farZ / (_farZ - _nearZ);

    *this = buMatrix4x4(w, 0, 0, 0,
      0, h, 0, 0,
      0, 0, fRange, 1,
      0, 0, -fRange * _nearZ, 0);
    return *this;
    // TODO: insert return statement here
  }

  buMatrix4x4& 
  buMatrix4x4::lookAtMatrixLH(buVector3F& _eye,
    buVector3F& _at,
    buVector3F& _up) {
    buVector3F zaxis = _at - _eye;
    zaxis.normalize();
    buVector3F UpCrosszaxis = _up.cross(zaxis);
    UpCrosszaxis.normalize();
    buVector3F xaxis = UpCrosszaxis;
    buVector3F zaxisCrossxaxis = zaxis.cross(xaxis);
    buVector3F yaxis = zaxisCrossxaxis;

    *this = buMatrix4x4(
      xaxis.x, yaxis.x, zaxis.x, 0,
      xaxis.y, yaxis.y, zaxis.y, 0,
      xaxis.z, yaxis.z, zaxis.z, 0,
      -xaxis.dot(_eye), -yaxis.dot(_eye), -zaxis.dot(_eye), 1);

    return *this;
  }

  buMatrix4x4&
  buMatrix4x4::rotateMatrixY(float _angle) {
    float fSinAngle = buMath::sinf(_angle);
    float fCosAngle = buMath::cosf(_angle);
    //tmpMat2.m_x0, tmpMat2.m_y0, tmpMat2.m_z0, tmpMat2.m_w0
    *this = buMatrix4x4(fCosAngle, 0.0f,fSinAngle, 0.0f,
                        0.0f, 1.0f,0.0f, 0.0f,
                        -fSinAngle,0.0f, fCosAngle, 0.0f,
                        0.0f, 0.0f,0.0f, 1.0f);

    return *this;
  }
  buMatrix4x4& 
  buMatrix4x4::rotateMatrix(buVector3F& _rotation, float angle) {
     float c = buMath::cos(angle);    // cosine
    float s = buMath::sin(angle);    // sine
    buVector3F vec = _rotation;
    vec.normalize();
    buMatrix4x4 result 
      { c + ((vec.x * vec.x) * (1 - c)), ((vec.x * vec.y) * (1 - c)) - (vec.z * s),  ((vec.x * vec.z) * (1 - c)) + (vec.y * s), 0, 
      ((vec.x * vec.y) * (1 - c)) + (vec.z * s), c + ((vec.y * vec.y) * (1 - c)),	((vec.y * vec.z) * (1 - c)) - (vec.x * s),
      0, ((vec.x * vec.z) * (1 - c)) - (vec.y * s)	, ((vec.y * vec.z) * (1 - c)) + (vec.x * s),	c + ((vec.z * vec.z) * (1 - c)), 0,
      0,0,0,1};
    
    *this *= result;
    return *this;
      
  }
  buMatrix4x4& 
  buMatrix4x4::translateMatrix(buVector3F& position) {
    buMatrix4x4 translation = buMatrix4x4(1, 0.0f, 0.0f, 0.0f,
                        0.0f, 1, 0.0f, 0.0f,
                        0.0f, 0.0f, 1, 0.0f,
                       position.x, position.y, position.z, 1.0f);
    *this *= translation;
    return *this;
  }
  buMatrix4x4& 
  buMatrix4x4::scaleMatrix(float _scale) {
    *this = buMatrix4x4(_scale, 0.0f, 0.0f, 0.0f,
                        0.0f, _scale, 0.0f, 0.0f,
                        0.0f, 0.0f, _scale, 0.0f,
                        0.0f, 0.0f, 0.0f,   1.0f);
    return *this;
  }
  buMatrix4x4& 
  buMatrix4x4::scaleMatrix(buVector3F& scale) {
     *this = buMatrix4x4(scale.x, 0.0f, 0.0f, 0.0f,
                        0.0f, scale.y, 0.0f, 0.0f,
                        0.0f, 0.0f, scale.z, 0.0f,
                        0.0f, 0.0f, 0.0f,   1.0f);
    return *this;
  }
  void buMatrix4x4::to4x4(buMatrix3x3& _mat) {
    *this = buMatrix4x4(_mat.m_x0, _mat.m_y0, _mat.m_z0, 0.0f,
                        _mat.m_x1, _mat.m_y1, _mat.m_z1, 0.0f,
                        _mat.m_x2, _mat.m_y2, _mat.m_z2, 0.0f,
                        0.0f, 0.0f, 0.0f,   1.0f);
  }
}
