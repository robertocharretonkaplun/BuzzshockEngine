#include "buRay.h"

namespace buEngineSDK {
	buRay::buRay(buVector3F _origin, buVector3F _direction, float _distance) {
		m_origin = _origin;
		m_direction = _direction;
		m_distance = _distance;
	}

	buRay::buRay(const buRay& _r)	{
		m_origin = _r.m_origin;
		m_direction = _r.m_direction;
		m_distance = _r.m_distance;
	}

	buRay::~buRay()	{
	}

	buVector3F 
	buRay::Ray(buVector3F _direction, float _distance) {
		_direction.x += _distance;
		_direction.y += _distance;
		_direction.z += _distance;

		return m_origin + _direction;
	}
}
