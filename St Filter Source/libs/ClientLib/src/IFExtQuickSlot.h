#pragma once

#include "IFWnd.h"
#include "NIFUnderMenuBar.h"

class CIFExtQuickSlot : public CIFWnd {
GFX_DECLARE_DYNAMIC_EXISTING(CIFExtQuickSlot, 0x00ee9a28)
GFX_DECLARE_DYNCREATE_FN(CIFExtQuickSlot)

GFX_DECLARE_MESSAGE_MAP(CIFExtQuickSlot)

    enum {
        SECTION_TYPE_1 = 1, //Type1
        SECTION_TYPE_2 = 2, //Type2
        SECTION_TYPE_3 = 3, //Type3
        SECTION_TYPE_4 = 4, //Type4
        GDR_EXT_QUICKSLOT_OPTION = 5, //CIFExtQuickSlotOption
        GDR_EXT_QUICKSLOT_WND = 10, //CIFDragableArea
        GDR_EXT_QUICKSLOT_OPT_BTN = 11, //CIFButton
        GDR_EXT_QUICKSLOT_HORI_BTN = 12, //CIFButton
        GDR_EXT_QUICKSLOT_VERT_BTN = 13, //CIFButton
        GDR_EXT_QUICKSLOT_ONOFF_BTN = 14, //CIFButton
        GDR_EXT_QUICKSLOT_SLOT_END = 20, //CIFStatic
        GDR_EXT_QUICKSLOT_SLOT_BOARD_1 = 30, //CIFStatic
        GDR_EXT_QUICKSLOT_SLOT_BOARD_2 = 31, //CIFStatic
        GDR_EXT_QUICKSLOT_SLOT_BOARD_3 = 32, //CIFStatic
        GDR_EXT_QUICKSLOT_SLOT_BOARD_4 = 33, //CIFStatic
        GDR_EXT_QUICKSLOT_SLOT_BOARD_5 = 34, //CIFStatic
        GDR_EXT_QUICKSLOT_SLOT_1 = 100, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SLOT_2 = 101, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SLOT_3 = 102, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SLOT_4 = 103, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SLOT_5 = 104, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SLOT_6 = 105, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SLOT_7 = 106, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SLOT_8 = 107, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SLOT_9 = 108, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SLOT_10 = 109, //CIFExtQuickSlotSlot
    };

public:
    CIFExtQuickSlot();

    ~CIFExtQuickSlot();

public:
    /// \address 0065f720
    bool OnCreate(long ln) override;

public: // only for hooks..
    /// \address 0065e8d0
    void SetBarVerticalState(bool bState);

    /// \address 0065e8e0
    void SetBarTransparentState(bool bState);

    /// \address 0065e8f0
    void SetSlotLockState(bool bState);

    /// \address 0065e900
    void SetBarLockState(bool bState);

    /// \address 0065e910
    void SetBarTwoLinesState(bool bState);

    /// \address 0065e9b0
    void SaveExtSlotSetting();

    /// \address 0065eef0
    void ClearChildofSlot();

    /// \address 0065ef70
    void UpdateBarSlotsStyle();

    /// \address 0065f390
    void UpdateSlotsBarDirection();

    /// \address 0065f580
    void LoadExtSlotSetting();

    /// \address 0065eb10
    undefined1 ToggleExtQuickSlotOption(bool bVisible);

    /// \address 0065ecd0
    void SetSlotsVisible(bool bVisible);

private:
    void OnToggleSlotsOption();

    void OnDropDownButton();

    void OnClickSlotsHorizontal();

    void OnClickSlotsVertical();

private:
    bool m_bSlotsVisible; //0x036C
    bool m_bVertical; //0x036D
    bool m_bTwoLines; //0x036E
    bool m_bTransparent; //0x036F
    bool m_bSlotsLocked; //0x0370
    bool m_bToolBarLocked; //0x0371
    short m_SectionTypeID; //0x0372 // the types in resinfo file
    CNIFUnderMenuBar *m_pMyUnerMenuBar; //0x0374
private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x378)
        ENSURE_OFFSET(m_bSlotsVisible, 0x36c)
        ENSURE_OFFSET(m_bVertical, 0x36d)
        ENSURE_OFFSET(m_bTwoLines, 0x36e)
        ENSURE_OFFSET(m_bTransparent, 0x36f)
        ENSURE_OFFSET(m_bSlotsLocked, 0x370)
        ENSURE_OFFSET(m_bToolBarLocked, 0x371)
        ENSURE_OFFSET(m_SectionTypeID, 0x372)
        ENSURE_OFFSET(m_pMyUnerMenuBar, 0x374)

    END_FIXTURE()

    RUN_FIXTURE(CIFExtQuickSlot)
};
