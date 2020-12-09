#pragma once
#include <buPrerequisitesCore.h>
#include <buCoreGraphicsAPI.h>
#include <sysRender.h>
#include <buLight.h>
#include <buCommons.h>
#include <buCameraManager.h>
#include <buCoreTexture2D.h>
#include <buCoreDepthStencilView.h>
#include <buCoreViewport.h>
#include <buLight.h>
#include <buUI.h>

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
		init(void* _window, float width, float height) override;

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

		buUI 
		getUI() override;

	private:
		buUI m_userInterface;
		// GBuffer
		SPtr<buCoreTexture2D> m_txBackBuffer_GB;
		SPtr<buCoreTexture2D> m_txDepthStencil_GB;
		SPtr<buCoreDepthStencilView> m_depthStencilView_GB;
		SPtr<buCoreViewport> m_viewport_GB;
		SPtr<buCoreVertexShader> m_vertexShader_GB;
		SPtr<buCoreInputLayout> m_inputLayout_GB;
		SPtr<buCorePixelShader> m_pixelShader_GB;
		SPtr<buCoreSampler> m_sampler_GB;
		// Temporal 
		SPtr<buCoreTexture2D> m_txBackBuffer_tmp;
		SPtr<buCoreTexture2D> m_txDepthStencil_tmp;
		SPtr<buCoreDepthStencilView> m_depthStencilView_tmp;
		SPtr<buCoreViewport> m_viewport_tmp;
		SPtr<buCoreVertexShader> m_vertexShader_tmp;
		SPtr<buCoreInputLayout> m_inputLayout_tmp;
		SPtr<buCorePixelShader> m_pixelShader_tmp;
		SPtr<buCoreSampler> m_sampler_tmp;
		buLight m_light;
		SPtr<buCoreTexture2D> m_cubeMap;
		buCameraManager m_cameraManager;
		SPtr<buCoreBuffer> BonesTranform;
		/*
		* @brief
		*/
		float ClearColor[4] = { 0.7f, 0.7f, 0.7f, 0.7f };
		/**
		 * @brief
		 */
		float m_position[3] = { 0,0,0 };

		/**
		 * @brief
		 */
		float m_Scale[3] = { 1.0f , 1.0f , 1.0f };
		/**
		 * @brief
		 */
		float m_Rotation[3] = { 0,1,0 };
		/**
		 * @brief
		 */
		float m_angle = 0.0f;
		float m_near = 3.0f;
		float m_EngineScale = 1.0f;
		float m_far = 300.0f;
		/**
		 * @brief
		 */
		float m_up[3] = { 0.0f, 90.0f, -1.0f };
		float m_at[3] = { 0.0f, 0.0f, 1.0f };
		float m_eye[3] = { 0.0f, 60.0f, -90.0f };
		//Vector<SPtr<buCoreTexture2D>> m_ShaderResources;
		float m_lightPos[3] = { -30.0f, 85, -50.0f };
		float m_LightColor[3] = { 1.0f, 1.0f, 1.0f };
		float m_surfColor[3] = { 1.0f, 1.0f, 1.0f };
		float m_constants[4] = { 2.0f, 0,0,0 };
		uint32 m_screenWidth = 0;
		uint32 m_screenHeight = 0;
		LightBuffer LB;
		
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