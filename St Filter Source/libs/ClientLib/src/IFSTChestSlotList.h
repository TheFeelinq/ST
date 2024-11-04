#pragma once
#include "IFMainFrame.h"
#include "IFSTChestSlot.h"

class CIFPlayerChestSlotList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFPlayerChestSlotList)
GFX_DECLARE_MESSAGE_MAP(CIFPlayerChestSlotList)

public:
    CIFPlayerChestSlotList(void);
    ~CIFPlayerChestSlotList(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;

    CIFPlayerChestSlot* line1;
    CIFPlayerChestSlot* line2;
    CIFPlayerChestSlot* line3;
    CIFPlayerChestSlot* line4;
    CIFPlayerChestSlot* line5;
    CIFPlayerChestSlot* line6;
    CIFPlayerChestSlot* line7;
    CIFPlayerChestSlot* line8;
    CIFPlayerChestSlot* line9;
    CIFPlayerChestSlot* line10;

    void ClearDDJ();
};
