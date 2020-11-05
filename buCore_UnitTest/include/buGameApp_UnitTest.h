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
#include <buGraphicsDebug.h>
#include <buCamera.h>
#include <buTransform.h>
#include <buCommons.h>

namespace buEngineSDK {

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
		 * @brief Member that creates a sampler object. 
		 */
		SPtr<buCoreSampler> sampler;
		SPtr<buCoreTexture2D> m_cubeMap;

		/**
	 	 * @brief Member that creates a changes every frame object. 
		 */
		SPtr<buCoreBuffer> changeEveryFrame;

		SPtr<buCoreBuffer> BonesTranform;
		
		/**
		 * @brief 
		 */
		buGraphicsDebug m_lineDebugger;

    CBChangesEveryFrame cb;

    buTransform m_meshTransform;

		
	};
}
