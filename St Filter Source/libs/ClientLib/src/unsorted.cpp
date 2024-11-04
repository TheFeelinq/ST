#include "StdAfx.h"
#include "unsorted.h"

#include "GlobalHelpersThatHaveNoHomeYet.h"
#include "GFXMainFrame/GWndBase.h"
#include "Process.h"
#include "TextStringManager.h"
#include "GInterface.h"
#include <BSLib/BSLib.h>
#include <GFX3DFunction/DrawingHelpers.h>
#include <ICharactor.h>

#include "NIFCommunityWnd.h"
#include "IFChatViewer.h"
#include "IFWholeChat.h"
#include "CPSMission.h"

#include <Game.h>

GlobalPtr<CGWndBase, 0x0110F60C> g_CurrentIF_UnderCursor;

bool TryCreateCompatibleDC() {
    g_hdc = CreateCompatibleDC(0);
    return g_hdc != 0;
}

bool StartNetEngine() {
    return reinterpret_cast<bool (*)()>(0x008449F0)();
}

void DrawRect(int x, int y, int height, int width, int color) {
    /*
     * x1|y1        x2|y1
     * --------------
     * |            |
     * |            |
     * --------------
     * x1|y2        x2|y2
    */

    int x1 = x;
    int x2 = x + width;
    int y1 = y;
    int y2 = y + height;

    // Draw vertical Left
    DXDrawLine(x1, y1, x2, y1, color, 1.0);
    DXDrawLine(x2, y1, x2, y2, color, 1.0);
    DXDrawLine(x2, y2, x1, y2, color, 1.0);
    DXDrawLine(x1, y2, x1, y1, color, 1.0);
}

void DrawRect(int x, int y, int height, int width) {
    DrawRect(x, y, height, width, 0x00FF0000);
}


void sub_BBDA70(int a1) {
    reinterpret_cast<void (*)(int)>(0xBBDA70)(a1);
}

void PopulateCharPositionsForNameChange(CGFXVideo3d *p) {
    reinterpret_cast<void (__cdecl *)(CGFXVideo3d *)>(0x85AFF0)(p);
}

int GetIDOfInterfaceUnderCursor() {
    if (g_CurrentIF_UnderCursor) {
        return g_CurrentIF_UnderCursor->UniqueID();
    } else {
        return -1;
    }
}

// Fun_CacheTexture_Create .text 005008F0 00000010 00000000 00000004 R . . . . . .
void *Fun_CacheTexture_Create(const std::n_string &a2) {
    return reinterpret_cast<void *(__cdecl *)(const std::n_string *)>(0x005008F0)(&a2);
}
IDirect3DBaseTexture9 *Fun_CacheTexture_Create_3D(const std::n_string &a2) {
    return reinterpret_cast<IDirect3DBaseTexture9 *(__cdecl *)(const std::n_string *)>(0x005008F0)(&a2);
}
// Fun_CacheTexture_Release .text 00500460 00000010 00000000 00000004 R . . . . . .
void Fun_CacheTexture_Release(std::n_string *a2) {
    assert(FALSE);
}

CIFSlotWithHelp *GetSlotWndByhgWnd(int hgWnd) {
    return reinterpret_cast<CIFSlotWithHelp *(__cdecl *)(char)>(0x00ba1140)(hgWnd);
}
void SendRestartRequest(char type) {
    reinterpret_cast<void (__stdcall *)(char)>(0x0081F030)(type);
}

int sub_4F9C50() {
    return reinterpret_cast<int (*)()>(0x4F9C50)();
}

// 009c3220
CICharactor *GetCharacterObjectByID_MAYBE(int uniqueid) {
    return reinterpret_cast<CICharactor *(__cdecl *)(int)>(0x009c3220)(uniqueid);
}

std::n_string GetKindredTextureFilePath(char param_1, int param_2) {
    return reinterpret_cast<std::n_string (__cdecl *)(char, int)>(0x0098caa0)(param_1, param_2);
}

void __stdcall WriteToChatWindow(ChatType type, const std::n_wstring &strRecipient, int uniqueid,
                                 const std::n_wstring &strMessage,
                                 char direction) {

    std::n_wstring strRecipientCopy = strRecipient;
    std::n_wstring strMessageCopy = strMessage;
   int signal = -2;
    std::n_wstring MessageTemp;
    std::n_wstring MessageTemp2;

   /* size_t start_pos2 = 0;
    const std::n_wstring& from2 = L"_";
    const std::n_wstring& to2= L"";
    while((start_pos2 = strMessageCopy.find(from2, start_pos2)) != std::string::npos) {
        strMessageCopy.replace(start_pos2, from2.length(), to2);
        start_pos2 += to2.length(); // Handles case where 'to' is a substring of 'from'
    }*/

    if (strMessageCopy.find('<') != std::string::npos && strMessageCopy.find('>') != std::string::npos )
    {
        for (int i=0;i<strMessageCopy.size();i++)
        {
            std::n_wstring ws = strMessageCopy.substr(i, 1);
            if(ws == L"<")
            {
                MessageTemp.append(ws.c_str());
                signal = i;
            }
            else if(i-signal ==1)
            {
                MessageTemp.append(L"\u0332");
                MessageTemp.append(ws.c_str());
                signal = i;
                if (ws == L">")
                    signal =0;
            }
            else
            {
                MessageTemp.append(ws.c_str());
            }
        }
        strMessageCopy = MessageTemp;
    }
    if (strMessageCopy.find(L"http") != std::string::npos)
    {

        for (int i=0;i<strMessageCopy.size();i++)
        {
            std::n_wstring ws = strMessageCopy.substr(i, 1);
                MessageTemp.append(L"\u0332");
                MessageTemp.append(ws.c_str());
        }
        strMessageCopy = MessageTemp;
    }

    CNIFCommunityWnd *communityWnd = g_pCGInterface->GetCommunityWnd();
    CNIFBlockWnd *someObj = communityWnd->GetBlockWnd();
    bool bIsBlocked = someObj->IsOnBlockList(strRecipientCopy);

    if (direction != 0 && bIsBlocked != 0) {
        switch (type) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 0xB:
            case 0x10:
                return;

            default:
                break;
        }
    }

    // Sanitize input
    // Remark: This is inefficient, make use of erase() both times
    std::n_wstring::size_type nextNewline;
    do {
        while (true) {
            nextNewline = strMessageCopy.find(L"\\n");
            if (nextNewline != std::n_wstring::npos) {

                std::n_wstring local_80 = strMessageCopy.substr(0, nextNewline);
                std::n_wstring local_208 = strMessageCopy.substr(nextNewline + 2, strMessageCopy.length());
                local_80.append(local_208);
                strMessageCopy = local_80;
            }
            int posEndOfLine = strMessageCopy.find(L"\n");
            if (posEndOfLine == std::n_wstring::npos)
                break;
            strMessageCopy.erase(posEndOfLine, 1);
        }
    } while (nextNewline != std::n_wstring::npos);

    D3DCOLOR color;
    switch (type) {
        default:
            color = D3DCOLOR_RGBA(255, 255, 255, 255);
            break;

        case 2:
            if (CGame::STA_FUN_004f9d00().field_4 == 0)
                return;
        case 10:
            color = D3DCOLOR_RGBA(0x9f, 0xff, 0xfe, 255);
            break;
        case 3:
        case 7:
            color = D3DCOLOR_RGBA(0xff, 0xae, 0xc3, 255);
            break;
        case 4:
            color = D3DCOLOR_RGBA(0x9a, 0xff, 0xd0, 255);
            break;
        case 5:
            color = D3DCOLOR_RGBA(0xff, 0xb5, 0x41, 255);
            break;
        case 6:
            color = D3DCOLOR_RGBA(0xff, 0xff, 0x00, 255);
            break;
        case 0xb:
            color = D3DCOLOR_RGBA(0xc2, 0xf5, 0x73, 255);
            break;
        case 0xd:
            color = D3DCOLOR_RGBA(0xdb, 0xad, 0xf8, 255);
            break;
        case 0x10:
            color = D3DCOLOR_RGBA(0x64, 0xc7, 0xff, 255);
            break;
    }

    std::n_wstring local_64;

    switch (type) {
        case CHAT_All:
        case CHAT_Global:
        case CHAT_Stall:
            local_64 = L":";
            break;

        case CHAT_PM: {
            const wchar_t *translatedIdent;
            if (direction == 0) {
                translatedIdent = TSM_GETTEXTPTR("UIIT_CHATERR_WHISPER_FROM_MESSAGE");
            } else {
                translatedIdent = TSM_GETTEXTPTR("UIIT_CHATERR_WHISPER_TO_MESSAGE");
            }

            // Remark: This is highly inefficient. TSM returns a n_wstring already!
            std::n_wstring directionWord(L"(");
            directionWord += translatedIdent;
            directionWord += L"):";

            local_64 += directionWord;
        }
            break;

        case CHAT_AllGM: {
            local_64 = L":";

            if (strMessageCopy.length() == 0)
                break;

            // If message starts with ';', make it appear like a normal player message
            if (strMessageCopy[0] == ';') {
                type = CHAT_All;
                color = D3DCOLOR_RGBA(255, 255, 255, 255);
                strMessageCopy.erase(0, 1);
            }
            // there would be a 'goto' leading past the if (type == CHAT_Stall)
        }
            break;

        case CHAT_Party:
            local_64 = L"(";
            local_64 += TSM_GETTEXTPTR("UIIT_CTL_PARTY");
            local_64 += L"):";
            break;

        case CHAT_Guild:
            local_64 = L"(";
            local_64 += TSM_GETTEXTPTR("UIIT_CTL_GUILD");
            local_64 += L"):";
            break;

        case CHAT_Notice: {
             g_pCGInterface->ShowMessage_Notice(strMessageCopy);

            local_64 = L"(";
            local_64 += TSM_GETTEXTPTR("UIIT_MSG_NOTIFY");
            local_64 += L"):";

            std::n_wstring tmp = local_64 + strMessageCopy;

            g_pCGInterface->FUN_00777c30(CHAT_AllGM, tmp.c_str(),0xffF296EA, 1);
            return;

        }

        case CHAT_Ask:
            local_64 = L"(ASK):";
            break;

        case CHAT_Union:
            local_64 = L"(";
            local_64 += TSM_GETTEXTPTR("UIIT_STT_GUILD_RESPECT_ALLY");
            local_64 += L"):";
            break;

        case CHAT_NPC:
            local_64 = L":";
            break;

        case CHAT_Academy:
            local_64 = L"(";
            local_64 += TSM_GETTEXTPTR("UIIT_CTL_TC_TRAININGCAMP" );
            local_64 += L"):";
            break;

        default:
            return;
    }

    if (type == CHAT_Stall) {
        std::n_wstring local_80 = strRecipientCopy + local_64 + strMessageCopy;
        g_pCGInterface->FUN_00778a10(1, local_80.c_str(), color);
        return;
    }
    if (type == CHAT_Global) {
        if (CPSMission::Gui_GlobalColors)
        {
            if (strMessageCopy.find(L"1`") == 0) {//red
                strMessageCopy.erase(0, 2);
                color =  D3DCOLOR_RGBA(255, 0, 0, 255);
            }
            else  if (strMessageCopy.find(L"2`") == 0) {//Blue
                strMessageCopy.erase(0, 2);
                color = D3DCOLOR_RGBA(0, 0, 255, 255);
            }
            else  if (strMessageCopy.find(L"3`") == 0) {//Green
                strMessageCopy.erase(0, 2);
                color = D3DCOLOR_RGBA(0, 255, 0, 255);
            }
            else   if (strMessageCopy.find(L"4`") == 0) {//aqua
                strMessageCopy.erase(0, 2);
                color = D3DCOLOR_RGBA(0, 248, 255, 255);
            }
            else if (strMessageCopy.find(L"5`") == 0) {//Orange
                strMessageCopy.erase(0, 2);
                color = 0xFF4500;
            }
            else  if (strMessageCopy.find(L"6`") == 0) {//Sky
                strMessageCopy.erase(0, 2);
                color = 0x008040;
            }
            else   if (strMessageCopy.find(L"7`") == 0) {//Purble
                strMessageCopy.erase(0, 2);
                color = 0x8b1a89;
            }
            else
                color = 0xFFFFFF00;
        }

        std::n_wstring local_80 = strRecipientCopy + local_64 + strMessageCopy;
        g_pCGInterface->FUN_00777c30(type, local_80.c_str(), color, 1);

        CICharactor *Char = 0;
        CLASSLINK_LOOP_BEGIN(CICharactor)
            if (obj->GetName() == strRecipientCopy) {
                Char = obj;
                break;
            }
        CLASSLINK_LOOP_END(CICharactor)

        if (Char != 0) {
            Char->ShowMessageAboveEntity(strMessageCopy, color);
        }

        return;
    }


    std::n_wstring local_80 = strRecipientCopy + local_64 + strMessageCopy;
    g_pCGInterface->FUN_00777c30(type, local_80.c_str(), color, 1);

    if (type == CHAT_PM) {
        g_pCGInterface->FUN_00777cf0(strRecipient);
        return;
    } else {
        if ((type == CHAT_All) || (type == CHAT_AllGM) || (type == CHAT_Global) || (type == CHAT_NPC)) {
            CICharactor *entity = 0;
            if (uniqueid == 0) {
                // We don't have an entity-id.
                // Try getting the entity by looking for the name ...
                CLASSLINK_LOOP_BEGIN(CICharactor)
                    if (obj->GetName() == strRecipientCopy) {
                        entity = obj;
                        break;
                    }
                CLASSLINK_LOOP_END(CICharactor)
            } else {
                entity = GetCharacterObjectByID_MAYBE(uniqueid);
            }

            // If we have an entity, display the message above it
            if (entity != 0) {
                entity->ShowMessageAboveEntity(strMessageCopy, color);
            }
        }
    }

}

GameCfg *Fun_GetCfgGame() {
    return reinterpret_cast<GameCfg *>(0x00eed578);
}
void __stdcall FUN_00bbda70(undefined4 a1) {
    reinterpret_cast<void(__stdcall *)(undefined4)>(0x00bbda70)(a1);
}
void FUN_009ef0c0(class CCompSimple *compound, std::n_string *str) {
    reinterpret_cast<void(__cdecl*)(class CCompSimple *, std::n_string*)>(0x009ef0c0)(compound, str);
}