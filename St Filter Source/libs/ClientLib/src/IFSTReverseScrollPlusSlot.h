#pragma once
#include "IFMainFrame.h"

class CIFSTReverseScrollPlusSlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTReverseScrollPlusSlot)
GFX_DECLARE_MESSAGE_MAP(CIFSTReverseScrollPlusSlot)

public:
    CIFSTReverseScrollPlusSlot(void);
    ~CIFSTReverseScrollPlusSlot(void);
    int OnMouseLeftUp(int a1, int x, int y) override;
    bool OnCreate(long ln) override;
    void OnButtonClick();
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;
    CIFButton* MoveTo;
    void WriteLine(const wchar_t* Num, const wchar_t* CharName, const wchar_t* Location, const wchar_t* Move);
};
