#include "IFExtQuickSlot.h"
#include "GInterface.h"
#include "Game.h"
#include "IFExtQuickSlotSlot.h"
#include "BSLib/Debug.h"
#include "IFExtQuickSlotOption.h"
#include <remodel/MemberFunctionHook.h>

GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFExtQuickSlot, 0x00ee9a28)

GFX_IMPLEMENT_DYNCREATE_FN(CIFExtQuickSlot, CIFWnd)

GFX_BEGIN_MESSAGE_MAP(CIFExtQuickSlot, CIFWnd)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_OPT_BTN, &CIFExtQuickSlot::OnToggleSlotsOption)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_ONOFF_BTN, &CIFExtQuickSlot::OnDropDownButton)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_HORI_BTN, &CIFExtQuickSlot::OnClickSlotsHorizontal)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_VERT_BTN, &CIFExtQuickSlot::OnClickSlotsVertical)
GFX_END_MESSAGE_MAP()

CIFExtQuickSlot::CIFExtQuickSlot() :
        m_bVertical(false),
        m_bTwoLines(false),
        m_bTransparent(false),
        m_bSlotsLocked(false),
        m_bToolBarLocked(false),
        m_pMyUnerMenuBar(NULL) {
    m_bSlotsVisible = true;
    m_SectionTypeID = 255;
}

HOOK_ORIGINAL_MEMBER(0x0065e8d0, &CIFExtQuickSlot::SetBarVerticalState)

void CIFExtQuickSlot::SetBarVerticalState(bool bState) {
    m_bVertical = bState;
}

HOOK_ORIGINAL_MEMBER(0x0065e8e0, &CIFExtQuickSlot::SetBarTransparentState)
void CIFExtQuickSlot::SetBarTransparentState(bool bState) {
    m_bTransparent = bState;
}

HOOK_ORIGINAL_MEMBER(0x0065e8f0, &CIFExtQuickSlot::SetSlotLockState)
void CIFExtQuickSlot::SetSlotLockState(bool bState) {
    m_bSlotsLocked = bState;
}

HOOK_ORIGINAL_MEMBER(0x0065e900, &CIFExtQuickSlot::SetBarLockState)
void CIFExtQuickSlot::SetBarLockState(bool bState) {
    m_bToolBarLocked = bState;
}

HOOK_ORIGINAL_MEMBER(0x0065e910, &CIFExtQuickSlot::SetBarTwoLinesState)
void CIFExtQuickSlot::SetBarTwoLinesState(bool bState) {
    m_bTwoLines = bState;
}

void CIFExtQuickSlot::SaveExtSlotSetting() {
    char buffer[0x200];
    sprintf_s(buffer, "%s\\Setting\\SRExtQSOption.dat", theApp.GetWorkingDir());

    FILE* file = fopen(buffer, "wb+");

    int local_208 = 1; //hmm setting is saved? // or Config type?
    if (file) {
        bool data[6];
        fwrite(&local_208, 4, 1, file);
        data[0] = m_bSlotsVisible;
        data[1] = m_bVertical;
        data[2] = m_bTwoLines;
        data[3] = m_bTransparent;
        data[4] = m_bSlotsLocked;
        data[5] = m_bToolBarLocked;
        fwrite(&data[0], 1, 6, file);
        fclose(file);
    }
}

CIFExtQuickSlot::~CIFExtQuickSlot() {
    SaveExtSlotSetting();
}

undefined1 CIFExtQuickSlot::ToggleExtQuickSlotOption(bool bVisible) {
    return reinterpret_cast<undefined1 (__thiscall *)(CIFExtQuickSlot *, bool)>(0x0065eb10)(this, bVisible);
}

void CIFExtQuickSlot::SetSlotsVisible(bool bVisible) {
    m_bSlotsVisible = bVisible;

    if (m_SectionTypeID == NULL || m_SectionTypeID == SECTION_TYPE_1) {
        if (!bVisible)
            m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_ONOFF_BTN, 1)->TB_Func_13(
                    "interface\\quick_slot\\qsl_hopen_button.ddj", NULL, NULL);
        else
            m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_ONOFF_BTN, 1)->TB_Func_13(
                    "interface\\quick_slot\\qsl_hclose_button.ddj", NULL, NULL);
    } else {
        if (!bVisible)
            m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_ONOFF_BTN, 1)->TB_Func_13(
                    "interface\\quick_slot\\qsl_vopen_button.ddj", NULL, NULL);
        else
            m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_ONOFF_BTN, 1)->TB_Func_13(
                    "interface\\quick_slot\\qsl_vclose_button.ddj", NULL, NULL);
    }

    if (m_SectionTypeID == NULL || m_SectionTypeID == SECTION_TYPE_2) {
        for (int iVar4 = 30, iVar2 = 10; iVar2 != NULL; iVar4++, iVar2--) {
            m_IRM.GetResObj<CIFExtQuickSlotSlot>(70 + iVar4, 1)->ShowGWnd(m_bSlotsVisible);
            m_IRM.GetResObj<CIFExtQuickSlotSlot>(iVar4, 1)->ShowGWnd(m_bSlotsVisible);
        }
    } else if (m_SectionTypeID == SECTION_TYPE_1 || m_SectionTypeID == SECTION_TYPE_3) {
        for (int iVar4 = 0; iVar4 < 10; iVar4++) {
            m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar4, 1)->ShowGWnd(m_bSlotsVisible);
            if (iVar4 < 5)
                m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_BOARD_1 + iVar4, 1)->ShowGWnd(
                        m_bSlotsVisible);
        }
    }

    m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_END, 1)->ShowGWnd(m_bSlotsVisible);
}

void CIFExtQuickSlot::OnToggleSlotsOption() {
    ToggleExtQuickSlotOption(!m_IRM.GetResObj<CIFExtQuickSlotOption>(GDR_EXT_QUICKSLOT_OPTION, 1));
}

void CIFExtQuickSlot::OnDropDownButton() {
    SetSlotsVisible(!m_bSlotsVisible);
}

void CIFExtQuickSlot::ClearChildofSlot() {
    reinterpret_cast<void(__thiscall*)(CIFExtQuickSlot*)>(0x0065eef0)(this);
#if 0
    for (int iVar2 = 0; iVar2 < 10; iVar2++) {
        m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar2,
            1)->GetSlotUnderBarBySlothgWnd()->FUN_006871d0(NULL);
        m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar2,
            1)->GetSlotUnderBarBySlothgWnd()->TB_Func_13("", NULL, NULL);
    }
#endif
}

void CIFExtQuickSlot::UpdateBarSlotsStyle() {
    short Sections = NULL;

    if (!m_bVertical && m_bTwoLines)
        Sections = SECTION_TYPE_1;
    else if (m_bVertical && !m_bTwoLines)
        Sections = SECTION_TYPE_2;
    else if (m_bTwoLines)
        Sections = SECTION_TYPE_3;

    if (Sections == m_SectionTypeID) {
        for (int iVar5 = NULL; iVar5 < 10; iVar5++)
            m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar5, 1)->UpdatehgWndSlot(
                    m_pMyUnerMenuBar->m_slots[40 + iVar5]->m_main_slot);
    }

    if (m_SectionTypeID == NULL)
        m_IRM.DeleteCreatedSection("Type1");
    else if (m_SectionTypeID != SECTION_TYPE_4)
        m_IRM.DeleteCreatedSection("Type4");

    if (Sections == NULL)
        m_IRM.CreateInterfaceSection("Type1", this);
    else if (Sections == SECTION_TYPE_1)
        m_IRM.CreateInterfaceSection("Type2", this);
    else if (Sections == SECTION_TYPE_2)
        m_IRM.CreateInterfaceSection("Type3", this);
    else
        m_IRM.CreateInterfaceSection("Type4", this);

    wnd_size dragsz = m_IRM.GetResObj(GDR_EXT_QUICKSLOT_WND, 1)->GetSize();
    this->SetGWndSize(dragsz.width, dragsz.height);
    wnd_pos barps = this->GetPos();

    m_SectionTypeID = Sections;
    switch (m_SectionTypeID) {
        case SECTION_TYPE_1: {
            int v32 = NULL;
            for (int iVar5 = NULL; iVar5 < 10; iVar5++) {
                CIFExtQuickSlotSlot* extslot = m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar5,
                                                                                    1);
                extslot->UpdatehgWndSlot(
                        m_pMyUnerMenuBar->m_slots[40 + iVar5]->m_main_slot);
                if (iVar5 >= 5)
                    extslot->MoveGWnd(v32 + (barps.x - 149), barps.y + 40);
                else
                    extslot->MoveGWnd(v32 + (barps.x + 31), barps.y + 4);
                v32 += 36;
            }
            break;
        } case SECTION_TYPE_2: {
            int v32 = NULL;
            for (int iVar5 = NULL; iVar5 < 10; iVar5++) {
                CIFExtQuickSlotSlot* extslot = m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar5,
                                                                                    1);
                extslot->UpdatehgWndSlot(
                        m_pMyUnerMenuBar->m_slots[40 + iVar5]->m_main_slot);
                extslot->MoveGWnd(barps.x + 5, v32 + (barps.y + 43));
                v32 += 36;
            }
            break;
        } case SECTION_TYPE_3: {
            int v32 = NULL;
            for (int iVar5 = NULL; iVar5 < 10; iVar5++) {
                CIFExtQuickSlotSlot* extslot = m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar5,
                                                                                    1);
                extslot->UpdatehgWndSlot(
                        m_pMyUnerMenuBar->m_slots[40 + iVar5]->m_main_slot);
                if (iVar5 >= 5)
                    extslot->MoveGWnd(barps.x + 41, v32 + (barps.y - 149));
                else
                    extslot->MoveGWnd(barps.x + 5, v32 + (barps.y + 31));
                v32 += 36;
            }
            break;
        } default: {
            for (int iVar5 = NULL; iVar5 < 10; iVar5++) {
                int v32 = NULL;
                CIFExtQuickSlotSlot* extslot = m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar5,
                                                                                    1);
                extslot->UpdatehgWndSlot(
                        m_pMyUnerMenuBar->m_slots[40 + iVar5]->m_main_slot);
                extslot->MoveGWnd(v32 + (barps.x + 43), barps.y + 4);
                v32 += 36;
            }
            break;
        }
    }

    SetSlotsVisible(m_bSlotsVisible);
}

void CIFExtQuickSlot::UpdateSlotsBarDirection() {
    UpdateBarSlotsStyle();

    char N00009BB9 = -1;

    if (m_bTransparent)
        N00009BB9 = 110;

    m_IRM.GetResObj<CIFDragableArea>(GDR_EXT_QUICKSLOT_WND, 1)->TB_Func_9(N00009BB9);
    m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_OPT_BTN, 1)->TB_Func_9(N00009BB9);
    m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_HORI_BTN, 1)->TB_Func_9(N00009BB9);
    m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_VERT_BTN, 1)->TB_Func_9(N00009BB9);
    m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_ONOFF_BTN, 1)->TB_Func_9(N00009BB9);

    if (!m_bSlotsVisible)
        return;

    m_IRM.GetResObj(GDR_EXT_QUICKSLOT_SLOT_END, 1)->TB_Func_9(N00009BB9);

    if (m_SectionTypeID == NULL || m_SectionTypeID == SECTION_TYPE_2) {
        for (int v22 = 10, v14 = 30; v22 != NULL; v14++, v22--) {
            m_IRM.GetResObj(v14 + 70, 1)->TB_Func_9(N00009BB9);
            m_IRM.GetResObj(v14, 1)->TB_Func_9(N00009BB9);
        }
    } else if (m_SectionTypeID == SECTION_TYPE_1 || m_SectionTypeID == SECTION_TYPE_3) {
        for (int v11 = NULL; v11 < 10; v11++) {
            m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + v11, 1)->TB_Func_9(N00009BB9);
            if (v11 < 5)
                m_IRM.GetResObj<CIFStatic>(GDR_EXT_QUICKSLOT_SLOT_BOARD_1 + v11, 1)->TB_Func_9(N00009BB9);
        }
    }

    for (int v17 = NULL; v17 < 10; v17++) {
        m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + v17, 1)->SetDragable(!m_bSlotsLocked);
    }

    m_IRM.GetResObj<CIFDragableArea>(GDR_EXT_QUICKSLOT_WND, 1)->SetClickable(!m_bToolBarLocked);
}

void CIFExtQuickSlot::LoadExtSlotSetting() {
    char buffer[0x200];

    sprintf_s(buffer, "%s\\Setting\\SRExtQSOption.dat", theApp.GetWorkingDir());

    FILE *file = fopen(buffer, "rb");

    int local_210; // Config type?
    if (!file) {
        SetBarVerticalState(true);
        SetBarTransparentState(true);
        SetSlotLockState(false);
        SetBarLockState(false);
        SetBarTwoLinesState(true);
    } else {
        fread_s(&local_210, -1, 4, 1, file);
        if (local_210 == 1) {
            bool config[6];

            fread_s(&config[0], sizeof(config), 1, 6, file);
            m_bSlotsVisible = config[0];
            SetBarVerticalState(config[1]);
            SetBarTransparentState(config[2]);
            SetSlotLockState(config[3]);
            SetBarLockState(config[4]);
            SetBarTwoLinesState(config[5]);
        }
        fclose(file);
    }
    UpdateSlotsBarDirection();
}

void CIFExtQuickSlot::OnClickSlotsHorizontal() {
    SetBarVerticalState(false);
    UpdateSlotsBarDirection();
}

void CIFExtQuickSlot::OnClickSlotsVertical() {
    SetBarVerticalState(true);
    UpdateSlotsBarDirection();
}

bool CIFExtQuickSlot::OnCreate(long ln) {
    m_IRM.LoadFromFile("resinfo\\ifextquickslot.txt");

    m_pMyUnerMenuBar = g_pCGInterface->GetUnderMenuBar();
    LoadExtSlotSetting();

    return true;
}