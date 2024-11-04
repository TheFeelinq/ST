#include "IFHelperBubbleWindow.h"
#include "TextStringManager.h"
#include "StdAfx.h"
#include "CharacterDependentData.h"
#include "IFflorian0Guide.h"
#include <sstream>
GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFHelperBubbleWindow, 0x00eebfdc)

std::wstring Tien(std::wstring text)
{

    if (text.size() >= 4) {

        std::wstring unit = text.substr(text.size() - 4);

        if (unit == TSM_GETTEXTPTR("UIIT_STT_GOLD"))
        {
                std::wstring amountNumberText = text.substr(0, text.find(unit)).substr(text.find(L": ") + 1);

                std::wstring unitName = text.substr(0, text.find(amountNumberText));

                std::stringstream buffer(acp_encode(amountNumberText));
                long unitAmount;
                buffer >> unitAmount;

                std::wstring commafiedAmount;
                int cnt = 0;
                do
                {
                    commafiedAmount.insert(0, 1, char('0' + unitAmount % 10));
                    unitAmount /= 10;
                    if (++cnt == 3 && unitAmount)
                    {
                        commafiedAmount.insert(0, 1, ',');
                        cnt = 0;
                    }
                } while (unitAmount);

                text = unitName + L" " + commafiedAmount + L" " + unit;

            return  text;
        }
    }
}

void CIFHelperBubbleWindow::WriteLine(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex)
{
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, ForegroundColor, a4, FontIndex);
}
void CIFHelperBubbleWindow::WriteLineGold(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex) //1
{
    std::wstring text1 = Tien(text);
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this,&text1, a2, 0xFFCCFF00, a4, FontIndex);
}
void CIFHelperBubbleWindow::WriteLineSilk(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex) //2
{
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, 0xFFFFCC00, a4, FontIndex);
}
void CIFHelperBubbleWindow::WriteLineGSilk(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex) //4
{
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, 0xFF00FF00, a4, FontIndex);
}
void CIFHelperBubbleWindow::WriteLinePSilk(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex) //16
{
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, 0xFFFF9966, a4, FontIndex);
}
void CIFHelperBubbleWindow::WriteLineGP(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex) //8
{
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, 0xFFFF9900, a4, FontIndex);
}
void CIFHelperBubbleWindow::WriteLineHonorPoint(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex) //8
{
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, 0xFF006666, a4, FontIndex);
}
void CIFHelperBubbleWindow::WriteLineTokenSD1(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex) //8
{
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, 0xFFFF3366, a4, FontIndex);
}
void CIFHelperBubbleWindow::WriteLineTokenSD2(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex) //8
{
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, 0xFF663366, a4, FontIndex);
}
void CIFHelperBubbleWindow::WriteLineTokenSD3(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex) //8
{
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, 0xFF003399, a4, FontIndex);
}
void CIFHelperBubbleWindow::WriteLineTokenSD4(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex) //8
{
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, 0xFFFF0099, a4, FontIndex);
}
void CIFHelperBubbleWindow::WriteLineArenaCoin(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex) //8
{
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, 0xFFCC33FF, a4, FontIndex);
}
void CIFHelperBubbleWindow::WriteLineParty(std::wstring& text, int a2, UINT ForegroundColor, int a4, BYTE FontIndex)
{
   /* const SPartyData &partyData = g_CCharacterDependentData.GetPartyData();
    std::wstring CharName;
    for (int i = 0; i < partyData.NumberOfMembers; ++i) {
        const SPartyMemberData &memberData = g_CCharacterDependentData.GetPartyMemberData(i);

        CharName = memberData.m_charactername.c_str();


    }*/
    //CIFflorian0Guide::CIFSTMacroGUI->ShowGWnd(true);
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, std::wstring*, int, UINT, int, BYTE)>(0x00776D20)(this, &text, a2, 0xFFFF0099, a4, FontIndex);
}

#include <IFHelperBubbleWindow.h>
#include <Game.h>

void CIFHelperBubbleWindow::Reset() {
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*)>(0x776A00)(this);
}
void CIFHelperBubbleWindow::sub_777020() {
    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*)>(0x777020)(this);
}
int CIFHelperBubbleWindow::sub_776C00(wnd_rect* a2,int a3) {
    //char* v5; // ecx
    //int v6; // ebx
    //int v7; // esi
    //int v8; // ebx
    //int v9; // ebp
    //int v10; // esi
    //int v11; // kr04_4
    //float v12; // edx
    //int result; // eax
    //float v14; // [esp+Ch] [ebp-Ch] BYREF
    //float v15; // [esp+10h] [ebp-8h]
    //int v16; // [esp+14h] [ebp-4h]
    //this->TB_Func_9(0xC4);
    //if (a3 == 1) {
    //	v6 = *a2;
    //	v7 = a2[1] - 0x28;
    //}
    //else {
    //	v8= m_width;
    //	v9 = a2[2];
    //	v10 = *a2;
    //	if (v8 + v9 + v10 + 20 <= CGame::GetClientDimensionStuff().width)
    //		v6 = v10 + v9 + 8;
    //	else
    //		v6 = v10 - v8 - 8;
    //	v7 = a2[1] + 8;
    //	if (v7 + m_heigth >= CGame::GetClientDimensionStuff().height - 15)
    //		v7 = CGame::GetClientDimensionStuff().height - m_heigth - 15;
    //}
    //sub_818690(v6,v7);
    //v11 = m_heigth;
    //v14 = (float)(v6 + m_width / 2);
    //v15 = (float)(v7 + v11 / 2);
    //*(float*)&v16 = 1.0;
    //sub_8189F0(&v14);
    //v12 = v15;
    //result = v16;
    //*((float*)this + 219) = v14;
    //*((float*)this + 220) = v12;
    //*((DWORD*)this + 221) = result;
    //return result;
    return reinterpret_cast<int(__thiscall*)(CIFHelperBubbleWindow*, wnd_rect*,int)>(0x776C00)(this, a2,a3);
}
void CIFHelperBubbleWindow::sub_818690(int a2, int a3) {

    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, int, int)>(0x818690)(this, a2, a3);
}
void CIFHelperBubbleWindow::sub_8189F0(float* a2) {

    reinterpret_cast<void(__thiscall*)(CIFHelperBubbleWindow*, float*)>(0x8189F0)(this, a2);
}
