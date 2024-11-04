#include "IFCircularMenuSlot.h"
#include "Game.h"
#include "GFXMainFrame/Controler.h"
#include "BSLib/multibyte.h"
#include "GInterface.h"
#include <BSLib/Debug.h>

#define GDR_SLOT_TEXTURE 10
#define GDR_ICON_TEXTURE 11

GFX_IMPLEMENT_DYNCREATE(CIFCircularMenuSlot, CIFWnd)

GFX_BEGIN_MESSAGE_MAP(CIFCircularMenuSlot, CIFWnd)
                    ONG_VISIBLE_CHANGE()
GFX_END_MESSAGE_MAP()


CIFCircularMenuSlot::CIFCircularMenuSlot(void)
{

}

CIFCircularMenuSlot::~CIFCircularMenuSlot(void)
{

}

bool CIFCircularMenuSlot::OnCreate(long ln)
{
    CIFWnd::OnCreate(ln);

    RECT REC = { 0, 0, 0, 0 };
    m_slot = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), REC, GDR_SLOT_TEXTURE, 0);
    m_slot->SetGWndSize(85, 85);
    m_slot->TB_Func_13("interface\\orbit\\orbit_radialmenu_slot.ddj", 0, 0);

    m_icon = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), REC, GDR_ICON_TEXTURE, 0);
    m_icon->SetGWndSize(85, 85);
    m_icon->TB_Func_13("interface\\orbit\\orbit_icons\\orbit_icon_default.ddj", 0, 0);

    m_slot->BringToFront();
    m_isFocused = false;

    this->ShowGWnd(true);

    return true;
}

void CIFCircularMenuSlot::OnUpdate()
{

}

void CIFCircularMenuSlot::SetSlotId(int slotID)
{
    this->slotId = slotID;
}

int CIFCircularMenuSlot::GetSlotId()
{
    return this->slotId;
}

void CIFCircularMenuSlot::SetPosition(int x, int y)
{
    m_slot->MoveGWnd(x, y);
    m_icon->MoveGWnd(x, y);
}

void CIFCircularMenuSlot::SetIcon(std::n_string str)
{
    m_icon->TB_Func_13(str, 0, 0);
}

void CIFCircularMenuSlot::SetTitle(std::n_wstring title)
{
    m_title = title;
}

std::n_wstring CIFCircularMenuSlot::GetTitle()
{
    return m_title;
}

void CIFCircularMenuSlot::SetDescription(std::n_wstring description)
{
    m_description = description;
}

std::n_wstring CIFCircularMenuSlot::GetDescription()
{
    return m_description;
}

void CIFCircularMenuSlot::SetFocus(bool shouldFocus)
{
    m_isFocused = shouldFocus;
    m_slot->TB_Func_13(
            shouldFocus ? "interface\\orbit\\orbit_radialmenu_slot_focus.ddj" : "interface\\orbit\\orbit_radialmenu_slot.ddj",
            0,
            0);
}

void CIFCircularMenuSlot::SetFade(bool fadeIn)
{
    m_slot->sub_6526E0(fadeIn ? 0 : 255, fadeIn ? 255 : 0, 0.4, 0.0, 1);
    m_icon->sub_6526E0(fadeIn ? 0 : 255, fadeIn ? 255 : 0, 0.4, 0.0, 1);
}

bool CIFCircularMenuSlot::IsFocused() { return m_isFocused; }

void CIFCircularMenuSlot::OnSelect()
{
    //g_pCGInterface->ShowMessage_Warning(L"OnSelect");
}

int CIFCircularMenuSlot::OnVisibleStateChange(int newstate, int a2)
{
    return 0;
}

