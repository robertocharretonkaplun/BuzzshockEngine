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
#include "buCoreVertexShader.h"

namespace InputClassification {
	enum E {
		BU_INPUT_PER_VERTEX_DATA = 0,
		BU_INPUT_PER_INSTANCE_DATA = 1
	};
}

namespace buEngineSDK {

	class buCoreInputLayout {
	public:
		/**
		 * @brief Default constructor
		 */
		buCoreInputLayout() = default;
		
		/**
		 * @brief Destructor
		 */
		~buCoreInputLayout() {};
		
		/** 
		 * @brief Virtual method that initialize the object.
		 */
		virtual void 
	  init(Vector<String> _semanticNames) = 0;
	private:

	};
}
