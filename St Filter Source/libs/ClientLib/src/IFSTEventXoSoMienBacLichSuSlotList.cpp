#include "IFSTEventXoSoMienBacLichSuSlotList.h"



GFX_IMPLEMENT_DYNCREATE(CIFSTEventXoSoMienBacLichSuSlotList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTEventXoSoMienBacLichSuSlotList, CIFWnd)
GFX_END_MESSAGE_MAP()

#define GDR_GXVSRO_STREACH 1

CIFSTEventXoSoMienBacLichSuSlotList::CIFSTEventXoSoMienBacLichSuSlotList(void)
{
    //  printf("> " __FUNCTION__ "\n");
}


CIFSTEventXoSoMienBacLichSuSlotList::~CIFSTEventXoSoMienBacLichSuSlotList(void)
{
    // printf("> " __FUNCTION__ "\n");
}

bool CIFSTEventXoSoMienBacLichSuSlotList::OnCreate(long ln)
{
    // printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);


    RECT line1rect = { 25,74,477,24 };
    RECT line2rect = { 25,97,477,24 };
    RECT line3rect = { 25,120,477,24 };
    RECT line4rect = { 25,143,477,24 };
    RECT line5rect = { 25,166,477,24 };
    RECT line6rect = { 25,189,477,24 };
    RECT line7rect = { 25,212,477,24 };
    RECT line8rect = { 25,235,477,24 };
    RECT line9rect = { 25,258,477,24 };
    RECT line10rect = { 25,281,477,24 };


    line1 = (CIFSTEventXoSoMienBacLichSuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlot), line1rect, 30, 0);
    line2 = (CIFSTEventXoSoMienBacLichSuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlot), line2rect, 31, 0);
    line3 = (CIFSTEventXoSoMienBacLichSuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlot), line3rect, 32, 0);
    line4 = (CIFSTEventXoSoMienBacLichSuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlot), line4rect, 33, 0);
    line5 = (CIFSTEventXoSoMienBacLichSuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlot), line5rect, 34, 0);
    line6 = (CIFSTEventXoSoMienBacLichSuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlot), line6rect, 35, 0);
    line7 = (CIFSTEventXoSoMienBacLichSuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlot), line7rect, 36, 0);
    line8 = (CIFSTEventXoSoMienBacLichSuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlot), line8rect, 37, 0);
    line9 = (CIFSTEventXoSoMienBacLichSuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlot), line9rect, 38, 0);
    line10 = (CIFSTEventXoSoMienBacLichSuSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventXoSoMienBacLichSuSlot), line10rect, 39, 0);



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

    this->ShowGWnd(false);
    return true;
}

void CIFSTEventXoSoMienBacLichSuSlotList::OnUpdate()
{
}
void CIFSTEventXoSoMienBacLichSuSlotList::ClearDDJ()
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