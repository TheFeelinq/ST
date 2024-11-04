
#pragma once
#include "IFMainFrame.h"


class CIFSTEventXoSoMienBacLichSuSlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTEventXoSoMienBacLichSuSlot)
GFX_DECLARE_MESSAGE_MAP(CIFSTEventXoSoMienBacLichSuSlot)

public:
    CIFSTEventXoSoMienBacLichSuSlot(void);
    ~CIFSTEventXoSoMienBacLichSuSlot(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void WriteLine(const wchar_t* num, const wchar_t* so, const wchar_t* tiencuoc, const wchar_t* trangthai,const wchar_t* loaitiente,const wchar_t* theloai,const wchar_t* ngay);

public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;
    CIFStatic* m_custom_label6;
    CIFStatic* m_custom_label7;
};


