#include "IFInventory.h"
#include "SOItem.h"

CSOItem* CIFInventory::GetItemBySlot(BYTE SlotIndex)
{
    return reinterpret_cast<CSOItem*(__thiscall*)(CIFInventory*, BYTE)>(0x006B3E50)(this, SlotIndex);
}
int CIFInventory::GetInventorySlotIndex(int numberOfelements)
{
    return reinterpret_cast<int (__thiscall *)(CIFInventory *,int)>(0x006AF600)(this,numberOfelements);
}