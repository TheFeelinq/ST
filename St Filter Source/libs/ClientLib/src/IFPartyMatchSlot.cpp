//
// Created by Admin on 16/2/2022.
//


#include "IFPartyMatchSlot.h"
#include "IFStatic.h"


GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFPartyMatchSlot, 0x00EEB94C)
bool CIFPartyMatchSlot::OnCreateIMPL(long ln) {

    bool b = reinterpret_cast<bool (__thiscall *)(CIFPartyMatchSlot *, long)>(0x00741250)(this, ln);

    return b;
}

void CIFPartyMatchSlot::OnUpdateIMPL()
{

    reinterpret_cast<void(__thiscall*)(CIFPartyMatchSlot*)>(0x006528a0)(this);
}

const wchar_t* CIFPartyMatchSlot::GetPartyMatchSlotByID(int ID)
{
    CIFStatic* PartyRaceType = this->m_IRM.GetResObj<CIFStatic>(ID, 1);
    const wchar_t *race2 = PartyRaceType->GetText();
    return race2;
}
