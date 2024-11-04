#pragma once


#include "IFMainFrame.h"
#include "IFButton.h"
#include "IFStatic.h"
#include "IFEdit.h"
#include "IFSlotWithHelp.h"
#include <iostream>
#include <sstream>
#include <cstring>


class CIFCOSSetup : public CIFFrame { //0x036C
GFX_DECLARE_DYNAMIC_EXISTING(CIFCOSSetup, 0x00eec0e8)

    GFX_DECLARE_DYNCREATE_FN(CIFCOSSetup)

GFX_DECLARE_MESSAGE_MAP(CIFCOSSetup)

public:
//FUN_007a83e0
    CIFCOSSetup(void);
    ~CIFCOSSetup(void);
    void On_BtnClick();
    /// \address 007a86c0
    bool OnCreateIMPL(long ln);
    /// \address  006528a0
    void OnUpdateIMPL() ;




}; // size 0x374
