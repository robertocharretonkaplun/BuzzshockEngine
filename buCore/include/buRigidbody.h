/**
 * @brief 
 * Ref: https://alanjfs.github.io/PhysX4Guide/Manual/RigidBodyOverview.html 
 */
#pragma once
#include <buPrerequisitesCore.h>
#include <PxPhysicsAPI.h>
#include <PxScene.h>
#include <PxRigidActor.h>
namespace buEngineSDK {
	class BU_CORE_EXPORT buRigidbody
	{
	public:
		buRigidbody() = default;
		~buRigidbody() = default;

		void
		init();
	private:
		/**
		 * @brief This member is in charge of manage shapes and transforms.
		 */
		physx::PxRigidActor* m_actor;


	};
}

