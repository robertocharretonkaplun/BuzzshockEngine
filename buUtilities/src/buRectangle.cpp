#include "buRectangle.h"

namespace buEngineSDK {
	buRectangle::buRectangle(float _x, float _y, float _width, float _lenght) :
		m_x(_x), m_y(_y), m_width(_width), m_lenght(_lenght) { }
	
	buRectangle::~buRectangle()	{
	}

	float
	buRectangle::getArea() {
		return m_width * m_lenght;
	}

	float 
	buRectangle::getPerimeter()	{
		return (m_lenght * m_lenght + m_width * m_width);
	}
}
