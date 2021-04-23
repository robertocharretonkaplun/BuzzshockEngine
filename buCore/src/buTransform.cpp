#include <buTransform.h>

namespace buEngineSDK {
  buTransform::buTransform() {
    m_world = buMatrix4x4::IDENTITY;
  }
  void 
  buTransform::update(buVector3F _pos, buVector3F _rot, 
                      buVector3F _scal, float _angle) {
    m_position = _pos;
    m_rotation = _rot;
    m_scale = _scal;
    m_angle = _angle;
    // Set Mesh transform
    m_world.scaleMatrix(_scal);
    m_world.rotateMatrix(_rot, _angle); 
    m_world.translateMatrix(_pos);
  }
 
}