//
// Created by Admin on 26/6/2021.
//

#include "IFSTStreamSetting.h"
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
#include "hook.h"
#include "GlobalDataManager.h"

#define GDR_STREAMSETTING_RT_LABEL 10
#define GDR_STREAMSETTING_RT_BTN_HIGH 11
#define GDR_STREAMSETTING_RT_FRAME 12
#define GDR_STREAMSETTING_RT_NORMALTILE 13
#define GDR_STREAMSETTING_RT_TOOLTIP 16
#define GDR_STREAMSETTING_RT_BTN_NORMAL 17
#define GDR_STREAMSETTING_RT_BTN_BEST 18
#define GDR_STREAMSETTING_RT_BTN_ZOOM_ON 19
#define GDR_STREAMSETTING_RT_BTN_ZOOM_OFF 20
#define GDR_STREAMSETTING_RT_BTN_FREEZE_ON 21
#define GDR_STREAMSETTING_RT_BTN_FREEZE_OFF 22
#define GDR_STREAMSETTING_RT_BTN_HIDEWND 26
#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)
#define CLIENT_SCREEN_HEIGHT (*(int*)0x00ED7CBC)

GFX_IMPLEMENT_DYNCREATE(CIFSTStreamSetting, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTStreamSetting, CIFMainFrame)
                    ONG_COMMAND(GDR_STREAMSETTING_RT_BTN_HIGH, &On_BtnClickHigh)
                    ONG_COMMAND(GDR_STREAMSETTING_RT_BTN_NORMAL, &On_BtnClickNorMal)
                    ONG_COMMAND(GDR_STREAMSETTING_RT_BTN_BEST, &On_BtnClickBest)
                    ONG_COMMAND(GDR_STREAMSETTING_RT_BTN_ZOOM_ON, &On_BtnClickZoomOn)
                    ONG_COMMAND(GDR_STREAMSETTING_RT_BTN_ZOOM_OFF, &On_BtnClickZoomOFF)
                    ONG_COMMAND(GDR_STREAMSETTING_RT_BTN_FREEZE_ON, &On_BtnClickFreezeOn)
                    ONG_COMMAND(GDR_STREAMSETTING_RT_BTN_FREEZE_OFF, &On_BtnClickFreezeOFF)
                    ONG_COMMAND(GDR_STREAMSETTING_RT_BTN_HIDEWND, &On_BtnClickShowWND)
GFX_END_MESSAGE_MAP()


CIFSTStreamSetting::CIFSTStreamSetting() :
        m_custom_label(NULL) {

}
bool CIFSTStreamSetting::m_fps_show_checked() const {
    return m_fps_show->GetCheckedState_MAYBE();
}
bool CIFSTStreamSetting::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);
    RECT rect_m_tile = {120, 9, 100, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_TITLE"));
    m_tile->BringToFront();


    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);
///////frame
    wnd_size sz = this->GetSize();

    RECT rect_frame = { 14,40 ,sz.width - 26, sz.height - 50 };

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame,
                                                  GDR_STREAMSETTING_RT_FRAME,
                                                  1);
    frame->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 0);

    RECT rect_background = {rect_frame.left + 10,
                            rect_frame.top + 10,
                            rect_frame.right - 20,
                            rect_frame.bottom - 20};

    CIFNormalTile *tile = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background,
                                                           GDR_STREAMSETTING_RT_NORMALTILE,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);

////////// tooltip
    RECT rect_m_tooltip_lable = {rect_frame.left + 10,
                                 rect_frame.top + 10,
                                 rect_frame.right - 20,
                                 10};
    m_custom_label_tooltip = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                 GFX_RUNTIME_CLASS(CIFStatic),
                                                                 rect_m_tooltip_lable,
                                                                 GDR_STREAMSETTING_RT_TOOLTIP,
                                                                 1);
    wchar_t buffer[255];
    swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_ST_STREAMSETTING_TOOLTIP"));
    m_custom_label_tooltip ->SetText(buffer);
///////// button
    RECT rect_button = {135,93,90,23};
    CIFButton *btn = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button,
                                                         GDR_STREAMSETTING_RT_BTN_HIGH,
                                                         1);

    btn->SetText(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_HIGH"));
    btn->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button2 = {30,93,90,23};
    CIFButton *btn2= (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button2,
                                                         GDR_STREAMSETTING_RT_BTN_NORMAL,
                                                         1);

    btn2->SetText(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_NORMAL"));
    btn2->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button3 = {240,93,90,23};
    CIFButton *btn3= (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button3,
                                                         GDR_STREAMSETTING_RT_BTN_BEST,
                                                         1);

    btn3->SetText(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_BEST"));
    btn3->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button4 = {50,200,110,23};
    CIFButton *btn4= (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button4,
                                                         GDR_STREAMSETTING_RT_BTN_ZOOM_ON,
                                                         1);

    btn4->SetText(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_INFINITY_ZOOM"));
    btn4->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button5 = {50,233,110,23};
    CIFButton *btn5= (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button5,
                                                         GDR_STREAMSETTING_RT_BTN_ZOOM_OFF,
                                                         1);

    btn5->SetText(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_NORMAL_ZOOM"));
    btn5->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button6 = {200,200,110,23};
    CIFButton *btn6 = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button6,
                                                         GDR_STREAMSETTING_RT_BTN_FREEZE_ON,
                                                         1);

    btn6->SetText(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_UNLOCK_FREEZE"));
    btn6->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button7 = {200,233,110,23};
    CIFButton *btn7 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button7,
                                                          GDR_STREAMSETTING_RT_BTN_FREEZE_OFF,
                                                          1);

    btn7->SetText(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_LOCK_FREEZE"));
    btn7->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT rect_button8 = {200,167,110,23};
    CIFButton *btn8 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button8,
                                                          GDR_STREAMSETTING_RT_BTN_HIDEWND,
                                                          1);

    btn8->SetText(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_HIDE_WND"));
    btn8->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);


    RECT rect_m_fps_show = {60, 170, 17, 17};

    m_fps_show = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), rect_m_fps_show, 23, 0);
    m_fps_show->ShowGWnd(true);
    m_fps_show->BringToFront();
    m_fps_show->FUN_00656d50(0);

    RECT rect_m_tile_m_fps_show = {rect_m_fps_show.left + 30, rect_m_fps_show.top + 2, 50, 13};
    CIFStatic * m_tile_m_fps_show = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile_m_fps_show,24,1);
    m_tile_m_fps_show->SetText(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_SHOW_FPS"));
    RECT rect_m_tile1 = {97, 62, 150, 13};
    CIFStatic * m_tile1 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile1,112,1);
    m_tile1->SetText(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_TOOLTIP"));

    RECT rect_m_tile2 = {97, 132, 150, 13};
    CIFStatic * m_tile2 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile2,113,1);
    m_tile2->SetText(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_TOOLTIP1"));

/////////
    this->ShowGWnd(false);
    return true;
}



void CIFSTStreamSetting::OnUpdate() {
    time_t rawtime;
    struct tm *timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);
}
int CIFSTStreamSetting::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
void BackgroundLimit(int addr, float value)
{
    DWORD dwProtect;

    if (!VirtualProtect((LPVOID)addr, sizeof(float), PAGE_EXECUTE_READWRITE, &dwProtect)) {
        perror("Failed to unprotect memory\n");
        return;
    }

    *((float*)addr) = value;

    DWORD otherProtect;
    if (!VirtualProtect((LPVOID)addr, sizeof(float), dwProtect, &otherProtect)) {
        perror("Failed to restore protection on memory");
    }
}
void ZoomHackOFF()
{
    g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0077B4F6), 2);
    *(BYTE*)(0x0077B4F6) = 0x7a;
    *(BYTE*)(0x0077B4F6 + 1) = 0x08;
    g_MemoryHelper->ReProtect();
}

void ZoomHackON()
{
    g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0077B4F6), 2);
    *(BYTE*)(0x0077B4F6) = 0xEB;
    *(BYTE*)(0x0077B4F6 + 1) = 0x08;
    g_MemoryHelper->ReProtect();
}
void FreezeOFF()
{
    g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x00ba6fc8), 10);
    *(BYTE*)(0x00BA6FC8) = 0xc7;
    *(BYTE*)(0x00BA6FC8 + 1) = 0x05;
    *(BYTE*)(0x00BA6FC8 + 2) = 0xb4;
    *(BYTE*)(0x00BA6FC8 + 3) = 0x7c;
    *(BYTE*)(0x00BA6FC8 + 4) = 0xed;
    *(BYTE*)(0x00BA6FC8 + 5) = 0x00;
    *(BYTE*)(0x00BA6FC8 + 6) = 0x00;
    *(BYTE*)(0x00BA6FC8 + 7) = 0x00;
    *(BYTE*)(0x00BA6FC8 + 8) = 0x00;
    *(BYTE*)(0x00BA6FC8 + 9) = 0x00;
    g_MemoryHelper->ReProtect();
}
void FreezeON()
{

    g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x00ba6fc8), 10);
    RenderNop((void*)0x00BA6FC8, 10);
    g_MemoryHelper->ReProtect();
}
void CIFSTStreamSetting::On_BtnClickHigh() {

    BackgroundLimit(0x00de34c0, 5000);
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_STREAM_SETTING_TOOLTIP2"));
    g_pCGInterface->ShowMessage_Warning(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_TOOLTIP3"));
    g_pCGInterface->ShowMessage_Notice(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_TOOLTIP4"));

    CIFSystemMessage* systemmessage = reinterpret_cast<CIFSystemMessage*>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 255, 255, 255);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);

}
void CIFSTStreamSetting::On_BtnClickNorMal() {
    BackgroundLimit(0x00de34c0, 2500);
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_STREAM_SETTING_TOOLTIP2"));
    g_pCGInterface->ShowMessage_Warning(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_TOOLTIP3"));
    g_pCGInterface->ShowMessage_Notice(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_TOOLTIP4"));

    CIFSystemMessage* systemmessage = reinterpret_cast<CIFSystemMessage*>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 255, 255, 255);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);
}
void CIFSTStreamSetting::On_BtnClickBest() {
    BackgroundLimit(0x00de34c0, 10000);
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_STREAM_SETTING_TOOLTIP2"));
    g_pCGInterface->ShowMessage_Warning(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_TOOLTIP3"));
    g_pCGInterface->ShowMessage_Notice(TSM_GETTEXTPTR("UIIT_STREAM_SETTING_TOOLTIP4"));

    CIFSystemMessage* systemmessage = reinterpret_cast<CIFSystemMessage*>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 255, 255, 255);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);
}
void CIFSTStreamSetting::On_BtnClickZoomOn() {
    ZoomHackON();
    wchar_t message[] = L"Note: Zoom Hack -> ON";
    CIFSystemMessage* systemmessage = reinterpret_cast<CIFSystemMessage*>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 255, 255, 255);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);
}
void CIFSTStreamSetting::On_BtnClickZoomOFF() {
    ZoomHackOFF();
    wchar_t message[] = L"Note: Zoom Hack -> OFF";
    CIFSystemMessage* systemmessage = reinterpret_cast<CIFSystemMessage*>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 255, 255, 255);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);
}
void CIFSTStreamSetting::On_BtnClickFreezeOn() {
    FreezeON();
    wchar_t message[] = L"Note: Freeze Hack -> ON";
    CIFSystemMessage* systemmessage = reinterpret_cast<CIFSystemMessage*>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 255, 255, 255);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);
}
void CIFSTStreamSetting::On_BtnClickFreezeOFF() {
    FreezeOFF();
    wchar_t message[] = L"Note: Freeze Hack -> OFF";
    CIFSystemMessage* systemmessage = reinterpret_cast<CIFSystemMessage*>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 255, 255, 255);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);
}
void CIFSTStreamSetting::On_BtnClickShowWND() {
    ShowWindow(Rebot::GameHWND, SW_MINIMIZE);
}
void CIFSTStreamSetting::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}