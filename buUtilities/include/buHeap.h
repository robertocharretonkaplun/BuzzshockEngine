// video ref: MA1-Heap-11Jan2021 
#pragma once
#include "buPrerequisitesUtil.h"
#include "buNumLimits.h"
namespace buEngineSDK {

	struct Allocation {
		void* pointerPos = nullptr;
		SIZE_T size = 0;
	};

	class buHeap {
	private:

	public:
		buHeap(SIZE_T size);
		~buHeap();
	public:
		void* alloc(SIZE_T size);
	public:
		SIZE_T m_memSize;
		BYTE* m_pData;
		List<Allocation> m_allocs;
	};
}