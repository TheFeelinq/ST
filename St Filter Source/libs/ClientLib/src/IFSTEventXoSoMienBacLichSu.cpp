//
// Created by Admin on 31/7/2021.
//

#include "IFSTEventXoSoMienBacLichSu.h"
#include "IFNormalTile.h"
#include "GlobalHelpersThatHaveNoHomeYet.h"
#include <ctime>

#define GDR_FLORIAN0_RT_LABEL 10
#define GDR_FLORIAN0_RT_BTN 11
#define GDR_FLORIAN0_RT_LABEL_TIME 13
#define GDR_FLORIAN0_RT_MAIN_FRAME 20

GFX_IMPLEMENT_DYNCREATE(CIFSTEventXoSoMienBacLichSu, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTEventXoSoMienBacLichSu, CIFMainFrame)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN, &On_BtnClick)
GFX_END_MESSAGE_MAP()
std::vector<CIFSTEventXoSoMienBacLichSu::XSMBLichSu> CIFSTEventXoSoMienBacLichSu::XSMBLichSuList;
CIFSTEventXoSoMienBacLichSu::CIFSTEventXoSoMienBacLichSu(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFSTEventXoSoMienBacLichSu::~CIFSTEventXoSoMienBacLichSu(void)
{
    //  printf("> " __FUNCTION__ "\n");
}

bool CIFSTEventXoSoMienBacLichSu::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);

    // Set own title
    SetText(L"florian0 runtime window");

    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);

    wnd_size sz = this->GetSize();

    RECT rect_frame = {10, 40, sz.width - 20, sz.height - 50};

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


    RECT rect_custom_label = {27, 51, 41, 25};
    m_stt = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label,21,1);
    RECT rect_label_time = {67, 51, 41, 25};
    m_so = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_label_time,22,1);
    RECT rect_tiencuoc = {107, 51, 111, 25};
    tiencuoc = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_tiencuoc,23,1);
    RECT rect_trangthai = {215, 51, 74, 25};
    trangthai = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_trangthai,24,1);
    RECT rect_tiente = {287, 51, 56, 25};
    tiente = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_tiente,24,1);
    RECT rect_loai = {342, 51, 51, 25};
    loai = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_loai,24,1);
    RECT rect_ngay = {392, 51, 110, 25};
    ngay = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_ngay,24,1);
    RECT Spinrect = {247, 322, 50, 16};
    m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), Spinrect, 4, 0);
   // HideLists();
    m_spin->SetMinValue(1);
    m_spin->SetCurrentValue(1);
    m_spin->SetMaxValue(10);
    m_spin->ShowGWnd(true);


    m_stt->SetText(TSM_GETTEXTPTR("UIIT_STT_XSMB_LS_STT_LABEL"));
    m_so->SetText(TSM_GETTEXTPTR("UIIT_STT_XSMB_LS_SO_LABEL"));
    tiencuoc->SetText(TSM_GETTEXTPTR("UIIT_STT_XSMB_LS_TIENCUOC_LABEL"));
    trangthai->SetText(TSM_GETTEXTPTR("UIIT_STT_XSMB_LS_TRANGTHAI_LABEL"));
    tiente->SetText(TSM_GETTEXTPTR("UIIT_STT_XSMB_LS_TIENTE_LABEL"));
    loai->SetText(TSM_GETTEXTPTR("UIIT_STT_XSMB_LS_LOAI_LABEL"));
    ngay->SetText(TSM_GETTEXTPTR("UIIT_STT_XSMB_LS_NGAY_LABEL"));
/*    m_so->MoveGWnd(m_stt->GetPos().x + m_stt->GetSize().width, m_stt->GetPos().y);
    tiencuoc->MoveGWnd(m_so->GetPos().x + m_so->GetSize().width, m_stt->GetPos().y);
    trangthai->MoveGWnd(tiencuoc->GetPos().x + tiencuoc->GetSize().width, m_stt->GetPos().y);
    tiente->MoveGWnd(trangthai->GetPos().x + trangthai->GetSize().width, m_stt->GetPos().y);
    loai->MoveGWnd(tiente->GetPos().x + tiente->GetSize().width, m_stt->GetPos().y);
    ngay->MoveGWnd(loai->GetPos().x + loai->GetSize().width, m_stt->GetPos().y);*/

    m_stt->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    m_so->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    tiencuoc->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    trangthai->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    tiente->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    loai->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    ngay->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);

    RECT rect_button = {50, 90, 60, 20};
    CIFButton *btn = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button,GDR_FLORIAN0_RT_BTN,1);

    btn->SetText(L"Click me");
    btn->TB_Func_13("interface\\system\\sys_button.ddj", 1, 1);

    RECT rect = { 0,0,0,0 };
    m_slot1 = (CIFSTEventXoSoMienBacLichSuSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlotList), rect, 40, 0);
    m_slot2 = (CIFSTEventXoSoMienBacLichSuSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlotList), rect, 41, 0);
    m_slot3 = (CIFSTEventXoSoMienBacLichSuSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlotList), rect, 42, 0);
    m_slot4 = (CIFSTEventXoSoMienBacLichSuSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlotList), rect, 43, 0);
    m_slot5 = (CIFSTEventXoSoMienBacLichSuSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlotList), rect, 44, 0);
    m_slot6 = (CIFSTEventXoSoMienBacLichSuSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlotList), rect, 45, 0);
    m_slot7 = (CIFSTEventXoSoMienBacLichSuSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlotList), rect, 46, 0);
    m_slot8 = (CIFSTEventXoSoMienBacLichSuSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlotList), rect, 47, 0);
    m_slot9 = (CIFSTEventXoSoMienBacLichSuSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlotList), rect, 48, 0);
    m_slot10 = (CIFSTEventXoSoMienBacLichSuSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlotList), rect, 49, 0);



    m_slot1->MoveGWnd(m_slot1->GetPos().x + 2, m_slot1->GetPos().y + 2);
    m_slot2->MoveGWnd(m_slot2->GetPos().x + 2, m_slot2->GetPos().y + 2);
    m_slot3->MoveGWnd(m_slot3->GetPos().x + 2, m_slot3->GetPos().y + 2);
    m_slot4->MoveGWnd(m_slot4->GetPos().x + 2, m_slot4->GetPos().y + 2);
    m_slot5->MoveGWnd(m_slot5->GetPos().x + 2, m_slot5->GetPos().y + 2);
    m_slot6->MoveGWnd(m_slot6->GetPos().x + 2, m_slot6->GetPos().y + 2);
    m_slot7->MoveGWnd(m_slot7->GetPos().x + 2, m_slot7->GetPos().y + 2);

    m_slot8->MoveGWnd(m_slot8->GetPos().x + 2, m_slot8->GetPos().y + 2);
    m_slot9->MoveGWnd(m_slot9->GetPos().x + 2, m_slot9->GetPos().y + 2);
    m_slot10->MoveGWnd(m_slot10->GetPos().x + 2, m_slot10->GetPos().y + 2);
    m_slot1->ShowGWnd(true);
    this->ShowGWnd(false);
    return true;
}


void CIFSTEventXoSoMienBacLichSu::On_BtnClick() {
    static int i = 0;

    wchar_t buffer[80];
    swprintf(buffer, L"Hello World (%d)", i++);


}

void CIFSTEventXoSoMienBacLichSu::OnUpdate() {
    time_t rawtime;
    struct tm *timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);


}
void CIFSTEventXoSoMienBacLichSu::HideLists()
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
void CIFSTEventXoSoMienBacLichSu::ClearDDJ() {
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
void CIFSTEventXoSoMienBacLichSu::ShowList(BYTE listid)
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

bool CIFSTEventXoSoMienBacLichSu::IsPageFull(BYTE PageID, BYTE LineID)
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


void CIFSTEventXoSoMienBacLichSu::UpdateXsmbLichSuList()
{
    int i = 0;
    for (std::vector<CIFSTEventXoSoMienBacLichSu::XSMBLichSu>::iterator it = CIFSTEventXoSoMienBacLichSu::XSMBLichSuList.begin(); it != CIFSTEventXoSoMienBacLichSu::XSMBLichSuList.end(); ++it)
    {
        ++i;
        // if(!(*it).NameStrID128.empty())
        //{
        (*it).LineNum = i;
        //}

        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 51:
            {
                m_slot6->line1->WriteLine(L"51", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 52:
            {
                m_slot6->line2->WriteLine(L"52", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 53:
            {
                m_slot6->line3->WriteLine(L"53", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 54:
            {
                m_slot6->line4->WriteLine(L"54", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 55:
            {
                m_slot6->line5->WriteLine(L"55", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 56:
            {
                m_slot6->line6->WriteLine(L"56", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 57:
            {
                m_slot6->line7->WriteLine(L"57", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 58:
            {
                m_slot6->line8->WriteLine(L"58", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 59:
            {
                m_slot6->line9->WriteLine(L"59", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 60:
            {
                m_slot6->line10->WriteLine(L"60", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 61:
            {
                m_slot7->line1->WriteLine(L"61", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 62:
            {
                m_slot7->line2->WriteLine(L"62", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 63:
            {
                m_slot7->line3->WriteLine(L"63", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 64:
            {
                m_slot7->line4->WriteLine(L"64", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 65:
            {
                m_slot7->line5->WriteLine(L"65", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 66:
            {
                m_slot7->line6->WriteLine(L"66", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 67:
            {
                m_slot7->line7->WriteLine(L"67", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 68:
            {
                m_slot7->line8->WriteLine(L"68", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 69:
            {
                m_slot7->line9->WriteLine(L"69", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 70:
            {
                m_slot7->line10->WriteLine(L"70", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 71:
            {
                m_slot8->line1->WriteLine(L"71", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 72:
            {
                m_slot8->line2->WriteLine(L"72", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 73:
            {
                m_slot8->line3->WriteLine(L"73", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 74:
            {
                m_slot8->line4->WriteLine(L"74", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 75:
            {
                m_slot8->line5->WriteLine(L"75", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 76:
            {
                m_slot8->line6->WriteLine(L"76", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 77:
            {
                m_slot8->line7->WriteLine(L"77", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 78:
            {
                m_slot8->line8->WriteLine(L"78", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 79:
            {
                m_slot8->line9->WriteLine(L"79", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 80:
            {
                m_slot8->line10->WriteLine(L"80", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 81:
            {
                m_slot9->line1->WriteLine(L"81", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 82:
            {
                m_slot9->line2->WriteLine(L"82", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 83:
            {
                m_slot9->line3->WriteLine(L"83", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 84:
            {
                m_slot9->line4->WriteLine(L"84", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 85:
            {
                m_slot9->line5->WriteLine(L"85", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 86:
            {
                m_slot9->line6->WriteLine(L"86", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 87:
            {
                m_slot9->line7->WriteLine(L"87", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 88:
            {
                m_slot9->line8->WriteLine(L"88", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 89:
            {
                m_slot9->line9->WriteLine(L"89", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 90:
            {
                m_slot9->line10->WriteLine(L"90", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 91:
            {
                m_slot10->line1->WriteLine(L"91", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 92:
            {
                m_slot10->line2->WriteLine(L"92", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 93:
            {
                m_slot10->line3->WriteLine(L"93", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 94:
            {
                m_slot10->line4->WriteLine(L"94", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 95:
            {
                m_slot10->line5->WriteLine(L"95", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 96:
            {
                m_slot10->line6->WriteLine(L"96", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 97:
            {
                m_slot10->line7->WriteLine(L"97", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 98:
            {
                m_slot10->line8->WriteLine(L"98", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 99:
            {
                m_slot10->line9->WriteLine(L"99", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
            case 100:
            {
                m_slot10->line10->WriteLine(L"100", (*it).So.c_str(), (*it).TienCuoc.c_str(), (*it).TrangThai.c_str(), (*it).TienTe.c_str(), (*it).Loai.c_str(), (*it).Ngay.c_str());
            }
                break;
        }
    }
}

void CIFSTEventXoSoMienBacLichSu::Clear()
{
    m_slot1->line1->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot1->line2->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot1->line3->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot1->line4->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot1->line5->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot1->line6->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot1->line7->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot1->line8->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot1->line9->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot1->line10->WriteLine(L"", L"", L"", L"", L"", L"", L"");

    m_slot2->line1->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot2->line2->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot2->line3->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot2->line4->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot2->line5->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot2->line6->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot2->line7->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot2->line8->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot2->line9->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot2->line10->WriteLine(L"", L"", L"", L"", L"", L"", L"");

    m_slot3->line1->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot3->line2->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot3->line3->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot3->line4->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot3->line5->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot3->line6->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot3->line7->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot3->line8->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot3->line9->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot3->line10->WriteLine(L"", L"", L"", L"", L"", L"", L"");

    m_slot4->line1->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot4->line2->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot4->line3->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot4->line4->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot4->line5->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot4->line6->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot4->line7->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot4->line8->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot4->line9->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot4->line10->WriteLine(L"", L"", L"", L"", L"", L"", L"");

    m_slot5->line1->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot5->line2->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot5->line3->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot5->line4->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot5->line5->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot5->line6->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot5->line7->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot5->line8->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot5->line9->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot5->line10->WriteLine(L"", L"", L"", L"", L"", L"", L"");

    m_slot6->line1->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot6->line2->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot6->line3->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot6->line4->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot6->line5->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot6->line6->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot6->line7->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot6->line8->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot6->line9->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot6->line10->WriteLine(L"", L"", L"", L"", L"", L"", L"");

    m_slot7->line1->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot7->line2->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot7->line3->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot7->line4->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot7->line5->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot7->line6->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot7->line7->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot7->line8->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot7->line9->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot7->line10->WriteLine(L"", L"", L"", L"", L"", L"", L"");

    m_slot8->line1->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot8->line2->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot8->line3->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot8->line4->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot8->line5->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot8->line6->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot8->line7->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot8->line8->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot8->line9->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot8->line10->WriteLine(L"", L"", L"", L"", L"", L"", L"");

    m_slot9->line1->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot9->line2->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot9->line3->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot9->line4->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot9->line5->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot9->line6->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot9->line7->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot9->line8->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot9->line9->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot9->line10->WriteLine(L"", L"", L"", L"", L"", L"", L"");

    m_slot10->line1->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot10->line2->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot10->line3->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot10->line4->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot10->line5->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot10->line6->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot10->line7->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot10->line8->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot10->line9->WriteLine(L"", L"", L"", L"", L"", L"", L"");
    m_slot10->line10->WriteLine(L"", L"", L"", L"", L"", L"", L"");
}
void CIFSTEventXoSoMienBacLichSu::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 780;
    this->MoveGWnd(PosX, PosY);
}