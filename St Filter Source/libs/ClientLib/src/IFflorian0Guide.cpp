#include "IFflorian0Guide.h"
#include <BSLib/Debug.h>
#include "GEffSoundBody.h"
#include "GInterface.h"
#include "BSLib/multibyte.h"
#include "IFMessageBox.h"
#include "../../../DevKit_DLL/src/Util.h"
#include "Rebot.h"
#include <algorithm>
#include <GFXMainFrame/Controler.h>
#include <ctime>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
GFX_IMPLEMENT_DYNCREATE(CIFflorian0Guide, CIFDecoratedStatic)
#define TIMER_CHATBLOCK1 502

std::map<std::n_wstring,TitleData*>CIFflorian0Guide::TitleDataList;

bool CIFflorian0Guide::OnCreate(long ln)
{
    CIFDecoratedStatic::OnCreate(ln);
/*    sub_634300();
    set_N00009BDC(0);
    set_wndsize(64,64);
    set_field_394(16);
    set_N00009BDD(100);
    set_N00009C18(1);
    set_N00009BD4(1);
    set_N00009BD3(0);
    field_3a0 = 283.500;
    field_3a4 = 382.500;
    field_3a8 = 1.000;
    field_3ac = 0.100;
    field_3b8 = 379.500;
    field_3bc = 382.500;
    field_3c0 = 1.000;
    field_3c4 = 0.100;
    field_3c8 = 0.250;
    field_3d0 = 379.500;
    field_3d4 = 478.500;
    field_3d8 = 1.000;
    field_3dc = 0.100;
    field_3e0 = 0.250;
    field_3e4 = 0.250;
    field_3e8 = 283.500;
    field_3ec = 478.500;
    field_3f0 = 1.000;
    field_3f4 = 0.100;
    field_3fc = 0.250;
    set_N00009BFD("interface\\alchemy\\alcm_effect_success.ddj");
    */
    TB_Func_13("interface\\ifcommon\\ngt\\ngt_menu_1.ddj", 0, 0);
    sub_634470("interface\\ifcommon\\ngt\\ngt_menu_2.ddj");
    sub_634470("interface\\ifcommon\\ngt\\ngt_menu_clean.ddj");
    set_N00009BD4(2);
    set_N00009BD3(600);

	CGEffSoundBody::get()->PlaySound(L"snd_quest");
	return true;
}

time_t lastClickTime9;
time_t lastClickTime;
void CIFflorian0Guide::OnUpdate()
{
    emojiHandler();
/*
    SYSTEMTIME time;
    GetSystemTime(&time);
    int ms = time.wMilliseconds;
    LONG time_ms = (time.wSecond *1000) + time.wMilliseconds;
    loop = ms/100;
    CIFHelperBubbleWindow *main1 = g_pCGInterface->m_IRM.GetResObj<CIFHelperBubbleWindow>(97, 1);
    loopcheck = 0;
    for (std::vector<CIFflorian0Guide::GifMaker>::iterator it = CIFflorian0Guide::gifMaker.begin(); it != CIFflorian0Guide::gifMaker.end(); ++it) {
        if (loopcheck != loop && (*it).showIcon) {
            loopcheck = loop;
            std::ostringstream temp;
            img = loop + 1;
            temp << img;
            std::string imgpath = "interface\\ifcommon\\electus\\bestslot_" + temp.str() + ".ddj";
            main1->m_circleIcon->TB_Func_13(imgpath, 0, 0);

        }
    }
*/


    if(g_pCICPlayer)
    {
       /* if(g_pCGInterface)
        {
            if(g_pCGInterface->GetMainPopup()->GetPlayerInfo())
            {
                CIFPlayerInfo* PlayerInfo = g_pCGInterface->GetMainPopup()->GetPlayerInfo();
                short Startpoint =  g_pCICPlayer->GetStatPointAvailable();
                if(Startpoint > 0 && PlayerInfo->m_mybutton_hp_checked() && PlayerInfo)
                {
                    if((time(NULL) - lastClickTime > 0.3)) {

                        g_pCGInterface->RequestStatIncrement(0x4b, 1, 0, 1);
                        lastClickTime = time(NULL);
                    }
                }
                else if(Startpoint > 0 &&  PlayerInfo->m_mybutton_mp_checked() && PlayerInfo)
                {
                    if((time(NULL) - lastClickTime > 0.3)) {

                        g_pCGInterface->RequestStatIncrement(0x4b, 2, 0, 1);
                        lastClickTime = time(NULL);
                    }
                }
            }

        }*/
        if(g_Controler->fKeys.F08_Key)
        {
            if((time(NULL) - lastClickTime9 > 1)) {

                SendMessageA(Rebot::GameHWND, WM_REBOTSTATUS, 1, 0);
                if(Rebot::RebotStart)
                {
                    g_pCGInterface->GetCIFSTMacroGUI()->btn2->TB_Func_13("interface\\macro\\macro_icon_hunting_on.ddj", 1, 1);
                    g_pCGInterface->GetCIFSTMacroGUI()->status = true;
                }
                else
                {
                    g_pCGInterface->GetCIFSTMacroGUI()->btn2->TB_Func_13("interface\\macro\\macro_icon_hunting_off.ddj", 1, 1);
                    g_pCGInterface->GetCIFSTMacroGUI()->status = false;
                }
                lastClickTime9 = time(NULL);
            }

        }
    }

}
int CIFflorian0Guide::OnMouseLeftUp(int a1, int x, int y)
{

	CGEffSoundBody::get()->PlaySound(L"snd_quest");
    g_pCGInterface->GetMainMenu()->ShowGWnd(true);
    g_pCGInterface->GetMainMenu()->ResetPosition();
    g_pCGInterface->GetMainMenu()->BringToFront();

	return 0;
}

void CIFflorian0Guide::OnCIFReady()
{
	BS_DEBUG_LOW("> " __FUNCTION__);

	CIFDecoratedStatic::OnCIFReady();
	sub_633990();

}


