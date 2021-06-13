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
		~buGameObject();

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

		void
		setSelectorState(GameObjectSelectType::E _selectType);

		void
		setRenderState(GameObjectRenderState::E _renderState);
		void drawUI();


	private:
		void
		vec3Control(String label, float* values, float resetValues = 0.0f, float columnWidth = 100.0f);

	public:
		// Model Object
		buCoreModel m_model;
		Vector<SPtr<buCoreTexture2D>> m_textures;
		// Components
		buTransform m_transform;
		// Local Variables
		float* pos;
		float* rot;
		float* sca;
		float* m_angle;
		// Buffers and Structures
		CBChangesEveryFrame cb;
		SPtr<buCoreBuffer> changeEveryFrame;
		// Attributes
		String m_name;
		uint32 m_id = 0;
		bool m_isActive = true;
		bool m_isActiveTransform = true;
		bool m_isSelected = false;
		bool m_isUsed = false;
		bool m_isActorHiddenInGame = false;
		bool m_serialize = false;
		GameObjectSelectType::E m_select = GameObjectSelectType::E::UNSELECTED;
		GameObjectType::E m_type = GameObjectType::E::DEFAULT_TYPE;
		// Render Attributes
		GameObjectRenderState::E m_renderState = GameObjectRenderState::E::RENDER_ON;
		bool m_canRender = false;
	};
}