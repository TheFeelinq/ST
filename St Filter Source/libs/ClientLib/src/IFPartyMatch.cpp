//
// Created by Admin on 18/12/2021.
//

#include "IFPartyMatch.h"
#include "IFStatic.h"
#include "TextStringManager.h"
#include "GInterface.h"
#include "Game.h"
#include "GlobalDataManager.h"
#include <ctime>
#include <GFXMainFrame/Controler.h>
GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFPartyMatch, 0x00EEB8CC)

void CIFPartyMatch::FUN_00740750(CIFHelperBubbleWindow* window)
{

    reinterpret_cast<void (__thiscall *)(CIFPartyMatch *, CIFHelperBubbleWindow *)>(0x00740750)(this, window);

}

void CIFPartyMatch::FUN_00740870(char param_1)
{
    reinterpret_cast<void(__thiscall*)(CIFPartyMatch*,BYTE)>(0x00740870)(this, param_1);

    /*CIFStatic* PartyRaceType = this->m_IRM.GetResObj<CIFStatic>(12, 1);
    PartyRaceType->SetGWndSize(16,16);
    if (param_1 == '\0') {

        PartyRaceType->TB_Func_13("interface\\ifcommon\\com_kindred_china16.ddj", 0, 0);
        PartyRaceType->SetText(L"");
    }
    else {
        if (param_1 != '\x01') {
            return;
        }
        PartyRaceType->TB_Func_13("interface\\ifcommon\\com_kindred_europe16.ddj", 0, 0);
        PartyRaceType->SetText(L"");
    }*/
}

void CIFPartyMatch::FUN_00740910(BYTE PatyType)
{
    CIFStatic* PartyIconType = this->m_IRM.GetResObj<CIFStatic>(11, 1);

    switch(PatyType) {
        case 0: //hunting
            PartyIconType->TB_Func_13("interface\\party\\pt_association.ddj", 0, 0);
            break;
        case 1: //quest
            PartyIconType->TB_Func_13("interface\\party\\pt_association.ddj", 0, 0);
            break;
        case 2: //trader
            PartyIconType->TB_Func_13("interface\\ifcommon\\com_job_merchant.ddj", 0, 0);
            break;
        case 3: //thief
            PartyIconType->TB_Func_13("interface\\ifcommon\\com_job_thief.ddj", 0, 0);
            break;

    }
    reinterpret_cast<void(__thiscall*)(CIFPartyMatch*,BYTE)>(0x00740910)(this, PatyType);
}
time_t lastClickTime4;
void CIFPartyMatch::OnUpdateIMPL()
{
    if (g_CurrentIfUnderCursor->IsSame(GFX_RUNTIME_CLASS(CIFStatic)))
    {
        CIFStatic* CurSlot = (CIFStatic*)g_CurrentIfUnderCursor;
        if(g_Controler->RBUTTON_Mouse && !CurSlot->GetNText().empty())
        {
            if(m_PartyMatchSlotSelected && m_PartyMatchSlotSelected != NULL)
            {
                POINT mMouse;
                GetCursorPos(&mMouse);
                POINT m_show_point;
                RECT r1;
                GetWindowRect(theApp.GetHWnd(), &r1);
                m_show_point.x = mMouse.x - (r1.left);
                m_show_point.y = mMouse.y - r1.top;

                g_pCGInterface->GetCIFSTPartyMatchMemberViewerGUI()->ShowGWnd(true);
                g_pCGInterface->GetCIFSTPartyMatchMemberViewerGUI()->MoveGWnd(m_show_point.x, m_show_point.y);
                g_pCGInterface->GetCIFSTPartyMatchMemberViewerGUI()->BringToFront();
                if((time(NULL) - lastClickTime4 > 1)) {

                    if ((wcscmp(m_PartyMatchSlotSelected->GetPartyMatchSlotByID(16), L"1/4") == 0) || (wcscmp(m_PartyMatchSlotSelected->GetPartyMatchSlotByID(16), L"1/8") == 0))
                    {
                        g_pCGInterface->ShowMessage_Warning(TSM_GETTEXTPTR("UIIT_ST_PARTY_MATCH_TOOLTIP"));
                    }
                    if (wcscmp(m_PartyMatchSlotSelected->GetPartyMatchSlotByID(15), TSM_GETTEXTPTR("UIIT_CTL_PARTYMATCH_PSEARCH_OBJECTTRADE")) == 0)
                    {
                        lastClickTime4 = time(NULL);
                        CMsgStreamBuffer buf(0x7093);
                        buf << (BYTE)1;
                        buf << (BYTE)2;
                        buf <<  std::n_string(TO_NSTRING(m_PartyMatchSlotSelected->m_MasterOfParty));
                        SendMsg(buf);
                    } else
                    {
                        lastClickTime4 = time(NULL);
                        CMsgStreamBuffer buf(0x7093);
                        buf << (BYTE)1;
                        buf << (BYTE)1;
                        buf <<  std::n_string(TO_NSTRING(m_PartyMatchSlotSelected->m_MasterOfParty));
                        SendMsg(buf);
                    }

                }
            }
        }
        if (CurSlot->GetNText().empty())
        {
            g_pCGInterface->GetCIFSTPartyMatchMemberViewerGUI()->Clear();
            CIFSTPartyMatchMemberViewer::PartyMatchMemberList.clear();
            g_pCGInterface->GetCIFSTPartyMatchMemberViewerGUI()->ShowGWnd(false);
        }
    }
    reinterpret_cast<void(__thiscall*)(CIFPartyMatch*)>(0x006528a0)(this);
}
int CIFPartyMatch::OnMouseLeftUpIMPL(int a1, int x, int y)
{
    int a =  reinterpret_cast<bool (__thiscall *)(CIFPartyMatch *, int,int,int)>(0x006523d0)(this,a1,x,y);


    return  a;
}
