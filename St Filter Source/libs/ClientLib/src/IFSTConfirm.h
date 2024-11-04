#pragma once

#include <IFMainFrame.h>
#include "IFEdit.h"

class CIFSTConfirm : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTConfirm)

GFX_DECLARE_MESSAGE_MAP(CIFSTConfirm)

public:
    CIFSTConfirm();

    bool OnCreate(long ln) override;
    int OnMouseMove(int a1, int x, int y) override;
    void OnUpdate() override;
    void ResetPosition();
private:
    void On_BtnClick();
    void On_BtnClickCancel();


public:
    CIFStatic *m_custom_label;
    CIFStatic *m_custom_label_tooltip;
    CIFEdit *m_edit;

};
