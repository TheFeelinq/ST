#include "IFMainFrame.h"
#include "IFCheckBox.h"

class CIFExtQuickSlotOption : public CIFMainFrame {
GFX_DECLARE_MESSAGE_MAP(CIFExtQuickSlotOption)

GFX_DECLARE_DYNAMIC_EXISTING(CIFExtQuickSlotOption, 0x00ee9a48)

    enum {
        GDR_EXT_QUICKSLOT_OPT_BG1 = 5, //CIFNormalTile
        GDR_EXT_QUICKSLOT_OPT_BG2 = 6, //CIFNormalTile
        GDR_EXT_QUICKSLOT_OPT_FRAME1 = 7, //CIFFrame
        GDR_EXT_QUICKSLOT_OPT_FRAME2 = 8, //CIFFrame
        GDR_EXT_QUICKSLOT_OPT_FRAME2_TEXT = 9, //CIFStatic
        GDR_EXT_QUICKSLOT_OPT_TRANS = 15, //CIFStatic
        GDR_EXT_QUICKSLOT_OPT_LOCK = 16, //CIFStatic
        GDR_EXT_QUICKSLOT_OPT_FIX = 17, //CIFStatic
        GDR_EXT_QUICKSLOT_OPT_DOUBLELINE = 18, //CIFStatic
        GDR_EXT_QUICKSLOT_OPT_TRANS_CHECKBOX = 25, //CIFCheckBox
        GDR_EXT_QUICKSLOT_OPT_LOCK_CHECKBOX = 26, //CIFCheckBox
        GDR_EXT_QUICKSLOT_OPT_FIX_CHECKBOX = 27, //CIFCheckBox
        GDR_EXT_QUICKSLOT_OPT_DOUBLELINE_CHECKBOX = 28, //CIFCheckBox
        GDR_EXT_QUICKSLOT_OK_BTN = 35, //CIFButton
        GDR_EXT_QUICKSLOT_APPLY_BTN = 36, //CIFButton
    };

public:
    GFX_DECLARE_DYNCREATE_FN(CIFExtQuickSlotOption)

    /// \address 0065f790
    ///CIFExtQuickSlotOption();

    /// \address 0065f7c0
    ///~CIFExtQuickSlotOption();

public:
    bool OnCreate(long ln) override;

    /// \address 0065f7e0
    undefined1 OnCloseWnd() override;

public:
    /// \address 0065f800
    void SetCheckBoxState(bool bTrasnpearnt, bool bSlotsLocked,
                          bool bToolBarLocked, bool bTwoLines);

    /// \address 0065f870
    void ApplyExtQSSetting();

private:
    void OnClickConfirm();

private:
    //nothing speciall :cry:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x7bc)
    END_FIXTURE()

    RUN_FIXTURE(CIFExtQuickSlotOption)
};
