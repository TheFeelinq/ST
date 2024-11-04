#pragma once

#include "IFWnd.h"
#include "IFStatic.h"
#include "SOItem.h"

class CIFEquipment : public CIFWnd
{
public:
    CSOItem* GetEquipmentObjectBySlot(BYTE SlotIndex); //0x2354
    bool OnCreateIMPL(long ln);
    void OnUpdateIMPL();
    //0x05e4 - mu avartar
    //0x05e8 - ao avartar
    //0x05ec - co avartar
    //0x05f0 - di kem avartar
    //0x05f4 - nasrun
/*	char pad_0x036C[0x230]; //0x036C
    CIFSlotWithHelp* equip_slot_shoulderguard; //0x59c
    CIFSlotWithHelp* equip_slot_gauntlet; //0x5a0
    CIFSlotWithHelp* equip_slot_pants; //0x5a4
    CIFSlotWithHelp* equip_slot_boots; //0x5a8
    CIFSlotWithHelp* equip_slot_weapon; //0x5ac
    CIFSlotWithHelp* equip_slot_shield; //0x5b0
    char pad_0x5b4[4];
    CIFSlotWithHelp* equip_slot_earring; //0x5b8
    CIFSlotWithHelp* equip_slot_necklace; //0x5bc
    CIFSlotWithHelp* equip_slot_l_ring; //0x5c0
    CIFSlotWithHelp* equip_slot_r_ring; //0x5c4
    char pad_0x5c8[8];
    CIFSlotWithHelp* equip_slot_helm; //0x5d0
    CIFSlotWithHelp* equip_slot_cloth; //0x5d4
    char pad_0x5dc[0x2354-(0x5d4+0x4)];*/
    char pad_0x036C[0x2354]; //0x036C
    CIFStatic * m_itempoint;

BEGIN_FIXTURE()
    //ENSURE_SIZE(0x26C0)

    END_FIXTURE()
    RUN_FIXTURE(CIFEquipment)

}; //Size=0x26C0