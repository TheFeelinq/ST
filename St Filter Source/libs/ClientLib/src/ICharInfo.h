#pragma once

#include "AnimationCallback.h"
#include "CObjAnimation.h"
#include "IFStatic.h"
#include <ghidra/undefined.h>

class SICharInfo : public CAnimationCallback {
public:
    EquipInfo Head;
    EquipInfo Jacket;
    EquipInfo Shoulder;
    EquipInfo Wristband;
    EquipInfo Trousers;
    EquipInfo Shoes;
    EquipInfo Weapon;
    EquipInfo Shield;
private:
BEGIN_FIXTURE()

        ENSURE_OFFSET(Head, 0x4) //wrong
        ENSURE_OFFSET(Jacket, 0x10)
    END_FIXTURE()

    RUN_FIXTURE(SICharInfo)
};