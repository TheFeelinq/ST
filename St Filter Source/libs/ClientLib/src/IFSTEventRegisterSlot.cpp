#include "IFSTEventRegisterSlot.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <ICPlayer.h>
#include <BSLib\multiBYTE.h>
#include "ICPlayer.h"
#include "IFflorian0Guide.h"
#include <BSLib/Debug.h>

#define STSRO_SLOT_EVENTNAME 11
#define STSRO_SLOT_DAY 12
#define STSRO_SLOT_EVENTTIME 13
#define STSRO_SLOT_STATE 14

GFX_IMPLEMENT_DYNCREATE(CIFSTEventRegisterSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTEventRegisterSlot, CIFWnd)
GFX_END_MESSAGE_MAP()

CIFSTEventRegisterSlot::CIFSTEventRegisterSlot(void)
{
    // BS_DEBUG("> " __FUNCTION__);
}


CIFSTEventRegisterSlot::~CIFSTEventRegisterSlot(void)
{
    // BS_DEBUG("> " __FUNCTION__);
}

bool CIFSTEventRegisterSlot::OnCreate(long ln)
{
    // Populate inherited members
    CIFWnd::OnCreate(ln);

    TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);

    RECT line1rect = { 2,5,220,13 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), line1rect, STSRO_SLOT_EVENTNAME, 0);
    m_custom_label1->SetTextColor(0xffffff);

    this->ShowGWnd(false);
    return true;
}

void CIFSTEventRegisterSlot::WriteLine(const wchar_t* EventName)
{
    m_custom_label1->SetText(EventName);

}
void CIFSTEventRegisterSlot::ClearText()
{
    m_custom_label1->SetText(L"");

}
void CIFSTEventRegisterSlot::SetColor()
{
    m_custom_label1->SetTextColor(D3DCOLOR_ARGB(255, 0, 255, 0));

}
int CIFSTEventRegisterSlot::OnMouseLeftUp(int a1, int x, int y)
{
    if (!m_custom_label1->GetNText().empty())
    {
        g_pCGInterface->GetEventRegisterGUI()->ClearDDJ();
        g_pCGInterface->GetEventRegisterGUI()->SelectedItemName = m_custom_label1->GetNText();
        TB_Func_13("interface\\ifcommon\\com_bar01select_mid.ddj", 0, 0);
    }
    return 0;
}