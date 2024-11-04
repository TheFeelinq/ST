#pragma once

#include <IFMainFrame.h>
#include "IFEdit.h"

class CIFSTLotteryEvent : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTLotteryEvent)

GFX_DECLARE_MESSAGE_MAP(CIFSTLotteryEvent)

public:
    CIFSTLotteryEvent();

    bool OnCreate(long ln) override;

    void OnUpdate() override;
    int loop;
    int loopcheck;
    int img;
public:
    void On_BtnClickGold();
    void On_BtnClickSilk();
    void  ResetPosition();
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
    CIFStatic *m_custom_label10;

    CIFStatic *m_time_label;
    CIFEdit *m_edit;
};
