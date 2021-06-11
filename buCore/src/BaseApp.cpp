#include "BaseApp.h"
//#include <imgui\imGuiDocking\imgui_internal.h>

namespace buEngineSDK {

  int32 
  BaseApp::run() {
    // Create Window
    m_windowName = "Buzzshock Engine";
    m_screenWidth = 1500;
    m_screenHeight = 800;
    createWindow();
    // Create systems
    initSystems();
    // Initialize the renderer 
    //auto& renderMan = g_renderAPI();
    //renderMan.init(m_window, m_screenWidth, m_screenHeight);
    //BYTE buffer[4096] = { 0 };
    //Vector<BYTE> ToMem;
    //Vector<BYTE> FromMem;
    //
    //ToMem.resize(sizeof(buVector3F));
    //FromMem.reserve(4096);
    //RTTIEmptyType<buVector3F> obj;
    //obj.toMemory(buVector3F(5, 15, 20), buffer);
    //obj.toMemory(buVector3F(5, 15, 20), ToMem.data());
    //
    //for (uint32 i = 0; i < 4096; i++) {
    //  ToMem.push_back(buffer[i]);
    //}
    //
    //m_saverMan.saveSerialization(ToMem);
    //FromMem = m_saverMan.getSerialization();
    //
    //
    //buVector3F empty;
    //obj.fromMemory(empty, &FromMem.data()[sizeof(empty)-1]);

    // Crate Json open document
    m_json.openDoc();

    onCreate();

    // Init Imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplWin32_Init(m_window);
    ImGui_ImplDX11_Init(reinterpret_cast<ID3D11Device*>(m_graphicsAPI->getDevice()),
      reinterpret_cast<ID3D11DeviceContext*>(m_graphicsAPI->getDeviceContext()));
    ImGui::StyleColorsLight();
    setUnrealStyle();
    // Main loop
    MSG msg = { nullptr };
    while (WM_QUIT != msg.message) {
      if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
      else {
        // Update game logic
        update(m_time.getDeltaTime());
        
        // Render frame
        render(); 
      }
    }

    // Destroy systems
    onDestroy();
    m_scene_graph.destroy();
    // Destroy all systems
    destroySystems();

    return 0;
  }

  void 
  BaseApp::initSystems() {
    if (m_directXPlug.loadPluggin("buDX_APId.dll")) {
      // Initialize the graphics API from DX11
      auto createGraphicsAPI = reinterpret_cast<fnGraphicsAPIProt>(
        m_directXPlug.getProcedureByName("createGraphicAPI"));
      // Initialize the Resource Manager
      auto createResourceManager = reinterpret_cast<fnresourceManagerProt>(
        m_directXPlug.getProcedureByName("createResourceManager"));
      // Initialize the app options
      auto createAppOptions = reinterpret_cast<fnAppOptionsProt>(
        m_directXPlug.getProcedureByName("createAppOptions"));
      // Initialize the Camera Manager
      auto createCameraManager = reinterpret_cast<fnCameraManagerProt>(
        m_directXPlug.getProcedureByName("createCameraManager"));
      // Initialize the Connect API from Buzzshock Connect

      buCoreGraphicsAPI::startUp();
      buCoreGraphicsAPI* graphicAPI = createGraphicsAPI();
      g_graphicsAPI().setObject(graphicAPI);
      m_graphicsAPI = &g_graphicsAPI();
      m_graphicsAPI->initialize(m_window, m_screenWidth, m_screenHeight);

      buResourceManager::startUp();
      buResourceManager* resourceManager = createResourceManager();
      g_resourceManager().setObject(resourceManager);
      m_resourceManager = &g_resourceManager();
      
    }

    // Initialize the Connect API from Buzzshock Connect
    if (m_connectAPIPlug.loadPluggin("Connect_APId.dll"))
    {
      auto createConnectAPI = reinterpret_cast<fnConnectAPIProt>(
        m_connectAPIPlug.getProcedureByName("createConnectAPI"));

      buCoreConnectAPI::startUp();
      buCoreConnectAPI* connectAPI = createConnectAPI();
      g_connectAPI().setObject(connectAPI);
      m_connectAPI = &g_connectAPI();
    }

  }

  bool 
  BaseApp::createWindow() {
    auto hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr));
    //auto& renderMan = g_renderAPI();
    // Register class
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEXA);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = handelWindowEvent;// renderMan.getUI().handelWindowEvent;// handelWindowEvent;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIconA(hInstance, (LPCTSTR)IDI_APPLICATION);
    wcex.hCursor = LoadCursorA(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "TutorialWindowClass";
    wcex.hIconSm = LoadIconA(wcex.hInstance, (LPCTSTR)IDI_APPLICATION);
    if (!RegisterClassExA(&wcex)) {
      return false;
    }

    // Create window
    //m_instance = hInstance;
    RECT rc = { 0, 0, m_screenWidth, m_screenHeight };
    AdjustWindowRect(&rc, WS_MAXIMIZEBOX, FALSE);
    
    HWND hWd;
    hWd = CreateWindowA("TutorialWindowClass",
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
    // Draw ui from imgui
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();

    onUpdate(_deltaTime);
    // Algorithm that update the different types and contexts of the engine
    switch (m_initType) {
    case InitType::Default:
      login();
      break;
    case InitType::BuzzshockEngine:
      MainMenu();
      BuzzshockEngineUpdate(_deltaTime);
      break;
    case InitType::BuzzshockConnect:
      MainMenu();
      showConnectWindow();
      break;
    }    


    // Update scene information
    // Update the renderer
    //auto& renderMan = g_renderAPI();
    //static bool animate = true;
    //ImGui::Checkbox("Animate", &animate);
    ////ImGui::Begin("App Average", &windowd);
    ////ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
    ////  1000.0 / (ImGui::GetIO().Framerate), (ImGui::GetIO().Framerate));
    ////ImGui::End();
    //static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
    //ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));
    //// Create a dummy array of contiguous float values to plot
    //// Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float and the sizeof() of your structure in the Stride parameter.
    //static float values[90] = { 0 };
    //static int values_offset = 0;
    //static float refresh_time = 0.0f;
    //if (!animate || refresh_time == 0.0f)
    //  refresh_time = ImGui::GetTime();
    //while (refresh_time < ImGui::GetTime()) // Create dummy data at fixed 60 hz rate for the demo
    //{
    //  static float phase = 0.0f;
    //  values[values_offset] = cosf(phase);
    //  values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
    //  phase += 0.10f * values_offset;
    //  refresh_time += 1.0f / 60.0f;
    //}
    //ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, "avg 0.0", -1.0f, 1.0f, ImVec2(0, 80));
    //ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0, 80));
    //// Set main menu
    //MainMenu();
    
    //auto GameObjects = m_resourceManager->getGameObjects();
    //static char str0[128] = "Game Object";
    //if (GameObjects.size() >= 2) {
    //  auto &currGameObject = GameObjects[val];
    //  currGameObject.m_name = str0;
    //  m_selectedObject = true;
    //}

    //cameraHerarchy(); 
    // Container for shader attributes
    //ImGui::Begin("Audio Resource");
    //if (ImGui::Button("Play")) {
    //  m_audioState = 1;
    //}
    //if (ImGui::Button("Pause")) {
    //  m_audioState = 0;
    //}
    //ImGui::End();

    //ImGui::Begin("Game");
    //ImGui::End();
    //
    //
    //if (m_scene_graph.m_gameObjects.size() >= 1 && m_scene_graph.m_selectedGO >= 0) {
    //  goProperties_ImGui(m_scene_graph.getSelectedGO());
    //}
    //else {
    //  buGameObject tmpGo;
    //  goProperties_ImGui(tmpGo);
    //}
    // goProperties_ImGui(tmpGO);
    // Shader Properties
    //cameraProperties(m_cameraManager.GetActiveCamera());
    
  
  }

  void
  BaseApp::BuzzshockEngineUpdate(float _deltaTime)  {    
    if (m_isDataLoaded) {
      buVector3F scale(m_scene_graph.getSelectedGO().sca[0] * m_EngineScale,
        m_scene_graph.getSelectedGO().sca[1] * m_EngineScale,
        m_scene_graph.getSelectedGO().sca[2] * m_EngineScale);
      buVector3F rotation(m_scene_graph.getSelectedGO().rot[0], m_scene_graph.getSelectedGO().rot[1], m_scene_graph.getSelectedGO().rot[2]);
      buVector3F position(m_scene_graph.getSelectedGO().pos[0], m_scene_graph.getSelectedGO().pos[1], m_scene_graph.getSelectedGO().pos[2]);

      buMatrix4x4 mat = buMatrix4x4::IDENTITY;
      //position.x = dir.x;
      ImGuizmo::RecomposeMatrixFromComponents(&position.x, &rotation.x, &scale.x, &mat.m_x0);

      buGizmo(&mat.m_x0);
      ImGuizmo::DecomposeMatrixToComponents(&mat.m_x0, &position.x, &rotation.x, &scale.x);

      m_Scale[0] = scale.x;
      m_Scale[1] = scale.y;
      m_Scale[2] = scale.z;

      m_Rotation[0] = rotation.x;
      m_Rotation[1] = rotation.y;
      m_Rotation[2] = rotation.z;

      m_position[0] = position.x;
      m_position[1] = position.y;
      m_position[2] = position.z;

      m_scene_graph.getSelectedGO().update(position, rotation, scale, m_angle);
      m_scene_graph.getSelectedGO().drawUI();
    }
    // Draw Scene Graph UI
    m_scene_graph.drawUI();
    // Draw Guizmo without GO
    if (!m_isDataLoaded) {
      buMatrix4x4 tmpMat = buMatrix4x4::IDENTITY;
      buGizmo(&tmpMat.m_x0);
    }
    // Draw the serialization UI
    serializerUI();
    // Server Window for elastic search + curl
    serverCURLUI();
    // Draw the tool bar
    toolsUI();
    // Draw change log
    changeLogUI();
  }

  void 
  BaseApp::render() {
    // Draw the renderer
    onRender();   
    switch (m_initType) {
    case buEngineSDK::Default:
      break;
    case buEngineSDK::BuzzshockEngine:
      {
      if (m_isDataLoaded) {
          m_scene_graph.render(TopologyType::E::BU_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
          renderBillBoard(m_scene_graph.getSelectedGO());
      }
      }
      break;
    case buEngineSDK::BuzzshockConnect:
      break;
    default:
      break;
    }
    // Render ImGui Data
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    // Present
    m_graphicsAPI->present(0, 0);
  }

  void
  BaseApp::setUnrealStyle() {
    
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
    //*/
  }

  void
  BaseApp::MainMenu() {
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Load...", "CTRL+O")) {
          // Load scene from file
          m_isDataLoaded = true;
          loadInformation();
        }
        if (ImGui::MenuItem("Save...", "CTRL+S")) {
          // Save scene to file
          saveInformation();
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
      if (ImGui::BeginMenu("Window")) {
        ImGui::Text("Level Editor");
        ImGui::Separator();
        if (ImGui::MenuItem("Herarchy")) {

        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Settings")) {
        if (ImGui::MenuItem("Scene Settings...")) {
          m_sceneWindow = true;
        }
        if (ImGui::MenuItem("Show Average...")) {
          windowd = true;
        }
        if (ImGui::MenuItem("Engine Scale...")) {
          m_showEngineScale = true;
        }
        if (ImGui::MenuItem("Show Console...")) {
          m_showConsole = true;
          //m_logs.clear();
        }
        ImGui::EndMenu();
      }
      
      ImGui::EndMainMenuBar();
    }
    if (m_sceneWindow) {
      ImGui::Begin("Scene Settings", &m_sceneWindow);
      ImGui::Text("Scene name ");

      static char str1[128] = "";
      ImGui::InputTextWithHint(" ", "Enter the new name... ", str1, IM_ARRAYSIZE(str1));
      //ImGui::InputTextWithHint("Change scene name: ", "enter text here", str1, IM_ARRAYSIZE(str1));
      if (ImGui::Button("Update")) {
        isUpdatedSceneInfo = true;
      }

      if (isUpdatedSceneInfo) {
        m_scene_graph.m_sceneName = str1;
        isUpdatedSceneInfo = false;
      }

      ImGui::End();
    }
    /*
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
      //auto currModel = m_resourceManager->getModel();
      //auto meshNum = currModel->m_meshes.size();
      //for (uint32 i = 0; i < meshNum; i++) {
      //  auto& currMesh = currModel->m_meshes[i];
      //  auto boneNum = currModel->m_skeleton->m_bonesInfo.size();
      //  for (uint32 j = 0; j < boneNum; j++) {
      //    auto& curreBone = currModel->m_skeleton->m_bonesInfo[j];
      //    if (ImGui::Button("+")) ImGui::OpenPopup("ElementList");
      //    ImGui::SameLine();
      //    //ImGui::Text(curreBone.boneName.c_str());
      //  }
      //}
      ImGui::End();
    }
    if (m_showConsole) {
      ImGui::Begin("Console", &m_showConsole, ImGuiWindowFlags_MenuBar);
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
        ImGui::SameLine();
        ImGui::Text(m_logs[i].c_str());
      }
      ImGui::End();
    }
    */
    
  }

  void 
  BaseApp::cameraHerarchy() { 
    /*
    ImGui::Begin("Camera Manager");
    auto currCamera = m_cameraManager.GetActiveCamera();
    // Container for the camera manager
    auto Cameras = m_cameraManager.GetCameras();
    static char cameraInput[128] = "Camera Object";
    ImGui::Text("Set Active Camera");
    ImGui::Separator();
    ImGui::InputInt("Curr Cam", &m_currCamera);
    if (Cameras.size() >= 1) {
      m_cameraManager.SetActiveCamera(m_currCamera);
    }
    ImGui::Separator();
    ImGui::Text("Create Camera");
    ImGui::Separator();
    ImGui::InputText("->", cameraInput, IM_ARRAYSIZE(cameraInput));
    ImGui::SameLine();
    if (ImGui::Button("Add cam")) {
      m_cameraManager.AddCamera(cameraInput);

    }
    ImGui::Separator();
    ImGui::Text("Camera Herarchy");
    ImGui::Separator();
    for (uint32 i = 0; i < Cameras.size(); i++) {
      bool m_activeCamera = false;
      if (Cameras[i].m_isCameraActive) {
        m_activeCamera = true;
      }
      ImGui::Checkbox(" ", &m_activeCamera);
      ImGui::SameLine();
      ImGui::Text(Cameras[i].m_name.c_str());
      ImGui::SameLine();
      ImGui::Checkbox("Static", &currCamera.m_static);
      ImGui::Separator();
    }
    ImGui::End();
    */
  }

  void 
  BaseApp::loadInformation() {
    //m_resourceManager->getTextures()->push_back(RoughnessTex);
    // Load model
    String modelPath = m_saverMan.getString("UnrealChar");
    m_scene_graph.addGameObject(modelPath);
    m_scene_graph.setSelectedGO(0);
    // Load Textures
    String AlbedoTexPath = m_saverMan.getString("AlbedoTex");
    SPtr<buCoreTexture2D> AlbedoTex = m_graphicsAPI->loadImageFromFile(
      AlbedoTexPath, m_screenWidth, m_screenHeight, TextureType::E::DEFAULT);
    //m_scene_graph.getSelectedGO().m_textures.push_back(AlbedoTex);
    m_scene_graph.addTexToSelectedObj(AlbedoTex);
    //m_resourceManager->getTextures()->push_back(AlbedoTex);
    String NormalTexPath = m_saverMan.getString("NormalTex");
    SPtr<buCoreTexture2D> NormalTex = m_graphicsAPI->loadImageFromFile(
      NormalTexPath, m_screenWidth, m_screenHeight, TextureType::E::DEFAULT);
    //m_scene_graph.getSelectedGO().m_textures.push_back(NormalTex);
    m_scene_graph.addTexToSelectedObj(NormalTex);
    //m_resourceManager->getTextures()->push_back(NormalTex);
    String MetallicTexPath = m_saverMan.getString("MetallicTex");
    SPtr<buCoreTexture2D> MetallicTex = m_graphicsAPI->loadImageFromFile(
      MetallicTexPath, m_screenWidth, m_screenHeight, TextureType::E::DEFAULT);
    //m_scene_graph.getSelectedGO().m_textures.push_back(MetallicTex);
    m_scene_graph.addTexToSelectedObj(MetallicTex);
    //m_resourceManager->getTextures()->push_back(MetallicTex);
    String RoughnessTexPath = m_saverMan.getString("RoughnessTex");
    SPtr<buCoreTexture2D> RoughnessTex = m_graphicsAPI->loadImageFromFile(
      RoughnessTexPath, m_screenWidth, m_screenHeight, TextureType::E::DEFAULT);
    //m_scene_graph.getSelectedGO().m_textures.push_back(RoughnessTex);
    m_scene_graph.addTexToSelectedObj(RoughnessTex);
    //m_resourceManager->loadMesh(modelPath);
    // Load Mesh transform
    buVector3F tmpPos = m_saverMan.getFloatVec3("MeshPos");
    m_position[0] = tmpPos.x;
    m_position[1] = tmpPos.y;
    m_position[2] = tmpPos.z;

    buVector3F tmpRot = m_saverMan.getFloatVec3("MeshRot");
    m_Rotation[0] = tmpRot.x;
    m_Rotation[1] = tmpRot.y;
    m_Rotation[2] = tmpRot.z;

    buVector3F tmpSca = m_saverMan.getFloatVec3("MeshSca");
    m_Scale[0] = tmpSca.x;
    m_Scale[1] = tmpSca.y;
    m_Scale[2] = tmpSca.z;
  }

  void 
  BaseApp::saveInformation() {
    m_saverMan.cleanFileData();
    // Save the shader file

    // Save the camera settings
    // Save the Gameobject settings 
    // Model name
    m_saverMan.setString("UnrealChar", "Data/Models/character.dae");

    // Model transform
    m_saverMan.setFloatVec3("MeshPos", m_position);
    m_saverMan.setFloatVec3("MeshRot", m_Rotation);
    m_saverMan.setFloatVec3("MeshSca", m_Scale);
    // Model loaded textures
    m_saverMan.setString("AlbedoTex", "Data/Textures/Character/Albedo.jpeg");
    m_saverMan.setString("NormalTex", "Data/Textures/Character/Normal.jpeg");
    m_saverMan.setString("MetallicTex", "Data/Textures/Character/Metallic.jpeg");
    m_saverMan.setString("RoughnessTex", "Data/Textures/Character/Roughness.jpeg");

    // Save Shader textures
  }

  void
  BaseApp::shaderProperties() {
    /*
    // Container for shader attributes
    ImGui::Begin("Shaders");
    vec3Control("Light Pos", m_lightPos);
    vec3Control("Light color", m_LightColor);
    vec3Control("Surf color", m_surfColor);
    ImGui::SliderFloat("LightIntensity", &m_constants[0], 0, 10);
    ImGui::End();
    */
  }

  void
  BaseApp::vec3Control(String label, float*values, float resetValues, float columnWidth) {
    /*
    ImGui::PushID(label.c_str());
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3,ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0,0 });
    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    if (ImGui::Button("X", buttonSize)) {
      values[0] = resetValues;
    }
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values[0], 0.1f);
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    if (ImGui::Button("Y", buttonSize)) {
      values[1] = resetValues;
    }
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values[1], 0.1f);
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    if (ImGui::Button("Z", buttonSize)) {
      values[2] = resetValues;
    }
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values[2], 0.1f);
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();
    */
  }

  void 
  BaseApp::valControl(String label, float *values, float resetValues, float columnWidth) {
    /*
    ImGui::PushID(label.c_str());
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0,0 });
    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    if (ImGui::Button("X", buttonSize)) {
      values[0] = resetValues;
    }
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values[0], 0.1f);
    ImGui::PopItemWidth();

    
    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();
    */
  }

  void 
  BaseApp::cameraProperties(buCamera currCamera) {
    /*
    // Container for the camera inpector
    ImGui::Begin("Camera Inspector");
    //auto currCamera = m_cameraManager.GetActiveCamera();
    String CameraName = currCamera.m_name + "               ";
    ImGui::Checkbox(CameraName.c_str(), &currCamera.m_isCameraActive);
    ImGui::SameLine();
    ImGui::Checkbox("Static", &currCamera.m_static);
    ImGui::Separator();
    bool transformSettings = true;
    ImGui::Checkbox("Transform", &transformSettings);
    ImGui::Separator();
    vec3Control("Camera Pos", m_eye);
    
    vec3Control("Front", m_at);
    vec3Control("Up", m_up);
    ImGui::Separator();
    bool cameraSettings = true;
    ImGui::Checkbox("Camera", &cameraSettings);
    ImGui::Separator();
    const char* items[] = { "Projection", "Orthographic" };
    static int selectedItem = 0;
    ImGui::Combo("Projection", &selectedItem, items, IM_ARRAYSIZE(items));
    ImGui::ColorEdit4("Background", ClearColor);
    ImGui::SliderFloat("Near", &m_near, 3, 5);
    ImGui::SliderFloat("Far", &m_far, 0, 300);
    ImGui::End();
    */
  }

  void 
  BaseApp::login() {
    // Render the login screen until the correct initialization is made.
    if (m_initType == InitType::Default) {
      ImGui::Begin("Login");
      ImGui::Text("New Project Categories");

      if (ImGui::Button("Rendering", ImVec2(120, 30))) {
        // If the app initialize the Buzzshock Engine, fill the initType var
        m_initType = InitType::BuzzshockEngine;
        //loadInformation();
      }

      if (ImGui::Button("Start Buzzshock Connect", ImVec2(120, 30))) {
        // If the app initialize the Buzzshock Connect, fill the initType var
        m_initType = InitType::BuzzshockConnect;
      }
      ImGui::End();
    }
  }

  void 
  BaseApp::showConnectWindow() {
    auto& ConnectDirector = g_connectAPI();
    // Window in charge of being the main context of the other windows
    ImGui::Begin("Buzzshock Connect");
    
    ImGui::End();
    // Window in charge of initialize the Amazon Web Service (Servers)
    ImGui::Begin("Buzzshock Connect Server");
   
    String title = "Server initialization";
    ImGui::Text(title.c_str());
    ImGui::Separator();
    toggleButton("Basic", &m_isAdvanceServerInitialization);
    ImGui::SameLine();
    ImGui::Text("Basic / Advanced");
    ImGui::Separator();
    if (m_isAdvanceServerInitialization) {
      static char serverName[128] = "";
      static char path[128] = "";
      static char port[128] = "";
      static char address[128] = "";
      ImGui::InputTextWithHint("Server Name", "Enter the server name...", serverName, IM_ARRAYSIZE(serverName));
      ImGui::InputTextWithHint("Server Path", "Enter the server path...", path, IM_ARRAYSIZE(path));
      ImGui::InputTextWithHint("Server Port", "Enter the server port...", port, IM_ARRAYSIZE(port));
      ImGui::InputTextWithHint("Server Address", "Enter the server address...", address, IM_ARRAYSIZE(address));
      if (ImGui::Button("Submit")) {

      }
    }
    if (!m_isAdvanceServerInitialization) {
      static char Path[128] = "";
      ImGui::InputTextWithHint("Server Path", "Enter the server path...", Path, IM_ARRAYSIZE(Path));
      if (ImGui::Button("Submit")) {

      }
    }
    ImGui::End();
    // Window in charge of initialize the NVIDIA Omniverse Server
    ImGui::Begin("Omniverse Server");

    ImGui::End();
    // Window in charge of showing the files pass between multiples apps.
    ImGui::Begin("Server Data");
    ImGui::Text("Files in server");
    ImGui::End();
    // Window in charge of showing the Host and clients in Lobby/Sesion
    ImGui::Begin("Lobby");

    ImGui::Text(ConnectDirector.getLobbyName().c_str());
    ImGui::End();
    // Window in charge of showing the status of the AWS server and Omniverse Server
    ImGui::Begin("Server Status");
    String status = "Status: ";
    String msg = status + "Waiting connection";
    ImGui::Text(msg.c_str());

    ImGui::End();

  }


  void BaseApp::buGizmo(float* matrix)
  {
    static buMatrix4x4 identity = buMatrix4x4::IDENTITY;

    
    if (m_cameraManager.GetCameras().size() <= 0) {
      return;
    }

    auto view = m_cameraManager.GetActiveCamera().m_cameraData.view;
    view.transpose();
    auto proj = m_cameraManager.GetActiveCamera().m_cameraData.projection;
    proj.transpose();
    
    ImGuizmo::SetRect(0, 0, m_screenWidth, m_screenHeight);
    ImGuizmo::Manipulate(&view.m_x0, &proj.m_x0, mCurrentGizmoOperation, ImGuizmo::MODE::LOCAL, matrix, nullptr, nullptr, nullptr, nullptr);
    ImGui::Begin("Gizmos");
    if (ImGui::Button("T", ImVec2(40, 40))) {
      mCurrentGizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
    }
    ImGui::SameLine();
    if (ImGui::Button("R", ImVec2(40, 40))) {
      mCurrentGizmoOperation = ImGuizmo::OPERATION::ROTATE;
    }
    ImGui::SameLine();
    if (ImGui::Button("S", ImVec2(40, 40))) {
      mCurrentGizmoOperation = ImGuizmo::OPERATION::SCALE;
    }
    ImGui::End();
  }

  void 
  BaseApp::toggleButton(const char* str_id, bool* v) {
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f;
    float radius = height * 0.50f;

    if (ImGui::InvisibleButton(str_id, ImVec2(width, height)))
      *v = !*v;
    ImU32 col_bg;
    if (ImGui::IsItemHovered())
      col_bg = *v ? IM_COL32(145 + 20, 211, 68 + 20, 255) : IM_COL32(218 - 20, 218 - 20, 218 - 20, 255);
    else
      col_bg = *v ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);

    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
  }

  void 
  BaseApp::serializerUI() {
    ImGui::Begin("Serialization");
    if (ImGui::Button("Save")) {
      Vector<BYTE> buffer;
      uint32 spaceAval = 0;
      //spaceAval += m_saverMan.serializeVec3(scale, buffer);
      //spaceAval += m_saverMan.serializeVec3(position, buffer);
      m_saverMan.saveSerialization(buffer);
    }
    if (ImGui::Button("Load")) {
      Vector<BYTE> buffer;
      buffer = m_saverMan.getSerialization();
      RTTIEmptyType<buVector3F> obj;
      buVector3F pos;
      obj.fromMemory(pos, buffer.data());
    }
    ImGui::End();
  }

  void 
  BaseApp::serverCURLUI() {
    ImGui::Begin("Server");
    if (ImGui::Button("Store current position")) {
      //m_json.writePositions(position);
      m_json.createBuf();
    }
    ImGui::Text("----- Json Buffer -----");
    ImGui::Text(m_json.m_buffer.c_str());

    if (ImGui::Button("POST")) {
      m_curl.post("http://localhost:9200/mytutorialindex/message?pretty", m_json.m_buffer.data());
    }

    if (ImGui::Button("GET")) {
      m_curl.get("http://localhost:9200/mytutorialindex/_search?pretty");
    }

    ImGui::End();
  }

  void 
  BaseApp::toolsUI() {
    ImGui::Begin("Tools");
    if (ImGui::Button("Load", ImVec2(40,40))) {
      m_isDataLoaded = true;
      loadInformation();
    }
    ImGui::SameLine();
    if (ImGui::Button("Save GO", ImVec2(40, 40))) {
      m_saverMan.saveGO(&m_scene_graph.getSelectedGO());
    }
    ImGui::SameLine();
    if (ImGui::Button("Load Maya GO", ImVec2(40, 40))) {
      m_scene_graph.addMayaGameObject();
      m_scene_graph.setSelectedGO(0);
    }
    ImGui::End();
  }

  void 
  BaseApp::changeLogUI() {
    ImGui::Begin("Change Log");
    for (auto log : m_logs) {
      ImGui::Text(log.c_str());
    }
    ImGui::End();
  }

  LRESULT
  BaseApp::handelWindowEvent(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam) {
    /*
    //*/
    if ( ImGui_ImplWin32_WndProcHandler(Hw, Msg, wParam, lParam)) {
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

  void 
  BaseApp::Log(String _log) {
    m_logs.push_back(_log);
  }
}
