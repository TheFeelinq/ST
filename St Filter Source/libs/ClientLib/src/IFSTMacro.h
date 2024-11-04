#pragma once

#include <IFMainFrame.h>
#include "IFEdit.h"

class CIFSTMacro : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTMacro)

GFX_DECLARE_MESSAGE_MAP(CIFSTMacro)

public:
    CIFSTMacro();

    bool OnCreate(long ln) override;
    int OnMouseMove(int a1, int x, int y) override;
    void OnUpdate() override;
    void ResetPosition();
private:
    void On_BtnClick_Autohunt();
    void On_BtnClick_Autohunt_opt();
    void On_BtnClick_AutoPotion();
    void On_BtnClick_AutoPotion_opt();
    void On_BtnClick_Pet_AutoPotion();
    void On_BtnClick_Pet_AutoPotion_opt();
private:
    CIFStatic *m_custom_label;
    CIFStatic *m_custom_label1;
    CIFStatic *m_custom_label2;
    CIFStatic *m_custom_label3;
    CIFStatic *m_custom_label_tooltip;
public:
    CIFButton *btn2;
    CIFButton *btn3;
    CIFButton *btn4;
    bool status;
};
