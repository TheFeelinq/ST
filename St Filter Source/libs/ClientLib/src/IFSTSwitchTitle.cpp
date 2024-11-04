#include "IFSTSwitchTitle.h"
#include "TextStringManager.h"
#include "GInterface.h"
#include "ICPlayer.h"
#include "SRO_MSG_DEF.h"
#include "IFChatViewer.h"
#include "IFListCtrl.h"
#include "Game.h"
#include <sstream>
#include <CPSMission.h>
#include "BSLib/multibyte.h"

#define STSROTITLES_FRAME 10
#define STSROTITLES_TITLE 2
#define STSROTITLES_VSCROLL 3
#define STSROTITLES_APPLY_BUTTON 4
#define STSROTITLES_REFRESH_BUTTON 5
#define STSROTITLES_TEXTBOX 6
#define STSROTITLES_LABLE_1 7
#define STSROTITLES_LABLE_2 8

GFX_IMPLEMENT_DYNCREATE(CIFSwitchTitle, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSwitchTitle, CIFMainFrame)
                    ONG_COMMAND(STSROTITLES_REFRESH_BUTTON, &CIFSwitchTitle::On_BtnClick)
                    ONG_COMMAND(STSROTITLES_APPLY_BUTTON, &CIFSwitchTitle::On_BtnClick1)
                    ONG_BSSig_u38(2, 0x806D, STSROTITLES_TEXTBOX, &CIFSwitchTitle::OnListChatThing)
GFX_END_MESSAGE_MAP()

CIFSwitchTitle::CIFSwitchTitle(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFSwitchTitle::~CIFSwitchTitle(void)
{
    // printf("> " __FUNCTION__ "\n");
}

bool CIFSwitchTitle::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    CIFMainFrame::OnCreate(ln);

    RECT RefReshRect = { 266,342,111,24 };
    RECT TextRect = { 27,28,365,343 };
    RECT labRect = { 220,51,16,23 };
    RECT lab2Rect = { 250,51,16,23 };
    RECT lab3Rect = { 0,0,300,300 };
    RECT scrollRect = { 602,88,16,209 };

    m_mybutton = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), RefReshRect, STSROTITLES_REFRESH_BUTTON, 0);
    m_mybutton2 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), RefReshRect, STSROTITLES_APPLY_BUTTON, 0);
    m_mybutton->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj",0,0);
    m_mybutton2->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);

    m_textbox = (CIFTextBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFTextBox), TextRect, STSROTITLES_TEXTBOX, 0);

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), labRect, STSROTITLES_LABLE_1, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lab2Rect, STSROTITLES_LABLE_2, 0);
    Frame = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lab3Rect, STSROTITLES_FRAME, 0);
    Frame->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\ttitles_frame.ddj", 0, 0);

    m_vericalSroll = (CIFVerticalScroll*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFVerticalScroll), scrollRect, STSROTITLES_VSCROLL, 0);

    m_mybutton->MoveGWnd(m_mybutton->GetPos().x - 95, m_mybutton->GetPos().y - 85);
    m_mybutton2->MoveGWnd(m_mybutton->GetPos().x - 150, m_mybutton->GetPos().y);

    m_custom_label2->SetGWndSize(175, 16);
    m_custom_label1->SetGWndSize(70, 20);
    m_custom_label1->MoveGWnd(m_custom_label1->GetPos().x - 200, m_custom_label1->GetPos().y - 5);
    m_custom_label2->MoveGWnd(m_custom_label2->GetPos().x - 152, m_custom_label1->GetPos().y + 3);

    m_textbox->SetGWndSize(235,130);
    m_textbox->MoveGWnd(Frame->GetPos().x + 28, Frame->GetPos().y + 110);

    m_vericalSroll->MoveGWnd(Frame->GetPos().x + Frame->GetSize().width - 32, m_vericalSroll->GetBounds().pos.y + 35);
    m_vericalSroll->sub_65A500(m_vericalSroll->GetSize().height - 120);
    m_vericalSroll->SetGWndSize(m_vericalSroll->GetBounds().size.width, m_vericalSroll->GetSize().height - 120);

    m_mybutton->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_SWITCH_APPLY"));
    m_mybutton2->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_SWITCH_REMOVE"));
    m_custom_label1->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_SWITCH_CURENT"));
    m_custom_label1->SetTextColor(0xf1dd38);

    m_chatSize = 3;
    for (int i = 0; i < 5; i++) {
        m_textbox[i].N00000608 = this;
        //m_textbox[i].ShowGWnd(true);
        m_textbox[i].m_LinesOfHistory = 100;

        m_textbox[i].m_HeightInLines = 2 * this->m_chatSize;
        m_textbox[i].SetLineHeight(23);
        m_textbox[i].sub_638B50(0);
        m_textbox[i].sub_64E380(1);
        m_textbox[i].sub_638C70(1);
        m_textbox[i].SetHightlineLine(true);
        m_textbox[i].sub_638D50(1);
        m_textbox[i].SetHighlightColor(D3DCOLOR_RGBA(255, 255, 255, 102));
        m_textbox[i].sub_638D40(1);
    }
    RECT v66;

    v66.bottom = 1;
    v66.right = 0;
    v66.left = 0;
    v66.top = 308;

    m_vericalSroll->sub_65A390(v66);


    int v5; // edi@1

    int chat_base_pos_y = CGame::GetClientDimensionStuff().height - 467;
    int v3 = CGame::GetClientDimensionStuff().height;
    v5 = v3 - 68;
    int chat_pos_y = chat_base_pos_y + chatSizeUnit * (6 - m_chatSize);
    m_vericalSroll->ShowGWnd(true);
    m_vericalSroll->sub_65A500(chatSizeUnit * 2 - 28);
    m_vericalSroll->SetGWndSize(m_vericalSroll->GetBounds().size.width, chatSizeUnit * 2 - 28);
    m_textbox->SetGWndSize(m_textbox->GetBounds().size.width, chatSizeUnit * m_chatSize - 28);
    wnd_rect a2 = m_textbox->GetBounds();
    m_textbox->LinkScrollbar(m_vericalSroll);
    m_textbox->TB_Func_5(0);
    m_textbox->TB_Func_6(0);

    std::n_wstring msg(TSM_GETTEXTPTR("UIIT_ST_TITLE_SWITCH_CURENT"));
    m_custom_label2->SetTooltipText(&msg);
    m_custom_label2->SetToolTipSetting(0x80);

    m_title->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_SWITCH"));
    m_title->BringToFront();
    m_close->BringToFront();
    m_textbox->BringToFront();
    m_vericalSroll->BringToFront();
    m_custom_label1->BringToFront();
    m_custom_label2->BringToFront();
    m_mybutton->BringToFront();
    m_mybutton2->BringToFront();

    this->ShowGWnd(false);
    ResetPosition();
    return true;
}

void CIFSwitchTitle::OnUpdate()
{
}
int CIFSwitchTitle::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}

void CIFSwitchTitle::OnListChatThing(int a1, int a2) {

    CIFListCtrl* pList;
    pList = m_textbox;

    CIFListCtrl::SLineOfText* line = pList->sub_63A940();

    std::n_wstring str;
    line->m_font->GetText(&str);
    TitleColor = line->m_font->GetFontColor();
    if (str.empty())
        return;
    m_custom_label2->SetText(str.c_str());
    m_custom_label2->SetTextColor(TitleColor);
}

void CIFSwitchTitle::On_BtnClick()
{
    if(m_custom_label2->GetNText().empty())
    {
        wchar_t message[1000];
        swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_SELECT_TITLE_RQ"));

        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 255, 0, 0);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    } else {
        CMsgStreamBuffer buf(0x1318);
        buf << std::n_string(TO_NSTRING(this->m_custom_label2->GetNText()));
        buf << std::n_string("!TitleSet");
        buf << TitleColor;
        SendMsg(buf);
    }
}

void CIFSwitchTitle::On_BtnClick1() {

    if (0 != CPSMission::CurHawn) {
        BYTE REMOVE = 0;
        CMsgStreamBuffer buf(0x1201);
        buf << REMOVE;
        SendMsg(buf);
    } else {
        g_pCGInterface->ShowMessage_Warning(TSM_GETTEXTPTR("UIIT_ST_TITLE_SWITCH_REMOVED"));
        return;
    }
}

void CIFSwitchTitle::OnClick_Exit()
{
    this->OnCloseWnd();
    m_custom_label2->SetText(L"");
    m_textbox->m_LinesOfHistory = 0;
}
void CIFSwitchTitle::ClearTextbox()
{
    for(int i =0;m_textbox->GetNumberOfItems();i++) {
        m_textbox->RemoveLine(i);
    }
    for(int i =0;i<=m_textbox->GetNumberOfItems();i++) {
        m_textbox->RemoveLine(i);
    }
    for(int i =0;i<=m_textbox->GetNumberOfItems();i++) {
        m_textbox->RemoveLine(i);
    }
    for(int i =0;i<=m_textbox->GetNumberOfItems();i++) {
        m_textbox->RemoveLine(i);
    }
}
void CIFSwitchTitle::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}
