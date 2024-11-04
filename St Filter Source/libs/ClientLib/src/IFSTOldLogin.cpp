//
// Created by Admin on 25/6/2021.
//

#include "IFSTOldLogin.h"
#include "memhelp.h"
#include "Packet.h"
#include "IFNormalTile.h"
#include "GInterface.h"
#include "IFSTCharacterIcons.h"
#include "../../../DevKit_DLL/src/Util.h"
#include <locale>
#include <fstream>
#include <sstream>
#include "BSLib/multibyte.h"
#include "BSLib/BSLib.h"
#include "IFflorian0Guide.h"

const DWORD dwHookSlash = 0x0085F4F8;
const DWORD dwHookSlashJumpback = 0x0085f4ff;

const DWORD dwHookSlash1 = 0x009daea4;
const DWORD dwHookSlashJumpback1 = 0x009daea6;

const DWORD fixf10crash = 0x00BA2156;
const DWORD fixf10crashjmp = 0x00BA2160;

const DWORD stallnetwork = 0x00799061;
const DWORD stallnetworkjmp = 0x00799081;
const DWORD stallnetworkhookpaket = 0x00821b07;
const DWORD stallnetworkjmppacket = 0x00821b0c;

const DWORD stallnetworkhookpaket1 = 0x00821b1c;
const DWORD stallnetworkjmppacket1 = 0x00821b21;
//FUN_006ec5d0
const DWORD dwHookPrintHelpMsg = 0x006ec77b; //friend list sc
const DWORD dwHookPrintHelpMsgCall = 0x00644c90; //friend list sc

const DWORD dwHookPrintHelpMsgJumpback = 0x006ec780;

const DWORD dwHookShouldLootCall = 0x008AF84F;
const DWORD dwHookShouldLootJumpback = 0x008AF8AA;

const DWORD dwHookPetSetupFil = 0x00657ba0;
const DWORD dwHookPetSetupCall = 0x007a8831;
const DWORD dwHookPetSetupJumpback = 0x007a8836;

const DWORD cdwOnMsgHandleHookAddr = 0x0078B6A8;
const DWORD cdwOnMsgHandleHookAddrRetn = 0x0078B690;
const DWORD cdwOnMsgHandleHookJmpback = 0x0078B6AD;

const DWORD cdwOnNpcPosIDHookAddr = 0x0061bb53;
const DWORD cdwOnNpcPosIDHookAddrRetn = 0x0061bb5b;

void OnPrintHelpMsg()
{
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_SELECT_MONEY_SILK"));
    CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 224, 199, 144);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);

}
std::string wchar2string(const wchar_t* str)
{
    std::string mystring;
    while( *str )
        mystring += (char)*str++;
    return  mystring;
}
bool __stdcall ShouldLoot(const wchar_t* playerName,UINT32 itemId,const wchar_t* itemName,const wchar_t* itemTypeName,UINT32 itemDropType)
{

    {

        static std::map<std::string, bool> filteredTypeIds;
        static std::map<std::string, bool> filteredNames;
        static bool loaded = false;

        if (!loaded)
        {
            try
            {
                filteredTypeIds.insert(std::pair<std::string, bool>("ITEM_ETC_GOLD_01", true));
                filteredTypeIds.insert(std::pair<std::string, bool>("ITEM_ETC_GOLD_02", true));
                filteredTypeIds.insert(std::pair<std::string, bool>("ITEM_ETC_GOLD_03", true));
                filteredTypeIds.insert(std::pair<std::string, bool>("ITEM_ETC_AMMO_BOLT_01", true));
                filteredTypeIds.insert(std::pair<std::string, bool>("ITEM_ETC_AMMO_ARROW_01", true));
                filteredNames.insert(std::pair<std::string, bool>("Jade tablet of strikes(Lvl.1)", true));
                loaded = true;
            }
            catch (const std::exception& ex)
            {
                OutputDebugStringA(ex.what());
                return false;
            }
            catch (...) // ¯\_(ツ)_/¯
            {
                OutputDebugStringA("An unhandled exception occurred");
                return false;
            }
        }

        // Check by type id
        if (!filteredTypeIds.empty())
        {
            std::string utf8 = wchar2string(itemTypeName);
            static std::map<std::string, bool>::iterator itr = filteredTypeIds.find(utf8);
            if (itr != filteredTypeIds.end())
            {
                return itr->second;
            }
        }

        if (!filteredNames.empty())
        {
            std::string utf8 =wchar2string(itemName);
            static std::map<std::string, bool>::iterator itr = filteredNames.find(utf8);
            if (itr != filteredNames.end())
            {
                return itr->second;
            }
        }
    }

}
__declspec(naked) void hookShouldLoot()
{
    __asm
    {

    pushad
    pushfd
    call ShouldLoot;
    popfd
    popad
    jmp dwHookShouldLootJumpback;
    }
}
__declspec(naked) void hookPetSetUp()
{
        __asm
        {
        CALL dwHookPetSetupFil;
        pushad
        pushfd
        call OnPrintHelpMsg;
        popfd
        popad
        jmp dwHookPetSetupJumpback;
        }
}
__declspec(naked) void OnChatStartsWithSlash()
{

    ///Default 6951
    __asm mov word ptr [ESP + 0x18],0x645C;
    __asm jmp dwHookSlashJumpback;
}
__declspec(naked) void hookstallnetwork()
{


    __asm jmp stallnetworkjmp;
}
__declspec(naked) void hookNpcPosID()
{
    __asm
    {
    mov eax,0x7e1;
    push eax;
    mov ecx,0x00EEDF08;
    jmp cdwOnNpcPosIDHookAddrRetn;
    }
}
__declspec(naked) void hookstallnetworkpacket()
{

    __asm PUSH 0x750c
    __asm jmp stallnetworkjmppacket;
}
__declspec(naked) void hookstallnetworkpacket1()
{

    __asm PUSH 0x750c
    __asm jmp stallnetworkjmppacket1;
}
__declspec(naked) void FixF10Crash()
{
    __asm cmp dword ptr ds:[0x110F930],0x1869F
    __asm jmp fixf10crashjmp;
}
__declspec(naked) void OnCharReload()
{
    __asm
    {
    CALL dwHookPrintHelpMsgCall;
    pushad;
    call OnPrintHelpMsg;
    popad;
    jmp dwHookPrintHelpMsgJumpback;
    }
    }


    const DWORD dwHookAddr = 0x00796735;
    const DWORD dwConditionMetJumpBack = 0x00797818;
    const DWORD dwConditionNotMetJumpBack = 0x0079673C;
    BYTE ItemSlot;

    void OnNameChangeUsage()
    {

        wchar_t message[1000];
        swprintf_s(message, L"[Client] It hits! Slot (%d).",ItemSlot);
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 224, 199, 144);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    }
//FUN_00796660 704c
    void __declspec(naked) OnHook(void)
    {
        __asm
        {
        mov eax, [esp + 0x20];
        cmp ax, 0x19ED;
        jne ConditionNotMet;
        push eax;
        movzx eax, [esp + 0x1A8];
        mov ItemSlot, al;
        pop eax;
        pushad;
        call OnNameChangeUsage;
        popad;
        jmp dwConditionMetJumpBack;
        ConditionNotMet:
        shr eax, 0x7;
        and eax, 0xF;
        jmp dwConditionNotMetJumpBack;
        }

    }
    bool Handled(DWORD esp)
    {
        if (*(UINT32*)(esp + 0x2C) == VK_ESCAPE)
        {

        }
        return false;
    }
    __declspec(naked) void ASM_OnClientMsgHandler()
    {
        __asm {
        pushad;
        pushfd;

        push esp;
        CALL Handled;

        cmp al, TRUE;
        je OnHappyEnd;
        pop esp;
        popfd;
        popad;
        LEA EAX, DWORD PTR SS : [ESP + 10];
        PUSH EAX;
        jmp cdwOnMsgHandleHookJmpback;
        OnHappyEnd:
        pop esp;
        popfd;
        popad;
        MOV EAX, 1;
        POP ESI;
        RET 0xC;
        }
        }
void IFSTOldLogin::Initialize()
{
   // memhelp::RenderNop((void*)dwHookAddr, 10);
   // memhelp::RenderDetour(ASM_JMP, (void*)dwHookAddr, OnHook);

  //  memhelp::RenderNop((void*)dwHookSlash, 1);
   // memhelp::RenderDetour(ASM_JMP, (void*)dwHookSlash, OnChatStartsWithSlash);

    //memhelp::RenderNop((void*)dwHookPetSetupCall, 5);
   // memhelp::RenderDetour(ASM_JMP, (void*)dwHookPetSetupCall, hookPetSetUp);
    //g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOnMsgHandleHookAddr), ASM_OnClientMsgHandler);
    memhelp::RenderNop((void*)fixf10crash, 1);
    memhelp::RenderDetour(ASM_JMP, (void*)fixf10crash, FixF10Crash);

   // memhelp::RenderNop((void*)dwHookShouldLootCall, 4);
   // memhelp::RenderDetour(ASM_JMP, (void*)dwHookShouldLootCall, hookShouldLoot);

   // memhelp::RenderNop((void*)stallnetwork, 6);
   // memhelp::RenderDetour(ASM_JMP, (void*)stallnetwork, hookstallnetwork);

    //memhelp::RenderNop((void*)cdwOnNpcPosIDHookAddr, 8);
    //memhelp::RenderDetour(ASM_JMP, (void*)cdwOnNpcPosIDHookAddr, hookNpcPosID);

    //memhelp::RenderNop((void*)stallnetworkhookpaket, 5);
    //memhelp::RenderDetour(ASM_JMP, (void*)stallnetworkhookpaket, hookstallnetworkpacket);

    //memhelp::RenderNop((void*)stallnetworkhookpaket1, 5);
   // memhelp::RenderDetour(ASM_JMP, (void*)stallnetworkhookpaket1, hookstallnetworkpacket1);
    //memhelp::RenderNop((void*)dwHookPrintHelpMsg, 5);
    //memhelp::RenderDetour(ASM_JMP, (void*)dwHookPrintHelpMsg, OnCharReload);
   // FUN_00821ae0
   // FUN_008237a0
}