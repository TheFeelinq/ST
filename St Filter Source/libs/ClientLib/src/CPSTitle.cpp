
#include <HWID/HawidManager.h>
#include <HWID/base64.h>
#include <HWID Manager/hwidmgr.h>
#include "CPSTitle.h"
#include "hook.h"
#include "xlib.h"
#include "MemoryHack.h"
#include "TextStringManager.h"
#include "CPSMission.h"
#include "../../DiscordRichPresence/src/DiscordRichPresence/DiscordManager.h"

void CPSTitle::Version(void)
{
    replaceOffsetEdit(0x0086BC33, 0xFF00D8D8);

    static std::wstring versionFormat;
    if (versionFormat.length() == 0)
    {
        versionFormat.append(L"Ver %d.%03d\n");
        versionFormat.append(L"STFilter 2.6.5\n");
        versionFormat.append(L"Thaidu0ngpr0\n");
    }
#pragma pack(push, 1)
    struct
    {
        uint8_t opcode;
        const wchar_t* address;
    } textPatch;
#pragma pack(pop)
    textPatch.opcode = 0x68;
    textPatch.address = versionFormat.c_str();
    MemoryHack::CopyBytes(0x0086BC6F, &textPatch, sizeof(textPatch));

}
bool CPSTitle::OnServerPacketRecv(CMsgStreamBuffer* msg) {


    if (msg->msgid() == 0x0FF1) {
        DiscordManager::UpdateState(GAME_STATE::SERVER_SELECTION);
        msg->m_currentReadBytes = 0;

    }

    return reinterpret_cast<int(__thiscall*)(CPSTitle*, CMsgStreamBuffer*)>(0x0086bfc0)(this, msg);
}