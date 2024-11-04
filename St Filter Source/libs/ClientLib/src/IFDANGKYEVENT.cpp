#include "../../../DevKit_DLL/src/StdAfx.h"
#include "IFDANGKYEVENT.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include "IFflorian0Guide.h"

GFX_IMPLEMENT_DYNCREATE(CIFDANGKYEVENT, CIFDecoratedStatic)


bool CIFDANGKYEVENT::OnCreate(long ln)
{
    printf("> " __FUNCTION__ "(%d)\n", ln);
    CIFDecoratedStatic::OnCreate(ln);

    TB_Func_13("icon\\etc\\bugle_icon_1.ddj", 0, 0);
    sub_634470("icon\\etc\\bugle_icon_2.ddj");

    CGEffSoundBody::get()->PlaySound(L"snd_quest");

    return true;
}

int CIFDANGKYEVENT::OnMouseLeftUp(int a1, int x, int y)
{
    printf("> " __FUNCTION__ "(%d, %d, %d)\n", a1, x, y);

    CGEffSoundBody::get()->PlaySound(L"snd_quest");
    g_pCGInterface->GetEventRegisterGUI()->ShowGWnd(true);
    g_pCGInterface->GetEventRegisterGUI()->ResetPosition();
    g_pCGInterface->GetEventRegisterGUI()->BringToFront();
    return 0;
}



void CIFDANGKYEVENT::OnCIFReady()
{
    printf("> " __FUNCTION__ "\n");

    CIFDecoratedStatic::OnCIFReady();
    sub_633990();

}



