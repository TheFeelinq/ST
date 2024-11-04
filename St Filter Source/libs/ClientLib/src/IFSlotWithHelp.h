#pragma once
#include "SOItem.h"
#include "IFEquipment.h"
#include "IFWnd.h"
#include "IFStatic.h"

/*iVar1 = FUN_00570dc0();
uVar3 = extraout_EDX_00;
if ((iVar1 != 0) && (this != (int *)0x0)) {
FUN_008bef90(local_1e0);
local_4 = 0;
iVar2 = FUN_006667c0(iVar1);*/


class CIFSlotWithHelp : public CIFWnd
{

GFX_DECLARE_DYNAMIC_EXISTING(CIFSlotWithHelp, 0x00ee9B18)
public:

    void HelperBubbleInventoryAndEquipment(class CIFHelperBubbleWindow *helperBubble);
//00680da0
//0067cfb0
    /// put item to slot with help
    void FUN_006871d0(CSOItem *itemInfo);
    ///00685e50
    void RenderMyselfIMPL();
    ///0066b460
    bool OnCreateIMPL(long ln);
    /// dis/en mouse click on item
    void FUN_00666810(undefined a1);
    /// set   blur icon of item
    void FUN_00666830(undefined a1);
    /// set   blur icon of item
    void FUN_00666850(int a1);
    ///
    void FUN_00686db0();


    /// \param SlotIndex
    void SetInventorySlotIndex(int SlotIndex);
    int GetInventorySlotIndex();
    int GetItemSourceParentWindowId();
    int GetParentWindowId();
    int GetSkillSlotInDex();
    int GetSlotInInventory();

/*    void sub_686C50(DWORD32 a2) const;
    void sub_685F20(DWORD32 a2) const;
    void sub_6860A0(DWORD32 a2) const;
    void sub_66EC40(DWORD32 a2) const;
    void sub_672990(DWORD32 a2) const;
    void sub_686DB0() const;*/
    void AppendAdvancedInfo(class CIFHelperBubbleWindow* window);
    void UpdateLocation(DWORD x, DWORD y);
    void MakeBubble();
    void ShowGWnd(bool bVisible);
public:
    //36C type 12 skill bar 70 backpack 71 equipment bar 73 skills
    //390 Item information pointer CSOItem
    int Type;//0x36C //windowsID
    int SlotType;//0x370 //windowsID
    int Slot;//0x374 // slot in windowID
    char pad_0x0378[0x8];//0x378
    int field_0x380;//0x380
    char pad_0x0384[0xC];//0x384
    CSOItem* ItemInfo;//0x390
    char pad_0x394[0x4];//0x394
    CSOItem m_SOItem; //0x0398
    char pad_0x036C[0x628-(0x0398+0x1d0)];
    const IDirect3DBaseTexture9* m_brokenIcon; //0x628
    const IDirect3DBaseTexture9* m_icon_disable;
    const IDirect3DBaseTexture9* m_icon_item_warning;
    const IDirect3DBaseTexture9* m_icon_mall_repair;
    const IDirect3DBaseTexture9* m_icon_mall_transgender;
    const IDirect3DBaseTexture9* m_icon_edge_rare;
    const IDirect3DBaseTexture9* m_pt_edge_effect;
    const IDirect3DBaseTexture9* m_pt_life_effect;
    const IDirect3DBaseTexture9* m_icon_edge_nasrun;
    char pad_0x064c[16]; //0x064c
    int m_SkillID;//0x065c
BEGIN_FIXTURE()
        //ENSURE_SIZE(0x06C8)
        ENSURE_OFFSET(Type, 0x36c)
        ENSURE_OFFSET(SlotType, 0x370)
        ENSURE_OFFSET(Slot, 0x374)
        ENSURE_OFFSET(field_0x380, 0x380)
        ENSURE_OFFSET(ItemInfo, 0x390)
        ENSURE_OFFSET(m_SOItem, 0x0398)
        ENSURE_OFFSET(m_brokenIcon, 0x628);
        ENSURE_OFFSET(m_icon_disable, 0x62c);
        ENSURE_OFFSET(m_icon_item_warning, 0x630);
        ENSURE_OFFSET(m_icon_mall_repair, 0x634);
        ENSURE_OFFSET(m_icon_mall_transgender, 0x638);
        ENSURE_OFFSET(m_icon_edge_rare, 0x63c);
        ENSURE_OFFSET(m_pt_edge_effect, 0x640);
        ENSURE_OFFSET(m_pt_life_effect, 0x644);
        ENSURE_OFFSET(m_icon_edge_nasrun, 0x648);
        ENSURE_OFFSET(m_SkillID, 0x65c);
    END_FIXTURE()
    RUN_FIXTURE(CIFSlotWithHelp)
}; //Size=0x06C8