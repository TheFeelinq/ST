#pragma once

#include <list>
#include "node_set.h"

class CPathfinder
{
public:
    CPathfinder(const LocationInfo& start, const LocationInfo& end);

    bool step();

    void render();

public:
    void check_neighbor(const CNode& node, float offset_x, float offset_z);

    void combine_segments();

public:
    CNode start;
    CNode end;
    bool completed;

    CNode* last_best;

    node_set open_set;
    node_set closed_set;
    node_set rejected_set;
    node_set mismatch_set;

    const int step_size;

    std::list<const CNode*> path_segms;
};
