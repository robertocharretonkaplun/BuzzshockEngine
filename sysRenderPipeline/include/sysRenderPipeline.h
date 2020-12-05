#pragma once
#include <sysRender.h>
#include <buCoreGraphicsAPI.h>
#include <buLight.h>
#include <buCommons.h>
#include <buCameraManager.h>
#include <buCoreTexture2D.h>
#include <buCoreDepthStencilView.h>
#include <buCoreViewport.h>
namespace buEngineSDK {
	struct cbBonesTranform
	{
		buMatrix4x4 boneTransform[100];
	};
	class sysRenderPipeline : public sysRender
	{
	public:
		sysRenderPipeline() = default;
		~sysRenderPipeline() = default;

		void
		init(float width, float height) override;

		void
		createGBuffer(float width, float height) override;

		void
		createTemporalPipeline(float width, float height) override;

		void
		update() override;

		void
		render() override;

		void 
		destroy() override;


	private:
		// GBuffer
		SPtr<buCoreTexture2D> m_txBackBuffer_GB;
		SPtr<buCoreTexture2D> m_txDepthStencil_GB;
		SPtr<buCoreDepthStencilView> m_depthStencilView_GB;
		SPtr<buCoreViewport> m_viewport_GB;
		SPtr<buCoreVertexShader> m_vertexShader_GB;
		SPtr<buCoreInputLayout> m_inputLayout_GB;
		SPtr<buCorePixelShader> m_pixelShader_GB;
		SPtr<buCoreSampler> m_sampler_GB;
		
	};
	/**
	* @brief Plugging exportation data method.
	* @return Instance of audio.
	*/
	extern "C" BU_PLUGIN_EXPORT sysRenderPipeline *
		createRenderAPI() {
		auto pRender = new sysRenderPipeline();
		return pRender;
	}
}