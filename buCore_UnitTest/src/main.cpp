/**
 * @file main.cpp
 * @version 1.0
 * @date 27/06/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief File in charge of Checking the unit testing of the Core.
 */
#include <buPrerequisitesCore.h>
#include <gtest/gtest.h>
#include "buGameApp_UnitTest.h"

using namespace buEngineSDK;

buGameApp_UnitTest App;

int32 main()
{
  return App.run();
}
