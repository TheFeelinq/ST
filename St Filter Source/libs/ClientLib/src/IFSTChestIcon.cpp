#include "../../../DevKit_DLL/src/StdAfx.h"
#include "IFSTChestIcon.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include "IFflorian0Guide.h"
#include "GlobalDataManager.h"

GFX_IMPLEMENT_DYNCREATE(CIFSTChestIcon, CIFDecoratedStatic)


bool CIFSTChestIcon::OnCreate(long ln)
{
    printf("> " __FUNCTION__ "(%d)\n", ln);
    CIFDecoratedStatic::OnCreate(ln);

    TB_Func_13("icon\\etc\\itemmall_0.ddj", 0, 0);
    sub_634470("icon\\etc\\itemmall_0.ddj");

    CGEffSoundBody::get()->PlaySound(L"snd_quest");

    return true;
}

int CIFSTChestIcon::OnMouseLeftUp(int a1, int x, int y)
{
    printf("> " __FUNCTION__ "(%d, %d, %d)\n", a1, x, y);

    CGEffSoundBody::get()->PlaySound(L"snd_quest");
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!UPDATECHEST");
    buf << std::n_string("!UPDATECHEST");
    SendMsg(buf);
    wchar_t buffer[255];
    swprintf_s(buffer,L"%d", g_CGlobalDataManager->GetEmptyInventorySlots());
    g_pCGInterface->GetChestGUI()->SlotCount->SetText(buffer);
    g_pCGInterface->GetChestGUI()->ShowGWnd(true);
    return 0;
}



void CIFSTChestIcon::OnCIFReady()
{
    printf("> " __FUNCTION__ "\n");

    CIFDecoratedStatic::OnCIFReady();
    sub_633990();

}



