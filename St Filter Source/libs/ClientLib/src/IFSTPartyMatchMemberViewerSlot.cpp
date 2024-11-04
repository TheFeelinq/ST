//
// Created by Admin on 19/2/2022.
//

#include "IFSTPartyMatchMemberViewerSlot.h"
#include "IFflorian0.h"
#include "GInterface.h"
#include "IFflorian0Guide.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <ICPlayer.h>
#include <ctime>

#define STFILTER_SLOT_PARTYMEMBER_RACE 1
#define STFILTER_SLOT_PARTYMEMBER_CHARNAME 2
#define STFILTER_SLOT_PARTYMEMBER_LEVELTEXT 3
#define STFILTER_SLOT_PARTYMEMBER_LEVEL 4

GFX_IMPLEMENT_DYNCREATE(CIFSTPartyMatchMemberViewerSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTPartyMatchMemberViewerSlot, CIFWnd)

GFX_END_MESSAGE_MAP()

CIFSTPartyMatchMemberViewerSlot::CIFSTPartyMatchMemberViewerSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

CIFSTPartyMatchMemberViewerSlot::~CIFSTPartyMatchMemberViewerSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTPartyMatchMemberViewerSlot::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect1 = { 5,1,20,20 };
    RECT rect2 = { 30,4,80,13 };
    RECT rect3 = { 130,4,15,13 };
    RECT rect4 = { 150,4,20,13 };

    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, STFILTER_SLOT_PARTYMEMBER_RACE, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, STFILTER_SLOT_PARTYMEMBER_CHARNAME, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect3, STFILTER_SLOT_PARTYMEMBER_LEVELTEXT, 0);
    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect4, STFILTER_SLOT_PARTYMEMBER_LEVEL, 0);


    //m_custom_label2->MoveGWnd(GetPos().x + 5, m_custom_label2->GetPos().y);
    //m_custom_label3->MoveGWnd(m_custom_label2->GetPos().x + m_custom_label2->GetSize().width + 10, m_custom_label3->GetPos().y);
    //m_custom_label4->MoveGWnd(m_custom_label3->GetPos().x + m_custom_label3->GetSize().width + 10, m_custom_label4->GetPos().y);
    //m_custom_label5->MoveGWnd(m_custom_label4->GetPos().x + m_custom_label4->GetSize().width + 30, m_custom_label5->GetPos().y);


    m_custom_label2->m_FontTexture.SetColor(0xffffff);
    m_custom_label3->m_FontTexture.SetColor(0xffffff);
    m_custom_label4->m_FontTexture.SetColor(0xffffff);
    m_custom_label5->m_FontTexture.SetColor(0xffffff);
    m_custom_label2->BringToFront();
    m_custom_label3->BringToFront();
    m_custom_label4->BringToFront();
    m_custom_label5->BringToFront();
    this->ShowGWnd(false);
    return true;
}

void CIFSTPartyMatchMemberViewerSlot::WriteLine(int Race, const wchar_t* CharName, const wchar_t* LevelText, const wchar_t* Level)
{

    if (Race >= 14875 && Race <= 14900)
    {
        m_custom_label2->TB_Func_13("interface\\ifcommon\\com_kindred_europe.ddj", 1, 1);
    }
    if (Race >= 1907 && Race <= 1932)
    {
        m_custom_label2->TB_Func_13("interface\\ifcommon\\com_kindred_china.ddj", 1, 1);
    }
    if (Race ==0)
    {
        m_custom_label2->TB_Func_13("", 1, 1);
    }
    m_custom_label3->SetText(CharName);
    m_custom_label4->SetText(LevelText);
    m_custom_label5->SetText(Level);

}
