//
// Created by Admin on 26/4/2022.
//

#include "IFSTMacroAutoBuffSlotList.h"
//
// Created by Admin on 19/2/2022.
//

#include "IFSTPartyMatchMemberViewerSlotList.h"

#include <ClientNet\MsgStreamBuffer.h>
#include <PSilkroad.h>


GFX_IMPLEMENT_DYNCREATE(CIFSTMacroAutoBuffSlotList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTMacroAutoBuffSlotList, CIFWnd)
GFX_END_MESSAGE_MAP()


CIFSTMacroAutoBuffSlotList::CIFSTMacroAutoBuffSlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFSTMacroAutoBuffSlotList::~CIFSTMacroAutoBuffSlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTMacroAutoBuffSlotList::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect1 = { 5,5,120,28 };
    RECT rect2 = { 5,5+ 28,120,28 };
    RECT rect3 = { 5,5+ (28*2),120,28 };
    RECT rect4 = { 5,5+ (28*3),120,28 };
    RECT rect5 = { 5,5+ (28*4),120,28 };
    RECT rect6 = { 5,5+ (28*5),120,28 };
    RECT rect7 = { 5,5+ (28*6),120,28 };
    RECT rect8 = { 5,5+ (28*7),120,28 };


    line1 = (CIFSTMacroAutoBuffSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSlot), rect1, 30, 0);
    line2 = (CIFSTMacroAutoBuffSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSlot), rect2, 31, 0);
    line3 = (CIFSTMacroAutoBuffSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSlot), rect3, 32, 0);
    line4 = (CIFSTMacroAutoBuffSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSlot), rect4, 33, 0);
    line5 = (CIFSTMacroAutoBuffSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSlot), rect5, 34, 0);
    line6 = (CIFSTMacroAutoBuffSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSlot), rect6, 35, 0);
    line7 = (CIFSTMacroAutoBuffSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSlot), rect7, 36, 0);
    line8 = (CIFSTMacroAutoBuffSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTMacroAutoBuffSlot), rect8, 37, 0);

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

void CIFSTMacroAutoBuffSlotList::OnUpdate()
{
}

void CIFSTMacroAutoBuffSlotList::ClearDDJ()
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