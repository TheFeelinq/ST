//
// Created by Admin on 26/4/2022.
//

#include "IFSTMacroAutoBuffSlot.h"

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

GFX_IMPLEMENT_DYNCREATE(CIFSTMacroAutoBuffSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTMacroAutoBuffSlot, CIFWnd)

GFX_END_MESSAGE_MAP()

CIFSTMacroAutoBuffSlot::CIFSTMacroAutoBuffSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

CIFSTMacroAutoBuffSlot::~CIFSTMacroAutoBuffSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTMacroAutoBuffSlot::OnCreate(long ln)
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


    m_custom_label2->m_FontTexture.SetColor(0xffffff);
    m_custom_label3->m_FontTexture.SetColor(0xffffff);

    m_custom_label2->BringToFront();
    m_custom_label3->BringToFront();

    this->ShowGWnd(false);
    return true;
}

void CIFSTMacroAutoBuffSlot::WriteLine(int Race, const wchar_t* CharName, const wchar_t* LevelText, const wchar_t* Level)
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


}
int CIFSTMacroAutoBuffSlot::OnMouseLeftUp(int a1, int x, int y)
{
    if (!m_custom_label3->GetNText().empty())
    {
        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ClearDDJ();
        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ClearDDJ3();
        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->Clear3();
        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->SelectedCharName = m_custom_label3->GetNText();
        TB_Func_13("interface\\ifcommon\\com_bar01select_mid.ddj", 0, 0);
        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->UpdateSkillBuffedList(m_custom_label3->GetNText().c_str());

    }
    return 0;
}