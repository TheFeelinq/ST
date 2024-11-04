#pragma once

#include <IFMainFrame.h>
#include "IFEdit.h"

class CIFSTConfirmUrl : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTConfirmUrl)

GFX_DECLARE_MESSAGE_MAP(CIFSTConfirmUrl)

public:
    CIFSTConfirmUrl();

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
