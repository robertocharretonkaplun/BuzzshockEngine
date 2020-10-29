#include "buGameObject.h"

namespace buEngineSDK {
  void 
  buGameObject::update(buVector3F _pos, buVector3F _rot,
                       buVector3F _scal, float _angle) {
    m_transform.update(_pos, _rot, _scal, _angle);
  }

  void
  buGameObject::render() {

  }
}