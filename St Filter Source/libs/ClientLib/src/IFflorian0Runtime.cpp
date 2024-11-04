#include "IFflorian0Runtime.h"
#include "IFNormalTile.h"
#include "ICPlayer.h"
#include "Game.h"
#include "IFflorian0Guide.h"
#include "IFChatViewer.h"
#include <ctime>
#include <SilkRoadWeb/SilkroadWeb.h>
#include "GInterface.h"
#include "CPSMission.h"
#include "GlobalDataManager.h"
#include "BSLib/multibyte.h"
#include "IFMessageBox.h"
#include "Rebot.h"

#define GDR_FLORIAN0_RT_LABEL 10
#define GDR_FLORIAN0_RT_BTN 11
#define GDR_FLORIAN0_RT_LABEL_TIME 13
#define GDR_FLORIAN0_RT_MAIN_FRAME 20
#define GDR_FLORIAN0_RT_MAIN_FRAME1 31
#define GDR_FLORIAN0_RT_MAIN_FRAME2 32
#define GDR_FLORIAN0_RT_MAIN_FRAME3 33
#define GDR_FLORIAN0_RT_BTN_DISCORD 34
#define GDR_FLORIAN0_RT_BTN_FACEBOOK 35
#define GDR_FLORIAN0_RT_BTN_WEB 36
#define GDR_FLORIAN0_RT_CHARLOCK 37
#define GDR_FLORIAN0_RT_CHARNAME 38
#define GDR_FLORIAN0_RT_BTN1 21
#define GDR_FLORIAN0_RT_BTN2 23
#define GDR_FLORIAN0_RT_BTN3 24
#define GDR_FLORIAN0_RT_BTN4 25
#define GDR_FLORIAN0_RT_BTN5 26
#define GDR_FLORIAN0_RT_BTN6 27
#define GDR_FLORIAN0_RT_BTN7 28
#define GDR_FLORIAN0_RT_BTN8 29

GFX_IMPLEMENT_DYNCREATE(CIFflorian0Runtime, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFflorian0Runtime, CIFMainFrame)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN, &On_BtnClick_ChangeGrantName)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN1, &On_BtnClickCharLock)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN2, &On_BtnClick)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN3, &On_BtnClick_Title)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN4, &On_BtnClick_New)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN5, &On_BtnClick_EventTimer)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN6, &On_BtnClick_Unknow)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN7, &On_BtnClick_SendPVP)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN8, &On_BtnClick_Test)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN_DISCORD, &On_BtnClick_Discord)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN_FACEBOOK, &On_BtnClick_Facebook)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN_WEB, &On_BtnClick_Web)
GFX_END_MESSAGE_MAP()


CIFflorian0Runtime::CIFflorian0Runtime() :
        m_custom_label(NULL) {

}

bool CIFflorian0Runtime::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);

    // Set own title


    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);

    wnd_size sz = this->GetSize();
    //RECT rect_frame = { 17,45,178,437 };
    // RECT rect_frame = {17, 45, sz.width - 45, sz.height - 15};
    RECT rect_frame = { 17,45,179,74 };

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame,
                                                  GDR_FLORIAN0_RT_MAIN_FRAME,
                                                  1);
    //frame->TB_Func_13("interface\\messagebox\\msgbox_window_", 1, 0);
    frame->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 0);

    RECT rect_background = {rect_frame.left + 10,
                            rect_frame.top + 10,
                            rect_frame.right - 20,
                            rect_frame.bottom - 20};

    CIFNormalTile *tile = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background,
                                                           GDR_FLORIAN0_RT_MAIN_FRAME,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);

    ////char_icon_frame
    RECT rect_frame_char_icon = { 34,64,42,42 };

    CIFFrame *frame_char_icon = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                            rect_frame_char_icon,
                                                  GDR_FLORIAN0_RT_MAIN_FRAME,
                                                  1);
    //frame_char_icon->TB_Func_13("interface\\messagebox\\msgbox_itemwindow.ddj", 1, 0);
    frame_char_icon->TB_Func_13("interface\\frame\\frame_make_", 1, 0);

    RECT rect_background_char_icon = {rect_frame_char_icon.left + 3,
                                      rect_frame_char_icon.top + 3,
                                      rect_frame_char_icon.right - 6,
                                      rect_frame_char_icon.bottom - 6};

    CIFNormalTile *tile_char_icon = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                                     rect_background_char_icon,
                                                           GDR_FLORIAN0_RT_MAIN_FRAME,
                                                           1);
    tile_char_icon->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_d.ddj", 1, 0);

    RECT rect_m_char_icon = {rect_frame_char_icon.left + 3,
                                      rect_frame_char_icon.top + 3,
                                      rect_frame_char_icon.right - 6,
                                      rect_frame_char_icon.bottom - 6};
    m_char_icon = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                      rect_m_char_icon,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);
    ///////// charname frame
    RECT rect_m_char_name = { 88,85,94,18 };
    m_char_name = (CIFStatic *) CGWnd::CreateInstance(this,
                                                      GFX_RUNTIME_CLASS(CIFStatic),
                                                      rect_m_char_name,
                                                      GDR_FLORIAN0_RT_CHARNAME,
                                                      1);
    RECT rect_m_frame_label = { 45,12,118,15 };
    m_frame_label = (CIFStatic *) CGWnd::CreateInstance(this,
                                                      GFX_RUNTIME_CLASS(CIFStatic),
                                                        rect_m_frame_label,
                                                      GDR_FLORIAN0_RT_CHARNAME,
                                                      1);
    ////char_lock_frame
    RECT rect_frame_char_lock = { 83,60,99,24 };

    CIFFrame *frame_char_lock = (CIFFrame *) CreateInstance(this,
                                                            GFX_RUNTIME_CLASS(CIFFrame),
                                                            rect_frame_char_lock,
                                                            GDR_FLORIAN0_RT_MAIN_FRAME,
                                                            1);
    //frame_char_icon->TB_Func_13("interface\\messagebox\\msgbox_itemwindow.ddj", 1, 0);
    frame_char_lock->TB_Func_13("interface\\frame\\ub_pet_wnd_", 1, 0);

    RECT rect_background_char_lock = {rect_frame_char_lock.left + 3,
                                      rect_frame_char_lock.top + 3,
                                      rect_frame_char_lock.right - 6,
                                      rect_frame_char_lock.bottom - 6};

    CIFNormalTile *tile_char_lock = (CIFNormalTile *) CreateInstance(this,
                                                                     GFX_RUNTIME_CLASS(CIFNormalTile),
                                                                     rect_background_char_lock,
                                                                     GDR_FLORIAN0_RT_MAIN_FRAME,
                                                                     1);
    tile_char_lock->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_d.ddj", 1, 0);

    RECT rect_m_char_lock_lable = {rect_frame_char_lock.left + 3,
                             rect_frame_char_lock.top + 3,
                             rect_frame_char_lock.right - 6,
                             rect_frame_char_lock.bottom - 6};
    m_char_lock_lable = (CIFStatic *) CGWnd::CreateInstance(this,
                                                      GFX_RUNTIME_CLASS(CIFStatic),
                                                            rect_m_char_lock_lable,
                                                            GDR_FLORIAN0_RT_CHARLOCK,
                                                      1);
    /////////// mainmenu frame
    RECT rect_frame1 = { 17,121,179,385 };

    CIFFrame *frame1 = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame1,
                                                  GDR_FLORIAN0_RT_MAIN_FRAME1,
                                                  1);
    //frame->TB_Func_13("interface\\messagebox\\msgbox_window_", 1, 0);
    frame1->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 0);

    RECT rect_background1 = {rect_frame1.left + 10,
                            rect_frame1.top + 10,
                            rect_frame1.right - 20,
                            rect_frame1.bottom - 20};

    CIFNormalTile *tile1 = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background1,
                                                           GDR_FLORIAN0_RT_MAIN_FRAME1,
                                                           1);
    tile1->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);
    /////////
    RECT rect_frame2 = { 17,507,179,58 };

    CIFFrame *frame2 = (CIFFrame *) CreateInstance(this,
                                                   GFX_RUNTIME_CLASS(CIFFrame),
                                                   rect_frame2,
                                                   GDR_FLORIAN0_RT_MAIN_FRAME1,
                                                   1);
    //frame->TB_Func_13("interface\\messagebox\\msgbox_window_", 1, 0);
    frame2->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 0);

    RECT rect_background2 = {rect_frame2.left + 10,
                             rect_frame2.top + 10,
                             rect_frame2.right - 20,
                             rect_frame2.bottom - 20};

    CIFNormalTile *tile2 = (CIFNormalTile *) CreateInstance(this,
                                                            GFX_RUNTIME_CLASS(CIFNormalTile),
                                                            rect_background2,
                                                            GDR_FLORIAN0_RT_MAIN_FRAME1,
                                                            1);
    tile2->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);
    ////// discord_icon
    RECT rect_discord_icon_button = {33,515,40,40};
    CIFButton *discord_icon_button = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_discord_icon_button,
                                                                         GDR_FLORIAN0_RT_BTN_DISCORD,
                                                         1);

    discord_icon_button->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\discord.ddj", 1, 1);
    ////// facebook_icon
    RECT rect_facebook_icon_button = {88,515,40,40};
    CIFButton *facebook_icon_button = (CIFButton *) CGWnd::CreateInstance(this,
                                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                                          rect_facebook_icon_button,
                                                                         GDR_FLORIAN0_RT_BTN_FACEBOOK,
                                                                         1);

    facebook_icon_button->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\facebook.ddj", 1, 1);
    ////// web_icon
    RECT rect_web_icon_button = {144,515,40,40};
    CIFButton *web_icon_button = (CIFButton *) CGWnd::CreateInstance(this,
                                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                                          rect_web_icon_button,
                                                                          GDR_FLORIAN0_RT_BTN_WEB,
                                                                          1);

    web_icon_button->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\website.ddj", 1, 1);
    ////////
    RECT rect_custom_label = {50, 50, 60, 20};
    m_custom_label = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_custom_label,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);


    RECT rect_label_time = {50, 70, 60, 20};
    m_time_label = (CIFStatic *) CGWnd::CreateInstance(this,
                                                       GFX_RUNTIME_CLASS(CIFStatic),
                                                       rect_label_time,
                                                       GDR_FLORIAN0_RT_LABEL_TIME,
                                                       1);
///////// button
    RECT rect_button = {rect_frame1.left + 20,
                         rect_frame1.top + 60,
                         rect_frame1.right - 40,
                         30};

    //RECT rect_button = {35, 70, 140, 30};
   btn = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button,
                                                         GDR_FLORIAN0_RT_BTN,
                                                         1);
    wchar_t buffer[255];
    swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_STT_EVENTREG4_NAME"));
    btn ->SetText(buffer);
    btn->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button1 = {rect_frame1.left + 20,
                        rect_frame1.top + 20,
                        rect_frame1.right - 40,
                        30};
    //RECT rect_button = {35, 70, 140, 30};
   btn1 = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button1,
                                                         GDR_FLORIAN0_RT_BTN1,
                                                         1);

    wchar_t buffer1[255];
    swprintf_s(buffer1, TSM_GETTEXTPTR("UIIT_ST_ITEM_LOCK"));
    btn1 ->SetText(buffer1);
    btn1->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);


    RECT rect_button2 = {rect_frame1.left + 20,
                         rect_frame1.top + 100,
                         rect_frame1.right - 40,
                         30};
    //RECT rect_button = {35, 70, 140, 30};
    btn2 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button2,
                                                          GDR_FLORIAN0_RT_BTN2,
                                                          1);

    btn2->SetText(TSM_GETTEXTPTR("UIIT_ST_UNIQUE_LABLE"));
    btn2->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button3 = {rect_frame1.left + 20,
                         rect_frame1.top + 140,
                         rect_frame1.right - 40,
                         30};
    btn3 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button3,
                                                          GDR_FLORIAN0_RT_BTN3,
                                                          1);

    btn3->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_SWITCH"));
    btn3->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);
    RECT rect_button4 = {rect_frame1.left + 20,
                         rect_frame1.top + 180,
                         rect_frame1.right - 40,
                         30};
    btn4 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button4,
                                                          GDR_FLORIAN0_RT_BTN4,
                                                          1);

    btn4->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_TILE"));
    btn4->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button5 = {rect_frame1.left + 20,
                         rect_frame1.top + 220,
                         rect_frame1.right - 40,
                         30};
    btn5 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button5,
                                                          GDR_FLORIAN0_RT_BTN5,
                                                          1);

    btn5->SetText(TSM_GETTEXTPTR("UIIT_ST_EVENTTIMER_TILE"));
    btn5->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button6 = {rect_frame1.left + 20,
                         rect_frame1.top + 260,
                         rect_frame1.right - 40,
                         30};
    btn6 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button6,
                                                          GDR_FLORIAN0_RT_BTN6,
                                                          1);

    btn6->SetText(TSM_GETTEXTPTR("UIIT_ST_TOTAL_POINT"));
    btn6->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button7 = {rect_frame1.left + 20,
                         rect_frame1.top + 300,
                         rect_frame1.right - 40,
                         30};
    btn7 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button7,
                                                          GDR_FLORIAN0_RT_BTN7,
                                                          1);

    btn7->SetText(TSM_GETTEXTPTR("UIIT_STT_PVP_CHALLENGE"));
    btn7->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button8 = {rect_frame1.left + 20,
                         rect_frame1.top + 340,
                         rect_frame1.right - 40,
                         30};
    btn8 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button8,
                                                          GDR_FLORIAN0_RT_BTN8,
                                                          1);

    btn8->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMNPC_SHOP"));
    btn8->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);
   // btn8->FUN_00656570(1);
/////////
    m_frame_label ->SetText(L"ST Filter Menu");
    this->ShowGWnd(false);
    return true;
}



void CIFflorian0Runtime::OnUpdate() {
    time_t rawtime;
    struct tm *timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);

    m_char_name->SetText(g_pCICPlayer->GetCharName().c_str());
    m_char_name->SetFont(theApp.GetFont(0));
    m_char_name->TB_Func_5(0); //can le
    m_char_name->TB_Func_6(2); // co chu


    if (!CPSMission::Gui_CharacterLock)
        btn1->SetEnabledState(0);

    //if (!CPSMission::Gui_GrantName)
    //    btn->SetEnabledState(0);

    if (!CPSMission::XSMB_ENABLE)
        btn->SetEnabledState(0);

    if (!CPSMission::Gui_UniqueHistory)
        btn2->SetEnabledState(0);

    if (!CPSMission::Gui_CustomTitle)
        btn3->SetEnabledState(0);

    if (!CPSMission::Gui_CustomRank)
        btn4->SetEnabledState(0);

    if (!CPSMission::Gui_EventTimer)
        btn5->SetEnabledState(0);

    if (!CPSMission::Gui_TotalPoint)
        btn6->SetEnabledState(0);

    if (!CPSMission::Gui_CustomNPC)
        btn8->SetEnabledState(0);

}
int CIFflorian0Runtime::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
void CIFflorian0Runtime::On_BtnClick() {
    if (!CPSMission::Gui_UniqueHistory)
    {
        g_pCGInterface->ShowMessage_Notice(L"Service not available");
        return;
    }

    g_pCGInterface->GetUniqueHistoryGUI()->ResetPosition();
    g_pCGInterface->GetUniqueHistoryGUI()->BringToFront();
    g_pCGInterface->GetUniqueHistoryGUI()->ShowGWnd(true);
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!uniquestatus");
    buf << std::n_string("!uniquestatus");
    SendMsg(buf);
}
void CIFflorian0Runtime::On_BtnClick_Test() {
    if (!CPSMission::Gui_CustomNPC)
    {
        g_pCGInterface->ShowMessage_Notice(L"Service not available");
        return;
    }
    //g_pCGInterface->GetCIFSTEffectGUI()->SetBattleRoyaleStage_1_Time(1);
    //g_CGlobalDataManager->m_CharacterIcons[L"SroSuTu"]=20;
    // CIFflorian0Guide::WorldMap->FUN_006192f0();
   // if (g_pCICPlayer) {
   //     g_pCGInterface->SwitchToStallNetwork(true);
   // }
  //  g_CGlobalDataManager-> m_IconsData.insert(std::pair<int,void*>(1337,Fun_CacheTexture_Create("icon\\etc\\fort_jangan.ddj")));
   // g_CGlobalDataManager->m_CharacterIcons.insert(std::pair<std::wstring,UINT32>(L"SroTuSu",1337));
   // g_CGlobalDataManager-> m_CharacterIcons.insert(std::pair<std::wstring,UINT32>(L"ICON",1337));
   // g_pCICPlayer->m_CCObjAnimation_MAYBE->SetClothes(3);
   // g_pCICPlayer->m_CCObjAnimation_MAYBE->SetClothesApply();
    g_pCGInterface->GetCustomNPCGUI() ->ShowGWnd(true);
//    CMsgStreamBuffer buf(0x1318);
//    buf << std::n_string("!PARTY");
//    buf << std::n_string("!PARTY");
//    SendMsg(buf);
   // CMsgStreamBuffer buf(0x7050);
   // buf ;
   // SendMsg(buf);

}
void CIFflorian0Runtime::On_BtnClick_SendPVP() {

    g_pCGInterface->GetPvpChallengeGUI()->ResetPosition();
    g_pCGInterface->GetPvpChallengeGUI()->BringToFront();
    g_pCGInterface->GetPvpChallengeGUI()->m_edit->SetText(L"");
    g_pCGInterface->GetPvpChallengeGUI()->m_edit2->SetText(L"");
    g_pCGInterface->GetPvpChallengeGUI()->ShowGWnd(true);
}
void CIFflorian0Runtime::On_BtnClickCharLock() {

    if (!CPSMission::Gui_CharacterLock)
    {
        g_pCGInterface->ShowMessage_Notice(L"Service not available");
        return;
    }
    //Rebot::GetListBase();
    //UINT  a =1;
    //g_NPCPosActive = *(&a);
//printf("Rebot::GetListBase() %d \n",Rebot::GetListBase());
    g_pCGInterface->GetCharLockGUI()->ResetPosition();
    g_pCGInterface->GetCharLockGUI()->BringToFront();
    g_pCGInterface->GetCharLockGUI()->ShowGWnd(true);
    g_pCGInterface->GetCharLockGUI()->m_edit1 -> SetText(L"");
    g_pCGInterface->GetCharLockGUI()->m_edit2 -> SetText(L"");


   /* CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!PARTYT");
    buf << std::n_string("!PARTYT");
    SendMsg(buf);*/
}
void CIFflorian0Runtime::On_BtnClick_Title() {

   /* SilkroadWeb* m_Web = new SilkroadWeb();
    wchar_t buffer[1000];
    swprintf_s(buffer, L"http://localhost/WebMall/gamemallgate.php?jid=%d&key=%S", CPSMission::m_UserJID,CPSMission::m_szToken.c_str());
    std::n_wstring strmsg(buffer);
    printf("%s",TO_STRING(strmsg).c_str());
    m_Web->Start(100, 200, 800, 570, TO_STRING(strmsg).c_str());
*/
    if (!CPSMission::Gui_CustomTitle)
    {
        g_pCGInterface->ShowMessage_Notice(L"Service not available");
        return;
    }


    CIFCustomTitle::ColorSelectShow = false;

    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!TitleUpdate");
    buf << std::n_string("!TitleUpdate");
    SendMsg(buf);
    g_pCGInterface->GetCustomTitleGUI()->m_custom_label3->ShowGWnd(true);
    g_pCGInterface->GetCustomTitleGUI()->m_custom_label3->m_FontTexture.SetColor(D3DCOLOR_RGBA(255, 0, 0, 255)); //#FF0000
    g_pCGInterface->GetCustomTitleGUI()->tab1= true;
    g_pCGInterface->GetCustomTitleGUI()->m_mybutton5->TB_Func_13("interface\\ifcommon\\com_long_tab_off.ddj", 0, 0);
    g_pCGInterface->GetCustomTitleGUI()->m_mybutton6->TB_Func_13("interface\\ifcommon\\com_long_tab_on.ddj", 0, 0);
    wchar_t buffer1[80];
    swprintf_s(buffer1, TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TOOLTIP7"));
    g_pCGInterface->GetCustomTitleGUI()->m_custom_label2->SetText(buffer1);
    wchar_t buffer2[80];
    swprintf_s(buffer2, TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TOOLTIP6"));
    g_pCGInterface->GetCustomTitleGUI()->m_custom_label3->SetText(buffer2);

    g_pCGInterface->GetCustomTitleGUI()->m_edit->ShowGWnd(true);
    g_pCGInterface->GetCustomTitleGUI()->m_edit->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_d.ddj", 0, 0);
    g_pCGInterface->GetCustomTitleGUI()->m_mybutton7->ShowGWnd(false);
    g_pCGInterface->GetCustomTitleGUI()->m_mybutton8->ShowGWnd(false);
    g_pCGInterface->GetCustomTitleGUI()->m_mybutton9->ShowGWnd(false);
    g_pCGInterface->GetCustomTitleGUI()->m_mybutton10->ShowGWnd(false);
    g_pCGInterface->GetCustomTitleGUI()->m_mybutton11->ShowGWnd(false);
    g_pCGInterface->GetCustomTitleGUI()->m_mybutton12->ShowGWnd(false);
    g_pCGInterface->GetCustomTitleGUI()->m_mybutton13->ShowGWnd(false);

    g_pCGInterface->GetCustomTitleGUI()->ResetPosition();
    g_pCGInterface->GetCustomTitleGUI()->BringToFront();
    g_pCGInterface->GetCustomTitleGUI()->ShowGWnd(true);

}
void CIFflorian0Runtime::On_BtnClick_ChangeGrantName() {

    g_pCGInterface->GetEventXoSoGUI()-> m_mybutton7 ->TB_Func_13("interface\\ifcommon\\ngt\\checkbutton_on.ddj", 0, 0);
    g_pCGInterface->GetEventXoSoGUI()-> m_mybutton8 ->TB_Func_13("interface\\ifcommon\\ngt\\checkbutton_off.ddj", 0, 0);
    g_pCGInterface->GetEventXoSoGUI()-> m_mybutton9 ->TB_Func_13("interface\\ifcommon\\ngt\\checkbutton_off.ddj", 0, 0);
    g_pCGInterface->GetEventXoSoGUI()-> gold = true;
    g_pCGInterface->GetEventXoSoGUI()-> silk = false;
    g_pCGInterface->GetEventXoSoGUI()-> gilf = false;
    g_pCGInterface->GetEventXoSoGUI()-> m_edit->SetText(L"");
    g_pCGInterface->GetEventXoSoGUI()-> m_edit1->SetText(L"");
    g_pCGInterface->GetEventXoSoGUI()-> m_edit->SetFocus_MAYBE();
    g_pCGInterface->GetEventXoSoGUI()-> silk = false;
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!XSMBKQ");
    buf << std::n_string("!XSMBKQ");
    SendMsg(buf);
    g_pCGInterface->GetEventXoSoGUI()->ResetPosition();
    g_pCGInterface->GetEventXoSoGUI()->ShowGWnd(true);
}
void CIFflorian0Runtime::On_BtnClick_New() {
    if (!CPSMission::Gui_CustomRank)
    {
        g_pCGInterface->ShowMessage_Notice(L"Service not available");
        return;
    }

    g_pCGInterface->GetCustomRankGUI()->ResetPosition();
    g_pCGInterface->GetCustomRankGUI()->BringToFront();
    g_pCGInterface->GetCustomRankGUI()->ShowGWnd(true);


}
void CIFflorian0Runtime::On_BtnClick_EventTimer() {
    if (!CPSMission::Gui_EventTimer)
    {
        g_pCGInterface->ShowMessage_Notice(L"Service not available");
        return;
    }
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!UPDATEEVENTTIMER");
    buf << std::n_string("!UPDATEEVENTTIMER");
    SendMsg(buf);
    g_pCGInterface->GetEventTimeGUI()->ResetPosition();
    g_pCGInterface->GetEventTimeGUI()->BringToFront();
    g_pCGInterface->GetEventTimeGUI()->ShowGWnd(true);

}
void CIFflorian0Runtime::On_BtnClick_Unknow()  {
    if (!CPSMission::Gui_TotalPoint)
    {
        g_pCGInterface->ShowMessage_Notice(L"Service not available");
        return;
    }
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!UPDATETOTALPOINT");
    buf << std::n_string("!UPDATETOTALPOINT");
    SendMsg(buf);

    g_pCGInterface->GetTotalPointsGUI()->ResetPosition();
    g_pCGInterface->GetTotalPointsGUI()->BringToFront();
    g_pCGInterface->GetTotalPointsGUI()->ShowGWnd(true);
}
void CIFflorian0Runtime::On_BtnClick_Discord() {
    ShellExecute(NULL, "open", CPSMission::DiscordUrl.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
void CIFflorian0Runtime::On_BtnClick_Facebook() {
    ShellExecute(NULL, "open", CPSMission::FacebookUrl.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
void CIFflorian0Runtime::On_BtnClick_Web() {
    ShellExecute(NULL, "open", CPSMission::WebsiteUrl.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void CIFflorian0Runtime::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosY = CLIENT_SCREEN_HEIGHT - 600;
    PosX = CLIENT_SCREEN_WIDTH - 305;
    this->MoveGWnd(PosX, PosY);
}