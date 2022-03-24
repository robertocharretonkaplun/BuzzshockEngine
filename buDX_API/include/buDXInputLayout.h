/**
 * @file 
 * @version 
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once
#include <buPrerequisitesDX.h>
#include <d3d11.h>
#include "buCoreInputLayout.h"

namespace buEngineSDK {
	class buDXInputLayout : public buCoreInputLayout
	{
	public:
		/**
		 * @brief 
		 */
		buDXInputLayout();
		/**
		 * @brief 
		 */
		~buDXInputLayout();
		/** 
		 * @brief 
		 * @param 
		 * @return 
		 * @bug 
		 */
		void 
	  init(Vector<String> _semanticNames) override;
	public:
		/**
		 * @brief 
		 */
		ID3D11InputLayout* m_inputLayout;
		/**
		 * @brief 
		 */
		Vector<D3D11_INPUT_ELEMENT_DESC> m_descriptor;
	};
}