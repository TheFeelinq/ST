//
// Created by Admin on 21/12/2021.
//

#include "IFPartyMatchReqJoin.h"
#include "GlobalDataManager.h"
#include "CPSMission.h"
#include "GameDataExt.h"


GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFPartyMatchReqJoin, 0x00EEB92C)

bool CIFPartyMatchReqJoin::OnCreateIMPL(long ln) {


    bool b = reinterpret_cast<bool (__thiscall *)(CIFPartyMatchReqJoin *, long)>(0x007400c0)(this, ln);

    RECT rect_button = {245, 315, 76, 24};
    CIFButton* CancelBtn = (CIFButton*)m_IRM.GetResObj<CIFButton>(46, 1);
    CIFButton* AcceptBtn = (CIFButton*)m_IRM.GetResObj<CIFButton>(45, 1);
    CancelBtn->MoveGWnd(CancelBtn->GetPos().x-45,CancelBtn->GetPos().y);
    AcceptBtn->MoveGWnd(AcceptBtn->GetPos().x-45,AcceptBtn->GetPos().y);

    m_BlockBtn = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), rect_button, 5589, 0);
    m_BlockBtn->SetText(L"Block");
    m_BlockBtn->TB_Func_13("interface\\ifcommon\\com_button.ddj",0,0);
    m_BlockBtn->MoveGWnd(CancelBtn->GetPos().x+87,CancelBtn->GetPos().y);
    D3DCOLOR Colors = AcceptBtn->m_FontTexture.GetFontColor();
    m_BlockBtn->m_FontTexture.SetColor(Colors);
    m_BlockBtn->BringToFront();
    m_BlockBtn->ShowGWnd(true);



    return b;
}
void CIFPartyMatchReqJoin::OnUpdateIMPL()
{
    if (Blocked_Party_CharNameRequest.find(CPSMission::CharNameRequest.c_str()) != Blocked_Party_CharNameRequest.end())
    {
        this->OnCloseWnd();
    }

    reinterpret_cast<void (__thiscall *)(CIFPartyMatchReqJoin *)>(0x006528a0)(this);
}
