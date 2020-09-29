/**
* @file buCoreRenderTargetView.h
* @version 1.0
* @date 13/07/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
* @brief Class in charge of providing virtual methods for the
* "buDXRenderTargetView" class.
* @bug
*/
#pragma once
#include <buPrerequisitesCore.h>

namespace buEngineSDK {
	class buCoreRenderTargetView {
	public:
		/**
		 * @brief Default constructor
		 */
		buCoreRenderTargetView() = default;
		/**
		 * @brief Destructor
		 */
		~buCoreRenderTargetView() {};
		/**
		 * @brief Method that initialize the object.
		 */
		virtual void 
		init() = 0;
	};
}
