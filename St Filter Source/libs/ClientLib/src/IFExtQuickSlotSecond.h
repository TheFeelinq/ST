#pragma once

#include "IFWnd.h"
#include "NIFUnderMenuBar.h"

class CIFExtQuickSlotSecond : public CIFWnd {
GFX_DECLARE_DYNCREATE(CIFExtQuickSlotSecond)
GFX_DECLARE_MESSAGE_MAP(CIFExtQuickSlotSecond)
    enum {
        SECTION_TYPE_1 = 1, //Type1
        SECTION_TYPE_2 = 2, //Type2
        SECTION_TYPE_3 = 3, //Type3
        SECTION_TYPE_4 = 4, //Type4
        GDR_EXT_QUICKSLOT_SECOND_OPTION = 5, //CIFExtQuickSlotOption
        GDR_EXT_QUICKSLOT_SECOND_WND = 10, //CIFDragableArea
        GDR_EXT_QUICKSLOT_SECOND_OPT_BTN = 11, //CIFButton
        GDR_EXT_QUICKSLOT_SECOND_HORI_BTN = 12, //CIFButton
        GDR_EXT_QUICKSLOT_SECOND_VERT_BTN = 13, //CIFButton
        GDR_EXT_QUICKSLOT_SECOND_ONOFF_BTN = 14, //CIFButton
        GDR_EXT_QUICKSLOT_SECOND_SLOT_END = 20, //CIFStatic
        GDR_EXT_QUICKSLOT_SECOND_SLOT_BOARD_1 = 30, //CIFStatic
        GDR_EXT_QUICKSLOT_SECOND_SLOT_BOARD_2 = 31, //CIFStatic
        GDR_EXT_QUICKSLOT_SECOND_SLOT_BOARD_3 = 32, //CIFStatic
        GDR_EXT_QUICKSLOT_SECOND_SLOT_BOARD_4 = 33, //CIFStatic
        GDR_EXT_QUICKSLOT_SECOND_SLOT_BOARD_5 = 34, //CIFStatic
        GDR_EXT_QUICKSLOT_SECOND_SLOT_1 = 100, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SECOND_SLOT_2 = 101, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SECOND_SLOT_3 = 102, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SECOND_SLOT_4 = 103, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SECOND_SLOT_5 = 104, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SECOND_SLOT_6 = 105, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SECOND_SLOT_7 = 106, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SECOND_SLOT_8 = 107, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SECOND_SLOT_9 = 108, //CIFExtQuickSlotSlot
        GDR_EXT_QUICKSLOT_SECOND_SLOT_10 = 109, //CIFExtQuickSlotSlot
    };

public:
    CIFExtQuickSlotSecond();

    ~CIFExtQuickSlotSecond();

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
    void ClearSlotsTexture();

    /// \address 0065ef70
    void UpdateBarSlotsStyle();

    /// \address 0065f390
    void UpdateSlotsBarDirection();

    /// \address 0065f580
    void LoadExtSlotSetting();

    /// \address 0065eb10
    undefined1 ToggleExtQuickSlotOption(bool bVisible);
private:


    /// \address 0065ecd0
    void SetSlotsVisible(bool bVisible);

private:
    void OnToggleSlotsOption();

    void OnDropDownButton();

    void OnClickSlotsHorizontal();

    void OnClickSlotsVertical();

    void ResetPosition();
private:
    bool m_bSlotsVisible;
    bool m_bVertical;
    bool m_bTwoLines;
    bool m_bTransparent;
    bool m_bSlotsLocked;
    bool m_bToolBarLocked;
    short m_SectionTypeID;
    CNIFUnderMenuBar *m_pMyUnerMenuBar;

};
