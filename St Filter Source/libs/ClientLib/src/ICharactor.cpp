#include "ICharactor.h"


CLASSLINK_STATIC_IMPL(CICharactor)

void CICharactor::ShowMessageAboveEntity(const std::n_wstring &message, D3DCOLOR color) {
    reinterpret_cast<void(__thiscall*)(CICharactor*, const std::n_wstring *, D3DCOLOR)>(0x009c77c0)(this, &message, color);
}

void CICharactor::SetName(const std::n_wstring &name, undefined4 show) {
    /// \todo Reconstruct from 009cbb90
    reinterpret_cast<void (__thiscall *)(CICharactor *, const std::n_wstring *, undefined4)>(0x009cbb90)(
            this, &name, show);
}
DWORD CICharactor::GetObjEffect()
{//Does this gets the proper NEEDED effect or it might be getting another effect? well, its the proper addr of the effect of the whole objects in sro, and i got it from makeeffect function so xD
    return m_effectId;
}
int CICharactor::GetJobTypes()
{//Does this gets the proper NEEDED effect or it might be getting another effect? well, its the proper addr of the effect of the whole objects in sro, and i got it from makeeffect function so xD
    return b_JobType;
}
unsigned int CICharactor::GetMaxHp() const {
    return m_hpMax;
}

unsigned int CICharactor::FUN_009c7880() const {
    return reinterpret_cast<unsigned int(__thiscall *)(const CICharactor *)>(0x009c7880)(this);
}

unsigned int CICharactor::GetCurrentMp() const {
    return m_mpCurrent;
}

unsigned int CICharactor::GetMaxMp() const {
    return m_mpMax;
}
void CICharactor::Func_15(int param_1, float *param_2) {
    //printf("%s\n", __FUNCTION__);
    reinterpret_cast<void (__thiscall *)(const CICharactor *, int param_1, float *param_2)>(0x009cf1b0)(this, param_1, param_2);
}

void CICharactor::Func_15_impl(int param_1, float *param_2) {
    CICharactor::Func_15(param_1, param_2);
}
void CICharactor::MakeEffect(UINT32 effectID)
{
    reinterpret_cast<void* (__thiscall*)(CICharactor*, UINT32)>(0x009CF960)(this, effectID);
}

void CICharactor::RemoveEffect(UINT32 effectID)
{
    reinterpret_cast<void* (__thiscall*)(CICharactor*, UINT32)>(0x009CD2B0)(this, effectID);
}
