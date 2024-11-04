#include "IFSTCustomTitle.h"
#include "CPSMission.h"
#include "Game.h"
#include <IFEdit.h>
#include <ICPlayer.h>
#include <BSLib\multiBYTE.h>
#include <IFflorian0Guide.h>
#include <GInterface.h>
#include <imgui/imgui.h>

#define ST_CUSTOMTITLE_APPLY 31
#define ST_CUSTOMTITLE_CLOSE_BUTTON 32
#define ST_CUSTOMTITLE_NAME_INPUT 36
#define ST_CUSTOMTITLE_DESC1 33
#define ST_CUSTOMTITLE_DESC2 34
#define ST_CUSTOMTITLE_DESC3 35
#define ST_CUSTOMTITLE_TITLE_2 23
#define ST_CUSTOMTITLE_FRAME 21
#define ST_CUSTOMTITLE_TAP1 24
#define ST_CUSTOMTITLE_TAP2 25

#define CUSTOMTITLES2_MAUHONG_BTN 43
#define CUSTOMTITLES2_MAUTIM_BTN 37
#define CUSTOMTITLES2_MAUXANHLAM_BTN 38
#define CUSTOMTITLES2_MAUXANHLA_BTN 39
#define CUSTOMTITLES2_MAUVANG_BTN 40
#define CUSTOMTITLES2_MAUCAM_BTN 41
#define CUSTOMTITLES2_MAUDO_BTN 42
#define CUSTOMTITLES2_MUA_LUOT_BTN 14

bool CIFCustomTitle::ColorSelectShow = false;

GFX_IMPLEMENT_DYNCREATE(CIFCustomTitle, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFCustomTitle, CIFMainFrame)
                    ONG_COMMAND(ST_CUSTOMTITLE_CLOSE_BUTTON, &CIFCustomTitle::OnClick_Exit)
                    ONG_COMMAND(ST_CUSTOMTITLE_APPLY, &CIFCustomTitle::On_BtnClick)
                    ONG_COMMAND(ST_CUSTOMTITLE_TAP2, &CIFCustomTitle::On_BtnClickTenTitle)
                    ONG_COMMAND(ST_CUSTOMTITLE_TAP1, &CIFCustomTitle::OnClick_MauTitle)
                    ONG_COMMAND(CUSTOMTITLES2_MUA_LUOT_BTN, &On_BtnClickMuaLuot)

                    ONG_COMMAND(CUSTOMTITLES2_MAUHONG_BTN, &On_BtnClickHong)
                    //ONG_COMMAND(CUSTOMTITLES2_MAUHONG_BTN, &On_ColorBtnClick)
                    //On_ColorBtnClick
                    ONG_COMMAND(CUSTOMTITLES2_MAUTIM_BTN, &On_BtnClickTim)
                    ONG_COMMAND(CUSTOMTITLES2_MAUXANHLAM_BTN, &On_BtnClickXanhLam)
                    ONG_COMMAND(CUSTOMTITLES2_MAUXANHLA_BTN, &On_BtnClickXanhLa)
                    ONG_COMMAND(CUSTOMTITLES2_MAUVANG_BTN, &On_BtnClickVang)
                    ONG_COMMAND(CUSTOMTITLES2_MAUCAM_BTN, &On_BtnClickCam)
                    ONG_COMMAND(CUSTOMTITLES2_MAUDO_BTN, &On_BtnClickDo)
GFX_END_MESSAGE_MAP()


CIFCustomTitle::CIFCustomTitle(void)
{
}

CIFCustomTitle::~CIFCustomTitle(void)
{
}
void CIFCustomTitle::OnColorSelect(D3DCOLOR Color) {
    TitleColor = Color;
    m_custom_label3->m_FontTexture.SetColor(Color);
}
bool CIFCustomTitle::OnCreate(long ln)
{

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT buttRect = { 217,212,111,24 };
    RECT butt2Rect = { 341,212,111,24 };
    RECT butt1Rect = { 90,212,111,24 };
    RECT butt3Rect = { 16,42,89,26 };
    RECT butt4Rect = { 115,42,89,26 };

    RECT butt7Rect = { 30,170,60,22 };
    RECT butt8Rect = { 100,170,60,22 };
    RECT butt9Rect = { 170,170,60,22 };
    RECT butt10Rect = { 240,170,60,22 };
    RECT butt11Rect = { 310,170,60,22 };
    RECT butt12Rect = { 380,170,60,22 };
    RECT butt13Rect = { 450,170,60,22 };
    RECT labRect = { 40,84,485,15 };
    RECT lab2Rect = { 40,106,485,15 };
    RECT lab3Rect = { 40,128,485,15 };

    RECT NormalRect = { 47,172,382,59 };
    RECT FrameRect = { 10,65,520,195 };
    RECT editRect = { 100,170,338,24 };

    m_mybutton = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), buttRect, ST_CUSTOMTITLE_APPLY, 0);
    m_mybutton2 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), butt2Rect, ST_CUSTOMTITLE_CLOSE_BUTTON, 0);
    m_mybutton1 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), butt1Rect, CUSTOMTITLES2_MUA_LUOT_BTN, 0);
    m_mybutton5 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), butt3Rect, ST_CUSTOMTITLE_TAP1, 0);
    m_mybutton6 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), butt4Rect, ST_CUSTOMTITLE_TAP2, 0);

    m_mybutton7 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), butt7Rect, CUSTOMTITLES2_MAUHONG_BTN, 0);
    m_mybutton8 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), butt8Rect, CUSTOMTITLES2_MAUTIM_BTN, 0);
    m_mybutton9 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), butt9Rect, CUSTOMTITLES2_MAUXANHLAM_BTN, 0);
    m_mybutton10 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), butt10Rect, CUSTOMTITLES2_MAUXANHLA_BTN, 0);
    m_mybutton11 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), butt11Rect, CUSTOMTITLES2_MAUVANG_BTN, 0);
    m_mybutton12 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), butt12Rect, CUSTOMTITLES2_MAUCAM_BTN, 0);
    m_mybutton13 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), butt13Rect, CUSTOMTITLES2_MAUDO_BTN, 0);


    m_edit = (CIFEdit*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEdit), editRect, ST_CUSTOMTITLE_NAME_INPUT, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), labRect, ST_CUSTOMTITLE_DESC1, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lab2Rect, ST_CUSTOMTITLE_DESC2, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lab3Rect, ST_CUSTOMTITLE_DESC3, 0);

    m_custom_label6 = (CIFNormalTile*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), NormalRect, ST_CUSTOMTITLE_TITLE_2, 0);
    Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), FrameRect, ST_CUSTOMTITLE_FRAME, 0);


    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
    m_custom_label6->SetGWndSize(Frame->GetSize().width - 20, Frame->GetSize().height - 20);
    m_custom_label6->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);
    m_custom_label6->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);

    m_mybutton->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton2->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton5->TB_Func_13("interface\\ifcommon\\com_long_tab_on.ddj", 0, 0);
    m_mybutton6->TB_Func_13("interface\\ifcommon\\com_long_tab_on.ddj", 0, 0);

    m_mybutton1->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton7->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton8->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton9->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton10->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton11->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton12->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    m_mybutton13->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);

    m_title->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM"));
    m_mybutton->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_APPLY"));
    m_mybutton2->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_MANAGER"));
    m_mybutton1->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_BUY"));
    m_mybutton5->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TITLECOLOR"));
    m_mybutton6->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TITLENAME"));
    m_mybutton7->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_HONG"));
    m_mybutton8->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TIM"));
    m_mybutton9->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_XANHDUONG"));
    m_mybutton10->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_XANHLA"));
    m_mybutton11->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_VANG"));
    m_mybutton12->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_CAM"));
    m_mybutton13->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_DO"));
    m_custom_label2->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TOOLTIP2"));
    m_custom_label3->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TOOLTIP6"));

    std::n_wstring msg(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TOOLTIP"));
    m_edit->SetTooltipText(&msg);
    m_edit->SetToolTipSetting(0x80);
    m_edit->SetMaxStringInput(30);
    m_edit->TB_Func_13("interface\\messagebox\\msgbox_gil_title.ddj", 0, 0);
    //m_edit->SetGWndSize(m_edit->GetSize().width, 28);
    m_edit->N00000608 = this;

    //m_mybutton->MoveGWnd(m_edit->GetPos().x, m_mybutton->GetBounds().pos.y - 60);
    //m_mybutton2->MoveGWnd(m_edit->GetPos().x + m_edit->GetSize().width - m_mybutton2->GetSize().width, m_mybutton2->GetBounds().pos.y - 60);

    m_edit->m_FontTexture.sub_8B4400(1, 0);
    m_edit->m_FontTexture.sub_8B4750(1);
    m_edit->TB_Func_5(1);
    m_edit->TB_Func_6(1);
    m_edit->SetFocus_MAYBE();
    m_custom_label2->m_FontTexture.sub_8B4400(0, 0);
    m_custom_label2->m_FontTexture.sub_8B4750(0);
    m_custom_label2->TB_Func_5(0);
    m_custom_label2->TB_Func_6(0);

    m_custom_label3->m_FontTexture.sub_8B4400(0, 0);
    m_custom_label3->m_FontTexture.sub_8B4750(0);
    m_custom_label3->TB_Func_5(0);
    m_custom_label3->TB_Func_6(0);


    m_custom_label4->m_FontTexture.sub_8B4400(0, 0);
    m_custom_label4->m_FontTexture.sub_8B4750(0);
    m_custom_label4->TB_Func_5(0);
    m_custom_label4->TB_Func_6(0);

    Frame->BringToFront();
    m_custom_label6->BringToFront();
    m_title->BringToFront();
    m_custom_label2->BringToFront();
    m_custom_label3->BringToFront();
    m_custom_label4->BringToFront();
    m_edit->BringToFront();
    m_mybutton->BringToFront();
    m_mybutton1->BringToFront();
    m_mybutton2->BringToFront();
    m_mybutton7->BringToFront();
    m_mybutton8->BringToFront();
    m_mybutton9->BringToFront();
    m_mybutton10->BringToFront();
    m_mybutton11->BringToFront();
    m_mybutton12->BringToFront();
    m_mybutton13->BringToFront();
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    this->ShowGWnd(false);
    ResetPosition();
    return true;
}
int CIFCustomTitle::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}

void CIFCustomTitle::OnUpdate()
{

/*    if (!ColorSelectShow)
        return;

    if (!ImGui::Begin("Color Select", &ColorSelectShow)) {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }
    ImGui::ColorPicker3("Color", m_color, ImGuiColorEditFlags_None);
    int red = static_cast<int>(m_color[0] * 255.0f);
    int green = static_cast<int>(m_color[1] * 255.0f);
    int blue = static_cast<int>(m_color[2] * 255.0f);

    D3DCOLOR TitleColor = D3DCOLOR_ARGB(255, red, green, blue);
    OnColorSelect(TitleColor);
    ImGui::End();*/
}
void CIFCustomTitle::On_BtnClick()
{


    if(tab1)
    {
        std::n_wstring input_text = m_edit->GetNText();

        if(input_text.empty())
        {
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TOOLTIP3"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 255, 0, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);
            return;
        }
        if (m_edit->GetNText().length() > 40)
        {
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TOOLTIP4"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 255, 0, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);
            return;
        }
        if (CGame::GetBadwordFilter()->sub_8C4020(m_edit->GetCurrentText())) {
            g_pCGInterface->WriteSystemMessage(SYSLOG_NONE, TSM_GETTEXTPTR("UIIT_MSG_WHOLECHATERR_NOTINUSEMSG"));
            m_edit->SetText(L"");
            return;
        }
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string(TO_NSTRING(this->m_edit->GetNText()));
            buf << std::n_string("!DOITENTITLE");
            SendMsg(buf);

    } else{
        if(TitleColor == 0 )
        {
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_RQ"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 255, 0, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);
        }
        else{
            D3DCOLOR Colors = m_custom_label3->m_FontTexture.GetFontColor();
            CMsgStreamBuffer buf(0x1318);

            buf << std::n_string("!DOIMAUTITLE");
            buf << std::n_string("!DOIMAUTITLE");
            buf << TitleColor;
            SendMsg(buf);
        }

    }

}
void CIFCustomTitle::On_ColorBtnClick()
{
    CIFCustomTitle::ColorSelectShow = true;
}
void CIFCustomTitle::OnClick_Exit()
{
    if (!CPSMission::Gui_SwitchTitle)
    {
        g_pCGInterface->ShowMessage_Notice(L"Service not available");
        return;
    }
    for(int i =0;i<= g_pCGInterface->GetSwitchTitleGUI()->m_textbox->GetNumberOfItems();i++) {
        g_pCGInterface->GetSwitchTitleGUI()->m_textbox->RemoveLine(i);
    }
    for(int i =0;i<= g_pCGInterface->GetSwitchTitleGUI()->m_textbox->GetNumberOfItems();i++) {
        g_pCGInterface->GetSwitchTitleGUI()->m_textbox->RemoveLine(i);
    }
    for(int i =0;i<= g_pCGInterface->GetSwitchTitleGUI()->m_textbox->GetNumberOfItems();i++) {
        g_pCGInterface->GetSwitchTitleGUI()->m_textbox->RemoveLine(i);
    }
    for(int i =0;i<= g_pCGInterface->GetSwitchTitleGUI()->m_textbox->GetNumberOfItems();i++) {
        g_pCGInterface->GetSwitchTitleGUI()->m_textbox->RemoveLine(i);
    }
    for(int i =0;i<= g_pCGInterface->GetSwitchTitleGUI()->m_textbox->GetNumberOfItems();i++) {
        g_pCGInterface->GetSwitchTitleGUI()->m_textbox->RemoveLine(i);
    }
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!TitleUpdate");
    buf << std::n_string("!TitleUpdate");
    SendMsg(buf);
    g_pCGInterface->GetSwitchTitleGUI()->ResetPosition();
    g_pCGInterface->GetSwitchTitleGUI()->BringToFront();
    g_pCGInterface->GetSwitchTitleGUI()->ShowGWnd(true);
}

void CIFCustomTitle::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}
void CIFCustomTitle::OnClick_MauTitle()
{

    CIFCustomTitle::ColorSelectShow = true;
    tab1= false;
    m_mybutton5->TB_Func_13("interface\\ifcommon\\com_long_tab_on.ddj", 0, 0);
    m_mybutton6->TB_Func_13("interface\\ifcommon\\com_long_tab_off.ddj", 0, 0);
    wchar_t buffer1[80];
    swprintf_s(buffer1, TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TOOLTIP8"));
    m_custom_label2->SetText(buffer1);
    wchar_t buffer2[80];
    swprintf_s(buffer2, TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TOOLTIP9"));
    m_custom_label3->SetText(buffer2);
    //wchar_t buffer3[80];
    //swprintf_s(buffer3, TSM_GETTEXTPTR("ELECTUSCUSTOMTITLE_TOOLTIP3"));
    // m_custom_label4->SetText(buffer3);
    m_edit->ShowGWnd(false);

    m_mybutton7->ShowGWnd(false);
    m_mybutton8->ShowGWnd(false);
    m_mybutton9->ShowGWnd(false);
    m_mybutton10->ShowGWnd(false);
    m_mybutton11->ShowGWnd(false);
    m_mybutton12->ShowGWnd(false);
    m_mybutton13->ShowGWnd(false);
    m_mybutton7->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_HONG"));
    m_mybutton8->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TIM"));
    m_mybutton9->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_XANHDUONG"));
    m_mybutton10->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_XANHLA"));
    m_mybutton11->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_VANG"));
    m_mybutton12->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_CAM"));
    m_mybutton13->SetText(TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_DO"));
}
void CIFCustomTitle::On_BtnClickTenTitle()
{

    CIFCustomTitle::ColorSelectShow = false;
    m_custom_label3->m_FontTexture.SetColor(D3DCOLOR_RGBA(255, 0, 0, 255)); //#FF0000
    tab1= true;
    m_mybutton5->TB_Func_13("interface\\ifcommon\\com_long_tab_off.ddj", 0, 0);
    m_mybutton6->TB_Func_13("interface\\ifcommon\\com_long_tab_on.ddj", 0, 0);
    wchar_t buffer1[80];
    swprintf_s(buffer1, TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TOOLTIP7"));
    m_custom_label2->SetText(buffer1);
    wchar_t buffer2[80];
    swprintf_s(buffer2, TSM_GETTEXTPTR("UIIT_ST_TITLE_CUSTOM_TOOLTIP6"));
    m_custom_label3->SetText(buffer2);
    // wchar_t buffer3[80];
    // swprintf_s(buffer3, TSM_GETTEXTPTR("ELECTUSCUSTOMTITLE_TOOLTIP3"));
    // m_custom_label4->SetText(buffer3);
    m_edit->ShowGWnd(true);
    m_edit->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_d.ddj", 0, 0);
    m_mybutton7->ShowGWnd(false);
    m_mybutton8->ShowGWnd(false);
    m_mybutton9->ShowGWnd(false);
    m_mybutton10->ShowGWnd(false);
    m_mybutton11->ShowGWnd(false);
    m_mybutton12->ShowGWnd(false);
    m_mybutton13->ShowGWnd(false);
}
void CIFCustomTitle::On_BtnClickHong()
{
    //ColorSelectShow = true;
    m_custom_label3->m_FontTexture.SetColor(D3DCOLOR_RGBA(241, 39, 201, 255)); //#F127C9
    TitleColor=4294508776;
}
void CIFCustomTitle::On_BtnClickTim()
{
    m_custom_label3->m_FontTexture.SetColor(D3DCOLOR_RGBA(124, 0, 255, 255)); //#7C00FF
    TitleColor=4285792505;
}
void CIFCustomTitle::On_BtnClickXanhLam()
{
    m_custom_label3->m_FontTexture.SetColor(D3DCOLOR_RGBA(0, 189, 255, 255)); //#00BDFF
    TitleColor=4278232825;
}
void CIFCustomTitle::On_BtnClickXanhLa()
{
    m_custom_label3->m_FontTexture.SetColor(D3DCOLOR_RGBA(0, 255, 16, 255)); //#00FF10
    TitleColor=4281465088;
}
void CIFCustomTitle::On_BtnClickVang()
{
    m_custom_label3->m_FontTexture.SetColor(D3DCOLOR_RGBA(255, 225, 0, 255)); //#FFE100
    TitleColor=4293787392;
}
void CIFCustomTitle::On_BtnClickCam()
{
    m_custom_label3->m_FontTexture.SetColor(D3DCOLOR_RGBA(255, 124, 0, 255)); //#FF7C00
    TitleColor=4294932224;
}
void CIFCustomTitle::On_BtnClickDo()
{
    m_custom_label3->m_FontTexture.SetColor(D3DCOLOR_RGBA(255, 0, 0, 255)); //#FF0000
    TitleColor=4294508544;
}
void CIFCustomTitle::On_BtnClickMuaLuot()
{

    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!MUAINFO");
    buf << std::n_string("!MUAINFO");
    SendMsg(buf);
    g_pCGInterface->GetConfirmGUI()->ResetPosition();
    g_pCGInterface->GetConfirmGUI()->BringToFront();
    g_pCGInterface->GetConfirmGUI()->ShowGWnd(true);

}
