/**
 * @file 
 * @version 
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once
#include <d3d11.h>
#include "buCoreRenderTargetView.h"

namespace buEngineSDK {
	class buDXRenderTargetView : public buCoreRenderTargetView
	{
	public:
		/**
		 * @brief 
		 */
		buDXRenderTargetView();
		/**
		 * @brief 
		 */
		~buDXRenderTargetView();
		/**
		 * @brief
		 */
		void
		init() override;
	public:
		ID3D11RenderTargetView* m_renderTargetView;
	};
}