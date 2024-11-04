#pragma once
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include "IFSTCustomNPCSlot.h"

class CIFSTCustomNPCList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTCustomNPCList)
GFX_DECLARE_MESSAGE_MAP(CIFSTCustomNPCList)

public:
    CIFSTCustomNPCList(void);
    ~CIFSTCustomNPCList(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void ClearDDJ();
public:
    CIFStatic* m_custom_label2;
    CIFSTCustomNPCSlot* line1;
    CIFSTCustomNPCSlot* line2;
    CIFSTCustomNPCSlot* line3;
    CIFSTCustomNPCSlot* line4;
    CIFSTCustomNPCSlot* line5;
    CIFSTCustomNPCSlot* line6;
    CIFSTCustomNPCSlot* line7;
    CIFSTCustomNPCSlot* line8;
    CIFSTCustomNPCSlot* line9;
    CIFSTCustomNPCSlot* line10;
    CIFSTCustomNPCSlot* line11;


};



