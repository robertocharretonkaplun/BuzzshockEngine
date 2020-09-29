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
#include <buCoreDepthStencilView.h>

namespace buEngineSDK {
	class buDXDepthStencilView : public buCoreDepthStencilView
	{
	public:
		/**
		 * @brief Default constructor
		 */
		buDXDepthStencilView();
		/**
		 * @brief Destructor
		 */
		~buDXDepthStencilView();
		/*
		 * @brief
		 */
		void
		init(uint32 _format, uint32 _viewDimension, uint32 _mipSlice) override;
	public:
		/**
		 * @brief Depth Stencil View ID
		 */
		ID3D11DepthStencilView* m_depthStencilView;
		/**
		 * @brief Depth Stencil View descriptor
		 */
		D3D11_DEPTH_STENCIL_VIEW_DESC m_descriptor;
		/**
		 * @brief 
		 */
		uint32 m_format;
		/**
		 * @brief 
		 */
		uint32 m_viewDimension;
		/**
		 * @brief 
		 */
		uint32 m_mipSlice;
	};
}
