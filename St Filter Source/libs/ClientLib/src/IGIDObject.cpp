#include "IGIDObject.h"
#include "ICPlayer.h"

const std::n_wstring &CIGIDObject::GetName() const {
    return m_name;
}


const std::n_wstring &CIGIDObject::GetTitle() const {
    return title_name;
}
void CIGIDObject::SetName(const std::n_wstring &name, undefined4 show) {
    /// \todo Reconstruct from 009c2710
    reinterpret_cast<void (__thiscall *)(CIGIDObject *, const std::n_wstring *, undefined4)>(0x009c2710)(
            this, &name, show);
}
void CIGIDObject::ChangeTitleColor(D3DCOLOR Color)
{
    fonttexture_title.SetColor(Color);
}
int CIGIDObject::GetPKStatus()
{
    return g_pCICPlayer->m_pkPenaltyPoint;
}
int CIGIDObject::GetPVPStatus()
{
    return g_pCICPlayer->m_PVPCapeState;
}
void CIGIDObject::ChangeNameColor(D3DCOLOR Color)
{
    fonttexture_playername.SetColor(Color);
}


void CIGIDObject::ChangeTitle(std::n_wstring* str)
{
    fonttexture_title.sub_8B3B60(str);
}

void CIGIDObject::ChangeName(std::n_wstring* str) {
    return fonttexture_playername.sub_8B3B60(str);
}
const int CIGIDObject::GetUniqueID()
{
    if (!this) {
        return 0;
    }
    return m_UniqueObjID;
}
DWORD CIGIDObject::GetObjID()
{
    if (!this) {
        return 0;
    }
    return m_ObjID;
}
D3DCOLOR CIGIDObject::GetNameColor()
{
    return fonttexture_playername.GetFontColor();
}
const CCharacterData::SData *CIGIDObject::GetSData() const {
    return m_characterData;
}
