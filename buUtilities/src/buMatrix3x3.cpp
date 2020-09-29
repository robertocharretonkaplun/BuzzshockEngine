#include "buMatrix3x3.h"

namespace buEngineSDK {
  const buMatrix3x3 buMatrix3x3::ZERO = buMatrix3x3(0.0f, 0.0f, 0.0f,
                                                    0.0f, 0.0f, 0.0f,
                                                    0.0f, 0.0f, 0.0f);

  const buMatrix3x3 buMatrix3x3::IDENTITY = buMatrix3x3(1.0f, 0.0f, 0.0f,
                                                        0.0f, 1.0f, 0.0f,
                                                        0.0f, 0.0f, 1.0f);

  buMatrix3x3::buMatrix3x3()
  {
    *this = buMatrix3x3::IDENTITY;
  }

  buMatrix3x3::buMatrix3x3(float x0, float y0, float z0,
                           float x1, float y1, float z1,
                           float x2, float y2, float z2) :
                           m_x0(x0), m_y0(y0), m_z0(z0),
                           m_x1(x1), m_y1(y1), m_z1(z1),
                           m_x2(x2), m_y2(y2), m_z2(z2) { }

  buMatrix3x3::buMatrix3x3(buVector4F& Vx, buVector4F& Vy,
    buVector4F& Vz) :
    m_x0(Vx.x), m_y0(Vy.x), m_z0(Vz.x),
    m_x1(Vx.y), m_y1(Vy.y), m_z1(Vz.y),
    m_x2(Vx.z), m_y2(Vy.z), m_z2(Vz.z) { }

  buMatrix3x3::buMatrix3x3(const buMatrix3x3& _mat) :
    m_x0(_mat.m_x0), m_y0(_mat.m_y0), m_z0(_mat.m_z0),
    m_x1(_mat.m_x1), m_y1(_mat.m_y1), m_z1(_mat.m_z1),
    m_x2(_mat.m_x2), m_y2(_mat.m_y2), m_z2(_mat.m_z2) { }

  buMatrix3x3::~buMatrix3x3() {
  }

  buMatrix3x3&
    buMatrix3x3::operator+=(const buMatrix3x3& _mat) {
    *this = *this + _mat;
    return *this;
  }

  buMatrix3x3
    buMatrix3x3::operator+(const buMatrix3x3& _mat) const {
    return buMatrix3x3(
      m_x0 + _mat.m_x0, m_y0 + _mat.m_y0, m_z0 + _mat.m_z0,
      m_x1 + _mat.m_x1, m_y1 + _mat.m_y1, m_z1 + _mat.m_z1,
      m_x2 + _mat.m_x2, m_y2 + _mat.m_y2, m_z2 + _mat.m_z2);
  }

  buMatrix3x3&
    buMatrix3x3::operator-=(const buMatrix3x3& _mat) {
    *this = *this - _mat;
    return *this;
  }

  buMatrix3x3
    buMatrix3x3::operator-(const buMatrix3x3& _mat) const {
    return buMatrix3x3(
      m_x0 - _mat.m_x0, m_y0 - _mat.m_y0, m_z0 - _mat.m_z0,
      m_x1 - _mat.m_x1, m_y1 - _mat.m_y1, m_z1 - _mat.m_z1,
      m_x2 - _mat.m_x2, m_y2 - _mat.m_y2, m_z2 - _mat.m_z2);
  }

  buMatrix3x3&
    buMatrix3x3::operator*=(const buMatrix3x3& _mat) {
    *this = *this * _mat;
    return *this;
  }

  buMatrix3x3
    buMatrix3x3::operator*(const buMatrix3x3& _mat) const {
    // Row 0
    float x0 = m_x0 * _mat.m_x0 + m_y0 * _mat.m_x1 + m_z0 * _mat.m_x2;
    float y0 = m_x0 * _mat.m_y0 + m_y0 * _mat.m_y1 + m_z0 * _mat.m_y2;
    float z0 = m_x0 * _mat.m_z0 + m_y0 * _mat.m_z1 + m_z0 * _mat.m_z2;
    // Row 1						
    float x1 = m_x1 * _mat.m_x0 + m_y1 * _mat.m_x1 + m_z1 * _mat.m_x2;
    float y1 = m_x1 * _mat.m_y0 + m_y1 * _mat.m_y1 + m_z1 * _mat.m_y2;
    float z1 = m_x1 * _mat.m_z0 + m_y1 * _mat.m_z1 + m_z1 * _mat.m_z2;
    // Row 2						
    float x2 = m_x2 * _mat.m_x0 + m_y2 * _mat.m_x1 + m_z2 * _mat.m_x2;
    float y2 = m_x2 * _mat.m_y0 + m_y2 * _mat.m_y1 + m_z2 * _mat.m_y2;
    float z2 = m_x2 * _mat.m_z0 + m_y2 * _mat.m_z1 + m_z2 * _mat.m_z2;

    return buMatrix3x3(x0, y0, z0,
                       x1, y1, z1,
                       x2, y2, z2);
  }

  float
    buMatrix3x3::determinant() {
    
    return 0;
  }

  void
    buMatrix3x3::transpose() {
    buMatrix3x3 tmpMatrix = *this;
    // | x0 | x1 | x2 | x3 |T    | A1 | B1 | C1 | D1 |
  // | y0 | y1 | y2 | y3 |     | A2 | B2 | C2 | D2 |
  // | z0 | z1 | z2 | z3 |  =  | A3 | B3 | C3 | D3 |
  // | w0 | w1 | w2 | z3 |     | A4 | B4 | C4 | D4 |
    // Addition of column x
    m_x0 = tmpMatrix.m_x0;
    m_x1 = tmpMatrix.m_y0;
    m_x2 = tmpMatrix.m_z0;
    // Addition of column y
    m_y0 = tmpMatrix.m_x1;
    m_y1 = tmpMatrix.m_y1;
    m_y2 = tmpMatrix.m_z1;
    // Addition of column z
    m_z0 = tmpMatrix.m_x2;
    m_z1 = tmpMatrix.m_y2;
    m_z2 = tmpMatrix.m_z2;

    //*this = tmpMatrix;
  }

}
