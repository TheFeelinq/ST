
#pragma once
#include "IFMainFrame.h"

class CIFSTMacroAutoBuffedSkillSlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTMacroAutoBuffedSkillSlot)
GFX_DECLARE_MESSAGE_MAP(CIFSTMacroAutoBuffedSkillSlot)

public:
    CIFSTMacroAutoBuffedSkillSlot(void);
    ~CIFSTMacroAutoBuffedSkillSlot(void);
    bool OnCreate(long ln) override;
    int OnMouseLeftUp(int a1, int x, int y) override;
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;

    void WriteLine(int Race, int SkillID);
};

