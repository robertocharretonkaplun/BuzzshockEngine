#include "SaveSystem.h"

namespace buEngineSDK {
  void 
  SaveSystem::cleanFileData() {
    std::ofstream m_data("Data/SavedData/EngineLoadedData.bu", std::ios::app);
    m_data.clear();
    m_data.close();
  }
  
  void
  SaveSystem::saveSerialization(Vector<BYTE> mem) {
    //String tmpFileData = "[ " + mem + " ];";
    std::ofstream m_data("Data/SavedData/Serialization.bu", std::ios::app | std::ios::binary);
    m_data.write(mem.data(), mem.size());
    m_data.close();
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
    Buffer.reserve(4096);
    std::ifstream readData("Data/SavedData/Serialization.bu", std::ios::in | std::ios::binary);
    
    readData.read(Buffer.data(), 4096);
    

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
}