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

		void
		drawUI();  

		void
		vec3Control(String label, float* values, float resetValues = 0.0f, float columnWidth = 100.0f);

	private:
		String m_name;
		LightBuffer LB;
		SPtr<buCoreBuffer> m_lightBuffer;
		// Include game object
		float* m_pos;
	};
};