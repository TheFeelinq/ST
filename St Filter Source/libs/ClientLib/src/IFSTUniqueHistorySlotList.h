#pragma once
#include "IFMainFrame.h"
#include "IFSTUniqueHistorySlot.h"


class CIFSTUniqueHistorySlotList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTUniqueHistorySlotList)
GFX_DECLARE_MESSAGE_MAP(CIFSTUniqueHistorySlotList)

public:
    CIFSTUniqueHistorySlotList(void);
    ~CIFSTUniqueHistorySlotList(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;

    CIFSTUniqueHistorySlot* line1;
    CIFSTUniqueHistorySlot* line2;
    CIFSTUniqueHistorySlot* line3;
    CIFSTUniqueHistorySlot* line4;
    CIFSTUniqueHistorySlot* line5;
    CIFSTUniqueHistorySlot* line6;
    CIFSTUniqueHistorySlot* line7;
    CIFSTUniqueHistorySlot* line8;
    CIFSTUniqueHistorySlot* line9;
    CIFSTUniqueHistorySlot* line10;

    void ClearDDJ();
};
