//
// Created by Admin on 26/6/2021.
//

#include "IFSTCharItemInfo.h"
#include "IFNormalTile.h"
#include "ICPlayer.h"
#include "Game.h"
#include "IFStretchWnd.h"
#include <ctime>
#include "BSLib/BSLib.h"
#include "CPSMission.h"
#include "GInterface.h"
#include "GameDataExt.h"
#include "GlobalDataManager.h"
#include "NetProcessIn.h"
#include <BSLib\multiBYTE.h>
#include <GFXMainFrame/Controler.h>


#define GDR_CHARINFO_RT_LABEL 10
#define GDR_CHARINFO_RT_BTN_APPLY 11
#define GDR_CHARINFO_RT_FRAME 12
#define GDR_CHARINFO_RT_NORMALTILE 13
#define GDR_CHARINFO_RT_EDIT 14
#define GDR_CHARINFO_RT_EDIT2 17
#define GDR_CHARINFO_RT_TOOLTIP 16
#define GDR_CHARINFO_RT_STRETCHWND 15
#define GDR_CHARINFO_RT_SLOT1 6666
#define GDR_CHARINFO_RT_SLOT2 6667
#define GDR_CHARINFO_RT_SLOT3 6668
#define GDR_CHARINFO_RT_SLOT4 6669
#define GDR_CHARINFO_RT_SLOT5 6670
#define GDR_CHARINFO_RT_SLOT6 6671
#define GDR_CHARINFO_RT_SLOT7 6672
#define GDR_CHARINFO_RT_SLOT8 6673
#define GDR_CHARINFO_RT_SLOT9 6674
#define GDR_CHARINFO_RT_SLOT10 6675
#define GDR_CHARINFO_RT_SLOT11 6676
#define GDR_CHARINFO_RT_SLOT12 6677
#define GDR_CHARINFO_RT_SLOT13 6678
#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)
#define CLIENT_SCREEN_HEIGHT (*(int*)0x00ED7CBC)
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot;
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot1;
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot2;
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot3;
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot4;
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot5;
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot6;
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot7;
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot8;
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot9;
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot10;
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot11;
CIFSlotWithHelp* CIFSTCharItemInfo::m_slot12;
std::n_string CIFSTCharItemInfo::CharName;
GFX_IMPLEMENT_DYNCREATE(CIFSTCharItemInfo, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTCharItemInfo, CIFMainFrame)
                    ONG_COMMAND(GDR_CHARINFO_RT_BTN_APPLY, &On_BtnClick)


GFX_END_MESSAGE_MAP()


CIFSTCharItemInfo::CIFSTCharItemInfo() :
        m_custom_label(NULL) {

}

bool CIFSTCharItemInfo::OnCreate(long ln) {
    //CIFMainFrame::OnCreate(ln);
    //RECT rect_m_tile = {148, 9, 100, 13};
    //CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    //m_tile->SetText(TSM_GETTEXTPTR("UIIT_STT_CHARINFO_VIEWER"));

    //TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);
///////frame
    wnd_size sz = this->GetSize();
    //RECT rect_frame = { 16,40,378,370 };
    RECT rect_frame = { 0,0,205,370 };

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame,
                                                  GDR_CHARINFO_RT_FRAME,
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
                                                           GDR_CHARINFO_RT_NORMALTILE,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);
///////// m_edit
/*    RECT rect_m_edit = {210,80,144,20};
    m_edit = (CIFStatic *) (CIFStatic *) CreateInstance(this,
                                                    GFX_RUNTIME_CLASS(CIFEdit),
                                                    rect_m_edit,
                                                    GDR_CHARINFO_RT_EDIT,
                                                    1);
    m_edit->BringToFront();
    m_edit->TB_Func_5(1);
    RECT rect_m_edit_frame =  {rect_m_edit.left -2,
                               rect_m_edit.top -2,
                               rect_m_edit.right +4,
                               rect_m_edit.bottom +4};
    CIFFrame *frame_m_edit = (CIFFrame *) CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFFrame),
                                                         rect_m_edit_frame,
                                                         GDR_CHARINFO_RT_FRAME,
                                                         1);
    frame_m_edit->TB_Func_13("interface\\frame\\ub_pet_wnd_", 1, 0);

    RECT rect_background_m_edit = {rect_m_edit_frame.left + 2,
                                   rect_m_edit_frame.top + 2,
                                   rect_m_edit_frame.right - 4,
                                   rect_m_edit_frame.bottom - 4};

    CIFNormalTile *tile_m_edit = (CIFNormalTile *) CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFNormalTile),
                                                                  rect_background_m_edit,
                                                                  GDR_CHARINFO_RT_NORMALTILE,
                                                                  1);
    tile_m_edit->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_d.ddj", 1, 0);*/
///////// m_edit2
   /* RECT rect_m_edit2 = {210,140,144,20};
    m_edit2 = (CIFStatic *) (CIFStatic *) CreateInstance(this,
                                                    GFX_RUNTIME_CLASS(CIFStatic),
                                                     rect_m_edit2,
                                                    GDR_CHARINFO_RT_EDIT2,
                                                    1);
    m_edit2->BringToFront();
    m_edit2->TB_Func_5(1);
    RECT rect_m_edit_frame2 =  {rect_m_edit2.left -2,
                                rect_m_edit2.top -2,
                                rect_m_edit2.right +4,
                                rect_m_edit2.bottom +4};
    CIFFrame *frame_m_edit2 = (CIFFrame *) CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFFrame),
                                                          rect_m_edit_frame2,
                                                         GDR_CHARINFO_RT_FRAME,
                                                         1);
    frame_m_edit2->TB_Func_13("interface\\frame\\ub_pet_wnd_", 1, 0);

    RECT rect_background_m_edit2 = {rect_m_edit_frame2.left + 2,
                                    rect_m_edit_frame2.top + 2,
                                    rect_m_edit_frame2.right - 4,
                                    rect_m_edit_frame2.bottom - 4};

    CIFNormalTile *tile_m_edit2 = (CIFNormalTile *) CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFNormalTile),
                                                                   rect_background_m_edit2,
                                                                  GDR_CHARINFO_RT_NORMALTILE,
                                                                  1);
    tile_m_edit2->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_d.ddj", 1, 0);*/

////////// tooltip1
   /* RECT rect_m_tooltip_lable = {rect_m_edit.left + 10,
                                 rect_m_edit.top - 20,
                                 rect_m_edit.right - 20,
                                 10};
    m_custom_label_tooltip = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                 GFX_RUNTIME_CLASS(CIFStatic),
                                                                 rect_m_tooltip_lable,
                                                                 GDR_CHARINFO_RT_TOOLTIP,
                                                                 1);
    wchar_t buffer[255];
    swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_ST_CHARINFO_TOOLTIP"));
    m_custom_label_tooltip ->SetText(buffer);*/
 ////////// tooltip2
    /*RECT rect_m_tooltip_lable2 = {rect_m_edit2.left + 10,
                                 rect_m_edit2.top - 20,
                                 rect_m_edit2.right - 20,
                                 10};
    m_custom_label_tooltip2 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                 GFX_RUNTIME_CLASS(CIFStatic),
                                                                 rect_m_tooltip_lable2,
                                                                 GDR_CHARINFO_RT_TOOLTIP,
                                                                 1);
    wchar_t buffer2[255];
    swprintf_s(buffer2, TSM_GETTEXTPTR("UIIT_ST_CHARINFO_TOOLTIP2"));
    m_custom_label_tooltip2 ->SetText(buffer2);*/


///////// button
    RECT rect_button = {240,180,16,35};
    //RECT rect_button = {35, 70, 140, 30};
    CIFButton *btn = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button,
                                                         GDR_CHARINFO_RT_BTN_APPLY,
                                                         1);
    btn->TB_Func_13("interface\\quick_slot\\qsl_hclose_button.ddj", 1, 1);
    btn->MoveGWnd(this->GetPos().x+205,this->GetPos().y+1);
/////////

///////// Slot1 weapon
    RECT rect_Slot1_lable = {30,20,56,56};
    CIFStatic *statics = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                 GFX_RUNTIME_CLASS(CIFStatic),
                                                                 rect_Slot1_lable,
                                                                 17,
                                                                 1);
    statics->TB_Func_13("interface\\equipment\\equip_slot_weapon.ddj", 1, 1);

    RECT rect_Slot1 ={rect_Slot1_lable.left + 12,
                      rect_Slot1_lable.top + 12,
                      rect_Slot1_lable.right - 24,
                      rect_Slot1_lable.bottom - 24};
    //RECT rect_button = {35, 70, 140, 30};
    m_slot1 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                         rect_Slot1,
                                                        GDR_CHARINFO_RT_SLOT1,
                                                         1);

///////// Slot2 shield
    RECT rect_Slot2_lable = {122,20,56,56};
    CIFStatic *statics2 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                             GFX_RUNTIME_CLASS(CIFStatic),
                                                              rect_Slot2_lable,
                                                             17,
                                                             1);
    statics2->TB_Func_13("interface\\equipment\\equip_slot_shield.ddj", 1, 1);

    RECT rect_Slot2 ={rect_Slot2_lable.left + 12,
                      rect_Slot2_lable.top + 12,
                      rect_Slot2_lable.right - 24,
                      rect_Slot2_lable.bottom - 24};
    m_slot2 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot2,
                                                        GDR_CHARINFO_RT_SLOT2,
                                                        1);
///////// Slot3 helm
    RECT rect_Slot3_lable = {36,90,40,40};
    CIFStatic *statics3 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                              GFX_RUNTIME_CLASS(CIFStatic),
                                                              rect_Slot3_lable,
                                                              17,
                                                              1);
    statics3->TB_Func_13("interface\\equipment\\equip_slot_helm.ddj", 1, 1);

    RECT rect_Slot3 ={rect_Slot3_lable.left + 6,
                      rect_Slot3_lable.top + 6,
                      rect_Slot3_lable.right - 12,
                      rect_Slot3_lable.bottom - 12};
    m_slot3 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot3,
                                                        GDR_CHARINFO_RT_SLOT3,
                                                        1);

    ///////// Slot4 shoulderguard
    RECT rect_Slot4_lable = {128,90,40,40};
    CIFStatic *statics4 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                              GFX_RUNTIME_CLASS(CIFStatic),
                                                              rect_Slot4_lable,
                                                              17,
                                                              1);
    statics4->TB_Func_13("interface\\equipment\\equip_slot_shoulderguard.ddj", 1, 1);

    RECT rect_Slot4 ={rect_Slot4_lable.left + 6,
                      rect_Slot4_lable.top + 6,
                      rect_Slot4_lable.right - 12,
                      rect_Slot4_lable.bottom - 12};
    m_slot4 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot4,
                                                        GDR_CHARINFO_RT_SLOT4,
                                                        1);
    ///////// Slot5 mail
    RECT rect_Slot5_lable = {36,145,40,40};
    CIFStatic *statics5 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                              GFX_RUNTIME_CLASS(CIFStatic),
                                                              rect_Slot5_lable,
                                                              17,
                                                              1);
    statics5->TB_Func_13("interface\\equipment\\equip_slot_mail.ddj", 1, 1);

    RECT rect_Slot5 ={rect_Slot5_lable.left + 6,
                      rect_Slot5_lable.top + 6,
                      rect_Slot5_lable.right - 12,
                      rect_Slot5_lable.bottom - 12};
    m_slot5 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot5,
                                                        GDR_CHARINFO_RT_SLOT5,
                                                        1);
    ///////// Slot6 gauntlet
    RECT rect_Slot6_lable = {128,145,40,40};
    CIFStatic *statics6 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                              GFX_RUNTIME_CLASS(CIFStatic),
                                                              rect_Slot6_lable,
                                                              17,
                                                              1);
    statics6->TB_Func_13("interface\\equipment\\equip_slot_gauntlet.ddj", 1, 1);

    RECT rect_Slot6 ={rect_Slot6_lable.left + 6,
                      rect_Slot6_lable.top + 6,
                      rect_Slot6_lable.right - 12,
                      rect_Slot6_lable.bottom - 12};
    m_slot6 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot6,
                                                        GDR_CHARINFO_RT_SLOT6,
                                                        1);
    ///////// Slot7 pants
    RECT rect_Slot7_lable = {36,200,40,40};
    CIFStatic *statics7 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                              GFX_RUNTIME_CLASS(CIFStatic),
                                                              rect_Slot7_lable,
                                                              17,
                                                              1);
    statics7->TB_Func_13("interface\\equipment\\equip_slot_pants.ddj", 1, 1);

    RECT rect_Slot7 ={rect_Slot7_lable.left + 6,
                      rect_Slot7_lable.top + 6,
                      rect_Slot7_lable.right - 12,
                      rect_Slot7_lable.bottom - 12};
    m_slot7 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot7,
                                                        GDR_CHARINFO_RT_SLOT7,
                                                        1);
    ///////// Slot8 boots
    RECT rect_Slot8_lable = {128,200,40,40};
    CIFStatic *statics8 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                              GFX_RUNTIME_CLASS(CIFStatic),
                                                              rect_Slot8_lable,
                                                              17,
                                                              1);
    statics8->TB_Func_13("interface\\equipment\\equip_slot_boots.ddj", 1, 1);

    RECT rect_Slot8 ={rect_Slot8_lable.left + 6,
                      rect_Slot8_lable.top + 6,
                      rect_Slot8_lable.right - 12,
                      rect_Slot8_lable.bottom - 12};
    m_slot8 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot8,
                                                        GDR_CHARINFO_RT_SLOT8,
                                                        1);
    ///////// Slot9 earring
    RECT rect_Slot9_lable = {36,255,40,40};
    CIFStatic *statics9 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                              GFX_RUNTIME_CLASS(CIFStatic),
                                                              rect_Slot9_lable,
                                                              17,
                                                              1);
    statics9->TB_Func_13("interface\\equipment\\equip_slot_earring.ddj", 1, 1);

    RECT rect_Slot9 ={rect_Slot9_lable.left + 6,
                      rect_Slot9_lable.top + 6,
                      rect_Slot9_lable.right - 12,
                      rect_Slot9_lable.bottom - 12};
    m_slot9 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot9,
                                                        GDR_CHARINFO_RT_SLOT9,
                                                        1);
    ///////// Slot10 necklace
    RECT rect_Slot10_lable = {128,255,40,40};
    CIFStatic *statics10 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                              GFX_RUNTIME_CLASS(CIFStatic),
                                                              rect_Slot10_lable,
                                                              17,
                                                              1);
    statics10->TB_Func_13("interface\\equipment\\equip_slot_necklace.ddj", 1, 1);

    RECT rect_Slot10 ={rect_Slot10_lable.left + 6,
                       rect_Slot10_lable.top + 6,
                       rect_Slot10_lable.right - 12,
                       rect_Slot10_lable.bottom - 12};
    m_slot10 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot10,
                                                        GDR_CHARINFO_RT_SLOT10,
                                                        1);
    ///////// Slot11 l_ring
    RECT rect_Slot11_lable = {36,310,40,40};
    CIFStatic *statics11 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                               GFX_RUNTIME_CLASS(CIFStatic),
                                                               rect_Slot11_lable,
                                                               17,
                                                               1);
    statics11->TB_Func_13("interface\\equipment\\equip_slot_l_ring.ddj", 1, 1);

    RECT rect_Slot11 ={rect_Slot11_lable.left + 6,
                       rect_Slot11_lable.top + 6,
                       rect_Slot11_lable.right - 12,
                       rect_Slot11_lable.bottom - 12};
    m_slot11 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                         rect_Slot11,
                                                         GDR_CHARINFO_RT_SLOT11,
                                                         1);
    ///////// Slot12 r_ring
    RECT rect_Slot12_lable = {128,310,40,40};
    CIFStatic *statics12 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                               GFX_RUNTIME_CLASS(CIFStatic),
                                                               rect_Slot12_lable,
                                                               17,
                                                               1);
    statics12->TB_Func_13("interface\\equipment\\equip_slot_r_ring.ddj", 1, 1);

    RECT rect_Slot12 ={rect_Slot12_lable.left + 6,
                       rect_Slot12_lable.top + 6,
                       rect_Slot12_lable.right - 12,
                       rect_Slot12_lable.bottom - 12};
    m_slot12 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                         rect_Slot12,
                                                         GDR_CHARINFO_RT_SLOT12,
                                                         1);

    ///////// Slot13
    RECT rect_Slot13_lable = {248,320,56,56};
    CIFStatic *statics13 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                               GFX_RUNTIME_CLASS(CIFStatic),
                                                               rect_Slot13_lable,
                                                               17,
                                                               1);
    statics13->TB_Func_13("interface\\equipment\\equip_slot_shield.ddj", 1, 1);

    RECT rect_Slot13 ={rect_Slot13_lable.left + 12,
                       rect_Slot13_lable.top + 12,
                       rect_Slot13_lable.right - 24,
                       rect_Slot13_lable.bottom - 24};
    m_slot = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                       rect_Slot13,
                                                         GDR_CHARINFO_RT_SLOT13,
                                                         1);
    ////////// tooltip2
    RECT rect_m_tooltip_lable3 = {rect_Slot13_lable.left + 10,
                                  rect_Slot13_lable.top - 20,
                                  rect_Slot13_lable.right - 20,
                                  10};
    m_custom_label_tooltip3 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFStatic),
                                                                  rect_m_tooltip_lable3,
                                                                  GDR_CHARINFO_RT_TOOLTIP,
                                                                  1);
    wchar_t buffer3[255];
    swprintf_s(buffer3, TSM_GETTEXTPTR("UIIT_ST_CHARINFO_TOOLTIP4"));
    m_custom_label_tooltip3->SetText(buffer3);

    statics13->ShowGWnd(false);
    m_slot->ShowGWnd(false);
    m_custom_label_tooltip3->ShowGWnd(false);


/////////
    statics->SetText(L"6");
    statics2->SetText(L"7");
    statics3->SetText(L"0");
    statics4->SetText(L"2");
    statics5->SetText(L"1");
    statics6->SetText(L"3");
    statics7->SetText(L"4");
    statics8->SetText(L"5");
    statics9->SetText(L"9");
    statics10->SetText(L"10");
    statics11->SetText(L"11");
    statics12->SetText(L"12");

    this->ResetPosition();
    this->ShowGWnd(false);
    return true;
}



void CIFSTCharItemInfo::OnUpdate() {

    if( this->IsVisible() && g_CurrentIfUnderCursor->IsSame(GFX_RUNTIME_CLASS(CIFSlotWithHelp)) && g_CurrentIfUnderCursor->UniqueID() > 6665 && g_CurrentIfUnderCursor->UniqueID() < 6678)
    {
        std::n_wstring CharName = CPSMission::CharNameSelected;
        std::n_wstring Slot;
        if(g_CurrentIfUnderCursor->UniqueID() == 6666)
            Slot=L"6";
        if(g_CurrentIfUnderCursor->UniqueID() == 6667)
            Slot=L"7";
        if(g_CurrentIfUnderCursor->UniqueID() == 6668)
            Slot=L"0";
        if(g_CurrentIfUnderCursor->UniqueID() == 6669)
            Slot=L"2";
        if(g_CurrentIfUnderCursor->UniqueID() == 6670)
            Slot=L"1";
        if(g_CurrentIfUnderCursor->UniqueID() == 6671)
            Slot=L"3";
        if(g_CurrentIfUnderCursor->UniqueID() == 6672)
            Slot=L"4";
        if(g_CurrentIfUnderCursor->UniqueID() == 6673)
            Slot=L"5";
        if(g_CurrentIfUnderCursor->UniqueID() == 6674)
            Slot=L"9";
        if(g_CurrentIfUnderCursor->UniqueID() == 6675)
            Slot=L"10";
        if(g_CurrentIfUnderCursor->UniqueID() == 6676)
            Slot=L"11";
        if(g_CurrentIfUnderCursor->UniqueID() == 6677)
            Slot=L"12";

        std::n_wstring SlotNew = L"<";
        SlotNew += Slot;
        SlotNew += L">";
        std::string nameinfo = TO_STRING(CharName) + TO_STRING(SlotNew) ;
        if (SCharItemInfoList.find(nameinfo) != SCharItemInfoList.end() ) //item found
        {
            RECT r1;
            GetWindowRect(theApp.GetHWnd(), &r1);
            POINT mMouse;
            GetCursorPos(&mMouse);

            CIFInventory *pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
            CIFSlotWithHelp *pEmptySlot;
            bool isFound = false;
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++) {
                CIFSlotWithHelp *pSlot = *reinterpret_cast<CIFSlotWithHelp **>(pInventory->pSlots + (i * 4));
                if (!pSlot->ItemInfo || pSlot->ItemInfo == 0) {
                    pEmptySlot = pSlot;
                    isFound = true;
                    break;
                }
            }
            if (isFound && pEmptySlot && !pEmptySlot->ItemInfo) {

                m_slot = pEmptySlot;

                LastEmptySlot = pEmptySlot->UniqueID() - 100 + 0xD;
                if (pEmptySlot->ItemInfo == NULL && pEmptySlot->ItemInfo == 0) {
                    byte Status = 0x1;
                    byte Action = 0x6;
                    CMsgStreamBuffer *pBuffer = new CMsgStreamBuffer(0xB034);
                    pBuffer->Write(&Status, 1);
                    pBuffer->Write(&Action, 1);
                    pBuffer->Write(&LastEmptySlot, 1);
                    for (size_t i = 0; i < SCharItemInfoList[nameinfo].buffer->GetLength(); ++i) {
                        UINT8 strLens;
                        SCharItemInfoList[nameinfo].buffer->Read(&strLens, 1);
                        pBuffer->Write(&strLens, 1);
                    }
                    SCharItemInfoList[nameinfo].buffer->m_currentReadBytes = 0;
                    //firstly get rid of the annoying message (we should hide it xd)
                    g_MemoryHelper->UnProtect(reinterpret_cast<void *>(0x0087C1F0), 2);
                    *(BYTE *) (0x0087C1F0) = 0xEB;
                    *(BYTE *) (0x0087C1F0 + 1) = 0x37;
                    g_MemoryHelper->ReProtect();
                    g_MemoryHelper->UnProtect(reinterpret_cast<void *>(0x0087C15B), 1);
                    *(BYTE *) (0x0087C15B) = 0x75;
                    g_MemoryHelper->ReProtect();
                    //first of all make a copy of original item
                    p_CNetProcessIn->ProcessItemMovementResult(pBuffer);
                    //after giving the item, rollback the item gained msg so player will keep seeing it
                    g_MemoryHelper->UnProtect(reinterpret_cast<void *>(0x0087C1F0), 2);
                    *(BYTE *) (0x0087C1F0) = 0x72;
                    *(BYTE *) (0x0087C1F0 + 1) = 0x05;
                    g_MemoryHelper->ReProtect();
                    g_MemoryHelper->UnProtect(reinterpret_cast<void *>(0x0087C15B), 1);
                    *(BYTE *) (0x0087C15B) = 0x74;
                    g_MemoryHelper->ReProtect();

                    m_slot->ItemInfo = pEmptySlot->ItemInfo;
                    //pEmptySlot->m_bVisible = false;
                    if (m_slot->ItemInfo) {
                        POINT m_show_point;
                        m_show_point.x = mMouse.x - (r1.left + 165);
                        m_show_point.y = mMouse.y - r1.top;
                        g_pCGInterface->m_helperWindow->ShowGWnd(true);
                        (*(void(__thiscall**)(CIFTextBox*, int, int))(*(DWORD32*)(g_pCGInterface->m_helperWindow->m_textBox) + 0x54))(g_pCGInterface->m_helperWindow->m_textBox,0xC8,1);

                        g_pCGInterface->m_helperWindow->m_ownerWindow = m_slot;
                        g_pCGInterface->m_helperWindow->Reset();
                        g_pCGInterface->N00002717->Reset();
                        m_slot->HelperBubbleInventoryAndEquipment(g_pCGInterface->m_helperWindow);

                        g_pCGInterface->m_helperWindow->sub_777020();
                        g_pCGInterface->m_helperWindow->MoveGWnd(m_show_point.x, m_show_point.y);
                        g_pCGInterface->m_helperWindow->sub_776C00(&g_pCGInterface->m_helperWindow->GetBounds(), g_pCGInterface->m_helperWindow->N00000618);
                        g_pCGInterface->m_helperWindow->BringToFront();

                        g_pCGInterface->N00002717->sub_777020();
                        g_pCGInterface->N00002717->MoveGWnd(m_show_point.x, m_show_point.y);
                        g_pCGInterface->N00002717->sub_776C00(&g_pCGInterface->N00002717->GetBounds(), g_pCGInterface->N00002717->N00000618);
                        g_pCGInterface->N00002717->BringToFront();
                    }
                }

            }
            else
            {
                g_pCGInterface->ShowMessage_Quest(TSM_GETTEXTPTR("UIIT_ST_CHATITEMLINK_NOTICE"));
            }
            if (LastEmptySlot > 0)
            {
                CMsgStreamBuffer* pBuffers = new CMsgStreamBuffer(0xB034);
                UINT8 Statuss = 0x1 ;
                UINT8 Actions = 0x7 ;
                pBuffers->Write(&Statuss,1);
                pBuffers->Write(&Actions,1);
                pBuffers->Write(&LastEmptySlot,1);
                p_CNetProcessIn->ProcessItemMovementResult(pBuffers);
                LastEmptySlot=0;
                m_slot->ItemInfo = NULL;
                pEmptySlot->ItemInfo=NULL;
            }
        }
    }

}
int CIFSTCharItemInfo::OnMouseMove(int a1, int x, int y) {
this->BringToFront();

    return 0;
}
void CIFSTCharItemInfo::On_BtnClick() {

    this->OnCloseWnd();
   /* std::n_wstring input_text = m_edit->GetNText();
    std::n_wstring input_text2 = m_edit2->GetNText();
    if(input_text.empty() || input_text2.empty())
    {
        wchar_t message[1000];
        swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_CHARINFO_TOOLTIP3"));

        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 255, 0, 0);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    } else {
        CMsgStreamBuffer buf(0x1319);
        buf << TO_NSTRING(this->m_edit->GetNText());
        buf << std::n_string("!CHECKCHARINFO");
        buf << TO_NSTRING(this->m_edit2->GetNText());
        SendMsg(buf);
        m_slot->TB_Func_13("", 0, 0);
        m_slot1->TB_Func_13("", 0, 0);
        m_slot2->TB_Func_13("", 0, 0);
        m_slot3->TB_Func_13("", 0, 0);
        m_slot4->TB_Func_13("", 0, 0);
        m_slot5->TB_Func_13("", 0, 0);
        m_slot6->TB_Func_13("", 0, 0);
        m_slot7->TB_Func_13("", 0, 0);
        m_slot8->TB_Func_13("", 0, 0);
        m_slot9->TB_Func_13("", 0, 0);
        m_slot10->TB_Func_13("", 0, 0);
        m_slot11->TB_Func_13("", 0, 0);
        m_slot12->TB_Func_13("", 0, 0);
        SCharItemInfoList.clear();
    }*/
}
void CIFSTCharItemInfo::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 780;
    this->MoveGWnd(PosX, PosY);
}
void CIFSTCharItemInfo::Showbuble(CSOItem *ItemInfo,CIFSlotWithHelp *m_slot)
{
    RECT r1;
    GetWindowRect(theApp.GetHWnd(), &r1);
    POINT mMouse;
    GetCursorPos(&mMouse);
    //m_slot->FUN_006871d0(ItemInfo);
    *((DWORD*)ItemInfo + 0x16)  = 7;
    *((DWORD*)ItemInfo + 0x15) = 0;
    *((DWORD*)ItemInfo + 0x11) = 0;
    *((DWORD*)ItemInfo + 0x30) = 7;
    *((DWORD*)ItemInfo + 0x2f) = 0;
    *((DWORD*)ItemInfo + 0x2b) = 0;
    int v2 = reinterpret_cast<DWORD(__stdcall*)()>(0x5CED70)();
    *((DWORD*)ItemInfo + 0x32) = v2;
    *(BYTE*)(v2 + 0x15) = 1;
    *(DWORD *)(*((DWORD *)ItemInfo + 0x32) + 4) = *((DWORD *)ItemInfo + 0x32);
    **((DWORD**)ItemInfo + 0x32) = *((DWORD*)ItemInfo + 0x32);
    *(DWORD *)(*((DWORD *)ItemInfo + 0x32) + 8) = *((DWORD *)ItemInfo + 0x32);
    *((DWORD*)ItemInfo + 0x33)= 0;
    *((DWORD*)ItemInfo + 0x35)= 0;
    *((DWORD*)ItemInfo + 0x36)= 0;
    *((DWORD*)ItemInfo + 0x37)= 0;
    //reinterpret_cast<void(__thiscall *)(DWORD*)>(0x008ba3d0)(((DWORD*)Slot->ItemInfo + 0x38));
    *((DWORD*)ItemInfo + 0x52)= 0;
    *((DWORD*)ItemInfo + 0x53)= 0;
    *((DWORD*)ItemInfo + 0x54)= 0;
    *((DWORD*)ItemInfo + 0x56)= 0;
    *((DWORD*)ItemInfo + 0x57)= 0;
    *((DWORD*)ItemInfo + 0x58)= 0;
    //reinterpret_cast<void(__thiscall *)(DWORD*)>(0x008ba750)(((DWORD*)Slot->ItemInfo + 0x5a));
    //reinterpret_cast<void(__thiscall *)(DWORD*)>(0x008bcbc0)(((DWORD*)Slot->ItemInfo));
    //FUN_008bef90
    //ItemInfo 0xA4
    //�㵽��Ʒ��Ϣ��
    POINT m_show_point;
    m_show_point.x = mMouse.x - (r1.left + 165);
    m_show_point.y = mMouse.y - r1.top;
    g_pCGInterface->m_helperWindow->ShowGWnd(true);
    (*(void(__thiscall**)(CIFTextBox*, int, int))(*(DWORD32*)(g_pCGInterface->m_helperWindow->m_textBox) + 0x54))(g_pCGInterface->m_helperWindow->m_textBox,0xC8,1);

    g_pCGInterface->m_helperWindow->m_ownerWindow = m_slot;
    g_pCGInterface->m_helperWindow->Reset();
    g_pCGInterface->N00002717->Reset();
    m_slot->HelperBubbleInventoryAndEquipment(g_pCGInterface->m_helperWindow);

    g_pCGInterface->m_helperWindow->sub_777020();
    g_pCGInterface->m_helperWindow->MoveGWnd(m_show_point.x, m_show_point.y);
    g_pCGInterface->m_helperWindow->sub_776C00(&g_pCGInterface->m_helperWindow->GetBounds(), g_pCGInterface->m_helperWindow->N00000618);
    g_pCGInterface->m_helperWindow->BringToFront();

    g_pCGInterface->N00002717->sub_777020();
    g_pCGInterface->N00002717->MoveGWnd(m_show_point.x, m_show_point.y);
    g_pCGInterface->N00002717->sub_776C00(&g_pCGInterface->N00002717->GetBounds(), g_pCGInterface->N00002717->N00000618);
    g_pCGInterface->N00002717->BringToFront();


}