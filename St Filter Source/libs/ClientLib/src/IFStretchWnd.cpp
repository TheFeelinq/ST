#include "IFStretchWnd.h"


//GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFStretchWnd, 0x00eecb74)
void CIFStretchWnd::SetEdgeTextures(const std::n_string &left, const std::n_string &top, const std::n_string &right,
                                    const std::n_string &bottom) {
    reinterpret_cast<void (__thiscall *)(CIFStretchWnd *,
                                         const std::n_string,
                                         const std::n_string,
                                         const std::n_string,
                                         const std::n_string)>(0x00819690)(this, left, top, right, bottom);
}

void CIFStretchWnd::SetCornerTextures(const std::n_string &cornerTexturePath) {
    reinterpret_cast<void (__thiscall *)(CIFStretchWnd *, std::n_string)>(0x008199e0)(this, cornerTexturePath);
}
