//
// Created by Admin on 19/9/2021.
//

#include "IFMessageBoxButton.h"


void CIFMessageBoxButton::SetGWndSize(int width, int height)
{
    reinterpret_cast<void(__thiscall*)(CIFMessageBoxButton*, int, int)>(0x00652970)(this, width, height);
}

void CIFMessageBoxButton::MoveGWnd(int x, int y)
{
    reinterpret_cast<void(__thiscall*)(CIFMessageBoxButton*, int, int)>(0x006529A0)(this, x, y);
}

bool CIFMessageBoxButton::SetText(const wchar_t * src)
{
    return reinterpret_cast<bool(__thiscall*)(CIFMessageBoxButton*, const wchar_t*)>(0x00653AC0)(this, src);
}
