#pragma once
#include "IFMainFrame.h"


class CIFSTCustomNPCSlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTCustomNPCSlot)
GFX_DECLARE_MESSAGE_MAP(CIFSTCustomNPCSlot)

public:
    CIFSTCustomNPCSlot(void);
    ~CIFSTCustomNPCSlot(void);
    int OnMouseLeftUp(int a1, int x, int y) override;
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void WriteLine(const wchar_t* num, std::n_string ItemName, const wchar_t* Count, const wchar_t* Price);
    void ShowIcon();
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;
};