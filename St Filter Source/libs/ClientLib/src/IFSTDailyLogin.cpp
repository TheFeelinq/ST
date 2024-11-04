#include "IFSTDailyLogin.h"
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

#include <IFSystemMessage.h>
#define ELECTUSDIEMDANH_DIEMDANH 61
#define ELECTUSDIEMDANH_NGAY1_SLOT 60
#define ELECTUSDIEMDANH_NGAY2_SLOT 59
#define ELECTUSDIEMDANH_NGAY3_SLOT 58
#define ELECTUSDIEMDANH_NGAY4_SLOT 57
#define ELECTUSDIEMDANH_NGAY5_SLOT 56
#define ELECTUSDIEMDANH_NGAY6_SLOT 55
#define ELECTUSDIEMDANH_NGAY7_SLOT 54
#define ELECTUSDIEMDANH_NGAY8_SLOT 53
#define ELECTUSDIEMDANH_NGAY9_SLOT 52
#define ELECTUSDIEMDANH_NGAY10_SLOT 51
#define ELECTUSDIEMDANH_NGAY11_SLOT 50
#define ELECTUSDIEMDANH_NGAY12_SLOT 49
#define ELECTUSDIEMDANH_NGAY13_SLOT 48
#define ELECTUSDIEMDANH_NGAY14_SLOT 47
#define ELECTUSDIEMDANH_NGAY15_SLOT 46
#define ELECTUSDIEMDANH_NGAY16_SLOT 45
#define ELECTUSDIEMDANH_NGAY17_SLOT 44
#define ELECTUSDIEMDANH_NGAY18_SLOT 43
#define ELECTUSDIEMDANH_NGAY19_SLOT 42
#define ELECTUSDIEMDANH_NGAY20_SLOT 41
#define ELECTUSDIEMDANH_NGAY21_SLOT 40
#define ELECTUSDIEMDANH_NGAY22_SLOT 39
#define ELECTUSDIEMDANH_NGAY23_SLOT 38
#define ELECTUSDIEMDANH_NGAY24_SLOT 37
#define ELECTUSDIEMDANH_NGAY25_SLOT 36
#define ELECTUSDIEMDANH_NHAN_1_NGAY 35
#define ELECTUSDIEMDANH_NHAN_3_NGAY 34
#define ELECTUSDIEMDANH_NHAN_5_NGAY 33
#define ELECTUSDIEMDANH_NHAN_7_NGAY 32
#define ELECTUSDIEMDANH_NHAN_10_NGAY 31
#define ELECTUSDIEMDANH_NHAN_13_NGAY 30
#define ELECTUSDIEMDANH_NHAN_16_NGAY 29
#define ELECTUSDIEMDANH_NHAN_19_NGAY 28
#define ELECTUSDIEMDANH_NHAN_22_NGAY 27
#define ELECTUSDIEMDANH_NHAN_25_NGAY 26
#define ELECTUSDIEMDANH_ITEM_ICON_SLOT1 25
#define ELECTUSDIEMDANH_ITEM_ICON_SLOT3 24
#define ELECTUSDIEMDANH_ITEM_ICON_SLOT5 23
#define ELECTUSDIEMDANH_ITEM_ICON_SLOT7 22

#define ELECTUSDIEMDANH_ITEM_ICON_SLOT10 21
#define ELECTUSDIEMDANH_ITEM_ICON_SLOT13 20
#define ELECTUSDIEMDANH_ITEM_ICON_SLOT16 19
#define ELECTUSDIEMDANH_ITEM_ICON_SLOT19 18
#define ELECTUSDIEMDANH_ITEM_ICON_SLOT22 17
#define ELECTUSDIEMDANH_ITEM_ICON_SLOT25 16
#define ELECTUSDIEMDANH_TOOLTIP1 15
#define ELECTUSDIEMDANH_TOOLTIP2 14
#define ELECTUSDIEMDANH_FRAME_TILE 13
#define ELECTUSDIEMDANH_CLOSE 12

#define ELECTUSDIEMDANH_REFRESH 11
#define ELECTUSDIEMDANH_FRAME 10



GFX_IMPLEMENT_DYNCREATE(CIFDailyLogin, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFDailyLogin, CIFMainFrame)
                    ONG_COMMAND(ELECTUSDIEMDANH_CLOSE, &OnClick_Exit)
                    ONG_COMMAND(ELECTUSDIEMDANH_REFRESH, &On_BtnClickRs)
                    ONG_COMMAND(ELECTUSDIEMDANH_NHAN_25_NGAY, &On_BtnClick25)
                    ONG_COMMAND(ELECTUSDIEMDANH_NHAN_22_NGAY, &On_BtnClick22)
                    ONG_COMMAND(ELECTUSDIEMDANH_NHAN_19_NGAY, &On_BtnClick19)
                    ONG_COMMAND(ELECTUSDIEMDANH_NHAN_16_NGAY, &On_BtnClick16)
                    ONG_COMMAND(ELECTUSDIEMDANH_NHAN_13_NGAY, &On_BtnClick13)
                    ONG_COMMAND(ELECTUSDIEMDANH_NHAN_10_NGAY, &On_BtnClick10)
                    ONG_COMMAND(ELECTUSDIEMDANH_NHAN_7_NGAY, &On_BtnClick7)
                    ONG_COMMAND(ELECTUSDIEMDANH_NHAN_5_NGAY, &On_BtnClick5)
                    ONG_COMMAND(ELECTUSDIEMDANH_NHAN_3_NGAY, &On_BtnClick3)
                    ONG_COMMAND(ELECTUSDIEMDANH_NHAN_1_NGAY, &On_BtnClick1)

                    ONG_COMMAND(ELECTUSDIEMDANH_DIEMDANH, &On_BtnClick)

GFX_END_MESSAGE_MAP()


CIFDailyLogin::CIFDailyLogin(void)
{
    printf("> " __FUNCTION__ "\n");
}


CIFDailyLogin::~CIFDailyLogin(void)
{
    printf("> " __FUNCTION__ "\n");
}

bool CIFDailyLogin::OnCreate(long ln)
{
    printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    m_IRM.LoadFromFile("resinfo\\ifstdiemdanh.txt");
    m_IRM.CreateInterfaceSection("Create", this);

    m_mybutton = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_NHAN_25_NGAY, 1);
    m_mybutton3 = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_NHAN_22_NGAY, 1);
    m_mybutton4 = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_NHAN_19_NGAY, 1);
    m_mybutton5 = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_NHAN_16_NGAY, 1);
    m_mybutton6 = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_NHAN_13_NGAY, 1);
    m_mybutton7 = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_NHAN_10_NGAY, 1);
    m_mybutton8 = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_NHAN_7_NGAY, 1);
    m_mybutton9 = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_NHAN_5_NGAY, 1);
    m_mybutton10 = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_NHAN_3_NGAY, 1);
    m_mybutton11 = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_NHAN_1_NGAY, 1);
    m_mybutton12 = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_REFRESH, 1);
    m_mybutton13 = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_CLOSE, 1);
    m_mybutton14 = m_IRM.GetResObj<CIFButton>(ELECTUSDIEMDANH_DIEMDANH, 1);

    m_custom_label11 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_FRAME, 1);
    m_custom_label12 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_FRAME_TILE, 1);
    m_custom_label13 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_TOOLTIP2, 1);
    m_custom_label14 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_TOOLTIP1, 1);

    m_custom_label18 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_ITEM_ICON_SLOT25, 1);
    m_custom_label19 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_ITEM_ICON_SLOT22, 1);
    m_custom_label20 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_ITEM_ICON_SLOT19, 1);
    m_custom_label21 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_ITEM_ICON_SLOT16, 1);
    m_custom_label22 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_ITEM_ICON_SLOT13, 1);
    m_custom_label23 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_ITEM_ICON_SLOT10, 1);
    m_custom_label24 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_ITEM_ICON_SLOT7, 1);
    m_custom_label25 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_ITEM_ICON_SLOT5, 1);
    m_custom_label26 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_ITEM_ICON_SLOT3, 1);
    m_custom_label27 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_ITEM_ICON_SLOT1, 1);

    m_custom_label28 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY25_SLOT, 1);
    m_custom_label29 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY24_SLOT, 1);
    m_custom_label30 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY23_SLOT, 1);
    m_custom_label31 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY22_SLOT, 1);
    m_custom_label32 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY21_SLOT, 1);
    m_custom_label33 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY20_SLOT, 1);
    m_custom_label34 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY19_SLOT, 1);
    m_custom_label35 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY18_SLOT, 1);
    m_custom_label36 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY17_SLOT, 1);
    m_custom_label37 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY16_SLOT, 1);
    m_custom_label38 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY15_SLOT, 1);
    m_custom_label39 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY14_SLOT, 1);
    m_custom_label40 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY13_SLOT, 1);
    m_custom_label41 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY12_SLOT, 1);
    m_custom_label42 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY11_SLOT, 1);
    m_custom_label43 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY10_SLOT, 1);
    m_custom_label44 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY9_SLOT, 1);
    m_custom_label45 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY8_SLOT, 1);
    m_custom_label46 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY7_SLOT, 1);
    m_custom_label47 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY6_SLOT, 1);
    m_custom_label48 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY5_SLOT, 1);
    m_custom_label49 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY4_SLOT, 1);
    m_custom_label50 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY3_SLOT, 1);
    m_custom_label51 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY2_SLOT, 1);
    m_custom_label52 = m_IRM.GetResObj<CIFStatic>(ELECTUSDIEMDANH_NGAY1_SLOT, 1);


    m_mybutton11->ShowGWnd(false);
    m_mybutton10->ShowGWnd(false);
    m_mybutton9->ShowGWnd(false);
    m_mybutton8->ShowGWnd(false);
    m_mybutton7->ShowGWnd(false);
    m_mybutton6->ShowGWnd(false);
    m_mybutton5->ShowGWnd(false);
    m_mybutton4->ShowGWnd(false);
    m_mybutton3->ShowGWnd(false);
    m_mybutton->ShowGWnd(false);
    this->ShowGWnd(false);


    return true;
}

void CIFDailyLogin::OnUpdate()
{
    time_t rawtime;
    struct tm * timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);

}

void CIFDailyLogin::On_BtnClick()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!diemdanh");
    buf << std::n_string("!diemdanh");
    SendMsg(buf);

}
void CIFDailyLogin::On_BtnClick1()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!NHANMOC1");
    buf << std::n_string("!NHANMOC1");
    SendMsg(buf);
}

void CIFDailyLogin::On_BtnClick3()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!NHANMOC3");
    buf << std::n_string("!NHANMOC3");
    SendMsg(buf);
}

void CIFDailyLogin::On_BtnClick5()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!NHANMOC5");
    buf << std::n_string("!NHANMOC5");
    SendMsg(buf);
}

void CIFDailyLogin::On_BtnClick7()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!NHANMOC7");
    buf << std::n_string("!NHANMOC7");
    SendMsg(buf);
}

void CIFDailyLogin::On_BtnClick10()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!NHANMOC10");
    buf << std::n_string("!NHANMOC10");
    SendMsg(buf);
}

void CIFDailyLogin::On_BtnClick13()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!NHANMOC13");
    buf << std::n_string("!NHANMOC13");
    SendMsg(buf);
}

void CIFDailyLogin::On_BtnClick16()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!NHANMOC16");
    buf << std::n_string("!NHANMOC16");
    SendMsg(buf);
}

void CIFDailyLogin::On_BtnClick19()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!NHANMOC19");
    buf << std::n_string("!NHANMOC19");
    SendMsg(buf);
}

void CIFDailyLogin::On_BtnClick22()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!NHANMOC22");
    buf << std::n_string("!NHANMOC22");
    SendMsg(buf);
}
void CIFDailyLogin::On_BtnClick25()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!NHANMOC25");
    buf << std::n_string("!NHANMOC25");
    SendMsg(buf);
}
void CIFDailyLogin::On_BtnClickRs()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!UPDATEDIEMDANH");
    buf << std::n_string("!UPDATEDIEMDANH");
    SendMsg(buf);
}
void CIFDailyLogin::OnClick_Exit()
{
    this->OnCloseWnd();


}
void CIFDailyLogin::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}