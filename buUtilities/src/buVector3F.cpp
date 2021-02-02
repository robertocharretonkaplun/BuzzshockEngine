#include "buVector3F.h"

namespace buEngineSDK {
  const buVector3F buVector3F::Zero = buVector3F(0.0f, 0.0f, 0.0f);

  buVector3F::buVector3F(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }

  buVector3F::~buVector3F() {}

  buVector3F::buVector3F(const buVector3F& _v) : x(_v.x), y(_v.y), z(_v.z) { }

  buVector3F& 
  buVector3F::operator=(const buVector3F& _v) {
    x = _v.x;
    y = _v.y;
    z = _v.z;
    return *this;
  }

  buVector3F&
  buVector3F::operator+=(const buVector3F& _v) {
    *this = *this + _v;
    return *this;
  }

  buVector3F 
  buVector3F::operator+(const buVector3F& _v) const {
    return buVector3F(x + _v.x, y + _v.y, z + _v.z);
  }

  buVector3F&
  buVector3F::operator-=(const buVector3F& _v) {
    *this = *this - _v;
    return *this;
  }

  buVector3F
  buVector3F::operator-(const buVector3F& _v) const {
    return buVector3F(x - _v.x, y - _v.y, z - _v.z);
  }

  void
  buVector3F::operator*=(const float _a) {
    x *= _a;
    y *= _a;
    z *= _a;
  }

  buVector3F 
  buVector3F::operator*(const float _a) const {
    return buVector3F(_a * x, _a * y, _a * z);
  }

  void
  buVector3F::operator/=(const float _a) {
    x = x / _a;
    y = y / _a;
    z = z / _a;
  }

  buVector3F
  buVector3F::operator/(const float _a) const {
    return buVector3F(x / _a, y / _a, z / _a);
  }

  float
  buVector3F::dot(const buVector3F& _v) const {
    return x * _v.x + y * _v.y + z * _v.z;
  }

  float
  buVector3F::operator*(const buVector3F& _v) const {
    return x * _v.x + y * _v.y + z * _v.z;
  }

  buVector3F
  buVector3F::cross(const buVector3F& _v) const {
    return buVector3F(y * _v.z - z * _v.y,
      z * _v.x - x * _v.z,
      x * _v.y - y * _v.x);
  }

  void
  buVector3F::operator%=(const buVector3F _v) {
    *this = cross(_v);
  }

  buVector3F 
  buVector3F::operator%(const buVector3F& _v) const {
    return buVector3F(y * _v.z - z * _v.y,
      z * _v.x - x * _v.z,
      x * _v.y - y * _v.x);
  }

  float 
  buVector3F::magnitude() {
    return buMath::sqrt(sqrMagnitude());
  }

  float 
  buVector3F::sqrMagnitude() {
    return buMath::sqr(x) + buMath::sqr(y) + buMath::sqr(z);
  }

  void
  buVector3F::normalize() {
    float sqrMag = sqrMagnitude();

    if (0.0f == sqrMag) {
      return;
    }

    float normValue = buMath::invSqrt(sqrMag);
    x = x * normValue;
    y = y * normValue;
    z = z * normValue;
    
  }

  float *
  buVector3F::data() {
    return nullptr;
  }
}
