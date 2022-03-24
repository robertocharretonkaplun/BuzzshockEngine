#pragma once
#include <buPrerequisitesCore.h>
#include <buVector3F.h>
#include <buMatrix4x4.h>
#include <buSerializer.h>
#include <buCommons.h>

namespace buEngineSDK {
	class BU_CORE_EXPORT buTransform
	{
	public:
		buTransform();
		~buTransform() = default;

		void
		update(buVector3F _pos, buVector3F _rot, buVector3F _scal, float _angle);

		void 
		ui(float* _pos, float* _rot, float* _scal, float* _angle);
	private:
		void
			vec3Control(String label, float* values, float resetValues = 0.0f, float columnWidth = 100.0f);
	public:
		String m_name = "Transform";
		buMatrix4x4 m_world;
		buVector3F m_position;
		buVector3F m_rotation;
		buVector3F m_scale;
		buVector3F m_sca = buVector3F::Zero;\
		float m_angle;
	};

}