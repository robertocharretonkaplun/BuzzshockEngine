/**
 * @file .h
 * @version 1.0
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bugs
 */
#pragma once
#include <d3d11.h>
#include <buCoreSampler.h>

namespace buEngineSDK {
	class buDXSampler : public buCoreSampler
	{
	public:
		/**
			* @brief Default Constructor
			*/
		buDXSampler();
		/**
		 * @brief Destructor
		 */
		~buDXSampler();
		/**
		 * @brief
		 */
		void
		init(uint32 _filter, uint32 _addressU, uint32 _addressV, uint32 _addressW,
		     uint32 _comparisonFunc, float _minLOD, float _maxLOD) override;

	public:
		/**
		 * @brief
		 */
		ID3D11SamplerState* m_sampler;
		/**
		 * @brief
		 */
		D3D11_SAMPLER_DESC m_descriptor;
		/**
		 * @brief
		 */
		uint32 m_filter;
		/**
		 * @brief
		 */
		uint32 m_addressU;
		/**
		 * @brief
		 */
		uint32 m_addressV;
		/**
		 * @brief
		 */
		uint32 m_addressW;
		/**
		 * @brief
		 */
		uint32 m_comparisonFunc;
		/**
		 * @brief
		 */
		float m_minLOD;
		/**
		 * @brief
		 */
		float m_maxLOD;
	};
}