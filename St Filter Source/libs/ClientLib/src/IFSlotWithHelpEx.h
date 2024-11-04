#pragma once

#include "NIFWnd.h"
#include "IFSlotWithHelp.h"


class CIFSlotWithHelpEx : public CNIFWnd {
GFX_DECLARE_DYNAMIC_EXISTING(CIFSlotWithHelpEx, 0xEEA4D0)
public:
    /// \address 00687d40
    bool OnCreate(long ln) override;

    /// \address 00687db0
    void Func_26(int a1) override;

public:
    CIFSlotWithHelp *m_main_slot; //0x0348

private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x34c)
        ENSURE_OFFSET(m_main_slot, 0x0348)
    END_FIXTURE()

    RUN_FIXTURE(CIFSlotWithHelpEx)
};