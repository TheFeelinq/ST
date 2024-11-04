#include "IFSTPvpChallengeAnswer.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include "ClientNet/MsgStreamBuffer.h"
#include "GInterface.h"
#include "IFDecoratedStatic.h"

#include "unsorted.h"
#include "GlobalHelpersThatHaveNoHomeYet.h"
#include "ClientNet/ClientNet.h"
#include "Game.h"
#include "ICPlayer.h"
#include "IFWnd.h"
#include <BSLib\multibyte.h>
#include "TextStringManager.h"
#include <IFSystemMessage.h>

#define STPVPCHALLENGEANSWER_TIMER 19
#define STPVPCHALLENGEANSWER_DECLINE 18
#define STPVPCHALLENGEANSWER_ACCEPT 17
#define STPVPCHALLENGEANSWER_SILK 16
#define STPVPCHALLENGEANSWER_SILK_ICON 15
#define STPVPCHALLENGEANSWER_CHALLENGEDYOU_LABEL 14
#define STPVPCHALLENGEANSWER_CHARACTER_NAME 13
#define STPVPCHALLENGEANSWER_CHARACTER_PICTURE_MASK 12
#define STPVPCHALLENGEANSWER_CHARACTER_PICTURE 11
#define STPVPCHALLENGEANSWER_FRAME 10
#define TIMER_CHATBLOCK1 553


GFX_IMPLEMENT_DYNCREATE(CIFSTPvpChallengeAnswer, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTPvpChallengeAnswer, CIFMainFrame)
                    ONG_COMMAND(STPVPCHALLENGEANSWER_DECLINE, &OnClick_Exit)
                    ONG_COMMAND(STPVPCHALLENGEANSWER_ACCEPT, &On_BtnClickACCEPT)



GFX_END_MESSAGE_MAP()


CIFSTPvpChallengeAnswer::CIFSTPvpChallengeAnswer(void)
{
    printf("> " __FUNCTION__ "\n");
}


CIFSTPvpChallengeAnswer::~CIFSTPvpChallengeAnswer(void)
{
    printf("> " __FUNCTION__ "\n");
}

bool CIFSTPvpChallengeAnswer::OnCreate(long ln)
{
    printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT rect_custom_label = {0,0,341,104};
    m_custom_label = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label,STPVPCHALLENGEANSWER_FRAME,1);
    m_custom_label->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\stpvpchallengeanswer_frame.ddj", 1, 0);

    RECT rect_button4 = {179,63,38,39};
    m_mybutton4 = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button4,STPVPCHALLENGEANSWER_DECLINE,1);
    m_mybutton4->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\stpvpchallengeanswer_decline.ddj", 1, 1);

    RECT rect_button2 = {291,4,28,26};
    m_mybutton2 = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button2,STPVPCHALLENGEANSWER_SILK_ICON,1);
    m_mybutton2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\stpvpchallengeanswer_silk_icon.ddj", 1, 1);

    RECT rect_button = {130,63,38,39};
    m_mybutton = (CIFButton *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFButton),rect_button,STPVPCHALLENGEANSWER_ACCEPT,1);
    m_mybutton->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\stpvpchallengeanswer_accept.ddj", 1, 1);

    RECT rect_custom_label1 = {48,0,44,44};
    m_custom_label1 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label1,STPVPCHALLENGEANSWER_CHARACTER_PICTURE,1);

    RECT rect_custom_label2 = {48,0,44,44};
    m_custom_label2 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label2,STPVPCHALLENGEANSWER_CHARACTER_PICTURE_MASK,1);
    m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\stpvpchallengeanswer_player_mask.ddj", 1, 0);

    RECT rect_custom_label3 = {100,4,161,16};
    m_custom_label3 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label3,STPVPCHALLENGEANSWER_CHARACTER_NAME,1);

    RECT rect_custom_label5 = {100,23,130,16};
    m_custom_label5 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label5,STPVPCHALLENGEANSWER_CHALLENGEDYOU_LABEL,1);
    m_custom_label5 ->SetText(TSM_GETTEXTPTR("UIIT_STT_PVP_CHALLENGE_TO_YOU"));

    RECT rect_custom_label4 = {235,23,94,16};
    m_custom_label4 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label4,STPVPCHALLENGEANSWER_SILK,1);

    RECT rect_custom_label6 = {279,65,16,16};
    m_custom_label6 = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_custom_label6,STPVPCHALLENGEANSWER_TIMER,1);
    ResetPosition();
    this->ShowGWnd(false);
    return true;
}
void CIFSTPvpChallengeAnswer::OnTimer(int timerId) {
    if (timerId == TIMER_CHATBLOCK1) {

        wchar_t buffer[255];
        swprintf_s(buffer, L"%d", m_ChatBlock_SecondsLefts);
        m_custom_label6->m_FontTexture.sub_8B4400(5, 1);
        m_custom_label6->SetText(buffer);
        m_custom_label6->ShowGWnd(true);


        if (m_ChatBlock_SecondsLefts > -1) {
            m_ChatBlock_SecondsLefts--;
        } else {
            CMsgStreamBuffer buf(0x1318);
            buf << std::n_string(TO_NSTRING(this->m_custom_label3->GetNText()));
            buf << std::n_string("!pvpchallengenoanswer");
            SendMsg(buf);
           this->ShowGWnd(false);
           this->KillTimer(TIMER_CHATBLOCK1);

        }
    }

}
void CIFSTPvpChallengeAnswer::OnUpdate()
{
    time_t rawtime;
    struct tm * timeinfo;
    wchar_t buffer[80];
    wchar_t buffer1[80];
    swprintf(buffer1, L"Change", 0);
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%d-%m-%Y %H:%M:%S", timeinfo);
    short ALTState = GetKeyState(VK_MENU);
    if (ALTState == -127 || ALTState == -128) // ALT is hold
    {
        this->OnCloseWnd();
    }

}

void CIFSTPvpChallengeAnswer::On_BtnClickACCEPT()
{

    std::n_wstring input_text =g_pCICPlayer ->GetCharName().c_str();

    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string(TO_NSTRING(this->m_custom_label3->GetNText()));
    buf << std::n_string("!Accectpvpchallenge");
    buf << std::n_string(TO_NSTRING(this->m_custom_label4->GetNText()));

    SendMsg(buf);
    this->OnCloseWnd();
    this->KillTimer(TIMER_CHATBLOCK1);
}

void CIFSTPvpChallengeAnswer::OnClick_Exit()
{
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string(TO_NSTRING(this->m_custom_label3->GetNText()));
    buf << std::n_string("!pvpchallengedecline");
    SendMsg(buf);

    this->OnCloseWnd();
    this->KillTimer(TIMER_CHATBLOCK1);
}


void CIFSTPvpChallengeAnswer::SetChatBlocked(int timeoutSeconds) {

    this->m_ChatBlock_SecondsLefts = timeoutSeconds;
    StartTimer(TIMER_CHATBLOCK1, 1000);
}
void CIFSTPvpChallengeAnswer::ResetPosition()
{

    const ClientResolutonData &res = CGame::GetClientDimensionStuff();
    this->MoveGWnd(res.width-300, res.height-400);
}