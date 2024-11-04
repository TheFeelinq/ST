#pragma once

#include <IFMainFrame.h>
#include "IFEdit.h"
#include "IFSlotWithHelp.h"

class CIFSTCharItemInfo : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTCharItemInfo)

GFX_DECLARE_MESSAGE_MAP(CIFSTCharItemInfo)

public:
    CIFSTCharItemInfo();

    bool OnCreate(long ln) override;
    int OnMouseMove(int a1, int x, int y) override;
    void OnUpdate() override;
    void ResetPosition();
    void Showbuble(CSOItem *ItemInfo , CIFSlotWithHelp *m_slot);
private:
    void On_BtnClick();



public:
    CIFStatic *m_custom_label;
    CIFStatic *m_custom_label_tooltip;
    CIFStatic *m_custom_label_tooltip2;
    CIFStatic *m_custom_label_tooltip3;
    static  CIFSlotWithHelp *m_slot1;
    static CIFSlotWithHelp *m_slot2;
    static CIFSlotWithHelp *m_slot3;
    static CIFSlotWithHelp *m_slot4;
    static CIFSlotWithHelp *m_slot5;
    static CIFSlotWithHelp *m_slot6;
    static CIFSlotWithHelp *m_slot7;
    static CIFSlotWithHelp *m_slot8;
    static CIFSlotWithHelp *m_slot9;
    static CIFSlotWithHelp *m_slot10;
    static CIFSlotWithHelp *m_slot11;
    static CIFSlotWithHelp *m_slot12;
    static CIFSlotWithHelp *m_slot;
    //CIFStatic *m_edit;
    //CIFStatic *m_edit2;
    static std::n_string CharName;

};
