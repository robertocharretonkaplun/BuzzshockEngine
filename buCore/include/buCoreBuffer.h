/*
 * @file buCoreBuffer.h
 * @version 1.0
 * @date 13/07/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of providing virtual methods for the "buDXBuffer" class.
 */
#pragma once
#include <buPrerequisitesCore.h>

namespace buEngineSDK {
	class buCoreBuffer {
	public:
		/**
		 * @brief Default Constructor
		 */
		buCoreBuffer() = default;
		/**
		 * @brief Destructor 
		 */
		~buCoreBuffer() {};
		/**
		 * @brief Virtual method the initialize the object.
		 */
		virtual void
		init(uint32 Usage, uint32 ByteWidth, uint32 BindFlags,
			   uint32 CPUAccessFlags, uint32 startSlot, uint32 numBuffers,
				 uint32 stride, uint32 offset, void* bufferData) = 0;
	private:

	};
}
