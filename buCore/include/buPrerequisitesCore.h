/**
 * @file 
 * @version 
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once
#include <buPrerequisitesUtil.h>

/**
 * @brief Library export specifics
 */
#if BU_PLATFORM == BU_PLATFORM_WIN32
# if BU_COMPILER == BU_COMPILER_MSVC
#   if defined ( BU_STATIC_LIB )
#     define BU_CORE_EXPORT
#   else
#     if defined ( BU_CORE_EXPORTS )
#       define BU_CORE_EXPORT __declspec( dllexport )
#     else
#       define BU_CORE_EXPORT __declspec( dllimport )
#     endif
#   endif
#else // Any other compiler
#  if defined( BU_STATIC_LIB )
#    define BU_CORE_EXPORT
#  else 
#    if defined( BU_CORE_EXPORTS )
#       define BU_CORE_EXPORT __attribute__ (( dllexport ))
#     else
#       define BU_CORE_EXPORT __attribute__ (( dllimport ))
#     endif
#   endif
#endif
# define BU_CORE_HIDDEN
#else // Linux / Mac settings
# define BU_CORE_EXPORT __attribute__ ((visIbility ("default")))
# define BU_CORE_HIDDEN __attribute__ ((visibility ("hidden")))
#endif

//#if !defined(SAFE_RELEASE)
//#define SAFE_RELEASE(x) { if(x != nullptr) x->Release(); x = nullptr};
//#endif

#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

// * To check monster
#define OutputLOG(_ClassName, _FunctionName, _OutputMessage)	   	\
OutputDebugStringA(_ClassName);											              \
OutputDebugStringA(" : In Function : ");								          \
OutputDebugStringA(_FunctionName);										            \
OutputDebugStringA(" : ");												                \
OutputDebugStringA(_OutputMessage);										            \
OutputDebugStringA("\n");