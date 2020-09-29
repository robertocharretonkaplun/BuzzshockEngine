#include "buVector2I.h"

namespace buEngineSDK {
  const buVector2I buVector2I::Zero = buVector2I(0, 0);

  buVector2I::buVector2I(int32 _x, int32 _y) : x(_x), y(_y) { }

  buVector2I::~buVector2I() { }

  buVector2I::buVector2I(const buVector2I& _v) : x(_v.x), y(_v.y) { }

  buVector2I&
  buVector2I::operator=(const buVector2I& _v) {
    x = _v.x;
    y = _v.y;
    return *this;
  }

  buVector2I& 
  buVector2I::operator+=(const buVector2I& _v) {
    *this = *this + _v;
    return *this;
  }

  buVector2I
  buVector2I::operator+(const buVector2I& _v) const {
    return buVector2I(x + _v.x, y + _v.y);
  }

  buVector2I&
  buVector2I::operator-=(const buVector2I& _v) {
    *this = *this - _v;
    return *this;
  }

  buVector2I
  buVector2I::operator-(const buVector2I& _v) const {
    return buVector2I(x - _v.x, y - _v.y);
  }

  void
  buVector2I::operator*=(const int32 _a) {
    x *= _a;
    y *= _a;
  }

  buVector2I 
  buVector2I::operator*(const int32 _a) const {
    return buVector2I(_a*x,_a*y);
  }

  void
  buVector2I::operator/=(const int32 _a) {
    x = x / _a;
    y = y / _a;
  }

  buVector2I 
  buVector2I::operator/(const int32 _a) const {
    return buVector2I(x / _a, y / _a);
  }

  buVector2I 
  buVector2I::cross(const buVector2I& _v) const {
    return buVector2I( x * _v.y, 
                       y *_v.x );
  }

  void 
  buVector2I::operator%=(const buVector2I _v) {
    *this = cross(_v);
  }

  buVector2I
  buVector2I::operator%(const buVector2I& _v) const {
    return buVector2I(x * _v.y,
                      y * _v.x);
  }
}
