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
#include <buGameObject.h>
#include <buCommons.h>
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
    
    buGameObject 
    getMesh(String _filepath) override;

    buCoreModel*
    getModel() override;

    Vector<buGameObject> 
    getGameObjects() override;

    Vector<SPtr<buCoreTexture2D>>*
    getTextures() override;

    buCoreModel*
    getModelStruct() override;

    buGameObject 
    getGO(String _filepath) override;
  public:
    
    Vector<String> textNames;
    Vector<SPtr<buCoreTexture2D>> m_textures;
    buCoreModel m_model;
    uint32 m_goCounter = 0;
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
