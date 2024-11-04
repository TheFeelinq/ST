#include "StdAfx.h"
#include "IFButton.h"
GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFButton, 0x00ee9828)
void CIFButton::FUN_00655fa0(undefined4 a1) {
    reinterpret_cast<void (__thiscall *)(CIFButton *, undefined4)>(0x00655fa0)(this, a1);
}
void CIFButton::SetEnabledState(bool a1) {
    reinterpret_cast<void (__thiscall *)(CIFButton *, bool)>(0x00655ec0)(this, a1);
}
void CIFButton::sub_653DC0(std::n_wstring *str) {
    reinterpret_cast<void (__thiscall *)(CIFButton *, std::n_wstring *)>(0x653DC0)(this, str);
}

void CIFButton::sub_652D20(int a2) {
    reinterpret_cast<void (__thiscall *)(CIFButton *, int)>(0x652D20)(this, a2);
}
void CIFButton::FUN_00656040(BYTE a2)  {
    reinterpret_cast<void (__thiscall *)(CIFButton *, BYTE)>(0x00656040)(this, a2);
}
void CIFButton::FUN_00656570(BYTE a2) {
    reinterpret_cast<void (__thiscall *)(CIFButton *, BYTE)>(0x00656040)(this, a2);
}
void CIFButton::FUN_00656640(std::n_string textureFileName) {
    reinterpret_cast<void(__thiscall *)(CIFButton *, std::n_string)>(0x00656640)(this, textureFileName);
}
