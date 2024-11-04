//
// Created by Admin on 12/8/2020.
//

#pragma once
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include "IFEdit.h"

class CIFSTPvpChallengeAnswer : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFSTPvpChallengeAnswer)
GFX_DECLARE_MESSAGE_MAP(CIFSTPvpChallengeAnswer)

public:
    CIFSTPvpChallengeAnswer(void);
    ~CIFSTPvpChallengeAnswer(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void OnTimer(int) override;
    void SetChatBlocked(int timeoutSeconds);
    void ResetPosition();
private:
    void On_BtnClick();
    void On_BtnClickACCEPT();
private:
    void OnClick_Exit();
public:
    int m_ChatBlock_SecondsLefts;
    CIFTextBox *m_textbox;
    CIFButton *m_mybutton;
    CIFButton *m_mybutton2;
    CIFButton *m_mybutton3;
    CIFButton *m_mybutton4;

    CIFStatic* m_custom_label;
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;
    CIFStatic* m_custom_label6;





};



