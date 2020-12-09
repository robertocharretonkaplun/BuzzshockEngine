#include "buGameApp_UnitTest.h"
#include <buMath.h>

namespace buEngineSDK
{
  buGameApp_UnitTest::buGameApp_UnitTest() {
  }

  buGameApp_UnitTest::~buGameApp_UnitTest() {
  }

  void 
  buGameApp_UnitTest::onCreate() {
  }

  void 
  buGameApp_UnitTest::onDestroy() {
    m_graphicsAPI->cleanUp();
    //m_sysAudioAPI.de;
    // Shutdown module
    buCoreGraphicsAPI::shutDown();
    sysAudioAPI::shutDown();
    //delete graphicAPI;
    m_directXPlug.destroy();
    m_audioPlug.destroy();
    
  }

  void 
  buGameApp_UnitTest::onUpdate(float _deltaTime) {
  }

  void 
  buGameApp_UnitTest::onRender() {
    //if (-1 < currModel->m_currAnimation) {
    //  for (uint32 i = 0; i < currModel->m_bonesTransforms.size(); ++i) {
    //    cbBonestransform.boneTransform[i] = currModel->m_bonesTransforms[i];
    //  }
    //  m_graphicsAPI->updateSubresource(BonesTranform,
    //    0,
    //    nullptr,
    //    &cbBonestransform,
    //    0,
    //    0);
    //}
    
  }
}
