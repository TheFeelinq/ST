#pragma once
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include "IFSTCustomRankSlot.h"

class CIFCustomRankList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFCustomRankList)
GFX_DECLARE_MESSAGE_MAP(CIFCustomRankList)

public:
    CIFCustomRankList(void);
    ~CIFCustomRankList(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
public:
    CIFStatic* m_custom_label2;
    CIFCustomRankSlot* line1;
    CIFCustomRankSlot* line2;
    CIFCustomRankSlot* line3;
    CIFCustomRankSlot* line4;
    CIFCustomRankSlot* line5;
    CIFCustomRankSlot* line6;
    CIFCustomRankSlot* line7;
    CIFCustomRankSlot* line8;
    CIFCustomRankSlot* line9;
    CIFCustomRankSlot* line10;
    CIFCustomRankSlot* line11;


};



