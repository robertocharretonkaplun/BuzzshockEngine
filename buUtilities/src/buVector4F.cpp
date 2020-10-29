#include "buVector4F.h"

namespace buEngineSDK {
  const buVector4F buVector4F::Zero = buVector4F(0.0f, 0.0f, 0.0f, 0.0f);

  buVector4F::buVector4F(float _x, float _y, float _z, float _w)
    : x(_x), y(_y), z(_z), w(_w) { }

  buVector4F::~buVector4F() { }

  buVector4F::buVector4F(const buVector4F& _v)
    : x(_v.x), y(_v.y), z(_v.z), w(_v.w) { }

  buVector4F::buVector4F(float _arr[4]) 
    : x(_arr[0]), y(_arr[1]), z(_arr[2]), w(_arr[0]) {}

  buVector4F::buVector4F(float _arr[3], float _const)
    : x(_arr[0]), y(_arr[1]), z(_arr[2]), w(_const) {}


  buVector4F&
  buVector4F::operator=(const buVector4F& _v) {
    x = _v.x;
    y = _v.y;
    z = _v.z;
    w = _v.w;
    return *this;
  }

  buVector4F& 
  buVector4F::operator+=(const buVector4F& _v) {
    *this = *this + _v;
    return *this;
  }

  buVector4F 
  buVector4F::operator+(const buVector4F& _v) const {
    return buVector4F(x + _v.x, y + _v.y, z + _v.z, w + _v.w);
  }

  buVector4F& 
  buVector4F::operator-=(const buVector4F& _v) {
    *this = *this - _v;
    return *this;
  }

  buVector4F
  buVector4F::operator-(const buVector4F& _v) const {
    return buVector4F(x - _v.x, y - _v.y, z - _v.z, w - _v.w);
  }

  void 
  buVector4F::operator*=(const float _a) {
    x *= _a;
    y *= _a;
    z *= _a;
    w *= _a;
  }

  buVector4F
  buVector4F::operator*(const float _a) const {
    return buVector4F(_a * x, _a * y, _a * z, _a * w);
  }

  void
  buVector4F::operator/=(const float _a) {
    x = x / _a;
    y = y / _a;
    z = z / _a;
    w = w / _a;
  }

  buVector4F 
  buVector4F::operator/(const float _a) const {
    return buVector4F(x / _a, y / _a, z / _a, w / _a);
  }
}
