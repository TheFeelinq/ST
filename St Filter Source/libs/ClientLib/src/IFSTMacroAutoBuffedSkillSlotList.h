
#pragma once
#include "IFMainFrame.h"
#include "IFSTMacroAutoBuffedSkillSlot.h"


class CIFSTMacroAutoBuffedSkillSlotList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTMacroAutoBuffedSkillSlotList)
GFX_DECLARE_MESSAGE_MAP(CIFSTMacroAutoBuffedSkillSlotList)

public:
    CIFSTMacroAutoBuffedSkillSlotList(void);
    ~CIFSTMacroAutoBuffedSkillSlotList(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;

    CIFSTMacroAutoBuffedSkillSlot* line1;
    CIFSTMacroAutoBuffedSkillSlot* line2;
    CIFSTMacroAutoBuffedSkillSlot* line3;
    CIFSTMacroAutoBuffedSkillSlot* line4;
    CIFSTMacroAutoBuffedSkillSlot* line5;
    CIFSTMacroAutoBuffedSkillSlot* line6;
    CIFSTMacroAutoBuffedSkillSlot* line7;
    CIFSTMacroAutoBuffedSkillSlot* line8;

    void ClearDDJ();
};


