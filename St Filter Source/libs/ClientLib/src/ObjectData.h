#pragma once
#include "xlib.h"

class ObjectData
{
public:
    unsigned short TID; //0x0000
    char pad_0002[2]; //0x0002
    unsigned int ObjID; //0x0004
    std::wstring ObjCodeName; //0x0008
    std::wstring ObjName; //0x0024
    std::wstring ObjOrgCodeName; //0x0040
    char pad_0064[4]; //0x005C
    std::wstring ObjNameStrID; //0x0060
    std::wstring DescStrID; //0x007C
    unsigned int DecayTime; //0x0098
    unsigned char Country; //0x009C
    unsigned char UNK_009D; //0x009D | Double country? WTF?
    char pad_009E[2]; //0x009E
    unsigned int Rarity; //0x00A0
    bool CanTrade; //0x00A4
    bool CanSell; //0x00A5
    bool CanBuy; //0x00A6
    bool CanBorrow; //0x00A7
    bool CanDrop; //0x00A8
    bool CanPick; //0x00A9
    bool CanRepair; //0x00AA
    bool CanRevive; //0x00AB
    bool CanUse; //0x00AC
    bool CanThrow; //0x00AD
    char pad_00AE[2]; //0x00AE
    long long Price; //0x00B0
    long long SellPrice; //0x00B8
    unsigned int CostRepair; //0x00C0
    unsigned int CostRevive; //0x00C4
    unsigned int CostBorrow; //0x00C8
    unsigned int KeepingFee; //0x00CC
    int ReqLevelType1; //0x00D0
    int ReqLevelType2; //0x00D4
    int ReqLevelType3; //0x00D8
    int ReqLevelType4; //0x00DC
    int ReqLevel1; //0x00E0
    int ReqLevel2; //0x00E4
    int ReqLevel3; //0x00E8
    int ReqLevel4; //0x00EC
    int MaxContain; //0x00F0
    unsigned int RegionID; //0x00F4
    int Direction; //0x098
    int OffsetX; //0x09C
    int OffsetY; //0x0100
    int OffsetZ; //0x0104
    unsigned int Speed1; //0x0108
    unsigned int Speed2; //0x010C
    int Scale; //0x0110
    int BCHeight; //0x0114
    int BCRadius; //0x0118
    unsigned int EventID; //0x011C
    unsigned int ObjItemLinkID; //0x0120
    std::wstring AssocFileObj; //0x0124
    std::wstring AssocFileDrop; //0x0140
    std::string AssocFileIcon; //0x015C
    std::wstring AssocFile1; //0x0178
    std::wstring AssocFile2; //0x0194
private:
BEGIN_FIXTURE()
        ENSURE_OFFSET(BCRadius, 0x0118)
        ENSURE_OFFSET(EventID, 0x011C)
        ENSURE_OFFSET(ObjItemLinkID, 0x0120)
        ENSURE_OFFSET(AssocFileObj, 0x0124)
    END_FIXTURE()

    RUN_FIXTURE(ObjectData)
};

class CharData : public ObjectData
{
public:
};