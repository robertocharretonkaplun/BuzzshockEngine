#pragma once
#include "buPrerequisitesUtil.h"
#include "buPlane.h"

namespace buPlaneFace {
  enum E {
    FRONT_PLANE,
    BACK_PLANE,
    LEFT_PLANE,
    RIGHT_PLANE,
    UP_PLANE,
    DOWN_PLANE
  };
}

namespace buEngineSDK {

  class BU_UTILITY_EXPORT buFrustrum
  {
  public:
    /**
     * @brief Default constructor
     */
    buFrustrum() = default;

    /**
     * @brief Destructor
     */
    ~buFrustrum();

  public:
    /**
     * @brief Member in charge of allocating the 6 planes that creates the frustrum
     */
    Vector<buPlane> m_frustrum;
  };
}