#include "IFSTCharLock.h"
#include "IFNormalTile.h"
#include <ctime>
#include "GInterface.h"
#include <BSLib\multibyte.h>
#define GDR_CHARLOCK_RT_LABEL 10
#define GDR_CHARLOCK_RT_BTN_LOCK 11
#define GDR_CHARLOCK_RT_BTN_REMOVELOCK 12
#define GDR_CHARLOCK_RT_MAIN_FRAME 20
#define GDR_CHARLOCK_RT_EDIT1 21
#define GDR_CHARLOCK_RT_EDIT2 22
#define GDR_CHARLOCK_RT_PASSWORD_INPUT_LABLE 22
#define GDR_CHARLOCK_RT_PASSWORD_REMOVE_LABLE 22
#define GDR_CHARLOCK_RT_LOCK_STATUS_LABLE 23
#define GDR_CHARLOCK_RT_LOCK_STATUS_ICON 24
#define GDR_CHARLOCK_RT_LOCK_STATUS 25
#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)
#define CLIENT_SCREEN_HEIGHT (*(int*)0x00ED7CBC)
GFX_IMPLEMENT_DYNCREATE(CIFSTCharLock, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTCharLock, CIFMainFrame)
                    ONG_COMMAND(GDR_CHARLOCK_RT_BTN_LOCK, &On_BtnClickLockUnLock)
                    ONG_COMMAND(GDR_CHARLOCK_RT_BTN_REMOVELOCK, &On_BtnClickNewLock)
GFX_END_MESSAGE_MAP()


CIFSTCharLock::CIFSTCharLock() :
        m_custom_label(NULL) {

}

bool CIFSTCharLock::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);
    ///////// main frame
    // Set own title
    //SetText(L"florian0 runtime window");

    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);


    RECT rect_frame = {11, 38, 189, 33};

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame,
                                                  GDR_CHARLOCK_RT_MAIN_FRAME,
                                                  1);
    frame->TB_Func_13("interface\\frame\\frame_sub_", 1, 0);

    RECT rect_frame1 = {11, 71, 189, 98};

    CIFFrame *frame1 = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame1,
                                                  GDR_CHARLOCK_RT_MAIN_FRAME,
                                                  1);
    frame1->TB_Func_13("interface\\frame\\frame_sub_", 1, 0);
    RECT rect_background1 = {rect_frame1.left + 8,
                             rect_frame1.top + 8,
                             rect_frame1.right - 16,
                             rect_frame1.bottom - 16};

    CIFNormalTile *tile1 = (CIFNormalTile *) CreateInstance(this,
                                                            GFX_RUNTIME_CLASS(CIFNormalTile),
                                                            rect_background1,
                                                            GDR_CHARLOCK_RT_MAIN_FRAME,
                                                            1);
    tile1->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);



    RECT rect_frame3 = {11, 169, 189, 98};

    CIFFrame *frame3 = (CIFFrame *) CreateInstance(this,
                                                   GFX_RUNTIME_CLASS(CIFFrame),
                                                   rect_frame3,
                                                   GDR_CHARLOCK_RT_MAIN_FRAME,
                                                   1);
    frame3->TB_Func_13("interface\\frame\\frame_sub_", 1, 0);
    RECT rect_background3 = {rect_frame3.left + 8,
                             rect_frame3.top + 8,
                             rect_frame3.right - 16,
                             rect_frame3.bottom - 16};

    CIFNormalTile *tile3 = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background3,
                                                            GDR_CHARLOCK_RT_MAIN_FRAME,
                                                           1);
    tile3->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);

   // interface\\ifcommon\\com_grad_gage_form.ddj



    ///////// m_edit1
    RECT rect_m_edit = {21,103,169,23};
    m_edit1 = (CIFEdit *) (CIFEdit *) CreateInstance(this,
                                                    GFX_RUNTIME_CLASS(CIFEdit),
                                                    rect_m_edit,
                                                     GDR_CHARLOCK_RT_EDIT1,
                                                    1);
    m_edit1->BringToFront();
    m_edit1->TB_Func_5(1);
    m_edit1->SetFocus_MAYBE();
   // m_edit1->SetStyleThingy(PASSWORD_MASKED);
    RECT rect_m_edit_frame =  {rect_m_edit.left -2,
                               rect_m_edit.top -2,
                               rect_m_edit.right +4,
                               rect_m_edit.bottom +4};
    CIFFrame *frame_m_edit = (CIFFrame *) CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFFrame),
                                                         rect_m_edit_frame,
                                                         GDR_CHARLOCK_RT_MAIN_FRAME,
                                                         1);
    frame_m_edit->TB_Func_13("interface\\frame\\ub_pet_wnd_", 1, 0);

    RECT rect_background_m_edit = {rect_m_edit_frame.left + 2,
                                   rect_m_edit_frame.top + 2,
                                   rect_m_edit_frame.right - 4,
                                   rect_m_edit_frame.bottom - 4};

    CIFNormalTile *tile_m_edit = (CIFNormalTile *) CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFNormalTile),
                                                                  rect_background_m_edit,
                                                                  GDR_CHARLOCK_RT_MAIN_FRAME,
                                                                  1);
    tile_m_edit->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_d.ddj", 1, 0);
    ///////// m_edit2
    RECT rect_m_edit2 = {21,198,169,23};
    m_edit2 = (CIFEdit *) (CIFEdit *) CreateInstance(this,
                                                     GFX_RUNTIME_CLASS(CIFEdit),
                                                     rect_m_edit2,
                                                     GDR_CHARLOCK_RT_EDIT2,
                                                     1);
    m_edit2->BringToFront();
    m_edit2->TB_Func_5(1);
    //m_edit2->SetStyleThingy(PASSWORD_MASKED);
    RECT rect_m_edit_frame2 =  {rect_m_edit2.left -2,
                               rect_m_edit2.top -2,
                               rect_m_edit2.right +4,
                               rect_m_edit2.bottom +4};
    CIFFrame *frame_m_edit2 = (CIFFrame *) CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFFrame),
                                                         rect_m_edit_frame2,
                                                         GDR_CHARLOCK_RT_MAIN_FRAME,
                                                         1);
    frame_m_edit2->TB_Func_13("interface\\frame\\ub_pet_wnd_", 1, 0);

    RECT rect_background_m_edit2 = {rect_m_edit_frame2.left + 2,
                                   rect_m_edit_frame2.top + 2,
                                   rect_m_edit_frame2.right - 4,
                                   rect_m_edit_frame2.bottom - 4};

    CIFNormalTile *tile_m_edit2 = (CIFNormalTile *) CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFNormalTile),
                                                                  rect_background_m_edit2,
                                                                  GDR_CHARLOCK_RT_MAIN_FRAME,
                                                                  1);
    tile_m_edit2->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_d.ddj", 1, 0);

//////// button1
    RECT rect_button = {67, 138, 76, 22};
    m_button_lock = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button,
                                                         GDR_CHARLOCK_RT_BTN_LOCK,
                                                         1);

    m_button_lock->SetText(L"Click me");
    m_button_lock->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);
//////// button2
    RECT rect_button2 = {67, 236, 76, 22};
    m_button_remove_lock = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button2,
                                                          GDR_CHARLOCK_RT_BTN_REMOVELOCK,
                                                         1);


    m_button_remove_lock->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);
    /////////// password input lable
    RECT rect_m_password_input_lable = { 30,82,148,15 };
    m_password_input_lable = (CIFStatic *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFStatic),
                                                                 rect_m_password_input_lable,
                                                                 GDR_CHARLOCK_RT_PASSWORD_INPUT_LABLE,
                                                        1);
    /////////// password remove lable
    RECT rect_m_password_remove_lable = { 30,178,148,15 };
    m_password_remove_lable = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                 GFX_RUNTIME_CLASS(CIFStatic),
                                                                  rect_m_password_remove_lable,
                                                                 GDR_CHARLOCK_RT_PASSWORD_REMOVE_LABLE,
                                                                 1);
    /////////// lock status lable
    RECT rect_m_lock_status_lable = { 30,40,99,34 };
    m_lock_status_lable = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFStatic),
                                                                  rect_m_lock_status_lable,
                                                                  GDR_CHARLOCK_RT_LOCK_STATUS_LABLE,
                                                                  1);
    ///////////  lock status icon
    RECT rect_m_lock_status_icon = { 100,45,20,19 };
    m_lock_status_icon = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFStatic),
                                                             rect_m_lock_status_icon,
                                                             GDR_CHARLOCK_RT_LOCK_STATUS_ICON,
                                                                  1);
    /////////// password remove lable
    RECT rect_m_lock_status = { 130,40,143,34 };
    m_lock_status = (CIFStatic *) CGWnd::CreateInstance(this,
                                                                  GFX_RUNTIME_CLASS(CIFStatic),
                                                        rect_m_lock_status,
                                                        GDR_CHARLOCK_RT_LOCK_STATUS,
                                                                  1);
    /////////// m_char_lock_title
    RECT rect_m_char_lock_title = { 40,10,130,15 };
    m_char_lock_title = (CIFStatic *) CGWnd::CreateInstance(this,
                                                        GFX_RUNTIME_CLASS(CIFStatic),
                                                            rect_m_char_lock_title,
                                                            GDR_CHARLOCK_RT_LABEL,
                                                        1);



    wchar_t buffer[80];
    wchar_t buffer1[80];
    wchar_t buffer2[80];
    wchar_t buffer3[80];
    swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_ST_CHARLOCK_PASSWORD_INPUT"));
    swprintf_s(buffer1, TSM_GETTEXTPTR("UIIT_ST_CHARLOCK_PASSWORD_REMOVE"));
    swprintf_s(buffer2, TSM_GETTEXTPTR("UIIT_ST_ITEM_LOCK"));
    swprintf_s(buffer3, TSM_GETTEXTPTR("UIIT_ST_STATUS_REMOVE_BTN"));
    m_password_input_lable->SetText(buffer);
    m_password_remove_lable->SetText(buffer1);
    m_lock_status_lable->TB_Func_5(0);
    m_lock_status->TB_Func_5(0);
    m_lock_status_lable->SetText(L"Status:");
    m_char_lock_title->SetText(buffer2);
    m_button_remove_lock->SetText(buffer3);
    m_edit1 ->SetMaxStringInput(4);
    m_edit1->SetStyleThingy(PASSWORD_MASKED);

    m_edit2 ->SetMaxStringInput(4);
    m_edit2->SetStyleThingy(PASSWORD_MASKED);
    this->ShowGWnd(false);
    return true;
}
int CIFSTCharLock::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}

void CIFSTCharLock::On_BtnClick() {

}
void CIFSTCharLock::On_BtnClickLockUnLock()
{
    std::n_wstring input_text = m_edit1->GetText();
    if(input_text.empty())
    {
        wchar_t message[1000];
        swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_CHARLOCK_TOOLTIP"));


        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 255, 0, 0);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    } else {

        std::n_wstring input_text = m_edit1->GetText();
        CMsgStreamBuffer buf(0x1318);

        buf << std::n_string(TO_NSTRING(input_text));
        buf << std::n_string("!lock");
        SendMsg(buf);
        m_edit1->SetText(L"");
    }
}
void CIFSTCharLock::On_BtnClickNewLock()
{
    std::n_wstring input_text = m_edit2->GetText();
    if(input_text.empty())
    {
        wchar_t message[1000];
        swprintf_s(message, TSM_GETTEXTPTR("UIIT_ST_CHARLOCK_TOOLTIP"));

        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 255, 0, 0);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    } else {
        std::n_wstring input_text = m_edit2->GetText();
        CMsgStreamBuffer buf(0x1318);

        buf << std::n_string(TO_NSTRING(input_text));
        buf << std::n_string("!unlock");
        SendMsg(buf);
        m_edit2->SetText(L"");
    }

}
void CIFSTCharLock::OnUpdate() {
    time_t rawtime;
    struct tm *timeinfo;
    wchar_t buffer[80];
    //m_edit1->OnTextChange();
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);

}
void CIFSTCharLock::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 780;
    this->MoveGWnd(PosX, PosY);
}