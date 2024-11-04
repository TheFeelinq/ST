
#include "IFSTMacroAutoBuffedSkillSlot.h"
#include "GInterface.h"
#include "IFflorian0Guide.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <ICPlayer.h>
#include <ctime>

#define STFILTER_SLOT_PARTYMEMBER_RACE 1
#define STFILTER_SLOT_PARTYMEMBER_CHARNAME 2
#define STFILTER_SLOT_PARTYMEMBER_LEVELTEXT 3
#define STFILTER_SLOT_PARTYMEMBER_LEVEL 4

GFX_IMPLEMENT_DYNCREATE(CIFSTMacroAutoBuffedSkillSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTMacroAutoBuffedSkillSlot, CIFWnd)

GFX_END_MESSAGE_MAP()

CIFSTMacroAutoBuffedSkillSlot::CIFSTMacroAutoBuffedSkillSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

CIFSTMacroAutoBuffedSkillSlot::~CIFSTMacroAutoBuffedSkillSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTMacroAutoBuffedSkillSlot::OnCreate(long ln)
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

void CIFSTMacroAutoBuffedSkillSlot::WriteLine(int Race, int SkillID)
{


    //m_custom_label2->SetText(Reg.str().c_str());
    if(SkillID > 0)
    {
        std::wstringstream Reg;
        Reg <<Race;
        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ClearDDJ3();
        for (int i = 0; i < g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->CharSkillDataList.size(); ++i)
        {
            if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->CharSkillDataList[i].SkillID == SkillID)
            {
                m_custom_label3->SetText(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->CharSkillDataList[i].SkillNames.c_str());
                break;
            }
        }
    } else
    {
        m_custom_label3->SetText(L"");
    }



}
int CIFSTMacroAutoBuffedSkillSlot::OnMouseLeftUp(int a1, int x, int y)
{
    if (!m_custom_label3->GetNText().empty())
    {
        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ClearDDJ3();
        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->SelectedSkillNameRemove = m_custom_label3->GetNText();
        TB_Func_13("interface\\ifcommon\\com_bar01select_mid.ddj", 0, 0);
        for (int i = 0; i < g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->CharSkillDataList.size(); ++i)
        {
            if (wcscmp(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->CharSkillDataList[i].SkillNames.c_str(), m_custom_label3->GetNText().c_str()) == 0)
            {
                g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->SkillIDSlelected = g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->CharSkillDataList[i].SkillID;
                break;
            }
        }
    }
    return 0;
}