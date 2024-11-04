#pragma once

#include <ghidra/undefined.h>
#include "SOItem.h"

struct ChatItemLink {
    int LineIndex;
    CSOItem ItemInfo;
    BYTE MagNum;
    std::n_map<short,int> pBluesMap;

};
struct ItemLinking {
    int LineIndex;
    CSOItem ItemInfo;
    CMsgStreamBuffer* buffer;
};