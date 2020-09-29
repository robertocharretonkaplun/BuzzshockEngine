/**
 * @file
 * @version
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief
 * @bug
 */
#pragma once
#include <buPrerequisitesDX.h>
#include <buResourceManager.h>
#include <buDXTexture2D.h>
#include <buResource.h>
#include <buCoreModelLoader.h>
#include <buCoreModel.h>
#include <buCoreMesh.h>
#include <buDXBuffer.h>
#include <buMatrix4x4.h>

namespace buEngineSDK {
  
  class buDXResourceManager : public buResourceManager
  {
  public:
    /**
     * @brief Default Constructor
     */
    buDXResourceManager();

    /**
     * @brief Default Destructor
     */
    ~buDXResourceManager();

    /**
     * @brief
     */
    void
    loadMesh(String _filepath) override;
    buCoreModel*
    getModel() override;

  public:
    
    Vector<String> textNames;

    buCoreModel m_model;
    
  };

  /**
   * @brief Plugging exportation data method.
   * @return Instance of DX.
   */
  extern "C" BU_PLUGIN_EXPORT buDXResourceManager *
    createResourceManager() {
    auto pRC = new buDXResourceManager();
    return pRC;
  }
}
