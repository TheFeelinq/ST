#pragma once
#include "IFMainFrame.h"


class CIFSTTotalPointSlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTTotalPointSlot)
GFX_DECLARE_MESSAGE_MAP(CIFSTTotalPointSlot)

public:
    CIFSTTotalPointSlot(void);
    ~CIFSTTotalPointSlot(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void WriteLine(const wchar_t* num, const wchar_t* Charname, const wchar_t* Guild);
    void ShowIcon();
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;

};