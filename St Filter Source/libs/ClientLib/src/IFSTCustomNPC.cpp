#include "IFSTCustomNPC.h"
#include "GInterface.h"
#include "GlobalDataManager.h"
#include "Game.h"
#include "GameDataExt.h"

#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>
#include <unsorted.h>
#include <ICPlayer.h>

#include <sstream>
#include <BSLib/multibyte.h>

#define GDR_Thief_BTN 3
#define GDR_Hunter_BTN 5
#define GDR_Trader_BTN 6
#define GDR_BUY_BTN 28
#define GDR_TEST_BTN 8

GFX_IMPLEMENT_DYNCREATE(CIFSTCustomNPC, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFSTCustomNPC, CIFMainFrame)
                    ONG_COMMAND(100, &CIFSTCustomNPC::OnUnknownStuff)
                    ONG_COMMAND(101, &CIFSTCustomNPC::OnUnknownStuff)
                    /*   ONG_COMMAND(102, &CIFSTCustomNPC::OnUnknownStuff)
                       ONG_COMMAND(103, &CIFSTCustomNPC::OnUnknownStuff)
                       ONG_COMMAND(104, &CIFSTCustomNPC::OnUnknownStuff)
                       ONG_COMMAND(105, &CIFSTCustomNPC::OnUnknownStuff)*/
                    ONG_COMMAND(GDR_BUY_BTN, &CIFSTCustomNPC::OnBuyItem)
                    ONG_COMMAND(GDR_TEST_BTN, &CIFSTCustomNPC::OnTestItem)

GFX_END_MESSAGE_MAP()

#define GDR_GXVSRO_FRAME 1
#define GDR_GXVSRO_TITLE 2
#define GDR_1_BTN 20
#define GDR_2_BTN 21
#define GDR_3_BTN 22
#define GDR_4_BTN 24
#define GDR_5_BTN 23
#define GDR_6_BTN 25


std::vector<CIFSTCustomNPC::RankStruct> CIFSTCustomNPC::GoldRankList;

std::vector<CIFSTCustomNPC::RankStruct> CIFSTCustomNPC::UniquesRankList;

CIFSTCustomNPC::CIFSTCustomNPC(void)
{
    //  printf("> " __FUNCTION__ "\n");
}


CIFSTCustomNPC::~CIFSTCustomNPC(void)
{
    //  printf("> " __FUNCTION__ "\n");
}
int CIFSTCustomNPC::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
bool CIFSTCustomNPC::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT rect_m_tile = {116, 9, 186, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMNPC_SHOP"));

    RECT Framerect = { 17,45,180,185 };
    RECT Lablerect = { 16,308,480,62 };
    RECT Buttrect = { 80,364,16,16 };
    RECT Butt2rect = { 60,364,16,16 };
    RECT Butt6rect = { 100,360,60,24 };
    RECT Butt7rect = { 30,360,60,24 };
    RECT Butt3rect = { 40,364,16,16 };
    RECT Butt1rect = { 26,76,50,23 };
    RECT Butt12rect = { 72,76,140,23 };
    RECT Butt4rect = { 208,76,120,23 };
    RECT Butt13rect = { 317,76,64,23 };
    RECT Spinrect = { 177,364,50,16 };

    Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), Framerect, GDR_GXVSRO_FRAME, 0);
    m_custom_label = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect, GDR_GXVSRO_TITLE, 0);
    m_mybutton = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Buttrect, GDR_Thief_BTN, 0);
    m_mybutton2 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt2rect, GDR_Hunter_BTN, 0);
    m_mybutton3 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt3rect, GDR_Trader_BTN, 0);
    m_mybutton4 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt6rect, GDR_BUY_BTN, 0);
    m_mybutton5 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt7rect, GDR_TEST_BTN, 0);

    Rank = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt1rect, GDR_1_BTN, 0);
    Charname = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt12rect, GDR_3_BTN, 0);
    Guild = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt4rect, GDR_6_BTN, 0);
    Points = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt13rect, GDR_5_BTN, 0);
    m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), Spinrect, 4, 0);

    Rank->TB_Func_13("interface\\guild\\gil_subj_button04.ddj", 0, 0);
    Charname->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    Points->TB_Func_13("interface\\guild\\gil_subj_button12.ddj", 0, 0);
    Guild->TB_Func_13("interface\\guild\\gil_subj_button12.ddj", 0, 0);
    m_custom_label->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
    m_mybutton->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electushonorpoints_thief.ddj", 0, 0);
    m_mybutton2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electushonorpoints_hunter.ddj", 0, 0);
    m_mybutton3->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electushonorpoints_trader.ddj", 0, 0);
    m_mybutton4->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton5->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);

    Frame->SetGWndSize(this->GetSize().width - 20, this->GetSize().height - 75);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 65);
    m_custom_label->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
    m_custom_label->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);

    Rank->SetText(L"#");
    Charname->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMNPC_ITEMNAME"));
    Points->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMNPC_PRICE"));
    Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMNPC_COUNT"));

    m_mybutton4->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMNPC_BUY"));
    m_mybutton5->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMNPC_TEST"));
    m_pTabs = new CIFSelectableArea * [numberOfTabs];

    for (int i = 0; i < numberOfTabs; i++) {

        RECT selectable_area_size;
        selectable_area_size.top = 0;
        selectable_area_size.left = tabMarginLeft + tabWidth * i;
        selectable_area_size.right = tabWidth + 1;
        selectable_area_size.bottom = tabHeight;

        m_pTabs[i] = (CIFSelectableArea*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSelectableArea),
                                                               selectable_area_size, tabFirstId + i, 0);
        m_pTabs[i]->SetFont(this->N00009C2F);

        m_pTabs[i]->sub_64CE30("interface\\ifcommon\\com_tab_on.ddj",
                               "interface\\ifcommon\\com_tab_off.ddj", "interface\\ifcommon\\com_tab_disable.ddj");

        switch (i) {
            case 0:
                m_pTabs[0]->MoveGWnd(Frame->GetPos().x + 10, GetPos().y + 41);
                m_pTabs[0]->sub_64CC30(1);
                break;
            case 1:
                m_pTabs[1]->MoveGWnd(m_pTabs[0]->GetPos().x + m_pTabs[0]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[1]->sub_64CC30(0);
                break;
/*            case 2:
                m_pTabs[2]->MoveGWnd(m_pTabs[1]->GetPos().x + m_pTabs[1]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[2]->sub_64CC30(0);
                break;
            case 3:
                m_pTabs[3]->MoveGWnd(m_pTabs[2]->GetPos().x + m_pTabs[2]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[3]->sub_64CC30(0);
                break;
            case 4:
                m_pTabs[4]->MoveGWnd(m_pTabs[3]->GetPos().x + m_pTabs[3]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[4]->sub_64CC30(0);
                break;
            case 5:
                m_pTabs[5]->MoveGWnd(m_pTabs[4]->GetPos().x + m_pTabs[4]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[5]->sub_64CC30(0);
                break;*/
        }
    }

    m_title->SetText(L"Dynamic Rank");
    m_pTabs[0]->SetText(L"Icon");//--
    m_pTabs[1]->SetText(L"None");
//    m_pTabs[2]->SetText(L"Job");//--
//    m_pTabs[3]->SetText(L"Gold");//--
//    m_pTabs[4]->SetText(L"Item");//--
//    m_pTabs[5]->SetText(L"Level");

    RECT rect = { 0,0,0,0 };
    m_slot1 = (CIFSTCustomNPCList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCList), rect, 40, 0);
    m_slot2 = (CIFSTCustomNPCList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCList), rect, 41, 0);
    m_slot3 = (CIFSTCustomNPCList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCList), rect, 42, 0);
    m_slot4 = (CIFSTCustomNPCList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCList), rect, 43, 0);
    m_slot5 = (CIFSTCustomNPCList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCList), rect, 44, 0);
    m_slot6 = (CIFSTCustomNPCList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCList), rect, 45, 0);
    m_slot7 = (CIFSTCustomNPCList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCList), rect, 46, 0);
    m_slot8 = (CIFSTCustomNPCList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCList), rect, 47, 0);
    m_slot9 = (CIFSTCustomNPCList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCList), rect, 48, 0);
    m_slot10 = (CIFSTCustomNPCList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCList), rect, 49, 0);
    HideLists();
    m_slot1->ShowGWnd(true);
    m_slot1->MoveGWnd(m_slot1->GetPos().x + 7, m_slot1->GetPos().y + 24);
    m_slot2->MoveGWnd(m_slot2->GetPos().x + 7, m_slot2->GetPos().y + 24);
    m_slot3->MoveGWnd(m_slot3->GetPos().x + 7, m_slot3->GetPos().y + 24);
    m_slot4->MoveGWnd(m_slot4->GetPos().x + 7, m_slot4->GetPos().y + 24);
    m_slot5->MoveGWnd(m_slot5->GetPos().x + 7, m_slot5->GetPos().y + 24);
    m_slot6->MoveGWnd(m_slot6->GetPos().x + 7, m_slot6->GetPos().y + 24);
    m_slot7->MoveGWnd(m_slot7->GetPos().x + 7, m_slot7->GetPos().y + 24);
    m_slot8->MoveGWnd(m_slot8->GetPos().x + 7, m_slot8->GetPos().y + 24);
    m_slot9->MoveGWnd(m_slot9->GetPos().x + 7, m_slot9->GetPos().y + 24);
    m_slot10->MoveGWnd(m_slot10->GetPos().x + 7, m_slot10->GetPos().y + 24);

    m_spin->SetMinValue(1);
    m_spin->SetCurrentValue(1);
    m_spin->SetMaxValue(10);
    m_spin->ShowGWnd(true);

    Rank->BringToFront();
    Charname->BringToFront();
    Guild->BringToFront();
    Points->BringToFront();
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    m_mybutton->ShowGWnd(false);
    m_mybutton2->ShowGWnd(false);
    m_mybutton3->ShowGWnd(false);
    m_mybutton4->ShowGWnd(false);
    m_mybutton5->ShowGWnd(false);
    this->ShowGWnd(false);
    ResetPosition();
    return true;
}

void CIFSTCustomNPC::OnUnknownStuff() {
    int id = GetIDOfInterfaceUnderCursor();
    int i = 0;

    for (int i = 0; i < numberOfTabs; ++i) {
        if (id == m_pTabs[i]->UniqueID()) {
            ActivateTabPage(i);
            return;
        }
    }
}

void CIFSTCustomNPC::ActivateTabPage(BYTE page) {

    for (int i = 0; i < numberOfTabs; i++) {
        if (i == page)
            continue;

        m_pTabs[i]->sub_64CC30(0);
    }

    m_pTabs[page]->sub_64CC30(1);

    //job hiden buttons
    if (page == 2)
    {
        m_mybutton->ShowGWnd(true);
        m_mybutton2->ShowGWnd(true);
        m_mybutton3->ShowGWnd(true);
    }
    else
    {
        m_mybutton->ShowGWnd(false);
        m_mybutton2->ShowGWnd(false);
        m_mybutton3->ShowGWnd(false);
    }
    if (page == 0)
    {
        m_mybutton4->ShowGWnd(true);
        m_mybutton5->ShowGWnd(true);
    }
    else
    {
        m_mybutton4->ShowGWnd(false);
        m_mybutton5->ShowGWnd(false);

    }
    switch (page)
    {
        case 0:
           // Points->SetText(L"Point/Kill");
           // Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_GUILD"));
            ClearDDJ();
            Clear();
            UpdateUniqueRank();
            break;
        case 1:
           // Points->SetText(L"Item Point");
           // Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_GUILD"));
            ClearDDJ();
            Clear();
            UpdateGoldRank();
            //UpdateGuildRank();
            break;
            /*  case 2:
                  Points->SetText(L"Kill");
                  Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_JOBTYPE"));
                  Clear();
                  UpdateJobKillsRank();
                  break;
              case 3:
                  Points->SetText(L"Gold");
                  Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_GUILD"));
                  Clear();
                  UpdateGoldRank();
                  break;
              case 4:
                  Points->SetText(L"Item Point");
                  Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_GUILD"));
                  Clear();
                  UpdateCharRank();
                  break;
              case 5:
                  Points->SetText(L"Lvl/Exp");
                  Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_GUILD"));
                  Clear();
                  UpdateLevelRank();
                  break;*/
    }
}

void CIFSTCustomNPC::Clear()
{
    m_slot1->line1->m_custom_label2->ShowGWnd(false);
    m_slot1->line2->m_custom_label2->ShowGWnd(false);
    m_slot1->line3->m_custom_label2->ShowGWnd(false);
    m_slot1->line4->m_custom_label2->ShowGWnd(false);
    m_slot1->line5->m_custom_label2->ShowGWnd(false);

    m_slot1->line11->m_custom_label2->ShowGWnd(false);
    m_slot2->line11->m_custom_label2->ShowGWnd(false);
    m_slot3->line11->m_custom_label2->ShowGWnd(false);
    m_slot4->line11->m_custom_label2->ShowGWnd(false);
    m_slot5->line11->m_custom_label2->ShowGWnd(false);

    m_slot1->line1->WriteLine(L"", "", L"", L"");
    m_slot1->line2->WriteLine(L"", "", L"", L"");
    m_slot1->line3->WriteLine(L"", "", L"", L"");
    m_slot1->line4->WriteLine(L"", "", L"", L"");
    m_slot1->line5->WriteLine(L"", "", L"", L"");
    m_slot1->line6->WriteLine(L"", "", L"", L"");
    m_slot1->line7->WriteLine(L"", "", L"", L"");
    m_slot1->line8->WriteLine(L"", "", L"", L"");
    m_slot1->line9->WriteLine(L"", "", L"", L"");
    m_slot1->line10->WriteLine(L"", "", L"", L"");
    m_slot1->line11->WriteLine(L"", "", L"", L"");
    m_slot2->line1->WriteLine(L"", "", L"", L"");
    m_slot2->line2->WriteLine(L"", "", L"", L"");
    m_slot2->line3->WriteLine(L"", "", L"", L"");
    m_slot2->line4->WriteLine(L"", "", L"", L"");
    m_slot2->line5->WriteLine(L"", "", L"", L"");
    m_slot2->line6->WriteLine(L"", "", L"", L"");
    m_slot2->line7->WriteLine(L"", "", L"", L"");
    m_slot2->line8->WriteLine(L"", "", L"", L"");
    m_slot2->line9->WriteLine(L"", "", L"", L"");
    m_slot2->line10->WriteLine(L"", "", L"", L"");
    m_slot2->line11->WriteLine(L"", "", L"", L"");
    m_slot3->line1->WriteLine(L"", "", L"", L"");
    m_slot3->line2->WriteLine(L"", "", L"", L"");
    m_slot3->line3->WriteLine(L"", "", L"", L"");
    m_slot3->line4->WriteLine(L"", "", L"", L"");
    m_slot3->line5->WriteLine(L"", "", L"", L"");
    m_slot3->line6->WriteLine(L"", "", L"", L"");
    m_slot3->line7->WriteLine(L"", "", L"", L"");
    m_slot3->line8->WriteLine(L"", "", L"", L"");
    m_slot3->line9->WriteLine(L"", "", L"", L"");
    m_slot3->line10->WriteLine(L"", "", L"", L"");
    m_slot3->line11->WriteLine(L"", "", L"", L"");
    m_slot4->line1->WriteLine(L"", "", L"", L"");
    m_slot4->line2->WriteLine(L"", "", L"", L"");
    m_slot4->line3->WriteLine(L"", "", L"", L"");
    m_slot4->line4->WriteLine(L"", "", L"", L"");
    m_slot4->line5->WriteLine(L"", "", L"", L"");
    m_slot4->line6->WriteLine(L"", "", L"", L"");
    m_slot4->line7->WriteLine(L"", "", L"", L"");
    m_slot4->line8->WriteLine(L"", "", L"", L"");
    m_slot4->line9->WriteLine(L"", "", L"", L"");
    m_slot4->line10->WriteLine(L"", "", L"", L"");
    m_slot4->line11->WriteLine(L"", "", L"", L"");
    m_slot5->line1->WriteLine(L"", "", L"", L"");
    m_slot5->line2->WriteLine(L"", "", L"", L"");
    m_slot5->line3->WriteLine(L"", "", L"", L"");
    m_slot5->line4->WriteLine(L"", "", L"", L"");
    m_slot5->line5->WriteLine(L"", "", L"", L"");
    m_slot5->line6->WriteLine(L"", "", L"", L"");
    m_slot5->line7->WriteLine(L"", "", L"", L"");
    m_slot5->line8->WriteLine(L"", "", L"", L"");
    m_slot5->line9->WriteLine(L"", "", L"", L"");
    m_slot5->line10->WriteLine(L"","", L"", L"");
    m_slot5->line11->WriteLine(L"", "", L"", L"");
    m_slot6->line1->WriteLine(L"", "", L"", L"");
    m_slot6->line2->WriteLine(L"", "", L"", L"");
    m_slot6->line3->WriteLine(L"", "", L"", L"");
    m_slot6->line4->WriteLine(L"", "", L"", L"");
    m_slot6->line5->WriteLine(L"", "", L"", L"");
    m_slot6->line6->WriteLine(L"", "", L"", L"");
    m_slot6->line7->WriteLine(L"", "", L"", L"");
    m_slot6->line8->WriteLine(L"", "", L"", L"");
    m_slot6->line9->WriteLine(L"", "", L"", L"");
    m_slot6->line10->WriteLine(L"", "", L"", L"");

    m_slot7->line1->WriteLine(L"", "", L"", L"");
    m_slot7->line2->WriteLine(L"", "", L"", L"");
    m_slot7->line3->WriteLine(L"", "", L"", L"");
    m_slot7->line4->WriteLine(L"", "", L"", L"");
    m_slot7->line5->WriteLine(L"", "", L"", L"");
    m_slot7->line6->WriteLine(L"", "", L"", L"");
    m_slot7->line7->WriteLine(L"", "", L"", L"");
    m_slot7->line8->WriteLine(L"", "", L"", L"");
    m_slot7->line9->WriteLine(L"", "", L"", L"");
    m_slot7->line10->WriteLine(L"", "", L"", L"");

    m_slot8->line1->WriteLine(L"", "", L"", L"");
    m_slot8->line2->WriteLine(L"", "", L"", L"");
    m_slot8->line3->WriteLine(L"", "", L"", L"");
    m_slot8->line4->WriteLine(L"", "", L"", L"");
    m_slot8->line5->WriteLine(L"", "", L"", L"");
    m_slot8->line6->WriteLine(L"", "", L"", L"");
    m_slot8->line7->WriteLine(L"", "", L"", L"");
    m_slot8->line8->WriteLine(L"", "", L"", L"");
    m_slot8->line9->WriteLine(L"", "", L"", L"");
    m_slot8->line10->WriteLine(L"", "", L"", L"");

    m_slot9->line1->WriteLine(L"", "", L"", L"");
    m_slot9->line2->WriteLine(L"", "", L"", L"");
    m_slot9->line3->WriteLine(L"", "", L"", L"");
    m_slot9->line4->WriteLine(L"", "", L"", L"");
    m_slot9->line5->WriteLine(L"", "", L"", L"");
    m_slot9->line6->WriteLine(L"", "", L"", L"");
    m_slot9->line7->WriteLine(L"", "", L"", L"");
    m_slot9->line8->WriteLine(L"", "", L"", L"");
    m_slot9->line9->WriteLine(L"", "", L"", L"");
    m_slot9->line10->WriteLine(L"", "", L"", L"");

    m_slot10->line1->WriteLine(L"", "", L"", L"");
    m_slot10->line2->WriteLine(L"", "", L"", L"");
    m_slot10->line3->WriteLine(L"", "", L"", L"");
    m_slot10->line4->WriteLine(L"", "", L"", L"");
    m_slot10->line5->WriteLine(L"", "", L"", L"");
    m_slot10->line6->WriteLine(L"", "", L"", L"");
    m_slot10->line7->WriteLine(L"", "", L"", L"");
    m_slot10->line8->WriteLine(L"", "", L"", L"");
    m_slot10->line9->WriteLine(L"", "", L"", L"");
    m_slot10->line10->WriteLine(L"", "", L"", L"");
}

void CIFSTCustomNPC::ShowList(BYTE listid)
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
        case 9:
            HideLists();
            m_slot9->ShowGWnd(true);
            break;
        case 10:
            HideLists();
            m_slot10->ShowGWnd(true);
            break;
    }
}



void CIFSTCustomNPC::UpdateUniqueRank()
{
    for (std::vector<CIFSTCustomNPC::RankStruct>::iterator it = CIFSTCustomNPC::UniquesRankList.begin(); it != CIFSTCustomNPC::UniquesRankList.end(); ++it)
    {

        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());




            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 51:
            {
                m_slot6->line1->WriteLine(L"51", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 52:
            {
                m_slot6->line2->WriteLine(L"52", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 53:
            {
                m_slot6->line3->WriteLine(L"53", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 54:
            {
                m_slot6->line4->WriteLine(L"54", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 55:
            {
                m_slot6->line5->WriteLine(L"55", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 56:
            {
                m_slot6->line6->WriteLine(L"56", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 57:
            {
                m_slot6->line7->WriteLine(L"57", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 58:
            {
                m_slot6->line8->WriteLine(L"58", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 59:
            {
                m_slot6->line9->WriteLine(L"59", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 60:
            {
                m_slot6->line10->WriteLine(L"60", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 61:
            {
                m_slot7->line1->WriteLine(L"61", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 62:
            {
                m_slot7->line2->WriteLine(L"62", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 63:
            {
                m_slot7->line3->WriteLine(L"63", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 64:
            {
                m_slot7->line4->WriteLine(L"64", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 65:
            {
                m_slot7->line5->WriteLine(L"65", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 66:
            {
                m_slot7->line6->WriteLine(L"66", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 67:
            {
                m_slot7->line7->WriteLine(L"67", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 68:
            {
                m_slot7->line8->WriteLine(L"68", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 69:
            {
                m_slot7->line9->WriteLine(L"69", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 70:
            {
                m_slot7->line10->WriteLine(L"70", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 71:
            {
                m_slot8->line1->WriteLine(L"71", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 72:
            {
                m_slot8->line2->WriteLine(L"72", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 73:
            {
                m_slot8->line3->WriteLine(L"73", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 74:
            {
                m_slot8->line4->WriteLine(L"74", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 75:
            {
                m_slot8->line5->WriteLine(L"75", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 76:
            {
                m_slot8->line6->WriteLine(L"76", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 77:
            {
                m_slot8->line7->WriteLine(L"77", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 78:
            {
                m_slot8->line8->WriteLine(L"78", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 79:
            {
                m_slot8->line9->WriteLine(L"79", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 80:
            {
                m_slot8->line10->WriteLine(L"80", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 81:
            {
                m_slot9->line1->WriteLine(L"81", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 82:
            {
                m_slot9->line2->WriteLine(L"82", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 83:
            {
                m_slot9->line3->WriteLine(L"83", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 84:
            {
                m_slot9->line4->WriteLine(L"84", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 85:
            {
                m_slot9->line5->WriteLine(L"85", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 86:
            {
                m_slot9->line6->WriteLine(L"86", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 87:
            {
                m_slot9->line7->WriteLine(L"87", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 88:
            {
                m_slot9->line8->WriteLine(L"88", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 89:
            {
                m_slot9->line9->WriteLine(L"89", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 90:
            {
                m_slot9->line10->WriteLine(L"90", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 91:
            {
                m_slot10->line1->WriteLine(L"91", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 92:
            {
                m_slot10->line2->WriteLine(L"92", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 93:
            {
                m_slot10->line3->WriteLine(L"93", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 94:
            {
                m_slot10->line4->WriteLine(L"94", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 95:
            {
                m_slot10->line5->WriteLine(L"95", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 96:
            {
                m_slot10->line6->WriteLine(L"96", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 97:
            {
                m_slot10->line7->WriteLine(L"97", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 98:
            {
                m_slot10->line8->WriteLine(L"98", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 99:
            {
                m_slot10->line9->WriteLine(L"99", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 100:
            {
                m_slot10->line10->WriteLine(L"100", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
        }
    }
}

void CIFSTCustomNPC::UpdateGoldRank()
{
    for (std::vector<CIFSTCustomNPC::RankStruct>::iterator it = CIFSTCustomNPC::GoldRankList.begin(); it != CIFSTCustomNPC::GoldRankList.end(); ++it)
    {


        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 51:
            {
                m_slot6->line1->WriteLine(L"51", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 52:
            {
                m_slot6->line2->WriteLine(L"52", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 53:
            {
                m_slot6->line3->WriteLine(L"53", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 54:
            {
                m_slot6->line4->WriteLine(L"54", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 55:
            {
                m_slot6->line5->WriteLine(L"55", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 56:
            {
                m_slot6->line6->WriteLine(L"56", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 57:
            {
                m_slot6->line7->WriteLine(L"57", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 58:
            {
                m_slot6->line8->WriteLine(L"58", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 59:
            {
                m_slot6->line9->WriteLine(L"59", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 60:
            {
                m_slot6->line10->WriteLine(L"60", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 61:
            {
                m_slot7->line1->WriteLine(L"61", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 62:
            {
                m_slot7->line2->WriteLine(L"62", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 63:
            {
                m_slot7->line3->WriteLine(L"63", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 64:
            {
                m_slot7->line4->WriteLine(L"64", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 65:
            {
                m_slot7->line5->WriteLine(L"65", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 66:
            {
                m_slot7->line6->WriteLine(L"66", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 67:
            {
                m_slot7->line7->WriteLine(L"67", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 68:
            {
                m_slot7->line8->WriteLine(L"68", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 69:
            {
                m_slot7->line9->WriteLine(L"69", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 70:
            {
                m_slot7->line10->WriteLine(L"70", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 71:
            {
                m_slot8->line1->WriteLine(L"71", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 72:
            {
                m_slot8->line2->WriteLine(L"72", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 73:
            {
                m_slot8->line3->WriteLine(L"73", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 74:
            {
                m_slot8->line4->WriteLine(L"74", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 75:
            {
                m_slot8->line5->WriteLine(L"75", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 76:
            {
                m_slot8->line6->WriteLine(L"76", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 77:
            {
                m_slot8->line7->WriteLine(L"77", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 78:
            {
                m_slot8->line8->WriteLine(L"78", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 79:
            {
                m_slot8->line9->WriteLine(L"79", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 80:
            {
                m_slot8->line10->WriteLine(L"80", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 81:
            {
                m_slot9->line1->WriteLine(L"81", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 82:
            {
                m_slot9->line2->WriteLine(L"82", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 83:
            {
                m_slot9->line3->WriteLine(L"83", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 84:
            {
                m_slot9->line4->WriteLine(L"84", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 85:
            {
                m_slot9->line5->WriteLine(L"85", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 86:
            {
                m_slot9->line6->WriteLine(L"86", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 87:
            {
                m_slot9->line7->WriteLine(L"87", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 88:
            {
                m_slot9->line8->WriteLine(L"88", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 89:
            {
                m_slot9->line9->WriteLine(L"89", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 90:
            {
                m_slot9->line10->WriteLine(L"90", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 91:
            {
                m_slot10->line1->WriteLine(L"91", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 92:
            {
                m_slot10->line2->WriteLine(L"92", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 93:
            {
                m_slot10->line3->WriteLine(L"93", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 94:
            {
                m_slot10->line4->WriteLine(L"94", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 95:
            {
                m_slot10->line5->WriteLine(L"95", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 96:
            {
                m_slot10->line6->WriteLine(L"96", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 97:
            {
                m_slot10->line7->WriteLine(L"97", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 98:
            {
                m_slot10->line8->WriteLine(L"98", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 99:
            {
                m_slot10->line9->WriteLine(L"99", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
            case 100:
            {
                m_slot10->line10->WriteLine(L"100", TO_NSTRING((*it).ItemName), (*it).Count.c_str(), (*it).Price.c_str());
            }
                break;
        }
    }
}



bool CIFSTCustomNPC::IsPageFull(BYTE PageID, BYTE LineID)
{
    bool full = false;
    if (PageID == 1)
    {
        if (LineID == 30)
        {
            if (m_slot1->line1->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot1->line10->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 2)
    {
        if (LineID == 30)
        {
            if (m_slot2->line1->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot2->line10->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 3)
    {
        if (LineID == 30)
        {
            if (m_slot3->line1->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot3->line10->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 4)
    {
        if (LineID == 30)
        {
            if (m_slot4->line1->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot4->line10->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 5)
    {
        if (LineID == 30)
        {
            if (m_slot5->line1->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot5->line10->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 6)
    {
        if (LineID == 30)
        {
            if (m_slot6->line1->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot6->line10->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 7)
    {
        if (LineID == 30)
        {
            if (m_slot7->line1->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot7->line10->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 8)
    {
        if (LineID == 30)
        {
            if (m_slot8->line1->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot8->line10->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 9)
    {
        if (LineID == 30)
        {
            if (m_slot9->line1->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot9->line10->m_custom_label4->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 10)
    {
        if (LineID == 30)
        {
            if (m_slot10->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot10->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    return full;
}
void CIFSTCustomNPC::OnBuyItem()
{
    if (!SelectedItemName.empty())
    {
        BYTE v1 = 1;
        for (int i = 0; i < UniquesRankList.size(); ++i)
        {
            std::ostringstream ss;
            ss << UniquesRankList[i].LineNum;
            if (wcscmp(TO_WSTRING(ss.str()).c_str(), SelectedItemName.c_str()) == 0)
            {
                CMsgStreamBuffer buf(0x1318);

                buf << std::n_string(ss.str().c_str());
                buf << std::n_string("!MUAITEM");
                buf << std::n_string(TO_NSTRING(UniquesRankList[i].Price));
                SendMsg(buf);

                break;
            }
        }
    }
    else
    {
        g_pCGInterface->ShowMessage_Warning(L"please select item first");
        return;
    }
}
void CIFSTCustomNPC::OnTestItem()
{
    if (!SelectedItemName.empty())
    {
        BYTE v1 = 1;
        for (int i = 0; i < UniquesRankList.size(); ++i)
        {
            std::ostringstream ss;
            ss << UniquesRankList[i].LineNum;
            if (wcscmp(TO_WSTRING(ss.str()).c_str(), SelectedItemName.c_str()) == 0)
            {
                std::map<std::wstring, UINT32>::iterator foundedInfo =  m_CharacterIcons.find(g_pCICPlayer->GetName().c_str());
                if (foundedInfo != m_CharacterIcons.end())
                    m_CharacterIcons[g_pCICPlayer->GetName().c_str()]=UniquesRankList[i].LineNum;
                else
                m_CharacterIcons.insert(std::pair<std::wstring,UINT32>(g_pCICPlayer->GetName().c_str(),UniquesRankList[i].LineNum));

                break;
            }
        }
    }
    else
    {
        g_pCGInterface->ShowMessage_Warning(L"please select item first");
        return;
    }


}
void CIFSTCustomNPC::OnUpdate()
{

}
void CIFSTCustomNPC::ClearDDJ() {
    m_slot1->ClearDDJ();
    m_slot2->ClearDDJ();
    m_slot3->ClearDDJ();
    m_slot4->ClearDDJ();
    m_slot5->ClearDDJ();
    m_slot6->ClearDDJ();
    m_slot7->ClearDDJ();
    m_slot8->ClearDDJ();
    m_slot9->ClearDDJ();
    m_slot10->ClearDDJ();
}
void CIFSTCustomNPC::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}

void CIFSTCustomNPC::HideLists()
{
    m_slot1->ShowGWnd(false);
    m_slot2->ShowGWnd(false);
    m_slot3->ShowGWnd(false);
    m_slot4->ShowGWnd(false);
    m_slot5->ShowGWnd(false);
    m_slot6->ShowGWnd(false);
    m_slot7->ShowGWnd(false);
    m_slot8->ShowGWnd(false);
    m_slot9->ShowGWnd(false);
    m_slot10->ShowGWnd(false);
}