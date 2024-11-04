#include "IFPlayerMiniInfo.h"
#include "ICPlayer.h"

#define GDR_PMI_GAUGE_HP 0
#define GDR_PMI_GAUGE_MP 1
#define GDR_PMI_TXT_ID 3
#define GDR_PMI_TXT_LEVEL 4
#define GDR_PMI_TXT_HP 5
#define GDR_PMI_TXT_MP 6
#define GDR_PMI_CIRCLE0 7
#define GDR_PMI_CIRCLE1 8
#define GDR_PMI_CIRCLE2 9
#define GDR_PMI_CIRCLE3 10
#define GDR_PMI_CIRCLE4 11
#define GDR_PMI_PICTURE 12
#define GDR_PMI_BTN_JAHWAN 13
#define GDR_PMI_PARTY_LEADER 14
#define GDR_PMI_RACE_MARK 15
#define GDR_PMI_BTN_CINFO 20
#define GDR_PMI_STA_CINFOBG 21
#define GDR_PMI_TXT_PHYATT 22
#define GDR_PMI_TXT_PHYDEF 23
#define GDR_PMI_TXT_MAGATT 24
#define GDR_PMI_TXT_MAGDEF 25
#define GDR_PMI_TXT_HIT 26
#define GDR_PMI_TXT_PARRY 27
#define GDR_PMI_TXT_PHYATTDAT 28
#define GDR_PMI_TXT_PHYDEFDAT 29
#define GDR_PMI_TXT_MAGATTDAT 30
#define GDR_PMI_TXT_MAGDEFDAT 31
#define GDR_PMI_TXT_HITDAT 32
#define GDR_PMI_TXT_PARRYDAT 33
#define GDR_PMI_BTN_STATUP 34
#define GDR_PMI_TXT_STR 35
#define GDR_PMI_TXT_INT 36
#define GDR_PMI_TXT_STRDAT 37
#define GDR_PMI_TXT_INTDAT 38
#define GDR_PMI_DECO_HWAN_SLOT0 40
#define GDR_PMI_DECO_HWAN_SLOT1 41
#define GDR_PMI_DECO_HWAN_SLOT2 42
#define GDR_PMI_DECO_HWAN_SLOT3 43
#define GDR_PMI_DECO_HWAN_SLOT4 44
#define GDR_PMI_HWAN_EFF_FACE 45
#define GDR_PMI_HWAN_EFF_GLOW 46
#define GDR_PMI_PK 50
#define GDR_PMI_FORFEIT 51
#define GDR_PMI_TXT_PHYBAL 52
#define GDR_PMI_TXT_MAGBAL 53
#define GDR_PMI_TXT_PHYBALDAT 54
#define GDR_PMI_TXT_MAGBALDAT 55
#define GDR_PMI_BATTLE_GRADE 60
#define GDR_PMI_FORTRESS_INFO 70
#define GDR_PMI_EFFECT_HP 77
#define GDR_PMI_EFFECT_MP 78
#define GDR_PMI_SELECT 200
bool CIFPlayerMiniInfo::OnCreateIMPL(long ln) {

    bool b = reinterpret_cast<bool (__thiscall *)(CIFPlayerMiniInfo *, long)>(0x007b5600)(this, ln);
    // CIFWnd* Info = this->m_IRM.GetResObj<CIFWnd>(22, 1);
    RECT rect_m_Job_Icon = {this->GetPos().x + 200, this->GetPos().y + 17, 32, 32};
    m_Job_Icon = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_Job_Icon,3131,1);
    return b;
}

void CIFPlayerMiniInfo::OnUpdateIMPL()
{
    int trijobType = g_pCICPlayer->GetJobTypes();
    if(trijobType == TRIJOB_NOJOB)
    {
        m_Job_Icon->ShowGWnd(false);
    } else if(trijobType == TRIJOB_TRADER) {
        m_Job_Icon->ShowGWnd(true);
        m_Job_Icon->TB_Func_13("interface\\ifcommon\\com_job_hunter_icon.ddj", 0, 0);
    } else if (trijobType == TRIJOB_THIEF) {
        m_Job_Icon->ShowGWnd(true);
        m_Job_Icon->TB_Func_13("interface\\ifcommon\\com_job_teaf_icon.ddj", 0, 0);
    } else if (trijobType == TRIJOB_HUNTER) {
        m_Job_Icon->ShowGWnd(true);
        m_Job_Icon->TB_Func_13("interface\\ifcommon\\com_job_hunter_icon.ddj", 0, 0);
    }

        reinterpret_cast<void(__thiscall*)(CIFPlayerMiniInfo*)>(0x007B7C60)(this);
}

