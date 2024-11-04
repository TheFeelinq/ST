#include "ColorPicker.h"
#include <GInterface.h>

void ColorSelect::Render() {
    if(!g_pCICPlayer)
        return;
    if(g_pCICPlayer && !g_pCGInterface->GetCustomTitleGUI()->IsVisible() )
        return;
    if(!g_pCGInterface->GetCustomTitleGUI()->ColorSelectShow)
        return;
    ImGui::SetNextWindowSize(ImVec2(130,108));
    if (!ImGui::Begin("thaidu0ng",0, ImGuiWindowFlags_NoMove| ImGuiWindowFlags_NoTitleBar |ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }
    ImGui::ColorPicker3("Color", m_color, ImGuiColorEditFlags_None | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoTooltip |ImGuiColorEditFlags_NoLabel |ImGuiColorEditFlags_NoDragDrop |ImGuiColorEditFlags_RGB|ImGuiColorEditFlags_HSV );
    ImGuiStyle* style = &ImGui::GetStyle();
    style->Colors[ImGuiCol_TitleBg] = ImColor(0,0,0,130);
    style->Colors[ImGuiCol_TitleBgActive] = ImColor(0,0,0,130);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0,0,0,130);
    int red = static_cast<int>(m_color[0] * 255.0f);
    int green = static_cast<int>(m_color[1] * 255.0f);
    int blue = static_cast<int>(m_color[2] * 255.0f);
    D3DCOLOR TitleColor = D3DCOLOR_ARGB(255, red, green, blue);
    if(g_pCICPlayer)
    {
        ImGui::SetWindowPos("thaidu0ng",ImVec2(g_pCGInterface->GetCustomTitleGUI()->GetPos().x + 370,g_pCGInterface->GetCustomTitleGUI()->GetPos().y + 85));
        g_pCGInterface->GetCustomTitleGUI()->OnColorSelect(TitleColor);
    }

    ImGui::End();
}
