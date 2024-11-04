#include "IFSTCustomNPCList.h"



GFX_IMPLEMENT_DYNCREATE(CIFSTCustomNPCList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTCustomNPCList, CIFWnd)
GFX_END_MESSAGE_MAP()

#define GDR_STFILTER_STREACH 1

CIFSTCustomNPCList::CIFSTCustomNPCList(void)
{
    //  printf("> " __FUNCTION__ "\n");
}


CIFSTCustomNPCList::~CIFSTCustomNPCList(void)
{
    // printf("> " __FUNCTION__ "\n");
}

bool CIFSTCustomNPCList::OnCreate(long ln)
{
    // printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    //m_IRM.LoadFromFile("resinfo\\GXVSROcustomrank.txt");
    //m_IRM.CreateInterfaceSection("RankingSlotList", this);


    RECT stratcherect = { 15,51,359,280 };
    RECT line1rect = { 18,74,353,24 };
    RECT line2rect = { 18,97,353,24 };
    RECT line3rect = { 18,120,353,24 };
    RECT line4rect = { 18,143,353,24 };
    RECT line5rect = { 18,166,353,24 };
    RECT line6rect = { 18,189,353,24 };
    RECT line7rect = { 18,212,353,24 };
    RECT line8rect = { 18,235,353,24 };
    RECT line9rect = { 18,258,353,24 };
    RECT line10rect = { 18,281,353,24 };
    RECT line11rect = { 18,304,353,24 };

    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), stratcherect, GDR_STFILTER_STREACH, 0);
    //m_custom_label2->TB_Func_13("interface\\ifcommon\\com_blacksquare_", 0, 0);

    //m_custom_label2->MoveGWnd(m_custom_label2->GetPos().x, m_custom_label2->GetPos().y + 2);
    //m_custom_label2->SetGWndSize(m_custom_label2->GetSize().width - 122, m_custom_label2->GetSize().height + 21);

    line1 = (CIFSTCustomNPCSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCSlot), line1rect, 30, 0);
    line2 = (CIFSTCustomNPCSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCSlot), line2rect, 31, 0);
    line3 = (CIFSTCustomNPCSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCSlot), line3rect, 32, 0);
    line4 = (CIFSTCustomNPCSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCSlot), line4rect, 33, 0);
    line5 = (CIFSTCustomNPCSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCSlot), line5rect, 34, 0);
    line6 = (CIFSTCustomNPCSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCSlot), line6rect, 35, 0);
    line7 = (CIFSTCustomNPCSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCSlot), line7rect, 36, 0);
    line8 = (CIFSTCustomNPCSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCSlot), line8rect, 37, 0);
    line9 = (CIFSTCustomNPCSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCSlot), line9rect, 38, 0);
    line10 = (CIFSTCustomNPCSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCSlot), line10rect, 39, 0);
    line11 = (CIFSTCustomNPCSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTCustomNPCSlot), line11rect, 40, 0);

    //line1 = m_IRM.GetResObj<CIFSTCustomNPCSlot>(30, 1);
    //line2 = m_IRM.GetResObj<CIFSTCustomNPCSlot>(31, 1);
    //line3 = m_IRM.GetResObj<CIFSTCustomNPCSlot>(32, 1);
    //line4 = m_IRM.GetResObj<CIFSTCustomNPCSlot>(33, 1);
    //line5 = m_IRM.GetResObj<CIFSTCustomNPCSlot>(34, 1);
    //line6 = m_IRM.GetResObj<CIFSTCustomNPCSlot>(35, 1);
    //line7 = m_IRM.GetResObj<CIFSTCustomNPCSlot>(36, 1);
    //line8 = m_IRM.GetResObj<CIFSTCustomNPCSlot>(37, 1);
    //line9 = m_IRM.GetResObj<CIFSTCustomNPCSlot>(38, 1);
    //line10 = m_IRM.GetResObj<CIFSTCustomNPCSlot>(39, 1);
    //line11 = m_IRM.GetResObj<CIFSTCustomNPCSlot>(40, 1);

    //line1->SetGWndSize(line1->GetSize().width - 122, line1->GetSize().height);
    //line2->SetGWndSize(line2->GetSize().width - 122, line2->GetSize().height);
    //line3->SetGWndSize(line3->GetSize().width - 122, line3->GetSize().height);
    //line4->SetGWndSize(line4->GetSize().width - 122, line4->GetSize().height);
    //line5->SetGWndSize(line5->GetSize().width - 122, line5->GetSize().height);
    //line6->SetGWndSize(line6->GetSize().width - 122, line6->GetSize().height);
    //line7->SetGWndSize(line7->GetSize().width - 122, line7->GetSize().height);
    //line8->SetGWndSize(line8->GetSize().width - 122, line8->GetSize().height);
    //line9->SetGWndSize(line9->GetSize().width - 122, line9->GetSize().height);
    //line10->SetGWndSize(line10->GetSize().width - 122, line10->GetSize().height);
    //line11->SetGWndSize(line11->GetSize().width - 122, line11->GetSize().height);

    //line11->MoveGWnd(line10->GetPos().x, line10->GetPos().y + 23);

    line1->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\honorpoints_rank1.ddj", 0, 0);
    line2->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\honorpoints_rank2.ddj", 0, 0);
    line3->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\honorpoints_rank3.ddj", 0, 0);
    line4->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\honorpoints_rank4.ddj", 0, 0);
    line5->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\honorpoints_rank5.ddj", 0, 0);

    line1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line8->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line9->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line10->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line11->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);

    line1->ShowGWnd(true);
    line2->ShowGWnd(true);
    line3->ShowGWnd(true);
    line4->ShowGWnd(true);
    line5->ShowGWnd(true);
    line6->ShowGWnd(true);
    line7->ShowGWnd(true);
    line8->ShowGWnd(true);
    line9->ShowGWnd(true);
    line10->ShowGWnd(true);
    line11->ShowGWnd(true);

    this->ShowGWnd(false);
    return true;
}

void CIFSTCustomNPCList::OnUpdate()
{
}
void CIFSTCustomNPCList::ClearDDJ()
{
    line1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line8->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line9->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line10->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line11->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
}