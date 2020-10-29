#pragma once
#include <buPrerequisitesCore.h>
#include <buCoreModel.h>
#include "buCommons.h"
#include "buTransform.h"
#include <buVector3F.h>
namespace buEngineSDK {
	class BU_CORE_EXPORT buGameObject {
	public:
		buGameObject() = default;
		~buGameObject() = default;

		void
		update(buVector3F _pos, buVector3F _rot, buVector3F _scal, float _angle);
		
		void
		render();

	public:
		String m_name;
		uint32 m_id = 0;
		GameObjectType::E m_type;
		buCoreModel m_model;
		buTransform m_transform;
		bool m_isActive = true;
		bool m_isActiveTransform = true;
		bool m_isSelected = false;
	};
}