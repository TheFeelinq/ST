#pragma once
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include "IFSTEventXoSoMienBacLichSuSlot.h"


class CIFSTEventXoSoMienBacLichSuSlotList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTEventXoSoMienBacLichSuSlotList)
GFX_DECLARE_MESSAGE_MAP(CIFSTEventXoSoMienBacLichSuSlotList)

public:
    CIFSTEventXoSoMienBacLichSuSlotList(void);
    ~CIFSTEventXoSoMienBacLichSuSlotList(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void ClearDDJ();
public:

    CIFSTEventXoSoMienBacLichSuSlot* line1;
    CIFSTEventXoSoMienBacLichSuSlot* line2;
    CIFSTEventXoSoMienBacLichSuSlot* line3;
    CIFSTEventXoSoMienBacLichSuSlot* line4;
    CIFSTEventXoSoMienBacLichSuSlot* line5;
    CIFSTEventXoSoMienBacLichSuSlot* line6;
    CIFSTEventXoSoMienBacLichSuSlot* line7;
    CIFSTEventXoSoMienBacLichSuSlot* line8;
    CIFSTEventXoSoMienBacLichSuSlot* line9;
    CIFSTEventXoSoMienBacLichSuSlot* line10;
    CIFSTEventXoSoMienBacLichSuSlot* line11;


};



