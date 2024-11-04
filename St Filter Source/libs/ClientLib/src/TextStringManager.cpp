#include "TextStringManager.h"

#include <set>
#include <algorithm>

#ifdef CONFIG_TRANSLATIONS_DEBUG

#endif

const std::n_wstring *CTextStringManager::GetString(const wchar_t *identifier) {
#ifdef CONFIG_TRANSLATIONS_DEBUG
    static std::set<std::n_wstring> strings;
    std::pair<std::set<std::n_wstring>::iterator, bool> ret = strings.insert(identifier);
    return &(*ret.first);
#else
    return reinterpret_cast<const std::n_wstring*(__thiscall*)(CTextStringManager*, const wchar_t*identifier)>(0x008C9C30)(this, identifier);
#endif
}

const std::n_wstring &CTextStringManager::FUN_008c9bb0(const std::n_wstring &identifier) {
    return reinterpret_cast<const std::n_wstring &(__thiscall *)(CTextStringManager *, const std::n_wstring &)>(0x008c9bb0)(this, identifier);
}

std::wstring* CTextStringManager::GetStringByNameStrID(std::wstring* NameStrID)
{
    return reinterpret_cast <std::wstring*(__thiscall*)(CTextStringManager*, std::wstring*)>(0x008C9BB0)(this, NameStrID);
}
std::wstring* CTextStringManager::GetStringTextByCode(const wchar_t* code)
{
    return reinterpret_cast<std::wstring*(__thiscall*)(CTextStringManager*, const wchar_t*)>(0x008C9C30)(this, code);
}

std::wstring* CTextStringManager::GetStringTextByCode(std::wstring* NameStrID)
{
    return reinterpret_cast<std::wstring*(__thiscall*)(CTextStringManager*, std::wstring*)>(0x008C9BB0)(this, NameStrID);
}

CTextStringManager* CTextStringManager::Get(void)
{
    return reinterpret_cast<CTextStringManager*>(0xEEDE90);
}
