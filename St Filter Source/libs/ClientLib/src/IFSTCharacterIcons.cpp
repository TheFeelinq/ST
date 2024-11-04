//
// Created by Admin on 21/9/2021.
//

#include "IFSTCharacterIcons.h"
#include "GlobalDataManager.h"
#include "memhelp.h"
#include "GameDataExt.h"


const DWORD fornopping = 0x009DED3D;
const DWORD onCharIconHookAddr = 0x009DED43;
const DWORD onCharIconHookAddrJmpback = 0x009DED4C;
const DWORD onCharIconIgnore = 0x9DEDE1;
void* lastFoundedIcon;

__declspec(naked) void OnIconCheck()
{
    __asm
    {
    pushad;
    pushfd;
    PUSH ECX;
    CALL CharacterIcons::OnCharacterIcon;
    CMP AL, TRUE;
    je patch;
    popfd;
    popad;
    jmp onCharIconIgnore;
    patch:
    popfd;
    popad;
    MOV EDX, DWORD PTR[0x110AB38];
    MOV EAX, lastFoundedIcon;
    jmp onCharIconHookAddrJmpback;
    }
    }

    void CharacterIcons::Initialize()
    {
       // g_MemoryHelper->SetNop(onCharIconHookAddr, 6);
       // g_MemoryHelper->SetNop(fornopping, 6);
       // g_MemoryHelper->Detour(false, reinterpret_cast<void*>(onCharIconHookAddr), OnIconCheck);

        memhelp::RenderNop((void*)onCharIconHookAddr, 6);
        memhelp::RenderNop((void*)fornopping, 6);
        memhelp::RenderDetour(ASM_JMP, (void*)onCharIconHookAddr, OnIconCheck);

    }

    bool __stdcall CharacterIcons::OnCharacterIcon(CICPlayer * player)
    {
        if (g_pCICPlayer && player && (*(DWORD*)player == (0xDE2E7C) || *(DWORD*)player == (0xDE2C24)))
        {
            std::map<std::wstring, UINT32>::iterator foundedInfo =  m_CharacterIcons.find(player->GetName().c_str());
            if (foundedInfo != m_CharacterIcons.end())
            {
                std::map<int, void*>::iterator foundedTheIcon = m_IconsData.find(foundedInfo->second);
                if (foundedTheIcon != m_IconsData.end())
                {
                    lastFoundedIcon = foundedTheIcon->second;
                    return TRUE;
                }
                else
                    return FALSE;
            }
            else
                return FALSE;
        }
        if(!lastFoundedIcon)
            return FALSE;
    }
