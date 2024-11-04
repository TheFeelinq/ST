 //
// Created by Admin on 18/2/2022.
//

#include "IFSTPartyMatchMemberViewer.h"
#include "IFNormalTile.h"
#include <ctime>
#include <sstream>
#include "ClientNet/MsgStreamBuffer.h"
#include "Game.h"
#include <BSLib/multibyte.h>

#define GDR_FLORIAN0_RT_LABEL 10
#define GDR_FLORIAN0_RT_MAIN_FRAME 20
GFX_IMPLEMENT_DYNCREATE(CIFSTPartyMatchMemberViewer, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTPartyMatchMemberViewer, CIFMainFrame)
                   // ONG_COMMAND(GDR_FLORIAN0_RT_BTN, &On_BtnClickGold)
                   // ONG_COMMAND(GDR_FLORIAN0_RT_BTN2, &On_BtnClickSilk)

GFX_END_MESSAGE_MAP()

std::vector<CIFSTPartyMatchMemberViewer::PartyMatchMember> CIFSTPartyMatchMemberViewer::PartyMatchMemberList;

CIFSTPartyMatchMemberViewer::CIFSTPartyMatchMemberViewer() :
        m_custom_label(NULL) {

}

bool CIFSTPartyMatchMemberViewer::OnCreate(long ln) {
    //CIFMainFrame::OnCreate(ln);


    RECT rect_frame = {0, 0, 200, 236};

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame,
                                                  GDR_FLORIAN0_RT_MAIN_FRAME,
                                                  1);
    frame->TB_Func_13("interface\\frame\\frame_tooltip_", 1, 0);

    RECT rect_background = {rect_frame.left + 5,
                            rect_frame.top + 5,
                            rect_frame.right - 10,
                            rect_frame.bottom - 10};

    CIFNormalTile *tile = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background,
                                                           GDR_FLORIAN0_RT_MAIN_FRAME,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_tl.ddj", 1, 0);
/////////
    RECT rect_bg1 ={rect_frame.left + 5,
                    rect_frame.top + 5,
                    rect_frame.right - 10,
                    28};
    CIFStatic *bg1 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_bg1,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);
    bg1->TB_Func_13("interface\\party\\pt_tooltip_listbar.ddj", 1, 1);

    RECT rect_bg2 ={rect_frame.left + 5,
                    rect_frame.top + 5 + 28,
                    rect_frame.right - 10,
                    28};
    CIFStatic *bg2 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_bg2,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);
    bg2->TB_Func_13("interface\\party\\pt_tooltip_listbar.ddj", 1, 1);

    RECT rect_bg3 ={rect_frame.left + 5,
                    rect_frame.top + 5 + (28*2),
                    rect_frame.right - 10,
                    28};
    CIFStatic *bg3 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_bg3,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);
    bg3->TB_Func_13("interface\\party\\pt_tooltip_listbar.ddj", 1, 1);

    RECT rect_bg4 ={rect_frame.left + 5,
                    rect_frame.top + 5 + (28*3),
                    rect_frame.right - 10,
                    28};
    CIFStatic *bg4 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_bg4,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);
    bg4->TB_Func_13("interface\\party\\pt_tooltip_listbar.ddj", 1, 1);

    RECT rect_bg5 ={rect_frame.left + 5,
                    rect_frame.top + 5 + (28*4),
                    rect_frame.right - 10,
                    28};
    CIFStatic *bg5 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_bg5,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);
    bg5->TB_Func_13("interface\\party\\pt_tooltip_listbar.ddj", 1, 1);

    RECT rect_bg6 ={rect_frame.left + 5,
                    rect_frame.top + 5 + (28*5),
                    rect_frame.right - 10,
                    28};
    CIFStatic *bg6 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_bg6,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);
    bg6->TB_Func_13("interface\\party\\pt_tooltip_listbar.ddj", 1, 1);

    RECT rect_bg7 ={rect_frame.left + 5,
                    rect_frame.top + 5 + (28*6),
                    rect_frame.right - 10,
                    28};
    CIFStatic *bg7 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_bg7,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);
    bg7->TB_Func_13("interface\\party\\pt_tooltip_listbar.ddj", 1, 1);

    RECT rect_bg8 ={rect_frame.left + 5,
                    rect_frame.top + 5 + (28*7),
                    rect_frame.right - 10,
                    28};
    CIFStatic *bg8 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_bg8,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);
    bg8->TB_Func_13("interface\\party\\pt_tooltip_listbar.ddj", 1, 1);


    m_slot1 = (CIFSTPartyMatchMemberViewerSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlotList), rect_bg1, 40, 0);
    m_slot2 = (CIFSTPartyMatchMemberViewerSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlotList), rect_bg2, 41, 0);
    m_slot3 = (CIFSTPartyMatchMemberViewerSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlotList), rect_bg3, 42, 0);
    m_slot4 = (CIFSTPartyMatchMemberViewerSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlotList), rect_bg4, 43, 0);
    m_slot5 = (CIFSTPartyMatchMemberViewerSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlotList), rect_bg5, 44, 0);
    m_slot6 = (CIFSTPartyMatchMemberViewerSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlotList), rect_bg6, 45, 0);
    m_slot7 = (CIFSTPartyMatchMemberViewerSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlotList), rect_bg7, 46, 0);
    m_slot8 = (CIFSTPartyMatchMemberViewerSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlotList), rect_bg8, 47, 0);

    
    ResetPosition();
    HideLists();
    m_slot1->ShowGWnd(true);
    this->ShowGWnd(false);
    return true;
}



void CIFSTPartyMatchMemberViewer::OnUpdate() {

}

void CIFSTPartyMatchMemberViewer::HideLists()
{
    m_slot1->ShowGWnd(false);
    m_slot2->ShowGWnd(false);
    m_slot3->ShowGWnd(false);
    m_slot4->ShowGWnd(false);
    m_slot5->ShowGWnd(false);
    m_slot6->ShowGWnd(false);
    m_slot7->ShowGWnd(false);
    m_slot8->ShowGWnd(false);

}
void CIFSTPartyMatchMemberViewer::ClearDDJ() {
    m_slot1->ClearDDJ();
    m_slot2->ClearDDJ();
    m_slot3->ClearDDJ();
    m_slot4->ClearDDJ();
    m_slot5->ClearDDJ();
    m_slot6->ClearDDJ();
    m_slot7->ClearDDJ();
    m_slot8->ClearDDJ();

}
void CIFSTPartyMatchMemberViewer::ShowList(BYTE listid)
{
    switch (listid)
    {
        case 1:
            HideLists();
            m_slot1->ShowGWnd(true);
            break;
        case 2:
            HideLists();
            m_slot2->ShowGWnd(true);
            break;
        case 3:
            HideLists();
            m_slot3->ShowGWnd(true);
            break;
        case 4:
            HideLists();
            m_slot4->ShowGWnd(true);
            break;
        case 5:
            HideLists();
            m_slot5->ShowGWnd(true);
            break;
        case 6:
            HideLists();
            m_slot6->ShowGWnd(true);
            break;
        case 7:
            HideLists();
            m_slot7->ShowGWnd(true);
            break;
        case 8:
            HideLists();
            m_slot8->ShowGWnd(true);
            break;

    }
}



void CIFSTPartyMatchMemberViewer::UpdatePartyMemberList()
{

    for (std::vector<CIFSTPartyMatchMemberViewer::PartyMatchMember>::iterator it = CIFSTPartyMatchMemberViewer::PartyMatchMemberList.begin(); it != CIFSTPartyMatchMemberViewer::PartyMatchMemberList.end(); ++it)
    {

        switch ((*it).LineNum)
        {
            case 0:
            {
                m_slot1->line1->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 1:
            {
                m_slot1->line2->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line3->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line4->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line5->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line6->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line7->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line8->WriteLine((*it).Race,(*it).CharName.c_str(), (*it).LevelText.c_str(), (*it).Level.c_str());
            }
                break;

        }
    }
}

void CIFSTPartyMatchMemberViewer::Clear()
{
    m_slot1->line1->WriteLine(0, L"", L"", L"");
    m_slot1->line2->WriteLine(0, L"", L"", L"");
    m_slot1->line3->WriteLine(0, L"", L"", L"");
    m_slot1->line4->WriteLine(0, L"", L"", L"");
    m_slot1->line5->WriteLine(0, L"", L"", L"");
    m_slot1->line6->WriteLine(0, L"", L"", L"");
    m_slot1->line7->WriteLine(0, L"", L"", L"");
    m_slot1->line8->WriteLine(0, L"", L"", L"");
}
void CIFSTPartyMatchMemberViewer::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}