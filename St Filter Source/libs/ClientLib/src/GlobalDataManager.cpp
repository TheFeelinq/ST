#include <BSLib/Debug.h>
#include "GlobalDataManager.h"
#include "ICPlayer.h"
MemoryHelper* g_MemoryHelper;

undefined4 CGlobalDataManager::FUN_008cbac0(int a1) {
    return reinterpret_cast<undefined4 (__thiscall *)(CGlobalDataManager *, int)>(0x008cbac0)(this, a1);
}
const CCharacterData::SData *CGlobalDataManager::GetCharacterData(int id) const {
    return reinterpret_cast<const CCharacterData::SData *(__thiscall *) (const CGlobalDataManager *, int)>(0x0093f370)(this, id);
}
const CNPCPosData::SData *CGlobalDataManager::GetNPCPosData(int id) const {
    return reinterpret_cast<const CNPCPosData::SData *(__thiscall *) (const CGlobalDataManager *, int)>(0x00938260)(this, id);
}
const CLevelData::SData &CGlobalDataManager::GetLevelData(int level) const {
    return reinterpret_cast<const CLevelData::SData &(__thiscall *)(const CGlobalDataManager *, int)>(0x00937f20)(this, level);
}

const CItemData *CGlobalDataManager::GetItemData(int id) const {
    return reinterpret_cast<const CItemData *(__thiscall *) (const CGlobalDataManager *, int)>(0x0093f2f0)(this, id);
}

void CGlobalDataManager::TEMPLE_93AEF0(unsigned char flag, unsigned char templething)
{
    reinterpret_cast<void(__thiscall*)(CGlobalDataManager*, unsigned char, unsigned char)>(0x0093AEF0)(this, flag, templething);
}

void CGlobalDataManager::TEMPLE_93ADB0(int a1, unsigned char uniontype)
{
    reinterpret_cast<void(__thiscall*)(CGlobalDataManager*, int, unsigned char)>(0x0093AEF0)(this, a1, uniontype);
}

void CGlobalDataManager::GetWorldCodeByID(std::wstring* code, unsigned short ID)
{
    reinterpret_cast<void(__thiscall*)(CGlobalDataManager*, std::wstring*, unsigned short)>(0x009399B0)(this, code, ID);
}

CharData* CGlobalDataManager::GetCharData(unsigned int ObjID)
{
    return reinterpret_cast<CharData*(__thiscall*)(CGlobalDataManager*, unsigned int)>(0x0093F630)(this, ObjID);
}
CSOItem* CGlobalDataManager::GetCSOItemData(unsigned int ItemID)
{
    return reinterpret_cast<CSOItem*(__thiscall*)(CGlobalDataManager*, unsigned int)>(0x0093f5f0)(this, ItemID);
}
CGlobalDataManager* CGlobalDataManager::Get(void)
{
    return reinterpret_cast<CGlobalDataManager*>(0xEEDF08);
}
DWORD CGlobalDataManager::GetEffectIdByName(wchar_t* szNameStr)
{
    return reinterpret_cast<DWORD(__cdecl*)(wchar_t*, DWORD)>(0x00A950A0)(szNameStr, 0);
}
undefined CGlobalDataManager::FUN_00939a60(undefined4 param_1) {
    return reinterpret_cast<undefined (__thiscall *)(const CGlobalDataManager *, undefined4)>(0x00939a60)(this,param_1);
}

undefined4 CGlobalDataManager::FUN_0093a610(std::n_wstring param_1) {
    return reinterpret_cast<undefined4 (__thiscall *)(const CGlobalDataManager *, std::n_wstring)>(0x0093a610)(this, param_1);
}

UINT16 CGlobalDataManager::GetCurrentRegion()
{
    if(g_pCICPlayer && g_CGamePtr)
        return *(UINT16*)(0xEEF68C);
    return 0;
}

UINT8 CGlobalDataManager::GetEmptyInventorySlots()
{
    DWORD dwCallAddr_1 = 0x00798D00;
    DWORD dwCallAddr_2 = 0x006A1D20;
    DWORD dwCallAddr_3 = 0x006B6230;

    UINT8 remainingSlots = 0;

    __asm
    {
    mov ecx, dword ptr ds : 0x0110F80C;
    call dwCallAddr_1;
    mov ecx, eax;
    call dwCallAddr_2;
    mov ecx, eax;
    call dwCallAddr_3;
    mov remainingSlots, al;
    }

    return remainingSlots;
}