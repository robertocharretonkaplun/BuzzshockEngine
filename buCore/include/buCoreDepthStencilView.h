/**
 * @file buCoreDepthStencilView.h
 * @version 1.0
 * @date 13/07/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of initializing virtual functions for the
 * "buDXDepthStencilView" class.
 */
#pragma once
#include <buPrerequisitesCore.h>

namespace buEngineSDK {
	class buCoreDepthStencilView {
	public:
		/**
		 * @brief Default constructor 
		 */
		buCoreDepthStencilView() = default;
		/**
		 * @brief Destructor
		 */
		~buCoreDepthStencilView() {};
		/*
		 * @brief Virtual method that initialize the depth stencil object.
		 */
		virtual void 
		init(uint32 /*_format*/, uint32 /*_viewDimension*/, uint32 /*_mipSlice*/) {};
	private:

	};
}
