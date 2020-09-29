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
#include "buCoreBuffer.h"

namespace buEngineSDK {
 class buDXBuffer : public buCoreBuffer
 {
 public:
 	/**
 	 * @brief 
 	 */
 	buDXBuffer();
 	/**
 	 * @brief 
 	 */
 	~buDXBuffer();
  /**
	 * @brief 
	 */
	void
	init(uint32 Usage, uint32 ByteWidth, uint32 BindFlags,
		   uint32 CPUAccessFlags, uint32 startSlot, uint32 numBuffers,
			 uint32 stride, uint32 offset, void* bufferData) override;
 public:
 	/**
 	 * @brief Buffer ID.
 	 */
 	ID3D11Buffer* m_buffer;

  /**
   * @brief Buffer descriptor.
   */
  D3D11_BUFFER_DESC m_descriptor;
  
  /*
   * @brief Buffer subresource
   */
  D3D11_SUBRESOURCE_DATA m_subresourceData;
  
  /**
   * @brief Member that stores the usage.
   */
  uint32 m_usage = 0;
  
  /**
   * @brief Member that stores the buffer byte width.
   */
  uint32 m_byteWidth = 0;

  /**
   * @brief Member that stores the buffer bind flags.
   */
  uint32 m_bindFlags = 0;

  /**
   * @brief Member that stores the CPU access flags.
   */
  uint32 m_CPUAccessFlags = 0;

  /**
   * @brief Member that stores the start slot.
   */
  uint32 m_startSlot = 0;

  /**
   * @brief Member that stores the number of buffers.
   */
  uint32 m_numBuffers = 0;

  /**
   * @brief Member that stores the stride of the buffer.
   */
  uint32 m_stride = 0; 

  /**
   * @brief Member that stores the offset of the buffer.
   */
  uint32 m_offset = 0;

  /**
   * @brief Member that stores the buffer data.
   */
  void* m_bufferData;
 };
}
