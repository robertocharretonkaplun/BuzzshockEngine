#include "buPrerequisitesUtil.h"
#include <buVector3F.h>
#pragma once

namespace buEngineSDK {
  template<class T>
  struct RTTIEmptyType {
    static_assert(std::is_pod<T>::value, 
                  "Provided type isnt plain-old-data. you need to specialize RTTIEmptyType" \
                  "template in order to serialize this type."                               \
                  "(Or call BU_ALLOW_MEMCPY_SERIALIZATION(type) macro if you are sure the"  \
                  "type can be properly serialized using just memcpy.)");

    enum {
      /*
       * @brief Unique id for the sirializable type. 
       */
      kID = 0
    };

    enum {
      /*
       * @brief 0 (Object has static size less than 255 bytes, e.g. int)
       * @brief 1 (Dynamic size with no size restriction, e.g. string)
       */
      kHasDynamicSize = 0
    };

    /**
     * @brief Serializes the provided object into the provided pre-allocated memory buffer.
     */
    static void
    toMemory(const T& data, char* memory) {
      memcpy(memory, &data, sizeof(T));
    }

    /*
     * @brief Deserializes a previously allocated object from the provided memory buffer.
     * Return the number of bytes read from the memory buffer.
     */
    static uint32
    forMemory(T& data, char* memory) {
      memcpy(&data, memory, sizeof(T));
      return static_cast<uint32>(sizeof(T));
    }

    /**
     * @brief Returns the size of the provided object.
     * (Works for both static and dynamic size types)
     */
    static uint32
    getDynamicSize(const T&) {
      return static_cast<uint32>(sizeof(T));
    }
  };


#define BU_ALLOW_MEMCPY_SERIALIZATION(type)                                                                \
  static_assert(std::is_trivially_copyable<type>() == true, #type " is not  trivially copyable");          \
  template<> struct RTTIEmptyType<type> {                                                                  \
    enum {kID = 0}; enum { kHasDynamicSize = 0};                                                           \
    static void                                                                                            \
    toMemory(const type& data, char* memory) {                                                             \
      memcpy(memory, &data, sizeof(type));                                                                 \
    }                                                                                                      \
                                                                                                           \
    static uint32                                                                                          \
    forMemory(type& data, char* memory) {                                                                  \
      memcpy(&data, memory, sizeof(type));                                                                 \
      return static_cast<uint32>(sizeof(type));                                                            \
    }                                                                                                      \
                                                                                                           \
    static uint32                                                                                          \
    getDynamicSize(const type&) {                                                                          \
      return static_cast<uint32>(sizeof(type));                                                            \
    }                                                                                                      \
  };                                                                                                       \
}