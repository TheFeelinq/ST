#include "IFSTTotalPoints.h"
#include "IFNormalTile.h"
#include "ICPlayer.h"
#include "Game.h"
#include <ctime>
#include <unsorted.h>

#include <sstream>
#include <BSLib/multibyte.h>
#define GDR_FLORIAN0_RT_LABEL 10
#define GDR_FLORIAN0_RT_BTN 11
#define GDR_FLORIAN0_RT_LABEL_TIME 13
#define GDR_FLORIAN0_RT_MAIN_FRAME 20

GFX_IMPLEMENT_DYNCREATE(CIFSTTotalPoints, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTTotalPoints, CIFMainFrame)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN, &On_BtnClick)
GFX_END_MESSAGE_MAP()

std::vector<CIFSTTotalPoints::TotalPoint> CIFSTTotalPoints::TotalPointList;

CIFSTTotalPoints::CIFSTTotalPoints() :
        m_custom_label(NULL) {

}

bool CIFSTTotalPoints::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);

    // Set own title
    RECT rect_m_tile = {172, 9, 186, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIT_ST_TOTAL_POINT"));

    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);

    wnd_size sz = this->GetSize();

    RECT rect_frame = {10, 40, 491, 280};

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame,
                                                  GDR_FLORIAN0_RT_MAIN_FRAME,
                                                  1);
    frame->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 0);

    RECT rect_background = {rect_frame.left + 10,
                            rect_frame.top + 10,
                            rect_frame.right - 20,
                            rect_frame.bottom - 20};

    CIFNormalTile *tile = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background,
                                                           GDR_FLORIAN0_RT_MAIN_FRAME,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);


    RECT rect_frame2 = {178, 55, 310, 225};

    CIFFrame *frame2 = (CIFFrame *) CreateInstance(this,
                                                   GFX_RUNTIME_CLASS(CIFFrame),
                                                   rect_frame2,
                                                   GDR_FLORIAN0_RT_MAIN_FRAME,
                                                   1);
    frame2->TB_Func_13("interface\\frame\\sframe_wnd_", 1, 0);

    RECT rect_background2 = {182,83,301,192};

    CIFNormalTile *tile2 = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background2,
                                                           GDR_FLORIAN0_RT_MAIN_FRAME,
                                                           1);
    tile2->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);

    RECT rect_frame3 = {178, 280, 310, 24};

    CIFFrame *frame3 = (CIFFrame *) CreateInstance(this,
                                                   GFX_RUNTIME_CLASS(CIFFrame),
                                                   rect_frame3,
                                                   GDR_FLORIAN0_RT_MAIN_FRAME,
                                                   1);
    frame3->TB_Func_13("interface\\frame\\frame_sub_", 1, 0);

    RECT rect_frame4 = {58, 66, 80, 80};

    CIFFrame *frame4 = (CIFFrame *) CreateInstance(this,
                                                   GFX_RUNTIME_CLASS(CIFFrame),
                                                   rect_frame4,
                                                   GDR_FLORIAN0_RT_MAIN_FRAME,
                                                   1);
    frame4->TB_Func_13("interface\\frame\\frame_make_", 1, 0);



    RECT rect_frame1 = {25, 55, 148, 249};

    CIFFrame *frame1 = (CIFFrame *) CreateInstance(this,
                                                   GFX_RUNTIME_CLASS(CIFFrame),
                                                   rect_frame1,
                                                   GDR_FLORIAN0_RT_MAIN_FRAME,
                                                   1);
    frame1->TB_Func_13("interface\\frame\\game_window_", 1, 0);







    RECT rect_button = {50, 165, 18, 18};
    CIFButton *btn = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button,
                                                         GDR_FLORIAN0_RT_BTN,
                                                         1);

    btn->TB_Func_13("interface\\ifcommon\\ngt\\ngtpoints_jobkills.ddj", 1, 1);

    RECT rect_custom_label = {75, 165, 18, 18};
    m_custom_label = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_custom_label,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);


    RECT rect_button2 = {50, 191, 18, 18};
    CIFButton *btn2 = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button2,
                                                         GDR_FLORIAN0_RT_BTN,
                                                         1);

    btn2->TB_Func_13("interface\\ifcommon\\ngt\\ngthonorpoints_survivalkills.ddj", 1, 1);

    RECT rect_custom_label2 = {75, 191, 18, 18};
    m_custom_label2 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_custom_label2,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);


    RECT rect_button3 = {50, 216, 18, 18};
    CIFButton *btn3 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button3,
                                                          GDR_FLORIAN0_RT_BTN,
                                                          1);

    btn3->TB_Func_13("interface\\ifcommon\\ngt\\ngthonorpoints_fortresswar.ddj", 1, 1);

    RECT rect_custom_label3 = {75, 216, 18, 18};
    m_custom_label3 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFStatic),
                                                          rect_custom_label3,
                                                          GDR_FLORIAN0_RT_LABEL,
                                                          1);


    RECT rect_button4 = {50, 243, 18, 18};
    CIFButton *btn4 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button4,
                                                          GDR_FLORIAN0_RT_BTN,
                                                          1);

    btn4->TB_Func_13("interface\\ifcommon\\ngt\\ngthonorpoints_uniques.ddj", 1, 1);

    RECT rect_custom_label4 = {75, 243, 18, 18};
    m_custom_label4 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFStatic),
                                                          rect_custom_label4,
                                                          GDR_FLORIAN0_RT_LABEL,
                                                          1);


    ///
    RECT rect_button5 = {115, 165, 18, 18};
    CIFButton *btn5 = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button5,
                                                         GDR_FLORIAN0_RT_BTN,
                                                         1);

    btn5->TB_Func_13("interface\\ifcommon\\ngt\\ngthonorpoints_jobbing.ddj", 1, 1);

    RECT rect_custom_label5 = {138, 165, 18, 18};
    m_custom_label5 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFStatic),
                                                          rect_custom_label5,
                                                          GDR_FLORIAN0_RT_LABEL,
                                                          1);

    RECT rect_button6 = {115, 191, 18, 18};
    CIFButton *btn6 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button6,
                                                          GDR_FLORIAN0_RT_BTN,
                                                          1);
    btn6->TB_Func_13("interface\\ifcommon\\ngt\\ngthonorpoints_itempoint.ddj", 1, 1);

    RECT rect_custom_label6 = {138, 191, 18, 18};
    m_custom_label6 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFStatic),
                                                          rect_custom_label6,
                                                          GDR_FLORIAN0_RT_LABEL,
                                                          1);

    RECT rect_button7 = {115, 216, 18, 18};
    CIFButton *btn7 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button7,
                                                          GDR_FLORIAN0_RT_BTN,
                                                          1);

    btn7->TB_Func_13("interface\\ifcommon\\ngt\\ngtpoints_alchemy.ddj", 1, 1);

    RECT rect_custom_label7 = {138, 216, 18, 18};
    m_custom_label7 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFStatic),
                                                          rect_custom_label7,
                                                          GDR_FLORIAN0_RT_LABEL,
                                                          1);

    RECT rect_button8 = {115, 243, 18, 18};
    CIFButton *btn8 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button8,
                                                          GDR_FLORIAN0_RT_BTN,
                                                          1);

    btn8->TB_Func_13("interface\\ifcommon\\ngt\\ngtpvpchallengeanswer_silk_icon.ddj", 1, 1);

    RECT rect_custom_label8 = {138, 243, 18, 18};
    m_custom_label8 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFStatic),
                                                          rect_custom_label8,
                                                          GDR_FLORIAN0_RT_LABEL,
                                                          1);

    RECT rect_button9 = {73, 275, 18, 18};
    CIFButton *btn9 = (CIFButton *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFButton),
                                                          rect_button9,
                                                          GDR_FLORIAN0_RT_BTN,
                                                          1);

    btn9->TB_Func_13("interface\\ifcommon\\ngt\\ngthonorpoints_honorpoints.ddj", 1, 1);

    RECT rect_custom_label9 = {96, 275, 18, 18};
    m_custom_label9 = (CIFStatic *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFStatic),
                                                          rect_custom_label9,
                                                          GDR_FLORIAN0_RT_LABEL,
                                                          1);

    RECT rect_custom_label10 = {229, 282, 223, 15};
    m_custom_label_tooltip = (CIFStatic *) CGWnd::CreateInstance(this,
                                                          GFX_RUNTIME_CLASS(CIFStatic),
                                                          rect_custom_label10,
                                                          GDR_FLORIAN0_RT_LABEL,
                                                          1);
    RECT rect_label_time =  {rect_frame4.left + 3,
                             rect_frame4.top + 3,
                             rect_frame4.right - 6,
                             rect_frame4.bottom - 6};
    m_char_icon = (CIFStatic *) CGWnd::CreateInstance(this,
                                                     GFX_RUNTIME_CLASS(CIFStatic),
                                                     rect_label_time,
                                                     GDR_FLORIAN0_RT_LABEL_TIME,
                                                     1);
    RECT rect_custom_label11 = {193, 60, 40, 13};
    m_custom_label_stt = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                 GFX_RUNTIME_CLASS(CIFStatic),
                                                                 rect_custom_label11,
                                                                 GDR_FLORIAN0_RT_LABEL,
                                                                 1);
    RECT rect_custom_label12 = {271, 60, 54, 13};
    m_custom_label_name = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                 GFX_RUNTIME_CLASS(CIFStatic),
                                                                 rect_custom_label12,
                                                                 GDR_FLORIAN0_RT_LABEL,
                                                                 1);
    RECT rect_custom_label13 = {407, 60, 36, 13};
    m_custom_label_point= (CIFStatic *) CGWnd::CreateInstance(this,
                                                                 GFX_RUNTIME_CLASS(CIFStatic),
                                                                 rect_custom_label13,
                                                                 GDR_FLORIAN0_RT_LABEL,
                                                                 1);

    std::n_wstring str3 = TSM_GETTEXTPTR("UIIT_ST_TOTAL_POINT_HONORPOINTS_ICON");
    btn9->sub_653DC0(&str3);
    btn9->sub_652D20(128);
    std::n_wstring str4 = TSM_GETTEXTPTR("UIIT_ST_TOTAL_POINT_SURVIVALKILLS_ICON");
    btn2->sub_653DC0(&str4);
    btn2->sub_652D20(128);

    std::n_wstring str5 = TSM_GETTEXTPTR("UIIT_ST_TOTAL_POINT_SURVIVALWINS_ICON");
    btn5->sub_653DC0(&str5);
    btn5->sub_652D20(128);

    std::n_wstring str6 = TSM_GETTEXTPTR("UIIT_ST_TOTAL_POINT_FORTRESSWAR_ICON");
    btn3->sub_653DC0(&str6);
    btn3->sub_652D20(128);

    std::n_wstring str9 = TSM_GETTEXTPTR("UIIT_ST_TOTAL_POINT_UNIQUES_ICON");
    btn4->sub_653DC0(&str9);
    btn4->sub_652D20(128);

    std::n_wstring str111 = TSM_GETTEXTPTR("UIIT_ST_TOTAL_POINT_ITEMPOINTALL");
    btn6->sub_653DC0(&str111);
    btn6->sub_652D20(128);

    std::n_wstring str10 = TSM_GETTEXTPTR("UIIT_ST_TOTAL_POINT_DONATE");
    btn8->sub_653DC0(&str10);
    btn8->sub_652D20(128);

    std::n_wstring str12 = TSM_GETTEXTPTR("UIIT_ST_TOTAL_POINT_ALCHEMY_LABEL");
    btn7->sub_653DC0(&str12);
    btn7->sub_652D20(128);


    std::n_wstring str15 = TSM_GETTEXTPTR("UIIT_ST_TOTAL_POINT_JOBKILLS_ICON");
    btn->sub_653DC0(&str15);
    btn->sub_652D20(128);
    ///////
    RECT Spinect = { 314,257,50,16 };
    m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), Spinect, 4, 0);


    RECT rect = { 0,0,0,0 };
    m_slot1 = (CIFSTTotalPointSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlotList), rect, 40, 0);
    m_slot2 = (CIFSTTotalPointSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlotList), rect, 41, 0);
    m_slot3 = (CIFSTTotalPointSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlotList), rect, 42, 0);
    m_slot4 = (CIFSTTotalPointSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlotList), rect, 43, 0);
    m_slot5 = (CIFSTTotalPointSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlotList), rect, 44, 0);
    m_slot6 = (CIFSTTotalPointSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlotList), rect, 45, 0);
    m_slot7 = (CIFSTTotalPointSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlotList), rect, 46, 0);



    m_slot1->MoveGWnd(m_slot1->GetPos().x + 2, m_slot1->GetPos().y + 2);
    m_slot2->MoveGWnd(m_slot2->GetPos().x + 2, m_slot2->GetPos().y + 2);
    m_slot3->MoveGWnd(m_slot3->GetPos().x + 2, m_slot3->GetPos().y + 2);
    m_slot4->MoveGWnd(m_slot4->GetPos().x + 2, m_slot4->GetPos().y + 2);
    m_slot5->MoveGWnd(m_slot5->GetPos().x + 2, m_slot5->GetPos().y + 2);
    m_slot6->MoveGWnd(m_slot6->GetPos().x + 2, m_slot6->GetPos().y + 2);
    m_slot7->MoveGWnd(m_slot7->GetPos().x + 2, m_slot7->GetPos().y + 2);
    m_custom_label_tooltip->SetText(L"Auto Update Every 5 Min");
    m_custom_label_stt->SetText(L"Rank");
    m_custom_label_name->SetText(TSM_GETTEXTPTR("UIIT_ST_CUSTOMRANK_CHARNAME"));
    m_custom_label_point->SetText(L"Point");
    m_custom_label_tooltip->m_FontTexture.SetColor(0xFFF18706);
    m_slot1->ShowGWnd(true);
    m_spin->SetMinValue(1);
    m_spin->SetCurrentValue(1);
    m_spin->SetMaxValue(6);
    m_spin->ShowGWnd(true);
    this->ShowGWnd(false);
    return true;
}


void CIFSTTotalPoints::On_BtnClick() {
    static int i = 0;

}

void CIFSTTotalPoints::OnUpdate() {
    time_t rawtime;
    struct tm *timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);

}
int CIFSTTotalPoints::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
void CIFSTTotalPoints::HideLists()
{
    m_slot1->ShowGWnd(false);
    m_slot2->ShowGWnd(false);
    m_slot3->ShowGWnd(false);
    m_slot4->ShowGWnd(false);
    m_slot5->ShowGWnd(false);
    m_slot6->ShowGWnd(false);
    m_slot7->ShowGWnd(false);

}
void CIFSTTotalPoints::ClearDDJ() {
    m_slot1->ClearDDJ();
    m_slot2->ClearDDJ();
    m_slot3->ClearDDJ();
    m_slot4->ClearDDJ();
    m_slot5->ClearDDJ();
    m_slot6->ClearDDJ();
    m_slot7->ClearDDJ();

}
void CIFSTTotalPoints::ShowList(BYTE listid)
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

    }
}

bool CIFSTTotalPoints::IsPageFull(BYTE PageID, BYTE LineID)
{
    bool full = false;
    if (PageID == 1)
    {
        if (LineID == 30)
        {
            if (m_slot1->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot1->line7->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 2)
    {
        if (LineID == 30)
        {
            if (m_slot2->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot2->line7->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 3)
    {
        if (LineID == 30)
        {
            if (m_slot3->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot3->line7->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 4)
    {
        if (LineID == 30)
        {
            if (m_slot4->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot4->line7->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 5)
    {
        if (LineID == 30)
        {
            if (m_slot5->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot5->line7->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 6)
    {
        if (LineID == 30)
        {
            if (m_slot6->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot6->line7->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 7)
    {
        if (LineID == 30)
        {
            if (m_slot7->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot7->line7->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }


    return full;
}


void CIFSTTotalPoints::UpdateTotalPointList()
{
    for (std::vector<CIFSTTotalPoints::TotalPoint>::iterator it = CIFSTTotalPoints::TotalPointList.begin(); it != CIFSTTotalPoints::TotalPointList.end(); ++it)
    {
       
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str());
                m_slot1->line1->m_custom_label2->ShowGWnd(true);
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str());
                m_slot1->line2->m_custom_label2->ShowGWnd(true);
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str());
                m_slot1->line3->m_custom_label2->ShowGWnd(true);
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str());
                m_slot1->line4->m_custom_label2->ShowGWnd(true);
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str());
                m_slot1->line5->m_custom_label2->ShowGWnd(true);
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 8:
            {
                m_slot2->line1->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 9:
            {
                m_slot2->line2->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 10:
            {
                m_slot2->line3->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line4->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line5->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line6->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line7->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 15:
            {
                m_slot3->line1->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 16:
            {
                m_slot3->line2->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 17:
            {
                m_slot3->line3->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 18:
            {
                m_slot3->line4->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 19:
            {
                m_slot3->line5->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 20:
            {
                m_slot3->line6->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line7->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 22:
            {
                m_slot4->line1->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 23:
            {
                m_slot4->line2->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 24:
            {
                m_slot4->line3->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 25:
            {
                m_slot4->line4->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 26:
            {
                m_slot4->line5->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 27:
            {
                m_slot4->line6->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 28:
            {
                m_slot4->line7->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 29:
            {
                m_slot5->line1->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 30:
            {
                m_slot5->line2->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 31:
            {
                m_slot5->line3->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 32:
            {
                m_slot5->line4->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 33:
            {
                m_slot5->line5->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 34:
            {
                m_slot5->line6->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 35:
            {
                m_slot6->line7->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 36:
            {
                m_slot6->line1->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 37:
            {
                m_slot6->line2->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 38:
            {
                m_slot6->line3->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 39:
            {
                m_slot6->line4->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 40:
            {
                m_slot6->line5->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 41:
            {
                m_slot6->line6->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
            case 42:
            {
                m_slot6->line7->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str());
            }
                break;
           

        }
    }
}

void CIFSTTotalPoints::Clear()
{
    m_slot1->line1->WriteLine(L"", L"", L"");
    m_slot1->line2->WriteLine(L"", L"", L"");
    m_slot1->line3->WriteLine(L"", L"", L"");
    m_slot1->line4->WriteLine(L"", L"", L"");
    m_slot1->line5->WriteLine(L"", L"", L"");
    m_slot1->line6->WriteLine(L"", L"", L"");
    m_slot1->line7->WriteLine(L"", L"", L"");


    m_slot2->line1->WriteLine(L"", L"", L"");
    m_slot2->line2->WriteLine(L"", L"", L"");
    m_slot2->line3->WriteLine(L"", L"", L"");
    m_slot2->line4->WriteLine(L"", L"", L"");
    m_slot2->line5->WriteLine(L"", L"", L"");
    m_slot2->line6->WriteLine(L"", L"", L"");
    m_slot2->line7->WriteLine(L"", L"", L"");


    m_slot3->line1->WriteLine(L"", L"", L"");
    m_slot3->line2->WriteLine(L"", L"", L"");
    m_slot3->line3->WriteLine(L"", L"", L"");
    m_slot3->line4->WriteLine(L"", L"", L"");
    m_slot3->line5->WriteLine(L"", L"", L"");
    m_slot3->line6->WriteLine(L"", L"", L"");
    m_slot3->line7->WriteLine(L"", L"", L"");


    m_slot4->line1->WriteLine(L"", L"", L"");
    m_slot4->line2->WriteLine(L"", L"", L"");
    m_slot4->line3->WriteLine(L"", L"", L"");
    m_slot4->line4->WriteLine(L"", L"", L"");
    m_slot4->line5->WriteLine(L"", L"", L"");
    m_slot4->line6->WriteLine(L"", L"", L"");
    m_slot4->line7->WriteLine(L"", L"", L"");


    m_slot5->line1->WriteLine(L"", L"", L"");
    m_slot5->line2->WriteLine(L"", L"", L"");
    m_slot5->line3->WriteLine(L"", L"", L"");
    m_slot5->line4->WriteLine(L"", L"", L"");
    m_slot5->line5->WriteLine(L"", L"", L"");
    m_slot5->line6->WriteLine(L"", L"", L"");
    m_slot5->line7->WriteLine(L"", L"", L"");


    m_slot6->line1->WriteLine(L"", L"", L"");
    m_slot6->line2->WriteLine(L"", L"", L"");
    m_slot6->line3->WriteLine(L"", L"", L"");
    m_slot6->line4->WriteLine(L"", L"", L"");
    m_slot6->line5->WriteLine(L"", L"", L"");
    m_slot6->line6->WriteLine(L"", L"", L"");
    m_slot6->line7->WriteLine(L"", L"", L"");


    m_slot7->line1->WriteLine(L"", L"", L"");
    m_slot7->line2->WriteLine(L"", L"", L"");
    m_slot7->line3->WriteLine(L"", L"", L"");
    m_slot7->line4->WriteLine(L"", L"", L"");
    m_slot7->line5->WriteLine(L"", L"", L"");
    m_slot7->line6->WriteLine(L"", L"", L"");
    m_slot7->line7->WriteLine(L"", L"", L"");


  
}
void CIFSTTotalPoints::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}