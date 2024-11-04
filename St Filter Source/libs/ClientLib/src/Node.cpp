#include "Node.h"
#include "../../../source/DevKit_DLL/src/Util.h"
#include "Rebot.h"


CNode::CNode(const LocationInfo& location)
        : parent(0), location(location), local_cost(0)
{
}

bool almostEquals(float a, float b)
{
    return (a - b) * (a - b) < 0.01;
}

void CNode::calculate_cost(const CNode& destination)
{
    heuristic_cost = distance_to(destination);
    local_cost = parent->local_cost + distance_to(*parent);
    if (parent && parent->parent)
    {
        D3DVECTOR locationPos = GetSilkPosD3D(location.region, location.pos);
        D3DVECTOR parentPos = GetSilkPosD3D(parent->location.region, parent->location.pos);
        D3DVECTOR parentParentPos = GetSilkPosD3D(parent->parent->location.region, parent->parent->location.pos);
        float dxp1 = locationPos.x - parentPos.x;
        float dzp1 = locationPos.z - parentPos.z;

        float dxp2 = parentPos.x - parentParentPos.x;
        float dzp2 = parentPos.z - parentParentPos.z;

        if (!almostEquals(dxp1, dxp2) || !almostEquals(dzp1, dzp2))
        {
            local_cost += 5; // penalty cost
        }
    }

    global_cost = heuristic_cost + local_cost;
}

float CNode::distance_to(const CNode& node)
{
    D3DVECTOR locationPos =  GetSilkPosD3D(this->location.region, this->location.pos);
    D3DVECTOR nodePos = GetSilkPosD3D(node.location.region, node.location.pos);
    return Rebot::Distance(locationPos, nodePos);
//	int region_distance_x = this->location.region.single.x - node.location.region.single.x;
//	int region_distance_y = this->location.region.single.y - node.location.region.single.y;
//
//	// Switch to ingame units, region-y is mesh-z :S
//	float distance_x = region_distance_x * NAVMESH_RESOLUTION;
//	float distance_z = region_distance_y * NAVMESH_RESOLUTION;
//
//	float node_distance_x = this->location.pos.x - node.location.pos.x;
//	float node_distance_z = this->location.pos.z - node.location.pos.z;
//
//	float total_distance_x = distance_x + node_distance_x;
//	float total_distance_z = distance_z + node_distance_z;
//#if EXO_BETTER_DISTANCE
//	return max(total_distance_x, total_distance_z) + (sqrt(2.0) - 1) * min(total_distance_x, total_distance_z);
//#else
//	return sqrt(total_distance_x * total_distance_x + total_distance_z * total_distance_z);
//#endif
}
