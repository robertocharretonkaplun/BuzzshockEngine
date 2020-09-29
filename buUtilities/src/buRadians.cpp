#include "buRadians.h"

namespace buEngineSDK {
	buRadians::buRadians(float _r) {
		m_radians = _r;
	}

	buRadians::buRadians(const buRadians& _r)	{
		m_radians = _r.m_radians;
	}
	
	buRadians::~buRadians()	{
	}

	float 
	buRadians::getDegree() {
		return m_radians * (3.1415926535f / 180.0f);
	}

	float
	buRadians::getRadians()	{
		return m_radians;
	}
}
