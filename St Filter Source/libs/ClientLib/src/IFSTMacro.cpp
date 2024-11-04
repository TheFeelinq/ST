
#include "IFSTMacro.h"

#include "IFNormalTile.h"
#include "ICPlayer.h"
#include "Game.h"
#include "IFStretchWnd.h"
#include "IFflorian0Guide.h"
#include "Rebot.h"
#include <ctime>
#include <BSLib\multibyte.h>

#define GDR_MACRO_RT_LABEL 10
#define GDR_MACRO_RT_BTN_HUNTING 11
#define GDR_MACRO_RT_FRAME 12
#define GDR_MACRO_RT_NORMALTILE 13
#define GDR_MACRO_RT_EDIT 14
#define GDR_MACRO_RT_TOOLTIP 16
#define GDR_MACRO_RT_BTN_ITEM 17
#define GDR_MACRO_RT_BTN_POTION 18
#define GDR_MACRO_RT_BTN_SKILL 19
#define GDR_MACRO_RT_BTN_HUNTING_ICON 20
#define GDR_MACRO_RT_BTN_POTION_ICON 21
#define GDR_MACRO_RT_BTN_PET_POTION 22
#define GDR_MACRO_RT_BTN_PET_POTION_ICON 23

#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)
#define CLIENT_SCREEN_HEIGHT (*(int*)0x00ED7CBC)

GFX_IMPLEMENT_DYNCREATE(CIFSTMacro, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTMacro, CIFMainFrame)
                    ONG_COMMAND(GDR_MACRO_RT_BTN_HUNTING, &On_BtnClick_Autohunt_opt)
                    ONG_COMMAND(GDR_MACRO_RT_BTN_HUNTING_ICON, &On_BtnClick_Autohunt)
                    ONG_COMMAND(GDR_MACRO_RT_BTN_POTION, &On_BtnClick_AutoPotion_opt)
                    ONG_COMMAND(GDR_MACRO_RT_BTN_POTION_ICON, &On_BtnClick_AutoPotion)
                    ONG_COMMAND(GDR_MACRO_RT_BTN_PET_POTION, &On_BtnClick_Pet_AutoPotion_opt)
                    ONG_COMMAND(GDR_MACRO_RT_BTN_PET_POTION_ICON, &On_BtnClick_Pet_AutoPotion)

GFX_END_MESSAGE_MAP()


CIFSTMacro::CIFSTMacro() :
        m_custom_label(NULL) {

}

bool CIFSTMacro::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);
    RECT rect_m_tile = {118, 9, 100, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_TOOLTIP"));

    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);
///////frame
    wnd_size sz = this->GetSize();
    RECT rect_frame = { 13,40,333,192 };

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame,
                                                  GDR_MACRO_RT_FRAME,
                                                  1);
    //frame->TB_Func_13("interface\\messagebox\\msgbox_window_", 1, 0);
    frame->TB_Func_13("interface\\frame\\frame_sub_", 1, 0);

    RECT rect_background = {rect_frame.left + 10,
                            rect_frame.top + 10,
                            rect_frame.right - 20,
                            rect_frame.bottom - 20};

    CIFNormalTile *tile = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background,
                                                           GDR_MACRO_RT_NORMALTILE,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_a.ddj", 1, 0);
////////// tooltip
    RECT rect_m_custom_bg = {rect_frame.left + 10,
                                 rect_frame.top + 10,
                                 rect_frame.right - 20,
                                 56};
    CIFStatic * m_custom_bg = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                 GFX_RUNTIME_CLASS(CIFStatic),
                                                                  rect_m_custom_bg,
                                                                 GDR_MACRO_RT_TOOLTIP,
                                                                 1);
    m_custom_bg->TB_Func_13("interface\\macro\\macro_box.ddj", 1, 1);

    RECT rect_m_custom_bg2 = {rect_frame.left + 10,
                             rect_frame.top + 10 + rect_m_custom_bg.bottom,
                             rect_frame.right - 20,
                             56};
    CIFStatic * m_custom_bg2 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFStatic),
                                                                   rect_m_custom_bg2,
                                                                  GDR_MACRO_RT_TOOLTIP,
                                                                  1);
    m_custom_bg2->TB_Func_13("interface\\macro\\macro_box.ddj", 1, 1);

    RECT rect_m_custom_bg3 = {rect_frame.left + 10,
                              rect_frame.top + 10 + rect_m_custom_bg.bottom + rect_m_custom_bg2.bottom,
                              rect_frame.right - 20,
                              56};
    CIFStatic * m_custom_bg3 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                   GFX_RUNTIME_CLASS(CIFStatic),
                                                                   rect_m_custom_bg3,
                                                                   GDR_MACRO_RT_TOOLTIP,
                                                                   1);
    m_custom_bg3->TB_Func_13("interface\\macro\\macro_box.ddj", 1, 1);

////////// CharName
    RECT rect_m_custom_label1 = {40,72,85,13};
    m_custom_label1 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFStatic),
                                                          rect_m_custom_label1,
                                                          GDR_MACRO_RT_TOOLTIP,
                                                          1);
    m_custom_label1 ->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_HUNT"));

    RECT rect_m_custom_label2 = {40,123,85,13};
    m_custom_label2 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFStatic),
                                                          rect_m_custom_label2,
                                                          GDR_MACRO_RT_TOOLTIP,
                                                          1);
    m_custom_label2 ->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_POTION"));

    RECT rect_m_custom_label3 = {40,174,85,13};
    m_custom_label3 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFStatic),
                                                          rect_m_custom_label3,
                                                          GDR_MACRO_RT_TOOLTIP,
                                                          1);
    m_custom_label3 ->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_PET_POTION"));

    ////////// gold

///////// button
    RECT rect_button_hunting = {230,66,90,23};
    //RECT rect_button = {35, 70, 140, 30};
    CIFButton *btn_hunting = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button_hunting,
                                                         GDR_MACRO_RT_BTN_HUNTING,
                                                         1);

    btn_hunting->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_TOOLTIP3"));
    btn_hunting->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button_potion = {230,120,90,23};
    CIFButton *btn_potion = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button_potion,
                                                         GDR_MACRO_RT_BTN_POTION,
                                                         1);

    btn_potion->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_TOOLTIP3"));
    btn_potion->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button_pet_potion = {230,174,90,23};
    CIFButton *btn_pet_potion = (CIFButton *) CGWnd::CreateInstance(this,
                                                                GFX_RUNTIME_CLASS(CIFButton),
                                                                rect_button_pet_potion,
                                                                GDR_MACRO_RT_BTN_PET_POTION,
                                                                1);

    btn_pet_potion->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_TOOLTIP3"));
    btn_pet_potion->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);
//////////
    RECT rect_m_rect_button_bg = {140,57,76,40};
    CIFStatic *m_btn_bg = (CIFStatic *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFStatic),
                                                          rect_m_rect_button_bg,
                                                          GDR_MACRO_RT_TOOLTIP,
                                                          1);
    m_btn_bg->TB_Func_13("interface\\macro\\macro_iconbg.ddj", 1, 1);

    RECT rect_button2 = {rect_m_rect_button_bg.left + 22,
                         rect_m_rect_button_bg.top + 4,
                                 32,
                                 32};
    btn2 = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button2,
                                                         GDR_MACRO_RT_BTN_HUNTING_ICON,
                                                         1);
    btn2->TB_Func_13("interface\\macro\\macro_icon_hunting_off.ddj", 1, 1);

    RECT rect_m_rect_button_bg2 = {140,111,76,40};
    CIFStatic *m_btn_bg2 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                              GFX_RUNTIME_CLASS(CIFStatic),
                                                              rect_m_rect_button_bg2,
                                                              GDR_MACRO_RT_TOOLTIP,
                                                              1);
    m_btn_bg2->TB_Func_13("interface\\macro\\macro_iconbg.ddj", 1, 1);

    RECT rect_button3 = {rect_m_rect_button_bg2.left + 22,
                         rect_m_rect_button_bg2.top + 4,
                         32,
                         32};
    btn3 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button3,
                                                          GDR_MACRO_RT_BTN_POTION_ICON,
                                                          1);
    btn3->TB_Func_13("interface\\macro\\macro_icon_potion_off.ddj", 1, 1);

    RECT rect_m_rect_button_bg3 = {140,165,76,40};
    CIFStatic *m_btn_bg3 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                               GFX_RUNTIME_CLASS(CIFStatic),
                                                               rect_m_rect_button_bg3,
                                                               GDR_MACRO_RT_TOOLTIP,
                                                               1);
    m_btn_bg3->TB_Func_13("interface\\macro\\macro_iconbg.ddj", 1, 1);

    RECT rect_button4 = {rect_m_rect_button_bg3.left + 22,
                         rect_m_rect_button_bg3.top + 4,
                         32,
                         32};
    btn4 = (CIFButton *) CGWnd::CreateInstance(this,
                                               GFX_RUNTIME_CLASS(CIFButton),
                                               rect_button4,
                                               GDR_MACRO_RT_BTN_PET_POTION_ICON,
                                               1);
    btn4->TB_Func_13("interface\\macro\\macro_icon_potion_off.ddj", 1, 1);

/*    RECT rect_m_custom_label22 = {15,123,313,21};
    CIFSliderCtrl * m_CIFSliderCtrl = (CIFSliderCtrl *) CGWnd::CreateInstance(this,
                                                                              GFX_RUNTIME_CLASS(CIFSliderCtrl),
                                                                              rect_m_custom_label22,
                                                                              2222,
                                                                              1);
    m_CIFSliderCtrl->TB_Func_13("interface\\option\\opt_volume2.ddj", 1, 1);
    m_CIFSliderCtrl->BringToFront();*/
/////////
    ResetPosition();
    this->ShowGWnd(false);
    status=false;
    return true;
}



void CIFSTMacro::OnUpdate() {
    time_t rawtime;
    struct tm *timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);

}
int CIFSTMacro::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
void CIFSTMacro::On_BtnClick_Autohunt() {

    SendMessageA(Rebot::GameHWND, WM_REBOTSTATUS, 1, 0);
  if(Rebot::RebotStart)
  {
      btn2->TB_Func_13("interface\\macro\\macro_icon_hunting_on.ddj", 1, 1);
      status = true;
  } else
  {
      btn2->TB_Func_13("interface\\macro\\macro_icon_hunting_off.ddj", 1, 1);
      status = false;
  }
}
void CIFSTMacro::On_BtnClick_Autohunt_opt() {
    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowGWnd(true);
    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ActivateTabPage(0);

}

void CIFSTMacro::On_BtnClick_AutoPotion() {

    if(!Rebot::Config.AutoPotion)
    {
        Rebot::Config.AutoPotion = true;
        btn3->TB_Func_13("interface\\macro\\macro_icon_potion_on.ddj", 1, 1);
    } else
    {
        Rebot::Config.AutoPotion = false;
        btn3->TB_Func_13("interface\\macro\\macro_icon_potion_off.ddj", 1, 1);
    }
}
void CIFSTMacro::On_BtnClick_Pet_AutoPotion() {

    if(!Rebot::Config.AutoPetPotion)
    {
        Rebot::Config.AutoPetPotion = true;
        btn4->TB_Func_13("interface\\macro\\macro_icon_potion_on.ddj", 1, 1);
    } else
    {
        Rebot::Config.AutoPetPotion = false;
        btn4->TB_Func_13("interface\\macro\\macro_icon_potion_off.ddj", 1, 1);
    }
}
void CIFSTMacro::On_BtnClick_AutoPotion_opt() {
    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowGWnd(true);
    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ActivateTabPage(1);
}
void CIFSTMacro::On_BtnClick_Pet_AutoPotion_opt() {
    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowGWnd(true);
    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ActivateTabPage(2);
}
void CIFSTMacro::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}