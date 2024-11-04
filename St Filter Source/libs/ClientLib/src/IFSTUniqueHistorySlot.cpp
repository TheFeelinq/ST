#include "IFSTUniqueHistorySlot.h"
#include "IFflorian0.h"
#include "GInterface.h"
#include "IFflorian0Guide.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <ICPlayer.h>
#include <ctime>

#define BFILTER_SLOT_UNIQUELOG_NUM 1
#define BFILTER_SLOT_UNIQUELOG_NAME 2
#define BFILTER_SLOT_UNIQUELOG_STATE 3
#define BFILTER_SLOT_UNIQUELOG_KILLER 4
#define BFILTER_SLOT_UNIQUELOG_TIME 5

GFX_IMPLEMENT_DYNCREATE(CIFSTUniqueHistorySlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTUniqueHistorySlot, CIFWnd)
GFX_END_MESSAGE_MAP()

CIFSTUniqueHistorySlot::CIFSTUniqueHistorySlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

CIFSTUniqueHistorySlot::~CIFSTUniqueHistorySlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTUniqueHistorySlot::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect1 = { 18,5,147,13 };
    RECT rect2 = { 275,5,67,13 };
    RECT rect3 = { 330,5,107,13 };
    RECT rect4 = { 480,5,90,13 };

    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, BFILTER_SLOT_UNIQUELOG_NAME, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, BFILTER_SLOT_UNIQUELOG_STATE, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect3, BFILTER_SLOT_UNIQUELOG_KILLER, 0);
    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect4, BFILTER_SLOT_UNIQUELOG_TIME, 0);

    m_custom_label2->MoveGWnd(GetPos().x + 5, m_custom_label2->GetPos().y);
    m_custom_label3->MoveGWnd(m_custom_label2->GetPos().x + m_custom_label2->GetSize().width + 10, m_custom_label3->GetPos().y);
    m_custom_label4->MoveGWnd(m_custom_label3->GetPos().x + m_custom_label3->GetSize().width + 10, m_custom_label4->GetPos().y);
    m_custom_label5->MoveGWnd(m_custom_label4->GetPos().x + m_custom_label4->GetSize().width + 10, m_custom_label5->GetPos().y);


    m_custom_label2->m_FontTexture.SetColor(0xffffff);
    m_custom_label3->m_FontTexture.SetColor(0xffffff);
    m_custom_label4->m_FontTexture.SetColor(0xffffff);
    m_custom_label5->m_FontTexture.SetColor(0xffffff);

    m_custom_label2->BringToFront();
    m_custom_label3->BringToFront();
    m_custom_label4->BringToFront();
    m_custom_label5->BringToFront();

    this->ShowGWnd(false);
    return true;
}

void CIFSTUniqueHistorySlot::WriteLine(const wchar_t* ItemName, const wchar_t* Count, const wchar_t* From, const wchar_t* Date)
{

    m_custom_label2->SetText(ItemName);
    m_custom_label3->SetText(Count);
    m_custom_label4->SetText(From);
    m_custom_label5->SetText(Date);
    const wchar_t *States;
    States = TSM_GETTEXTPTR("UIIT_ST_UNIQUE_ALIVE");
    if (wcscmp(Count, States) == 0)
    {
        m_custom_label3->m_FontTexture.SetColor(0xFF00FF38);
       // m_custom_label5->SetText(States);
        m_custom_label5->m_FontTexture.SetColor(0xFFB2FF08);
    }
    else
    {
       m_custom_label3->m_FontTexture.SetColor(0xFFFF0000);
    }
    const wchar_t *State1 = TSM_GETTEXTPTR("UIIT_ST_UNIQUE_DIE");
    if (wcscmp(Count, State1) == 0)
    {
        m_custom_label5->m_FontTexture.SetColor(0xFFB2FF08);
    }
}

int CIFSTUniqueHistorySlot::OnMouseLeftUp(int a1, int x, int y)
{
    if (!m_custom_label2->GetNText().empty())
    {
        g_pCGInterface->GetUniqueHistoryGUI()->ClearDDJ();
    }
    return 0;
}
