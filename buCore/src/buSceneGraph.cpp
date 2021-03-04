#include "buSceneGraph.h"

namespace buEngineSDK {
  
  void
  buSceneGraph::update(buVector3F _pos, buVector3F _rot,
                       buVector3F _scal, float _angle) {
    for (auto go : m_gameObjects) {
      // If the go is in use
      if (go.m_isUsed && go.m_isSelected) {
        go.update(_pos, _rot, _scal, _angle);
      }
    }
  }
  
  void
  buSceneGraph::render(TopologyType::E _typology) {
    for (auto go : m_gameObjects) {
      // If the go is in use
      if (go.m_isUsed) {
      }
        go.render(_typology);
    }
  }

  void
  buSceneGraph::renderBillBoard(TopologyType::E _typology) {

  }
  
  void
  buSceneGraph::destroy() {
    m_gameObjects.clear();
    m_inUseGameObjects.clear();
    m_notInUseGameObjects.clear();
  }

  void 
  buSceneGraph::poolOfObjects() {
    // Organize the list of game objects
    for (auto go : m_gameObjects) {
      bool isInUsedList = false;
      // Check if the object is already in the vector
      for (auto usedGO : m_inUseGameObjects) {
        if (go.m_id == usedGO.m_id) {
          // The object is already on the vector
          isInUsedList = true;
          break;
        }
      }
      if (!isInUsedList) {
        // If the object is used add it to the vector
        if (go.m_isUsed) {
          m_inUseGameObjects.push_back(go);
        }
      }
      
      bool isInNotUsedList = false;
      // Check if the object is already in the vector
      for (auto notUsedGO : m_notInUseGameObjects) {
        if (go.m_id == notUsedGO.m_id) {
          // The object is already on the vector
          isInNotUsedList = true;
          break;
        }
      }

      // Else, add it to the not used vector
      if (!isInNotUsedList) {
        if (!go.m_isUsed) { 
          m_notInUseGameObjects.push_back(go);
        }
      }
    }
  }

  void 
  buSceneGraph::addGameObject(String _filepath) {
    // Load the gameObject from the resource manager
    buGameObject GO;
    auto &graphMan = g_graphicsAPI();
    auto &loader = g_resourceManager();
    GO = loader.getMesh(_filepath);
    GO.m_isUsed = true;
    GO.m_id = StringUtilities::hash(GO.m_name);
    // Add the game object to the game objects vector
    m_gameObjects.push_back(GO);
    poolOfObjects();
  }

  void
  buSceneGraph::setSelectedGO(int32 _index) {
    // Diselect all the game objects
    for (auto go : m_gameObjects) {
      go.m_isSelected = false;
    }
    m_selectedGO = _index;
    // Set the new game object as the selected one
    m_gameObjects[m_selectedGO].m_isSelected = true;
  }

  buGameObject 
  buSceneGraph::getSelectedGO() {
    // Check if the selected go was selected
    if (m_gameObjects[m_selectedGO].m_isSelected) {
      return m_gameObjects[m_selectedGO];
    }
    
    return buGameObject();
  }

  void 
  buSceneGraph::addTexToSelectedObj(SPtr<buCoreTexture2D> tmpTex) {
    if (m_gameObjects[m_selectedGO].m_isSelected) {
      m_gameObjects[m_selectedGO].m_textures.push_back(tmpTex);
    }
  }

  void 
  buSceneGraph::drawUI() {
    ImGui::Begin("Herarchy");
    if (ImGui::TreeNode(m_sceneName.c_str()))
    {
      for (auto go : m_gameObjects) {
        if (ImGui::TreeNode(go.m_name.c_str())) {
          ImGui::TreePop();
        }
      }

      //if (ImGui::TreeNode("Base"))
      //{
      //  ImGui::Indent();
      //  ImGui::Text("Num Slots");
      //  ImGui::Text("Count");
      //  ImGui::Unindent();
      //  ImGui::TreePop();
      //}
      //if (ImGui::TreeNode("Slots"))
      //{
      //  ImGui::TreePop();
      //}
      ImGui::TreePop();
    }
    ImGui::Indent();
    //ImGui::Text("Previous Modifications");
    //ImGui::Text("Debug Ticks");
    ImGui::Unindent();

    ImGui::End();
  }

}
