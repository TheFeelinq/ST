#pragma once
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include "IFEdit.h"

class CIFFTWCounter : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFFTWCounter)
GFX_DECLARE_MESSAGE_MAP(CIFFTWCounter)

public:
    CIFFTWCounter(void);
    ~CIFFTWCounter(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
private:
    void On_BtnClick();
    void On_BtnClick1();
    void OnClick_Exit();
public:
    void ResetPosition();
    void WriteLine(BYTE Num, const wchar_t* Charname, const wchar_t* DMG);
    void Clear();
public:
    //CIFStatic* m_custom_label;
    CIFStatic* m_custom_label1;
    //CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;
    CIFStatic* m_custom_label6;
    CIFStatic* m_custom_label7;
    CIFStatic* m_custom_label8;
    CIFStatic* m_custom_label9;
    CIFStatic* m_custom_label10;
    CIFStatic* m_custom_label11;
    CIFStatic* m_custom_label12;
    CIFStatic* m_custom_label13;
    CIFStatic* m_custom_label14;
    CIFStatic* m_custom_label15;
    CIFStatic* m_custom_label16;
    CIFStatic* m_custom_label17;
    CIFStatic* m_custom_label18;
    CIFStatic* m_custom_label19;
    CIFStatic* m_custom_label20;
    CIFStatic* m_custom_label21;
    CIFStatic* m_custom_label22;
    CIFStatic* m_custom_label23;
    CIFStatic* m_custom_label24;
    CIFStatic* m_custom_label25;
    CIFStatic* m_custom_label26;
    CIFStatic* m_custom_label27;
    CIFStatic* m_custom_label28;
    CIFStatic* m_custom_label29;
    CIFStatic* m_custom_label30;
    CIFStatic* m_custom_label31;
    CIFStatic* m_custom_label32;
    CIFFrame* Frame;
    CIFWnd* NormalTitle;

};