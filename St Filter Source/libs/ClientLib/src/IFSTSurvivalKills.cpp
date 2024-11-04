#include "IFSTSurvivalKills.h"
#include "IFNormalTile.h"
#include <ctime>
#include "memhelp.h"
#include "Packet.h"
#include "Game.h"
#include "ICPlayer.h"
#include "sstream"
#include <BSLib/multibyte.h>
#define GDR_DPS_RT_LABEL 10
#define GDR_DPS_RT_MAIN_FRAME 20

#define GDR_DPS_PLAYERNAME_LABEL 21
#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)


GFX_IMPLEMENT_DYNCREATE(CIFSTSurvivalKills, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTSurvivalKills, CIFMainFrame)

GFX_END_MESSAGE_MAP()


CIFSTSurvivalKills::CIFSTSurvivalKills() :
        m_damage_lable(NULL) {

}

bool CIFSTSurvivalKills::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);

    // Set own title

    TB_Func_13("interface\\frame\\mall_ms_wnd_", 1, 0);

    RECT rect_background = {32,
                            44,
                            123,
                            95};

    CIFNormalTile *tile = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background,
                                                           GDR_DPS_RT_MAIN_FRAME,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_m.ddj", 1, 0);

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

    RECT rect_m_unique_icon = {9,138,105,13};
    m_unique_icon = (CIFStatic *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFStatic),
                                                        rect_m_unique_icon,
                                                        GDR_DPS_PLAYERNAME_LABEL,
                                                        1);
    RECT rect_m_unique_name = {132,138,14,14};
    m_unique_name = (CIFStatic *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFStatic),
                                                        rect_m_unique_name,
                                                        GDR_DPS_PLAYERNAME_LABEL,
                                                        1);

    m_rank_lable_slot1->SetText(L"#1");
    m_rank_lable_slot2->SetText(L"#2");
    m_rank_lable_slot3->SetText(L"#3");
    m_rank_lable_slot4->SetText(L"#4");
    m_rank_lable_slot5->SetText(L"#5");
    m_playername_lable->SetText(L"Player");
    m_damage_lable->SetText(L"Kills");
    m_frame_lable->SetText(L"Survival Kills");
    m_unique_name->SetText(L"0");
    m_unique_icon->SetText(L"Your Sur Kills:");


    this->ResetPosition();
    this->ShowGWnd(false);
    return true;
}


void CIFSTSurvivalKills::OnUpdate() {
    time_t rawtime;
    struct tm *timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);

}
void CIFSTSurvivalKills::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width), (client.res[0].height - v109.height) / 2);
}
void CIFSTSurvivalKills::WriteLine(int Num, const wchar_t* Charname, const wchar_t* DMG) const
{
    if((Charname, g_pCICPlayer->GetCharName().c_str()) == 0)
    {
        m_unique_name->SetText(DMG);
    }

    switch (Num)
    {
        case 1:
            m_playername_lable_slot1->SetText(Charname);
            m_damage_lable_slot1->SetText(DMG);
            break;
        case 2:
            m_playername_lable_slot2->SetText(Charname);
            m_damage_lable_slot2->SetText(DMG);
            break;
        case 3:
            m_playername_lable_slot3->SetText(Charname);
            m_damage_lable_slot3->SetText(DMG);
            break;
        case 4:
            m_playername_lable_slot4->SetText(Charname);
            m_damage_lable_slot4->SetText(DMG);
            break;
        case 5:
            m_playername_lable_slot5->SetText(Charname);
            m_damage_lable_slot5->SetText(DMG);
            break;
        default:
            break;
    }
}

void CIFSTSurvivalKills::Clear() const
{
    m_playername_lable_slot1->SetText(L"-");
    m_damage_lable_slot1->SetText(L"-");

    m_playername_lable_slot2->SetText(L"-");
    m_damage_lable_slot2->SetText(L"-");

    m_playername_lable_slot3->SetText(L"-");
    m_damage_lable_slot3->SetText(L"-");

    m_playername_lable_slot4->SetText(L"-");
    m_damage_lable_slot4->SetText(L"-");

    m_playername_lable_slot5->SetText(L"-");
    m_damage_lable_slot5->SetText(L"-");
}