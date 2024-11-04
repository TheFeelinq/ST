#include "IFExtQuickSlotSlot.h"
#include "BSLib/Debug.h"
#include "unsorted.h"

GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFExtQuickSlotSlot, 0x00ee9a68)

GFX_IMPLEMENT_DYNCREATE_FN(CIFExtQuickSlotSlot, CIFWnd)

CIFExtQuickSlotSlot::CIFExtQuickSlotSlot() :
        m_UnderBarSlot_hgWnd(NULL) {
    BS_DEBUG_LOW(">" __FUNCTION__ "<")

    SetDragable(true);
}

CIFExtQuickSlotSlot::~CIFExtQuickSlotSlot() {
    BS_DEBUG_LOW(">" __FUNCTION__ "<")
}

bool CIFExtQuickSlotSlot::OnCreate(long ln) {
    BS_DEBUG_LOW(">" __FUNCTION__ "<")
    return true;
}

void CIFExtQuickSlotSlot::RenderMyself() {
    CIFSlotWithHelp *pWnd = GetSlotWndByhgWnd(m_UnderBarSlot_hgWnd);
    if (pWnd)
        pWnd->Func_24(this->GetPos().x, this->GetPos().y);
}

bool CIFExtQuickSlotSlot::Func_28(int a1, int a2, int a3) {
    CIFSlotWithHelp *pWnd = GetSlotWndByhgWnd(m_UnderBarSlot_hgWnd);
    if (pWnd)
        return pWnd->Func_28(a1, a2, a3);;

    return this->Func_28(a1, a2, a3);
}

void CIFExtQuickSlotSlot::OnWndMessage(Event3D *a1) {
    reinterpret_cast<void (__thiscall *)(CIFExtQuickSlotSlot *, Event3D *)>(0x0065fb90)(this, a1);
}

bool CIFExtQuickSlotSlot::Func_25(int a1) {
    return reinterpret_cast<bool (__thiscall *)(CIFExtQuickSlotSlot *, int)>(0x0065fbf0)(this, a1);
}

int CIFExtQuickSlotSlot::OnMouseRightDown(int a1, int x, int y) {
    return reinterpret_cast<bool (__thiscall *)(CIFExtQuickSlotSlot *, int, int, int)>(0x0065fc10)(this, a1, x, y);
}

int CIFExtQuickSlotSlot::OnMouseRightUp(int a1, int x, int y) {
    return reinterpret_cast<bool (__thiscall *)(CIFExtQuickSlotSlot *, int, int, int)>(0x0065fc20)(this, a1, x, y);
}

void CIFExtQuickSlotSlot::UpdatehgWndSlot(CIFWnd *pIFWnd) {
    if (!pIFWnd) {
        m_UnderBarSlot_hgWnd = NULL;
        return;
    }
    m_UnderBarSlot_hgWnd = pIFWnd->GethgWnd();
    pIFWnd->ShowGWnd(false);
}

CIFSlotWithHelp *CIFExtQuickSlotSlot::GetSlotUnderBarBySlothgWnd() const {
    return GetSlotWndByhgWnd(m_UnderBarSlot_hgWnd);
}