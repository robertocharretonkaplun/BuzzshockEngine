#include "buDegrees.h"

namespace buEngineSDK {
	buDegrees::buDegrees(float _d) {
		m_degrees = _d;	
	}

	buDegrees::buDegrees(const buDegrees& _d)	{
		m_degrees = _d.m_degrees;
	}
	
	buDegrees::~buDegrees()	{
	}

	float 
	buDegrees::getRadians()	{
		return m_degrees * (3.1415926535f / 180.0f);
	}

	float
	buDegrees::getDegrees()	{
		return m_degrees;
	}
}