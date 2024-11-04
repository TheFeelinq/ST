//
// Created by Admin on 12/2/2022.
//

#include "IFSTMacroAutoHunt.h"
#include "Game.h"
#include "Rebot.h"
#include "IFflorian0Guide.h"
#include "PartyData.h"
#include "CharacterDependentData.h"

#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>
#include <unsorted.h>
#include <ICPlayer.h>

#include <sstream>
#include <BSLib/multibyte.h>
#include <algorithm>

#define GDR_RANGE_SEL_BTN 3
#define GDR_SAVE_BTN 5
#define GDR_CANCEL_BTN 6
#define GDR_EU_BTN 28
#define GDR_ASIAN_BTN 8
#define GDR_GXVSRO_FRAME 1
#define GDR_GXVSRO_FRAME2 29
#define GDR_GXVSRO_FRAME3 30
#define GDR_GXVSRO_FRAME4 31
#define GDR_GXVSRO_FRAME5 34
#define GDR_GXVSRO_FRAME6 36
#define GDR_GXVSRO_FRAME7 38
#define GDR_GXVSRO_FRAME8 40
#define GDR_GXVSRO_TITLE 2
#define GDR_1_BTN 20
#define GDR_2_BTN 21
#define GDR_3_BTN 22
#define GDR_4_BTN 24
#define GDR_5_BTN 23
#define GDR_6_BTN 25
#define GDR_GXVSRO_TEXTBOX1 33
#define GDR_GXVSRO_CHECKBOX_BER 35
#define GDR_GXVSRO_CHECKBOX_GOBACK_CENTRER 37
#define GDR_GXVSRO_CHECKBOX_ATTACK_HOSTILITY 39
#define GDR_GXVSRO_CHECKBOX_JOIN_PARTY 56
#define GDR_GXVSRO_CHECKBOX_LURE_MODE 57
#define GDR_GXVSRO_CHECKBOX_ACCEPT_RES 58
#define GDR_GXVSRO_CHECKBOX_RES_PARTYMEMBER 59
#define GDR_GXVSRO_CHECKBOX_ATTACK_OTHER_PLAYER 60
#define GDR_GXVSRO_HP_SLIDER 60
#define GDR_GXVSRO_MP_SLIDER 61
#define GDR_GXVSRO_VIGOR_SLIDER 62
#define GDR_GXVSRO_ABNORMAL_SLIDER 63
#define GDR_GXVSRO_SLOT1_POTION 7781
#define GDR_GXVSRO_SLOT2_POTION 7782
#define GDR_GXVSRO_SLOT3_POTION 7783
#define GDR_GXVSRO_SLOT4_POTION 7784
#define GDR_GXVSRO_SLOT5_POTION 7785
#define GDR_GXVSRO_CHECKBOX_HP 45
#define GDR_GXVSRO_CHECKBOX_MP 46
#define GDR_GXVSRO_CHECKBOX_ABNORMAL 47
#define GDR_GXVSRO_CHECKBOX_SPEEDSCROLL 64
#define GDR_GXVSRO_EDIT_HP 48
#define GDR_GXVSRO_EDIT_MP 49
#define GDR_GXVSRO_EDIT_VIGOR 50
#define GDR_GXVSRO_TEXT_POTION 51
#define GDR_GXVSRO_CHECKBOX_VIGOR 52
#define GDR_SAVE2_BTN 53
#define GDR_CANCEL2_BTN 54
#define GDR_GXVSRO_TEXT_POTION_TOOLTIP 55

#define GDR_GXVSRO_CHECKBOX_PET_HP 80
#define GDR_GXVSRO_CHECKBOX_PET_HGP 81
#define GDR_GXVSRO_EDIT_PET_HP 82
#define GDR_GXVSRO_EDIT_PET_HGP 83
#define GDR_GXVSRO_PET_HP_SLIDER 84
#define GDR_GXVSRO_PET_HGP_SLIDER 85
#define GDR_GXVSRO_CHECKBOX_PET_CURE 86
#define GDR_GXVSRO_CHECKBOX_PET_RESURRECT 87
#define GDR_GXVSRO_CHECKBOX_PET_TRIGGER 88
#define GDR_GXVSRO_FRAME_PET_CURE 89
#define GDR_GXVSRO_FRAME_PET_HP 90
#define GDR_GXVSRO_FRAME_PET_HGP 91
#define GDR_GXVSRO_FRAME_PET_RESURRECT 92
#define GDR_GXVSRO_FRAME_PET_TRIGGER 93
#define GDR_GXVSRO_FRAME_PET_POTION 94
#define GDR_GXVSRO_EDIT_PET_TRADE_RIDDING 95
#define GDR_GXVSRO_CHECKBOX_PET_TRADE 96
#define GDR_GXVSRO_PET_TRADE_RIDDING_SLIDER 97
#define GDR_GXVSRO_CHECKBOX_PET_RIDDING 98
#define GDR_SAVE3_BTN 99
#define GDR_CANCEL3_BTN 400
#define GDR_GXVSRO_FRAME_BUFF_CHARNAME_LIST 401
#define GDR_GXVSRO_FRAME_BUFF_SKILLNAME_LIST 402
#define GDR_GXVSRO_FRAME_BUFF_SKILLBUFFED_LIST 402
#define GDR_GXVSRO_FRAME_BUFF_TITLE 403
#define GDR_ADD_SKILL_BTN 404
#define GDR_REMOVE_SKILL_BTN 405
#define GDR_GXVSRO_CHECKBOX_BUFFMODE 406

#define GDR_GXVSRO_SLOT6_PET_POTION 7786
#define GDR_GXVSRO_SLOT7_PET_POTION 7787
#define GDR_GXVSRO_SLOT8_PET_POTION 7788
#define GDR_GXVSRO_SLOT9_PET_POTION 7789
#define GDR_GXVSRO_SLOT10_PET_POTION 7790
#define GDR_GXVSRO_SLOT11_PET_POTION 7791

GFX_IMPLEMENT_DYNCREATE(CIFSTMacroAutoHunt, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFSTMacroAutoHunt, CIFMainFrame)
                    ONG_COMMAND(GDR_RANGE_SEL_BTN, &CIFSTMacroAutoHunt::OnListSelectRange)
                    ONG_COMMAND(GDR_SAVE_BTN, &CIFSTMacroAutoHunt::OnSaveClick)
                    ONG_COMMAND(GDR_SAVE2_BTN, &CIFSTMacroAutoHunt::OnSave2Click)
                    ONG_COMMAND(GDR_SAVE3_BTN, &CIFSTMacroAutoHunt::OnSave3Click)
                    ONG_COMMAND(GDR_CANCEL_BTN, &CIFSTMacroAutoHunt::OnCancelClick)
                    ONG_COMMAND(GDR_CANCEL2_BTN, &CIFSTMacroAutoHunt::OnCancelClick)
                    ONG_COMMAND(GDR_CANCEL3_BTN, &CIFSTMacroAutoHunt::OnCancelClick)
                    ONG_COMMAND(GDR_ADD_SKILL_BTN, &CIFSTMacroAutoHunt::On_Buff_AddSkill)
                    ONG_COMMAND(GDR_REMOVE_SKILL_BTN, &CIFSTMacroAutoHunt::On_Buff_RemoveSkill)
                    ONG_COMMAND(100, &CIFSTMacroAutoHunt::OnUnknownStuff)
                    ONG_COMMAND(101, &CIFSTMacroAutoHunt::OnUnknownStuff)
                    ONG_COMMAND(102, &CIFSTMacroAutoHunt::OnUnknownStuff)
                    ONG_COMMAND(103, &CIFSTMacroAutoHunt::OnUnknownStuff)
                    ONG_COMMAND(104, &CIFSTMacroAutoHunt::OnUnknownStuff)
                    ONG_COMMAND(105, &CIFSTMacroAutoHunt::OnUnknownStuff)

                    ONG_BSSig_u38(2, 0x806D, GDR_GXVSRO_TEXTBOX1, &CIFSTMacroAutoHunt::OnListChatThing)

GFX_END_MESSAGE_MAP()

std::vector<CIFSTMacroAutoHunt::PartyMatchMember> CIFSTMacroAutoHunt::PartyMatchMemberList;
std::vector<CIFSTMacroAutoHunt::CharSkillData> CIFSTMacroAutoHunt::CharSkillDataList;
CIFSTMacroAutoHunt::CIFSTMacroAutoHunt(void)
{
    //  printf("> " __FUNCTION__ "\n");
}


CIFSTMacroAutoHunt::~CIFSTMacroAutoHunt(void)
{
    //  printf("> " __FUNCTION__ "\n");
}
int CIFSTMacroAutoHunt::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
bool CIFSTMacroAutoHunt::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT rect_m_tile = {190, 9, 186, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_TOOLTIP2"));

    RECT Framerect = { 10,65,385,315 };
    RECT Lablerect = { 16,308,480,62 };
    RECT Butt2rect = { 155,375,100,24 };
    RECT Butt3rect = { 297,375,100,24 };


    Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), Framerect, GDR_GXVSRO_FRAME, 0);
    m_custom_label = (CIFNormalTile*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), Lablerect, GDR_GXVSRO_TITLE, 0);

    m_mybutton2 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt2rect, GDR_SAVE_BTN, 0);
    m_mybutton3 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt3rect, GDR_CANCEL_BTN, 0);
    m_mybutton4 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt2rect, GDR_SAVE2_BTN, 0);
    m_mybutton5 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt3rect, GDR_CANCEL2_BTN, 0);
    m_mybutton6 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt2rect, GDR_SAVE3_BTN, 0);
    m_mybutton7 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt3rect, GDR_CANCEL3_BTN, 0);
    m_mybutton8 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt2rect, GDR_ADD_SKILL_BTN, 0);
    m_mybutton9 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt3rect, GDR_REMOVE_SKILL_BTN, 0);

    m_custom_label->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 1, 0);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
    m_mybutton2->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton3->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton2->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_SAVE"));
    m_mybutton3->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_CANCEL"));
    m_mybutton4->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton5->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton4->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_SAVE"));
    m_mybutton5->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_CANCEL"));
    m_mybutton6->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton7->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton6->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_SAVE"));
    m_mybutton7->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_CANCEL"));
    m_mybutton8->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton8->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_BUFF_ADD_BTN"));
    m_mybutton9->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton9->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_BUFF_REMOVE_BTN"));

    Frame->SetGWndSize(this->GetSize().width - 18, this->GetSize().height - 110);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 65);
    m_custom_label->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
    m_custom_label->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);

///////////////
    RECT rect_m_custom_bg = {Framerect.left + 10,
                             Framerect.top + 20,
                             Framerect.right - 20,
                             38};
    m_custom_bg = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_bg,GDR_GXVSRO_FRAME2,1);
    m_custom_bg->TB_Func_13("interface\\option\\opt_camera.ddj", 1, 1);

    RECT rect_m_custom_box = {rect_m_custom_bg.left + 180,
                              rect_m_custom_bg.top + 7,
                              150,
                             24};
    m_custom_label2 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_box,GDR_GXVSRO_FRAME3,1);
    m_custom_label2->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);
    m_custom_label2->SetText(L"10m");

    RECT rect_m_custom_range = {rect_m_custom_bg.left + 10,
                              rect_m_custom_bg.top + 11,
                              150,
                              15};
    m_custom_label3 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_range,GDR_GXVSRO_FRAME4,1);
    m_custom_label3 -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_HUNT_RANGE"));
    m_custom_label3->TB_Func_5(0);


    RECT Buttrect = {rect_m_custom_box.left + 151,
                     rect_m_custom_box.top + 2,
                                20,
                                20};
    m_mybutton = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Buttrect, GDR_RANGE_SEL_BTN, 0);
    m_mybutton->TB_Func_13("interface\\ifcommon\\com_qst_downarrow_button.ddj", 1, 1);

    RECT rect_m_custom_bg2 = {Framerect.left + 10,
                              Framerect.top + 20 + rect_m_custom_bg.bottom,
                              Framerect.right - 120,
                              38};
    m_custom_bg2 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_bg2,GDR_GXVSRO_FRAME2,1);
    m_custom_bg2->TB_Func_13("interface\\option\\opt_camera.ddj", 1, 1);

    RECT rect_m_custom_berserk = {rect_m_custom_bg2.left + 10,
                                  rect_m_custom_bg2.top + 11,
                                  150,
                                  15};
    m_custom_label11 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_berserk,GDR_GXVSRO_FRAME5,1);
    m_custom_label11 -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_HUNT_BERSERK"));
    m_custom_label11->TB_Func_5(0);
    RECT rect_m_checkbox_berserk =  {rect_m_custom_bg2.left + 216,
                                     rect_m_custom_bg2.top + 11,
                                     16,
                                     16};
    m_checkbox_berserk = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_berserk, GDR_GXVSRO_CHECKBOX_BER, 0);


    RECT rect_m_custom_bg3 = {Framerect.left + 10,
                              Framerect.top + 20 + rect_m_custom_bg2.bottom  + rect_m_custom_bg.bottom,
                              Framerect.right - 120,
                              38};
    m_custom_bg3 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_bg3,GDR_GXVSRO_FRAME2,1);
    m_custom_bg3->TB_Func_13("interface\\option\\opt_camera.ddj", 1, 1);

    RECT rect_m_custom_goback_centrer = {rect_m_custom_bg3.left + 10,
                                         rect_m_custom_bg3.top + 11,
                                  150,
                                  15};
    m_custom_label12 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_goback_centrer,GDR_GXVSRO_FRAME6,1);
    m_custom_label12 -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_HUNT_GOBACK"));
    m_custom_label12->TB_Func_5(0);

    RECT rect_m_checkbox_goback_centrer =  {rect_m_custom_bg3.left + 216,
                                            rect_m_custom_bg3.top + 11,
                                     16,
                                     16};
    m_checkbox_goback_center = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_goback_centrer, GDR_GXVSRO_CHECKBOX_GOBACK_CENTRER, 0);

    RECT rect_m_custom_bg4 = {Framerect.left + 10,
                              Framerect.top + 20 + rect_m_custom_bg2.bottom  + rect_m_custom_bg.bottom + rect_m_custom_bg3.bottom,
                              Framerect.right - 120,
                              38};
    m_custom_bg4 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_bg4,GDR_GXVSRO_FRAME2,1);
    m_custom_bg4->TB_Func_13("interface\\option\\opt_camera.ddj", 1, 1);

    RECT rect_m_custom_attack_hostility = {rect_m_custom_bg4.left + 10,
                                           rect_m_custom_bg4.top + 11,
                                         150,
                                         15};
    m_custom_label13 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_attack_hostility,GDR_GXVSRO_FRAME7,1);
    m_custom_label13 -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_HUNT_ATTACK_HOSTILITY"));
    m_custom_label13->TB_Func_5(0);
    RECT rect_m_checkbox_attack_hostility =  {rect_m_custom_bg4.left + 216,
                                              rect_m_custom_bg4.top + 11,
                                            16,
                                            16};
    m_checkbox_attack_hostility = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_attack_hostility, GDR_GXVSRO_CHECKBOX_ATTACK_HOSTILITY, 0);


    RECT rect_m_custom_bg5 = {Framerect.left + 10,
                              Framerect.top + 20 + rect_m_custom_bg2.bottom  + rect_m_custom_bg.bottom + rect_m_custom_bg3.bottom + + rect_m_custom_bg4.bottom,
                              Framerect.right - 120,
                              38};
    m_custom_bg5 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_bg5,GDR_GXVSRO_FRAME2,1);
    m_custom_bg5->TB_Func_13("interface\\option\\opt_camera.ddj", 1, 1);

    RECT rect_m_custom_accept_request_joinparty = {rect_m_custom_bg5.left + 10,
                                                   rect_m_custom_bg5.top + 11,
                                           150,
                                           15};
    m_custom_label14 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_accept_request_joinparty,GDR_GXVSRO_FRAME7,1);
    m_custom_label14 -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_HUNT_REQUEST_JOIN_PARTY"));
    m_custom_label14->TB_Func_5(0);
    RECT rect_m_checkbox_accept_request_joinparty =  {rect_m_custom_bg5.left + 216,
                                                      rect_m_custom_bg5.top + 11,
                                              16,
                                              16};
    m_checkbox_accept_request_joinparty = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_accept_request_joinparty, GDR_GXVSRO_CHECKBOX_JOIN_PARTY, 0);

    RECT rect_m_custom_bg6 = {Framerect.left + 10,
                              Framerect.top + 20 + rect_m_custom_bg2.bottom  + rect_m_custom_bg.bottom + rect_m_custom_bg3.bottom + rect_m_custom_bg4.bottom + rect_m_custom_bg5.bottom,
                              Framerect.right - 120,
                              38};
    m_custom_bg6 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_bg6,GDR_GXVSRO_FRAME2,1);
    m_custom_bg6->TB_Func_13("interface\\option\\opt_camera.ddj", 1, 1);

    RECT rect_m_custom_luremode = {rect_m_custom_bg6.left + 10,
                                   rect_m_custom_bg6.top + 11,
                                                   150,
                                                   15};
    m_custom_label15 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_luremode,GDR_GXVSRO_FRAME7,1);
    m_custom_label15 -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_LURE_MODE"));
    m_custom_label15->TB_Func_5(0);
    RECT rect_m_checkbox_luremode =  {rect_m_custom_bg6.left + 216,
                                      rect_m_custom_bg6.top + 11,
                                                      16,
                                                      16};
    m_checkbox_luremode = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_luremode, GDR_GXVSRO_CHECKBOX_LURE_MODE, 0);

    RECT rect_m_custom_bg7 = {Framerect.left + 10,
                              Framerect.top + 20 + rect_m_custom_bg2.bottom  + rect_m_custom_bg.bottom + rect_m_custom_bg3.bottom + rect_m_custom_bg4.bottom + rect_m_custom_bg5.bottom + rect_m_custom_bg6.bottom,
                              Framerect.right - 120,
                              38};
    m_custom_bg7 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_bg7,GDR_GXVSRO_FRAME2,1);
    m_custom_bg7->TB_Func_13("interface\\option\\opt_camera.ddj", 1, 1);

    RECT rect_m_custom_accept_res = {rect_m_custom_bg7.left + 10,
                                   rect_m_custom_bg7.top + 11,
                                   150,
                                   15};
    m_custom_label16 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_accept_res,GDR_GXVSRO_FRAME7,1);
    m_custom_label16 -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_HUNT_ACCEPT_RESCUE"));
    m_custom_label16->TB_Func_5(0);
    RECT rect_m_checkbox_accept_res =  {rect_m_custom_bg7.left + 216,
                                      rect_m_custom_bg7.top + 11,
                                      16,
                                      16};
    m_checkbox_accept_res = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_accept_res, GDR_GXVSRO_CHECKBOX_ACCEPT_RES, 0);

    RECT rect_m_custom_bg8 = {Framerect.left + 10 + rect_m_custom_bg3.right,
                              Framerect.top + 20   + rect_m_custom_bg2.bottom,
                              Framerect.right - 120,
                              38};
    m_custom_bg8 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_bg8,GDR_GXVSRO_FRAME2,1);
    m_custom_bg8->TB_Func_13("interface\\option\\opt_camera.ddj", 1, 1);

    RECT rect_m_custom_res_partymember = {rect_m_custom_bg8.left + 10,
                                          rect_m_custom_bg8.top + 11,
                                     150,
                                     15};
    m_custom_label17 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_res_partymember,GDR_GXVSRO_FRAME7,1);
    m_custom_label17 -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_RES_PARTYMEMBER"));
    m_custom_label17->TB_Func_5(0);
    RECT rect_m_checkbox_res_partymember =  {rect_m_custom_bg8.left + 216,
                                             rect_m_custom_bg8.top + 11,
                                        16,
                                        16};
    m_checkbox_res_partymember = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_res_partymember, GDR_GXVSRO_CHECKBOX_RES_PARTYMEMBER, 0);

    RECT rect_m_custom_bg9 = {Framerect.left + 10 + rect_m_custom_bg3.right,
                              Framerect.top + 20   + rect_m_custom_bg2.bottom + rect_m_custom_bg8.bottom,
                              Framerect.right - 120,
                              38};
    m_custom_bg9 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_bg9,GDR_GXVSRO_FRAME2,1);
    m_custom_bg9->TB_Func_13("interface\\option\\opt_camera.ddj", 1, 1);

    RECT rect_m_custom_bg10 = {Framerect.left + 10 + rect_m_custom_bg3.right,
                              Framerect.top + 20   + rect_m_custom_bg2.bottom + rect_m_custom_bg8.bottom + rect_m_custom_bg9.bottom,
                              Framerect.right - 120,
                              38};
    m_custom_bg10 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_bg10,GDR_GXVSRO_FRAME2,1);
    m_custom_bg10->TB_Func_13("interface\\option\\opt_camera.ddj", 1, 1);

    RECT rect_m_custom_bg11 = {Framerect.left + 10 + rect_m_custom_bg3.right,
                               Framerect.top + 20   + rect_m_custom_bg2.bottom + rect_m_custom_bg8.bottom + rect_m_custom_bg9.bottom + rect_m_custom_bg10.bottom,
                               Framerect.right - 120,
                               38};
    m_custom_bg11 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_bg11,GDR_GXVSRO_FRAME2,1);
    m_custom_bg11->TB_Func_13("interface\\option\\opt_camera.ddj", 1, 1);

    RECT rect_m_custom_attack_other_player = {rect_m_custom_bg9.left + 10,
                                              rect_m_custom_bg9.top + 11,
                                          150,
                                          15};
    m_custom_label18= (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_attack_other_player,GDR_GXVSRO_FRAME7,1);
    m_custom_label18 -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_ATTACK_PLAYER"));
    m_custom_label18->TB_Func_5(0);

    RECT rect_m_custom_buff_mode = {rect_m_custom_bg10.left + 10,
                                    rect_m_custom_bg10.top + 11,
                                              150,
                                              15};
    m_custom_label19= (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_buff_mode,GDR_GXVSRO_FRAME7,1);
    m_custom_label19 -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_BUFF_MODE"));
    m_custom_label19->TB_Func_5(0);

    RECT rect_m_attack_snowman_and_pillar = {rect_m_custom_bg11.left + 10,
                                             rect_m_custom_bg11.top + 11,
                                    150,
                                    15};
    m_custom_label20= (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_attack_snowman_and_pillar,GDR_GXVSRO_FRAME7,1);
    m_custom_label20 -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_ATTACK_SNOWMAN_AND_PILLAR"));
    m_custom_label20->TB_Func_5(0);

    RECT rect_mm_checkbox_attack_other_player =  {rect_m_custom_bg9.left + 216,
                                            rect_m_custom_bg9.top + 11,
                                             16,
                                             16};
    m_checkbox_attack_other_player = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_mm_checkbox_attack_other_player, GDR_GXVSRO_CHECKBOX_ATTACK_OTHER_PLAYER, 0);

    RECT rect_mm_checkbox_buff_mode =  {rect_m_custom_bg10.left + 216,
                                        rect_m_custom_bg10.top + 11,
                                                  16,
                                                  16};
    m_checkbox_buff_mode = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_mm_checkbox_buff_mode, GDR_GXVSRO_CHECKBOX_BUFFMODE, 0);

    RECT rect_m_checkbox_attack_snowman_and_pillar =  {rect_m_custom_bg11.left + 216,
                                        rect_m_custom_bg11.top + 11,
                                        16,
                                        16};
    m_checkbox_attack_snowman_and_pillar = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_attack_snowman_and_pillar, GDR_GXVSRO_CHECKBOX_BUFFMODE, 0);

    m_checkbox_attack_snowman_and_pillar->FUN_00656d50(1);
    m_checkbox_buff_mode->FUN_00656d50(0);
    std::n_wstring str = TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_BUFF_TOOLTIP");
    m_checkbox_buff_mode->SetTooltipText(&str);
    m_checkbox_buff_mode->FUN_00652d20(128);

    m_checkbox_attack_other_player->FUN_00656d50(0);
    m_checkbox_res_partymember->FUN_00656d50(0);
    std::n_wstring str2 = TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_BUFF_TOOLTIP2");
    m_checkbox_res_partymember->SetTooltipText(&str2);
    m_checkbox_res_partymember->FUN_00652d20(128);

    m_checkbox_luremode->FUN_00656d50(0);
    std::n_wstring str3 = TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_BUFF_TOOLTIP3");
    m_checkbox_luremode->SetTooltipText(&str3);
    m_checkbox_luremode->FUN_00652d20(128);


    m_checkbox_goback_center->FUN_00656d50(0);
    m_checkbox_accept_res->FUN_00656d50(0);
////////

    RECT Framerect2 = {rect_m_custom_box.left,
                       rect_m_custom_box.bottom+3,
                       rect_m_custom_box.right,
                              105};
    Frame2 = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), Framerect2, GDR_GXVSRO_FRAME2, 0);
    Frame2->TB_Func_13("interface\\frame\\mall_sub_wnd02_", 0, 0);
    Frame2->MoveGWnd(m_custom_label2->GetPos().x,m_custom_label2->GetPos().y+25);

    RECT NormalTileRect = {Framerect2.left + 10,
                           Framerect2.top + 10,
                           Framerect2.right - 20,
                           Framerect2.bottom - 20};
    m_custom_NormalTile = (CIFNormalTile*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), NormalTileRect, GDR_GXVSRO_TITLE, 0);
    m_custom_NormalTile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_o.ddj", 1, 0);
    m_custom_NormalTile->MoveGWnd(Frame2->GetPos().x+5,Frame2->GetPos().y+5);
//////////
    RECT rect_Slot11_lable = {10,45,46,46};

    statics11 = (CIFFrame *) CreateInstance(this,
                                            GFX_RUNTIME_CLASS(CIFFrame),
                                            rect_Slot11_lable,
                                            GDR_GXVSRO_FRAME_PET_POTION,
                                            1);
    statics11->TB_Func_13("interface\\option\\opt_inner_box_", 1, 1);
    statics11->SetGWndSize(this->GetSize().width - 42, this->GetSize().height - 230);
    statics11->MoveGWnd(this->GetPos().x + 22, this->GetPos().y + 80);

    RECT rect_buff_frame_1 = {10,45,145,251};
    RECT rect_buff_frame_2 = {10,45,192,251};
    RECT rect_buff_frame_3 = {10,45,192,251};
    RECT rect_buff_frame_title_1 = {36,83,90,15};
    RECT rect_buff_frame_title_2 = {181,83,150,15};
    RECT rect_buff_frame_title_3 = {378,83,150,15};
    statics14 = (CIFFrame *) CreateInstance(this,
                                            GFX_RUNTIME_CLASS(CIFFrame),
                                            rect_buff_frame_1,
                                            GDR_GXVSRO_FRAME_BUFF_CHARNAME_LIST,
                                            1);
    statics14->TB_Func_13("interface\\option\\opt_inner_box_", 1, 1);
    statics14->MoveGWnd(this->GetPos().x + 22, this->GetPos().y + 80);

    RECT rect_m_custom_partymemberlist = {rect_buff_frame_1.left + 10,
                                          rect_buff_frame_1.top + 2,
                                          90,
                                          15};
    m_custom_label_partymemberlist = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_buff_frame_title_1,GDR_GXVSRO_FRAME_BUFF_TITLE,1);
    m_custom_label_partymemberlist -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_BUFF_CHARNAME_LIST"));
    m_custom_label_partymemberlist->BringToFront();

    statics15 = (CIFFrame *) CreateInstance(this,
                                            GFX_RUNTIME_CLASS(CIFFrame),
                                            rect_buff_frame_2,
                                            GDR_GXVSRO_FRAME_BUFF_SKILLNAME_LIST,
                                            1);
    statics15->TB_Func_13("interface\\option\\opt_inner_box_", 1, 1);
    statics15->MoveGWnd(this->GetPos().x + 22 + rect_buff_frame_1.right, this->GetPos().y + 80);

    m_custom_label_skilllist = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_buff_frame_title_2,GDR_GXVSRO_FRAME_BUFF_TITLE,1);
    m_custom_label_skilllist -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_BUFF_SKILL_LIST"));
    m_custom_label_skilllist->BringToFront();

    statics16 = (CIFFrame *) CreateInstance(this,
                                            GFX_RUNTIME_CLASS(CIFFrame),
                                            rect_buff_frame_3,
                                            GDR_GXVSRO_FRAME_BUFF_SKILLBUFFED_LIST,
                                            1);
    statics16->TB_Func_13("interface\\option\\opt_inner_box_", 1, 1);
    statics16->MoveGWnd(this->GetPos().x + 22 + rect_buff_frame_1.right + rect_buff_frame_2.right, this->GetPos().y + 80);

    m_custom_label_skillbuffedlist = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_buff_frame_title_3,GDR_GXVSRO_FRAME_BUFF_TITLE,1);
    m_custom_label_skillbuffedlist -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_BUFF_BUFFED_LIST"));
    m_custom_label_skillbuffedlist->BringToFront();

    RECT rect_Slot12_lable = {10,45,46,46};

    statics12 = (CIFFrame *) CreateInstance(this,
                                            GFX_RUNTIME_CLASS(CIFFrame),
                                            rect_Slot12_lable,
                                            GDR_GXVSRO_FRAME_PET_POTION,
                                            1);
    statics12->TB_Func_13("interface\\option\\opt_inner_box_", 1, 1);
    statics12->SetGWndSize(this->GetSize().width - 42, this->GetSize().height - 324);
    statics12->MoveGWnd(this->GetPos().x + 22, this->GetPos().y + 268);

    RECT rect_m_custom_label_fellowpet ={rect_Slot11_lable.left + 250,
                      rect_Slot11_lable.top + 26,
                      rect_Slot11_lable.right - 12,
                      rect_Slot11_lable.bottom - 12};
    m_custom_label_fellowpet = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_label_fellowpet,GDR_GXVSRO_EDIT_MP,1);
    m_custom_label_fellowpet->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_PET_FELLOW"));

    RECT rect_m_custom_label_tradepet ={rect_Slot11_lable.left + 250,
                                         rect_Slot11_lable.top + 214,
                                         rect_Slot11_lable.right - 12,
                                         rect_Slot11_lable.bottom - 12};
    m_custom_label_tradepet = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_custom_label_tradepet,GDR_GXVSRO_EDIT_MP,1);
    m_custom_label_tradepet->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_PET_RIDDING"));
///////////////////////

    RECT rect_Slot1_lable = {30,100,46,46};

    statics = (CIFFrame *) CreateInstance(this,
                                                    GFX_RUNTIME_CLASS(CIFFrame),
                                                    rect_Slot1_lable,
                                                    GDR_GXVSRO_FRAME8,
                                                    1);
    statics->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot1 ={rect_Slot1_lable.left + 6,
                      rect_Slot1_lable.top + 6,
                      rect_Slot1_lable.right - 12,
                      rect_Slot1_lable.bottom - 12};

    m_slot1 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot1,
                                                        GDR_GXVSRO_SLOT1_POTION,
                                                        1);
    m_slot1->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);
/////////
    RECT rect_m_checkbox_hp =  {rect_Slot1_lable.left + 100,
                                rect_Slot1_lable.top + 5,
                                              16,
                                              16};
    m_checkbox_hp = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_hp, GDR_GXVSRO_CHECKBOX_HP, 0);

    RECT rect_m_edit_hp_box = {rect_Slot1_lable.left + 100,
                               rect_Slot1_lable.top + 24,
                               60,
                               20};
    m_edit_hp = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_edit_hp_box,GDR_GXVSRO_EDIT_HP,1);
    m_edit_hp->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);
    m_edit_hp->SetText(L"70");
    m_edit_hp->TB_Func_5(1);

    RECT rect_m_text_hp = {rect_Slot1_lable.left + 120,
                           rect_Slot1_lable.top + 6,
                           50,
                           15};
    m_text_hp = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_hp,GDR_GXVSRO_TEXT_POTION,1);
    m_text_hp -> SetText(L"HP");
    RECT rect_m_text_percent_hp = {rect_Slot1_lable.left + 145,
                           rect_Slot1_lable.top + 25,
                           50,
                           15};
    m_text_percent_hp = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_percent_hp,GDR_GXVSRO_TEXT_POTION,1);
    m_text_percent_hp -> SetText(L"%");

    RECT rect_m_Hp_Slider = {rect_Slot1_lable.left + 180,
                                   rect_Slot1_lable.top + 23,
                                   324,
                                   21};
    m_Hp_Slider = (CIFSliderCtrl *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSliderCtrl), rect_m_Hp_Slider, GDR_GXVSRO_HP_SLIDER, 1);
    m_Hp_Slider->TB_Func_13("interface\\recovery\\re_selectbar.ddj", 0, 1);
    m_Hp_Slider->SetSliderTexture("interface\\ifcommon\\com_qst_lefttarrow_button.ddj",
                                      "interface\\ifcommon\\com_qst_rightarrow_button.ddj",
                                      "interface\\ifcommon\\com_scroll_button.ddj");
    m_Hp_Slider->FUN_006596f0(0, 0, 303, 0, 20, 2);
    m_Hp_Slider->SetMaxButtonSlide(267);
    m_Hp_Slider->FUN_006599e0(1, 100, 1, 1);
    m_Hp_Slider->BringToFront();

/////////
    RECT rect_m_checkbox_pet_hp =  {rect_Slot1_lable.left + 100,
                                rect_Slot1_lable.top + 5,
                                16,
                                16};
    m_checkbox_pet_hp = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_pet_hp, GDR_GXVSRO_CHECKBOX_PET_HP, 0);

    RECT rect_m_edit_pet_hp_box = {rect_Slot1_lable.left + 100,
                               rect_Slot1_lable.top + 24,
                               60,
                               20};
    m_edit_pet_hp = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_edit_pet_hp_box,GDR_GXVSRO_EDIT_PET_HP,1);
    m_edit_pet_hp->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);
    m_edit_pet_hp->SetText(L"70");
    m_edit_pet_hp->TB_Func_5(1);

    RECT rect_m_text_pet_hp = {rect_Slot1_lable.left + 120,
                           rect_Slot1_lable.top + 6,
                           50,
                           15};
    m_text_pet_hp = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_pet_hp,GDR_GXVSRO_TEXT_POTION,1);
    m_text_pet_hp -> SetText(L"HP");
    RECT rect_m_text_pet_percent_hp = {rect_Slot1_lable.left + 145,
                                   rect_Slot1_lable.top + 25,
                                   50,
                                   15};
    m_text_pet_percent_hp = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_pet_percent_hp,GDR_GXVSRO_TEXT_POTION,1);
    m_text_pet_percent_hp -> SetText(L"%");

    RECT rect_m_Pet_Hp_Slider = {rect_Slot1_lable.left + 180,
                             rect_Slot1_lable.top + 23,
                             324,
                             21};
    m_Pet_HP_Slider = (CIFSliderCtrl *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSliderCtrl), rect_m_Pet_Hp_Slider, GDR_GXVSRO_PET_HP_SLIDER, 1);
    m_Pet_HP_Slider->TB_Func_13("interface\\recovery\\re_selectbar.ddj", 0, 1);
    m_Pet_HP_Slider->SetSliderTexture("interface\\ifcommon\\com_qst_lefttarrow_button.ddj",
                                  "interface\\ifcommon\\com_qst_rightarrow_button.ddj",
                                  "interface\\ifcommon\\com_scroll_button.ddj");
    m_Pet_HP_Slider->FUN_006596f0(0, 0, 303, 0, 20, 2);
    m_Pet_HP_Slider->SetMaxButtonSlide(267);
    m_Pet_HP_Slider->FUN_006599e0(1, 100, 1, 1);
    m_Pet_HP_Slider->BringToFront();
////////
    RECT rect_Slot1_lable2 = {30,155,46,46};

    statics2 = (CIFFrame *) CreateInstance(this,
                                                     GFX_RUNTIME_CLASS(CIFFrame),
                                                     rect_Slot1_lable2,
                                                     GDR_GXVSRO_FRAME8,
                                                     1);
    statics2->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot2 ={rect_Slot1_lable2.left + 6,
                      rect_Slot1_lable2.top + 6,
                      rect_Slot1_lable2.right - 12,
                      rect_Slot1_lable2.bottom - 12};
    //RECT rect_button = {35, 70, 140, 30};
    m_slot2 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot2,
                                                        GDR_GXVSRO_SLOT2_POTION,
                                                        1);
    m_slot2->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);

    RECT rect_Slot6_lable = {30,100,46,46};

    statics6 = (CIFFrame *) CreateInstance(this,
                                           GFX_RUNTIME_CLASS(CIFFrame),
                                           rect_Slot6_lable,
                                           GDR_GXVSRO_FRAME_PET_HP,
                                           1);
    statics6->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot6 ={rect_Slot6_lable.left + 6,
                      rect_Slot6_lable.top + 6,
                      rect_Slot6_lable.right - 12,
                      rect_Slot6_lable.bottom - 12};
    //RECT rect_button = {35, 70, 140, 30};
    m_slot6 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot6,
                                                        GDR_GXVSRO_SLOT6_PET_POTION,
                                                        1);
    m_slot6->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);
    /////////
    RECT rect_m_checkbox_mp =  {rect_Slot1_lable2.left + 100,
                                rect_Slot1_lable2.top + 5,
                                16,
                                16};
    m_checkbox_mp = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_mp, GDR_GXVSRO_CHECKBOX_MP, 0);

    RECT rect_m_edit_mp_box = {rect_Slot1_lable2.left + 100,
                               rect_Slot1_lable2.top + 24,
                               60,
                               20};
    m_edit_mp = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_edit_mp_box,GDR_GXVSRO_EDIT_MP,1);
    m_edit_mp->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);
    m_edit_mp->SetText(L"70");
    m_edit_mp->TB_Func_5(1);

    RECT rect_m_text_mp = {rect_Slot1_lable2.left + 120,
                           rect_Slot1_lable2.top + 6,
                           50,
                           15};
    m_text_mp = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_mp,GDR_GXVSRO_TEXT_POTION,1);
    m_text_mp -> SetText(L"MP");
    RECT rect_m_text_percent_mp = {rect_Slot1_lable2.left + 145,
                                   rect_Slot1_lable2.top + 25,
                                   50,
                                   15};
    m_text_percent_mp = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_percent_mp,GDR_GXVSRO_TEXT_POTION,1);
    m_text_percent_mp -> SetText(L"%");

    RECT rect_m_Mp_Slider = {rect_Slot1_lable2.left + 180,
                             rect_Slot1_lable2.top + 23,
                             324,
                             21};
    m_Mp_Slider = (CIFSliderCtrl *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSliderCtrl), rect_m_Mp_Slider, GDR_GXVSRO_MP_SLIDER, 1);
    m_Mp_Slider->TB_Func_13("interface\\recovery\\re_selectbar.ddj", 0, 1);
    m_Mp_Slider->SetSliderTexture("interface\\ifcommon\\com_qst_lefttarrow_button.ddj",
                                  "interface\\ifcommon\\com_qst_rightarrow_button.ddj",
                                  "interface\\ifcommon\\com_scroll_button.ddj");
    m_Mp_Slider->FUN_006596f0(0, 0, 303, 0, 20, 2);
    m_Mp_Slider->SetMaxButtonSlide(267);
    m_Mp_Slider->FUN_006599e0(1, 100, 1, 1);
    m_Mp_Slider->BringToFront();
/////////
    RECT rect_m_checkbox_pet_hgp =  {rect_Slot1_lable2.left + 100,
                                rect_Slot1_lable2.top + 5,
                                16,
                                16};
    m_checkbox_pet_hgp = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_pet_hgp, GDR_GXVSRO_CHECKBOX_PET_HGP, 0);

    RECT rect_m_edit_pet_hgp_box = {rect_Slot1_lable2.left + 100,
                               rect_Slot1_lable2.top + 24,
                               60,
                               20};
    m_edit_pet_hgp = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_edit_pet_hgp_box,GDR_GXVSRO_EDIT_PET_HGP,1);
    m_edit_pet_hgp->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);
    m_edit_pet_hgp->SetText(L"70");
    m_edit_pet_hgp->TB_Func_5(1);

    RECT rect_m_text_pet_hgp = {rect_Slot1_lable2.left + 120,
                           rect_Slot1_lable2.top + 6,
                           50,
                           15};
    m_text_pet_hgp = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_pet_hgp,GDR_GXVSRO_TEXT_POTION,1);
    m_text_pet_hgp -> SetText(L"HGP");
    RECT rect_m_text_pet_percent_hgp = {rect_Slot1_lable2.left + 145,
                                   rect_Slot1_lable2.top + 25,
                                   50,
                                   15};
    m_text_pet_percent_hgp = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_pet_percent_hgp,GDR_GXVSRO_TEXT_POTION,1);
    m_text_pet_percent_hgp -> SetText(L"%");

    RECT rect_m_Pet_Hgp_Slider = {rect_Slot1_lable2.left + 180,
                             rect_Slot1_lable2.top + 23,
                             324,
                             21};
    m_Pet_HGP_Slider = (CIFSliderCtrl *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSliderCtrl), rect_m_Pet_Hgp_Slider, GDR_GXVSRO_PET_HGP_SLIDER, 1);
    m_Pet_HGP_Slider->TB_Func_13("interface\\recovery\\re_selectbar.ddj", 0, 1);
    m_Pet_HGP_Slider->SetSliderTexture("interface\\ifcommon\\com_qst_lefttarrow_button.ddj",
                                  "interface\\ifcommon\\com_qst_rightarrow_button.ddj",
                                  "interface\\ifcommon\\com_scroll_button.ddj");
    m_Pet_HGP_Slider->FUN_006596f0(0, 0, 303, 0, 20, 2);
    m_Pet_HGP_Slider->SetMaxButtonSlide(267);
    m_Pet_HGP_Slider->FUN_006599e0(1, 100, 1, 1);
    m_Pet_HGP_Slider->BringToFront();

    /////////
    RECT rect_Slot13_lable = {30,300,46,46};

    statics13 = (CIFFrame *) CreateInstance(this,
                                           GFX_RUNTIME_CLASS(CIFFrame),
                                            rect_Slot13_lable,
                                           GDR_GXVSRO_FRAME8,
                                           1);
    statics13->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot13 ={rect_Slot13_lable.left + 6,
                       rect_Slot13_lable.top + 6,
                       rect_Slot13_lable.right - 12,
                       rect_Slot13_lable.bottom - 12};
    //RECT rect_button = {35, 70, 140, 30};
    m_slot11 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot13,
                                                         GDR_GXVSRO_SLOT11_PET_POTION,
                                                        1);
    m_slot11->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);

    RECT rect_m_checkbox_pet_trade =  {rect_Slot13_lable.left + 100,
                                       rect_Slot13_lable.top + 5,
                                     16,
                                     16};
    m_checkbox_pet_trade = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_pet_trade, GDR_GXVSRO_CHECKBOX_PET_TRADE, 0);

    RECT rect_m_checkbox_pet_ridding =  {rect_Slot13_lable.left + 250,
                                       rect_Slot13_lable.top + 5,
                                       16,
                                       16};
    m_checkbox_pet_ridding = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_pet_ridding, GDR_GXVSRO_CHECKBOX_PET_RIDDING, 0);

    RECT rect_m_edit_pet_trade_box = {rect_Slot13_lable.left + 100,
                                      rect_Slot13_lable.top + 24,
                                    60,
                                    20};
    m_edit_pet_trade_and_ridding = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_edit_pet_trade_box,GDR_GXVSRO_EDIT_PET_TRADE_RIDDING,1);
    m_edit_pet_trade_and_ridding->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);
    m_edit_pet_trade_and_ridding->SetText(L"70");
    m_edit_pet_trade_and_ridding->TB_Func_5(1);

    RECT rect_m_text_pet_trade = {rect_Slot13_lable.left + 140,
                                              rect_Slot13_lable.top + 6,
                                50,
                                15};
    m_text_pet_hp_trade = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_pet_trade,GDR_GXVSRO_TEXT_POTION,1);
    m_text_pet_hp_trade -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_PET_TRANS_HP"));
    m_text_pet_hp_trade->TB_Func_5(1);
    RECT rect_m_text_pet_ridding = {rect_Slot13_lable.left + 290,
                                              rect_Slot13_lable.top + 6,
                                              50,
                                              15};
    m_text_pet_hp_ridding = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_pet_ridding,GDR_GXVSRO_TEXT_POTION,1);
    m_text_pet_hp_ridding -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_PET_RIDDING_HP"));
    m_text_pet_hp_ridding->TB_Func_5(1);

    RECT rect_m_text_pet_trade_and_ridding_percent_hp = {rect_Slot13_lable.left + 145,
                                                         rect_Slot13_lable.top + 25,
                                        50,
                                        15};
    m_text_pet_percent_hp_2 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_pet_trade_and_ridding_percent_hp,GDR_GXVSRO_TEXT_POTION,1);
    m_text_pet_percent_hp_2 -> SetText(L"%");

    RECT rect_m_Pet_trade_and_ridding_Hp_Slider = {rect_Slot13_lable.left + 180,
                                                   rect_Slot13_lable.top + 23,
                                  324,
                                  21};
    m_Pet_Trade_And_Ridding_HP_Slider = (CIFSliderCtrl *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSliderCtrl), rect_m_Pet_trade_and_ridding_Hp_Slider, GDR_GXVSRO_PET_TRADE_RIDDING_SLIDER, 1);
    m_Pet_Trade_And_Ridding_HP_Slider->TB_Func_13("interface\\recovery\\re_selectbar.ddj", 0, 1);
    m_Pet_Trade_And_Ridding_HP_Slider->SetSliderTexture("interface\\ifcommon\\com_qst_lefttarrow_button.ddj",
                                       "interface\\ifcommon\\com_qst_rightarrow_button.ddj",
                                       "interface\\ifcommon\\com_scroll_button.ddj");
    m_Pet_Trade_And_Ridding_HP_Slider->FUN_006596f0(0, 0, 303, 0, 20, 2);
    m_Pet_Trade_And_Ridding_HP_Slider->SetMaxButtonSlide(267);
    m_Pet_Trade_And_Ridding_HP_Slider->FUN_006599e0(1, 100, 1, 1);
    m_Pet_Trade_And_Ridding_HP_Slider->BringToFront();
////////

    RECT rect_Slot1_lable3 = {30,265,46,46};

    statics3 = (CIFFrame *) CreateInstance(this,
                                                     GFX_RUNTIME_CLASS(CIFFrame),
                                                     rect_Slot1_lable3,
                                                     GDR_GXVSRO_FRAME8,
                                                     1);
    statics3->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot3 ={rect_Slot1_lable3.left + 6,
                      rect_Slot1_lable3.top + 6,
                      rect_Slot1_lable3.right - 12,
                      rect_Slot1_lable3.bottom - 12};

    m_slot3 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot3,
                                                        GDR_GXVSRO_SLOT3_POTION,
                                                        1);
    m_slot3->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);

    RECT rect_Slot7_lable = {30,155,46,46};

    statics7 = (CIFFrame *) CreateInstance(this,
                                           GFX_RUNTIME_CLASS(CIFFrame),
                                           rect_Slot7_lable,
                                           GDR_GXVSRO_FRAME_PET_HGP,
                                           1);
    statics7->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot7 ={rect_Slot7_lable.left + 6,
                      rect_Slot7_lable.top + 6,
                      rect_Slot7_lable.right - 12,
                      rect_Slot7_lable.bottom - 12};

    m_slot7 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot7,
                                                        GDR_GXVSRO_SLOT7_PET_POTION,
                                                        1);
    m_slot7->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);
/////////
    RECT rect_m_checkbox_abnormal =  {rect_Slot1_lable3.left + 100,
                                      rect_Slot1_lable3.top + 11,
                                16,
                                16};
    m_checkbox_abnormal = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_abnormal, GDR_GXVSRO_CHECKBOX_ABNORMAL, 0);

    RECT rect_m_text_abnormal = {rect_Slot1_lable3.left + 120,
                                 rect_Slot1_lable3.top + 12,
                           50,
                           15};
    m_text_abnormal = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_abnormal,GDR_GXVSRO_TEXT_POTION,1);
    m_text_abnormal -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_POTION_ABNORMAL"));
    m_text_abnormal ->TB_Func_5(0);
    /////////////
    RECT rect_Slot1_lable5 = {300,265,46,46};

    statics5 = (CIFFrame *) CreateInstance(this,
                                           GFX_RUNTIME_CLASS(CIFFrame),
                                           rect_Slot1_lable5,
                                           GDR_GXVSRO_FRAME8,
                                           1);
    statics5->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot5 ={rect_Slot1_lable5.left + 6,
                      rect_Slot1_lable5.top + 6,
                      rect_Slot1_lable5.right - 12,
                      rect_Slot1_lable5.bottom - 12};

    m_slot5 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot5,
                                                        GDR_GXVSRO_SLOT5_POTION,
                                                        1);
    m_slot5->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);

    RECT rect_m_checkbox_speed =  {rect_Slot1_lable5.left + 80,
                                   rect_Slot1_lable5.top + 11,
                                      16,
                                      16};
    m_checkbox_speedscroll = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_speed, GDR_GXVSRO_CHECKBOX_SPEEDSCROLL, 0);

    RECT rect_m_text_speedscroll = {rect_Slot1_lable5.left + 100,
                                    rect_Slot1_lable5.top + 12,
                                 50,
                                 15};
    m_text_speedscroll = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_speedscroll,GDR_GXVSRO_TEXT_POTION,1);
    m_text_speedscroll -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_USE_SPEED_SCROLL"));
    m_text_speedscroll ->TB_Func_5(0);
    //////////////
    /////////////
    RECT rect_Slot8_lable = {30,210,46,46};

    statics8 = (CIFFrame *) CreateInstance(this,
                                           GFX_RUNTIME_CLASS(CIFFrame),
                                           rect_Slot8_lable,
                                           GDR_GXVSRO_FRAME_PET_CURE,
                                           1);
    statics8->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot8 ={rect_Slot8_lable.left + 6,
                      rect_Slot8_lable.top + 6,
                      rect_Slot8_lable.right - 12,
                      rect_Slot8_lable.bottom - 12};

    m_slot8 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot8,
                                                        GDR_GXVSRO_SLOT8_PET_POTION,
                                                        1);
    m_slot8->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);

    RECT rect_m_checkbox_pet_cure =  {rect_Slot8_lable.left + 70,
                                      rect_Slot8_lable.top + 21,
                                   16,
                                   16};
    m_checkbox_pet_cure = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_pet_cure, GDR_GXVSRO_CHECKBOX_PET_CURE, 0);

    RECT rect_m_text_pet_cure = {rect_Slot8_lable.left + 90,
                                 rect_Slot8_lable.top + 22,
                                    50,
                                    15};
    m_text_pet_cure = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_pet_cure,GDR_GXVSRO_TEXT_POTION,1);
    m_text_pet_cure -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_POTION_ABNORMAL"));
    m_text_pet_cure ->TB_Func_5(0);

    /////////////
    RECT rect_Slot9_lable = {210,210,46,46};

    statics9 = (CIFFrame *) CreateInstance(this,
                                           GFX_RUNTIME_CLASS(CIFFrame),
                                           rect_Slot9_lable,
                                           GDR_GXVSRO_FRAME_PET_RESURRECT,
                                           1);
    statics9->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot9 ={rect_Slot9_lable.left + 6,
                      rect_Slot9_lable.top + 6,
                      rect_Slot9_lable.right - 12,
                      rect_Slot9_lable.bottom - 12};

    m_slot9 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot9,
                                                        GDR_GXVSRO_SLOT9_PET_POTION,
                                                        1);
    m_slot9->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);

    RECT rect_m_checkbox_pet_resurrect =  {rect_Slot9_lable.left + 70,
                                           rect_Slot9_lable.top + 21,
                                      16,
                                      16};
    m_checkbox_pet_resurrect = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_pet_resurrect, GDR_GXVSRO_CHECKBOX_PET_RESURRECT, 0);

    RECT rect_m_text_pet_resurrect = {rect_Slot9_lable.left + 90,
                                      rect_Slot9_lable.top + 22,
                                 50,
                                 15};
    m_text_pet_resurrect = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_pet_resurrect,GDR_GXVSRO_TEXT_POTION,1);
    m_text_pet_resurrect -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_PET_RESURRECT"));
    m_text_pet_resurrect ->TB_Func_5(0);
    /////////////
    RECT rect_Slot10_lable = {380,210,46,46};

    statics10 = (CIFFrame *) CreateInstance(this,
                                           GFX_RUNTIME_CLASS(CIFFrame),
                                            rect_Slot10_lable,
                                           GDR_GXVSRO_FRAME_PET_TRIGGER,
                                           1);
    statics10->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot10 ={rect_Slot10_lable.left + 6,
                       rect_Slot10_lable.top + 6,
                       rect_Slot10_lable.right - 12,
                       rect_Slot10_lable.bottom - 12};

    m_slot10 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot10,
                                                        GDR_GXVSRO_SLOT10_PET_POTION,
                                                        1);
    m_slot10->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);

    RECT rect_m_checkbox_pet_trigger =  {rect_Slot10_lable.left + 70,
                                         rect_Slot10_lable.top + 21,
                                           16,
                                           16};
    m_checkbox_pet_trigger = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_pet_trigger, GDR_GXVSRO_CHECKBOX_PET_TRIGGER, 0);

    RECT rect_m_text_pet_trigger = {rect_Slot10_lable.left + 90,
                                      rect_Slot10_lable.top + 22,
                                      50,
                                      15};
    m_text_pet_trigger = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_pet_trigger,GDR_GXVSRO_TEXT_POTION,1);
    m_text_pet_trigger -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_PET_TRIGGER"));
    m_text_pet_trigger ->TB_Func_5(0);
    /////////////
    RECT rect_Slot1_lable4 = {30,210,46,46};

    statics4 = (CIFFrame *) CreateInstance(this,
                                           GFX_RUNTIME_CLASS(CIFFrame),
                                           rect_Slot1_lable4,
                                           GDR_GXVSRO_FRAME8,
                                           1);
    statics4->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot4 ={rect_Slot1_lable4.left + 6,
                      rect_Slot1_lable4.top + 6,
                      rect_Slot1_lable4.right - 12,
                      rect_Slot1_lable4.bottom - 12};

    m_slot4 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot4,
                                                        GDR_GXVSRO_SLOT4_POTION,
                                                        1);
    m_slot4->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);

    /////////
    RECT rect_m_checkbox_vigor =  {rect_Slot1_lable4.left + 100,
                                   rect_Slot1_lable4.top + 5,
                                16,
                                16};
    m_checkbox_vigor = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_checkbox_vigor, GDR_GXVSRO_CHECKBOX_VIGOR, 0);

    RECT rect_m_edit_vigor_box = {rect_Slot1_lable4.left + 100,
                                  rect_Slot1_lable4.top + 24,
                               60,
                               20};
    m_edit_vigor = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_edit_vigor_box,GDR_GXVSRO_EDIT_VIGOR,1);
    m_edit_vigor->TB_Func_13("interface\\ifcommon\\com_grad_gage_form.ddj", 1, 1);
    m_edit_vigor->SetText(L"70");
    m_edit_vigor->TB_Func_5(1);

    RECT rect_m_text_vigor = {rect_Slot1_lable4.left + 120,
                           rect_Slot1_lable4.top + 6,
                           50,
                           15};
    m_text_vigor = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_vigor,GDR_GXVSRO_TEXT_POTION,1);
    m_text_vigor -> SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_POTION_VIGOR"));
    RECT rect_m_text_percent_vigor = {rect_Slot1_lable4.left + 145,
                                   rect_Slot1_lable4.top + 25,
                                   50,
                                   15};
    m_text_percent_vigor = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_text_percent_vigor,GDR_GXVSRO_TEXT_POTION,1);
    m_text_percent_vigor -> SetText(L"%");

    RECT rect_m_vigor_Slider = {rect_Slot1_lable4.left + 180,
                             rect_Slot1_lable4.top + 23,
                             324,
                             21};
    m_Vigor_Slider = (CIFSliderCtrl *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSliderCtrl), rect_m_vigor_Slider, GDR_GXVSRO_VIGOR_SLIDER, 1);
    m_Vigor_Slider->TB_Func_13("interface\\recovery\\re_selectbar.ddj", 0, 1);
    m_Vigor_Slider->SetSliderTexture("interface\\ifcommon\\com_qst_lefttarrow_button.ddj",
                                  "interface\\ifcommon\\com_qst_rightarrow_button.ddj",
                                  "interface\\ifcommon\\com_scroll_button.ddj");
    m_Vigor_Slider->FUN_006596f0(0, 0, 303, 0, 20, 2);
    m_Vigor_Slider->SetMaxButtonSlide(267);
    m_Vigor_Slider->FUN_006599e0(1, 100, 1, 1);
    m_Vigor_Slider->BringToFront();
    ////////// tooltip3
    RECT rect_m_tooltip_lable3 = {150,330,200,10};
    m_custom_label_tooltip3 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFStatic),
                                                                  rect_m_tooltip_lable3,
                                                                  GDR_GXVSRO_TEXT_POTION_TOOLTIP,
                                                                  1);
    wchar_t buffer10[255];
    swprintf_s(buffer10, TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_POTION_TOOLTIP"));
    m_custom_label_tooltip3 ->SetText(buffer10);
    m_custom_label_tooltip3 ->TB_Func_5(0);
    m_custom_label_tooltip3->m_FontTexture.SetColor(0xFFF18706);
    ////////////

    RECT rect_bg1 ={Framerect.left + 20,
                    Framerect.top + 33,
                    Framerect.right - 300,
                    28};
    RECT rect_bg2 ={Framerect.left + 40 + 120,
                    Framerect.top + 33,
                    Framerect.right - 30,
                    28};
    RECT rect_bg3 ={Framerect.left + 352,
                    Framerect.top + 33,
                    Framerect.right - 30,
                    28};
    RECT Spinect = { 238,333,50,16 };


    m_partymember_slot1 = (CIFSTMacroAutoBuffSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSlotList), rect_bg1, 611, 0);
    m_mySkill_slot1 = (CIFSTMacroAutoBuffSkillSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSkillSlotList), rect_bg2, 612, 0);
    m_mySkill_slot2 = (CIFSTMacroAutoBuffSkillSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSkillSlotList), rect_bg2, 613, 0);
    m_mySkill_slot3 = (CIFSTMacroAutoBuffSkillSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSkillSlotList), rect_bg2, 614, 0);
    m_mySkill_slot4 = (CIFSTMacroAutoBuffSkillSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSkillSlotList), rect_bg2, 615, 0);
    m_mySkill_slot5 = (CIFSTMacroAutoBuffSkillSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSkillSlotList), rect_bg2, 616, 0);
    m_mySkill_slot6 = (CIFSTMacroAutoBuffSkillSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSkillSlotList), rect_bg2, 617, 0);
    m_mySkill_slot7 = (CIFSTMacroAutoBuffSkillSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSkillSlotList), rect_bg2, 618, 0);
    m_mySkill_slot8 = (CIFSTMacroAutoBuffSkillSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSkillSlotList), rect_bg2, 619, 0);
    m_mySkill_slot9 = (CIFSTMacroAutoBuffSkillSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSkillSlotList), rect_bg2, 620, 0);
    m_mySkill_slot10 = (CIFSTMacroAutoBuffSkillSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSkillSlotList), rect_bg2, 621, 0);

    m_SkillBuffed_slot1 = (CIFSTMacroAutoBuffedSkillSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffedSkillSlotList), rect_bg3, 613, 0);

    m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), Spinect, 622, 0);
    ////////////////
    RECT TexboxRect = {0,0,40,99};
    m_custom_textbox_range = (CIFTextBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFTextBox), TexboxRect, GDR_GXVSRO_TEXTBOX1, 0);
    m_custom_textbox_range->MoveGWnd(Frame2->GetPos().x+63,Frame2->GetPos().y+1);
    m_custom_textbox_range->TB_Func_5(0); //can le
    wchar_t buffer[255];
    swprintf(buffer, L"10m", 0);
    std::n_wstring strmsg(buffer);
    m_custom_textbox_range->sub_64F8A0(strmsg, 0, D3DCOLOR_RGBA(255, 255, 0, 0), D3DCOLOR_RGBA(255, 255, 0, 0), -1, 0, 0);
    wchar_t buffer1[255];
    swprintf(buffer1, L"30m", 0);
    std::n_wstring strmsg1(buffer1);
    m_custom_textbox_range->sub_64F8A0(strmsg1, 0, D3DCOLOR_RGBA(255, 255, 0, 0), D3DCOLOR_RGBA(255, 255, 0, 0), -1, 0, 0);
    wchar_t buffer2[255];
    swprintf(buffer2, L"50m", 0);
    std::n_wstring strmsg2(buffer2);
    m_custom_textbox_range->sub_64F8A0(strmsg2, 0, D3DCOLOR_RGBA(255, 255, 0, 0), D3DCOLOR_RGBA(255, 255, 0, 0), -1, 0, 0);
    wchar_t buffer3[255];
    swprintf(buffer3, L"70m", 0);
    std::n_wstring strmsg3(buffer3);
    m_custom_textbox_range->sub_64F8A0(strmsg3, 0, D3DCOLOR_RGBA(255, 255, 0, 0), D3DCOLOR_RGBA(255, 255, 0, 0), -1, 0, 0);
    wchar_t buffer4[255];
    swprintf(buffer4, L"100m", 0);
    std::n_wstring strmsg4(buffer4);
    m_custom_textbox_range->sub_64F8A0(strmsg4, 0, D3DCOLOR_RGBA(255, 255, 0, 0), D3DCOLOR_RGBA(255, 255, 0, 0), -1, 0, 0);
    m_custom_textbox_range->N00000608 = this;
    //m_textbox[i].ShowGWnd(true);
    m_custom_textbox_range->m_LinesOfHistory = 3;

    m_custom_textbox_range->m_HeightInLines = 10;
    m_custom_textbox_range->SetLineHeight(20);
    m_custom_textbox_range->sub_638B50(0);
    m_custom_textbox_range->sub_64E380(1);
    m_custom_textbox_range->sub_638C70(1);
    m_custom_textbox_range->SetHightlineLine(true);
    m_custom_textbox_range->sub_638D50(1);
    m_custom_textbox_range->SetHighlightColor(D3DCOLOR_RGBA(255, 255, 255, 102));
    m_custom_textbox_range->sub_638D40(1);
    m_custom_textbox_range->Func_01(0);
    OnListSelectRangeState(false);
    m_mybutton->BringToFront();
 //////////
    m_pTabs = new CIFSelectableArea * [numberOfTabs];

    for (int i = 0; i < numberOfTabs; i++) {

        RECT selectable_area_size;
        selectable_area_size.top = 0;
        selectable_area_size.left = tabMarginLeft + tabWidth * i;
        selectable_area_size.right = tabWidth + 1;
        selectable_area_size.bottom = tabHeight;

        m_pTabs[i] = (CIFSelectableArea*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSelectableArea),
                                                               selectable_area_size, tabFirstId + i, 0);
        m_pTabs[i]->SetFont(this->N00009C2F);

        m_pTabs[i]->sub_64CE30("interface\\ifcommon\\com_long_tab_on.ddj",
                               "interface\\ifcommon\\com_long_tab_off.ddj", "interface\\ifcommon\\com_long_tab_disable.ddj");

        switch (i) {
            case 0:
                m_pTabs[0]->MoveGWnd(Frame->GetPos().x + 10, GetPos().y + 41);
                m_pTabs[0]->sub_64CC30(1);
                break;
            case 1:
                m_pTabs[1]->MoveGWnd(m_pTabs[0]->GetPos().x + m_pTabs[0]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[1]->sub_64CC30(0);
                break;
            case 2:
                m_pTabs[2]->MoveGWnd(m_pTabs[1]->GetPos().x + m_pTabs[1]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[2]->sub_64CC30(0);
                break;
            case 3:
                m_pTabs[3]->MoveGWnd(m_pTabs[2]->GetPos().x + m_pTabs[2]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[3]->sub_64CC30(0);
                break;
            case 4:
                m_pTabs[4]->MoveGWnd(m_pTabs[3]->GetPos().x + m_pTabs[3]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[4]->sub_64CC30(0);
                break;
            case 5:
                m_pTabs[5]->MoveGWnd(m_pTabs[4]->GetPos().x + m_pTabs[4]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[5]->sub_64CC30(0);
                break;
        }
    }

    m_pTabs[0]->SetText(L"Auto Hunt");//--
    m_pTabs[1]->SetText(L"Auto Potion");
    m_pTabs[2]->SetText(L"Pet");
    m_pTabs[3]->SetText(L"Buff");

    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    HP_ID = 0;
    MP_ID = 0;
    VIGOR_ID = 0;
    ABNORMAL_ID = 0;
    SPEEDITEM_ID = 0;
    PET_HP_ID = 0;
    PET_HGP_ID = 0;
    PET_CURE_ID = 0;
    PET_RESURRECT_ID = 0;
    PET_TRIGGER_ID = 0;

    m_checkbox_hp->FUN_00656d50(0);
    m_checkbox_mp->FUN_00656d50(0);
    m_checkbox_vigor->FUN_00656d50(0);
    m_checkbox_abnormal->FUN_00656d50(0);
    m_checkbox_speedscroll->FUN_00656d50(0);
    m_checkbox_pet_trade->FUN_00656d50(0);
    m_checkbox_pet_ridding->FUN_00656d50(0);
/*    m_slot1->Type = 12;
    m_slot2->Type = 12;
    m_slot3->Type = 12;
    m_slot4->Type = 12;*/
    HideLists();
    m_spin->SetMinValue(1);
    m_spin->SetCurrentValue(1);
    m_spin->SetMaxValue(10);
    //m_spin->MoveGWnd(m_spin->GetPos().x-30, m_spin->GetPos().y + 8);

    m_mySkill_slot1->ShowGWnd(true);
    this->ShowGWnd(false);
    ResetPosition();
    return true;
}
void CIFSTMacroAutoHunt::OnUpdate()
{
     if(IsAutoHPChecked())
     {
         m_Hp_Slider->SetEnabledState(1);
         int m_hp_percent = (((float)m_Hp_Slider->m_SliderCurrentVol / (float)m_Hp_Slider->m_SliderMaxVol) * 100);
         wchar_t buffer1[80];
         swprintf_s(buffer1, L"%d" ,m_hp_percent );
         m_edit_hp -> SetText(buffer1);
     }
     else
         m_Hp_Slider->SetEnabledState(0);

    if(IsAutoMPChecked())
    {
        m_Mp_Slider->SetEnabledState(1);
        int m_mp_percent = (((float)m_Mp_Slider->m_SliderCurrentVol / (float)m_Mp_Slider->m_SliderMaxVol) * 100);
        wchar_t buffer1[80];
        swprintf_s(buffer1, L"%d" ,m_mp_percent );
        m_edit_mp -> SetText(buffer1);
    }
    else
        m_Mp_Slider->SetEnabledState(0);

    if(IsAutoVigorChecked())
    {
        m_Vigor_Slider->SetEnabledState(1);
        int m_vigor_percent = (((float)m_Vigor_Slider->m_SliderCurrentVol / (float)m_Vigor_Slider->m_SliderMaxVol) * 100);
        wchar_t buffer1[80];
        swprintf_s(buffer1, L"%d" ,m_vigor_percent );
        m_edit_vigor -> SetText(buffer1);
    }
    else
        m_Vigor_Slider->SetEnabledState(0);

    if(IsAutoPetHpChecked())
    {
        m_Pet_HP_Slider->SetEnabledState(1);
        int m_vigor_percent = (((float)m_Pet_HP_Slider->m_SliderCurrentVol / (float)m_Pet_HP_Slider->m_SliderMaxVol) * 100);
        wchar_t buffer1[80];
        swprintf_s(buffer1, L"%d" ,m_vigor_percent );
        m_edit_pet_hp -> SetText(buffer1);
    }
    else
        m_Pet_HP_Slider->SetEnabledState(0);

    if(IsAutoPetHgpChecked())
    {
        m_Pet_HGP_Slider->SetEnabledState(1);
        int m_vigor_percent = (((float)m_Pet_HGP_Slider->m_SliderCurrentVol / (float)m_Pet_HGP_Slider->m_SliderMaxVol) * 100);
        wchar_t buffer1[80];
        swprintf_s(buffer1, L"%d" ,m_vigor_percent );
        m_edit_pet_hgp -> SetText(buffer1);
    }
    else
        m_Pet_HGP_Slider->SetEnabledState(0);

    if(IsAutoPetTradeHPChecked() || IsAutoPetRiddingHPChecked())
    {
        m_Pet_Trade_And_Ridding_HP_Slider->SetEnabledState(1);
        int m_vigor_percent = (((float)m_Pet_Trade_And_Ridding_HP_Slider->m_SliderCurrentVol / (float)m_Pet_Trade_And_Ridding_HP_Slider->m_SliderMaxVol) * 100);
        wchar_t buffer1[80];
        swprintf_s(buffer1, L"%d" ,m_vigor_percent );
        m_edit_pet_trade_and_ridding -> SetText(buffer1);
    }
    else
        m_Pet_Trade_And_Ridding_HP_Slider->SetEnabledState(0);

    if(m_checkbox_pet_trade->GetCheckedState_MAYBE())
    {
        m_checkbox_pet_ridding->FUN_00656d50(0);
    }
    if(m_checkbox_pet_ridding->GetCheckedState_MAYBE())
    {
        m_checkbox_pet_trade->FUN_00656d50(0);
    }

    if (g_pCICPlayer) {

        //printf(" g_pCICPlayer->Status : %d \n",g_pCICPlayer->Status);
        const SPartyData &partyData = g_CCharacterDependentData.GetPartyData();
        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->Clear();
        CIFSTMacroAutoHunt::PartyMatchMemberList.clear();

        for (int i = 0; i < partyData.NumberOfMembers; ++i) {
            const SPartyMemberData &memberData = g_CCharacterDependentData.GetPartyMemberData(i);

            CIFSTMacroAutoHunt::PartyMatchMember Memeber = CIFSTMacroAutoHunt::PartyMatchMember();
            std::wstringstream Reg;
            Reg <<memberData.currentLevel;

            Memeber.LineNum = i;
            Memeber.Race = memberData.refobjID;
            Memeber.CharName =memberData.m_charactername.c_str();
            Memeber.LevelText = L"Lv";
            Memeber.Level = Reg.str().c_str();
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PartyMatchMemberList.push_back(Memeber);

            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->UpdatePartyMemberList();

        }


    }
}
bool CIFSTMacroAutoHunt::Func_28(int a1, int a2, int a3) {
    CIFSlotWithHelp *pDraggedSlot = (CIFSlotWithHelp *) a1;

    CSOItem *pDraagedSlotItem = g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(
            pDraggedSlot->GetSlotInInventory());
    if (pDraagedSlotItem)
    {

        std::list<int>::iterator hp = std::find(Rebot::Potion_ObjID_HP_Potion_List.begin(), Rebot::Potion_ObjID_HP_Potion_List.end(), pDraggedSlot->ItemInfo->GetItemData()->TID);
        std::list<int>::iterator mp = std::find(Rebot::Potion_ObjID_MP_Potion_List.begin(), Rebot::Potion_ObjID_MP_Potion_List.end(), pDraggedSlot->ItemInfo->GetItemData()->TID);
        std::list<int>::iterator vigor = std::find(Rebot::Potion_ObjID_Vigor_Potion_List.begin(), Rebot::Potion_ObjID_Vigor_Potion_List.end(), pDraggedSlot->ItemInfo->GetItemData()->TID);
        std::list<int>::iterator abnormal = std::find(Rebot::Potion_ObjID_Universal_Pill_List.begin(), Rebot::Potion_ObjID_Universal_Pill_List.end(), pDraggedSlot->ItemInfo->GetItemData()->TID);
        std::list<int>::iterator speed = std::find(Rebot::Speed_Scroll_ItemID.begin(), Rebot::Speed_Scroll_ItemID.end(), pDraggedSlot->ItemInfo->GetItemData()->m_id);

        std::list<int>::iterator pet_hp = std::find(Rebot::Potion_Pet_HP_Tid_List.begin(), Rebot::Potion_Pet_HP_Tid_List.end(), pDraggedSlot->ItemInfo->GetItemData()->TID);
        std::list<int>::iterator pet_hgp = std::find(Rebot::Potion_Pet_HGP_Tid_List.begin(), Rebot::Potion_Pet_HGP_Tid_List.end(), pDraggedSlot->ItemInfo->GetItemData()->TID);
        std::list<int>::iterator pet_cure = std::find(Rebot::Potion_Pet_Cure_List.begin(), Rebot::Potion_Pet_Cure_List.end(), pDraggedSlot->ItemInfo->GetItemData()->TID);
        std::list<int>::iterator pet_resurrect = std::find(Rebot::Potion_Pet_Resurrect_List.begin(), Rebot::Potion_Pet_Resurrect_List.end(), pDraggedSlot->ItemInfo->GetItemData()->TID);
        std::list<int>::iterator pet_trigger = std::find(Rebot::Potion_Pet_Summon_Trigger_List.begin(), Rebot::Potion_Pet_Summon_Trigger_List.end(), pDraggedSlot->ItemInfo->GetItemData()->TID);

        if(pet_hp != Rebot::Potion_Pet_HP_Tid_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot6->IsVisible() && (g_CurrentIfUnderCursor->UniqueID()==7786))
        {
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot6->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot6->FUN_006871d0(pDraggedSlot->ItemInfo);
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_HP_ID=pDraggedSlot->ItemInfo->GetItemData()->m_id;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_HP_SLOT =  pDraggedSlot->GetSlotInInventory();
        }
        if(pet_hp != Rebot::Potion_Pet_HP_Tid_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot11->IsVisible() && (g_CurrentIfUnderCursor->UniqueID()==7791))
        {
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot11->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot11->FUN_006871d0(pDraggedSlot->ItemInfo);
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_HP_RIDDING_TRADE_ID=pDraggedSlot->ItemInfo->GetItemData()->m_id;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_HP_RIDDING_TRADE_SLOT =  pDraggedSlot->GetSlotInInventory();
        }
        if(pet_hgp != Rebot::Potion_Pet_HGP_Tid_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot7->IsVisible() && g_CurrentIfUnderCursor->UniqueID()==7787)
        {
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot7->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot7->FUN_006871d0(pDraggedSlot->ItemInfo);
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_HGP_ID=pDraggedSlot->ItemInfo->GetItemData()->m_id;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_HGP_SLOT =  pDraggedSlot->GetSlotInInventory();
        }
        if(pet_cure != Rebot::Potion_Pet_Cure_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot8->IsVisible() && g_CurrentIfUnderCursor->UniqueID()==7788)
        {
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot8->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot8->FUN_006871d0(pDraggedSlot->ItemInfo);
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_CURE_ID=pDraggedSlot->ItemInfo->GetItemData()->m_id;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_CURE_SLOT =  pDraggedSlot->GetSlotInInventory();
        }
        if(pet_resurrect != Rebot::Potion_Pet_Resurrect_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot9->IsVisible() && g_CurrentIfUnderCursor->UniqueID()==7789)
        {
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot9->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot9->FUN_006871d0(pDraggedSlot->ItemInfo);
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_RESURRECT_ID=pDraggedSlot->ItemInfo->GetItemData()->m_id;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_RESURRECT_SLOT =  pDraggedSlot->GetSlotInInventory();
        }
        if(pet_trigger != Rebot::Potion_Pet_Summon_Trigger_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot10->IsVisible() && g_CurrentIfUnderCursor->UniqueID()==7790)
        {
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot10->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot10->FUN_006871d0(pDraggedSlot->ItemInfo);
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_TRIGGER_ID=pDraggedSlot->ItemInfo->GetItemData()->m_id;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_TRIGGER_SLOT =  pDraggedSlot->GetSlotInInventory();
        }

        if(hp != Rebot::Potion_ObjID_HP_Potion_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot1->IsVisible() && g_CurrentIfUnderCursor->UniqueID()==7781)
        {
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot1->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot1->FUN_006871d0(pDraggedSlot->ItemInfo);
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->HP_ID=pDraggedSlot->ItemInfo->GetItemData()->m_id;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->HP_SLOT =  pDraggedSlot->GetSlotInInventory();
        }
        if(mp != Rebot::Potion_ObjID_MP_Potion_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot2->IsVisible() && g_CurrentIfUnderCursor->UniqueID()==7782)
        {
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot2->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot2->FUN_006871d0(pDraggedSlot->ItemInfo);
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->MP_ID=pDraggedSlot->ItemInfo->GetItemData()->m_id;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->MP_SLOT =  pDraggedSlot->GetSlotInInventory();

        }
        if(vigor != Rebot::Potion_ObjID_Vigor_Potion_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot4->IsVisible() && g_CurrentIfUnderCursor->UniqueID()==7784)
        {
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot4->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot4->FUN_006871d0(pDraggedSlot->ItemInfo);
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->VIGOR_ID=pDraggedSlot->ItemInfo->GetItemData()->m_id;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->VIGOR_SLOT =  pDraggedSlot->GetSlotInInventory();
        }
        if(abnormal != Rebot::Potion_ObjID_Universal_Pill_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot3->IsVisible() && g_CurrentIfUnderCursor->UniqueID()==7783)
        {
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot3->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot3->FUN_006871d0(pDraggedSlot->ItemInfo);
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ABNORMAL_ID=pDraggedSlot->ItemInfo->GetItemData()->m_id;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ABNORMAL_SLOT =  pDraggedSlot->GetSlotInInventory();

        }
        if(speed != Rebot::Speed_Scroll_ItemID.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot5->IsVisible() && g_CurrentIfUnderCursor->UniqueID()==7785)
        {
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot5->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot5->FUN_006871d0(pDraggedSlot->ItemInfo);
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->SPEEDITEM_ID=pDraggedSlot->ItemInfo->GetItemData()->m_id;
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->SPEED_SLOT =  pDraggedSlot->GetSlotInInventory();

        }
    }

    return true;
}
bool CIFSTMacroAutoHunt::IsAutoBerserkChecked() const {
    return m_checkbox_berserk->GetCheckedState_MAYBE();
}

bool CIFSTMacroAutoHunt::IsGoBackCenterChecked() const {
    return m_checkbox_goback_center->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAttackHostilityChecked() const {
    return m_checkbox_attack_hostility->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsRequestJoinPartyChecked() const {
    return m_checkbox_accept_request_joinparty->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoHPChecked() const {
    return m_checkbox_hp->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoMPChecked() const {
    return m_checkbox_mp->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoAbnormalChecked() const {
    return m_checkbox_abnormal->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoVigorChecked() const {
    return m_checkbox_vigor->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoLureChecked() const {
    return m_checkbox_luremode->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoAcceptResChecked() const {
    return m_checkbox_accept_res->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoResPartyMemberChecked() const {
    return m_checkbox_res_partymember->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoAttackOtherPlayerChecked() const {
    return m_checkbox_attack_other_player->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoSpeedScrollChecked() const {
    return m_checkbox_speedscroll->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoPetHpChecked() const {
    return m_checkbox_pet_hp->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoPetHgpChecked() const {
    return m_checkbox_pet_hgp->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoPetCureChecked() const {
    return m_checkbox_pet_cure->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoPetResurrectChecked() const {
    return m_checkbox_pet_resurrect->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoPetTriggerChecked() const {
    return m_checkbox_pet_trigger->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoPetTradeHPChecked() const {
    return m_checkbox_pet_trade->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoPetRiddingHPChecked() const {
    return m_checkbox_pet_ridding->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoBuffModeChecked() const {
    return m_checkbox_buff_mode->GetCheckedState_MAYBE();
}
bool CIFSTMacroAutoHunt::IsAutoAttackSnowManAndPillarChecked() const {
    return m_checkbox_attack_snowman_and_pillar->GetCheckedState_MAYBE();
}
void CIFSTMacroAutoHunt::OnUnknownStuff() {
    int id = GetIDOfInterfaceUnderCursor();
    int i = 0;

    for (int i = 0; i < numberOfTabs; ++i) {
        if (id == m_pTabs[i]->UniqueID()) {
            ActivateTabPage(i);
            return;
        }
    }
}
void CIFSTMacroAutoHunt::OnListChatThing(int a1, int a2) {
    printf("%s(%d, %d)\n", __FUNCTION__, a1, a2 );
    CIFListCtrl *pList;
    pList = m_custom_textbox_range;
    CIFListCtrl::SLineOfText *line = pList->sub_63A940();
    std::n_wstring str;
    line->m_font->GetText(&str);
    if (str.empty())
        return;

    wchar_t buffer[255];
    swprintf_s(buffer, L"%s",str.c_str());
    m_custom_label2->SetText(buffer);
    OnListSelectRangeState(false);
}
void CIFSTMacroAutoHunt::OnListSelectRange()
{
    if(Frame2->IsVisible())
    {
        OnListSelectRangeState(false);
    } else
    {
        OnListSelectRangeState(true);
    }

}
void CIFSTMacroAutoHunt::OnListSelectRangeState(bool State)
{
    Frame2->ShowGWnd(State);
    m_custom_NormalTile->ShowGWnd(State);
    m_custom_textbox_range->ShowGWnd(State);
}
void CIFSTMacroAutoHunt::OnListSelectTab(bool State)
{
    m_mybutton2->ShowGWnd(State);
    m_mybutton3->ShowGWnd(State);
    m_mybutton->ShowGWnd(State);
    m_custom_bg->ShowGWnd(State);
    m_custom_bg2->ShowGWnd(State);
    m_custom_bg3->ShowGWnd(State);
    m_custom_bg4->ShowGWnd(State);
    m_custom_bg5->ShowGWnd(State);
    m_custom_bg6->ShowGWnd(State);
    m_custom_bg7->ShowGWnd(State);
    m_custom_bg8->ShowGWnd(State);
    m_custom_bg9->ShowGWnd(State);
    m_custom_bg10->ShowGWnd(State);
    m_custom_bg11->ShowGWnd(State);
    m_custom_label2->ShowGWnd(State);
    m_custom_label3->ShowGWnd(State);
    m_custom_label11->ShowGWnd(State);
    m_custom_label12->ShowGWnd(State);
    m_custom_label13->ShowGWnd(State);
    m_custom_label14->ShowGWnd(State);
    m_custom_label15->ShowGWnd(State);
    m_custom_label16->ShowGWnd(State);
    m_custom_label17->ShowGWnd(State);
    m_custom_label18->ShowGWnd(State);
    m_custom_label19->ShowGWnd(State);
    m_custom_label20->ShowGWnd(State);
    m_checkbox_berserk->ShowGWnd(State);
    m_checkbox_goback_center->ShowGWnd(State);
    m_checkbox_attack_hostility->ShowGWnd(State);
    m_custom_textbox_range->ShowGWnd(State);
    m_checkbox_accept_request_joinparty->ShowGWnd(State);
    m_checkbox_luremode->ShowGWnd(State);
    m_checkbox_accept_res->ShowGWnd(State);
    m_checkbox_res_partymember->ShowGWnd(State);
    m_checkbox_attack_other_player->ShowGWnd(State);
    m_checkbox_buff_mode->ShowGWnd(State);
    m_checkbox_attack_snowman_and_pillar->ShowGWnd(State);
}
void CIFSTMacroAutoHunt::OnListSelectTabPotion(bool State)
{

    m_slot1->ShowGWnd(State);
    m_slot2->ShowGWnd(State);
    m_slot3->ShowGWnd(State);
    m_slot4->ShowGWnd(State);
    m_slot5->ShowGWnd(State);
    statics->ShowGWnd(State);
    statics2->ShowGWnd(State);
    statics3->ShowGWnd(State);
    statics4->ShowGWnd(State);
    statics5->ShowGWnd(State);
    statics11->ShowGWnd(State);
    m_checkbox_hp->ShowGWnd(State);
    m_checkbox_mp->ShowGWnd(State);
    m_checkbox_vigor->ShowGWnd(State);
    m_checkbox_abnormal->ShowGWnd(State);
    m_checkbox_speedscroll->ShowGWnd(State);
    m_text_hp->ShowGWnd(State);
    m_text_mp->ShowGWnd(State);
    m_text_vigor->ShowGWnd(State);
    m_text_abnormal->ShowGWnd(State);
    m_text_percent_hp->ShowGWnd(State);
    m_text_percent_mp->ShowGWnd(State);
    m_text_percent_vigor->ShowGWnd(State);
    m_text_speedscroll->ShowGWnd(State);
    m_edit_hp->ShowGWnd(State);
    m_edit_mp->ShowGWnd(State);
    m_edit_vigor->ShowGWnd(State);
    m_mybutton4->ShowGWnd(State);
    m_mybutton5->ShowGWnd(State);
    m_custom_label_tooltip3->ShowGWnd(State);
    m_Hp_Slider->ShowGWnd(State);
    m_Mp_Slider->ShowGWnd(State);
    m_Vigor_Slider->ShowGWnd(State);
}
void CIFSTMacroAutoHunt::OnListSelectTabPet(bool State)
{
    m_mybutton6->ShowGWnd(State);
    m_mybutton7->ShowGWnd(State);
    m_slot6->ShowGWnd(State);
    m_slot7->ShowGWnd(State);
    m_slot8->ShowGWnd(State);
    m_slot9->ShowGWnd(State);
    m_slot10->ShowGWnd(State);
    m_slot11->ShowGWnd(State);
    statics6->ShowGWnd(State);
    statics7->ShowGWnd(State);
    statics8->ShowGWnd(State);
    statics9->ShowGWnd(State);
    statics10->ShowGWnd(State);
    statics11->ShowGWnd(State);
    statics12->ShowGWnd(State);
    statics13->ShowGWnd(State);
    m_custom_label_tradepet->ShowGWnd(State);
    m_custom_label_fellowpet->ShowGWnd(State);
    m_checkbox_pet_hp->ShowGWnd(State);
    m_checkbox_pet_hgp->ShowGWnd(State);
    m_checkbox_pet_cure->ShowGWnd(State);
    m_checkbox_pet_resurrect->ShowGWnd(State);
    m_checkbox_pet_trigger->ShowGWnd(State);
    m_checkbox_pet_trade->ShowGWnd(State);
    m_checkbox_pet_ridding->ShowGWnd(State);
    m_text_pet_percent_hp->ShowGWnd(State);
    m_text_pet_percent_hgp->ShowGWnd(State);
    m_text_pet_cure->ShowGWnd(State);
    m_text_pet_hgp->ShowGWnd(State);
    m_text_pet_trigger->ShowGWnd(State);
    m_text_pet_resurrect->ShowGWnd(State);
    m_text_pet_hp->ShowGWnd(State);
    m_edit_pet_hp->ShowGWnd(State);
    m_edit_pet_hgp->ShowGWnd(State);
    m_Pet_HP_Slider->ShowGWnd(State);
    m_Pet_HGP_Slider->ShowGWnd(State);
    m_text_pet_hp_trade->ShowGWnd(State);
    m_text_pet_hp_ridding->ShowGWnd(State);
    m_text_pet_percent_hp_2->ShowGWnd(State);
    m_edit_pet_trade_and_ridding->ShowGWnd(State);
    m_edit_pet_trade_and_ridding->ShowGWnd(State);
    m_Pet_Trade_And_Ridding_HP_Slider->ShowGWnd(State);
}
void CIFSTMacroAutoHunt::OnLoadSkillTabBuff()
{
    CIFSTMacroAutoHunt::CharSkillDataList.clear();
    for (std::map<short, Skill*>::iterator it = Rebot::AllSkillOfChar.begin();
         it != Rebot::AllSkillOfChar.end(); ++it) {
        if(it->second->Param1==3 || it->second->Param3==63 || it->second->Param2==1751474540 || it->second->Param2==6645362)
        {
            CIFSTMacroAutoHunt::CharSkillData SkillData = CIFSTMacroAutoHunt::CharSkillData();
            std::wstringstream Reg;
            Reg << it->first;
            SkillData.SkillID = it->first;
            SkillData.SkillNames = g_CTextStringManager->GetStringTextByCode(TO_WSTRING(it->second->SkillName).c_str())->c_str();
            g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->CharSkillDataList.push_back(SkillData);


        }

    }
}
void CIFSTMacroAutoHunt::OnListSelectTabBuff(bool State)
{
    OnLoadSkillTabBuff();
    Clear2();
    ClearDDJ2();
    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->UpdateSkilDataList();
    m_partymember_slot1->ShowGWnd(State);
    m_mySkill_slot1->ShowGWnd(State);
    m_mySkill_slot2->ShowGWnd(false);
    m_mySkill_slot3->ShowGWnd(false);
    m_mySkill_slot4->ShowGWnd(false);
    m_mySkill_slot5->ShowGWnd(false);
    m_mySkill_slot6->ShowGWnd(false);
    m_mySkill_slot7->ShowGWnd(false);
    m_mySkill_slot8->ShowGWnd(false);
    m_mySkill_slot9->ShowGWnd(false);
    m_mySkill_slot10->ShowGWnd(false);
    m_SkillBuffed_slot1->ShowGWnd(State);
    m_spin->ShowGWnd(State);
    m_custom_label_partymemberlist->ShowGWnd(State);
    m_custom_label_skilllist->ShowGWnd(State);
    m_custom_label_skillbuffedlist->ShowGWnd(State);
    statics14->ShowGWnd(State);
    statics15->ShowGWnd(State);
    statics16->ShowGWnd(State);
    m_mybutton8->ShowGWnd(State);
    m_mybutton9->ShowGWnd(State);

}
void CIFSTMacroAutoHunt::OnSaveClick()
{

    Rebot::Config.GoBackCentrer = IsGoBackCenterChecked();
    Rebot::Config.AttackHostility = IsAttackHostilityChecked();
    Rebot::Config.RequestJoinParty = IsRequestJoinPartyChecked();
    Rebot::Config.AutoBerserk = IsAutoBerserkChecked();
    Rebot::Config.LureMode = IsAutoLureChecked();
    Rebot::Config.AcceptRes = IsAutoAcceptResChecked();
    Rebot::Config.OnlyResPartyMember = IsAutoResPartyMemberChecked();
    Rebot::Config.AutoResMember = IsAutoResPartyMemberChecked();
    Rebot::Config.AttackOtherPlayer = IsAutoAttackOtherPlayerChecked();
    Rebot::Config.AutoBuffMode = IsAutoBuffModeChecked();
    Rebot::Config.AutoAttackSnowMan = IsAutoAttackSnowManAndPillarChecked();
    std::n_wstring input_text = m_custom_label2->GetNText();
    if (wcscmp(input_text.c_str(), L"10m") == 0)
    {
        Rebot::Config.RebotRange=100;
    }
    else if (wcscmp(input_text.c_str(), L"30m")==0)
    {
        Rebot::Config.RebotRange=300;
    }
    else if (wcscmp(input_text.c_str(), L"50m")==0)
    {
        Rebot::Config.RebotRange=500;
    }
    else if (wcscmp(input_text.c_str(), L"70m")==0)
    {
        Rebot::Config.RebotRange=700;
    }
    else if (wcscmp(input_text.c_str(), L"100m")==0)
    {
        Rebot::Config.RebotRange=1000;
    }
    this->OnCloseWnd();
}
void CIFSTMacroAutoHunt::OnSave2Click()
{
    Rebot::Config.AutoHP = IsAutoHPChecked();
    Rebot::Config.AutoMP = IsAutoMPChecked();
    Rebot::Config.AutoVigor = IsAutoVigorChecked();
    Rebot::Config.AutoAbnormal = IsAutoAbnormalChecked();
    Rebot::Config.AutoSpeedScroll = IsAutoSpeedScrollChecked();

    std::n_wstring hp_input_text = m_edit_hp->GetNText();
    std::n_wstring mp_input_text = m_edit_mp->GetNText();
    std::n_wstring vigor_input_text = m_edit_vigor->GetNText();

    int hp_input_per =  atoi(TO_NSTRING(hp_input_text).c_str());
    int mp_input_per =  atoi(TO_NSTRING(mp_input_text).c_str());
    int vigor_input_per =  atoi(TO_NSTRING(vigor_input_text).c_str());

    Rebot::Config.HpPercent = hp_input_per;
    Rebot::Config.MpPercent = mp_input_per;
    Rebot::Config.VigorPercent = vigor_input_per;
    Rebot::Config.HpItemID=HP_ID;
    Rebot::Config.MpItemID = MP_ID;
    Rebot::Config.VigorItemID = VIGOR_ID;
    Rebot::Config.AbnormalItemID = ABNORMAL_ID;
    Rebot::Config.SpeedItemID = SPEEDITEM_ID;
    this->OnCloseWnd();
}
void CIFSTMacroAutoHunt::OnSave3Click()
{
    Rebot::Config.AutoRidingPetHP = IsAutoPetRiddingHPChecked();
    Rebot::Config.AutoTransPetHP = IsAutoPetTradeHPChecked();
    Rebot::Config.AutoAttackPetPotion = IsAutoPetTriggerChecked();
    Rebot::Config.AutoAttackPetHP = IsAutoPetHpChecked();
    Rebot::Config.AutoAttackPetHGP = IsAutoPetHgpChecked();
    Rebot::Config.AutoAttackPetCure = IsAutoPetCureChecked();
    Rebot::Config.AutoAttackPetResurrect = IsAutoPetResurrectChecked();

    std::n_wstring hp_input_text = m_edit_pet_trade_and_ridding->GetNText();
    std::n_wstring hp_attack_input_text = m_edit_pet_hp->GetNText();
    std::n_wstring hgp_attack_input_text = m_edit_pet_hgp->GetNText();

    int hp_input_per =  atoi(TO_NSTRING(hp_input_text).c_str());
    int hp_attack_input_per =  atoi(TO_NSTRING(hp_attack_input_text).c_str());
    int hgp_attack_input_per =  atoi(TO_NSTRING(hgp_attack_input_text).c_str());

    Rebot::Config.PetRiddingAndTradeHPPercent = hp_input_per;
    Rebot::Config.PetHpRiddingAndTradeItemID=PET_HP_RIDDING_TRADE_ID;

    Rebot::Config.PetAttackHPPercent = hp_attack_input_per;
    Rebot::Config.PetAttackHPGPercent = hgp_attack_input_per;
    Rebot::Config.PetAttackHPtemID = PET_HP_ID;
    Rebot::Config.PetAttackHPGItemID = PET_HGP_ID;
    Rebot::Config.PetAttackCureItemID = PET_CURE_ID;
    Rebot::Config.PetAttackResurrectItemID = PET_RESURRECT_ID;
    Rebot::Config.PetAttackItemID = PET_TRIGGER_ID;


    this->OnCloseWnd();
}
void CIFSTMacroAutoHunt::OnCancelClick()
{
    this->OnCloseWnd();
}

int CIFSTMacroAutoHunt::OnMouseLeftUp(int a1, int x, int y)
{
    printf("> " __FUNCTION__ "(%d, %d, %d)\n", a1, x, y);
    OnListSelectRangeState(false);
    return 0;
}
void CIFSTMacroAutoHunt::ActivateTabPage(BYTE page) {

    for (int i = 0; i < numberOfTabs; i++) {
        if (i == page)
            continue;

        m_pTabs[i]->sub_64CC30(0);
    }

    m_pTabs[page]->sub_64CC30(1);

    switch (page)
    {
        case 0:
            OnListSelectTab(true);
            OnListSelectTabPet(false);
            OnListSelectRangeState(false);
            OnListSelectTabPotion(false);
            OnListSelectTabBuff(false);
            break;
        case 1:
            OnListSelectTab(false);
            OnListSelectRangeState(false);
            OnListSelectTabPet(false);
            OnListSelectTabBuff(false);
            statics11->SetGWndSize(this->GetSize().width - 42, this->GetSize().height - 180);
            OnListSelectTabPotion(true);
            break;
        case 2:
            OnListSelectTab(false);
            OnListSelectRangeState(false);
            OnListSelectTabPotion(false);
            OnListSelectTabBuff(false);
            statics11->SetGWndSize(this->GetSize().width - 42, this->GetSize().height - 230);
            OnListSelectTabPet(true);
            break;
        case 3:
            OnListSelectTabBuff(true);
            OnListSelectTab(false);
            OnListSelectTabPet(false);
            OnListSelectRangeState(false);
            OnListSelectTabPotion(false);
            break;
        case 4:

            break;
        case 5:

            break;
    }
}

void CIFSTMacroAutoHunt::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 5, (client.res[0].height - v109.height) / 4);
}
void CIFSTMacroAutoHunt::Clear()
{
    m_partymember_slot1->line1->WriteLine(0, L"", L"", L"");
    m_partymember_slot1->line2->WriteLine(0, L"", L"", L"");
    m_partymember_slot1->line3->WriteLine(0, L"", L"", L"");
    m_partymember_slot1->line4->WriteLine(0, L"", L"", L"");
    m_partymember_slot1->line5->WriteLine(0, L"", L"", L"");
    m_partymember_slot1->line6->WriteLine(0, L"", L"", L"");
    m_partymember_slot1->line7->WriteLine(0, L"", L"", L"");
    m_partymember_slot1->line8->WriteLine(0, L"", L"", L"");
}
void CIFSTMacroAutoHunt::Clear2()
{
    m_mySkill_slot1->line1->WriteLine(0, L"");
    m_mySkill_slot1->line2->WriteLine(0, L"");
    m_mySkill_slot1->line3->WriteLine(0, L"");
    m_mySkill_slot1->line4->WriteLine(0, L"");
    m_mySkill_slot1->line5->WriteLine(0, L"");
    m_mySkill_slot1->line6->WriteLine(0, L"");
    m_mySkill_slot1->line7->WriteLine(0, L"");
    m_mySkill_slot1->line8->WriteLine(0, L"");

    m_mySkill_slot2->line1->WriteLine(0, L"");
    m_mySkill_slot2->line2->WriteLine(0, L"");
    m_mySkill_slot2->line3->WriteLine(0, L"");
    m_mySkill_slot2->line4->WriteLine(0, L"");
    m_mySkill_slot2->line5->WriteLine(0, L"");
    m_mySkill_slot2->line6->WriteLine(0, L"");
    m_mySkill_slot2->line7->WriteLine(0, L"");
    m_mySkill_slot2->line8->WriteLine(0, L"");

    m_mySkill_slot3->line1->WriteLine(0, L"");
    m_mySkill_slot3->line2->WriteLine(0, L"");
    m_mySkill_slot3->line3->WriteLine(0, L"");
    m_mySkill_slot3->line4->WriteLine(0, L"");
    m_mySkill_slot3->line5->WriteLine(0, L"");
    m_mySkill_slot3->line6->WriteLine(0, L"");
    m_mySkill_slot3->line7->WriteLine(0, L"");
    m_mySkill_slot3->line8->WriteLine(0, L"");

    m_mySkill_slot4->line1->WriteLine(0, L"");
    m_mySkill_slot4->line2->WriteLine(0, L"");
    m_mySkill_slot4->line3->WriteLine(0, L"");
    m_mySkill_slot4->line4->WriteLine(0, L"");
    m_mySkill_slot4->line5->WriteLine(0, L"");
    m_mySkill_slot4->line6->WriteLine(0, L"");
    m_mySkill_slot4->line7->WriteLine(0, L"");
    m_mySkill_slot4->line8->WriteLine(0, L"");

    m_mySkill_slot5->line1->WriteLine(0, L"");
    m_mySkill_slot5->line2->WriteLine(0, L"");
    m_mySkill_slot5->line3->WriteLine(0, L"");
    m_mySkill_slot5->line4->WriteLine(0, L"");
    m_mySkill_slot5->line5->WriteLine(0, L"");
    m_mySkill_slot5->line6->WriteLine(0, L"");
    m_mySkill_slot5->line7->WriteLine(0, L"");
    m_mySkill_slot5->line8->WriteLine(0, L"");

    m_mySkill_slot6->line1->WriteLine(0, L"");
    m_mySkill_slot6->line2->WriteLine(0, L"");
    m_mySkill_slot6->line3->WriteLine(0, L"");
    m_mySkill_slot6->line4->WriteLine(0, L"");
    m_mySkill_slot6->line5->WriteLine(0, L"");
    m_mySkill_slot6->line6->WriteLine(0, L"");
    m_mySkill_slot6->line7->WriteLine(0, L"");
    m_mySkill_slot6->line8->WriteLine(0, L"");

    m_mySkill_slot7->line1->WriteLine(0, L"");
    m_mySkill_slot7->line2->WriteLine(0, L"");
    m_mySkill_slot7->line3->WriteLine(0, L"");
    m_mySkill_slot7->line4->WriteLine(0, L"");
    m_mySkill_slot7->line5->WriteLine(0, L"");
    m_mySkill_slot7->line6->WriteLine(0, L"");
    m_mySkill_slot7->line7->WriteLine(0, L"");
    m_mySkill_slot7->line8->WriteLine(0, L"");

    m_mySkill_slot8->line1->WriteLine(0, L"");
    m_mySkill_slot8->line2->WriteLine(0, L"");
    m_mySkill_slot8->line3->WriteLine(0, L"");
    m_mySkill_slot8->line4->WriteLine(0, L"");
    m_mySkill_slot8->line5->WriteLine(0, L"");
    m_mySkill_slot8->line6->WriteLine(0, L"");
    m_mySkill_slot8->line7->WriteLine(0, L"");
    m_mySkill_slot8->line8->WriteLine(0, L"");

    m_mySkill_slot9->line1->WriteLine(0, L"");
    m_mySkill_slot9->line2->WriteLine(0, L"");
    m_mySkill_slot9->line3->WriteLine(0, L"");
    m_mySkill_slot9->line4->WriteLine(0, L"");
    m_mySkill_slot9->line5->WriteLine(0, L"");
    m_mySkill_slot9->line6->WriteLine(0, L"");
    m_mySkill_slot9->line7->WriteLine(0, L"");
    m_mySkill_slot9->line8->WriteLine(0, L"");

    m_mySkill_slot10->line1->WriteLine(0, L"");
    m_mySkill_slot10->line2->WriteLine(0, L"");
    m_mySkill_slot10->line3->WriteLine(0, L"");
    m_mySkill_slot10->line4->WriteLine(0, L"");
    m_mySkill_slot10->line5->WriteLine(0, L"");
    m_mySkill_slot10->line6->WriteLine(0, L"");
    m_mySkill_slot10->line7->WriteLine(0, L"");
    m_mySkill_slot10->line8->WriteLine(0, L"");

}
void CIFSTMacroAutoHunt::Clear3()
{
    m_SkillBuffed_slot1->line1->WriteLine(0, 0);
    m_SkillBuffed_slot1->line2->WriteLine(0, 0);
    m_SkillBuffed_slot1->line3->WriteLine(0, 0);
    m_SkillBuffed_slot1->line4->WriteLine(0, 0);
    m_SkillBuffed_slot1->line5->WriteLine(0, 0);
    m_SkillBuffed_slot1->line6->WriteLine(0, 0);
    m_SkillBuffed_slot1->line7->WriteLine(0, 0);
    m_SkillBuffed_slot1->line8->WriteLine(0, 0);
}
void CIFSTMacroAutoHunt::ClearDDJ() {
    m_partymember_slot1->ClearDDJ();

}
void CIFSTMacroAutoHunt::ClearDDJ2() {
    m_mySkill_slot1->ClearDDJ();
    m_mySkill_slot2->ClearDDJ();
    m_mySkill_slot3->ClearDDJ();
    m_mySkill_slot4->ClearDDJ();
    m_mySkill_slot5->ClearDDJ();
    m_mySkill_slot6->ClearDDJ();
    m_mySkill_slot7->ClearDDJ();
    m_mySkill_slot8->ClearDDJ();
    m_mySkill_slot9->ClearDDJ();
    m_mySkill_slot10->ClearDDJ();
}
void CIFSTMacroAutoHunt::ClearDDJ3() {
    m_SkillBuffed_slot1->ClearDDJ();

}
void CIFSTMacroAutoHunt::UpdateSkillBuffedList(std::n_wstring SelectedCharName)
{
   int i = 0;

    for (std::map<std::wstring, BuffSkill*>::iterator it = Rebot::m_SkillNeedBuffList.begin(); it != Rebot::m_SkillNeedBuffList.end(); ++it)
    {

        if (wcscmp(SelectedCharName.c_str(), it->first.c_str()) == 0)
        {

            for(std::list<short >::iterator itr = Rebot::m_SkillNeedBuffList[SelectedCharName.c_str()]->m_SkillNeedBuff.begin(); itr != Rebot::m_SkillNeedBuffList[SelectedCharName.c_str()]->m_SkillNeedBuff.end(); ++itr)
            {
                ++i;
                switch (i)
                {
                    case 1:
                    {
                        m_SkillBuffed_slot1->line1->WriteLine(i,*itr);
                    }
                        break;
                    case 2:
                    {
                        m_SkillBuffed_slot1->line2->WriteLine(i,*itr);
                    }
                        break;
                    case 3:
                    {
                        m_SkillBuffed_slot1->line3->WriteLine(i,*itr);
                    }
                        break;
                    case 4:
                    {
                        m_SkillBuffed_slot1->line4->WriteLine(i,*itr);
                    }
                        break;
                    case 5:
                    {
                        m_SkillBuffed_slot1->line5->WriteLine(i,*itr);
                    }
                        break;
                    case 6:
                    {
                        m_SkillBuffed_slot1->line6->WriteLine(i,*itr);
                    }
                        break;
                    case 7:
                    {
                        m_SkillBuffed_slot1->line7->WriteLine(i,*itr);
                    }
                        break;
                    case 8:
                    {
                        m_SkillBuffed_slot1->line8->WriteLine(i,*itr);
                    }
                        break;

                }
            }
        }

    }
}
void CIFSTMacroAutoHunt::UpdatePartyMemberList()
{

    for (std::vector<CIFSTMacroAutoHunt::PartyMatchMember>::iterator it = CIFSTMacroAutoHunt::PartyMatchMemberList.begin(); it != CIFSTMacroAutoHunt::PartyMatchMemberList.end(); ++it)
    {

        switch ((*it).LineNum)
        {
            case 0:
            {
                m_partymember_slot1->line1->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 1:
            {
                m_partymember_slot1->line2->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 2:
            {
                m_partymember_slot1->line3->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 3:
            {
                m_partymember_slot1->line4->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 4:
            {
                m_partymember_slot1->line5->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 5:
            {
                m_partymember_slot1->line6->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 6:
            {
                m_partymember_slot1->line7->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 7:
            {
                m_partymember_slot1->line8->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;

        }
    }
}
void CIFSTMacroAutoHunt::UpdateSkilDataList()
{
    int i = 0;
    for (std::vector<CIFSTMacroAutoHunt::CharSkillData>::iterator it = CIFSTMacroAutoHunt::CharSkillDataList.begin(); it != CIFSTMacroAutoHunt::CharSkillDataList.end(); ++it)
    {
        ++i;
        (*it).LineNum = i;
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_mySkill_slot1->line1->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 2:
            {
                m_mySkill_slot1->line2->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 3:
            {
                m_mySkill_slot1->line3->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 4:
            {
                m_mySkill_slot1->line4->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 5:
            {
                m_mySkill_slot1->line5->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 6:
            {
                m_mySkill_slot1->line6->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 7:
            {
                m_mySkill_slot1->line7->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 8:
            {
                m_mySkill_slot1->line8->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 9:
            {
                m_mySkill_slot2->line1->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 10:
            {
                m_mySkill_slot2->line2->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 11:
            {
                m_mySkill_slot2->line3->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 12:
            {
                m_mySkill_slot2->line4->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 13:
            {
                m_mySkill_slot2->line5->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 14:
            {
                m_mySkill_slot2->line6->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 15:
            {
                m_mySkill_slot2->line7->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 16:
            {
                m_mySkill_slot2->line8->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 17:
            {
                m_mySkill_slot2->line1->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 18:
            {
                m_mySkill_slot2->line2->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 19:
            {
                m_mySkill_slot2->line3->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 20:
            {
                m_mySkill_slot2->line4->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 21:
            {
                m_mySkill_slot2->line5->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 22:
            {
                m_mySkill_slot2->line6->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 23:
            {
                m_mySkill_slot2->line7->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 24:
            {
                m_mySkill_slot2->line8->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 25:
            {
                m_mySkill_slot3->line1->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 26:
            {
                m_mySkill_slot3->line2->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 27:
            {
                m_mySkill_slot3->line3->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 28:
            {
                m_mySkill_slot3->line4->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 29:
            {
                m_mySkill_slot3->line5->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 30:
            {
                m_mySkill_slot3->line6->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 31:
            {
                m_mySkill_slot3->line7->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 32:
            {
                m_mySkill_slot3->line8->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 33:
            {
                m_mySkill_slot4->line1->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 34:
            {
                m_mySkill_slot4->line2->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 35:
            {
                m_mySkill_slot4->line3->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 36:
            {
                m_mySkill_slot4->line4->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 37:
            {
                m_mySkill_slot4->line5->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 38:
            {
                m_mySkill_slot4->line6->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 39:
            {
                m_mySkill_slot4->line7->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 40:
            {
                m_mySkill_slot4->line8->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 41:
            {
                m_mySkill_slot5->line1->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 42:
            {
                m_mySkill_slot5->line2->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 43:
            {
                m_mySkill_slot5->line3->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 44:
            {
                m_mySkill_slot5->line4->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 45:
            {
                m_mySkill_slot5->line5->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 46:
            {
                m_mySkill_slot5->line6->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 47:
            {
                m_mySkill_slot5->line7->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 48:
            {
                m_mySkill_slot5->line8->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 49:
            {
                m_mySkill_slot6->line1->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 50:
            {
                m_mySkill_slot6->line2->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 51:
            {
                m_mySkill_slot6->line3->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 52:
            {
                m_mySkill_slot6->line4->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 53:
            {
                m_mySkill_slot6->line5->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 54:
            {
                m_mySkill_slot6->line6->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 55:
            {
                m_mySkill_slot6->line7->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 56:
            {
                m_mySkill_slot6->line8->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 57:
            {
                m_mySkill_slot7->line1->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 58:
            {
                m_mySkill_slot7->line2->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 59:
            {
                m_mySkill_slot7->line3->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 60:
            {
                m_mySkill_slot7->line4->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 61:
            {
                m_mySkill_slot7->line5->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 62:
            {
                m_mySkill_slot7->line6->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 63:
            {
                m_mySkill_slot7->line7->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 64:
            {
                m_mySkill_slot7->line8->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 65:
            {
                m_mySkill_slot8->line1->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 66:
            {
                m_mySkill_slot8->line2->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 67:
            {
                m_mySkill_slot8->line3->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 68:
            {
                m_mySkill_slot8->line4->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 69:
            {
                m_mySkill_slot8->line5->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 70:
            {
                m_mySkill_slot8->line6->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 71:
            {
                m_mySkill_slot8->line7->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
            case 72:
            {
                m_mySkill_slot8->line8->WriteLine((*it).SkillID,(*it).SkillNames.c_str());
            }
                break;
        }

    }
}
void CIFSTMacroAutoHunt::ShowList(BYTE listid)
{
    switch (listid)
    {
        case 1:
            HideLists();
            printf("page1 \n");
            m_mySkill_slot1->ShowGWnd(true);
            break;
        case 2:
            HideLists();
            printf("page2 \n");
            m_mySkill_slot2->ShowGWnd(true);
            break;
        case 3:
            HideLists();
            printf("page3 \n");
            m_mySkill_slot3->ShowGWnd(true);
            break;
        case 4:
            HideLists();
            m_mySkill_slot4->ShowGWnd(true);
            break;
        case 5:
            HideLists();
            m_mySkill_slot5->ShowGWnd(true);
            break;
        case 6:
            HideLists();
            m_mySkill_slot6->ShowGWnd(true);
            break;
        case 7:
            HideLists();
            m_mySkill_slot7->ShowGWnd(true);
            break;
        case 8:
            HideLists();
            m_mySkill_slot8->ShowGWnd(true);
            break;
        case 9:
            HideLists();
            m_mySkill_slot9->ShowGWnd(true);
            break;
        case 10:
            HideLists();
            m_mySkill_slot10->ShowGWnd(true);
            break;
    }
}

bool CIFSTMacroAutoHunt::IsPageFull(BYTE PageID, BYTE LineID)
{
    bool full = false;
    if (PageID == 1)
    {
        if (LineID == 30)
        {
            if (m_mySkill_slot1->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 37)
        {
            if (m_mySkill_slot1->line8->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 2)
    {
        if (LineID == 30)
        {
            if (m_mySkill_slot2->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 37)
        {
            if (m_mySkill_slot2->line8->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 3)
    {
        if (LineID == 30)
        {
            if (m_mySkill_slot3->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 37)
        {
            if (m_mySkill_slot3->line8->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 4)
    {
        if (LineID == 30)
        {
            if (m_mySkill_slot4->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 37)
        {
            if (m_mySkill_slot4->line8->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 5)
    {
        if (LineID == 30)
        {
            if (m_mySkill_slot5->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 37)
        {
            if (m_mySkill_slot5->line8->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 6)
    {
        if (LineID == 30)
        {
            if (m_mySkill_slot6->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 37)
        {
            if (m_mySkill_slot6->line8->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 7)
    {
        if (LineID == 30)
        {
            if (m_mySkill_slot7->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 37)
        {
            if (m_mySkill_slot7->line8->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 8)
    {
        if (LineID == 30)
        {
            if (m_mySkill_slot8->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 37)
        {
            if (m_mySkill_slot8->line8->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 9)
    {
        if (LineID == 30)
        {
            if (m_mySkill_slot9->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 37)
        {
            if (m_mySkill_slot9->line8->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 10)
    {
        if (LineID == 30)
        {
            if (m_mySkill_slot10->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 37)
        {
            if (m_mySkill_slot10->line8->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }

    return full;
}
void CIFSTMacroAutoHunt::HideLists()
{
    m_mySkill_slot1->ShowGWnd(false);
    m_mySkill_slot2->ShowGWnd(false);
    m_mySkill_slot3->ShowGWnd(false);
    m_mySkill_slot4->ShowGWnd(false);
    m_mySkill_slot5->ShowGWnd(false);
    m_mySkill_slot6->ShowGWnd(false);
    m_mySkill_slot7->ShowGWnd(false);
    m_mySkill_slot8->ShowGWnd(false);
    m_mySkill_slot9->ShowGWnd(false);
    m_mySkill_slot10->ShowGWnd(false);
}
void CIFSTMacroAutoHunt::On_Buff_AddSkill()
{
    if (!SelectedCharName.empty() && !SelectedSkillName.empty())
    {
        BYTE v1 = 1;
        for (int i = 0; i < CharSkillDataList.size(); ++i)
        {
            if (wcscmp(CharSkillDataList[i].SkillNames.c_str(), SelectedSkillName.c_str()) == 0)
            {
                BuffSkill* NewSkill = new BuffSkill();
                NewSkill->SkillNames = SelectedSkillName.c_str();
                NewSkill->m_SkillNeedBuff.push_back(CharSkillDataList[i].SkillID);

                std::map<std::wstring, BuffSkill*>::iterator foundedInfo = Rebot::m_SkillNeedBuffList.find(SelectedCharName.c_str());
                if (foundedInfo != Rebot::m_SkillNeedBuffList.end())
                    Rebot::m_SkillNeedBuffList[SelectedCharName.c_str()]->m_SkillNeedBuff.push_back(CharSkillDataList[i].SkillID);
                else
                    Rebot::m_SkillNeedBuffList.insert(std::pair<std::wstring, BuffSkill*>(SelectedCharName.c_str(),NewSkill));
               /*
                Rebot::m_SkillNeedBuffList[SelectedCharName.c_str()] = new BuffSkill;
                Rebot::m_SkillNeedBuffList[SelectedCharName.c_str()]->SkillNames=SelectedSkillName.c_str();
                Rebot::m_SkillNeedBuffList[SelectedCharName.c_str()]->m_SkillNeedBuff.push_back(CharSkillDataList[i].SkillID);*/
                ClearDDJ();
                ClearDDJ2();
                UpdateSkillBuffedList(SelectedCharName.c_str());
                break;
            }
        }
    }
    else
    {
        g_pCGInterface->ShowMessage_Warning(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_BUFF_PLEASE_SELECT"));
        return;
    }
}
void CIFSTMacroAutoHunt::On_Buff_RemoveSkill()
{
    if (!SelectedCharName.empty() && !SelectedSkillNameRemove.empty())
    {
        for (std::map<std::wstring, BuffSkill*>::iterator it = Rebot::m_SkillNeedBuffList.begin(); it != Rebot::m_SkillNeedBuffList.end(); ++it)
        {

            if (wcscmp(SelectedCharName.c_str(), it->first.c_str()) == 0)
            {

                for(std::list<short >::iterator itr = Rebot::m_SkillNeedBuffList[SelectedCharName.c_str()]->m_SkillNeedBuff.begin(); itr != Rebot::m_SkillNeedBuffList[SelectedCharName.c_str()]->m_SkillNeedBuff.end(); ++itr)
                {
                    if (*itr==SkillIDSlelected)
                    {

                        Rebot::m_SkillNeedBuffList[SelectedCharName.c_str()]->m_SkillNeedBuff.erase(itr);

                        break;
                    }
                }
            }

        }
        Clear3();
        UpdateSkillBuffedList(SelectedCharName.c_str());
    }
    else
    {
        g_pCGInterface->ShowMessage_Warning(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_BUFF_PLEASE_SELECT"));
        return;
    }
}