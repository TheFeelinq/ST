#pragma once
#include "IFMainFrame.h"

class CIFSTUniqueHistorySlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTUniqueHistorySlot)
GFX_DECLARE_MESSAGE_MAP(CIFSTUniqueHistorySlot)

public:
    CIFSTUniqueHistorySlot(void);
    ~CIFSTUniqueHistorySlot(void);
    int OnMouseLeftUp(int a1, int x, int y) override;
    bool OnCreate(long ln) override;
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;

    void WriteLine(const wchar_t* ItemName, const wchar_t* Count, const wchar_t* From, const wchar_t* Date);
};
