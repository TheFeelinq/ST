//
// Created by kinge on 1/7/2021.
//

#include "IFSTFTWCounter.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>

#define BFILTER_FTWCounter_Num1 14
#define BFILTER_FTWCounter_Num2 15
#define BFILTER_FTWCounter_Num3 16
#define BFILTER_FTWCounter_Num4 17
#define BFILTER_FTWCounter_Num5 18
#define BFILTER_FTWCounter_Num6 19
#define BFILTER_FTWCounter_Num7 20
#define BFILTER_FTWCounter_Num8 21

#define BFILTER_FTWCounter_CharNum1 22
#define BFILTER_FTWCounter_CharNum2 23
#define BFILTER_FTWCounter_CharNum3 24
#define BFILTER_FTWCounter_CharNum4 25
#define BFILTER_FTWCounter_CharNum5 26
#define BFILTER_FTWCounter_CharNum6 27
#define BFILTER_FTWCounter_CharNum7 28
#define BFILTER_FTWCounter_CharNum8 29

#define BFILTER_FTWCounter_DMGNum1 30
#define BFILTER_FTWCounter_DMGNum2 31
#define BFILTER_FTWCounter_DMGNum3 32
#define BFILTER_FTWCounter_DMGNum4 33
#define BFILTER_FTWCounter_DMGNum5 34
#define BFILTER_FTWCounter_DMGNum6 35
#define BFILTER_FTWCounter_DMGNum7 36
#define BFILTER_FTWCounter_DMGNum8 37

#define BFILTER_FTWCounter_DMGText 13
#define BFILTER_FTWCounter_CharText 12

#define BFILTER_FTWCounter_TITLE 11
#define BFILTER_FTWCounter_FRAME 10

#define BFILTER_MENU_FRAME 6
#define BFILTER_MENU_NORMALTITLE 5

GFX_IMPLEMENT_DYNCREATE(CIFFTWCounter, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFFTWCounter, CIFMainFrame)
GFX_END_MESSAGE_MAP()


CIFFTWCounter::CIFFTWCounter(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFFTWCounter::~CIFFTWCounter(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFFTWCounter::OnCreate(long ln)
{
    // printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT FrameRect = { 17,45,180,185 };
    RECT normal2Rect = { 33,82,148,110 };

    RECT lable1Rect = { 24,33,82,14 };
    RECT lable2Rect = { 129,33,49,14 };

    RECT lable3Rect = { 9,51,13,13 };
    RECT lable4Rect = { 9,66,13,13 };
    RECT lable5Rect = { 9,81,13,13 };
    RECT lable6Rect = { 9,96,13,13 };
    RECT lable7Rect = { 9,111,13,13 };
    RECT lable8Rect = { 9,126,13,13 };
    RECT lable9Rect = { 9,141,13,13 };
    RECT lable10Rect = { 9,156,13,13 };

    RECT lable11Rect = { 26,51,110,14 };
    RECT lable12Rect = { 26,66,110,14 };
    RECT lable13Rect = { 26,81,110,14 };
    RECT lable14Rect = { 26,96,110,14 };
    RECT lable15Rect = { 26,111,110,14 };
    RECT lable16Rect = { 26,126,110,14 };
    RECT lable17Rect = { 26,141,110,14 };
    RECT lable18Rect = { 26,156,110,14 };

    RECT lable19Rect = { 132,51,44,14 };
    RECT lable20Rect = { 132,66,44,14 };
    RECT lable21Rect = { 132,81,44,14 };
    RECT lable22Rect = { 132,96,44,14 };
    RECT lable23Rect = { 132,111,44,14 };
    RECT lable24Rect = { 132,126,44,14 };
    RECT lable25Rect = { 132,141,44,14 };
    RECT lable26Rect = { 132,156,44,14 };

    Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), FrameRect, BFILTER_MENU_FRAME, 0);
    NormalTitle = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), normal2Rect, BFILTER_MENU_NORMALTITLE, 0);

    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
    NormalTitle->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);

    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable1Rect, BFILTER_FTWCounter_CharText, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable2Rect, BFILTER_FTWCounter_DMGText, 0);

    m_custom_label3->MoveGWnd(m_custom_label3->GetBounds().pos.x + 15, m_custom_label3->GetBounds().pos.y + 15);
    m_custom_label4->MoveGWnd(m_custom_label4->GetBounds().pos.x + 10, m_custom_label4->GetBounds().pos.y + 15);

    m_custom_label3->SetTextColor(0xffffff);
    m_custom_label4->SetTextColor(0xffffff);

    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable3Rect, BFILTER_FTWCounter_Num1, 0);
    m_custom_label6 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable4Rect, BFILTER_FTWCounter_Num2, 0);
    m_custom_label7 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable5Rect, BFILTER_FTWCounter_Num3, 0);
    m_custom_label8 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable6Rect, BFILTER_FTWCounter_Num4, 0);
    m_custom_label9 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable7Rect, BFILTER_FTWCounter_Num5, 0);
    m_custom_label10 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable8Rect, BFILTER_FTWCounter_Num6, 0);
    m_custom_label11 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable9Rect, BFILTER_FTWCounter_Num7, 0);
    m_custom_label12 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable10Rect, BFILTER_FTWCounter_Num8, 0);


    m_custom_label13 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable11Rect, BFILTER_FTWCounter_CharNum1, 0);
    m_custom_label14 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable12Rect, BFILTER_FTWCounter_CharNum2, 0);
    m_custom_label15 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable13Rect, BFILTER_FTWCounter_CharNum3, 0);
    m_custom_label16 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable14Rect, BFILTER_FTWCounter_CharNum4, 0);
    m_custom_label17 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable15Rect, BFILTER_FTWCounter_CharNum5, 0);
    m_custom_label18 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable16Rect, BFILTER_FTWCounter_CharNum6, 0);
    m_custom_label19 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable17Rect, BFILTER_FTWCounter_CharNum7, 0);
    m_custom_label20 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable18Rect, BFILTER_FTWCounter_CharNum8, 0);


    m_custom_label21 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable19Rect, BFILTER_FTWCounter_DMGNum1, 0);
    m_custom_label22 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable20Rect, BFILTER_FTWCounter_DMGNum2, 0);
    m_custom_label23 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable21Rect, BFILTER_FTWCounter_DMGNum3, 0);
    m_custom_label24 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable22Rect, BFILTER_FTWCounter_DMGNum4, 0);
    m_custom_label25 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable23Rect, BFILTER_FTWCounter_DMGNum5, 0);
    m_custom_label26 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable24Rect, BFILTER_FTWCounter_DMGNum6, 0);
    m_custom_label27 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable25Rect, BFILTER_FTWCounter_DMGNum7, 0);
    m_custom_label28 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable26Rect, BFILTER_FTWCounter_DMGNum8, 0);

    m_custom_label5->MoveGWnd(m_custom_label5->GetBounds().pos.x + 15, m_custom_label5->GetBounds().pos.y + 15);
    m_custom_label6->MoveGWnd(m_custom_label6->GetBounds().pos.x + 15, m_custom_label6->GetBounds().pos.y + 15);
    m_custom_label7->MoveGWnd(m_custom_label7->GetBounds().pos.x + 15, m_custom_label7->GetBounds().pos.y + 15);
    m_custom_label8->MoveGWnd(m_custom_label8->GetBounds().pos.x + 15, m_custom_label8->GetBounds().pos.y + 15);
    m_custom_label9->MoveGWnd(m_custom_label9->GetBounds().pos.x + 15, m_custom_label9->GetBounds().pos.y + 15);
    m_custom_label10->MoveGWnd(m_custom_label10->GetBounds().pos.x + 15, m_custom_label10->GetBounds().pos.y + 15);
    m_custom_label11->MoveGWnd(m_custom_label11->GetBounds().pos.x + 15, m_custom_label11->GetBounds().pos.y + 15);
    m_custom_label12->MoveGWnd(m_custom_label12->GetBounds().pos.x + 15, m_custom_label12->GetBounds().pos.y + 15);
    m_custom_label13->MoveGWnd(m_custom_label13->GetBounds().pos.x + 15, m_custom_label13->GetBounds().pos.y + 15);
    m_custom_label14->MoveGWnd(m_custom_label14->GetBounds().pos.x + 15, m_custom_label14->GetBounds().pos.y + 15);
    m_custom_label15->MoveGWnd(m_custom_label15->GetBounds().pos.x + 15, m_custom_label15->GetBounds().pos.y + 15);
    m_custom_label16->MoveGWnd(m_custom_label16->GetBounds().pos.x + 15, m_custom_label16->GetBounds().pos.y + 15);
    m_custom_label17->MoveGWnd(m_custom_label17->GetBounds().pos.x + 15, m_custom_label17->GetBounds().pos.y + 15);
    m_custom_label18->MoveGWnd(m_custom_label18->GetBounds().pos.x + 15, m_custom_label18->GetBounds().pos.y + 15);
    m_custom_label19->MoveGWnd(m_custom_label19->GetBounds().pos.x + 15, m_custom_label19->GetBounds().pos.y + 15);
    m_custom_label20->MoveGWnd(m_custom_label20->GetBounds().pos.x + 15, m_custom_label20->GetBounds().pos.y + 15);
    //
    m_custom_label21->MoveGWnd(m_custom_label21->GetBounds().pos.x + 10, m_custom_label21->GetBounds().pos.y + 15);
    m_custom_label22->MoveGWnd(m_custom_label22->GetBounds().pos.x + 10, m_custom_label22->GetBounds().pos.y + 15);
    m_custom_label23->MoveGWnd(m_custom_label23->GetBounds().pos.x + 10, m_custom_label23->GetBounds().pos.y + 15);
    m_custom_label24->MoveGWnd(m_custom_label24->GetBounds().pos.x + 10, m_custom_label24->GetBounds().pos.y + 15);
    m_custom_label25->MoveGWnd(m_custom_label25->GetBounds().pos.x + 10, m_custom_label25->GetBounds().pos.y + 15);
    m_custom_label26->MoveGWnd(m_custom_label26->GetBounds().pos.x + 10, m_custom_label26->GetBounds().pos.y + 15);
    m_custom_label27->MoveGWnd(m_custom_label27->GetBounds().pos.x + 10, m_custom_label27->GetBounds().pos.y + 15);
    m_custom_label28->MoveGWnd(m_custom_label28->GetBounds().pos.x + 10, m_custom_label28->GetBounds().pos.y + 15);

    m_custom_label5->SetTextColor(0xffffff);
    m_custom_label6->SetTextColor(0xffffff);
    m_custom_label7->SetTextColor(0xffffff);
    m_custom_label8->SetTextColor(0xffffff);
    m_custom_label9->SetTextColor(0xffffff);
    m_custom_label10->SetTextColor(0xffffff);
    m_custom_label11->SetTextColor(0xffffff);
    m_custom_label12->SetTextColor(0xffffff);
    m_custom_label16->SetTextColor(0xffffff);
    m_custom_label17->SetTextColor(0xffffff);
    m_custom_label18->SetTextColor(0xffffff);
    m_custom_label19->SetTextColor(0xffffff);
    m_custom_label20->SetTextColor(0xffffff);
    m_custom_label24->SetTextColor(0xffffff);
    m_custom_label25->SetTextColor(0xffffff);
    m_custom_label26->SetTextColor(0xffffff);
    m_custom_label27->SetTextColor(0xffffff);
    m_custom_label28->SetTextColor(0xffffff);

    Frame->SetGWndSize(this->GetBounds().size.width - 20, this->GetBounds().size.height - 48);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 38);

    NormalTitle->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
    NormalTitle->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);

    m_title->SetText(L"Fortress Kills");
    m_close->ShowGWnd(false);
    //m_handleBar->ShowGWnd(false);

    m_custom_label3->SetText(L"Character");
    m_custom_label4->SetText(L"Damage");

    m_custom_label5->SetText(L"#1");
    m_custom_label5->SetTextColor(0xeb345b);
    m_custom_label6->SetText(L"#2");
    m_custom_label6->SetTextColor(0xfef29d);
    m_custom_label7->SetText(L"#3");
    m_custom_label7->SetTextColor(0x5ad3a9);
    m_custom_label8->SetText(L"#4");
    m_custom_label9->SetText(L"#5");
    m_custom_label10->SetText(L"#6");
    m_custom_label11->SetText(L"#7");
    m_custom_label12->SetText(L"#8");

    m_custom_label13->SetTextColor(0xeb345b);
    m_custom_label14->SetTextColor(0xfef29d);
    m_custom_label15->SetTextColor(0x5ad3a9);

    m_custom_label21->SetTextColor(0xeb345b);
    m_custom_label22->SetTextColor(0xfef29d);
    m_custom_label23->SetTextColor(0x5ad3a9);

    m_custom_label13->SetText(L"<NONE>");
    m_custom_label21->SetText(L"0");

    m_custom_label14->SetText(L"<NONE>");
    m_custom_label22->SetText(L"0");

    m_custom_label15->SetText(L"<NONE>");
    m_custom_label23->SetText(L"0");

    m_custom_label16->SetText(L"<NONE>");
    m_custom_label24->SetText(L"0");

    m_custom_label17->SetText(L"<NONE>");
    m_custom_label25->SetText(L"0");

    m_custom_label18->SetText(L"<NONE>");
    m_custom_label26->SetText(L"0");

    m_custom_label19->SetText(L"<NONE>");
    m_custom_label27->SetText(L"0");

    m_custom_label20->SetText(L"<NONE>");
    m_custom_label28->SetText(L"0");
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    this->ShowGWnd(false);
    return true;
}

void CIFFTWCounter::OnUpdate()
{
}

void CIFFTWCounter::On_BtnClick()
{

}

void CIFFTWCounter::On_BtnClick1()
{
}

void CIFFTWCounter::OnClick_Exit()
{
    this->OnCloseWnd();
}

void CIFFTWCounter::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 650;
    this->MoveGWnd(PosX, PosY);

}
void CIFFTWCounter::WriteLine(BYTE Num, const wchar_t* Charname, const wchar_t* DMG)
{
    switch (Num)
    {
        case 1:
            m_custom_label13->SetText(Charname);
            m_custom_label21->SetText(DMG);
            break;
        case 2:
            m_custom_label14->SetText(Charname);
            m_custom_label22->SetText(DMG);
            break;
        case 3:
            m_custom_label15->SetText(Charname);
            m_custom_label23->SetText(DMG);
            break;
        case 4:
            m_custom_label16->SetText(Charname);
            m_custom_label24->SetText(DMG);
            break;
        case 5:
            m_custom_label17->SetText(Charname);
            m_custom_label25->SetText(DMG);
            break;
        case 6:
            m_custom_label18->SetText(Charname);
            m_custom_label26->SetText(DMG);
            break;
        case 7:
            m_custom_label19->SetText(Charname);
            m_custom_label27->SetText(DMG);
            break;
        case 8:
            m_custom_label20->SetText(Charname);
            m_custom_label28->SetText(DMG);
            break;

        default:
            break;
    }
}

void CIFFTWCounter::Clear()
{
    m_custom_label13->SetText(L"<NONE>");
    m_custom_label21->SetText(L"0");

    m_custom_label14->SetText(L"<NONE>");
    m_custom_label22->SetText(L"0");

    m_custom_label15->SetText(L"<NONE>");
    m_custom_label23->SetText(L"0");

    m_custom_label16->SetText(L"<NONE>");
    m_custom_label24->SetText(L"0");

    m_custom_label17->SetText(L"<NONE>");
    m_custom_label25->SetText(L"0");

    m_custom_label18->SetText(L"<NONE>");
    m_custom_label26->SetText(L"0");

    m_custom_label19->SetText(L"<NONE>");
    m_custom_label27->SetText(L"0");

    m_custom_label20->SetText(L"<NONE>");
    m_custom_label28->SetText(L"0");
}