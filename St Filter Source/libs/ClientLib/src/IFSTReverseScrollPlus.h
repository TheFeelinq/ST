#pragma once

#include <IFMainFrame.h>
#include "IFSTReverseScrollPlusSlotList.h"

class CIFSTReverseScrollPlus : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTReverseScrollPlus)

GFX_DECLARE_MESSAGE_MAP(CIFSTReverseScrollPlus)

public:
    CIFSTReverseScrollPlus();

    bool OnCreate(long ln) override;
    int OnMouseMove(int a1, int x, int y) override;
    void OnUpdate() override;
    void HideLists();
    void ShowList(BYTE listid);
    bool IsPageFull(BYTE PageID, BYTE LineID);
    void Clear();
    void UpdatePartyMemberList();
    void ClearDDJ();
    void ResetPosition();
    bool GetBtnStatus() const;
    void MoveToPartyMember();
    static struct ReverseScrollPlus
    {
        int LineNum;
        std::wstring CharName;
        std::wstring Location;
        std::wstring Move;

    };

    static std::vector<ReverseScrollPlus> ReverseScrollPlusList;
private:
    void On_BtnClick();


public:
    CIFStatic* Num;
    CIFStatic* CharName;
    CIFStatic* Location;
    CIFStatic* Move;
    CIFStatic *m_custom_label;
    CIFStatic *m_time_label;
    CIFButton *btn;
    std::n_wstring SelectedCharName;

    CIFSTReverseScrollPlusSlotList* m_slot1;
    CIFSTReverseScrollPlusSlotList* m_slot2;
    CIFSTReverseScrollPlusSlotList* m_slot3;
    CIFSTReverseScrollPlusSlotList* m_slot4;
    CIFSTReverseScrollPlusSlotList* m_slot5;
    CIFSTReverseScrollPlusSlotList* m_slot6;
    CIFSTReverseScrollPlusSlotList* m_slot7;
    CIFSTReverseScrollPlusSlotList* m_slot8;
    static byte ReverseSlot;
    int m_ReverseScollSlot;
    bool m_BtnState;

};
