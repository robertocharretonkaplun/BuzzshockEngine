#pragma once
#include <buPrerequisitesUtil.h>

/**
 * @brief Library export specifics
 */
#if BU_PLATFORM == BU_PLATFORM_WIN32
# if BU_COMPILER == BU_COMPILER_MSVC
#   if defined ( BU_STATIC_LIB )
#     define BU_AUDIO_EXPORT
#   else
#     if defined ( BU_AUDIO_EXPORTS )
#       define BU_AUDIO_EXPORT __declspec( dllexport )
#     else
#       define BU_AUDIO_EXPORT __declspec( dllimport )
#     endif
#   endif
#else // Any other compiler
#  if defined( BU_STATIC_LIB )
#    define BU_AUDIO_EXPORT
#  else 
#    if defined( BU_AUDIO_EXPORTS )
#       define BU_AUDIO_EXPORT __attribute__ (( dllexport ))
#     else
#       define BU_AUDIO_EXPORT __attribute__ (( dllimport ))
#     endif
#   endif
#endif
# define BU_AUDIO_HIDDEN
#else // Linux / Mac settings
# define BU_AUDIO_EXPORT __attribute__ ((visIbility ("default")))
# define BU_AUDIO_HIDDEN __attribute__ ((visibility ("hidden")))
#endif

#define OpenAL_ErrorCheck(message)\
{\
	ALenum error = alGetError();\
	if(error != AL_NO_ERROR)\
	{\
		std::cerr << "OpenAL Error: " << error << " with call for " << #message << std::endl;\
	}\
}\

#define alec(FUNCTION_CALL)\
FUNCTION_CALL;\
OpenAL_ErrorCheck(FUNCTION_CALL)