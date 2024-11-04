#include "ItemData.h"

#include <GlobalDataManager.h>
#include <imgui/imgui.h>
#include <EntityManagerClient.h>
#include <Rebot.h>
#include <IFSTPetFilter.h>
#include <IFflorian0Guide.h>
#include <algorithm>
#include <ctime>
void ItemData::MenuItem() {
    ImGui::MenuItem("Item Data", 0, &bShow);
}

void ItemData::Render() {

    if (!bShow) return;

    if (!ImGui::Begin("Item Data", &bShow)) {
        ImGui::End();
        return;
    }
    static int id = 0;
    static const CItemData *data = NULL;
    //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    data = g_CGlobalDataManager->GetItemData(id);

    if (ImGui::InputInt("ID", &id)) {
        // Update
        data = g_CGlobalDataManager->GetItemData(id);
    }

    if (data != NULL) {
        ImGui::LabelText("CodeName", "%ls", data->m_codeName128.c_str());
        ImGui::LabelText("m_id", "%d", data->m_id);
        ImGui::LabelText("TID", "%d", data->TID);
        ImGui::LabelText("m_itemClass", "%d", data->m_itemClass);
        ImGui::LabelText("m_reqLevel1", "%d", data->m_reqLevel1);
        ImGui::LabelText("m_reqLevelType1", "%d", data->m_reqLevelType1);
        ImGui::LabelText("m_reqLevel2", "%d", data->m_reqLevel2);
        ImGui::LabelText("m_reqLevelType2", "%d", data->m_reqLevelType2);
        ImGui::LabelText("m_scale", "%d", data->m_scale);
        ImGui::LabelText("m_bcHeight", "%d", data->m_bcHeight);
        ImGui::LabelText("m_bcRadius", "%d", data->m_bcRadius);
        ImGui::LabelText("m_eventId", "%d", data->m_eventId);
        ImGui::LabelText("m_reqGender", "%d", data->m_reqGender);
        ImGui::LabelText("m_param1", "%d", data->m_param1);
    }

    ImGui::End();
}
