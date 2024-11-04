//
// Created by Admin on 26/6/2021.
//

#include "IFSTConfirm.h"
#include "IFNormalTile.h"
#include "ICPlayer.h"
#include "Game.h"
#include "IFStretchWnd.h"
#include <ctime>

#define GDR_GRANTNAME_RT_LABEL 10
#define GDR_GRANTNAME_RT_BTN_APPLY 11
#define GDR_GRANTNAME_RT_BTN_CANCEL 17
#define GDR_GRANTNAME_RT_FRAME 12
#define GDR_GRANTNAME_RT_NORMALTILE 13
#define GDR_GRANTNAME_RT_EDIT 14
#define GDR_GRANTNAME_RT_TOOLTIP 16
#define GDR_GRANTNAME_RT_STRETCHWND 15
#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)
#define CLIENT_SCREEN_HEIGHT (*(int*)0x00ED7CBC)

GFX_IMPLEMENT_DYNCREATE(CIFSTConfirm, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTConfirm, CIFMainFrame)
                    ONG_COMMAND(GDR_GRANTNAME_RT_BTN_APPLY, &On_BtnClick)
                    ONG_COMMAND(GDR_GRANTNAME_RT_BTN_CANCEL, &On_BtnClickCancel)


GFX_END_MESSAGE_MAP()


CIFSTConfirm::CIFSTConfirm() :
        m_custom_label(NULL) {

}

bool CIFSTConfirm::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);

    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);
///////frame
    wnd_size sz = this->GetSize();
    RECT rect_frame = { 16,40,340,88 };

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame,
                                                  GDR_GRANTNAME_RT_FRAME,
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
                                                           GDR_GRANTNAME_RT_NORMALTILE,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);

/*    RECT rect_edit_interface = {79,65,162,20};
    CIFStretchWnd *edit_interface = (CIFStretchWnd *) CreateInstance(this,
                                                                     GFX_RUNTIME_CLASS(CIFStretchWnd),
                                                                     rect_edit_interface,
                                                                     GDR_GRANTNAME_RT_STRETCHWND,
                                                                     1);
    edit_interface->TB_Func_13("interface\\ifcommon\\com_blacksquare_", 1, 0);*/
////////// tooltip
    RECT rect_m_tooltip_lable = {rect_frame.left + 10,
                                 rect_frame.top + 20,
                                 rect_frame.right - 20,
                                 10};
    m_custom_label_tooltip = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                 GFX_RUNTIME_CLASS(CIFStatic),
                                                                 rect_m_tooltip_lable,
                                                                 GDR_GRANTNAME_RT_TOOLTIP,
                                                                 1);
    wchar_t buffer[255];
    swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_ST_GRANTNAME_TOOLTIP"));
    m_custom_label_tooltip ->SetText(buffer);
///////// button1
    RECT rect_button = {90,93,90,23};
    //RECT rect_button = {35, 70, 140, 30};
    CIFButton *btn = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button,
                                                         GDR_GRANTNAME_RT_BTN_APPLY,
                                                         1);

    btn->SetText(TSM_GETTEXTPTR("UIIT_ST_CONFIRM_APPLY"));
    btn->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

/////////
///////// button2
    RECT rect_button2 = {200,93,90,23};
    //RECT rect_button = {35, 70, 140, 30};
    CIFButton *btn2 = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button2,
                                                          GDR_GRANTNAME_RT_BTN_CANCEL,
                                                         1);

    btn2->SetText(TSM_GETTEXTPTR("UIIT_ST_CONFIRM_CANCEL"));
    btn2->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

/////////
    this->ShowGWnd(false);
    return true;
}


int CIFSTConfirm::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
void CIFSTConfirm::OnUpdate() {
    time_t rawtime;
    struct tm *timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);

}
void CIFSTConfirm::On_BtnClick() {
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!MUALUOT");
    buf << std::n_string("!MUALUOT");
    SendMsg(buf);
    this->OnCloseWnd();
}
void CIFSTConfirm::On_BtnClickCancel() {

    this->OnCloseWnd();
}
void CIFSTConfirm::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}