#pragma once
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"

#include <ghidra/undefined.h>
#include "IFWnd.h"
#include "IFChatModeViewer.h"
#include "IFSelectableArea.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include "IFButton.h"
#include "IFEdit.h"
#include "unsorted.h"

class CIFSwitchTitle : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFSwitchTitle)
GFX_DECLARE_MESSAGE_MAP(CIFSwitchTitle)

public:
    CIFSwitchTitle(void);
    ~CIFSwitchTitle(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void OnListChatThing(int, int);
    int OnMouseMove(int a1, int x, int y) override;

    void ResetPosition();
    void ClearTextbox();

private:
    void On_BtnClick();
    void On_BtnClick1();
    void OnClick_Exit();
public:
    int m_chatSize;
    D3DCOLOR TitleColor;
    static const int chatSizeUnit = 56;
    CIFVerticalScroll* m_vericalSroll;
    CIFTextBox* m_textbox;
    CIFButton* m_mybutton;
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
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;
    CIFStatic* m_custom_label6;
    CIFStatic* m_custom_label7;
    CIFStatic* m_custom_label8;
    CIFStatic* m_custom_label9;
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
    CIFStatic* Frame;

};