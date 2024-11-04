#pragma once

#include "NIFWnd.h"
#include "NIFGauge.h"
#include "NIFStatic.h"

#include "IFSlotWithHelpEx.h"
// https://www.elitepvpers.com/forum/sro-pserver-guides-releases/4256375-source-fix-old-exp-bar-writing-code.html
class CNIFUnderMenuBar : public CNIFWnd {
public:
    void Update();
    void On_Cmd32869();
    static void Initialize();
    void SaveQuickslotData(int byIndexSot);
    char padx[8];
    CNIFGauge *gauge_skillexp; //0x0350
    CNIFStatic *lbl_percentage; //0x0354
    CNIFStatic *lbl_spcount; //0x0358
    CNIFStatic *lbl_exp_bar_scaler; //0x035C
    CNIFStatic *lbl_360; //0x0360
    CNIFStatic *lbl_percent_bar; //0x0364
    CNIFStatic *lbl_level; //0x0368
    CNIFGauge *gauges[10]; //0x036C
    char pad_0394[4 * 16]; //0x0394
    CIFSlotWithHelpEx *m_slots[51]; //0x03D4 //yep 50 slots ;-;
    CIFSlotWithHelp *m_slotunk; //0x04A0
    //CIFSlotWithHelpEx *m_slotNew[11]; //0x03D4 //yep 50 slots ;-;
    char pad_cnifundermenubar[4];
private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x4a8)
        ENSURE_OFFSET(m_slots, 0x3d4)
        ENSURE_OFFSET(m_slotunk, 0x4A0)
    END_FIXTURE()

    RUN_FIXTURE(CNIFUnderMenuBar)

};