
#pragma once
#include "IFMainFrame.h"

#include "IFSTMacroAutoBuffSkillSlot.h"


class CIFSTMacroAutoBuffSkillSlotList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTMacroAutoBuffSkillSlotList)
GFX_DECLARE_MESSAGE_MAP(CIFSTMacroAutoBuffSkillSlotList)

public:
    CIFSTMacroAutoBuffSkillSlotList(void);
    ~CIFSTMacroAutoBuffSkillSlotList(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;

    CIFSTMacroAutoBuffSkillSlot* line1;
    CIFSTMacroAutoBuffSkillSlot* line2;
    CIFSTMacroAutoBuffSkillSlot* line3;
    CIFSTMacroAutoBuffSkillSlot* line4;
    CIFSTMacroAutoBuffSkillSlot* line5;
    CIFSTMacroAutoBuffSkillSlot* line6;
    CIFSTMacroAutoBuffSkillSlot* line7;
    CIFSTMacroAutoBuffSkillSlot* line8;

    void ClearDDJ();
};


