#include "StdAfx.h"
#include "GInterface.h"
#include "IFflorian0Guide.h"
#include "IFNotify.h"
#include "IFChatViewer.h"
#include "IFNotify.h"
#include "GlobalDataManager.h"
#include "IFTaiXiuIcon.h"
#include "IFNapThe.h"
#include "IFDANGKYEVENT.h"
#include "IFDailyLoginIcon.h"
#include <BSLib/Debug.h>
#include <remodel/MemberFunctionHook.h>
#include "IFflorian0Runtime.h"
#include "IFflorian0.h"
#include "IFSTChestIcon.h"
#include "IFSTEventTime.h"
#include "IFReBotIcon.h"
#include "CPSMission.h"
#include "IFSTStremSettingIcon.h"

HOOK_ORIGINAL_MEMBER(0x0079D5B0, &CGInterface::ToggleActionWnd);
void CGInterface::ToggleActionWnd() {
    // If MainPopup is visible and page 'action' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_ACTION)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    } else {
        m_mainPopup->ShowGWnd(true);
        m_mainPopup->ShowSubPage(GDR_ACTION);
        FUN_0079a7e0(m_mainPopup);
    }
}
HOOK_ORIGINAL_MEMBER(0x0079B0B0, &CGInterface::ToggleApprenticeshipWnd);
void CGInterface::ToggleApprenticeshipWnd() {
    // If MainPopup is visible and page 'apprenticeship' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_APPRENTICESHIP)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
        g_CGlobalDataManager->FUN_008cbac0(GDR_APPRENTICESHIP);
    } else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetApprenticeShip()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_APPRENTICESHIP);
        }
        FUN_0079a7e0(m_mainPopup);
        g_CGlobalDataManager->FUN_008cbac0(GDR_APPRENTICESHIP);
    }
}
HOOK_ORIGINAL_MEMBER(0x0079ACE0, &CGInterface::TogglePlayerInfoWnd);
void CGInterface::TogglePlayerInfoWnd() {
    // If MainPopup is visible and page 'playerinfo' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_PLAYERINFO)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    } else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetPlayerInfo()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_PLAYERINFO);
        }
        FUN_0079a7e0(m_mainPopup);
    }
}

void CGInterface::RenderToggle_GDR_GAMEGUIDE() {
    return reinterpret_cast<void (__thiscall *)(void *)>(0x0079F690)(this);
}
HOOK_ORIGINAL_MEMBER(0x0079B020, &CGInterface::ToggleInventoryWnd);
void CGInterface::ToggleInventoryWnd() {
    // If MainPopup is visible and page 'inventory' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_INVENTORY)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    } else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetInventory()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_INVENTORY);
        }
        FUN_0079a7e0(m_mainPopup);
    }
}
HOOK_ORIGINAL_MEMBER(0x0079ad70, &CGInterface::ToggleEquipmentWnd);
void CGInterface::ToggleEquipmentWnd() {
    // If MainPopup is visible and page 'equipment' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_INVENTORY)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    } else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetEquipment()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_INVENTORY);
        }
        FUN_0079a7e0(m_mainPopup);
    }
}
HOOK_ORIGINAL_MEMBER(0x0079AE90, &CGInterface::TogglePartyWnd);
void CGInterface::TogglePartyWnd() {
    // If MainPopup is visible and page 'party' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_PARTY)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
        g_CGlobalDataManager->FUN_008cbac0(GDR_PARTY);
    } else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetParty()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_PARTY);
        }
        FUN_0079a7e0(m_mainPopup);
        g_CGlobalDataManager->FUN_008cbac0(GDR_PARTY);
    }
}
HOOK_ORIGINAL_MEMBER(0x0079AE00, &CGInterface::ToggleSkillWnd);
void CGInterface::ToggleSkillWnd() {
    // If MainPopup is visible and page 'skill' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_SKILL)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    } else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetSkill()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_SKILL);
        }
        FUN_0079a7e0(m_mainPopup);
    }
}
HOOK_ORIGINAL_MEMBER(0x0079af20, &CGInterface::ShowInventoryWnd);
void CGInterface::ShowInventoryWnd() {
    m_mainPopup->ShowGWnd(true);
    if (!m_mainPopup->GetInventory()->IsVisible()) {
        m_mainPopup->ShowSubPage(GDR_INVENTORY);
    }
    FUN_0079a7e0(m_mainPopup);
}

HOOK_ORIGINAL_MEMBER(0x0079af70, &CGInterface::ShowApprenticeshipWnd);
void CGInterface::ShowApprenticeshipWnd() {
    m_mainPopup->ShowGWnd(true);
    if (!m_mainPopup->GetApprenticeShip()->IsVisible()) {
        m_mainPopup->ShowSubPage(GDR_APPRENTICESHIP);
    }
    FUN_0079a7e0(m_mainPopup);
}
HOOK_ORIGINAL_MEMBER(0x00798D00, &CGInterface::GetMainPopup);
void CGInterface::ToggleMainPopup() {
    m_mainPopup->ShowGWnd(!m_mainPopup->IsVisible());
    FUN_0079a7e0(m_mainPopup);
}

void CGInterface::RenderToggle_WORLDMAP_GUIDE() {
    return reinterpret_cast<void (__thiscall *)(void *)>(0x0079ABE0)(this);
}

void CGInterface::Render_GDR_AUTO_POTION(bool visible) {
    return reinterpret_cast<void (__thiscall *)(void *, bool)>(0x0079C750)(this, visible);
}

void CGInterface::CreateFlorian0Event() {
    CGWnd *guide = GetAlarmManager()->GetGuide(GUIDE_FLORIAN0);
}

CAlramGuideMgrWnd *CGInterface::GetAlarmManager() {
    return m_IRM.GetResObj<CAlramGuideMgrWnd>(GDR_ALRAM_GUIDE_MGR_WND, 1);
}

bool CGInterface::OnCreateIMPL(long ln) {

    BeforeOnCreate();

    bool b = reinterpret_cast<bool (__thiscall *)(CGInterface *, long)>(0x0078c910)(this, ln);

    AfterOnCreate();

    return b;
}

void CGInterface::BeforeOnCreate() {

}

void CGInterface::AfterOnCreate() {
    CreateFlorian0Event(); //menu

    if(CPSMission::Icon_TaiXiu)
    {
        CreateFlorian0Event1(); //taixiu
    }
    if(CPSMission::Icon_Chest)
    {
        CreateFlorian0Event5(); //chest
    }
    if(CPSMission::Icon_DailyLogin)
    {
        CreateFlorian0Event4(); //dailylogin
    }
    if(CPSMission::Icon_Event)
    {
        CreateFlorian0Event3(); //dangky event
    }

    if(CPSMission::Icon_ExtralFeature)
    {
        CreateFlorian0Event2(); //napthe
    }
    if(CPSMission::Icon_ReBot)
    {
        CreateFlorian0Event6(); //rebot
    }
    if(CPSMission::Icon_LiveStream)
    {
        CreateFlorian0Event7(); //streamsetting
    }

    BS_INFO("Well this worked\n");

    CIFNotify *notify = m_IRM.GetResObj<CIFNotify>(GDR_MY_NOTIFY, 1);
    notify->SetEdgeTextures(
            "interface\\ifcommon\\cop_notice_edge2.ddj",
            "interface\\ifcommon\\cop_notice_edge.ddj",
            "interface\\ifcommon\\cop_notice_edge2.ddj",
            "interface\\ifcommon\\cop_notice_edge.ddj"
    );

    notify->SetCornerTextures("interface\\ifcommon\\cop_notice_corner.ddj");
    notify->SetYPosition(190);
    notify->SetColor(255, 99, 71);

    CIFNotify *notify1 = m_IRM.GetResObj<CIFNotify>(GDR_TIM_NOTIFY, 1);
    notify1->SetEdgeTextures(
            "interface\\ifcommon\\coq_notice_edge2.ddj",
            "interface\\ifcommon\\coq_notice_edge.ddj",
            "interface\\ifcommon\\coq_notice_edge2.ddj",
            "interface\\ifcommon\\coq_notice_edge.ddj"
    );

    notify1->SetCornerTextures("interface\\ifcommon\\coq_notice_edge2.ddj");
    notify1->SetYPosition(70);
    notify1->SetColor(75, 0, 130);

    RECT ChestRect = { 0,0,600,370 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChest), ChestRect, 19576, 0);

    RECT MainMenuRect = {0, 0, 210, 580};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFflorian0Runtime), MainMenuRect, 19577, 0);

    RECT GrantNameRect = {0,0,320,135};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTChangeGrantName), GrantNameRect, 19578, 0);

    RECT DPSRect = {0,0,187,210};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTDpsMetter), DPSRect, 19579, 0);

    RECT CharLockRect = {0,0,210,280};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCharLock), CharLockRect, 19575, 0);

    RECT UniqueHistoryRect = { 0,0,500,370 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistory), UniqueHistoryRect, 19580, 0);

    RECT SwitchRect = { 0,0,300,300 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSwitchTitle), SwitchRect, 19581, 0);

    RECT CustomTitleRect = { 0,0,540,270 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCustomTitle), CustomTitleRect, 19582, 0);

    RECT ConfirmRect = {0,0,370,140};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTConfirm), ConfirmRect, 19583, 0);

    RECT CustomRankRect = { 0,0,405,415 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCustomRank), CustomRankRect, 19584, 0);

    RECT EventRect = { 0,0,395,375 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTime), EventRect, 19585, 0);

    RECT SurRect = {0,0,187,163};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTSurvivalKills), SurRect, 19586, 0);

    RECT PointRect = {0,0,510,332};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPoints), PointRect, 19587, 0);

    RECT EventRegRect = {0,0,270,330};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventRegister), EventRegRect, 19588, 0);

    RECT EventXoSoRect = {0,0,600,465};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBac), EventXoSoRect, 19589, 0);


    RECT EventXoSoLSRect = {0,0,530,370};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSu), EventXoSoLSRect, 19591, 0);

    RECT EventLotteryRect = {0,0,284,336};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTLotteryEvent), EventLotteryRect, 19592, 0);

    RECT PvpChallengeRect = {0,0,320,185};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPvpChallenge), PvpChallengeRect, 19593, 0);

    RECT PvpChallengeAnswerRect = {0,0,320,185};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPvpChallengeAnswer), PvpChallengeAnswerRect, 19594, 0);

    RECT ReverseScrollPlusRect = { 0,0,500,350 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlus), ReverseScrollPlusRect, 19595, 0);

    RECT FTWRect = { 0,0,187,165 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFTWCounter), FTWRect, 19596, 0);

    RECT CustomNPCRect = { 0,0,405,415 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPC), CustomNPCRect, 19597, 0);

   // RECT CharInfoRect = { 0,0,408,425 };
    RECT CharInfoRect = { 0,0,205,370 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCharItemInfo), CharInfoRect, 19598, 0);

    RECT ExtraFeatureRect = { 0,0,448,475 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTExtraFeature), ExtraFeatureRect, 19599, 0);

    RECT PetFilterRect =  { 0,0,405,415 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPetFilter), PetFilterRect, 19600, 0);

    RECT StreamSettingRect =  { 0,0,360,300 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTStreamSetting), StreamSettingRect, 19601, 0);

    RECT ConfirmUrlRect = {0,0,370,140};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTConfirmUrl), ConfirmUrlRect, 19602, 0);

    RECT CIFSTMacroRect = {0,0,360,244};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacro), CIFSTMacroRect, 19603, 0);

    RECT CIFSTMacroAutoHuntRect = { 0,0,570,415 };
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoHunt), CIFSTMacroAutoHuntRect, 19604, 0);

    RECT PartyMatchMemberViewerGUIRect = {0,0,200,236};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewer), PartyMatchMemberViewerGUIRect, 19605, 0);

    RECT QuickSlotOptionRect = {0,0,290,223};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFExtQuickSecondSlotOption), QuickSlotOptionRect, 19606, 0);

    RECT CIFSTEffectRect = {0,0,300,120};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEffect), CIFSTEffectRect, 19607, 0);

    RECT CIFSTBloodEffectRect = {300,200,400,300};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTBloodEffect), CIFSTBloodEffectRect, 19608, 0);

    RECT CIFSTBattleRoyaleKillCountRect = {0,0,140,140};
    CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTBattleRoyaleKillCount), CIFSTBattleRoyaleKillCountRect, 19609, 0);
}

void CGInterface::ShowMessage_Orange(const std::n_wstring &msg) {
    CIFNotify* notify = m_IRM.GetResObj<CIFNotify>(GDR_MY_NOTIFY, 1);
    notify->BringToFront();
    notify->ShowMessage(msg);

}
void CGInterface::ShowMessage_Purble(const std::n_wstring &msg) {
    CIFNotify* notify = m_IRM.GetResObj<CIFNotify>(GDR_TIM_NOTIFY, 1);
    notify->BringToFront();
    notify->ShowMessage(msg);

}
void CGInterface::ShowMessage_Quest(const std::n_wstring &msg) {
    CIFNotify *notify = m_IRM.GetResObj<CIFNotify>(GDR_UPDATE_QUEST_INFO, 1);
    notify->ShowMessage(msg);
    //notify-> SetColor(102,102,255);
    //notify->SetYPosition(200);
}

void CGInterface::ShowMessage_Notice(const std::n_wstring &msg) {
    CIFNotify *notify = m_IRM.GetResObj<CIFNotify>(GDR_NOTICE, 1);
    notify->ShowMessage(msg);
   // notify-> SetColor(255,0,255);
   // notify->SetYPosition(300);
}
void CGInterface::ShowLogMessage(int color, const wchar_t* msg) {
    GetSystemMessageView()->WriteMessage(0xff, color, msg, 0, 1);
}
void CGInterface::ShowMessage_Warning(const std::n_wstring &msg) {
    CIFNotify *notify = m_IRM.GetResObj<CIFNotify>(GDR_WARNING_WND, 1);
    notify->ShowMessage(msg);
  //  notify-> SetColor(0,204,255);
   // notify->SetYPosition(400);
}

void CGInterface::CreateFlorian0Event1() {
    CGWnd *guide = GetAlarmManager()->GetGuide(GUIDE_FLORIAN01);
}
void CGInterface::CreateFlorian0Event2() {
    CGWnd *guide = GetAlarmManager()->GetGuide(GUIDE_FLORIAN03);
}
void CGInterface::CreateFlorian0Event3() {
    CGWnd *guide = GetAlarmManager()->GetGuide(GUIDE_FLORIAN04);
}
void CGInterface::CreateFlorian0Event4() {
    CGWnd *guide = GetAlarmManager()->GetGuide(GUIDE_FLORIAN05);
}
void CGInterface::CreateFlorian0Event5() {
    CGWnd *guide = GetAlarmManager()->GetGuide(GUIDE_FLORIAN06);
}
void CGInterface::CreateFlorian0Event6() {
    CGWnd *guide = GetAlarmManager()->GetGuide(GUIDE_FLORIAN07);
}
void CGInterface::CreateFlorian0Event7() {
    CGWnd *guide = GetAlarmManager()->GetGuide(GUIDE_FLORIAN08);
}
int CGInterface::Get_SelectedObjectId() {
    return this->m_selectedObjectId;
}

CIFTimerWnd *CGInterface::Get_TimerWindow() {
    return this->m_timerWindow;
}

CIFQuickStateHalfWnd *CGInterface::Get_QuickStateHalfWnd() {
    return this->N00002637;
}

CIF_NPCWindow *CGInterface::Get_GDR_NPCWINDOW() {
    return (CIF_NPCWindow *) this->m_IRM.GetResObj(GDR_NPCWINDOW, 1);
}

CIFMainPopup *CGInterface::GetMainPopup() {
    return (CIFMainPopup *) this->m_IRM.GetResObj(GDR_MAINPOPUP, 1);
}

CIFStorageRoom *CGInterface::Get_GDR_STORAGEROOM() {
    return (CIFStorageRoom *) this->m_IRM.GetResObj(GDR_STORAGEROOM, 1);
}

CIFStorageRoom *CGInterface::Get_GDR_GUILDSTORAGEROOM() {
    return (CIFStorageRoom *) this->m_IRM.GetResObj(GDR_GUILDSTORAGEROOM, 1);
}
CIFCOS *CGInterface::Get_Cos_Window() {
    return (CIFCOS *) this->m_IRM.GetResObj(GDR_COSWINDOW, 1);
}
void CGInterface::WriteErrorMessage(byte errorType, unsigned __int16 errorCode, int colorARGB, int a5, int a6) {
    return reinterpret_cast<
            void (__thiscall *)(void *, byte, unsigned __int16, int, int, int)
            >(0x00778190)(this, errorType, errorCode, colorARGB, a5, a6);
}

void CGInterface::WriteSystemMessage(eLogType level, const wchar_t *str) {
    reinterpret_cast<void (__thiscall *)(CGInterface *, eLogType, const wchar_t *)>(0x007781B0)(this, level, str);
}

void CGInterface::sub_787C10(SChatMetaData &meta) {
    reinterpret_cast<void (__thiscall *)(CGInterface *, SChatMetaData *)>(0x787C10)(this, &meta);
}

int CGInterface::TryParseChatCommands(const wchar_t *text, RECT &r, std::vector<void *> &v) {
    return reinterpret_cast<
            int (__thiscall *)(CGInterface *, const wchar_t *, RECT *, std::vector<void *> *)
            >(0x0078BEA0)(this, text, &r, &v);
}

void CGInterface::ToggleQuestNew() {
    reinterpret_cast<void (__thiscall *)(CGInterface *)>(0x007990e0)(this);
}

CNIFCommunityWnd *CGInterface::GetCommunityWnd() {
    return reinterpret_cast<CNIFCommunityWnd *(__thiscall *)(CGInterface *)>(0x007994f0)(this);
}

void CGInterface::FUN_00777c30(ChatType type, const wchar_t *message, D3DCOLOR color, int a5) {
    CIFChatViewer *chatViewer = m_IRM.GetResObj<CIFChatViewer>(GDR_CHATVIEWER, 1);
    chatViewer->FUN_007aca30(type, color, message, 0, a5);
}

void CGInterface::FUN_00778a10(int a2, const wchar_t *message, D3DCOLOR color) {
    reinterpret_cast<
            void (__thiscall *)(CGInterface *, int, const wchar_t *, D3DCOLOR)
            >(0x00778a10)(this, a2, message, color);
}

void CGInterface::FUN_00777cf0(const std::n_wstring &recipient) {
    reinterpret_cast<void (__thiscall *)(CGInterface *, const std::n_wstring *)>(0x00777cf0)(this, &recipient);
}

CIFSystemMessage *CGInterface::GetSystemMessageView() {
    return m_IRM.GetResObj<CIFSystemMessage>(GDR_SYSTEM_MESSAGE_VIEW, 1);
}

void CGInterface::FUN_0079a7e0(CGWndBase *pGWnd) const {
    reinterpret_cast<void (__thiscall *)(const CGInterface *, CGWndBase *)>(0x0079a7e0)(this, pGWnd);
}

CGInterface* CGInterface::Get(void)
{
    return *reinterpret_cast<CGInterface**>(0x0110F80C);
}
void CGInterface::ShowPinkNotify(std::wstring msg)
{
    reinterpret_cast<void(__thiscall *)(CGInterface*, std::wstring*)>(0x00777BF0)(this, &msg);
}

void CGInterface::ShowBlueNotify(std::wstring msg)
{
    reinterpret_cast<void(__thiscall *)(CGInterface*, std::wstring*)>(0x0077B580)(this, &msg);
}

void CGInterface::ShowGreenNotify(std::wstring msg)
{
    reinterpret_cast<void(__thiscall *)(CGInterface*, std::wstring*)>(0x0077B5B0)(this, &msg);
}

void CGInterface::ShowPinkNotify(std::wstring* msg)
{
    reinterpret_cast<void(__thiscall *)(CGInterface*, std::wstring*)>(0x00777BF0)(this, msg);
}

void CGInterface::ShowBlueNotify(std::wstring* msg)
{
    reinterpret_cast<void(__thiscall *)(CGInterface*, std::wstring*)>(0x0077B580)(this, msg);
}

void CGInterface::ShowGreenNotify(std::wstring* msg)
{
    reinterpret_cast<void(__thiscall *)(CGInterface*, std::wstring*)>(0x0077B5B0)(this, msg);
}


void CGInterface::OnNotifyAction(int a1, unsigned short action, int color, int a4, int a5)
{
    reinterpret_cast<void(__thiscall*)(CGInterface*, int, unsigned short, int, int, int)>(0x00778190)(this, a1, action, color, a4, a5);
}

int CGInterface::sub_799970(void)
{
    return reinterpret_cast<int(__thiscall*)(CGInterface*)>(0x00799970)(this);
}
void CGInterface::HandleSystemMessages(int type, const wchar_t* msg)
{
    reinterpret_cast<void(__thiscall*)(CGInterface*, int, const wchar_t*)>(0x007781B0)(this, type, msg);
}
void CGInterface::FUN_00778650(CObj* object) {
    reinterpret_cast<void(__thiscall*)(CGInterface*, CObj*)>(0x00778650)(this, object);
}
void CGInterface::SwitchToStallNetwork(bool Enabled)
{
    return reinterpret_cast<void(__thiscall*)(CGInterface*, bool)>(0x00799020)(this, Enabled);
}
void CGInterface::SwitchToItemMall()
{
    reinterpret_cast<void(__thiscall*)(CGInterface*)>(0x007995e0)(this);
}
CIFWholeChat *CGInterface::GetWholeChat() {
    return m_IRM.GetResObj<CIFWholeChat>(GDR_WHOLE_CHAT, 1);
}
void CGInterface::FUN_0079b8a0(undefined1 a1, undefined4 a2) {
    reinterpret_cast<void(__thiscall *)(CGInterface *, undefined1, undefined4)>(0x0079b8a0)(this, a1, a2);
}

HOOK_ORIGINAL_MEMBER(0x007901c0, &CGInterface::WriteGlobalMessage)
void CGInterface::WriteGlobalMessage(unsigned char nSlot, std::n_wstring message) {
    CIFMainPopup *popup = GetMainPopup();
    CIFInventory *inventory = popup->GetInventory();

    CSOItem *item = inventory->GetItemBySlot(nSlot);

    if (item->field_28 == 0) {
        return;
    }

    const CItemData *pItemData = item->GetItemData();

    if (pItemData->TID==0x29ED || pItemData->TID==0x29EC) {
        NEWMSG(0x704c)

            pReq << static_cast<unsigned char>(nSlot + 13u) << pItemData->TID << acp_encode(message);

        SENDMSG()
    }
}
void CGInterface::RequestStatIncrement(undefined4 a1, undefined4 a2, undefined4 a3, undefined4 a4) {
    if (a1 == 0x4b) {
        if (a2 == 1) {
            NEWMSG(0x7050)
            SENDMSG()
        } else if (a2 == 2) {
            NEWMSG(0x7051)
            SENDMSG()
        }
    }
}
void CGInterface::FUN_00777a70(undefined4 param_1, undefined4 param_2) {
    reinterpret_cast<void(__thiscall *)(CGInterface *, undefined4, undefined4)>(0x00777a70)(this, param_1, param_2);
}
CNIFUnderMenuBar *CGInterface::GetUnderMenuBar() {
    return reinterpret_cast<CNIFUnderMenuBar * (__thiscall *)(CGInterface *)>(0x007994e0)(this);
}

CIFExtQuickSlot *CGInterface::GetExtQuickSlot() {
    return m_IRM.GetResObj<CIFExtQuickSlot>(GDR_EXT_QUICK_SLOT, 1);
}
CIFPetMiniInfo *CGInterface::GetPetMiniInfoWnd() {
    return m_IRM.GetResObj<CIFPetMiniInfo>(GDR_PET_MINI_INFO, 1);
}
CIFExtQuickSlotSecond *CGInterface::GetExtQuickSecondSlot() {
    return m_IRM.GetResObj<CIFExtQuickSlotSecond>(GDR_EXT_QUICK_SECOND_SLOT, 1);
}

CIFflorian0Runtime *CGInterface::GetMainMenu() {
    return GetControlFromList<CIFflorian0Runtime>(19577);;
}
CIFPlayerChest *CGInterface::GetChestGUI() {
    return GetControlFromList<CIFPlayerChest>(19576);;
}
CIFSTChangeGrantName *CGInterface::GetChangeGrantNameGUI() {
    return GetControlFromList<CIFSTChangeGrantName>(19578);;
}
CIFSTDpsMetter *CGInterface::GetDpsMetterGUI() {
    return GetControlFromList<CIFSTDpsMetter>(19579);;
}
CIFSTCharLock *CGInterface::GetCharLockGUI() {
    return GetControlFromList<CIFSTCharLock>(19575);;
}
CIFSTUniqueHistory *CGInterface::GetUniqueHistoryGUI() {
    return GetControlFromList<CIFSTUniqueHistory>(19580);;
}
CIFSwitchTitle *CGInterface::GetSwitchTitleGUI() {
    return GetControlFromList<CIFSwitchTitle>(19581);;
}
CIFCustomTitle *CGInterface::GetCustomTitleGUI() {
    return GetControlFromList<CIFCustomTitle>(19582);;
}
CIFSTConfirm *CGInterface::GetConfirmGUI() {
    return GetControlFromList<CIFSTConfirm>(19583);;
}
CIFCustomRank *CGInterface::GetCustomRankGUI() {
    return GetControlFromList<CIFCustomRank>(19584);;
}
CIFEventTime *CGInterface::GetEventTimeGUI() {
    return GetControlFromList<CIFEventTime>(19585);;
}
CIFSTSurvivalKills *CGInterface::GetSurvivalKillGUI() {
    return GetControlFromList<CIFSTSurvivalKills>(19586);;
}
CIFSTTotalPoints *CGInterface::GetTotalPointsGUI() {
    return GetControlFromList<CIFSTTotalPoints>(19587);;
}
CIFSTEventRegister *CGInterface::GetEventRegisterGUI() {
    return GetControlFromList<CIFSTEventRegister>(19588);;
}
CIFSTEventXoSoMienBac *CGInterface::GetEventXoSoGUI() {
    return GetControlFromList<CIFSTEventXoSoMienBac>(19589);;
}
CIFSTEventXoSoMienBacLichSu *CGInterface::GetEventXoSoLichSuGUI() {
    return GetControlFromList<CIFSTEventXoSoMienBacLichSu>(19591);;
}
CIFSTLotteryEvent *CGInterface::GetEventLotteryGUI() {
    return GetControlFromList<CIFSTLotteryEvent>(19592);;
}
CIFSTPvpChallenge *CGInterface::GetPvpChallengeGUI() {
    return GetControlFromList<CIFSTPvpChallenge>(19593);;
}
CIFSTPvpChallengeAnswer *CGInterface::GetPvpChallengeAnswerGUI() {
    return GetControlFromList<CIFSTPvpChallengeAnswer>(19594);;
}
CIFSTReverseScrollPlus *CGInterface::GetCIFSTReverseScrollPlusGUI() {
    return GetControlFromList<CIFSTReverseScrollPlus>(19595);;
}
CIFFTWCounter *CGInterface::GetFtwCunterGUI() {
    return GetControlFromList<CIFFTWCounter>(19596);;
}
CIFSTCustomNPC *CGInterface::GetCustomNPCGUI() {
    return GetControlFromList<CIFSTCustomNPC>(19597);;
}
CIFSTCharItemInfo *CGInterface::GetCharInfoGUI() {
    return GetControlFromList<CIFSTCharItemInfo>(19598);;
}
CIFSTExtraFeature *CGInterface::GetExtraFeatureGUI() {
    return GetControlFromList<CIFSTExtraFeature>(19599);;
}
CIFSTPetFilter *CGInterface::GetPetFilterGUI() {
    return GetControlFromList<CIFSTPetFilter>(19600);;
}
CIFSTStreamSetting *CGInterface::GetStreamSettingGUI() {
    return GetControlFromList<CIFSTStreamSetting>(19601);;
}
CIFSTConfirmUrl *CGInterface::GetCIFSTConfirmUrlGUI() {
    return GetControlFromList<CIFSTConfirmUrl>(19602);;
}
CIFSTMacro *CGInterface::GetCIFSTMacroGUI() {
    return GetControlFromList<CIFSTMacro>(19603);;
}
CIFSTMacroAutoHunt *CGInterface::GetCIFSTMacroAutoHuntGUI() {
    return GetControlFromList<CIFSTMacroAutoHunt>(19604);;
}
CIFSTPartyMatchMemberViewer *CGInterface::GetCIFSTPartyMatchMemberViewerGUI() {
    return GetControlFromList<CIFSTPartyMatchMemberViewer>(19605);;
}
CIFExtQuickSecondSlotOption *CGInterface::GetCIFExtQuickSecondSlotOptionGUI() {
    return GetControlFromList<CIFExtQuickSecondSlotOption>(19606);;
}
CIFSTEffect *CGInterface::GetCIFSTEffectGUI() {
    return GetControlFromList<CIFSTEffect>(19607);;
}
CIFSTBloodEffect *CGInterface::GetCIFSTBloodEffectGUI() {
    return GetControlFromList<CIFSTBloodEffect>(19608);;
}
CIFSTBattleRoyaleKillCount *CGInterface::GetCIFSTBattleRoyaleKillCountGUI() {
    return GetControlFromList<CIFSTBattleRoyaleKillCount>(19609);;
}
CNIFWorldMap *CGInterface::GetCNIFWorldMap() {
    return reinterpret_cast<CNIFWorldMap * (__thiscall *)(CGInterface *)>(0x00799920)(this);
}
int CGInterface::OnKeyDown(int keycode, int a3, int a4)
{
   // if(g_pCICPlayer->m_zerkPoint != 5)
    /*{
        switch (keycode) {
            case 0x4F:
                m_IRM.GetResObj(5105,1)->ShowGWnd(true);
                break;
        }
    }*/
    return reinterpret_cast<int (__thiscall *)(CGInterface *, int, int, int)>(0x00780610)(this, keycode, a3, a4);
}

void CGInterface::OnEscapePressed()
{
    if(m_IRM.GetResObj(5105,1) && m_IRM.GetResObj(5105,1)->IsVisible())
    {
        m_IRM.GetResObj(5105,1)->ShowGWnd(false);
        return;
    }
    if(m_IRM.GetResObj(5096,1) && m_IRM.GetResObj(5096,1)->IsVisible())
    {
        m_IRM.GetResObj(5096,1)->ShowGWnd(false);
        return;
    }
    if(m_IRM.GetResObj(5092,1) && m_IRM.GetResObj(5092,1)->IsVisible())
    {
        m_IRM.GetResObj(5092,1)->ShowGWnd(false);
        return;
    }

    if(GetStreamSettingGUI()->IsVisible())
    {
        GetStreamSettingGUI()->OnCloseWnd();
        return;
    }
    if(GetChestGUI()->IsVisible())
    {
        GetChestGUI()->OnCloseWnd();
        return;
    }
    if(GetCIFSTMacroGUI()->IsVisible())
    {
        GetCIFSTMacroGUI()->OnCloseWnd();
        return;
    }
    if(GetCIFSTMacroAutoHuntGUI()->IsVisible())
    {
        GetCIFSTMacroAutoHuntGUI()->OnCloseWnd();
        return;
    }
    if(GetChangeGrantNameGUI()->IsVisible())
    {
        GetChangeGrantNameGUI()->OnCloseWnd();
        return;
    }
    if(GetCharLockGUI()->IsVisible())
    {
        GetCharLockGUI()->OnCloseWnd();
        return;
    }
    if(GetUniqueHistoryGUI()->IsVisible())
    {
        GetUniqueHistoryGUI()->OnCloseWnd();
        return;
    }
    if(GetSwitchTitleGUI()->IsVisible())
    {
        GetSwitchTitleGUI()->OnCloseWnd();
        return;
    }
    if(GetCustomTitleGUI()->IsVisible())
    {
        GetCustomTitleGUI()->OnCloseWnd();
        return;
    }
    if(GetConfirmGUI()->IsVisible())
    {
        GetConfirmGUI()->OnCloseWnd();
        return;
    }
    if(GetCustomRankGUI()->IsVisible())
    {
        GetCustomRankGUI()->OnCloseWnd();
        return;
    }
    if(GetEventTimeGUI()->IsVisible())
    {
        GetEventTimeGUI()->OnCloseWnd();
        return;
    }
    if(GetSurvivalKillGUI()->IsVisible())
    {
        GetSurvivalKillGUI()->OnCloseWnd();
        return;
    }
    if(GetTotalPointsGUI()->IsVisible())
    {
        GetTotalPointsGUI()->OnCloseWnd();
        return;
    }
    if(GetEventRegisterGUI()->IsVisible())
    {
        GetEventRegisterGUI()->OnCloseWnd();
        return;
    }
    if(GetEventXoSoGUI()->IsVisible())
    {
        GetEventXoSoGUI()->OnCloseWnd();
        return;
    }
    if(GetEventXoSoLichSuGUI()->IsVisible())
    {
        GetEventXoSoLichSuGUI()->OnCloseWnd();
        return;
    }
    if(GetEventLotteryGUI()->IsVisible())
    {
        GetEventLotteryGUI()->OnCloseWnd();
        return;
    }
    if(GetPvpChallengeGUI()->IsVisible())
    {
        GetPvpChallengeGUI()->OnCloseWnd();
        return;
    }
    if(GetPvpChallengeAnswerGUI()->IsVisible())
    {
        GetPvpChallengeAnswerGUI()->OnCloseWnd();
        return;
    }
    if(GetCIFSTReverseScrollPlusGUI()->IsVisible())
    {
        GetCIFSTReverseScrollPlusGUI()->OnCloseWnd();
        return;
    }
    if(GetCustomNPCGUI()->IsVisible())
    {
        GetCustomNPCGUI()->OnCloseWnd();
        return;
    }
    if(GetCharInfoGUI()->IsVisible())
    {
        GetCharInfoGUI()->OnCloseWnd();
        return;
    }
    if(GetExtraFeatureGUI()->IsVisible())
    {
        GetExtraFeatureGUI()->OnCloseWnd();
        return;
    }
    if(GetMainMenu()->IsVisible())
    {
        GetMainMenu()->OnCloseWnd();
        return;
    }

    reinterpret_cast<void (__thiscall *)(CGInterface *)>(0x0079d620)(this);
}