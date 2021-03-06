/**
 * @file 
 * @version 
 * @date 00/00/2020
 * @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
 * @brief 
 * @bug
 */
#pragma once
#include "buPrerequisitesCore.h"
#include <buCoreGraphicsAPI.h>
//#include <sysAudioAPI.h>
//#include <sysRender.h>
#include <buCameraManager.h>
#include <buResourceManager.h>
#include <buCoreConfig.h>
#include <buPluggin.h>
#include <buCoreTexture2D.h>
#include <SaveSystem.h>
#include <buSceneGraph.h>
#include "buCommons.h"
#include "buLogger.h"
#include "buTime.h"
//#include "imgui\imGuiDocking\imgui.h"
//#include "imgui\imGuiDocking\imgui_impl_dx11.h"
//#include "imgui\imGuiDocking\imgui_impl_win32.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
																							UINT msg,
																						  WPARAM wParam,
																							LPARAM lParam);
namespace buEngineSDK {
	class BU_CORE_EXPORT BaseApp {
	public:
		/**
		 * @brief Default constructor
		 */
		BaseApp() = default;
		/**
		 * @brief Destructor
		 */
		~BaseApp() {};
		/** 
		 * @brief Method in charge of initialize the main loop and systems of the 
		 * graphics.
		 * @return A integer, usually zero.
		 * @bug Error loading the texture from file.
		 */
		int32 
		run();
	protected:
		/** 
		 * @brief Method in charge of creating a virtual method that can be used in
		 * gameApp.
		 */
		virtual void 
		onCreate() {};

		/** 
		 * @brief Method in charge of destroying the game settings and members. This
		 * method can be used in the gameApp.
		 */
		virtual void
		onDestroy() {};

		/** 
		 * @brief Virtual method in charge of updating the logical information of 
		 * the game. This method can be used in the gameApp.
		 * @param _deltaTime Variable in charge of updating the game time.
		 */
		virtual void
		onUpdate(float _deltaTime = 0) { (void)_deltaTime;};

		/** 
		 * @brief Virtual method in charge of drawing on screen all the visual info.
		 * This method can be used in the gameApp.
		 */
		virtual void
		onRender() {};

		virtual void
		renderBillBoard(buGameObject) {};
	private:
		/** 
		* @brief Method in charge of creating a window in the App.
		* @return A boolean value.
		*/
		bool
		createWindow();

		/** 
		 * @brief Method the updates the logic information that the users will not 
		 * be available to modify.
		 * @param _deltaTime Variable in charge of updating the game time.
		 */
		void
		update(float _deltaTime);

		/** 
		 * @brief Method that draw the information that the user will not be
		 * available to modify.
		 */
		void 
		render();

		/**
		 * @brief Method that initialize the modules and plug-ins for the engine.
		 */
		void 
		initSystems();

		/** 
		 * @brief Method that destroys the systems of the engine.
		 */
		void 
		destroySystems() {};

		void
		setUnrealStyle();

		void
		MainMenu();

		void 
		cameraHerarchy();

		void
		loadInformation();
		
		void
		saveInformation();

		void 
		goProperties_ImGui(buGameObject gameobject);

		void
		shaderProperties();

		void 
		vec3Control(String label, float* values, float resetValues = 0.0f, float columnWidth = 100.0f);

		void
		valControl(String label, float *value,
							 float resetValues = 0.0f, float columnWidth = 100.0f);

		void 
		cameraProperties(buCamera currCamera);

		void 
		sceneGraph();

		/**
		 * @brief Method in charge of having a visual initialization for the online method.
		 */
		void 
		login();
	public:
		/**
		* @brief Method that set the events and messages for the game.
		*/
		static LRESULT CALLBACK
		handelWindowEvent(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam);

		/*LRESULT CALLBACK 
	  CustomDialogProcInstance(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam);*/
		void 
		Log(String _log);

  protected:
		/*
		 * @brief Member in charge of getting the dll of directX.
		 */
    buPluggin m_directXPlug;
    buPluggin m_audioPlug;
    buPluggin m_renderPlug;

		/**
		* @brief Member that sets the window reference.
		*/
		void* m_window = nullptr;
		/**
		 * @brief Member in charge of setting the name of the window.
		 */
		String m_windowName;

		/**
		 * @brief Member in charge of setting the screen width of the game window.
		 */
		uint32 m_screenWidth = 0;
		uint32 m_screenHeight = 0;
		/**
		 * @brief 
		 */
		bool windowd = false;
		bool m_sceneWindow = false;
		bool isUpdatedSceneInfo = false;
		
		bool m_showEngineScale = false;
		bool m_showConsole = false;
		bool m_showAnimator = false;
		bool m_isRotating = false;
		/**
		 * @brief Member in charge of setting the screen height of the game window.
		 */
		/**
		 * @brief 
		 */
		//AppOptions* m_appOptions = nullptr;
		/**
		 * @brief Member in charge of storing the graphicsAPI context.
		 */
		buCoreGraphicsAPI* m_graphicsAPI = nullptr;
		//sysAudioAPI* m_sysAudioAPI = nullptr;
		//sysRender* m_sysRenderAPI = nullptr;
		buCameraManager m_cameraManager ;
		/**
		 * @brief 
		 */
		buResourceManager* m_resourceManager = nullptr;
		buSceneGraph m_scene_graph ;
		/**
		 * @brief Member that creates a depth stencil view object.
		 */
		SPtr<buCoreDepthStencilView> depthStencilView;

		/**
		 * @brief Member that will be used as a depth stencil texture.
		 */
		SPtr<buCoreTexture2D> depthStencil;
		/*
		 * @brief Member that will be used as a back buffer texture.
		 */
		SPtr<buCoreTexture2D> backBuffer;

		/**
		 * @brief Member that creates a viewport object.
		 */
		SPtr<buCoreViewport> viewport;

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
		/**
		 * @brief 
		 */
		Vector<String> m_list;

		bool m_renderObjects = true;
		bool m_selectedObject = false;
		bool m_isCubeLoaded = false;
		uint32 m_audioStatec = 0;
		uint32 val = 1;
		uint32 m_currCamera = 0;
		uint32 m_selectedItem = 1;
		//buGameObject tmpGO;
		SaveSystem m_saverMan;

		Vector<String> m_logs = buLogger::GetLogger()->GetLogDataFromFile();

		buTime m_time;
		// UI variables 
		bool IsEngineInitialized = false;
	};
}
