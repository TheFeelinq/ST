#include "IFSTDpsMetter.h"
#include "IFNormalTile.h"
#include <ctime>
#include "memhelp.h"
#include "Packet.h"

#define GDR_DPS_RT_LABEL 10
#define GDR_DPS_RT_MAIN_FRAME 20

#define GDR_DPS_PLAYERNAME_LABEL 21
#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)


GFX_IMPLEMENT_DYNCREATE(CIFSTDpsMetter, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTDpsMetter, CIFMainFrame)

GFX_END_MESSAGE_MAP()


CIFSTDpsMetter::CIFSTDpsMetter() :
        m_damage_lable(NULL) {

}

bool CIFSTDpsMetter::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);

    // Set own title

    TB_Func_13("interface\\frame\\event_sub_wnd_", 1, 0);

    RECT rect_background = {31,
                            48,
                            124,
                            115};

    CIFNormalTile *tile = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background,
                                                           GDR_DPS_RT_MAIN_FRAME,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_t.ddj", 1, 0);

    RECT rect_m_frame_lable = {30,8,123,15};
    m_frame_lable = (CIFStatic *) CGWnd::CreateInstance(this,
                                                             GFX_RUNTIME_CLASS(CIFStatic),
                                                        rect_m_frame_lable,
                                                             GDR_DPS_PLAYERNAME_LABEL,
                                                             1);
    RECT rect_m_playername_lable = {24,33,82,14};
    m_playername_lable = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                             rect_m_playername_lable,
                                                             GDR_DPS_PLAYERNAME_LABEL,
                                                         1);

    RECT rect_m_damage_lable = {129,33,49,14};
    m_damage_lable = (CIFStatic *) CGWnd::CreateInstance(this,
                                                             GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_m_damage_lable,
                                                             GDR_DPS_PLAYERNAME_LABEL,
                                                             1);
    RECT rect_m_damage_lable_slot1 = {132,51,44,14};
    m_damage_lable_slot1 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                               rect_m_damage_lable_slot1,
                                                         GDR_DPS_PLAYERNAME_LABEL,
                                                         1);
    RECT rect_m_damage_lable_slot2 = {132,66,44,14};
    m_damage_lable_slot2 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                               GFX_RUNTIME_CLASS(CIFStatic),
                                                               rect_m_damage_lable_slot2,
                                                               GDR_DPS_PLAYERNAME_LABEL,
                                                               1);
    RECT rect_m_damage_lable_slot3 = {132,81,44,14};
    m_damage_lable_slot3 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                               GFX_RUNTIME_CLASS(CIFStatic),
                                                               rect_m_damage_lable_slot3,
                                                               GDR_DPS_PLAYERNAME_LABEL,
                                                               1);
    RECT rect_m_damage_lable_slot4 = {132,96,44,14};
    m_damage_lable_slot4 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                               GFX_RUNTIME_CLASS(CIFStatic),
                                                               rect_m_damage_lable_slot4,
                                                               GDR_DPS_PLAYERNAME_LABEL,
                                                               1);
    RECT rect_m_damage_lable_slot5 = {132,111,44,14};
    m_damage_lable_slot5 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                               GFX_RUNTIME_CLASS(CIFStatic),
                                                               rect_m_damage_lable_slot5,
                                                               GDR_DPS_PLAYERNAME_LABEL,
                                                               1);
    RECT rect_m_damage_lable_slot6 = {132,126,44,14};
    m_damage_lable_slot6 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                               GFX_RUNTIME_CLASS(CIFStatic),
                                                               rect_m_damage_lable_slot6,
                                                               GDR_DPS_PLAYERNAME_LABEL,
                                                               1);
    RECT rect_m_damage_lable_slot7 = {132,141,44,14};
    m_damage_lable_slot7 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                               GFX_RUNTIME_CLASS(CIFStatic),
                                                               rect_m_damage_lable_slot7,
                                                               GDR_DPS_PLAYERNAME_LABEL,
                                                               1);
    RECT rect_m_damage_lable_slot8 = {132,156,44,14};
    m_damage_lable_slot8 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                               GFX_RUNTIME_CLASS(CIFStatic),
                                                               rect_m_damage_lable_slot8,
                                                               GDR_DPS_PLAYERNAME_LABEL,
                                                               1);

    //////////////
    RECT rect_m_playername_lable_slot1 = {26,51,110,14};
    m_playername_lable_slot1 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                               GFX_RUNTIME_CLASS(CIFStatic),
                                                                   rect_m_playername_lable_slot1,
                                                               GDR_DPS_PLAYERNAME_LABEL,
                                                               1);
    RECT rect_m_playername_lable_slot2 = {26,66,110,14};
    m_playername_lable_slot2 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                   GFX_RUNTIME_CLASS(CIFStatic),
                                                                   rect_m_playername_lable_slot2,
                                                                   GDR_DPS_PLAYERNAME_LABEL,
                                                                   1);
    RECT rect_m_playername_lable_slot3 = {26,81,110,14};
    m_playername_lable_slot3 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                   GFX_RUNTIME_CLASS(CIFStatic),
                                                                   rect_m_playername_lable_slot3,
                                                                   GDR_DPS_PLAYERNAME_LABEL,
                                                                   1);
    RECT rect_m_playername_lable_slot4 = {26,96,110,14};
    m_playername_lable_slot4 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                   GFX_RUNTIME_CLASS(CIFStatic),
                                                                   rect_m_playername_lable_slot4,
                                                                   GDR_DPS_PLAYERNAME_LABEL,
                                                                   1);
    RECT rect_m_playername_lable_slot5 = {26,111,110,14};
    m_playername_lable_slot5 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                   GFX_RUNTIME_CLASS(CIFStatic),
                                                                   rect_m_playername_lable_slot5,
                                                                   GDR_DPS_PLAYERNAME_LABEL,
                                                                   1);
    RECT rect_m_playername_lable_slot6 = {26,126,110,14};
    m_playername_lable_slot6 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                   GFX_RUNTIME_CLASS(CIFStatic),
                                                                   rect_m_playername_lable_slot6,
                                                                   GDR_DPS_PLAYERNAME_LABEL,
                                                                   1);
    RECT rect_m_playername_lable_slot7 = {26,141,110,14};
    m_playername_lable_slot7 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                   GFX_RUNTIME_CLASS(CIFStatic),
                                                                   rect_m_playername_lable_slot7,
                                                                   GDR_DPS_PLAYERNAME_LABEL,
                                                                   1);
    RECT rect_m_playername_lable_slot8 = {26,156,110,14};
    m_playername_lable_slot8 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                   GFX_RUNTIME_CLASS(CIFStatic),
                                                                   rect_m_playername_lable_slot8,
                                                                   GDR_DPS_PLAYERNAME_LABEL,
                                                                   1);
////////////////
    RECT rect_m_rank_lable_slot1 = {9,51,13,13};
    m_rank_lable_slot1 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                   GFX_RUNTIME_CLASS(CIFStatic),
                                                             rect_m_rank_lable_slot1,
                                                                   GDR_DPS_PLAYERNAME_LABEL,
                                                                   1);
    RECT rect_m_rank_lable_slot2 = {9,66,13,13};
    m_rank_lable_slot2 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                             GFX_RUNTIME_CLASS(CIFStatic),
                                                             rect_m_rank_lable_slot2,
                                                             GDR_DPS_PLAYERNAME_LABEL,
                                                             1);
    RECT rect_m_rank_lable_slot3 = {9,81,13,13};
    m_rank_lable_slot3 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                             GFX_RUNTIME_CLASS(CIFStatic),
                                                             rect_m_rank_lable_slot3,
                                                             GDR_DPS_PLAYERNAME_LABEL,
                                                             1);
    RECT rect_m_rank_lable_slot4 = {9,96,13,13};
    m_rank_lable_slot4 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                             GFX_RUNTIME_CLASS(CIFStatic),
                                                             rect_m_rank_lable_slot4,
                                                             GDR_DPS_PLAYERNAME_LABEL,
                                                             1);
    RECT rect_m_rank_lable_slot5 = {9,111,13,13};
    m_rank_lable_slot5 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                             GFX_RUNTIME_CLASS(CIFStatic),
                                                             rect_m_rank_lable_slot5,
                                                             GDR_DPS_PLAYERNAME_LABEL,
                                                             1);
    RECT rect_m_rank_lable_slot6 = {9,126,13,13};
    m_rank_lable_slot6 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                             GFX_RUNTIME_CLASS(CIFStatic),
                                                             rect_m_rank_lable_slot6,
                                                             GDR_DPS_PLAYERNAME_LABEL,
                                                             1);
    RECT rect_m_rank_lable_slot7 = {9,141,13,13};
    m_rank_lable_slot7 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                             GFX_RUNTIME_CLASS(CIFStatic),
                                                             rect_m_rank_lable_slot7,
                                                             GDR_DPS_PLAYERNAME_LABEL,
                                                             1);
    RECT rect_m_rank_lable_slot8 = {9,156,13,13};
    m_rank_lable_slot8 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                             GFX_RUNTIME_CLASS(CIFStatic),
                                                             rect_m_rank_lable_slot8,
                                                             GDR_DPS_PLAYERNAME_LABEL,
                                                             1);
    RECT rect_m_unique_icon = {9,183,16,16};
    m_unique_icon = (CIFStatic *) CGWnd::CreateInstance(this,
                                                             GFX_RUNTIME_CLASS(CIFStatic),
                                                             rect_m_unique_icon,
                                                             GDR_DPS_PLAYERNAME_LABEL,
                                                             1);
    RECT rect_m_unique_name = {40,180,100,20};
    m_unique_name = (CIFStatic *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFStatic),
                                                        rect_m_unique_name,
                                                        GDR_DPS_PLAYERNAME_LABEL,
                                                        1);

    m_rank_lable_slot1->SetText(L"1.");
    m_rank_lable_slot2->SetText(L"2.");
    m_rank_lable_slot3->SetText(L"3.");
    m_rank_lable_slot4->SetText(L"4.");
    m_rank_lable_slot5->SetText(L"5.");
    m_rank_lable_slot6->SetText(L"6.");
    m_rank_lable_slot7->SetText(L"7.");
    m_rank_lable_slot8->SetText(L"8.");
    m_playername_lable->SetText(L"Player");
    m_damage_lable->SetText(L"Damage");
    m_frame_lable->SetText(L"Dps Metter");
    m_unique_name->SetText(L"tesstttt");
    m_unique_icon->TB_Func_13("interface\\targetwindow\\tw_icon_unique.ddj", 1, 0);

    USHORT PosX = 0, PosY = 20;
    PosX = CLIENT_SCREEN_WIDTH - 400;
    this->MoveGWnd(PosX, PosY);
    this->ShowGWnd(false);
    return true;
}


void CIFSTDpsMetter::On_BtnClick() {
    static int i = 0;

}

void CIFSTDpsMetter::OnUpdate() {
    time_t rawtime;
    struct tm *timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);

}
