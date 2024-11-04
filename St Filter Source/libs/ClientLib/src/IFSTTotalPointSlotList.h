#pragma once
#include "IFMainFrame.h"
#include "IFSTTotalPointSlot.h"


class CIFSTTotalPointSlotList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTTotalPointSlotList)
GFX_DECLARE_MESSAGE_MAP(CIFSTTotalPointSlotList)

public:
    CIFSTTotalPointSlotList(void);
    ~CIFSTTotalPointSlotList(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;

    CIFSTTotalPointSlot* line1;
    CIFSTTotalPointSlot* line2;
    CIFSTTotalPointSlot* line3;
    CIFSTTotalPointSlot* line4;
    CIFSTTotalPointSlot* line5;
    CIFSTTotalPointSlot* line6;
    CIFSTTotalPointSlot* line7;


    void ClearDDJ();
};
