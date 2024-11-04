#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include "IFEdit.h"
#include "IFNormalTile.h"

class CIFCustomTitle : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFCustomTitle)
GFX_DECLARE_MESSAGE_MAP(CIFCustomTitle)

public:
    CIFCustomTitle(void);
    ~CIFCustomTitle(void);
    void OnColorSelect(D3DCOLOR Color);
    bool OnCreate(long ln) override;
    void ResetPosition();
    void OnUpdate() override;
    int OnMouseMove(int a1, int x, int y) override;
private:

    void On_BtnClick();
    void On_ColorBtnClick();
    void OnClick_MauTitle();
    void On_BtnClickTenTitle();
    void On_BtnClickHong();
    void On_BtnClickTim();
    void On_BtnClickXanhLam();
    void On_BtnClickXanhLa();
    void On_BtnClickVang();
    void On_BtnClickCam();
    void On_BtnClickDo();
    void On_BtnClickChange();
    void On_BtnClickMuaLuot();
public:
    bool ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);;
private:
    void OnClick_Exit();
public:

    std::n_string color;
    bool tab1;
    float m_color[3];
    char m_buffer[200];
    D3DCOLOR TitleColor;
    static bool ColorSelectShow;
    CIFEdit* m_edit;
    ImGuiWindow* TestWnd;
    CIFTextBox* m_textbox;
    CIFButton* m_mybutton;
    CIFButton* m_mybutton1;
    CIFButton* m_mybutton2;
    CIFButton* m_mybutton3;
    CIFButton* m_mybutton4;
    CIFButton* m_mybutton5;
    CIFButton* m_mybutton6;
    CIFButton* m_mybutton7;
    CIFButton* m_mybutton8;
    CIFButton* m_mybutton9;
    CIFButton* m_mybutton10;
    CIFButton* m_mybutton11;
    CIFButton* m_mybutton12;
    CIFButton* m_mybutton13;
    CIFButton* m_mybutton14;
    CIFButton* m_mybutton15;
    CIFButton* m_mybutton16;
    CIFButton* m_mybutton17;
    CIFButton* m_mybutton18;
    CIFButton* m_mybutton19;
    CIFButton* m_mybutton20;
    CIFStatic* m_custom_label;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;
    CIFNormalTile* m_custom_label6;
    CIFNormalTile* m_custom_label8;
    CIFFrame* m_custom_label9;
    CIFStatic* m_custom_label10;
    CIFStatic* m_custom_label11;
    CIFStatic* m_custom_label12;
    CIFStatic* m_custom_label13;
    CIFStatic* m_custom_label14;
    CIFStatic* m_custom_label15;
    CIFStatic* m_custom_label16;
    CIFStatic* m_custom_label17;
    CIFStatic* m_custom_label18;
    CIFStatic* m_custom_label19;
    CIFStatic* m_custom_label20;
    CIFStatic* m_custom_label21;
    CIFStatic* m_custom_label22;
    CIFStatic* m_custom_label23;
    CIFStatic* m_custom_label24;
    CIFStatic* m_custom_label25;
    CIFFrame* Frame;
    CIFFrame* FrameForm;
    CIFWnd* NormalTitle;
};



