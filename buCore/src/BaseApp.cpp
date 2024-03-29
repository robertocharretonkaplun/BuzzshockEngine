#include "BaseApp.h"
#include <chrono>
namespace buEngineSDK {

  int32 
  BaseApp::run() {
    // Create Window
    m_windowName = "Buzz shock Engine";
    m_screenWidth = 1350;
    m_screenHeight = 700;
    createWindow();
    // Create systems
    initSystems();

    
    // Sends message onCreate method
    onCreate();


    // Init Imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplWin32_Init(m_window);
    ImGui_ImplDX11_Init(reinterpret_cast<ID3D11Device*>(m_graphicsAPI->getDevice()),
      reinterpret_cast<ID3D11DeviceContext*>(m_graphicsAPI->getDeviceContext()));
    ImGui::StyleColorsLight();
    //ImFont* font1 = io.Fonts->AddFontDefault();
    //ImFont* font2 = io.Fonts->AddFontFromFileTTF("Data/Fonts/fontello.ttf", 16.0f);
    //setDarkStyle();
    setUnrealStyle();
    // Main loop
    MSG msg = { nullptr };
    while (WM_QUIT != msg.message) {
      if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
      else {
        // Update the game time
        static float t = 0.0f;
        //if (g_driverType == D3D_DRIVER_TYPE_REFERENCE) {
        //  t += (float)3.1415926535f * 0.0125f;
        //}
        //else {
        //}
          static uint32 dwTimeStart = 0;
          uint32 dwTimeCur = GetTickCount();
          if (dwTimeStart == 0)
            dwTimeStart = dwTimeCur;
          t = (dwTimeCur - dwTimeStart) / 1000.0f;

           std::chrono::high_resolution_clock timer;
           auto start = timer.now();

          //dealtaTime = 1.0f / ( clock() - oldTime );
        // Update game logic
        update(dealtaTime);
        // Render frame
        render();
        auto stop = timer.now();
        dealtaTime = std::chrono::duration_cast<std::chrono::milliseconds > (stop - start).count() / 1000.0f; //DELTATIME WAS LESS THAN 1 MILLISECOND SO THAT IS WHY I USED THIS
      }
    }

    // Destroy systems
    onDestroy();

    // Destroy all systems
    destroySystems();

    return 0;
  }

  void 
  BaseApp::initSystems() {
    if (m_directXPlug.loadPluggin("buDX_APId.dll")) {
      auto createGraphicsAPI = reinterpret_cast<fnGraphicsAPIProt>(
        m_directXPlug.getProcedureByName("createGraphicAPI"));

      auto createResourceManager = reinterpret_cast<fnresourceManagerProt>(
        m_directXPlug.getProcedureByName("createResourceManager"));
      
      auto createAppOptions = reinterpret_cast<fnAppOptionsProt>(
        m_directXPlug.getProcedureByName("createAppOptions"));

      buCoreGraphicsAPI::startUp();
      buCoreGraphicsAPI* graphicAPI = createGraphicsAPI();
      g_graphicsAPI().setObject(graphicAPI);
      m_graphicsAPI = &g_graphicsAPI();
      m_graphicsAPI->initialize(m_window, m_screenWidth, m_screenHeight);

      buResourceManager::startUp();
      buResourceManager* resourceManager = createResourceManager();
      g_resourceManager().setObject(resourceManager);
      m_resourceManager = &g_resourceManager();

      /*AppOptions::startUp();
      AppOptions* appOptions = createAppOptions();
      g_AppOptions().setObject(appOptions);
      m_appOptions = &g_AppOptions();*/
    }
    

  }

  bool 
  BaseApp::createWindow() {
    auto hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr));

    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = handelWindowEvent;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "TutorialWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_APPLICATION);
    if (!RegisterClassEx(&wcex)) {
      return false;
    }

    // Create window
    //m_instance = hInstance;
    RECT rc = { 0, 0, m_screenWidth, m_screenHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    
    HWND hWd;
    hWd = CreateWindow("TutorialWindowClass",
                       "Buzz shock Engine",
                       WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT,
                       CW_USEDEFAULT, 
                       rc.right - rc.left,
                       rc.bottom - rc.top, 
                       nullptr,
                       nullptr,
                       hInstance,
                       nullptr);
    if (!hWd) {
      return false;
    }

    ShowWindow(hWd, SW_SHOW);

    RECT clientRect;
    GetClientRect(hWd, &clientRect);

    m_screenWidth =  clientRect.right - clientRect.left;
    m_screenHeight = clientRect.bottom - clientRect.top;

    m_window = reinterpret_cast<void*>(hWd);

    return true;
  }

  void 
  BaseApp::update(float _deltaTime = 0) {
    onUpdate(_deltaTime);
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    // Set main menu
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Load...", "CTRL+O")) {
        }
        if (ImGui::MenuItem("Save...", "CTRL+S")) {

        }
        ImGui::Separator();

        if (ImGui::MenuItem("Exit", "CTRL+F4")) {
          exit(1);
        }

        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Edit")) {
        if (ImGui::MenuItem("Animator...")) {
          m_showAnimator = true;
        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Settings")) {
        
        if (ImGui::MenuItem("Show Average...")) {
          windowd = true;
        }
        if (ImGui::MenuItem("Engine Scale...")) {
          m_showEngineScale = true;
        }
        if (ImGui::MenuItem("Clear Console...")) {
          m_logs.clear();
        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
          
    if (windowd) {
      ImGui::Begin("App Average", &windowd);
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
        1000.0 / (ImGui::GetIO().Framerate), (ImGui::GetIO().Framerate));
      ImGui::End();
    }
    
    if (m_showEngineScale) {
      ImGui::Begin("Engine Scale", &m_showEngineScale);
      ImGui::InputFloat("Unit scale", &m_EngineScale);
      ImGui::End();
    }
    if (m_showAnimator) {
      ImGui::Begin("Animator", &m_showAnimator);
      auto currModel = m_resourceManager->getModel();
      auto meshNum = currModel->m_meshes.size();
      for (uint32 i = 0; i < meshNum; i++) {
        auto& currMesh = currModel->m_meshes[i];
        auto boneNum = currModel->m_skeleton->m_bonesInfo.size();
        for (uint32 j = 0; j < boneNum; j++) {
          auto& curreBone = currModel->m_skeleton->m_bonesInfo[j];
          if (ImGui::Button("+")) ImGui::OpenPopup("ElementList");
          ImGui::SameLine();
          //ImGui::Text(curreBone.boneName.c_str());
        }
      }
      ImGui::End();
    }

    ImGui::Begin("World Outliner");
    for (int i = 0; i < m_GONames.size(); ++i) {
      ImGui::AlignTextToFramePadding();
      bool treeopen = ImGui::TreeNodeEx(m_GONames[i].c_str(), ImGuiTreeNodeFlags_AllowItemOverlap);
      ImGui::SameLine();
      if (ImGui::Button("+")) ImGui::OpenPopup("ElementList");
      if (treeopen) {
        ImGui::TreePop();
      }
    }
    ImGui::End();

    ImGui::Begin("Camera Inspector");
    ImGui::SliderFloat3("Up", m_up, -10, 10);
    ImGui::SliderFloat3("At", m_at, -10, 10);
    ImGui::SliderFloat3("Eye", m_eye, -10, 10);
    ImGui::SliderFloat("Near", &m_near,0, 300);
    ImGui::SliderFloat("Far", &m_far,0, 300);
    ImGui::End();

    ImGui::Begin("Inspector");
    ImGui::Text("Tranform");
    
    ImGui::InputFloat3("Translation", m_position);
    ImGui::SliderFloat3("Rotation", m_Rotation, 0, 1);
    ImGui::InputFloat3("Scale", m_Scale);
    if (ImGui::Button("Rotate")) {
      if (m_isRotating) {
        m_isRotating = false;
      }
      else {
        m_isRotating = true;
      }
    }
    //ImGui::SameLine();
    ImGui::SliderFloat("Ang", &m_angle,-3,3);
    ImGui::Text("Mesh Renderer");
    for (uint32 i = 0; i < m_graphicsAPI->getShaderResource().size(); ++i) {
      ImGui::Text("Material ");
      if (ImGui::ImageButton(m_graphicsAPI->getShaderResource()[i], 
                             ImVec2(128, 128))) {
        OPENFILENAME ofn = { 0 };
        TCHAR szFile[260] = { 0 };
        // Initialize remaining fields of OPENFILENAME structure
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = reinterpret_cast<HWND>(m_window);
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = ("All\0*.*\0Text\0*.TXT\0");
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = nullptr;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = nullptr;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileName(&ofn) == TRUE) {
        }
      }
    }
    ImGui::End();
      
    ImGui::Begin("Content Browser", nullptr, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("Open...")) {
        if (ImGui::MenuItem("File", "CTRL+O")) {
          OPENFILENAME ofn = { 0 };
          TCHAR szFile[260] = { 0 };
          // Initialize remaining fields of OPENFILENAME structure
          ofn.lStructSize = sizeof(ofn);
          ofn.hwndOwner = reinterpret_cast<HWND>(m_window);
          ofn.lpstrFile = szFile;
          ofn.nMaxFile = sizeof(szFile);
          ofn.lpstrFilter = ("All\0*.*\0Text\0*.TXT\0");
          ofn.nFilterIndex = 1;
          ofn.lpstrFileTitle = nullptr;
          ofn.nMaxFileTitle = 0;
          ofn.lpstrInitialDir = nullptr;
          ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

          if (GetOpenFileName(&ofn) == TRUE) {
            Log("Resource Manager - Loading Mesh from file [Data/Models/AdvanceDancing.fbx]");
            m_resourceManager->loadMesh(ofn.lpstrFile);
            m_GONames.push_back(m_resourceManager->getModel()->TexName);
          }
        }
        if (ImGui::MenuItem("Texture")) {}
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }
    ImGui::End();

    ImGui::Begin("Console", nullptr, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("Clear")) {
        m_logs.clear();
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }
    for (int i = 0; i < m_logs.size(); ++i) {
      if (ImGui::Button("+")) {
        ImGui::OpenPopup("ElementList"); 
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("More Info...");
      }
        /*if (ImGui::BeginPopup("ElementList")) {
        ImGui::MenuItem("Possible error in []");
        ImGui::EndPopup();
      }*/
      ImGui::SameLine();
      ImGui::Text(m_logs[i].c_str());
    }
    ImGui::End();

    ImGui::Begin("Game");
    ImGui::Image(m_graphicsAPI->getShaderResource()[0],
      ImVec2(800, 450));
    ImGui::End();
    
  }

  void 
  BaseApp::render() {
    onRender();   

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    // Present
    m_graphicsAPI->present(0, 0);
  }


  void
  BaseApp::setImguiWhiteStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    ImVec4* colors = style.Colors;

    style.WindowRounding = 2.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
    style.ScrollbarRounding = 3.0f;             // Radius of grab corners rounding for scrollbar
    style.GrabRounding = 2.0f;             // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
    style.AntiAliasedLines = true;
    style.AntiAliasedFill = true;
    style.WindowRounding = 2;
    style.ChildRounding = 2;
    style.ScrollbarSize = 16;
    style.ScrollbarRounding = 3;
    style.GrabRounding = 2;
    style.ItemSpacing.x = 10;
    style.ItemSpacing.y = 4;
    style.IndentSpacing = 22;
    style.FramePadding.x = 6;
    style.FramePadding.y = 4;
    style.Alpha = 1.0f;
    style.FrameRounding = 3.0f;

    colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    //colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.93f, 0.93f, 0.93f, 0.98f);
    colors[ImGuiCol_Border] = ImVec4(0.71f, 0.71f, 0.71f, 0.08f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.71f, 0.71f, 0.71f, 0.55f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.94f, 0.94f, 0.94f, 0.55f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.71f, 0.78f, 0.69f, 0.98f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.82f, 0.78f, 0.78f, 0.51f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.61f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.90f, 0.90f, 0.90f, 0.30f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.92f, 0.92f, 0.78f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.184f, 0.407f, 0.193f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.71f, 0.78f, 0.69f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.725f, 0.805f, 0.702f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.793f, 0.900f, 0.836f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.71f, 0.78f, 0.69f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.71f, 0.78f, 0.69f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.71f, 0.78f, 0.69f, 1.00f);
    colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.45f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_NavHighlight] = colors[ImGuiCol_HeaderHovered];
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
  }

  void 
  BaseApp::setDarkStyle() {
    // Load Fonts
    
    //imGuiIO.Fonts->AddFontFromFileTTF("../data/Fonts/Ruda-Bold.ttf", 15.0f, &config);
    ImGui::GetStyle().FrameRounding = 4.0f;
    ImGui::GetStyle().GrabRounding = 4.0f;
    ImGui::GetStyle().WindowRounding = 0.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
    ImGui::GetStyle().ScrollbarRounding = 3.0f;
    ImGui::GetStyle().AntiAliasedLines = true;
    ImGui::GetStyle().AntiAliasedFill = true;
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

  void BaseApp::setUnrealStyle()
  {
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, .40f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 0.6f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.6f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.6f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.003921569, 0.7019608, 1, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.81f, 0.83f, 0.81f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.6f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 0.6f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.93f, 0.65f, 0.14f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.0f, 0.0f, 0.0f, 0.6f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
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

    ImGui::GetStyle().FrameRounding = 4.0f;
    ImGui::GetStyle().GrabRounding = 4.0f;
    ImGui::GetStyle().WindowRounding = 0.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
    ImGui::GetStyle().ScrollbarRounding = 3.0f;
    ImGui::GetStyle().AntiAliasedLines = true;
    ImGui::GetStyle().AntiAliasedFill = true;
  }

  LRESULT 
  BaseApp::handelWindowEvent(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam) {
    if ( ImGui_ImplWin32_WndProcHandler(Hw, Msg, wParam, lParam)) {
      return true;
    }
    /*auto pThis = (BaseApp*)GetWindowLongPtr(Hw, GWLP_USERDATA);
    if (pThis != nullptr) {
      return pThis->CustomDialogProcInstance(Hw, Msg, wParam, lParam);*/
    return DefWindowProc(Hw, Msg, wParam, lParam);
  }

  void 
  BaseApp::Log(String _log) {
    m_logs.push_back(_log);
  }
}
