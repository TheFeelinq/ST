
#include "IFParty.h"
#include "GInterface.h"

bool CIFParty::OnCreateIMPL(long ln) {


    bool b = reinterpret_cast<bool (__thiscall *)(CIFParty *, long)>(0x006d6fc0)(this, ln);
    m_partySlot0->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_partySlot1->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_partySlot2->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_partySlot3->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_partySlot4->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_partySlot5->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_partySlot6->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_leaderPlayerPicture->BringToFront();
    return b;
}
void CIFParty::OnUpdateIMPL()
{

    reinterpret_cast<void (__thiscall *)(CIFParty *)>(0x006d5ca0)(this);
}

void CIFParty::ClearDDJ()
{
    m_partySlot0->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_partySlot1->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_partySlot2->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_partySlot3->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_partySlot4->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_partySlot5->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);
    m_partySlot6->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0, 0);

}