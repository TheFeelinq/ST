//
// Created by Admin on 24/12/2021.
//

#include <ICPlayer.h>
#include <IFflorian0Guide.h>
#include <IFChatViewer.h>
#include <GInterface.h>
#include "FPSViewer.h"
#include "IFSTStreamSetting.h"
void FPSViewer::Render() {
    if(!g_pCICPlayer)
        return;

    if(!g_pCGInterface->GetStreamSettingGUI()->m_fps_show_checked())
        return;
    ImGui::SetNextWindowSize(ImVec2(75,18));
    if (!ImGui::Begin("fpsviewer",0, ImGuiWindowFlags_NoMove| ImGuiWindowFlags_NoTitleBar |ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize ))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }
    ImGui::Text("%.1f FPS",  ImGui::GetIO().Framerate);
    CIFChatViewer* Chatview = reinterpret_cast<CIFChatViewer*>(g_pCGInterface->m_IRM.GetResObj(1, 1));
    if(g_pCICPlayer)
    {
        ImGui::SetWindowPos("fpsviewer",ImVec2(Chatview->GetPos().x + 60,Chatview->GetPos().y + 190));
    }

    ImGui::End();
}
