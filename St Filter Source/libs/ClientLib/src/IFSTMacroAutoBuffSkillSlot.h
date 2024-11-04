
#pragma once
#include "IFMainFrame.h"

class CIFSTMacroAutoBuffSkillSlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTMacroAutoBuffSkillSlot)
GFX_DECLARE_MESSAGE_MAP(CIFSTMacroAutoBuffSkillSlot)

public:
    CIFSTMacroAutoBuffSkillSlot(void);
    ~CIFSTMacroAutoBuffSkillSlot(void);
    bool OnCreate(long ln) override;
    int OnMouseLeftUp(int a1, int x, int y) override;
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;

    void WriteLine(int Race, const wchar_t* SkillName);
};
