#pragma once
#include <buPrerequisitesCore.h>
#include <buVector3F.h>
#include <buMatrix4x4.h>

namespace buEngineSDK {
	class BU_CORE_EXPORT buTransform
	{
	public:
		buTransform();
		~buTransform() = default;

		void
		update(buVector3F _pos, buVector3F _rot, buVector3F _scal, float _angle);

	public:
		String m_name = "Transform";
		buMatrix4x4 m_world;
		buVector3F m_position;
		buVector3F m_rotation;
		buVector3F m_scale;
		float m_angle;
	};
}