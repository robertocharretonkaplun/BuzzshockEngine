/**
  * @file buPlatformDefines.h
  * @version 1.0
  * @date 26/05/2021
  * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
  * @brief Header in charge of define the platform architecture.
  * @
  */
#pragma once

#define BU_PLATFORM_WIN32 1
#define BU_PLATFORM_LINUX 2
#define BU_PLATFORM_OSX   3

#define BU_COMPILER_MSVC 1
#define BU_COMPILER_GNUC 2
#define BU_COMPILER_CLANG 3

#define BU_ARCHITECTURE_X86_32 1
#define BU_ARCHITECTURE_X86_64 2

#define BU_ENDIAN_LITTLE 1
#define BU_ENDIAN_BIG 2

#define BU_ENDIAN BU_ENDIAN_LITTLE

  /**
   * @brief Compiler type and version
   */
#if defined(__clang__)
#   define BU_COMPILER GE_COMPILER_CLANG
#   define BU_COMP_VER __clang_version__
#   define BU_THREADLOCAL __thread
#   define BU_STDCALL __attribute_((stdcall))
#   define BU_CDECL _attribute__((cdecl))
#   define BU_FALLTHROUGH [[clang::fallthrough]];
#elif defined(__GNUC__)
#   define BU_COMPILER GE_COMPILER_GNUC
#   define BU_COMP_VER (((__GNUC__))*100) + (__GNUC_MINOR__*10) + __GNUC_PATCHLEVEL__)
#   define BU_THREADLOCAL __thread
#   define BU_STDCALL __attribute_((stdcall))
#   define BU_CDECL _attribute__((cdecl))
#   define BU_FALLTHROUGH __attribute__((fallthrough))
#elif defined(_MSC_VER)
#   define BU_COMPILER BU_COMPILER_MSVC
#   define BU_COMP_VER _MSC_VER
#   define BU_THREADLOCAL __declspec(thread)
#   define BU_STDCALL _stdcall
#   define BU_CDECL _cdecl
#   define BU_FALLTHROUGH
#   undef __PRETTY_FUNCTION__
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#else
   // No know compiler found, send the error to the output (if any)
#   pragma error "No known compiler. "
#endif

/**
 * @brief See if we can use __forceinline or if we need to use __inline instead
 */
#if BU_COMPILER == BU_COMPILER_MSVC
# if BU_COMP_VER >= 1200
#   define FORCEINLINE __forceinline
#   ifndef RESTRICT
#     define RESTRICT __restrict
#   endif
# endif
#elif defined (__MINGW32__)
# if !defined(FORCEINLINE)
#   define FORCEINLINE __inline
#   ifndef RESTRICT
#     define RESTRICT
#  endif
# #endif
#else
# define FORCEINLINE __inline
# #ifndef RESTRICT
#    define RESTRICT __restrict
# endif
#endif

 /**
  * @brief Find the current platform
  */
#if defined(__WIN32__) || defined(_WIN32)
# define BU_PLATFORM BU_PLATFORM_WIN32
#elif defined(__APPLE_C__)
# define BU_PLATFORM BU_PLATFORM_OSX
#else
# define BU_PLATFORM GE_PLATFORM_LINUX
#endif

  /**
   * @brief Find the architecture type
   */
#if defined (__x86_64__) || defined(_M_X64)
# define BU_ARCH_TYPE BU_ARCHITECTURE_x86_64
#else
# define BU_ARCH_TYPE BU_ARCHITECTURE_x86_32
#endif

   /**
    * @brief Memory Aligment macros
    */
#if BU_COMPILER == BU_COMPILER_MSVC  // If we are compiling on visual studio
# define MS_ALIGN(n) __declspec(align(n))
# ifndef GCC_PACK
#   define GCC_PACK(n)
# endif
#elif ( BU_COMPILER == BU_COMPILER_GNUC )
# define MS_ALIGN(n)
# define GCC_PACK(n)
# define GCC_ALIGN(n) __attribute__ ( (__aligned__(n)) )
#else                               // If we are on the Unix type system
# define MS_ALIGN(n)
# define GCC_PACK(n) __attribute__ ( (packed, aligned(n)) )
# define GCC_ALIGN(n) __attribute__( (aligned(n)) )
#endif

    /**
     * @brief For throw override (deprecated on c++11 but Visual Studio
     * does not have handle noexcept
     */
#if BU_COMPILER == BU_COMPILER_MSVC
# define _NOEXCEPT noexcept
#elif BU_COMPILER == BU_COMPILER_GNUC
# define _NOEXCEPT noexcept
#else
# define _NOEXCEPT
#endif

     /**
      * @brief Library export specifics
      */
#if BU_PLATFORM == BU_PLATFORM_WIN32
# if BU_COMPILER == BU_COMPILER_MSVC
#   if defined ( BU_STATIC_LIB )
#     define BU_CONNECT_EXPORT
#   else
#     if defined ( BU_CONNECT_EXPORTS )
#       define BU_CONNECT_EXPORT __declspec( dllexport )
#     else
#       define BU_CONNECT_EXPORT __declspec( dllimport )
#     endif
#   endif
#else // Any other compiler
#  if defined( BU_STATIC_LIB )
#    define BU_CONNECT_EXPORT
#  else 
#    if defined( BU_CONNECT_EXPORTS )
#       define BU_CONNECT_EXPORT __attribute__ (( dllexport ))
#     else
#       define BU_CONNECT_EXPORT __attribute__ (( dllimport ))
#     endif
#   endif
#endif
# define BU_UTILITY_HIDDEN
#else // Linux/Mac settings
# define BU_UTILITY_EXPORT __attribute__ ((visIbility ("default")))
# define BU_UTILITY_HIDDEN __attribute__ ((visibility ("hidden")))
#endif

      /**
       * @brief DLL export for plug ins
       */
#if BU_PLATFORM == BU_PLATFORM_WIN32
# if BU_COMPILER == BU_COMPILER_MSVC
#   define BU_PLUGIN_EXPORT __declspec(dllexport)
# else
#   define BU_PLUGIN_EXPORT __attribute__ ((dllexport))
# endif
#else // Linux/Mac settings
# define BU_PLUGIN_EXPORT __attribute__ ((visibility ("default")))
#endif

       /**
        * @brief Windows specific Settings
        * Win32 compilers use _DEBUG for specifying debug builds. For MinGW, we set DEBUG
        */
#if BU_PLATFORM == BU_PLATFORM_WIN32
# if defined(_DEBUG) || defined (DEBUG)
#   define BU_DEBUG_MODE 1                  // Specifies that we ae on a DEBUG build
# else
#   define BU_DEBUG_MODE 0                  // We are not on a DEBUG buid
# endif
#endif 

        /**
         * @brief Linux / Apple specific settings
         */
#if BU_PLATFORM == BU_PLATFORM_LINUX || BU_PLATFORM == BU_PLATFORM_OSX
# define stricmp strcasecmp

         // if we are on a DEBUG build
# if defined(_DEBUG) || defined (DEBUG)
#   define BU_DEBUG_MODE 1                  // Specifies that we ae on a DEBUG build
# else
#   define BU_DEBUG_MODE 0                  // We are not on a DEBUG buid
# endif
#endif 

/**
 * @brief Definition of Debug macros
 */
#if BU_DEBUG_MODE
# define BU_DEBUG_MODE_ONLY(x) x
# define BU_ASSERT(x) assert(x)
#else
# define BU_DEBUG_ONLY(x)
# define BU_ASSERT(x)
#endif

 /**
  * @brief Disable some compiler warnings
  */
#if BU_COMPILER == BU_COMPILER_MSVC
# define _CRT_SECURE_NO_WARNINGS        
# pragma warning(disable:4201)          // Ignore structures without name
# pragma warning(disable: 4251)         // Ingore the DLL interface
# pragma warning(disable: 4503)         // Delete warnigns of long names
#endif