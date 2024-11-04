//
// Created by Admin on 27/4/2022.
//

#include "IFSTMacroAutoBuffSkillSlot.h"

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

GFX_IMPLEMENT_DYNCREATE(CIFSTMacroAutoBuffSkillSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTMacroAutoBuffSkillSlot, CIFWnd)

GFX_END_MESSAGE_MAP()

CIFSTMacroAutoBuffSkillSlot::CIFSTMacroAutoBuffSkillSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

CIFSTMacroAutoBuffSkillSlot::~CIFSTMacroAutoBuffSkillSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTMacroAutoBuffSkillSlot::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect1 = { 5,1,20,20 };
    RECT rect2 = { 30,4,80,13 };


    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, STFILTER_SLOT_PARTYMEMBER_RACE, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, STFILTER_SLOT_PARTYMEMBER_CHARNAME, 0);



    m_custom_label2->m_FontTexture.SetColor(0xffffff);
    m_custom_label3->m_FontTexture.SetColor(0xffffff);
    m_custom_label2->BringToFront();
    m_custom_label3->BringToFront();
    m_custom_label3->TB_Func_5(0);
    this->ShowGWnd(false);
    return true;
}

void CIFSTMacroAutoBuffSkillSlot::WriteLine(int Race, const wchar_t* SkillName)
{

    std::wstringstream Reg;
    Reg <<Race;
    //m_custom_label2->SetText(Reg.str().c_str());
    m_custom_label3->SetText(SkillName);

}
int CIFSTMacroAutoBuffSkillSlot::OnMouseLeftUp(int a1, int x, int y)
{
    if (!m_custom_label3->GetNText().empty())
    {
        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ClearDDJ2();
        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->SelectedSkillName = m_custom_label3->GetNText();
        TB_Func_13("interface\\ifcommon\\com_bar01select_mid.ddj", 0, 0);
    }
    return 0;
}