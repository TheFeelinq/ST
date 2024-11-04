#pragma once

#include "LocationInfo.h"
#include "BSLib/BSLib.h"

#define g_CRegionManagerBody (*reinterpret_cast<IRegionManager*>(0x0115B0C8))


class IRegionManager
{
public:
    virtual ~IRegionManager();


    virtual void InitMaploader() = 0;
    virtual void Func_2() = 0;
    virtual void Func_3() = 0;
    virtual void Func_4() = 0;
    virtual void Func_5() = 0;
    virtual void Func_6() = 0;
    virtual void Func_7() = 0;
    virtual void Func_8() = 0;
    virtual void Func_9() = 0;
    virtual void Func_10() = 0;
    virtual void Func_11() = 0;
    virtual int SomethingWithMapCollision_MAYBE(int b_IsMeOrPlayerOrCOS, int a3, const LocationInfo *pos1, LocationInfo *pos2, int a6, CObj *a7) = 0;
    virtual void Func_13() = 0;
    virtual void Func_14() = 0;
    virtual void Func_15() = 0;
    virtual void Func_16() = 0;
    virtual void Func_17() = 0;
    virtual void Func_18() = 0;
    virtual void Func_19() = 0;
    virtual void Func_20() = 0;
    virtual void IsEnableRegist() = 0;
    virtual void Func_22() = 0;
    virtual void Func_23() = 0;
    virtual void Func_24() = 0;
    virtual void Func_25() = 0;
    virtual void Func_26() = 0;
    virtual void Func_27() = 0;
    virtual void Func_28() = 0;
    virtual void Func_29() = 0;
    virtual void Func_30() = 0;
    virtual void Func_31() = 0;

};

