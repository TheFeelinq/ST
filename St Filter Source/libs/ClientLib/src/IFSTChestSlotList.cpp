#include "IFSTChestSlotList.h"

#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <PSilkroad.h>
#include <IFApprenticeShipSlot.h>

#define GDR_FIRST_BTN 30
#define GDR_SECOND_BTN 31
#define GDR_THIRD_BTN 32
#define GDR_FOUR_BTN 33
#define GDR_FIVE_BTN 34
#define GDR_SIX_BTN 35
#define GDR_SEVEN_BTN 36
#define GDR_EGHIT_BTN 37
#define GDR_NIGHN_BTN 38
#define GDR_TEEN_BTN 39

GFX_IMPLEMENT_DYNCREATE(CIFPlayerChestSlotList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFPlayerChestSlotList, CIFWnd)
GFX_END_MESSAGE_MAP()


CIFPlayerChestSlotList::CIFPlayerChestSlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFPlayerChestSlotList::~CIFPlayerChestSlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFPlayerChestSlotList::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect1 = { 18,74,540,24 };
    RECT rect2 = { 18,97,540,24 };
    RECT rect3 = { 18,120,540,24 };
    RECT rect4 = { 18,143,540,24 };
    RECT rect5 = { 18,166,540,24 };
    RECT rect6 = { 18,189,540,24 };
    RECT rect7 = { 18,212,540,24 };
    RECT rect8 = { 18,235,540,24 };
    RECT rect9 = { 18,258,540,24 };
    RECT rect10 = { 18,281,540,24 };

    line1 = (CIFPlayerChestSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlot), rect1, 30, 0);
    line2 = (CIFPlayerChestSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlot), rect2, 31, 0);
    line3 = (CIFPlayerChestSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlot), rect3, 32, 0);
    line4 = (CIFPlayerChestSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlot), rect4, 33, 0);
    line5 = (CIFPlayerChestSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlot), rect5, 34, 0);
    line6 = (CIFPlayerChestSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlot), rect6, 35, 0);
    line7 = (CIFPlayerChestSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlot), rect7, 36, 0);
    line8 = (CIFPlayerChestSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlot), rect8, 37, 0);
    line9 = (CIFPlayerChestSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlot), rect9, 38, 0);
    line10 = (CIFPlayerChestSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlot), rect10, 39, 0);

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

void CIFPlayerChestSlotList::OnUpdate()
{
}

void CIFPlayerChestSlotList::ClearDDJ()
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