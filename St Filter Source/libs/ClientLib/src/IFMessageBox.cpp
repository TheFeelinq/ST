//
// Created by Admin on 19/9/2021.
//

#include "IFMessageBox.h"
#include "GInterface.h"
#include "memhelp.h"
#include "PartyData.h"
#include "CharacterDependentData.h"
#include "IFflorian0Guide.h"
#include "GlobalDataManager.h"
#include "GameDataExt.h"

CIFMessageBox* ReverseWindow;
void CIFMessageBox::CreateReverse(int wndID , int slot)
{
   // printf("WndID %d Slot %d \n",wndID,slot);
    if(wndID==30 )
    {
        if(g_pCICPlayer)
        {
            if (DimenSionalRegion.find(g_pCICPlayer->GetRegion().r) != DimenSionalRegion.end())
            {
                return;
            }
        }

        reinterpret_cast<void(__thiscall*)(CIFMessageBox*,int,int)>(0x00644c90)(this,wndID, slot);
    }
    if(wndID==33 )
    {

        reinterpret_cast<void(__thiscall*)(CIFMessageBox*,int,int)>(0x00644c90)(this,wndID, slot);
        ReverseWindow = this;

        if(ReverseWindow!=0 && ReverseWindow)
        {
            RECT rect_button = {25, 170, 252, 24};
            CIFButton *btn = (CIFButton*)reinterpret_cast<CIFMessageBox *(__cdecl *)(CIFMessageBox *, const CGfxRuntimeClass *, RECT *, int, int)>(0x00BA20B0)(this, GFX_RUNTIME_CLASS(CIFButton), &rect_button, 5555, 0);
            btn->SetText(TSM_GETTEXTPTR("UIIT_ST_PARTY_MEMBER_MOVE_TO"));
            btn->TB_Func_13("interface\\ifcommon\\com_return_button.ddj", 1, 1);
            btn->m_FontTexture.SetColor(0xfbf7d2);
            btn->ShowGWnd(true);
            g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->m_ReverseScollSlot=slot;
            ReverseWindow->SetGWndSize(300,240);
            ReverseWindow->IFBtnCancel->MoveGWnd(ReverseWindow->IFBtnCancel->GetPos().x,btn->GetPos().y+31);
            if(g_pCICPlayer)
            {
                const SPartyData &partyData = g_CCharacterDependentData.GetPartyData();
                if(partyData.NumberOfMembers > 0)
                {
                    btn->SetEnabledState(true);
                    g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->m_BtnState=true;
                } else
                {
                    btn->SetEnabledState(false);
                    g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->m_BtnState=false;
                }
            }
        }

    }
    else
    {

        reinterpret_cast<void(__thiscall*)(CIFMessageBox*,int,int)>(0x00644c90)(this,wndID, slot);
    }

}

void CIFMessageBox::SetGWndSizeIMPL(int width, int height)
{

    if(width==300 && height==204)
    {
        reinterpret_cast<void(__thiscall*)(CIFMessageBox*, int, int)>(0x00652970)(this, width, height);
    }
    else
    {

        reinterpret_cast<void(__thiscall*)(CIFMessageBox*, int, int)>(0x00652970)(this, width, height);
    }

}

void CIFMessageBox::ShowGWndIMPL(bool bVisible)
{
   if(!bVisible)
   {
       if(g_pCGInterface->IsVisible())
            CIFWnd::ShowGWnd(bVisible);
            CIFWnd::BringToFront();
       return;
   }
    if(g_pCGInterface->IsVisible())
    {
        CIFWnd::BringToFront();
        CIFWnd::ShowGWnd(bVisible);
    }
}

