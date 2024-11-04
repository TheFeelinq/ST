#include "CPSMission.h"
#include "GInterface.h"
#include "ClientNet/MsgStreamBuffer.h"
#include "IFSTChest.h"
#include "BSLib/multibyte.h"
#include "IFflorian0.h"
#include "GlobalDataManager.h"
#include "ObjectData.h"
#include "IFSTDpsMetter.h"
#include "GameDataExt.h"
#include "IFSTTaiXiu.h"
#include "IFSTDailyLogin.h"
#include "IFChatViewer.h"
#include "Rebot.h"
#include "CharacterDependentData.h"
#include "OptimizeCloth.h"
#include "Game.h"
#include "IFSTCharacterIcons.h"
#include "IFSTPetFilter.h"
#include "../../DiscordRichPresence/src/DiscordRichPresence/DiscordManager.h"
#include "ICMonster.h"
#include "../../../DevKit_DLL/src/Util.h"
#include <sstream>
#include <TlHelp32.h>
#include <HWID/HawidManager.h>
#include <HWID/base64.h>

const DWORD cdwPHBotOffset_1 = 0x00795AE5 + 1;
const DWORD cdwPHBotOffset_2 = 0x00795AFA + 1;
const DWORD cdwPHBotOffset_3 = 0x00796160 + 1;
const DWORD cdwPHBotOffset_4 = 0x00796175 + 1;

bool CPSMission::char_is_ready;
BYTE CPSMission::CurHawn = -1;

bool CPSMission::Gui_GrantName;
bool CPSMission::Gui_UniqueHistory;
bool CPSMission::Gui_CustomTitle;
bool CPSMission::Gui_SwitchTitle;
bool CPSMission::Gui_EventTimer;
bool CPSMission::Gui_CharacterLock;
bool CPSMission::Gui_CustomRank;
bool CPSMission::Gui_ColorsRender;
bool CPSMission::Gui_TotalPoint;
bool CPSMission::Gui_GlobalColors;
bool CPSMission::Gui_CustomNPC;
bool CPSMission::Npc_Is_Opening;
bool CPSMission::Icon_TaiXiu;
bool CPSMission::Icon_DailyLogin;
bool CPSMission::Icon_ExtralFeature;
bool CPSMission::Icon_ReBot;
bool CPSMission::Icon_Chest;
bool CPSMission::Icon_Event;
bool CPSMission::XSMB_ENABLE;
bool CPSMission::LOTO_ENABLE;
bool CPSMission::Icon_LiveStream;
bool CPSMission::Double_Click_ToLogin;
bool CPSMission::m_IsRegionChange =false;
bool CPSMission::m_CharSelectOn =false;
std::n_wstring CPSMission::CharNameSelected;
std::n_wstring CPSMission::CharNameRequest;
std::string CPSMission::DiscordUrl;
std::string CPSMission::FacebookUrl;
std::string CPSMission::WebsiteUrl;
std::string CPSMission::m_szToken;
int CPSMission::m_UserJID = 0;

#define SERVER_GROUP_SPAWN_BEGIN  0x3017
#define SERVER_GROUP_SPAWN_DATA  0x3019
#define SERVER_GROUP_SPAWN_END  0x3018
#define SERVER_SINGLE_OBJECT_DESPAWN  0x3016


UINT8 g_GroupSpawn_Type;
std::vector<DWORD> g_despawned_objects;
bool handled = false;
wchar_t* CPSMission::Convert(std::n_string name)
{
    wchar_t buffer[1000];
    swprintf_s(buffer, L"%S", name.c_str());
    return buffer;
}
DWORD find_by_process_name(const char * processName)
{
    DWORD pid = 0;
    HANDLE hndl = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPMODULE, 0);
    if (hndl)
    {
        PROCESSENTRY32  process = { sizeof(PROCESSENTRY32) };
        Process32First(hndl, &process);
        do
        {
            if (_stricmp(process.szExeFile, processName) == 0)
            {
                pid = process.th32ProcessID;
                break;
            }
        } while (Process32Next(hndl, &process));

        CloseHandle(hndl);
    }

    return pid;
}

void RemoveExistingUniqueData(const DWORD dead_object)
{
    if (g_pCICPlayer)
    {
        bool remove_key_player = false;
        bool remove_key_unique = false;

        UINT32 remove_val_key = 0;

        std::map<int, int>::iterator it_1 = UniqueTargetHashmapPlayer.find(dead_object);
        if (it_1 != UniqueTargetHashmapPlayer.end()) //player gitti, player map'ten playerı sil, unique map'ten value 0 yap.
        {
            //printf("player kayboldu\n");
            remove_key_player = true;
            remove_val_key = it_1->second;
        }

        if (!remove_key_player) //player değil ise bak
        {
            std::map<int, int>::iterator it_2 = UniqueTargetHashmap.find(dead_object);
            if (it_2 != UniqueTargetHashmap.end()) //unique gitti, player mapten unique'i 0 yap, unique map'ten unique'i sil.
            {
                //printf("unique kayboldu\n");
                remove_key_unique = true;
                remove_val_key = it_2->first;

                CICPlayer* LastTarget = g_pCICPlayer->GetCICPlayerByUniqueID(it_2->second);
                if (LastTarget)
                {
                    LastTarget->RemoveEffect(g_CGlobalDataManager->GetEffectIdByName(L"SYSTEM_AGGRO_EFFECT"));
                }
            }
        }
        else //player gitmiş
        {
            UniqueTargetHashmapPlayer.erase(remove_val_key);

            if (UniqueTargetHashmap.count(remove_val_key) > 0)
                UniqueTargetHashmap[remove_val_key] = 0;

            return;
        }

        if (remove_key_unique)
        {
            UniqueTargetHashmap.erase(remove_val_key);

            if (UniqueTargetHashmapPlayer.count(remove_val_key) > 0)
                UniqueTargetHashmapPlayer[remove_val_key] = 0;
        }
    }
}

void CPSMission::SkillDamageParsing (class CMsgStreamBuffer* MsgBuffer)
{
    byte hasDamage;
    MsgBuffer->Read(&hasDamage, 1);
    if (hasDamage==1)
    {
        byte hitCount ;
        MsgBuffer->Read(&hitCount, 1);
        byte targetCount;
        MsgBuffer->Read(&targetCount, 1);
        for (byte j = 0; j < targetCount; j++)
        {
            DWORD32 targetUniqueID;
            MsgBuffer->Read(&targetUniqueID, 4);
            byte dmgEffect ;
            MsgBuffer->Read(&dmgEffect, 1);
            if (( dmgEffect & 0x80 ) != 0 || ( dmgEffect & 0x2 ) != 0 || ( dmgEffect & 0x8 ) != 0)
                continue;

            // Since there it's not enough flags to check, then this way have to be used
            byte dmgState ;
            MsgBuffer->Read(&dmgState, 1);
            DWORD32 dmgValue;
            MsgBuffer->Read(&dmgValue, 4);
            if (( dmgState & 32 ) != 0 )
            {
                wchar_t message[1000];
                swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_IGNORE_DAMAGE_TOOLTIP"),dmgValue);
                if (g_pCGInterface->Get_SelectedObjectId() != 0) {
                    CIObject *SelectdObject = Rebot::FindBaseByUID(g_pCGInterface->Get_SelectedObjectId());
                    if (!strcmp(SelectdObject->GetRuntimeClass()->m_lpszClassName, "CICMonster")) {
                        CICMonster *SelectdUser = (CICMonster *) SelectdObject;
                        SelectdUser->ShowMessageAboveEntity(message,0xFFCCFF00);
                    }
                }
                /*g_pCGInterface->GetCIFSTEffectGUI()->SetIgnoreDamageTime(9);
                wchar_t message[1000];
                swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_IGNORE_DAMAGE_TOOLTIP"),dmgValue);
                CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
                int color = D3DCOLOR_ARGB(255, 255, 0, 0);
                systemmessage->WriteMessage(0xFF, color, message, 0, 1);*/
            }

            byte unkByte01 ;
            MsgBuffer->Read(&unkByte01, 1);
            byte unkByte02 ;
            MsgBuffer->Read(&unkByte02, 1);
            byte unkByte03 ;
            MsgBuffer->Read(&unkByte03, 1);

        }
    }
}
int CPSMission::OnPacketRecv(CMsgStreamBuffer* MsgBuffer)
{


    ////Plus Notice
    if (MsgBuffer->msgid() == 0x180D)
    {
        std::n_string ItemName;
        std::n_string CharName;
        int PlusValue=0;
        int Adv = 0;
        *MsgBuffer >> ItemName >> CharName >> PlusValue>> Adv;
        wchar_t* NewMsg = new wchar_t[1024];
        wchar_t* NewMsg2 = new wchar_t[1024];
        wchar_t NoticeStr[1000];
        swprintf_s(NoticeStr, TSM_GETTEXTPTR("UIIT_ST_PLUS_NOTICE3"));
        wsprintfW(NewMsg2,L"%S:<%S> %s", CharName.c_str(), ItemName.c_str() ,NoticeStr);
        if(Adv==0)
        {
            wsprintfW(NewMsg,TSM_GETTEXTPTR("UIIT_ST_PLUS_NOTICE1"), CharName.c_str(), ItemName.c_str(),PlusValue);
        } else
        {
            wsprintfW(NewMsg,TSM_GETTEXTPTR("UIIT_ST_PLUS_NOTICE2"), CharName.c_str(), ItemName.c_str(),PlusValue+Adv,Adv);
        }
        std::n_wstring strMessageCopy = NewMsg2;
        int signal = -2;
        std::n_wstring MessageTemp;
        if (strMessageCopy.find('<') != std::string::npos && strMessageCopy.find('>') != std::string::npos)
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

        g_pCGInterface->ShowMessage_Purble(NewMsg);
        CIFChatViewer* chatView = (CIFChatViewer*)g_pCGInterface->m_IRM.GetResObj(1, 1);
        chatView->WriteToChatW(MessageTemp.c_str(), D3DCOLOR_ARGB(255, 255, 0, 0), 1);
        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0xb021)
    {
        UINT uniqueID;
        *MsgBuffer >> uniqueID;
        // Check my character movements
        if (uniqueID == GET_OWN_GAME_ID()) {

            if (m_IsRegionChange)
            {
                m_IsRegionChange = false;
                DiscordManager::UpdateState();
            }

            // Read packet
            byte hasCoordinate;
            *MsgBuffer >> hasCoordinate;
            if (hasCoordinate == 1) {
                short newRegionID;
                *MsgBuffer >> newRegionID;
                if (g_pCICPlayer->GetRegion().r != newRegionID)
                {
                    // We guess the next movement will be from a new region
                    m_IsRegionChange = true;
                }
                if (OptimizeCloth::IsHideClothesRegion(OptimizeCloth::GetCurRegionID()))
                {
                    CLASSLINK_LOOP_BEGIN(CICPlayer)
                        OptimizeCloth::ApplyHideNameClothes(obj);
                    CLASSLINK_LOOP_END(CICPlayer)
                }
            }
        }

        MsgBuffer->m_currentReadBytes = 0;
    }
    if (MsgBuffer->msgid() == 0x190D)
    {
        int Slot;
        int Adv = 0;
        int PlusValue=0;
        std::n_string CharName;
        *MsgBuffer >> Slot >> CharName >> PlusValue>> Adv;
        CSOItem *this_03 = g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(Slot-0xD);
        const wchar_t *ItemName = g_CTextStringManager->GetStringTextByCode(this_03->GetObjectData()->ObjNameStrID.c_str())->c_str();
        int ItemID = this_03->GetObjectData()->ObjID;
            std::n_wstring ItemNameW = std::n_wstring(ItemName);
            UINT16 Size = ItemNameW.length();
            NEWMSG(0x170C)
                pReq.Write(&Size, 2);
                pReq.Write(ItemName, Size * 2);
                pReq.Write(&Slot, 1);
                // pReq << *this_03;
            SENDMSG()
            NEWMSG(0x180D)
                pReq.Write(&Size, 2);
                pReq.Write(ItemName, Size * 2);
                pReq << CharName;
                pReq << PlusValue;
                pReq << Adv;
            SENDMSG()

        MsgBuffer->FlushRemaining();
    }

    ////FORTRESS KILLS
    if (MsgBuffer->msgid() == 0x5122)
    {
        BYTE sCount;
        std::n_string GuildName;
        std::n_string Kills;
        *MsgBuffer >> sCount;
        BYTE i = 0;

        g_pCGInterface->GetFtwCunterGUI()->Clear();

        while (i < sCount && sCount > 0)
        {
            i++;
            *MsgBuffer >> GuildName >> Kills;
            g_pCGInterface->GetFtwCunterGUI()->WriteLine(i, TO_WSTRING(GuildName).c_str(), TO_WSTRING(Kills).c_str());
            //std::wcout << "Guild " << TO_WSTRING(GuildName).c_str() << " Kills " << TO_WSTRING(Kills).c_str() << std::endl;
        }

        g_pCGInterface->GetFtwCunterGUI()->ResetPosition();
        g_pCGInterface->GetFtwCunterGUI()->ShowGWnd(true);

        MsgBuffer->FlushRemaining();
    }
    /// pvp challengeanswer
    if (MsgBuffer->msgid() == 0x9987)//Show Form
    {

        BYTE ID = 0;
        std::n_string Gold;
        std::n_string CharNameSend;
        int CharID = 0;
        *MsgBuffer >> ID >> Gold>>CharNameSend>>CharID;
        if(ID==3)
        {
            wchar_t buffer[1000];
            swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_STT_PVP_CHALLENGE_DECLINE"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 213, 197, 136);
            systemmessage->WriteMessage(0xFF, color, buffer, 0, 1);
        }
        if(ID==2)
        {
            wchar_t buffer[1000];
            swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_STT_PVP_CHALLENGE_NO_REP"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 213, 197, 136);
            systemmessage->WriteMessage(0xFF, color, buffer, 0, 1);
        }
        if (ID==1)
        {

            g_pCGInterface->GetPvpChallengeAnswerGUI()->ShowGWnd(true);
            wchar_t buffer[255];
            swprintf_s(buffer, L"%S", CharNameSend.c_str());
            g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label3->SetText(buffer);

            wchar_t buffer1[255];
            swprintf_s(buffer1,  L"%S", Gold.c_str());
            g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label4->SetText(buffer1);
            g_pCGInterface->GetPvpChallengeAnswerGUI()->SetChatBlocked(60);
            switch(CharID)
            {
                case 1907:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man1.ddj", 0, 0);
                }
                    break;
                case 1908:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man2.ddj", 0, 0);
                }
                    break;
                case 1909:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man3.ddj", 0, 0);
                }
                    break;
                case 1910:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man4.ddj", 0, 0);
                }
                    break;
                case 1911:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man5.ddj", 0, 0);
                }
                    break;
                case 1912:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man6.ddj", 0, 0);
                }
                    break;
                case 1913:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man7.ddj", 0, 0);
                }
                    break;
                case 1914:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man8.ddj", 0, 0);
                }
                    break;
                case 1915:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man9.ddj", 0, 0);
                }
                    break;
                case 1916:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man10.ddj", 0, 0);
                }
                    break;
                case 1917:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man11.ddj", 0, 0);
                }
                    break;
                case 1918:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man12.ddj", 0, 0);
                }
                    break;
                case 1919:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_man13.ddj", 0, 0);
                }
                    break;
                case 1920:
                {


                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman1.ddj", 0, 0);
                }
                    break;
                case 1921:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman2.ddj", 0, 0);
                }
                    break;
                case 1922:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman3.ddj", 0, 0);
                }
                    break;
                case 1923:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman4.ddj", 0, 0);
                }
                    break;
                case 1924:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman5.ddj", 0, 0);
                }
                    break;
                case 1925:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman6.ddj", 0, 0);
                }
                    break;
                case 1926:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman7.ddj", 0, 0);
                }
                    break;
                case 1927:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman8.ddj", 0, 0);
                }
                    break;
                case 1928:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman9.ddj", 0, 0);
                }
                    break;
                case 1929:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman10.ddj", 0, 0);
                }
                    break;
                case 1930:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman11.ddj", 0, 0);
                }
                    break;
                case 1931:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman12.ddj", 0, 0);
                }
                    break;
                case 1932:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_ch_woman13.ddj", 0, 0);
                }
                    break;

                case 14875:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man1.ddj", 0, 0);
                }
                    break;
                case 14876:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man2.ddj", 0, 0);
                }
                    break;
                case 14877:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man3.ddj", 0, 0);
                }
                    break;
                case 14878:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man4.ddj", 0, 0);
                }
                    break;
                case 14879:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man5.ddj", 0, 0);
                }
                    break;
                case 14880:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man6.ddj", 0, 0);
                }
                    break;
                case 14881:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man7.ddj", 0, 0);
                }
                    break;
                case 14882:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man8.ddj", 0, 0);
                }
                    break;
                case 14883:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man9.ddj", 0, 0);
                }
                    break;
                case 14884:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man10.ddj", 0, 0);
                }
                    break;
                case 14885:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man11.ddj", 0, 0);
                }
                    break;
                case 14886:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man12.ddj", 0, 0);
                }
                    break;
                case 14887:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_man13.ddj", 0, 0);
                }
                    break;

                case 14888:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman1.ddj", 0, 0);
                }
                    break;
                case 14889:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman2.ddj", 0, 0);
                }
                    break;
                case 14890:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman3.ddj", 0, 0);
                }
                    break;
                case 14891:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman4.ddj", 0, 0);
                }
                    break;
                case 14892:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman5.ddj", 0, 0);
                }
                    break;
                case 14893:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman6.ddj", 0, 0);
                }
                    break;
                case 14894:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman7.ddj", 0, 0);
                }
                    break;
                case 14895:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman8.ddj", 0, 0);
                }
                    break;
                case 14896:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman9.ddj", 0, 0);
                }
                    break;
                case 14897:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman10.ddj", 0, 0);
                }
                    break;
                case 14898:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman11.ddj", 0, 0);
                }
                    break;
                case 14899:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman12.ddj", 0, 0);
                }
                    break;
                case 14900:
                {

                    g_pCGInterface->GetPvpChallengeAnswerGUI()->m_custom_label1->TB_Func_13("interface\\character\\char_eu_woman13.ddj", 0, 0);
                }
                    break;
            }

        }


        MsgBuffer->FlushRemaining();
    }
    ///
    if (MsgBuffer->msgid() == 0x3038)
    {
        DWORD dwPlayerGID;
        *MsgBuffer >> dwPlayerGID;

        CICPlayer* pPlayer = OptimizeCloth::GetPlayerByGameID(dwPlayerGID);
        if (pPlayer)
            OptimizeCloth::ApplyHideNameClothes(pPlayer);

        MsgBuffer->m_currentReadBytes = 0;
    }
    if (MsgBuffer->msgid() == 0x3039)
    {
        DWORD dwPlayerGID;
        *MsgBuffer >> dwPlayerGID;

        CICPlayer* pPlayer = OptimizeCloth::GetPlayerByGameID(dwPlayerGID);
        if (pPlayer)
            OptimizeCloth::ApplyHideNameClothes(pPlayer);

        MsgBuffer->m_currentReadBytes=0;
    }
    if (MsgBuffer->msgid() == SERVER_GROUP_SPAWN_BEGIN)
    {
        byte g_GroupSpawn_Types;
        MsgBuffer->Read(&g_GroupSpawn_Types, 1);
        g_GroupSpawn_Type =g_GroupSpawn_Types;
        MsgBuffer->m_currentReadBytes=0;
    }
    if (MsgBuffer->msgid() == SERVER_GROUP_SPAWN_DATA) // possible the crash is here
    {
        if (g_GroupSpawn_Type == 2)
        {
            for (size_t i = 0; i < ( MsgBuffer->m_availableBytesForReading / 4); i++)
            {
                DWORD dead_object;
                MsgBuffer->Read(&dead_object, 4);
                g_despawned_objects.push_back(dead_object);
            }
        }

        MsgBuffer->m_currentReadBytes=0;
    }
    if (MsgBuffer->msgid() == SERVER_GROUP_SPAWN_END)
    {
        if (g_GroupSpawn_Type == 2)
        {
            for (std::vector<DWORD>::iterator it = g_despawned_objects.begin(); it != g_despawned_objects.end(); ++it)
            {
                RemoveExistingUniqueData(*it);
            }
/*
            for (std::vector<DWORD>::iterator::value_type &shit : g_despawned_objects)
            {
                RemoveExistingUniqueData(shit);
            }
*/

            //g_despawned_objects.clear();
            //g_despawned_objects->shrink_to_fit();
        }
        MsgBuffer->m_currentReadBytes=0;
    }
    if (MsgBuffer->msgid() == SERVER_SINGLE_OBJECT_DESPAWN)
    {
        if (g_pCICPlayer)
        {
            DWORD dead_object;
            MsgBuffer->Read(&dead_object, 4);

            RemoveExistingUniqueData(dead_object);
        }

        MsgBuffer->m_currentReadBytes=0;
    }


    /// Npc Open Detect
    if (MsgBuffer->msgid() == 0xB046)
    {
        BYTE Status;
        *MsgBuffer >> Status;
        if(Status==1)
        Npc_Is_Opening=true;
        MsgBuffer->m_currentReadBytes=0;
    }
    /// Npc Close Detect
    if (MsgBuffer->msgid() == 0xB04B)
    {
        BYTE Status;
        *MsgBuffer >> Status;
        if(Status==1)
            Npc_Is_Opening=false;
        MsgBuffer->m_currentReadBytes=0;
    }
    if (MsgBuffer->msgid() == 0x3080)
    {
        BYTE Action;
        int SrcUinqueID;
        *MsgBuffer >> Action >> SrcUinqueID;
        if(Action==4 && Rebot::Config.AcceptRes && Rebot::RebotStart)
        {
            NEWMSG(0x3080)
                pReq << (byte)1;
                pReq << (byte)1;
            SENDMSG()
        }
        MsgBuffer->m_currentReadBytes=0;
    }
    /// SERVER_CHARACTER_INFO_UPDATE
    /*if (MsgBuffer->msgid() == 0x304E)
    {
        BYTE updateType;
        BYTE BerserkPoint;
        *MsgBuffer >> updateType;
        if(updateType==4)
        {
            *MsgBuffer >> BerserkPoint;
            Rebot::BerSerkPoint=BerserkPoint;
        }
        MsgBuffer->m_currentReadBytes=0;
    }*/
    /// Npc Close Detect
    if (MsgBuffer->msgid() == 0xB034)
    {
        BYTE Status;
        BYTE Action;
        BYTE Slot;
        UINT32 PetUniqueID;
        UINT32 unk;
        UINT32 ItemID;
        *MsgBuffer >> Status;
        if(Status==1)
        {
            *MsgBuffer>>Action;
            if(Action==6)
            {
                *MsgBuffer>>Slot;
                if(Slot != 0xFE)
                {
                    *MsgBuffer>>unk>>ItemID;
                    static const CItemData *data = NULL;
                    data = g_CGlobalDataManager->GetItemData(ItemID);
                    if( data->Rarity==2 || data->Rarity==6)
                    {
                        g_pCGInterface->GetCIFSTEffectGUI()->m_ChatLinking->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                        g_pCGInterface->GetCIFSTEffectGUI()->SetPickupTime(20);

                    }
                }

            }
            if(Action==0x11)
            {
                *MsgBuffer>>PetUniqueID>>Slot>>unk>>ItemID;

                static const CItemData *data = NULL;
                data = g_CGlobalDataManager->GetItemData(ItemID);
                if( data->Rarity==2 || data->Rarity==6)
                {

                    g_pCGInterface->GetCIFSTEffectGUI()->m_ChatLinking->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                    g_pCGInterface->GetCIFSTEffectGUI()->SetPickupTime(20);

                }
            }
            /*if(Action==0)
            {
                byte SlotBeforeMove;
                byte SlotAfterMove;
                MsgBuffer->Read(&SlotBeforeMove, 1);
                MsgBuffer->Read(&SlotAfterMove, 1);
                if(SlotBeforeMove == g_pCGInterface->GetExtraFeatureGUI()->m_dame_abs_slot+0xD)
                {
                    if(g_pCGInterface->GetExtraFeatureGUI()->IsVisible())
                    {
                        g_pCGInterface->GetExtraFeatureGUI()->ShowGWnd(false);
                    }

                    g_pCGInterface->GetExtraFeatureGUI()->m_slot1->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetExtraFeatureGUI()->m_dame_abs_slot=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetExtraFeatureGUI()->m_dame_inc_slot+0xD)
                {
                    if(g_pCGInterface->GetExtraFeatureGUI()->IsVisible())
                    {
                        g_pCGInterface->GetExtraFeatureGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetExtraFeatureGUI()->m_slot2->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetExtraFeatureGUI()->m_dame_inc_slot=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetExtraFeatureGUI()->m_dame_absorbbubble_slot+0xD)
                {
                    if(g_pCGInterface->GetExtraFeatureGUI()->IsVisible())
                    {
                        g_pCGInterface->GetExtraFeatureGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetExtraFeatureGUI()->m_slot3->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetExtraFeatureGUI()->m_dame_absorbbubble_slot=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetExtraFeatureGUI()->m_dame_Increasebubble_slot+0xD)
                {
                    if(g_pCGInterface->GetExtraFeatureGUI()->IsVisible())
                    {
                        g_pCGInterface->GetExtraFeatureGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetExtraFeatureGUI()->m_slot4->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetExtraFeatureGUI()->m_dame_Increasebubble_slot=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->HP_SLOT+0xD)
                {
                    if(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot1->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->HP_SLOT=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->MP_SLOT+0xD)
                {
                    if(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot2->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->MP_SLOT=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->VIGOR_SLOT+0xD)
                {
                    if(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot3->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->VIGOR_SLOT=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ABNORMAL_SLOT+0xD)
                {
                    if(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot4->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ABNORMAL_SLOT=SlotAfterMove-0xD;
                }
            }*/
        }

        MsgBuffer->m_currentReadBytes=0;
    }
    /// 3015
/*    if (MsgBuffer->msgid() == 0x3015)
    {
        int ObjID;
        *MsgBuffer >> ObjID;
        if(g_pCICPlayer)
        {
            int petBase = Rebot::get_pet_bytype(2);
            if (0 != petBase && 0 != *(DWORD32*)(petBase + 0x04))
            {
                int uniqueid = *(DWORD32*)(petBase + 0x04);
                int nItems[1024] = { 0 };
                Rebot::get_itemlist(nItems);

                for (int i = 0; i < 1024; i ++)
                {
                    ITEM_INFO ii = { 0 };
                    if (0 != nItems[i] && Rebot::get_iteminfo(ii, nItems[i]))
                    {
                        if (ii.item_pickable)
                        {
                            printf("UNIDEID %d", ii.item_id);

                            NEWMSG(0x70C5)
                                pReq << uniqueid;
                                pReq << (byte)8;
                                pReq << ii.item_id;
                            SENDMSG()
                        }
                    }
                }
*//*                if(ObjID != 0)
                {
                    static const CItemData *data = NULL;
                    data = g_CGlobalDataManager->GetItemData(ObjID);
                    if (data != NULL) {
                        NEWMSG(0x70C5)
                                pReq << uniqueid;
                                pReq << (byte)8;
                                pReq << data->m_id;

                        SENDMSG()
                       // CIFSTPetFilter::itemTypeName = data->m_codeName128.c_str();
                    }
                }*//*
            }
        }

        MsgBuffer->m_currentReadBytes=0;
    }*/
   /* if (MsgBuffer->msgid() == 0xb034)
    {
        byte bSuccessFlag;
        MsgBuffer->Read(&bSuccessFlag, 1);
        if (g_pCICPlayer && bSuccessFlag == 1 )
        {
            byte Action;
            MsgBuffer->Read(&Action, 1);
            if(Action==0)
            {
                byte SlotBeforeMove;
                byte SlotAfterMove;
                MsgBuffer->Read(&SlotBeforeMove, 1);
                MsgBuffer->Read(&SlotAfterMove, 1);
                if(SlotBeforeMove == g_pCGInterface->GetExtraFeatureGUI()->m_dame_abs_slot+0xD)
                {
                    if(g_pCGInterface->GetExtraFeatureGUI()->IsVisible())
                    {
                        g_pCGInterface->GetExtraFeatureGUI()->ShowGWnd(false);
                    }

                    g_pCGInterface->GetExtraFeatureGUI()->m_slot1->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetExtraFeatureGUI()->m_dame_abs_slot=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetExtraFeatureGUI()->m_dame_inc_slot+0xD)
                {
                    if(g_pCGInterface->GetExtraFeatureGUI()->IsVisible())
                    {
                        g_pCGInterface->GetExtraFeatureGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetExtraFeatureGUI()->m_slot2->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetExtraFeatureGUI()->m_dame_inc_slot=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetExtraFeatureGUI()->m_dame_absorbbubble_slot+0xD)
                {
                    if(g_pCGInterface->GetExtraFeatureGUI()->IsVisible())
                    {
                        g_pCGInterface->GetExtraFeatureGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetExtraFeatureGUI()->m_slot3->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetExtraFeatureGUI()->m_dame_absorbbubble_slot=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetExtraFeatureGUI()->m_dame_Increasebubble_slot+0xD)
                {
                    if(g_pCGInterface->GetExtraFeatureGUI()->IsVisible())
                    {
                        g_pCGInterface->GetExtraFeatureGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetExtraFeatureGUI()->m_slot4->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetExtraFeatureGUI()->m_dame_Increasebubble_slot=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->HP_SLOT+0xD)
                {
                    if(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot1->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->HP_SLOT=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->MP_SLOT+0xD)
                {
                    if(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot2->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->MP_SLOT=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->VIGOR_SLOT+0xD)
                {
                    if(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot3->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->VIGOR_SLOT=SlotAfterMove-0xD;
                }
                else if (SlotBeforeMove == g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ABNORMAL_SLOT+0xD)
                {
                    if(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowGWnd(false);
                    }
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot4->FUN_006871d0(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(SlotAfterMove-0xD));
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ABNORMAL_SLOT=SlotAfterMove-0xD;
                }
            }
        }

        MsgBuffer->m_currentReadBytes=0;
    }*/
    /// 0xb071
    if (MsgBuffer->msgid() == 0xb071)
    {
        byte bSuccessFlag;
        MsgBuffer->Read(&bSuccessFlag, 1);
        if (g_pCICPlayer && bSuccessFlag == 1 )
        {
            DWORD32 SkillID;
            MsgBuffer->Read(&SkillID, 4);
            DWORD32 AttackerID;
            MsgBuffer->Read(&AttackerID, 4);
            SkillDamageParsing(MsgBuffer);
        }

    MsgBuffer->m_currentReadBytes=0;
    }
    /// 0xb070

    if (MsgBuffer->msgid() == 0xb070)// skill casting
    {
        byte bSuccessFlag;
        MsgBuffer->Read(&bSuccessFlag, 1);

        if (g_pCICPlayer && bSuccessFlag == 1 )//&& MsgBuffer->m_currentReadBytes >= 20) // i'am just checking static size here, so i guess no any problems may occur while parsing.
        {
            byte _type;
            MsgBuffer->Read(&_type, 1);
            byte _reason;
            MsgBuffer->Read(&_reason, 1);

            if (_type == 2)//Attack action
            {
                DWORD32 SkillID;
                MsgBuffer->Read(&SkillID, 4);
                DWORD32 AttackerID;
                MsgBuffer->Read(&AttackerID, 4);
                DWORD32 SkillInstanceUniqueID;
                MsgBuffer->Read(&SkillInstanceUniqueID, 4);
                DWORD32 AttackedID;
                MsgBuffer->Read(&AttackedID, 4);
                if (AttackerID > 0)//Attacker ID will never be 0
                {
                    //well, i'm stressed the one that i've used here,GetCICPlayerByUniqueID this function is nullable
                    //well, no problems but I firstly need to verify that parsing xD kk
                    CICPlayer *CICAttacker = g_pCICPlayer->GetCICPlayerByUniqueID(AttackerID);
                    DWORD check_shit = *(DWORD*)(CICAttacker);
                    if (CICAttacker && check_shit == 0xDE26C4) // checking if the unique id is MOB exactly a MOnster you know :D ye but the thing is that those client functions are already crashable
                    {
                        if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
                        {
                            if (CharData* uqdata = g_datamanager->GetCharData(CICAttacker->GetObjID()))
                            {
                                if (uqdata && (uqdata->Rarity == 3 || uqdata->Rarity == 8))
                                {
                                    //printf("ptr = %02x\n", CICAttacker);
                                    DWORD effect = g_CGlobalDataManager->GetEffectIdByName(L"SYSTEM_AGGRO_EFFECT");
                                    std::map<int, int>::iterator it = UniqueTargetHashmap.find(AttackerID);
                                    if (it == UniqueTargetHashmap.end()) // first attack, let the shit begin.
                                    {
                                        UniqueTargetHashmap[AttackerID] = AttackedID;//i'am using these maps for unique target, lel this packet is a pain in the ass, i hope you are parsing it correctly xDD
                                        UniqueTargetHashmapPlayer[AttackedID] = AttackerID;
                                        CICPlayer *CICAttacked = g_pCICPlayer->GetCICPlayerByUniqueID(AttackedID);
                                        if (CICAttacked)
                                        {
                                            CICAttacked->MakeEffect(effect);
                                        }
                                    }
                                    else
                                    {
                                        if (it->second != AttackedID) // Attacker is changed, let them switch.
                                        {
                                            UINT32 oldTarget = it->second;
                                            CICPlayer *CICOldTarget = g_pCICPlayer->GetCICPlayerByUniqueID(oldTarget);
                                            if (CICOldTarget) CICOldTarget->RemoveEffect(effect);
                                            CICPlayer *CICNewTarget = g_pCICPlayer->GetCICPlayerByUniqueID(AttackedID);
                                            if (CICNewTarget) CICNewTarget->MakeEffect(effect);
                                            UniqueTargetHashmap[AttackerID] = AttackedID;
                                            UniqueTargetHashmap[AttackedID] = AttackedID;
                                            UniqueTargetHashmapPlayer.erase(oldTarget);
                                        }
                                        else if (it->second == AttackedID) //attacker is same, check if he still have the effect
                                        {
                                            CICPlayer *CICCurrentTarget = g_pCICPlayer->GetCICPlayerByUniqueID(AttackedID);
                                            if (CICCurrentTarget)
                                            {
                                                if (CICCurrentTarget->GetObjEffect() != effect)//Lemme show u so its safe to use.
                                                    CICCurrentTarget->MakeEffect(effect);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                SkillDamageParsing(MsgBuffer);

            }
        }
        else
        {
            byte _type;
            MsgBuffer->Read(&_type, 1);
            switch (_type) {
                case 0x4:
                    //g_pCGInterface->UseItemInBackpack(0);
                    break;
                case 0x5:
                    break;
                case 0x6:
                    Rebot::InvalidObjects.push_back(Rebot::SelectObj);
                    Rebot::SelectObj = 0;
                    break;
                case 0x10:
                    Rebot::InvalidObjects.push_back(Rebot::SelectObj);
                    Rebot::SelectObj = 0;
                    break;
                case 0xC:
                    break;
                case 0xD:
                    break;
                case 0xE:
                    break;
                case 0xF:
                    break;
                default:
                    break;
            }
        }
        MsgBuffer->m_currentReadBytes=0;
    }

    /// lottery event
    if (MsgBuffer->msgid() == 0x9945)
    {

        std::n_string SumPlayerReg;
        std::n_string SumTotalGold;
        std::n_string SumTotalSilk;
        std::n_string LotteryTime;
        *MsgBuffer >> SumPlayerReg >> SumTotalGold>>SumTotalSilk>>LotteryTime;

            wchar_t buffer[255];
            swprintf_s(buffer,L"%S", SumPlayerReg.c_str());
            g_pCGInterface->GetEventLotteryGUI()->m_custom_label8->SetText(buffer);
            wchar_t buffer1[255];
            swprintf_s(buffer1,L"%S", SumTotalGold.c_str());
            g_pCGInterface->GetEventLotteryGUI()->m_custom_label4->SetText(buffer1);
            wchar_t buffer2[255];
            swprintf_s(buffer2,L"%S", SumTotalSilk.c_str());
            g_pCGInterface->GetEventLotteryGUI()->m_custom_label3->SetText(buffer2);
            wchar_t buffer3[255];
            swprintf_s(buffer3,L"%S", LotteryTime.c_str());
            g_pCGInterface->GetEventLotteryGUI()->m_custom_label10->SetText(buffer3);

        MsgBuffer->FlushRemaining();
    }
    /// Daily login
    if (MsgBuffer->msgid() == 0x9924)// player count
    {
        int Nhan1Ngay;
        int Nhan3Ngay;
        int Nhan5Ngay;
        int Nhan7Ngay;
        int Nhan10Ngay;
        int Nhan13Ngay;
        int Nhan16Ngay;
        int Nhan19Ngay;
        int Nhan22Ngay;
        int Nhan25Ngay;
        int SoNgay;
        std::n_string Icon_Moc1;
        std::n_string Icon_Moc3;
        std::n_string Icon_Moc5;
        std::n_string Icon_Moc7;
        std::n_string Icon_Moc10;
        std::n_string Icon_Moc13;
        std::n_string Icon_Moc16;
        std::n_string Icon_Moc19;
        std::n_string Icon_Moc22;
        std::n_string Icon_Moc25;
        *MsgBuffer >>Nhan1Ngay>>Nhan3Ngay>>Nhan5Ngay>>Nhan7Ngay>>Nhan10Ngay>>Nhan13Ngay>>Nhan16Ngay>>Nhan19Ngay>>Nhan22Ngay>>Nhan25Ngay>>SoNgay>>Icon_Moc1>>Icon_Moc3>>Icon_Moc5>>Icon_Moc7>>Icon_Moc10>>Icon_Moc13>>Icon_Moc16>>Icon_Moc19>>Icon_Moc22>>Icon_Moc25 ;
        CIFDailyLogin *main1 = reinterpret_cast<CIFDailyLogin *>(g_pCGInterface->m_IRM.GetResObj(5096, 1));


        main1->m_custom_label27->TB_Func_13(Icon_Moc1.c_str(), 0, 0);
        main1->m_custom_label26->TB_Func_13(Icon_Moc3.c_str(), 0, 0);
        main1->m_custom_label25->TB_Func_13(Icon_Moc5.c_str(), 0, 0);
        main1->m_custom_label24->TB_Func_13(Icon_Moc7.c_str(), 0, 0);
        main1->m_custom_label23->TB_Func_13(Icon_Moc10.c_str(), 0, 0);
        main1->m_custom_label22->TB_Func_13(Icon_Moc13.c_str(), 0, 0);
        main1->m_custom_label21->TB_Func_13(Icon_Moc16.c_str(), 0, 0);
        main1->m_custom_label20->TB_Func_13(Icon_Moc19.c_str(), 0, 0);
        main1->m_custom_label19->TB_Func_13(Icon_Moc22.c_str(), 0, 0);
        main1->m_custom_label18->TB_Func_13(Icon_Moc25.c_str(), 0, 0);
        if(SoNgay ==1 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==2 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==3 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==4 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==5 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==6 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==7 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==8 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==9 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==10 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==11 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==12 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==13 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==14 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label39->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==15 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label39->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label38->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==16 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label39->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label38->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label37->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==17 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label39->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label38->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label37->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label36->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==18 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label39->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label38->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label37->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label36->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label35->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==19 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label39->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label38->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label37->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label36->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label35->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label34->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==20 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label39->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label38->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label37->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label36->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label35->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label34->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label33->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==21 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label39->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label38->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label37->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label36->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label35->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label34->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label33->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label32->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==22 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label39->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label38->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label37->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label36->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label35->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label34->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label33->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label32->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label31->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==23 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label39->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label38->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label37->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label36->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label35->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label34->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label33->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label32->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label31->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label30->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay ==24 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label39->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label38->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label37->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label36->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label35->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label34->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label33->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label32->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label31->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label30->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label29->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }
        if(SoNgay >=25 )
        {
            main1->m_custom_label52->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label51->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label50->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label49->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label48->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label47->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label46->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label45->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label44->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label43->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label42->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label41->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label40->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label39->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label38->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label37->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label36->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label35->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label34->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label33->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label32->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label31->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label30->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label29->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
            main1->m_custom_label28->TB_Func_13("interface\\ifcommon\\electus\\ok.ddj", 0, 0);
        }

        if(SoNgay>=1 && Nhan1Ngay == 0)
        {
            main1-> m_mybutton11->ShowGWnd(true);

        }
        else
        {
            main1-> m_mybutton11->ShowGWnd(false);
        }
        if(SoNgay>=3 && Nhan3Ngay == 0)
        {
            main1-> m_mybutton10->ShowGWnd(true);

        }
        else
        {
            main1-> m_mybutton10->ShowGWnd(false);
        }
        if(SoNgay>=5 && Nhan5Ngay == 0)
        {
            main1-> m_mybutton9->ShowGWnd(true);

        }
        else
        {
            main1-> m_mybutton9->ShowGWnd(false);
        }
        if(SoNgay>=7 && Nhan7Ngay == 0)
        {
            main1-> m_mybutton8->ShowGWnd(true);

        }
        else
        {
            main1-> m_mybutton8->ShowGWnd(false);
        }
        if(SoNgay>=10 && Nhan10Ngay == 0)
        {
            main1-> m_mybutton7->ShowGWnd(true);

        }
        else
        {
            main1-> m_mybutton7->ShowGWnd(false);
        }
        if(SoNgay>=13 && Nhan13Ngay == 0)
        {
            main1-> m_mybutton6->ShowGWnd(true);

        }
        else
        {
            main1-> m_mybutton6->ShowGWnd(false);
        }
        if(SoNgay>=16 && Nhan16Ngay == 0)
        {
            main1-> m_mybutton5->ShowGWnd(true);

        }
        else
        {
            main1-> m_mybutton5->ShowGWnd(false);
        }
        if(SoNgay>=19 && Nhan19Ngay == 0)
        {
            main1-> m_mybutton4->ShowGWnd(true);

        }
        else
        {
            main1-> m_mybutton4->ShowGWnd(false);
        }
        if(SoNgay>=22 && Nhan22Ngay == 0)
        {
            main1-> m_mybutton3->ShowGWnd(true);

        }
        else
        {
            main1-> m_mybutton3->ShowGWnd(false);
        }
        if(SoNgay>=25 && Nhan25Ngay == 0)
        {
            main1-> m_mybutton->ShowGWnd(true);

        }
        else
        {
            main1-> m_mybutton->ShowGWnd(false);
        }


        MsgBuffer->FlushRemaining();
    }
    /// total point info
    if (MsgBuffer->msgid() == 0x9942)// electus point
    {
        int FormID = 0;
        int HonorPoint = 0;
        int JobKill = 0;
        int UniqueKill = 0;
        int BattleArenaWin = 0;
        int CapFlagWin = 0;
        int FTWKill = 0;
        int JobbingPoint = 0;
        int Survivalwin = 0;
        int ItemPoints = 0;

        int SurvivalKills = 0;
        int TotalEarned = 0;
        int DailyJobPoints = 0;
        int ItemPointALL = 0;
        int Donate = 0;
        *MsgBuffer >> FormID >> HonorPoint>> JobKill>> UniqueKill>> BattleArenaWin>> CapFlagWin>> FTWKill>> JobbingPoint>> Survivalwin>> ItemPoints>>SurvivalKills>>TotalEarned>>DailyJobPoints>>ItemPointALL>>Donate;

        if (FormID == 5002) // electus point id
        {

            wchar_t buffer1[255];
            swprintf_s(buffer1, L"%d", ItemPointALL); //itempoint done
            g_pCGInterface->GetTotalPointsGUI()->m_custom_label6->SetText(buffer1);

            wchar_t buffer2[255];
            swprintf_s(buffer2, L"%d", UniqueKill); //done
            g_pCGInterface->GetTotalPointsGUI()->m_custom_label4->SetText(buffer2);

            wchar_t buffer3[255];
            swprintf_s(buffer3, L"%d", Survivalwin);
            g_pCGInterface->GetTotalPointsGUI()->m_custom_label5->SetText(buffer3);

            wchar_t buffer4[255];
            swprintf_s(buffer4, L"%d", SurvivalKills);
            g_pCGInterface->GetTotalPointsGUI()->m_custom_label2->SetText(buffer4);

            wchar_t buffer5[255];
            swprintf_s(buffer5, L"%d", FTWKill); //done
            g_pCGInterface->GetTotalPointsGUI()->m_custom_label3->SetText(buffer5);

            wchar_t buffer6[255];
            swprintf_s(buffer6, L"%d", JobKill); //done
            g_pCGInterface->GetTotalPointsGUI()->m_custom_label->SetText(buffer6);

            wchar_t buffer7[255];
            swprintf_s(buffer7, L"%d", ItemPoints); //alchemy done
            g_pCGInterface->GetTotalPointsGUI()->m_custom_label7->SetText(buffer7);


            wchar_t buffer9[255];
            swprintf_s(buffer9, L"%d", Donate); //donate done
            g_pCGInterface->GetTotalPointsGUI()->m_custom_label8->SetText(buffer9);

            wchar_t buffer10[255];
            swprintf_s(buffer10, L"%d", HonorPoint); //done
            g_pCGInterface->GetTotalPointsGUI()->m_custom_label9->SetText(buffer10);

        }

        MsgBuffer->FlushRemaining();
    }

    /// survival counter
    if (MsgBuffer->msgid() == 0x5123)
    {
        int sCount;
        std::n_string Player;
        std::n_string Kills;
        *MsgBuffer >> sCount>> Player >> Kills;;

       // g_pCGInterface->GetSurvivalKillGUI()->Clear();
        g_pCGInterface->GetSurvivalKillGUI()->WriteLine(sCount, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str());
        g_pCGInterface->GetSurvivalKillGUI()->ResetPosition();
        g_pCGInterface->GetSurvivalKillGUI()->ShowGWnd(true);

        MsgBuffer->FlushRemaining();
    }

    //// notice color
    if (MsgBuffer->msgid() == 0x9918)// electus point limit
    {

        std::n_string msg;
        *MsgBuffer >> msg ;

        wchar_t buffer[1000];
        swprintf_s(buffer, L"%S", msg.c_str());

        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 97, 204, 238);
        systemmessage->WriteMessage(0xFF, color, buffer, 0, 1);

        g_pCGInterface->ShowMessage_Orange(buffer);

        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x9919)// electus point limit
    {

        std::n_string msg;
        *MsgBuffer >> msg ;

        wchar_t buffer[1000];
        swprintf_s(buffer, L"%S", msg.c_str());

        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 97, 204, 238);
        systemmessage->WriteMessage(0xFF, color, buffer, 0, 1);
        g_pCGInterface->ShowMessage_Purble(buffer);

        MsgBuffer->FlushRemaining();
    }
    //// tai xiu
    if (MsgBuffer->msgid() == 0x9935)//Show Form
    {

        int FormID = 0;
        int KetQua;
        std::n_string SoGoldTai;
        std::n_string SoGoldXiu;

        *MsgBuffer >> FormID >> KetQua >> SoGoldTai>> SoGoldXiu;

        if (FormID == 5092) {

            CIFSTTaiXiu *main = g_pCGInterface->m_IRM.GetResObj<CIFSTTaiXiu>(5092, 1);


            wchar_t buffer2[255];
            wchar_t buffer3[255];
            wchar_t buffer4[255];
            swprintf_s(buffer2, L"%d", KetQua);
            swprintf_s(buffer3, L"%S", SoGoldTai.c_str());
            swprintf_s(buffer4, L"%S", SoGoldXiu.c_str());
            main->m_custom_label28->SetText(buffer2);
            main->m_custom_label12->SetText(buffer3);
            main->m_custom_label13->SetText(buffer4);
            switch (KetQua) {
                case 3: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\3.ddj", 0, 0);
                }
                    break;
                case 4: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\4.ddj", 0, 0);
                }
                    break;
                case 5: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\5.ddj", 0, 0);
                }
                    break;
                case 6: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\6.ddj", 0, 0);
                }
                    break;
                case 7: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\7.ddj", 0, 0);
                }
                    break;
                case 8: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\8.ddj", 0, 0);
                }
                    break;
                case 9: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\9.ddj", 0, 0);
                }
                    break;
                case 10: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\10.ddj", 0, 0);
                }
                    break;
                case 11: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\11.ddj", 0, 0);
                }
                    break;
                case 12: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\12.ddj", 0, 0);
                }
                    break;
                case 13: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\13.ddj", 0, 0);
                }
                    break;
                case 14: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\14.ddj", 0, 0);
                }
                    break;
                case 15: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\15.ddj", 0, 0);
                }
                    break;
                case 16: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\16.ddj", 0, 0);
                }
                    break;
                case 17: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\17.ddj", 0, 0);
                }
                    break;
                case 18: {
                    main->m_custom_label29->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\18.ddj", 0, 0);
                }
                    break;
            }

        }

        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x9934)//Show Form
    {

        int FormID = 0;
        int i;
        int TheLoai;


        *MsgBuffer >> FormID >> i >> TheLoai;

        if (FormID == 5092) {

            CIFSTTaiXiu *main = g_pCGInterface->m_IRM.GetResObj<CIFSTTaiXiu>(5092, 1);


            switch (i) {
                case 1: {
                    if (TheLoai==1)
                    {
                        main->m_custom_label26->SetText(L"Tai");
                    } else
                    {
                        main->m_custom_label26->SetText(L"Xiu");
                    }


                }
                    break;
                case 2: {
                    if (TheLoai==1)
                    {
                        main->m_custom_label25->SetText(L"Tai");
                    } else
                    {
                        main->m_custom_label25->SetText(L"Xiu");
                    }

                }
                    break;
                case 3: {
                    if (TheLoai==1)
                    {
                        main->m_custom_label24->SetText(L"Tai");
                    } else
                    {
                        main->m_custom_label24->SetText(L"Xiu");
                    }

                }
                    break;
                case 4: {
                    if (TheLoai==1)
                    {
                        main->m_custom_label23->SetText(L"Tai");
                    } else
                    {
                        main->m_custom_label23->SetText(L"Xiu");
                    }

                }
                    break;
                case 5: {
                    if (TheLoai==1)
                    {
                        main->m_custom_label22->SetText(L"Tai");
                    } else
                    {
                        main->m_custom_label22->SetText(L"Xiu");
                    }

                }
                    break;
                case 6: {
                    if (TheLoai==1)
                    {
                        main->m_custom_label21->SetText(L"Tai");
                    } else
                    {
                        main->m_custom_label21->SetText(L"Xiu");
                    }

                }
                    break;
                case 7: {
                    if (TheLoai==1)
                    {
                        main->m_custom_label20->SetText(L"Tai");
                    } else
                    {
                        main->m_custom_label20->SetText(L"Xiu");
                    }

                }
                    break;
                case 8: {
                    if (TheLoai==1)
                    {
                        main->m_custom_label19->SetText(L"Tai");
                    } else
                    {
                        main->m_custom_label19->SetText(L"Xiu");
                    }

                }
                    break;
                case 9: {
                    if (TheLoai==1)
                    {
                        main->m_custom_label18->SetText(L"Tai");
                    } else
                    {
                        main->m_custom_label18->SetText(L"Xiu");
                    }
                }
                    break;
                case 10: {
                    if (TheLoai==1)
                    {
                        main->m_custom_label17->SetText(L"Tai");
                    } else
                    {
                        main->m_custom_label17->SetText(L"Xiu");
                    }
                }
                    break;

            }

        }

        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x9925)// electus point limit
    {

        byte ID = 0;
        int timetoset = 0;
        int ketqua = 0;
        *MsgBuffer >> ID >> timetoset>>ketqua;
        CIFSTTaiXiu *main = g_pCGInterface->m_IRM.GetResObj<CIFSTTaiXiu>(5092, 1);

        switch (ID)
        {
            case 1:
            {
                main->show=1;
                main->SetChatBlocked(timetoset);

            }
                break;
            case 2:
            {
                main->show=2;
                main->SetChatBlocked1(timetoset);
            }
                break;
            case 3:
            {

                CMsgStreamBuffer buf(0x1323);
                buf << std::n_string("!TAIXIUUP");
                buf << std::n_string("!TAIXIUUP");
                SendMsg(buf);
            }
                break;
        }

        MsgBuffer->FlushRemaining();
    }
    ///XSMB
    if (MsgBuffer->msgid() == 0x5128)
    {

        BYTE sCount;
        BYTE RankType;
        std::n_string GiaiDB ;
        std::n_string GiaiNhat ;
        std::n_string GiaiNhi_1 ;
        std::n_string GiaiNhi_2 ;
        std::n_string GiaiBa_1 ;
        std::n_string GiaiBa_2 ;
        std::n_string GiaiBa_3 ;
        std::n_string GiaiBa_4 ;
        std::n_string GiaiBa_5 ;
        std::n_string GiaiBa_6 ;
        std::n_string GiaiBon_1;

        std::n_string GiaiBon_2 ;
        std::n_string GiaiBon_3 ;
        std::n_string GiaiBon_4 ;

        std::n_string GiaiNam_1 ;
        std::n_string GiaiNam_2 ;
        std::n_string GiaiNam_3 ;
        std::n_string GiaiNam_4 ;
        std::n_string GiaiNam_5 ;
        std::n_string GiaiNam_6 ;

        std::n_string GiaiSau_1 ;
        std::n_string GiaiSau_2 ;
        std::n_string GiaiSau_3 ;
        std::n_string GiaiBay_1 ;
        std::n_string GiaiBay_2 ;
        std::n_string GiaiBay_3 ;
        std::n_string GiaiBay_4 ;

        *MsgBuffer >>RankType >> sCount >> GiaiDB>> GiaiNhat>> GiaiNhi_1>> GiaiNhi_2>> GiaiBa_1>> GiaiBa_2>> GiaiBa_3>> GiaiBa_4>> GiaiBa_5>> GiaiBa_6>> GiaiBon_1>> GiaiBon_2>> GiaiBon_3>> GiaiBon_4>> GiaiNam_1>> GiaiNam_2>> GiaiNam_3>> GiaiNam_4>> GiaiNam_5>> GiaiNam_6>> GiaiSau_1>> GiaiSau_2>> GiaiSau_3>> GiaiBay_1>> GiaiBay_2>> GiaiBay_3>>GiaiBay_4;

        if (RankType == 1) // electus point id
        {

            wchar_t buffer[255];
            swprintf_s(buffer, L"%S", GiaiDB.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label22->SetText(buffer);
            wchar_t buffer1[255];
            swprintf_s(buffer1, L"%S", GiaiNhat.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label23->SetText(buffer1);
            wchar_t buffer2[255];
            swprintf_s(buffer2, L"%S", GiaiNhi_1.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label25->SetText(buffer2);
            wchar_t buffer3[255];
            swprintf_s(buffer3, L"%S", GiaiNhi_2.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label24->SetText(buffer3);

            wchar_t buffer4[255];
            swprintf_s(buffer4, L"%S", GiaiBa_1.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label26->SetText(buffer4);
            wchar_t buffer5[255];
            swprintf_s(buffer5, L"%S", GiaiBa_2.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label27->SetText(buffer5);
            wchar_t buffer6[255];
            swprintf_s(buffer6, L"%S", GiaiBa_3.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label28->SetText(buffer6);
            wchar_t buffer7[255];
            swprintf_s(buffer7, L"%S", GiaiBa_4.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label29->SetText(buffer7);
            wchar_t buffer8[255];
            swprintf_s(buffer8, L"%S", GiaiBa_5.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label30->SetText(buffer8);
            wchar_t buffer9[255];
            swprintf_s(buffer9, L"%S", GiaiBa_6.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label31->SetText(buffer9);

            wchar_t buffer10[255];
            swprintf_s(buffer10, L"%S", GiaiBon_1.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label32->SetText(buffer10);
            wchar_t buffer11[255];
            swprintf_s(buffer11, L"%S", GiaiBon_2.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label33->SetText(buffer11);
            wchar_t buffer12[255];
            swprintf_s(buffer12, L"%S", GiaiBon_3.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label34->SetText(buffer12);
            wchar_t buffer13[255];
            swprintf_s(buffer13, L"%S", GiaiBon_4.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label35->SetText(buffer13);

            wchar_t buffer14[255];
            swprintf_s(buffer14, L"%S", GiaiNam_1.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label36->SetText(buffer14);
            wchar_t buffer15[255];
            swprintf_s(buffer15, L"%S", GiaiNam_2.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label37->SetText(buffer15);
            wchar_t buffer16[255];
            swprintf_s(buffer16, L"%S", GiaiNam_3.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label38->SetText(buffer16);
            wchar_t buffer17[255];
            swprintf_s(buffer17, L"%S", GiaiNam_4.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label39->SetText(buffer17);
            wchar_t buffer18[255];
            swprintf_s(buffer18, L"%S", GiaiNam_5.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label40->SetText(buffer18);
            wchar_t buffer19[255];
            swprintf_s(buffer19, L"%S", GiaiNam_6.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label41->SetText(buffer19);

            wchar_t buffer20[255];
            swprintf_s(buffer20, L"%S", GiaiSau_1.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label42->SetText(buffer20);
            wchar_t buffer21[255];
            swprintf_s(buffer21, L"%S", GiaiSau_2.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label43->SetText(buffer21);
            wchar_t buffer22[255];
            swprintf_s(buffer22, L"%S", GiaiSau_3.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label44->SetText(buffer22);

            wchar_t buffer23[255];
            swprintf_s(buffer23, L"%S", GiaiBay_1.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label45->SetText(buffer23);
            wchar_t buffer24[255];
            swprintf_s(buffer24, L"%S", GiaiBay_2.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label46->SetText(buffer24);
            wchar_t buffer25[255];
            swprintf_s(buffer25, L"%S", GiaiBay_3.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label47->SetText(buffer25);
            wchar_t buffer26[255];
            swprintf_s(buffer26, L"%S", GiaiBay_4.c_str());
            g_pCGInterface->GetEventXoSoGUI()->m_custom_label48->SetText(buffer26);
        }



        MsgBuffer->FlushRemaining();
    }
    ////Town Region
    if (MsgBuffer->msgid() == 0x5331)
    {
        BYTE sCount;
        BYTE RankType;
        UINT16 Region;

        *MsgBuffer >> RankType >> sCount;

        BYTE i = 0;
        if (RankType == 1)
        {
            TownRegion.clear();
        }
        while (i < sCount && sCount > 0)
        {
            i++;

            *MsgBuffer >> Region;

            if (TownRegion.find(Region) == TownRegion.end())
            {
                TownRegion.insert(Region);
            }

        }

        MsgBuffer->FlushRemaining();
    }
    ////Rank info
    if (MsgBuffer->msgid() == 0x5129)
    {
        BYTE sCount;
        BYTE RankType;
        BYTE No;
        std::n_string So;
        std::n_string TienCuoc;
        std::n_string TrangThai;
        std::n_string TienTe;
        std::n_string TheLoai;
        std::n_string Ngay;
        *MsgBuffer >> RankType >> sCount;
        BYTE i = 0;

        if (RankType == 1)//uq rank
        {
            CIFSTEventXoSoMienBacLichSu::XSMBLichSuList.clear();
        }

        while (i < sCount && sCount > 0)
        {
            i++;

            *MsgBuffer >> No >> So >> TienCuoc >> TrangThai>>TienTe>>TheLoai>>Ngay;

            CIFSTEventXoSoMienBacLichSu::XSMBLichSu uqR = CIFSTEventXoSoMienBacLichSu::XSMBLichSu();

            uqR.LineNum = No;
            uqR.So = TO_WSTRING(So).c_str();
            uqR.TienCuoc = TO_WSTRING(TienCuoc).c_str();
            uqR.TrangThai = TO_WSTRING(TrangThai).c_str();
            uqR.TienTe = TO_WSTRING(TienTe).c_str();
            uqR.Loai = TO_WSTRING(TheLoai).c_str();
            uqR.Ngay = TO_WSTRING(Ngay).c_str();


            if (RankType == 1)//uq rank
            {
                CIFSTEventXoSoMienBacLichSu::XSMBLichSuList.push_back(uqR);
            }

        }

        g_pCGInterface->GetEventXoSoLichSuGUI()->UpdateXsmbLichSuList();
        MsgBuffer->FlushRemaining();
    }
    ////Event Time List
    ////Rank info
    if (MsgBuffer->msgid() == 0x5124)
    {
        BYTE sCount;
        BYTE RankType;
        BYTE No;
        std::n_string Name;
        std::n_string Guild;
        std::n_string Points;
        *MsgBuffer >> RankType >> sCount;
        BYTE i = 0;

        if (RankType == 1)//uq rank
        {
            CIFCustomRank::UniquesRankList.clear();
        }
        else if (RankType == 2)//honor rank
        {
            CIFCustomRank::GuildRankList.clear();
        }
        else if (RankType == 3)//pvp rank
        {
            CIFCustomRank::GoldRankList.clear();
        }
        else if (RankType == 4)//Trader rank
        {
            CIFCustomRank::JobTraderRank.clear();
        }
        else if (RankType == 5)//Hunter rank
        {
            CIFCustomRank::JobHunterRank.clear();
        }
        else if (RankType == 6)//Thief rank
        {
            CIFCustomRank::JobThiefRank.clear();
        }
        else if (RankType == 7)//item rank
        {
            CIFCustomRank::CharRankList.clear();
        }
        else if (RankType == 8)//job kills rank
        {
            CIFCustomRank::JobRankList.clear();
        }
        else if (RankType == 9)//char level rank
        {
            CIFCustomRank::CharLevelRankList.clear();
        }
        else if (RankType == 10)//char eu level rank
        {
            CIFCustomRank::CharLevelEuRankList.clear();
        }
        else if (RankType == 11)//char as level rank
        {
            CIFCustomRank::CharLevelAsianRankList.clear();
        }
        else if (RankType == 12)//TotalPointList rank
        {
            CIFSTTotalPoints::TotalPointList.clear();
        }
        while (i < sCount && sCount > 0)
        {
            i++;

            *MsgBuffer >> No >> Name >> Guild >> Points;

            CIFCustomRank::RankStruct uqR = CIFCustomRank::RankStruct();
            CIFSTTotalPoints::TotalPoint uqRR = CIFSTTotalPoints::TotalPoint();
            uqR.LineNum = No;
            uqR.Charname = TO_WSTRING(Name).c_str();
            uqR.Guild = TO_WSTRING(Guild).c_str();
            uqR.Points = TO_WSTRING(Points).c_str();

            uqRR.LineNum = No;
            uqRR.Charname = TO_WSTRING(Name).c_str();
            uqRR.Guild = TO_WSTRING(Points).c_str();


            if (RankType == 1)//uq rank
            {
                CIFCustomRank::UniquesRankList.push_back(uqR);
            }
            else if (RankType == 2)//honor rank
            {
                CIFCustomRank::GuildRankList.push_back(uqR);
            }
            else if (RankType == 3)//pvp rank
            {
                CIFCustomRank::GoldRankList.push_back(uqR);
            }
            else if (RankType == 4)//Trader rank
            {
                CIFCustomRank::JobTraderRank.push_back(uqR);
            }
            else if (RankType == 5)//Hunter rank
            {
                CIFCustomRank::JobHunterRank.push_back(uqR);
            }
            else if (RankType == 6)//Thief rank
            {
                CIFCustomRank::JobThiefRank.push_back(uqR);
            }
            else if (RankType == 7)//item rank
            {
                CIFCustomRank::CharRankList.push_back(uqR);
            }
            else if (RankType == 8)//job kills rank
            {
                CIFCustomRank::JobRankList.push_back(uqR);
            }
            else if (RankType == 9)//char rank
            {
                CIFCustomRank::CharLevelRankList.push_back(uqR);
            }
            else if (RankType == 10)//job kills rank
            {
                CIFCustomRank::CharLevelEuRankList.push_back(uqR);

            }
            else if (RankType == 11)//job kills rank
            {

                CIFCustomRank::CharLevelAsianRankList.push_back(uqR);
            }
            else if (RankType == 12)//job kills rank
            {

                CIFSTTotalPoints::TotalPointList.push_back(uqRR);
            }
        }

        g_pCGInterface->GetCustomRankGUI()->ActivateTabPage(0);
        g_pCGInterface->GetTotalPointsGUI()->UpdateTotalPointList();
        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x5133)
    {
        BYTE sCount;
        BYTE RankType;
        BYTE No;
        std::n_string Name;
        std::n_string Guild;
        std::n_string Points;
        *MsgBuffer >> RankType >> sCount;
        BYTE i = 0;


        if (RankType == 10)//char eu level rank
        {
            CIFCustomRank::CharLevelEuRankList.clear();
        }
        else if (RankType == 11)//char as level rank
        {
            CIFCustomRank::CharLevelAsianRankList.clear();
        }

        while (i < sCount && sCount > 0)
        {
            i++;

            *MsgBuffer >> No >> Name >> Guild >> Points;

            CIFCustomRank::RankStruct uqR = CIFCustomRank::RankStruct();
            CIFSTTotalPoints::TotalPoint uqRR = CIFSTTotalPoints::TotalPoint();
            uqR.LineNum = No;
            uqR.Charname = TO_WSTRING(Name).c_str();
            uqR.Guild = TO_WSTRING(Guild).c_str();
            uqR.Points = TO_WSTRING(Points).c_str();

            uqRR.LineNum = No;
            uqRR.Charname = TO_WSTRING(Name).c_str();
            uqRR.Guild = TO_WSTRING(Points).c_str();



            if (RankType == 10)//job kills rank
            {
                CIFCustomRank::CharLevelEuRankList.push_back(uqR);

            }
            else if (RankType == 11)//job kills rank
            {

                CIFCustomRank::CharLevelAsianRankList.push_back(uqR);
            }

        }

        MsgBuffer->FlushRemaining();
    }
    ///CharSkillInFo
    if (MsgBuffer->msgid() == 0x180E)
    {
        BYTE sCount;
        BYTE Type;
        int SkillID;
        std::n_string SkillName;
        BYTE TargetRequired;
        BYTE TargetEtc_SelectDeadBody;
        int Param1;
        int Param8;
        int Param4;
        int Param5;
        int Param3;
        int Param2;
        *MsgBuffer >> Type >> sCount;
        BYTE i = 0;

        if (Type == 1)//shop type
        {
            Rebot::HaveSkill.clear();
        }

        while (i < sCount && sCount > 0)
        {
            i++;

            *MsgBuffer >> SkillID >> SkillName >>TargetRequired>>TargetEtc_SelectDeadBody>> Param1 >> Param8 >> Param4 >> Param5 >> Param3 >> Param2;

            Rebot::HaveSkill[SkillID] = new Skill;
            Rebot::HaveSkill[SkillID]->SkillName = SkillName;
            Rebot::HaveSkill[SkillID]->TargetRequired = TargetRequired;
            Rebot::HaveSkill[SkillID]->TargetEtc_SelectDeadBody = TargetEtc_SelectDeadBody;
            Rebot::HaveSkill[SkillID]->Param1 = Param1;
            Rebot::HaveSkill[SkillID]->Param8 = Param8;
            Rebot::HaveSkill[SkillID]->Param4 = Param4;
            Rebot::HaveSkill[SkillID]->Param5 = Param5;
            Rebot::HaveSkill[SkillID]->Param3 = Param3;
            Rebot::HaveSkill[SkillID]->Param2 = Param2;

            Rebot::AllSkillOfChar[SkillID] = new Skill;
            Rebot::AllSkillOfChar[SkillID]->SkillName = SkillName;
            Rebot::AllSkillOfChar[SkillID]->TargetRequired = TargetRequired;
            Rebot::AllSkillOfChar[SkillID]->TargetEtc_SelectDeadBody = TargetEtc_SelectDeadBody;
            Rebot::AllSkillOfChar[SkillID]->Param1 = Param1;
            Rebot::AllSkillOfChar[SkillID]->Param8 = Param8;
            Rebot::AllSkillOfChar[SkillID]->Param4 = Param4;
            Rebot::AllSkillOfChar[SkillID]->Param5 = Param5;
            Rebot::AllSkillOfChar[SkillID]->Param3 = Param3;
            Rebot::AllSkillOfChar[SkillID]->Param2 = Param2;
        }

        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x182E)
    {
        BYTE sCount;
        BYTE Type;
        int ItemID;
        *MsgBuffer >> Type >> sCount;
        BYTE i = 0;
        if (Type == 2)//shop type
        {
            Rebot::Speed_Scroll_ItemID.clear();
        }
        while (i < sCount && sCount > 0)
        {
            i++;
            *MsgBuffer >> ItemID;
            Rebot::Speed_Scroll_ItemID.push_back(ItemID);
        }

        MsgBuffer->FlushRemaining();
    }
    ////Custom NPC
    if (MsgBuffer->msgid() == 0x5126)
    {
        BYTE sCount;
        BYTE ShopType;
        BYTE No;
        std::n_string ItemName;
        std::n_string Count;
        std::n_string Price;
        *MsgBuffer >> ShopType >> sCount;
        BYTE i = 0;

        if (ShopType == 1)//shop type
        {
            CIFSTCustomNPC::UniquesRankList.clear();
        }

        while (i < sCount && sCount > 0)
        {
            i++;

            *MsgBuffer >> No >> ItemName >> Count >> Price;

            CIFSTCustomNPC::RankStruct uqR = CIFSTCustomNPC::RankStruct();

            uqR.LineNum = No;
            uqR.ItemName = TO_WSTRING(ItemName).c_str();
            uqR.Count = TO_WSTRING(Count).c_str();
            uqR.Price = TO_WSTRING(Price).c_str();


            if (ShopType == 1)//uq rank
            {
               // g_CGlobalDataManager-> m_IconsData.insert(std::pair<int,void*>(No,Fun_CacheTexture_Create(ItemName.c_str())));
                m_IconsDataStore.insert(std::pair<int,const IDirect3DBaseTexture9*>(No,Fun_CacheTexture_Create_3D(ItemName.c_str())));
                CIFSTCustomNPC::UniquesRankList.push_back(uqR);
            }

        }

        g_pCGInterface->GetCustomNPCGUI()->ActivateTabPage(0);
        MsgBuffer->FlushRemaining();
    }
    ///Custom CharIcon
    if (MsgBuffer->msgid() == 0x5131)
    {
        BYTE sCount;
        BYTE Type;
        std::n_string CharName;
        int ID;
        *MsgBuffer >> Type >> sCount;
        BYTE i = 0;
        while (i < sCount && sCount > 0)
        {
            i++;

            *MsgBuffer >> CharName >> ID ;
            std::map<std::wstring, UINT32>::iterator foundedInfo = m_CharacterIcons.find(TO_WSTRING(CharName));
            if (foundedInfo != m_CharacterIcons.end())
                m_CharacterIcons[TO_WSTRING(CharName)]=ID;
            else
                m_CharacterIcons.insert(std::pair<std::wstring,UINT32>(TO_WSTRING(CharName),ID));


        }
        MsgBuffer->FlushRemaining();
    }
    ///Custom Char Vip Icon
    if (MsgBuffer->msgid() == 0x5134)
    {
        BYTE sCount;
        BYTE Type;
        std::n_string CharName;
        int VipLevel;
        *MsgBuffer >> Type >> sCount;
        BYTE i = 0;
        while (i < sCount && sCount > 0)
        {
            i++;
            *MsgBuffer >> CharName >> VipLevel ;
            std::map<std::wstring, UINT32>::iterator foundedInfo = m_CharacterVipIcons.find(TO_WSTRING(CharName));
            if (foundedInfo != m_CharacterVipIcons.end())
                m_CharacterVipIcons[TO_WSTRING(CharName)]=VipLevel;
            else
                m_CharacterVipIcons.insert(std::pair<std::wstring,UINT32>(TO_WSTRING(CharName),VipLevel));

        }
        MsgBuffer->FlushRemaining();
    }
    ///GetCharName Selected
/*    if (MsgBuffer->msgid() == 0x5155)
    {

        std::n_string CharName;
        *MsgBuffer >> CharName;

        //CharNameSelected = TO_WSTRING(CharName).c_str();
        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0xB045)
    {
        BYTE status;
        int UniqueID;
        *MsgBuffer >>status >>UniqueID;

        CICharactor* Char = 0;
        Char = GetCharacterObjectByID_MAYBE(UniqueID);
        if (Char != 0)
        {
            CharNameSelected= Char->GetName();
        }

        MsgBuffer->m_currentReadBytes = 0;
    }*/
/*    if (MsgBuffer->msgid() == 0x30BF)
    {

        int UniqueID;
        BYTE updateType;
        BYTE updateState;
        *MsgBuffer >>UniqueID >>updateType>>updateState;

        if (updateType==0 && updateState==2)
        {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!PLAYERDEADSTATUS");
            buf << std::n_string("!PLAYERDEADSTATUS");
            //buf << g_pCICPlayer->GetRegion().r;
            SendMsg(buf);
        }

        MsgBuffer->m_currentReadBytes = 0;
    }*/

    ///party disbale region
    if (MsgBuffer->msgid() == 0x5132)
    {
        int Action;
        int sCount;
        int RegionID;
        std::n_string CharName;
        *MsgBuffer >>Action>> sCount ;
        if(Action==1)
        {
            BYTE i = 0;
            m_PartyDisabledRegions.clear();
            while (i < sCount && sCount > 0)
            {
                i++;
                *MsgBuffer >> RegionID;
                if (m_PartyDisabledRegions.find(RegionID) == m_PartyDisabledRegions.end())
                {
                    m_PartyDisabledRegions.insert(RegionID);
                }
            }
        }
        else if(Action==2)
        {
            BYTE i = 0;

            OptimizeCloth::ClearHideClothesRegions();
            while (i < sCount && sCount > 0)
            {
                i++;
                *MsgBuffer >> RegionID;
                if (!OptimizeCloth::IsHideClothesRegion(RegionID))
                {
                    OptimizeCloth::AddHideClothesRegion(RegionID);
                }
            }
        }
        else if(Action==3)
        {
            *MsgBuffer >> RegionID >> CharName;
            std::wstringstream Reg;
            Reg <<RegionID;
            std::wstring Location =  g_CTextStringManager->GetString(Reg.str().c_str())->c_str();
            wchar_t* NewMsg = new wchar_t[1024];
            wsprintfW(NewMsg,TSM_GETTEXTPTR("UIIT_STT_WELCOME_MSG_CUSTOM"), CharName.c_str(), Location.c_str());
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            g_pCGInterface->ShowMessage_Warning(NewMsg);
            int color = D3DCOLOR_ARGB(255, 213, 197, 136);
            systemmessage->WriteMessage(0xFF, color, NewMsg, 0, 1);
        }
        MsgBuffer->FlushRemaining();
    }
    ////Event Time List
    if (MsgBuffer->msgid() == 0x9477)// unique status
    {


        int Estatus = 0;
        int Time=0;
        int EventID=0;
        std::n_string CheckTime;
        int hour = 0;

        *MsgBuffer >> Estatus>>EventID>>CheckTime;

        switch (EventID) {
            case 1001: {

                if (Estatus == 1) // unique live = 2
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line1->WriteLineEventTime(TSM_GETTEXTPTR("UIIT_STT_EVENTTIMER_REG"));
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line1->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_alive.ddj", 0,0);
                }
                else if (Estatus != 1) // unique dead = 1
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line1->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_dead.ddj", 0,0);
                    wchar_t buffer[255];
                    swprintf_s(buffer, L"%S",CheckTime.c_str());
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line1->WriteLineEventTime(buffer);
                }
            }
                break;
            case 1002: {
                if (Estatus == 1) // unique live = 2
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line2->WriteLineEventTime(TSM_GETTEXTPTR("UIIT_STT_EVENTTIMER_REG"));
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line2->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_alive.ddj", 0,0);
                }
                else if (Estatus != 1) // unique dead = 1
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line2->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_dead.ddj", 0,0);
                    wchar_t buffer[255];
                    swprintf_s(buffer, L"%S",CheckTime.c_str());

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line2->WriteLineEventTime(buffer);
                }


            } break;
            case 1003: {
                if (Estatus == 1) // unique live = 2
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line3->WriteLineEventTime(TSM_GETTEXTPTR("UIIT_STT_EVENTTIMER_REG"));
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line3->m_custom_label2->TB_Func_13("interface\\ifcommon\\electus\\electuseventtimers_alive.ddj", 0,0);
                }
                else if (Estatus != 1) // unique dead = 1
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line3->m_custom_label2->TB_Func_13("interface\\ifcommon\\electus\\electuseventtimers_dead.ddj", 0,0);
                    wchar_t buffer[255];
                    swprintf_s(buffer, L"%S",CheckTime.c_str());
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line3->WriteLineEventTime(buffer);
                }


            } break;
            case 1004: {
                if (Estatus == 1) // unique live = 2
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line4->WriteLineEventTime(TSM_GETTEXTPTR("UIIT_STT_EVENTTIMER_REG"));
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line4->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_alive.ddj", 0,0);
                }
                else if (Estatus != 1) // unique dead = 1
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line4->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_dead.ddj", 0,0);
                    wchar_t buffer[255];
                    swprintf_s(buffer, L"%S",CheckTime.c_str());
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line4->WriteLineEventTime(buffer);
                }


            } break;
            case 1005: {
                if (Estatus == 1) // unique live = 2
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line5->WriteLineEventTime(TSM_GETTEXTPTR("UIIT_STT_EVENTTIMER_REG"));
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line5->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_alive.ddj", 0,0);
                }
                else if (Estatus != 1) // unique dead = 1
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line5->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_dead.ddj", 0,0);
                    wchar_t buffer[255];
                    swprintf_s(buffer, L"%S",CheckTime.c_str());
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line5->WriteLineEventTime(buffer);
                }


            } break;
            case 1006: {
                if (Estatus == 1) // unique live = 2
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line6->WriteLineEventTime(TSM_GETTEXTPTR("UIIT_STT_EVENTTIMER_REG"));
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line6->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_alive.ddj", 0,0);
                }
                else if (Estatus != 1) // unique dead = 1
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line6->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_dead.ddj", 0,0);
                    wchar_t buffer[255];
                    swprintf_s(buffer, L"%S",CheckTime.c_str());
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line6->WriteLineEventTime(buffer);
                }


            } break;
            case 1007: {
                if (Estatus == 1) // unique live = 2
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line7->WriteLineEventTime(TSM_GETTEXTPTR("UIIT_STT_EVENTTIMER_REG"));
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line7->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_alive.ddj", 0,0);
                }
                else if (Estatus != 1) // unique dead = 1
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line7->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_dead.ddj", 0,0);
                    wchar_t buffer[255];
                    swprintf_s(buffer, L"%S",CheckTime.c_str());
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line7->WriteLineEventTime(buffer);
                }


            } break;
            case 1008: {
                if (Estatus == 1) // unique live = 2
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line8->WriteLineEventTime(TSM_GETTEXTPTR("UIIT_STT_EVENTTIMER_REG"));
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line8->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_alive.ddj", 0,0);
                }
                else if (Estatus != 1) // unique dead = 1
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line8->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_dead.ddj", 0,0);
                    wchar_t buffer[255];
                    swprintf_s(buffer, L"%S",CheckTime.c_str());
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line8->WriteLineEventTime(buffer);
                }

            } break;
            case 1009: {
                if (Estatus == 1) // unique live = 2
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line9->WriteLineEventTime(TSM_GETTEXTPTR("UIIT_STT_EVENTTIMER_REG"));
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line9->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_alive.ddj", 0,0);
                }
                else if (Estatus != 1) // unique dead = 1
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line9->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_dead.ddj", 0,0);
                    wchar_t buffer[255];
                    swprintf_s(buffer, L"%S",CheckTime.c_str());
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line9->WriteLineEventTime(buffer);
                }

            } break;
            case 1010: {
                if (Estatus == 1) // unique live = 2
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line10->WriteLineEventTime(TSM_GETTEXTPTR("UIIT_STT_EVENTTIMER_REG"));
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line10->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_alive.ddj", 0,0);
                }
                else if (Estatus != 1) // unique dead = 1
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line10->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_dead.ddj", 0,0);
                    wchar_t buffer[255];
                    swprintf_s(buffer, L"%S",CheckTime.c_str());
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line10->WriteLineEventTime(buffer);
                }

            } break;
            case 1011: {
                if (Estatus == 1) // unique live = 2
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line11->WriteLineEventTime(TSM_GETTEXTPTR("UIIT_STT_EVENTTIMER_REG"));
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_alive.ddj", 0,0);
                }
                else if (Estatus != 1) // unique dead = 1
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_dead.ddj", 0,0);
                    wchar_t buffer[255];
                    swprintf_s(buffer, L"%S",CheckTime.c_str());
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line11->WriteLineEventTime(buffer);
                }


            } break;
            case 1012: {
                if (Estatus == 1) // unique live = 2
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line12->WriteLineEventTime(TSM_GETTEXTPTR("UIIT_STT_EVENTTIMER_REG"));
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line12->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_alive.ddj", 0,0);
                }
                else if (Estatus != 1) // unique dead = 1
                {

                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line12->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electuseventtimers_dead.ddj", 0,0);
                    wchar_t buffer[255];
                    swprintf_s(buffer, L"%S",CheckTime.c_str());
                    g_pCGInterface->GetEventTimeGUI()-> Slot1->Line12->WriteLineEventTime(buffer);
                }


            } break;


        }
        MsgBuffer->FlushRemaining();

    }
    ////// title system
    if (MsgBuffer->msgid() == 0x9921)// title color
    {
        int Titlecolor = 0;
        int Namecolor = 0;
        int ListCount;
        std::n_string CharName;
        std::n_string TitleName;
        std::n_string CustomName;

        //CIFflorian0Guide::TitleDataList.clear();
        *MsgBuffer >> ListCount;
        int i = 0;
        while (i < ListCount && ListCount > 0)
        {
            i++;
            *MsgBuffer >>CharName >>Titlecolor>>Namecolor>>CustomName>>TitleName ;
            TitleData* newchar = new TitleData();
            newchar->titlecolor = Titlecolor;
            newchar->namecolor = Namecolor;
            newchar->charname = (TO_NWSTRING(CharName));
            newchar->Title = (TO_NWSTRING(TitleName));
            newchar->NameTitle = (TO_NWSTRING(CustomName));

            std::map<std::n_wstring,TitleData*>::iterator foundedInfo = CIFflorian0Guide::TitleDataList.find(TO_NWSTRING(CharName));
            if (foundedInfo != CIFflorian0Guide::TitleDataList.end())
                CIFflorian0Guide::TitleDataList[TO_NWSTRING(CharName)]=(newchar);
            else
                CIFflorian0Guide::TitleDataList.insert(std::pair<std::n_wstring,TitleData*>(TO_NWSTRING(CharName),newchar));

        }

    }
    if (MsgBuffer->msgid() == 0x9939)//title
    {
        int ID = 0;
        std::n_string TitleName;
        int TitleColor = 0;
        *MsgBuffer >> ID >> TitleName>>TitleColor;
        if (ID==5010)
        {
            wchar_t buffer[255];
            swprintf_s(buffer,L"%S", TitleName.c_str());
            std::n_wstring strmsg(buffer);
            g_pCGInterface->GetSwitchTitleGUI()->m_textbox->sub_64F8A0(strmsg, 0, TitleColor, TitleColor, -1, 0, 0);
        }

        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0xB666)//title
    {

        int UserJID = 0;
        std::n_string szToken;
        *MsgBuffer >> UserJID >> szToken;
        m_UserJID = UserJID;
        m_szToken = szToken.c_str();
        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x9922)// player count
    {

        int ID = 0;
        int playercount = 0;
        *MsgBuffer >>ID>>playercount ;

        if(ID==5098)
        {
            wchar_t buffer[255];
            swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_MUA_LUOT_XACNHAN"), playercount);
            g_pCGInterface->GetConfirmGUI()-> m_custom_label_tooltip->SetText(buffer);
        }
        if(ID==5097)
        {
            wchar_t buffer3[80];
            swprintf_s(buffer3, TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TOOLTIP5"),playercount);
            g_pCGInterface->GetCustomTitleGUI()->m_custom_label4->SetText(buffer3);
        }
        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x9933)// player count
    {

        int ID = 0;
        *MsgBuffer >>ID ;

/*        if(ID==5000)
        {
            CICharactor *entity = 0;
            BYTE a = 1;
            CLASSLINK_LOOP_BEGIN(CICharactor)
                if (obj->GetName() == g_pCICPlayer->GetName()) {
                    entity = obj;
                    if (entity)
                        entity->FUN_009dae90(a);
                }
            CLASSLINK_LOOP_END(CICharactor)
        }*/

        MsgBuffer->FlushRemaining();
    }
    //// Auto Use Item
    /*if(MsgBuffer->msgid()==0x190A)
    {
     int Action;
        *MsgBuffer >>Action ;

        CIFSlotWithHelp* pSlot;
        CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();

        if(Action==1 && g_pCGInterface->GetExtraFeatureGUI()->SetAutoABS)
        {

            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot->ItemInfo != 0)
                {
                    if ( pSlot->ItemInfo->GetObjectData()->ObjID == 3768)
                    {
                        if(pSlot->ItemInfo->m_quantity == 1)
                        {
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot1->FUN_006871d0(0);
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot1->TB_Func_13("", 1, 1);
                            g_pCGInterface->GetExtraFeatureGUI()->SetAutoABS = false;
                            g_pCGInterface->GetExtraFeatureGUI()->m_btn1->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                        }
                        else
                        {
                            g_pCGInterface->GetExtraFeatureGUI()-> m_dame_abs_slot = pSlot->UniqueID()- 100 + 0xD;
                            CMsgStreamBuffer buf(0x704C);
                            buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_dame_abs_slot;
                            buf << (UINT16)0x0EED ;
                            SendMsg(buf);
                            break;
                        }

                    }
                }

            }
*//*            if((g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_abs_slot)->m_quantity==1) &&
                    (g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_abs_slot)-> GetObjectData()->ObjID != 3768))
            {
                g_pCGInterface->GetExtraFeatureGUI()->m_slot1->FUN_006871d0(0);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot1->TB_Func_13("", 1, 1);
                g_pCGInterface->GetExtraFeatureGUI()->SetAutoABS = false;
                g_pCGInterface->GetExtraFeatureGUI()->m_btn1->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
            }
            else
            {
                BYTE Slot = g_pCGInterface->GetExtraFeatureGUI()->m_dame_abs_slot+0xD;
                CMsgStreamBuffer buf(0x704C);
                buf << (byte)Slot;
                buf << (UINT16)0x0EED ;
                SendMsg(buf);
            }*//*
        }
        else if(Action==2 && g_pCGInterface->GetExtraFeatureGUI()->SetAutoINC)
        {
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot->ItemInfo != 0)
                {
                    if ( pSlot->ItemInfo->GetObjectData()->ObjID == 3767)
                    {
                        if(pSlot->ItemInfo->m_quantity == 1)
                        {
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot2->FUN_006871d0(0);
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot2->TB_Func_13("", 1, 1);
                            g_pCGInterface->GetExtraFeatureGUI()->SetAutoINC = false;
                            g_pCGInterface->GetExtraFeatureGUI()->m_btn2->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                        }
                        else
                        {
                            g_pCGInterface->GetExtraFeatureGUI()-> m_dame_inc_slot = pSlot->UniqueID()- 100 + 0xD;
                            CMsgStreamBuffer buf(0x704C);
                            buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_dame_inc_slot;
                            buf << (UINT16)0x0EED ;
                            SendMsg(buf);
                            break;
                        }
                    }
                }

            }
*//*            if((g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_inc_slot)->m_quantity==1) &&
               (g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_inc_slot)-> GetObjectData()->ObjID != 3767))
            {
                g_pCGInterface->GetExtraFeatureGUI()->m_slot2->FUN_006871d0(0);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot2->TB_Func_13("", 1, 1);
                g_pCGInterface->GetExtraFeatureGUI()->SetAutoINC = false;
                g_pCGInterface->GetExtraFeatureGUI()->m_btn2->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
            }
            else
            {
                BYTE Slot = g_pCGInterface->GetExtraFeatureGUI()->m_dame_inc_slot+0xD;
                CMsgStreamBuffer buf(0x704C);
                buf << (byte)Slot;
                buf << (UINT16)0x0EED ;
                SendMsg(buf);
            }*//*

        }
        else if(Action==3 && g_pCGInterface->GetExtraFeatureGUI()->SetAutoABSbubble)
        {
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot->ItemInfo != 0 )
                {
                    if ( (pSlot->ItemInfo->GetObjectData()->ObjID == 24394 ||
                         pSlot->ItemInfo->GetObjectData()->ObjID == 24390||
                         pSlot->ItemInfo->GetObjectData()->ObjID == 24386||
                         pSlot->ItemInfo->GetObjectData()->ObjID == 24402))
                    {
                        if(pSlot->ItemInfo->m_quantity == 1)
                        {
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot3->FUN_006871d0(0);
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot3->TB_Func_13("", 1, 1);
                            g_pCGInterface->GetExtraFeatureGUI()->SetAutoABSbubble = false;
                            g_pCGInterface->GetExtraFeatureGUI()->m_btn3->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                        }
                        else
                        {
                            g_pCGInterface->GetExtraFeatureGUI()-> m_dame_absorbbubble_slot = pSlot->UniqueID()- 100 + 0xD;
                            CMsgStreamBuffer buf(0x704C);
                            buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_dame_absorbbubble_slot;
                            buf << (UINT16)0x0EED ;
                            SendMsg(buf);
                            break;
                        }

                    }
                }

            }
*//*            if((g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_absorbbubble_slot)->m_quantity==1) &&
               ((g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_absorbbubble_slot)-> GetObjectData()->ObjID != 24394)
                || (g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_absorbbubble_slot)-> GetObjectData()->ObjID != 24390)
                || (g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_absorbbubble_slot)-> GetObjectData()->ObjID != 24386)
                || (g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_absorbbubble_slot)-> GetObjectData()->ObjID != 24402)))
            {
                g_pCGInterface->GetExtraFeatureGUI()->m_slot3->FUN_006871d0(0);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot3->TB_Func_13("", 1, 1);
                g_pCGInterface->GetExtraFeatureGUI()->SetAutoABSbubble = false;
                g_pCGInterface->GetExtraFeatureGUI()->m_btn3->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
            }
            else
            {
                BYTE Slot = g_pCGInterface->GetExtraFeatureGUI()->m_dame_absorbbubble_slot+0xD;
                CMsgStreamBuffer buf(0x704C);
                buf << (byte)Slot;
                buf << (UINT16)0x0EED ;
                SendMsg(buf);
            }*//*

        }
        else if(Action==4 && g_pCGInterface->GetExtraFeatureGUI()->SetAutoINCbubble)
        {
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot->ItemInfo != 0)
                {
                    if ( (pSlot->ItemInfo->GetObjectData()->ObjID == 24393 ||
                         pSlot->ItemInfo->GetObjectData()->ObjID == 24389||
                         pSlot->ItemInfo->GetObjectData()->ObjID == 24385||
                         pSlot->ItemInfo->GetObjectData()->ObjID == 24401) )
                    {
                        if(pSlot->ItemInfo->m_quantity == 1)
                        {
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot4->FUN_006871d0(0);
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot4->TB_Func_13("", 1, 1);
                            g_pCGInterface->GetExtraFeatureGUI()->SetAutoINCbubble = false;
                            g_pCGInterface->GetExtraFeatureGUI()->m_btn4->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                        }
                        else
                        {
                            g_pCGInterface->GetExtraFeatureGUI()-> m_dame_Increasebubble_slot = pSlot->UniqueID()- 100 + 0xD;
                            CMsgStreamBuffer buf(0x704C);
                            buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_dame_Increasebubble_slot;
                            buf << (UINT16)0x0EED ;
                            SendMsg(buf);
                            break;
                        }

                    }
                }

            }
*//*            if((g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_Increasebubble_slot)->m_quantity==1) &&
                    ((g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_Increasebubble_slot)-> GetObjectData()->ObjID != 24393)
                    || (g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_Increasebubble_slot)-> GetObjectData()->ObjID != 24389)
                       || (g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_Increasebubble_slot)-> GetObjectData()->ObjID != 24385)
                          || (g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot( g_pCGInterface->GetExtraFeatureGUI()->m_dame_Increasebubble_slot)-> GetObjectData()->ObjID != 24401)))
            {
                g_pCGInterface->GetExtraFeatureGUI()->m_slot4->FUN_006871d0(0);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot4->TB_Func_13("", 1, 1);
                g_pCGInterface->GetExtraFeatureGUI()->SetAutoINCbubble = false;
                g_pCGInterface->GetExtraFeatureGUI()->m_btn4->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
            }
            else
            {
                BYTE Slot = g_pCGInterface->GetExtraFeatureGUI()->m_dame_Increasebubble_slot+0xD;
                CMsgStreamBuffer buf(0x704C);
                buf << (byte)Slot;
                buf << (UINT16)0x0EED ;
                SendMsg(buf);
            }*//*
        }
        MsgBuffer->FlushRemaining();
    }*/
    //// item link
    if(MsgBuffer->msgid()==0x180F)
    {

        byte SlotID;
        *MsgBuffer >> SlotID;
        CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
        RECT r1;
        GetWindowRect(theApp.GetHWnd(), &r1);
        POINT mMouse;
        GetCursorPos(&mMouse);


        for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
        {
            CIFSlotWithHelp* pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
            if (pSlot->UniqueID()- 100 + 0xD == SlotID)
            {
                CIFChatViewer* chatView = (CIFChatViewer*)g_pCGInterface->m_IRM.GetResObj(1, 1);

                if(chatView->Slot)
                {
                    chatView->Slot->MoveGWnd(9999, 0);
                    if(chatView->Slot->ItemInfo)
                    {
                        chatView->Slot->ShowGWnd(false);

                    }
                }
                chatView->Slot->ItemInfo=pSlot->ItemInfo;
                if (chatView->Slot->ItemInfo) {
                    POINT m_show_point;
                    m_show_point.x = mMouse.x - (r1.left + 165);
                    m_show_point.y = mMouse.y - r1.top;
                    g_pCGInterface->m_helperWindow->ShowGWnd(true);
                    (*(void(__thiscall**)(CIFTextBox*, int, int))(*(DWORD32*)(g_pCGInterface->m_helperWindow->m_textBox) + 0x54))(g_pCGInterface->m_helperWindow->m_textBox,0xC8,1);

                    g_pCGInterface->m_helperWindow->m_ownerWindow = chatView->Slot;
                    g_pCGInterface->m_helperWindow->Reset();
                    g_pCGInterface->N00002717->Reset();
                    chatView->Slot->HelperBubbleInventoryAndEquipment(g_pCGInterface->m_helperWindow);

                    g_pCGInterface->m_helperWindow->sub_777020();
                    g_pCGInterface->m_helperWindow->MoveGWnd(m_show_point.x, m_show_point.y);
                    g_pCGInterface->m_helperWindow->sub_776C00(&g_pCGInterface->m_helperWindow->GetBounds(), g_pCGInterface->m_helperWindow->N00000618);
                    g_pCGInterface->m_helperWindow->BringToFront();

                    g_pCGInterface->N00002717->sub_777020();
                    g_pCGInterface->N00002717->MoveGWnd(m_show_point.x, m_show_point.y);
                    g_pCGInterface->N00002717->sub_776C00(&g_pCGInterface->N00002717->GetBounds(), g_pCGInterface->N00002717->N00000618);
                    g_pCGInterface->N00002717->BringToFront();
                }
                break;
            }
        }
        g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C1F0), 2);
        *(BYTE*)(0x0087C1F0) = 0x72;
        *(BYTE*)(0x0087C1F0 + 1) = 0x05;
        g_MemoryHelper->ReProtect();
        g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C15B), 1);
        *(BYTE*)(0x0087C15B) = 0x74;
        g_MemoryHelper->ReProtect();

        CMsgStreamBuffer buf(0x180F);
        buf << byte(0x02) << SlotID;
        SendMsg(buf);
        MsgBuffer->FlushRemaining();
    }
    if(MsgBuffer->msgid()==0x180C)
     {
         UINT16 strLen;
         MsgBuffer->Read(&strLen, 2);
         char* charName = new char[strLen];
         MsgBuffer->Read(charName, strLen);
         CSOItem gold;
         MsgBuffer->Read(&gold, 0x1D0);
         CIFChatViewer *main12 = g_pCGInterface->m_IRM.GetResObj<CIFChatViewer>(1, 1);
         ChatItemLink Link;
         Link.ItemInfo = gold;
         Link.LineIndex = main12->m_CurrentActiveChatlist ->GetNumberOfItems();
         ChatItemInfoList[charName] = Link;
     }
    if(MsgBuffer->msgid()==0x170C)
    {
        UINT16 strLen;
        MsgBuffer->Read(&strLen, 2);
        char* charName = new char[strLen];
        MsgBuffer->Read(charName, strLen);
        size_t length = strlen(charName);
        ItemLinking Link;
        CMsgStreamBuffer * temporaryPacket = new CMsgStreamBuffer(0xB034);
        CIFChatViewer *main12 = g_pCGInterface->m_IRM.GetResObj<CIFChatViewer>(1, 1);
        for (size_t i = 0; i < ((MsgBuffer->m_availableBytesForReading)-(length+3)); i++)
        {
            UINT8 strLens ;
            MsgBuffer->Read(&strLens, 1);
            temporaryPacket->Write(&strLens, 1);
        }
        Link.buffer=temporaryPacket;
        Link.LineIndex = main12->m_CurrentActiveChatlist->GetNumberOfItems();
        ItemLinkInfoList[charName] = Link;
        MsgBuffer->FlushRemaining();
    }
    //// Char info

    if(MsgBuffer->msgid()==0x170E)
    {
        UINT16 strLen;
        UINT32 ItemID;
        byte Slot ;
        MsgBuffer->Read(&strLen, 2);
        char* charName = new char[strLen];
        MsgBuffer->Read(charName, strLen);
        size_t length = strlen(charName);
        MsgBuffer->Read(&ItemID, 0x4);
        MsgBuffer->Read(&Slot, 0x1);
        ItemLinking Link;
        CMsgStreamBuffer * temporaryPacket = new CMsgStreamBuffer(0xB034);
        for (size_t i = 0; i < ((MsgBuffer->m_availableBytesForReading)-(length+3+5)); i++)
        {
            UINT8 strLens ;
            MsgBuffer->Read(&strLens, 1);
            temporaryPacket->Write(&strLens, 1);
        }
        Link.buffer=temporaryPacket;
        SCharItemInfoList[charName] = Link;
        static const CItemData *data = NULL;
        data = g_CGlobalDataManager->GetItemData(ItemID);
        if( data && data != NULL)
        {
            switch (Slot) {
                case 0: {
                    g_pCGInterface->GetCharInfoGUI()->m_slot3->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                }
                    break;
                case 1: {
                    g_pCGInterface->GetCharInfoGUI()->m_slot5->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                }
                    break;
                case 2: {
                    g_pCGInterface->GetCharInfoGUI()->m_slot4->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                }
                    break;
                case 3: {
                    g_pCGInterface->GetCharInfoGUI()->m_slot6->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                }
                    break;
                case 4: {
                    g_pCGInterface->GetCharInfoGUI()->m_slot7->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                }
                    break;
                case 5: {
                    g_pCGInterface->GetCharInfoGUI()->m_slot8->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                }
                    break;
                case 6: {
                    g_pCGInterface->GetCharInfoGUI()->m_slot1->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                }
                    break;
                case 7: {
                    g_pCGInterface->GetCharInfoGUI()->m_slot2->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                }
                    break;
                case 9: {
                    g_pCGInterface->GetCharInfoGUI()->m_slot9->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                }
                    break;
                case 10: {
                    g_pCGInterface->GetCharInfoGUI()->m_slot10->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                }
                    break;
                case 11: {
                    g_pCGInterface->GetCharInfoGUI()->m_slot11->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                }
                    break;
                case 12: {
                    g_pCGInterface->GetCharInfoGUI()->m_slot12->TB_Func_13(data->m_assocFileIcon128.c_str(), 0, 0);
                }
                    break;
            }

        }
        MsgBuffer->FlushRemaining();
    }
    if(MsgBuffer->msgid()==0x190B)
    {

        std::n_string charName;
        *MsgBuffer >>charName ;
        CSOItem gold;
        MsgBuffer->Read(&gold, 0x1D0);
        Rebot::CharInfoList1[charName] = gold;
           g_pCGInterface->GetCharInfoGUI()->m_slot->ItemInfo = &Rebot::CharInfoList1[charName];
           g_pCGInterface->GetCharInfoGUI()->m_slot->TB_Func_13(g_pCGInterface->GetCharInfoGUI()->m_slot->ItemInfo->GetObjectData()->AssocFileIcon.c_str(), 0, 0);

    }
    if(MsgBuffer->msgid()==0x190C)
    {
        BYTE Slot = 0;
        std::n_string CharNameSendCommand;
        *MsgBuffer >>Slot>>CharNameSendCommand ;
        switch (Slot) {
            case 6: {
                CSOItem *this_01 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(6);

                NEWMSG(0x190C)
                    pReq << CharNameSendCommand;
                    pReq << *this_01;
                SENDMSG()
            }
                break;
            case 7: {
                CSOItem *this_01 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(7);

                NEWMSG(0x190C)
                    pReq << CharNameSendCommand;
                    pReq << *this_01;
                SENDMSG()
            }
                break;
            case 0: {
                CSOItem *this_01 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(0);

                NEWMSG(0x190C)
                    pReq << CharNameSendCommand;
                    pReq << *this_01;
                SENDMSG()
            }
                break;
            case 2: {
                CSOItem *this_01 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(2);

                NEWMSG(0x190C)
                    pReq << CharNameSendCommand;
                    pReq << *this_01;
                SENDMSG()
            }
                break;
            case 1: {
                CSOItem *this_01 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(1);

                NEWMSG(0x190C)
                    pReq << CharNameSendCommand;
                    pReq << *this_01;
                SENDMSG()
            }
                break;
            case 3: {
                CSOItem *this_01 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(3);

                NEWMSG(0x190C)
                    pReq << CharNameSendCommand;
                    pReq << *this_01;
                SENDMSG()
            }
                break;
            case 4: {
                CSOItem *this_01 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(4);

                NEWMSG(0x190C)
                    pReq << CharNameSendCommand;
                    pReq << *this_01;
                SENDMSG()
            }
                break;
            case 5: {
                CSOItem *this_01 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(5);

                NEWMSG(0x190C)
                    pReq << CharNameSendCommand;
                    pReq << *this_01;
                SENDMSG()
            }
                break;
            case 9: {
                CSOItem* this_01 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(9);

                NEWMSG(0x190C)
                    pReq << CharNameSendCommand;
                    pReq << *this_01;
                SENDMSG()
            }
                break;
            case 10: {
                CSOItem* this_01 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(10);
                    if(this_01)
                    {
                        NEWMSG(0x190C)
                            pReq << CharNameSendCommand;
                            pReq << *this_01;
                        SENDMSG()
                    }
            }
                break;
            case 11: {
                CSOItem* this_01 = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(11);

                NEWMSG(0x190C)
                    pReq << CharNameSendCommand;
                    pReq << *this_01;
                SENDMSG()
            }
                break;
            case 12: {
                CIFEquipment* myequipments = g_pCGInterface->GetMainPopup()->GetEquipment();
                CSOItem* this_01 = myequipments->GetEquipmentObjectBySlot(12);

                NEWMSG(0x190C)
                    pReq << CharNameSendCommand;
                    pReq << *this_01;
                SENDMSG()
            }
                break;

        }

        MsgBuffer->FlushRemaining();
    }
    if(MsgBuffer->msgid()==0xB093)
    {
        BYTE checktype;
        std::n_string CharNameSendCommand;
        *MsgBuffer >>checktype;
        if(checktype==0x1)
        {
            *MsgBuffer >> CharNameSendCommand ;
            if (g_pCICPlayer) {
                const SPartyData &partyData = g_CCharacterDependentData.GetPartyData();
                CMsgStreamBuffer buf(0x7093);
                buf << (BYTE)0x2;
                buf <<  (BYTE)(partyData.NumberOfMembers);
                buf << CharNameSendCommand;
                for (size_t i = 0; i < partyData.NumberOfMembers; ++i)
                {
                    const SPartyMemberData &memberData = g_CCharacterDependentData.GetPartyMemberData(i);
                    buf << std::n_string(TO_NSTRING(memberData.m_charactername));
                    buf << (UINT32)(memberData.currentLevel);
                    buf << (UINT32)(memberData.refobjID);

                }
                SendMsg(buf);

            }
        }
        else if(checktype==0x2)
        {
            byte partymembercount;
            int CharRace;
            std::n_string CharName;
            std::n_string CharLevel;
            byte lineNum;
            *MsgBuffer >>partymembercount;
            g_pCGInterface->GetCIFSTPartyMatchMemberViewerGUI()->Clear();
            CIFSTPartyMatchMemberViewer::PartyMatchMemberList.clear();
            for (int i = 0; i < partymembercount; ++i) {

                *MsgBuffer >> lineNum >> CharRace >> CharName >> CharLevel;

                CIFSTPartyMatchMemberViewer::PartyMatchMember Member = CIFSTPartyMatchMemberViewer::PartyMatchMember();
                Member.LineNum = lineNum;
                Member.Race = CharRace;
                Member.CharName = TO_WSTRING(CharName);
                Member.LevelText = L"Lv";
                Member.Level = TO_WSTRING(CharLevel);
                g_pCGInterface->GetCIFSTPartyMatchMemberViewerGUI()->PartyMatchMemberList.push_back(Member);
                g_pCGInterface->GetCIFSTPartyMatchMemberViewerGUI()->UpdatePartyMemberList();

            }

        }
        else if(checktype==0x3)
        {
            g_pCGInterface->GetCIFSTPartyMatchMemberViewerGUI()->Clear();
            CIFSTPartyMatchMemberViewer::PartyMatchMemberList.clear();

        }


        MsgBuffer->FlushRemaining();
    }

    /// ORG PACKETS

    if (MsgBuffer->msgid() == 0xB06C)
    {
        byte Bool;
        byte pageCount;
        byte pageIndex;
        byte partyCount;
        int Number;
        int MasterJoinID;
        std::n_string MasterName;
        byte RaceType;
        byte MemberCount;
        byte setup;
        byte purpose;
        byte LevelMin;
        byte LevelMax;
        std::n_string Title;
        *MsgBuffer >>Bool;
        if(Bool==1)
        {
            *MsgBuffer >> pageCount>>pageIndex>>partyCount;

            for (byte j = 1; j < partyCount; j++)
            {
                *MsgBuffer >>Number>>MasterJoinID>>MasterName>>RaceType>>MemberCount>>setup>>purpose>>LevelMin>>LevelMax>>Title;
                //printf("Number %d \n",Number);
                //printf("Purpose %d \n",purpose);
                SRPartyMatch Party;
                Party.Number = Number;
                Party.MasterJoinID = MasterJoinID;
                Party.MasterName = MasterName.c_str();
                Party.Title = Title.c_str();
                Party.Racetype = RaceType;
                Party.MemberCount = MemberCount;
                Party.setup = setup;
                Party.Purpose = purpose;
                Party.LevelMin = LevelMin;
                Party.LevelMax = LevelMax;
                std::map<int, SRPartyMatch>::iterator foundedInfo = PartyMatches.find(Number);
                if (foundedInfo != PartyMatches.end())
                    PartyMatches[Number] = Party;
                else
                    PartyMatches.insert(std::pair<int,SRPartyMatch>(Number,Party));

            }

        }
        MsgBuffer->m_currentReadBytes = 0;
    }

    if (MsgBuffer->msgid() == 0x3020)
    {
        DiscordManager::UpdateState(GAME_STATE::IN_GAME);
        MsgBuffer->m_currentReadBytes = 0;
    }

    if (MsgBuffer->msgid() == 0x34B4)
    {
        DiscordManager::UpdateState();
        MsgBuffer->m_currentReadBytes = 0;
    }
    if (MsgBuffer->msgid() == 0x3054)
    {
        uint32_t uniqueID; *MsgBuffer >> uniqueID;
        // Check if my character level up
        if (uniqueID == g_pCICPlayer->GetUniqueID())
        {
            DiscordManager::UpdateState();
        }

        MsgBuffer->m_currentReadBytes = 0;
    }
  /*  if (MsgBuffer->msgid() == 0x3020)
    {
        uint32_t PlayerUniqueID;
        MsgBuffer->Read(&PlayerUniqueID, 4);
        CICPlayer *TargetPlayer = g_pCICPlayer->GetCICPlayerByUniqueID(PlayerUniqueID);
        wchar_t buffer1[45];
        std::wstring mymsg1;
        swprintf_s(buffer1, sizeof(buffer1), L"Hello %s,Test 3020", g_pCICPlayer->GetCharName().c_str());
        mymsg1.assign(buffer1);
        g_pCGInterface->ShowLogMessage(D3DCOLOR_RGBA(0x00, 0xff, 0x00, 255), mymsg1.c_str());
        int CustomIcon =1337;
        if (CustomIcon != 0)
        {
            std::map<std::wstring, uint32_t>::iterator iconData = g_CGlobalDataManager->m_CharacterIcons.find(TargetPlayer->GetCharName().c_str());
            if (iconData == g_CGlobalDataManager->m_CharacterIcons.end())
            {
                g_CGlobalDataManager->m_CharacterIcons.insert(pair<std::wstring,UINT32>(TargetPlayer->GetCharName().c_str(),CustomIcon));
            }
*//*            else // if exists
            {
                for (std::pair<const std::wstring, uint32_t> &val : g_CGlobalDataManager->m_CharacterIcons)
                {
                    if (val.first == TargetPlayer->GetCharName().c_str())
                    {
                        if (val.second != CustomIcon)
                            val.second = CustomIcon;
                    }
                }
            }*//*
        }
        else if(TargetPlayer && TargetPlayer->GetCharName().c_str() != L"")
        {
            if (g_CGlobalDataManager->m_CharacterIcons.find(TargetPlayer->GetCharName().c_str()) != g_CGlobalDataManager->m_CharacterIcons.end())
            {
                g_CGlobalDataManager->m_CharacterIcons.erase(TargetPlayer->GetCharName().c_str());
            }
        }
        MsgBuffer->m_currentReadBytes = 0;
    }*/
    if (MsgBuffer->msgid() == 0x706D)
    {
        UINT32 requestID;
        UINT32 joinID;
        UINT32 matchNumber;
        UINT32 masteryID_primary;
        UINT32 masteryID_secondary;
        BYTE unk6;
        BYTE unk7;
        UINT32 joinID_x2;
        std::n_string CharName;

        *MsgBuffer >> requestID >> joinID >> matchNumber >> masteryID_primary >> masteryID_secondary >> unk6 >> unk7 >> joinID_x2 >> CharName;

        CharNameRequest = TO_WSTRING(CharName).c_str();
        if (Blocked_Party_CharNameRequest.find(CPSMission::CharNameRequest.c_str()) != Blocked_Party_CharNameRequest.end())
        {

            CMsgStreamBuffer buf(0x306E);
            buf << requestID;
            buf << joinID;
            buf << BYTE(0);
            SendMsg(buf);

        }
        else
        {
            if(Rebot::Config.RequestJoinParty && Rebot::RebotStart)
            {
                CMsgStreamBuffer buf(0x306E);
                buf << requestID;
                buf << joinID;
                buf << BYTE(1);
                SendMsg(buf);
            }

        }
        MsgBuffer->m_currentReadBytes = 0;
    }
    if (MsgBuffer->msgid() == 0x30DF)
    {
        unsigned int ID;
        BYTE Hawn;
        *MsgBuffer >> ID >> Hawn;

        if (ID == GET_OWN_GAME_ID())
        {
            CurHawn = Hawn;
        }
        MsgBuffer->m_currentReadBytes = 0;
    }
    if (MsgBuffer->msgid() == 0x309C)
    {
        unsigned int PetUniqueID;
        BYTE UpdateType;
        *MsgBuffer >> PetUniqueID >> UpdateType;

        if (UpdateType == 1)
        {
            if(Rebot::Config.AutoAttackPetResurrect && Rebot::Config.PetAttackResurrectItemID != 0 && Rebot::Config.PetAttackItemID > 0)
            {
                CIFSlotWithHelp* pSlot;
                CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
                BYTE PetDiedSlot;
                BYTE ResurrectSlot;
                bool PetAttackResurrectItemIDFound = false;
                for (int i = 0; i <  g_pCICPlayer->m_inventorySize; i++)
                {
                    pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                    if(pSlot->ItemInfo)
                    {
                        if ( pSlot->ItemInfo->GetItemData()->m_id == Rebot::Config.PetAttackItemID && pSlot->ItemInfo->m_petStatus == 4)
                        {
                                PetDiedSlot = pSlot->UniqueID()- 100 + 0xD;
                                CMsgStreamBuffer buf(0x704C);
                                buf << (byte)(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_RESURRECT_SLOT);
                                buf << (UINT16)(0xec30) ;
                                buf << (byte)(PetDiedSlot) ;
                                SendMsg(buf);
                            break;
                        }
                    }
                }
            }
        }
        MsgBuffer->m_currentReadBytes = 0;
    }
    if (MsgBuffer->msgid() == 0x3305)
    {

            BYTE JOBTYPE =  g_pCICPlayer->FUN_009db0d0();
            BYTE CURLEVEL = g_pCICPlayer->GetCurrentLevel();
             uregion CurRegion = g_pCICPlayer->GetRegion();

            CMsgStreamBuffer buf(0x3560);
            buf << JOBTYPE;
            buf << CURLEVEL;
            buf << CurRegion.r;
            SendMsg(buf);



        if (!CPSMission::char_is_ready)
        {
            if (g_pCICPlayer)
            {
                emojiHandler();
                wchar_t* NewMsg = new wchar_t[1024];
                wsprintfW(NewMsg,TSM_GETTEXTPTR("UIIT_ST_WELCOME_MSG"), g_pCICPlayer->GetCharName().c_str());
                g_pCGInterface->ShowLogMessage(D3DCOLOR_RGBA(0x00, 0xff, 0x00, 255), NewMsg);
                CPSMission::char_is_ready = true;
                wchar_t* NewMsg2 = new wchar_t[1024];
                wsprintfW(NewMsg2,L"%s", g_pCICPlayer->GetCharName().c_str());
                SetWindowTextW(Rebot::GameHWND,NewMsg2);
                g_pCGInterface->GetCIFSTEffectGUI()->SetHWIDTime();
                if(LOTO_ENABLE)
                    g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG2_NAME"));
            }
        }

        if (m_PartyDisabledRegions.find(g_pCICPlayer->GetRegion().r) != m_PartyDisabledRegions.end())
        {
            const SPartyData &partyData = g_CCharacterDependentData.GetPartyData();
            if (partyData.PartyNumber > 0)
            {

                CMsgStreamBuffer buf(0x706B);
                buf<<partyData.PartyNumber;
                SendMsg(buf);

            }
            if (g_CCharacterDependentData.IsInParty())
            {

                CMsgStreamBuffer buf(0x7061);
                buf;
                SendMsg(buf);
            }
        }
        if (DimenSionalRegion.find(g_pCICPlayer->GetRegion().r) != DimenSionalRegion.end())
        {
            CIFWnd *IFMinimap = (CIFWnd *) g_pCGInterface->m_IRM.GetResObj(10, 1);
            g_pCGInterface->GetCIFSTBattleRoyaleKillCountGUI()->ShowGWnd(true);
            if(IFMinimap)
            {
                if(IFMinimap->IsVisible())
                    IFMinimap->ShowGWnd(false);
            }
        }
        else
        {
            CIFWnd *IFMinimap = (CIFWnd *) g_pCGInterface->m_IRM.GetResObj(10, 1);
            g_pCGInterface->GetCIFSTBattleRoyaleKillCountGUI()->ShowGWnd(false);
            if(IFMinimap)
            {
                if(!IFMinimap->IsVisible())
                    IFMinimap->ShowGWnd(true);
            }
        }

        if(g_pCGInterface->GetChestGUI()->IsVisible())
            g_pCGInterface->GetChestGUI()->OnCloseWnd();
        if(g_pCGInterface->GetMainMenu()->IsVisible())
            g_pCGInterface->GetMainMenu()->OnCloseWnd();
        if(g_pCGInterface->GetChangeGrantNameGUI()->IsVisible())
            g_pCGInterface->GetChangeGrantNameGUI()->OnCloseWnd();
        if(g_pCGInterface->GetCharLockGUI()->IsVisible())
            g_pCGInterface->GetCharLockGUI()->OnCloseWnd();
        if(g_pCGInterface->GetUniqueHistoryGUI()->IsVisible())
            g_pCGInterface->GetUniqueHistoryGUI()->OnCloseWnd();
        if(g_pCGInterface->GetSwitchTitleGUI()->IsVisible())
            g_pCGInterface->GetSwitchTitleGUI()->OnCloseWnd();
        if(g_pCGInterface->GetCustomTitleGUI()->IsVisible())
            g_pCGInterface->GetCustomTitleGUI()->OnCloseWnd();
        if(g_pCGInterface->GetConfirmGUI()->IsVisible())
            g_pCGInterface->GetConfirmGUI()->OnCloseWnd();
        if(g_pCGInterface->GetCustomRankGUI()->IsVisible())
            g_pCGInterface->GetCustomRankGUI()->OnCloseWnd();
        if(g_pCGInterface->GetEventTimeGUI()->IsVisible())
            g_pCGInterface->GetEventTimeGUI()->OnCloseWnd();
        if(g_pCGInterface->GetSurvivalKillGUI()->IsVisible())
            g_pCGInterface->GetSurvivalKillGUI()->OnCloseWnd();
        if(g_pCGInterface->GetTotalPointsGUI()->IsVisible())
            g_pCGInterface->GetTotalPointsGUI()->OnCloseWnd();
        if(g_pCGInterface->GetEventRegisterGUI()->IsVisible())
            g_pCGInterface->GetEventRegisterGUI()->OnCloseWnd();
        if(g_pCGInterface->GetEventXoSoGUI()->IsVisible())
            g_pCGInterface->GetEventXoSoGUI()->OnCloseWnd();
        if(g_pCGInterface->GetEventXoSoLichSuGUI()->IsVisible())
            g_pCGInterface->GetEventXoSoLichSuGUI()->OnCloseWnd();
        if(g_pCGInterface->GetEventLotteryGUI()->IsVisible())
            g_pCGInterface->GetEventLotteryGUI()->OnCloseWnd();
        if(g_pCGInterface->GetPvpChallengeGUI()->IsVisible())
            g_pCGInterface->GetPvpChallengeGUI()->OnCloseWnd();
        if(g_pCGInterface->GetPvpChallengeAnswerGUI()->IsVisible())
            g_pCGInterface->GetPvpChallengeAnswerGUI()->OnCloseWnd();
        if(g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->IsVisible())
            g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->OnCloseWnd();
        if(g_pCGInterface->GetCustomNPCGUI()->IsVisible())
            g_pCGInterface->GetCustomNPCGUI()->OnCloseWnd();
        if(g_pCGInterface->GetCharInfoGUI()->IsVisible())
            g_pCGInterface->GetCharInfoGUI()->OnCloseWnd();
        if(g_pCGInterface->GetExtraFeatureGUI()->IsVisible())
            g_pCGInterface->GetExtraFeatureGUI()->OnCloseWnd();


        switch (g_pCICPlayer->GetObjID()) {
            case 1907: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man1.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man1.ddj", 0, 0);

            }
                break;
            case 1908: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man2.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man2.ddj", 0, 0);

            }
                break;
            case 1909: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man3.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man3.ddj", 0, 0);

            }
                break;
            case 1910: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man4.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man4.ddj", 0, 0);

            }
                break;
            case 1911: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man5.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man5.ddj", 0, 0);

            }
                break;
            case 1912: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man6.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man6.ddj", 0, 0);

            }
                break;
            case 1913: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man7.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man7.ddj", 0, 0);

            }
                break;
            case 1914: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man8.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man8.ddj", 0, 0);

            }
                break;
            case 1915: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man9.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man9.ddj", 0, 0);

            }
                break;
            case 1916: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man10.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man10.ddj", 0, 0);

            }
                break;
            case 1917: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man11.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man11.ddj", 0, 0);

            }
                break;
            case 1918: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man12.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man12.ddj", 0, 0);

            }
                break;
            case 1919: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man13.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_man13.ddj", 0, 0);

            }
                break;
            case 1920: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman1.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman1.ddj", 0, 0);

            }
                break;
            case 1921: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman2.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman2.ddj", 0, 0);

            }
                break;
            case 1922: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman3.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman3.ddj", 0, 0);

            }
                break;
            case 1923: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman4.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman4.ddj", 0, 0);

            }
                break;
            case 1924: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman5.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman5.ddj", 0, 0);

            }
                break;
            case 1925: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman6.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman6.ddj", 0, 0);

            }
                break;
            case 1926: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman7.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman7.ddj", 0, 0);

            }
                break;
            case 1927: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman8.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman8.ddj", 0, 0);

            }
                break;
            case 1928: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman9.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman9.ddj", 0, 0);

            }
                break;
            case 1929: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman10.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman10.ddj", 0, 0);

            }
                break;
            case 1930: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman11.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman11.ddj", 0, 0);

            }
                break;
            case 1931: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman12.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman12.ddj", 0, 0);

            }
                break;
            case 1932: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman13.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_ch_woman13.ddj", 0, 0);

            }
                break;

            case 14875: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man1.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man1.ddj", 0, 0);

            }
                break;
            case 14876: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man2.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man2.ddj", 0, 0);

            }
                break;
            case 14877: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man3.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man3.ddj", 0, 0);

            }
                break;
            case 14878: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man4.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man4.ddj", 0, 0);

            }
                break;
            case 14879: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man5.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man5.ddj", 0, 0);

            }
                break;
            case 14880: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man6.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man6.ddj", 0, 0);

            }
                break;
            case 14881: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man7.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man7.ddj", 0, 0);

            }
                break;
            case 14882: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man8.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man8.ddj", 0, 0);

            }
                break;
            case 14883: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man9.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man9.ddj", 0, 0);

            }
                break;
            case 14884: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man10.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man10.ddj", 0, 0);

            }
                break;
            case 14885: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man11.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man11.ddj", 0, 0);

            }
                break;
            case 14886: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man12.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man12.ddj", 0, 0);

            }
                break;
            case 14887: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man13.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_man13.ddj", 0, 0);

            }
                break;

            case 14888: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman1.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman1.ddj", 0, 0);

            }
                break;
            case 14889: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman2.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman2.ddj", 0, 0);

            }
                break;
            case 14890: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman3.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman3.ddj", 0, 0);

            }
                break;
            case 14891: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman4.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman4.ddj", 0, 0);

            }
                break;
            case 14892: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman5.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman5.ddj", 0, 0);

            }
                break;
            case 14893: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman6.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman6.ddj", 0, 0);

            }
                break;
            case 14894: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman7.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman7.ddj", 0, 0);

            }
                break;
            case 14895: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman8.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman8.ddj", 0, 0);

            }
                break;
            case 14896: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman9.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman9.ddj", 0, 0);

            }
                break;
            case 14897: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman10.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman10.ddj", 0, 0);

            }
                break;
            case 14898: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman11.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman11.ddj", 0, 0);

            }
                break;
            case 14899: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman12.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman12.ddj", 0, 0);

            }
                break;
            case 14900: {
                g_pCGInterface->GetMainMenu()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman13.ddj", 0, 0);
                g_pCGInterface->GetTotalPointsGUI()->m_char_icon->TB_Func_13("interface\\character\\char_eu_woman13.ddj", 0, 0);

            }
                break;
        }
        MsgBuffer->m_currentReadBytes = 0;
    }

    /////GUI SETTING
    if (MsgBuffer->msgid() == 0x5114)
    {
        bool GUIGrantName;
        bool GUIUniqueHistory;
        bool GUICustomTitle;
        bool GUISwitchTitle;
        bool GUICharacterLock;
        bool GUIEventTimer;
        bool GUIRank;
        bool GUIRender;
        bool GUIGlobalColor;
        bool GUITotalPoint;
        bool GUICustomNPC;

        *MsgBuffer >>
             GUIGrantName >> GUIUniqueHistory >>
             GUICustomTitle >> GUISwitchTitle  >>
             GUICharacterLock >> GUIEventTimer>>
             GUIRank >> GUIRender >> GUIGlobalColor>>
             GUITotalPoint>>GUICustomNPC;

        CPSMission::Gui_GrantName = GUIGrantName;
        CPSMission::Gui_UniqueHistory = GUIUniqueHistory;
        CPSMission::Gui_CustomTitle = GUICustomTitle;
        CPSMission::Gui_SwitchTitle = GUISwitchTitle;
        CPSMission::Gui_CharacterLock = GUICharacterLock;
        CPSMission::Gui_EventTimer = GUIEventTimer;
        CPSMission::Gui_CustomRank = GUIRank;
        CPSMission::Gui_ColorsRender = GUIRender;
        CPSMission::Gui_GlobalColors = GUIGlobalColor;
        CPSMission::Gui_TotalPoint = GUITotalPoint;
        CPSMission::Gui_CustomNPC = GUICustomNPC;
        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x5116)
    {
        std::n_string DiscordUrl;
        std::n_string FacebookUrl;
        std::n_string WebsiteUrl;

        *MsgBuffer >> DiscordUrl >> FacebookUrl >> WebsiteUrl;

        CPSMission::DiscordUrl = DiscordUrl.c_str();
        CPSMission::FacebookUrl = FacebookUrl.c_str();
        CPSMission::WebsiteUrl = WebsiteUrl.c_str();

        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x5117)
    {
        UINT8 multipler;
        UINT8 splitter;
        UINT64 opcode;
        *MsgBuffer >> multipler >> splitter >> opcode;
        UINT64 Custom_Opcode = (opcode - splitter) / multipler;

        g_MemoryHelper->UnProtect(reinterpret_cast<void*>(cdwPHBotOffset_1), sizeof(UINT16));
        *(UINT16*)(cdwPHBotOffset_1) = Custom_Opcode;
        g_MemoryHelper->ReProtect();
        g_MemoryHelper->UnProtect(reinterpret_cast<void*>(cdwPHBotOffset_2), sizeof(UINT16));
        *(UINT16*)(cdwPHBotOffset_2) = Custom_Opcode;
        g_MemoryHelper->ReProtect();
        g_MemoryHelper->UnProtect(reinterpret_cast<void*>(cdwPHBotOffset_3), sizeof(UINT16));
        *(UINT16*)(cdwPHBotOffset_3) = Custom_Opcode;
        g_MemoryHelper->ReProtect();
        g_MemoryHelper->UnProtect(reinterpret_cast<void*>(cdwPHBotOffset_4), sizeof(UINT16));
        *(UINT16*)(cdwPHBotOffset_4) = Custom_Opcode;
        g_MemoryHelper->ReProtect();
        MsgBuffer->FlushRemaining();
    }
    //////////Chest GUI
     if (MsgBuffer->msgid() == 0x5125) {
        int sCount;
        int No;
        int ItemID;
        std::n_string ItemCode;
        std::n_string CodeName;
        bool RandomStat;
        std::n_string Count;
        std::n_string From;
        std::n_string Date;
        std::n_string OptLevel;
        *MsgBuffer >> sCount;
        BYTE i = 0;
         CIFPlayerChest::ChestList.clear();
        while (i < sCount && sCount > 0) {
            i++;
            *MsgBuffer >> No >> ItemID >> ItemCode >> CodeName >> Count >> RandomStat >> OptLevel >> From >> Date;

            std::wstring ItemName = g_CTextStringManager->GetStringTextByCode(TO_WSTRING(ItemCode).c_str())->c_str();
            static const CItemData *data = NULL;
            data = g_CGlobalDataManager->GetItemData(ItemID);

            CIFPlayerChest::Chest ChestStru = CIFPlayerChest::Chest();
            ChestStru.LineNum = No;
            ChestStru.ItemIconUrl = TO_WSTRING(data->m_assocFileIcon128).c_str() ;
            ChestStru.NameStrID128 = ItemName.c_str();
            ChestStru.CodeName128 = TO_WSTRING(CodeName).c_str();
            ChestStru.Count = TO_WSTRING(Count).c_str();
            ChestStru.RandomStat = RandomStat;
            ChestStru.OptLevel = OptLevel;
            ChestStru.From = TO_WSTRING(From).c_str();
            ChestStru.Date = TO_WSTRING(Date).c_str();
            g_pCGInterface->GetChestGUI()->ChestList.push_back(ChestStru);
        }

         g_pCGInterface->GetChestGUI()->UpdateChest();
         MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x5127) {
         BYTE TYPE;
         std::n_string CodeName;
         *MsgBuffer >> TYPE;
         if (TYPE == 1) {
             *MsgBuffer >> CodeName;
             for (std::vector<CIFPlayerChest::Chest>::iterator it = CIFPlayerChest::ChestList.begin();
                  it != CIFPlayerChest::ChestList.end(); ++it) {
                 if (wcscmp(it->CodeName128.c_str(), TO_WSTRING(CodeName).c_str()) == 0) {
                     g_pCGInterface->GetChestGUI()->Clear();
                     CIFPlayerChest::ChestList.erase(it);
                     g_pCGInterface->GetChestGUI()->UpdateChest();
                     break;
                 }
             }
         } else if (TYPE == 2) {
             g_pCGInterface->GetChestGUI()->Clear();
             CIFPlayerChest::ChestList.clear();
         }
         MsgBuffer->FlushRemaining();
     }
    if (MsgBuffer->msgid() == 0x5118) {
        int EventID;
        BYTE Status;
        *MsgBuffer >> EventID>>Status;
         switch (EventID)
         {
             case 1012: //dautruongsinhtu
             {
                 if(Status== 1)
                 {
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line3->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line4->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line5->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line6->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line7->ClearText();

                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG5_NAME"));
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->SetColor();
                     if(LOTO_ENABLE)
                         g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG2_NAME"));
                 }
                 else
                 {
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line3->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line4->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line5->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line6->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line7->ClearText();
                     if(LOTO_ENABLE)
                         g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG2_NAME"));
                 }

             }
                 break;
             case 1010: //bossjob
             {
                 if(Status== 1)
                 {
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line3->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line4->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line5->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line6->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line7->ClearText();

                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG3_NAME"));
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->SetColor();
                     if(LOTO_ENABLE)
                         g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG2_NAME"));
                 }
                 else
                 {
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line3->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line4->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line5->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line6->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line7->ClearText();
                     if(LOTO_ENABLE)
                         g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG2_NAME"));
                 }

             }
                 break;
             case 1014: //drunk
             {
                 if(Status== 1)
                 {
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line3->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line4->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line5->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line6->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line7->ClearText();

                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG6_NAME"));
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->SetColor();
                     if(LOTO_ENABLE)
                         g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG2_NAME"));
                 }
                 else
                 {
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line3->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line4->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line5->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line6->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line7->ClearText();
                     if(LOTO_ENABLE)
                         g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG2_NAME"));
                 }

             }
                 break;
             case 1015: //battleroyale
             {
                 if(Status== 1)
                 {
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line3->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line4->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line5->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line6->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line7->ClearText();

                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG7_NAME"));
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->SetColor();
                     if(LOTO_ENABLE)
                         g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG2_NAME"));
                 }
                 else
                 {
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line1->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line3->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line4->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line5->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line6->ClearText();
                     g_pCGInterface->GetEventRegisterGUI()->Slot1->Line7->ClearText();
                     if(LOTO_ENABLE)
                         g_pCGInterface->GetEventRegisterGUI()->Slot1->Line2->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG2_NAME"));
                 }

             }
                 break;
         }
        MsgBuffer->FlushRemaining();
    }
     /////////// Unique History GUI
    if (MsgBuffer->msgid() == 0x5130) {
         BYTE sCount;
         BYTE PageNum;
         BYTE No;
         int DBID;
         BYTE State;
         std::n_string Killer;
         std::n_string Time;
         *MsgBuffer >> sCount;
         BYTE i = 0;

         CIFSTUniqueHistory::UniqueHistoryList.clear();
         while (i < sCount && sCount > 0)
         {
             i++;

             *MsgBuffer >> PageNum >> No >> DBID >> State >> Killer >> Time;

             std::wstring UqName = L"<NONE>";
             if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
             {
                 if (CharData* uqdata = g_datamanager->GetCharData(DBID))
                 {
                     UqName = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
                 }
             }
            std::wstring States = L"";
            if(State==1)
            {
                std::n_string AliveText = "UIIT_ST_UNIQUE_ALIVE";
                States = TSM_GETTEXTPTR("UIIT_ST_UNIQUE_ALIVE");
            }
            if(State==0)
            {
                std::n_string DieText = "UIIT_ST_UNIQUE_DIE";
                States = TSM_GETTEXTPTR("UIIT_ST_UNIQUE_DIE");
            }
            CIFSTUniqueHistory::UniqueHistory UniqueHis = CIFSTUniqueHistory::UniqueHistory();
            UniqueHis.LineNum = No;
            UniqueHis.NameStrID128 = UqName.c_str();
            UniqueHis.State = States.c_str();
            UniqueHis.Killer = TO_WSTRING(Killer).c_str();
            UniqueHis.Date = TO_WSTRING(Time).c_str();
            g_pCGInterface->GetUniqueHistoryGUI()->UniqueHistoryList.push_back(UniqueHis);

        }

        g_pCGInterface->GetUniqueHistoryGUI()->UpdateUniqueList();
        MsgBuffer->FlushRemaining();
    }
     ////////// notice
    if (MsgBuffer->msgid() == 0x5102)
    {
        /*
        Notice Types
        1- Notice Red?
        2- Blue Noitfy
        3- Green Quest huh?
        4- Normal System Msg Yellow one.
        5- Guide System Msg seems blue?
        6- Colored System Msg thx flo <3
        7- Colored Chat Msg like PM,ALL CHAT,GLOBAL
        */
        BYTE Type;
        std::n_string notice;
        int color;
        *MsgBuffer >> Type >> notice >> color;

        if (Type == 1)
        {
            g_pCGInterface->ShowMessage_Notice(Convert(notice));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            //int color = D3DCOLOR_ARGB(255, 97, 204, 238);
            systemmessage->WriteMessage(0xFF, color, Convert(notice), 0, 1);
        }

        if (Type == 2)
        {
            g_pCGInterface->ShowMessage_Warning(Convert(notice));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
           // int color = D3DCOLOR_ARGB(255, 97, 204, 238);
            systemmessage->WriteMessage(0xFF, color, Convert(notice), 0, 1);
        }

        if (Type == 3)
        {
            g_pCGInterface->ShowMessage_Quest(Convert(notice));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
           // int color = D3DCOLOR_ARGB(255, 97, 204, 238);
            systemmessage->WriteMessage(0xFF, color, Convert(notice), 0, 1);
        }

        if (Type == 4)
        {
            g_pCGInterface->ShowMessage_Orange(Convert(notice));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            //int color = D3DCOLOR_ARGB(255, 97, 204, 238);
            systemmessage->WriteMessage(0xFF, color, Convert(notice), 0, 1);
        }

        if (Type == 5)
        {
            g_pCGInterface->ShowMessage_Purble(Convert(notice));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
           // int color = D3DCOLOR_ARGB(255, 97, 204, 238);
            systemmessage->WriteMessage(0xFF, color, Convert(notice), 0, 1);
        }

        if (Type == 6)
        {
            g_pCGInterface->WriteSystemMessage(SYSLOG_NONE, Convert(notice));
        }

        if (Type == 7)
        {
            g_pCGInterface->WriteSystemMessage(SYSLOG_GUIDE, Convert(notice));
        }

        if (Type == 8)
        {

            g_pCGInterface->ShowLogMessage(color, Convert(notice));
        }

        if (Type == 9)
        {
            std::n_string Key;
            UINT Color;
            *MsgBuffer >> Color >> Key;

            std::n_wstring local_64;
            local_64 = L"(";
            local_64 += Convert(Key);
            local_64 += L"):";

            std::n_wstring local_80 = local_64 + Convert(notice);

            g_pCGInterface->FUN_00777c30(CHAT_Ask, local_80.c_str(), Color, 1);

        }

        if (Type == 10)
        {
            std::n_string Key;
            *MsgBuffer >> Key;

            wchar_t buffer1[255];
            std::wstring Name = g_CTextStringManager->GetStringByNameStrID(&TO_WSTRING(Key))->c_str();

            if (Name.empty())
                Name = L"<UnKnown Item>";

            swprintf_s(buffer1, sizeof(buffer1), TO_WSTRING(notice).c_str(), Name.c_str());
            std::n_wstring strmsg;
            strmsg.assign(buffer1);

            g_pCGInterface->ShowMessage_Purble(strmsg.c_str());

            CMsgStreamBuffer buf(0x3504);
            buf << TO_NSTRING(strmsg);
            SendMsg(buf);
        }

        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x5104)
    {

        std::n_string KillerName;
        int UniqueID;
        int Silk;
        int Gold;
        int Point;
        std::n_string ItemCode;
        *MsgBuffer >> KillerName >> UniqueID >> Silk >> Gold >> Point >> ItemCode;

        std::wstring UniqueName = L"";
        CTextStringManager* g_textmanager = CTextStringManager::Get();
        if (CGlobalDataManager * g_datamanager = CGlobalDataManager::Get())
        {
            if (CharData* uqdata = g_datamanager->GetCharData(UniqueID))
            {
                UniqueName = g_textmanager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
            }
        }
        std::wstring ItemName = g_CTextStringManager->GetStringTextByCode(TO_WSTRING(ItemCode).c_str())->c_str();

        wchar_t* NewMsg = new wchar_t[1024];
        wsprintfW(NewMsg,TSM_GETTEXTPTR("UIIT_UNIQUE_REWARD_NOTICE"), KillerName.c_str(), UniqueName.c_str(),Silk,Gold,Point,ItemName.c_str());
        g_pCGInterface->ShowMessage_Orange(NewMsg);
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 224, 199, 144);
        systemmessage->WriteMessage(0xFF, color, NewMsg, 0, 1);

        MsgBuffer->FlushRemaining();
    }
    /////////Battle royale
    if (MsgBuffer->msgid() == 0x5144)
    {
        byte CurStage = 0;
        byte ShowHide = 0;
        int Timer = 0 ;
        *MsgBuffer >> CurStage >> ShowHide >> Timer;


        switch (CurStage)
        {

            case 0:
            {
                g_pCGInterface->GetCIFSTEffectGUI()->SetBattleRoyaleRegionStartTime();
            }
            break;
            case 1:
            {
                //Rebot::Config.CircleShow = ShowHide;
                g_pCGInterface->GetCIFSTEffectGUI()->SetBattleRoyaleStage_1_Time(1);
                Rebot::Config.CircleGreenShow = ShowHide;
            }
                break;
            case 2:
            {
                //Rebot::Config.CircleShow = ShowHide;
                //g_pCGInterface->GetCIFSTEffectGUI()->SetBattleRoyaleStage_2_Time(1);
                Rebot::Config.CircleGreenShow = ShowHide;
            }
                break;
            case 3:
            {
                //Rebot::Config.CircleShow = ShowHide;
                g_pCGInterface->GetCIFSTEffectGUI()->SetBattleRoyaleStage_2_Time(1);
                Rebot::Config.CircleGreenShow = ShowHide;
            }
                break;
            case 5:
            {
                //Rebot::Config.CircleShow = ShowHide;
                g_pCGInterface->GetCIFSTEffectGUI()->SetBattleRoyaleStage_3_Time(1);
                Rebot::Config.CircleGreenShow = ShowHide;
            }
                break;
            case 7:
            {
                //Rebot::Config.CircleShow = ShowHide;
                g_pCGInterface->GetCIFSTEffectGUI()->SetBattleRoyaleStage_4_Time(1);
                Rebot::Config.CircleGreenShow = ShowHide;
            }
                break;
            case 9:
            {
                //Rebot::Config.CircleShow = ShowHide;
                g_pCGInterface->GetCIFSTEffectGUI()->SetBattleRoyaleStage_5_Time(1);
                Rebot::Config.CircleGreenShow = ShowHide;
            }
                break;
            case 16:
            {
                Rebot::Config.x1 = 0;
                Rebot::Config.x2 = 0;
                Rebot::Config.y1 = 0;
                Rebot::Config.y2 = 0;
                Rebot::Config.cercle = -47;
                Rebot::Config.cercleX = 321;
                Rebot::Config.cercleY = 202;
                Rebot::Config.cercleRadius = 176;
                Rebot::Config.CircleShow = false;
                Rebot::Config.CircleGreenShow = false;
                g_pCGInterface->GetCIFSTEffectGUI()->SetBattleRoyaleRegionKillTime();
               // g_pCGInterface->GetCIFSTBloodEffectGUI()->ShowGWnd(false);
            }
                break;
            case 17:
            {
               // g_pCGInterface->GetCIFSTBloodEffectGUI()->ShowGWnd(ShowHide);
            }
                break;
        }
        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x5145)
    {
        byte UpdateType = 0;
        int LeftSurvivors = 0;
        int TotalParticipants = 0 ;
        int Mykills = 0;
        *MsgBuffer >> UpdateType >> LeftSurvivors >> TotalParticipants >> Mykills;


        switch (UpdateType)
        {
            case 0:
            {
                wchar_t buffer[255];
                swprintf_s(buffer,L"%d", LeftSurvivors);
                wchar_t buffer2[255];
                swprintf_s(buffer2,L"%d", TotalParticipants);
                g_pCGInterface->GetCIFSTBattleRoyaleKillCountGUI()->m_left_survivor_value->SetText(buffer);
                g_pCGInterface->GetCIFSTBattleRoyaleKillCountGUI()->m_total_participants_value->SetText(buffer2);
            }
                break;
            case 1:
            {
                wchar_t buffer[255];
                swprintf_s(buffer,L"%d", Mykills);
                g_pCGInterface->GetCIFSTBattleRoyaleKillCountGUI()->m_my_kill_value->SetText(buffer);
                wchar_t buffer2[255];
                swprintf_s(buffer2,L"%d", LeftSurvivors);
                g_pCGInterface->GetCIFSTBattleRoyaleKillCountGUI()->m_left_survivor_value->SetText(buffer2);
            }
                break;

        }
        MsgBuffer->FlushRemaining();
    }
     ////////// DPS Metter GUI
    if (MsgBuffer->msgid() == 0x5101)
    {
        int FormID = 0;
        bool ShowHide = 0;
        *MsgBuffer >> FormID >> ShowHide;


        switch (FormID)
        {
            case 19579:
            {
                if (ShowHide == 0) {
                    //CIFMainMenu::DmgMeterGui->Clear();
                    //g_pCGInterface->GetDpsMetterGUI()->ShowGWnd(false);
                }
            }
                break;
            case 19586:
            {
                if (ShowHide == 0) {
                    g_pCGInterface->GetSurvivalKillGUI()->Clear();
                    g_pCGInterface->GetSurvivalKillGUI()->ShowGWnd(false);
                }
            }
            case 19596:
            {
                if (ShowHide == 0) {
                    g_pCGInterface->GetFtwCunterGUI()->Clear();
                    g_pCGInterface->GetFtwCunterGUI()->ShowGWnd(false);
                }
            }
                break;
        }
        MsgBuffer->FlushRemaining();
    }
    if (MsgBuffer->msgid() == 0x5103)
    {
        std::n_string DMG;
        int PlayerID;
        int MobID;
        int RecordCount;

        std::wstring UniqueName = L"";

        *MsgBuffer >> MobID >> RecordCount;
        BYTE i = 0;

        CTextStringManager* g_textmanager = CTextStringManager::Get();
        if (CGlobalDataManager * g_datamanager = CGlobalDataManager::Get())
        {
            if (CharData* uqdata = g_datamanager->GetCharData(MobID))
            {
                UniqueName = g_textmanager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
            }
        }

        g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot1->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot2->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot3->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot4->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot5->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot6->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot7->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot8->SetText(L"-");


        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot1->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot2->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot3->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot4->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot5->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot6->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot7->SetText(L"-");
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot8->SetText(L"-");

        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot1->m_FontTexture.SetColor(0xFFFFFFFF);
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot2->m_FontTexture.SetColor(0xFFFFFFFF);
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot3->m_FontTexture.SetColor(0xFFFFFFFF);
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot4->m_FontTexture.SetColor(0xFFFFFFFF);
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot5->m_FontTexture.SetColor(0xFFFFFFFF);
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot6->m_FontTexture.SetColor(0xFFFFFFFF);
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot7->m_FontTexture.SetColor(0xFFFFFFFF);
        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot8->m_FontTexture.SetColor(0xFFFFFFFF);

        g_pCGInterface->GetDpsMetterGUI()->m_unique_name->m_FontTexture.SetColor(0xFFCCFF00);

        while (i < RecordCount && RecordCount > 0)
        {
            i++;
            *MsgBuffer >> PlayerID >> DMG;
            CICharactor* Char = 0;
            Char = GetCharacterObjectByID_MAYBE(PlayerID);
            if (Char != 0)
            {

                if (i == 1 && PlayerID)
                {
                    g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot1->SetText(Char->GetName().c_str());
                    g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot1->SetText(TO_WSTRING(DMG).c_str());
                    if(g_pCICPlayer->GetName() == Char->GetName())
                    {
                        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot1->m_FontTexture.SetColor(0xFF00FF38);
                    }

                }
                else if (i == 2 && PlayerID)
                {
                    g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot2->SetText(Char->GetName().c_str());
                    g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot2->SetText(TO_WSTRING(DMG).c_str());
                    if(g_pCICPlayer->GetName()==Char->GetName())
                    {
                        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot2->m_FontTexture.SetColor(0xFF00FF38);
                    }
                }
                else if (i == 3 && PlayerID)
                {
                    g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot3->SetText(Char->GetName().c_str());
                    g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot3->SetText(TO_WSTRING(DMG).c_str());
                    if(g_pCICPlayer->GetName() == Char->GetName())
                    {
                        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot3->m_FontTexture.SetColor(0xFF00FF38);
                    }
                }
                else if (i == 4 && PlayerID)
                {
                    g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot4->SetText(Char->GetName().c_str());
                    g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot4->SetText(TO_WSTRING(DMG).c_str());
                    if(g_pCICPlayer->GetName() == Char->GetName())
                    {
                        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot4->m_FontTexture.SetColor(0xFF00FF38);
                    }
                }
                else if (i == 5 && PlayerID)
                {
                    g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot5->SetText(Char->GetName().c_str());
                    g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot5->SetText(TO_WSTRING(DMG).c_str());
                    if(g_pCICPlayer->GetName() == Char->GetName())
                    {
                        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot5->m_FontTexture.SetColor(0xFF00FF38);
                    }
                }
                else if (i == 6 && PlayerID)
                {
                    g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot6->SetText(Char->GetName().c_str());
                    g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot6->SetText(TO_WSTRING(DMG).c_str());
                    if(g_pCICPlayer->GetName() == Char->GetName())
                    {
                        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot6->m_FontTexture.SetColor(0xFF00FF38);
                    }
                }
                else if (i == 7 && PlayerID)
                {
                    g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot7->SetText(Char->GetName().c_str());
                    g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot7->SetText(TO_WSTRING(DMG).c_str());
                    if(g_pCICPlayer->GetName() == Char->GetName())
                    {
                        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot7->m_FontTexture.SetColor(0xFF00FF38);
                    }
                }
                else if (i == 8 && PlayerID)
                {
                    g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot8->SetText(Char->GetName().c_str());
                    g_pCGInterface->GetDpsMetterGUI()->m_damage_lable_slot8->SetText(TO_WSTRING(DMG).c_str());
                    if(g_pCICPlayer->GetName() == Char->GetName())
                    {
                        g_pCGInterface->GetDpsMetterGUI()->m_playername_lable_slot8->m_FontTexture.SetColor(0xFF00FF38);
                    }
                }
                {
                    g_pCGInterface->GetDpsMetterGUI()->m_unique_name->SetText((UniqueName).c_str());
                }
            }
        }

        g_pCGInterface->GetDpsMetterGUI()->ShowGWnd(true);
        g_pCGInterface->GetCIFSTEffectGUI()->SetDPSTime(4);
        MsgBuffer->FlushRemaining();
    }
    ///////////////
    if (MsgBuffer->msgid() == 0x9920)// electus point limit
    {

        int id = 0;
        std::n_string msg;
        int color;
        *MsgBuffer >> id>>msg>>color ;

        if(id != 0 )
        {

            D3DCOLOR chatcolor = color;

            wchar_t* NewMsg2 = new wchar_t[1024];

            wsprintfW(NewMsg2,L"%S", msg.c_str());

            std::n_wstring strMessageCopy = NewMsg2;
            int signal = -2;
            std::n_wstring MessageTemp;
            if (strMessageCopy.find('<') != std::string::npos && strMessageCopy.find('>') != std::string::npos)
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

                CIFChatViewer* chatView = (CIFChatViewer*)g_pCGInterface->m_IRM.GetResObj(1, 1);
                chatView->WriteToChatW(strMessageCopy.c_str(), chatcolor, 1);

        }

        MsgBuffer->FlushRemaining();
    }
    ////////////// Char lock system
    if (MsgBuffer->msgid() == 0x9946)// update honor point
    {

        int FormID = 0;
        int CharID = 0;
        *MsgBuffer >> FormID >>CharID;


        if (FormID == 11) // itemlock unlock
        {

            wchar_t buffer[80];
            wchar_t buffer1[80];
            wchar_t buffer2[80];
            wchar_t buffer3[80];
            swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_ST_CHARLOCK_LOCK"));
            swprintf_s(buffer1, TSM_GETTEXTPTR("UIIT_ST_CHARLOCK_UNLOCK"));
            swprintf_s(buffer2, TSM_GETTEXTPTR("UIIT_ST_STATUS_UNLOCKED"));
            swprintf_s(buffer3, TSM_GETTEXTPTR("UIIT_ST_STATUS_LOCK_BTN"));
            g_pCGInterface->GetCharLockGUI()->m_lock_status->m_FontTexture.SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
            g_pCGInterface->GetCharLockGUI()->m_lock_status->SetText(buffer1);
            g_pCGInterface->GetCharLockGUI()->m_button_lock->SetText(buffer3);
            g_pCGInterface->GetCharLockGUI()->m_lock_status_icon->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\charlock_unlocked.ddj", 0, 0);


            g_pCGInterface->GetMainMenu()->m_char_lock_lable->m_FontTexture.SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
            g_pCGInterface->GetMainMenu()->m_char_lock_lable->SetText(buffer2);

        }
        else if (FormID == 12) // itemlock lock
        {

            wchar_t buffer[80];
            wchar_t buffer1[80];
            wchar_t buffer2[80];
            wchar_t buffer3[80];
            swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_ST_CHARLOCK_LOCK"));
            swprintf_s(buffer1, TSM_GETTEXTPTR("UIIT_ST_CHARLOCK_UNLOCK"));
            swprintf_s(buffer2, TSM_GETTEXTPTR("UIIT_ST_STATUS_LOCKED"));
            swprintf_s(buffer3, TSM_GETTEXTPTR("UIIT_ST_STATUS_UNLOCK_BTN"));
            g_pCGInterface->GetCharLockGUI()->m_lock_status->m_FontTexture.SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
            g_pCGInterface->GetCharLockGUI()->m_lock_status->SetText(buffer);
            g_pCGInterface->GetCharLockGUI()->m_button_lock->SetText(buffer3);
            g_pCGInterface->GetCharLockGUI()->m_lock_status_icon->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\charlock_locked.ddj", 0, 0);


            g_pCGInterface->GetMainMenu()->m_char_lock_lable->m_FontTexture.SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
            g_pCGInterface->GetMainMenu()->m_char_lock_lable->SetText(buffer2);

        }

        MsgBuffer->FlushRemaining();
    }
    /////////////

    //MsgBuffer->FlushRemaining();
    //Returning 1 means packet is accepted & read, 0 means fail & afair client may crash if you do return 0
    //Also, if you're planning to read original packets, set TotalReadBytes to 0 after you finish reading, because sro_client will re-read this stuff and if any byte were read before, it'll crash because it attempts to read over max bytes limit.
    return reinterpret_cast<int(__thiscall*)(CPSMission*, CMsgStreamBuffer*)>(0x0084CAB0)(this, MsgBuffer);
}
