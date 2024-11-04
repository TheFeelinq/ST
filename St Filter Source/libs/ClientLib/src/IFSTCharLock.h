#pragma once

#include <IFMainFrame.h>
#include "IFEdit.h"

class CIFSTCharLock : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTCharLock)

GFX_DECLARE_MESSAGE_MAP(CIFSTCharLock)

public:
    CIFSTCharLock();

    bool OnCreate(long ln) override;
    int OnMouseMove(int a1, int x, int y) override;
    void OnUpdate() override;
    void CIFSTCharLock::ResetPosition();
private:
    void On_BtnClick();
    void On_BtnClickLockUnLock();
    void On_BtnClickNewLock();

public:
    CIFStatic *m_custom_label;
    CIFStatic *m_time_label;
    CIFStatic *m_password_input_lable;
    CIFStatic *m_password_remove_lable;
    CIFStatic *m_lock_status_lable;
    CIFStatic *m_lock_status_icon;
    CIFStatic *m_lock_status;
    CIFStatic *m_char_lock_title;
    CIFButton *m_button_lock;
    CIFButton *m_button_remove_lock;
    CIFEdit *m_edit1;
    CIFEdit *m_edit2;
};
