#include "buPlane.h"

namespace buEngineSDK {
	buPlane::buPlane(const buVector4F& V) 
		: x(V.x), y(V.y), z(V.z), w(V.w) { }

	buPlane::buPlane(float X, float Y, float Z, float W) 
		: x(X), y(Y), z(Z), w(W) { }

	buPlane::~buPlane() {	}

	float 
  buPlane::planDot(const buVector3F& V) const {
		return x * V.x + y * V.y + z * V.z - w;
	}
	
	buPlane
	buPlane::flip() const {
		return buPlane(-x, -y, -z, -w);
	}
}