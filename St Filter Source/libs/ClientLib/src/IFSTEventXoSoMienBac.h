#pragma once
#include "IFMainFrame.h"
#include "IFEdit.h"



class CIFSTEventXoSoMienBac : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFSTEventXoSoMienBac)
GFX_DECLARE_MESSAGE_MAP(CIFSTEventXoSoMienBac)

public:
    CIFSTEventXoSoMienBac(void);
    ~CIFSTEventXoSoMienBac(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void  ResetPosition();
private:
    void On_BtnClick();
    void On_BtnClickKQ();
    void On_BtnClickLichSu();
    void On_BtnClickDanhDe();
    void On_BtnClickDANHBANGGOLD();
    void On_BtnClickLichSuDANHBANGSILK();
    void On_BtnClickDanhDeDANHBANGGILFSILK();
private:
    void OnClick_Exit();
public:
    bool gold;
    bool silk;
    bool gilf;
    CIFEdit *m_edit;
    CIFEdit *m_edit1;
    CIFButton *m_mybutton;
    CIFButton *m_mybutton2;
    CIFButton *m_mybutton3;
    CIFButton *m_mybutton4;
    CIFButton *m_mybutton5;
    CIFButton *m_mybutton6;
    CIFButton *m_mybutton7;
    CIFButton *m_mybutton8;
    CIFButton *m_mybutton9;
    CIFButton *m_mybutton10;
    CIFButton *m_mybutton11;
    CIFButton *m_mybutton12;
    CIFButton *m_mybutton13;
    CIFButton *m_mybutton14;
    CIFButton *m_mybutton15;
    CIFButton *m_mybutton16;
    CIFButton *m_mybutton17;
    CIFButton *m_mybutton18;
    CIFButton *m_mybutton19;
    CIFButton *m_mybutton20;
    CIFButton *m_mybutton21;
    CIFButton *m_mybutton22;
    CIFButton *m_mybutton23;
    CIFButton *m_mybutton24;
    CIFButton *m_mybutton25;
    CIFButton *m_mybutton26;

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

    CIFStatic* m_custom_label26;
    CIFStatic* m_custom_label27;
    CIFStatic* m_custom_label28;
    CIFStatic* m_custom_label29;
    CIFStatic* m_custom_label30;
    CIFStatic* m_custom_label31;
    CIFStatic* m_custom_label32;
    CIFStatic* m_custom_label33;
    CIFStatic* m_custom_label34;
    CIFStatic* m_custom_label35;
    CIFStatic* m_custom_label36;
    CIFStatic* m_custom_label37;
    CIFStatic* m_custom_label38;
    CIFStatic* m_custom_label39;
    CIFStatic* m_custom_label40;
    CIFStatic* m_custom_label41;
    CIFStatic* m_custom_label42;
    CIFStatic* m_custom_label43;
    CIFStatic* m_custom_label44;
    CIFStatic* m_custom_label45;
    CIFStatic* m_custom_label46;
    CIFStatic* m_custom_label47;

    CIFStatic* m_custom_label48;
    CIFStatic* m_custom_label49;
    CIFStatic* m_custom_label50;
    CIFStatic* m_custom_label51;
    CIFStatic* m_custom_label52;
    CIFStatic* m_custom_label53;
    CIFStatic* m_custom_label54;
    CIFStatic* m_custom_label55;
    CIFStatic* m_custom_label56;
    CIFStatic* m_custom_label57;
    CIFStatic* m_custom_label58;
    CIFStatic* m_custom_label59;
    CIFStatic* m_custom_label60;
    CIFStatic* m_custom_label61;
    CIFStatic* m_custom_label62;
};



