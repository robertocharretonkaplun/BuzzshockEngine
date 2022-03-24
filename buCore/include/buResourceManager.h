/**
 * @file buResourceManager.h
 * @version 1.0
 * @date 03/08/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief Class in charge of providing virtual methods for the DX Resource Manager.
 * TODO: Load textures, meshes
 */
#pragma once
#include <buPrerequisitesCore.h>
#include <buModule.h>
#include <buCoreTexture2D.h>
#include <buCoreModel.h>
#include <buGameObject.h>
namespace buEngineSDK {

  class BU_CORE_EXPORT buResourceManager : public buModule<buResourceManager>
  {
  public:
    /**
     * @brief Default Constructor
     */
    buResourceManager() = default;
    /**
     * @brief Default Destructor
     */
    ~buResourceManager() = default;

    /**
   * @brief Instances of this object.
   */
    FORCEINLINE void
      setObject(buResourceManager* _api) {
      buResourceManager::_instance() = _api;
    }

    /**
     * @brief
     */
    virtual void
    loadMesh(String _filepath) {};

    virtual buGameObject
    getMesh(String _filepath) {return buGameObject();};

    virtual buCoreModel*
    getModel() {return nullptr;};
    
    virtual Vector<SPtr<buCoreTexture2D>>*
    getTextures() {return nullptr;}

    virtual Vector<buGameObject>
    getGameObjects() { return Vector<buGameObject>(); };

    virtual buCoreModel*
    getModelStruct() { return nullptr; };

    virtual buGameObject 
    getGO(String _filepath) { return buGameObject();};
  };

  /**
  * @brief Export method for the class instance.
  */
  BU_CORE_EXPORT buResourceManager&
    g_resourceManager();
  using fnresourceManagerProt = buResourceManager * (*)();
}

