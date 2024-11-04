#pragma once

#include <D3D9.h>
#include "NavMesh/LocationInfo.h"


class CNode
{
public:
    CNode(const LocationInfo& location);

    void calculate_cost(const CNode& destination);

    float distance_to(const CNode& node);


    const CNode* parent;
    LocationInfo location;
    float global_cost;
    float local_cost;
    float heuristic_cost;
};
