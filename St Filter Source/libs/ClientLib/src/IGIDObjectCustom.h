#pragma once

#include "IObject.h"

#include <GFX3DFunction/GFontTexture.h>
#include <ghidra/undefined.h>
#include "xlib.h"
#include "ClassLink.h"
#include "Data/CharacterData.h"

class CIGIDObjectCustom : public CIObject {
public:
    std::n_wstring charname;
    std::n_wstring Title;
    D3DCOLOR titlecolor;
    std::n_wstring NameTitle;
    D3DCOLOR namecolor;
};
