#include "IFFrame.h"
#include "IFHelperBubbleWindow.h"
#include "IFPartyMatchSlot.h"

class CIFPartyMatch : public CIFFrame {
GFX_DECLARE_DYNAMIC_EXISTING(CIFPartyMatch, 0x00EEB8CC)

//FUN_00740870
//FUN_00740750
    void OnUpdateIMPL();
    void FUN_00740910(BYTE PatyType);
    void FUN_00740870(char param_1);
    void FUN_00740750(CIFHelperBubbleWindow* window);
    int OnMouseLeftUpIMPL(int a1, int x, int y) ;
public:
    char pad_0000[0x7EC - sizeof(CIFFrame)];
    CIFPartyMatchSlot * m_PartyMatchSlotSelected; //0x7EC
BEGIN_FIXTURE()
        ENSURE_OFFSET(m_PartyMatchSlotSelected, 0x7EC)
    END_FIXTURE()

    RUN_FIXTURE(CIFPartyMatch)
}; //size 0x800

