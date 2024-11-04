#include "IFSTUniqueHistorySlotList.h"

#include <ClientNet\MsgStreamBuffer.h>
#include <PSilkroad.h>


GFX_IMPLEMENT_DYNCREATE(CIFSTUniqueHistorySlotList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTUniqueHistorySlotList, CIFWnd)
GFX_END_MESSAGE_MAP()


CIFSTUniqueHistorySlotList::CIFSTUniqueHistorySlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFSTUniqueHistorySlotList::~CIFSTUniqueHistorySlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTUniqueHistorySlotList::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect1 = { 18,74,447,24 };
    RECT rect2 = { 18,97,447,24 };
    RECT rect3 = { 18,120,447,24 };
    RECT rect4 = { 18,143,447,24 };
    RECT rect5 = { 18,166,447,24 };
    RECT rect6 = { 18,189,447,24 };
    RECT rect7 = { 18,212,447,24 };
    RECT rect8 = { 18,235,447,24 };
    RECT rect9 = { 18,258,447,24 };
    RECT rect10 = { 18,281,447,24 };

    line1 = (CIFSTUniqueHistorySlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlot), rect1, 30, 0);
    line2 = (CIFSTUniqueHistorySlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlot), rect2, 31, 0);
    line3 = (CIFSTUniqueHistorySlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlot), rect3, 32, 0);
    line4 = (CIFSTUniqueHistorySlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlot), rect4, 33, 0);
    line5 = (CIFSTUniqueHistorySlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlot), rect5, 34, 0);
    line6 = (CIFSTUniqueHistorySlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlot), rect6, 35, 0);
    line7 = (CIFSTUniqueHistorySlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlot), rect7, 36, 0);
    line8 = (CIFSTUniqueHistorySlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlot), rect8, 37, 0);
    line9 = (CIFSTUniqueHistorySlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlot), rect9, 38, 0);
    line10 = (CIFSTUniqueHistorySlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTUniqueHistorySlot), rect10, 39, 0);

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

    line1->BringToFront();
    line2->BringToFront();
    line3->BringToFront();
    line4->BringToFront();
    line5->BringToFront();
    line6->BringToFront();
    line7->BringToFront();
    line8->BringToFront();
    line9->BringToFront();
    line10->BringToFront();

    this->ShowGWnd(false);
    return true;

}

void CIFSTUniqueHistorySlotList::OnUpdate()
{
}

void CIFSTUniqueHistorySlotList::ClearDDJ()
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
}