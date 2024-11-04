#include "IFSTEventRegister.h"
#include "IFNormalTile.h"
#include <ctime>
#include "ClientNet/MsgStreamBuffer.h"
#include "IFSTTaiXiu.h"
#include "IFflorian0Guide.h"
#include "Game.h"
#include <BSLib/multibyte.h>
#include <GInterface.h>

#define GDR_FLORIAN0_RT_LABEL 10
#define GDR_FLORIAN0_RT_BTN 11
#define GDR_FLORIAN0_RT_BTN2 12
#define GDR_FLORIAN0_RT_LABEL_TIME 13
#define GDR_FLORIAN0_RT_MAIN_FRAME 20


std::vector<CIFSTEventRegister::Event> CIFSTEventRegister::EventList;

GFX_IMPLEMENT_DYNCREATE(CIFSTEventRegister, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTEventRegister, CIFMainFrame)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN, &On_BtnClick)
                    ONG_COMMAND(GDR_FLORIAN0_RT_BTN2, &On_BtnClick2)
GFX_END_MESSAGE_MAP()


CIFSTEventRegister::CIFSTEventRegister() :
        m_custom_label(NULL) {

}

bool CIFSTEventRegister::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);

    // Set own title
    RECT rect_m_tile = {42, 12, 186, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,GDR_FLORIAN0_RT_LABEL,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIT_STT_EVENTREG_TILE"));

    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);


    RECT rect_frame = {10, 40, 250, 278};

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


    RECT rect_custom_label = {50, 50, 60, 20};
    m_custom_label = (CIFStatic *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFStatic),
                                                         rect_custom_label,
                                                         GDR_FLORIAN0_RT_LABEL,
                                                         1);


    RECT rect_label_time = {50, 70, 60, 20};
    m_time_label = (CIFStatic *) CGWnd::CreateInstance(this,
                                                       GFX_RUNTIME_CLASS(CIFStatic),
                                                       rect_label_time,
                                                       GDR_FLORIAN0_RT_LABEL_TIME,
                                                       1);

    RECT rect_button = {40, 280, 80, 24};
    CIFButton *btn = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button,
                                                         GDR_FLORIAN0_RT_BTN,
                                                         1);

    btn->SetText(TSM_GETTEXTPTR("UIIT_STT_EVENTREG_REG"));
    btn->TB_Func_13("interface\\system\\sys_button.ddj", 1, 1);

    RECT rect_button1 = {155, 280, 80, 24};
    CIFButton *btn1 = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button1,
                                                         GDR_FLORIAN0_RT_BTN2,
                                                         1);

    btn1->SetText(TSM_GETTEXTPTR("UIIT_STT_EVENTREG_CANCEL"));

    btn1->TB_Func_13("interface\\system\\sys_button.ddj", 1, 1);


    RECT rect = { 20,50,225,169 };
    Slot1 = (CIFSTEventRegisterSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventRegisterSlotList), rect, 40, 0);
    Slot2 = (CIFSTEventRegisterSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventRegisterSlotList), rect, 41, 0);
    Slot3 = (CIFSTEventRegisterSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventRegisterSlotList), rect, 42, 0);
    Slot4 = (CIFSTEventRegisterSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventRegisterSlotList), rect, 43, 0);
 /*   Slot1->Line1->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG1_NAME"));
    Slot1->Line2->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG2_NAME"));
    Slot1->Line3->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG3_NAME"));
    Slot1->Line4->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG4_NAME"));
    Slot1->Line5->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG5_NAME"));
    Slot1->Line6->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG6_NAME"));
    Slot1->Line7->WriteLine(TSM_GETTEXTPTR("UIIT_STT_EVENTREG7_NAME"));*/
    Slot1->ShowGWnd(true);
    Slot2->ShowGWnd(false);
    Slot3->ShowGWnd(false);
    Slot4->ShowGWnd(false);
    this->ShowGWnd(false);

    return true;
}


void CIFSTEventRegister::On_BtnClick() {
    if (!SelectedItemName.empty())
    {
        printf("%S",SelectedItemName.c_str());
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG1_NAME")) == 0)
        {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!TAIXIUUP");
            buf << std::n_string("!TAIXIUUP");
            SendMsg(buf);
            g_pCGInterface->m_IRM.GetResObj(5092, 1)->ShowGWnd(true);
            CIFSTTaiXiu* main10 = g_pCGInterface->m_IRM.GetResObj<CIFSTTaiXiu>(5092, 1);
            main10->gold = false;
            main10->silk = true;
            main10->gilf=false;
            main10->m_mybutton11 ->TB_Func_13("interface\\ifcommon\\ngt\\checkbutton_on.ddj", 0, 0);
            main10->m_mybutton10 ->TB_Func_13("interface\\ifcommon\\ngt\\checkbutton_off.ddj", 0, 0);
        }
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG5_NAME")) == 0)
        {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!dangkyeventdautruong");
            buf << std::n_string("!dangkyevent");
            SendMsg(buf);
        }
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG6_NAME")) == 0)
        {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!dangkyeventdrunk");
            buf << std::n_string("!dangkyevent");
            SendMsg(buf);
        }
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG7_NAME")) == 0)
        {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!dangkyeventbattleroyale");
            buf << std::n_string("!dangkyevent");
            SendMsg(buf);
        }
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG2_NAME")) == 0)
        {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!lotteryupdate");
            buf << std::n_string("!lotteryupdate");
            g_pCGInterface->GetEventLotteryGUI()->m_edit->SetText(L"");
            g_pCGInterface->GetEventLotteryGUI()->m_edit->SetFocus_MAYBE();
            g_pCGInterface->GetEventLotteryGUI()->ResetPosition();
            g_pCGInterface->GetEventLotteryGUI()->ShowGWnd(true);
            SendMsg(buf);
        }
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG3_NAME")) == 0)
        {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!dangkyeventbossjob");
            buf << std::n_string("!dangkyevent");
            SendMsg(buf);
        }
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG4_NAME")) == 0)
        {
            g_pCGInterface->GetEventXoSoGUI()-> m_mybutton7 ->TB_Func_13("interface\\ifcommon\\ngt\\checkbutton_on.ddj", 0, 0);
            g_pCGInterface->GetEventXoSoGUI()-> m_mybutton8 ->TB_Func_13("interface\\ifcommon\\ngt\\checkbutton_off.ddj", 0, 0);
            g_pCGInterface->GetEventXoSoGUI()-> m_mybutton9 ->TB_Func_13("interface\\ifcommon\\ngt\\checkbutton_off.ddj", 0, 0);
            g_pCGInterface->GetEventXoSoGUI()-> gold = true;
            g_pCGInterface->GetEventXoSoGUI()-> silk = false;
            g_pCGInterface->GetEventXoSoGUI()-> gilf = false;
            g_pCGInterface->GetEventXoSoGUI()-> m_edit->SetText(L"");
            g_pCGInterface->GetEventXoSoGUI()-> m_edit1->SetText(L"");
            g_pCGInterface->GetEventXoSoGUI()-> m_edit->SetFocus_MAYBE();
            g_pCGInterface->GetEventXoSoGUI()-> silk = false;
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!XSMBKQ");
            buf << std::n_string("!XSMBKQ");
            SendMsg(buf);
            g_pCGInterface->GetEventXoSoGUI()->ResetPosition();
            g_pCGInterface->GetEventXoSoGUI()->ShowGWnd(true);
        }


    }
    else
    {
        g_pCGInterface->ShowMessage_Warning(L"please select event first");
        return;
    }
}
void CIFSTEventRegister::On_BtnClick2() {
    if (!SelectedItemName.empty())
    {
         if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG1_NAME")) == 0)
        {
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_EVENTREG_CANT_CANCEL"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 255, 0, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);
        }
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG2_NAME")) == 0)
        {
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_EVENTREG_CANT_CANCEL"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 255, 0, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);
        }
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG4_NAME")) == 0)
        {
            wchar_t message[1000];
            swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_EVENTREG_CANT_CANCEL"));
            CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
            int color = D3DCOLOR_ARGB(255, 255, 0, 0);
            systemmessage->WriteMessage(0xFF, color, message, 0, 1);
        }
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG5_NAME")) == 0)
        {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!huyeventdautruong");
            buf << std::n_string("!dangkyevent");
            SendMsg(buf);
        }
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG6_NAME")) == 0)
        {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!huyeventdrunk");
            buf << std::n_string("!dangkyevent");
            SendMsg(buf);
        }
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG7_NAME")) == 0)
        {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!huyeventbattleroyale");
            buf << std::n_string("!dangkyevent");
            SendMsg(buf);
        }
        if(wcscmp(SelectedItemName.c_str(), TSM_GETTEXTPTR("UIIT_STT_EVENTREG3_NAME")) == 0)
        {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!huyeventbossjob");
            buf << std::n_string("!dangkyevent");
            SendMsg(buf);
        }


    }
    else
    {
        g_pCGInterface->ShowMessage_Warning(L"please select event first");
        return;
    }
}
void CIFSTEventRegister::OnUpdate() {
    time_t rawtime;
    struct tm *timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);

}
void CIFSTEventRegister::ClearDDJ() {
    Slot1->ClearDDJ();
    Slot2->ClearDDJ();
    Slot3->ClearDDJ();
    Slot4->ClearDDJ();

}
void CIFSTEventRegister::UpdateLog()
{
    for (std::vector<CIFSTEventRegister::Event>::iterator it = CIFSTEventRegister::EventList.begin(); it != CIFSTEventRegister::EventList.end(); ++it)
    {
        switch ((*it).LineNum)
        {
            case 1:
            {
                Slot1->Line1->WriteLine((*it).EventName.c_str());
            }
                break;
            case 2:
            {
                Slot1->Line2->WriteLine((*it).EventName.c_str());
            }
                break;
            case 3:
            {
                Slot1->Line3->WriteLine((*it).EventName.c_str());
            }
                break;
            case 4:
            {
                Slot1->Line4->WriteLine((*it).EventName.c_str() );
            }
                break;
            case 5:
            {
                Slot1->Line5->WriteLine((*it).EventName.c_str());
            }
                break;
            case 6:
            {
                Slot1->Line6->WriteLine((*it).EventName.c_str());
            }
                break;
            case 7:
            {
                Slot1->Line7->WriteLine((*it).EventName.c_str());
            }
                break;

        }
    }
}
void CIFSTEventRegister::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}
