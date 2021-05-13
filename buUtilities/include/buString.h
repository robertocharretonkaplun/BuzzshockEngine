/**
* @file buString.h
* @version 1.0
* @date 28/05/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
* @brief 
* @bugs
*/
#pragma once
/**
 * @brief Includes
 */
#include "buPlatformDefines.h"
#include <string>

namespace buEngineSDK {
 using std::char_traits;
 using std::basic_string;
 using std::basic_stringstream;
 
 /**
  * @brief Basic string that uses buEngine memory allocators
  */
 template<typename T>
 using BasicString = basic_string<T, char_traits<T>, std::allocator<T>>;
 
 /**
  * @brief Basic string stream that uses buEngine memory allocators
  */
 template<typename T>
 using BasicStringStream = basic_stringstream<T, char_traits<T>, std::allocator<T>>;
 
 /**
  * @brief Wide string used primarly for handling Unicode text.
  */
 using WString = BasicString<UNICHAR>;
 
 /**
  * @brief Narrow string used primarly for handling ASCII text.
  */
 using String = BasicString<ANSICHAR>;
 
 /**
  * @brief Wide string stream used for primarily for constructiong strings 
  * consisting for Unicode text
  */
 using WStringStream = BasicStringStream<UNICHAR>;
 
 /**
  * @brief Wide string stream used for primarily for constructing  strings
  * consisting of ASCII text.
  */
 using StringStream = BasicStringStream<ANSICHAR>;

 
}


namespace buEngineSDK {
  struct StringUtilities {
    static uint32 hash(String _string) {
      uint32 hash = 0;
      for (char i : _string) {
        hash = 65599 * hash + i;
      }
      return hash ^ (hash >> 16);
    };

    static String ToString(uint32 _val) {
      String str;
      StringStream ss;
      ss << _val;
      ss >> str;
      return str;
    }
  };
}