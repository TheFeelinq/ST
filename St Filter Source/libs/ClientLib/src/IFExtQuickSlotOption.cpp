#include "IFExtQuickSlotOption.h"
#include "GInterface.h"
#include "BSLib/Debug.h"
#include <remodel/MemberFunctionHook.h>

GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFExtQuickSlotOption, 0x00ee9a48)

GFX_IMPLEMENT_DYNCREATE_FN(CIFExtQuickSlotOption, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFExtQuickSlotOption, CIFMainFrame)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_OK_BTN, &CIFExtQuickSlotOption::OnClickConfirm)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_APPLY_BTN, &CIFExtQuickSlotOption::ApplyExtQSSetting)
GFX_END_MESSAGE_MAP()

undefined1 CIFExtQuickSlotOption::OnCloseWnd() {
    return g_pCGInterface->GetExtQuickSlot()->ToggleExtQuickSlotOption(false);
}

HOOK_ORIGINAL_MEMBER(0x0065f800, &CIFExtQuickSlotOption::SetCheckBoxState)
void CIFExtQuickSlotOption::SetCheckBoxState(bool bTrasnpearnt, bool bSlotsLocked, bool bToolBarLocked,
                                             bool bTwoLines) {
    BS_DEBUG_LOW("%s </(Transpearnt %d, SlotsLocked %d, BarLocked %d, TwoLines %d)/>", __FUNCTION__, bTrasnpearnt,
                 bSlotsLocked, bToolBarLocked, bTwoLines)
    m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_OPT_TRANS_CHECKBOX, 1)->FUN_00656d50(bTrasnpearnt);
    m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_OPT_LOCK_CHECKBOX, 1)->FUN_00656d50(bSlotsLocked);
    m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_OPT_FIX_CHECKBOX, 1)->FUN_00656d50(bToolBarLocked);
    m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_OPT_DOUBLELINE_CHECKBOX, 1)->FUN_00656d50(bTwoLines);
}

void CIFExtQuickSlotOption::ApplyExtQSSetting() {
    g_pCGInterface->GetExtQuickSlot()->SetBarTransparentState(
            m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_OPT_TRANS_CHECKBOX, 1)->GetCheckedState_MAYBE());
    g_pCGInterface->GetExtQuickSlot()->SetSlotLockState(
            m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_OPT_LOCK_CHECKBOX, 1)->GetCheckedState_MAYBE());
    g_pCGInterface->GetExtQuickSlot()->SetBarLockState(
            m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_OPT_FIX_CHECKBOX, 1)->GetCheckedState_MAYBE());
    g_pCGInterface->GetExtQuickSlot()->SetBarTwoLinesState(
            m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_OPT_DOUBLELINE_CHECKBOX, 1)->GetCheckedState_MAYBE());
    g_pCGInterface->GetExtQuickSlot()->UpdateSlotsBarDirection();
}

void CIFExtQuickSlotOption::OnClickConfirm() {
    ApplyExtQSSetting();
    this->OnCloseWnd();
}

bool CIFExtQuickSlotOption::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);
    m_IRM.LoadFromFile("resinfo\\ifextquickslotoption.txt");
    m_IRM.CreateInterfaceSection("Create", this);

    return true;
}
