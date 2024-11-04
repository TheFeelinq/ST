
#pragma once
#include "IFMainFrame.h"
#include "IFSTMacroAutoBuffSlot.h"


class CIFSTMacroAutoBuffSlotList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTMacroAutoBuffSlotList)
GFX_DECLARE_MESSAGE_MAP(CIFSTMacroAutoBuffSlotList)

public:
    CIFSTMacroAutoBuffSlotList(void);
    ~CIFSTMacroAutoBuffSlotList(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;

    CIFSTMacroAutoBuffSlot* line1;
    CIFSTMacroAutoBuffSlot* line2;
    CIFSTMacroAutoBuffSlot* line3;
    CIFSTMacroAutoBuffSlot* line4;
    CIFSTMacroAutoBuffSlot* line5;
    CIFSTMacroAutoBuffSlot* line6;
    CIFSTMacroAutoBuffSlot* line7;
    CIFSTMacroAutoBuffSlot* line8;

    void ClearDDJ();
};

