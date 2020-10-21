#pragma once
#include <buPrerequisitesCore.h>
#include <buCoreModel.h>
#include "buCommons.h"
namespace buEngineSDK {
	class buGameObject {
	public:
		buGameObject() = default;
		~buGameObject() = default;

	private:
		String m_name;
		uint32 m_id;
		GameObjectType::E m_type;
		buCoreModel m_model;
		// Add transforma class
	};
}