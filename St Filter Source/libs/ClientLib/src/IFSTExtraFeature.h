#pragma once

#include <IFMainFrame.h>
#include "IFEdit.h"
#include "IFSlotWithHelp.h"

class CIFSTExtraFeature : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTExtraFeature)

GFX_DECLARE_MESSAGE_MAP(CIFSTExtraFeature)

public:
    CIFSTExtraFeature();

    bool OnCreate(long ln) override;
    int OnMouseMove(int a1, int x, int y) override;
    int OnMouseLeftUp(int a1, int x, int y) override;
    void OnUpdate() override;
    bool Func_28(int a1, int a2, int a3) override;
    void ResetPosition();
private:
    void On_BtnClickSetAutoABS();
    void On_BtnClickSetAutoINC();
    void On_BtnClickSetAutoDamageIncreasebubble();
    void On_BtnClickSetAutoDamageabsorbbubble();
    void On_BtnClickSetAutoRessurect();
    void On_BtnClickSetAutoUpSkill();
    void On_BtnClickSetAutoBerserkerPotion();
public:
    CIFStatic *m_custom_label;
    CIFStatic *m_custom_label_tooltip;
    CIFStatic *m_custom_label_tooltip2;
    CIFStatic *m_custom_label_tooltip3;
    CIFStatic *m_custom_label_tooltip4;
    CIFStatic *m_custom_label_tooltip5;
    CIFStatic *m_custom_label_tooltip6;
    CIFStatic *m_custom_label_tooltip7;
    CIFStatic *m_custom_label_tooltip8;
    CIFSlotWithHelp *m_slot1;
    CIFSlotWithHelp *m_slot2;
    CIFSlotWithHelp *m_slot3;
    CIFSlotWithHelp *m_slot4;
    CIFSlotWithHelp *m_slot5;
    CIFSlotWithHelp *m_slot6;
    CIFButton *m_btn1;
    CIFButton *m_btn2;
    CIFButton *m_btn3;
    CIFButton *m_btn4;
    CIFButton *m_btn5;
    CIFButton *m_btn6;
    CIFButton *m_btn7;
    CIFButton *m_btn8;
    CIFEdit *m_edit;
    float m_color[3];
    char m_buffer[200];
    static BYTE m_dame_inc_slot;
    static BYTE m_dame_abs_slot;
    static BYTE m_dame_Increasebubble_slot;
    static BYTE m_dame_absorbbubble_slot;
    static BYTE m_ressurect_slot;
    static BYTE m_berserker_potion_slot;
    bool SetAutoABS;
    bool SetAutoINC;
    bool SetAutoABSbubble;
    bool SetAutoINCbubble;
    bool SetAutoRessurect;
    bool SetAutoBerserkerPotion;
    CSOItem *m_slot1_os;
    CSOItem *m_slot2_os;
    CSOItem *m_slot3_os;
    CSOItem *m_slot4_os;
};
