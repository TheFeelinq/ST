#pragma once

#include <IFMainFrame.h>

class CIFflorian0Runtime : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFflorian0Runtime)

GFX_DECLARE_MESSAGE_MAP(CIFflorian0Runtime)

public:
    CIFflorian0Runtime();

    bool OnCreate(long ln) override;
    int OnMouseMove(int a1, int x, int y) override;
    void OnUpdate() override;

public:
    void On_BtnClick();
    void On_BtnClickCharLock();
    void On_BtnClick_Discord();
    void On_BtnClick_Facebook();
    void On_BtnClick_Web();
    void On_BtnClick_New();
    void On_BtnClick_Title();
    void On_BtnClick_ChangeGrantName();
    void ResetPosition();
    void On_BtnClick_EventTimer();
    void On_BtnClick_Unknow();
    void On_BtnClick_Test();
    void On_BtnClick_SendPVP();
public:
    CIFStatic *m_frame_label;
    CIFStatic *m_custom_label;
    CIFStatic *m_char_icon;
    CIFStatic *m_char_name;
    CIFStatic *m_char_lock_lable;
    CIFStatic *m_time_label;
    CIFButton *btn;
    CIFButton *btn1;
    CIFButton *btn2;
    CIFButton *btn3;
    CIFButton *btn4;
    CIFButton *btn5;
    CIFButton *btn6;
    CIFButton *btn7;
    CIFButton *btn8;
};
