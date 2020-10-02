/**
 * @file 
 * @version 
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once
//#include <buPrerequisitesCore.h>
#include "BaseApp.h"
#include "buPrerequisitesCore.h"
#include <buCoreGraphicsAPI.h>
#include <buPluggin.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <buVector2F.h>
#include <buVector3F.h>
#include <buVector4F.h>
#include <buMatrix4x4.h>
#include <buDegrees.h>
#include <buTransform.h>


namespace buEngineSDK {

	struct CBNeverChanges	{
		buMatrix4x4 mView;
	};

	struct CBChangeOnResize	{
		buMatrix4x4 mProjection;
	};

	struct CBChangesEveryFrame {
		buMatrix4x4 mWorld = buMatrix4x4::ZERO;
		buVector4F vMeshColor;
	};

	struct cbBonesTranform
	{
		buMatrix4x4 boneTransform[100];
	};

	class buGameApp_UnitTest : public BaseApp
	{
	public:
		/**
		 * @brief Constructor
		 */
		buGameApp_UnitTest();
		/**
		 * @brief Destructor
		 */
		~buGameApp_UnitTest();
		/** 
		 * @brief Method that allows the user to initialize the information.
		 */
		void 
		onCreate() override;

		/** 
		 * @brief Method that destroys the modules and components of the app.
		 */
		void
		onDestroy() override;

		/** 
		 * @brief Method that updates the logic information of the app.
		 */
		void
		onUpdate(float _deltaTime = 0) override;

		/** 
		 * @brief Method that draw the objects on the screen.
		 */
		void
		onRender() override;
	private: 
		/*
		 * @brief Member that will be used as a back buffer texture. 
		 */
		SPtr<buCoreTexture2D> backBuffer;

		/**
		 * @brief Member that will be used as a depth stencil texture.
		 */
		SPtr<buCoreTexture2D> depthStencil;

		/**
		 * @brief Member that creates a depth stencil view object.
		 */
		SPtr<buCoreDepthStencilView> depthStencilView;

		/**
		 * @brief Member that creates a render target view object. 
		 */
		SPtr<buCoreRenderTargetView> renderTargetView;

		/**
		 * @brief Member that creates a viewport object.
		 */
		SPtr<buCoreViewport> viewport;

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

		/**
		 * @brief Member that creates a texture for a mesh.
		 */
		SPtr<buCoreTexture2D> meshTexture;
		
		/**
		 * @brief UI icon for the loaded mesh
		 */
		SPtr<buCoreTexture2D> meshIcon_UI;
		SPtr<buCoreTexture2D> transformIcon_UI;

		/**
		 * @brief Member that creates a sampler object. 
		 */
		SPtr<buCoreSampler> sampler;

		/**
		 * @brief Member that creates a never changes buffer. 
		 */
		SPtr<buCoreBuffer> neverChanges;

		/**
		 * @brief Member that creates a change on resize buffer.
		 */
		SPtr<buCoreBuffer> changeOnResize;

		/**
	 	 * @brief Member that creates a changes every frame object. 
		 */
		SPtr<buCoreBuffer> changeEveryFrame;

		SPtr<buCoreBuffer> BonesTranform;

		//
		//SPtr<buCoreModelLoader> m_loader;
		
		/**
		 * @brief Member that sets the world matrix
		 */
		buMatrix4x4 m_World = buMatrix4x4(0.2f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.2f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.2f, 0.0f,
                          0.0f, 0.0f, 0.0f, 0.2f);

		/**
		 * @brief Member that sets the view matrix.
		 */
		buMatrix4x4 m_view = buMatrix4x4::ZERO;

		/**
		 * @brief Member that set the projection matrix. 
		 */
		buMatrix4x4 m_projection = buMatrix4x4::ZERO;
		
		/**
		 * @brief Member that sets the color of the mesh.
		 */
		buVector4F m_meshColor = buVector4F(0.7f, 0.7f, 0.7f, 1.0f);
		
		/**
		 * @brief Member that sets the clear color 
		 */
		//float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; 
		float ClearColor[4] = { 0.5803221f, 0.5901454f, 0.5943396f, 1.0f };
		//float ClearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
		buTransform m_testTransform;
	};
}
