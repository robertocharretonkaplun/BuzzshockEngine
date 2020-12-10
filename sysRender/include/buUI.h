#pragma once
#include <buPrerequisitesCore.h>
#include <PrerequisitesRender.h>
#include <buCoreGraphicsAPI.h>
#include "imgui\imGuiDocking\imgui.h"
#include "imgui\imGuiDocking\imgui_impl_dx11.h"
#include "imgui\imGuiDocking\imgui_impl_win32.h"
#include <Windows.h>
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);
namespace buEngineSDK {
	class BU_RENDER_EXPORT buUI
	{
	public:
		buUI() = default;
		~buUI() = default;

		void 
		init(void* _window, void* _device, void* _deviceContext);

		void 
		update();

		void 
		render();

		void 
		destroy();

		void
		setCostumStyle();

		void
		setInspector();

		void
		setMenu();
		static LRESULT CALLBACK
		handelWindowEvent(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam);
	private:
		bool windowd = false;
		bool m_showEngineScale = false;
		float m_EngineScale = 1.0f;
	};
}