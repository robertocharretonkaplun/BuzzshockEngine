/**
 * @file buCoreSampler.h
 * @version 1.0
 * @date 13/07/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of providing virtual methods for the "buDXSampler" class.
 */
#pragma once
#include <buPrerequisitesCore.h>

namespace buEngineSDK {
	class buCoreSampler	{
	public:
		 /**
		  * @brief Default Constructor
			*/
		buCoreSampler() = default;
		/**
		 * @brief Destructor
		 */
		~buCoreSampler() {};
		/**
		 * @brief Virtual method that initialize the object.
		 */
		virtual void
		init(uint32 _filter, uint32 _addressU, uint32 _addressV, uint32 _addressW, 
				 uint32 _comparisonFunc, float _minLOD, float _maxLOD) = 0;
	};
}
