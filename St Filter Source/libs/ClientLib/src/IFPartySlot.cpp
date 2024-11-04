

#include "IFPartySlot.h"
#include "GInterface.h"
GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFPartySlot, 0x00EEADF0)

int CIFPartySlot::OnMouseLeftUpIMPL(int a1, int x, int y)
{

    int a =  reinterpret_cast<bool (__thiscall *)(CIFPartySlot *, int,int,int)>(0x0046fd70)(this,a1,x,y);
    if (!m_playerNameValueText->GetNText().empty())
    {
        g_pCGInterface->GetMainPopup()->GetParty()->ClearDDJ();
        this->TB_Func_13("interface\\guild\\gil_bar02_select.ddj", 0, 0);
    }
    return  a;
}
