//
// Created by Admin on 29/1/2022.
//

#include "NIFGuildWnd.h"
#include "GlobalDataManager.h"
#include "CPSMission.h"
#include "NIFButton.h"


GFX_IMPLEMENT_DYNAMIC_EXISTING(CNIFGuildWnd, 0xEE8750)

bool CNIFGuildWnd::OnCreateIMPL(long ln) {


    bool b = reinterpret_cast<bool (__thiscall *)(CNIFGuildWnd *, long)>(0x00479a50)(this, ln);

    RECT rect_button = {370, 384, 112, 24};
    CIFButton * m_ChangeGrantName = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), rect_button, 5590, 0);
    m_ChangeGrantName->SetText(TSM_GETTEXTPTR("UIIT_STT_GUILD_NAME_GRANT"));

    m_ChangeGrantName->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj",0,0);
    //m_ChangeGrantName->MoveGWnd(CancelBtn->GetPos().x+87,CancelBtn->GetPos().y);
    m_ChangeGrantName->BringToFront();
    m_ChangeGrantName->ShowGWnd(true);
    //ChangeGrantName->SetEnabledState(true);

    return b;
}
void CNIFGuildWnd::OnUpdateIMPL()
{
    reinterpret_cast<void (__thiscall *)(CNIFGuildWnd *)>(0x0046cd80)(this);
}

