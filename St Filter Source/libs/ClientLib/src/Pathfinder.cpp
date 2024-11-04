#include "Pathfinder.h"
#include "location_equals.h"

#include <NavMesh/IRegionManager.h>
#include <ICPlayer.h>
#include <algorithm>
#include <fstream>
#include <GFX3DFunction/DrawingHelpers.h>
#include <GFX3DFunction/GFXVideo3d.h>
#include <iomanip>
#include <iostream>
#include <unsorted.h>
#include "../../../source/DevKit_DLL/src/Util.h"

CPathfinder::CPathfinder(const LocationInfo& start, const LocationInfo& end)
        : start(start), end(end), completed(false), step_size(10)
{
    open_set.insert(&this->start);
    last_best = &this->start;
}

bool CPathfinder::step()
{
    node_set::iterator first_node = open_set.begin();

    CNode& current_node = **first_node;

    last_best = &current_node;

    // Move current node to closed set

    closed_set.insert(*first_node);
    open_set.erase(first_node);

    if (current_node.distance_to(end) <= step_size * 2)
    {
        this->end.parent = &current_node;
        last_best = &this->end;
        printf("×Ô¶¯Ñ°Â·Â·Ïß¹æ»®Íê±Ï!\n");
        completed = true;
        combine_segments();
        return true;
    }


    // Check neighbors
    check_neighbor(current_node, step_size, 0);
    check_neighbor(current_node, -step_size, 0);
    check_neighbor(current_node, 0, step_size);
    check_neighbor(current_node, 0, -step_size);

    check_neighbor(current_node, step_size, step_size);
    check_neighbor(current_node, step_size, -step_size);
    check_neighbor(current_node, -step_size, step_size);
    check_neighbor(current_node, -step_size, -step_size);

    return false;
}

void CPathfinder::render()
{
    CGFXVideo3d* gfx = CGFXVideo3d::get();

    for (node_set::iterator it = open_set.begin(); it != open_set.end(); ++it)
    {
        D3DVECTOR p12d;
        D3DVECTOR P13d= GetSilkPosD3D((*it)->location.region, (*it)->location.pos);
        if (gfx->Project(P13d, p12d) > 0)
            DrawRect(p12d.x - 5, p12d.y - 5, 10, 10, D3DCOLOR_RGBA(255, 0, 0, 255));
    }

    for (node_set::iterator it = closed_set.begin(); it != closed_set.end(); ++it)
    {
        D3DVECTOR p12d;
        D3DVECTOR P13d = GetSilkPosD3D((*it)->location.region, (*it)->location.pos);
        if (gfx->Project(P13d, p12d) > 0)
            DrawRect(p12d.x - 2, p12d.y - 2, 4, 4, D3DCOLOR_RGBA(0, 255, 255, 255));
    }

    for (node_set::iterator it = rejected_set.begin(); it != rejected_set.end(); ++it)
    {
        D3DVECTOR p12d;
        D3DVECTOR P13d = GetSilkPosD3D((*it)->location.region, (*it)->location.pos);
        if (gfx->Project(P13d, p12d) > 0)
            DrawRect(p12d.x - 4, p12d.y - 4, 8, 8, D3DCOLOR_RGBA(255, 0, 255, 255));
    }

    for (node_set::iterator it = mismatch_set.begin(); it != mismatch_set.end(); ++it)
    {
        D3DVECTOR p12d;
        D3DVECTOR P13d = GetSilkPosD3D((*it)->location.region, (*it)->location.pos);
        const int diameter = 10;
        if (gfx->Project(P13d, p12d) > 0)
        {
            // 4 /\ 1
            //  /  \
			//  \  /
            // 3 \/ 2

            DXDrawLine(
                    p12d.x + diameter / 2, p12d.y + diameter,
                    p12d.x + diameter, p12d.y + diameter / 2,
                    D3DCOLOR_RGBA(255, 0, 255, 255), 1.0);

            DXDrawLine(
                    p12d.x + diameter, p12d.y + diameter / 2,
                    p12d.x + diameter / 2, p12d.y,
                    D3DCOLOR_RGBA(255, 0, 255, 255), 1.0);

            DXDrawLine(
                    p12d.x + diameter / 2, p12d.y,
                    p12d.x, p12d.y + diameter / 2,
                    D3DCOLOR_RGBA(255, 0, 255, 255), 1.0);

            DXDrawLine(
                    p12d.x, p12d.y + diameter / 2,
                    p12d.x + diameter / 2, p12d.y + diameter,
                    D3DCOLOR_RGBA(255, 0, 255, 255), 1.0);

        }
    }

    const CNode* lastnode = 0;
    for (const CNode* node = last_best; node->parent != 0; lastnode = node, node = node->parent)
    {
        if (lastnode == 0)
            continue;
        D3DVECTOR nodePos = GetSilkPosD3D(node->location.region, node->location.pos);
        D3DVECTOR lastnodePos = GetSilkPosD3D(lastnode->location.region, lastnode->location.pos);
        Line3D(nodePos, lastnodePos, D3DCOLOR_RGBA(255, 255, 0, 255), 2.0);
    }

    if (completed)
    {
        for (std::list<const CNode*>::const_iterator segm_end_iter = ++path_segms.begin();
             segm_end_iter != path_segms.end(); ++segm_end_iter)
        {
            std::list<const CNode*>::const_iterator segm_start_iter = segm_end_iter;
            std::advance(segm_start_iter, -1);

            const CNode* segm_start = *segm_start_iter;
            const CNode* segm_end = *segm_end_iter;
            D3DVECTOR segm_startPos = GetSilkPosD3D(segm_start->location.region, segm_start->location.pos);
            D3DVECTOR segm_endPos = GetSilkPosD3D(segm_end->location.region, segm_end->location.pos);
            Line3D(segm_startPos, segm_endPos, D3DCOLOR_RGBA(0, 100, 180, 255), 4.0);
        }
    }
}

void CPathfinder::check_neighbor(const CNode& node, float offset_x, float offset_z)
{
    LocationInfo neighbor_location = node.location;
    neighbor_location.pos.x += offset_x;
    neighbor_location.normalize_x();
    neighbor_location.pos.z += offset_z;
    neighbor_location.normalize_z();
    //printf("x:%f,y:%f,z:%f,region x:%d,region y:%d\r\n", neighbor_location.pos.x, neighbor_location.pos.y, neighbor_location.pos.z, neighbor_location.region.single.x, neighbor_location.region.single.y);
    CNode* neighbor = new CNode(neighbor_location);

    LocationInfo node_old_location = node.location;
    LocationInfo neighbor_old_location = neighbor->location;

    //!ObjIntersect(node_old_location.region, node_old_location.pos, neighbor_old_location.region, neighbor_old_location.pos)
    if (!g_CRegionManagerBody.SomethingWithMapCollision_MAYBE(1, 1, &node.location, &neighbor->location, 0,
                                                              g_pCICPlayer))
    {
        // No collision

        // Check if neighbor is already in closed list
        const location_equals neighbor_location_equals(neighbor->location);
        if (std::find_if(closed_set.begin(), closed_set.end(), neighbor_location_equals) != closed_set.end())
        {
            //printf("Neighbor (%.2f, %.2f, %.2f) is already in set\n", neighbor_location.pos.x, neighbor_location.pos.y, neighbor_location.pos.z);
            delete neighbor;
            return;
        }


        // Check if really no collision
        // (SomethingWithMapCollision_MAYBE changes the location without triggering a collision sometimes ... HUH?)
        if (!neighbor_location_equals(neighbor_old_location))
        {
#if 0
            printf("MISMATCH! [%.2f, %.2f, %.2f] != [%.2f, %.2f, %.2f] delta [%e, %e, %e]\n",
				neighbor_old_location.pos.x,
				neighbor_old_location.pos.y,
				neighbor_old_location.pos.z,
				neighbor->location.pos.x,
				neighbor->location.pos.y,
				neighbor->location.pos.z,
				neighbor_old_location.pos.x - neighbor->location.pos.x,
				neighbor_old_location.pos.y - neighbor->location.pos.y,
				neighbor_old_location.pos.z - neighbor->location.pos.z
			);

#endif
            //delete neighbor;
            mismatch_set.insert(neighbor);
            return;
        }



        // Set parent
        neighbor->parent = &node;

        // Calculate costs
        neighbor->calculate_cost(end);

        // Check if neighbor is already in closed list
        node_set::iterator found_it = std::find_if(open_set.begin(), open_set.end(),
                                                   location_equals(neighbor->location));

        if (found_it != open_set.end())
        {
            CNode& current_node = **found_it;
            if (current_node.local_cost > neighbor->local_cost)
            {
                current_node.parent = &node;
                current_node.calculate_cost(end);

                open_set.erase(found_it);
                open_set.insert(&current_node);
            }
            // Delete no longer needed node
            delete neighbor;
        }
        else
        {
            open_set.insert(neighbor);
        }
    }
    else
    {
        // collision, delete neighbor
        //delete neighbor;
#if 0
        printf("Collision [%.2f, %.2f, %.2f]\n",
			neighbor->location.pos.x,
			neighbor->location.pos.y,
			neighbor->location.pos.z);
#endif
        rejected_set.insert(neighbor);
    }
}

void CPathfinder::combine_segments()
{
    path_segms.clear();
    path_segms.push_back(&end);

    for (const CNode* segm_end = &end, *segm_start = NULL; segm_end->parent != NULL; segm_end = segm_start)
    {
        segm_start = segm_end->parent;

        for (const CNode* segm_start_test = NULL; segm_start->parent; segm_start = segm_start_test)
        {
            segm_start_test = segm_start->parent;

            LocationInfo intersection = segm_end->location;
            LocationInfo segm_start_loc = segm_start_test->location;

            if (g_CRegionManagerBody.SomethingWithMapCollision_MAYBE(1, 1, &segm_start_loc, &intersection, 0,
                                                                     g_pCICPlayer))
                break;
        }

        path_segms.push_front(segm_start);
    }
}
