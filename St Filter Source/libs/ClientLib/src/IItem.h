#pragma once
#include "xlib.h"
#include <map>
#include <Data/ItemData.h>

class CIItem
{
public:
    char pad_000[0x258];
    std::map<unsigned __int32, CItemData *> m_itemDataMap; //0x258

};
