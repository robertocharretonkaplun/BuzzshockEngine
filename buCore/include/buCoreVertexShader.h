/**
 * @file buCoreVertexShader.h
 * @version 1.0
 * @date 13/07/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of providing virtual methods 
 * @bug
 */
#pragma once
#include <buPrerequisitesCore.h>

namespace buEngineSDK {
	class buCoreVertexShader {
	public:
		/**
		 * @brief Default Constructor
		 */
		buCoreVertexShader() = default;
		/**
		 * @brief Destructor
		 */
		~buCoreVertexShader() {};
		/**
		* @brief Virtual method that initialize the object.
		*/
		virtual void
		init(WString _fileName, String _entryPoint, String _shaderModel) = 0;
	};
}
