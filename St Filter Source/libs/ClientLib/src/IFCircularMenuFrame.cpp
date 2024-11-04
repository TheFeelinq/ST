#include "IFCircularMenuFrame.h"
#include "GEffSoundBody.h"
#include "Game.h"

GFX_IMPLEMENT_DYNCREATE(CIFCircularMenuFrame, CIFDecoratedStatic)

bool CIFCircularMenuFrame::OnCreate(long ln)
{
    CIFDecoratedStatic::OnCreate(ln);

    SetGWndSize(550, 550);
    TB_Func_13("interface\\orbit\\orbit_radialmenu\\orbit_radialmenu.ddj", 0, 0);
    sub_634470("interface\\orbit\\orbit_radialmenu\\orbit_radialmenu_0.ddj");

    set_N00009BD4(2);
    set_N00009BD3(500);

    return true;
}

void CIFCircularMenuFrame::SetIcon(std::n_string str)
{
    sub_634470(str);
}

void CIFCircularMenuFrame::OnCIFReady()
{
    CIFDecoratedStatic::OnCIFReady();
    sub_633990();
}
