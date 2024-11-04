#pragma once

#include <IFMainFrame.h>
#include "IFSTUniqueHistorySlotList.h"
#include "IFSpinControl.h"

class CIFSTUniqueHistory : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTUniqueHistory)

GFX_DECLARE_MESSAGE_MAP(CIFSTUniqueHistory)

public:
    CIFSTUniqueHistory();

    bool OnCreate(long ln) override;
    int OnMouseMove(int a1, int x, int y) override;
    void OnUpdate() override;
    void HideLists();
    void ShowList(BYTE listid);
    bool IsPageFull(BYTE PageID, BYTE LineID);
    void Clear();
    void UpdateUniqueList();
    void ClearDDJ();
    void CIFSTUniqueHistory::ResetPosition();
    static struct UniqueHistory
    {
        int LineNum;
        std::wstring NameStrID128;
        std::wstring State;
        std::wstring Killer;
        std::wstring Date;

    };

    static std::vector<UniqueHistory> UniqueHistoryList;
private:
    void On_BtnClick();


public:
    CIFStatic* UniqueName;
    CIFStatic* AliveState;
    CIFStatic* KilledBy;
    CIFStatic* SpwanTime;
    CIFStatic *m_custom_label;
    CIFStatic *m_time_label;
    CIFSpinControl* m_spin;


    CIFSTUniqueHistorySlotList* m_slot1;
    CIFSTUniqueHistorySlotList* m_slot2;
    CIFSTUniqueHistorySlotList* m_slot3;
    CIFSTUniqueHistorySlotList* m_slot4;
    CIFSTUniqueHistorySlotList* m_slot5;
    CIFSTUniqueHistorySlotList* m_slot6;
    CIFSTUniqueHistorySlotList* m_slot7;
    CIFSTUniqueHistorySlotList* m_slot8;
    CIFSTUniqueHistorySlotList* m_slot9;
    CIFSTUniqueHistorySlotList* m_slot10;
};
