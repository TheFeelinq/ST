#pragma once

#include "IFStatic.h"
class CInstanceEdit
{
private:
    DWORD SelfPtr;
public:
    DWORD GetPtr()
    {
        return this->SelfPtr;
    }
};
class CIFEdit : public CIFStatic {
GFX_DECLARE_DYNAMIC_EXISTING(CIFEdit, 0x00ee9540)

public:
    /// \address 00634EA0
    bool HasFocus() const;
    /// set max input string
    void SetMaxStringInput(int a1);
    /// \address 00635150
    void AddValue_404(undefined4 value);

    /// \address 00635070
    void SetValue_404(undefined4 value);

    /// \address 00635060
    undefined4 GetValue_404() const;

    /// \address 00635170
    bool IsSetValue_404(undefined4 value) const;

    /// \address 00634f80
    void FUN_00634f80(unsigned int a1);

    /// \address 006351b0
    void SetTextmode(undefined4 mode);

    const std::n_wstring &GetCurrentText() const;

    bool SetText(const wchar_t* src);
    const wchar_t* GetText();
    CInstanceEdit* GetInstance();
    int GetAreaSize();
    int GetCurrentIndex();
    void SetCurrentIndex(int Index);
    void SetTextAreaSize(int Size);
    void OnTextChange();



private:
    char pad_0000[48]; //0x0000
    CInstanceEdit* pInstanceEdit; //0x0030
    char pad_0034[356]; //0x0034
    std::wstring m_innerText; //0x01AC
    char pad_01B0[584]; //0x01B0
    int m_TextAreaSize; //0x03FC
    char pad_0400[68]; //0x0400
    int m_CurrentIndex; //0x0448
    char pad_044C[996]; //0x044C
};
