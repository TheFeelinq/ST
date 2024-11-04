#include "IFflorian0.h"
#include "IFflorian0Guide.h"
#include "GInterface.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include "IFPlayerMiniInfo.h"
#include "ICPlayer.h"
#include "TextStringManager.h"

#include "IFWholeChat.h"

#define NGTMENU_PLAYERONLINE_COUNT 41
#define NGTMENU_PLAYERONLINE_TEXT 40
#define NGTMENU_MAIN_TEXT 39
#define NGTMENU_LINK4 38
#define NGTMENU_LINK3 37
#define NGTMENU_LINK2 36
#define NGTMENU_LINK1 35
#define NGTMENU_MENU_TEXT 34
#define NGTMENU_GRANTNAME_TEXT 33
#define NGTMENU_TITLES_TEXT 32
#define NGTMENU_UNIQUETIMERS_TEXT 31
#define NGTMENU_EVENTTIMERS_TEXT 30
#define NGTMENU_HONORPOINTS_TEXT 29
#define NGTMENU_MENU 28
#define NGTMENU_GRANTNAME 27
#define NGTMENU_TITLES 26
#define NGTMENU_UNIQUETIMERS 25
#define NGTMENU_EVENTTIMERS 24
#define NGTMENU_HONORPOINTS 23
#define NGTMENU_RANKINGS 21
#define NGTMENU_CHARACTER_LOCK 18
#define NGTMENU_LOCKED_STATUS 17
#define NGTMENU_HONOR_POINTS 16
#define NGTMENU_CHARACTER_NAME 15
#define NGTMENU_RANK_ICON 14
#define NGTMENU_CHARACTER_PICTURE_MASK 13
#define NGTMENU_CHARACTER_PICTURE 12
#define NGTMENU_CLOSE_BUTTON 11
#define NGTMENU_FRAME 10




GFX_IMPLEMENT_DYNCREATE(CIFflorian0, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFflorian0, CIFMainFrame)
                    ONG_COMMAND(NGTMENU_CHARACTER_LOCK, &On_BtnClickCharLock)
                    ONG_COMMAND(NGTMENU_RANKINGS, &On_BtnClick)
                    ONG_COMMAND(NGTMENU_HONORPOINTS, &On_BtnClickXepHang)
                    ONG_COMMAND(NGTMENU_EVENTTIMERS, &On_BtnClickTichNap)
                    ONG_COMMAND(NGTMENU_UNIQUETIMERS, &On_BtnClickUniqueTimer)
                    ONG_COMMAND(NGTMENU_TITLES, &On_BtnClickTitle)
                    ONG_COMMAND(NGTMENU_GRANTNAME, &On_BtnClickIFElectusGrantName)
                    ONG_COMMAND(NGTMENU_MENU, &On_BtnClickXoSo)
                    ONG_COMMAND(NGTMENU_LINK1, &On_BtnClickTrangChu)
                    ONG_COMMAND(NGTMENU_LINK2, &On_BtnClickDisCord)
                    ONG_COMMAND(NGTMENU_LINK3, &On_BtnClickFaceBook)
                    ONG_COMMAND(NGTMENU_LINK4, &On_BtnClickMes)
                    ONG_COMMAND(NGTMENU_RANK_ICON, &On_BtnClick)
                    ONG_COMMAND(NGTMENU_CLOSE_BUTTON, &OnClick_Exit)

GFX_END_MESSAGE_MAP()


CIFflorian0::CIFflorian0(void)
{
    printf("> " __FUNCTION__ "\n");
}


CIFflorian0::~CIFflorian0(void)
{
    printf("> " __FUNCTION__ "\n");
}

bool CIFflorian0::OnCreate(long ln)
{
    printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    m_IRM.LoadFromFile("resinfo\\ifngtmenu.txt");
    m_IRM.CreateInterfaceSection("Create", this);

    m_mybutton = m_IRM.GetResObj<CIFButton>(NGTMENU_LINK4, 1);
    m_mybutton2 = m_IRM.GetResObj<CIFButton>(NGTMENU_LINK3, 1);
    m_mybutton3 = m_IRM.GetResObj<CIFButton>(NGTMENU_LINK2, 1);
    m_mybutton4 = m_IRM.GetResObj<CIFButton>(NGTMENU_LINK1, 1);
    m_mybutton5 = m_IRM.GetResObj<CIFButton>(NGTMENU_MENU, 1);
    m_mybutton6 = m_IRM.GetResObj<CIFButton>(NGTMENU_GRANTNAME, 1);
    m_mybutton7 = m_IRM.GetResObj<CIFButton>(NGTMENU_TITLES, 1);
    m_mybutton8 = m_IRM.GetResObj<CIFButton>(NGTMENU_UNIQUETIMERS, 1);
    m_mybutton9 = m_IRM.GetResObj<CIFButton>(NGTMENU_EVENTTIMERS, 1);
    m_mybutton10 = m_IRM.GetResObj<CIFButton>(NGTMENU_HONORPOINTS, 1);
    m_mybutton12 = m_IRM.GetResObj<CIFButton>(NGTMENU_RANKINGS, 1);


    m_mybutton15 = m_IRM.GetResObj<CIFButton>(NGTMENU_CHARACTER_LOCK, 1);
    m_mybutton16 = m_IRM.GetResObj<CIFButton>(NGTMENU_RANK_ICON, 1);
    m_mybutton17 = m_IRM.GetResObj<CIFButton>(NGTMENU_CLOSE_BUTTON, 1);

    m_custom_label = m_IRM.GetResObj<CIFStatic>(NGTMENU_MAIN_TEXT, 1);
    m_custom_label1 = m_IRM.GetResObj<CIFStatic>(NGTMENU_MENU_TEXT, 1);
    m_custom_label2 = m_IRM.GetResObj<CIFStatic>(NGTMENU_GRANTNAME_TEXT, 1);
    m_custom_label3 = m_IRM.GetResObj<CIFStatic>(NGTMENU_TITLES_TEXT, 1);
    m_custom_label4 = m_IRM.GetResObj<CIFStatic>(NGTMENU_UNIQUETIMERS_TEXT, 1);
    m_custom_label5 = m_IRM.GetResObj<CIFStatic>(NGTMENU_EVENTTIMERS_TEXT, 1);
    m_custom_label6 = m_IRM.GetResObj<CIFStatic>(NGTMENU_HONORPOINTS_TEXT, 1);
    m_custom_label7 = m_IRM.GetResObj<CIFStatic>(NGTMENU_LOCKED_STATUS, 1);
    m_custom_label8 = m_IRM.GetResObj<CIFStatic>(NGTMENU_HONOR_POINTS, 1);
    m_custom_label9 = m_IRM.GetResObj<CIFStatic>(NGTMENU_CHARACTER_NAME, 1);

    m_custom_label10 = m_IRM.GetResObj<CIFStatic>(NGTMENU_CHARACTER_PICTURE_MASK, 1);
    m_custom_label12 = m_IRM.GetResObj<CIFStatic>(NGTMENU_CHARACTER_PICTURE, 1);
    m_custom_label13 = m_IRM.GetResObj<CIFStatic>(NGTMENU_FRAME, 1);
    m_custom_label14 = m_IRM.GetResObj<CIFStatic>(NGTMENU_PLAYERONLINE_COUNT, 1);


    this->ShowGWnd(false);


    return true;
}

void CIFflorian0::OnUpdate()
{
    time_t rawtime;
    struct tm * timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);
//    m_IRM.GetResObj<CIFStatic>(NGTMENU_CHARACTER_NAME, 1)->SetText(g_pCICPlayer->GetCharName().c_str());
}

void CIFflorian0::On_BtnClick()
{


}
void CIFflorian0::On_BtnClickTrangChu()
{
    ShellExecute(NULL, "open", "http://srodevuong.com", NULL, NULL, SW_SHOWNORMAL);

}
void CIFflorian0::On_BtnClickDisCord()
{
    ShellExecute(NULL, "open", "http://srodevuong.com", NULL, NULL, SW_SHOWNORMAL);

}
void CIFflorian0::On_BtnClickFaceBook()
{

}
void CIFflorian0::On_BtnClickMes()
{
    ShellExecute(NULL, "open", "http://srodevuong.com", NULL, NULL, SW_SHOWNORMAL);
}
void CIFflorian0::On_BtnClickXepHang()
{

    ShellExecute(NULL, "open", "http://srodevuong.com", NULL, NULL, SW_SHOWNORMAL);
}
void CIFflorian0::On_BtnClickUniqueTimer()
{
    ShellExecute(NULL, "open", "http://srodevuong.com", NULL, NULL, SW_SHOWNORMAL);
}

void CIFflorian0::On_BtnClickCharLock()
{
    ShellExecute(NULL, "open", "http://srodevuong.com", NULL, NULL, SW_SHOWNORMAL);
}
void CIFflorian0::On_BtnClickTitle()
{
    ShellExecute(NULL, "open", "http://srodevuong.com", NULL, NULL, SW_SHOWNORMAL);
}

void CIFflorian0::On_BtnClickIFElectusGrantName()
{
    ShellExecute(NULL, "open", "http://srodevuong.com", NULL, NULL, SW_SHOWNORMAL);
}
void CIFflorian0::On_BtnClickTichNap()
{
    ShellExecute(NULL, "open", "http://srodevuong.com", NULL, NULL, SW_SHOWNORMAL);
}
void CIFflorian0::On_BtnClickIFelectuseventtimers()
{
    ShellExecute(NULL, "open", "http://srodevuong.com", NULL, NULL, SW_SHOWNORMAL);
}
void CIFflorian0::On_BtnClickXoSo()
{
    ShellExecute(NULL, "open", "http://srodevuong.com", NULL, NULL, SW_SHOWNORMAL);

}


void CIFflorian0::OnClick_Exit()
{
    this->OnCloseWnd();


}
