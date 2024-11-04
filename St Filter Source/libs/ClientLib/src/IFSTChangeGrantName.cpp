//
// Created by Admin on 26/6/2021.
//

#include "IFSTChangeGrantName.h"
#include "IFNormalTile.h"
#include "ICPlayer.h"
#include "Game.h"
#include "IFStretchWnd.h"
#include <ctime>
#include "BSLib/BSLib.h"
#include "CPSMission.h"
#include "GInterface.h"
#include <BSLib\multiBYTE.h>
#include <imgui/imgui.h>

#define GDR_GRANTNAME_RT_LABEL 10
#define GDR_GRANTNAME_RT_BTN_APPLY 11
#define GDR_GRANTNAME_RT_FRAME 12
#define GDR_GRANTNAME_RT_NORMALTILE 13
#define GDR_GRANTNAME_RT_EDIT 14
#define GDR_GRANTNAME_RT_TOOLTIP 16
#define GDR_GRANTNAME_RT_STRETCHWND 15
#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)
#define CLIENT_SCREEN_HEIGHT (*(int*)0x00ED7CBC)

GFX_IMPLEMENT_DYNCREATE(CIFSTChangeGrantName, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTChangeGrantName, CIFMainFrame)
                    ONG_COMMAND(GDR_GRANTNAME_RT_BTN_APPLY, &On_BtnClick)


GFX_END_MESSAGE_MAP()


CIFSTChangeGrantName::CIFSTChangeGrantName() :
        m_custom_label(NULL) {

}

bool CIFSTChangeGrantName::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);
    RECT rect_m_tile = {113, 9, 100, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIT_ST_GRANTNAME"));

    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);
///////frame
    wnd_size sz = this->GetSize();
    RECT rect_frame = { 16,40,290,83 };

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
///////// m_edit
    RECT rect_m_edit = {92,68,144,20};
    m_edit = (CIFEdit *) (CIFEdit *) CreateInstance(this,
                                                      GFX_RUNTIME_CLASS(CIFEdit),
                                                      rect_m_edit,
                                                    GDR_GRANTNAME_RT_EDIT,
                                                      1);
    m_edit->BringToFront();
    m_edit->TB_Func_5(1);
    m_edit->SetFocus_MAYBE();
    RECT rect_m_edit_frame =  {rect_m_edit.left -2,
                               rect_m_edit.top -2,
                               rect_m_edit.right +4,
                               rect_m_edit.bottom +4};
    CIFFrame *frame_m_edit = (CIFFrame *) CreateInstance(this,
                                                            GFX_RUNTIME_CLASS(CIFFrame),
                                                         rect_m_edit_frame,
                                                            GDR_GRANTNAME_RT_FRAME,
                                                            1);
    frame_m_edit->TB_Func_13("interface\\frame\\ub_pet_wnd_", 1, 0);

    RECT rect_background_m_edit = {rect_m_edit_frame.left + 2,
                                   rect_m_edit_frame.top + 2,
                                   rect_m_edit_frame.right - 4,
                                   rect_m_edit_frame.bottom - 4};

    CIFNormalTile *tile_m_edit = (CIFNormalTile *) CreateInstance(this,
                                                                     GFX_RUNTIME_CLASS(CIFNormalTile),
                                                                     rect_background_m_edit,
                                                                     GDR_GRANTNAME_RT_NORMALTILE,
                                                                     1);
    tile_m_edit->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_d.ddj", 1, 0);


/*    RECT rect_edit_interface = {79,65,162,20};
    CIFStretchWnd *edit_interface = (CIFStretchWnd *) CreateInstance(this,
                                                                     GFX_RUNTIME_CLASS(CIFStretchWnd),
                                                                     rect_edit_interface,
                                                                     GDR_GRANTNAME_RT_STRETCHWND,
                                                                     1);
    edit_interface->TB_Func_13("interface\\ifcommon\\com_blacksquare_", 1, 0);*/
////////// tooltip
    RECT rect_m_tooltip_lable = {rect_frame.left + 10,
                                 rect_frame.top + 10,
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
///////// button
    RECT rect_button = {120,93,90,23};
    //RECT rect_button = {35, 70, 140, 30};
    CIFButton *btn = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button,
                                                         GDR_GRANTNAME_RT_BTN_APPLY,
                                                         1);

    btn->SetText(L"Change");
    btn->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

/////////
    m_edit ->SetMaxStringInput(12);
    this->ShowGWnd(false);
    return true;
}



void CIFSTChangeGrantName::OnUpdate() {
    time_t rawtime;
    struct tm *timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);
}
int CIFSTChangeGrantName::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
void CIFSTChangeGrantName::On_BtnClick() {
    if (g_pCICPlayer->GetGuildName().empty() || m_edit->GetNText().length() > 12)
    {
        g_pCGInterface->ShowBlueNotify(L"Grant name must be 12 Letters as max");
        return;
    }

    if (m_edit->GetNText().empty())
    {
        g_pCGInterface->ShowBlueNotify(L"Set a grant name first");
        return;
    }
    if (CGame::GetBadwordFilter()->sub_8C4020(m_edit->GetCurrentText())) {
        g_pCGInterface->WriteSystemMessage(SYSLOG_NONE, TSM_GETTEXTPTR("UIIT_MSG_WHOLECHATERR_NOTINUSEMSG"));
        m_edit->SetText(L"");
        return;
    }
   CMsgStreamBuffer buf(0x1318);
    buf << std::n_string(TO_NSTRING(this->m_edit->GetNText()));
    buf << std::n_string("!DOIBIETHIEU");
    SendMsg(buf);
}
void CIFSTChangeGrantName::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 2);
}