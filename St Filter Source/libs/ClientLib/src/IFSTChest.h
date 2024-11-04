#pragma once
#include <IFMainFrame.h>
#include "IFSTChestSlotList.h"
#include <list>
#include "ICPlayer.h"
#include "IFSpinControl.h"


#define MEMUTIL_READ_BY_PTR_OFFSET(ptr, offset, type) \
	*(type*)(((uintptr_t)ptr) + offset)

class CIFPlayerChest : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFPlayerChest)

GFX_DECLARE_MESSAGE_MAP(CIFPlayerChest)

public:
    CIFPlayerChest(void);
    ~CIFPlayerChest(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void ResetPosition();
    int OnMouseMove(int a1, int x, int y) override;
    void HideLists();
    void ShowList(BYTE listid);
    bool IsPageFull(BYTE PageID, BYTE LineID);
    void Clear();
    void UpdateChest();
    bool ChestContains(const wchar_t* ItemName);
    //static  DWORD WINAPI UpdateSlotCount(LPVOID lpParam);

private:
    void On_BtnClick_1();

    void On_BtnClick_2();

    void OnClick_Exit();

public:
    static struct Chest
    {
        int LineNum;
        std::wstring ItemIconUrl;
        std::wstring CodeName128;
        bool RandomStat;
        std::n_string OptLevel;
        std::wstring NameStrID128;
        std::wstring Count;
        std::wstring From;
        std::wstring Date;
    };

    static std::vector<Chest> ChestList;

    CIFPlayerChestSlotList* m_slot1;
    CIFPlayerChestSlotList* m_slot2;
    CIFPlayerChestSlotList* m_slot3;
    CIFPlayerChestSlotList* m_slot4;
    CIFPlayerChestSlotList* m_slot5;
    CIFPlayerChestSlotList* m_slot6;
    CIFPlayerChestSlotList* m_slot7;
    CIFPlayerChestSlotList* m_slot8;
    CIFPlayerChestSlotList* m_slot9;
    CIFPlayerChestSlotList* m_slot10;

    CIFSpinControl* m_spin;
    CIFStatic* m_custom_label;
    CIFStatic* m_custom_label2;
    CIFStatic* Count;
    CIFStatic* UniqueName;
    CIFStatic* AliveState;
    CIFStatic* KilledBy;
    CIFStatic* SpwanTime;
    CIFButton* Take;
    CIFButton* TakeAll;
    CIFFrame* Frame;
    CIFStatic* SlotCount;
    CIFStatic* SlotCountText;
    std::n_wstring SelectedItemName;

    void ClearDDJ();

};
