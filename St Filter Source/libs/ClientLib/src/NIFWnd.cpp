#include "NIFWnd.h"

GFX_IMPLEMENT_DYNAMIC_EXISTING(CNIFWnd, 0x115DEA0)

GFX_BEGIN_MESSAGE_MAP(CNIFWnd, CObjChild)
                    ONG_WM_4001()
                    ONG_WM_4006()
GFX_END_MESSAGE_MAP()
void CNIFWnd::ShowGWnd(bool bVisible) {
    reinterpret_cast<void (__thiscall *)(CNIFWnd *, bool)>(0x0046d760)(this, bVisible);
}
// CIFWnd::On4001(int,int) .text 00652390 00000012 00000000 00000000 R . . . . . .
int CNIFWnd::On4001(int a2, int a3)
{
    return reinterpret_cast<int(__thiscall*)(CNIFWnd*,int,int)>(0x0046c810)(this, a2, a3);
}

// CIFWnd::On4006(int,int) .text 006523B0 00000012 00000000 00000000 R . . . . . .
int CNIFWnd::On4006(int a2, int a3)
{
    return reinterpret_cast<int(__thiscall*)(CNIFWnd*,int,int)>(0x0046c830)(this, a2, a3);
}
void CNIFWnd::SetSomeRect(const RECT &rect) {
    m_someRECT = rect;
}
const wchar_t* CNIFWnd::GetText()
{
    return m_innerText.c_str();
}
CNIFWnd *CNIFWnd::LoadResObj(int Id)
{
    return reinterpret_cast<CNIFWnd *(__thiscall *)(CNIFWnd *, int)>(0x0046e060)(this, Id);
}