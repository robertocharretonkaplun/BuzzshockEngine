#include "buPxScene.h"

namespace buEngineSDK {
  void
  buPxScene::init() {
    //m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback,
    //  gDefaultErrorCallback);
    //if (!m_foundation) {
    //  //fatalError("PxCreateFoundation failed!");
    //}
    //
    //bool recordMemoryAllocations = true;
    //
    //m_pvd = physx::PxCreatePvd(*m_foundation);
    //physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(00, 5425, 10);
    //m_pvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
    //
    //m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation,
    //  physx::PxTolerancesScale(), recordMemoryAllocations, m_pvd);
    //if (!m_physics) {
    //  // fatalError("PxCreatePhysics failed!");
    //}


  }

  physx::PxPhysics* 
  buPxScene::customCreatePhysics(physx::PxU32 version, 
                                 physx::PxFoundation& foundation, 
                                 const physx::PxTolerancesScale& scale, 
                                 bool trackOutstandingAllocations, 
                                 physx::PxPvd* pvd) {
    physx::PxPhysics* physics = PxCreateBasePhysics(version, foundation, scale,
      trackOutstandingAllocations, pvd);

    if (!physics)
      return NULL;

    PxRegisterArticulations(*physics);
    PxRegisterHeightFields(*physics);

    return physics;
  }
}