//
// Created by Admin on 24/12/2021.
//

#include "IFSTStremSettingIcon.h"
#include "../../../DevKit_DLL/src/StdAfx.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include "IFflorian0Guide.h"
#include "CPSMission.h"

GFX_IMPLEMENT_DYNCREATE(CIFSTStremSettingIcon, CIFDecoratedStatic)


bool CIFSTStremSettingIcon::OnCreate(long ln)
{

    printf("> " __FUNCTION__ "(%d)\n", ln);
    CIFDecoratedStatic::OnCreate(ln);

    TB_Func_13("icon\\etc\\streamsetting.ddj", 0, 0);
    sub_634470("icon\\etc\\streamsetting.ddj");
    // sub_634470("interface\\ifcommon\\electus\\electusbestinslot.ddj");
    set_N00009BD4(2);
    set_N00009BD3(500);

    CGEffSoundBody::get()->PlaySound(L"snd_quest");

    return true;
}

int CIFSTStremSettingIcon::OnMouseLeftUp(int a1, int x, int y)
{
    printf("> " __FUNCTION__ "(%d, %d, %d)\n", a1, x, y);
    CGEffSoundBody::get()->PlaySound(L"snd_quest");
    g_pCGInterface->GetStreamSettingGUI()->ShowGWnd(true);
    g_pCGInterface->GetStreamSettingGUI()->ResetPosition();
    return 0;
}

void CIFSTStremSettingIcon::OnCIFReady()
{
    printf("> " __FUNCTION__ "\n");

    CIFDecoratedStatic::OnCIFReady();
    sub_633990();

}



