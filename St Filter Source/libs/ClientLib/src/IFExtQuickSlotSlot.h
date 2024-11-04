#pragma once

#include "IFWnd.h"
#include "NIFWnd.h"
#include "IFSlotWithHelp.h"

class CIFExtQuickSlotSlot : public CIFWnd {
GFX_DECLARE_DYNAMIC_EXISTING(CIFExtQuickSlotSlot, 0x00ee9a68)

    GFX_DECLARE_DYNCREATE_FN(CIFExtQuickSlotSlot)

public:
    CIFExtQuickSlotSlot();

    ~CIFExtQuickSlotSlot();

public:
    /// \address 0065faf0
    bool OnCreate(long ln) override;

    /// \address 0065fb00
    void RenderMyself() override;

    /// \address 0065fb90
    void OnWndMessage(Event3D *a1) override;

    /// \address 0065fbf0
    bool Func_25(int a1) override;

    /// \address 0065fb50
    bool Func_28(int a1, int a2, int a3) override;

    /// \address 0065fc10
    int OnMouseRightDown(int a1, int x, int y) override;

    /// \address 0065fc20
    int OnMouseRightUp(int a1, int x, int y) override;

public:
    /// \address 0065fc70
    void UpdatehgWndSlot(CIFWnd *pIFWnd);

    /// \address 0065fcb0
    CIFSlotWithHelp *GetSlotUnderBarBySlothgWnd() const;

private:
    int m_UnderBarSlot_hgWnd; //0x036C //its -stole- the hgwnd from the underbarslots

private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x370)
    END_FIXTURE()

    RUN_FIXTURE(CIFExtQuickSlotSlot)
};