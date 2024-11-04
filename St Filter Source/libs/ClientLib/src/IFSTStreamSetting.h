#pragma once

#include <IFMainFrame.h>
#include "IFEdit.h"
#include "IFCheckBox.h"
class CIFSTStreamSetting : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTStreamSetting)

GFX_DECLARE_MESSAGE_MAP(CIFSTStreamSetting)

public:
    CIFSTStreamSetting();

    bool OnCreate(long ln) override;
    int OnMouseMove(int a1, int x, int y) override;
    void OnUpdate() override;
    void ResetPosition();
private:
    void On_BtnClickHigh();
    void On_BtnClickNorMal();
    void On_BtnClickBest();
    void On_BtnClickZoomOn();
    void On_BtnClickZoomOFF();
    void On_BtnClickFreezeOn();
    void On_BtnClickFreezeOFF();
    void On_BtnClickShowWND();
public:
    bool m_fps_show_checked() const;
public:
    CIFStatic *m_custom_label;
    CIFStatic *m_custom_label_tooltip;
    CIFCheckBox *m_fps_show;
    float m_color[3];
    char m_buffer[200];

};
