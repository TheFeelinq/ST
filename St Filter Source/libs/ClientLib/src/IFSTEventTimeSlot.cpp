#include "IFSTEventTimeSlot.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <ICPlayer.h>
#include <BSLib\multiBYTE.h>
#include "ICPlayer.h"
#include <BSLib/Debug.h>

#define STSRO_SLOT_EVENTNAME 11
#define STSRO_SLOT_DAY 12
#define STSRO_SLOT_EVENTTIME 13
#define STSRO_SLOT_STATE 14

GFX_IMPLEMENT_DYNCREATE(CIFEentTimeSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFEentTimeSlot, CIFWnd)
GFX_END_MESSAGE_MAP()

CIFEentTimeSlot::CIFEentTimeSlot(void)
{
    // BS_DEBUG("> " __FUNCTION__);
}


CIFEentTimeSlot::~CIFEentTimeSlot(void)
{
    // BS_DEBUG("> " __FUNCTION__);
}

bool CIFEentTimeSlot::OnCreate(long ln)
{
    // Populate inherited members
    CIFWnd::OnCreate(ln);

    TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);

    RECT line1rect = { 2,5,165,13 };
    RECT line2rect = { 177,5,13,13 };
    RECT line3rect = { 222,5,120,13 };
   // RECT line4rect = { 297,5,45,13 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), line1rect, STSRO_SLOT_EVENTNAME, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), line2rect, STSRO_SLOT_DAY, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), line3rect, STSRO_SLOT_EVENTNAME, 0);
  //  m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), line4rect, STSRO_SLOT_STATE, 0);

    m_custom_label1->SetTextColor(0xffffff);
   // m_custom_label2->SetTextColor(0xffffff);
    m_custom_label3->SetTextColor(0xffffff);
  //  m_custom_label4->SetTextColor(0x5ad3a9);

    this->ShowGWnd(false);
    return true;
}

void CIFEentTimeSlot::WriteLine(const wchar_t* EventName, const wchar_t* DAY)
{
    m_custom_label1->SetText(EventName);
    //m_custom_label2->SetText(DAY);
    m_custom_label3->SetText(DAY);
    //m_custom_label4->SetText(State);


}
void CIFEentTimeSlot::WriteLineEventName(const wchar_t* EventName)
{
    m_custom_label1->SetText(EventName);



}
void CIFEentTimeSlot::WriteLineEventTime(const wchar_t* Time)
{

    m_custom_label3->SetText(Time);


}
