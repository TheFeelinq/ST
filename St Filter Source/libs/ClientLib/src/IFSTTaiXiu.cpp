#include "IFSTTaiXiu.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>

#include "GInterface.h"
#include "ClientNet/MsgStreamBuffer.h"
#include "CPSMission.h"
#include "PSQuickStart.h"


#include "unsorted.h"
#include "GlobalHelpersThatHaveNoHomeYet.h"
#include "ClientNet/ClientNet.h"
#include "Game.h"
#include "ICPlayer.h"
#include "IFWnd.h"
#include <BSLib\multibyte.h>
#include "TextStringManager.h"
#include "IFChatViewer.h"
#include "Rebot.h"
#include <IFSystemMessage.h>
#include <sstream>

#define CHONGOLD_LABLE 41
#define CHONGOLD_BUTTON 40
#define CHONGILFSILK_LABLE 39
#define CHONSILK_LABLE 38
#define CHONGILFSILK_BUTTON 37
#define CHONSILK_BUTTON 36

#define KETQUAANH_LABLE 35
#define KETQUA_LABLE 34
#define THELOAIDACHON_LABLE 32
#define TONGTIENCUOCTAI_LABLE 31
#define TONGTIENCUOCXIU_LABLE 30
#define TONGTIENDACUOC_LABLE 29
#define SOICAU_SLOT1 28
#define SOICAU_SLOT2 27
#define SOICAU_SLOT3 26
#define SOICAU_SLOT4 25
#define SOICAU_SLOT5 24
#define SOICAU_SLOT6 23
#define SOICAU_SLOT7 22
#define SOICAU_SLOT8 21
#define SOICAU_SLOT9 20
#define SOICAU_SLOT10 19
#define DATCUOCTAI_BUTTON 18
#define DATCUOCXIU_BUTTON 17
#define XEPHANG_BUTTON 16
#define LICHSU_BUTTON 15
#define DAT1M_BUTTON 14
#define DAT5M_BUTTON 13
#define DAT10M_BUTTON 12
#define DATCUOC_BUTTON 11
#define THOAT_BUTTON 33
#define TAIXIU_FRAME 10
#define TIMER_CHATBLOCK1 500
#define TIMER_CHATBLOCK2 501
std::vector<CIFSTTaiXiu::GifMaker> CIFSTTaiXiu::gifMaker;
GFX_IMPLEMENT_DYNCREATE(CIFSTTaiXiu, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTTaiXiu, CIFMainFrame)
                    ONG_COMMAND(THOAT_BUTTON, &OnClick_Exit)
                    ONG_COMMAND(DATCUOCTAI_BUTTON, &On_BtnClicktai)
                    ONG_COMMAND(DATCUOCXIU_BUTTON, &On_BtnClickxiu)
                    ONG_COMMAND(XEPHANG_BUTTON, &On_BtnClick)
                    ONG_COMMAND(LICHSU_BUTTON, &On_BtnClick)
                    ONG_COMMAND(DAT1M_BUTTON, &On_BtnClick1m)
                    ONG_COMMAND(DAT5M_BUTTON, &On_BtnClick5m)
                    ONG_COMMAND(DAT10M_BUTTON, &On_BtnClick10m)
                    ONG_COMMAND(DATCUOC_BUTTON, &On_BtnClickdatcuoc)
                    ONG_COMMAND(CHONGILFSILK_BUTTON, &On_BtnClickDANHBANGGILFSILK)
                    ONG_COMMAND(CHONSILK_BUTTON, &On_BtnClickDANHBANGSILK)
                    ONG_COMMAND(CHONGOLD_BUTTON, &On_BtnClickDANHBANGGOLD)
GFX_END_MESSAGE_MAP()


CIFSTTaiXiu::CIFSTTaiXiu(void)
{
    printf("> " __FUNCTION__ "\n");
}


CIFSTTaiXiu::~CIFSTTaiXiu(void)
{
    printf("> " __FUNCTION__ "\n");
}
void CIFSTTaiXiu::OnTimer(int timerId) {
    if (timerId == TIMER_CHATBLOCK1) {

        wchar_t buffer[255];
        swprintf_s(buffer, TSM_GETTEXTPTR("TAIXIU_TIMER"), m_ChatBlock_SecondsLeft);
        CIFChatViewer *main12 = g_pCGInterface->m_IRM.GetResObj<CIFChatViewer>(1, 1);
        main12->m_ChatBlockLabel->m_FontTexture.sub_8B4400(5, 1);
        main12->m_ChatBlockLabel->SetText(buffer);
        main12-> m_ChatBlockLabel->ShowGWnd(true);

        std::ostringstream temp;
        temp << m_ChatBlock_SecondsLeft;
        std::string imgpath = "interface\\ifcommon\\thaidu0ngpr0\\num\\num_" + temp.str() + ".ddj";
        std::n_string imgpath1 = std::n_string((imgpath.c_str()));
        m_custom_label29->TB_Func_13(imgpath1, 0, 0);

        if (m_ChatBlock_SecondsLeft > -1) {
            m_ChatBlock_SecondsLeft--;
        } else {
            main12-> m_ChatBlockLabel->ShowGWnd(false);
            this->KillTimer(TIMER_CHATBLOCK1);
        }
    }
    if (timerId == TIMER_CHATBLOCK2) {

        wchar_t buffer[255];
        swprintf_s(buffer, TSM_GETTEXTPTR("TAIXIU_TIMER2"), m_ChatBlock_SecondsLeft1);
        CIFChatViewer *main12 = g_pCGInterface->m_IRM.GetResObj<CIFChatViewer>(1, 1);
        main12->m_ChatBlockLabel->m_FontTexture.sub_8B4400(5, 1);
        main12->m_ChatBlockLabel->SetText(buffer);
        main12-> m_ChatBlockLabel->ShowGWnd(true);

           std::ostringstream temp;
           temp << m_ChatBlock_SecondsLeft1;
           std::string imgpath = "interface\\ifcommon\\thaidu0ngpr0\\" + temp.str() + ".ddj";
            std::n_string imgpath1 = std::n_string((imgpath.c_str()));
           m_custom_label29->TB_Func_13(imgpath1, 0, 0);

        if (m_ChatBlock_SecondsLeft1 > -1) {
            m_ChatBlock_SecondsLeft1--;
        } else {
            main12-> m_ChatBlockLabel->ShowGWnd(false);
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string("!TAIXIUUP");
            buf << std::n_string("!TAIXIUUP");
            SendMsg(buf);

            this->KillTimer(TIMER_CHATBLOCK2);

        }
    }
}
bool CIFSTTaiXiu::OnCreate(long ln)
{
    printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    m_IRM.LoadFromFile("resinfo\\ifsttaixiu.txt");
    m_IRM.CreateInterfaceSection("Create", this);

    m_mybutton = m_IRM.GetResObj<CIFButton>(THOAT_BUTTON, 1);
    m_mybutton3 = m_IRM.GetResObj<CIFButton>(DATCUOCTAI_BUTTON, 1);
    m_mybutton2 = m_IRM.GetResObj<CIFButton>(DATCUOCXIU_BUTTON, 1);
    m_mybutton4 = m_IRM.GetResObj<CIFButton>(XEPHANG_BUTTON, 1);
    m_mybutton5 = m_IRM.GetResObj<CIFButton>(LICHSU_BUTTON, 1);
    m_mybutton6 = m_IRM.GetResObj<CIFButton>(DAT1M_BUTTON, 1);
    m_mybutton7 = m_IRM.GetResObj<CIFButton>(DAT5M_BUTTON, 1);
    m_mybutton8 = m_IRM.GetResObj<CIFButton>(DAT10M_BUTTON, 1);
    m_mybutton9 = m_IRM.GetResObj<CIFButton>(DATCUOC_BUTTON, 1);
    m_mybutton10 = m_IRM.GetResObj<CIFButton>(CHONGILFSILK_BUTTON, 1);
    m_mybutton11 = m_IRM.GetResObj<CIFButton>(CHONSILK_BUTTON, 1);
    m_mybutton12 = m_IRM.GetResObj<CIFButton>(CHONGOLD_BUTTON, 1);

    m_custom_label11 = m_IRM.GetResObj<CIFStatic>(THELOAIDACHON_LABLE, 1);
    m_custom_label12 = m_IRM.GetResObj<CIFStatic>(TONGTIENCUOCTAI_LABLE, 1);
    m_custom_label13 = m_IRM.GetResObj<CIFStatic>(TONGTIENCUOCXIU_LABLE, 1);
    m_custom_label16 = m_IRM.GetResObj<CIFStatic>(TONGTIENDACUOC_LABLE, 1);
    m_custom_label17 = m_IRM.GetResObj<CIFStatic>(SOICAU_SLOT1, 1);
    m_custom_label18 = m_IRM.GetResObj<CIFStatic>(SOICAU_SLOT2, 1);
    m_custom_label19 = m_IRM.GetResObj<CIFStatic>(SOICAU_SLOT3, 1);
    m_custom_label20 = m_IRM.GetResObj<CIFStatic>(SOICAU_SLOT4, 1);
    m_custom_label21 = m_IRM.GetResObj<CIFStatic>(SOICAU_SLOT5, 1);
    m_custom_label22 = m_IRM.GetResObj<CIFStatic>(SOICAU_SLOT6, 1);
    m_custom_label23 = m_IRM.GetResObj<CIFStatic>(SOICAU_SLOT7, 1);
    m_custom_label24 = m_IRM.GetResObj<CIFStatic>(SOICAU_SLOT8, 1);
    m_custom_label25 = m_IRM.GetResObj<CIFStatic>(SOICAU_SLOT9, 1);
    m_custom_label26 = m_IRM.GetResObj<CIFStatic>(SOICAU_SLOT10, 1);
    m_custom_label27 = m_IRM.GetResObj<CIFStatic>(TAIXIU_FRAME, 1);
    m_custom_label28 = m_IRM.GetResObj<CIFStatic>(KETQUA_LABLE, 1);
    m_custom_label29 = m_IRM.GetResObj<CIFStatic>(KETQUAANH_LABLE, 1);
    m_custom_label30 = m_IRM.GetResObj<CIFStatic>(CHONSILK_LABLE, 1);
    m_custom_label31 = m_IRM.GetResObj<CIFStatic>(CHONGILFSILK_LABLE, 1);
    m_custom_label32 = m_IRM.GetResObj<CIFStatic>(CHONGOLD_LABLE, 1);
    this->ShowGWnd(false);


    return true;
}

void CIFSTTaiXiu::OnUpdate()
{

    short ALTState = GetKeyState(VK_MENU);
    if (ALTState == -127 || ALTState == -128) // ALT is hold
    {
        this->OnCloseWnd();
    }

    SYSTEMTIME time;
    GetSystemTime(&time);
    ms =  time.wMilliseconds;

    loop = ms/50;
    loopcheck = 0;

/*       if (show == 1) {
            loopcheck = loop;
            std::ostringstream temp;
            img = loop;
            temp << img;
            std::string imgpath = "interface\\ifcommon\\electus\\" + temp.str() + ".ddj";

            m_custom_label29->TB_Func_13(imgpath, 0, 0);

        }*/


}
void CIFSTTaiXiu::On_BtnClickDANHBANGGOLD()
{
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_SELECT_MONEY_GOLD"));

    CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 213, 197, 136);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    m_mybutton12 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_on.ddj", 0, 0);
    m_mybutton11 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    m_mybutton10 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    this->gold = true;
    this->silk = false;
    this->gilf=false;

}
void CIFSTTaiXiu::On_BtnClickDANHBANGSILK()
{
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_SELECT_MONEY_SILK"));

    CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 213, 197, 136);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    m_mybutton12 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    m_mybutton11 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_on.ddj", 0, 0);
    m_mybutton10 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    this->gold = false;
    this->silk = true;
    this->gilf=false;

}
void CIFSTTaiXiu::On_BtnClickDANHBANGGILFSILK()
{
    wchar_t message[1000];
    swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_SELECT_MONEY_GIFTSILK"));


    CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 213, 197, 136);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    m_mybutton12 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    m_mybutton11->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);
    m_mybutton10 ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_on.ddj", 0, 0);
    this->gold = false;
    this->silk = false;
    this->gilf=true;
}
void CIFSTTaiXiu::On_BtnClick()
{


    wchar_t message[] = L"Updated";

    CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 213, 197, 136);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);

}
void CIFSTTaiXiu::On_BtnClick1m()
{

    if(this->gilf || this->silk) {
        wchar_t message[] = L"Dat Cuoc 1000 Silk";
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 213, 197, 136);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
        m_custom_label16->SetText(L"1000");
    }
    if(this->gold)
    {
        wchar_t message[] = L"Dat Cuoc 1.000.000 gold";
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 213, 197, 136);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
        m_custom_label16 ->SetText(L"1000000");
    }
}
void CIFSTTaiXiu::On_BtnClick5m()
{
    if(this->gilf || this->silk) {
        wchar_t message[] = L"Dat Cuoc 5000 Silk";
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 213, 197, 136);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
        m_custom_label16->SetText(L"5000");
    }
    if(this->gold)
    {
        wchar_t message[] = L"Dat Cuoc 5.000.000 gold";
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 213, 197, 136);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
        m_custom_label16 ->SetText(L"5000000");
    }
}
void CIFSTTaiXiu::On_BtnClick10m()
{

    if(this->gilf || this->silk)
    {
        wchar_t message[] = L"Dat Cuoc 10.000 Silk";
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 213, 197, 136);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
        m_custom_label16 ->SetText(L"10.000");
    }
    if(this->gold)
    {
        wchar_t message[] = L"Dat Cuoc 10.000.000 gold";
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 213, 197, 136);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
        m_custom_label16 ->SetText(L"10000000");
    }

}
void CIFSTTaiXiu::On_BtnClicktai()
{


    wchar_t message[] = L"Dat Cuoc Tai";

    CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 213, 197, 136);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    m_custom_label11 ->SetText(L"1");
}
void CIFSTTaiXiu::On_BtnClickxiu()
{


    wchar_t message[] = L"Dat Cuoc Xiu";

    CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
    int color = D3DCOLOR_ARGB(255, 213, 197, 136);
    systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    m_custom_label11 ->SetText(L"2");
}
void CIFSTTaiXiu::On_BtnClickdatcuoc()
{



    std::n_wstring input_text = m_custom_label11->GetNText();
    std::n_wstring input_text1 = m_custom_label16->GetNText();
    if(input_text.empty() || input_text1.empty() )
    {
        wchar_t message[1000];
        swprintf_s(message, TSM_GETTEXTPTR("UIIT_STT_INPUT_RQ"));
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 213, 197, 136);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    } else {


        if(this->silk) {

            CMsgStreamBuffer buf(0x1321);
            buf << std::n_string(TO_NSTRING(this->m_custom_label11->GetNText())); // the loai
            buf << std::n_string(TO_NSTRING(this->m_custom_label16->GetNText())); // so gold

            SendMsg(buf);


        }
        else if(this->gilf) {

            CMsgStreamBuffer buf(0x1322);
            buf << std::n_string(TO_NSTRING(this->m_custom_label11->GetNText())); // the loai
            buf << std::n_string(TO_NSTRING(this->m_custom_label16->GetNText())); // so gold

            SendMsg(buf);

        }
        else if(this->gold) {

            CMsgStreamBuffer buf(0x1324);
            buf << std::n_string(TO_NSTRING(this->m_custom_label11->GetNText())); // the loai
            buf << std::n_string(TO_NSTRING(this->m_custom_label16->GetNText())); // so gold

            SendMsg(buf);

        }

    }

}

void CIFSTTaiXiu::OnClick_Exit()
{


    this->OnCloseWnd();


}

void CIFSTTaiXiu::SetChatBlocked(int timeoutSeconds) {

    this->m_ChatBlock_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_CHATBLOCK1, 1000);
}
void CIFSTTaiXiu::SetChatBlocked1(int timeoutSeconds) {

    this->m_ChatBlock_SecondsLeft1 = timeoutSeconds;
    StartTimer(TIMER_CHATBLOCK2, 1000);
}

void CIFSTTaiXiu::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}

