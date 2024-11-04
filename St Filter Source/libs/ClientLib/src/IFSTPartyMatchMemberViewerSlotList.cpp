//
// Created by Admin on 19/2/2022.
//

#include "IFSTPartyMatchMemberViewerSlotList.h"

#include <ClientNet\MsgStreamBuffer.h>
#include <PSilkroad.h>


GFX_IMPLEMENT_DYNCREATE(CIFSTPartyMatchMemberViewerSlotList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTPartyMatchMemberViewerSlotList, CIFWnd)
GFX_END_MESSAGE_MAP()


CIFSTPartyMatchMemberViewerSlotList::CIFSTPartyMatchMemberViewerSlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFSTPartyMatchMemberViewerSlotList::~CIFSTPartyMatchMemberViewerSlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTPartyMatchMemberViewerSlotList::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect1 = { 5,5,190,28 };
    RECT rect2 = { 5,5+ 28,190,28 };
    RECT rect3 = { 5,5+ (28*2),190,28 };
    RECT rect4 = { 5,5+ (28*3),190,28 };
    RECT rect5 = { 5,5+ (28*4),190,28 };
    RECT rect6 = { 5,5+ (28*5),190,28 };
    RECT rect7 = { 5,5+ (28*6),190,28 };
    RECT rect8 = { 5,5+ (28*7),190,28 };


    line1 = (CIFSTPartyMatchMemberViewerSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlot), rect1, 30, 0);
    line2 = (CIFSTPartyMatchMemberViewerSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlot), rect2, 31, 0);
    line3 = (CIFSTPartyMatchMemberViewerSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlot), rect3, 32, 0);
    line4 = (CIFSTPartyMatchMemberViewerSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlot), rect4, 33, 0);
    line5 = (CIFSTPartyMatchMemberViewerSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlot), rect5, 34, 0);
    line6 = (CIFSTPartyMatchMemberViewerSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlot), rect6, 35, 0);
    line7 = (CIFSTPartyMatchMemberViewerSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlot), rect7, 36, 0);
    line8 = (CIFSTPartyMatchMemberViewerSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTPartyMatchMemberViewerSlot), rect8, 37, 0);





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

void CIFSTPartyMatchMemberViewerSlotList::OnUpdate()
{
}

void CIFSTPartyMatchMemberViewerSlotList::ClearDDJ()
{
    line1->TB_Func_13("", 0, 0);
    line2->TB_Func_13("", 0, 0);
    line3->TB_Func_13("", 0, 0);
    line4->TB_Func_13("", 0, 0);
    line5->TB_Func_13("", 0, 0);
    line6->TB_Func_13("", 0, 0);
    line7->TB_Func_13("", 0, 0);
    line8->TB_Func_13("", 0, 0);

}