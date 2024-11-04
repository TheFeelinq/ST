#pragma once
#include <BSLib/_internal/custom_stl.h>
#include "IFWnd.h"
#include "ObjectData.h"
#include "Data/ItemData.h"
enum Blue : short {
    BLUE_INT = 0x0005,
    BLUE_STR = 0x000b,
    BLUE_DURABILITY = 0x0050,
    BLUE_LUCKY = 0x003d,
    BLUE_LUCKY2 = 0x003b,
    BLUE_MP = 0x0098,
    BLUE_HP = 0x008C,
    BLUE_PARRY = 0x0080,
    BLUE_REPAIR_INVALID = 0x0041,
    BLUE_STEADY = 0x0035
};
class CSOItem // size = 464, approved by CIFExchange::ctor
{
public:
    ObjectData* GetObjectData();
    const CItemData *GetItemData() const;
    int GetItemId() const;
    int GetQuantity() const;
    void CreateObject();
    void DestructorObject();
public:
    char pad_0000[24]; //0x0000
    DWORD unkClass;
    DWORD unk_1;
    DWORD ActiveShit;
    char pad_0024[4];//0x0024
    undefined1 field_28;//0x0028
    char pad_0029[3];//0x0029
    BYTE m_Slot; //0x002c -- maybe only for pet
    char pad_002D[7];//0x002D
    int dwObjID; //0x0034
    int UnkID; //0x0038
    int m_UniqueID; //0x003c
    char pad_0040[0x1c]; //0x0040
    BYTE m_petStatus; //0x005c  --- 2 pet active --- 3 pet non active -- 4 pet die
    char pad_005d[47]; //0x005d
    BYTE OptLevel; //0x008C
    char pad_000C[10]; //0x0000
    int CurrDurability; //0x0098
    int m_quantity; // 0x009c
    char pad_00A0[0x22]; //0x0000
    char pad_00c4[0xc]; //0x0000
    //std::n_map<Blue, int> bluemap;//0x00c4
    char pad_00cc[0x00E0 - (0xc4 + 0xc)];
    int PhyAtkPwrMax; //0x00E0
    int PhyAtkPwrMin; //0x00E4
    int MagAtkPwrMax; //0x00E8
    int MagAtkPwrMin; //0x00EC
    int BlockingRateValue; //0x00F0
    int MaxDurability; //0x00F4
    float PhyDefPwrValue; //0x00F8
    int ParryRateValue; //0x00FC
    float PhyAbsorption; //0x0100
    unsigned int HitRate;//0x104
    int CriticalValue; //0x0108
    float MagDefPwrValue; //0x010C
    float MagAbsorption; //0x0110
    float PhyReinforcementMin; //0x0114
    float PhyReinforcementMax; //0x0118
    float MagReinforcementMin; //0x011C
    float MagReinforcementMax; //0x0120
    float PhyReinforcementValue; //0x0124
    float MagReinforcementValue; //0x0128
    char pad_012C[4]; //0x012C
    int AttackRateValue; //0x0130
    char un8[0xa4-8];
BEGIN_FIXTURE()
        ENSURE_OFFSET(ActiveShit, 0x0020)
        ENSURE_OFFSET(field_28, 0x0028)
        ENSURE_OFFSET(m_Slot, 0x002c)
        ENSURE_OFFSET(dwObjID, 0x0034)
        ENSURE_OFFSET(m_UniqueID, 0x003c)
        ENSURE_OFFSET(m_petStatus, 0x005c)
        ENSURE_OFFSET(OptLevel, 0x008C)
        ENSURE_OFFSET(CurrDurability, 0x0098)
        ENSURE_OFFSET(m_quantity, 0x9c)
       // ENSURE_OFFSET(bluemap, 0x00c4)
        ENSURE_OFFSET(PhyAtkPwrMax, 0x00E0)
        ENSURE_OFFSET(PhyAtkPwrMin, 0x00E4)
        ENSURE_OFFSET(MagReinforcementValue, 0x0128)
        ENSURE_OFFSET(AttackRateValue, 0x0130)

    END_FIXTURE()
    RUN_FIXTURE(CSOItem)
}; //Size: 0x01D0
