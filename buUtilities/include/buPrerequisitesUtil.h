/**
* @file buPrerequisitesUtil.h
* @version 1.0
* @date 28/05/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
* @brief Utility include with the mos basic defines needed for the compilation
* This is the file that must be included for use on external objects
* @bugs
*/
#pragma once

/**
 * @brief Most basic includes (requires for everything else)
 */
#include <cassert>

/**
 * @brief Platform specific stuff
 */
#include "buPlatformDefines.h"

/**
 * @brief Include of short-hand names for various built-in types
 */
#include "buPlatformTypes.h"      // Platform types
#include "buStdHeaders.h"         // Commonly used standar headers

#include "buString.h"