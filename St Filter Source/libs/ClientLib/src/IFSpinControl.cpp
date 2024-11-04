 #include "IFSpinButtonCtrl.h"
#include "GlobalHelpersThatHaveNoHomeYet.h"
#include "IFflorian0.h"
#include "GInterface.h"
#include "IFflorian0Guide.h"


#define GDR_SPIN_BTN_NEXT 2
#define GDR_SPIN_BTN_PREV 1
#define GDR_SPIN_TEXT_PAGE 0

GFX_IMPLEMENT_DYNCREATE(CIFSpinControl, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSpinControl, CIFWnd)
                    ONG_COMMAND(GDR_SPIN_BTN_NEXT, &CIFSpinControl::OnNext)
                    ONG_COMMAND(GDR_SPIN_BTN_PREV, &CIFSpinControl::OnPrev)
GFX_END_MESSAGE_MAP()

CIFSpinControl::CIFSpinControl() :
        m_buttonPrev(0),
        m_buttonNext(0),
        m_text(0),
        m_valueCurrent(1),
        m_valueMin(1),
        m_valueMax(1) {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s\n", __FUNCTION__);
#endif
}

void CIFSpinControl::UpdateText() {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s\n", __FUNCTION__);
#endif

    wchar_t buf[8];
    swprintf_s(buf, L"%d", m_valueCurrent);

    m_text->SetText(buf);

    //printf("> " __FUNCTION__ "from id %d\n", this->GetParentControl()->UniqueID());
}

CIFSpinControl::~CIFSpinControl(void)
{
}

void CIFSpinControl::SetMaxValue(int value) {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s(%d)\n", __FUNCTION__, value);
#endif
    m_valueMax = value;
}

int CIFSpinControl::GetMaxValue() const {
    return m_valueMax;
}

void CIFSpinControl::SetMinValue(int value) {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s(%d)\n", __FUNCTION__, value);
#endif
    m_valueMin = value;
}

int CIFSpinControl::GetMinValue() const {
    return m_valueMin;
}

void CIFSpinControl::SetCurrentValue(int value) {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s(%d)\n", __FUNCTION__, value);
#endif
    m_valueCurrent = value;
    UpdateText();
}

int CIFSpinControl::GetCurrentValue() const {
    return m_valueCurrent;
}

bool CIFSpinControl::OnCreate(long ln) {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s(%d)\n", __FUNCTION__, ln);
#endif

    //m_IRM.LoadFromFile("resinfo\\ifspincontrol.txt");
    //m_IRM.CreateInterfaceSection("Create", this);

    RECT labrect = { 16,4,18,12 };
    RECT Butt1rect = { 0,0,16,16 };
    RECT Butt2rect = { 34,0,16,16 };

    m_text = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), labrect, GDR_SPIN_TEXT_PAGE, 0);
    m_buttonPrev = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt1rect, GDR_SPIN_BTN_PREV, 0);
    m_buttonNext = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt2rect, GDR_SPIN_BTN_NEXT, 0);

    m_buttonPrev->TB_Func_13("interface\\ifcommon\\com_left_arrow.ddj", 0, 0);
    m_buttonNext->TB_Func_13("interface\\ifcommon\\com_right_arrow.ddj", 0, 0);

    TB_Func_13("interface\\store\\str_slot_02.ddj", 0, 0);

    UpdateText();


    m_ChestPage=1;
    m_uniquelogpage=1;
    m_Ranklogpage=1;
    m_PointPage=1;
    m_XsmbLichSuPage=1;
    m_CustomNpcPage=1;
    m_SkillBuffPage=1;
    this->ShowGWnd(false);
    return true;
}

void CIFSpinControl::OnPrev() {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s\n", __FUNCTION__);
#endif

    if (m_valueMin >= m_valueCurrent)
        return;

    if (m_valueCurrent < m_valueMin)
        return;

    m_valueCurrent--;

    //now its yours
    //printf("UQ ID %d\n", this->GetParentControl()->UniqueID());


    switch (this->GetParentControl()->UniqueID()) {
        case 19576: {
            m_ChestPage--;
            if (m_ChestPage > 0) {
                m_valueCurrent = m_ChestPage;
                g_pCGInterface->GetChestGUI()->ShowList(m_ChestPage);
            } else {
                m_ChestPage = 1;
                m_valueCurrent = 1;
                return;
            }
        }
            break;
        case 19580: {
            m_uniquelogpage--;
            if (m_uniquelogpage > 0) {
                m_valueCurrent = m_uniquelogpage;
                g_pCGInterface->GetUniqueHistoryGUI()->ShowList(m_uniquelogpage);
            } else {
                m_uniquelogpage = 1;
                m_valueCurrent = 1;
                return;
            }
        }
            break;
        case 19584:
        {
            m_Ranklogpage--;
            if (m_Ranklogpage > 0)
            {
                m_valueCurrent = m_Ranklogpage;
                g_pCGInterface->GetCustomRankGUI()->ShowList(m_Ranklogpage);
            }
            else
            {
                m_Ranklogpage = 1;
                m_valueCurrent = 1;
                return;
            }
        }
            break;
        case 19587:
        {
            m_PointPage--;
            if (m_PointPage > 0)
            {
                m_valueCurrent = m_PointPage;
                g_pCGInterface->GetTotalPointsGUI()->ShowList(m_PointPage);
            }
            else
            {
                m_PointPage = 1;
                m_valueCurrent = 1;
                return;
            }
        }
            break;

        case 19591:
        {
            m_XsmbLichSuPage--;
            if (m_XsmbLichSuPage > 0)
            {
                m_valueCurrent = m_XsmbLichSuPage;
                g_pCGInterface->GetEventXoSoLichSuGUI()->ShowList(m_XsmbLichSuPage);
            }
            else
            {
                m_XsmbLichSuPage = 1;
                m_valueCurrent = 1;
                return;
            }
        }
            break;

        case 19597:
        {
            m_CustomNpcPage--;
            if (m_CustomNpcPage > 0)
            {
                m_valueCurrent = m_CustomNpcPage;
                g_pCGInterface->GetCustomNPCGUI()->ShowList(m_CustomNpcPage);
            }
            else
            {
                m_CustomNpcPage = 1;
                m_valueCurrent = 1;
                return;
            }
        }
            break;

        case 19604:
        {
            m_SkillBuffPage--;
            if (m_SkillBuffPage > 0)
            {
                m_valueCurrent = m_SkillBuffPage;
                g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowList(m_SkillBuffPage);
            }
            else
            {
                m_SkillBuffPage = 1;
                m_valueCurrent = 1;
                return;
            }
        }
            break;

    }
            UpdateText();

    g_CurrentIfUnderCursor = 0;
}

void CIFSpinControl::OnNext() {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s\n", __FUNCTION__);
#endif

    if (m_valueCurrent > m_valueMax)
        return;

    m_valueCurrent++;

    switch (this->GetParentControl()->UniqueID()) {
        case 19576: {
            if (g_pCGInterface->GetChestGUI()->IsPageFull(m_ChestPage, 39)) {
                m_ChestPage++;

                if (g_pCGInterface->GetChestGUI()->IsPageFull(m_ChestPage, 30)) {
                    m_valueCurrent = m_ChestPage;
                    g_pCGInterface->GetChestGUI()->ShowList(m_ChestPage);
                } else {
                    m_valueCurrent = m_ChestPage - 1;
                    m_ChestPage = m_valueCurrent;
                }
            } else {
                return;
            }
        }
            break;
        case 19580: {
            if (g_pCGInterface->GetUniqueHistoryGUI()->IsPageFull(m_uniquelogpage, 39)) {
                m_uniquelogpage++;

                if (g_pCGInterface->GetUniqueHistoryGUI()->IsPageFull(m_uniquelogpage, 30)) {
                    m_valueCurrent = m_uniquelogpage;
                    g_pCGInterface->GetUniqueHistoryGUI()->ShowList(m_uniquelogpage);
                } else {
                    m_valueCurrent = m_uniquelogpage - 1;
                    m_uniquelogpage = m_valueCurrent;
                }
            } else {
                return;
            }
        }
            break;
        case 19584:
        {
            if (g_pCGInterface->GetCustomRankGUI()->IsPageFull(m_Ranklogpage, 39))
            {
                m_Ranklogpage++;

                if (g_pCGInterface->GetCustomRankGUI()->IsPageFull(m_Ranklogpage, 30))
                {
                    m_valueCurrent = m_Ranklogpage;
                    g_pCGInterface->GetCustomRankGUI()->ShowList(m_Ranklogpage);
                }
                else
                {
                    m_valueCurrent = m_Ranklogpage - 1;
                    m_Ranklogpage = m_valueCurrent;
                }
            }
            else
            {
                return;
            }
        }
            break;

        case 19587:
        {
            if (g_pCGInterface->GetTotalPointsGUI()->IsPageFull(m_PointPage, 39))
            {
                m_PointPage++;

                if (g_pCGInterface->GetTotalPointsGUI()->IsPageFull(m_PointPage, 30))
                {
                    m_valueCurrent = m_PointPage;
                    g_pCGInterface->GetTotalPointsGUI()->ShowList(m_PointPage);
                }
                else
                {
                    m_valueCurrent = m_PointPage - 1;
                    m_PointPage = m_valueCurrent;
                }
            }
            else
            {
                return;
            }
        }
            break;

        case 19591:
        {
            if (g_pCGInterface->GetEventXoSoLichSuGUI()->IsPageFull(m_XsmbLichSuPage, 39))
            {
                m_XsmbLichSuPage++;

                if (g_pCGInterface->GetEventXoSoLichSuGUI()->IsPageFull(m_XsmbLichSuPage, 30))
                {
                    m_valueCurrent = m_XsmbLichSuPage;
                    g_pCGInterface->GetEventXoSoLichSuGUI()->ShowList(m_XsmbLichSuPage);
                }
                else
                {
                    m_valueCurrent = m_XsmbLichSuPage - 1;
                    m_XsmbLichSuPage = m_valueCurrent;
                }
            }
            else
            {
                return;
            }
        }
            break;

        case 19597:
        {
            if (g_pCGInterface->GetCustomNPCGUI()->IsPageFull(m_CustomNpcPage, 39))
            {
                m_CustomNpcPage++;

                if (g_pCGInterface->GetCustomNPCGUI()->IsPageFull(m_CustomNpcPage, 30))
                {
                    m_valueCurrent = m_CustomNpcPage;
                    g_pCGInterface->GetCustomNPCGUI()->ShowList(m_CustomNpcPage);
                }
                else
                {
                    m_valueCurrent = m_CustomNpcPage - 1;
                    m_CustomNpcPage = m_valueCurrent;
                }
            }
            else
            {
                return;
            }
        }
            break;

        case 19604:
        {
            if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->IsPageFull(m_SkillBuffPage, 37))
            {
                m_SkillBuffPage++;

                if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->IsPageFull(m_SkillBuffPage, 30))
                {
                    m_valueCurrent = m_SkillBuffPage;
                    g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ShowList(m_SkillBuffPage);
                }
                else
                {
                    m_valueCurrent = m_SkillBuffPage - 1;
                    m_SkillBuffPage = m_valueCurrent;
                }
            }
            else
            {
                return;
            }
        }
            break;

    }


    UpdateText();
    // g_CurrentIfUnderCursor = 0;
}
