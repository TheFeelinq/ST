#pragma once

#include "IFWnd.h"
#include "IFStoreForPackage.h"
#include "IFStorageRoom.h"
#include <Windows.h>
#include "SOItem.h"

class CIFInventory : public CIFWnd
{
public:
    int GetInventorySlotIndex(int numberOfelements);
public:
	CIFStoreForPackage* m_storeWindow; //0x036C
	CIFStorageRoom* m_storageWindow; //0x0370
	char pad_0x0374[0xC]; //0x0374
	__int32 N00000183; //0x0380
	char pad_0x0384[0x4]; //0x0384
	CIFStatic* m_goldAmtText; //0x0388
	char pad_0x038C[0xC]; //0x038C
	CIFButton* m_moneyDropButton; //0x0398 //920
    char pad_0x03B0[944-924]; //0x03B0
    unsigned int pSlots;//0x03B0
	char pad_0x039C[0x3C]; //0x039C
    CSOItem* GetItemBySlot(BYTE SlotIndex);

private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x03F0)
        ENSURE_OFFSET(m_storeWindow, 0x036C)
        ENSURE_OFFSET(m_storageWindow, 0x0370)
        ENSURE_OFFSET(m_goldAmtText, 0x0388)
        ENSURE_OFFSET(m_moneyDropButton, 0x0398)
        ENSURE_OFFSET(pSlots, 0x03B0)

    END_FIXTURE()

    RUN_FIXTURE(CIFInventory)

}; //Size=0x03F0