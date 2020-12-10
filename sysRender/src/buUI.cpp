#include "buUI.h"
#include <imgui\imGuiDocking\imgui_internal.h>

namespace buEngineSDK {
  void
  buUI::init(void * _window, void * _device, void* _deviceContext) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplWin32_Init(_window);
    ImGui_ImplDX11_Init(reinterpret_cast<ID3D11Device*>(_device),
      reinterpret_cast<ID3D11DeviceContext*>(_deviceContext));
    ImGui::StyleColorsLight();
    setCostumStyle();
  }

  void 
  buUI::update() {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // Render Menu
    setInspector();
  }

  void 
  buUI::render() {
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  }

  void 
  buUI::destroy() {
  }
  
  void
  buUI::setCostumStyle() {
    ImGui::GetStyle().FrameRounding = 0.0f;
    ImGui::GetStyle().GrabRounding = 4.0f;
    ImGui::GetStyle().WindowRounding = 0.0f;
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
  }

  void
  buUI::setInspector() {
    static char str0[128] = "Game Object";
    //gameobject.m_name = str0;
    ImGui::Begin("Properties");
    //ImGui::Checkbox(" ", &m_renderObjects);
    ImGui::SameLine();
    ImGui::InputText("-", str0, IM_ARRAYSIZE(str0));
    ImGui::Separator();

    ImGui::Text("Active GO");
    //ImGui::Checkbox(" ", &m_selectedObject);
    ImGui::SameLine();

    //ImGui::InputInt("GO", &m_scene_graph.m_selectedGO);
    ImGui::Separator();
    ImGui::Text("Transform");
    ImGui::Separator();

    // Set Mesh transform
    //buVector3F scale(m_Scale[0] * m_EngineScale,
    //  m_Scale[1] * m_EngineScale,
    //  m_Scale[2] * m_EngineScale);
    //buVector3F rotation(m_Rotation[0], m_Rotation[1], m_Rotation[2]);
    //
    //
    //buVector3F position(m_position[0], m_position[1], m_position[2]);
    //
    //gameobject.update(position, rotation, scale, m_angle);
    //vec3Control("Position", m_position);
    //vec3Control("Rotation", m_Rotation);
    //vec3Control("Scale", m_Scale);
    //valControl("Angle", &m_angle);
    ImGui::Separator();
    ImGui::Text("Material");
    // Button to add a texture component to the scene

    ImGui::Separator();

   
    ImGui::Separator();
    const float ItemSpacing = ImGui::GetStyle().ItemSpacing.x;

    static float HostButtonWidth = 255.0f; //The 100.0f is just a guess size for the first frame.
    float pos = HostButtonWidth + ItemSpacing;
    ImGui::SameLine(ImGui::GetWindowWidth() - pos);
    if (ImGui::Button("Add Component Texture")) {
      //OPENFILENAME ofn = { 0 };
      //TCHAR szFile[260] = { 0 };
      //// Initialize remaining fields of OPENFILENAME structure
      //ofn.lStructSize = sizeof(ofn);
      //ofn.hwndOwner = reinterpret_cast<HWND>(m_window);
      //ofn.lpstrFile = szFile;
      //ofn.nMaxFile = sizeof(szFile);
      //ofn.lpstrFilter = ("All\0*.*\0Text\0*.TXT\0");
      //ofn.nFilterIndex = 1;
      //ofn.lpstrFileTitle = nullptr;
      //ofn.nMaxFileTitle = 0;
      //ofn.lpstrInitialDir = nullptr;
      //ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
      //
      //if (GetOpenFileName(&ofn) == TRUE) {
      //  SPtr<buCoreTexture2D> currTex = m_graphicsAPI->loadImageFromFile(
      //    ofn.lpstrFile, m_screenWidth, m_screenHeight, TextureType::E::DEFAULT);
      //  m_scene_graph.addTexToSelectedObj(currTex);
      //  // m_resourceManager->getModel()->m_textures.push_back(currTex);
      //}
    }

    ImGui::End();
  }

  void
  buUI::setMenu() {
    
    
    
  }

  LRESULT
  buUI::handelWindowEvent(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(Hw, Msg, wParam, lParam)) {
      return true;
    }
    //auto& renderMan = g_renderAPI();
    //renderMan.getUI().WndProc(Hw, Msg, wParam, lParam);
    /*
    auto pThis = (BaseApp*)GetWindowLongPtr(Hw, GWLP_USERDATA);
    if (pThis != nullptr) {
      return pThis->CustomDialogProcInstance(Hw, Msg, wParam, lParam);*/
    return DefWindowProc(Hw, Msg, wParam, lParam);
  }


}