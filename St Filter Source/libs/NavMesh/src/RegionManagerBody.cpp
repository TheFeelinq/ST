#include "RegionManagerBody.h"

int CRegionManagerBody::SomethingWithMapCollision_MAYBE_IMPL(int b_IsMeOrPlayerOrCOS, int a3, const LocationInfo* pos1, LocationInfo* pos2, int a6, CObj* a7)
{
    int ret = reinterpret_cast<int(__thiscall*)(CRegionManagerBody*, int, int, const LocationInfo*, LocationInfo*, int, CObj*)>(0x00412660)(this, b_IsMeOrPlayerOrCOS, a3, pos1, pos2, a6 ,a7);

    //printf("[%p %p] - [%p %p]\n", pos1->field_0, pos1->field_1, pos2->field_0, pos2->field_1);

    return ret;
}
