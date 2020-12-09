#pragma once
#include <buPrerequisitesCore.h>
#include <buCoreModel.h>
#include "buCommons.h"
#include "buTransform.h"
#include <buVector3F.h>
#include <buCoreGraphicsAPI.h>
namespace buEngineSDK {
	class BU_CORE_EXPORT buGameObject {
	public:
		buGameObject() = default;
		~buGameObject() = default;

		void 
		init();

		void
		update(buVector3F _pos, buVector3F _rot, buVector3F _scal, float _angle);
		
		void
		render(TopologyType::E _typology);

		void getTextures(SPtr<buCoreTexture2D> tmpTex) {
			m_model.m_textures.clear();
			m_model.m_textures.push_back(tmpTex);
		}
		void addTexture(SPtr<buCoreTexture2D> tmpTex) {
			m_model.m_textures.push_back(tmpTex);
		}

	public:
		String m_name;
		uint32 m_id = 0;
		GameObjectType::E m_type = GameObjectType::E::DEFAULT_TYPE;
		buCoreModel m_model;
		Vector<SPtr<buCoreTexture2D>> m_textures;
		buTransform m_transform;
		buVector3F m_pos = buVector3F::Zero;
		buVector3F m_rot = buVector3F::Zero;
		buVector3F m_sca = buVector3F::Zero;
		float m_angle = 0.0f;
		buTransform m_lastTransform;
		CBChangesEveryFrame cb;
		SPtr<buCoreBuffer> changeEveryFrame;
		bool m_isActive = true;
		bool m_isActiveTransform = true;
		bool m_isSelected = false;
		bool m_isUsed = false;
	};
}