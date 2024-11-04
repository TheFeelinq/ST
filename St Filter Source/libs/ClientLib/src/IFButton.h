#pragma once

#include "IFStatic.h"
#include <ghidra/undefined.h>
#include "IFWnd.h"
#include "TextStringManager.h"
class CIFButton : public CIFStatic {
GFX_DECLARE_DYNAMIC_EXISTING(CIFButton, 0x00ee9828)


public:
    /// \address 00655fa0
    void FUN_00655fa0(undefined4 a1);

/// \address 00655ec0
    void SetEnabledState(bool a1);

    /// \brief Maybe sets the hover text
    /// \address 00653DC0
    void sub_653DC0(std::n_wstring *str);

    /// \address 00652D20
    /// \remark Related to setting the hover text
    void sub_652D20(int a2);
/// \address 00656640
    void FUN_00656640(std::n_string textureFileName);

    void FUN_00656040(BYTE a2); //show/hide btn
    void FUN_00656570(BYTE a2);
private:
    char pad_0x0380[0x1C]; //0x0380
    char *m_disabledPath; //0x039C
    char pad_0x03A0[0x18]; //0x03A0
    char *m_pressedPath; //0x03B8
    char pad_0x03BC[0x18]; //0x03BC
};

