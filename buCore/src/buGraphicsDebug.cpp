#include "buGraphicsDebug.h"

namespace buEngineSDK {
  buGraphicsDebug::buGraphicsDebug()
  {
  }
  void buGraphicsDebug::init()
  {
  }
  void buGraphicsDebug::update()
  {
  }
  void buGraphicsDebug::render()
  {
  }
  void buGraphicsDebug::addLine(buVector3F& _posA, buVector3F& _posB,
                                buVector4F _color, float _duration)
  {
    DEBUG_VERTEX currDebugVertexA;
    currDebugVertexA.m_position = _posA;
    currDebugVertexA.m_color = _color;
    m_frameInfo.push_back(currDebugVertexA);
    DEBUG_VERTEX currDebugVertexB;
    currDebugVertexB.m_position = _posB;
    currDebugVertexB.m_color = _color;
    m_frameInfo.push_back(currDebugVertexB);
  }
}