//
// Created by Admin on 14/12/2021.
//

#include "IFCOSSetup.h"

#include <windows.h>
#include <shellapi.h>
#include "CPSMission.h"
#include "ClientNet/MsgStreamBuffer.h"
#include "GInterface.h"
#include "ICPlayer.h"
#include "IFParty.h"
#include <iomanip>
#include "BSLib/multibyte.h"
#include "ObjectData.h"
#include "Game.h"
#include "memhelp.h"


#define STCOSSETUP_FILTER_BUTTON 5588

GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFCOSSetup, 0x00eec0e8)
GFX_IMPLEMENT_DYNCREATE_FN(CIFCOSSetup, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFCOSSetup, CIFWnd)
                    ONG_COMMAND(STCOSSETUP_FILTER_BUTTON, &CIFCOSSetup::On_BtnClick)
GFX_END_MESSAGE_MAP()
CIFCOSSetup::CIFCOSSetup(void)
{
    printf("> " __FUNCTION__ "\n");
}
CIFCOSSetup::~CIFCOSSetup(void)
{
    printf("> " __FUNCTION__ "\n");
}

bool CIFCOSSetup::OnCreateIMPL(long ln)
{

    RECT RefReshRect = { 220,263,76,24 };
    bool b = reinterpret_cast<bool (__thiscall *)(CIFCOSSetup *, long)>(0x007a86c0)(this, ln);
    CIFButton* m_mybutton;
    m_mybutton = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), RefReshRect, STCOSSETUP_FILTER_BUTTON, 0);
    m_mybutton->TB_Func_13("interface\\ifcommon\\com_button.ddj",0,0);
    m_mybutton->SetText(TSM_GETTEXTPTR("UIIS_CTL_PET_FILTER"));
    m_mybutton->ShowGWnd(true);
    m_mybutton->BringToFront();
    return  b;
}

void CIFCOSSetup::OnUpdateIMPL() {
    reinterpret_cast<void (__thiscall *)(CIFCOSSetup *)>(0x006528a0)(this);
}
void CIFCOSSetup::On_BtnClick() {
    printf("> " __FUNCTION__ "\n");
}
