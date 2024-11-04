#pragma once

#include <IFMainFrame.h>
#include "IFEdit.h"

class CIFSTChangeGrantName : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTChangeGrantName)

GFX_DECLARE_MESSAGE_MAP(CIFSTChangeGrantName)

public:
    CIFSTChangeGrantName();

    bool OnCreate(long ln) override;
    int OnMouseMove(int a1, int x, int y) override;
    void OnUpdate() override;
    void CIFSTChangeGrantName::ResetPosition();
private:
    void On_BtnClick();


public:
    CIFStatic *m_custom_label;
    CIFStatic *m_custom_label_tooltip;
    CIFEdit *m_edit;
    float m_color[3];
    char m_buffer[200];
};
