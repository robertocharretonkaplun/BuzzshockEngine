#pragma once
#include <buPrerequisitesCore.h>
#include <buGameObject.h>
#include <buCoreBuffer.h>
#include <buCommons.h>

namespace buEngineSDK {
	class BU_CORE_EXPORT buLight {
	public:
		buLight() = default;
		~buLight() = default;

		void 
		init();

		void 
		update(LightBuffer _lb);

		void
		render();

	private:
		String m_name;
		LightBuffer LB;
		SPtr<buCoreBuffer> m_lightBuffer;
	};
};