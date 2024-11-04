#pragma once
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include <IFEdit.h>
#include <IFSTEventTimeSlot.h>
#include <IFSTEventTimeSlotList.h>
#include <IFSpinControl.h>

class CIFEventTime : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFEventTime)
GFX_DECLARE_MESSAGE_MAP(CIFEventTime)

public:
    CIFEventTime(void);
    ~CIFEventTime(void);
    int OnMouseMove(int a1, int x, int y) override;
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void ResetPosition();

    void HideLists();

    void ShowList(BYTE listid);

    bool EventListContains(const wchar_t* UqName);

    void UpdateLog();

    bool IsPageFull(BYTE PageID, BYTE LineID);

private:
    void On_BtnClick();
    void On_BtnClick1();
    void OnClick_Exit();
public:
    static struct EventSetting
    {
        int LineNum;
        std::wstring EventName;
        std::wstring Day;
    };

    static std::vector<EventSetting> EventList;

    CIFEdit* m_edit;
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
    CIFFrame* Frame;
    //CIFButton* Refresh;
    CIFEventTimeList* Slot1;
    CIFEventTimeList* Slot2;
    CIFEventTimeList* Slot3;
    CIFEventTimeList* Slot4;
    CIFSpinControl* m_spin;
};

