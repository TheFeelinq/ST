//
// Created by Admin on 12/5/2021.
//

#include "IFSlotWithHelpForPackage.h"
#include "IFHelperBubbleWindow.h"
#include "GInterface.h"
#include "IFMainPopup.h"
#include "IFEquipment.h"
#include "SOItem.h"
#include "ObjectData.h"

void CIFSlotWithHelpForPackage::ChangeColorPrice(CIFHelperBubbleWindow* window) {
    reinterpret_cast<void (__thiscall *)(CIFSlotWithHelpForPackage *, CIFHelperBubbleWindow *)>(0x006784a0)(this, window);
    CIFHelperBubbleWindow *main1 = g_pCGInterface->m_IRM.GetResObj<CIFHelperBubbleWindow>(97, 1);
    wchar_t buffers[255] = L"ThaiDu0ngPr0";
    std::n_wstring strmsg(buffers);
     main1->m_textBox->sub_64F8A0(strmsg, 0, D3DCOLOR_RGBA(255, 255, 0, 0), D3DCOLOR_RGBA(255, 255, 0, 0), -1, 0, 0);
}
