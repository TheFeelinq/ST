//
// Created by Admin on 26/6/2021.
//

#include "IFSTExtraFeature.h"
#include "IFNormalTile.h"
#include "ICPlayer.h"
#include "Game.h"
#include "IFStretchWnd.h"
#include <ctime>
#include "BSLib/BSLib.h"
#include "CPSMission.h"
#include "GInterface.h"
#include "Rebot.h"
#include "IFChatViewer.h"
#include <BSLib\multiBYTE.h>
#include <imgui/imgui.h>

#define GDR_EXTRAFEATURE_RT_LABEL 10
#define GDR_EXTRAFEATURE_RT_BTN_APPLY 20
#define GDR_EXTRAFEATURE_RT_BTN2_APPLY 21
#define GDR_EXTRAFEATURE_RT_BTN3_APPLY 22
#define GDR_EXTRAFEATURE_RT_BTN4_APPLY 23
#define GDR_EXTRAFEATURE_RT_BTN5_APPLY 24
#define GDR_EXTRAFEATURE_RT_BTN6_APPLY 25
#define GDR_EXTRAFEATURE_RT_BTN7_APPLY 26
#define GDR_EXTRAFEATURE_RT_BTN8_APPLY 27
#define GDR_EXTRAFEATURE_RT_FRAME 12
#define GDR_EXTRAFEATURE_RT_NORMALTILE 13
#define GDR_EXTRAFEATURE_RT_EDIT 14
#define GDR_EXTRAFEATURE_RT_TOOLTIP 16
#define GDR_EXTRAFEATURE_RT_SLOT1 7777
#define GDR_EXTRAFEATURE_RT_SLOT2 7778
#define GDR_EXTRAFEATURE_RT_SLOT3 7779
#define GDR_EXTRAFEATURE_RT_SLOT4 7780
#define GDR_EXTRAFEATURE_RT_SLOT5 7880
#define GDR_EXTRAFEATURE_RT_SLOT6 7881
#define GDR_EXTRAFEATURE_RT_STRETCHWND 15
#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)
#define CLIENT_SCREEN_HEIGHT (*(int*)0x00ED7CBC)
//SKILL_MALL_DAMAGE_INC_20P_SCROLL_01
//SKILL_MALL_DAMAGE_ABS_20P_SCROLL_01

BYTE CIFSTExtraFeature::m_dame_inc_slot;
BYTE CIFSTExtraFeature::m_dame_abs_slot;
BYTE CIFSTExtraFeature::m_dame_Increasebubble_slot;
BYTE CIFSTExtraFeature::m_dame_absorbbubble_slot;
BYTE CIFSTExtraFeature::m_ressurect_slot;
BYTE CIFSTExtraFeature::m_berserker_potion_slot;

GFX_IMPLEMENT_DYNCREATE(CIFSTExtraFeature, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTExtraFeature, CIFMainFrame)
                    ONG_COMMAND(GDR_EXTRAFEATURE_RT_BTN_APPLY, &On_BtnClickSetAutoABS)
                    ONG_COMMAND(GDR_EXTRAFEATURE_RT_BTN2_APPLY, &On_BtnClickSetAutoINC)
                    ONG_COMMAND(GDR_EXTRAFEATURE_RT_BTN3_APPLY, &On_BtnClickSetAutoDamageabsorbbubble)
                    ONG_COMMAND(GDR_EXTRAFEATURE_RT_BTN4_APPLY, &On_BtnClickSetAutoDamageIncreasebubble)
                    ONG_COMMAND(GDR_EXTRAFEATURE_RT_BTN5_APPLY, &On_BtnClickSetAutoUpSkill)
                    ONG_COMMAND(GDR_EXTRAFEATURE_RT_BTN7_APPLY, &On_BtnClickSetAutoRessurect)
                    ONG_COMMAND(GDR_EXTRAFEATURE_RT_BTN8_APPLY, &On_BtnClickSetAutoBerserkerPotion)
GFX_END_MESSAGE_MAP()


CIFSTExtraFeature::CIFSTExtraFeature() :
        m_custom_label(NULL) {

}

bool CIFSTExtraFeature::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);
    RECT rect_m_tile = {170, 9, 100, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIT_STT_EXTRAFEATURE_VIEWER"));

    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);
///////frame
    wnd_size sz = this->GetSize();
    RECT rect_frame = { 13,40,423,423 };

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame,
                                                  GDR_EXTRAFEATURE_RT_FRAME,
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
                                                           GDR_EXTRAFEATURE_RT_NORMALTILE,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);


/*    RECT rect_edit_interface = {79,65,162,20};
    CIFStretchWnd *edit_interface = (CIFStretchWnd *) CreateInstance(this,
                                                                     GFX_RUNTIME_CLASS(CIFStretchWnd),
                                                                     rect_edit_interface,
                                                                     GDR_EXTRAFEATURE_RT_STRETCHWND,
                                                                     1);
    edit_interface->TB_Func_13("interface\\ifcommon\\com_blacksquare_", 1, 0);*/
////////// tooltip
    RECT rect_m_tooltip_lable = {30,75,200,10};
    m_custom_label_tooltip = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                 GFX_RUNTIME_CLASS(CIFStatic),
                                                                 rect_m_tooltip_lable,
                                                                 GDR_EXTRAFEATURE_RT_TOOLTIP,
                                                                 1);
    wchar_t buffer[255];
    swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP2"));
    m_custom_label_tooltip ->SetText(buffer);
    m_custom_label_tooltip->TB_Func_5(0); //can le
////////// tooltip2
    RECT rect_m_tooltip_lable2 = {30,130,200,10};
    m_custom_label_tooltip2 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                 GFX_RUNTIME_CLASS(CIFStatic),
                                                                 rect_m_tooltip_lable2,
                                                                 GDR_EXTRAFEATURE_RT_TOOLTIP,
                                                                 1);
    wchar_t buffer2[255];
    swprintf_s(buffer2, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP"));
    m_custom_label_tooltip2 ->SetText(buffer2);
    m_custom_label_tooltip2 ->TB_Func_5(0);

    ////////// tooltip3
    RECT rect_m_tooltip_lable3 = {30,410,200,10};
    m_custom_label_tooltip3 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFStatic),
                                                                  rect_m_tooltip_lable3,
                                                                  GDR_EXTRAFEATURE_RT_TOOLTIP,
                                                                  1);
    wchar_t buffer3[255];
    swprintf_s(buffer3, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP3"));
    m_custom_label_tooltip3 ->SetText(buffer3);
    m_custom_label_tooltip3 ->TB_Func_5(0);
    m_custom_label_tooltip3->m_FontTexture.SetColor(0xFFF18706);
    ////////// tooltip4
    RECT rect_m_tooltip_lable4 = {30,430,200,10};
    m_custom_label_tooltip4 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFStatic),
                                                                  rect_m_tooltip_lable4,
                                                                  GDR_EXTRAFEATURE_RT_TOOLTIP,
                                                                  1);
    wchar_t buffer4[255];
    swprintf_s(buffer4, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP4"));
    m_custom_label_tooltip4 ->SetText(buffer4);
    m_custom_label_tooltip4 ->TB_Func_5(0);
    m_custom_label_tooltip4->m_FontTexture.SetColor(0xFFF18706);
    ////////// tooltip5
    RECT rect_m_tooltip_lable5 = {30,185,200,10};
    m_custom_label_tooltip5 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFStatic),
                                                                  rect_m_tooltip_lable5,
                                                                  GDR_EXTRAFEATURE_RT_TOOLTIP,
                                                                  1);
    wchar_t buffer5[255];
    swprintf_s(buffer5, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP6"));
    m_custom_label_tooltip5 ->SetText(buffer5);
    m_custom_label_tooltip5 ->TB_Func_5(0);
    ////////// tooltip6
    RECT rect_m_tooltip_lable6 = {30,240,200,10};
    m_custom_label_tooltip6 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFStatic),
                                                                  rect_m_tooltip_lable6,
                                                                  GDR_EXTRAFEATURE_RT_TOOLTIP,
                                                                  1);
    wchar_t buffer6[255];
    swprintf_s(buffer6, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP5"));
    m_custom_label_tooltip6 ->SetText(buffer6);
    m_custom_label_tooltip6 ->TB_Func_5(0);
    ////////// tooltip7
    RECT rect_m_tooltip_lable7 = {30,295,200,10};
    m_custom_label_tooltip7 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFStatic),
                                                                  rect_m_tooltip_lable7,
                                                                  GDR_EXTRAFEATURE_RT_TOOLTIP,
                                                                  1);
    wchar_t buffer7[255];
    swprintf_s(buffer7, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP14"));
    m_custom_label_tooltip7 ->SetText(buffer7);
    m_custom_label_tooltip7 ->TB_Func_5(0);
    ////////// tooltip8
    RECT rect_m_tooltip_lable8 = {30,350,200,10};
    m_custom_label_tooltip8 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFStatic),
                                                                  rect_m_tooltip_lable8,
                                                                  GDR_EXTRAFEATURE_RT_TOOLTIP,
                                                                  1);
    wchar_t buffer8[255];
    swprintf_s(buffer8, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_AUTO_RESSURECT"));
    m_custom_label_tooltip8 ->SetText(buffer8);
    m_custom_label_tooltip8 ->TB_Func_5(0);
///////// button
    RECT rect_button = {340,70,70,23};
    //RECT rect_button = {35, 70, 140, 30};
    m_btn1 = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button,
                                                         GDR_EXTRAFEATURE_RT_BTN_APPLY,
                                                         1);

    m_btn1->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
    m_btn1->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);
///////// button2
    RECT rect_button2 = {340,125,70,23};
    //RECT rect_button = {35, 70, 140, 30};
    m_btn2 = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button2,
                                                         GDR_EXTRAFEATURE_RT_BTN2_APPLY,
                                                         1);

    m_btn2->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
    m_btn2->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);
///////// button3
    RECT rect_button3 = {340,180,70,23};
    m_btn3 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button3,
                                                          GDR_EXTRAFEATURE_RT_BTN3_APPLY,
                                                          1);

    m_btn3->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
    m_btn3->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);
///////// button4
    RECT rect_button4 = {340,235,70,23};
    m_btn4 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button4,
                                                          GDR_EXTRAFEATURE_RT_BTN4_APPLY,
                                                          1);

    m_btn4->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
    m_btn4->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);
///////// button5
    RECT rect_button5 = {340,285,70,23};
    m_btn5 = (CIFButton *) CGWnd::CreateInstance(this,
                                                 GFX_RUNTIME_CLASS(CIFButton),
                                                 rect_button5,
                                                 GDR_EXTRAFEATURE_RT_BTN5_APPLY,
                                                 1);

    m_btn5->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP15"));
    m_btn5->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);
 ///////// button6
    RECT rect_button6 = {260,280,32,32};
    m_btn6 = (CIFButton *) CGWnd::CreateInstance(this,
                                                 GFX_RUNTIME_CLASS(CIFButton),
                                                 rect_button6,
                                                 GDR_EXTRAFEATURE_RT_BTN6_APPLY,
                                                 1);

    m_btn6->TB_Func_13("icon\\action\\cos_cmd_coswindow.ddj", 1, 1);
    std::n_wstring str = TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP13");
    m_btn6->SetTooltipText(&str);
    m_btn6->FUN_00652d20(128);

    ///////// button7
    RECT rect_button7 = {340,345,70,23};
    m_btn7 = (CIFButton *) CGWnd::CreateInstance(this,
                                                 GFX_RUNTIME_CLASS(CIFButton),
                                                 rect_button7,
                                                 GDR_EXTRAFEATURE_RT_BTN7_APPLY,
                                                 1);

    m_btn7->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
    m_btn7->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    ///////// button7
    RECT rect_button8 = {340,290,70,23};
    m_btn8 = (CIFButton *) CGWnd::CreateInstance(this,
                                                 GFX_RUNTIME_CLASS(CIFButton),
                                                 rect_button8,
                                                 GDR_EXTRAFEATURE_RT_BTN8_APPLY,
                                                 1);

    m_btn8->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
    m_btn8->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);
/////////
    RECT rect_Slot1_lable = {255,60,46,46};

    CIFFrame *statics = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                    rect_Slot1_lable,
                                                  GDR_EXTRAFEATURE_RT_FRAME,
                                                  1);
    statics->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot1 ={rect_Slot1_lable.left + 6,
                      rect_Slot1_lable.top + 6,
                      rect_Slot1_lable.right - 12,
                      rect_Slot1_lable.bottom - 12};
    //RECT rect_button = {35, 70, 140, 30};
    m_slot1 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot1,
                                                        GDR_EXTRAFEATURE_RT_SLOT1,
                                                        1);
    //m_slot1->Type = 0x25;
    //m_slot1->field_0x380 = 1;
    //m_slot1->N0000074F = 1;
    //m_slot1->m_bClickable=0;
    //m_slot1->m_bDragable = 0;
/////
/////////
    RECT rect_Slot1_lable2 = {255,115,46,46};

    CIFFrame *statics2 = (CIFFrame *) CreateInstance(this,
                                                    GFX_RUNTIME_CLASS(CIFFrame),
                                                    rect_Slot1_lable2,
                                                    GDR_EXTRAFEATURE_RT_FRAME,
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
                                                        GDR_EXTRAFEATURE_RT_SLOT2,
                                                        1);
    //m_slot2->Type = 26;


/////
/////////
    RECT rect_Slot1_lable3 = {255,170,46,46};

    CIFFrame *statics3 = (CIFFrame *) CreateInstance(this,
                                                     GFX_RUNTIME_CLASS(CIFFrame),
                                                     rect_Slot1_lable3,
                                                     GDR_EXTRAFEATURE_RT_FRAME,
                                                     1);
    statics3->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot3 ={rect_Slot1_lable3.left + 6,
                      rect_Slot1_lable3.top + 6,
                      rect_Slot1_lable3.right - 12,
                      rect_Slot1_lable3.bottom - 12};

    m_slot3 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot3,
                                                        GDR_EXTRAFEATURE_RT_SLOT3,
                                                        1);
    //m_slot3->Type = 26;

 /////////
    RECT rect_Slot1_lable4 = {255,225,46,46};

    CIFFrame *statics4 = (CIFFrame *) CreateInstance(this,
                                                     GFX_RUNTIME_CLASS(CIFFrame),
                                                     rect_Slot1_lable4,
                                                     GDR_EXTRAFEATURE_RT_FRAME,
                                                     1);
    statics4->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot4 ={rect_Slot1_lable4.left + 6,
                      rect_Slot1_lable4.top + 6,
                      rect_Slot1_lable4.right - 12,
                      rect_Slot1_lable4.bottom - 12};

    m_slot4 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot4,
                                                        GDR_EXTRAFEATURE_RT_SLOT4,
                                                        1);
    //m_slot4->Type = 26;

    RECT rect_Slot1_lable5 = {255,335,46,46};

    CIFFrame *statics5 = (CIFFrame *) CreateInstance(this,
                                                     GFX_RUNTIME_CLASS(CIFFrame),
                                                     rect_Slot1_lable5,
                                                     GDR_EXTRAFEATURE_RT_FRAME,
                                                     1);
    statics5->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot5 ={rect_Slot1_lable5.left + 6,
                      rect_Slot1_lable5.top + 6,
                      rect_Slot1_lable5.right - 12,
                      rect_Slot1_lable5.bottom - 12};

    m_slot5 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot5,
                                                        GDR_EXTRAFEATURE_RT_SLOT5,
                                                        1);


    RECT rect_Slot1_lable6 =  {255,280,46,46};

    CIFFrame *statics6 = (CIFFrame *) CreateInstance(this,
                                                     GFX_RUNTIME_CLASS(CIFFrame),
                                                     rect_Slot1_lable6,
                                                     GDR_EXTRAFEATURE_RT_FRAME,
                                                     1);
    statics6->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);

    RECT rect_Slot6 ={rect_Slot1_lable6.left + 6,
                      rect_Slot1_lable6.top + 6,
                      rect_Slot1_lable6.right - 12,
                      rect_Slot1_lable6.bottom - 12};

    m_slot6 = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFSlotWithHelp),
                                                        rect_Slot6,
                                                        GDR_EXTRAFEATURE_RT_SLOT6,
                                                        1);
/////

    wchar_t buffer9[255];
    swprintf_s(buffer9, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_AUTO_BERSERKER_POTION"));
    m_custom_label_tooltip7 ->SetText(buffer9);
    ResetPosition();
    SetAutoABS = false;
    SetAutoINC = false;
    SetAutoABSbubble= false;
    SetAutoINCbubble= false;
    SetAutoRessurect= false;
    SetAutoBerserkerPotion=false;
    m_btn6->ShowGWnd(false);
    m_btn5->ShowGWnd(false);
    this->ShowGWnd(false);
    return true;

}



void CIFSTExtraFeature::OnUpdate() {

/*    if (*(DWORD**)0x0110F80C)
    {

        if (!strcmp(g_CurrentIfUnderCursor->GetRuntimeClass()->m_lpszClassName, "CIFSlotWithHelp")) {
            CIFSlotWithHelp* CurSlot = (CIFSlotWithHelp*)g_CurrentIfUnderCursor;

            short ALTState = GetKeyState(VK_MENU);
            short MouseState = GetKeyState(VK_LBUTTON);
            if (CurSlot && (ALTState == -127 || ALTState == -128) && (MouseState == -127 || MouseState == -128)) {

            CSOItem *myitem11 = CurSlot->ItemInfo;
            int GetParentWindow = CurSlot->GetParentWindowId();
                if (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 3768 && GetParentWindow == 70) {
                    m_dame_abs_slot = CurSlot->GetSlotInInventory();

                    m_slot1->ItemInfo = g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(m_dame_abs_slot);
                    m_slot1->FUN_006871d0(m_slot1->ItemInfo);
                }
                if (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 3767 && GetParentWindow == 70) {
                    m_dame_inc_slot = CurSlot->GetSlotInInventory();

                    m_slot2->ItemInfo = g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(m_dame_inc_slot);
                    m_slot2->FUN_006871d0(m_slot2->ItemInfo);
                }
                if ((CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24394 && GetParentWindow == 70)
                   || (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24390 && GetParentWindow == 70)
                   || (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24386 && GetParentWindow == 70)
                   || (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24402 && GetParentWindow == 70)) ///abs item
                {
                    m_dame_absorbbubble_slot = CurSlot->GetSlotInInventory();

                    m_slot3->ItemInfo = g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(m_dame_absorbbubble_slot);
                    m_slot3->FUN_006871d0(m_slot3->ItemInfo);
                }
                if ((CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24393 && GetParentWindow == 70)
                    || (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24389 && GetParentWindow == 70)
                    || (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24385 && GetParentWindow == 70)
                    || (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24401 && GetParentWindow == 70)) ///inc item
                {
                    m_dame_Increasebubble_slot = CurSlot->GetSlotInInventory();

                    m_slot4->ItemInfo = g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(m_dame_Increasebubble_slot);
                    m_slot4->FUN_006871d0(m_slot4->ItemInfo);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7777 && this)
            {
                if (m_slot1->ItemInfo && m_slot1->ItemInfo != NULL) {

                    Showbuble(m_slot1->ItemInfo,m_slot1);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7778 && this)
            {
                if (m_slot2->ItemInfo && m_slot2->ItemInfo != NULL ) {

                    Showbuble(m_slot2->ItemInfo,m_slot2);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7779 && this)
            {
                if (m_slot3->ItemInfo && m_slot3->ItemInfo != NULL) {

                    Showbuble(m_slot3->ItemInfo,m_slot3);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7780 && this)
            {
                if (m_slot4->ItemInfo && m_slot4->ItemInfo != NULL) {

                    Showbuble(m_slot4->ItemInfo,m_slot4);
                }
            }
        }
    }*/

}
bool CIFSTExtraFeature::Func_28(int a1, int a2, int a3) {
    CIFSlotWithHelp *pDraggedSlot = (CIFSlotWithHelp *) a1;

    CSOItem *pDraagedSlotItem = g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(
            pDraggedSlot->GetSlotInInventory());
    if (pDraagedSlotItem)
    {

        if (pDraagedSlotItem->GetObjectData()->ObjID == 3768  && g_CurrentIfUnderCursor->UniqueID()==7777 ) {
            g_pCGInterface->GetExtraFeatureGUI()-> m_dame_abs_slot = pDraggedSlot->GetSlotInInventory();
            g_pCGInterface->GetExtraFeatureGUI()->m_slot1->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetExtraFeatureGUI()->m_slot1->FUN_006871d0(pDraggedSlot->ItemInfo);
        }
        if (pDraagedSlotItem->GetObjectData()->ObjID == 3767  && g_CurrentIfUnderCursor->UniqueID()==7778) {
            g_pCGInterface->GetExtraFeatureGUI()->m_dame_inc_slot = pDraggedSlot->GetSlotInInventory();
            g_pCGInterface->GetExtraFeatureGUI()-> m_slot2->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetExtraFeatureGUI()-> m_slot2->FUN_006871d0(pDraggedSlot->ItemInfo);
        }
        if ((pDraagedSlotItem->GetObjectData()->ObjID == 24394 && g_CurrentIfUnderCursor->UniqueID()==7779)
            || (pDraagedSlotItem->GetObjectData()->ObjID == 24390 && g_CurrentIfUnderCursor->UniqueID()==7779)
            || (pDraagedSlotItem->GetObjectData()->ObjID == 24386 && g_CurrentIfUnderCursor->UniqueID()==7779)
            || (pDraagedSlotItem->GetObjectData()->ObjID == 24402 && g_CurrentIfUnderCursor->UniqueID()==7779)) ///abs item
        {
            g_pCGInterface->GetExtraFeatureGUI()->m_dame_absorbbubble_slot = pDraggedSlot->GetSlotInInventory();
            g_pCGInterface->GetExtraFeatureGUI()->m_slot3->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetExtraFeatureGUI()->m_slot3->FUN_006871d0(pDraggedSlot->ItemInfo);
        }
        if ((pDraagedSlotItem->GetObjectData()->ObjID == 24393 && g_CurrentIfUnderCursor->UniqueID()==7780)
            || (pDraagedSlotItem->GetObjectData()->ObjID == 24389 && g_CurrentIfUnderCursor->UniqueID()==7780)
            || (pDraagedSlotItem->GetObjectData()->ObjID == 24385 && g_CurrentIfUnderCursor->UniqueID()==7780)
            || (pDraagedSlotItem->GetObjectData()->ObjID == 24401 && g_CurrentIfUnderCursor->UniqueID()==7780)) ///inc item
        {
            g_pCGInterface->GetExtraFeatureGUI()->m_dame_Increasebubble_slot = pDraggedSlot->GetSlotInInventory();
            g_pCGInterface->GetExtraFeatureGUI()->m_slot4->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetExtraFeatureGUI()->m_slot4->FUN_006871d0(pDraggedSlot->ItemInfo);
        }
        if ((pDraagedSlotItem->GetObjectData()->TID == 14061 || pDraagedSlotItem->GetObjectData()->TID == 14060)  && g_CurrentIfUnderCursor->UniqueID()==7880 ) {
            g_pCGInterface->GetExtraFeatureGUI()-> m_ressurect_slot = pDraggedSlot->GetSlotInInventory();
            g_pCGInterface->GetExtraFeatureGUI()->m_slot5->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetExtraFeatureGUI()->m_slot5->FUN_006871d0(pDraggedSlot->ItemInfo);
        }
        if (pDraagedSlotItem->GetObjectData()->TID == 16620  && g_CurrentIfUnderCursor->UniqueID()==7881 ) {
            g_pCGInterface->GetExtraFeatureGUI()-> m_berserker_potion_slot = pDraggedSlot->GetSlotInInventory();
            g_pCGInterface->GetExtraFeatureGUI()->m_slot6->ItemInfo = pDraggedSlot->ItemInfo;
            g_pCGInterface->GetExtraFeatureGUI()->m_slot6->FUN_006871d0(pDraggedSlot->ItemInfo);
        }
    }

    return true;
}
int CIFSTExtraFeature::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();

    return 0;
}
int CIFSTExtraFeature::OnMouseLeftUp(int a1, int x, int y)
{


    return 0;
}

void CIFSTExtraFeature::On_BtnClickSetAutoUpSkill()
{

    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!AUTOUPSKILL");
    buf << std::n_string("!AUTOUPSKILL");
    SendMsg(buf);
}
void CIFSTExtraFeature::On_BtnClickSetAutoABS() {
    std::n_wstring input_text = m_btn1->GetNText();
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));

    if (wcscmp(input_text.c_str(), message) == 0)
    {
        if(m_slot1->ItemInfo==NULL)
        {
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_RQ"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 255, 0, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);
        }
        else
        {

            if(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(m_dame_abs_slot)->m_quantity==1)
            {
                wchar_t message[1000];
                swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIPX"));
                CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
                int color = D3DCOLOR_ARGB(255, 255, 0, 0);
                systemmessage->WriteMessage(0xFF, color, message, 0, 1);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot1->FUN_006871d0(0);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot1->TB_Func_13("", 1, 1);
                return;
            }

            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP8"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 0, 255, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);

            BYTE Slot = m_dame_abs_slot+0xD;
            CMsgStreamBuffer buf(0x704C);
            buf << (byte)Slot;
            buf << (UINT16)0x0EED ;
            SendMsg(buf);
            m_btn1->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP11"));
            g_pCGInterface->GetExtraFeatureGUI()->SetAutoABS = true;
           // CIFflorian0Guide::CIFSTEffectGUI->SetABSTime(1805);
        }
    }
    else
    {
        g_pCGInterface->GetExtraFeatureGUI()->m_slot1->FUN_006871d0(0);
        g_pCGInterface->GetExtraFeatureGUI()->m_slot1->TB_Func_13("", 1, 1);
        m_btn1->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
        g_pCGInterface->GetExtraFeatureGUI()->SetAutoABS = false;
    }
}
void CIFSTExtraFeature::On_BtnClickSetAutoINC() {
    std::n_wstring input_text = m_btn2->GetNText();
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12")); // dang tat

    if (wcscmp(input_text.c_str(), message) == 0)
    {
        if(m_slot2->ItemInfo==NULL)
        {
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_RQ"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 255, 0, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);

        }
        else
        {
            if(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(m_dame_inc_slot)->m_quantity==1)
            {
                wchar_t message[1000];
                swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIPX"));
                CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
                int color = D3DCOLOR_ARGB(255, 255, 0, 0);
                systemmessage->WriteMessage(0xFF, color, message, 0, 1);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot2->FUN_006871d0(0);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot2->TB_Func_13("", 1, 1);
                return;
            }
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP7"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 0, 255, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);

            BYTE Slot = m_dame_inc_slot+0xD;
            CMsgStreamBuffer buf(0x704C);
            buf << (byte)Slot;
            buf << (UINT16)0x0EED ;
            SendMsg(buf);

            g_pCGInterface->GetExtraFeatureGUI()->SetAutoINC = true;
            m_btn2->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP11"));

            //CIFflorian0Guide::CIFSTEffectGUI->SetINCTime(1805);
        }
    }
    else
    {
        g_pCGInterface->GetExtraFeatureGUI()->m_slot2->FUN_006871d0(0);
        g_pCGInterface->GetExtraFeatureGUI()->m_slot2->TB_Func_13("", 1, 1);
        m_btn2->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
        g_pCGInterface->GetExtraFeatureGUI()->SetAutoINC = false;
    }

}
void CIFSTExtraFeature::On_BtnClickSetAutoDamageabsorbbubble() {
    std::n_wstring input_text = m_btn3->GetNText();
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12")); // dang tat

    if (wcscmp(input_text.c_str(), message) == 0)
    {
        if(m_slot3->ItemInfo==NULL)
        {
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_RQ"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 255, 0, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);

        }
        else
        {

            if(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(m_dame_absorbbubble_slot)->m_quantity==1)
            {
                wchar_t message[1000];
                swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIPX"));
                CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
                int color = D3DCOLOR_ARGB(255, 255, 0, 0);
                systemmessage->WriteMessage(0xFF, color, message, 0, 1);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot3->FUN_006871d0(0);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot3->TB_Func_13("", 1, 1);
                return;
            }
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP9"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 0, 255, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);


            BYTE Slot = m_dame_absorbbubble_slot+0xD;
            CMsgStreamBuffer buf(0x704C);
            buf << (byte)Slot;
            buf << (UINT16)0x0EED ;
            SendMsg(buf);
            g_pCGInterface->GetExtraFeatureGUI()->SetAutoABSbubble = true;
            m_btn3->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP11"));
           // CIFflorian0Guide::CIFSTEffectGUI->SetABSBUBBLETime(1805);
        }
    }
    else
    {
        g_pCGInterface->GetExtraFeatureGUI()->m_slot3->FUN_006871d0(0);
        g_pCGInterface->GetExtraFeatureGUI()->m_slot3->TB_Func_13("", 1, 1);
        m_btn3->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
        g_pCGInterface->GetExtraFeatureGUI()->SetAutoABSbubble = false;
    }

}
void CIFSTExtraFeature::On_BtnClickSetAutoDamageIncreasebubble() {
    std::n_wstring input_text = m_btn4->GetNText();
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12")); // dang tat

    if (wcscmp(input_text.c_str(), message) == 0)
    {
        if(m_slot4->ItemInfo==NULL)
        {
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_RQ"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 255, 0, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);

        }
        else
        {

            if(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(m_dame_Increasebubble_slot)->m_quantity==1)
            {
                wchar_t message[1000];
                swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIPX"));
                CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
                int color = D3DCOLOR_ARGB(255, 255, 0, 0);
                systemmessage->WriteMessage(0xFF, color, message, 0, 1);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot4->FUN_006871d0(0);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot4->TB_Func_13("", 1, 1);
                return;
            }
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP10"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 0, 255, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);

            BYTE Slot = m_dame_Increasebubble_slot+0xD;
            CMsgStreamBuffer buf(0x704C);
            buf << (byte)Slot;
            buf << (UINT16)0x0EED ;
            SendMsg(buf);
            g_pCGInterface->GetExtraFeatureGUI()->SetAutoINCbubble = true;
            m_btn4->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP11"));
            //CIFflorian0Guide::CIFSTEffectGUI->SetINCBUBBLETime(1805);
        }
    }
    else
    {
        g_pCGInterface->GetExtraFeatureGUI()->m_slot4->FUN_006871d0(0);
        g_pCGInterface->GetExtraFeatureGUI()->m_slot4->TB_Func_13("", 1, 1);
        m_btn4->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
        g_pCGInterface->GetExtraFeatureGUI()->SetAutoINCbubble = false;
    }

}
void CIFSTExtraFeature::On_BtnClickSetAutoBerserkerPotion() {
    std::n_wstring input_text = m_btn8->GetNText();
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12")); // dang tat

    if (wcscmp(input_text.c_str(), message) == 0)
    {
        if(m_slot6->ItemInfo==NULL)
        {
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_RQ"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 255, 0, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);

        }
        else
        {

            if(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(m_berserker_potion_slot)->m_quantity==1)
            {
                wchar_t message[1000];
                swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIPX"));
                CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
                int color = D3DCOLOR_ARGB(255, 255, 0, 0);
                systemmessage->WriteMessage(0xFF, color, message, 0, 1);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot6->FUN_006871d0(0);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot6->TB_Func_13("", 1, 1);
                return;
            }
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_AUTO_BERSERKER_POTION_ON"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 0, 255, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);

            g_pCGInterface->GetExtraFeatureGUI()->SetAutoBerserkerPotion = true;
            m_btn8->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP11"));
            //CIFflorian0Guide::CIFSTEffectGUI->SetINCBUBBLETime(1805);
        }
    }
    else
    {
        g_pCGInterface->GetExtraFeatureGUI()->m_slot6->FUN_006871d0(0);
        g_pCGInterface->GetExtraFeatureGUI()->m_slot6->TB_Func_13("", 1, 1);
        m_btn8->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
        g_pCGInterface->GetExtraFeatureGUI()->SetAutoBerserkerPotion = false;
    }

}
void CIFSTExtraFeature::On_BtnClickSetAutoRessurect() {
    std::n_wstring input_text = m_btn7->GetNText();
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12")); // dang tat

    if (wcscmp(input_text.c_str(), message) == 0)
    {
        if(m_slot5->ItemInfo==NULL)
        {
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_RQ"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 255, 0, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);

        }
        else
        {

            if(g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(m_ressurect_slot)->m_quantity==1)
            {
                wchar_t message[1000];
                swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIPX"));
                CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
                int color = D3DCOLOR_ARGB(255, 255, 0, 0);
                systemmessage->WriteMessage(0xFF, color, message, 0, 1);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot5->FUN_006871d0(0);
                g_pCGInterface->GetExtraFeatureGUI()->m_slot5->TB_Func_13("", 1, 1);
                return;
            }
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_AUTO_RESSURECT_ON"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 0, 255, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);

            g_pCGInterface->GetExtraFeatureGUI()->SetAutoRessurect = true;
            m_btn7->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP11"));
            //CIFflorian0Guide::CIFSTEffectGUI->SetINCBUBBLETime(1805);
        }
    }
    else
    {
        g_pCGInterface->GetExtraFeatureGUI()->m_slot5->FUN_006871d0(0);
        g_pCGInterface->GetExtraFeatureGUI()->m_slot5->TB_Func_13("", 1, 1);
        m_btn7->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
        g_pCGInterface->GetExtraFeatureGUI()->SetAutoRessurect = false;
    }

}
void CIFSTExtraFeature::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}

