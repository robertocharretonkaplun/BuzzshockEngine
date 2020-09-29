#include "buVector4I.h"

namespace buEngineSDK {
 const buVector4I buVector4I::Zero = buVector4I(0, 0, 0, 0);
 
 buVector4I::buVector4I(int32 _x, int32 _y, int32 _z, int32 _w) 
   : x(_x), y(_y), z(_z), w(_w) { }
 
 buVector4I::~buVector4I() { }
 
 buVector4I::buVector4I(const buVector4I& _v) 
   : x(_v.x), y(_v.y), z(_v.z), w(_v.w) { }
 
 buVector4I&
 buVector4I::operator=(const buVector4I& _v) {
   x = _v.x;
   y = _v.y;
   z = _v.z;
   w = _v.w;
   return *this;
 }
 
 buVector4I& 
 buVector4I::operator+=(const buVector4I& _v) {
   *this = *this + _v;
   return *this;
 }
 
 buVector4I
 buVector4I::operator+(const buVector4I& _v) const {
   return buVector4I(x + _v.x, y + _v.y, z + _v.z, w + _v.w);
 }
 
 buVector4I& 
 buVector4I::operator-=(const buVector4I& _v) {
   *this = *this - _v;
   return *this;
 }
 
 buVector4I
 buVector4I::operator-(const buVector4I& _v) const {
   return buVector4I(x - _v.x, y - _v.y, z - _v.z, w - _v.w);
 }
 
 void
 buVector4I::operator*=(const int32 _a) {
   x *= _a;
   y *= _a;
   z *= _a;
   w *= _a;
 }
 
 buVector4I
 buVector4I::operator*(const int32 _a) const {
   return buVector4I(_a * x, _a * y, _a * z, _a * w);
 }
 
 void 
 buVector4I::operator/=(const int32 _a) {
   x = x / _a;
   y = y / _a;
   z = z / _a;
   w = w / _a;
 }
 
 buVector4I
 buVector4I::operator/(const int32 _a) const {
   return buVector4I(x / _a, y / _a, z / _a, w / _a);
 }
}
