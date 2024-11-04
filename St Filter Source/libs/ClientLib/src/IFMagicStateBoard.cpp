//
// Created by Admin on 3/2/2022.
//

#include "IFMagicStateBoard.h"
#include "IFPlayerMiniInfo.h"
#include "GInterface.h"

GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFMagicStateBoard, 0x00EEC928)

bool CIFMagicStateBoard::OnCreateIMPL(long ln) {

    bool b = reinterpret_cast<bool (__thiscall *)(CIFMagicStateBoard *, long)>(0x007feda0)(this, ln);
       // CIFWnd* Info = this->m_IRM.GetResObj<CIFWnd>(22, 1);


    return b;
}
void CIFMagicStateBoard::OnUpdateIMPL()
{
    CIFPlayerMiniInfo *main12 = g_pCGInterface->m_IRM.GetResObj<CIFPlayerMiniInfo>(11, 1);
    this->MoveGWnd(main12->GetPos().x + 239, this->GetPos().y);
    reinterpret_cast<void (__thiscall *)(CIFMagicStateBoard *)>(0x008056a0)(this);
}
