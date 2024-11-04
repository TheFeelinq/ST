#include "IFSTReverseScrollPlusSlotList.h"

#include <ClientNet\MsgStreamBuffer.h>
#include <PSilkroad.h>


GFX_IMPLEMENT_DYNCREATE(CIFSTReverseScrollPlusSlotList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTReverseScrollPlusSlotList, CIFWnd)
GFX_END_MESSAGE_MAP()


CIFSTReverseScrollPlusSlotList::CIFSTReverseScrollPlusSlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFSTReverseScrollPlusSlotList::~CIFSTReverseScrollPlusSlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTReverseScrollPlusSlotList::OnCreate(long ln)
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

    line1 = (CIFSTReverseScrollPlusSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlot), rect1, 30, 0);
    line2 = (CIFSTReverseScrollPlusSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlot), rect2, 31, 0);
    line3 = (CIFSTReverseScrollPlusSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlot), rect3, 32, 0);
    line4 = (CIFSTReverseScrollPlusSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlot), rect4, 33, 0);
    line5 = (CIFSTReverseScrollPlusSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlot), rect5, 34, 0);
    line6 = (CIFSTReverseScrollPlusSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlot), rect6, 35, 0);
    line7 = (CIFSTReverseScrollPlusSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlot), rect7, 36, 0);
    line8 = (CIFSTReverseScrollPlusSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlot), rect8, 37, 0);


    line1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line8->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);


    line1->ShowGWnd(true);
    line2->ShowGWnd(true);
    line3->ShowGWnd(true);
    line4->ShowGWnd(true);
    line5->ShowGWnd(true);
    line6->ShowGWnd(true);
    line7->ShowGWnd(true);
    line8->ShowGWnd(true);


    line1->BringToFront();
    line2->BringToFront();
    line3->BringToFront();
    line4->BringToFront();
    line5->BringToFront();
    line6->BringToFront();
    line7->BringToFront();
    line8->BringToFront();


    this->ShowGWnd(false);
    return true;

}

void CIFSTReverseScrollPlusSlotList::OnUpdate()
{
}

void CIFSTReverseScrollPlusSlotList::ClearDDJ()
{
    line1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    line8->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);

}