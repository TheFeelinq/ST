#pragma once

#include <IFMainFrame.h>
#include "IFSTTotalPointSlotList.h"
#include "IFSpinControl.h"

class CIFSTTotalPoints : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTTotalPoints)

GFX_DECLARE_MESSAGE_MAP(CIFSTTotalPoints)

public:
    CIFSTTotalPoints();

    bool OnCreate(long ln) override;

    void OnUpdate() override;
    int OnMouseMove(int a1, int x, int y) override;
    void HideLists();
    void ShowList(BYTE listid);
    bool IsPageFull(BYTE PageID, BYTE LineID);
    void Clear();
    void ClearDDJ();
    void ResetPosition();
    void UpdateTotalPointList();

    static struct TotalPoint
    {
        int LineNum;
        std::wstring Charname;
        std::wstring Guild;

    };

    static std::vector<TotalPoint> TotalPointList;
private:
    void On_BtnClick();


public:
    CIFStatic *m_custom_label;
    CIFStatic *m_custom_label1;
    CIFStatic *m_custom_label2;
    CIFStatic *m_custom_label3;
    CIFStatic *m_custom_label4;
    CIFStatic *m_custom_label5;
    CIFStatic *m_custom_label6;
    CIFStatic *m_custom_label7;
    CIFStatic *m_custom_label8;
    CIFStatic *m_custom_label9;
    CIFStatic *m_custom_label_tooltip;
    CIFStatic *m_custom_label_stt;
    CIFStatic *m_custom_label_name;
    CIFStatic *m_custom_label_point;
    CIFSpinControl* m_spin;

    CIFSTTotalPointSlotList* m_slot1;
    CIFSTTotalPointSlotList* m_slot2;
    CIFSTTotalPointSlotList* m_slot3;
    CIFSTTotalPointSlotList* m_slot4;
    CIFSTTotalPointSlotList* m_slot5;
    CIFSTTotalPointSlotList* m_slot6;
    CIFSTTotalPointSlotList* m_slot7;


    CIFStatic *m_char_icon;
};
