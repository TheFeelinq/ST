
#include "NIFFrame.h"
#include <BSLib/Debug.h>
GFX_IMPLEMENT_DYNAMIC_EXISTING(CNIFFrame, 0x115DF28)

bool CNIFFrame::OnCreate(long ln) {
    return reinterpret_cast<bool(__thiscall*)(CNIFFrame*, long)>(0x00473670)(this, ln);
}

void CNIFFrame::RenderMyself() {
    reinterpret_cast<void (__thiscall *)(CNIFFrame *)>(0x004736a0)(this);
}

/*void CNIFFrame::Func_49(std::n_string str) {
    BS_DEBUG_LOW("%s (\"%s\")", __FUNCTION__, str.c_str());
    reinterpret_cast<void (__thiscall *)(CNIFFrame *, std::n_string)>(0x0046c330)(this, str);
}*/
