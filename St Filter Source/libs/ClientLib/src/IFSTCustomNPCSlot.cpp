#include "IFSTCustomNPCSlot.h"
#include "ICPlayer.h"
#include "IFflorian0Guide.h"
#include "BSLib/multibyte.h"
#include "GInterface.h"

#define STFILTER_SLOT_UNIQUELOG_NUM 1
#define STFILTER_SLOT_UNIQUELOG_NUM_PIC 2
#define STFILTER_SLOT_UNIQUELOG_NAME 3
#define STFILTER_SLOT_UNIQUELOG_Guild 5
#define STFILTER_SLOT_UNIQUELOG_POINT 6

GFX_IMPLEMENT_DYNCREATE(CIFSTCustomNPCSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTCustomNPCSlot, CIFWnd)
GFX_END_MESSAGE_MAP()

CIFSTCustomNPCSlot::CIFSTCustomNPCSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFSTCustomNPCSlot::~CIFSTCustomNPCSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTCustomNPCSlot::OnCreate(long ln)
{
    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect0 = { 20,5,25,13 };
    RECT rect1 = { 68,5,20,20 };
    RECT rect2 = { 110,5,115,13 };
    RECT rect3 = { 320,5,80,13 };
    RECT rect4 = { 363,5,40,13 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect0, STFILTER_SLOT_UNIQUELOG_NUM, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, STFILTER_SLOT_UNIQUELOG_NUM_PIC, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, STFILTER_SLOT_UNIQUELOG_NAME, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect3, STFILTER_SLOT_UNIQUELOG_Guild, 0);
    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect4, STFILTER_SLOT_UNIQUELOG_POINT, 0);


    m_custom_label2->MoveGWnd(GetPos().x + 1, m_custom_label1->GetPos().y-3);

    m_custom_label3->MoveGWnd(m_custom_label1->GetPos().x + m_custom_label1->GetSize().width + 5, m_custom_label1->GetPos().y);
    m_custom_label4->MoveGWnd(m_custom_label3->GetPos().x + m_custom_label3->GetSize().width + 30, m_custom_label1->GetPos().y);
    m_custom_label5->MoveGWnd(m_custom_label4->GetPos().x + m_custom_label4->GetSize().width + 30, m_custom_label1->GetPos().y);

    m_custom_label1->SetTextColor(0xffffff);
    m_custom_label2->SetTextColor(0xffffff);
    m_custom_label3->SetTextColor(0xffffff);
    m_custom_label4->SetTextColor(0xffffff);
    m_custom_label5->SetTextColor(0xffffff);
    m_custom_label2->ShowGWnd(false);
    ShowGWnd(true);
    return true;
}

void CIFSTCustomNPCSlot::OnUpdate()
{
}

void CIFSTCustomNPCSlot::WriteLine(const wchar_t* num, std::n_string ItemName, const wchar_t* Count, const wchar_t* Price)
{
    m_custom_label3->SetGWndSize(16,16);
    m_custom_label3->MoveGWnd(m_custom_label1->GetPos().x + m_custom_label1->GetSize().width + 60, m_custom_label1->GetPos().y);
    m_custom_label4->MoveGWnd(m_custom_label3->GetPos().x + m_custom_label3->GetSize().width + 80, m_custom_label1->GetPos().y);
    m_custom_label5->MoveGWnd(m_custom_label4->GetPos().x + m_custom_label4->GetSize().width + 20, m_custom_label1->GetPos().y);
    m_custom_label1->SetText(num);
    m_custom_label3->TB_Func_13(ItemName.c_str(), 0, 0);
    m_custom_label4->SetText(Count);
    m_custom_label5->SetText(Price);

}

void CIFSTCustomNPCSlot::ShowIcon()
{
    m_custom_label2->ShowGWnd(true);
}
int CIFSTCustomNPCSlot::OnMouseLeftUp(int a1, int x, int y)
{
    if (!m_custom_label1->GetNText().empty())
    {
        g_pCGInterface->GetCustomNPCGUI()->ClearDDJ();
        g_pCGInterface->GetCustomNPCGUI()->SelectedItemName = m_custom_label1->GetNText();
        TB_Func_13("interface\\ifcommon\\com_bar01select_mid.ddj", 0, 0);
    }
    return 0;
}
