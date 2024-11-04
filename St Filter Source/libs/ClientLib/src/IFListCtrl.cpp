#include "IFListCtrl.h"

void CIFListCtrl::SetHighlightColor(D3DCOLOR color) {
    m_BackgroundColor = color;
}

void CIFListCtrl::SetHightlineLine(bool a2) {
    m_bHighlighLine = a2;
}

bool CIFListCtrl::OnCreate(long ln) {
    return true;
}

CIFListCtrl::SLineOfText* CIFListCtrl::sub_63A940() {
    return reinterpret_cast<CIFListCtrl::SLineOfText*(__thiscall*)(CIFListCtrl*)>(0x63A940)(this);
}

int CIFListCtrl::GetNumberOfItems() const {
    return m_numberOfItems;
}

void CIFListCtrl::SetLineHeight(int height) {
    m_LineHeight = height;
}
CIFListCtrl::SLineOfText* CIFListCtrl::GetTextByIndex(int index) {
    int* piVar1;
    int iVar2;

    iVar2 = 0;
    if (*(int*)((int)this + 0x3bc) == 0) {
        return 0;
    }
    piVar1 = *(int**)((int)this + 0x3b8);
    while (true) {
        piVar1 = (int*)*piVar1;
        if (piVar1 == (int*)*(int*)((int)this + 0x3b8)) {
            return 0;
        }
        if (iVar2 == index) break;
        if (piVar1 == (int*)*(int*)((int)this + 0x3b8)) goto LAB_0063a980;
        iVar2 = iVar2 + 1;
    }
    if (piVar1 != (int*)*(int*)((int)this + 0x3b8)) {
        return (CIFListCtrl::SLineOfText*)(piVar1 + 2);
    }
    LAB_0063a980:
    return reinterpret_cast<CIFListCtrl::SLineOfText * (__thiscall*)(CIFListCtrl*)>(0x639500)(this);
}