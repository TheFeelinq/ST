#include "../../../DevKit_DLL/src/StdAfx.h"
#include "IFTaiXiuIcon.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include "ClientNet/MsgStreamBuffer.h"
#include "CPSMission.h"
#include "IFSTTaiXiu.h"

GFX_IMPLEMENT_DYNCREATE(CIFTaiXiu, CIFDecoratedStatic)


bool CIFTaiXiu::OnCreate(long ln)
{
    printf("> " __FUNCTION__ "(%d)\n", ln);
    CIFDecoratedStatic::OnCreate(ln);

    TB_Func_13("icon\\etc\\taixiu_1.ddj", 0, 0);
    sub_634470("icon\\etc\\taixiu_2.ddj");
    //sub_634470("icon\\etc\\facebook_2.ddj");
    set_N00009BD4(2);
    set_N00009BD3(500);

    CGEffSoundBody::get()->PlaySound(L"snd_quest");

    return true;
}

int CIFTaiXiu::OnMouseLeftUp(int a1, int x, int y)
{
    printf("> " __FUNCTION__ "(%d, %d, %d)\n", a1, x, y);
    CMsgStreamBuffer buf(0x1318);
    buf << std::n_string("!TAIXIUUP");
    buf << std::n_string("!TAIXIUUP");
    SendMsg(buf);
    CGEffSoundBody::get()->PlaySound(L"snd_quest");
    g_pCGInterface->m_IRM.GetResObj(5092, 1)->ShowGWnd(true);
    CIFSTTaiXiu* main10 = g_pCGInterface->m_IRM.GetResObj<CIFSTTaiXiu>(5092, 1);
    main10->gold = false;
    main10->silk = true;
    main10->gilf=false;
    main10->m_mybutton12 ->TB_Func_13("interface\\ifcommon\\ngt\\checkbutton_off.ddj", 0, 0);
    main10->m_mybutton11 ->TB_Func_13("interface\\ifcommon\\ngt\\checkbutton_on.ddj", 0, 0);
    main10->m_mybutton10 ->TB_Func_13("interface\\ifcommon\\ngt\\checkbutton_off.ddj", 0, 0);
    main10->ResetPosition();
    return 0;
}



void CIFTaiXiu::OnCIFReady()
{
    printf("> " __FUNCTION__ "\n");

    CIFDecoratedStatic::OnCIFReady();
    sub_633990();

}



