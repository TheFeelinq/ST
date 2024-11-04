#pragma once

#include "IFStretchWnd.h"
#include "IFTextBox.h"
#include "IFSlotWithHelp.h"
#include "IFStatic.h"
#include <iostream>


class CIFHelperBubbleWindow : public CIFStretchWnd
{
GFX_DECLARE_DYNAMIC_EXISTING(CIFHelperBubbleWindow, 0x00eebfdc)

public:
    void WriteLine(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void WriteLineGold(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void WriteLineSilk(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void WriteLineGSilk(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void WriteLinePSilk(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void WriteLineGP(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void WriteLineHonorPoint(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void WriteLineTokenSD1(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void WriteLineTokenSD2(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void WriteLineTokenSD3(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void WriteLineTokenSD4(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void WriteLineArenaCoin(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void WriteLineParty(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex);
    void Reset();
    void sub_777020();
    int sub_776C00(wnd_rect* a2, int a3);
    void sub_818690(int a2, int a3);
    void sub_8189F0(float* a2);
public:

    CIFTextBox* m_textBox; //0x07C4
    char pad_0x07C8[0x4]; //0x07C8
    __int32 m_width; //0x07CC
    __int32 m_heigth; //0x07D0
    char pad_0x07D4[0x8]; //0x07D4
    CIFSlotWithHelp* m_ownerWindow; //0x07DC
    CIFStatic* m_circleIcon; //0x07E0  // worked
    CIFStatic* N00006405; //0x07E4
    CIFStatic* m_squareIcon; //0x07E8 //not work
    char pad_0x07EC[0x4]; //0x07EC


BEGIN_FIXTURE()
        //ENSURE_SIZE(0x07F0)

        ENSURE_OFFSET(m_textBox, 0x07C4)
        ENSURE_OFFSET(m_ownerWindow, 0x07DC)
        ENSURE_OFFSET(m_circleIcon, 0x07E0)
        ENSURE_OFFSET(m_width, 0x07CC)
        ENSURE_OFFSET(m_heigth, 0x07D0)
        ENSURE_OFFSET(N00006405, 0x07E4)
        ENSURE_OFFSET(m_squareIcon, 0x07E8)

    END_FIXTURE()

    RUN_FIXTURE(CIFHelperBubbleWindow)
}; //Size=0x07F0