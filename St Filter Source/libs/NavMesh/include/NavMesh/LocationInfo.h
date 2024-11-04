#pragma once
#include <D3DX9.h>
#include "../../../ClientLib/src/GlobalHelpersThatHaveNoHomeYet.h"

#define NAVMESH_RESOLUTION 1920.0

struct LocationInfo
{

    void normalize_x();
    void normalize_z();

    class CRTNavCell* field_0;
    void* field_1;
    uregion region;
    D3DXVECTOR3 pos;

    bool operator==(const LocationInfo &rhs) const;
};
