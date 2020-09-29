#include "buSphere.h"

namespace buEngineSDK {
	buSphere::buSphere(buVector3F& _center, float _radius) {
		m_center = _center;
		m_radius = _radius;
	}

	buSphere::buSphere(const buSphere& _s) {
		m_center = _s.m_center;
		m_radius = _s.m_radius;
	}

	buSphere::~buSphere()	{
	}
}
