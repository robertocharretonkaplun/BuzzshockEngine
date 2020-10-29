/**
 * @file 
 * @version 
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once
#include <buPrerequisitesCore.h>

namespace buEngineSDK {
	class buCorePixelShader	{
	public:
		/**
		 * @brief Default constructor
		 */
		buCorePixelShader() = default;
		
		/**
		 * @brief Destructor 
		 */
		~buCorePixelShader() {};

		/**
		* @brief Virtual method that initialize the object.
		*/
		virtual void
		init(WString _fileName) = 0;
	};
}
