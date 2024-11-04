#include "../../../DevKit_DLL/src/StdAfx.h"
#include "IFDailyLoginIcon.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include "IFflorian0.h"
#include "IFflorian0Guide.h"
#include "CPSMission.h"
#include "IFSTDailyLogin.h"

GFX_IMPLEMENT_DYNCREATE(CIFDailyLoginIcon, CIFDecoratedStatic)


bool CIFDailyLoginIcon::OnCreate(long ln)
{

    printf("> " __FUNCTION__ "(%d)\n", ln);
    CIFDecoratedStatic::OnCreate(ln);

    // TB_Func_13("icon\\etc\\bugle_icon_1.ddj", 0, 0);


    TB_Func_13("icon\\etc\\summer_event_calendar.ddj", 0, 0);
    sub_634470("icon\\etc\\summer_event_calendar.ddj");
    // sub_634470("interface\\ifcommon\\electus\\electusbestinslot.ddj");
    set_N00009BD4(2);
    set_N00009BD3(500);

    CGEffSoundBody::get()->PlaySound(L"snd_quest");

    return true;
}

int CIFDailyLoginIcon::OnMouseLeftUp(int a1, int x, int y)
{
    printf("> " __FUNCTION__ "(%d, %d, %d)\n", a1, x, y);
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!UPDATEDIEMDANH");
    buf << std::n_string("!UPDATEDIEMDANH");
    SendMsg(buf);
    CGEffSoundBody::get()->PlaySound(L"snd_quest");
    CIFDailyLogin * Login = (CIFDailyLogin *)g_pCGInterface->m_IRM.GetResObj(5096, 1);
    Login->ShowGWnd(true);
    Login->ResetPosition();
    return 0;
}



void CIFDailyLoginIcon::OnCIFReady()
{
    printf("> " __FUNCTION__ "\n");

    CIFDecoratedStatic::OnCIFReady();
    sub_633990();

}



