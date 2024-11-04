#pragma once

#include "IObject.h"

#include <GFX3DFunction/GFontTexture.h>
#include <ghidra/undefined.h>
#include "xlib.h"
#include "ClassLink.h"
#include "Data/CharacterData.h"

class CIGIDObject : public CIObject {
public:
    /// \address 004df110
    void Func_15(int param_1, float *param_2) override;

    virtual void Func_18();

    virtual void Func_19();

    virtual void Func_20();

    virtual void Func_21();

    virtual void Func_22();

    virtual void Func_23();

    virtual void Func_24();

    virtual void Func_25();

    virtual void Func_26();

    virtual void Func_27();

    virtual void Func_28();

    virtual void Func_29();

    virtual void Func_30();

    virtual void Func_31();

    virtual void Func_32();

    virtual void Func_33();

    void ChangeTitleColor(D3DCOLOR Color);
    void ChangeNameColor(D3DCOLOR Color);
    void ChangeTitle(std::n_wstring* str);
    void ChangeName(std::n_wstring* str);
    int GetPKStatus();
    int GetPVPStatus();
    const int GetUniqueID();
    DWORD GetObjID();
    D3DCOLOR GetNameColor();
public:
    /// \brief Get the assigned name of this object
    const std::n_wstring &GetName() const;
    const std::n_wstring &GetTitle() const;
    virtual void SetName(const std::n_wstring &name, undefined4 show);
    const CCharacterData::SData *GetSData() const;


public:

    CClassLink<CIGIDObject> m_classLink;
    undefined1 field_0xec;
    undefined field_0xed;
    undefined field_0xee;
    undefined field_0xef;
    undefined4 field_0xf0;
    undefined1 field_0xf4;
    undefined field_0xf5;
    undefined field_0xf6;
    undefined field_0xf7;
    int m_UniqueObjID; /* ID assigned by the server */ //field_0xf8
    undefined field_0xfc;
    undefined field_0xfd;
    undefined field_0xfe;
    undefined field_0xff;
    undefined field_0x100;
    undefined field_0x101;
    undefined field_0x102;
    undefined field_0x103;
    undefined field_0x104;
    undefined field_0x105;
    undefined field_0x106;
    undefined field_0x107;
    undefined field_0x108;
    undefined field_0x109;
    undefined field_0x10a;
    undefined field_0x10b;
    undefined field_0x10c;
    undefined field_0x10d;
    undefined field_0x10e;
    undefined field_0x10f;
    std::n_wstring m_name;
    CGFontTexture fonttexture_playername;
    std::n_wstring title_name;
    CGFontTexture fonttexture_title;
    undefined field_0x218;
    undefined field_0x219;
    undefined field_0x21a;
    undefined field_0x21b;
protected:
    int m_ObjID; //field_0x21c
private:
    CCharacterData::SData* m_characterData; //0x0220
    undefined4 field_0x224;
    float field_0x228;
    undefined field_0x22c;
    undefined field_0x22d;
    undefined field_0x22e;
    undefined field_0x22f;
    undefined field_0x230;
    undefined field_0x231;
    undefined field_0x232;
    undefined field_0x233;
    undefined field_0x234;
    undefined field_0x235;
    undefined field_0x236;
    undefined field_0x237;
    undefined field_0x238;
    undefined field_0x239;
    undefined field_0x23a;
    undefined field_0x23b;
    undefined field_0x23c;
    undefined field_0x23d;
    undefined field_0x23e;
    undefined field_0x23f;
    undefined field_0x240;
    undefined field_0x241;
    undefined field_0x242;
    undefined field_0x243;
    undefined field_0x244;
    undefined field_0x245;
    undefined field_0x246;
    undefined field_0x247;
    undefined field_0x248;
    undefined field_0x249;
    undefined field_0x24a;
    undefined field_0x24b;
    float field_0x24c;
    undefined field_0x250;
    undefined field_0x251;
    undefined field_0x252;
    undefined field_0x253;

BEGIN_FIXTURE()
        ENSURE_SIZE(0x254)

        ENSURE_OFFSET(m_classLink, 0xdc)
        ENSURE_OFFSET(m_name, 0x110)
        ENSURE_OFFSET(fonttexture_playername, 0x12c)
        ENSURE_OFFSET(title_name, 0x194)
        ENSURE_OFFSET(fonttexture_title, 0x1b0)
        ENSURE_OFFSET(m_ObjID, 0x21c)
        ENSURE_OFFSET(m_characterData, 0x220)

    END_FIXTURE()

    RUN_FIXTURE(CIGIDObject)
};
