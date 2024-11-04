#include "../../../DevKit_DLL/src/StdAfx.h"
#include "IFNapThe.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include "Rebot.h"
#include "IFflorian0Guide.h"
#include "CPSMission.h"

GFX_IMPLEMENT_DYNCREATE(CIFNapThe, CIFDecoratedStatic)


bool CIFNapThe::OnCreate(long ln)
{

    printf("> " __FUNCTION__ "(%d)\n", ln);
    CIFDecoratedStatic::OnCreate(ln);

    TB_Func_13("icon\\etc\\sell_icon_1.ddj", 0, 0);
    sub_634470("icon\\etc\\sell_icon_2.ddj");
    //sub_634470("icon\\etc\\facebook_2.ddj");
    set_N00009BD4(2);
    set_N00009BD3(500);

    CGEffSoundBody::get()->PlaySound(L"snd_quest");

    return true;
}

int CIFNapThe::OnMouseLeftUp(int a1, int x, int y)
{
    printf("> " __FUNCTION__ "(%d, %d, %d)\n", a1, x, y);

    CGEffSoundBody::get()->PlaySound(L"snd_quest");
    g_pCGInterface->GetExtraFeatureGUI()->ShowGWnd(true);
  // g_pCGInterface->m_IRM.GetResObj(5090, 1)->ShowGWnd(true);
    return 0;
}



void CIFNapThe::OnCIFReady()
{
    printf("> " __FUNCTION__ "\n");

    CIFDecoratedStatic::OnCIFReady();
    sub_633990();

}



