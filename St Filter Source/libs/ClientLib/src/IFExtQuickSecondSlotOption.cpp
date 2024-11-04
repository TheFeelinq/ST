//
// Created by Admin on 1/3/2022.
//

#include "GInterface.h"
#include "Game.h"



GFX_IMPLEMENT_DYNCREATE(CIFExtQuickSecondSlotOption, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFExtQuickSecondSlotOption, CIFMainFrame)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_SECOND_OK_BTN, &CIFExtQuickSecondSlotOption::OnClickConfirm)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_SECOND_APPLY_BTN, &CIFExtQuickSecondSlotOption::ApplyExtQSSetting)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_SECOND_OPT_TRANS_CHECKBOX, &CIFExtQuickSecondSlotOption::OnOptionChanged)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_SECOND_OPT_LOCK_CHECKBOX, &CIFExtQuickSecondSlotOption::OnOptionChanged)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_SECOND_OPT_FIX_CHECKBOX, &CIFExtQuickSecondSlotOption::OnOptionChanged)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_SECOND_OPT_DOUBLELINE_CHECKBOX, &CIFExtQuickSecondSlotOption::OnOptionChanged)
GFX_END_MESSAGE_MAP()

void CIFExtQuickSecondSlotOption::SetCheckBoxState(bool bTrasnpearnt, bool bSlotsLocked, bool bToolBarLocked,
                                             bool bTwoLines) {
    //BS_DEBUG_LOW("%s </(Transpearnt %d, SlotsLocked %d, BarLocked %d, TwoLines %d)/>", __FUNCTION__, bTrasnpearnt,
     //            bSlotsLocked, bToolBarLocked, bTwoLines)
    m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_SECOND_OPT_TRANS_CHECKBOX, 1)->FUN_00656d50(bTrasnpearnt);
    m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_SECOND_OPT_LOCK_CHECKBOX, 1)->FUN_00656d50(bSlotsLocked);
    m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_SECOND_OPT_FIX_CHECKBOX, 1)->FUN_00656d50(bToolBarLocked);
    m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_SECOND_OPT_DOUBLELINE_CHECKBOX, 1)->FUN_00656d50(bTwoLines);
}

void CIFExtQuickSecondSlotOption::ApplyExtQSSetting() {
    g_pCGInterface->GetExtQuickSecondSlot()->SetBarTransparentState(
            m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_SECOND_OPT_TRANS_CHECKBOX, 1)->GetCheckedState_MAYBE());
    g_pCGInterface->GetExtQuickSecondSlot()->SetSlotLockState(
            m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_SECOND_OPT_LOCK_CHECKBOX, 1)->GetCheckedState_MAYBE());
    g_pCGInterface->GetExtQuickSecondSlot()->SetBarLockState(
            m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_SECOND_OPT_FIX_CHECKBOX, 1)->GetCheckedState_MAYBE());
    g_pCGInterface->GetExtQuickSecondSlot()->SetBarTwoLinesState(
            m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_SECOND_OPT_DOUBLELINE_CHECKBOX, 1)->GetCheckedState_MAYBE());
    g_pCGInterface->GetExtQuickSecondSlot()->UpdateSlotsBarDirection();
}

void CIFExtQuickSecondSlotOption::OnClickConfirm() {
    ApplyExtQSSetting();
    this->OnCloseWnd();
}

bool CIFExtQuickSecondSlotOption::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);
    TB_Func_13("interface\\frame\\mall_ms_wnd_", 1, 0);
    m_IRM.LoadFromFile("resinfo\\ifextquickslotsecondoption.txt");
    m_IRM.CreateInterfaceSection("Create", this);

    m_GDR_EXT_QUICKSLOT_SECOND_OPT_TRANS_CHECKBOX = m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_SECOND_OPT_TRANS_CHECKBOX, 1);
    m_GDR_EXT_QUICKSLOT_SECOND_OPT_LOCK_CHECKBOX = m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_SECOND_OPT_LOCK_CHECKBOX, 1);
    m_GDR_EXT_QUICKSLOT_SECOND_OPT_FIX_CHECKBOX = m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_SECOND_OPT_FIX_CHECKBOX, 1);
    m_GDR_EXT_QUICKSLOT_SECOND_OPT_DOUBLELINE_CHECKBOX = m_IRM.GetResObj<CIFCheckBox>(GDR_EXT_QUICKSLOT_SECOND_OPT_DOUBLELINE_CHECKBOX, 1);
    this->ShowGWnd(false);
    char buffer[0x200];
    sprintf_s(buffer, "%s\\Setting\\SROptionSetSec.dat", theApp.GetWorkingDir());

    FILE *file = fopen(buffer, "rb+");
    if (file == NULL) {
        m_GDR_EXT_QUICKSLOT_SECOND_OPT_TRANS_CHECKBOX->FUN_00656d50(false);
        return true;
    }

    char config[4];
    fread_s(&config[0], sizeof(config), 1, 4, file);

    m_GDR_EXT_QUICKSLOT_SECOND_OPT_TRANS_CHECKBOX->FUN_00656d50(config[0] != 0);
    m_GDR_EXT_QUICKSLOT_SECOND_OPT_LOCK_CHECKBOX->FUN_00656d50(config[1] != 0);
    m_GDR_EXT_QUICKSLOT_SECOND_OPT_FIX_CHECKBOX->FUN_00656d50(config[2] != 0);
    m_GDR_EXT_QUICKSLOT_SECOND_OPT_DOUBLELINE_CHECKBOX->FUN_00656d50(config[3] != 0);

    fclose(file);


    return true;
}
void CIFExtQuickSecondSlotOption::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}
void CIFExtQuickSecondSlotOption::OnOptionChanged() {
    char buffer[0x200];
    sprintf_s(buffer, "%s\\Setting\\SROptionSetSec.dat", theApp.GetWorkingDir());

    FILE *file = fopen(buffer, "wb+");
    if (file != NULL) {
        bool data[4];
        data[0] = m_GDR_EXT_QUICKSLOT_SECOND_OPT_TRANS_CHECKBOX->GetCheckedState_MAYBE();
        data[1] = m_GDR_EXT_QUICKSLOT_SECOND_OPT_LOCK_CHECKBOX->GetCheckedState_MAYBE();
        data[2] = m_GDR_EXT_QUICKSLOT_SECOND_OPT_FIX_CHECKBOX->GetCheckedState_MAYBE();
        data[3] = m_GDR_EXT_QUICKSLOT_SECOND_OPT_DOUBLELINE_CHECKBOX->GetCheckedState_MAYBE();
        fwrite(&data[0], 1, 4, file);
        fclose(file);
    }
}
