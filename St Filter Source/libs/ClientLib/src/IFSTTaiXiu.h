#pragma once
#include "IFMainFrame.h"
#include "IFEdit.h"



class CIFSTTaiXiu : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFSTTaiXiu)
GFX_DECLARE_MESSAGE_MAP(CIFSTTaiXiu)

public:
    CIFSTTaiXiu(void);
    ~CIFSTTaiXiu(void);
    void ResetPosition();
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void OnTimer(int) override;
    void SetChatBlocked(int timeoutSeconds);
    void SetChatBlocked1(int timeoutSeconds);
    int loop;
    int loopcheck;
    int img;
    int ms;
    bool show;
    struct GifMaker
    {
        std::n_wstring UrlName;
        int showIcon;
    };
    static std::vector<GifMaker> gifMaker;
private:
    void On_BtnClick();
    void On_BtnClick1m();
    void On_BtnClick5m();
    void On_BtnClick10m();
    void On_BtnClicktai();
    void On_BtnClickxiu();
    void On_BtnClickdatcuoc();
    void On_BtnClickDANHBANGGILFSILK();
    void On_BtnClickDANHBANGSILK();
    void On_BtnClickDANHBANGGOLD();
private:
    void OnClick_Exit();
public:
    bool gold;
    bool silk;
    bool gilf;
    int m_ChatBlock_SecondsLeft;
    int m_ChatBlock_SecondsLeft1;
    CIFWnd *m_ChatBlockLabel; //0x0468
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
    CIFStatic* m_custom_label63;
    CIFStatic* m_custom_label64;
    CIFStatic* m_custom_label65;
    CIFStatic* m_custom_label66;
    CIFStatic* m_custom_label67;
    CIFStatic* m_custom_label68;
    CIFStatic* m_custom_label69;
    CIFStatic* m_custom_label70;
    CIFStatic* m_custom_label71;
    CIFStatic* m_custom_label72;
    CIFStatic* m_custom_label73;
    CIFStatic* m_custom_label74;
    CIFStatic* m_custom_label75;

    CIFStatic* m_custom_label76;
    CIFStatic* m_custom_label77;
    CIFStatic* m_custom_label78;
    CIFStatic* m_custom_label79;
    CIFStatic* m_custom_label80;
    CIFStatic* m_custom_label81;
    CIFStatic* m_custom_label82;
    CIFStatic* m_custom_label83;
    CIFStatic* m_custom_label84;
    CIFStatic* m_custom_label85;
    CIFStatic* m_custom_label86;
    CIFStatic* m_custom_label87;
    CIFStatic* m_custom_label88;

    CIFStatic* m_custom_label89;
    CIFStatic* m_custom_label90;
    CIFStatic* m_custom_label91;
    CIFStatic* m_custom_label92;
    CIFStatic* m_custom_label93;
    CIFStatic* m_custom_label94;
    CIFStatic* m_custom_label95;
    CIFStatic* m_custom_label96;
    CIFStatic* m_custom_label97;
    CIFStatic* m_custom_label98;
    CIFStatic* m_custom_label99;

    CIFStatic* m_custom_label100;
    CIFStatic* m_custom_label101;
    CIFStatic* m_custom_label102;
    CIFStatic* m_custom_label103;
    CIFStatic* m_custom_label104;
    CIFStatic* m_custom_label105;
    CIFStatic* m_custom_label106;
    CIFStatic* m_custom_label107;
    CIFStatic* m_custom_label108;
    CIFStatic* m_custom_label109;
    CIFStatic* m_custom_label110;

    CIFStatic* m_custom_label111;
    CIFStatic* m_custom_label112;
    CIFStatic* m_custom_label113;
    CIFStatic* m_custom_label114;
    CIFStatic* m_custom_label115;
    CIFStatic* m_custom_label116;
    CIFStatic* m_custom_label117;
    CIFStatic* m_custom_label118;
    CIFStatic* m_custom_label119;
    CIFStatic* m_custom_label120;
    CIFStatic* m_custom_label121;

    CIFStatic* m_custom_label122;
    CIFStatic* m_custom_label123;
    CIFStatic* m_custom_label124;
    CIFStatic* m_custom_label125;
    CIFStatic* m_custom_label126;
    CIFStatic* m_custom_label127;
    CIFStatic* m_custom_label128;
    CIFStatic* m_custom_label129;
    CIFStatic* m_custom_label130;
    CIFStatic* m_custom_label131;
    CIFStatic* m_custom_label132;
    CIFStatic* m_custom_label133;
    CIFStatic* m_custom_label134;
};



