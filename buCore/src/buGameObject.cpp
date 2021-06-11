#include "buGameObject.h"
#include <imgui\imGuiDocking\imgui_internal.h>
namespace buEngineSDK {
  buGameObject::~buGameObject()
  {
  }
  void
  buGameObject::init() {
    auto& graphMan = g_graphicsAPI();
    // Create Change Every Frame
    changeEveryFrame = graphMan.createBuffer(sizeof(CBChangesEveryFrame));
    pos = new float[3];
    rot = new float[3];
    sca = new float[3];

    pos[0] = 0;
    pos[1] = 60;
    pos[2] = 0;

    rot[0] = 0;
    rot[1] = 1;
    rot[2] = 0;

    sca[0] = 50;
    sca[1] = 50;
    sca[2] = 50;

    m_angle = new float[1];
    m_angle[0] = 0;
  }

  void
  buGameObject::update(buVector3F _pos, buVector3F _rot,
                       buVector3F _scal, float _angle) {
    auto& graphMan = g_graphicsAPI();
    //m_pos = _pos;

    pos[0] = _pos.x;
    pos[1] = _pos.y;
    pos[2] = _pos.z;
    
    rot[0] = _rot.x;
    rot[1] = _rot.y;
    rot[2] = _rot.z;

    sca[0] = _scal.x;
    sca[1] = _scal.y;
    sca[2] = _scal.z;
    buVector3F newPos(pos[0], pos[1], pos[2]);
    buVector3F newRot(rot[0], rot[1], rot[2]);
    buVector3F newSca(sca[0], sca[1], sca[2]);

    //m_rot = _rot;
    //m_sca = _scal;
    //m_angle = _angle;
    m_transform.update(newPos, newRot, newSca, m_angle[0]);
    cb.mWorld = m_transform.m_world;
    graphMan.updateSubresource(changeEveryFrame, 0, nullptr, &cb, 0, 0);
    
  }

  void
  buGameObject::render(TopologyType::E _typology) {
    auto& graphMan = g_graphicsAPI();

    // Set change every frame constant buffers
    graphMan.VSsetConstantBuffers(changeEveryFrame, 1, 1);

    

    //graphMan.VSsetConstantBuffers(m_lightBuffer, 3, 1);
    
    // Set change every frame buffer.
    graphMan.PSsetConstantBuffers(changeEveryFrame, BufferSlot::E::WORLD, 1);
    // Render if the go is active
    if (m_isActive) {
      for (uint32 i = 0; i < m_model.m_meshes.size(); ++i) {
        auto& currMesh = m_model.m_meshes[i];
        // Set Mesh texture
        for (uint32 j = 0; j < m_textures.size(); j++) {
          auto& currTexture = m_textures[j];
          graphMan.PSSetShaderResources(currTexture, j, 1);
        }
        // Set primitive topology
        graphMan.setPrimitiveTopology(_typology);
        // Set vertex buffer
        graphMan.setVertexBuffers(m_model.m_vertexBuffer);
        // Set Index buffer
        graphMan.setIndexBuffer(m_model.m_indexBuffer,
                                Format::E::BU_FORMAT_R32_UINT,
                                0);
        // Draw
        graphMan.drawIndexed(currMesh.m_numIndices, currMesh.m_baseIndex, 0);
      }

    }
  }
  
  void 
  buGameObject::drawUI() {
    ImGui::Begin("Properties");
    ImGui::Checkbox(" ", &m_isUsed);
    static char str1[128] = "";
    ImGui::SameLine();
    ImGui::InputTextWithHint(" ", m_name.c_str(), str1, IM_ARRAYSIZE(str1));
    ImGui::Separator();
    // Draw transform ui
    m_transform.ui(pos, rot, sca, m_angle);

    if (ImGui::Button("Add Component")) {

    }    

    ImGui::End();

  }


  void
  buGameObject::vec3Control(String label, float* values, float resetValues, float columnWidth) {
    
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


    
  }
}