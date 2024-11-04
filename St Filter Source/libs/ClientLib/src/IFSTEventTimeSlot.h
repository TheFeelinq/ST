#pragma once
#include "IFMainFrame.h"

class CIFEentTimeSlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFEentTimeSlot)
GFX_DECLARE_MESSAGE_MAP(CIFEentTimeSlot)

public:
    CIFEentTimeSlot(void);
    ~CIFEentTimeSlot(void);

    bool OnCreate(long ln) override;
    void WriteLine(const wchar_t* EventName, const wchar_t* DAY);
    void WriteLineEventName(const wchar_t* EventName);
    void WriteLineEventTime(const wchar_t* Time);
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;

};

