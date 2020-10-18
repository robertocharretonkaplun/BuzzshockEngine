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

namespace Format {
	enum E {
    BU_FORMAT_UNKNOWN = 0,
    BU_FORMAT_R32G32B32A32_TYPELESS = 1,
    BU_FORMAT_R32G32B32A32_FLOAT = 2,
    BU_FORMAT_R32G32B32A32_UINT = 3,
    BU_FORMAT_R32G32B32A32_SINT = 4,
    BU_FORMAT_R32G32B32_TYPELESS = 5,
    BU_FORMAT_R32G32B32_FLOAT = 6,
    BU_FORMAT_R32G32B32_UINT = 7,
    BU_FORMAT_R32G32B32_SINT = 8,
    BU_FORMAT_R16G16B16A16_TYPELESS = 9,
    BU_FORMAT_R16G16B16A16_FLOAT = 10,
    BU_FORMAT_R16G16B16A16_UNORM = 11,
    BU_FORMAT_R16G16B16A16_UINT = 12,
    BU_FORMAT_R16G16B16A16_SNORM = 13,
    BU_FORMAT_R16G16B16A16_SINT = 14,
    BU_FORMAT_R32G32_TYPELESS = 15,
    BU_FORMAT_R32G32_FLOAT = 16,
    BU_FORMAT_R32G32_UINT = 17,
    BU_FORMAT_R32G32_SINT = 18,
    BU_FORMAT_R32G8X24_TYPELESS = 19,
    BU_FORMAT_D32_FLOAT_S8X24_UINT = 20,
    BU_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
    BU_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
    BU_FORMAT_R10G10B10A2_TYPELESS = 23,
    BU_FORMAT_R10G10B10A2_UNORM = 24,
    BU_FORMAT_R10G10B10A2_UINT = 25,
    BU_FORMAT_R11G11B10_FLOAT = 26,
    BU_FORMAT_R8G8B8A8_TYPELESS = 27,
    BU_FORMAT_R8G8B8A8_UNORM = 28,
    BU_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
    BU_FORMAT_R8G8B8A8_UINT = 30,
    BU_FORMAT_R8G8B8A8_SNORM = 31,
    BU_FORMAT_R8G8B8A8_SINT = 32,
    BU_FORMAT_R16G16_TYPELESS = 33,
    BU_FORMAT_R16G16_FLOAT = 34,
    BU_FORMAT_R16G16_UNORM = 35,
    BU_FORMAT_R16G16_UINT = 36,
    BU_FORMAT_R16G16_SNORM = 37,
    BU_FORMAT_R16G16_SINT = 38,
    BU_FORMAT_R32_TYPELESS = 39,
    BU_FORMAT_D32_FLOAT = 40,
    BU_FORMAT_R32_FLOAT = 41,
    BU_FORMAT_R32_UINT = 42,
    BU_FORMAT_R32_SINT = 43,
    BU_FORMAT_R24G8_TYPELESS = 44,
    BU_FORMAT_D24_UNORM_S8_UINT = 45,
    BU_FORMAT_R24_UNORM_X8_TYPELESS = 46,
    BU_FORMAT_X24_TYPELESS_G8_UINT = 47,
    BU_FORMAT_R8G8_TYPELESS = 48,
    BU_FORMAT_R8G8_UNORM = 49,
    BU_FORMAT_R8G8_UINT = 50,
    BU_FORMAT_R8G8_SNORM = 51,
    BU_FORMAT_R8G8_SINT = 52,
    BU_FORMAT_R16_TYPELESS = 53,
    BU_FORMAT_R16_FLOAT = 54,
    BU_FORMAT_D16_UNORM = 55,
    BU_FORMAT_R16_UNORM = 56,
    BU_FORMAT_R16_UINT = 57,
    BU_FORMAT_R16_SNORM = 58,
    BU_FORMAT_R16_SINT = 59,
    BU_FORMAT_R8_TYPELESS = 60,
    BU_FORMAT_R8_UNORM = 61,
    BU_FORMAT_R8_UINT = 62,
    BU_FORMAT_R8_SNORM = 63,
    BU_FORMAT_R8_SINT = 64,
    BU_FORMAT_A8_UNORM = 65,
    BU_FORMAT_R1_UNORM = 66,
    BU_FORMAT_R9G9B9E5_SHAREDEXP = 67,
    BU_FORMAT_R8G8_B8G8_UNORM = 68,
    BU_FORMAT_G8R8_G8B8_UNORM = 69,
    BU_FORMAT_BC1_TYPELESS = 70,
    BU_FORMAT_BC1_UNORM = 71,
    BU_FORMAT_BC1_UNORM_SRGB = 72,
    BU_FORMAT_BC2_TYPELESS = 73,
    BU_FORMAT_BC2_UNORM = 74,
    BU_FORMAT_BC2_UNORM_SRGB = 75,
    BU_FORMAT_BC3_TYPELESS = 76,
    BU_FORMAT_BC3_UNORM = 77,
    BU_FORMAT_BC3_UNORM_SRGB = 78,
    BU_FORMAT_BC4_TYPELESS = 79,
    BU_FORMAT_BC4_UNORM = 80,
    BU_FORMAT_BC4_SNORM = 81,
    BU_FORMAT_BC5_TYPELESS = 82,
    BU_FORMAT_BC5_UNORM = 83,
    BU_FORMAT_BC5_SNORM = 84,
    BU_FORMAT_B5G6R5_UNORM = 85,
    BU_FORMAT_B5G5R5A1_UNORM = 86,
    BU_FORMAT_B8G8R8A8_UNORM = 87,
    BU_FORMAT_B8G8R8X8_UNORM = 88,
    BU_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
    BU_FORMAT_B8G8R8A8_TYPELESS = 90,
    BU_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
    BU_FORMAT_B8G8R8X8_TYPELESS = 92,
    BU_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
    BU_FORMAT_BC6H_TYPELESS = 94,
    BU_FORMAT_BC6H_UF16 = 95,
    BU_FORMAT_BC6H_SF16 = 96,
    BU_FORMAT_BC7_TYPELESS = 97,
    BU_FORMAT_BC7_UNORM = 98,
    BU_FORMAT_BC7_UNORM_SRGB = 99,
    BU_FORMAT_AYUV = 100,
    BU_FORMAT_Y410 = 101,
    BU_FORMAT_Y416 = 102,
    BU_FORMAT_NV12 = 103,
    BU_FORMAT_P010 = 104,
    BU_FORMAT_P016 = 105,
    BU_FORMAT_420_OPAQUE = 106,
    BU_FORMAT_YUY2 = 107,
    BU_FORMAT_Y210 = 108,
    BU_FORMAT_Y216 = 109,
    BU_FORMAT_NV11 = 110,
    BU_FORMAT_AI44 = 111,
    BU_FORMAT_IA44 = 112,
    BU_FORMAT_P8 = 113,
    BU_FORMAT_A8P8 = 114,
    BU_FORMAT_B4G4R4A4_UNORM = 115,

    BU_FORMAT_P208 = 130,
    BU_FORMAT_V208 = 131,
    BU_FORMAT_V408 = 132,


    BU_FORMAT_FORCE_UINT = 0xffffffff
	};
}

namespace BindFlag {
  enum E {
    BU_BIND_VERTEX_BUFFER = 0x1L,
    BU_BIND_INDEX_BUFFER = 0x2L,
    BU_BIND_CONSTANT_BUFFER = 0x4L,
    BU_BIND_SHADER_RESOURCE = 0x8L,
    BU_BIND_STREAM_OUTPUT = 0x10L,
    BU_BIND_RENDER_TARGET = 0x20L,
    BU_BIND_DEPTH_STENCIL = 0x40L,
    BU_BIND_UNORDERED_ACCESS = 0x80L,
    BU_BIND_DECODER = 0x200L,
    BU_BIND_VIDEO_ENCODER = 0x400L
  };
}

namespace buEngineSDK {

	struct CBChangesEveryFrame {
		buMatrix4x4 mWorld = buMatrix4x4::ZERO;
		buVector4F vMeshColor;
		buVector4F viewDirection;
		buVector4F LightPos;
		buVector4F LightColor;
		buVector4F surfColor;
    buVector4F constants;
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
		//SPtr<buCoreTexture2D> backBuffer;

		

		

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
		SPtr<buCoreTexture2D> normalTexture;

		/**
		 * @brief Member that creates a sampler object. 
		 */
		SPtr<buCoreSampler> sampler;

		/**
	 	 * @brief Member that creates a changes every frame object. 
		 */
		SPtr<buCoreBuffer> changeEveryFrame;

		SPtr<buCoreBuffer> BonesTranform;

		
		/**
		 * @brief Member that sets the world matrix
		 */
		buMatrix4x4 m_World = buMatrix4x4(0.2f, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.2f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.2f, 0.0f,
                          0.0f, 0.0f, 0.0f, 0.2f);
		
		/**
		 * @brief Member that sets the color of the mesh.
		 */
		buVector4F m_meshColor = buVector4F(0.7f, 0.7f, 0.7f, 1.0f);
		
		/**
		 * @brief Member that sets the clear color 
		 */
		//float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; 
		
    buCamera m_camera;
		/**
		 * @brief 
		 */
		buGraphicsDebug m_lineDebugger;

    CBChangesEveryFrame cb;
	};
}
