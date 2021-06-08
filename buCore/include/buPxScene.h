/**
 * @brief 
 * ref: https://gameworksdocs.nvidia.com/PhysX/4.1/documentation/physxguide/Manual/Startup.html
 */
#pragma once
#include <buPrerequisitesCore.h>
#include <PxScene.h>
#include <PxPhysicsAPI.h>
#include <PxPhysics.h>
#include <PxFoundation.h>
namespace buEngineSDK {
	class buPxScene	{
	public:
		buPxScene() = default;
		~buPxScene() = default;

		void
		init();

		void
		update();

		void 
		render();

		physx::PxPhysics* customCreatePhysics(physx::PxU32 version,
			physx::PxFoundation& foundation,
			const physx::PxTolerancesScale& scale,
			bool trackOutstandingAllocations,
			physx::PxPvd* pvd);
	private:
		/**
		 * @brief 
		 */
		physx::PxScene* m_scene;
		
		physx::PxPhysics* m_physics;
		physx::PxFoundation* m_foundation;
		physx::PxPvd* m_pvd;
		static physx::PxDefaultErrorCallback gDefaultErrorCallback;
		static physx::PxDefaultAllocator gDefaultAllocatorCallback;
	};
}
