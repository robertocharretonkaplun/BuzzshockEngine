#pragma once
#include "buPrerequisitesUtil.h"
#include "buVector2F.h"
namespace buEngineSDK {
	class BU_UTILITY_EXPORT buBoxMuller
	{
	public:
		buBoxMuller() = default;
		~buBoxMuller() = default;

		void 
		generateGaussianNoise(float mu, float sigma);
	private:

	};
}