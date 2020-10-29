#pragma once
#include <buPrerequisitesCore.h>
#include <buCoreVertexShader.h>
#include <buCorePixelShader.h>
#include <buCoreInputLayout.h>
#include <buVector4F.h>
#include <buVector3F.h>

namespace buEngineSDK {
	struct DEBUG_VERTEX	{
		DEBUG_VERTEX() = default;

		DEBUG_VERTEX(buVector3F _position, buVector4F _color)
			: m_position(_position), m_color(_color) {}


		buVector3F m_position;
		buVector4F m_color;
	};

	class BU_CORE_EXPORT buGraphicsDebug
	{
	public:
		buGraphicsDebug();
		~buGraphicsDebug() = default;

		void
		init();

		void 
		update();

		void
		render();

		void
		addLine(buVector3F& _posA, buVector3F& _posB,
						buVector4F _color, float _duration = 0);
	private:
		/**
		 * @brief Member that creates a vertex shader object.
		 */
		SPtr<buCoreVertexShader> vertexShader;

		/**
		 * @brief Member that creates an input layout object.
		 */
		SPtr<buCoreInputLayout> inputLayout;

		/**
		 * @brief Member that creates a pixel shader object.
		 */
		SPtr<buCorePixelShader> pixelShader;

		Vector<DEBUG_VERTEX> m_frameInfo;
	};
}