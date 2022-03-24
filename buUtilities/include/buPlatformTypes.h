/**
* @file buPlatformTypes.h
* @version 1.0
* @date 28/05/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
* @brief Define the basic platform type variables. For porting,this might be the place to start
* @bugs
*/
#pragma once
#include <cstdint>
#include "buPlatformDefines.h"

namespace buEngineSDK {
  using std::uint8_t;
  using std::uint16_t;
  using std::uint32_t;
  using std::uint64_t;
  using std::int8_t;
  using std::int16_t;
  using std::int32_t;
  using std::int64_t;

  /**
   * @brief Basic unsigned types
   */
  using uint8 = int8_t;    // 8-bit unsigned
  using uint16 = int16_t;  // 16-bit unsigned
  using uint32 = int32_t;  // 32-bit unsigned
  using uint64 = int64_t;  // 64-bit unsigned

  /**
   * @brief Basic signed types
   */
  using int8 = int8_t;    // 8-bit unsigned
  using int16 = int16_t;  // 16-bit unsigned
  using int32 = int32_t;  // 32-bit unsigned
  using int64 = int64_t;  // 64-bit unsigned

  /**
   * @brief Character types
   */
#if BU_COMPILER == BU_COMPILER_MSVC
  using WCHAR = wchar_t;  // Wide Character (used by Visual Studio)
#else
  using WCHAR = unsigned short;  // Wide Character (Any other Compiler)
#endif
  using ANSICHAR = char; // ANSI character type
  using UNICHAR = WCHAR; // UNICODE character type
  using BYTE = char;
  using UBYTE = unsigned char;
  /**
   * @brief NULL data type
   */
  using TYPE_OF_NULL = int32;

  /**
   * @brief SIZE_T is an architecture dependdent data type 
   */
  using SIZE_T = size_t;
}
