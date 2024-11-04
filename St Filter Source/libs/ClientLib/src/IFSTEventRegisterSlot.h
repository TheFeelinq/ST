#pragma once
#include "IFMainFrame.h"

class CIFSTEventRegisterSlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTEventRegisterSlot)
GFX_DECLARE_MESSAGE_MAP(CIFSTEventRegisterSlot)

public:
    CIFSTEventRegisterSlot(void);
    ~CIFSTEventRegisterSlot(void);

    bool OnCreate(long ln) override;
    void WriteLine(const wchar_t* EventName);
    void ClearText();
    void SetColor();
    int OnMouseLeftUp(int a1, int x, int y) override;
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;

};

