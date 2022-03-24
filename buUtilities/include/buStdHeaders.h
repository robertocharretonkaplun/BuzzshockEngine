/**
* @file buStdHeaders.h
* @version 1.0
* @date 28/0t5/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
* @brief This file includes the most common and required libraries
* @bugs None.
*/
#pragma once

/**
 * @brief C type objects
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>

/**
 * @brief For memory managment
 */
#include <memory>

/**
 * @brief STL containers
 */
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <set>
#include <forward_list>
#include <deque>
#include <queue>
#include <bitset>
#include <array>

#include <unordered_map>
#include <unordered_set>

/**
 * @brief STD algorithms & functions
 */
#include <algorithm>
#include <functional>
#include <limits>
#include <iterator>

/**
 * @brief C++ stream stuff
 */
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

/**
 * @brief 
 */
#include <time.h>

/**
 * @brief C Types and Stats
 */
extern "C" {
#include <sys/types.h>
#include <sys/stat.h>
}

/**
 * @brief Windows specifics
 */
#if BU_PLATFORM == BU_PLATFORM_WIN32
  // Undefined min & max
#undef min
#undef max
#if !defined(NOMINMAX)&& defined(_MSC_VER)
#  define NOMINMAX  // Rquired to stop windows.h messing up std::min
#endif
#endif

/**
 * @brief Linux specifics
 */
#if BU_PLATFORM == BU_PLATFORM_LINUX
extern "C" {
#include <unistd.h>
#include <sys/param.h>
#include <CoreFundation/CoreFundation.h>
  }
#endif

/**
 * @brief Apple specifics
 */
#if BU_PLATFORM == BU_PLATFORM_OSX
extern "C" {
#include <unistd.h>
#include <sys/param.h>
#include <CoreFundation/CoreFundation.h>
}
#endif

namespace buEngineSDK {
 
 /**
  * @brief
  */
 template<typename T, size_t N>
 using Array = std::array<T, N>;

 /**
  * @brief Dynamically sized array that stores element contiguously
  */
 template<typename T, typename A = std::allocator<T>>
 using Vector = std::vector<T, A>;

 /**
  * @brief
  */
 template<typename T, typename A = std::allocator<T>>
 using Deque = std::deque<T, A>;

 /**
  * @brief Container that supports constant time insertion and removal, but
  */
 template<typename T, typename A = std::allocator<T>>
 using List = std::list<T, A>;

 /**
  * @brief
  */
 template<typename T, typename A = std::allocator<T>>
 using ForwardList = std::forward_list<T, A>;

 /**
  * @brief
  */
 template<
   typename T, 
   typename Compare = std::less<T>, 
   typename A = std::allocator<T>>
 using Set = std::set<T, Compare, A>;

 /**
  * @brief
  */
 template<
   typename K, 
   typename T, 
   typename C = std::less<K>,
   typename A = std::allocator<std::pair<const K, T>>>
 using Map = std::map<K, T, C, A >;

 /**
  * @brief
  */
 template<
   typename K,
   typename H = std::hash<K>,
   typename P = std::equal_to<K>,
   typename A = std::allocator<K>>
 using UnorderedSet = std::unordered_set<K, H, P, A>;

 /**
  * @brief
  */
 template<
   typename K,
   typename T,
   typename H = std::hash<K>,
   typename P = std::equal_to<K>,
   typename A = std::allocator<std::pair<const K, T>>>
 using UnorderedMap = std::unordered_map<K, T, H, P, A>;

 /**
  * @brief
  */
 template<typename T, typename Container = std::deque<T>>
 using Stack = std::stack<T, Container>;

 /**
  * @brief
  */
 template<typename T, typename Container = std::deque<T>>
 using Queue = std::queue<T, Container>;

 /**
  * @brief
  */
 template <typename T>
 using SPtr = std::shared_ptr<T>;

 /**
  * @brief
  */
 template <typename T>
 using WeakSPtr = std::weak_ptr<T>;
 
}
