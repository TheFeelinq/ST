#pragma once

#include <set>
#include <algorithm>

#include "Node.h"
#include "location_equals.h"

struct lowest_cost
{
    bool operator()(const CNode* lhs, const CNode* rhs) const
    {
        return lhs->global_cost < rhs->global_cost;
    }
};


template<typename Key, typename Sort, typename Equals>
class better_set
{
public:
    typedef std::multiset<Key, Sort> base_type;
    typedef typename base_type::iterator iterator;
    typedef typename base_type::const_iterator const_iterator;
    typedef typename Key value_type;
    typedef typename Equals compare_type;
    typedef typename base_type::size_type size_type;


    bool contains(const value_type& val)
    {
        return std::find_if(begin(), end(), compare_type(val)) != end();
    }

    std::pair<iterator, bool> insert(const value_type& val)
    {
        if (contains(val))
        {
            return std::make_pair(end(), false);
        }

        iterator it = set_.insert(val);

        return std::make_pair(it, true);
    }

    size_type erase(const value_type& val)
    {
        return set_.erase(val);
    }

    iterator erase(const iterator& it)
    {
        return set_.erase(it);
    }

    iterator begin()
    {
        return set_.begin();
    }

    iterator end()
    {
        return set_.end();
    }

    size_type size()
    {
        return set_.size();
    }


private:
    std::multiset<Key, Sort> set_;
};

typedef better_set<CNode*, lowest_cost, location_equals> node_set;
