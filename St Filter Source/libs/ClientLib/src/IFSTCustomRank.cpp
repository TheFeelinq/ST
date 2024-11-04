#include "IFSTCustomRank.h"
#include "Game.h"

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
#define GDR_EU_BTN 28
#define GDR_ASIAN_BTN 8

GFX_IMPLEMENT_DYNCREATE(CIFCustomRank, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFCustomRank, CIFMainFrame)
                    ONG_COMMAND(100, &CIFCustomRank::OnUnknownStuff)
                    ONG_COMMAND(101, &CIFCustomRank::OnUnknownStuff)
                    ONG_COMMAND(102, &CIFCustomRank::OnUnknownStuff)
                    ONG_COMMAND(103, &CIFCustomRank::OnUnknownStuff)
                    ONG_COMMAND(104, &CIFCustomRank::OnUnknownStuff)
                    ONG_COMMAND(105, &CIFCustomRank::OnUnknownStuff)
                    ONG_COMMAND(GDR_Thief_BTN, &CIFCustomRank::OnThiefRank)
                    ONG_COMMAND(GDR_Hunter_BTN, &CIFCustomRank::OnHunterRank)
                    ONG_COMMAND(GDR_Trader_BTN, &CIFCustomRank::OnTraderRank)
                    ONG_COMMAND(GDR_EU_BTN, &CIFCustomRank::OnEURank)
                    ONG_COMMAND(GDR_ASIAN_BTN, &CIFCustomRank::OnAsianRank)
GFX_END_MESSAGE_MAP()

#define GDR_GXVSRO_FRAME 1
#define GDR_GXVSRO_TITLE 2
#define GDR_1_BTN 20
#define GDR_2_BTN 21
#define GDR_3_BTN 22
#define GDR_4_BTN 24
#define GDR_5_BTN 23
#define GDR_6_BTN 25


std::vector<CIFCustomRank::RankStruct> CIFCustomRank::GoldRankList;
std::vector<CIFCustomRank::RankStruct> CIFCustomRank::GuildRankList;
std::vector<CIFCustomRank::RankStruct> CIFCustomRank::JobTraderRank;
std::vector<CIFCustomRank::RankStruct> CIFCustomRank::JobHunterRank;
std::vector<CIFCustomRank::RankStruct> CIFCustomRank::JobThiefRank;
std::vector<CIFCustomRank::RankStruct> CIFCustomRank::UniquesRankList;
std::vector<CIFCustomRank::RankStruct> CIFCustomRank::CharRankList;
std::vector<CIFCustomRank::RankStruct> CIFCustomRank::JobRankList;
std::vector<CIFCustomRank::RankStruct> CIFCustomRank::CharLevelRankList;
std::vector<CIFCustomRank::RankStruct> CIFCustomRank::CharLevelEuRankList;
std::vector<CIFCustomRank::RankStruct> CIFCustomRank::CharLevelAsianRankList;
CIFCustomRank::CIFCustomRank(void)
{
    //  printf("> " __FUNCTION__ "\n");
}


CIFCustomRank::~CIFCustomRank(void)
{
    //  printf("> " __FUNCTION__ "\n");
}
int CIFCustomRank::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
bool CIFCustomRank::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT rect_m_tile = {116, 9, 186, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_TILE"));

    RECT Framerect = { 17,45,180,185 };
    RECT Lablerect = { 16,308,480,62 };
    RECT Buttrect = { 80,364,16,16 };
    RECT Butt2rect = { 60,364,16,16 };
    RECT Butt6rect = { 100,364,16,16 };
    RECT Butt7rect = { 60,364,16,16 };
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
    m_mybutton4 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt6rect, GDR_EU_BTN, 0);
    m_mybutton5 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt7rect, GDR_ASIAN_BTN, 0);

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
    m_mybutton4->TB_Func_13("interface\\ifcommon\\com_kindred_europe16.ddj", 0, 0);
    m_mybutton5->TB_Func_13("interface\\ifcommon\\com_kindred_china16.ddj", 0, 0);

    Frame->SetGWndSize(this->GetSize().width - 20, this->GetSize().height - 75);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 65);
    m_custom_label->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
    m_custom_label->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);

    Rank->SetText(L"#");
    Charname->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_CHARNAME"));
    Points->SetText(L"P/K");
    Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_GUILD"));

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
            case 2:
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
                break;
        }
    }

    m_title->SetText(L"Dynamic Rank");
    m_pTabs[0]->SetText(L"Boss");//--
    m_pTabs[1]->SetText(L"Guild");
    m_pTabs[2]->SetText(L"Job");//--
    m_pTabs[3]->SetText(L"Gold");//--
    m_pTabs[4]->SetText(L"Item");//--
    m_pTabs[5]->SetText(L"Level");

    RECT rect = { 0,0,0,0 };
    m_slot1 = (CIFCustomRankList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCustomRankList), rect, 40, 0);
    m_slot2 = (CIFCustomRankList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCustomRankList), rect, 41, 0);
    m_slot3 = (CIFCustomRankList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCustomRankList), rect, 42, 0);
    m_slot4 = (CIFCustomRankList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCustomRankList), rect, 43, 0);
    m_slot5 = (CIFCustomRankList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCustomRankList), rect, 44, 0);

    HideLists();
    m_slot1->ShowGWnd(true);
    m_slot1->MoveGWnd(m_slot1->GetPos().x + 7, m_slot1->GetPos().y + 24);
    m_slot2->MoveGWnd(m_slot2->GetPos().x + 7, m_slot2->GetPos().y + 24);
    m_slot3->MoveGWnd(m_slot3->GetPos().x + 7, m_slot3->GetPos().y + 24);
    m_slot4->MoveGWnd(m_slot4->GetPos().x + 7, m_slot4->GetPos().y + 24);
    m_slot5->MoveGWnd(m_slot5->GetPos().x + 7, m_slot5->GetPos().y + 24);

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

void CIFCustomRank::OnUnknownStuff() {
    int id = GetIDOfInterfaceUnderCursor();
    int i = 0;

    for (int i = 0; i < numberOfTabs; ++i) {
        if (id == m_pTabs[i]->UniqueID()) {
            ActivateTabPage(i);
            return;
        }
    }
}

void CIFCustomRank::ActivateTabPage(BYTE page) {

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
    if (page == 5)
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
            Points->SetText(L"Point/Kill");
            Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_GUILD"));
            Clear();
            UpdateUniqueRank();
            break;
        case 1:
            Points->SetText(L"Item Point");
            Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_GUILD"));
            Clear();
            UpdateGuildRank();
            break;
        case 2:
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
            Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_RACE"));
            Clear();
            UpdateLevelRank();
            break;
    }
}

void CIFCustomRank::Clear()
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

    m_slot1->line1->WriteLine(L"", L"", L"", L"");
    m_slot1->line2->WriteLine(L"", L"", L"", L"");
    m_slot1->line3->WriteLine(L"", L"", L"", L"");
    m_slot1->line4->WriteLine(L"", L"", L"", L"");
    m_slot1->line5->WriteLine(L"", L"", L"", L"");
    m_slot1->line6->WriteLine(L"", L"", L"", L"");
    m_slot1->line7->WriteLine(L"", L"", L"", L"");
    m_slot1->line8->WriteLine(L"", L"", L"", L"");
    m_slot1->line9->WriteLine(L"", L"", L"", L"");
    m_slot1->line10->WriteLine(L"", L"", L"", L"");
    m_slot1->line11->WriteLine(L"", L"", L"", L"");
    m_slot2->line1->WriteLine(L"", L"", L"", L"");
    m_slot2->line2->WriteLine(L"", L"", L"", L"");
    m_slot2->line3->WriteLine(L"", L"", L"", L"");
    m_slot2->line4->WriteLine(L"", L"", L"", L"");
    m_slot2->line5->WriteLine(L"", L"", L"", L"");
    m_slot2->line6->WriteLine(L"", L"", L"", L"");
    m_slot2->line7->WriteLine(L"", L"", L"", L"");
    m_slot2->line8->WriteLine(L"", L"", L"", L"");
    m_slot2->line9->WriteLine(L"", L"", L"", L"");
    m_slot2->line10->WriteLine(L"", L"", L"", L"");
    m_slot2->line11->WriteLine(L"", L"", L"", L"");
    m_slot3->line1->WriteLine(L"", L"", L"", L"");
    m_slot3->line2->WriteLine(L"", L"", L"", L"");
    m_slot3->line3->WriteLine(L"", L"", L"", L"");
    m_slot3->line4->WriteLine(L"", L"", L"", L"");
    m_slot3->line5->WriteLine(L"", L"", L"", L"");
    m_slot3->line6->WriteLine(L"", L"", L"", L"");
    m_slot3->line7->WriteLine(L"", L"", L"", L"");
    m_slot3->line8->WriteLine(L"", L"", L"", L"");
    m_slot3->line9->WriteLine(L"", L"", L"", L"");
    m_slot3->line10->WriteLine(L"", L"", L"", L"");
    m_slot3->line11->WriteLine(L"", L"", L"", L"");
    m_slot4->line1->WriteLine(L"", L"", L"", L"");
    m_slot4->line2->WriteLine(L"", L"", L"", L"");
    m_slot4->line3->WriteLine(L"", L"", L"", L"");
    m_slot4->line4->WriteLine(L"", L"", L"", L"");
    m_slot4->line5->WriteLine(L"", L"", L"", L"");
    m_slot4->line6->WriteLine(L"", L"", L"", L"");
    m_slot4->line7->WriteLine(L"", L"", L"", L"");
    m_slot4->line8->WriteLine(L"", L"", L"", L"");
    m_slot4->line9->WriteLine(L"", L"", L"", L"");
    m_slot4->line10->WriteLine(L"", L"", L"", L"");
    m_slot4->line11->WriteLine(L"", L"", L"", L"");
    m_slot5->line1->WriteLine(L"", L"", L"", L"");
    m_slot5->line2->WriteLine(L"", L"", L"", L"");
    m_slot5->line3->WriteLine(L"", L"", L"", L"");
    m_slot5->line4->WriteLine(L"", L"", L"", L"");
    m_slot5->line5->WriteLine(L"", L"", L"", L"");
    m_slot5->line6->WriteLine(L"", L"", L"", L"");
    m_slot5->line7->WriteLine(L"", L"", L"", L"");
    m_slot5->line8->WriteLine(L"", L"", L"", L"");
    m_slot5->line9->WriteLine(L"", L"", L"", L"");
    m_slot5->line10->WriteLine(L"", L"", L"", L"");
    m_slot5->line11->WriteLine(L"", L"", L"", L"");
}

void CIFCustomRank::ShowList(BYTE listid)
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
    }
}

void CIFCustomRank::WriteLineOwn(const wchar_t* Num,const wchar_t* Charname, const wchar_t* Guild, const wchar_t* Points)
{
    m_slot1->line11->WriteLine(Num, Charname, Guild, Points);
    m_slot1->line11->m_custom_label3->SetText(Charname);
    m_slot1->line11->m_custom_label4->SetText(Guild);
    m_slot1->line11->m_custom_label5->SetText(Points);

    m_slot1->line11->m_custom_label1->SetTextColor(0x5ad3a9);
    m_slot1->line11->m_custom_label3->SetTextColor(0x5ad3a9);
    m_slot1->line11->m_custom_label4->SetTextColor(0x5ad3a9);
    m_slot1->line11->m_custom_label5->SetTextColor(0x5ad3a9);
    //
    m_slot2->line11->WriteLine(Num, Charname, Guild, Points);

    m_slot2->line11->m_custom_label1->SetTextColor(0x5ad3a9);
    m_slot2->line11->m_custom_label3->SetTextColor(0x5ad3a9);
    m_slot2->line11->m_custom_label4->SetTextColor(0x5ad3a9);
    m_slot2->line11->m_custom_label5->SetTextColor(0x5ad3a9);
    //
    m_slot3->line11->WriteLine(Num, Charname, Guild, Points);

    m_slot3->line11->m_custom_label1->SetTextColor(0x5ad3a9);
    m_slot3->line11->m_custom_label3->SetTextColor(0x5ad3a9);
    m_slot3->line11->m_custom_label4->SetTextColor(0x5ad3a9);
    m_slot3->line11->m_custom_label5->SetTextColor(0x5ad3a9);
    //
    m_slot4->line11->WriteLine(Num, Charname, Guild, Points);

    m_slot4->line11->m_custom_label1->SetTextColor(0x5ad3a9);
    m_slot4->line11->m_custom_label3->SetTextColor(0x5ad3a9);
    m_slot4->line11->m_custom_label4->SetTextColor(0x5ad3a9);
    m_slot4->line11->m_custom_label5->SetTextColor(0x5ad3a9);
    //
    m_slot5->line11->WriteLine(Num, Charname, Guild, Points);
    m_slot5->line11->m_custom_label1->SetTextColor(0x5ad3a9);
    m_slot5->line11->m_custom_label3->SetTextColor(0x5ad3a9);
    m_slot5->line11->m_custom_label4->SetTextColor(0x5ad3a9);
    m_slot5->line11->m_custom_label5->SetTextColor(0x5ad3a9);
}

void CIFCustomRank::UpdateUniqueRank()
{
    for (std::vector<CIFCustomRank::RankStruct>::iterator it = CIFCustomRank::UniquesRankList.begin(); it != CIFCustomRank::UniquesRankList.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());




            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}

void CIFCustomRank::UpdateGoldRank()
{
    for (std::vector<CIFCustomRank::RankStruct>::iterator it = CIFCustomRank::GoldRankList.begin(); it != CIFCustomRank::GoldRankList.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }

        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}

void CIFCustomRank::UpdateGuildRank()
{
    for (std::vector<CIFCustomRank::RankStruct>::iterator it = CIFCustomRank::GuildRankList.begin(); it != CIFCustomRank::GuildRankList.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;

            m_slot1->line11->m_custom_label2->ShowGWnd(true);
            m_slot2->line11->m_custom_label2->ShowGWnd(true);
            m_slot3->line11->m_custom_label2->ShowGWnd(true);
            m_slot4->line11->m_custom_label2->ShowGWnd(true);
            m_slot5->line11->m_custom_label2->ShowGWnd(true);

            switch ((*it).LineNum)
            {
                case 1:
                {
                    m_slot1->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank1.ddj", 0, 0);
                    m_slot2->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank1.ddj", 0, 0);
                    m_slot3->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank1.ddj", 0, 0);
                    m_slot4->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank1.ddj", 0, 0);
                    m_slot5->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank1.ddj", 0, 0);
                }
                    break;
                case 2:
                {
                    m_slot1->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank2.ddj", 0, 0);
                    m_slot2->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank2.ddj", 0, 0);
                    m_slot3->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank2.ddj", 0, 0);
                    m_slot4->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank2.ddj", 0, 0);
                    m_slot5->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank2.ddj", 0, 0);
                }
                    break;
                case 3:
                {
                    m_slot1->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank3.ddj", 0, 0);
                    m_slot2->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank3.ddj", 0, 0);
                    m_slot3->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank3.ddj", 0, 0);
                    m_slot4->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank3.ddj", 0, 0);
                    m_slot5->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank3.ddj", 0, 0);
                }
                    break;
                case 4:
                {
                    m_slot1->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank4.ddj", 0, 0);
                    m_slot2->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank4.ddj", 0, 0);
                    m_slot3->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank4.ddj", 0, 0);
                    m_slot4->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank4.ddj", 0, 0);
                    m_slot5->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank4.ddj", 0, 0);
                }
                    break;
                case 5:
                {
                    m_slot1->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank5.ddj", 0, 0);
                    m_slot2->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank5.ddj", 0, 0);
                    m_slot3->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank5.ddj", 0, 0);
                    m_slot4->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank5.ddj", 0, 0);
                    m_slot5->line11->m_custom_label2->TB_Func_13("interface\\ifcommon\\gxvsro\\honorpoints_rank5.ddj", 0, 0);
                }
                    break;
                default:
                    m_slot1->line11->m_custom_label2->ShowGWnd(false);
                    m_slot2->line11->m_custom_label2->ShowGWnd(false);
                    m_slot3->line11->m_custom_label2->ShowGWnd(false);
                    m_slot4->line11->m_custom_label2->ShowGWnd(false);
                    m_slot5->line11->m_custom_label2->ShowGWnd(false);
                    break;
            }
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
                m_slot1->line1->m_custom_label2->ShowGWnd(true);
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
                m_slot1->line2->m_custom_label2->ShowGWnd(true);
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
                m_slot1->line3->m_custom_label2->ShowGWnd(true);
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
                m_slot1->line4->m_custom_label2->ShowGWnd(true);
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
                m_slot1->line5->m_custom_label2->ShowGWnd(true);
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}

void CIFCustomRank::UpdateCharRank()
{
    for (std::vector<CIFCustomRank::RankStruct>::iterator it = CIFCustomRank::CharRankList.begin(); it != CIFCustomRank::CharRankList.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());




            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}
void CIFCustomRank::UpdateLevelRank()
{
    for (std::vector<CIFCustomRank::RankStruct>::iterator it = CIFCustomRank::CharLevelRankList.begin(); it != CIFCustomRank::CharLevelRankList.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());




            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}
void CIFCustomRank::UpdateLevelEURank()
{
    for (std::vector<CIFCustomRank::RankStruct>::iterator it = CIFCustomRank::CharLevelEuRankList.begin(); it != CIFCustomRank::CharLevelEuRankList.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());




            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}
void CIFCustomRank::UpdateLevelAsianRank()
{
    for (std::vector<CIFCustomRank::RankStruct>::iterator it = CIFCustomRank::CharLevelAsianRankList.begin(); it != CIFCustomRank::CharLevelAsianRankList.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());




            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}
void CIFCustomRank::UpdateJobKillsRank()
{
    for (std::vector<CIFCustomRank::RankStruct>::iterator it = CIFCustomRank::JobRankList.begin(); it != CIFCustomRank::JobRankList.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());




            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}

void CIFCustomRank::UpdateTraderRank()
{
    for (std::vector<CIFCustomRank::RankStruct>::iterator it = CIFCustomRank::JobTraderRank.begin(); it != CIFCustomRank::JobTraderRank.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());




            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}

void CIFCustomRank::UpdateHunterRank()
{
    for (std::vector<CIFCustomRank::RankStruct>::iterator it = CIFCustomRank::JobHunterRank.begin(); it != CIFCustomRank::JobHunterRank.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());




            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}

void CIFCustomRank::UpdateThiefRank()
{
    for (std::vector<CIFCustomRank::RankStruct>::iterator it = CIFCustomRank::JobThiefRank.begin(); it != CIFCustomRank::JobThiefRank.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());




            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}

bool CIFCustomRank::IsPageFull(BYTE PageID, BYTE LineID)
{
    bool full = false;
    if (PageID == 1)
    {
        if (LineID == 30)
        {
            if (m_slot1->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot1->line10->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 2)
    {
        if (LineID == 30)
        {
            if (m_slot2->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot2->line10->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 3)
    {
        if (LineID == 30)
        {
            if (m_slot3->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot3->line10->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 4)
    {
        if (LineID == 30)
        {
            if (m_slot4->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot4->line10->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 5)
    {
        if (LineID == 30)
        {
            if (m_slot5->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot5->line10->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    return full;
}

void CIFCustomRank::OnUpdate()
{

}

void CIFCustomRank::OnThiefRank()
{
    Points->SetText(L"Kill/Dead");
    Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_GUILD"));
    Clear();
    UpdateThiefRank();
}

void CIFCustomRank::OnHunterRank()
{
    Points->SetText(L"Kill/Dead");
    Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_GUILD"));
    Clear();
    UpdateHunterRank();
}
void CIFCustomRank::OnTraderRank()
{
    Points->SetText(L"Kill/Dead");
    Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_GUILD"));
    Clear();
    UpdateTraderRank();
}
void CIFCustomRank::OnEURank()
{
    Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_RACE"));
    Clear();
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!OnEURank");
    buf << std::n_string("!OnEURank");
    SendMsg(buf);
    UpdateLevelEURank();

}
void CIFCustomRank::OnAsianRank()
{
    Guild->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_RACE"));
    printf("CharLevelAsianRankList.................\n");
    Clear();
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!OnAsianRank");
    buf << std::n_string("!OnAsianRank");
    SendMsg(buf);

    UpdateLevelAsianRank();

}
void CIFCustomRank::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}

void CIFCustomRank::HideLists()
{
    m_slot1->ShowGWnd(false);
    m_slot2->ShowGWnd(false);
    m_slot3->ShowGWnd(false);
    m_slot4->ShowGWnd(false);
    m_slot5->ShowGWnd(false);
}