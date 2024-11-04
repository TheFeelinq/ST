#include "IFTest.h"
#include "../../../DevKit_DLL/src/NameGenerator.h"
#include <ctime>
#include <BSLib/Debug.h>


#define GDR_FLORIAN0_LABEL 10
#define GDR_FLORIAN0_BTN 11
#define GDR_FLORIAN0_LABEL_TIME 13

#define GDR_FLORIAN0_SPINLIST 25

#define GDR_FLORIAN0_LIST0 100
#define GDR_FLORIAN0_LIST1 101
#define GDR_FLORIAN0_LIST2 102
#define GDR_FLORIAN0_LIST3 103
#define GDR_FLORIAN0_LIST4 104


GFX_IMPLEMENT_DYNCREATE(CIFTest, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFTest, CIFMainFrame)
                    ONG_COMMAND(GDR_FLORIAN0_BTN, &On_BtnClick)
                    ONG_COMMAND(GDR_FLORIAN0_SPINLIST, &On_SpinButtonClick)
                    ONG_WM_4001()
                    ONG_WM_4002()
                    ONG_WM_4003()
                    ONG_VISIBLE_CHANGE()
                    ONG_WM_4005()
                    ONG_WM_4006()
GFX_END_MESSAGE_MAP()


CIFTest::CIFTest(void)
        : m_spin(NULL)
{
    BS_DEBUG("> " __FUNCTION__);
}

CIFTest::~CIFTest(void)
{
    BS_DEBUG("> " __FUNCTION__);
}

bool CIFTest::OnCreate(long ln)
{
    BS_DEBUG("> " __FUNCTION__ "(%d)", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    m_IRM.LoadFromFile("resinfo\\iftest.txt");
    m_IRM.CreateInterfaceSection("Create", this);

    m_mybutton = m_IRM.GetResObj<CIFButton>(GDR_FLORIAN0_BTN, 1);
    m_time_label = m_IRM.GetResObj<CIFStatic>(GDR_FLORIAN0_LABEL_TIME, 1);
    m_custom_label = m_IRM.GetResObj<CIFStatic>(GDR_FLORIAN0_LABEL, 1);
    this->ShowGWnd(false);

    m_list_label[0] = m_IRM.GetResObj<CIFStatic>(GDR_FLORIAN0_LIST0, 1);
    m_list_label[1] = m_IRM.GetResObj<CIFStatic>(GDR_FLORIAN0_LIST1, 1);
    m_list_label[2] = m_IRM.GetResObj<CIFStatic>(GDR_FLORIAN0_LIST2, 1);
    m_list_label[3] = m_IRM.GetResObj<CIFStatic>(GDR_FLORIAN0_LIST3, 1);
    m_list_label[4] = m_IRM.GetResObj<CIFStatic>(GDR_FLORIAN0_LIST4, 1);

    m_spin = m_IRM.GetResObj<CIFSpinButtonCtrl>(GDR_FLORIAN0_SPINLIST, 1);

    const int numberOfRanks = 10;

    GenerateRanks(numberOfRanks);

    ShowPage(0);

    return true;
}

void CIFTest::OnUpdate()
{
    time_t rawtime;
    struct tm * timeinfo;
    wchar_t buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer,sizeof(buffer),L"%d-%m-%Y %H:%M:%S",timeinfo);

    m_time_label->SetText(buffer);
}

void CIFTest::GenerateRanks(int count) {
    ClearRanks();

    for (int i = 0; i < count; i++) {
        AddRank(Rank(rand() % 100000, GenerateRandomName()));
    }
}

void CIFTest::ClearRanks() {
    m_ranks.clear();
}

void CIFTest::AddRank(const Rank &rank) {
    m_ranks.push_back(rank);
    m_ranks.sort();

    const int numberOfRanks = m_ranks.size();
    const int numberOfPages = numberOfRanks / m_sizeOfPage;

    m_spin->SetMaxValue(numberOfPages);
}

void CIFTest::On_BtnClick()
{
    BS_DEBUG("> " __FUNCTION__);

    static int i = 0;

    wchar_t buffer[80];
    swprintf(buffer, L"Hello World (%d)", i++);

    m_custom_label->SetText(buffer);
}

void CIFTest::On_SpinButtonClick()
{
    const int currentPage = m_spin->GetCurrentValue();
    BS_WARNING("Current Page: %d\n", currentPage);
    ShowPage(currentPage);
}

int CIFTest::On4001(int a1, int a2)
{
    BS_DEBUG("> " __FUNCTION__ " ( %p, %p )", a1, a2);
    return 0;
}

int CIFTest::On4002(int a1, int a2)
{
    BS_DEBUG("> " __FUNCTION__ " ( %p, %p )", a1, a2);
    return 0;
}

int CIFTest::On4003(int a1, int a2)
{
    BS_DEBUG("> " __FUNCTION__ " ( %p, %p )", a1, a2);
    return 0;
}

int CIFTest::OnVisibleStateChange(int newstate, int a2)
{
    BS_DEBUG("> " __FUNCTION__ " ( %p, %p )", newstate, a2);
    return 0;
}

int CIFTest::On4005(int a1, int a2)
{
    BS_DEBUG("> " __FUNCTION__ " ( %p, %p )", a1, a2);
    return 0;
}

int CIFTest::On4006(int a1, int a2)
{
    BS_DEBUG("> " __FUNCTION__ " ( %p, %p )", a1, a2);
    return 0;
}
void CIFTest::ShowPage(int page) {
    const int startItem = m_sizeOfPage * page;

    std::n_list<Rank>::const_iterator it = m_ranks.begin();
    std::advance(it, startItem);

    for (int i = 0; i < m_sizeOfPage; ++i) {
        if (it != m_ranks.end()) {
            wchar_t buffer[256];
            swprintf(buffer, L"%d - %s",
                     (*it).points,
                     (*it).name.c_str());

            m_list_label[i]->SetText(buffer);
            std::advance(it, 1);
        } else {
            // Set empty
            m_list_label[i]->SetText(L"");
        }
    }

}
