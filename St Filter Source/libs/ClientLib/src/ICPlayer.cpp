#include "ICPlayer.h"
#include "CPSMission.h"
#include "GInterface.h"
#include "GlobalDataManager.h"
#include "EntityManagerClient.h"

GFX_IMPLEMENT_DYNAMIC_EXISTING(CICPlayer, 0x00ef1b44)


// CICPlayer::IsGameMasterMAYBE(void) .text 009D4C40 00000009   R . . . . T .
bool CICPlayer::IsGameMaster() {
    return N000094A7 & 1;
}

// sub_9D6580 .text 009D6580 00000032 00000008 00000004 R . . . . T .
// I am pretty sure this func simply returned a copy of the players name ... ridiculous!
std::n_wstring *CICPlayer::sub_9D6580(std::n_wstring *str) {
    return reinterpret_cast<std::n_wstring*(__thiscall*)(CICPlayer*, std::n_wstring*)>(0x9D6580)(this, str);
}

std::n_wstring CICPlayer::GetCharName() const {
    return m_charname;
}


CICPlayer* CICPlayer::GetCICPlayerByUniqueID(DWORD UniqueID)
{
    //009d32c0
    return reinterpret_cast<CICPlayer*(__cdecl*)(DWORD)>(0x009C3220)(UniqueID);
}
void CICPlayer::OnRenderItemName()
{
    std::map<int, CIObject*> entities = g_pGfxEttManager->entities;
    for (std::map<int, CIObject*>::iterator it = entities.begin();
         it != entities.end(); ++it) {
        if (!strcmp(it->second->GetRuntimeClass()->m_lpszClassName, "CICMonster")) {
            short Level = *(short *) ((DWORD32) it->second + 0x7AC);
            int mobID = *(int *) ((int) (it->second) + 0x21C);
            if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
            {
                if (CharData* uqdata = g_datamanager->GetCharData(mobID))
                {
                    char mobLevel = *(char *) ((int) (uqdata) + 0x1E8);
                    wchar_t buffer[200];
                    std::n_wstring mymsg;
                    swprintf(buffer, sizeof(buffer), L"%s (Lv.%d)", ((CICharactor *) it->second)->GetName().c_str(), mobLevel);
                    mymsg.assign(buffer);
                    ((CICharactor*)it->second)->ChangeName(&mymsg);
                }
            }
            if (Level == 3) {
                ((CICharactor *) it->second)->ChangeNameColor(0xFFFF0000);
            }
        }
        if (!strcmp(it->second->GetRuntimeClass()->m_lpszClassName, "CIItem")) {
            int itemID = *(int *) ((int) (it->second) + 0x21C);
            static const CItemData *data = NULL;
            data = g_CGlobalDataManager->GetItemData(itemID);
            if (data != NULL)
            {
                std::wstring NameStrID = data->m_nameStrId128.c_str();
                std::wstring NameStrID128 = g_CTextStringManager->GetStringByNameStrID(&NameStrID)->c_str();
                if(data->m_reqLevel1 > 0)
                {
                    std::n_wstring ItemNameW = (NameStrID128).c_str();
                    wchar_t buffer[200];
                    std::n_wstring mymsg;
                    swprintf_s(buffer, sizeof(buffer), L"%s (Lv.%d)", ItemNameW.c_str(), data->m_reqLevel1);
                    mymsg.assign(buffer);
                    ((CICharactor*)it->second)->ChangeName(&mymsg);
                }
            }

        }
    }

}

void CICPlayer::OnRender()
{

    if (CPSMission::Gui_ColorsRender)
    {
        OnRenderItemName();
        CICharactor* entity = 0;
        CLASSLINK_LOOP_BEGIN(CICharactor)
            TitleData* titleDate = CIFflorian0Guide::TitleDataList[obj->GetName()];
            if (titleDate != NULL) {
                entity = obj;
                if (entity) {
                    std::n_wstring newName = std::n_wstring(L" <" + titleDate->NameTitle + L"> " + titleDate->charname);
                    if (titleDate->NameTitle.length() > 0) {
                        entity->ChangeName(&newName);
                    }
                    if (titleDate->namecolor > 0 && entity->GetPKStatus()  == 0 && entity->GetPVPStatus() == 0) {
                        entity->ChangeNameColor(titleDate->namecolor);
                    }
                    if (titleDate->Title.length() > 0) {
                        entity->ChangeTitle(&titleDate->Title);
                    }
                    if (titleDate->titlecolor > 0) {
                        entity->ChangeTitleColor(titleDate->titlecolor);
                    }
                }
            }
        CLASSLINK_LOOP_END(CICharactor)

        reinterpret_cast<void(__thiscall*)(CICPlayer*)>(0x009D87C0)(this); //Render
    }
    else
    {
        OnRenderItemName();
        reinterpret_cast<void(__thiscall*)(CICPlayer*)>(0x009D87C0)(this); //Render
    }

}

unsigned char CICPlayer::GetCurrentLevel() const {
    return m_level;
}

long long int CICPlayer::GetCurrentExp() const {
    return m_exp_current;
}

short CICPlayer::GetStatPointAvailable() const {
    return m_statpoint_available;
}

short CICPlayer::GetStrength() const {
    return m_str_stat;
}

short CICPlayer::GetIntelligence() const {
    return m_int_stat;
}

const std::n_wstring &CICPlayer::GetJobAlias() const {
    return m_jobAlias;
}

int CICPlayer::GetCurrentJobExperiencePoints() const {
    return reinterpret_cast<int (__thiscall *)(const CICPlayer *)>(0x009d4d20)(this);
}
void CICPlayer::Func_15(int param_1, float *param_2) {
    //printf("%s %d %p\n", __FUNCTION__, param_1, param_2);
   // reinterpret_cast<void (__thiscall *)(const CICharactor *, int param_1, float *param_2)>(0x009d49c0)(this, param_1, param_2);
    if ((param_1 == 3) && (g_pCGInterface != NULL)) {
        g_pCGInterface->FUN_00777a70(0,1);
    }
    CICUser::Func_15(param_1,param_2);
}

void CICPlayer::Func_15_impl(int param_1, float *param_2) {
    CICPlayer::Func_15(param_1, param_2);
}

undefined4 CICPlayer::FUN_009d68f0() {
    return reinterpret_cast<undefined4 (__thiscall *)(const CICPlayer*)>(0x009d68f0)(this);
}
int CICPlayer::GetWorldID()
{
    return reinterpret_cast<int(__thiscall*)(CICPlayer*)>(0x009D4D90)(this) % 65536;
}