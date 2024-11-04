#include "IFSTEventRegisterSlotList.h"
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>

#define STSRO_TITLE 3
#define STSRO_FRAME 5
#define STSRO_STREATCH 6

#define STSRO_SUBJ_NUM 25
#define STSRO_SUBJ_NAME 26
#define STSRO_SUBJ_DAY 27
#define STSRO_SUBJ_TIME 28
#define STSRO_SUBJ_STATE 29

#define STSRO_SLOT_1 30
#define STSRO_SLOT_2 31
#define STSRO_SLOT_3 32
#define STSRO_SLOT_4 33
#define STSRO_SLOT_5 34
#define STSRO_SLOT_6 35
#define STSRO_SLOT_7 36
#define STSRO_SLOT_8 37
#define STSRO_SLOT_9 38
#define STSRO_SLOT_10 39
#define STSRO_SLOT_11 40
#define STSRO_SLOT_12 41

GFX_IMPLEMENT_DYNCREATE(CIFSTEventRegisterSlotList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTEventRegisterSlotList, CIFWnd)
GFX_END_MESSAGE_MAP()


CIFSTEventRegisterSlotList::CIFSTEventRegisterSlotList(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFSTEventRegisterSlotList::~CIFSTEventRegisterSlotList(void)
{
    // printf("> " __FUNCTION__ "\n");
}

bool CIFSTEventRegisterSlotList::OnCreate(long ln)
{
    // printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT lable1rect = { 20,50,225,167 };
    RECT lable2rect = { 2,54,227,24 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable1rect, STSRO_STREATCH, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable2rect, STSRO_SUBJ_NAME, 0);


    RECT Line1rect = { 20,220,222,24 };
    RECT Line2rect = { 20,243,222,24 };
    RECT Line3rect = { 20,266,222,24 };
    RECT Line4rect = { 20,289,222,24 };
    RECT Line5rect = { 20,312,222,24 };
    RECT Line6rect = { 20,335,222,24 };
    RECT Line7rect = { 20,358,222,24 };


    Line1 = (CIFSTEventRegisterSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventRegisterSlot), Line1rect, STSRO_SLOT_1, 0);
    Line2 = (CIFSTEventRegisterSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventRegisterSlot), Line2rect, STSRO_SLOT_2, 0);
    Line3 = (CIFSTEventRegisterSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventRegisterSlot), Line3rect, STSRO_SLOT_3, 0);
    Line4 = (CIFSTEventRegisterSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventRegisterSlot), Line4rect, STSRO_SLOT_4, 0);
    Line5 = (CIFSTEventRegisterSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventRegisterSlot), Line5rect, STSRO_SLOT_5, 0);
    Line6 = (CIFSTEventRegisterSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventRegisterSlot), Line6rect, STSRO_SLOT_6, 0);
    Line7 = (CIFSTEventRegisterSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTEventRegisterSlot), Line7rect, STSRO_SLOT_7, 0);


    Line1->ShowGWnd(true);
    Line2->ShowGWnd(true);
    Line3->ShowGWnd(true);
    Line4->ShowGWnd(true);
    Line5->ShowGWnd(true);
    Line6->ShowGWnd(true);
    Line7->ShowGWnd(true);

    Line1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);


    m_custom_label1->MoveGWnd(GetPos().x, GetPos().y);
    m_custom_label1->SetGWndSize(232, 265);

    m_custom_label2->MoveGWnd(m_custom_label1->GetPos().x + 2, m_custom_label1->GetPos().y);
    m_custom_label2->TB_Func_13("interface\\guild\\gil_subj_button09.ddj", 0, 0);


    Line1->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 20);
    Line2->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 44);
    Line3->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 68);
    Line4->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 92);
    Line5->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 116);
    Line6->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 140);
    Line7->MoveGWnd(m_custom_label2->GetPos().x + 2, m_custom_label2->GetPos().y + 164);


    m_custom_label2->SetText(TSM_GETTEXTPTR("UIIT_ST_EVENTTIMER_NAME"));


    this->ShowGWnd(false);
    return true;
}

void CIFSTEventRegisterSlotList::OnUpdate()
{
}
void CIFSTEventRegisterSlotList::ClearDDJ()
{
    Line1->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line2->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line3->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line4->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line5->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line6->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    Line7->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);

}