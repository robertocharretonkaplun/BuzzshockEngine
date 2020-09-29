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

namespace buEngineSDK {
	class buResource
	{
	public:
		buResource() = default;
		~buResource() = default;

		void 
		setResourceID(uint32 id) {
			ID = id;
		}
	private:
		uint32 ID;
	};
}