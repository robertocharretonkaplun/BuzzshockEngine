#include "buLight.h"
#include <imgui\imGuiDocking\imgui_internal.h>

namespace buEngineSDK {
  void
  buLight::init() {
    auto& graphMan = g_graphicsAPI();
    m_lightBuffer = graphMan.createBuffer(sizeof(LightBuffer));
    m_pos = new float[3];

    m_pos[0] = -30.0f;
    m_pos[1] = 85;
    m_pos[2] = -50.0f;
  }

  void
  buLight::update(LightBuffer _lb){
    LB = _lb;
    LB.LightPos.x = m_pos[0];
    LB.LightPos.y = m_pos[1];
    LB.LightPos.z = m_pos[2];
    auto& graphMan = g_graphicsAPI();
    graphMan.updateSubresource(m_lightBuffer, 0, nullptr, &LB, 0, 0);

    drawUI();
  }

  void
  buLight::render() {
    auto& graphMan = g_graphicsAPI();
    graphMan.PSsetConstantBuffers(m_lightBuffer, BufferSlot::E::LIGHT, 1);
  }

  void
  buLight::drawUI() {
    ImGui::Begin("Light Properties");
    //ImGui::Checkbox(" ", &m_isUsed);
    //ImGui::SameLine();
    ImGui::Text("Light");
    ImGui::Separator();


    vec3Control("Position", m_pos);
    //vec3Control("Position", pos);
    ImGui::Separator();
    ImGui::End();
  }

  void
  buLight::vec3Control(String label, float* values, float resetValues, float columnWidth) {
    
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