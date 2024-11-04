#include "IFSTLotteryEvent.h"
#include "IFNormalTile.h"
#include <ctime>
#include <sstream>
#include "ClientNet/MsgStreamBuffer.h"
#include "Game.h"
#include <BSLib/multibyte.h>
#include <GInterface.h>

#define GDR_FLORIAN0_RT_LABEL 10
#define GDR_FLORIAN0_RT_BTN 11
#define GDR_FLORIAN0_RT_EDIT 12
#define GDR_FLORIAN0_RT_LABEL_TIME 13
#define GDR_FLORIAN0_RT_MAIN_FRAME 20
#define GDR_FLORIAN0_RT_BTN2 40
GFX_IMPLEMENT_DYNCREATE(CIFSTLotteryEvent, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTLotteryEvent, CIFMainFrame)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN, &On_BtnClickGold)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN2, &On_BtnClickSilk)

GFX_END_MESSAGE_MAP()


CIFSTLotteryEvent::CIFSTLotteryEvent() :
        m_custom_label(NULL) {

}

bool CIFSTLotteryEvent::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);

    // Set own title
    SetText(L"florian0 runtime window");

    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);

    wnd_size sz = this->GetSize();

    RECT rect_frames = {10, 40, sz.width - 20, sz.height - 50};

    RECT rect_background = {rect_frames.left + 10,
                            rect_frames.top + 10,
                            rect_frames.right - 20,
                            rect_frames.bottom - 20};

    CIFNormalTile *tile = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background,
                                                           GDR_FLORIAN0_RT_MAIN_FRAME,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);

    RECT rect_frame = {10, 40, 263, 60};

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame,
                                                  GDR_FLORIAN0_RT_MAIN_FRAME,
                                                  1);
    frame->TB_Func_13("interface\\frame\\frame_sub_", 1, 0);

    RECT rect_frame1 = {10, 101, 263, 160};

    CIFFrame *frame1 = (CIFFrame *) CreateInstance(this,
                                                   GFX_RUNTIME_CLASS(CIFFrame),
                                                   rect_frame1,
                                                   GDR_FLORIAN0_RT_MAIN_FRAME,
                                                   1);
    frame1->TB_Func_13("interface\\frame\\frame_sub_", 1, 0);
    RECT rect_background1 = {rect_frame1.left + 8,
                             rect_frame1.top + 8,
                             rect_frame1.right - 16,
                             rect_frame1.bottom - 16};

    CIFNormalTile *tile1 = (CIFNormalTile *) CreateInstance(this,
                                                            GFX_RUNTIME_CLASS(CIFNormalTile),
                                                            rect_background1,
                                                            GDR_FLORIAN0_RT_MAIN_FRAME,
                                                            1);
    tile1->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);



    RECT rect_frame3 = {10, 262, 263, 64};

    CIFFrame *frame3 = (CIFFrame *) CreateInstance(this,
                                                   GFX_RUNTIME_CLASS(CIFFrame),
                                                   rect_frame3,
                                                   GDR_FLORIAN0_RT_MAIN_FRAME,
                                                   1);
    frame3->TB_Func_13("interface\\frame\\frame_sub_", 1, 0);
    RECT rect_background3 = {rect_frame3.left + 8,
                             rect_frame3.top + 8,
                             rect_frame3.right - 16,
                             rect_frame3.bottom - 16};

    CIFNormalTile *tile3 = (CIFNormalTile *) CreateInstance(this,
                                                            GFX_RUNTIME_CLASS(CIFNormalTile),
                                                            rect_background3,
                                                            GDR_FLORIAN0_RT_MAIN_FRAME,
                                                            1);
    tile3->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);


    RECT rect_custom_label = {0, 132, 284, 121};
    m_custom_label = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label,GDR_FLORIAN0_RT_LABEL,1);
    m_custom_label->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\lottery.ddj",1,0);

    RECT rect_custom_label1 = {18, 114, 76, 13};
    m_custom_label1 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label1,21,1);
    m_custom_label1->SetText(TSM_GETTEXTPTR("UIIT_STT_LOTTERY_SILK_REG"));
    RECT rect_custom_label2 =  {187, 114, 76, 13};
    m_custom_label2 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label2,22,1);
    m_custom_label2->SetText(TSM_GETTEXTPTR("UIIT_STT_LOTTERY_GOLD_REG"));
    RECT rect_custom_label3 =  {18, 140, 76, 13};
    m_custom_label3 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label3,23,1);
    m_custom_label3->SetText(L"25645");
    RECT rect_custom_label4 =  {187, 140, 76, 13};
    m_custom_label4 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label4,24,1);
    m_custom_label4->SetText(L"222222222");

    RECT rect_custom_label5 =  {37, 55, 76, 13};
    m_custom_label5 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label5,25,1);
    m_custom_label5->SetText(TSM_GETTEXTPTR("UIIT_STT_LOTTERY_INPUT"));

    //////
    RECT rect_custom_label6 =  {138, 55, 105, 18};
    m_edit = (CIFEdit *) (CIFEdit *) CreateInstance(this,GFX_RUNTIME_CLASS(CIFEdit),rect_custom_label6,GDR_FLORIAN0_RT_EDIT,1);
    RECT rect_m_edit_frame =  {rect_custom_label6.left -2,
                               rect_custom_label6.top -2,
                               rect_custom_label6.right +4,
                               rect_custom_label6.bottom +4};
    CIFFrame *frame_m_edit = (CIFFrame *) CreateInstance(this,GFX_RUNTIME_CLASS(CIFFrame),rect_m_edit_frame,28,1);
    frame_m_edit->TB_Func_13("interface\\frame\\ub_pet_wnd_", 1, 0);
    RECT rect_background_m_edit = {rect_m_edit_frame.left + 2,
                                   rect_m_edit_frame.top + 2,
                                   rect_m_edit_frame.right - 4,
                                   rect_m_edit_frame.bottom - 4};
    CIFNormalTile *tile_m_edit = (CIFNormalTile *) CreateInstance(this,GFX_RUNTIME_CLASS(CIFNormalTile),rect_background_m_edit,29,1);
    tile_m_edit->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_d.ddj", 1, 0);

    //////
    RECT rect_custom_label7 =  {37, 80, 76, 13};
    m_custom_label7 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label7,26,1);
    m_custom_label7->SetText(TSM_GETTEXTPTR("UIIT_STT_LOTTERY_TOTAL_PLAYER_REG"));
    RECT rect_custom_label8 =  {150, 80, 60, 13};
    m_custom_label8 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label8,27,1);
    m_custom_label8->SetText(L"212");

    RECT rect_custom_label9 =  {43, 272, 128, 13};
    m_custom_label9 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label9,26,1);
    m_custom_label9->SetText(TSM_GETTEXTPTR("UIIT_STT_LOTTERY_TIME"));
    RECT rect_custom_label10 =  {186, 272, 58, 13};
    m_custom_label10 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label10,27,1);
    m_custom_label10->SetText(L"12:00");

    RECT rect_label_time = {44,99,213,160};
    m_time_label = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_label_time,GDR_FLORIAN0_RT_LABEL_TIME,1);
    m_time_label->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\electussilklottery_chest.ddj",1,0);

    RECT rect_button = {47, 295, 70, 22};
    CIFButton *btn = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button,GDR_FLORIAN0_RT_BTN,1);

    btn->SetText(L"Gold");
    btn->TB_Func_13("interface\\system\\sys_button.ddj", 1, 1);

    RECT rect_button2 = {168, 295, 70, 22};
    CIFButton *btn2 = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button2,GDR_FLORIAN0_RT_BTN2,1);

    btn2->SetText(L"Silk");
    btn2->TB_Func_13("interface\\system\\sys_button.ddj", 1, 1);

    m_edit->BringToFront();
    m_edit->SetMaxStringInput(7);
    m_edit->TB_Func_5(1);
    m_edit->SetFocus_MAYBE();
    ResetPosition();
    this->ShowGWnd(false);
    return true;
}


void CIFSTLotteryEvent::On_BtnClickGold() {
    std::n_wstring input_text1 = m_edit->GetNText();
    if(input_text1.empty())
    {
        wchar_t message[1000];
        swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_RQ"));
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 255, 0, 0);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    }
    else
    {
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string(TO_NSTRING(this->m_edit->GetNText()));
    buf << std::n_string("!eventlotterygold");
    SendMsg(buf);
    }

}
void CIFSTLotteryEvent::On_BtnClickSilk() {
    std::n_wstring input_text1 = m_edit->GetNText();
    if(input_text1.empty())
    {
        wchar_t message[1000];
        swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_RQ"));
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 255, 0, 0);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    }
    else
    {
        CMsgStreamBuffer buf(0x1318);
        buf << std::n_string(TO_NSTRING(this->m_edit->GetNText()));
        buf << std::n_string("!eventlotterysilk");
        SendMsg(buf);
    }

}
void CIFSTLotteryEvent::OnUpdate() {
/*    SYSTEMTIME time;
    GetSystemTime(&time);
    double ms = time.wMilliseconds;
    loop = ms/6.25;
    loopcheck = 0;

        if (loopcheck != loop )
        {
            loopcheck = loop;
            std::ostringstream temp;
            img = loop + 1;
            temp << img;
            std::string imgpath = "interface\\ifcommon\\thaidu0ngpr0\\electussilklottery_chest_" + temp.str() + ".ddj";
            m_time_label->TB_Func_13(imgpath, 0, 0);
        }*/
}
void CIFSTLotteryEvent::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}