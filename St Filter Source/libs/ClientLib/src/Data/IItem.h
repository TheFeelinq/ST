#pragma once
#include "IGIDObject.h"

class CIItem : public CIGIDObject {
GFX_DECLARE_DYNAMIC_EXISTING(CIItem,0x00EF1C28)
public:
    byte hasOwner; //0x254
    char pad_0255[0x3]; //0x255
    int SomeCheckForPlayerOwnerName; //0x258;
    char pad_025C[0x30]; //0x25C
    int m_bPickAbbilty; //0x28C
    char pad_0290[0x1C]; //0x290
BEGIN_FIXTURE()
        ENSURE_SIZE(0x2AC)
        ENSURE_OFFSET(hasOwner, 0x254)
    END_FIXTURE()
    RUN_FIXTURE(CIItem)
};