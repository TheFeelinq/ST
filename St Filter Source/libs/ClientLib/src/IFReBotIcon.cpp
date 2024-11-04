#include "../../../DevKit_DLL/src/StdAfx.h"
#include "IFReBotIcon.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include "IFflorian0Guide.h"
#include "Rebot.h"
#include "CPSMission.h"

GFX_IMPLEMENT_DYNCREATE(CIFReBotIcon, CIFDecoratedStatic)


bool CIFReBotIcon::OnCreate(long ln)
{

    CIFDecoratedStatic::OnCreate(ln);

    TB_Func_13("icon\\etc\\menu.ddj", 0, 0);
    sub_634470("icon\\etc\\menu_1.ddj");
    set_N00009BD4(2);
    set_N00009BD3(500);
    CGEffSoundBody::get()->PlaySound(L"snd_quest");

    return true;
}

int CIFReBotIcon::OnMouseLeftUp(int a1, int x, int y)
{
    printf("> " __FUNCTION__ "(%d, %d, %d)\n", a1, x, y);

    CGEffSoundBody::get()->PlaySound(L"snd_quest");

    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!UpdateSkillRebot");
    buf << std::n_string("!UpdateSkillRebot");
    SendMsg(buf);
    g_pCGInterface->GetCIFSTMacroGUI()->ResetPosition();
    g_pCGInterface->GetCIFSTMacroGUI()->ShowGWnd(true);
    //Rebot::RebotShow=true;

    return 0;
}



void CIFReBotIcon::OnCIFReady()
{
    printf("> " __FUNCTION__ "\n");

    CIFDecoratedStatic::OnCIFReady();
    sub_633990();

}



