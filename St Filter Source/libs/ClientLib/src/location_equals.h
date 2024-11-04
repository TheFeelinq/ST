#pragma once
#include "Node.h"

struct location_equals
{
    explicit location_equals(const LocationInfo& loc)
            : other_loc(loc)
    {
    }

    explicit location_equals(const CNode* const& node)
            : other_loc(node->location)
    {

    }

    bool operator()(const CNode& rhs) const
    {
        return operator()(&rhs);
    }

    bool operator()(const CNode* const rhs) const
    {
        return other_loc.region.r == rhs->location.region.r
               && close_enough(other_loc.pos.x, rhs->location.pos.x)
               && close_enough(other_loc.pos.z, rhs->location.pos.z);
    }

    bool operator()(const LocationInfo& rhs) const
    {
        // TODO: Why no region compare here?
        return close_enough(other_loc.pos.x, rhs.pos.x)
               && close_enough(other_loc.pos.z, rhs.pos.z);
    }

private:
    // Roughly compare two values
    inline bool close_enough(float v1, float v2) const
    {
        const int precision = 100;

        return static_cast<int>(v1 * precision) == static_cast<int>(v2 * precision);
    }

private:
    const LocationInfo& other_loc;
};
