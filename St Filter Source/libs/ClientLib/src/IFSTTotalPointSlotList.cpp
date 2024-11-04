#include "IFSTTotalPointSlotList.h"

#include <ClientNet\MsgStreamBuffer.h>
#include <PSilkroad.h>


GFX_IMPLEMENT_DYNCREATE(CIFSTTotalPointSlotList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTTotalPointSlotList, CIFWnd)
GFX_END_MESSAGE_MAP()


CIFSTTotalPointSlotList::CIFSTTotalPointSlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFSTTotalPointSlotList::~CIFSTTotalPointSlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTTotalPointSlotList::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect1 = { 187,88,289,24 };
    RECT rect2 = { 187,111,289,24 };
    RECT rect3 = { 187,134,289,24 };
    RECT rect4 = { 187,157,289,24 };
    RECT rect5 = { 187,180,289,24 };
    RECT rect6 = { 187,203,289,24 };
    RECT rect7 = { 187,226,289,24 };


    line1 = (CIFSTTotalPointSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlot), rect1, 30, 0);
    line2 = (CIFSTTotalPointSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlot), rect2, 31, 0);
    line3 = (CIFSTTotalPointSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlot), rect3, 32, 0);
    line4 = (CIFSTTotalPointSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlot), rect4, 33, 0);
    line5 = (CIFSTTotalPointSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlot), rect5, 34, 0);
    line6 = (CIFSTTotalPointSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlot), rect6, 35, 0);
    line7 = (CIFSTTotalPointSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTTotalPointSlot), rect7, 36, 0);


    line1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line1->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\honorpoints_rank1.ddj", 0, 0);
    line2->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\honorpoints_rank2.ddj", 0, 0);
    line3->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\honorpoints_rank3.ddj", 0, 0);
    line4->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\honorpoints_rank4.ddj", 0, 0);
    line5->m_custom_label2->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\honorpoints_rank5.ddj", 0, 0);

    line1->ShowGWnd(true);
    line2->ShowGWnd(true);
    line3->ShowGWnd(true);
    line4->ShowGWnd(true);
    line5->ShowGWnd(true);
    line6->ShowGWnd(true);
    line7->ShowGWnd(true);

    line1->BringToFront();
    line2->BringToFront();
    line3->BringToFront();
    line4->BringToFront();
    line5->BringToFront();
    line6->BringToFront();
    line7->BringToFront();


    this->ShowGWnd(false);
    return true;

}

void CIFSTTotalPointSlotList::OnUpdate()
{
}

void CIFSTTotalPointSlotList::ClearDDJ()
{
    line1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);

}