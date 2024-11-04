//
// Created by Admin on 12/8/2022.
//

#include "IFSTBattleRoyaleKillCount.h"
#include "IFNormalTile.h"
#include <ctime>
#include "Game.h"
#include "ICPlayer.h"
#include "sstream"
#include <BSLib/multibyte.h>

#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)


GFX_IMPLEMENT_DYNCREATE(CIFSTBattleRoyaleKillCount, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTBattleRoyaleKillCount, CIFMainFrame)

GFX_END_MESSAGE_MAP()


bool CIFSTBattleRoyaleKillCount::OnCreate(long ln) {
    //CIFMainFrame::OnCreate(ln);

    // Set own title


    RECT rect_m_frame = {0,0,140,140};
    m_frame = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_frame,101,1);
    m_frame->TB_Func_13("interface\\royale\\eventpopup.ddj", 1, 0);

    RECT rect_m_left_survivor_lable = {10,26,80,20};
    m_left_survivor_lable = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_left_survivor_lable,102,1);

    RECT rect_m_left_survivor_value = {100,26,40,20};
    m_left_survivor_value = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_left_survivor_value,103,1);

    RECT rect_m_total_participants = {10,51,80,20};
    m_total_participants = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_total_participants,104,1);

    RECT rect_m_total_participants_value = {100,51,40,20};
    m_total_participants_value = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_total_participants_value,105,1);

    RECT rect_m_my_kill = {10,76,80,20};
    m_my_kill_lable = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_my_kill,106,1);

    RECT rect_m_my_kill_value = {100,76,40,20};
    m_my_kill_value = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_my_kill_value,107,1);


    m_left_survivor_lable->SetText(L"Left Survivors");
    m_total_participants->SetText(L"Total Participants");
    m_my_kill_lable->SetText(L"My Kills");
    m_left_survivor_value->SetText(L"0");
    m_total_participants_value->SetText(L"0");
    m_my_kill_value->SetText(L"0");



    this->ResetPosition();
    this->ShowGWnd(false);
    return true;
}
void CIFSTBattleRoyaleKillCount::OnUpdate() {

}
void CIFSTBattleRoyaleKillCount::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width), 0);
}
