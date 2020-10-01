#pragma once
#include <buPrerequisitesCore.h>
#include <buTransform.h>

namespace buEngineSDK {
	class buGameObject
	{
	public:
		buGameObject() = default;
		~buGameObject() = default;

	public:
		uint32 m_id = 0;
		String m_name = "";
		buTransform m_transform;
	};
} 