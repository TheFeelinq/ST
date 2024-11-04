#pragma once
#include "IFMainFrame.h"
#include "IFStaticWithPictureClip.h"
#include "IFSTChest.h"


class CIFflorian0 : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFflorian0)
GFX_DECLARE_MESSAGE_MAP(CIFflorian0)

public:
    CIFflorian0(void);
    ~CIFflorian0(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;


private:
    void On_BtnClick();

private:
    void On_BtnClickifelectuspoints();

private:
    void On_BtnClickIFelectuseventtimers();
private:
    void On_BtnClickCharLock();
    void On_BtnClickUniqueTimer();
    void On_BtnClickTitle();
    void On_BtnClickXoSo();
    void On_BtnClickTichNap();
    void On_BtnClickXepHang();
    void On_BtnClickTrangChu();
    void On_BtnClickDisCord();
    void On_BtnClickFaceBook();
    void On_BtnClickMes();
private:
    void On_BtnClickIFElectusGrantName();
private:
    void OnClick_Exit();

public:
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
    CIFStaticWithPictureClip *m_leaderPlayerPicture;
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



};
