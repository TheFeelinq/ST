
#include <IFFrame.h>

class CIFPartyMatchSlot : public CIFWnd{
GFX_DECLARE_DYNAMIC_EXISTING(CIFPartyMatchSlot, 0x00EEB94C)


public:
    void OnUpdateIMPL();
    bool OnCreateIMPL(long ln);
    const wchar_t* GetPartyMatchSlotByID(int ID);
public:
    //
    int m_MatchNumber; // 0x36c
    char pad_0000[0x9];
    std::n_wstring m_MasterOfParty; //0x37c
    std::n_wstring m_PartyMatchTitle; //0x398

BEGIN_FIXTURE()
        //ENSURE_SIZE(0x3b8)
        ENSURE_OFFSET(m_MatchNumber, 0x36c)
        ENSURE_OFFSET(m_MasterOfParty, 0x37c)
        ENSURE_OFFSET(m_PartyMatchTitle, 0x398)
    END_FIXTURE()

    RUN_FIXTURE(CIFPartyMatchSlot)
}; //size 0x3b8


