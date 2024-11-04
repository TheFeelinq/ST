#include <BSLib/multibyte.h>
#include <sstream>
#include "IFEdit.h"
#include "ICPlayer.h"
#include <remodel/MemberFunctionHook.h>
GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFEdit, 0x00ee9540)

bool CIFEdit::HasFocus() const {
    return reinterpret_cast<bool (__thiscall *)(const CIFEdit *)>(0x00634EA0)(this);
}
void CIFEdit::SetMaxStringInput(int a1) {
    reinterpret_cast<void(__thiscall*)(CIFEdit*,int)>(0x00634f80)(this,a1);

}
const wchar_t* CIFEdit::GetText()
{
    return reinterpret_cast<const wchar_t*(__thiscall*)(const CIFEdit*)>(0x00653350)(this);
}
// CIFEdit::SetText(void) .text 00653AC0 00000062 00000004 00000004 R . . . . T .
bool CIFEdit::SetText(const wchar_t* src)
{
    reinterpret_cast<void(__thiscall*)(CIFEdit*, const wchar_t*)>(0x00635EA0)(this, src);
    return true;
}
CInstanceEdit* CIFEdit::GetInstance()
{
    return this->pInstanceEdit;
}
int CIFEdit::GetAreaSize()
{
    return this->m_TextAreaSize;
}
int CIFEdit::GetCurrentIndex()
{
    return this->m_CurrentIndex;
}
void CIFEdit::SetCurrentIndex(int Index)
{
    this->m_CurrentIndex = Index;
}
void CIFEdit::SetTextAreaSize(int Size)
{
    this->m_TextAreaSize = Size;
}
void CIFEdit::AddValue_404(undefined4 value) {
    reinterpret_cast<void(__thiscall *)(CIFEdit *, undefined4)>(0x00635150)(this, value);
}

void CIFEdit::SetValue_404(undefined4 value) {
    reinterpret_cast<void(__thiscall *)(CIFEdit *, undefined4)>(0x00635070)(this, value);
}

undefined4 CIFEdit::GetValue_404() const {
    return reinterpret_cast<undefined4(__thiscall *)(const CIFEdit *)>(00635060)(this);
}

bool CIFEdit::IsSetValue_404(undefined4 value) const {
    return reinterpret_cast<bool(__thiscall *)(const CIFEdit *, undefined4)>(0x00635170)(this, value);
}

void CIFEdit::FUN_00634f80(unsigned int a1) {
    reinterpret_cast<void(__thiscall *)(CIFEdit *, unsigned int)>(0x00634f80)(this, a1);
}

void CIFEdit::SetTextmode(undefined4 mode) {
    reinterpret_cast<void(__thiscall *)(CIFEdit *, undefined4)>(0x006351b0)(this, mode);
}
const std::n_wstring &CIFEdit::GetCurrentText() const {
    return m_texturestr_font;
}
//HOOK_ORIGINAL_MEMBER(0x00634DF0, &CIFEdit::OnTextChange);
void CIFEdit::OnTextChange()
{
    std::wstring  text = this->GetText();

    if (text.size() >= 4) {

            std::stringstream buffer(acp_encode(text));
            long long unitAmount;
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

            text = commafiedAmount ;
            UINT msgcolor = 0xffFF0000; //No Difference: FFFEFEFF | Better: FFFFD953 | Worse: FFFF4A4A
            //ForegroundColor = msgcolor;

    }
    /*switch (amountString.length())
    {
        case 5:
            this->m_FontTexture.SetColor(0xEAEA3300);
            break;
        case 6:
            this->m_FontTexture.SetColor(0xEABA3300);
            break;
        case 7:
            this->m_FontTexture.SetColor(0xEAB03300);
            break;
        case 8:
            this->m_FontTexture.SetColor(0xE6987400);
            break;
        case 9:
            this->m_FontTexture.SetColor(0xB974E600);
            break;
        case 10:
            this->m_FontTexture.SetColor(0xA08CCA00);
            break;
        case 11:
            this->m_FontTexture.SetColor(0x66CCF500);
            break;
        case 12:
            this->m_FontTexture.SetColor(0x66F5BD00);
            break;
    }*/
        std::n_wstring NameTitle = text.c_str();
        this->m_FontTexture.sub_8B3B60(&NameTitle);
}