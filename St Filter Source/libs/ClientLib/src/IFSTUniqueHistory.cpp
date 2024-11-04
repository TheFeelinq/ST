#include "IFSTUniqueHistory.h"
#include "IFNormalTile.h"
#include "Game.h"
#include <ctime>

#define GDR_UNIQUE_HISTORY_RT_LABEL 10
#define GDR_UNIQUE_HISTORY_RT_BTN 11
#define GDR_UNIQUE_HISTORY_RT_LABEL_TIME 13
#define GDR_UNIQUE_HISTORY_RT_MAIN_FRAME 20
#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)
#define CLIENT_SCREEN_HEIGHT (*(int*)0x00ED7CBC)
GFX_IMPLEMENT_DYNCREATE(CIFSTUniqueHistory, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTUniqueHistory, CIFMainFrame)
                    ONG_COMMAND(GDR_UNIQUE_HISTORY_RT_BTN, &On_BtnClick)
GFX_END_MESSAGE_MAP()

std::vector<CIFSTUniqueHistory::UniqueHistory> CIFSTUniqueHistory::UniqueHistoryList;
CIFSTUniqueHistory::CIFSTUniqueHistory() :
        m_custom_label(NULL) {

}

bool CIFSTUniqueHistory::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);

    // Set own title
    RECT rect_m_tile = {173, 9, 100, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIT_ST_UNIQUE_LABLE"));

    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);


    RECT rect_frame = {12, 40, 478,318};

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame,
                                                  GDR_UNIQUE_HISTORY_RT_MAIN_FRAME,
                                                  1);
    frame->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 0);

    RECT rect_background = {rect_frame.left + 10,
                            rect_frame.top + 10,
                            rect_frame.right - 20,
                            rect_frame.bottom - 20};

    CIFNormalTile *tile = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background,
                                                           GDR_UNIQUE_HISTORY_RT_MAIN_FRAME,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);

    /////////////////
    RECT Butt1rect = { 25,56,163,24 };
    RECT Butt2rect = { 183,56,76,24 };
    RECT Butt3rect = { 257,56,123,24 };
    RECT Butt4rect = { 376,56,102,24 };
    RECT Spinect = { 226,320,50,16 };

    UniqueName = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt1rect, GDR_UNIQUE_HISTORY_RT_MAIN_FRAME, 0);
    AliveState = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt2rect, GDR_UNIQUE_HISTORY_RT_MAIN_FRAME, 0);
    KilledBy = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt3rect, GDR_UNIQUE_HISTORY_RT_MAIN_FRAME, 0);
    SpwanTime = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt4rect, GDR_UNIQUE_HISTORY_RT_MAIN_FRAME, 0);
    m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), Spinect, 4, 0);
    wchar_t buffer[80];
    wchar_t buffer1[80];
    wchar_t buffer2[80];
    wchar_t buffer3[80];
    swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_ST_UNIQUE_NAME"));
    swprintf_s(buffer1, TSM_GETTEXTPTR("UIIT_ST_UNIQUE_STATUS"));
    swprintf_s(buffer2, TSM_GETTEXTPTR("UIIT_ST_UNIQUE_KILLER"));
    swprintf_s(buffer3, TSM_GETTEXTPTR("UIIT_ST_UNIQUE_DATE"));
    UniqueName->SetText(buffer);
    AliveState->SetText(buffer1);
    KilledBy->SetText(buffer2);
    SpwanTime->SetText(buffer3);

    RECT rect = { 0,0,0,0 };
    m_slot1 = (CIFSTUniqueHistorySlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlotList), rect, 40, 0);
    m_slot2 = (CIFSTUniqueHistorySlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlotList), rect, 41, 0);
    m_slot3 = (CIFSTUniqueHistorySlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlotList), rect, 42, 0);
    m_slot4 = (CIFSTUniqueHistorySlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlotList), rect, 43, 0);
    m_slot5 = (CIFSTUniqueHistorySlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlotList), rect, 44, 0);
    m_slot6 = (CIFSTUniqueHistorySlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlotList), rect, 45, 0);
    m_slot7 = (CIFSTUniqueHistorySlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlotList), rect, 46, 0);
    m_slot8 = (CIFSTUniqueHistorySlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlotList), rect, 47, 0);
    m_slot9 = (CIFSTUniqueHistorySlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlotList), rect, 48, 0);
    m_slot10 = (CIFSTUniqueHistorySlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlotList), rect, 49, 0);


    m_slot1->MoveGWnd(m_slot1->GetPos().x + 7, m_slot1->GetPos().y + 5);
    m_slot2->MoveGWnd(m_slot2->GetPos().x + 7, m_slot2->GetPos().y + 5);
    m_slot3->MoveGWnd(m_slot3->GetPos().x + 7, m_slot3->GetPos().y + 5);
    m_slot4->MoveGWnd(m_slot4->GetPos().x + 7, m_slot4->GetPos().y + 5);
    m_slot5->MoveGWnd(m_slot5->GetPos().x + 7, m_slot5->GetPos().y + 5);
    m_slot6->MoveGWnd(m_slot6->GetPos().x + 7, m_slot6->GetPos().y + 5);
    m_slot7->MoveGWnd(m_slot7->GetPos().x + 7, m_slot7->GetPos().y + 5);
    m_slot8->MoveGWnd(m_slot8->GetPos().x + 7, m_slot8->GetPos().y + 5);
    m_slot9->MoveGWnd(m_slot9->GetPos().x + 7, m_slot9->GetPos().y + 5);
    m_slot10->MoveGWnd(m_slot10->GetPos().x + 7, m_slot10->GetPos().y + 5);

    SpwanTime->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    UniqueName->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    AliveState->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    KilledBy->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    HideLists();
    m_slot1->ShowGWnd(true);
    m_spin->SetMinValue(1);
    m_spin->SetCurrentValue(1);
    m_spin->SetMaxValue(10);
    m_spin->ShowGWnd(true);



    //////////////
    this->ShowGWnd(false);
    return true;
}


void CIFSTUniqueHistory::On_BtnClick() {
    static int i = 0;

}

void CIFSTUniqueHistory::OnUpdate() {
    time_t rawtime;
    struct tm *timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);

}
int CIFSTUniqueHistory::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
void CIFSTUniqueHistory::HideLists()
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
void CIFSTUniqueHistory::ClearDDJ() {
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
void CIFSTUniqueHistory::ShowList(BYTE listid)
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

bool CIFSTUniqueHistory::IsPageFull(BYTE PageID, BYTE LineID)
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
            if (m_slot1->line10->m_custom_label2->GetNText().length() > 0)
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
            if (m_slot2->line10->m_custom_label2->GetNText().length() > 0)
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
            if (m_slot3->line10->m_custom_label2->GetNText().length() > 0)
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
            if (m_slot4->line10->m_custom_label2->GetNText().length() > 0)
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
            if (m_slot5->line10->m_custom_label2->GetNText().length() > 0)
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
            if (m_slot6->line10->m_custom_label2->GetNText().length() > 0)
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
            if (m_slot7->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 8)
    {
        if (LineID == 30)
        {
            if (m_slot8->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot8->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 9)
    {
        if (LineID == 30)
        {
            if (m_slot9->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot9->line10->m_custom_label2->GetNText().length() > 0)
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


void CIFSTUniqueHistory::UpdateUniqueList()
{

    for (std::vector<CIFSTUniqueHistory::UniqueHistory>::iterator it = CIFSTUniqueHistory::UniqueHistoryList.begin(); it != CIFSTUniqueHistory::UniqueHistoryList.end(); ++it)
    {

        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 51:
            {
                m_slot6->line1->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 52:
            {
                m_slot6->line2->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 53:
            {
                m_slot6->line3->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 54:
            {
                m_slot6->line4->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 55:
            {
                m_slot6->line5->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 56:
            {
                m_slot6->line6->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 57:
            {
                m_slot6->line7->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 58:
            {
                m_slot6->line8->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 59:
            {
                m_slot6->line9->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 60:
            {
                m_slot6->line10->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 61:
            {
                m_slot7->line1->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 62:
            {
                m_slot7->line2->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 63:
            {
                m_slot7->line3->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 64:
            {
                m_slot7->line4->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 65:
            {
                m_slot7->line5->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 66:
            {
                m_slot7->line6->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 67:
            {
                m_slot7->line7->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 68:
            {
                m_slot7->line8->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 69:
            {
                m_slot7->line9->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 70:
            {
                m_slot7->line10->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 71:
            {
                m_slot8->line1->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 72:
            {
                m_slot8->line2->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 73:
            {
                m_slot8->line3->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 74:
            {
                m_slot8->line4->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 75:
            {
                m_slot8->line5->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 76:
            {
                m_slot8->line6->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 77:
            {
                m_slot8->line7->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 78:
            {
                m_slot8->line8->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 79:
            {
                m_slot8->line9->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 80:
            {
                m_slot8->line10->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 81:
            {
                m_slot9->line1->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 82:
            {
                m_slot9->line2->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 83:
            {
                m_slot9->line3->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 84:
            {
                m_slot9->line4->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 85:
            {
                m_slot9->line5->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 86:
            {
                m_slot9->line6->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 87:
            {
                m_slot9->line7->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 88:
            {
                m_slot9->line8->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 89:
            {
                m_slot9->line9->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 90:
            {
                m_slot9->line10->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 91:
            {
                m_slot10->line1->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 92:
            {
                m_slot10->line2->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 93:
            {
                m_slot10->line3->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 94:
            {
                m_slot10->line4->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 95:
            {
                m_slot10->line5->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 96:
            {
                m_slot10->line6->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 97:
            {
                m_slot10->line7->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 98:
            {
                m_slot10->line8->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 99:
            {
                m_slot10->line9->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
            case 100:
            {
                m_slot10->line10->WriteLine((*it).NameStrID128.c_str(), (*it).State.c_str(), (*it).Killer.c_str(), (*it).Date.c_str());
            }
                break;
        }
    }
}

void CIFSTUniqueHistory::Clear()
{
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

    m_slot6->line1->WriteLine(L"", L"", L"", L"");
    m_slot6->line2->WriteLine(L"", L"", L"", L"");
    m_slot6->line3->WriteLine(L"", L"", L"", L"");
    m_slot6->line4->WriteLine(L"", L"", L"", L"");
    m_slot6->line5->WriteLine(L"", L"", L"", L"");
    m_slot6->line6->WriteLine(L"", L"", L"", L"");
    m_slot6->line7->WriteLine(L"", L"", L"", L"");
    m_slot6->line8->WriteLine(L"", L"", L"", L"");
    m_slot6->line9->WriteLine(L"", L"", L"", L"");
    m_slot6->line10->WriteLine(L"", L"", L"", L"");

    m_slot7->line1->WriteLine(L"", L"", L"", L"");
    m_slot7->line2->WriteLine(L"", L"", L"", L"");
    m_slot7->line3->WriteLine(L"", L"", L"", L"");
    m_slot7->line4->WriteLine(L"", L"", L"", L"");
    m_slot7->line5->WriteLine(L"", L"", L"", L"");
    m_slot7->line6->WriteLine(L"", L"", L"", L"");
    m_slot7->line7->WriteLine(L"", L"", L"", L"");
    m_slot7->line8->WriteLine(L"", L"", L"", L"");
    m_slot7->line9->WriteLine(L"", L"", L"", L"");
    m_slot7->line10->WriteLine(L"", L"", L"", L"");

    m_slot8->line1->WriteLine(L"", L"", L"", L"");
    m_slot8->line2->WriteLine(L"", L"", L"", L"");
    m_slot8->line3->WriteLine(L"", L"", L"", L"");
    m_slot8->line4->WriteLine(L"", L"", L"", L"");
    m_slot8->line5->WriteLine(L"", L"", L"", L"");
    m_slot8->line6->WriteLine(L"", L"", L"", L"");
    m_slot8->line7->WriteLine(L"", L"", L"", L"");
    m_slot8->line8->WriteLine(L"", L"", L"", L"");
    m_slot8->line9->WriteLine(L"", L"", L"", L"");
    m_slot8->line10->WriteLine(L"", L"", L"", L"");

    m_slot9->line1->WriteLine(L"", L"", L"", L"");
    m_slot9->line2->WriteLine(L"", L"", L"", L"");
    m_slot9->line3->WriteLine(L"", L"", L"", L"");
    m_slot9->line4->WriteLine(L"", L"", L"", L"");
    m_slot9->line5->WriteLine(L"", L"", L"", L"");
    m_slot9->line6->WriteLine(L"", L"", L"", L"");
    m_slot9->line7->WriteLine(L"", L"", L"", L"");
    m_slot9->line8->WriteLine(L"", L"", L"", L"");
    m_slot9->line9->WriteLine(L"", L"", L"", L"");
    m_slot9->line10->WriteLine(L"", L"", L"", L"");

    m_slot10->line1->WriteLine(L"", L"", L"", L"");
    m_slot10->line2->WriteLine(L"", L"", L"", L"");
    m_slot10->line3->WriteLine(L"", L"", L"", L"");
    m_slot10->line4->WriteLine(L"", L"", L"", L"");
    m_slot10->line5->WriteLine(L"", L"", L"", L"");
    m_slot10->line6->WriteLine(L"", L"", L"", L"");
    m_slot10->line7->WriteLine(L"", L"", L"", L"");
    m_slot10->line8->WriteLine(L"", L"", L"", L"");
    m_slot10->line9->WriteLine(L"", L"", L"", L"");
    m_slot10->line10->WriteLine(L"", L"", L"", L"");
}
void CIFSTUniqueHistory::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}