#pragma once

#include <IFMainFrame.h>
#include "IFEdit.h"

class CIFSTPvpChallenge : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTPvpChallenge)

GFX_DECLARE_MESSAGE_MAP(CIFSTPvpChallenge)

public:
    CIFSTPvpChallenge();

    bool OnCreate(long ln) override;
    int OnMouseMove(int a1, int x, int y) override;
    void OnUpdate() override;
    void ResetPosition();
private:
    void On_BtnClick();


private:
    CIFStatic *m_custom_label;
    CIFStatic *m_custom_label1;
    CIFStatic *m_custom_label2;
    CIFStatic *m_custom_label_tooltip;
public:
    CIFEdit *m_edit;
    CIFEdit *m_edit2;

};
