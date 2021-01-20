#include "buHeap.h"

namespace buEngineSDK {
  buHeap::buHeap(SIZE_T size) : m_memSize(size) {
    m_pData = new BYTE[size];
  }

  void*
  buHeap::alloc(SIZE_T size) {
    Allocation newAlloc;
    BYTE* pLastData = m_pData;

    for (auto& myAlloc : m_allocs) {
      //if () {
      //  //myAlloc.pointerPos + size 
      //}
      //SIZE_T freeSize = &myAlloc;
    }

    return nullptr;
  }
}