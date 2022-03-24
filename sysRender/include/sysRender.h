#pragma once
#include <PrerequisitesRender.h>
#include <buModule.h>
#include "buUI.h"
namespace buEngineSDK {
	class BU_RENDER_EXPORT sysRender : public buModule<sysRender>
	{
	public:
		/**
		 * @brief Default constructor
		 */
		sysRender() = default;
		/**
		 * @brief Default Destructor
		 */
		~sysRender() = default;
		
		/**
		 * @brief Instances of this object.
		 */
		FORCEINLINE void
			setObject(sysRender* _api) {
			sysRender::_instance() = _api;
		}

		virtual void
		init(void* _window, float width, float height) {}

		virtual void
		createGBuffer(float width, float height) {}

		virtual void
		createTemporalPipeline(float width, float height) {}

		virtual void
		update(buVector3F _pos, buVector3F _rot,
			buVector3F _scal, float _angle) {}

		virtual void
		render() {}

		virtual void 
		destroy() {}

		virtual buUI 
		getUI() {return buUI(); };
	};
	/**
 * @brief Export method for the class instance.
 */
	BU_RENDER_EXPORT sysRender&
		g_renderAPI();

	/**
	 * @brief Specific member uses as a instance to the class.
	 */
	using fnRenderAPIProt = sysRender * (*)();
}