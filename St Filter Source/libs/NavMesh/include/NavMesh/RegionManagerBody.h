#pragma once
#include "IRegionManager.h"


class CRegionManagerBody : public IRegionManager
{
public:
    int SomethingWithMapCollision_MAYBE_IMPL(int b_IsMeOrPlayerOrCOS, int a3, const LocationInfo* pos1, LocationInfo* pos2, int a6, CObj* a7);
};

