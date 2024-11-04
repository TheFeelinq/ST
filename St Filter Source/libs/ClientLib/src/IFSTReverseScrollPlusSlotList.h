#pragma once
#include "IFMainFrame.h"
#include "IFSTReverseScrollPlusSlot.h"


class CIFSTReverseScrollPlusSlotList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTReverseScrollPlusSlotList)
GFX_DECLARE_MESSAGE_MAP(CIFSTReverseScrollPlusSlotList)

public:
    CIFSTReverseScrollPlusSlotList(void);
    ~CIFSTReverseScrollPlusSlotList(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;

    CIFSTReverseScrollPlusSlot* line1;
    CIFSTReverseScrollPlusSlot* line2;
    CIFSTReverseScrollPlusSlot* line3;
    CIFSTReverseScrollPlusSlot* line4;
    CIFSTReverseScrollPlusSlot* line5;
    CIFSTReverseScrollPlusSlot* line6;
    CIFSTReverseScrollPlusSlot* line7;
    CIFSTReverseScrollPlusSlot* line8;


    void ClearDDJ();
};
