#include "SaveSystem.h"

namespace buEngineSDK {
  void 
  SaveSystem::cleanFileData() {
    std::ofstream m_data("Data/SavedData/EngineLoadedData.bu", std::ios::app);
    m_data.clear();
    m_data.close();
  }
  
  void
  SaveSystem::saveSerialization(Vector<BYTE>& mem) {
    //String tmpFileData = "[ " + mem + " ];";
    std::ofstream m_data("Data/SavedData/Serialization.bu", std::ios::out | std::ios::binary);
    m_data.write(mem.data(), mem.size());
    m_data.close();
  }
 
  uint32
  SaveSystem::serializeVec3(buVector3F& vec, Vector<BYTE>& outBuffer) {
    auto space = outBuffer.capacity() - outBuffer.size();
    if (space < sizeof(buVector3F)) {
      outBuffer.reserve(outBuffer.size() + vec.memSize());
    }
    memcpy(outBuffer.data(), &vec, sizeof(buVector3F));
    //RTTIEmptyType<buVector3F> obj;
    //obj.toMemory(vec, &outBuffer[outBuffer.size()-1]);

    return vec.memSize();
  }

  void SaveSystem::saveSerialization(BYTE mem)
  {
    std::ofstream m_data("Data/SavedData/Serialization.bu", std::ios::out | std::ios::binary);
    m_data.write(&mem, sizeof(BYTE));
    m_data.close();
  }

  Vector<BYTE> SaveSystem::getSerialization()
  {
    Vector<BYTE> Buffer;
    std::ifstream readData("Data/SavedData/Serialization.bu", std::ios::in | std::ios::binary);
    
    //readData.seekg(0, readData.end);
    //uint32 length = readData.tellg();
    //readData.seekg(0, readData.beg);
    //
    Buffer.resize(sizeof(buVector3F));
    readData.read(Buffer.data(), 0);//sizeof(buVector3F));
    

    readData.close();
    return Buffer;
  }

  void
  SaveSystem::setString(String _key, String _val) {
    String tmpFileData = "[ " + _key + " , " + _val + " ];";
    std::ofstream m_data("Data/SavedData/EngineLoadedData.bu", std::ios::app );
    m_data << tmpFileData;
    m_data.close();
  }

  void 
  SaveSystem::setInt(String _key, int _val) {
    String tmpFileData = "[ " + _key + " , " + std::to_string(_val) + " ];";
    std::ofstream m_data("Data/SavedData/EngineLoadedData.bu", std::ios::app);
    m_data << tmpFileData;
    m_data.close();
  }
  void 
  SaveSystem::setFloat(String _key, float _val) {
    String tmpFileData = "[ " + _key + " , " + std::to_string(_val) + " ];";
    std::ofstream m_data("Data/SavedData/EngineLoadedData.bu", std::ios::app);
    m_data << tmpFileData;
    m_data.close();
  }

  void 
  SaveSystem::setBool(String _key, bool _val) {
    String boolVal;
    if (_val) {
      boolVal = "true";
    }
    else {
      boolVal = "false";
    }
    String tmpFileData = "[ " + _key + " , " + boolVal + " ];";
    std::ofstream m_data("Data/SavedData/EngineLoadedData.bu", std::ios::app);
    m_data << tmpFileData;
    m_data.close();
  }

  void 
  SaveSystem::setIntVec4(String _key, int _val[4]) {
    String tmpFileData = "[ " + _key + " , " + " ( " +
      std::to_string(_val[0]) + " , " + std::to_string(_val[1]) + " , " + 
      std::to_string(_val[2]) + " , " + std::to_string(_val[3]) + ", ) " + " ];";
    std::ofstream m_data("Data/SavedData/EngineLoadedData.bu", std::ios::app);
    m_data << tmpFileData;
    m_data.close();
  }

  void 
  SaveSystem::setIntVec3(String _key, int _val[3]) {
    String tmpFileData = "[ " + _key + " , " + " ( " +
      std::to_string(_val[0]) + " , " + std::to_string(_val[1]) + " , " +
      std::to_string(_val[2]) + ", ) " + " ];";

    std::ofstream m_data("Data/SavedData/EngineLoadedData.bu", std::ios::app);
    m_data << tmpFileData;
    m_data.close();
  }

  void 
  SaveSystem::setFloatVec4(String _key, float _val[4]) {
    String tmpFileData = "[ " + _key + " , " + " ( " +
      std::to_string(_val[0]) + " , " + std::to_string(_val[1]) + " , " + 
      std::to_string(_val[2]) + " , " + std::to_string(_val[3]) + ", ) " + " ];";
    std::ofstream m_data("Data/SavedData/EngineLoadedData.bu", std::ios::app);
    m_data << tmpFileData;
    m_data.close();
  }

  void 
  SaveSystem::setFloatVec3(String _key, float _val[3]) {
    String tmpFileData = "[ " + _key + " , " + " ( " +
      std::to_string(_val[0]) + " , " + std::to_string(_val[1]) + " , " +
      std::to_string(_val[2]) + ", ) " + " ];";

    std::ofstream m_data("Data/SavedData/EngineLoadedData.bu", std::ios::app);
    m_data << tmpFileData;
    m_data.close();
  }

  String 
  SaveSystem::getString(String _key) {
    std::ifstream readData("Data/SavedData/EngineLoadedData.bu", std::ios::in );
    String tmpFileData;
    while (!readData.eof()) {
      std::getline(readData, tmpFileData);
    }
    String currKey;
    String currVal;
    for (uint32 i = 0; i < tmpFileData.size(); i++) {
      if (currKey == _key) {
        if (tmpFileData[i] == ';') {
          break;
        }
        if (tmpFileData[i] != ']' && tmpFileData[i] != ' ') {
          currVal += tmpFileData[i];
        }
      }
      if (currKey != _key) {
        if (tmpFileData[i] == ';') {
          currKey.clear();
          i+=1;
        }
        if (tmpFileData[i] != '[' && tmpFileData[i] != ']' && tmpFileData[i] != ' ') {
          currKey += tmpFileData[i];
          if (currKey==_key) {
            i += 2;
          }
        }
      }
    }
    readData.close();
    return currVal;
  }

  int
  SaveSystem::getInt(String _key) {

    return 0;
  }

  float
  SaveSystem::getFloat(String _key) {

    return 0.0f;
  }

  bool 
  SaveSystem::getBool(String _key) {

    return false;
  }

  buVector4I
  SaveSystem::getIntVec4(String _key) {

    return buVector4I();
  }

  buVector3I 
  SaveSystem::getIntVec3(String _key) {
    
    return buVector3I();
  }

  buVector4F 
  SaveSystem::getFloatVec4(String _key) {

    return buVector4F();
  }

  buVector3F 
  SaveSystem::getFloatVec3(String _key) {
    std::ifstream readData("Data/SavedData/EngineLoadedData.bu", std::ios::in);
    String tmpFileData;
    while (!readData.eof()) {
      std::getline(readData, tmpFileData);
    }
    String currKey;
    String tmpVal;
    Vector<String> currVal;
    for (uint32 i = 0; i < tmpFileData.size(); i++) {
      // Store the value
      if (currKey == _key) {
        if (tmpFileData[i] == ';') {
          break;
        }
        if (tmpFileData[i] != ']' && tmpFileData[i] != ' ' && tmpFileData[i] != '(') {
          if (tmpFileData[i] == ',' && tmpFileData[i] != ')') {
            currVal.push_back(tmpVal);
            tmpVal.clear();
            i++;
          }
          tmpVal += tmpFileData[i];
        }
      }
      // Get the Key 
      if (currKey != _key) {
        if (tmpFileData[i] == ';') {
          currKey.clear();
          i += 1;
        }
        if (tmpFileData[i] != '[' && tmpFileData[i] != ']' && tmpFileData[i] != ' ') {
          currKey += tmpFileData[i];
          if (currKey == _key) {
            i += 2;
          }
        }
      }
    }
    readData.close();
    return buVector3F( std::stof(currVal[0]), std::stof(currVal[1]), std::stof(currVal[2]));
  }

  void 
  SaveSystem::saveGO(buGameObject *_go) {
    String tmpPath = "Data/SavedData/";
    String extensionType = ".bu";
    String fullPath = tmpPath + "GO" + extensionType;
    std::ofstream projectFile(fullPath.c_str(), std::ios::binary);
    if (projectFile)
    {
      ModelData modelinfo;
      int numMeshs = _go->m_model.m_meshes.size();// tempModel->meshes.size();
      modelinfo.numMeshes = numMeshs;
      modelinfo.numAnimations = 0;
      modelinfo.animationNodes = false;

      projectFile.write((char*)&modelinfo, sizeof(ModelData));

      for (unsigned int m = 0; m < numMeshs; ++m) {
        auto cMesh = _go->m_model.m_meshes[m];// tempModel->meshes[m];
        MeshData meshInfo;
        meshInfo.nameSize = _go->m_name.size();// cMesh.name.size();

        meshInfo.numVertex = cMesh.m_numVertex;
        meshInfo.numIndex = cMesh.m_numIndices;

        projectFile.write((char*)&meshInfo, sizeof(MeshData));
        projectFile.write((char*)_go->m_name.data(),
          sizeof(char) * meshInfo.nameSize);

        //write vertexData
        projectFile.write((char*)_go->m_model.m_vertices.data(),
          sizeof(Vertex) * meshInfo.numVertex);
        //write index
        projectFile.write((char*)_go->m_model.m_indices.data(), sizeof(unsigned int) * meshInfo.numIndex);
      }
      projectFile.close();
    }
  }
  
  buGameObject
  SaveSystem::loadGO(String _filename) {
    buCoreModel tmpModel;


    return buGameObject();
  }
  
  std::pair<bool, uint32_t> SaveSystem::DirectoryTreeViewRecursive(const std::filesystem::path& path, uint32_t* count, int* selection_mask) {
    ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_SpanFullWidth;

    bool any_node_clicked = false;
    uint32_t node_clicked = 0;
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
      ImGuiTreeNodeFlags node_flags = base_flags;
      const bool is_selected = (*selection_mask & BIT(*count)) != 0;
      if (is_selected)
        node_flags |= ImGuiTreeNodeFlags_Selected;

      std::string name = entry.path().string();

      auto lastSlash = name.find_last_of("/\\");
      lastSlash = lastSlash == String::npos ? 0 : lastSlash + 1;
      name = name.substr(lastSlash, name.size() - lastSlash);
      bool entryIsFile = !std::filesystem::is_directory(entry.path());
      if (entryIsFile)
        node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

      bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)(*count), node_flags, name.c_str());

      if (ImGui::IsItemClicked())
      {
        m_pathFile = name;
        node_clicked = *count;
        any_node_clicked = true;
      }

      (*count)--;

      if (!entryIsFile)
      {
        if (node_open)
        {

          auto clickState = DirectoryTreeViewRecursive(entry.path(), count, selection_mask);

          if (!any_node_clicked)
          {
            any_node_clicked = clickState.first;
            node_clicked = clickState.second;
          }

          ImGui::TreePop();
        }
        else
        {
          for (const auto& e : std::filesystem::recursive_directory_iterator(entry.path()))
            (*count)--;
        }
      }
    }

    return { any_node_clicked, node_clicked };
  }
  void SaveSystem::OnImGui(std::string directoryPath)
  {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });


    if (ImGui::CollapsingHeader("Assets"))
    {
      uint32_t count = 0;
        
      for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath))
        count++;

      static int selection_mask = 0;

      auto clickState = DirectoryTreeViewRecursive(directoryPath, &count, &selection_mask);

      if (clickState.first)
      {
        // Update selection state
        // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
        if (ImGui::GetIO().KeyCtrl)
          selection_mask ^= BIT(clickState.second);          // CTRL+click to toggle
        else //if (!(selection_mask & (1 << clickState.second))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
          selection_mask = BIT(clickState.second);           // Click to single-select
      }
    }
    

    ImGui::PopStyleVar();
  }
}